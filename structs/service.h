typedef signed char s8;
typedef signed short s16;
typedef signed int s32;
typedef signed long s64;

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef float f32;
typedef double f64;


// =================== SERVICE BASES ===================
// service objects have these as bases, usually coming after the object itself

#include "nn/nn.h"

// nn::Result ServiceHandler_IAudioOutManager(nn::sf::IServiceObject *object, nn::sf::cmif::server::CmifServerMessage *message, nn::sf::detail::PointerAndSize const *pas)
// nn::Result Process_IAudioOutManager_ListAudioOuts(nn::sf::cmif::CmifOutHeader **, Interface *, nn::sf::cmif::server::CmifServerMessage *, nn::sf::detail::PointerAndSize *)

// =================== SERVICE ===================

struct nn::audio::detail::IAudioRendererManager {
    struct nn::audio::server::IAudioRendererManagerImpl::vtbl* __vftable;
};

struct nn::audio::server::IAudioRendererManagerImpl::vtbl {
    /* 0x00 */ void (*AddReference)(nn::audio::detail::IAudioRendererManager*);
    /* 0x08 */ void (*Release)(nn::audio::detail::IAudioRendererManager*);
    /* 0x10 */ void (*GetProxyInfo)(nn::audio::detail::IAudioRendererManager*);
    /* 0x18 */ void (*GetInterfaceTypeInfo)(nn::audio::detail::IAudioRendererManager*);

    /* 0x20 */ void (*OpenAudioRenderer)(nn::audio::detail::IAudioRendererManager*);
    /* 0x28 */ void (*GetWorkBufferSize)(nn::audio::detail::IAudioRendererManager*);
    /* 0x30 */ void (*GetAudioDeviceService)(nn::audio::detail::IAudioRendererManager*);
    /* 0x38 */ void (*OpenAudioRendererForManualExecution)(nn::audio::detail::IAudioRendererManager*);
    /* 0x40 */ void (*GetAudioDeviceServiceWithRevisionInfo)(nn::audio::detail::IAudioRendererManager*);
}; // size = 0x48

struct nn::audio::server::IAudioRenderer {
    struct nn::audio::server::IAudioRenderer::vtbl* __vftable;
};

struct nn::audio::server::IAudioRenderer::vtbl {
    /* 0x00 */ void (*AddReference)(nn::audio::server::IAudioRenderer*);
    /* 0x08 */ void (*Release)(nn::audio::server::IAudioRenderer*);
    /* 0x10 */ void (*GetProxyInfo)(nn::audio::server::IAudioRenderer*);
    /* 0x18 */ void (*GetInterfaceTypeInfo)(nn::audio::server::IAudioRenderer*);

    /* 0x20 */ void (*GetSampleRate)(nn::audio::server::IAudioRenderer*);
    /* 0x28 */ void (*GetSampleCount)(nn::audio::server::IAudioRenderer*);
    /* 0x30 */ void (*GetMixBuffer)(nn::audio::server::IAudioRenderer*);
    /* 0x40 */ void (*GetState)(nn::audio::server::IAudioRenderer*);
    /* 0x48 */ void (*RequestUpdate)(nn::audio::server::IAudioRenderer*);
    /* 0x50 */ void (*Start)(nn::audio::server::IAudioRenderer*);
    /* 0x58 */ void (*Stop)(nn::audio::server::IAudioRenderer*);
    /* 0x60 */ void (*QuerySystemEvent)(nn::audio::server::IAudioRenderer*);
    /* 0x68 */ void (*SetRenderingTimeLimit)(nn::audio::server::IAudioRenderer*);
    /* 0x70 */ void (*GetRenderingTimeLimit)(nn::audio::server::IAudioRenderer*);
    /* 0x78 */ void (*RequestUpdateAuto)(nn::audio::server::IAudioRenderer*);
    /* 0x80 */ void (*ExecuteAudioRendererRendering)(nn::audio::server::IAudioRenderer*);
}; // size = 0x88

// audout:u
struct nn::audio::server::IAudioOutManager {
    /* 0x00 */ struct nn::audio::server::IAudioOutManager::vtbl* __vtable;
    /* 0x08 */ nn::sf::hipc::client::Hipc2ClientProxyBaseObject proxyBase;
    /* 0x10 */ nn::sf::detail::CmifProxyInfo proxyInfo;
}; // size = 0x20

struct nn::audio::server::IAudioOutManager::vtbl {
    /* 0x00 */ void (*AddReference)(nn::audio::server::IAudioOutManager*);
    /* 0x08 */ void (*Release)(nn::audio::server::IAudioOutManager*);
    /* 0x10 */ void (*GetProxyInfo)(nn::audio::server::IAudioOutManager*);
    /* 0x18 */ void (*GetInterfaceTypeInfo)(nn::audio::server::IAudioOutManager*);

    /* 0x20 */ nn::Result (*ListAudioOuts)(nn::audio::server::IAudioOutManager*, nn::sf::detail::PointerAndSize** outNames, s32* outCount);
    /* 0x28 */ nn::Result (*OpenAudioOut)(nn::audio::server::IAudioOutManager*);
    /* 0x30 */ nn::Result (*ListAudioOutsAuto)(nn::audio::server::IAudioOutManager*);
    /* 0x38 */ nn::Result (*OpenAudioOutAuto)(nn::audio::server::IAudioOutManager*);
};

struct nn::audio::server::IAudioOut::vtbl {
    /* 0x00 */ void (*AddReference)(struct nn::audio::server::IAudioOut*);
    /* 0x08 */ void (*Release)(struct nn::audio::server::IAudioOut*);
    /* 0x10 */ void (*GetProxyInfo)(struct nn::audio::server::IAudioOut*);
    /* 0x18 */ void (*GetInterfaceTypeInfo)(struct nn::audio::server::IAudioOut*);

    /* 0x20 */ nn::Result (*GetAudioOutState)(struct nn::audio::server::IAudioOut*);
    /* 0x28 */ nn::Result (*Start)(struct nn::audio::server::IAudioOut*);
    /* 0x30 */ nn::Result (*Stop)(struct nn::audio::server::IAudioOut*);
    /* 0x38 */ nn::Result (*AppendAudioOutBuffer)(struct nn::audio::server::IAudioOut*);
    /* 0x40 */ nn::Result (*RegisterBufferEvent)(struct nn::audio::server::IAudioOut*);
    /* 0x48 */ nn::Result (*GetReleasedAudioOutBuffers)(struct nn::audio::server::IAudioOut*);
    /* 0x50 */ nn::Result (*ContainsAudioOutBuffer)(struct nn::audio::server::IAudioOut*);
    /* 0x58 */ nn::Result (*AppendAudioOutBufferAuto)(struct nn::audio::server::IAudioOut*);
    /* 0x60 */ nn::Result (*GetReleasedAudioOutBuffersAuto)(struct nn::audio::server::IAudioOut*);
    /* 0x68 */ nn::Result (*GetAudioOutBufferCount)(struct nn::audio::server::IAudioOut*);
    /* 0x70 */ nn::Result (*GetAudioOutPlayedSampleCount)(struct nn::audio::server::IAudioOut*);
    /* 0x78 */ nn::Result (*FlushAudioOutBuffers)(struct nn::audio::server::IAudioOut*);
    /* 0x80 */ nn::Result (*SetAudioOutVolume)(struct nn::audio::server::IAudioOut*);
    /* 0x88 */ nn::Result (*GetAudioOutVolume)(struct nn::audio::server::IAudioOut*);
};

struct nn::audio::IAudioInManager {
    /* 0x000 */ struct nn::audio::server::IAudioInManager::vtbl* __vftable;
};

struct nn::audio::server::IAudioInManager::vtbl {
    /* 0x00 */ void (*AddReference)(nn::audio::IAudioInManager*);
    /* 0x08 */ void (*Release)(nn::audio::IAudioInManager*);
    /* 0x10 */ void (*GetProxyInfo)(nn::audio::IAudioInManager*);
    /* 0x18 */ void (*GetInterfaceTypeInfo)(nn::audio::IAudioInManager*);

    /* 0x20 */ nn::Result (*ListAudioIns)(nn::audio::IAudioInManager*, nn::sf::detail::PointerAndSize** outNames, s32* outCount);
    /* 0x28 */ nn::Result (*OpenAudioIn)(nn::audio::IAudioInManager*);
    /* 0x30 */ nn::Result (*ListAudioInsAuto)(nn::audio::IAudioInManager*);
    /* 0x38 */ nn::Result (*OpenAudioInAuto)(nn::audio::IAudioInManager*);
    /* 0x38 */ nn::Result (*ListAudioInsAutoFiltered)(nn::audio::IAudioInManager*);
    /* 0x38 */ nn::Result (*OpenAudioInProtocolSpecified)(nn::audio::IAudioInManager*);
};

struct nn::audio::IAudioIn::vtbl {
    /* 0x00 */ void (*AddReference)(struct nn::audio::AudioIn*);
    /* 0x08 */ void (*Release)(struct nn::audio::AudioIn*);
    /* 0x10 */ void (*GetProxyInfo)(struct nn::audio::AudioIn*);
    /* 0x18 */ void (*GetInterfaceTypeInfo)(struct nn::audio::AudioIn*);

    /* 0x20 */ nn::Result (*GetAudioInState)(struct nn::audio::AudioIn*);
    /* 0x28 */ nn::Result (*Start)(struct nn::audio::AudioIn*);
    /* 0x30 */ nn::Result (*Stop)(struct nn::audio::AudioIn*);
    /* 0x38 */ nn::Result (*AppendAudioInBuffer)(struct nn::audio::AudioIn*);
    /* 0x40 */ nn::Result (*RegisterBufferEvent)(struct nn::audio::AudioIn*);
    /* 0x48 */ nn::Result (*GetReleasedAudioInBuffers)(struct nn::audio::AudioIn*);
    /* 0x50 */ nn::Result (*ContainsAudioInBuffer)(struct nn::audio::AudioIn*);
    /* 0x58 */ nn::Result (*AppendUacInBuffer)(struct nn::audio::AudioIn*);
    /* 0x60 */ nn::Result (*AppendAudioInBufferAuto)(struct nn::audio::AudioIn*);
    /* 0x68 */ nn::Result (*GetReleasedAudioInBuffersAuto)(struct nn::audio::AudioIn*);
    /* 0x70 */ nn::Result (*AppendUacInBufferAuto)(struct nn::audio::AudioIn*);
    /* 0x78 */ nn::Result (*GetAudioInBufferCount)(struct nn::audio::AudioIn*);
    /* 0x80 */ nn::Result (*SetDeviceGain)(struct nn::audio::AudioIn*);
    /* 0x88 */ nn::Result (*GetDeviceGain)(struct nn::audio::AudioIn*);
    /* 0x90 */ nn::Result (*FlushAudioInBuffers)(struct nn::audio::AudioIn*);
};

struct nn::audio::IFinalOutputRecorderManager {
    /* 0x000 */ struct nn::audio::IFinalOutputRecorderManager::vtable* __vftable;
};

struct nn::audio::IFinalOutputRecorderManager::vtable {
    /* 0x00 */ void (*AddReference)(struct nn::audio::IFinalOutputRecorderManager*);
    /* 0x08 */ void (*Release)(struct nn::audio::IFinalOutputRecorderManager*);
    /* 0x10 */ void (*GetProxyInfo)(struct nn::audio::IFinalOutputRecorderManager*);
    /* 0x18 */ void (*GetInterfaceTypeInfo)(struct nn::audio::IFinalOutputRecorderManager*);

    /* 0x00 */ void (*OpenFinalOutputRecorder)(nn::audio::IFinalOutputRecorderManager*);
    /* 0x08 */ void (*D2)(nn::audio::IFinalOutputRecorderManager*);
    /* 0x10 */ void (*D0)(nn::audio::IFinalOutputRecorderManager*);
}; 

struct nn::audio::FinalOutputRecorder::vtable {
    /* 0x00 */ void (*AddReference)(struct nn::audio::FinalOutputRecorder*);
    /* 0x08 */ void (*Release)(struct nn::audio::FinalOutputRecorder*);
    /* 0x10 */ void (*GetProxyInfo)(struct nn::audio::FinalOutputRecorder*);
    /* 0x18 */ void (*GetInterfaceTypeInfo)(struct nn::audio::FinalOutputRecorder*);

    /* 0x20 */ nn::Result (*GetFinalOutputRecorderState)(struct nn::audio::FinalOutputRecorder*);
    /* 0x28 */ nn::Result (*Start)(struct nn::audio::FinalOutputRecorder*);
    /* 0x30 */ nn::Result (*Stop)(struct nn::audio::FinalOutputRecorder*);
    /* 0x38 */ nn::Result (*AppendFinalOutputRecorderBuffer)(struct nn::audio::FinalOutputRecorder*);
    /* 0x40 */ nn::Result (*RegisterBufferEvent)(struct nn::audio::FinalOutputRecorder*);
    /* 0x48 */ nn::Result (*GetReleasedFinalOutputRecorderBuffers)(struct nn::audio::FinalOutputRecorder*);
    /* 0x50 */ nn::Result (*ContainsFinalOutputRecorderBuffer)(struct nn::audio::FinalOutputRecorder*);
    /* 0x58 */ nn::Result (*AppendFinalOutputRecorderBufferEndTime)(struct nn::audio::FinalOutputRecorder*);
    /* 0x60 */ nn::Result (*AppendFinalOutputRecorderBufferAuto)(struct nn::audio::FinalOutputRecorder*);
    /* 0x68 */ nn::Result (*GetReleasedFinalOutputRecorderBuffersAuto)(struct nn::audio::FinalOutputRecorder*);
    /* 0x70 */ nn::Result (*FlushFinalOutputRecorderBuffers)(struct nn::audio::FinalOutputRecorder*);
    /* 0x78 */ nn::Result (*AttachWorkbuffer)(struct nn::audio::FinalOutputRecorder*);
};

struct nn::audio::server::IAudioDevice::vtbl {
    /* 0x00 */ void (*AddReference)(struct nn::audio::server::IAudioDevice*);
    /* 0x08 */ void (*Release)(struct nn::audio::server::IAudioDevice*);
    /* 0x10 */ void (*GetProxyInfo)(struct nn::audio::server::IAudioDevice*);
    /* 0x18 */ void (*GetInterfaceTypeInfo)(struct nn::audio::server::IAudioDevice*);

    /* 0x20 */ nn::Result (*ListAudioDeviceName)(struct nn::audio::server::IAudioDevice*);
    /* 0x28 */ nn::Result (*SetAudioDeviceOutputVolume)(struct nn::audio::server::IAudioDevice*);
    /* 0x30 */ nn::Result (*GetAudioDeviceOutputVolume)(struct nn::audio::server::IAudioDevice*);
    /* 0x38 */ nn::Result (*GetActiveAudioDeviceName)(struct nn::audio::server::IAudioDevice*);
    /* 0x40 */ nn::Result (*QueryAudioDeviceSystemEvent)(struct nn::audio::server::IAudioDevice*);
    /* 0x48 */ nn::Result (*GetActiveChannelCount)(struct nn::audio::server::IAudioDevice*);
    /* 0x50 */ nn::Result (*ListAudioDeviceNameAuto)(struct nn::audio::server::IAudioDevice*);
    /* 0x58 */ nn::Result (*SetAudioDeviceOutputVolumeAuto)(struct nn::audio::server::IAudioDevice*);
    /* 0x60 */ nn::Result (*GetAudioDeviceOutputVolumeAuto)(struct nn::audio::server::IAudioDevice*);
    /* 0x68 */ nn::Result (*GetActiveAudioDeviceNameAuto)(struct nn::audio::server::IAudioDevice*);
    /* 0x70 */ nn::Result (*QueryAudioDeviceInputEvent)(struct nn::audio::server::IAudioDevice*);
    /* 0x78 */ nn::Result (*QueryAudioDeviceOutputEvent)(struct nn::audio::server::IAudioDevice*);
    /* 0x80 */ nn::Result (*GetAudioSystemMasterVolumeSetting)(struct nn::audio::server::IAudioDevice*);
    /* 0x88 */ nn::Result (*ListAudioOutputDeviceName)(struct nn::audio::server::IAudioDevice*);
};

struct nn::audio::server::IAudioDevice {
    /* 0x00 */ nn::audio::server::IAudioDevice::vtbl* __vftable;
};

struct nn::audio::AudioController;

struct nn::audio::AudioController::vtable {
    /* 0x000 */ void (*AddReference)(struct nn::audio::server::IAudioDevice*);
    /* 0x008 */ void (*Release)(struct nn::audio::server::IAudioDevice*);
    /* 0x010 */ void (*GetProxyInfo)(struct nn::audio::server::IAudioDevice*);
    /* 0x018 */ void (*GetInterfaceTypeInfo)(struct nn::audio::server::IAudioDevice*);
    
    /* 0x000 */ void (*GetTargetVolume)(nn::audio::AudioController*);
    /* 0x008 */ void (*SetTargetVolume)(nn::audio::AudioController*);
    /* 0x010 */ void (*GetTargetVolumeMin)(nn::audio::AudioController*);
    /* 0x018 */ void (*GetTargetVolumeMax)(nn::audio::AudioController*);
    /* 0x020 */ void (*IsTargetMute)(nn::audio::AudioController*);
    /* 0x028 */ void (*SetTargetMute)(nn::audio::AudioController*);
    /* 0x030 */ void (*IsTargetConnected)(nn::audio::AudioController*);
    /* 0x038 */ void (*SetDefaultTarget)(nn::audio::AudioController*);
    /* 0x040 */ void (*GetDefaultTarget)(nn::audio::AudioController*);
    /* 0x048 */ void (*GetAudioOutputMode)(nn::audio::AudioController*);
    /* 0x050 */ void (*SetAudioOutputMode)(nn::audio::AudioController*);
    /* 0x058 */ void (*SetForceMutePolicy)(nn::audio::AudioController*);
    /* 0x060 */ void (*GetForceMutePolicy)(nn::audio::AudioController*);
    /* 0x068 */ void (*GetOutputModeSetting)(nn::audio::AudioController*);
    /* 0x070 */ void (*SetOutputModeSetting)(nn::audio::AudioController*);
    /* 0x078 */ void (*SetOutputTarget)(nn::audio::AudioController*);
    /* 0x080 */ void (*SetInputTargetForceEnabled)(nn::audio::AudioController*);
    /* 0x088 */ void (*SetHeadphoneOutputLevelMode)(nn::audio::AudioController*);
    /* 0x090 */ void (*GetHeadphoneOutputLevelMode)(nn::audio::AudioController*);
    /* 0x098 */ void (*AcquireAudioVolumeUpdateEventForPlayReport)(nn::audio::AudioController*);
    /* 0x0A0 */ void (*AcquireAudioOutputDeviceUpdateEventForPlayReport)(nn::audio::AudioController*);
    /* 0x0A8 */ void (*GetAudioOutputTargetForPlayReport)(nn::audio::AudioController*);
    /* 0x0B0 */ void (*NotifyHeadphoneVolumeWarningDisplayedEvent)(nn::audio::AudioController*);
    /* 0x0B8 */ void (*SetSystemOutputMasterVolume)(nn::audio::AudioController*);
    /* 0x0C0 */ void (*GetSystemOutputMasterVolume)(nn::audio::AudioController*);
    /* 0x0C8 */ void (*GetAudioVolumeDataForPlayReport)(nn::audio::AudioController*);
    /* 0x0D0 */ void (*UpdateHeadphoneSettings)(nn::audio::AudioController*);
    /* 0x0D8 */ void (*SetVolumeMappingTableForDev)(nn::audio::AudioController*);
    /* 0x0E0 */ void (*GetAudioOutputChannelCountForPlayReport)(nn::audio::AudioController*);
    /* 0x0E8 */ void (*BindAudioOutputChannelCountUpdateEventForPlayReport)(nn::audio::AudioController*);
    /* 0x0F0 */ void (*SetSpeakerAutoMuteEnabled)(nn::audio::AudioController*);
    /* 0x0F8 */ void (*IsSpeakerAutoMuteEnabled)(nn::audio::AudioController*);
    /* 0x100 */ void (*GetActiveOutputTarget)(nn::audio::AudioController*);
    /* 0x108 */ void (*GetTargetDeviceInfo)(nn::audio::AudioController*);
    /* 0x110 */ void (*AcquireTargetNotification)(nn::audio::AudioController*);
    /* 0x118 */ void (*NotifyAudioOutputTargetForPlayReport)(nn::audio::AudioController*);
    /* 0x120 */ void (*NotifyAudioOutputChannelCountForPlayReport)(nn::audio::AudioController*);
    /* 0x128 */ void (*NotifyUnsupportedUsbOutputDeviceAttachedForPlayReport)(nn::audio::AudioController*);
};

struct nn::audio::detail::AudioSystemManagerForAppletImpl {
    /* 0x00 */ char unk00[0x4];
};

struct nn::audio::detail::AudioSystemManagerForApplet {
    /* 0x00 */ struct nn::audio::detail::AudioSystemManagerForApplet::vtable* __vftable;
    /* 0x08 */ nn::audio::detail::AudioSystemManagerForAppletImpl* impl;
};

struct nn::audio::detail::AudioSystemManagerForApplet::vtable {
    /* 0x00 */ void (*AddReference)(nn::audio::detail::AudioSystemManagerForApplet*);
    /* 0x08 */ void (*Release)(nn::audio::detail::AudioSystemManagerForApplet*);
    /* 0x10 */ void (*GetProxyInfo)(nn::audio::detail::AudioSystemManagerForApplet*);
    /* 0x18 */ void (*GetInterfaceTypeInfo)(nn::audio::detail::AudioSystemManagerForApplet*);
    
    /* 0x20 */ void (*RegisterAppletResourceUserId)(nn::audio::detail::AudioSystemManagerForApplet*);
    /* 0x28 */ void (*UnregisterAppletResourceUserId)(nn::audio::detail::AudioSystemManagerForApplet*);
    /* 0x30 */ void (*RequestSuspendAudio)(nn::audio::detail::AudioSystemManagerForApplet*);
    /* 0x38 */ void (*RequestResumeAudio)(nn::audio::detail::AudioSystemManagerForApplet*);
    /* 0x40 */ void (*GetAudioOutputProcessMasterVolume)(nn::audio::detail::AudioSystemManagerForApplet*);
    /* 0x48 */ void (*SetAudioOutputProcessMasterVolume)(nn::audio::detail::AudioSystemManagerForApplet*);
    /* 0x50 */ void (*GetAudioInputProcessMasterVolume)(nn::audio::detail::AudioSystemManagerForApplet*);
    /* 0x58 */ void (*SetAudioInputProcessMasterVolume)(nn::audio::detail::AudioSystemManagerForApplet*);
    /* 0x60 */ void (*GetAudioOutputProcessRecordVolume)(nn::audio::detail::AudioSystemManagerForApplet*);
    /* 0x68 */ void (*SetAudioOutputProcessRecordVolume)(nn::audio::detail::AudioSystemManagerForApplet*);
};

struct nn::audio::detail::IHardwareOpusDecoderManager {
    /* 0x00 */ struct nn::audio::detail::IHardwareOpusDecoderManager::vtable* __vftable;
    /* 0x08 */ nn::sf::hipc::client::Hipc2ClientProxyBaseObject proxyBase;
    /* 0x10 */ nn::sf::detail::CmifProxyInfo proxyInfo;
}; // size = 0x20

struct nn::audio::detail::IHardwareOpusDecoderManager::vtable {
    /* 0x00 */ void (*AddReference)(nn::audio::detail::IHardwareOpusDecoderManager*);
    /* 0x08 */ void (*Release)(nn::audio::detail::IHardwareOpusDecoderManager*);
    /* 0x10 */ void (*GetProxyInfo)(nn::audio::detail::IHardwareOpusDecoderManager*);
    /* 0x18 */ void (*GetInterfaceTypeInfo)(nn::audio::detail::IHardwareOpusDecoderManager*);
    
    /* 0x20 */ void (*OpenHardwareOpusDecoder)(nn::audio::detail::IHardwareOpusDecoderManager*);
    /* 0x28 */ void (*GetWorkBufferSize)(nn::audio::detail::IHardwareOpusDecoderManager*);
    /* 0x30 */ void (*OpenHardwareOpusDecoderForMultistream)(nn::audio::detail::IHardwareOpusDecoderManager*);
    /* 0x38 */ void (*GetWorkBufferSizeForMultiStream)(nn::audio::detail::IHardwareOpusDecoderManager*);
    /* 0x40 */ void (*OpenHardwareOpusDecoderEx)(nn::audio::detail::IHardwareOpusDecoderManager*);
    /* 0x48 */ void (*GetWorkBufferSizeEx)(nn::audio::detail::IHardwareOpusDecoderManager*);
    /* 0x50 */ void (*OpenHardwareOpusDecoderForMultiStreamEx)(nn::audio::detail::IHardwareOpusDecoderManager*);
    /* 0x58 */ void (*GetWorkBufferSizeForMultiStreamEx)(nn::audio::detail::IHardwareOpusDecoderManager*);
};

struct nn::audio::detail::IHardwareOpusDecoder {
    /* 0x00 */ struct nn::audio::detail::IHardwareOpusDecoder::vtable* __vftable;
    /* 0x08 */ nn::sf::hipc::client::Hipc2ClientProxyBaseObject proxyBase;
    /* 0x10 */ nn::sf::detail::CmifProxyInfo proxyInfo;
}; // size = 0x20

struct nn::audio::detail::IHardwareOpusDecoder::vtable {
    /* 0x00 */ void (*AddReference)(nn::audio::detail::IHardwareOpusDecoder*);
    /* 0x08 */ void (*Release)(nn::audio::detail::IHardwareOpusDecoder*);
    /* 0x10 */ void (*GetProxyInfo)(nn::audio::detail::IHardwareOpusDecoder*);
    /* 0x18 */ void (*GetInterfaceTypeInfo)(nn::audio::detail::IHardwareOpusDecoder*);
    
    /* 0x20 */ void (*DecodeInterleavedOld)(nn::audio::detail::IHardwareOpusDecoder*);
    /* 0x28 */ void (*SetContext)(nn::audio::detail::IHardwareOpusDecoder*);
    /* 0x30 */ void (*DecodeInterleavedForMultiStreamOld)(nn::audio::detail::IHardwareOpusDecoder*);
    /* 0x38 */ void (*SetContextForMultiStream)(nn::audio::detail::IHardwareOpusDecoder*);
    /* 0x40 */ void (*DecodeInterleavedWithPerfOld)(nn::audio::detail::IHardwareOpusDecoder*);
    /* 0x48 */ void (*DecodeInterleavedForMultiStreamWithPerfOld)(nn::audio::detail::IHardwareOpusDecoder*);
    /* 0x50 */ void (*DecodeInterleavedWithPerfAndResetOld)(nn::audio::detail::IHardwareOpusDecoder*);
    /* 0x58 */ void (*DecodeInterleavedForMultiStreamWithPerfAndResetOld)(nn::audio::detail::IHardwareOpusDecoder*);
    /* 0x60 */ void (*DecodeInterleaved)(nn::audio::detail::IHardwareOpusDecoder*);
    /* 0x68 */ void (*DecodeInterleavedForMultiStream)(nn::audio::detail::IHardwareOpusDecoder*);
};

// =================== OS ===================

struct nn::sf::OutBuffer {
    /* 0x00 */ void* pointer;
    /* 0x08 */ u64 size;
}; // size = 0x10

struct nn::sf::InBuffer {
    /* 0x00 */ void* pointer;
    /* 0x08 */ u64 size;
}; // size = 0x10

struct nn::os::TimeSpan {
    /* 0x00 */ u64 time;
}; // size = 0x8

struct nn::os::detail::InternalCriticalSection {
    /* 0x00 */ u32 image;
}; // size = 0x4

struct nn::os::detail::InternalConditionVariable  {
    /* 0x00 */ u32 image;
}; // size = 0x4

struct nn::os::SystemEvent {
    /* 0x00 */ u32 handle;
    /* 0x04 */ bool valid;
    /* 0x05 */ char unk05[0xF];
    /* 0x14 */ u32 unk_14;
}; // size >= 0x18

//struct nn::os::SystemEventType {
//    union {
//        /* 0x00 */ nn::os::EventType event;
//        /* 0x00 */ nn::os::detail::InterProcessEventType;
//    };
//    /* 0x28 */ u8 state;
//    /* 0x29 */ char unk29[0x7];
//}; // size = 0x30

//struct nn::os::EventType {
//    /* 0x00 */ nn::os::EventType* multi_wait_object_list_storage;
//    /* 0x08 */ nn::os::EventType* multi_wait_object_list_storage08;
//    /* 0x10 */ bool signalled;
//    /* 0x11 */ bool initiallySignaled;
//    /* 0x12 */ u8 clear_mode;
//    /* 0x13 */ u8 state;
//    /* 0x14 */ u32 broadcast_counter_low;
//    /* 0x18 */ u32 broadcast_counter_high;
//    /* 0x1C */ nn::os::detail::InternalCriticalSection section;
//    /* 0x20 */ nn::os::detail::InternalConditionVariable conditionVariable;
//    /* 0x24 */ char unk24[0x4];
//}; // size = 0x28

struct nn::os::Mutex {
    /* 0x00 */ char unk00[0x20];
}; // size = 0x20

struct nn::os::SdkMutexType {
    /* 0x00 */ u32 mutex;
}; // size >= 0x4

struct nn::os::SdkRecursiveMutexType {
    /* 0x00 */ u32 mutex;
    /* 0x00 */ u32 unk_04;
}; // size = 0x8

struct nn::os::Thread {
    /* 0x000 */ char unk000[0x1A0];
    /* 0x1A0 */ char* name;
    /* 0x1A8 */ char unk1A8[0x18];
}; // size = 0x1C0

struct nn::os::SemaphoreType {
    /* 0x00 */ char storage[0x28];
}; // size = 0x28

struct nn::os::MultiWaitType {
    /* 0x00 */ bool isInitialised;
    /* 0x01 */ char unk01[0x27];
    /* 0x28 */ nn::os::detail::InternalCriticalSection criticalSection;
    /* 0x2C */ char unk2C[0x4];
}; // size = 0x30

struct nn::os::MultiWaitHolderType {
    /* 0x00 */ nn::os::MultiWaitType multiWait;
    /* 0x30 */ nn::os::SemaphoreType* semaphore;
    /* 0x38 */ u64 userData;
}; // size = 0x40

struct __attribute__((packed)) nn::util::BitArray {
    /* 0x00 */ u64* buffer;
    /* 0x08 */ s32 size;
}; // size = 0x0C

enum EXECUTIONMODE : u32 {
    DSP = 1,
    CPU = 2,
};

enum nn::audio::server::MemoryPoolInfo::Location {
    CPU = 1,
    DSP = 2,
};

// a span-type struct
struct span {
    void* data;
    s64 size;
};

enum nn::psc::PmModuleId {
    /* 0x00 */ Reserved0,
    /* 0x01 */ Reserved1,
    /* 0x02 */ Reserved2,
    /* 0x03 */ Socket,
    /* 0x04 */ Usb,
    /* 0x05 */ Eth,
    /* 0x06 */ Fgm,
    /* 0x07 */ PcvClock,
    /* 0x08 */ PcvVoltage,
    /* 0x09 */ Gpio,
    /* 0x0A */ Pinmux,
    /* 0x0B */ Uart,
    /* 0x0C */ I2c,
    /* 0x0D */ I2cPowerBus,
    /* 0x0E */ Spi,
    /* 0x0F */ Pwm,
    /* 0x10 */ Psm,
    /* 0x11 */ Tc,
    /* 0x12 */ Omm,
    /* 0x13 */ Pcie,
    /* 0x14 */ Lbl,
    /* 0x15 */ Display,
    /* 0x16 */ Multimedia,
    /* 0x17 */ Time17,
    /* 0x18 */ Hid,
    /* 0x19 */ SocketWlan,
    /* 0x1A */ Wlan,
    /* 0x1B */ Fs,
    /* 0x1C */ Audio,
    /* 0x1D */ Tm,
    /* 0x1E */ TmHostIo,
    /* 0x1F */ Bluetooth,
    /* 0x20 */ Bpc,
    /* 0x21 */ Fan,
    /* 0x22 */ Pcm,
    /* 0x23 */ Nfc,
    /* 0x24 */ Apm,
    /* 0x25 */ Btm,
    /* 0x26 */ Nifm,
    /* 0x27 */ GpioLow,
    /* 0x28 */ Npns,
    /* 0x29 */ Lm,
    /* 0x2A */ Bcat,
    /* 0x2B */ Time2B,
    /* 0x2C */ Pctl,
    /* 0x2D */ Erpt,
    /* 0x2E */ Eupld,
    /* 0x2F */ Friends,
    /* 0x30 */ Bgtc,
    /* 0x31 */ Account,
    /* 0x32 */ Sasbus,
    /* 0x33 */ Ntc,
    /* 0x34 */ Idle,
    /* 0x35 */ Tcap,
    /* 0x36 */ PsmLow,
    /* 0x37 */ Ndd,
    /* 0x38 */ Olsc,
    /* 0x39 */ Rtc,
    /* 0x3A */ Unk3A,
    /* 0x3B */ Unk3B,
    /* 0x3C */ Led,
    /* 0x3D */ Ns,
    /* 0x3E */ Unk3E,
    /* 0x3F */ NotificationPresenter,
    /* 0x40 */ Unk40,
    /* 0x41 */ DhcpClient,
    /* 0x65 */ NvHost = 0x65,
    /* 0x69 */ NvDbgSvc = 0x69,
    /* 0x6A */ Tspm = 0x6A,
    /* 0x7F */ Spsm = 0x7F,
};

enum nn::psc::PmState {
    /* 0 */ FullAwake,                   // Everything is awake.
    /* 1 */ MinimumAwake,                // Preparing to transition to awake.
    /* 2 */ SleepReady,                  // Preparing to transition to sleep.
    /* 3 */ EssentialServicesSleepReady, // Critical services are ready to sleep.
    /* 4 */ EssentialServicesAwake,      // Critical services are ready to wake up.
    /* 5 */ ShutdownReady,               // Preparing to transition to shutdown.
    /* 6 */ Invalid,                     // Default state. 
};

struct nn::bluetooth::IBluetoothDriver {
    /* 0x00 */ struct nn::bluetooth::IBluetoothDriver::vtable* __vftable;
    /* 0x08 */ char unk_08[0x18];
}; // size = 0x20

struct nn::bluetooth::IBluetoothDriver::vtable {
    /* 0x00 */ void (*AddReference)(nn::bluetooth::IBluetoothDriver*);
    /* 0x08 */ void (*Release)(nn::bluetooth::IBluetoothDriver*);
    /* 0x10 */ void (*GetProxyInfo)(nn::bluetooth::IBluetoothDriver*);
    /* 0x18 */ void (*GetInterfaceTypeInfo)(nn::bluetooth::IBluetoothDriver*);

    /* 0x020 */ void (*InitializeBluetoothDriver)(nn::bluetooth::IBluetoothDriver*);
    /* 0x028 */ void (*InitializeBluetooth)(nn::bluetooth::IBluetoothDriver*);
    /* 0x030 */ void (*EnableBluetooth)(nn::bluetooth::IBluetoothDriver*);
    /* 0x038 */ void (*DisableBluetooth)(nn::bluetooth::IBluetoothDriver*);
    /* 0x040 */ void (*FinalizeBluetooth)(nn::bluetooth::IBluetoothDriver*);
    /* 0x048 */ void (*GetAdapterProperties)(nn::bluetooth::IBluetoothDriver*);
    /* 0x050 */ void (*GetAdapterProperty)(nn::bluetooth::IBluetoothDriver*);
    /* 0x058 */ void (*SetAdapterProperty)(nn::bluetooth::IBluetoothDriver*);
    /* 0x060 */ void (*StartInquiry)(nn::bluetooth::IBluetoothDriver*);
    /* 0x068 */ void (*StopInquiry)(nn::bluetooth::IBluetoothDriver*);
    /* 0x070 */ void (*CreateBond)(nn::bluetooth::IBluetoothDriver*);
    /* 0x078 */ void (*RemoveBond)(nn::bluetooth::IBluetoothDriver*);
    /* 0x080 */ void (*CancelBond)(nn::bluetooth::IBluetoothDriver*);
    /* 0x088 */ void (*RespondToPinRequest)(nn::bluetooth::IBluetoothDriver*);
    /* 0x090 */ void (*RespondToSspRequest)(nn::bluetooth::IBluetoothDriver*);
    /* 0x098 */ void (*GetEventInfo)(nn::bluetooth::IBluetoothDriver*);
    /* 0x0A0 */ void (*InitializeHid)(nn::bluetooth::IBluetoothDriver*);
    /* 0x0A8 */ void (*OpenHidConnection)(nn::bluetooth::IBluetoothDriver*);
    /* 0x0B0 */ void (*CloseHidConnection)(nn::bluetooth::IBluetoothDriver*);
    /* 0x0B8 */ void (*WriteHidData)(nn::bluetooth::IBluetoothDriver*);
    /* 0x0C0 */ void (*WriteHidData2)(nn::bluetooth::IBluetoothDriver*);
    /* 0x0C8 */ void (*SetHidReport)(nn::bluetooth::IBluetoothDriver*);
    /* 0x0D0 */ void (*GetHidReport)(nn::bluetooth::IBluetoothDriver*);
    /* 0x0D8 */ void (*TriggerConnection)(nn::bluetooth::IBluetoothDriver*);
    /* 0x0E0 */ void (*AddPairedDeviceInfo)(nn::bluetooth::IBluetoothDriver*);
    /* 0x0E8 */ void (*GetPairedDeviceInfo)(nn::bluetooth::IBluetoothDriver*);
    /* 0x0F0 */ void (*FinalizeHid)(nn::bluetooth::IBluetoothDriver*);
    /* 0x0F8 */ void (*GetHidEventInfo)(nn::bluetooth::IBluetoothDriver*);
    /* 0x100 */ void (*SetTsi)(nn::bluetooth::IBluetoothDriver*);
    /* 0x108 */ void (*EnableBurstMode)(nn::bluetooth::IBluetoothDriver*);
    /* 0x110 */ void (*SetZeroRetransmission)(nn::bluetooth::IBluetoothDriver*);
    /* 0x118 */ void (*EnableMcMode)(nn::bluetooth::IBluetoothDriver*);
    /* 0x120 */ void (*EnableLlrScan)(nn::bluetooth::IBluetoothDriver*);
    /* 0x128 */ void (*DisableLlrScan)(nn::bluetooth::IBluetoothDriver*);
    /* 0x130 */ void (*EnableRadio)(nn::bluetooth::IBluetoothDriver*);
    /* 0x138 */ void (*SetVisibility)(nn::bluetooth::IBluetoothDriver*);
    /* 0x140 */ void (*EnableTbfcScan)(nn::bluetooth::IBluetoothDriver*);
    /* 0x148 */ void (*RegisterHidReportEvent)(nn::bluetooth::IBluetoothDriver*);
    /* 0x150 */ void (*GetHidReportEventInfo)(nn::bluetooth::IBluetoothDriver*);
    /* 0x158 */ void (*GetLatestPlr)(nn::bluetooth::IBluetoothDriver*);
    /* 0x160 */ void (*GetPendingConnections)(nn::bluetooth::IBluetoothDriver*);
    /* 0x168 */ void (*GetChannelMap)(nn::bluetooth::IBluetoothDriver*);
    /* 0x170 */ void (*EnableTxPowerBoostSetting)(nn::bluetooth::IBluetoothDriver*);
    /* 0x178 */ void (*IsTxPowerBoostSettingEnabled)(nn::bluetooth::IBluetoothDriver*);
    /* 0x180 */ void (*EnableAfhSetting)(nn::bluetooth::IBluetoothDriver*);
    /* 0x188 */ void (*IsAfhSettingEnabled)(nn::bluetooth::IBluetoothDriver*);
    /* 0x190 */ void (*InitializeBle)(nn::bluetooth::IBluetoothDriver*);
    /* 0x198 */ void (*EnableBle)(nn::bluetooth::IBluetoothDriver*);
    /* 0x1A0 */ void (*DisableBle)(nn::bluetooth::IBluetoothDriver*);
    /* 0x1A8 */ void (*FinalizeBle)(nn::bluetooth::IBluetoothDriver*);
    /* 0x1B0 */ void (*SetBleVisibility)(nn::bluetooth::IBluetoothDriver*);
    /* 0x1B8 */ void (*SetBleConnectionParameter)(nn::bluetooth::IBluetoothDriver*);
    /* 0x1C0 */ void (*SetBleDefaultConnectionParameter)(nn::bluetooth::IBluetoothDriver*);
    /* 0x1C8 */ void (*SetBleAdvertiseData)(nn::bluetooth::IBluetoothDriver*);
    /* 0x1D0 */ void (*SetBleAdvertiseParameter)(nn::bluetooth::IBluetoothDriver*);
    /* 0x1D8 */ void (*StartBleScan)(nn::bluetooth::IBluetoothDriver*);
    /* 0x1E0 */ void (*StopBleScan)(nn::bluetooth::IBluetoothDriver*);
    /* 0x1E8 */ void (*AddBleScanFilterCondition)(nn::bluetooth::IBluetoothDriver*);
    /* 0x1F0 */ void (*DeleteBleScanFilterCondition)(nn::bluetooth::IBluetoothDriver*);
    /* 0x1F8 */ void (*DeleteBleScanFilter)(nn::bluetooth::IBluetoothDriver*);
    /* 0x200 */ void (*ClearBleScanFilters)(nn::bluetooth::IBluetoothDriver*);
    /* 0x208 */ void (*EnableBleScanFilter)(nn::bluetooth::IBluetoothDriver*);
    /* 0x210 */ void (*RegisterGattClient)(nn::bluetooth::IBluetoothDriver*);
    /* 0x218 */ void (*UnregisterGattClient)(nn::bluetooth::IBluetoothDriver*);
    /* 0x220 */ void (*UnregisterAllGattClients)(nn::bluetooth::IBluetoothDriver*);
    /* 0x228 */ void (*ConnectGattServer)(nn::bluetooth::IBluetoothDriver*);
    /* 0x230 */ void (*CancelConnectGattServer)(nn::bluetooth::IBluetoothDriver*);
    /* 0x238 */ void (*DisconnectGattServer)(nn::bluetooth::IBluetoothDriver*);
    /* 0x240 */ void (*GetGattAttribute)(nn::bluetooth::IBluetoothDriver*);
    /* 0x248 */ void (*GetGattService)(nn::bluetooth::IBluetoothDriver*);
    /* 0x250 */ void (*ConfigureAttMtu)(nn::bluetooth::IBluetoothDriver*);
    /* 0x258 */ void (*RegisterGattServer)(nn::bluetooth::IBluetoothDriver*);
    /* 0x260 */ void (*UnregisterGattServer)(nn::bluetooth::IBluetoothDriver*);
    /* 0x268 */ void (*ConnectGattClient)(nn::bluetooth::IBluetoothDriver*);
    /* 0x270 */ void (*DisconnectGattClient)(nn::bluetooth::IBluetoothDriver*);
    /* 0x278 */ void (*AddGattService)(nn::bluetooth::IBluetoothDriver*);
    /* 0x280 */ void (*EnableGattService)(nn::bluetooth::IBluetoothDriver*);
    /* 0x288 */ void (*AddGattCharacteristic)(nn::bluetooth::IBluetoothDriver*);
    /* 0x290 */ void (*AddGattDescriptor)(nn::bluetooth::IBluetoothDriver*);
    /* 0x298 */ void (*GetBleManagedEventInfo)(nn::bluetooth::IBluetoothDriver*);
    /* 0x2A0 */ void (*GetGattFirstCharacteristic)(nn::bluetooth::IBluetoothDriver*);
    /* 0x2A8 */ void (*GetGattNextCharacteristic)(nn::bluetooth::IBluetoothDriver*);
    /* 0x2B0 */ void (*GetGattFirstDescriptor)(nn::bluetooth::IBluetoothDriver*);
    /* 0x2B8 */ void (*GetGattNextDescriptor)(nn::bluetooth::IBluetoothDriver*);
    /* 0x2C0 */ void (*RegisterGattManagedDataPath)(nn::bluetooth::IBluetoothDriver*);
    /* 0x2C8 */ void (*UnregisterGattManagedDataPath)(nn::bluetooth::IBluetoothDriver*);
    /* 0x2D0 */ void (*RegisterGattHidDataPath)(nn::bluetooth::IBluetoothDriver*);
    /* 0x2D8 */ void (*UnregisterGattHidDataPath)(nn::bluetooth::IBluetoothDriver*);
    /* 0x2E0 */ void (*RegisterGattDataPath)(nn::bluetooth::IBluetoothDriver*);
    /* 0x2E8 */ void (*UnregisterGattDataPath)(nn::bluetooth::IBluetoothDriver*);
    /* 0x2F0 */ void (*ReadGattCharacteristic)(nn::bluetooth::IBluetoothDriver*);
    /* 0x2F8 */ void (*ReadGattDescriptor)(nn::bluetooth::IBluetoothDriver*);
    /* 0x300 */ void (*WriteGattCharacteristic)(nn::bluetooth::IBluetoothDriver*);
    /* 0x308 */ void (*WriteGattDescriptor)(nn::bluetooth::IBluetoothDriver*);
    /* 0x310 */ void (*RegisterGattNotification)(nn::bluetooth::IBluetoothDriver*);
    /* 0x318 */ void (*UnregisterGattNotification)(nn::bluetooth::IBluetoothDriver*);
    /* 0x320 */ void (*GetLeHidEventInfo)(nn::bluetooth::IBluetoothDriver*);
    /* 0x328 */ void (*RegisterBleHidEvent)(nn::bluetooth::IBluetoothDriver*);
    /* 0x330 */ void (*SetBleScanParameter)(nn::bluetooth::IBluetoothDriver*);
    /* 0x338 */ void (*MoveToSecondaryPiconet)(nn::bluetooth::IBluetoothDriver*);
    /* 0x340 */ void (*IsBluetoothEnabled)(nn::bluetooth::IBluetoothDriver*);
    /* 0x348 */ void (*AcquireAudioEvent)(nn::bluetooth::IBluetoothDriver*);
    /* 0x350 */ void (*GetAudioEventInfo)(nn::bluetooth::IBluetoothDriver*);
    /* 0x358 */ void (*OpenAudioConnection)(nn::bluetooth::IBluetoothDriver*);
    /* 0x360 */ void (*CloseAudioConnection)(nn::bluetooth::IBluetoothDriver*);
    /* 0x368 */ void (*OpenAudioOut)(nn::bluetooth::IBluetoothDriver*);
    /* 0x370 */ void (*CloseAudioOut)(nn::bluetooth::IBluetoothDriver*);
    /* 0x378 */ void (*AcquireAudioOutStateChangedEvent)(nn::bluetooth::IBluetoothDriver*);
    /* 0x380 */ void (*StartAudioOut)(nn::bluetooth::IBluetoothDriver*);
    /* 0x388 */ void (*StopAudioOut)(nn::bluetooth::IBluetoothDriver*);
    /* 0x390 */ void (*GetAudioOutState)(nn::bluetooth::IBluetoothDriver*);
    /* 0x398 */ void (*GetAudioOutFeedingCodec)(nn::bluetooth::IBluetoothDriver*);
    /* 0x3A0 */ void (*GetAudioOutFeedingParameter)(nn::bluetooth::IBluetoothDriver*);
    /* 0x3A8 */ void (*AcquireAudioOutBufferAvailableEvent)(nn::bluetooth::IBluetoothDriver*);
    /* 0x3B0 */ void (*SendAudioData)(nn::bluetooth::IBluetoothDriver*);
    /* 0x3B8 */ void (*AcquireAudioControlInputStateChangedEvent)(nn::bluetooth::IBluetoothDriver*);
    /* 0x3C0 */ void (*GetAudioControlInputState)(nn::bluetooth::IBluetoothDriver*);
    /* 0x3C8 */ void (*AcquireAudioConnectionStateChangedEvent)(nn::bluetooth::IBluetoothDriver*);
    /* 0x3D0 */ void (*GetConnectedAudioDevice)(nn::bluetooth::IBluetoothDriver*);
    /* 0x3D8 */ void (*CloseAudioControlInput)(nn::bluetooth::IBluetoothDriver*);
    /* 0x3E0 */ void (*RegisterAudioControlNotification)(nn::bluetooth::IBluetoothDriver*);
    /* 0x3E8 */ void (*SendAudioControlPassthroughCommand)(nn::bluetooth::IBluetoothDriver*);
    /* 0x3F0 */ void (*SendAudioControlSetAbsoluteVolumeCommand)(nn::bluetooth::IBluetoothDriver*);
    /* 0x3F8 */ void (*AcquireAudioSinkVolumeLocallyChangedEvent)(nn::bluetooth::IBluetoothDriver*);
    /* 0x400 */ void (*AcquireAudioSinkVolumeUpdateRequestCompletedEvent)(nn::bluetooth::IBluetoothDriver*);
    /* 0x408 */ void (*GetAudioSinkVolume)(nn::bluetooth::IBluetoothDriver*);
    /* 0x410 */ void (*RequestUpdateAudioSinkVolume)(nn::bluetooth::IBluetoothDriver*);
    /* 0x418 */ void (*IsAudioSinkVolumeSupported)(nn::bluetooth::IBluetoothDriver*);
    /* 0x420 */ void (*IsManufacturingMode)(nn::bluetooth::IBluetoothDriver*);
    /* 0x428 */ void (*EmulateBluetoothCrash)(nn::bluetooth::IBluetoothDriver*);
    /* 0x430 */ void (*GetBleChannelMap)(nn::bluetooth::IBluetoothDriver*);
};

struct nn::settings::ISystemSettingsServer {
    struct nn::settings::ISystemSettingsServer::vtable_16* __vftable;
};

struct nn::settings::ISystemSettingsServer::vtable {
    /* 0x00 */ void (*AddReference)(nn::settings::ISystemSettingsServer*);
    /* 0x08 */ void (*Release)(nn::settings::ISystemSettingsServer*);
    /* 0x10 */ void (*GetProxyInfo)(nn::settings::ISystemSettingsServer*);
    /* 0x18 */ void (*GetInterfaceTypeInfo)(nn::settings::ISystemSettingsServer*);

    /* 0x020 */ nn::Result (*SetLanguageCode)(nn::settings::ISystemSettingsServer*);
    /* 0x028 */ nn::Result (*SetNetworkSettings)(nn::settings::ISystemSettingsServer*);
    /* 0x030 */ nn::Result (*GetNetworkSettings)(nn::settings::ISystemSettingsServer*);
    /* 0x038 */ nn::Result (*GetFirmwareVersion)(nn::settings::ISystemSettingsServer*);
    /* 0x040 */ nn::Result (*GetFirmwareVersion2)(nn::settings::ISystemSettingsServer*);
    /* 0x048 */ nn::Result (*GetFirmwareVersionDigest)(nn::settings::ISystemSettingsServer*);
    /* 0x050 */ nn::Result (*GetLockScreenFlag)(nn::settings::ISystemSettingsServer*);
    /* 0x058 */ nn::Result (*SetLockScreenFlag)(nn::settings::ISystemSettingsServer*);
    /* 0x060 */ nn::Result (*GetBacklightSettings)(nn::settings::ISystemSettingsServer*);
    /* 0x068 */ nn::Result (*SetBacklightSettings)(nn::settings::ISystemSettingsServer*);
    /* 0x070 */ nn::Result (*SetBluetoothDevicesSettings)(nn::settings::ISystemSettingsServer*);
    /* 0x078 */ nn::Result (*GetBluetoothDevicesSettings)(nn::settings::ISystemSettingsServer*);
    /* 0x080 */ nn::Result (*GetExternalSteadyClockSourceId)(nn::settings::ISystemSettingsServer*);
    /* 0x088 */ nn::Result (*SetExternalSteadyClockSourceId)(nn::settings::ISystemSettingsServer*);
    /* 0x090 */ nn::Result (*GetUserSystemClockContext)(nn::settings::ISystemSettingsServer*);
    /* 0x098 */ nn::Result (*SetUserSystemClockContext)(nn::settings::ISystemSettingsServer*);
    /* 0x0A0 */ nn::Result (*GetAccountSettings)(nn::settings::ISystemSettingsServer*);
    /* 0x0A8 */ nn::Result (*SetAccountSettings)(nn::settings::ISystemSettingsServer*);
    /* 0x0B0 */ nn::Result (*GetAudioVolume)(nn::settings::ISystemSettingsServer*);
    /* 0x0B8 */ nn::Result (*SetAudioVolume)(nn::settings::ISystemSettingsServer*);
    /* 0x0C0 */ nn::Result (*GetEulaVersions)(nn::settings::ISystemSettingsServer*);
    /* 0x0C8 */ nn::Result (*SetEulaVersions)(nn::settings::ISystemSettingsServer*);
    /* 0x0D0 */ nn::Result (*GetColorSetId)(nn::settings::ISystemSettingsServer*);
    /* 0x0D8 */ nn::Result (*SetColorSetId)(nn::settings::ISystemSettingsServer*);
    /* 0x0E0 */ nn::Result (*GetConsoleInformationUploadFlag)(nn::settings::ISystemSettingsServer*);
    /* 0x0E8 */ nn::Result (*SetConsoleInformationUploadFlag)(nn::settings::ISystemSettingsServer*);
    /* 0x0F0 */ nn::Result (*GetAutomaticApplicationDownloadFlag)(nn::settings::ISystemSettingsServer*);
    /* 0x0F8 */ nn::Result (*SetAutomaticApplicationDownloadFlag)(nn::settings::ISystemSettingsServer*);
    /* 0x100 */ nn::Result (*GetNotificationSettings)(nn::settings::ISystemSettingsServer*);
    /* 0x108 */ nn::Result (*SetNotificationSettings)(nn::settings::ISystemSettingsServer*);
    /* 0x110 */ nn::Result (*GetAccountNotificationSettings)(nn::settings::ISystemSettingsServer*);
    /* 0x118 */ nn::Result (*SetAccountNotificationSettings)(nn::settings::ISystemSettingsServer*);
    /* 0x120 */ nn::Result (*GetVibrationMasterVolume)(nn::settings::ISystemSettingsServer*);
    /* 0x128 */ nn::Result (*SetVibrationMasterVolume)(nn::settings::ISystemSettingsServer*);
    /* 0x130 */ nn::Result (*GetSettingsItemValueSize)(nn::settings::ISystemSettingsServer*);
    /* 0x138 */ nn::Result (*GetSettingsItemValue)(nn::settings::ISystemSettingsServer*);
    /* 0x140 */ nn::Result (*GetTvSettings)(nn::settings::ISystemSettingsServer*);
    /* 0x148 */ nn::Result (*SetTvSettings)(nn::settings::ISystemSettingsServer*);
    /* 0x150 */ nn::Result (*GetEdid)(nn::settings::ISystemSettingsServer*);
    /* 0x158 */ nn::Result (*SetEdid)(nn::settings::ISystemSettingsServer*);
    /* 0x160 */ nn::Result (*GetAudioOutputMode)(nn::settings::ISystemSettingsServer*);
    /* 0x168 */ nn::Result (*SetAudioOutputMode)(nn::settings::ISystemSettingsServer*);
    /* 0x170 */ nn::Result (*GetSpeakerAutoMuteFlag)(nn::settings::ISystemSettingsServer*);
    /* 0x178 */ nn::Result (*SetSpeakerAutoMuteFlag)(nn::settings::ISystemSettingsServer*);
    /* 0x180 */ nn::Result (*GetQuestFlag)(nn::settings::ISystemSettingsServer*);
    /* 0x188 */ nn::Result (*SetQuestFlag)(nn::settings::ISystemSettingsServer*);
    /* 0x190 */ nn::Result (*GetDataDeletionSettings)(nn::settings::ISystemSettingsServer*);
    /* 0x198 */ nn::Result (*SetDataDeletionSettings)(nn::settings::ISystemSettingsServer*);
    /* 0x1A0 */ nn::Result (*GetInitialSystemAppletProgramId)(nn::settings::ISystemSettingsServer*);
    /* 0x1A8 */ nn::Result (*GetOverlayDispProgramId)(nn::settings::ISystemSettingsServer*);
    /* 0x1B0 */ nn::Result (*GetDeviceTimeZoneLocationName)(nn::settings::ISystemSettingsServer*);
    /* 0x1B8 */ nn::Result (*SetDeviceTimeZoneLocationName)(nn::settings::ISystemSettingsServer*);
    /* 0x1C0 */ nn::Result (*GetWirelessCertificationFileSize)(nn::settings::ISystemSettingsServer*);
    /* 0x1C8 */ nn::Result (*GetWirelessCertificationFile)(nn::settings::ISystemSettingsServer*);
    /* 0x1D0 */ nn::Result (*SetRegionCode)(nn::settings::ISystemSettingsServer*);
    /* 0x1D8 */ nn::Result (*GetNetworkSystemClockContext)(nn::settings::ISystemSettingsServer*);
    /* 0x1E0 */ nn::Result (*SetNetworkSystemClockContext)(nn::settings::ISystemSettingsServer*);
    /* 0x1E8 */ nn::Result (*IsUserSystemClockAutomaticCorrectionEnabled)(nn::settings::ISystemSettingsServer*);
    /* 0x1F0 */ nn::Result (*SetUserSystemClockAutomaticCorrectionEnabled)(nn::settings::ISystemSettingsServer*);
    /* 0x1F8 */ nn::Result (*GetDebugModeFlag)(nn::settings::ISystemSettingsServer*);
    /* 0x200 */ nn::Result (*GetPrimaryAlbumStorage)(nn::settings::ISystemSettingsServer*);
    /* 0x208 */ nn::Result (*SetPrimaryAlbumStorage)(nn::settings::ISystemSettingsServer*);
    /* 0x210 */ nn::Result (*GetUsb30EnableFlag)(nn::settings::ISystemSettingsServer*);
    /* 0x218 */ nn::Result (*SetUsb30EnableFlag)(nn::settings::ISystemSettingsServer*);
    /* 0x220 */ nn::Result (*GetBatteryLot)(nn::settings::ISystemSettingsServer*);
    /* 0x228 */ nn::Result (*GetSerialNumber)(nn::settings::ISystemSettingsServer*);
    /* 0x230 */ nn::Result (*GetNfcEnableFlag)(nn::settings::ISystemSettingsServer*);
    /* 0x238 */ nn::Result (*SetNfcEnableFlag)(nn::settings::ISystemSettingsServer*);
    /* 0x240 */ nn::Result (*GetSleepSettings)(nn::settings::ISystemSettingsServer*);
    /* 0x248 */ nn::Result (*SetSleepSettings)(nn::settings::ISystemSettingsServer*);
    /* 0x250 */ nn::Result (*GetWirelessLanEnableFlag)(nn::settings::ISystemSettingsServer*);
    /* 0x258 */ nn::Result (*SetWirelessLanEnableFlag)(nn::settings::ISystemSettingsServer*);
    /* 0x260 */ nn::Result (*GetInitialLaunchSettings)(nn::settings::ISystemSettingsServer*);
    /* 0x268 */ nn::Result (*SetInitialLaunchSettings)(nn::settings::ISystemSettingsServer*);
    /* 0x270 */ nn::Result (*GetDeviceNickName)(nn::settings::ISystemSettingsServer*);
    /* 0x278 */ nn::Result (*SetDeviceNickName)(nn::settings::ISystemSettingsServer*);
    /* 0x280 */ nn::Result (*GetProductModel)(nn::settings::ISystemSettingsServer*);
    /* 0x288 */ nn::Result (*GetLdnChannel)(nn::settings::ISystemSettingsServer*);
    /* 0x290 */ nn::Result (*SetLdnChannel)(nn::settings::ISystemSettingsServer*);
    /* 0x298 */ nn::Result (*AcquireTelemetryDirtyFlagEventHandle)(nn::settings::ISystemSettingsServer*);
    /* 0x2A0 */ nn::Result (*GetTelemetryDirtyFlags)(nn::settings::ISystemSettingsServer*);
    /* 0x2A8 */ nn::Result (*GetPtmBatteryLot)(nn::settings::ISystemSettingsServer*);
    /* 0x2B0 */ nn::Result (*SetPtmBatteryLot)(nn::settings::ISystemSettingsServer*);
    /* 0x2B8 */ nn::Result (*GetPtmFuelGaugeParameter)(nn::settings::ISystemSettingsServer*);
    /* 0x2C0 */ nn::Result (*SetPtmFuelGaugeParameter)(nn::settings::ISystemSettingsServer*);
    /* 0x2C8 */ nn::Result (*GetBluetoothEnableFlag)(nn::settings::ISystemSettingsServer*);
    /* 0x2D0 */ nn::Result (*SetBluetoothEnableFlag)(nn::settings::ISystemSettingsServer*);
    /* 0x2D8 */ nn::Result (*GetMiiAuthorId)(nn::settings::ISystemSettingsServer*);
    /* 0x2E0 */ nn::Result (*SetShutdownRtcValue)(nn::settings::ISystemSettingsServer*);
    /* 0x2E8 */ nn::Result (*GetShutdownRtcValue)(nn::settings::ISystemSettingsServer*);
    /* 0x2F0 */ nn::Result (*AcquireFatalDirtyFlagEventHandle)(nn::settings::ISystemSettingsServer*);
    /* 0x2F8 */ nn::Result (*GetFatalDirtyFlags)(nn::settings::ISystemSettingsServer*);
    /* 0x300 */ nn::Result (*GetAutoUpdateEnableFlag)(nn::settings::ISystemSettingsServer*);
    /* 0x308 */ nn::Result (*SetAutoUpdateEnableFlag)(nn::settings::ISystemSettingsServer*);
    /* 0x310 */ nn::Result (*GetNxControllerSettings)(nn::settings::ISystemSettingsServer*);
    /* 0x318 */ nn::Result (*SetNxControllerSettings)(nn::settings::ISystemSettingsServer*);
    /* 0x320 */ nn::Result (*GetBatteryPercentageFlag)(nn::settings::ISystemSettingsServer*);
    /* 0x328 */ nn::Result (*SetBatteryPercentageFlag)(nn::settings::ISystemSettingsServer*);
    /* 0x330 */ nn::Result (*GetExternalRtcResetFlag)(nn::settings::ISystemSettingsServer*);
    /* 0x338 */ nn::Result (*SetExternalRtcResetFlag)(nn::settings::ISystemSettingsServer*);
    /* 0x340 */ nn::Result (*GetUsbFullKeyEnableFlag)(nn::settings::ISystemSettingsServer*);
    /* 0x348 */ nn::Result (*SetUsbFullKeyEnableFlag)(nn::settings::ISystemSettingsServer*);
    /* 0x350 */ nn::Result (*SetExternalSteadyClockInternalOffset)(nn::settings::ISystemSettingsServer*);
    /* 0x358 */ nn::Result (*GetExternalSteadyClockInternalOffset)(nn::settings::ISystemSettingsServer*);
    /* 0x360 */ nn::Result (*GetBacklightSettingsEx)(nn::settings::ISystemSettingsServer*);
    /* 0x368 */ nn::Result (*SetBacklightSettingsEx)(nn::settings::ISystemSettingsServer*);
    /* 0x370 */ nn::Result (*GetHeadphoneVolumeWarningCount)(nn::settings::ISystemSettingsServer*);
    /* 0x378 */ nn::Result (*SetHeadphoneVolumeWarningCount)(nn::settings::ISystemSettingsServer*);
    /* 0x380 */ nn::Result (*GetBluetoothAfhEnableFlag)(nn::settings::ISystemSettingsServer*);
    /* 0x388 */ nn::Result (*SetBluetoothAfhEnableFlag)(nn::settings::ISystemSettingsServer*);
    /* 0x390 */ nn::Result (*GetBluetoothBoostEnableFlag)(nn::settings::ISystemSettingsServer*);
    /* 0x398 */ nn::Result (*SetBluetoothBoostEnableFlag)(nn::settings::ISystemSettingsServer*);
    /* 0x3A0 */ nn::Result (*GetInRepairProcessEnableFlag)(nn::settings::ISystemSettingsServer*);
    /* 0x3A8 */ nn::Result (*SetInRepairProcessEnableFlag)(nn::settings::ISystemSettingsServer*);
    /* 0x3B0 */ nn::Result (*GetHeadphoneVolumeUpdateFlag)(nn::settings::ISystemSettingsServer*);
    /* 0x3B8 */ nn::Result (*SetHeadphoneVolumeUpdateFlag)(nn::settings::ISystemSettingsServer*);
    /* 0x3C0 */ nn::Result (*NeedsToUpdateHeadphoneVolume)(nn::settings::ISystemSettingsServer*);
    /* 0x3C8 */ nn::Result (*GetPushNotificationActivityModeOnSleep)(nn::settings::ISystemSettingsServer*);
    /* 0x3D0 */ nn::Result (*SetPushNotificationActivityModeOnSleep)(nn::settings::ISystemSettingsServer*);
    /* 0x3D8 */ nn::Result (*GetServiceDiscoveryControlSettings)(nn::settings::ISystemSettingsServer*);
    /* 0x3E0 */ nn::Result (*SetServiceDiscoveryControlSettings)(nn::settings::ISystemSettingsServer*);
    /* 0x3E8 */ nn::Result (*GetErrorReportSharePermission)(nn::settings::ISystemSettingsServer*);
    /* 0x3F0 */ nn::Result (*SetErrorReportSharePermission)(nn::settings::ISystemSettingsServer*);
    /* 0x3F8 */ nn::Result (*GetAppletLaunchFlags)(nn::settings::ISystemSettingsServer*);
    /* 0x400 */ nn::Result (*SetAppletLaunchFlags)(nn::settings::ISystemSettingsServer*);
    /* 0x408 */ nn::Result (*GetConsoleSixAxisSensorAccelerationBias)(nn::settings::ISystemSettingsServer*);
    /* 0x410 */ nn::Result (*SetConsoleSixAxisSensorAccelerationBias)(nn::settings::ISystemSettingsServer*);
    /* 0x418 */ nn::Result (*GetConsoleSixAxisSensorAngularVelocityBias)(nn::settings::ISystemSettingsServer*);
    /* 0x420 */ nn::Result (*SetConsoleSixAxisSensorAngularVelocityBias)(nn::settings::ISystemSettingsServer*);
    /* 0x428 */ nn::Result (*GetConsoleSixAxisSensorAccelerationGain)(nn::settings::ISystemSettingsServer*);
    /* 0x430 */ nn::Result (*SetConsoleSixAxisSensorAccelerationGain)(nn::settings::ISystemSettingsServer*);
    /* 0x438 */ nn::Result (*GetConsoleSixAxisSensorAngularVelocityGain)(nn::settings::ISystemSettingsServer*);
    /* 0x440 */ nn::Result (*SetConsoleSixAxisSensorAngularVelocityGain)(nn::settings::ISystemSettingsServer*);
    /* 0x448 */ nn::Result (*GetKeyboardLayout)(nn::settings::ISystemSettingsServer*);
    /* 0x450 */ nn::Result (*SetKeyboardLayout)(nn::settings::ISystemSettingsServer*);
    /* 0x458 */ nn::Result (*GetWebInspectorFlag)(nn::settings::ISystemSettingsServer*);
    /* 0x460 */ nn::Result (*GetAllowedSslHosts)(nn::settings::ISystemSettingsServer*);
    /* 0x468 */ nn::Result (*GetHostFsMountPoint)(nn::settings::ISystemSettingsServer*);
    /* 0x470 */ nn::Result (*GetRequiresRunRepairTimeReviser)(nn::settings::ISystemSettingsServer*);
    /* 0x478 */ nn::Result (*SetRequiresRunRepairTimeReviser)(nn::settings::ISystemSettingsServer*);
    /* 0x480 */ nn::Result (*SetBlePairingSettings)(nn::settings::ISystemSettingsServer*);
    /* 0x488 */ nn::Result (*GetBlePairingSettings)(nn::settings::ISystemSettingsServer*);
    /* 0x490 */ nn::Result (*GetConsoleSixAxisSensorAngularVelocityTimeBias)(nn::settings::ISystemSettingsServer*);
    /* 0x498 */ nn::Result (*SetConsoleSixAxisSensorAngularVelocityTimeBias)(nn::settings::ISystemSettingsServer*);
    /* 0x4A0 */ nn::Result (*GetConsoleSixAxisSensorAngularAcceleration)(nn::settings::ISystemSettingsServer*);
    /* 0x4A8 */ nn::Result (*SetConsoleSixAxisSensorAngularAcceleration)(nn::settings::ISystemSettingsServer*);
    /* 0x4B0 */ nn::Result (*GetRebootlessSystemUpdateVersion)(nn::settings::ISystemSettingsServer*);
    /* 0x4B8 */ nn::Result (*GetDeviceTimeZoneLocationUpdatedTime)(nn::settings::ISystemSettingsServer*);
    /* 0x4C0 */ nn::Result (*SetDeviceTimeZoneLocationUpdatedTime)(nn::settings::ISystemSettingsServer*);
    /* 0x4C8 */ nn::Result (*GetUserSystemClockAutomaticCorrectionUpdatedTime)(nn::settings::ISystemSettingsServer*);
    /* 0x4D0 */ nn::Result (*SetUserSystemClockAutomaticCorrectionUpdatedTime)(nn::settings::ISystemSettingsServer*);
    /* 0x4D8 */ nn::Result (*GetAccountOnlineStorageSettings)(nn::settings::ISystemSettingsServer*);
    /* 0x4E0 */ nn::Result (*SetAccountOnlineStorageSettings)(nn::settings::ISystemSettingsServer*);
    /* 0x4E8 */ nn::Result (*GetPctlReadyFlag)(nn::settings::ISystemSettingsServer*);
    /* 0x4F0 */ nn::Result (*SetPctlReadyFlag)(nn::settings::ISystemSettingsServer*);
    /* 0x4F8 */ nn::Result (*GetAnalogStickUserCalibrationL)(nn::settings::ISystemSettingsServer*);
    /* 0x500 */ nn::Result (*SetAnalogStickUserCalibrationL)(nn::settings::ISystemSettingsServer*);
    /* 0x508 */ nn::Result (*GetAnalogStickUserCalibrationR)(nn::settings::ISystemSettingsServer*);
    /* 0x510 */ nn::Result (*SetAnalogStickUserCalibrationR)(nn::settings::ISystemSettingsServer*);
    /* 0x518 */ nn::Result (*GetPtmBatteryVersion)(nn::settings::ISystemSettingsServer*);
    /* 0x520 */ nn::Result (*SetPtmBatteryVersion)(nn::settings::ISystemSettingsServer*);
    /* 0x528 */ nn::Result (*GetUsb30HostEnableFlag)(nn::settings::ISystemSettingsServer*);
    /* 0x530 */ nn::Result (*SetUsb30HostEnableFlag)(nn::settings::ISystemSettingsServer*);
    /* 0x538 */ nn::Result (*GetUsb30DeviceEnableFlag)(nn::settings::ISystemSettingsServer*);
    /* 0x540 */ nn::Result (*SetUsb30DeviceEnableFlag)(nn::settings::ISystemSettingsServer*);
    /* 0x548 */ nn::Result (*GetThemeId)(nn::settings::ISystemSettingsServer*);
    /* 0x550 */ nn::Result (*SetThemeId)(nn::settings::ISystemSettingsServer*);
    /* 0x558 */ nn::Result (*GetChineseTraditionalInputMethod)(nn::settings::ISystemSettingsServer*);
    /* 0x560 */ nn::Result (*SetChineseTraditionalInputMethod)(nn::settings::ISystemSettingsServer*);
    /* 0x568 */ nn::Result (*GetPtmCycleCountReliability)(nn::settings::ISystemSettingsServer*);
    /* 0x570 */ nn::Result (*SetPtmCycleCountReliability)(nn::settings::ISystemSettingsServer*);
    /* 0x578 */ nn::Result (*GetHomeMenuScheme)(nn::settings::ISystemSettingsServer*);
    /* 0x580 */ nn::Result (*GetThemeSettings)(nn::settings::ISystemSettingsServer*);
    /* 0x588 */ nn::Result (*SetThemeSettings)(nn::settings::ISystemSettingsServer*);
    /* 0x590 */ nn::Result (*GetThemeKey)(nn::settings::ISystemSettingsServer*);
    /* 0x598 */ nn::Result (*SetThemeKey)(nn::settings::ISystemSettingsServer*);
    /* 0x5A0 */ nn::Result (*GetZoomFlag)(nn::settings::ISystemSettingsServer*);
    /* 0x5A8 */ nn::Result (*SetZoomFlag)(nn::settings::ISystemSettingsServer*);
    /* 0x5B0 */ nn::Result (*GetT)(nn::settings::ISystemSettingsServer*);
    /* 0x5B8 */ nn::Result (*SetT)(nn::settings::ISystemSettingsServer*);
    /* 0x5C0 */ nn::Result (*GetPlatformRegion)(nn::settings::ISystemSettingsServer*);
    /* 0x5C8 */ nn::Result (*SetPlatformRegion)(nn::settings::ISystemSettingsServer*);
    /* 0x5D0 */ nn::Result (*GetHomeMenuSchemeModel)(nn::settings::ISystemSettingsServer*);
    /* 0x5D8 */ nn::Result (*GetMemoryUsageRateFlag)(nn::settings::ISystemSettingsServer*);
    /* 0x5E0 */ nn::Result (*GetTouchScreenMode)(nn::settings::ISystemSettingsServer*);
    /* 0x5E8 */ nn::Result (*SetTouchScreenMode)(nn::settings::ISystemSettingsServer*);
    /* 0x5F0 */ nn::Result (*GetButtonConfigSettingsFull)(nn::settings::ISystemSettingsServer*);
    /* 0x5F8 */ nn::Result (*SetButtonConfigSettingsFull)(nn::settings::ISystemSettingsServer*);
    /* 0x600 */ nn::Result (*GetButtonConfigSettingsEmbedded)(nn::settings::ISystemSettingsServer*);
    /* 0x608 */ nn::Result (*SetButtonConfigSettingsEmbedded)(nn::settings::ISystemSettingsServer*);
    /* 0x610 */ nn::Result (*GetButtonConfigSettingsLeft)(nn::settings::ISystemSettingsServer*);
    /* 0x618 */ nn::Result (*SetButtonConfigSettingsLeft)(nn::settings::ISystemSettingsServer*);
    /* 0x620 */ nn::Result (*GetButtonConfigSettingsRight)(nn::settings::ISystemSettingsServer*);
    /* 0x628 */ nn::Result (*SetButtonConfigSettingsRight)(nn::settings::ISystemSettingsServer*);
    /* 0x630 */ nn::Result (*GetButtonConfigRegisteredSettingsEmbedded)(nn::settings::ISystemSettingsServer*);
    /* 0x638 */ nn::Result (*SetButtonConfigRegisteredSettingsEmbedded)(nn::settings::ISystemSettingsServer*);
    /* 0x640 */ nn::Result (*GetButtonConfigRegisteredSettings)(nn::settings::ISystemSettingsServer*);
    /* 0x648 */ nn::Result (*SetButtonConfigRegisteredSettings)(nn::settings::ISystemSettingsServer*);
    /* 0x650 */ nn::Result (*GetFieldTestingFlag)(nn::settings::ISystemSettingsServer*);
    /* 0x658 */ nn::Result (*SetFieldTestingFlag)(nn::settings::ISystemSettingsServer*);
    /* 0x660 */ nn::Result (*GetPanelCrcMode)(nn::settings::ISystemSettingsServer*);
    /* 0x668 */ nn::Result (*SetPanelCrcMode)(nn::settings::ISystemSettingsServer*);
    /* 0x670 */ nn::Result (*GetNxControllerSettingsEx)(nn::settings::ISystemSettingsServer*);
    /* 0x678 */ nn::Result (*SetNxControllerSettingsEx)(nn::settings::ISystemSettingsServer*);
    /* 0x680 */ nn::Result (*GetHearingProtectionSafeguardFlag)(nn::settings::ISystemSettingsServer*);
    /* 0x688 */ nn::Result (*SetHearingProtectionSafeguardFlag)(nn::settings::ISystemSettingsServer*);
    /* 0x690 */ nn::Result (*GetHearingProtectionSafeguardRemainingTime)(nn::settings::ISystemSettingsServer*);
    /* 0x698 */ nn::Result (*SetHearingProtectionSafeguardRemainingTime)(nn::settings::ISystemSettingsServer*); /* 0x000 */ 
};

struct nn::settings::ISystemSettingsServer::vtable_16 {
    /* 0x00 */ void (*AddReference)(nn::settings::ISystemSettingsServer*);
    /* 0x08 */ void (*Release)(nn::settings::ISystemSettingsServer*);
    /* 0x10 */ void (*GetProxyInfo)(nn::settings::ISystemSettingsServer*);
    /* 0x18 */ void (*GetInterfaceTypeInfo)(nn::settings::ISystemSettingsServer*);

    nn::Result (*SetLanguageCode)(nn::settings::ISystemSettingsServer*);
    nn::Result (*SetNetworkSettings)(nn::settings::ISystemSettingsServer*);
    nn::Result (*GetNetworkSettings)();
    nn::Result (*GetFirmwareVersion)();
    nn::Result (*GetFirmwareVersion2)();
    nn::Result (*GetFirmwareVersionDigest)();
    nn::Result (*GetLockScreenFlag)();
    nn::Result (*SetLockScreenFlag)();
    nn::Result (*GetBacklightSettings)();
    nn::Result (*SetBacklightSettings)();
    nn::Result (*SetBluetoothDevicesSettings)();
    nn::Result (*GetBluetoothDevicesSettings)();
    nn::Result (*GetExternalSteadyClockSourceId)();
    nn::Result (*SetExternalSteadyClockSourceId)();
    nn::Result (*GetUserSystemClockContext)();
    nn::Result (*SetUserSystemClockContext)();
    nn::Result (*GetAccountSettings)();
    nn::Result (*SetAccountSettings)();
    nn::Result (*GetAudioVolume)();
    nn::Result (*SetAudioVolume)();
    nn::Result (*GetEulaVersions)();
    nn::Result (*SetEulaVersions)();
    nn::Result (*GetColorSetId)();
    nn::Result (*SetColorSetId)();
    nn::Result (*GetConsoleInformationUploadFlag)();
    nn::Result (*SetConsoleInformationUploadFlag)();
    nn::Result (*GetAutomaticApplicationDownloadFlag)();
    nn::Result (*SetAutomaticApplicationDownloadFlag)();
    nn::Result (*GetNotificationSettings)();
    nn::Result (*SetNotificationSettings)();
    nn::Result (*GetAccountNotificationSettings)();
    nn::Result (*SetAccountNotificationSettings)();
    nn::Result (*GetVibrationMasterVolume)();
    nn::Result (*SetVibrationMasterVolume)();
    nn::Result (*GetSettingsItemValueSize)();
    nn::Result (*GetSettingsItemValue)();
    nn::Result (*GetTvSettings)();
    nn::Result (*SetTvSettings)();
    nn::Result (*GetEdid)();
    nn::Result (*SetEdid)();
    nn::Result (*GetAudioOutputMode)();
    nn::Result (*SetAudioOutputMode)();
    nn::Result (*IsForceMuteOnHeadphoneRemoved)();
    nn::Result (*SetForceMuteOnHeadphoneRemoved)();
    nn::Result (*GetQuestFlag)();
    nn::Result (*SetQuestFlag)();
    nn::Result (*GetDataDeletionSettings)();
    nn::Result (*SetDataDeletionSettings)();
    nn::Result (*GetInitialSystemAppletProgramId)();
    nn::Result (*GetOverlayDispProgramId)();
    nn::Result (*GetDeviceTimeZoneLocationName)();
    nn::Result (*SetDeviceTimeZoneLocationName)();
    nn::Result (*GetWirelessCertificationFileSize)();
    nn::Result (*GetWirelessCertificationFile)();
    nn::Result (*SetRegionCode)();
    nn::Result (*GetNetworkSystemClockContext)();
    nn::Result (*SetNetworkSystemClockContext)();
    nn::Result (*IsUserSystemClockAutomaticCorrectionEnabled)();
    nn::Result (*SetUserSystemClockAutomaticCorrectionEnabled)();
    nn::Result (*GetDebugModeFlag)();
    nn::Result (*GetPrimaryAlbumStorage)();
    nn::Result (*SetPrimaryAlbumStorage)();
    nn::Result (*GetUsb30EnableFlag)();
    nn::Result (*SetUsb30EnableFlag)();
    nn::Result (*GetBatteryLot)();
    nn::Result (*GetSerialNumber)();
    nn::Result (*GetNfcEnableFlag)();
    nn::Result (*SetNfcEnableFlag)();
    nn::Result (*GetSleepSettings)();
    nn::Result (*SetSleepSettings)();
    nn::Result (*GetWirelessLanEnableFlag)();
    nn::Result (*SetWirelessLanEnableFlag)();
    nn::Result (*GetInitialLaunchSettings)();
    nn::Result (*SetInitialLaunchSettings)();
    nn::Result (*GetDeviceNickName)();
    nn::Result (*SetDeviceNickName)();
    nn::Result (*GetProductModel)();
    nn::Result (*GetLdnChannel)();
    nn::Result (*SetLdnChannel)();
    nn::Result (*AcquireTelemetryDirtyFlagEventHandle)();
    nn::Result (*GetTelemetryDirtyFlags)();
    nn::Result (*GetPtmBatteryLot)();
    nn::Result (*SetPtmBatteryLot)();
    nn::Result (*GetPtmFuelGaugeParameter)();
    nn::Result (*SetPtmFuelGaugeParameter)();
    nn::Result (*GetBluetoothEnableFlag)();
    nn::Result (*SetBluetoothEnableFlag)();
    nn::Result (*GetMiiAuthorId)();
    nn::Result (*SetShutdownRtcValue)();
    nn::Result (*GetShutdownRtcValue)();
    nn::Result (*AcquireFatalDirtyFlagEventHandle)();
    nn::Result (*GetFatalDirtyFlags)();
    nn::Result (*GetAutoUpdateEnableFlag)();
    nn::Result (*SetAutoUpdateEnableFlag)();
    nn::Result (*GetNxControllerSettings)();
    nn::Result (*SetNxControllerSettings)();
    nn::Result (*GetBatteryPercentageFlag)();
    nn::Result (*SetBatteryPercentageFlag)();
    nn::Result (*GetExternalRtcResetFlag)();
    nn::Result (*SetExternalRtcResetFlag)();
    nn::Result (*GetUsbFullKeyEnableFlag)();
    nn::Result (*SetUsbFullKeyEnableFlag)();
    nn::Result (*SetExternalSteadyClockInternalOffset)();
    nn::Result (*GetExternalSteadyClockInternalOffset)();
    nn::Result (*GetBacklightSettingsEx)();
    nn::Result (*SetBacklightSettingsEx)();
    nn::Result (*GetHeadphoneVolumeWarningCount)();
    nn::Result (*SetHeadphoneVolumeWarningCount)();
    nn::Result (*GetBluetoothAfhEnableFlag)();
    nn::Result (*SetBluetoothAfhEnableFlag)();
    nn::Result (*GetBluetoothBoostEnableFlag)();
    nn::Result (*SetBluetoothBoostEnableFlag)();
    nn::Result (*GetInRepairProcessEnableFlag)();
    nn::Result (*SetInRepairProcessEnableFlag)();
    nn::Result (*GetHeadphoneVolumeUpdateFlag)();
    nn::Result (*SetHeadphoneVolumeUpdateFlag)();
    nn::Result (*GetPushNotificationActivityModeOnSleep)();
    nn::Result (*SetPushNotificationActivityModeOnSleep)();
    nn::Result (*GetServiceDiscoveryControlSettings)();
    nn::Result (*SetServiceDiscoveryControlSettings)();
    nn::Result (*GetErrorReportSharePermission)();
    nn::Result (*SetErrorReportSharePermission)();
    nn::Result (*GetAppletLaunchFlags)();
    nn::Result (*SetAppletLaunchFlags)();
    nn::Result (*GetConsoleSixAxisSensorAccelerationBias)();
    nn::Result (*SetConsoleSixAxisSensorAccelerationBias)();
    nn::Result (*GetConsoleSixAxisSensorAngularVelocityBias)();
    nn::Result (*SetConsoleSixAxisSensorAngularVelocityBias)();
    nn::Result (*GetConsoleSixAxisSensorAccelerationGain)();
    nn::Result (*SetConsoleSixAxisSensorAccelerationGain)();
    nn::Result (*GetConsoleSixAxisSensorAngularVelocityGain)();
    nn::Result (*SetConsoleSixAxisSensorAngularVelocityGain)();
    nn::Result (*GetKeyboardLayout)();
    nn::Result (*SetKeyboardLayout)();
    nn::Result (*GetWebInspectorFlag)();
    nn::Result (*GetAllowedSslHosts)();
    nn::Result (*GetHostFsMountPoint)();
    nn::Result (*GetRequiresRunRepairTimeReviser)();
    nn::Result (*SetRequiresRunRepairTimeReviser)();
    nn::Result (*SetBlePairingSettings)();
    nn::Result (*GetBlePairingSettings)();
    nn::Result (*GetConsoleSixAxisSensorAngularVelocityTimeBias)();
    nn::Result (*SetConsoleSixAxisSensorAngularVelocityTimeBias)();
    nn::Result (*GetConsoleSixAxisSensorAngularAcceleration)();
    nn::Result (*SetConsoleSixAxisSensorAngularAcceleration)();
    nn::Result (*GetRebootlessSystemUpdateVersion)();
    nn::Result (*GetDeviceTimeZoneLocationUpdatedTime)();
    nn::Result (*SetDeviceTimeZoneLocationUpdatedTime)();
    nn::Result (*GetUserSystemClockAutomaticCorrectionUpdatedTime)();
    nn::Result (*SetUserSystemClockAutomaticCorrectionUpdatedTime)();
    nn::Result (*GetAccountOnlineStorageSettings)();
    nn::Result (*SetAccountOnlineStorageSettings)();
    nn::Result (*GetPctlReadyFlag)();
    nn::Result (*SetPctlReadyFlag)();
    nn::Result (*GetAnalogStickUserCalibrationL)();
    nn::Result (*SetAnalogStickUserCalibrationL)();
    nn::Result (*GetAnalogStickUserCalibrationR)();
    nn::Result (*SetAnalogStickUserCalibrationR)();
    nn::Result (*GetPtmBatteryVersion)();
    nn::Result (*SetPtmBatteryVersion)();
    nn::Result (*GetUsb30HostEnableFlag)();
    nn::Result (*SetUsb30HostEnableFlag)();
    nn::Result (*GetUsb30DeviceEnableFlag)();
    nn::Result (*SetUsb30DeviceEnableFlag)();
    nn::Result (*GetThemeId)();
    nn::Result (*SetThemeId)();
    nn::Result (*GetChineseTraditionalInputMethod)();
    nn::Result (*SetChineseTraditionalInputMethod)();
    nn::Result (*GetPtmCycleCountReliability)();
    nn::Result (*SetPtmCycleCountReliability)();
    nn::Result (*GetHomeMenuScheme)();
    nn::Result (*GetThemeSettings)();
    nn::Result (*SetThemeSettings)();
    nn::Result (*GetThemeKey)();
    nn::Result (*SetThemeKey)();
    nn::Result (*GetZoomFlag)();
    nn::Result (*SetZoomFlag)();
    nn::Result (*GetT)();
    nn::Result (*SetT)();
    nn::Result (*GetPlatformRegion)();
    nn::Result (*SetPlatformRegion)();
    nn::Result (*GetHomeMenuSchemeModel)();
    nn::Result (*GetMemoryUsageRateFlag)();
    nn::Result (*GetTouchScreenMode)();
    nn::Result (*SetTouchScreenMode)();
    nn::Result (*GetButtonConfigSettingsFull)();
    nn::Result (*SetButtonConfigSettingsFull)();
    nn::Result (*GetButtonConfigSettingsEmbedded)();
    nn::Result (*SetButtonConfigSettingsEmbedded)();
    nn::Result (*GetButtonConfigSettingsLeft)();
    nn::Result (*SetButtonConfigSettingsLeft)();
    nn::Result (*GetButtonConfigSettingsRight)();
    nn::Result (*SetButtonConfigSettingsRight)();
    nn::Result (*GetButtonConfigRegisteredSettingsEmbedded)();
    nn::Result (*SetButtonConfigRegisteredSettingsEmbedded)();
    nn::Result (*GetButtonConfigRegisteredSettings)();
    nn::Result (*SetButtonConfigRegisteredSettings)();
    nn::Result (*GetFieldTestingFlag)();
    nn::Result (*SetFieldTestingFlag)();
    nn::Result (*GetPanelCrcMode)();
    nn::Result (*SetPanelCrcMode)();
    nn::Result (*GetNxControllerSettingsEx)();
    nn::Result (*SetNxControllerSettingsEx)();
    nn::Result (*GetHearingProtectionSafeguardFlag)();
    nn::Result (*SetHearingProtectionSafeguardFlag)();
    nn::Result (*GetHearingProtectionSafeguardRemainingTime)();
    nn::Result (*SetHearingProtectionSafeguardRemainingTime)(); 
};

struct nn::gpio::IManager {
    struct nn::gpio::IManager::vtable* __vftable;
};

struct nn::gpio::IManager::vtable {
    /* 0x00 */ void (*AddReference)(nn::gpio::IManager*);
    /* 0x08 */ void (*Release)(nn::gpio::IManager*);
    /* 0x10 */ void (*GetProxyInfo)(nn::gpio::IManager*);
    /* 0x18 */ void (*GetInterfaceTypeInfo)(nn::gpio::IManager*);

    /* 0x020 */ nn::Result (*OpenSessionForDevDeprecated)(nn::gpio::IManager*);
    /* 0x028 */ nn::Result (*OpenSessionDeprecated )(nn::gpio::IManager*);
    /* 0x030 */ nn::Result (*OpenSessionForTestDeprecated)(nn::gpio::IManager*);
    /* 0x038 */ nn::Result (*IsWakeEventActiveDeprecated)(nn::gpio::IManager*);
    /* 0x040 */ nn::Result (*GetWakeEventActiveFlagSetDeprecated)(nn::gpio::IManager*);
    /* 0x048 */ nn::Result (*SetWakeEventActiveFlagSetForDebugDeprecated)(nn::gpio::IManager*);
    /* 0x050 */ nn::Result (*SetWakePinDebugMode)(nn::gpio::IManager*);
    /* 0x058 */ nn::Result (*OpenSession)(nn::gpio::IManager*);
    /* 0x060 */ nn::Result (*IsWakeEventActive)(nn::gpio::IManager*);
    /* 0x068 */ nn::Result (*SetWakeEventActiveFlagSetForDebug)(nn::gpio::IManager*);
    /* 0x070 */ nn::Result (*DumpStateForDebug)(nn::gpio::IManager*);
};

struct nn::hid::IHidSystemServer {
    struct nn::hid::IHidSystemServer* __vftable;
};

struct nn::hid::IHidSystemServer::vtable {
    /* 0x00 */ void (*AddReference)(nn::hid::IHidSystemServer*);
    /* 0x08 */ void (*Release)(nn::hid::IHidSystemServer*);
    /* 0x10 */ void (*GetProxyInfo)(nn::hid::IHidSystemServer*);
    /* 0x18 */ void (*GetInterfaceTypeInfo)(nn::hid::IHidSystemServer*);

    /* 0x020 */ nn::Result (*SendKeyboardLockKeyEvent)(nn::hid::IHidSystemServer*);
    ///* 0x028 */ nn::Result (*SetSystemKeyboardState)(nn::hid::IHidSystemServer*);
    ///* 0x030 */ nn::Result (*UnsetSystemKeyboardState)(nn::hid::IHidSystemServer*);
    /* 0x038 */ nn::Result (*AcquireHomeButtonEventHandle)(nn::hid::IHidSystemServer*);
    /* 0x040 */ nn::Result (*ActivateHomeButton)(nn::hid::IHidSystemServer*);
    /* 0x048 */ nn::Result (*AcquireSleepButtonEventHandle)(nn::hid::IHidSystemServer*);
    /* 0x050 */ nn::Result (*ActivateSleepButton)(nn::hid::IHidSystemServer*);
    /* 0x058 */ nn::Result (*AcquireCaptureButtonEventHandle)(nn::hid::IHidSystemServer*);
    /* 0x060 */ nn::Result (*ActivateCaptureButton)(nn::hid::IHidSystemServer*);
    /* 0x068 */ nn::Result (*GetPlatformConfig)(nn::hid::IHidSystemServer*);
    /* 0x070 */ nn::Result (*AcquireNfcDeviceUpdateEventHandle)(nn::hid::IHidSystemServer*);
    /* 0x078 */ nn::Result (*GetNpadsWithNfc)(nn::hid::IHidSystemServer*);
    /* 0x080 */ nn::Result (*AcquireNfcActivateEventHandle)(nn::hid::IHidSystemServer*);
    /* 0x088 */ nn::Result (*ActivateNfc)(nn::hid::IHidSystemServer*);
    /* 0x090 */ nn::Result (*GetXcdHandleForNpadWithNfc)(nn::hid::IHidSystemServer*);
    /* 0x098 */ nn::Result (*IsNfcActivated)(nn::hid::IHidSystemServer*);
    /* 0x0A0 */ nn::Result (*AcquireIrSensorEventHandle)(nn::hid::IHidSystemServer*);
    /* 0x0A8 */ nn::Result (*ActivateIrSensor)(nn::hid::IHidSystemServer*);
    /* 0x0B0 */ nn::Result (*GetIrSensorState)(nn::hid::IHidSystemServer*);
    /* 0x0B8 */ nn::Result (*GetXcdHandleForNpadWithIrSensor)(nn::hid::IHidSystemServer*);
    /* 0x0C0 */ nn::Result (*ActivateNpadSystem)(nn::hid::IHidSystemServer*);
    /* 0x0C8 */ nn::Result (*ApplyNpadSystemCommonPolicy)(nn::hid::IHidSystemServer*);
    /* 0x0D0 */ nn::Result (*EnableAssigningSingleOnSlSrPress)(nn::hid::IHidSystemServer*);
    /* 0x0D8 */ nn::Result (*DisableAssigningSingleOnSlSrPress)(nn::hid::IHidSystemServer*);
    /* 0x0E0 */ nn::Result (*GetLastActiveNpad)(nn::hid::IHidSystemServer*);
    /* 0x0E8 */ nn::Result (*GetNpadSystemExtStyle)(nn::hid::IHidSystemServer*);
    /* 0x0F0 */ nn::Result (*ApplyNpadSystemCommonPolicyFull)(nn::hid::IHidSystemServer*);
    /* 0x0F8 */ nn::Result (*GetNpadFullKeyGripColor)(nn::hid::IHidSystemServer*);
    /* 0x100 */ nn::Result (*GetMaskedSupportedNpadStyleSet)(nn::hid::IHidSystemServer*);
    /* 0x108 */ nn::Result (*SetNpadPlayerLedBlinkingDevice)(nn::hid::IHidSystemServer*);
    /* 0x110 */ nn::Result (*SetSupportedNpadStyleSetAll)(nn::hid::IHidSystemServer*);
    /* 0x118 */ nn::Result (*GetNpadCaptureButtonAssignment)(nn::hid::IHidSystemServer*);
    /* 0x120 */ nn::Result (*GetAppletFooterUiType)(nn::hid::IHidSystemServer*);
    /* 0x128 */ nn::Result (*GetAppletDetailedUiType)(nn::hid::IHidSystemServer*);
    /* 0x130 */ nn::Result (*GetNpadInterfaceType)(nn::hid::IHidSystemServer*);
    /* 0x138 */ nn::Result (*GetNpadLeftRightInterfaceType)(nn::hid::IHidSystemServer*);
    /* 0x140 */ nn::Result (*HasBattery)(nn::hid::IHidSystemServer*);
    /* 0x148 */ nn::Result (*HasLeftRightBattery)(nn::hid::IHidSystemServer*);
    /* 0x150 */ nn::Result (*GetUniquePadsFromNpad)(nn::hid::IHidSystemServer*);
    /* 0x158 */ nn::Result (*SetNpadSystemExtStateEnabled )(nn::hid::IHidSystemServer*);
    /* 0x160 */ nn::Result (*GetLastActiveUniquePad )(nn::hid::IHidSystemServer*);
    /* 0x168 */ nn::Result (*GetUniquePadButtonSet)(nn::hid::IHidSystemServer*);
    /* 0x170 */ nn::Result (*GetUniquePadColor)(nn::hid::IHidSystemServer*);
    /* 0x178 */ nn::Result (*GetUniquePadAppletDetailedUiType)(nn::hid::IHidSystemServer*);
    ///* 0x180 */ nn::Result (*GetAbstractedPadIdDataFromNpad)(nn::hid::IHidSystemServer*);
    ///* 0x188 */ nn::Result (*AttachAbstractedPadToNpad)(nn::hid::IHidSystemServer*);
    ///* 0x190 */ nn::Result (*DetachAbstractedPadAll)(nn::hid::IHidSystemServer*);
    ///* 0x198 */ nn::Result (*CheckAbstractedPadConnection)(nn::hid::IHidSystemServer*);
    /* 0x1A0 */ nn::Result (*SetAppletResourceUserId)(nn::hid::IHidSystemServer*);
    /* 0x1A8 */ nn::Result (*RegisterAppletResourceUserId)(nn::hid::IHidSystemServer*);
    /* 0x1B0 */ nn::Result (*UnregisterAppletResourceUserId)(nn::hid::IHidSystemServer*);
    /* 0x1B8 */ nn::Result (*EnableAppletToGetInput)(nn::hid::IHidSystemServer*);
    /* 0x1C0 */ nn::Result (*SetAruidValidForVibration)(nn::hid::IHidSystemServer*);
    /* 0x1C8 */ nn::Result (*EnableAppletToGetSixAxisSensor)(nn::hid::IHidSystemServer*);
    ///* 0x1D0 */ nn::Result (*EnableAppletToGetPadInput)(nn::hid::IHidSystemServer*);
    ///* 0x1D8 */ nn::Result (*EnableAppletToGetTouchScreen)(nn::hid::IHidSystemServer*);
    /* 0x1E0 */ nn::Result (*SetVibrationMasterVolume)(nn::hid::IHidSystemServer*);
    /* 0x1E8 */ nn::Result (*GetVibrationMasterVolume)(nn::hid::IHidSystemServer*);
    /* 0x1F0 */ nn::Result (*BeginPermitVibrationSession)(nn::hid::IHidSystemServer*);
    /* 0x1F8 */ nn::Result (*EndPermitVibrationSession)(nn::hid::IHidSystemServer*);
    /* 0x200 */ nn::Result (*SendVibrationNotificationPattern)(nn::hid::IHidSystemServer*);
    /* 0x208 */ nn::Result (*EnableHandheldHids)(nn::hid::IHidSystemServer*);
    /* 0x210 */ nn::Result (*DisableHandheldHids)(nn::hid::IHidSystemServer*);
    /* 0x218 */ nn::Result (*SetJoyConRailEnabled)(nn::hid::IHidSystemServer*);
    /* 0x220 */ nn::Result (*IsJoyConRailEnabled)(nn::hid::IHidSystemServer*);
    /* 0x228 */ nn::Result (*IsHandheldHidsEnabled)(nn::hid::IHidSystemServer*);
    /* 0x230 */ nn::Result (*IsJoyConAttachedOnAllRail)(nn::hid::IHidSystemServer*);
    /* 0x238 */ nn::Result (*AcquirePlayReportControllerUsageUpdateEvent)(nn::hid::IHidSystemServer*);
    /* 0x240 */ nn::Result (*GetPlayReportControllerUsages)(nn::hid::IHidSystemServer*);
    /* 0x248 */ nn::Result (*AcquirePlayReportRegisteredDeviceUpdateEvent)(nn::hid::IHidSystemServer*);
    /* 0x250 */ nn::Result (*GetRegisteredDevicesOld)(nn::hid::IHidSystemServer*);
    /* 0x258 */ nn::Result (*AcquireConnectionTriggerTimeoutEvent)(nn::hid::IHidSystemServer*);
    /* 0x260 */ nn::Result (*SendConnectionTrigger)(nn::hid::IHidSystemServer*);
    /* 0x268 */ nn::Result (*AcquireDeviceRegisteredEventForControllerSupport)(nn::hid::IHidSystemServer*);
    /* 0x270 */ nn::Result (*GetAllowedBluetoothLinksCount)(nn::hid::IHidSystemServer*);
    /* 0x278 */ nn::Result (*GetRegisteredDevices)(nn::hid::IHidSystemServer*);
    /* 0x280 */ nn::Result (*GetConnectableRegisteredDevices)(nn::hid::IHidSystemServer*);
    /* 0x288 */ nn::Result (*ActivateUniquePad)(nn::hid::IHidSystemServer*);
    /* 0x290 */ nn::Result (*AcquireUniquePadConnectionEventHandle)(nn::hid::IHidSystemServer*);
    /* 0x298 */ nn::Result (*GetUniquePadIds)(nn::hid::IHidSystemServer*);
    /* 0x2A0 */ nn::Result (*AcquireJoyDetachOnBluetoothOffEventHandle)(nn::hid::IHidSystemServer*);
    /* 0x2A8 */ nn::Result (*ListSixAxisSensorHandles)(nn::hid::IHidSystemServer*);
    /* 0x2B0 */ nn::Result (*IsSixAxisSensorUserCalibrationSupported)(nn::hid::IHidSystemServer*);
    /* 0x2B8 */ nn::Result (*ResetSixAxisSensorCalibrationValues)(nn::hid::IHidSystemServer*);
    /* 0x2C0 */ nn::Result (*StartSixAxisSensorUserCalibration)(nn::hid::IHidSystemServer*);
    /* 0x2C8 */ nn::Result (*CancelSixAxisSensorUserCalibration)(nn::hid::IHidSystemServer*);
    /* 0x2D0 */ nn::Result (*GetUniquePadBluetoothAddress)(nn::hid::IHidSystemServer*);
    /* 0x2D8 */ nn::Result (*DisconnectUniquePad)(nn::hid::IHidSystemServer*);
    /* 0x2E0 */ nn::Result (*GetUniquePadType)(nn::hid::IHidSystemServer*);
    /* 0x2E8 */ nn::Result (*GetUniquePadInterface)(nn::hid::IHidSystemServer*);
    /* 0x2F0 */ nn::Result (*GetUniquePadSerialNumber)(nn::hid::IHidSystemServer*);
    /* 0x2F8 */ nn::Result (*GetUniquePadControllerNumber)(nn::hid::IHidSystemServer*);
    /* 0x300 */ nn::Result (*GetSixAxisSensorUserCalibrationStage)(nn::hid::IHidSystemServer*);
    /* 0x308 */ nn::Result (*GetConsoleUniqueSixAxisSensorHandle)(nn::hid::IHidSystemServer*);
    /* 0x310 */ nn::Result (*StartAnalogStickManualCalibration)(nn::hid::IHidSystemServer*);
    /* 0x318 */ nn::Result (*RetryCurrentAnalogStickManualCalibrationStage)(nn::hid::IHidSystemServer*);
    /* 0x320 */ nn::Result (*CancelAnalogStickManualCalibration)(nn::hid::IHidSystemServer*);
    /* 0x328 */ nn::Result (*ResetAnalogStickManualCalibration)(nn::hid::IHidSystemServer*);
    /* 0x330 */ nn::Result (*GetAnalogStickState)(nn::hid::IHidSystemServer*);
    /* 0x338 */ nn::Result (*GetAnalogStickManualCalibrationStage)(nn::hid::IHidSystemServer*);
    /* 0x340 */ nn::Result (*IsAnalogStickButtonPressed)(nn::hid::IHidSystemServer*);
    /* 0x348 */ nn::Result (*IsAnalogStickInReleasePosition)(nn::hid::IHidSystemServer*);
    /* 0x350 */ nn::Result (*IsAnalogStickInCircumference)(nn::hid::IHidSystemServer*);
    /* 0x358 */ nn::Result (*SetNotificationLedPattern)(nn::hid::IHidSystemServer*);
    /* 0x360 */ nn::Result (*SetNotificationLedPatternWithTimeout)(nn::hid::IHidSystemServer*);
    /* 0x368 */ nn::Result (*PrepareHidsForNotificationWake)(nn::hid::IHidSystemServer*);
    /* 0x370 */ nn::Result (*IsUsbFullKeyControllerEnabled)(nn::hid::IHidSystemServer*);
    /* 0x378 */ nn::Result (*EnableUsbFullKeyController)(nn::hid::IHidSystemServer*);
    /* 0x380 */ nn::Result (*IsUsbConnected)(nn::hid::IHidSystemServer*);
    /* 0x388 */ nn::Result (*IsHandheldButtonPressedOnConsoleMode)(nn::hid::IHidSystemServer*);
    ///* 0x390 */ nn::Result (*ActivateInputDetector)(nn::hid::IHidSystemServer*);
    ///* 0x398 */ nn::Result (*NotifyInputDetector)(nn::hid::IHidSystemServer*);
    /* 0x3A0 */ nn::Result (*InitializeFirmwareUpdate)(nn::hid::IHidSystemServer*);
    /* 0x3A8 */ nn::Result (*GetFirmwareVersion)(nn::hid::IHidSystemServer*);
    /* 0x3B0 */ nn::Result (*GetAvailableFirmwareVersion)(nn::hid::IHidSystemServer*);
    /* 0x3B8 */ nn::Result (*IsFirmwareUpdateAvailable)(nn::hid::IHidSystemServer*);
    /* 0x3C0 */ nn::Result (*CheckFirmwareUpdateRequired)(nn::hid::IHidSystemServer*);
    /* 0x3C8 */ nn::Result (*StartFirmwareUpdate)(nn::hid::IHidSystemServer*);
    /* 0x3D0 */ nn::Result (*AbortFirmwareUpdate)(nn::hid::IHidSystemServer*);
    /* 0x3D8 */ nn::Result (*GetFirmwareUpdateState)(nn::hid::IHidSystemServer*);
    /* 0x3E0 */ nn::Result (*ActivateAudioControl)(nn::hid::IHidSystemServer*);
    /* 0x3E8 */ nn::Result (*AcquireAudioControlEventHandle)(nn::hid::IHidSystemServer*);
    /* 0x3F0 */ nn::Result (*GetAudioControlStates)(nn::hid::IHidSystemServer*);
    /* 0x3F8 */ nn::Result (*DeactivateAudioControl)(nn::hid::IHidSystemServer*);
    /* 0x400 */ nn::Result (*IsSixAxisSensorAccurateUserCalibrationSupported)(nn::hid::IHidSystemServer*);
    /* 0x408 */ nn::Result (*StartSixAxisSensorAccurateUserCalibration)(nn::hid::IHidSystemServer*);
    /* 0x410 */ nn::Result (*CancelSixAxisSensorAccurateUserCalibration)(nn::hid::IHidSystemServer*);
    /* 0x418 */ nn::Result (*GetSixAxisSensorAccurateUserCalibrationState)(nn::hid::IHidSystemServer*);
    /* 0x420 */ nn::Result (*GetHidbusSystemServiceObject)(nn::hid::IHidSystemServer*);
    /* 0x428 */ nn::Result (*SetFirmwareHotfixUpdateSkipEnabled)(nn::hid::IHidSystemServer*);
    /* 0x430 */ nn::Result (*InitializeUsbFirmwareUpdate)(nn::hid::IHidSystemServer*);
    /* 0x438 */ nn::Result (*FinalizeUsbFirmwareUpdate)(nn::hid::IHidSystemServer*);
    /* 0x440 */ nn::Result (*CheckUsbFirmwareUpdateRequired)(nn::hid::IHidSystemServer*);
    /* 0x448 */ nn::Result (*StartUsbFirmwareUpdate)(nn::hid::IHidSystemServer*);
    /* 0x450 */ nn::Result (*GetUsbFirmwareUpdateState)(nn::hid::IHidSystemServer*);
    /* 0x458 */ nn::Result (*InitializeUsbFirmwareUpdateWithoutMemory)(nn::hid::IHidSystemServer*);
    /* 0x460 */ nn::Result (*SetTouchScreenMagnification)(nn::hid::IHidSystemServer*);
    /* 0x468 */ nn::Result (*GetTouchScreenFirmwareVersion)(nn::hid::IHidSystemServer*);
    /* 0x470 */ nn::Result (*SetTouchScreenDefaultConfiguration)(nn::hid::IHidSystemServer*);
    /* 0x478 */ nn::Result (*GetTouchScreenDefaultConfiguration)(nn::hid::IHidSystemServer*);
    /* 0x480 */ nn::Result (*IsFirmwareAvailableForNotification)(nn::hid::IHidSystemServer*);
    /* 0x488 */ nn::Result (*SetForceHandheldStyleVibration)(nn::hid::IHidSystemServer*);
    /* 0x490 */ nn::Result (*SendConnectionTriggerWithoutTimeoutEvent)(nn::hid::IHidSystemServer*);
    /* 0x498 */ nn::Result (*CancelConnectionTrigger)(nn::hid::IHidSystemServer*);
    /* 0x4A0 */ nn::Result (*IsButtonConfigSupported)(nn::hid::IHidSystemServer*);
    /* 0x4A8 */ nn::Result (*IsButtonConfigEmbeddedSupported)(nn::hid::IHidSystemServer*);
    /* 0x4B0 */ nn::Result (*DeleteButtonConfig)(nn::hid::IHidSystemServer*);
    /* 0x4B8 */ nn::Result (*DeleteButtonConfigEmbedded)(nn::hid::IHidSystemServer*);
    /* 0x4C0 */ nn::Result (*SetButtonConfigEnabled)(nn::hid::IHidSystemServer*);
    /* 0x4C8 */ nn::Result (*SetButtonConfigEmbeddedEnabled)(nn::hid::IHidSystemServer*);
    /* 0x4D0 */ nn::Result (*IsButtonConfigEnabled)(nn::hid::IHidSystemServer*);
    /* 0x4D8 */ nn::Result (*IsButtonConfigEmbeddedEnabled)(nn::hid::IHidSystemServer*);
    /* 0x4E0 */ nn::Result (*SetButtonConfigEmbedded)(nn::hid::IHidSystemServer*);
    /* 0x4E8 */ nn::Result (*SetButtonConfigFull)(nn::hid::IHidSystemServer*);
    /* 0x4F0 */ nn::Result (*GetButtonConfigLeftDeprecated)(nn::hid::IHidSystemServer*);
    /* 0x4F8 */ nn::Result (*SetButtonConfigRight)(nn::hid::IHidSystemServer*);
    /* 0x500 */ nn::Result (*GetButtonConfigEmbedded)(nn::hid::IHidSystemServer*);
    /* 0x508 */ nn::Result (*GetButtonConfigFull)(nn::hid::IHidSystemServer*);
    /* 0x510 */ nn::Result (*GetButtonConfigLeft)(nn::hid::IHidSystemServer*);
    /* 0x518 */ nn::Result (*GetButtonConfigRight)(nn::hid::IHidSystemServer*);
    /* 0x520 */ nn::Result (*IsCustomButtonConfigSupported)(nn::hid::IHidSystemServer*);
    /* 0x528 */ nn::Result (*IsDefaultButtonConfigEmbedded)(nn::hid::IHidSystemServer*);
    /* 0x530 */ nn::Result (*IsDefaultButtonConfigFull)(nn::hid::IHidSystemServer*);
    /* 0x538 */ nn::Result (*IsDefaultButtonConfigLeft)(nn::hid::IHidSystemServer*);
    /* 0x540 */ nn::Result (*IsDefaultButtonConfigRight)(nn::hid::IHidSystemServer*);
    /* 0x548 */ nn::Result (*IsButtonConfigStorageEmbeddedEmpty)(nn::hid::IHidSystemServer*);
    /* 0x550 */ nn::Result (*IsButtonConfigStorageFullEmpty)(nn::hid::IHidSystemServer*);
    /* 0x558 */ nn::Result (*IsButtonConfigStorageLeftEmpty)(nn::hid::IHidSystemServer*);
    /* 0x560 */ nn::Result (*IsButtonConfigStorageRightEmpty)(nn::hid::IHidSystemServer*);
    /* 0x568 */ nn::Result (*GetButtonConfigStorageEmbeddedDeprecated)(nn::hid::IHidSystemServer*);
    /* 0x570 */ nn::Result (*GetButtonConfigStorageFullDeprecated)(nn::hid::IHidSystemServer*);
    /* 0x578 */ nn::Result (*GetButtonConfigStorageLeftDeprecated)(nn::hid::IHidSystemServer*);
    /* 0x580 */ nn::Result (*GetButtonConfigStorageRightDeprecated)(nn::hid::IHidSystemServer*);
    /* 0x588 */ nn::Result (*SetButtonConfigStorageEmbeddedDeprecated)(nn::hid::IHidSystemServer*);
    /* 0x590 */ nn::Result (*SetButtonConfigStorageFullDeprecated)(nn::hid::IHidSystemServer*);
    /* 0x598 */ nn::Result (*SetButtonConfigStorageLeftDeprecated)(nn::hid::IHidSystemServer*);
    /* 0x5A0 */ nn::Result (*SetButtonConfigStorageRightDeprecated)(nn::hid::IHidSystemServer*);
    /* 0x5A8 */ nn::Result (*DeleteButtonConfigStorageEmbedded)(nn::hid::IHidSystemServer*);
    /* 0x5B0 */ nn::Result (*DeleteButtonConfigStorageFull)(nn::hid::IHidSystemServer*);
    /* 0x5B8 */ nn::Result (*DeleteButtonConfigStorageLeft)(nn::hid::IHidSystemServer*);
    /* 0x5C0 */ nn::Result (*DeleteButtonConfigStorageRight)(nn::hid::IHidSystemServer*);
    /* 0x5C8 */ nn::Result (*IsUsingCustomButtonConfig)(nn::hid::IHidSystemServer*);
    /* 0x5D0 */ nn::Result (*IsAnyCustomButtonConfigEnabled)(nn::hid::IHidSystemServer*);
    /* 0x5D8 */ nn::Result (*SetAllCustomButtonConfigEnabled)(nn::hid::IHidSystemServer*);
    /* 0x5E0 */ nn::Result (*SetDefaultButtonConfig)(nn::hid::IHidSystemServer*);
    /* 0x5E8 */ nn::Result (*SetAllDefaultButtonConfig)(nn::hid::IHidSystemServer*);
    /* 0x5F0 */ nn::Result (*SetHidButtonConfigEmbedded)(nn::hid::IHidSystemServer*);
    /* 0x5F8 */ nn::Result (*SetHidButtonConfigFull)(nn::hid::IHidSystemServer*);
    /* 0x600 */ nn::Result (*SetHidButtonConfigLeft)(nn::hid::IHidSystemServer*);
    /* 0x608 */ nn::Result (*SetHidButtonConfigRight)(nn::hid::IHidSystemServer*);
    /* 0x610 */ nn::Result (*GetHidButtonConfigEmbedded)(nn::hid::IHidSystemServer*);
    /* 0x618 */ nn::Result (*GetHidButtonConfigFull)(nn::hid::IHidSystemServer*);
    /* 0x620 */ nn::Result (*GetHidButtonConfigLeft)(nn::hid::IHidSystemServer*);
    /* 0x628 */ nn::Result (*GetHidButtonConfigRight)(nn::hid::IHidSystemServer*);
    /* 0x630 */ nn::Result (*GetButtonConfigStorageEmbedded)(nn::hid::IHidSystemServer*);
    /* 0x638 */ nn::Result (*GetButtonConfigStorageFull)(nn::hid::IHidSystemServer*);
    /* 0x640 */ nn::Result (*GetButtonConfigStorageLeft)(nn::hid::IHidSystemServer*);
    /* 0x648 */ nn::Result (*GetButtonConfigStorageRight)(nn::hid::IHidSystemServer*);
    /* 0x650 */ nn::Result (*SetButtonConfigStorageEmbedded)(nn::hid::IHidSystemServer*);
    /* 0x658 */ nn::Result (*SetButtonConfigStorageFull)(nn::hid::IHidSystemServer*);
    /* 0x660 */ nn::Result (*SetButtonConfigStorageLeft)(nn::hid::IHidSystemServer*);
    /* 0x668 */ nn::Result (*SetButtonConfigStorageRight)(nn::hid::IHidSystemServer*);
    /* 0x670 */ nn::Result (*SetButtonConfigLeft)(nn::hid::IHidSystemServer*);
};

struct nn::ins::ISenderManager {
    struct nn::ins::ISenderManager* __vftable;
};

struct nn::ins::ISenderManager::vtable {
    /* 0x00 */ void (*AddReference)(nn::ins::ISenderManager*);
    /* 0x08 */ void (*Release)(nn::ins::ISenderManager*);
    /* 0x10 */ void (*GetProxyInfo)(nn::ins::ISenderManager*);
    /* 0x18 */ void (*GetInterfaceTypeInfo)(nn::ins::ISenderManager*);

    /* 0x020 */ nn::Result (*GetNotifyEvent)(nn::ins::ISenderManager*);
};

struct nn::timesrv::detail::service::ITimeServiceManager {
    struct nn::timesrv::detail::service::ITimeServiceManager::vtable* __vftable;
};

struct nn::timesrv::detail::service::ITimeServiceManager::vtable {
    /* 0x00 */ void (*AddReference)(nn::ins::ISenderManager*);
    /* 0x08 */ void (*Release)(nn::ins::ISenderManager*);
    /* 0x10 */ void (*GetProxyInfo)(nn::ins::ISenderManager*);
    /* 0x18 */ void (*GetInterfaceTypeInfo)(nn::ins::ISenderManager*);

    /* 0x000 */ nn::Result (*GetStaticServiceAsUser)(nn::timesrv::detail::service::ITimeServiceManager*);
    /* 0x008 */ nn::Result (*GetStaticServiceAsAdmin)(nn::timesrv::detail::service::ITimeServiceManager*);
    /* 0x010 */ nn::Result (*GetStaticServiceAsRepair)(nn::timesrv::detail::service::ITimeServiceManager*);
    /* 0x018 */ nn::Result (*GetStaticServiceAsServiceManager)(nn::timesrv::detail::service::ITimeServiceManager*);
    /* 0x020 */ nn::Result (*SetupStandardSteadyClockCore)(nn::timesrv::detail::service::ITimeServiceManager*);
    /* 0x028 */ nn::Result (*SetupStandardLocalSystemClockCore)(nn::timesrv::detail::service::ITimeServiceManager*);
    /* 0x030 */ nn::Result (*SetupStandardNetworkSystemClockCore)(nn::timesrv::detail::service::ITimeServiceManager*);
    /* 0x038 */ nn::Result (*SetupStandardUserSystemClockCore)(nn::timesrv::detail::service::ITimeServiceManager*);
    /* 0x040 */ nn::Result (*SetupTimeZoneServiceCore)(nn::timesrv::detail::service::ITimeServiceManager*);
    /* 0x048 */ nn::Result (*SetupEphemeralNetworkSystemClockCore)(nn::timesrv::detail::service::ITimeServiceManager*);
    /* 0x050 */ nn::Result (*GetStandardLocalClockOperationEvent)(nn::timesrv::detail::service::ITimeServiceManager*);
    /* 0x058 */ nn::Result (*GetStandardNetworkClockOperationEventForServiceManager)(nn::timesrv::detail::service::ITimeServiceManager*);
    /* 0x060 */ nn::Result (*GetEphemeralNetworkClockOperationEventForServiceManager)(nn::timesrv::detail::service::ITimeServiceManager*);
    /* 0x068 */ nn::Result (*GetStandardUserSystemClockAutomaticCorrectionUpdatedEvent)(nn::timesrv::detail::service::ITimeServiceManager*);
    /* 0x070 */ nn::Result (*SetStandardSteadyClockBaseTime)(nn::timesrv::detail::service::ITimeServiceManager*, s64);
    /* 0x078 */ nn::Result (*GetClosestAlarmUpdatedEvent)(nn::timesrv::detail::service::ITimeServiceManager*);
    /* 0x080 */ nn::Result (*CheckAndSignalAlarms)(nn::timesrv::detail::service::ITimeServiceManager*);
    /* 0x088 */ nn::Result (*GetClosestAlarmInfo)(nn::timesrv::detail::service::ITimeServiceManager*);
};

struct nn::fssrv::sf::IFileSystemProxy {
    struct nn::fssrv::sf::IFileSystemProxy::vtable* __vftable;
};

struct nn::fssrv::sf::IFileSystemProxy::vtable {
    /* 0x00 */ void (*AddReference)(nn::ins::ISenderManager*);
    /* 0x08 */ void (*Release)(nn::ins::ISenderManager*);
    /* 0x10 */ void (*GetProxyInfo)(nn::ins::ISenderManager*);
    /* 0x18 */ void (*GetInterfaceTypeInfo)(nn::ins::ISenderManager*);

    nn::Result (*FakePad)();

    nn::Result (*OpenFileSystem)();
    nn::Result (*SetCurrentProcess)();
    nn::Result (*OpenDataFileSystemByCurrentProcess)();
    nn::Result (*OpenFileSystemWithPatch)();
    nn::Result (*OpenFileSystemWithIdObsolete)();
    nn::Result (*OpenDataFileSystemByProgramId)();
    nn::Result (*OpenFileSystemWithId)();
    nn::Result (*OpenBisFileSystem)();
    nn::Result (*OpenBisStorage)();
    nn::Result (*InvalidateBisCache)();
    nn::Result (*OpenHostFileSystem)();
    nn::Result (*OpenSdCardFileSystem)();
    nn::Result (*FormatSdCardFileSystem)();
    nn::Result (*DeleteSaveDataFileSystem)();
    nn::Result (*CreateSaveDataFileSystem)();
    nn::Result (*CreateSaveDataFileSystemBySystemSaveDataId)();
    nn::Result (*RegisterSaveDataFileSystemAtomicDeletion)();
    nn::Result (*DeleteSaveDataFileSystemBySaveDataSpaceId)();
    nn::Result (*FormatSdCardDryRun)();
    nn::Result (*IsExFatSupported)();
    nn::Result (*DeleteSaveDataFileSystemBySaveDataAttribute)();
    nn::Result (*OpenGameCardStorage)();
    nn::Result (*OpenGameCardFileSystem)();
    nn::Result (*ExtendSaveDataFileSystem)();
    nn::Result (*DeleteCacheStorage)();
    nn::Result (*GetCacheStorageSize)();
    nn::Result (*CreateSaveDataFileSystemWithHashSalt)();
    nn::Result (*OpenHostFileSystemWithOption)();
    nn::Result (*CreateSaveDataFileSystemWithCreationInfo2)();
    nn::Result (*OpenSaveDataFileSystem)();
    nn::Result (*OpenSaveDataFileSystemBySystemSaveDataId)();
    nn::Result (*OpenReadOnlySaveDataFileSystem)();
    nn::Result (*ReadSaveDataFileSystemExtraDataBySaveDataSpaceId)();
    nn::Result (*ReadSaveDataFileSystemExtraData)();
    nn::Result (*WriteSaveDataFileSystemExtraData)();
    nn::Result (*OpenSaveDataInfoReader)();
    nn::Result (*OpenSaveDataInfoReaderBySaveDataSpaceId)();
    nn::Result (*OpenSaveDataInfoReaderOnlyCacheStorage)();
    nn::Result (*OpenSaveDataInternalStorageFileSystem)();
    nn::Result (*UpdateSaveDataMacForDebug)();
    nn::Result (*WriteSaveDataFileSystemExtraDataWithMask)();
    nn::Result (*FindSaveDataWithFilter)();
    nn::Result (*OpenSaveDataInfoReaderWithFilter)();
    nn::Result (*ReadSaveDataFileSystemExtraDataBySaveDataAttribute)();
    nn::Result (*WriteSaveDataFileSystemExtraDataWithMaskBySaveDataAttribute)();
    nn::Result (*ReadSaveDataFileSystemExtraDataWithMaskBySaveDataAttribute)();
    nn::Result (*OpenSaveDataMetaFile)();
    nn::Result (*OpenSaveDataTransferManager)();
    nn::Result (*OpenSaveDataTransferManagerVersion2)();
    nn::Result (*OpenSaveDataTransferProhibiter)();
    nn::Result (*ListAccessibleSaveDataOwnerId)();
    nn::Result (*OpenSaveDataTransferManagerForSaveDataRepair)();
    nn::Result (*OpenSaveDataMover)();
    nn::Result (*OpenSaveDataTransferManagerForRepair)();
    nn::Result (*OpenImageDirectoryFileSystem)();
    nn::Result (*OpenBaseFileSystem)();
    nn::Result (*FormatBaseFileSystem)();
    nn::Result (*OpenContentStorageFileSystem)();
    nn::Result (*OpenCloudBackupWorkStorageFileSystem)();
    nn::Result (*OpenCustomStorageFileSystem)();
    nn::Result (*OpenDataStorageByCurrentProcess)();
    nn::Result (*OpenDataStorageByProgramId)();
    nn::Result (*OpenDataStorageByDataId)();
    nn::Result (*OpenPatchDataStorageByCurrentProcess)();
    nn::Result (*OpenDataFileSystemWithProgramIndex)();
    nn::Result (*OpenDataStorageWithProgramIndex)();
    nn::Result (*OpenDataStorageByPath)();
    nn::Result (*OpenDataFileSystemByDataId)();
    nn::Result (*OpenDeviceOperator)();
    nn::Result (*OpenSdCardDetectionEventNotifier)();
    nn::Result (*OpenGameCardDetectionEventNotifier)();
    nn::Result (*OpenSystemDataUpdateEventNotifier)();
    nn::Result (*NotifySystemDataUpdateEvent)();
    nn::Result (*SimulateDeviceDetectionEvent)();
    nn::Result (*SetCurrentPosixTime)();
    nn::Result (*QuerySaveDataTotalSize)();
    nn::Result (*VerifySaveDataFileSystem)();
    nn::Result (*CorruptSaveDataFileSystem)();
    nn::Result (*CreatePaddingFile)();
    nn::Result (*DeleteAllPaddingFiles)();
    nn::Result (*GetRightsId)();
    nn::Result (*RegisterExternalKey)();
    nn::Result (*UnregisterAllExternalKey)();
    nn::Result (*GetRightsIdAndKeyGenerationByPath)();
    nn::Result (*SetCurrentPosixTimeWithTimeDifference)();
    nn::Result (*GetFreeSpaceSizeForSaveData)();
    nn::Result (*VerifySaveDataFileSystemBySaveDataSpaceId)();
    nn::Result (*CorruptSaveDataFileSystemBySaveDataSpaceId)();
    nn::Result (*QuerySaveDataInternalStorageTotalSize)();
    nn::Result (*GetSaveDataCommitId)();
    nn::Result (*UnregisterExternalKey)();
    nn::Result (*GetProgramId)();
    nn::Result (*SetSdCardEncryptionSeed)();
    nn::Result (*SetSdCardAccessibility)();
    nn::Result (*IsSdCardAccessible)();
    nn::Result (*OpenAccessFailureDetectionEventNotifier)();
    nn::Result (*GetAccessFailureDetectionEvent)();
    nn::Result (*IsAccessFailureDetected)();
    nn::Result (*ResolveAccessFailure)();
    nn::Result (*AbandonAccessFailure)();
    nn::Result (*GetAndClearErrorInfo)();
    nn::Result (*RegisterProgramIndexMapInfo)();
    nn::Result (*SetSaveDataSize)();
    nn::Result (*SetSaveDataRootPath)();
    nn::Result (*DisableAutoSaveDataCreation)();
    nn::Result (*SetGlobalAccessLogMode)();
    nn::Result (*GetGlobalAccessLogMode)();
    nn::Result (*OutputAccessLogToSdCard)();
    nn::Result (*RegisterUpdatePartition)();
    nn::Result (*OpenRegisteredUpdatePartition)();
    nn::Result (*GetAndClearMemoryReportInfo)();
    nn::Result (*SetDataStorageRedirectTarget)();
    nn::Result (*GetProgramIndexForAccessLog)();
    nn::Result (*GetFsStackUsage)();
    nn::Result (*UnsetSaveDataRootPath)();
    nn::Result (*FlushAccessLogOnSdCard)();
    nn::Result (*OutputApplicationInfoAccessLog)();
    nn::Result (*SetDebugOption)();
    nn::Result (*UnsetDebugOption)();
    nn::Result (*OverrideSaveDataTransferTokenSignVerificationKey)();
    nn::Result (*CorruptSaveDataFileSystemByOffset)();
    nn::Result (*OpenMultiCommitManager)();
    nn::Result (*OpenBisWiper)();
    nn::Result (*NotifyErrorContextServiceReady)(); 
};

struct nn::psc::sf::IPmStateLock {
    /* 0x00 */ struct nn::psc::sf::IPmStateLock::vtable* __vftable; 
};

struct nn::psc::sf::IPmStateLock::vtable {
    /* 0x00 */ void (*AddReference)(nn::psc::sf::IPmStateLock*);
    /* 0x08 */ void (*Release)(nn::psc::sf::IPmStateLock*);
    /* 0x10 */ void (*GetProxyInfo)(nn::psc::sf::IPmStateLock*);
    /* 0x18 */ void (*GetInterfaceTypeInfo)(nn::psc::sf::IPmStateLock*);

    /* 0x20 */ nn::Result (*Initialize)(nn::psc::sf::IPmStateLock*);
    /* 0x28 */ nn::Result (*Lock)(nn::psc::sf::IPmStateLock*);
    /* 0x28 */ nn::Result (*Unlock)(nn::psc::sf::IPmStateLock*);
    /* 0x28 */ nn::Result (*IsLocked)(nn::psc::sf::IPmStateLock*);
    /* 0x28 */ nn::Result (*GetLockState)(nn::psc::sf::IPmStateLock*);
};

struct nn::psc::sf::IPmService {
    struct nn::psc::sf::IPmService::vtable* __vftable;
};

struct nn::psc::sf::IPmService::vtable {
    /* 0x00 */ void (*AddReference)(nn::psc::sf::IPmService*);
    /* 0x08 */ void (*Release)(nn::psc::sf::IPmService*);
    /* 0x10 */ void (*GetProxyInfo)(nn::psc::sf::IPmService*);
    /* 0x18 */ void (*GetInterfaceTypeInfo)(nn::psc::sf::IPmService*);

    /* 0x20 */ nn::Result (*GetPmModule)(nn::psc::sf::IPmService*);
};

struct nn::psc::sf::IPmModule {
    struct nn::psc::sf::IPmModule::vtable* __vftable;
    nn::os::SystemEventType event;
}; // size >= 0x48

struct nn::psc::sf::IPmModule::vtable {
    /* 0x00 */ void (*AddReference)(nn::psc::sf::IPmModule*);
    /* 0x08 */ void (*Release)(nn::psc::sf::IPmModule*);
    /* 0x10 */ void (*GetProxyInfo)(nn::psc::sf::IPmModule*);
    /* 0x18 */ void (*GetInterfaceTypeInfo)(nn::psc::sf::IPmModule*);

    /* 0x20 */ nn::Result (*Initialize)(nn::psc::sf::IPmModule*);
    /* 0x28 */ nn::Result (*GetRequest)(nn::psc::sf::IPmModule*);
    /* 0x30 */ nn::Result (*Acknowledge)(nn::psc::sf::IPmModule*);
    /* 0x38 */ nn::Result (*Finalize)(nn::psc::sf::IPmModule*);
    /* 0x40 */ nn::Result (*AcknowledgeEx)(nn::psc::sf::IPmModule*);
};

struct nn::rtc::IRtcManager {
    struct nn::rtc::IRtcManager::vtable* __vftable;
};

struct nn::rtc::IRtcManager::vtable {
    /* 0x00 */ void (*AddReference)(nn::rtc::IRtcManager*);
    /* 0x08 */ void (*Release)(nn::rtc::IRtcManager*);
    /* 0x10 */ void (*GetProxyInfo)(nn::rtc::IRtcManager*);
    /* 0x18 */ void (*GetInterfaceTypeInfo)(nn::rtc::IRtcManager*);

    /* 0x20 */ nn::Result (*GetTimeInSeconds)(nn::rtc::IRtcManager*);
    /* 0x28 */ nn::Result (*SetTimeInSeconds)(nn::rtc::IRtcManager*);
    /* 0x30 */ nn::Result (*SetResetOnShutdown)(nn::rtc::IRtcManager*);
    /* 0x38 */ nn::Result (*GetResetDetected)(nn::rtc::IRtcManager*);
    /* 0x40 */ nn::Result (*ClearResetDetected)(nn::rtc::IRtcManager*);
    /* 0x40 */ nn::Result (*EnableAlarm)(nn::rtc::IRtcManager*);
    /* 0x40 */ nn::Result (*DisableRtcAlarm)(nn::rtc::IRtcManager*);
};

struct nn::srepo::EventId {
    /* 0x00 */ char string[0x20];
}; // size = 0x20

struct nn::srepo::SystemReport {
    /* 0x00 */ nn::srepo::EventId event_id;
    /* 0x20 */ u64 application_id;
    /* 0x28 */ u32 flags;
    /* 0x2C */ bool unk_2C;
    /* 0x2D */ char unk_2D[3];
    /* 0x30 */ u64 report_address;
    /* 0x38 */ u64 report_total_size;
    /* 0x40 */ u64 report_current_size;
}; // size = 0x48

struct nn::srepo::detail::ipc::ISrepoService {
    /* 0x00 */ struct nn::srepo::detail::ipc::ISrepoService::vtable __vftable;
};

struct nn::srepo::detail::ipc::ISrepoService::vtable {
    /* 0x00 */ void (*AddReference)(nn::rtc::IRtcManager*);
    /* 0x08 */ void (*Release)(nn::rtc::IRtcManager*);
    /* 0x10 */ void (*GetProxyInfo)(nn::rtc::IRtcManager*);
    /* 0x18 */ void (*GetInterfaceTypeInfo)(nn::rtc::IRtcManager*);

    /* 0x00 */ nn::Result (*SaveReport)();
    /* 0x00 */ nn::Result (*SaveReportWithUser)();
    /* 0x00 */ nn::Result (*SaveReportForAntiPiracy)();
    /* 0x00 */ nn::Result (*SaveReportWithUserForAntiPiracy)();
    /* 0x00 */ nn::Result (*SendReportWithUser)();
    /* 0x00 */ nn::Result (*NotifyUserList)();
    /* 0x00 */ nn::Result (*NotifyUserDeleted)();
    /* 0x00 */ nn::Result (*NotifyUserRegistered)();
    /* 0x00 */ nn::Result (*NotifyUserClosed)();
    /* 0x00 */ nn::Result (*NotifyUserOpened)();
    /* 0x00 */ nn::Result (*NotifyUserClosedWithApplicationId)();
    /* 0x00 */ nn::Result (*NotifyUserOpenedWithApplicationId)();
    /* 0x00 */ nn::Result (*NotifyCompletedNetworkRequestChanged)();
    /* 0x00 */ nn::Result (*NotifyFriendPresenceChanged)();
    /* 0x00 */ nn::Result (*NotifyNotificationConnectivityChanged)();
    /* 0x00 */ nn::Result (*NotifyDeviceOperationModeChanged)();
    /* 0x00 */ nn::Result (*NotifySystemPowerStateChanged)();
    /* 0x00 */ nn::Result (*NotifyAppletLaunched)();
    /* 0x00 */ nn::Result (*NotifyAppletExited)();
    /* 0x00 */ nn::Result (*NotifyForegroundAppletChanged)();
    /* 0x00 */ nn::Result (*NotifyControllerCountChanged)();
    /* 0x00 */ nn::Result (*NotifyAudioInStarted)();
    /* 0x00 */ nn::Result (*NotifyAudioInStopped)();
    /* 0x00 */ nn::Result (*NotifyLaunchApplicationStorage)();
    /* 0x00 */ nn::Result (*NotifyApplicationRightsInfo)();
    /* 0x00 */ nn::Result (*RegisterWatchdog)();
    /* 0x00 */ nn::Result (*UnregisterWatchdog)();
    /* 0x00 */ nn::Result (*GetSyslogLogger)();
    /* 0x00 */ nn::Result (*SaveSyslogReport)();
    /* 0x00 */ nn::Result (*PopReport)();
    /* 0x00 */ nn::Result (*GetPushEventReadableHandle)();
    /* 0x00 */ nn::Result (*Shutdown)();
    /* 0x00 */ nn::Result (*PopLostByBufferShortageInfo)();
    /* 0x00 */ nn::Result (*GetBufferUsageInfo)();
    /* 0x00 */ nn::Result (*SetDurationReportChatteringDetectionThreshold)();
    /* 0x00 */ nn::Result (*GetWatchdogStatistics)();
    /* 0x00 */ nn::Result (*NotifyForegroundTransmissionResult)();
};

struct RomFSHeader {
    /* 0x00 */ u64 header_size;
    /* 0x08 */ u64 dir_hash_table_ofs;
    /* 0x10 */ u64 dir_hash_table_size;
    /* 0x18 */ u64 dir_table_ofs;
    /* 0x20 */ u64 dir_table_size;
    /* 0x28 */ u64 file_hash_table_ofs;
    /* 0x30 */ u64 file_hash_table_size;
    /* 0x38 */ u64 file_table_ofs;
    /* 0x40 */ u64 file_table_size;
    /* 0x48 */ u64 file_partition_ofs;
}; // size = 0x50
