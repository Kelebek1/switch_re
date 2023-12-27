enum nn::audio::SessionType {
    /* 0 */ Invalid,
    /* 1 */ Render,
    /* 2 */ AudioOut,
    /* 3 */ Unk3,
    /* 4 */ Unk4,
    /* 5 */ NearVoice,
    /* 6 */ GameRecord,
    /* 7 */ Unk7,
    /* 8 */ UacOrBluetooth,
};

struct msgq_t {
    /* 0x00 */ s32 size;
    /* 0x04 */ s32 write_index;
    /* 0x08 */ s32 read_index;
    /* 0x0C */ s32 queue;
}; // size = 0x10

struct MessageQueue {
    /* 0x00 */ msgq_t msgq;
    /* 0x10 */ char messages[0x7F0];
}; // size = 0x800

struct MixRender {
    /* 0x0000 */ char unk0000[0x6000]; // mix buffer?
    /* 0x6000 */ char unk6000[0x1000];
    /* 0x7000 */ s32 readPosition;
    /* 0x7004 */ char unk7004[0x4];
    /* 0x7008 */ s32 unk_7008; // set to 0 in AudioRenderSession::Open
    /* 0x700C */ s32 unk_700C; // set to 0 in AudioRenderSession::Open
}; // size = 0x7010

struct MixOut {
    /* 0x00 */ s32 subStructIndex; // is an index to subStruct in the DSP
    /* 0x04 */ s32 subStructIndex2; // incremented in a loop in SetReadPosition up to subStructCount
    /* 0x08 */ s32 readPosition;
    /* 0x0C */ char unk0C[0x4];
    /* 0x10 */ s64 playedSampleCount;
}; // size = 0x18

struct MixNearVoice {
    /* 0x00 */ char unk00[0x8];
    /* 0x08 */ s32 writePosition;
    /* 0x0C */ char unk0C[0xC];
    /* 0x18 */ s32 readPosition;
    /* 0x1C */ s32 unk_1C; // some kind of state? set to 3 in Session->Unk30, set to 2 in Session->Unk34
}; // size = 0x20

// dramSharedApp
struct gMixData {
    /* 0x00000 */ MessageQueue adspMsgQ;
    /* 0x00800 */ MessageQueue firmwareMsgQ;
    /* 0x01000 */ MixRender mixRender[6]; // render
    /* 0x2B060 */ MixOut mixOut[12];  // audioOut
    /* 0x2B180 */ char unk2B180[2][0x18];   // 
    /* 0x2B1B0 */ char unk2B1B0[3][0x18];   // finalOutput?
    /* 0x2B1F8 */ MixNearVoice nearVoices[2];   // nearVoice
    /* 0x2B238 */ char unk2B238[4][0x20];   // gameRecord
    /* 0x2B2B8 */ char unk2B2B8[0x900];
    /* 0x2BBB8 */ char unk2BBB8[0x10];
    /* 0x2BBC8 */ char unk2BBC8[0x1800];
    /* 0x2D3C8 */ char unk2D3C8[0x10];
    /* 0x2D3D8 */ char unk2D3D8[0x1900];
    /* 0x2ECD8 */ char unk2ECD8[0x10];
    /* 0x2ECE8 */ u32 unk_2ECE8[5]; // func pointers for writing samples?
    /* 0x2ECFC */ char unk2ECFC[0x4];
    /* 0x2ED00 */ char unk2ED00[0xB8]; // 4 func pointers
}; // size = 0x2EDB8


struct DSP_App_B8 {
    /* 0x00 */ struct DSP_App_B8::vtable* __vftable;
    /* 0x08 */ char unk08[0x80];
    /* 0x88 */ nn::os::EventType unk_88;
    /* 0xB0 */ nn::os::EventType unk_B0;
    /* 0xD8 */ char unkD8[0x28];
}; // size = 0x100

struct DSP_App_B8::vtable {
    /* 0x00 */ void* (*unk_00)(DSP_App_B8*);
};

// each app
struct DSP_App {
    /* 0x0000 */ char name[0x80];
    /* 0x0080 */ char unk80[0x8];
    /* 0x0088 */ nn::os::Mutex mutex;
    /* 0x00A8 */ DSP_App_B8 unk_A8[20];
    /* 0x14A8 */ char unk14A8[0xD0];
}; // size = 0x1578

// apps running on the dsp?
struct DSP_Apps {
    /* 0x00 */ DSP_App unk_0000[20];
}; // size = 0x1AD60

enum OpusMessage : u32 {
    /*  0 */ Invalid = 0,
    /*  1 */ Start = 1,
    /*  2 */ Shutdown = 2,
    /* 11 */ StartOK = 11,
    /* 12 */ ShutdownOK = 12,
    /* 21 */ GetWorkBufferSize = 21,
    /* 22 */ InitializeDecodeObject = 22,
    /* 23 */ ShutdownDecodeObject = 23,
    /* 24 */ DecodeInterleaved = 24,
    /* 25 */ MapMemory = 25,
    /* 26 */ UnmapMemory = 26,
    /* 27 */ GetWorkBufferSizeForMultiStream = 27,
    /* 28 */ InitializeMultiStreamDecodeObject = 28,
    /* 29 */ ShutdownMultiStreamDecodeObject = 29,
    /* 30 */ DecodeInterleavedForMultiStream = 30,

    /* 41 */ GetWorkBufferSizeOK = 41,
    /* 42 */ InitializeDecodeObjectOK = 42,
    /* 43 */ ShutdownDecodeObjectOK = 43,
    /* 44 */ DecodeInterleavedOK = 44,
    /* 45 */ MapMemoryOK = 45,
    /* 46 */ UnmapMemoryOK = 46,
    /* 47 */ GetWorkBufferSizeForMultiStreamOK = 47,
    /* 48 */ InitializeMultiStreamDecodeObjectOK = 48,
    /* 49 */ ShutdownMultiStreamDecodeObjectOK = 49,
    /* 50 */ DecodeInterleavedForMultiStreamOK = 50,
};
