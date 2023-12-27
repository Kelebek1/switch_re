#include "service.h"
#include "shared.h"

// =================== COMMON ===================

struct nn::audio::common::WorkBufferAllocator {
    /* 0x00 */ s64 workBuffer;
    /* 0x08 */ s64 workbufferSize;
    /* 0x10 */ s64 workBufferCurrentOffset;
};

struct nn::audio::common::UpdateDataHeader {
    /* 0x00 */ u32 revision;
    /* 0x04 */ u32 behaviourSize;
    /* 0x08 */ u32 mempoolSize;
    /* 0x0C */ u32 voiceSize;
    /* 0x10 */ u32 voiceResourceSize;
    /* 0x14 */ u32 effectSize;
    /* 0x18 */ u32 mixSize;
    /* 0x1C */ u32 sinksSize;
    /* 0x20 */ u32 performanceBufferSize;
    /* 0x24 */ char unk_24[4];
    /* 0x28 */ u32 renderInfoSize;
    /* 0x2C */ char unk_2C[0x10];
    /* 0x3C */ u32 size;
}; // size = 0x40

enum nn::audio::SampleFormat : u8 {
    /* 0 */ Invalid,
    /* 1 */ PcmInt8,
    /* 2 */ PcmInt16,
    /* 3 */ PcmInt24,
    /* 4 */ PcmInt32,
    /* 5 */ PcmFloat,
    /* 6 */ Adpcm,
};

enum nn::audio::PlayState : u8 {
    /* 0 */ Started,
    /* 1 */ Stopped,
    /* 2 */ Paused,
};

enum nn::audio::ServerPlayState : s32 {
    /* 0 */ Started,
    /* 1 */ Stopped,
    /* 2 */ RequestStop,
    /* 3 */ Paused,
};

enum VoiceType::SrcQuality : u8 {
    /* 0 */ SrcQuality_Medium,
    /* 1 */ SrcQuality_High,
    /* 2 */ SrcQuality_Low,
};

enum nn::audio::CommandType : u8 {
    /* 0x00 */ Invalid,
    /* 0x01 */ PcmInt16DataSourceCommandVersion1,
    /* 0x02 */ PcmInt16DataSourceCommandVersion2,
    /* 0x03 */ FloatDataSourceCommandVersion1,
    /* 0x04 */ FloatDataSourceCommandVersion2,
    /* 0x05 */ AdpcmDataSourceCommandVersion1,
    /* 0x06 */ AdpcmDataSourceCommandVersion2,
    /* 0x07 */ Volume,
    /* 0x08 */ VolumeRamp,
    /* 0x09 */ BiquadFilter,
    /* 0x0A */ Mix,
    /* 0x0B */ MixRamp,
    /* 0x0C */ MixRampGrouped,
    /* 0x0D */ DepopPrepare,
    /* 0x0E */ DepopForMixBuffers,
    /* 0x0F */ Delay,
    /* 0x10 */ Upsample,
    /* 0x11 */ DownMix6chTo2ch,
    /* 0x12 */ Aux,
    /* 0x13 */ DeviceSink,
    /* 0x14 */ CircularBufferSink,
    /* 0x15 */ Reverb,
    /* 0x16 */ I3dl2Reverb,
    /* 0x17 */ Performance,
    /* 0x18 */ ClearMixBuffer,
    /* 0x19 */ CopyMixBuffer,
    /* 0x1A */ LightLimiterV1,
    /* 0x1B */ LightLimiterV2,
    /* 0x1C */ MultiTapBiquadFilter,
    /* 0x1D */ Capture,
    /* 0x1E */ Compressor,
};

enum EffectState : u8 {
    /* 0 */ Invalid,
    /* 1 */ New,
    /* 2 */ Enabled,
    /* 3 */ Disabled,
};

enum ParameterState : u8 {
    /* 0 */ Initialised,
    /* 1 */ Updating,
    /* 2 */ Updated,
};

// =================== SERVER ===================

struct nn::audio::server::SystemEventHolderPool {
    /* 0x00 */ char unk00[0x28];
    /* 0x28 */ nn::os::SystemEventType event1;
    /* 0x58 */ char unk58[0x10];
    /* 0x68 */ nn::os::SystemEventType event2;
}; // size >= 0x98

// testing for render events
struct nn::audio::server::SystemEventHolderPoolTemp {
    /* 0x00 */ char unk00[0x10];
    /* 0x10 */ char unk10[0x10];
    /* 0x20 */ nn::os::SystemEventType renderEvent1;
    /* 0x50 */ char unk58[0x10];
    /* 0x60 */ nn::os::SystemEventType renderEvent2;
}; // size = 0x90



struct nn::audio::server::AudioRendererManagerImpl::AudioDeviceImpl {
    /* 0x00 */ struct nn::audio::server::AudioRendererManagerImpl* manager;
    /* 0x08 */ s64 appletResourceId;
    /* 0x10 */ u32 revision;
    /* 0x14 */ u32 revision2; // Wrong? initial revision?
    /* 0x18 */ s32 unk_18;
    /* 0x20 */ void* heap;
}; // size = 0x28

struct nn::audio::server::AudioRendererManagerImpl::AudioDevice_Wrap : nn::audio::server::IAudioDevice {
    /* 0x08 */ nn::audio::server::AudioRendererManagerImpl::AudioDeviceImpl impl;
}; // size = 0x30

struct nn::audio::server::AudioRenderSystemManager {
    /* 0x000 */ nn::os::SdkMutexType mutex1;
    /* 0x004 */ nn::os::SdkMutexType mutex2;
    /* 0x008 */ nn::os::Thread thread;
    /* 0x1C8 */ bool active;
    /* 0x1D0 */ struct nn::audio::server::AudioRenderSystem* head;
    /* 0x1D8 */ struct nn::audio::server::AudioRenderSystem* systems;
}; // size = 0x1E0

struct nn::audio::server::AudioRendererManagerImpl::vtbl {
    void (*virt1)(struct nn::audio::server::AudioRendererManagerImpl*);
    void (*virt2)(struct nn::audio::server::AudioRendererManagerImpl*);
    void (*D2)(struct nn::audio::server::AudioRendererManagerImpl*);
    void (*D0)(struct nn::audio::server::AudioRendererManagerImpl*);
};

// contains AudioRendererImpl and AudioDeviceImpl
struct nn::audio::server::AudioRendererManagerImpl {
    /* 0x0000 */ nn::audio::server::AudioRendererManagerImpl::vtbl* __vftable;
    /* 0x0008 */ void* heap1;
    /* 0x0010 */ nn::os::Mutex mutex;
    /* 0x0030 */ nn::lmem::detail::HeapHead heapHead;
    /* 0x00C0 */ char unkC0[0x1770];
    /* 0x1830 */ void* heap2; // same as heap1
    /* 0x1838 */ s32 sessionIds[2];
    /* 0x1840 */ s32 currentSessionCount;
    /* 0x1844 */ nn::os::SdkMutexType sessionLock;
    /* 0x1848 */ char unk1848[0x8];
    /* 0x1850 */ nn::audio::server::AudioRenderSystemManager systemManager;
}; // size = 0x1A30

struct nn::audio::server::AudioRendererManager_Wrap {
    /* 0x000 */ nn::audio::server::IAudioRendererManagerImpl::vtbl* __vftable;
    /* 0x008 */ char unk_08[0x8];
    /* 0x010 */ nn::audio::server::AudioRendererManagerImpl impl;
}; // size = ??

enum ManagerTypes {
    /* 0 */ AudioInManager,
    /* 1 */ AudioOutManager,
    /* 2 */ FinalOutputRecorderManager,
};

struct nn::audio::AudioManager {
  /* 0x0000 */ char threadStack[0x3000];
  /* 0x3000 */ nn::os::MultiWaitType updateEvents[2];
  /* 0x3060 */ nn::os::MultiWaitHolderType managerWaitHolders[3]; // linked to updateEvent[1]
  /* 0x3120 */ nn::os::MultiWaitHolderType terminateWaitHolder;
  /* 0x3160 */ nn::os::SemaphoreType* semaphores[3];
  /* 0x3178 */ void (*bufferRegisterFuncs[3])(struct nn::audio::AudioOutManagerImpl*);  // can be any of the 3 manager types
  /* 0x3190 */ struct nn::audio::AudioOutManagerImpl* managers[3]; // can be any of the 3 manager types
  /* 0x31A8 */ nn::os::EventType terminateEvent;
  /* 0x31D0 */ nn::os::SdkMutexType sdkMutex;
  /* 0x31D8 */ nn::os::Thread thread;
  /* 0x3398 */ bool sessionsStarted;
  /* 0x3399 */ bool needsUpdate; // set to 1 when an event is added to updateEvents[1], which makes it get copied to [0]
  /* 0x339A */ bool running;
};

struct nn::audio::server::AddressInfo {
    /* 0x00 */ void* cpuAddress;
    /* 0x08 */ u64 size;
    /* 0x10 */ struct nn::audio::server::MemoryPoolInfoS* memoryPoolInfo;
    /* 0x18 */ u32 dspAddress;
}; // size = 0x20

enum nn::audio::MemoryPoolInfo::State {
    /* 0 */ Invalid,
    /* 1 */ Aquired,
    /* 2 */ RequestDetach,
    /* 3 */ Detached,
    /* 4 */ RequestAttach,
    /* 5 */ Attached,
    /* 6 */ Released,
};

enum nn::audio::MemoryPoolInfo::ResultState {
    /* 0 */ Success,
    /* 1 */ BadParam,
    /* 2 */ MapFailed,
    /* 3 */ InUse,
};

struct nn::audio::MemoryPoolInfo::InParameter {
    /* 0x00 */ void* cpuAddress;
    /* 0x08 */ u64 size;
    /* 0x10 */ nn::audio::MemoryPoolInfo::State state;
    /* 0x14 */ bool inUse;
    /* 0x18 */ char unk18[0x8];
}; // size = 0x20

struct nn::audio::MemoryPoolInfo::OutParameter {
    /* 0x00 */ nn::audio::MemoryPoolInfo::State state;
    /* 0x04 */ char unk04[0xC];
}; // size = 0x10

struct nn::audio::MemoryPoolInfo {
    /* 0x00 */ void* cpuAddress;
    /* 0x08 */ u64 size;
    /* 0x10 */ nn::audio::MemoryPoolInfo::State state;
    /* 0x14 */ bool inUse;
}; // size >= 0x18

// default proc handle 0xFFFF8001
// this is used sdk side
struct nn::audio::server::MemoryPoolInfo {
    /* 0x00 */ void* cpuAddress;
    /* 0x08 */ void* dspAddress;
    /* 0x10 */ char unk10[0x8];
    /* 0x18 */ u64 size;
    /* 0x20 */ nn::audio::server::MemoryPoolInfo::Location location;
    /* 0x24 */ bool inUse;
    /* 0x28 */ char unk28[0x8];
}; // size = 0x30

// this one is used firmware side
struct nn::audio::server::MemoryPoolInfoS {
    /* 0x00 */ void* cpuAddress;
    /* 0x08 */ u32 dspAddress;
    /* 0x10 */ u64 size;
    /* 0x18 */ nn::audio::server::MemoryPoolInfo::Location location;
    /* 0x1C */ bool inUse;
}; // size = 0x20

struct nn::audio::server::PoolMapper {
    /* 0x00 */ u32 processHandle;
    /* 0x08 */ nn::audio::server::MemoryPoolInfoS* memoryPoolInfo;
    /* 0x10 */ u32 memoryPoolSize;
    /* 0x14 */ bool forceMap;
}; // size = 0x18

struct nn::audio::common::BehaviorParameter::ErrorInfo {
    /* 0x00 */ u32 errorCode;
    /* 0x04 */ u32 unk_04;
    /* 0x08 */ void* address;
}; // size = 0x10

struct nn::audio::common::BehaviorParameter::InParameter {
    /* 0x00 */ u32 revision;
    /* 0x08 */ u64 flags;
}; // size = 0x10

struct nn::audio::common::BehaviorParameter::OutStatus {
    /* 0x00 */ nn::audio::common::BehaviorParameter::ErrorInfo errors[10];
    /* 0xA0 */ u32 errorCount;
    /* 0xA4 */ char unkA4[0xC];
}; // size = 0xB0

struct nn::audio::server::BehaviorInfo {
    /* 0x00 */ u32 processRevision;
    /* 0x04 */ u32 userRevision;
    /* 0x08 */ u64 flags;
    /* 0x10 */ nn::audio::common::BehaviorParameter::ErrorInfo errors[10];
    /* 0xB0 */ u32 errorCount;
}; // size = 0xB4

// input:
//  SplitterInParamHeader
//  SplitterInfo::InParameter * infoCount
//  destinationIds * destinationCount
//  SplitterDestinationData::InParameter * destinationCount

struct nn::audio::SplitterInParamHeader {
    /* 0x00 */ u32 magic; // 'SNDH'
    /* 0x04 */ s32 infoCount;
    /* 0x08 */ s32 destinationCount;
    /* 0x0C */ char unk0C[0x14];
}; // size = 0x20

struct nn::audio::SplitterInfo::InParameter {
    /* 0x00 */ u32 magic; // 'SNDI'
    /* 0x04 */ s32 id;
    /* 0x08 */ s32 sampleRate;
    /* 0x0C */ s32 destinationCount;
    /* 0x10 */ s32 infoCount;
}; // size = 0x14

// sdk-side
struct nn::audio::SplitterInfo {
    /* 0x00 */ void* unk_00; // init'd to this
    /* 0x08 */ void* unk_08; // init'd to this
    /* 0x10 */ bool inUse;
    /* 0x11 */ bool updated;
    /* 0x14 */ s32 id;
    /* 0x18 */ s32 channelCount;
    /* 0x1C */ s32 sampleRate;
    /* 0x20 */ struct nn::audio::SplitterDestinationData* destinationHead;
    /* 0x28 */ struct nn::audio::SplitterDestinationData* destinationData;
}; // size = 0x30

struct nn::audio::SplitterDestinationData::InParameter {
    /* 0x00 */ u32 magic; // 'SNDD'
    /* 0x04 */ s32 id;
    /* 0x08 */ f32 mixVolumes[24];
    /* 0x68 */ s32 mixId;
    /* 0x6C */ bool inUse;
}; // size = 0x70

// sdk-side
struct nn::audio::SplitterDestinationData {
    /* 0x00 */ nn::audio::SplitterDestinationData* prev; // maybe head, not prev
    /* 0x08 */ nn::audio::SplitterDestinationData* next;
    /* 0x10 */ s32 id;
    /* 0x14 */ s32 destinationId;
    /* 0x18 */ f32 mixVolumes[24];
    /* 0x78 */ bool inUse;
    /* 0x79 */ bool needUpdate;
    /* 0x7A */ char unk7A[6]; // padding?
}; // size = 0x80

struct nn::audio::server::SplitterInfo {
    /* 0x00 */ s32 id;
    /* 0x04 */ s32 sampleRate;
    /* 0x08 */ s32 destinationCount;
    /* 0x0C */ bool hasNewConnection;
    /* 0x10 */ struct nn::audio::server::SplitterDestinationData* destinations;
    /* 0x18 */ s32 channelCount;
    /* 0x1C */ char unk1C[0x4];
}; // size = 0x20

struct nn::audio::server::SplitterDestinationData {
    /* 0x00 */ s32 id;
    /* 0x04 */ s32 destinationId;
    /* 0x08 */ f32 mixVolumes[24];
    /* 0x68 */ f32 prevMixVolumes[24];
    /* 0xC8 */ nn::audio::server::SplitterDestinationData* next;
    /* 0xD0 */ bool inUse;
    /* 0xD1 */ bool needUpdate;
    /* 0xD2 */ char unkD2[0xD];
}; // size = 0xE0

struct nn::audio::server::SplitterContext {
    /* 0x00 */ nn::audio::server::SplitterInfo* splitterInfos;
    /* 0x08 */ s32 infoCount;
    /* 0x10 */ nn::audio::server::SplitterDestinationData* splitterDestinations;
    /* 0x18 */ s32 destinationsCount;
    /* 0x1C */ bool splitterBugFixed;
}; // size = 0x20

struct nn::audio::server::VoiceChannelResource::InParameter {
    /* 0x00 */ u32 id;
    /* 0x04 */ f32 mixVolumes[24];
    /* 0x64 */ bool inUse;
    /* 0x65 */ char unk65[0xB];
}; // size = 0x70

struct nn::audio::server::VoiceChannelResource {
    /* 0x00 */ f32 mixVolumes[24];
    /* 0x60 */ f32 prevMixVolumes[24];
    /* 0xC0 */ u32 id; // initialised in a loop to i
    /* 0xC4 */ bool inUse;
    /* 0xC8 */ char unkC8[0x8];
}; // size= 0xD0

struct nn::audio::BiquadFilterState {
    /* 0x00 */ s32 s0;
    /* 0x04 */ s32 s1;
    /* 0x08 */ s32 s2;
    /* 0x0C */ s32 s3;
}; // size = 0x10

struct nn::codec::AdpcmContext {
    /* 0x00 */ u16 header;
    /* 0x02 */ u16 yn1;
    /* 0x04 */ u16 yn2;
}; // size = 0x6

struct nn::audio::VoiceState {
    /* 0x00 */ s64 playedSampleCount;
    /* 0x08 */ s32 offset;
    /* 0x0C */ s32 waveBufferIndex;
    /* 0x10 */ bool waveBufferValid[4];
    /* 0x14 */ s32 waveBufferConsumed;
    /* 0x18 */ s32 sampleHistory[4];
    /* 0x28 */ s32 fraction;
    /* 0x2C */ char unk2C[0x4];
    /* 0x30 */ nn::codec::AdpcmContext adpcmContext;
    /* 0x36 */ char unk36[0xA];
    /* 0x40 */ nn::audio::BiquadFilterState biquadStates[2][2];
    /* 0x80 */ s32 previousSamples[24];
    /* 0xE0 */ s16 adpcmCoeff[16];
}; // size = 0x100

struct nn::audio::server::VoiceContext {
    /* 0x00 */ struct nn::audio::server::VoiceInfo** sortedVoiceInfo;
    /* 0x08 */ struct nn::audio::server::VoiceInfo* voices;
    /* 0x10 */ nn::audio::server::VoiceChannelResource* channelResources;
    /* 0x18 */ nn::audio::VoiceState* cpuState;
    /* 0x20 */ nn::audio::VoiceState* dspState;
    /* 0x28 */ u32 voiceCount;
    /* 0x2C */ u32 activeCount;
}; // size = 0x30

struct nn::audio::server::WaveBuffer {
    /* 0x00 */ nn::audio::server::AddressInfo bufferAddress;
    /* 0x20 */ nn::audio::server::AddressInfo contextAddress;
    /* 0x40 */ s32 startOffset;
    /* 0x44 */ s32 endOffset;
    /* 0x48 */ bool loop;
    /* 0x49 */ bool streamEnded;
    /* 0x4A */ bool sentToDSP;
    /* 0x4C */ s32 loopStartOffset;
    /* 0x50 */ s32 loopEndOffset;
    /* 0x54 */ s32 loopCount;
}; // size = 0x58

struct nn::audio::WaveBuffer {
    /* 0x00 */ u32 dspBuffer;
    /* 0x04 */ u32 bufferSize;
    /* 0x08 */ u32 startOffset;
    /* 0x0C */ u32 endOffset;
    /* 0x10 */ bool loop;
    /* 0x11 */ bool streamEnded;
    /* 0x14 */ u32 dspContext;
    /* 0x18 */ u32 contextSize;
}; // size = 0x1C

struct nn::audio::WaveBufferVersion2 {
    /* 0x00 */ u32 dspBuffer;
    /* 0x04 */ u32 dspContext;
    /* 0x08 */ u32 bufferSize;
    /* 0x0C */ u32 contextSize;
    /* 0x10 */ u32 startOffset;
    /* 0x14 */ u32 endOffset;
    /* 0x18 */ u32 loopStartOffset;
    /* 0x1C */ u32 loopEndOffset;
    /* 0x20 */ u32 loopCount;
    /* 0x24 */ bool loop;
    /* 0x25 */ bool streamEnded;
}; // size = 0x28

struct nn::audio::server::VoiceInfo::WaveBufferInternal {
    /* 0x00 */ u64 address;
    /* 0x08 */ u64 size;
    /* 0x10 */ s32 startOffset;
    /* 0x14 */ s32 endOffset;
    /* 0x18 */ bool loop;
    /* 0x19 */ bool streamEnded;
    /* 0x1A */ bool sentToDSP;
    /* 0x1C */ s32 loopCount;
    /* 0x20 */ u64 contextAddress;
    /* 0x28 */ u64 contextSize;
    /* 0x30 */ s32 loopStart;
    /* 0x34 */ s32 loopEnd;
}; // size = 0x38

struct nn::audio::BiquadFilterParameter {
    /* 0x00 */ bool enabled;
    /* 0x02 */ s16 b[3];
    /* 0x08 */ s16 a[2];
}; // size = 0xC

struct nn::audio::server::VoiceInfo::InParameter {
    /* 0x000 */ s32 id;
    /* 0x004 */ s32 nodeId;
    /* 0x008 */ bool isNew;
    /* 0x009 */ bool inUse;
    /* 0x00A */ nn::audio::PlayState playState;
    /* 0x00B */ nn::audio::SampleFormat sampleFormat;
    /* 0x00C */ s32 sampleRate;
    /* 0x010 */ s32 priority;
    /* 0x014 */ s32 sortOrder;
    /* 0x018 */ s32 channelCount;
    /* 0x01C */ f32 pitch;
    /* 0x020 */ f32 volume;
    /* 0x024 */ nn::audio::BiquadFilterParameter biquads[2];
    /* 0x03C */ s32 waveBufferCount;
    /* 0x040 */ s16 waveBufferIndex;
    /* 0x042 */ char unk_042[0x6];
    /* 0x048 */ void* srcDataAddress;
    /* 0x050 */ void* srcDataSize;
    /* 0x058 */ s32 mixId;
    /* 0x05C */ s32 splitterId;
    /* 0x060 */ nn::audio::server::VoiceInfo::WaveBufferInternal waveBufferInternal[4];
    /* 0x140 */ s32 channelResourceIds[6];
    /* 0x158 */ bool clearVoiceDrop;
    /* 0x159 */ bool flushBufferCount;
    /* 0x15A */ char unk_15A[0x2];
    /* 0x15C */ u8 flags; // bit 0: IsVoicePlayedSampleCountResetAtLoopPointSupported
                          // bit 1: IsVoicePitchAndSrcSkippedSupported
    /* 0x15D */ char unk_15D[0x1];
    /* 0x15E */ VoiceType::SrcQuality srcQuality;
    /* 0x15F */ char unk_15F[0x11];
}; // size = 0x170

struct nn::audio::server::VoiceInfo::OutStatus {
    /* 0x00 */ s64 playedSampleCount;
    /* 0x08 */ s32 waveBuffersConsumed;
    /* 0x0C */ bool voiceDropped;
}; // size = 0x10

// these are bitflags
//enum nn::audio::server::VoiceInfo::flags {
//    /* 0 */ IsVoicePlayedSampleCountResetAtLoopPointSupported,
//    /* 1 */ IsVoicePitchAndSrcSkippedSupported,
//};

struct nn::audio::server::VoiceInfo {
    /* 0x000 */ bool inUse;
    /* 0x001 */ bool isNew;
    /* 0x002 */ bool wasPlaying;
    /* 0x003 */ nn::audio::SampleFormat sampleFormat;
    /* 0x004 */ s32 sampleRate;
    /* 0x008 */ s32 channelCount;
    /* 0x00C */ s32 id;
    /* 0x010 */ s32 nodeId;
    /* 0x014 */ s32 mixId;
    /* 0x018 */ nn::audio::ServerPlayState currentPlayState;
    /* 0x01C */ nn::audio::ServerPlayState oldPlayState;
    /* 0x020 */ u32 priority;
    /* 0x024 */ u32 sortOrder;
    /* 0x028 */ f32 pitch;
    /* 0x02C */ f32 volume;
    /* 0x030 */ f32 prevVolume;
    /* 0x034 */ nn::audio::BiquadFilterParameter biquads[2];
    /* 0x04C */ s32 waveBufferCount;
    /* 0x050 */ s16 waveBufferIndex;
    /* 0x052 */ char unk52[0x2];
    /* 0x054 */ u16 flags;
    /* 0x058 */ nn::audio::server::AddressInfo dataAddress;
    /* 0x078 */ nn::audio::server::WaveBuffer waveBuffers[4];
    /* 0x1D8 */ s32 channelResourceIds[6];
    /* 0x1F0 */ s32 splitterId;
    /* 0x1F4 */ VoiceType::SrcQuality srcQuality;
    /* 0x1F5 */ char unk1F5[0x23];
    /* 0x218 */ bool dropped;
    /* 0x219 */ bool dataUnmapped;
    /* 0x21A */ bool bufferUnmapped;
    /* 0x21B */ bool biquadInitialised[2];
    /* 0x21D */ s8 flushBufferCount;
}; // size = 0x220

struct nn::audio::VoiceInfoManager {
    /* 0x00 */ u32 voiceCount;
    /* 0x08 */ void* voicePtr; // ?
    /* 0x10 */ char unk10[0x10];
    /* 0x20 */ void* tail;
    /* 0x28 */ void* head;
    /* 0x30 */ u32 voiceResourceCount;
    /* 0x34 */ char unk34[0x1C];
    /* 0x50 */ nn::os::SdkRecursiveMutexType mutex;
}; // size = 0x58

enum nn::audio::common::NodeStates::SearchState {
    /* 0 */ Unknown,
    /* 1 */ Found,
    /* 2 */ Complete,
};

struct nn::audio::common::NodeStates::Stack {
    /* 0x00 */ s32* stack;
    /* 0x08 */ s32 size;
    /* 0x0C */ s32 pos;
    /* 0x10 */ s32 unk_10;
}; // size = 0x14?

struct nn::audio::common::EdgeMatrix {
    /* 0x00 */ nn::util::BitArray edges;
    /* 0x0C */ s32 nodeCount;
}; // size = 0x10

struct nn::audio::common::NodeStates {
    /* 0x00 */ s32 nodeCount;
    /* 0x04 */ s32 resultPos;
    /* 0x08 */ nn::audio::common::EdgeMatrix nodesFound;
    /* 0x18 */ nn::audio::common::EdgeMatrix nodesComplete;
    /* 0x28 */ nn::util::BitArray results;
    /* 0x38 */ nn::audio::common::NodeStates::Stack stack;
}; // size = 0x50

struct nn::audio::MixInfo::DirtyInParameter {
    /* 0x00 */ u32 magic;
    /* 0x04 */ u32 count;
    /* 0x08 */ char unk08[0x18];
}; // size = 0x20

struct nn::audio::MixInfo::InParameter {
    /* 0x000 */ f32 volume;
    /* 0x004 */ s32 sampleRate;
    /* 0x008 */ u32 bufferCount;
    /* 0x00C */ bool inUse;
    /* 0x00D */ bool isDirty;
    /* 0x010 */ s32 mixId;
    /* 0x014 */ s32 effectCount;
    /* 0x018 */ s32 nodeId;
    /* 0x01C */ char unk1C[0x8];
    /* 0x024 */ f32 mixVolumes[24 * 24];
    /* 0x924 */ char unk924[0x4];
    /* 0x928 */ s32 destMixId;
    /* 0x92C */ s32 destSplitterId;
}; // size = 0x930

struct nn::audio::server::MixInfo {
    /* 0x000 */ f32 volume;
    /* 0x004 */ s32 sampleRate;
    /* 0x008 */ s32 bufferCount;
    /* 0x00C */ bool inUse;
    /* 0x00D */ bool enabled;
    /* 0x010 */ s32 mixId;
    /* 0x014 */ s32 nodeId;
    /* 0x018 */ s32 bufferOffset; // used for circular buffer
    /* 0x01C */ s32 distanceFromFinalMix;
    /* 0x020 */ void* effectOrderBuffer;
    /* 0x028 */ s32 effectCount;
    /* 0x02C */ s32 destMixId;
    /* 0x030 */ f32 mixVolumes[24 * 24];
    /* 0x930 */ s32 destSplitterId;
    /* 0x934 */ bool longSizePreDelaySupported;
    /* 0x935 */ char unk935[0xB];
}; // size = 0x940

struct nn::audio::server::MixContext {
    /* 0x00 */ nn::audio::server::MixInfo** sortedInfos;
    /* 0x08 */ nn::audio::server::MixInfo* mixInfos;
    /* 0x10 */ s32 count;
    /* 0x18 */ void* effectBuffer;
    /* 0x20 */ s64 effectCount;
    /* 0x28 */ nn::audio::common::NodeStates nodeStates;
    /* 0x78 */ nn::audio::common::EdgeMatrix edgeMatrix;
}; // size = 0x88

enum nn::audio::server::EffectType : u8 {
    /* 0x0 */ Invalid,
    /* 0x1 */ Mix,
    /* 0x2 */ Aux,
    /* 0x3 */ Delay,
    /* 0x4 */ Reverb,
    /* 0x5 */ I3dl2Reverb,
    /* 0x6 */ BiquadFilter,
    /* 0x7 */ LightLimiter,
    /* 0x8 */ Capture,
    /* 0x9 */ Compressor,
};

enum nn::audio::EffectInfo::OutStatus : u8 {
    /* 0 */ Invalid,
    /* 1 */ New,
    /* 2 */ Initialised,
    /* 3 */ Used,
    /* 4 */ Removed,
};

struct nn::audio::EffectResultState {
    /* 0x00 */ char unk00[0x18];
    /* 0x18 */ f32 unk_18[6];
    /* 0x30 */ char unk30[0x50];
}; // size = 0x80

struct nn::audio::EffectInfo::OutParamsVersion1 {
    /* 0x00 */ nn::audio::EffectInfo::OutStatus state;
    /* 0x01 */ char unk01[0xF];
}; // size = 0x10

struct nn::audio::EffectInfo::OutParamsVersion2 {
    /* 0x00 */ nn::audio::EffectInfo::OutStatus state;
    /* 0x01 */ char unk01[0xF];
    /* 0x10 */ nn::audio::EffectResultState resultState;
}; // size = 0x90

struct nn::audio::EffectInfo::InParameterBasic {
    /* 0x00 */ nn::audio::server::EffectType type;
    /* 0x01 */ u8 isNew;
    /* 0x02 */ u8 enabled;
    /* 0x04 */ u32 mixId;
    /* 0x08 */ void* workbufferAddr;
    /* 0x10 */ void* workbufferSize;
    /* 0x18 */ u32 processOrder;
    /* 0x1C */ char unk1C[0x4];
}; // size = 0x20

struct nn::audio::EffectInfo::InParameter {
    /* 0x00 */ nn::audio::server::EffectType type;
    /* 0x01 */ u8 isNew;
    /* 0x02 */ u8 enabled;
    /* 0x04 */ u32 mixId;
    /* 0x08 */ void* workbufferAddr;
    /* 0x10 */ void* workbufferSize;
    /* 0x18 */ u32 processOrder;
    /* 0x1C */ char unk1C[0x4];
    /* 0x20 */ u8 raw[0xA0];
}; // size = 0xC0

struct nn::audio::server::EffectInfoBase::vtable {
    /* 0x00 */ void (*UpdateV1)(struct nn::audio::server::EffectInfoBase*, nn::audio::common::BehaviorParameter::ErrorInfo*, nn::audio::EffectInfo::InParameter*, nn::audio::server::PoolMapper*);
    /* 0x08 */ void (*UpdateV2)(struct nn::audio::server::EffectInfoBase*, nn::audio::common::BehaviorParameter::ErrorInfo*, nn::audio::EffectInfo::InParameter*, nn::audio::server::PoolMapper*);
    /* 0x10 */ void (*UpdateForCommandGeneration)(struct nn::audio::server::EffectInfoBase*);
    /* 0x18 */ void (*InitializeResultState)(struct nn::audio::server::EffectInfoBase*, nn::audio::EffectResultState*);
    /* 0x20 */ void (*UpdateResultState)(struct nn::audio::server::EffectInfoBase*, char*, nn::audio::EffectResultState*);
    /* 0x28 */ void* (*GetWorkBuffer)(struct nn::audio::server::EffectInfoBase*, u32 index); // nn::audio::server::EffectInfoBase::Index
};

struct nn::audio::server::EffectInfoBase {
    /* 0x000 */ nn::audio::server::EffectInfoBase::vtable* __vftable;
    /* 0x008 */ nn::audio::server::EffectType type;
    /* 0x009 */ bool enabled;
    /* 0x00A */ bool shouldSkip;
    /* 0x00B */ EffectState usageState;
    /* 0x00C */ s32 mixId;
    /* 0x010 */ s32 processOrder;
    /* 0x014 */ char unk14[0xC];
    /* 0x020 */ nn::audio::server::AddressInfo workBuffers[2];
    /* 0x060 */ char unk60[0x10];
    /* 0x080 */ nn::audio::EffectInfo::InParameter parameter;
    /* 0x140 */ char stateBuffer[0x380];
}; // size = 0x4B0

struct nn::audio::server::EffectContext {
    /* 0x00 */ nn::audio::server::EffectInfoBase* effectInfos;
    /* 0x08 */ u32 effectCount;
    /* 0x10 */ nn::audio::EffectResultState* resultStateCpu;
    /* 0x18 */ nn::audio::EffectResultState* resultStateDsp;
    /* 0x20 */ s32 stateCount;
}; // size = 0x28

enum nn::audio::common::SinkType : u8 {
    /* 0 */ Invalid,
    /* 1 */ DeviceSink,
    /* 2 */ CircularBufferSink,
};

struct nn::audio::common::SinkInDeviceParameter {
    /* 0x000 */ char name[0x100];
    /* 0x100 */ s32 inputCount;
    /* 0x104 */ s8 inputs[6];
    /* 0x10A */ char unk10A[0x1];
    /* 0x10B */ u8 downMixEnabled;
    /* 0x10C */ f32 downMixCoeff[4];
}; // size 0x11C

struct nn::audio::common::SinkInCircularBufferParameter {
    /* 0x00 */ u64 cpuAddr;
    /* 0x08 */ s32 size;
    /* 0x0C */ s32 inputCount;
    /* 0x10 */ s32 sampleCount;
    /* 0x14 */ s32 previousPos;
    /* 0x18 */ nn::audio::SampleFormat format;
    /* 0x19 */ char unk19[0x3];
    /* 0x1C */ u8 input[6];
    /* 0x22 */ bool inUse;
    /* 0x23 */ char unk23[0x5];
}; // size 0x28

struct nn::audio::common::SinkInParameter {
    /* 0x000 */ nn::audio::common::SinkType type;
    /* 0x001 */ u8 inUse;
    /* 0x004 */ u32 nodeId;
    /* 0x008 */ char unk08[0x18];
    union {
        /* 0x020 */ nn::audio::common::SinkInDeviceParameter device;
        /* 0x020 */ nn::audio::common::SinkInCircularBufferParameter circularBuffer;
    };
}; // size 0x140

struct nn::audio::common::SinkOutStatus {
    /* 0x00 */ u32 writeOffset;
    /* 0x04 */ char unk04[0x1C];
}; // size == 0x20

struct nn::audio::server::SinkInfoBase::vtable {
    /* 0x00 */ void (*Update)(struct nn::audio::server::SinkInfoBase*, nn::audio::common::BehaviorParameter::ErrorInfo*, nn::audio::common::SinkOutStatus*, nn::audio::common::SinkInParameter*, nn::audio::server::PoolMapper*);
    /* 0x08 */ void (*UpdateForCommandGeneration)(struct nn::audio::server::SinkInfoBase*);
};

struct nn::audio::server::SinkInfoBase {
    /* 0x000 */ nn::audio::server::SinkInfoBase::vtable* __vftable;
    /* 0x008 */ nn::audio::common::SinkType type;
    /* 0x009 */ bool inUse;
    /* 0x00A */ bool bufferUnmapped;
    /* 0x00C */ s32 nodeId;
    /* 0x010 */ char unk10[0x10];
    /* 0x020 */ char state[0x30];
    union {
        /* 0x050 */ nn::audio::common::SinkInDeviceParameter device;
        /* 0x050 */ nn::audio::common::SinkInCircularBufferParameter circularBuffer;
    };
}; // size = 0x170

struct nn::audio::server::DeviceSinkState {
    /* 0x00 */ struct nn::audio::UpsamplerInfo* upsamplerInfo;
    /* 0x08 */ s32 downMixCoeff[4]; // Q16
    /* 0x18 */ char unk18[0x18];
}; // size = 0x30

struct nn::audio::server::DeviceSinkInfo {
    /* 0x000 */ nn::audio::server::SinkInfoBase::vtable* __vftable;
    /* 0x008 */ u8 type;
    /* 0x009 */ bool inUse;
    /* 0x00A */ bool bufferUnmapped;
    /* 0x00C */ u32 nodeId;
    /* 0x010 */ char unk10[0x10];
    /* 0x020 */ nn::audio::server::DeviceSinkState state;
    /* 0x050 */ nn::audio::common::SinkInDeviceParameter parameter;
}; // size = 0x16C

struct nn::audio::server::CircularBufferSinkState {
    /* 0x00 */ u32 lastPos2;
    /* 0x04 */ s32 currentPos;
    /* 0x08 */ u32 lastPos;
    /* 0x0C */ char unk0C[0x4];
    /* 0x10 */ nn::audio::server::AddressInfo addressInfo;
}; // size = 0x30

struct nn::audio::server::CircularBufferSinkInfo {
    /* 0x000 */ nn::audio::server::SinkInfoBase::vtable* __vftable;
    /* 0x008 */ u8 type;
    /* 0x009 */ bool inUse;
    /* 0x00A */ bool bufferUnmapped;
    /* 0x00C */ u32 nodeId;
    /* 0x010 */ char unk10[0x10];
    /* 0x020 */ nn::audio::server::CircularBufferSinkState state;
    /* 0x050 */ nn::audio::common::SinkInCircularBufferParameter parameter;
    /* 0x078 */ char pad[0xF4];
}; // size = 0x16C

struct nn::audio::server::SinkContext {
    /* 0x00 */ nn::audio::server::SinkInfoBase* sinkInfos;
    /* 0x08 */ u32 sinkCount;
}; // size = 0x10

struct nn::audio::common::PerformanceEntryVersion1 {
    /* 0x00 */ s32 nodeId;
    /* 0x04 */ s32 startTime; // microseconds
    /* 0x08 */ s32 processedTime;
    /* 0x0C */ u8 entryType; // nn::audio::PerformanceEntryType
}; // size = 0x10

struct nn::audio::common::PerformanceEntryVersion2 {
    /* 0x00 */ s32 nodeId;
    /* 0x04 */ s32 startTime; // microseconds
    /* 0x08 */ s32 processedTime;
    /* 0x0C */ u8 entryType; // nn::audio::PerformanceEntryType
    /* 0x0D */ char unk0D[0xB];
}; // size = 0x18

struct nn::audio::common::PerformanceDetailVersion1 {
    /* 0x00 */ s32 nodeId;
    /* 0x04 */ s32 startTime; // microseconds
    /* 0x08 */ s32 processedTime;
    /* 0x0C */ u8 detailType; // nn::audio::PerformanceDetailType
    /* 0x0D */ u8 entryType; // nn::audio::PerformanceEntryType
}; // size = 0x10

struct nn::audio::common::PerformanceDetailVersion2 {
    /* 0x00 */ s32 nodeId;
    /* 0x04 */ s32 startTime; // microseconds
    /* 0x08 */ s32 processedTime;
    /* 0x0C */ u8 detailType; // nn::audio::PerformanceDetailType
    /* 0x0D */ u8 entryType; // nn::audio::PerformanceEntryType
    /* 0x0E */ char unk0E[0x2];
    /* 0x10 */ char unk10[0x4];
    /* 0x14 */ char unk14[0x4];
}; // size = 0x18

struct nn::audio::common::PerformanceFrameHeaderVersion1 {
    /* 0x00 */ char magic[4];
    /* 0x04 */ s32 entryCount;
    /* 0x08 */ s32 detailCount;
    /* 0x0C */ s32 nextOffset;
    /* 0x10 */ s32 totalProcessingTime;
    /* 0x14 */ s32 frameIndex;
}; // size = 0x18

struct nn::audio::common::PerformanceFrameHeaderVersion2 {
    /* 0x00 */ char magic[4];
    /* 0x04 */ s32 entryCount;
    /* 0x08 */ s32 detailCount;
    /* 0x0C */ s32 nextOffset;
    /* 0x10 */ s32 totalProcessingTime;
    /* 0x14 */ s32 voicesDropped;
    /* 0x18 */ s64 startTime;
    /* 0x20 */ s32 frameIndex;
    /* 0x24 */ bool renderingTimeLimitExceeded;
    /* 0x25 */ char unk25[0xB];
}; // size = 0x30

struct nn::audio::PerformanceInfo {
    /* 0x00 */ nn::audio::common::PerformanceFrameHeaderVersion2* header;
    /* 0x08 */ u64 bufferSize; // ?
    /* 0x10 */ nn::audio::common::PerformanceFrameHeaderVersion2* buffer; // header followed by entries
    /* 0x18 */ nn::audio::common::PerformanceEntryVersion2* entries; // after header
    /* 0x20 */ nn::audio::common::PerformanceDetailVersion2* details; // after details
};

struct nn::audio::server::PerformanceManagerImpl {
    /* 0x00 */ struct nn::audio::server::PerformanceManagerImpl::vtable* __vftable;
    /* 0x08 */ void* buffer;
    /* 0x10 */ void* translatedBuffer;
    /* 0x18 */ s32 historyFrameIndex;
    /* 0x20 */ nn::audio::common::PerformanceFrameHeaderVersion2* frameHeader;
    /* 0x28 */ void* entryBuffer;
    /* 0x30 */ void* detailBuffer;
    /* 0x38 */ s32 entryCount;
    /* 0x3C */ s32 detailCount;
    /* 0x40 */ void* frameHistory;
    /* 0x48 */ nn::audio::common::PerformanceFrameHeaderVersion2* frameHistoryHeader;
    /* 0x50 */ nn::audio::common::PerformanceEntryVersion2* frameHistoryEntries;
    /* 0x58 */ nn::audio::common::PerformanceDetailVersion2* frameHistoryDetails;
    /* 0x60 */ s32 outputFrameIndex;
    /* 0x64 */ s32 lastOutputFrameIndex;
    /* 0x68 */ s32 maxFrames;
    /* 0x6C */ s32 entriesPerFrame;
    /* 0x70 */ s32 maxDetailCount;
    /* 0x78 */ s64 frameSize;
    /* 0x80 */ bool isInitialised;
    /* 0x84 */ s32 targetNodeId;
    /* 0x88 */ s32 version;
    /* 0x8C */ char unk8C[0xC];
}; // size = 0x98?

struct nn::audio::server::PerformanceManagerImpl::vtable {
    /* 0x00 */ void (*D1_PerformanceManagerImpl)();
    /* 0x08 */ void (*D0_PerformanceManagerImpl)();
    /* 0x10 */ void (*Initialize)(nn::audio::server::PerformanceManagerImpl*, u8*, u64, struct nn::audio::detail::AudioRendererParameterInternal *, nn::audio::server::BehaviorInfo *, nn::audio::server::MemoryPoolInfo *);
    /* 0x18 */ bool (*isInitialized)(nn::audio::server::PerformanceManagerImpl*);
    /* 0x20 */ bool (*CopyHistories)(nn::audio::server::PerformanceManagerImpl*, void*, u64);
    /* 0x28 */ bool (*GetNextEntryEntry)(nn::audio::server::PerformanceManagerImpl*, void*, u32, u32); // PerformanceEntryAddresses, PerformanceEntryType, unk
    /* 0x30 */ bool (*GetNextEntryDetail)(nn::audio::server::PerformanceManagerImpl*, void*, u32, u32, u32); // PerformanceEntryAddresses, PerformanceDetailType, PerformanceEntryType, unk
    /* 0x30 */ bool (*GetNextEntry3)(nn::audio::server::PerformanceManagerImpl*, void*, u32**, u32); // PerformanceEntryAddresses, unk, PerformanceSysDetailType, unk
    /* 0x38 */ bool (*SetDetailTarget)(nn::audio::server::PerformanceManagerImpl*, u32);
    /* 0x40 */ bool (*IsDetailTarget)(nn::audio::server::PerformanceManagerImpl*, u32);
    /* 0x48 */ bool (*TapFrame)(nn::audio::server::PerformanceManagerImpl*, bool, s32, s64);
};

struct nn::audio::server::PerformanceManagerImplS {
    /* 0x00 */ nn::audio::server::PerformanceManagerImpl::vtable* __vftable;
    /* 0x08 */ void* buffer;
    /* 0x10 */ u32 translatedBuffer;
    /* 0x14 */ s32 historyFrameIndex;
    /* 0x18 */ nn::audio::common::PerformanceFrameHeaderVersion2* frameHeader;
    /* 0x20 */ nn::audio::common::PerformanceEntryVersion2* entryBuffer;
    /* 0x28 */ nn::audio::common::PerformanceDetailVersion2* detailBuffer;
    /* 0x30 */ s32 entryCount;
    /* 0x34 */ s32 detailCount;
    /* 0x38 */ void* frameHistory;
    /* 0x40 */ nn::audio::common::PerformanceFrameHeaderVersion2* frameHistoryHeader;
    /* 0x48 */ nn::audio::common::PerformanceEntryVersion2* frameHistoryEntries;
    /* 0x50 */ nn::audio::common::PerformanceDetailVersion2* frameHistoryDetails;
    /* 0x58 */ s32 outputFrameIndex;
    /* 0x5C */ s32 lastOutputFrameIndex;
    /* 0x60 */ s32 maxFrames;
    /* 0x64 */ s32 entriesPerFrame;
    /* 0x68 */ s32 maxDetailCount;
    /* 0x70 */ s64 frameSize;
    /* 0x78 */ bool isInitialised;
    /* 0x7C */ s32 targetNodeId;
    /* 0x80 */ s32 version;
    /* 0x84 */ char unk84[0xC];
}; // size = 0x90?

struct nn::audio::server::PerformanceManager {
    /* 0x00 */ nn::audio::server::PerformanceManagerImpl* implPtr;
    /* 0x08 */ nn::audio::server::PerformanceManagerImpl impl;
}; // size = 0xA0

// Firmware side
struct nn::audio::server::PerformanceManagerS {
    /* 0x00 */ nn::audio::server::PerformanceManagerImplS* implPtr;
    /* 0x08 */ nn::audio::server::PerformanceManagerImplS impl;
}; // size = 0x98

struct nn::audio::server::PerformanceInParameter {
    /* 0x00 */ s32 node_id;
    /* 0x04 */ char unk04[0xC];
}; // size = 0x10

struct nn::audio::server::PerformanceOutput {
    /* 0x00 */ s32 historySize;
    /* 0x04 */ char unk04[0xC];
}; // size = 0x10

struct nn::audio::server::PerformanceEntryAddresses {
    /* 0x00 */ u32 translatedAddr;
    /* 0x04 */ u32 entryStartTimeOffset;
    /* 0x08 */ u32 headerEntryCountOffset;
    /* 0x0C */ u32 entryProcessedTimeOffset;
}; // size = 0x10

struct nn::audio::server::PerformanceEntryAddressesV2 {
    /* 0x00 */ u64 translatedAddr;
    /* 0x08 */ u32 entryStartTimeOffset;
    /* 0x0C */ u32 headerEntryCountOffset;
    /* 0x10 */ u32 entryProcessedTimeOffset;
    /* 0x14 */ char padding[0x4];
}; // size = 0x18

struct nn::audio::server::EntryAspect::vtable {
    /* 0x00 */ void (*D2_EntryAspect)();
    /* 0x08 */ void (*D0_EntryAspect)();
};

struct nn::audio::server::EntryAspect {
    /* 0x00 */ nn::audio::server::EntryAspect::vtable* __vftable;
    /* 0x08 */ struct nn::audio::server::CommandGenerator* commandGenerator;
    /* 0x10 */ nn::audio::server::PerformanceEntryAddressesV2 performanceEntryAddress;
    /* 0x28 */ bool initialised;
    /* 0x2C */ s32 nodeId;
}; // size = 0x30

struct nn::audio::server::EntryAspectS {
    /* 0x00 */ nn::audio::server::EntryAspect::vtable* __vftable;
    /* 0x08 */ struct nn::audio::server::CommandGenerator* commandGenerator;
    /* 0x10 */ nn::audio::server::PerformanceEntryAddresses performanceEntryAddress;
    /* 0x20 */ char unk20[0x4];
    /* 0x24 */ bool initialised;
    /* 0x28 */ s32 nodeId;
}; // size = 0x2C

struct nn::audio::server::DetailAspect {
    /* 0x00 */ nn::audio::server::EntryAspect::vtable* __vftable;
    /* 0x08 */ struct nn::audio::server::CommandGenerator* commandGenerator;
    /* 0x10 */ nn::audio::server::PerformanceEntryAddressesV2 performanceEntryAddress;
    /* 0x28 */ s32 nodeId;
    /* 0x2C */ bool initialised;
}; // size = 0x30

struct nn::audio::server::DetailAspectS {
    /* 0x00 */ nn::audio::server::EntryAspect::vtable* __vftable;
    /* 0x08 */ struct nn::audio::server::CommandGenerator* commandGenerator;
    /* 0x10 */ nn::audio::server::PerformanceEntryAddresses performanceEntryAddress;
    /* 0x20 */ char unk20[0x4];
    /* 0x24 */ s32 nodeId;
    /* 0x28 */ bool initialised;
}; // size = 0x2C

struct nn::audio::UpsamplerState {
    /* 0x00 */ s32 ratio; // Q16
    /* 0x04 */ s32 history[20];
    /* 0x54 */ s16 coefficientsSize;
    /* 0x56 */ s16 historyOutputIndex;
    /* 0x58 */ s16 historyInputIndex;
    /* 0x5A */ u8 historyStartIndex;
    /* 0x5B */ u8 historyEndIndex;
    /* 0x5C */ bool initialised;
    /* 0x5D */ u8 sampleIndex;
}; // size = 0x60

struct nn::audio::UpsamplerInfo {
    /* 0x000 */ nn::audio::UpsamplerState states[6];
    /* 0x240 */ struct nn::audio::server::UpsamplerManager* manager;
    /* 0x248 */ f32* samplesPos; // points to its place in work memory, numInfos * 240 samples * 6 channels
    /* 0x250 */ u32 sampleCount;
    /* 0x254 */ s32 inputCount;
    /* 0x258 */ bool enabled;
    /* 0x259 */ s8 inputs[6];
    /* 0x25F */ char unk25F[0x21];
}; // size = 0x280

struct nn::audio::server::UpsamplerManager {
    /* 0x00 */ u32 upsamplerCount;
    /* 0x08 */ nn::audio::UpsamplerInfo* upsamplerInfo;
    /* 0x10 */ void* upsamplerMemory; // ?
    /* 0x18 */ nn::os::SdkRecursiveMutexType mutex;
}; // size >= 0x24

struct nn::audio::server::AudioRendererSystemContext {
    /* 0x00 */ u32 sessionId;
    /* 0x04 */ u32 channels;
    /* 0x08 */ u32 mixBufferCount;
    /* 0x10 */ nn::audio::server::BehaviorInfo* behaviorInfo;
    /* 0x18 */ void* depopBuffer; // rendersystem->unk_28
    /* 0x20 */ nn::audio::server::UpsamplerManager* upsamplerManager;
    /* 0x30 */ nn::audio::server::MemoryPoolInfo* memoryPoolInfo;
}; // size = 0x30

struct nn::audio::server::ICommandProcessingTimeEstimator::vtable {
    u32 (*EstimatePcmInt16DataSourceCommandVersion1)(struct nn::audio::server::CommandProcessingTimeEstimatorVersion1*, struct nn::audio::PcmInt16DataSourceCommandVersion1*);
    u32 (*EstimatePcmInt16DataSourceCommandVersion2)(struct nn::audio::server::CommandProcessingTimeEstimatorVersion1*, struct nn::audio::PcmInt16DataSourceCommandVersion2*);
    u32 (*EstimateAdpcmDataSourceCommandVersion1)(struct nn::audio::server::CommandProcessingTimeEstimatorVersion1*, struct nn::audio::AdpcmDataSourceCommandVersion1*);
    u32 (*EstimateAdpcmDataSourceCommandVersion2)(struct nn::audio::server::CommandProcessingTimeEstimatorVersion1*, struct nn::audio::AdpcmDataSourceCommandVersion2*);
    u32 (*EstimatePcmFloatDataSourceCommandVersion1)(struct nn::audio::server::CommandProcessingTimeEstimatorVersion1*, struct nn::audio::PcmFloatDataSourceCommandVersion1*);
    u32 (*EstimatePcmFloatDataSourceCommandVersion2)(struct nn::audio::server::CommandProcessingTimeEstimatorVersion1*, struct nn::audio::PcmFloatDataSourceCommandVersion2*);
    u32 (*EstimateVolumeCommand)(struct nn::audio::server::CommandProcessingTimeEstimatorVersion1*, struct nn::audio::VolumeCommand*);
    u32 (*EstimateVolumeRampCommand)(struct nn::audio::server::CommandProcessingTimeEstimatorVersion1*, struct nn::audio::VolumeRampCommand*);
    u32 (*EstimateBiquadFilterCommand)(struct nn::audio::server::CommandProcessingTimeEstimatorVersion1*, struct nn::audio::BiquadFilterCommand*);
    u32 (*EstimateMixCommand)(struct nn::audio::server::CommandProcessingTimeEstimatorVersion1*, struct nn::audio::MixCommand*);
    u32 (*EstimateMixRampCommand)(struct nn::audio::server::CommandProcessingTimeEstimatorVersion1*, struct nn::audio::MixRampCommand*);
    u32 (*EstimateMixRampGroupedCommand)(struct nn::audio::server::CommandProcessingTimeEstimatorVersion1*, struct nn::audio::MixRampGroupedCommand*);
    u32 (*EstimateDepopPrepareCommand)(struct nn::audio::server::CommandProcessingTimeEstimatorVersion1*, struct nn::audio::DepopPrepareCommand*);
    u32 (*EstimateDepopForMixBuffersCommand)(struct nn::audio::server::CommandProcessingTimeEstimatorVersion1*, struct nn::audio::DepopForMixBuffersCommand*);
    u32 (*EstimateDelayCommand)(struct nn::audio::server::CommandProcessingTimeEstimatorVersion1*, struct nn::audio::DelayCommand*);
    u32 (*EstimateUpsampleCommand)(struct nn::audio::server::CommandProcessingTimeEstimatorVersion1*, struct nn::audio::UpsampleCommand*);
    u32 (*EstimateDownMix6chTo2chCommand)(struct nn::audio::server::CommandProcessingTimeEstimatorVersion1*, struct nn::audio::DownMix6chTo2chCommand*);
    u32 (*EstimateAuxCommand)(struct nn::audio::server::CommandProcessingTimeEstimatorVersion1*, struct nn::audio::AuxCommand*);
    u32 (*EstimateDeviceSinkCommand)(struct nn::audio::server::CommandProcessingTimeEstimatorVersion1*, struct nn::audio::DeviceSinkCommand*);
    u32 (*EstimateCircularBufferSinkCommand)(struct nn::audio::server::CommandProcessingTimeEstimatorVersion1*, struct nn::audio::CircularBufferSinkCommand*);
    u32 (*EstimateReverbCommand)(struct nn::audio::server::CommandProcessingTimeEstimatorVersion1*, struct nn::audio::ReverbCommand*);
    u32 (*EstimateI3dl2ReverbCommand)(struct nn::audio::server::CommandProcessingTimeEstimatorVersion1*, struct nn::audio::I3dl2ReverbCommand*);
    u32 (*EstimatePerformanceCommand)(struct nn::audio::server::CommandProcessingTimeEstimatorVersion1*, struct nn::audio::PerformanceCommand*);
    u32 (*EstimateClearMixBufferCommand)(struct nn::audio::server::CommandProcessingTimeEstimatorVersion1*, struct nn::audio::ClearMixBufferCommand*);
    u32 (*EstimateCopyMixBufferCommand)(struct nn::audio::server::CommandProcessingTimeEstimatorVersion1*, struct nn::audio::CopyMixBufferCommand*);
    u32 (*EstimateLightLimiterCommandVersion1)(struct nn::audio::server::CommandProcessingTimeEstimatorVersion1*, struct nn::audio::LightLimiterV1Command*);
    u32 (*EstimateLightLimiterCommandVersion2)(struct nn::audio::server::CommandProcessingTimeEstimatorVersion2*, struct nn::audio::LightLimiterV2Command*);
    u32 (*EstimateMultiTapBiquadFilterCommand)(struct nn::audio::server::CommandProcessingTimeEstimatorVersion2*, struct nn::audio::MultiTapBiquadFilterCommand*);
    u32 (*EstimateCaptureCommand)(struct nn::audio::server::CommandProcessingTimeEstimatorVersion1*, struct nn::audio::CaptureCommand*);
    u32 (*EstimateCompressorCommand)(struct nn::audio::server::CommandProcessingTimeEstimatorVersion1*, struct nn::audio::CompressorCommand*);
};

struct nn::audio::server::CommandProcessingTimeEstimatorVersion1 {
    /* 0x00 */ nn::audio::server::ICommandProcessingTimeEstimator::vtable* __vftable;
    /* 0x08 */ u32 sampleCount;
    /* 0x0C */ u32 bufferCount;
}; // size = 0x10

struct nn::audio::server::CommandProcessingTimeEstimatorVersion2 {
    /* 0x00 */ nn::audio::server::ICommandProcessingTimeEstimator::vtable* __vftable;
    /* 0x08 */ u32 sampleCount;
    /* 0x0C */ u32 bufferCount;
}; // size = 0x10

struct nn::audio::server::CommandProcessingTimeEstimatorVersion3 {
    /* 0x00 */ nn::audio::server::ICommandProcessingTimeEstimator::vtable* __vftable;
    /* 0x08 */ u32 sampleCount;
    /* 0x0C */ u32 bufferCount;
}; // size = 0x10

struct nn::audio::server::CommandProcessingTimeEstimatorVersion4 {
    /* 0x00 */ nn::audio::server::ICommandProcessingTimeEstimator::vtable* __vftable;
    /* 0x08 */ u32 sampleCount;
    /* 0x0C */ u32 bufferCount;
}; // size = 0x10

struct nn::audio::server::CommandProcessingTimeEstimatorVersion5 {
    /* 0x00 */ nn::audio::server::ICommandProcessingTimeEstimator::vtable* __vftable;
    /* 0x08 */ u32 sampleCount;
    /* 0x0C */ u32 bufferCount;
}; // size = 0x10

// sdk
struct nn::audio::server::AudioRenderSystem {
    /* 0x000 */ nn::audio::server::AudioRenderSystem* head;
    /* 0x008 */ nn::audio::server::AudioRenderSystem* next;
    /* 0x010 */ bool initialised;
    /* 0x011 */ bool renderActive;
    /* 0x012 */ u8 state;
    /* 0x014 */ s32 sampleRate;
    /* 0x018 */ s32 sampleCount;
    /* 0x01C */ s32 mixBufferCount;
    /* 0x020 */ void* samplesWorkbuffer;
    /* 0x028 */ void* depopBuffer;
    /* 0x030 */ s32 memoryPoolCount;
    /* 0x038 */ nn::audio::server::MemoryPoolInfo* memoryPoolWorkbuffer;
    /* 0x040 */ nn::audio::server::MemoryPoolInfo memoryPoolInfo;
    /* 0x070 */ void* commandWorkbuffer;
    /* 0x078 */ u64 commandWorkbufferSize;
    /* 0x080 */ u64 commandCount;
    /* 0x088 */ nn::audio::server::UpsamplerManager* upsamplerManager;
    /* 0x090 */ nn::audio::UpsamplerInfo* upsamplerInfo;
    /* 0x098 */ s32 upsamplerCount;
    /* 0x09C */ char unk9C[0x4];
    /* 0x0A0 */ nn::audio::server::VoiceContext voiceContext;
    /* 0x0D0 */ nn::audio::server::MixContext mixContext;
    /* 0x158 */ nn::audio::server::EffectContext effectContext;
    /* 0x180 */ nn::audio::server::SinkContext sinkContext;
    /* 0x190 */ nn::audio::server::SplitterContext splitterContext;
    /* 0x1B0 */ void* commandTimeEstimatorPtr; // points to whichever version is active
    /* 0x1B8 */ s32 sessionId;
    /* 0x1BC */ s32 voiceChannels;
    /* 0x1C0 */ nn::os::SystemEvent* dspFinishedEvent;
    /* 0x1C8 */ nn::os::EventType terminateEvent;
    /* 0x1F0 */ nn::os::SdkMutexType lock;
    /* 0x1F4 */ u32 processHandle1;
    /* 0x1F8 */ u64 appletResourceId;
    /* 0x200 */ nn::audio::server::PerformanceManager performanceManager;
    /* 0x2A0 */ void* perfManagerMemory;
    /* 0x2A8 */ void* workBuffer;
    /* 0x2B0 */ void* workBufferSize;
    /* 0x2B8 */ char unk2B8[0x10];
    /* 0x2C8 */ s32 renderingTimeLimitPercent;
    /* 0x2CC */ bool dropVoice;
    /* 0x2CD */ bool resetCommandBuffers;
    /* 0x2D0 */ EXECUTIONMODE executionMode;
    /* 0x2D4 */ u32 renderDevice;
    /* 0x2D8 */ nn::audio::server::CommandProcessingTimeEstimatorVersion1 timeEstimatorv1;
    /* 0x2E8 */ nn::audio::server::CommandProcessingTimeEstimatorVersion2 timeEstimatorv2;
    /* 0x2F8 */ nn::audio::server::CommandProcessingTimeEstimatorVersion3 timeEstimatorv3;
    /* 0x308 */ nn::audio::server::CommandProcessingTimeEstimatorVersion4 timeEstimatorv4;
    /* 0x318 */ nn::audio::server::CommandProcessingTimeEstimatorVersion5 timeEstimatorv5;
    /* 0x328 */ nn::audio::server::BehaviorInfo behaviorInfo;
    /* 0x3E0 */ s64 totalElapsedTicks;
    /* 0x3E8 */ s64 ticksSpentUpdating;
    /* 0x3F0 */ s64 numTimesCommandsGenerated;
    /* 0x3F8 */ void* updateOutput;
    /* 0x400 */ s64 elapsedFrames;
    /* 0x408 */ bool dspRunningBehind;
    /* 0x40C */ s32 voicesDropped;
    /* 0x410 */ s64 renderingStartTick;
}; // size >= 0x418

// firmware
struct nn::audio::server::AudioRenderSystemS {
    /* 0x000 */ nn::audio::server::AudioRenderSystem* head;
    /* 0x008 */ nn::audio::server::AudioRenderSystem* next;
    /* 0x010 */ bool initialised;
    /* 0x011 */ bool renderActive;
    /* 0x012 */ u8 state;
    /* 0x014 */ s32 sampleRate;
    /* 0x018 */ s32 sampleCount;
    /* 0x01C */ s32 mixBufferCount;
    /* 0x020 */ void* samplesWorkbuffer;
    /* 0x028 */ void* depopBuffer;
    /* 0x030 */ s32 memoryPoolCount;
    /* 0x038 */ nn::audio::server::MemoryPoolInfoS* memoryPoolWorkbuffer;
    /* 0x040 */ nn::audio::server::MemoryPoolInfoS memoryPoolInfo;
    /* 0x060 */ void* commandWorkbuffer;
    /* 0x068 */ u64 commandWorkbufferSize;
    /* 0x070 */ u64 commandBufferSize;
    /* 0x078 */ nn::audio::server::UpsamplerManager* upsamplerManager;
    /* 0x080 */ nn::audio::UpsamplerInfo* upsamplerInfo;
    /* 0x088 */ s32 upsamplerCount;
    /* 0x08C */ char unk9C[0x4];
    /* 0x090 */ nn::audio::server::VoiceContext voiceContext;
    /* 0x0C0 */ nn::audio::server::MixContext mixContext;
    /* 0x148 */ nn::audio::server::EffectContext effectContext;
    /* 0x170 */ nn::audio::server::SinkContext sinkContext;
    /* 0x180 */ nn::audio::server::SplitterContext splitterContext;
    /* 0x1A0 */ void* commandTimeEstimatorPtr; // points to whichever version is active
    /* 0x1A8 */ s32 sessionId;
    /* 0x1AC */ s32 voiceChannels;
    /* 0x1B0 */ nn::os::SystemEvent* dspFinishedEvent;
    /* 0x1B8 */ nn::os::EventType terminateEvent;
    /* 0x1E0 */ nn::os::SdkMutexType lock;
    /* 0x1E4 */ u32 processHandle;
    /* 0x1E8 */ u64 appletResourceId;
    /* 0x1F0 */ nn::audio::server::PerformanceManagerS performanceManager;
    /* 0x288 */ void* perfManagerMemory;
    /* 0x290 */ void* workBuffer;
    /* 0x298 */ void* workBufferSize;
    /* 0x2A0 */ char unk2A8[0x10];
    /* 0x2B0 */ s32 renderingTimeLimitPercent;
    /* 0x2B4 */ bool dropVoice;
    /* 0x2B5 */ bool resetCommandBuffers;
    /* 0x2B8 */ EXECUTIONMODE executionMode;
    /* 0x2BC */ u32 renderDevice;
    /* 0x2C0 */ nn::audio::server::CommandProcessingTimeEstimatorVersion1 timeEstimatorv1;
    /* 0x2D0 */ nn::audio::server::CommandProcessingTimeEstimatorVersion2 timeEstimatorv2;
    /* 0x2E0 */ nn::audio::server::CommandProcessingTimeEstimatorVersion3 timeEstimatorv3;
    /* 0x2F0 */ nn::audio::server::CommandProcessingTimeEstimatorVersion4 timeEstimatorv4;
    /* 0x300 */ nn::audio::server::CommandProcessingTimeEstimatorVersion5 timeEstimatorv5;
    /* 0x310 */ nn::audio::server::BehaviorInfo behaviorInfo;
    /* 0x3C8 */ s64 totalElapsedTicks;
    /* 0x3D0 */ s64 ticksSpentUpdating;
    /* 0x3D8 */ s64 numTimesCommandsGenerated;
    /* 0x3E0 */ bool dspBehind;
    /* 0x3E4 */ s32 numVoicesDropped;
    /* 0x3E8 */ s64 elapsedFrames;
    /* 0x3F0 */ bool dspRunningBehind;
    /* 0x3F4 */ s32 voicesDropped;
    /* 0x3F8 */ s64 renderingStartTick;
    /* 0x400 */ f32 voiceDrop;
    /* 0x408 */ char unk408[0x8];
}; // size = 0x410

struct nn::audio::server::AudioRendererManagerImpl::AudioRendererImpl {
    /* 0x000 */ struct nn::audio::server::AudioRendererManagerImpl* manager;
    /* 0x008 */ nn::os::TransferMemoryType transferMemory;
    /* 0x048 */ bool initialised;
    /* 0x049 */ bool hasActiveRenderSystem;
    /* 0x04A */ char unk4A[0x6];
    /* 0x050 */ nn::audio::server::SystemEventHolderPoolTemp* renderEvent; // passed to AudioRenderSystem->dspFinishedEvent
                                                  // needs a signal for games to send a new Update...
    /* 0x058 */ char unk58[0x8];
    /* 0x060 */ nn::audio::server::AudioRenderSystemS renderSystem;
}; // size = 0x470

struct nn::audio::server::AudioRendererManagerImpl::AudioRendererImpl_Wrap {
    /* 0x000 */ nn::audio::server::IAudioRenderer::vtbl* __vftable; // IAudioRenderer
    /* 0x008 */ char unk_08[0x8];
    /* 0x010 */ nn::audio::server::AudioRendererManagerImpl::AudioRendererImpl impl;
    /* 0x480 */ bool initialised;
    /* 0x488 */ void* heap;
}; // size = 0x490

struct nn::audio::server::InfoUpdater {
    /* 0x00 */ char *input;
    /* 0x08 */ char *inputOrigin;
    /* 0x10 */ ulong expectedSize;
    /* 0x18 */ nn::audio::common::UpdateDataHeader *inHeader;
    /* 0x20 */ nn::audio::common::UpdateDataHeader *outHeader;
    /* 0x28 */ char *output;
    /* 0x30 */ char *outputOrigin;
    /* 0x38 */ ulong outputSize;
    /* 0x40 */ nn::audio::server::BehaviorInfo *behaviourInfo;
    /* 0x48 */ u32 processHandle;
};

struct nn::audio::detail::AudioRendererParameterInternal {
    /* 0x00 */ s32 sampleRate;
    /* 0x04 */ s32 sampleCount;
    /* 0x08 */ s32 mixes;
    /* 0x0C */ s32 subMixes;
    /* 0x10 */ s32 voices;
    /* 0x14 */ s32 sinks;
    /* 0x18 */ s32 effects;
    /* 0x1C */ s32 perfFrames;
    /* 0x20 */ u8 voiceDropEnabled;
    /* 0x21 */ u8 unk_21;
    /* 0x22 */ u8 renderingDevice;
    /* 0x23 */ u8 executionMode;
    /* 0x24 */ u32 splitterInfos;
    /* 0x28 */ s32 splitterDestinations;
    /* 0x2C */ s32 externalContextSize;
    /* 0x30 */ s32 revision;
}; // size = 0x34

struct nn::audio::server::CommandBuffer {
    /* 0x00 */ struct nn::audio::server::CommandBuffer::vtable* __vftable;
    /* 0x08 */ struct nn::audio::CommandListHeader* commandList;
    /* 0x10 */ s32 sampleCount;
    /* 0x14 */ s32 sampleRate;
    /* 0x18 */ u64 commandBufferPos;
    /* 0x20 */ u32 commandBufferSize;
    /* 0x24 */ u32 estimatedProcessTime;
    /* 0x28 */ nn::audio::server::MemoryPoolInfo* memoryPool;
    /* 0x30 */ nn::audio::server::CommandProcessingTimeEstimatorVersion1* timeEstimator; // points to whichever ver is active
    /* 0x38 */ nn::audio::server::BehaviorInfo* behaviorInfo;
}; // size = 0x40

struct nn::audio::server::CommandBuffer::vtable {
    /* 0x00 */ void (*D1)(nn::audio::server::CommandBuffer*);
    /* 0x08 */ void (*D0)(nn::audio::server::CommandBuffer*);
};

// =================== COMMAND ===================

struct nn::audio::ICommand {
    /* 0x00 */ u32 magic; // 0xCAFEBABE
    /* 0x04 */ bool enabled;
    /* 0x05 */ nn::audio::CommandType type;
    /* 0x06 */ s16 size;
    /* 0x08 */ u32 estimatedProcessTime;
    /* 0x0C */ u32 nodeId;
}; // size = 0x10

struct nn::audio::PcmInt16DataSourceCommandVersion1 : nn::audio::ICommand {
    /* 0x10 */ VoiceType::SrcQuality srcQuality;
    /* 0x11 */ char pad11[0x3];
    /* 0x14 */ s16 outputIndex;
    /* 0x16 */ u16 flags;
    /* 0x18 */ s32 sampleRate;
    /* 0x1C */ s32 pitch;
    /* 0x20 */ s32 channelIndex;
    /* 0x24 */ s32 channelCount;
    /* 0x28 */ nn::audio::WaveBuffer waveBuffers[4];
    /* 0x98 */ u32 dspVoiceState;
}; // size = 0x9C

struct nn::audio::PcmInt16DataSourceCommandVersion2 : nn::audio::ICommand {
    /* 0x10 */ VoiceType::SrcQuality srcQuality;
    /* 0x11 */ char pad11[0x3];
    /* 0x14 */ s16 outputIndex;
    /* 0x16 */ u16 flags;
    /* 0x18 */ s32 sampleRate;
    /* 0x1C */ s32 pitch;
    /* 0x20 */ s32 channelIndex;
    /* 0x24 */ s32 channelCount;
    /* 0x28 */ nn::audio::WaveBufferVersion2 waveBuffers[4];
    /* 0xC8 */ u32 dspVoiceState;
    /* 0xCC */ char padCC[0x4];
}; // size = 0xD0

struct nn::audio::PcmFloatDataSourceCommandVersion1 : nn::audio::ICommand {
    /* 0x10 */ VoiceType::SrcQuality srcQuality;
    /* 0x11 */ char pad11[0x3];
    /* 0x14 */ s16 outputIndex;
    /* 0x16 */ u16 flags;
    /* 0x18 */ s32 sampleRate;
    /* 0x1C */ s32 pitch;
    /* 0x20 */ s32 channelIndex;
    /* 0x24 */ s32 channelCount;
    /* 0x28 */ nn::audio::WaveBuffer waveBuffers[4];
    /* 0x98 */ u32 dspVoiceState;
}; // size = 0x9C

struct nn::audio::PcmFloatDataSourceCommandVersion2 : nn::audio::ICommand {
    /* 0x10 */ VoiceType::SrcQuality srcQuality;
    /* 0x11 */ char pad11[0x3];
    /* 0x14 */ s16 outputIndex;
    /* 0x16 */ u16 flags;
    /* 0x18 */ s32 sampleRate;
    /* 0x1C */ s32 pitch;
    /* 0x20 */ s32 channelIndex;
    /* 0x24 */ s32 channelCount;
    /* 0x28 */ nn::audio::WaveBufferVersion2 waveBuffers[4];
    /* 0xC8 */ u32 dspVoiceState;
    /* 0xCC */ char padCC[0x4];
}; // size = 0xD0

struct nn::audio::AdpcmDataSourceCommandVersion1 : nn::audio::ICommand {
    /* 0x10 */ VoiceType::SrcQuality srcQuality;
    /* 0x11 */ char pad11[0x3];
    /* 0x14 */ s16 outputIndex;
    /* 0x16 */ u16 flags;
    /* 0x18 */ s32 sampleRate;
    /* 0x1C */ s32 pitch;
    /* 0x20 */ nn::audio::WaveBuffer waveBuffers[4];
    /* 0x90 */ u32 dspVoiceState;
    /* 0x94 */ u32 dspDataAddress;
}; // size = 0x98

struct nn::audio::AdpcmDataSourceCommandVersion2 : nn::audio::ICommand {
    /* 0x10 */ VoiceType::SrcQuality srcQuality;
    /* 0x11 */ char pad11[0x3];
    /* 0x14 */ s16 outputIndex;
    /* 0x16 */ u16 flags;
    /* 0x18 */ s32 sampleRate;
    /* 0x1C */ s32 pitch;
    /* 0x20 */ s32 channelIndex;
    /* 0x24 */ s32 channelCount;
    /* 0x28 */ nn::audio::WaveBufferVersion2 waveBuffers[4];
    /* 0xC8 */ u32 dspVoiceState;
    /* 0xCC */ u32 dspDataAddress;
}; // size = 0xD0

struct nn::audio::VolumeCommand : nn::audio::ICommand {
    /* 0x10 */ char unk10[0x3];
    /* 0x13 */ u8 precision;
    /* 0x14 */ s16 inputIndex;
    /* 0x16 */ s16 outputIndex;
    /* 0x18 */ s32 volume;
}; // size = 0x1C

struct nn::audio::VolumeRampCommand : nn::audio::ICommand {
    /* 0x10 */ char unk10[0x3];
    /* 0x13 */ u8 precision;
    /* 0x14 */ s16 inputIndex;
    /* 0x16 */ s16 outputIndex;
    /* 0x18 */ s32 prevVolume;
    /* 0x1C */ s32 currentVolume;
}; // size = 0x20

struct nn::audio::BiquadFilterInfo::InParameter {
    /* 0x00 */ s8 inputs[6];
    /* 0x06 */ s8 outputs[6];
    /* 0x0C */ s16 b[3];
    /* 0x12 */ s16 a[2];
    /* 0x14 */ u8 channelCount;
    /* 0x15 */ ParameterState state;
    /* 0x16 */ char pad16[0x2];
}; // size = 0x18

struct nn::audio::server::BiquadFilterInfo {
    /* 0x000 */ nn::audio::server::EffectInfoBase::vtable* __vftable;
    /* 0x008 */ nn::audio::server::EffectType type;
    /* 0x009 */ bool enabled;
    /* 0x00A */ bool shouldSkip;
    /* 0x00B */ EffectState usageState;
    /* 0x00C */ s32 mixId;
    /* 0x010 */ s32 processOrder;
    /* 0x014 */ char unk14[0xC];
    /* 0x020 */ nn::audio::server::AddressInfo workBuffers[2];
    /* 0x060 */ char unk60[0x10];
    /* 0x080 */ nn::audio::BiquadFilterInfo::InParameter parameter;
    /* 0x098 */ char padding[0xA8];
    /* 0x140 */ char stateBuffer[0x140];
    /* 0x280 */ char unk270[0x240];
}; // size >= 0x98

struct nn::audio::BiquadFilterType {
    /* 0x00 */ nn::audio::EffectInfo::InParameterBasic param;
    /* 0x20 */ nn::audio::BiquadFilterInfo::InParameter specific;
    /* 0xE0 */ 
};

struct nn::audio::BiquadFilterCommand : nn::audio::ICommand {
    /* 0x10 */ char unk10[0x4];
    /* 0x14 */ s16 input;
    /* 0x16 */ s16 output;
    /* 0x18 */ s16 b[3];
    /* 0x1E */ s16 a[2];
    /* 0x24 */ u32 dspState;
    /* 0x28 */ bool needsInit;
    /* 0x29 */ bool useFloatProcessing;
    /* 0x2A */ char pad2A[0x2];
}; // size = 0x2C

struct nn::audio::MixParameter {
    /* 0x00 */ s8 inputs[24];
    /* 0x18 */ s8 outputs[24];
    /* 0x30 */ f32 volumes[24];
    /* 0x90 */ s32 mixCount;
}; // size = 0x94

struct nn::audio::MixerBufferInfo {
    /* 0x000 */ nn::audio::server::EffectInfoBase::vtable* __vftable;
    /* 0x008 */ nn::audio::server::EffectType type;
    /* 0x009 */ bool enabled;
    /* 0x00A */ bool shouldSkip;
    /* 0x00B */ EffectState usageState;
    /* 0x00C */ s32 mixId;
    /* 0x010 */ s32 processOrder;
    /* 0x014 */ char unk14[0xC];
    /* 0x020 */ nn::audio::server::AddressInfo workBuffers[2];
    /* 0x060 */ char unk60[0x10];
    /* 0x080 */ nn::audio::MixParameter parameter;
    /* 0x0B8 */ char padding[0x88];
    /* 0x140 */ char stateBuffer[0x140];
    /* 0x280 */ char unk270[0x240];
};

struct nn::audio::MixCommand : nn::audio::ICommand {
    /* 0x10 */ char unk10[0x3];
    /* 0x13 */ u8 precision;
    /* 0x14 */ s16 input;
    /* 0x16 */ s16 output;
    /* 0x18 */ s32 volume;
}; // size = 0x1C

struct nn::audio::MixRampCommand : nn::audio::ICommand {
    /* 0x10 */ char unk10[0x3];
    /* 0x13 */ u8 precision;
    /* 0x14 */ s16 inputIndex;
    /* 0x16 */ s16 outputIndex;
    /* 0x18 */ s32 prevVolume;
    /* 0x1C */ s32 currentVolume;
    /* 0x20 */ u32 lastSampleAddr;
}; // size = 0x24

struct nn::audio::MixRampGroupedCommand : nn::audio::ICommand {
    /* 0x010 */ char unk10[0x3];
    /* 0x013 */ u8 precision;
    /* 0x014 */ s32 bufferCount;
    /* 0x018 */ s16 inputIndexes[24];
    /* 0x048 */ s16 outputIndexes[24];
    /* 0x078 */ s32 prevVolumes[24];
    /* 0x0D8 */ s32 currVolumes[24];
    /* 0x138 */ u32 lastSampleAddr;
}; // size = 0x13C

struct nn::audio::DpopPrepareState {
    /* 0x00 */ f32 depopSamples[24];
}; // size = 0x60

struct nn::audio::DepopPrepareCommand : nn::audio::ICommand {
    /* 0x10 */ char unk10[0x4];
    /* 0x14 */ s16 mixBufferIndexes[24];
    /* 0x44 */ u32 prevSamples;
    /* 0x48 */ s32 bufferCount;
    /* 0x4C */ u32 dspDepopBuffer;
}; // size = 0x50

struct nn::audio::DepopForMixBuffersCommand : nn::audio::ICommand {
    /* 0x10 */ char unk10[0x4];
    /* 0x14 */ s32 input;
    /* 0x18 */ s32 count;
    /* 0x1C */ s32 decay;
    /* 0x20 */ u32 depopBuffer;
}; // size = 0x24

struct nn::audio::DelayParameter {
    /* 0x00 */ s8 inputs[6];
    /* 0x06 */ s8 outputs[6];
    /* 0x0C */ s16 numChannelsMax;
    /* 0x0E */ s16 numChannels;
    /* 0x10 */ s32 delayTimeMax;
    /* 0x14 */ s32 delayTime;
    /* 0x18 */ s32 sampleRate;
    /* 0x1C */ s32 inGain;
    /* 0x20 */ s32 feedbackGain;
    /* 0x24 */ s32 wetGain;
    /* 0x28 */ s32 dryGain;
    /* 0x2C */ s32 channelSpread;
    /* 0x30 */ s32 lowPassAmount;
    /* 0x34 */ ParameterState state;
    /* 0x35 */ char unk35[0x3];
    /* 0x38 */ char unk38[0xC];
}; // size = 0x44

struct nn::audio::DelayParameterSet {
    /* 0x00 */ s64 delayTime; // nanoseconds
    /* 0x08 */ s32 inGain;
    /* 0x0C */ s32 feedbackGain;
    /* 0x10 */ s32 dryGain;
    /* 0x14 */ s32 channelSpread;
    /* 0x18 */ s32 lowPassAmount;
}; // size = 0x1C

// Q14
struct nn::audio::DelayLine {
    /* 0x00 */ s32 sampleCountMax;
    /* 0x04 */ s32 sampleCount;
    /* 0x08 */ s32 bufferStart;
    /* 0x0C */ s32 bufferEnd;
    /* 0x10 */ s32 bufferCurrent;
    /* 0x14 */ s32 decayRate; // 0.5f
}; // size = 0x18

struct nn::audio::DelayLineSdk {
    /* 0x00 */ s32 sampleCountMax;
    /* 0x04 */ s32 sampleCount;
    /* 0x08 */ s32* bufferStart;
    /* 0x0C */ s32* bufferEnd;
    /* 0x10 */ s32* bufferCurrent;
    /* 0x14 */ s32 decayRate; // 0.5f
    char unk18[0x4];
}; // size = 0x18

struct nn::audio::DelayState {
    /* 0x000 */ char unk000[0x20];
    /* 0x020 */ nn::audio::DelayLine delayLines[6];
    /* 0x0B0 */ s32 feedbackGain;
    /* 0x0B4 */ s32 delayFeedbackGain;
    /* 0x0B8 */ s32 lowPassCrossGain;
    /* 0x0BC */ s32 lowPassGain;
    /* 0x0C0 */ s32 lowPassFeedbackGain;
    /* 0x0C4 */ s32 lowPassZ[6];
    /* 0x0C8 */ char unk0C8[0x78];
}; // size = 0x140

struct nn::audio::DelayType {
    /* 0x00 */ nn::audio::EffectInfo::InParameterBasic param;
    /* 0x20 */ nn::audio::DelayParameter specific;
};

struct nn::audio::DelayInfo {
    /* 0x000 */ nn::audio::server::EffectInfoBase::vtable* __vftable;
    /* 0x008 */ nn::audio::server::EffectType type;
    /* 0x009 */ bool enabled;
    /* 0x00A */ bool shouldSkip;
    /* 0x00B */ EffectState usageState;
    /* 0x00C */ s32 mixId;
    /* 0x010 */ s32 processOrder;
    /* 0x014 */ char unk14[0xC];
    /* 0x020 */ nn::audio::server::AddressInfo workBuffers[2];
    /* 0x060 */ char unk60[0x10];
    /* 0x080 */ nn::audio::DelayParameter parameter;
    /* 0x0B8 */ char padding[0x88];
    /* 0x140 */ char stateBuffer[0x140];
    /* 0x280 */ char unk270[0x240];
};

struct nn::audio::DelayCommand : nn::audio::ICommand {
    /* 0x10 */ char unk10[0x4];
    /* 0x14 */ s16 inputs[6];
    /* 0x20 */ s16 outputs[6];
    /* 0x2C */ nn::audio::DelayParameter param;
    /* 0x70 */ u32 dspStateBuffer;
    /* 0x74 */ u32 dspWorkBuffer;
    /* 0x78 */ bool enabled;
    /* 0x79 */ bool longSizePreDelaySupported;
    /* 0x7A */ char pad7A[0x2];
    /* 0x7C */ char pad7C[0x4];
}; // size = 0x80

struct nn::audio::UpsampleCommand : nn::audio::ICommand {
    /* 0x10 */ char unk10[0x4];
    /* 0x14 */ u32 dspSamplesBuffer;
    /* 0x18 */ u32 dspUnkBuffer;
    /* 0x1C */ u32 bufferCount;
    /* 0x20 */ u32 unk_20;
    /* 0x24 */ u32 targetSampleCount;
    /* 0x28 */ u32 targetSampleRate;
    /* 0x2C */ nn::audio::UpsamplerInfo* dspUpsamplerInfo;
}; // size = 0x30

// channels:
//      0 - front left
//      1 - front right
//      2 - center
//      3 - lfe
//      4 - back left
//      5 - back right
struct nn::audio::DownMix6chTo2chCommand : nn::audio::ICommand {
    /* 0x10 */ char unk10[0x4];
    /* 0x14 */ s16 inputs[6];
    /* 0x20 */ s16 outputs[6];
    /* 0x2C */ f32 downMixCoeff[4];
    /* 0x3C */ char unk3C[0x4];
}; // size = 0x40

struct nn::audio::AuxParameter {
    /* 0x00 */ s8 inputs[24];
    /* 0x18 */ s8 outputs[24];
    /* 0x30 */ s32 mixBufferCount;
    /* 0x34 */ s32 sampleRate;
    /* 0x38 */ s32 countMax;
    /* 0x3C */ s32 mixBufferCountMax;
    /* 0x40 */ s64 sendBufferInfoAddress;
    /* 0x48 */ s64 sendBufferStorageAddress;
    /* 0x50 */ s64 returnBufferInfoAddress;
    /* 0x58 */ s64 returnBufferStorageAddress;
    /* 0x60 */ s32 mixBufferSampleSize;
    /* 0x64 */ s32 sampleCount;
    /* 0x68 */ s32 mixBufferSampleCount;
    /* 0x6C */ char unk6C[0x54];
}; // size = 0xC0

struct nn::audio::AuxInfo::InParameter {
    /* 0x00 */ nn::audio::EffectInfo::InParameterBasic param;
    /* 0x20 */ nn::audio::AuxParameter specific;
};

struct nn::audio::server::AuxInfo {
    /* 0x000 */ nn::audio::server::EffectInfoBase::vtable* __vftable;
    /* 0x008 */ nn::audio::server::EffectType type;
    /* 0x009 */ bool enabled;
    /* 0x00A */ bool shouldSkip;
    /* 0x00B */ EffectState usageState;
    /* 0x00C */ s32 mixId;
    /* 0x010 */ s32 processOrder;
    /* 0x014 */ char unk14[0xC];
    /* 0x020 */ nn::audio::server::AddressInfo workBuffers[2];
    /* 0x060 */ u32 dspSendBufferInfo;
    /* 0x064 */ u32 dspSendBufferInfoBase;
    /* 0x068 */ u32 dspReturnBufferInfo;
    /* 0x06C */ u32 dspReturnBufferInfoBase;
    /* 0x080 */ nn::audio::AuxParameter parameter;
    /* 0x140 */ char stateBuffer[0x140];
    /* 0x280 */ char unk270[0x240];
};

struct nn::audio::AuxInfoDsp {
    /* 0x00 */ s32 readOffset;
    /* 0x04 */ s32 writeOffset;
    /* 0x08 */ s32 lostSampleCount;
    /* 0x0C */ s32 totalSampleCount;
    /* 0x10 */ char unk10[0x30];
}; // size = 0x40

// Sdk side
struct nn::audio::AuxInfoDspSdk {
    /* 0x00 */ s32* readOffset;
    /* 0x08 */ s32* writeOffset;
    /* 0x10 */ s32* lostSampleCount;
    /* 0x18 */ s32* totalSampleCount;
    /* 0x20 */ char unk20[0x20];
}; // size = 0x40

struct nn::audio::AuxBufferInfo {
    /* 0x00 */ nn::audio::AuxInfoDsp cpuInfo;
    /* 0x40 */ nn::audio::AuxInfoDsp dspInfo;
}; // size = 0x80

struct nn::audio::AuxBufferInfoSdk {
    /* 0x00 */ nn::audio::AuxInfoDspSdk cpuInfo;
    /* 0x40 */ nn::audio::AuxInfoDspSdk dspInfo;
}; // size = 0x80

struct nn::audio::AuxCommand : nn::audio::ICommand {
    /* 0x10 */ char unk10[0x4];
    /* 0x14 */ s16 input;
    /* 0x16 */ s16 output;
    /* 0x18 */ u32 sendBufferInfo;
    /* 0x1C */ u32 returnBufferInfo;
    /* 0x20 */ u32 sendBufferInfoBase;
    /* 0x24 */ u32 returnBufferInfoBase;
    /* 0x28 */ u32 countMax;
    /* 0x2C */ u32 writeOffset;
    /* 0x30 */ u32 updateCount;
    /* 0x34 */ bool enabled;
}; // size = 0x38

struct nn::audio::DeviceSinkCommand : nn::audio::ICommand {
    /* 0x010 */ char unk10[0x4];
    /* 0x014 */ char name[0x100];
    /* 0x114 */ s32 sessionId;
    /* 0x118 */ u32 dspSampleBuffer;
    /* 0x11C */ s32 inputCount;
    /* 0x120 */ s16 inputs[6];
    /* 0x12C */ char unk12C[0x4];
}; // size = 0x130

struct nn::audio::CircularBufferSinkCommand : nn::audio::ICommand {
    /* 0x10 */ char unk10[0x4];
    /* 0x14 */ s32 inputCount;
    /* 0x18 */ s16 input[6];
    /* 0x24 */ u32 address;
    /* 0x28 */ s32 size;
    /* 0x2C */ s32 pos;
    /* 0x30 */ char unk30[0x4];
}; // size = 0x34

struct nn::audio::ReverbState {
    /* 0x000 */ nn::audio::DelayLine preDelayLine;
    /* 0x018 */ nn::audio::DelayLine centerDelayLine;
    /* 0x030 */ s32 earlyDelayTimes[10];
    /* 0x058 */ s32 earlyGains[10];
    /* 0x080 */ s32 preDelayTime;
    /* 0x084 */ nn::audio::DelayLine decayDelayLines[4];
    /* 0x0E0 */ nn::audio::DelayLine fdnDelayLines[4];
    /* 0x140 */ s32 hfDecayGain[4];
    /* 0x150 */ s32 hfDecayPrevGain[4];
    /* 0x160 */ s32 previousFeedbackOutput[4];
    /* 0x170 */ char unk170[0xD0];
}; // size = 0x240

struct nn::audio::ReverbStateSdk {
    /* 0x000 */ nn::audio::DelayLineSdk preDelayLine;
    /* 0x018 */ nn::audio::DelayLineSdk centerDelayLine;
    /* 0x030 */ s32 earlyDelayTimes[10];
    /* 0x058 */ s32 earlyGains[10];
    /* 0x080 */ s32 preDelayTime;
    /* 0x084 */ nn::audio::DelayLineSdk decayDelayLines[4];
    /* 0x0E0 */ nn::audio::DelayLineSdk fdnDelayLines[4];
    /* 0x140 */ char unk140[0x100];
}; // size = 0x240

// Q14
struct nn::audio::ReverbParameter {
    /* 0x00 */ s8 inputs[6];
    /* 0x06 */ s8 outputs[6];
    /* 0x0C */ s16 channelCountMax;
    /* 0x0E */ s16 channelCount;
    /* 0x10 */ s32 sampleRate;
    /* 0x14 */ s32 earlyMode;
    /* 0x18 */ s32 earlyGain;
    /* 0x1C */ s32 preDelay;
    /* 0x20 */ s32 lateMode;
    /* 0x24 */ s32 lateGain;
    /* 0x28 */ s32 decayTime;
    /* 0x2C */ s32 highFreqDecayRatio;
    /* 0x30 */ s32 colouration;
    /* 0x34 */ s32 baseGain;
    /* 0x38 */ s32 outGain;
    /* 0x3C */ s32 dryGain;
    /* 0x40 */ ParameterState usage;
}; // size = 0x44

struct nn::audio::ReverbInfo {
    /* 0x000 */ nn::audio::server::EffectInfoBase::vtable* __vftable;
    /* 0x008 */ nn::audio::server::EffectType type;
    /* 0x009 */ bool enabled;
    /* 0x00A */ bool shouldSkip;
    /* 0x00B */ EffectState usageState;
    /* 0x00C */ s32 mixId;
    /* 0x010 */ s32 processOrder;
    /* 0x014 */ char unk14[0xC];
    /* 0x020 */ nn::audio::server::AddressInfo workBuffers[2];
    /* 0x060 */ char unk60[0x10];
    /* 0x080 */ nn::audio::ReverbParameter parameter;
    /* 0x0C4 */ char padding[0x7C];
    /* 0x140 */ char stateBuffer[0x140];
    /* 0x280 */ char unk270[0x240];
}; // size = 0x4B0

struct nn::audio::ReverbType {
    /* 0x00 */ nn::audio::EffectInfo::InParameterBasic param;
    /* 0x20 */ nn::audio::ReverbParameter specific;
};

struct nn::audio::ReverbCommand : nn::audio::ICommand {
    /* 0x10 */ char unk10[0x4];
    /* 0x14 */ s16 inputs[6];
    /* 0x20 */ s16 outputs[6];
    /* 0x2C */ nn::audio::ReverbParameter parameter;
    /* 0x70 */ u32 state;
    /* 0x74 */ u32 workBuffer;
    /* 0x78 */ bool enabled;
    /* 0x79 */ bool longSizePreDelaySupported;
    /* 0x7A */ char unk7A[0x6];
}; // size = 0x80

struct nn::audio::I3dl2ReverbParameterSet {
    /* 0x00 */ f32 roomGain;
    /* 0x04 */ f32 roomHFGain;
    /* 0x08 */ f32 lateReverbDecayTime;
    /* 0x0C */ f32 lateReverbHFDecayRatio;
    /* 0x10 */ f32 reflectionGain;
    /* 0x14 */ f32 reflectionDelay;
    /* 0x18 */ f32 reverbGain;
    /* 0x1C */ f32 lateReverbDelayTime;
    /* 0x20 */ f32 lateReverbDiffusion;
    /* 0x24 */ f32 lateReverbDensity;
    /* 0x28 */ f32 referenceHF;
    /* 0x2C */ f32 dryGain;
}; // size = 0x30

struct nn::audio::I3dl2ReverbParameter {
    /* 0x00 */ s8 inputs[6];
    /* 0x06 */ s8 outputs[6];
    /* 0x0C */ u16 channelCountMax;
    /* 0x0E */ u16 channelCount;
    /* 0x10 */ char unk10[0x4];
    /* 0x14 */ s32 sampleRate;
    /* 0x18 */ f32 roomHFGain;
    /* 0x1C */ f32 referenceHF;
    /* 0x20 */ f32 lateReverbDecayTime;
    /* 0x24 */ f32 lateReverbHFDecayRatio;
    /* 0x28 */ f32 roomGain;
    /* 0x2C */ f32 reflectionGain;
    /* 0x30 */ f32 reverbGain;
    /* 0x34 */ f32 lateReverbDiffusion;
    /* 0x38 */ f32 reflectionDelay;
    /* 0x3C */ f32 lateReverbDelayTime;
    /* 0x40 */ f32 lateReverbDensity;
    /* 0x44 */ f32 dryGain;
    /* 0x48 */ ParameterState state;
    /* 0x49 */ char unk49[0x3];
}; // size = 0x4C

struct nn::audio::server::I3dl2ReverbInfo {
    /* 0x000 */ nn::audio::server::EffectInfoBase::vtable* __vftable;
    /* 0x008 */ nn::audio::server::EffectType type;
    /* 0x009 */ bool enabled;
    /* 0x00A */ bool shouldSkip;
    /* 0x00B */ EffectState usageState;
    /* 0x00C */ s32 mixId;
    /* 0x010 */ s32 processOrder;
    /* 0x014 */ char unk014[0xC];
    /* 0x020 */ nn::audio::server::AddressInfo workBuffers[2];
    /* 0x060 */ char unk060[0x10];
    /* 0x080 */ nn::audio::I3dl2ReverbParameter parameter;
    /* 0x0CC */ char unk0BC[0x74];
    /* 0x140 */ char stateBuffer[0x380];
}; // size = 0x4B0

struct nn::audio::I3dl2DelayLine {
    /* 0x00 */ f32* bufferStart;
    /* 0x04 */ f32* bufferEnd;
    /* 0x08 */ s32 maxDelay;
    /* 0x0C */ f32* input;
    /* 0x10 */ f32* output;
    /* 0x14 */ s32 delay;
    /* 0x18 */ f32 wetGain;
}; // size = 0x1C

struct nn::audio::I3dl2ReverbState {
    /* 0x000 */ f32 lowpass_0;
    /* 0x004 */ f32 lowpass_1;
    /* 0x008 */ f32 lowpass_2;
    /* 0x00C */ nn::audio::I3dl2DelayLine earlyDelayLine;
    /* 0x028 */ s32 earlyTapSteps[20];
    /* 0x078 */ f32 earlyGain;
    /* 0x07C */ f32 lateGain;
    /* 0x080 */ s32 earlyToLateTaps;
    /* 0x084 */ nn::audio::I3dl2DelayLine fdnDelayLine[4];
    /* 0x0F4 */ nn::audio::I3dl2DelayLine decayDelayLine0[4];
    /* 0x164 */ nn::audio::I3dl2DelayLine decayDelayLine1[4];
    /* 0x1D4 */ f32 lastReverbEcho;
    /* 0x1D8 */ nn::audio::I3dl2DelayLine centerDelayLine;
    /* 0x1F4 */ f32 lpfCoefficients[4][3];
    /* 0x224 */ f32 shelfFilter[4];
    /* 0x234 */ f32 dryGain;
    /* 0x238 */ char unk238[0x148];
}; // size = 0x380

struct nn::audio::I3dl2ReverbType {
    /* 0x00 */ nn::audio::EffectInfo::InParameterBasic param;
    /* 0x20 */ nn::audio::I3dl2ReverbParameter specific;
};

struct nn::audio::I3dl2ReverbCommand : nn::audio::ICommand {
    /* 0x10 */ char unk10[0x4];
    /* 0x14 */ s16 inputs[6];
    /* 0x20 */ s16 outputs[6];
    /* 0x2C */ nn::audio::I3dl2ReverbParameter parameter;
    /* 0x78 */ u32 state;
    /* 0x7C */ u32 workBuffer;
    /* 0x80 */ bool enabled;
}; // size = 0x84

enum nn::audio::PerformanceEntryType {
    /* 0 */ Invalid,
    /* 1 */ Voice,
    /* 2 */ SubMix,
    /* 3 */ FinalMix,
    /* 3 */ Sink,
};

enum nn::audio::PerformanceDetailType {
    /*  0 */ Invalid,
    /*  1 */ Unk1,
    /*  2 */ Unk2,
    /*  3 */ Unk3,
    /*  4 */ Unk4,
    /*  5 */ Unk5,
    /*  6 */ Unk6,
    /*  7 */ Unk7,
    /*  8 */ Unk8,
    /*  9 */ Unk9,
    /* 10 */ Unk10,
    /* 11 */ Unk11,
    /* 12 */ Unk12,
};

enum nn::audio::PerformanceState {
    /* 0 */ Invalid,
    /* 1 */ Start,
    /* 2 */ Stop,
};

struct nn::audio::PerformanceCommand : nn::audio::ICommand {
    /* 0x10 */ char unk10[0x4];
    /* 0x14 */ nn::audio::PerformanceState state;
    /* 0x18 */ nn::audio::server::PerformanceEntryAddresses performanceEntryAddress;
}; // size = 0x28

struct nn::audio::PerformanceCommandV2 : nn::audio::ICommand {
    /* 0x10 */ char unk10[0x10];
    /* 0x20 */ nn::audio::PerformanceState state;
    /* 0x24 */ char unk24[0x4];
    /* 0x28 */ nn::audio::server::PerformanceEntryAddressesV2 performanceEntryAddress;
}; // size = 0x40 in firmware >= 13.3

struct nn::audio::ClearMixBufferCommand : nn::audio::ICommand {
    /* 0x10 */ char unk10[0x4];
}; // size = 0x14

struct nn::audio::CopyMixBufferCommand : nn::audio::ICommand {
    /* 0x10 */ char unk10[0x4];
    /* 0x14 */ s16 inputIndex;
    /* 0x16 */ s16 outputIndex;
}; // size = 0x18

struct nn::audio::LightLimiterParameter {
    /* 0x00 */ s8 inputs[6];
    /* 0x06 */ s8 outputs[6];
    /* 0x0C */ s16 channelCountMax;
    /* 0x0E */ s16 channelCount;
    /* 0x0C */ s32 sampleRate;
    /* 0x14 */ s32 lookAheadTimeMax;
    /* 0x18 */ s32 attackTime;
    /* 0x1C */ s32 releaseTime;
    /* 0x20 */ s32 lookAheadTime;
    /* 0x24 */ f32 attackCoeff;
    /* 0x28 */ f32 releaseCoeff;
    /* 0x2C */ f32 threshold;
    /* 0x30 */ f32 inputGain;
    /* 0x34 */ f32 outputGain;
    /* 0x38 */ s32 lookAheadSamplesMin;
    /* 0x3C */ s32 lookAheadSamplesMax;
    /* 0x40 */ ParameterState state;
    /* 0x41 */ bool statisticsEnabled;
    /* 0x42 */ bool statisticsResetRequired;
    /* 0x43 */ u8 processingMode;
}; // size = 0x44

struct nn::audio::LightLimiterStatisticsInternal {
    /* 0x00 */ f32 channelMaxSample[6];
    /* 0x18 */ f32 channelCompressionGainMin[6];
}; // size = 0x30

struct nn::audio::LightLimiterType {
    /* 0x00 */ nn::audio::EffectInfo::InParameterBasic param;
    /* 0x20 */ nn::audio::LightLimiterParameter specific;
    /* 0x64 */ char padding64[0x5C];
    /* 0xC0 */ EffectState state;
    /* 0xC4 */ char unkC4[0xC];
    /* 0xD0 */ nn::audio::LightLimiterStatisticsInternal resultState;
}; // size = 0x100

struct nn::audio::LightLimiterState {
    /* 0x00 */ f32* detectorAverage;
    /* 0x08 */ f32* compressionGain;
    /* 0x10 */ f32* lookAheadSampleBuffers;
    /* 0x18 */ s32* lookAheadSampleOffsets;
    /* 0x20 */ char unk20[0x20];
}; // size = 0x40

struct nn::audio::server::LightLimiterInfo {
    /* 0x000 */ nn::audio::server::EffectInfoBase::vtable* __vftable;
    /* 0x008 */ nn::audio::server::EffectType type;
    /* 0x009 */ bool enabled;
    /* 0x00A */ bool shouldSkip;
    /* 0x00B */ EffectState usageState;
    /* 0x00C */ s32 mixId;
    /* 0x010 */ s32 processOrder;
    /* 0x014 */ char unk14[0xC];
    /* 0x020 */ nn::audio::server::AddressInfo workBuffers[2];
    /* 0x060 */ char unk60[0x10];
    /* 0x080 */ nn::audio::LightLimiterParameter parameter;
    /* 0x0C4 */ char padding[0x7C];
    /* 0x140 */ char stateBuffer[0x140];
    /* 0x280 */ char unk270[0x240];
}; // size = 0x4B0

struct nn::audio::LightLimiterV1Command : nn::audio::ICommand {
    /* 0x10 */ s16 inputs[6];
    /* 0x1C */ s16 outputs[6];
    /* 0x28 */ nn::audio::LightLimiterParameter param;
    /* 0x6C */ u32 dspStateBuffer; // nn::audio::LightLimiterState
    /* 0x70 */ u32 dspWorkBuffer;
    /* 0x74 */ bool enabled;
}; // size = 0x78

struct nn::audio::LightLimiterV2Command : nn::audio::ICommand {
    /* 0x10 */ s16 inputs[6];
    /* 0x1C */ s16 outputs[6];
    /* 0x28 */ nn::audio::LightLimiterParameter param;
    /* 0x6C */ u32 dspStateBuffer; // nn::audio::LightLimiterState
    /* 0x70 */ u32 dspWorkBuffer;
    /* 0x74 */ u32 dspResultStateBuffer; // nn::audio::LightLimiterStatisticsInternal
    /* 0x78 */ bool enabled;
}; // size = 0x7C

struct nn::audio::MultiTapBiquadFilterCommand : nn::audio::ICommand {
    /* 0x10 */ char unk10[0x4];
    /* 0x14 */ s16 inputIndex;
    /* 0x16 */ s16 outputIndex;
    /* 0x18 */ char unk18[0x2];
    /* 0x1A */ s16 biquad1b[3];
    /* 0x20 */ s16 biquad2b[3];
    /* 0x24 */ s16 biquad1a[2];
    /* 0x2A */ s16 biquad2a[2];
    /* 0x30 */ u32 dspState1;
    /* 0x34 */ u32 dspState2;
    /* 0x38 */ bool biquad1NeedsInit;
    /* 0x39 */ bool biquad2NeedsInit;
    /* 0x3A */ u8 filterTapCount;
}; // size = 0x3C

struct nn::audio::CaptureInfo::InParameter {
    /* 0x00 */ nn::audio::EffectInfo::InParameterBasic param;
    /* 0x20 */ nn::audio::AuxParameter specific;
};

struct nn::audio::server::CaptureInfo {
    /* 0x000 */ nn::audio::server::EffectInfoBase::vtable* __vftable;
    /* 0x008 */ nn::audio::server::EffectType type;
    /* 0x009 */ bool enabled;
    /* 0x00A */ bool shouldSkip;
    /* 0x00B */ EffectState usageState;
    /* 0x00C */ s32 mixId;
    /* 0x010 */ s32 processOrder;
    /* 0x014 */ char unk14[0xC];
    /* 0x020 */ nn::audio::server::AddressInfo workBuffers[2];
    /* 0x060 */ u32 dspSendBufferInfo;
    /* 0x064 */ u32 dspSendBufferInfoBase;
    /* 0x068 */ u32 dspReturnBufferInfo;
    /* 0x06C */ u32 dspReturnBufferInfoBase;
    /* 0x080 */ nn::audio::AuxParameter parameter;
    /* 0x140 */ char stateBuffer[0x140];
    /* 0x280 */ char unk270[0x240];
};

struct nn::audio::CaptureType {
    /* 0x00 */ nn::audio::EffectInfo::InParameterBasic param;
    /* 0x20 */ nn::audio::AuxParameter specific;
};

struct nn::audio::CaptureCommand : nn::audio::ICommand {
    /* 0x10 */ char unk10[0x4];
    /* 0x14 */ s16 input;
    /* 0x16 */ s16 output;
    /* 0x18 */ s32 sendBufferInfo;
    /* 0x1C */ s32 sendBufferInfoBase;
    /* 0x20 */ s32 countMax;
    /* 0x24 */ s32 writeOffset;
    /* 0x28 */ s32 updateCount;
    /* 0x2C */ bool enabled;
}; // size = 0x30

struct nn::audio::CompressorParameter {
    /* 0x00 */ s8 inputs[6];
    /* 0x06 */ s8 outputs[6];
    /* 0x0C */ s16 channelCountMax;
    /* 0x0E */ s16 channelCount;
    /* 0x10 */ s32 sampleRate;
    /* 0x14 */ f32 threshold;
    /* 0x18 */ f32 compressorRatio;
    /* 0x1C */ s32 attackTime;
    /* 0x20 */ s32 releaseTime;
    /* 0x24 */ f32 unk_24; // set with mix type
    /* 0x28 */ f32 unk_28; // decay?
    /* 0x2C */ f32 unk_2C; // set with releaseTime, can't be sustain?
    /* 0x30 */ f32 outGain;
    /* 0x34 */ u8 state;
    /* 0x35 */ bool makeupGainEnabled;
}; // size >= 0x38

struct nn::audio::CompressorType {
    /* 0x00 */ nn::audio::EffectInfo::InParameterBasic param;
    /* 0x20 */ nn::audio::CompressorParameter specific;
};

struct nn::audio::server::CompressorInfo {
    /* 0x000 */ nn::audio::server::EffectInfoBase::vtable* __vftable;
    /* 0x008 */ nn::audio::server::EffectType type;
    /* 0x009 */ bool enabled;
    /* 0x00A */ bool shouldSkip;
    /* 0x00B */ EffectState usageState;
    /* 0x00C */ s32 mixId;
    /* 0x010 */ s32 processOrder;
    /* 0x014 */ char unk14[0xC];
    /* 0x020 */ nn::audio::server::AddressInfo workBuffers[2];
    /* 0x060 */ u32 dspSendBufferInfo;
    /* 0x064 */ u32 dspSendBufferInfoBase;
    /* 0x068 */ u32 dspReturnBufferInfo;
    /* 0x06C */ u32 dspReturnBufferInfoBase;
    /* 0x080 */ nn::audio::CompressorParameter parameter;
    /* 0x0B8 */ char unk0A8[0x88];
    /* 0x140 */ char stateBuffer[0x140];
    /* 0x280 */ char unk270[0x240];
};

struct nn::audio::CompressorState {
    /* 0x00 */ f32 unk_00;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ f32 makeupGain;
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ char unk_24[0x1C];
}; // size = 0x40

struct nn::audio::CompressorCommand : nn::audio::ICommand {
    /* 0x10 */ char unk10[0x4];
    /* 0x14 */ s16 inputs[6];
    /* 0x20 */ s16 outputs[6];
    /* 0x2C */ nn::audio::CompressorParameter params;
    /* 0x64 */ u32 workbuffer;
    /* 0x68 */ bool enabled;
    /* 0x69 */ char pad69[0x3];
}; // size = 0x6C

struct nn::audio::CommandListHeader {
    /* 0x00 */ u32 bufferPos;
    /* 0x04 */ s32 commandCount;
    /* 0x08 */ u32 translatedSamplesBuffer;
    /* 0x0C */ s32 bufferCount;
    /* 0x10 */ s32 sampleCount;
    /* 0x14 */ s32 sampleRate;
}; // size = 0x18

struct nn::audio::dsp::CommandListProcessor {
    /* 0x00 */ void* workBufferHeader;
    /* 0x08 */ void* workBufferCommands;
    /* 0x10 */ u64 workBufferCommandsSize;
    /* 0x18 */ u32 maxProcessTime;
    /* 0x1C */ u32 commandCount;
    /* 0x20 */ u32 sampleCount;
    /* 0x24 */ u32 targetSampleRate;
    /* 0x28 */ void* mixBuffers;
    /* 0x30 */ u32 bufferCount;
    /* 0x34 */ u32 processedCommandCount;
    /* 0x38 */ u64 processingStartTime;
    /* 0x40 */ u64 currentBlockStartTime;
    /* 0x48 */ u64 endTime;
}; // size = 0x50?

struct nn::audio::server::CommandGenerator {
    /* 0x00 */ nn::audio::server::CommandBuffer* inCommandBuffer;
    /* 0x08 */ nn::audio::CommandListHeader* outCommandBuffer;
    /* 0x10 */ nn::audio::server::AudioRendererSystemContext* renderContext;
    /* 0x18 */ nn::audio::server::VoiceContext* voiceContext;
    /* 0x20 */ nn::audio::server::MixContext* mixContext;
    /* 0x28 */ nn::audio::server::EffectContext* effectContext;
    /* 0x30 */ nn::audio::server::SinkContext* sinkContext;
    /* 0x38 */ nn::audio::server::SplitterContext* splitterContext;
    /* 0x40 */ nn::audio::server::PerformanceManager* performanceManager;
}; // size = 0x48

// =================== DSP ===================

enum adsp_mbx_direction {
  ADSP_MBX_SEND = 0x0,
  ADSP_MBX_RCV = 0x1,
};
enum handler_return {
  INT_NO_RESCHEDULE = 0x0,
  INT_RESCHEDULE = 0x1,
};

typedef adsp_mbx_direction adsp_mbx_direction_t;
typedef handler_return (*adsp_mbx_handler_t)(int32_t, void *, adsp_mbx_direction_t, int16_t);

struct adsp_hw_mbx {
    /* 0x0000 */ void* __vftable;
    /* 0x0008 */ void* sharedMemory; // ?? Mapped to 0x702EC000, size 0x2000
    /* 0x0010 */ char unk10[0x20];
    /* 0x0030 */ s32 buffer[1024];
    /* 0x1030 */ s16 rd_idx;
    /* 0x1032 */ s16 wr_idx;
    /* 0x1034 */ s16 err_code;
    /* 0x1036 */ s16 busy;
    /* 0x1038 */ s16 count;
    /* 0x103C */ u32 send_mbx;
    /* 0x1040 */ u32 rcv_mbx;
    /* 0x1044 */ u16 empty_irq;
    /* 0x1046 */ u16 full_irq;
    /* 0x1048 */ s32 last_msg;
    /* 0x104C */ char align104C[0x4];
    /* 0x1050 */ nn::os::SemaphoreType s;
    /* 0x1078 */ nn::os::Mutex mutex;
}; // size = 0x1098

struct adsp_mbx {
    /* 0x00 */ s32 rcv_buffer[16];
    /* 0x40 */ s8 rcv_rd_idx;
    /* 0x41 */ s8 rcv_wr_idx;
    /* 0x42 */ s8 count;
    /* 0x44 */ s16 mbx_id;
    /* 0x46 */ s8 err_code;
    /* 0x47 */ char align[0x1];
    /* 0x48 */ nn::os::SemaphoreType s;
    /* 0x70 */ nn::os::SemaphoreType* rcv_sem;
    /* 0x78 */ adsp_mbx_handler_t err_handler;
    /* 0x80 */ adsp_mbx_handler_t msg_handler;
    /* 0x88 */ void* context;
}; // size = 0x90

struct __attribute__((aligned(4))) mailbox_attributes {
  /* 0x00 */ void* owner;
  /* 0x08 */ s16 flags;
}; // size = 0xC

struct nn::audio::dsp::Mailbox {
    /* 0x00 */ adsp_mbx mailbox;
    /* 0x90 */ nn::os::SemaphoreType semaphore;
}; // size = 0xB8

struct nn::audio::dsp::CommandBuffer {
    /* 0x00 */ u32 listHeader;
    /* 0x04 */ u32 commandBufferSize;
    /* 0x08 */ s32 timeLimit;
    /* 0x0C */ s32 remainingCommandCount;
    /* 0x10 */ bool resetBuffers;
    /* 0x18 */ s64 resourceUserId;
    /* 0x20 */ s32 renderTimeTaken;
}; // size = 0x28

struct nn::audio::dsp::CommandBufferS {
    /* 0x00 */ u32 dspAddr; // nn::audio::CommandListHeader*
    /* 0x04 */ u32 commandBufferSize;
    /* 0x08 */ s32 timeLimit;
    /* 0x0C */ s32 remainingCommandCount;
    /* 0x10 */ bool resetBuffers;
    /* 0x18 */ s64 appletResourceUserId;
    /* 0x20 */ char unk20[0x8];
}; // size = 0x28

struct nn::audio::dsp::MapUnmapBuffer {
    /* 0x00 */ u32 addr;
    /* 0x04 */ u32 size;
}; // size = 0x8

struct nn::audio::dsp::Buffer {
    /* 0x00 */ nn::audio::dsp::CommandBuffer cmdBuffers[2];
    /* 0x50 */ nn::audio::dsp::MapUnmapBuffer mapUnmapBuffer;
}; // size = 0x58

struct nn::audio::dsp {
    /* 0x000 */ nn::audio::dsp::Buffer* commandBuffer;
    /* 0x008 */ s64 signalledTick;
    /* 0x010 */ DSP_App* audioRenderer;
    /* 0x018 */ nn::os::EventType event1;
    /* 0x040 */ nn::os::EventType event2;
    /* 0x068 */ nn::os::EventType event3;
    /* 0x090 */ nn::audio::dsp::Mailbox mapMailbox;
    /* 0x148 */ nn::audio::dsp::Mailbox renderMailbox;
}; // size >= 0x200

struct nn::audio::UnkDsp { // used when sending data to the DSP, at 0x71001A2098. DSP buffer list maybe?
    /* 0x00 */ void* cpuAddr;
    /* 0x08 */ u32 dspAddr;
    /* 0x0C */ u32 alignedSize;
    /* 0x10 */ s8 state; // 1 = sentToDSP?, 2 = ?
    /* 0x14 */ s32 index; // ? incremented once per addition
    /* 0x18 */ u32 handle;
}; // size = 0x20

// DSP-side the pointers are 32-bit
struct nn::audio::dsp::DecodeFromWaveBuffersArgs {
    /* 0x00 */ nn::audio::SampleFormat sampleFormat;
    /* 0x04 */ u32 output;
    /* 0x08 */ nn::audio::VoiceState* voiceState;
    /* 0x0C */ nn::audio::WaveBuffer* waveBuffer;
    /* 0x10 */ s32 channel;
    /* 0x14 */ s32 channelCount;
    /* 0x18 */ VoiceType::SrcQuality srcQuality;
    /* 0x1C */ s32 pitch;
    /* 0x20 */ s32 sourceSampleRate;
    /* 0x24 */ s32 targetSampleRate;
    /* 0x28 */ s32 sampleCount;
    /* 0x2C */ u32 dataAddress;
    /* 0x30 */ bool IsVoicePlayedSampleCountResetAtLoopPointSupported;
    /* 0x31 */ bool IsVoicePitchAndSrcSkippedSupported;
}; // size >= 0x34

struct nn::audio::dsp::DecodeArg {
    /* 0x00 */ u32 dspBuffer;
    /* 0x04 */ u32 bufferSize;
    /* 0x08 */ s32 startOffset;
    /* 0x0C */ s32 endOffset;
    /* 0x10 */ s32 channelCount;
    /* 0x14 */ s16* coefficients;
    /* 0x18 */ nn::codec::AdpcmContext* adpcmContext;
    /* 0x1C */ s32 channel;
    /* 0x20 */ s32 offset;
    /* 0x24 */ s32 samplesToRead;
}; // size >= 0x28

enum nn::audio::dsp::MailboxMessage {
    /* 0x00 */ Invalid,
    /* 0x01 */ AudioRenderer_MapUnmap_Map,
    /* 0x02 */ AudioRenderer_MapUnmap_MapResponse,
    /* 0x03 */ AudioRenderer_MapUnmap_Unmap,
    /* 0x04 */ AudioRenderer_MapUnmap_UnmapResponse,
    /* 0x05 */ AudioRenderer_MapUnmap_InvalidateCache,
    /* 0x06 */ AudioRenderer_MapUnmap_InvalidateCacheResponse,
    /* 0x07 */ AudioRenderer_MapUnmap_Shutdown,
    /* 0x08 */ AudioRenderer_MapUnmap_ShutdownResponse,
    /* 0x20 */ AudioRenderer_RenderResponse = 0x20,
    /* 0x2A */ AudioRenderer_Render = 0x2A,
    /* 0x34 */ AudioRenderer_Shutdown = 0x34,
};

// =================== AUDIOOUT ===================

struct nn::audio::AudioBuffer {
    /* 0x00 */ s64 playedTimestamp; // set to the time it was released
    /* 0x08 */ void* pointer;
    /* 0x10 */ void* deviceAddr;
    /* 0x18 */ u64 tag;
    /* 0x20 */ s64 size;
}; // size = 0x28

struct nn::audio::AudioOutInfo {
    /* 0x00 */ char name[256];
}; // size = 0x100

struct nn::audio::AudioOutParameter {
    /* 0x00 */ s32 sampleRate;
    /* 0x04 */ s16 channelCount;
    /* 0x06 */ char unk06[0x2];
}; // size = 0x8

struct nn::audio::AudioOutParameterInternal {
    /* 0x00 */ s32 sampleRate;
    /* 0x04 */ s32 channelCount;
    /* 0x08 */ nn::audio::SampleFormat sampleFormat;
    /* 0x0C */ s32 state;
}; // size = 0x10

enum nn::audio::AudioOutState {
    Started,
    Stopped,
};

struct nn::audio::AudioOutBuffer {
    /* 0x00 */ nn::audio::AudioOutBuffer* next;
    /* 0x08 */ void* pointer;
    /* 0x10 */ s64 capacity;
    /* 0x18 */ s64 size;
    /* 0x20 */ s64 offset;
}; // size = 0x28

struct nn::audio::AudioOutBuffers {
    /* 0x000 */ nn::audio::AudioBuffer audioBuffers[32];
    /* 0x500 */ s32 releasedIndex;
    /* 0x504 */ s32 releasedCount;
    /* 0x508 */ s32 registeredIndex;
    /* 0x50C */ s32 registeredCount;
    /* 0x510 */ s32 appendedIndex;
    /* 0x514 */ s32 appendedCount;
    /* 0x518 */ s32 bufferRegisterLimit;
}; // size == ???

struct nn::audio::AudioOutSystem {
    /* 0x000 */ struct nn::audio::AudioOutSystem::vtable* __vftable;
    /* 0x008 */ u32 handle;
    /* 0x010 */ s64 appletResourceUserId;
    /* 0x018 */ nn::os::SystemEventType* bufferEvent;
    /* 0x020 */ struct nn::audio::AudioDeviceSession* session;
    /* 0x028 */ nn::audio::AudioOutBuffers buffers;
    /* 0x548 */ char unk548[0x28];
    /* 0x570 */ s32 sessionIndex;
    /* 0x574 */ nn::audio::SampleFormat sampleFormat;
    /* 0x578 */ s32 sampleRate;
    /* 0x57C */ s16 channelCount;
    /* 0x580 */ nn::audio::AudioOutState state;
    /* 0x584 */ s32 sessionId;
    /* 0x588 */ s32 unk_588;
    /* 0x58C */ char name[0x100];
    /* 0x68C */ s16 nameSize;
    /* 0x690 */ f32 volume;
}; // size = 0x698

struct nn::audio::AudioOutSystem::vtable {
    /* 0x00 */ char* (*GetDefaultOutputDeviceName)(nn::audio::AudioOutSystem*);
    /* 0x08 */ bool (*AreSettingsValid)(nn::audio::AudioOutSystem*, char*, nn::audio::AudioOutParameter*);
    /* 0x10 */ u64 (*Initialise)(nn::audio::AudioOutSystem*);
    /* 0x18 */ u64 (*Start)(nn::audio::AudioOutSystem*);
    /* 0x20 */ u64 (*Stop)(nn::audio::AudioOutSystem*);
};

struct nn::audio::AudioOut {
    /* 0x000 */ struct nn::audio::VirtualDeviceSession* virtualDeviceSession;
    /* 0x008 */ nn::audio::AudioOutSystem system;
    /* 0x6A0 */ struct nn::audio::AudioOutManagerImpl* manager;
    /* 0x6A8 */ nn::os::SdkRecursiveMutexType* parentMutex;
}; // size = 0x6B0

struct nn::audio::AudioOut_Wrap {
    /* 0x000 */ nn::audio::server::IAudioOut::vtbl*__vftable;
    /* 0x008 */ nn::audio::AudioOut impl;
    /* 0x6B8 */ s32 unk_6B8;
    /* 0x6C0 */ nn::lmem::detail::HeapHead* heapHead;
}; // size = 0x6C8

// 0x4000 heap
struct nn::audio::AudioOutManagerImpl {
    /* 0x000 */ nn::audio::server::IAudioOutManager::vtbl* __vftable;
    /* 0x008 */ nn::lmem::detail::HeapHead_Wrap heapHead;
    /* 0x018 */ char unk018[0x90];
    /* 0x0A8 */ nn::lmem::detail::HeapHead* heap;
    /* 0x0B0 */ bool linkedToManager;
    /* 0x0B4 */ s32 sessionIds[12];
    /* 0x0E4 */ s32 nextSessionId;
    /* 0x0E8 */ char unk0E8[0x4];
    /* 0x0EC */ s32 numFreeSessions;
    /* 0x0F0 */ nn::os::SemaphoreType* semaphore;
    /* 0x0F8 */ nn::audio::AudioOut* sessions[12];
    /* 0x158 */ s64 appletResourceUserIds[12];
    /* 0x1B8 */ nn::os::EventType event;
    /* 0x1E0 */ nn::os::SdkRecursiveMutexType recursiveMutex;
    /* 0x1E8 */ bool sessionsStarted;
}; // size >= 0x1EC

struct nn::audio::AudioOutManager_Wrap {
    /* 0x000 */ nn::audio::server::IAudioOutManager::vtbl* __vftable;
    /* 0x008 */ nn::audio::AudioOutManagerImpl impl;
};

// =================== AUDIOIN ===================

struct nn::audio::AudioInBuffer {
    /* 0x00 */ nn::audio::AudioInBuffer* next;
    /* 0x08 */ void* pointer;
    /* 0x10 */ s64 capacity;
    /* 0x18 */ s64 size;
    /* 0x20 */ s64 offset;
}; // size = 0x28

struct nn::audio::AudioInParameter {
    /* 0x00 */ nn::audio::SampleFormat sampleFormat;
    /* 0x04 */ u16 channelCount;
    /* 0x06 */ u16 pad;
}; // size = 0x8

struct nn::audio::AudioInParameterInternal {
    /* 0x00 */ s32 sampleRate;
    /* 0x04 */ s32 channelCount;
    /* 0x08 */ nn::audio::SampleFormat sampleFormat;
    /* 0x0C */ s32 state;
}; // size = 0x10

enum nn::audio::AudioInState {
    Started,
    Stopped,
};

struct nn::audio::AudioInBuffers {
    /* 0x000 */ nn::audio::AudioBuffer audioBuffers[32];
    /* 0x500 */ s32 releasedIndex; // free buffers
    /* 0x504 */ s32 releasedCount; // free buffers
    /* 0x508 */ s32 registeredIndex; // buffers in use by the adsp/hardware
    /* 0x50C */ s32 registeredCount; // buffers in use by the adsp/hardware
    /* 0x510 */ s32 appendedIndex; // buffers pending being sent to the adsp/hardware
    /* 0x514 */ s32 appendedCount; // buffers pending being sent to the adsp/hardware
    /* 0x518 */ s32 bufferRegisterLimit; // maybe part of buffers
}; // size == ???

struct nn::audio::AudioInSystem {
    /* 0x000 */ struct nn::audio::AudioInSystem::vtable* __vftable;
    /* 0x008 */ u32 handle;
    /* 0x010 */ s64 appletResourceUserId;
    /* 0x018 */ nn::os::SystemEventType* bufferEvent;
    /* 0x020 */ struct nn::audio::AudioDeviceSession* session; // up to 2 headset sessions, and 2 USB sessions?
    /* 0x028 */ nn::audio::AudioInBuffers buffers;
    /* 0x548 */ char unk548[0x28];
    /* 0x570 */ s32 sessionIndex;
    /* 0x574 */ nn::audio::SampleFormat sampleFormat;
    /* 0x578 */ s32 sampleRate;
    /* 0x57C */ s16 channelCount;
    /* 0x580 */ nn::audio::AudioInState state;
    /* 0x584 */ s32 sessionId;
    /* 0x588 */ s32 unk_588;
    /* 0x58C */ char name[0x100];
    /* 0x68C */ s16 nameSize;
    /* 0x690 */ s64 activeSessionCount;
}; // size = 0x698

struct nn::audio::AudioInSystem::vtable {
    /* 0x00 */ char* (*GetDefaultInputDeviceName)(nn::audio::AudioInSystem*);
    /* 0x08 */ bool (*AreSettingsValid)(nn::audio::AudioInSystem*, char*, nn::audio::AudioInParameter*);
    /* 0x10 */ u64 (*Initialise)(nn::audio::AudioInSystem*);
    /* 0x18 */ u64 (*Start)(nn::audio::AudioInSystem*);
    /* 0x20 */ u64 (*Stop)(nn::audio::AudioInSystem*);
};

struct nn::audio::AudioInManagerImpl {
    /* 0x000 */ nn::audio::server::IAudioInManager::vtbl* __vftable;
    /* 0x008 */ nn::lmem::detail::HeapHead_Wrap heapHead;
    /* 0x018 */ bool linkedToManager;
    /* 0x01C */ nn::os::SdkRecursiveMutexType recursiveMutex;
    /* 0x024 */ s32 sessionIds[4];
    /* 0x034 */ s32 nextSessionId;
    /* 0x038 */ char unk038[0x4];
    /* 0x03C */ s32 numFreeSessions;
    /* 0x040 */ char unk040[0x90];
    /* 0x0D0 */ nn::lmem::detail::HeapHead* unitHeap;
    /* 0x0D8 */ nn::os::SemaphoreType semaphore;
    /* 0x100 */ struct nn::audio::AudioIn* sessions[4];
    /* 0x120 */ nn::os::EventType sessionEvents[4];
    /* 0x1C0 */ s64 appletResourceUserIds[4];
    /* 0x1E0 */ nn::os::EventType event;
    /* 0x204 */ bool audioInInitialised; // ?
    /* 0x205 */ char unk205[0x3];
    /* 0x208 */ bool sessionsStarted;
}; // size >= 0x20C

struct nn::audio::AudioInManager_Wrap {
    /* 0x000 */ nn::audio::server::IAudioInManager::vtbl* __vftable;
    /* 0x008 */ nn::audio::AudioInManagerImpl impl;
};

struct nn::audio::AudioIn {
    /* 0x000 */ struct nn::audio::VirtualDeviceSession* virtualDeviceSession;
    /* 0x008 */ nn::audio::AudioInSystem system;
    /* 0x6A0 */ nn::os::SdkRecursiveMutexType* parentMutex;
    /* 0x6A8 */ nn::audio::AudioInManagerImpl* manager;
    /* 0x6B0 */ bool isUAC;
    /* 0x6B1 */ char unk6B1[0x7];
}; // size = 0x6B8

struct nn::audio::AudioIn_Wrap {
    /* 0x000 */ nn::audio::IAudioIn::vtbl*__vftable;
    /* 0x008 */ nn::audio::AudioIn impl;
    /* 0x6C0 */ s32 unk_6C0; // isManaged?
    /* 0x6C8 */ nn::lmem::detail::HeapHead_Wrap* heapHead;
}; // size = 0x6D0

// =================== FINAL OUTPUT RECORDER ===================

struct nn::audio::FinalOutputRecorderBuffer {
    /* 0x00 */ s64 released;
    /* 0x08 */ nn::audio::FinalOutputRecorderBuffer* next;
    /* 0x10 */ void* samples;
    /* 0x18 */ s64 capacity;
    /* 0x20 */ s64 size;
    /* 0x28 */ s64 offset;
}; // size = 0x30

struct nn::audio::detail::FinalOutputRecorderWorkBufferParameterInternal {
    /* 0x00 */ void* pointer;
    /* 0x08 */ s64 size;
    /* 0x10 */ s64 sampleCount; // ??
}; // size = 0x18

struct nn::audio::FinalOutputRecorderSystemParameter {
    /* 0x00 */ nn::audio::SampleFormat sampleFormat;
    /* 0x04 */ s32 sampleRate;
    /* 0x08 */ s32 channelCount;
    /* 0x0C */ s32 state;
}; // size = 0x10

enum nn::audio::FinalOutputRecorderState {
    Started,
    Stopped,
};

struct nn::audio::FinalOutputRecorderBuffers {
    /* 0x000 */ nn::audio::AudioBuffer audioBuffers[16];
    /* 0x280 */ s32 releasedIndex;
    /* 0x284 */ s32 releasedCount;
    /* 0x288 */ s32 registeredIndex;
    /* 0x28C */ s32 registeredCount;
    /* 0x290 */ s32 appendedIndex;
    /* 0x294 */ s32 appendedCount;
    /* 0x298 */ s32 bufferRegisterLimit;
}; // size == ???

struct nn::audio::FinalOutputRecorderSystem {
    /* 0x000 */ struct nn::audio::FinalOutputRecorderSystem::vtable* __vftable;
    /* 0x008 */ u32 handle;
    /* 0x010 */ s64 appletResourceUserId;
    /* 0x018 */ nn::os::SystemEventType* bufferEvent;
    /* 0x020 */ struct nn::audio::AudioDeviceSession* session;
    /* 0x028 */ nn::audio::FinalOutputRecorderBuffers buffers;
    /* 0x2C8 */ nn::audio::AudioBuffer workBuffer;
    /* 0x2F0 */ s32 systemType; // see ManagerTypes
    /* 0x2F4 */ nn::audio::SampleFormat sampleFormat;
    /* 0x2F8 */ s32 sampleRate;
    /* 0x2FC */ s16 channelCount;
    /* 0x300 */ nn::audio::FinalOutputRecorderState state;
    /* 0x304 */ s32 sessionId;
    /* 0x308 */ char unk308[0x4];
    /* 0x30C */ char deviceName[0xFF];
    /* 0x40C */ s16 deviceNameSize;
}; // size = 0x410

struct nn::audio::FinalOutputRecorderSystem::vtable {
    /* 0x00 */ char* (*GetDefaultInputDeviceName)(nn::audio::FinalOutputRecorderSystem*);
    /* 0x08 */ bool (*AreSettingsValid)(nn::audio::FinalOutputRecorderSystem*, char*, nn::audio::FinalOutputRecorderSystemParameter*);
    /* 0x10 */ u64 (*Initialise)(nn::audio::FinalOutputRecorderSystem*);
    /* 0x18 */ u64 (*Start)(nn::audio::FinalOutputRecorderSystem*);
    /* 0x20 */ u64 (*Stop)(nn::audio::FinalOutputRecorderSystem*);
};

struct nn::audio::FinalOutputRecorder {
    /* 0x000 */ void* unk_000;
    /* 0x008 */ nn::audio::FinalOutputRecorderSystem system;
    /* 0x418 */ struct nn::audio::FinalOutputRecorderManagerImpl* manager;
    /* 0x420 */ nn::os::SdkRecursiveMutexType* parentMutex;
}; // size = 0x428

struct nn::audio::FinalOutputRecorder_Wrap {
    /* 0x000 */ nn::audio::FinalOutputRecorder::vtable* __vftable;
    /* 0x008 */ nn::audio::FinalOutputRecorder impl;
    /* 0x430 */ s32 unk_430;
    /* 0x438 */ nn::lmem::detail::HeapHead* heapHead;
}; // size = 0x440

struct nn::audio::FinalOutputRecorderManagerImpl {
    /* 0x000 */ struct nn::audio::IFinalOutputRecorderManager::vtable* __vftable;
    /* 0x008 */ nn::lmem::detail::HeapHead_Wrap heapHead;
    /* 0x018 */ char unk018[0x90];
    /* 0x0A8 */ nn::lmem::detail::HeapHead* unitHeap;
    /* 0x0B0 */ bool linkedToManager;
    /* 0x0B4 */ nn::os::SdkRecursiveMutexType recursiveMutex;
    /* 0x0BC */ s32 sessionIds[3];
    /* 0x0C8 */ s32 nextSessionId;
    /* 0x0CC */ s32 nextSessionId2;
    /* 0x0D0 */ s32 numFreeSessions;
    /* 0x0D4 */ char unk0D4[0x4];
    /* 0x0D8 */ nn::os::SemaphoreType semaphore;
    /* 0x100 */ nn::audio::FinalOutputRecorder* sessions[3];
    /* 0x118 */ nn::os::EventType sessionEvents[3];
    /* 0x190 */ s64 appletResourceUserIds[3];
    /* 0x1A8 */ nn::os::EventType event;
    /* 0x1D0 */ bool sessionsStarted;
}; // size >= 0x1D4

struct nn::audio::FinalOutputRecorderManager_Wrap {
    /* 0x000 */ nn::audio::IFinalOutputRecorderManager::vtable* __vftable;
    /* 0x008 */ nn::audio::FinalOutputRecorderManagerImpl impl;
}; // size = 0x1E0

// =================== DEVICE ===================

enum DeviceTypes {
    /* 0 */ Invalid,
    /* 1 */ Speaker,
    /* 2 */ Headphone,
    /* 3 */ Tv,
    /* 4 */ UsbOutputDevice,
    /* 5 */ BtOutputDevice,
};

enum OutputDeviceTypes {
    /* 0 */ AudioStereoJackOutput1,
    /* 1 */ AudioBuiltInSpeakerOutput,
    /* 2 */ AudioTvOutput,
    /* 3 */ AudioUsbDeviceOutput,
    /* 4 */ AudioStereoJackOutput2,
};

// max sessions:
//   render: 2
//   out:   12
//   

// session type -> device index mapping for AudioDevices:
//   Render: 0
//   Out: 1
//   In: 2
//   FinalOutputRecorder: 3

// gGetDeviceRegistryTypeFromSystemIndex get session type from index in AudioInSystem::Start
// 0 = AudioIn (2)
// 1 = AudioOut (1)
// 2 = FinalOutputRecorder (3)

enum nn::audio::AudioDevices::Type {
    /* 0 */ AudioOut,
    /* 1 */ AudioFinalOutputRecorder,
    /* 2 */ AudioIn,
    /* 3 */ Unk3,
};

struct nn::audio::AudioDevice {
    /* 0x00 */ s32 refCount;
    /* 0x08 */ s64 appletResourceUserId;
    /* 0x10 */ f32 masterVolumes[4]; // AudioOut sets 0 and 1
    /* 0x20 */ f32 recordVolumes[4];
    /* 0x30 */ f32 deviceVolumes[4][5]; // [sessionType][deviceType]
    /* 0x80 */ s32 audioOutDeviceIndex;
    /* 0x84 */ s32 finalOutDeviceIndex;
    /* 0x88 */ s32 audioInDeviceIndex;
    /* 0x8C */ bool suspended;
    /* 0x8D */ char unk8D[0x3];
    /* 0x90 */ bool suspendedDebug;
    /* 0x91 */ char unk91[0x7];
}; // size = 0x98

struct nn::audio::VirtualDeviceSession {
    /* 0x00 */ nn::audio::VirtualDeviceSession* prev;
    /* 0x08 */ nn::audio::VirtualDeviceSession* next;
    /* 0x10 */ nn::os::SystemEvent systemEvent;
    ///* 0x28 */ nn::audio::VirtualDeviceSession* head2;
    ///* 0x30 */ nn::audio::VirtualDeviceSession* next2;
    ///* 0x38 */ char unk38[0x8];
    ///* 0x40 */ bool inUse;
    ///* 0x41 */ char unk41[0x7];
}; // size = 0x48

struct nn::audio::DeviceSession {
    /* 0x00 */ u32 state; // 1 = running, 2 = suspended
    /* 0x08 */ s64 suspendResumeTime;
    /* 0x10 */ nn::os::EventType* event;
    /* 0x18 */ s64 ticksNow;
    /* 0x20 */ s64 inTicks;
    /* 0x28 */ f32 processMasterVolumes[2];
    /* 0x30 */ bool needsUpdate; // signals the event when set to 1
    /* 0x34 */ nn::os::SdkMutexType mutex;
    /* 0x38 */ s32 unk_38;
    /* 0x3C */ u32 state2;
    /* 0x40 */ char unk40[0x8];
    /* 0x48 */ s64 appletResourceUserId;
    /* 0x50 */ s32 unk_50;
    /* 0x54 */ f32 deviceVolumes[3]; // 1 = masterVolume
    /* 0x60 */ f32 unkVolume;
    /* 0x64 */ f32 outputDeviceVolumes[5]; // indexed with OutputDeviceTypes
    /* 0x78 */ char unk78[0x18];
    /* 0x90 */ struct nn::audio::DeviceSession::sub_vtable** unk_90;
}; // size = 0x98

// 7100164E08
struct nn::audio::DeviceSession::sub_vtable {
    /* 0x00 */ void (*D2)();
    /* 0x08 */ void (*D0)();
    /* 0x10 */ void (*Unk00)();
    /* 0x18 */ void (*Unk08)();
    /* 0x20 */ void (*Unk10)();
    /* 0x28 */ void (*Unk18)();
};

struct nn::audio::AudioDevices {
    /* 0x0000 */ char unk0000[0x3000];
    /* 0x3000 */ nn::os::SdkMutexType sdkMutex;
    /* 0x3004 */ nn::os::SdkMutexType sdkMutex2;
    /* 0x3008 */ nn::os::EventType event;
    /* 0x3030 */ nn::os::Thread appletVolumeManagerThread;
    /* 0x31F0 */ nn::audio::DeviceSession audioOutSessions[12]; // audioout?
    /* 0x3910 */ nn::audio::DeviceSession renderSessions[2]; // render?
    /* 0x3A40 */ nn::audio::DeviceSession audioInSessions[4]; // audioin?
    /* 0x3CA0 */ nn::audio::DeviceSession finalOutputRecorderSessions[3]; // finaloutputrecorder?
    /* 0x3E68 */ nn::audio::AudioDevice devices[16];
    /* 0x47E8 */ s32 deviceCount;
    /* 0x47EC */ bool appletVolumeManagerIsSetup;
    /* 0x47ED */ bool unk_47ED;
    /* 0x47F0 */ s32 activeDeviceIndex;
    /* 0x47F4 */ s32 activeDeviceChannelCount;
    /* 0x47F8 */ f32 activeDeviceVolume;
    /* 0x47FC */ char unk47FC[0x2C];
    /* 0x4828 */ nn::os::SdkMutexType sdkMutex3;
    /* 0x482C */ char unk482C[0x4];
    /* 0x4830 */ nn::audio::VirtualDeviceSession outSessions[16];
    /* 0x4CB0 */ nn::audio::VirtualDeviceSession finalOutRecorderSessions[16];
    /* 0x5130 */ nn::audio::VirtualDeviceSession inSessions[16];
    /* 0x55B0 */ nn::audio::VirtualDeviceSession* audioOutHead;
    /* 0x55B8 */ nn::audio::VirtualDeviceSession* audioOutNext; // Tail?
    /* 0x55C0 */ nn::audio::VirtualDeviceSession* audioFinalOutRecorderHead;
    /* 0x55C8 */ nn::audio::VirtualDeviceSession* audioFinalOutRecorderNext;
    /* 0x55D0 */ nn::audio::VirtualDeviceSession* audioInHead;
    /* 0x55D8 */ nn::audio::VirtualDeviceSession* audioInNext;
    /* 0x55E0 */ char unk55B0[0xA0];
}; // size = 0x5680

struct nn::audio::AudioDeviceSession {
    /* 0x00 */ struct nn::audio::AudioDeviceSession::vtbl* __vftable;
    /* 0x08 */ nn::audio::AudioBuffer audioBuffers[2];
    /* 0x58 */ s64 appletResourceUserId;
    /* 0x60 */ u32 handle;
    /* 0x64 */ char unk64[0x4];
    /* 0x68 */ struct nn::audio::AudioRenderSession* session;
    /* 0x70 */ s64 playedSampleCount;
    /* 0x78 */ s32 unk_78;
    /* 0x7C */ s32 unk_7C;
    /* 0x80 */ s32 unk_80;
    /* 0x84 */ nn::audio::SessionType sessionType;
    /* 0x88 */ s32 deviceRegistryType; // 0: render, 1: audioout, 2: audioin, 3: finaloutput
    /* 0x8C */ s32 channelCount;
    /* 0x90 */ s32 sessionId;
    /* 0x94 */ s32 numFrames; // sampleCount / (channelCount * sampleFormatByteSize)
}; // size = 0x98

struct nn::audio::AudioDeviceSession::vtbl {
    /* 0x00 */ void (*D2)(nn::audio::AudioDeviceSession*);
    /* 0x08 */ void (*D0)(nn::audio::AudioDeviceSession*);
    /* 0x10 */ void (*Finalise)(nn::audio::AudioDeviceSession*);
    /* 0x18 */ void (*Initialise)(nn::audio::AudioDeviceSession*, s32, s32, char*, nn::audio::SampleFormat*, s32, s32, s64);
    /* 0x20 */ void (*SessionCommand0x9)(nn::audio::AudioDeviceSession*);
    /* 0x28 */ void (*SessionCommand0xA)(nn::audio::AudioDeviceSession*); // Must be stop? Called in AudioOutSystem::Stop
    /* 0x30 */ void (*Stop)(nn::audio::AudioDeviceSession*);
    /* 0x38 */ void (*Start)(nn::audio::AudioDeviceSession*);
    /* 0x40 */ void (*Unk40)(nn::audio::AudioDeviceSession*);
    /* 0x48 */ s64 (*GetPlayedSamplesCount)(nn::audio::AudioDeviceSession*);
    /* 0x50 */ bool (*MapBuffer)(nn::audio::AudioDeviceSession*, nn::audio::AudioBuffer*, u32 handle);
    /* 0x58 */ void (*ClearBufferDeviceAddr)(nn::audio::AudioDeviceSession*);
    /* 0x60 */ void (*UnmapBuffer)(nn::audio::AudioDeviceSession*, nn::audio::AudioBuffer*);
    /* 0x68 */ bool (*TryUnmapBuffer)(nn::audio::AudioDeviceSession*, nn::audio::AudioBuffer*);
    /* 0x70 */ void (*AppendBuffer)(nn::audio::AudioDeviceSession*, nn::audio::AudioBuffer*);
    /* 0x78 */ void (*Maybe_GetCurrentPlayingBuffer)(nn::audio::AudioDeviceSession*);
    /* 0x80 */ nn::Result (*SetVolume)(nn::audio::AudioDeviceSession*, f32 volume);
    /* 0x88 */ f32 (*GetVolume)(nn::audio::AudioDeviceSession*);
    /* 0x90 */ nn::Result (*AttachWorkbuffer)(nn::audio::AudioDeviceSession*, nn::audio::AudioBuffer*, s32 size, u32 handle);
};

struct nn::audio::UacAudioDeviceSession {
    /* 0x000 */ struct nn::audio::UacAudioDeviceSession::vtbl* __vftable;
    /* 0x008 */ char unk008[0x948];
}; // size = 0x950

struct nn::audio::UacAudioDeviceSession::vtbl {
    /* 0x00 */ void (*D0)(nn::audio::AudioDeviceSession*);
    /* 0x08 */ void (*D2)(nn::audio::AudioDeviceSession*);
    /* 0x10 */ void (*Finalise)(nn::audio::AudioDeviceSession*);
    /* 0x18 */ void (*Initialise)(nn::audio::AudioDeviceSession*, s32, s32, char*, nn::audio::SampleFormat*, s32, s32, s64);
    /* 0x20 */ void (*Unk20)(nn::audio::AudioDeviceSession*);
    /* 0x28 */ void (*Unk28)(nn::audio::AudioDeviceSession*);
    /* 0x30 */ void (*Stop)(nn::audio::AudioDeviceSession*);
    /* 0x38 */ void (*Start)(nn::audio::AudioDeviceSession*);
    /* 0x40 */ void (*Unk40)(nn::audio::AudioDeviceSession*);
    /* 0x48 */ s64 (*GetPlayedSamplesCount)(nn::audio::AudioDeviceSession*);
    /* 0x50 */ bool (*MapBuffer)(nn::audio::AudioDeviceSession*, nn::audio::AudioBuffer*, u32 handle);
    /* 0x58 */ void (*ClearBufferDeviceAddr)(nn::audio::AudioDeviceSession*);
    /* 0x60 */ void (*UnmapBuffer)(nn::audio::AudioDeviceSession*, nn::audio::AudioBuffer*);
    /* 0x68 */ bool (*TryUnmapBuffer)(nn::audio::AudioDeviceSession*, nn::audio::AudioBuffer*);
    /* 0x70 */ void (*AppendBuffer)(nn::audio::AudioDeviceSession*, nn::audio::AudioBuffer*);
    /* 0x78 */ void (*Maybe_GetCurrentPlayingBuffer)(nn::audio::AudioDeviceSession*);
    /* 0x80 */ nn::Result (*SetVolume)(nn::audio::AudioDeviceSession*, f32 volume);
    /* 0x88 */ f32 (*GetVolume)(nn::audio::AudioDeviceSession*);
    /* 0x90 */ void (*AttachWorkbuffer)(nn::audio::AudioDeviceSession*);
};

// =================== SESSIONS ===================

// buffer info, similar to AudioBuffer?
struct nn::audio::SessionThing {
    /* 0x00 */ void* __vftable;
    /* 0x08 */ void* buffer; // sized 0x6000
    /* 0x10 */ s32 dspAddr;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ s32 size;
    /* 0x1C */ char unk1C[0x4];
    /* 0x20 */ s8 unk_20;
    /* 0x21 */ char unk21[0x7];
}; // size = 0x28

struct nn::audio::AudioRenderSession {
    /* 0x00 */ struct nn::audio::AudioRenderSession::vtbl* __vftable;
    /* 0x08 */ nn::audio::SessionType sessionType;
    /* 0x0C */ s32 sessionId;
    /* 0x10 */ char unk10[0x8];
    /* 0x18 */ nn::audio::SessionThing unk_18[2]; // two playing buffers?
    /* 0x68 */ MixRender* mixRender; // points to its place in gMixData
    /* 0x70 */ char unk70[0x8];
}; // size = 0x78

struct nn::audio::AudioRenderSession::vtbl {
    /* 0x00 */ void* (*Maybe_GetCurrentlyPlayingBufferAddr)(nn::audio::AudioRenderSession*);
    /* 0x08 */ void (*Maybe_GetCurrentlyPlayingBufferDSPAddr)(nn::audio::AudioRenderSession*);
    /* 0x10 */ void (*Maybe_GetCurrentlyPlayingBufferSize)(nn::audio::AudioRenderSession*);
    /* 0x18 */ void (*Unk_18)(nn::audio::AudioRenderSession*);
    /* 0x20 */ void (*Unk_20)(nn::audio::AudioRenderSession*);
    /* 0x28 */ void (*GetPlayedSamplesCount)(nn::audio::AudioRenderSession*);
    /* 0x30 */ void (*SetPlayedSamplesCount)(nn::audio::AudioRenderSession*, s64 sampleCount);
    /* 0x38 */ void (*Unk_38)(nn::audio::AudioRenderSession*);
    /* 0x40 */ void (*Unk_40)(nn::audio::AudioRenderSession*);
    /* 0x48 */ void (*Unk_48)(nn::audio::AudioRenderSession*);
    /* 0x50 */ void (*AppendBuffer)(nn::audio::AudioRenderSession*);
    /* 0x58 */ void (*Unk_58)(nn::audio::AudioRenderSession*);
    /* 0x60 */ void (*SendCommand0x9)(nn::audio::AudioRenderSession*);
    /* 0x68 */ void (*SendCommand0xA)(nn::audio::AudioRenderSession*);
    /* 0x70 */ void (*FlushBuffers)(nn::audio::AudioRenderSession*);
    /* 0x78 */ void (*Suspend)(nn::audio::AudioRenderSession*);
    /* 0x80 */ void (*Resume)(nn::audio::AudioRenderSession*);
    /* 0x88 */ void (*SendCommand0xC)(nn::audio::AudioRenderSession*);
    /* 0x90 */ void (*SendCommand0xD)(nn::audio::AudioRenderSession*);
    /* 0x98 */ void (*SendCommand0xE)(nn::audio::AudioRenderSession*);
    /* 0xA0 */ void (*AttachWorkBuffer)(nn::audio::AudioRenderSession*, int audioBuffer0, int audioBuffer0Size, int audioBuffer1, int audioBuffer1Size, int sampleCount);
    /* 0xA8 */ void (*Open)(nn::audio::AudioRenderSession*);
    /* 0xB0 */ void (*Close)(nn::audio::AudioRenderSession*);
    /* 0xB8 */ void (*Unk_B8)(nn::audio::AudioRenderSession*);
};

struct nn::audio::AudioOutSession {
    /* 0x000 */ nn::audio::AudioRenderSession::vtbl* __vftable;
    /* 0x008 */ nn::audio::SessionType sessionType;
    /* 0x00C */ s32 sessionId;
    /* 0x010 */ char unk10[0x8];
    /* 0x018 */ nn::audio::SessionThing unk_18[2]; // two playing buffers?
    /* 0x068 */ MixOut* mixOut; // points to session in gMixData. MixBuffer?
    /* 0x070 */ nn::audio::SessionThing buffers[4];
    /* 0x110 */ char unk110[0x4];
    /* 0x114 */ u32 numFreeBuffers;
}; // size = 0x118

struct nn::audio::SessionRegistry {
    /* 0x0000 */ nn::os::MutexType mutex;
    /* 0x0020 */ s32 unk_20;
    /* 0x0028 */ DSP_App_B8* gMix;
    /* 0x0030 */ adsp_mbx mailbox;
    /* 0x00C0 */ void (*AbortFunc)(); // just aborts?
    /* 0x00C8 */ nn::os::SemaphoreType* sem_Default; // AudioOut?
    /* 0x00D0 */ nn::os::SemaphoreType* sem_Session7;
    /* 0x00D8 */ nn::os::SemaphoreType* sem_Session8;
    /* 0x00E0 */ nn::os::SemaphoreType* sem_NearVoice; // AudioIn
    /* 0x00E8 */ nn::os::SemaphoreType* sem_GameRecord; // FinalOutputRecorder
    /* 0x00F0 */ nn::audio::AudioRenderSession renderSessions[6];
    /* 0x03C0 */ nn::audio::AudioOutSession audioOutSessions[12];
    /* 0x10E0 */ char unk10E0[0x18];
    /* 0x10F8 */ nn::audio::SessionThing unk_10F8;
    /* 0x1120 */ nn::os::MutexType mutex2;
    /* 0x1140 */ char unk1140[0x518];
    /* 0x1658 */ char nearVoiceSessions[2][0x118]; // AudioIn
    /* 0x1888 */ char gameRecordSessions[4][0x118]; // FinalOutput
    /* 0x1CE8 */ char type7Session[2][0x70]; // session 7
    /* 0x1DC8 */ char type8Sessions[0x70]; // session 8
    /* 0x1E38 */ s32 unk_1E38; // initialised to 7
}; // size >= 0x1E3C

// =================== CONTROLLER ===================

struct nn::audio::AudioController {
    /* 0x00 */ char unk00[0x4];
};

struct nn::audio::AudioController_Wrap {
    /* 0x00 */ struct nn::audio::AudioController::vtable* __vftable;
    /* 0x08 */ nn::audio::AudioController impl;
};

// =================== CAPTURE ===================

struct nn::audio::capture::SystemAudioCaptureServer {
    /* 0x00 */ char unk00[0x4];
};

// =================== OPUS ===================

struct OpusParameters {
    /* 0x00 */ s32 sampleRate;
    /* 0x04 */ s32 channelCount;
}; // size = 0x8

struct OpusParametersEx {
    /* 0x00 */ s32 sampleRate;
    /* 0x04 */ s32 channelCount;
    /* 0x08 */ s32 useLargeFrameSize;
    /* 0x0C */ char pad[0x4];
}; // size = 0x10

struct OpusMultiStreamParameters {
    /* 0x00 */ s32 sampleRate;
    /* 0x04 */ s32 channelCount;
    /* 0x08 */ s32 totalStreamCount;
    /* 0x0C */ s32 stereoStreamCount;
    /* 0x10 */ u8 mappings[0x100];
}; // size = 0x110

struct OpusMultiStreamParametersEx {
    /* 0x00 */ s32 sampleRate;
    /* 0x04 */ s32 channelCount;
    /* 0x08 */ s32 totalStreamCount;
    /* 0x0C */ s32 stereoStreamCount;
    /* 0x10 */ s32 useLargeFrameSize;
    /* 0x14 */ char pad[0x4];
    /* 0x18 */ u8 mappings[0x100];
}; // size = 0x118

struct OpusPacketHeader {
    /* 0x00 */ u32 size;
    /* 0x04 */ u32 final_range;
}; // size = 0x8

struct nn::codec::OpusDecoder {
    /* 0x00 */ struct OpusDecoder* decoder1;
    /* 0x08 */ struct OpusDecoder* decoder2;
    /* 0x10 */ u64 transferMemorySize;
    /* 0x18 */ s32 sampleRate;
    /* 0x1C */ s32 channelCount;
    /* 0x20 */ bool needsReset;
    /* 0x21 */ char unk21[0x8];
}; // size >= 0x29

struct nn::codec::OpusDecoder_Wrap {
    /* 0x00 */ nn::audio::detail::IHardwareOpusDecoder::vtable* __vftable;
    /* 0x08 */ nn::codec::OpusDecoder impl;
}; // size >= 0x29

struct HardwareOpusSharedMemoryInfo {
    /* 0x00 */ u64 hostAddr;
    /* 0x08 */ u64 deviceAddr;
    /* 0x10 */ u64 size;
}; // size = 0x18

struct HardwareOpusSharedMemory {
    /* 0x0000 */ u8 hostChannelMapping[0x100];
    /* 0x0100 */ char unk0100[0xE80];
    /* 0x0F80 */ u32 dspSendData[16]; // channel mapping at [6]
    /* 0x0FC0 */ u32 dspReturnData[16];
}; // size = 0x1000

struct HardwareOpusMailbox {
    /* 0x00 */ u16 id;
    /* 0x08 */ nn::audio::dsp::Mailbox mailbox;
    /* 0xC0 */ bool isOpen;
    /* 0xC4 */ u32 opened_id;
}; // size = 0xC8

struct nn::audio::detail::HardwareOpusDecoderManagerImpl {
    /* 0x0000 */ nn::audio::detail::IHardwareOpusDecoderManager::vtable* __vftable;
    /* 0x0008 */ void* heap1;
    /* 0x0010 */ nn::os::Mutex mutex;
    /* 0x0030 */ nn::lmem::detail::HeapHead heapHead;
    /* 0x00C0 */ char unkC0[0x1F70];
    /* 0x2030 */ void* heap2; // same as heap1
}; // size = 0x2038

struct nn::audio::detail::HardwareOpusDecoderManager_Wrap {
    /* 0x0000 */ nn::audio::detail::IHardwareOpusDecoderManager::vtable* __vftable;
    /* 0x0008 */ char unk08[0x8];
    /* 0x0010 */ nn::audio::detail::HardwareOpusDecoderManagerImpl impl;
}; // size = 0x2048

struct HardwareOpusDecoder_Sub {
    /* 0x00 */ u64 hostInData;
    /* 0x08 */ u64 dspInData;
    /* 0x10 */ u64 inDataSize;
    /* 0x18 */ u64 hostOutData;
    /* 0x20 */ u64 dspOutData;
    /* 0x28 */ u64 bufferSize;
    /* 0x30 */ u64 hostSharedMem;
    /* 0x38 */ u64 sharedMemSize;
    /* 0x40 */ u32 dspSharedMem;
    /* 0x44 */ s32 sampleRate;
    /* 0x48 */ s32 channelCount;
    /* 0x4C */ s32 useLargeFrameSize;
    /* 0x50 */ s32 totalStreamCount;
    /* 0x54 */ s32 stereoStreamCount;
    /* 0x58 */ bool sharedMemoryMapped;
    /* 0x59 */ bool dspDecodeObjectInitialised;
}; // size = 0x60

struct nn::audio::detail::HardwareOpusDecoderImpl {
    /* 0x00 */ nn::os::TransferMemoryType transferMemory;
    /* 0x40 */ bool transferMemoryMapped;
    /* 0x48 */ HardwareOpusDecoder_Sub unk_48;
    /* 0xA8 */ u32 unk_A8;
}; // size = 0xB0

struct nn::audio::detail::HardwareOpusDecoder {
    /* 0x00 */ nn::audio::detail::IHardwareOpusDecoder::vtable* __vftable;
    /* 0x08 */ nn::audio::detail::HardwareOpusDecoderImpl impl;
    /* 0xB8 */ void* heap;
}; // size = 0xC0


