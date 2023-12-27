#include "service.h"
#include "shared.h"

enum TimeType : u8 {
    UserSystemClock,
    NetworkSystemClock,
    LocalSystemClock,
};

struct TimeZone::CalendarTime {
    /* 0x00 */ s16 year;
    /* 0x02 */ s8 month;
    /* 0x03 */ s8 day;
    /* 0x04 */ s8 hour;
    /* 0x05 */ s8 minute;
    /* 0x06 */ s8 second;
    /* 0x07 */ char pad[0x1];
}; // size = 0x8

struct TimeZone::CalendarAdditionalInfo {
    /* 0x00 */ u32 day_of_week;
    /* 0x04 */ u32 day_of_year;
    /* 0x08 */ char name[8];
    /* 0x10 */ bool is_dst;
    /* 0x14 */ s32 ut_off;
}; // size = 0x18

struct TimeZone::LocationName {
    /* 0x00 */ char name[36];
}; // size = 0x24

struct TimeZone::TimeZoneRuleVersion {
    /* 0x00 */ char version[16];
}; // size = 0x10

struct TimeZone::CalendarTimeInternal {
    /* 0x00 */ u32 tm_sec;
    /* 0x04 */ u32 tm_min;
    /* 0x08 */ u32 tm_hour;
    /* 0x0C */ u32 tm_mday;
    /* 0x10 */ u32 tm_mon;
    /* 0x14 */ u32 tm_year;
    /* 0x18 */ u32 tm_wday;
    /* 0x1C */ u32 tm_yday;
    /* 0x20 */ u32 tm_isdst;
    /* 0x24 */ char tm_zone[16];
    /* 0x34 */ u32 tm_gmtoff;
    /* 0x38 */ u32 time_index;
}; // size = 0x3C

enum r_type : s32 {
    JULIAN_DAY = 0,
    DAY_OF_YEAR = 1,
    MONTH_NTH_DAY_OF_WEEK = 2,
};

struct rule {
    /* 0x00 */ r_type type;
    /* 0x04 */ s32 day;
    /* 0x08 */ s32 week;
    /* 0x0C */ s32 month;
    /* 0x10 */ s32 time;
};

struct ttinfo {
    /* 0x00 */ s32 tt_utoff;
    /* 0x04 */ bool tt_isdst;
    /* 0x08 */ s32 tt_desigidx;
    /* 0x0C */ bool tt_ttisstd;
    /* 0x0D */ bool tt_ttisut;
}; // size = 0x10

struct TimeZone::Rule {
    /* 0x0000 */ s32 timecnt;
    /* 0x0004 */ s32 typecnt;
    /* 0x0008 */ s32 charcnt;
    /* 0x000C */ bool goback;
    /* 0x000D */ bool goahead;
    /* 0x000E */ bool pad[0x2];
    /* 0x0010 */ s64 ats[1000];
    /* 0x1F50 */ u8 types[1000];
    /* 0x2338 */ ttinfo ttis[128];
    /* 0x2B38 */ s8 chars[512];
    /* 0x2D38 */ s32 defaulttype;
    /* 0x2D3C */ char reserved[0x12C4];
}; // size = 0x4000

struct TzifHeader {
    /* 0x00 */ u8 tzh_magic[4]; // "TZif"
    /* 0x04 */ u8 tzh_version[1];
    /* 0x05 */ char tzh_reserved[0xF];
    /* 0x14 */ u8 tzh_ttisutcnt[4];
    /* 0x18 */ u8 tzh_ttisstdcnt[4];
    /* 0x1C */ u8 tzh_leapcnt[4];
    /* 0x20 */ u8 tzh_timecnt[4];
    /* 0x24 */ u8 tzh_typecnt[4];
    /* 0x28 */ u8 tzh_charcnt[4];
}; // size = 0x2C

struct gTimeZoneBinary {
    /* 0x0000 */ TzifHeader* binary;
    /* 0x0008 */ TimeZone::Rule rule;
}; // size = 0x4008

struct SteadyClockTimePoint {
    /* 0x00 */ s64 time_point;
    /* 0x08 */ char clock_source_id[16];
}; // size = 0x18

struct SystemClockContext {
    /* 0x00 */ s64 offset;
    /* 0x08 */ SteadyClockTimePoint steady_time_point;
}; // size = 0x20

struct ClockSnapshot {
    /* 0x00 */ SystemClockContext user_context;
    /* 0x20 */ SystemClockContext network_context;
    /* 0x40 */ s64 user_time;
    /* 0x48 */ s64 network_time;
    /* 0x50 */ TimeZone::CalendarTime user_calendar_time;
    /* 0x58 */ TimeZone::CalendarTime network_calendar_time;
    /* 0x60 */ TimeZone::CalendarAdditionalInfo user_calendar_additional_time;
    /* 0x78 */ TimeZone::CalendarAdditionalInfo network_calendar_additional_time;
    /* 0x90 */ SteadyClockTimePoint steady_clock_time_point;
    /* 0xA8 */ TimeZone::LocationName location_name;
    /* 0xCC */ u8 is_automatic_correction_enabled;
    /* 0xCD */ TimeType type;
    /* 0xCE */ char pad[0x2];
}; // size = 0xD0

struct ContinuousAdjustmentTimePoint {
    /* 0x00 */ s64 rtc_offset;
    /* 0x08 */ s64 diff_scale;
    /* 0x10 */ s64 shift_amount;
    /* 0x18 */ s64 lower;
    /* 0x20 */ s64 upper;
    /* 0x28 */ char clock_source_id[16];
}; // size = 0x38

struct AlarmInfo {
    /* 0x00 */ s64 alert_time;
    /* 0x08 */ u32 priority;
}; // size = 0x10

struct SteadyClockCore {
    /* 0x00 */ struct SteadyClockCore::vtable* __vftable;
    ///* 0x08 */ bool initialised; // IDA can't handle the 1 byte alignment
    ///* 0x09 */ bool reset_detected; // IDA can't handle the 1 byte alignment
}; // size = 0x08

struct SteadyClockCore::vtable {
    /* 0x00 */ nn::Result (*GetCurrentTimePoint)(SteadyClockCore*, SteadyClockTimePoint*);
    /* 0x08 */ s64 (*GetCurrentRawTimePoint)(SteadyClockCore*);
    /* 0x10 */ s64 (*GetTestOffset)(SteadyClockCore*);
    /* 0x18 */ void (*SetTestOffset)(SteadyClockCore*, s64*);
    /* 0x20 */ s64 (*GetInternalOffset)(SteadyClockCore*);
    /* 0x28 */ s64 (*SetInternalOffset)(SteadyClockCore*, s64*);
    /* 0x30 */ nn::Result (*GetRtcValue)(SteadyClockCore*, s64*);
    /* 0x38 */ nn::Result (*D0)(SteadyClockCore*);
    /* 0x40 */ nn::Result (*D1)(SteadyClockCore*);
    /* 0x48 */ nn::Result (*GetSetupResultValue)(SteadyClockCore*);
};

struct SystemClockCore {
    /* 0x00 */ struct SystemClockCore::vtable* __vftable;
    /* 0x08 */ bool initialised;
    /* 0x09 */ char unk09[0x6];
    /* 0x10 */ struct LocalSystemClockContextWriter* context_writer;
    /* 0x18 */ SteadyClockCore* steady_clock;
    /* 0x20 */ SystemClockContext context;
}; // size = 0x40

struct SystemClockCore::vtable {
    /* 0x00 */ nn::Result (*GetContext)(SystemClockCore*, SystemClockContext*);
    /* 0x08 */ nn::Result (*SetContext)(SystemClockCore*, SystemClockContext*);
    /* 0x10 */ nn::Result (*D1)(SystemClockCore*);
    /* 0x18 */ nn::Result (*D0)(SystemClockCore*);
};

struct StandardSteadyClockCore {
    /* 0x00 */ SteadyClockCore core;
    /* 0x08 */ bool initialised; // should be inside SteadyClockCore, but IDA can't handle alignment
    /* 0x09 */ bool reset_detected; // should be inside SteadyClockCore, but IDA can't handle alignment
    /* 0x0C */ nn::os::SdkMutexType mutex;
    /* 0x10 */ s64 test_offset;
    /* 0x18 */ s64 internal_offset;
    /* 0x20 */ char clock_source_id[16];
    /* 0x30 */ s64 rtc_offset;
    /* 0x38 */ s64 cached_time_point;
    /* 0x40 */ ContinuousAdjustmentTimePoint continuous_adjustment_time_point;
}; // size = 0x78

struct TickBasedSteadyClockCore {
    /* 0x00 */ SteadyClockCore core;
    /* 0x08 */ bool initialised; // should be inside SteadyClockCore, but IDA can't handle alignment
    /* 0x09 */ bool reset_detected; // should be inside SteadyClockCore, but IDA can't handle alignment
    /* 0x0A */ char clock_source_id[16];
    /* 0x1A */ char unk1A[0x6];
}; // size = 0x20

struct StandardLocalSystemClockCore {
    /* 0x00 */ SystemClockCore core;
}; // size = 0x40

struct StandardNetworkSystemClockCore {
    /* 0x00 */ SystemClockCore core;
    /* 0x40 */ s64 sufficient_accuracy;
}; // size = 0x48

struct StandardUserSystemClockCore {
    /* 0x00 */ SystemClockCore core;
    /* 0x40 */ bool automatic_correction;
    /* 0x48 */ StandardLocalSystemClockCore* local_system_clock;
    /* 0x50 */ StandardNetworkSystemClockCore* network_system_clock;
    /* 0x58 */ SteadyClockTimePoint time_point;
    /* 0x70 */ nn::os::SystemEventType event;
}; // size = 0xA0

struct TimeZone {
    /* 0x0000 */ bool initialised;
    /* 0x0004 */ nn::os::SdkRecursiveMutexType mutex;
    /* 0x000C */ TimeZone::LocationName location;
    /* 0x0030 */ TimeZone::Rule my_rule;
    /* 0x4030 */ SteadyClockTimePoint steady_clock_time_point;
    /* 0x4048 */ u32 total_location_name_count;
    /* 0x404C */ TimeZone::TimeZoneRuleVersion rule_version;
}; // size = 0x4060

struct EphemeralNetworkSystemClockCore {
    /* 0x00 */ SystemClockCore core;
}; // size = 0x40

struct LockFreeAtomic_SteadyClockTimePoint {
    /* 0x00 */ u32 counter;
    /* 0x08 */ SteadyClockTimePoint time_points[2];
}; // size = 0x38

struct LockFreeAtomic_SystemClockContext {
    /* 0x00 */ u32 counter;
    /* 0x08 */ SystemClockContext contexts[2];
}; // size = 0x48

struct LockFreeAtomic_AutomaticCorrection {
    /* 0x00 */ u32 counter;
    /* 0x04 */ bool auto_corrects[2];
}; // size = 0x8

struct LockFreeAtomic_ContinuousAdjustmentTimePoint {
    /* 0x00 */ u32 counter;
    /* 0x08 */ ContinuousAdjustmentTimePoint time_points[2];
}; // size = 0x78

struct SharedMemory {
    /* 0x0000 */ LockFreeAtomic_SteadyClockTimePoint steady_time_points;
    /* 0x0038 */ LockFreeAtomic_SystemClockContext local_system_contexts;
    /* 0x0080 */ LockFreeAtomic_SystemClockContext network_system_contexts;
    /* 0x00C8 */ LockFreeAtomic_AutomaticCorrection automatic_corrections;
    /* 0x00D0 */ LockFreeAtomic_ContinuousAdjustmentTimePoint continuous_time_points;
    /* 0x0148 */ char unk0148[0xEB8];
}; // size = 0x1000

struct TimeSharedMemory {
    /* 0x00 */ nn::os::SharedMemoryType shared_memory;
    /* 0x40 */ SharedMemory* memory;
}; // size = 0x48

struct Node {
    /* 0x00 */ Node* tail;
    /* 0x08 */ Node* head;
}; // size = 0x40

struct OperationEvent {
    /* 0x00 */ Node node;
    /* 0x10 */ nn::os::SystemEventType event;
}; // size = 0x40

struct Alarms {
    /* 0x00 */ SteadyClockCore* steady_clock;
    /* 0x08 */ struct Unk42A8* unk_42A8;
    /* 0x10 */ Node node;
    /* 0x20 */ nn::os::SystemEventType event;
    /* 0x50 */ Node* unk_node; // ??
    /* 0x58 */ nn::os::SdkMutexType mutex;
}; // size >= 0x60

struct nn::timesrv::detail::service::SystemClockContextWriter {
    nn::Result (*Write)(struct LocalSystemClockContextWriter*, SystemClockContext*);
};

struct LocalSystemClockContextWriter {
    /* 0x00 */ nn::timesrv::detail::service::SystemClockContextWriter* __vftable;
    /* 0x08 */ Node node;
    /* 0x18 */ nn::os::SdkMutexType mutex;
    /* 0x20 */ TimeSharedMemory* shared_memory;
    /* 0x28 */ bool in_use;
    /* 0x30 */ SystemClockContext context;
}; // size = 0x50

struct NetworkSystemClockContextWriter {
    /* 0x00 */ nn::timesrv::detail::service::SystemClockContextWriter* __vftable;
    /* 0x08 */ Node node;
    /* 0x18 */ nn::os::SdkMutexType mutex;
    /* 0x20 */ TimeSharedMemory* shared_memory;
    /* 0x28 */ bool in_use;
    /* 0x30 */ SystemClockContext context;
    /* 0x50 */ SystemClockCore* system_clock;
}; // size = 0x58

struct EphemeralNetworkSystemClockContextWriter {
    /* 0x00 */ nn::timesrv::detail::service::SystemClockContextWriter* __vftable;
    /* 0x08 */ Node node;
    /* 0x18 */ nn::os::SdkMutexType mutex;
    /* 0x1C */ char pad[0x4];
    /* 0x20 */ bool in_use;
    /* 0x28 */ SystemClockContext context;
}; // size = 0x48

struct StaticServiceSetupInfo {
    /* 0x00 */ bool unk_00; // user = 0, admin = 1, repair = 0, service manager = 1, su = 0, s = 0
    /* 0x01 */ bool unk_01; // user = 0, admin = 1, repair = 0, service manager = 1, su = 0, s = 0
    /* 0x02 */ bool unk_02; // user = 0, admin = 0, repair = 0, service manager = 1, su = 0, s = 1
    /* 0x03 */ bool unk_03; // user = 0, admin = 1, repair = 0, service manager = 1, su = 0, s = 0
    /* 0x04 */ bool unk_04; // user = 0, admin = 0, repair = 1, service manager = 1, su = 0, s = 0
    /* 0x05 */ bool unk_05; // user = 0, admin = 0, repair = 0, service manager = 0, su = 1, s = 0
}; // size = 0x6

struct StaticService {
    /* 0x00 */ StaticServiceSetupInfo setup_info;
    /* 0x08 */ nn::lmem::detail::HeapHead* heap;
    /* 0x10 */ StandardLocalSystemClockCore* local_system_clock;
    /* 0x18 */ StandardUserSystemClockCore* user_system_clock;
    /* 0x20 */ StandardNetworkSystemClockCore* network_system_clock;
    /* 0x28 */ struct TimeServer* time;
    /* 0x30 */ TimeZone* time_zone;
    /* 0x38 */ EphemeralNetworkSystemClockCore* ephemeral_network_clock;
    /* 0x40 */ TimeSharedMemory* shared_memory;
}; // size = 0x48

struct nn::timesrv::detail::service::IStaticService::vtable {
    /* 0x00 */ void (*AddReference)(SystemClock*);
    /* 0x08 */ void (*Release)(SystemClock*);
    /* 0x10 */ void (*GetProxyInfo)(SystemClock*);
    /* 0x18 */ void (*GetInterfaceTypeInfo)(SystemClock*);

    /* 0x20 */ nn::Result (*GetStandardUserSystemClock)(StaticService*);
    /* 0x28 */ nn::Result (*GetStandardNetworkSystemClock)(StaticService*);
    /* 0x30 */ nn::Result (*GetStandardSteadyClock)(StaticService*);
    /* 0x38 */ nn::Result (*GetTimeZoneService)(StaticService*);
    /* 0x40 */ nn::Result (*GetStandardLocalSystemClock)(StaticService*);
    /* 0x48 */ nn::Result (*GetEphemeralNetworkSystemClock)(StaticService*);
    /* 0x50 */ nn::Result (*GetSharedMemoryNativeHandle)(StaticService*);
    /* 0x58 */ nn::Result (*SetStandardSteadyClockInternalOffset)(StaticService*);
    /* 0x60 */ nn::Result (*GetStandardSteadyClockRtcValue)(StaticService*);
    /* 0x68 */ nn::Result (*IsStandardUserSystemClockAutomaticCorrectionEnabled)(StaticService*);
    /* 0x70 */ nn::Result (*SetStandardUserSystemClockAutomaticCorrectionEnabled)(StaticService*);
    /* 0x78 */ nn::Result (*GetStandardUserSystemClockInitialYear)(StaticService*);
    /* 0x80 */ nn::Result (*IsStandardNetworkSystemClockAccuracySufficient)(StaticService*);
    /* 0x88 */ nn::Result (*GetStandardUserSystemClockAutomaticCorrectionUpdatedTime)(StaticService*);
    /* 0x90 */ nn::Result (*CalculateMonotonicSystemClockBaseTimePoint)(StaticService*);
    /* 0x98 */ nn::Result (*GetClockSnapshot)(StaticService*);
    /* 0xA0 */ nn::Result (*GetClockSnapshotFromSystemClockContext)(StaticService*);
    /* 0xA8 */ nn::Result (*CalculateStandardUserSystemClockDifferenceByUser)(StaticService*);
    /* 0xB0 */ nn::Result (*CalculateSpanBetween)(StaticService*);
};

struct StaticService_Wrap {
    /* 0x00 */ nn::timesrv::detail::service::IStaticService::vtable* __vftable;
    /* 0x08 */ StaticService impl;
}; // size = 0x50

struct StaticService_Wrap2 {
    /* 0x00 */ nn::timesrv::detail::service::IStaticService::vtable* __vftable;
    /* 0x08 */ StaticService impl;
    /* 0x50 */ u32 initialised;
    /* 0x58 */ nn::lmem::detail::HeapHead** heap;
}; // size = 0x60

struct AlarmService {
    /* 0x00 */ nn::lmem::detail::HeapHead** heap;
    /* 0x08 */ Alarms* alarms;
}; // size = 0x10

struct AlarmService_Wrap {
    /* 0x00 */ struct nn::timesrv::detail::service::IAlarmService::vtable* __vftable;
    /* 0x08 */ AlarmService impl;
}; // size = 0x18

struct nn::timesrv::detail::service::IAlarmService::vtable {
    /* 0x00 */ void (*AddReference)(AlarmService_Wrap*);
    /* 0x08 */ void (*Release)(AlarmService_Wrap*);
    /* 0x10 */ void (*GetProxyInfo)(AlarmService_Wrap*);
    /* 0x18 */ void (*GetInterfaceTypeInfo)(AlarmService_Wrap*);

    /* 0x20 */ nn::Result (*CreateWakeupAlarm)(AlarmService_Wrap*);
    /* 0x28 */ nn::Result (*CreateBackgroundTaskAlarm)(AlarmService_Wrap*);
};

enum AlarmType : u32 {
    WakeupAlarm = 0,
    BackgroundTaskAlarm = 1,
};

struct Alarm {
    /* 0x00 */ Node node;
    /* 0x10 */ u32 priority;
    /* 0x18 */ nn::os::SystemEventType event;
    /* 0x48 */ s64 alert_time;
    /* 0x50 */ nn::psc::sf::IPmStateLock* psc_lock_service;
}; // size = 0x58

struct SteadyClockAlarm {
    /* 0x00 */ Alarms* alarms;
    /* 0x08 */ Alarm alarm;
}; // size = 0x60

struct SteadyClockAlarm_Wrap {
    /* 0x00 */ struct nn::timesrv::detail::service::ISteadyClockAlarm::vtable* __vftable;
    /* 0x08 */ SteadyClockAlarm impl;
    /* 0x68 */ bool heap_initialised;
    /* 0x70 */ nn::lmem::detail::HeapHead** heap;
}; // size = 0x78

struct nn::timesrv::detail::service::ISteadyClockAlarm::vtable {
    /* 0x00 */ void (*AddReference)(SteadyClockAlarm*);
    /* 0x08 */ void (*Release)(SteadyClockAlarm*);
    /* 0x10 */ void (*GetProxyInfo)(SteadyClockAlarm*);
    /* 0x18 */ void (*GetInterfaceTypeInfo)(SteadyClockAlarm*);

    /* 0x20 */ nn::Result (*GetAlarmEvent)(SteadyClockAlarm*);
    /* 0x28 */ nn::Result (*Enable)(SteadyClockAlarm*);
    /* 0x28 */ nn::Result (*Disable)(SteadyClockAlarm*);
    /* 0x28 */ nn::Result (*IsEnabled)(SteadyClockAlarm*);
    /* 0x28 */ nn::Result (*CreateWakeLock)(SteadyClockAlarm*);
    /* 0x28 */ nn::Result (*DestroyWakeLock)(SteadyClockAlarm*);
};

struct TimeServiceManager {
    /* 0x000 */ struct TimeServer* time;
    /* 0x008 */ nn::lmem::detail::HeapHead** heap;
    /* 0x010 */ StandardLocalSystemClockCore* local_system_clock;
    /* 0x018 */ StandardUserSystemClockCore* user_system_clock;
    /* 0x020 */ StandardNetworkSystemClockCore* network_system_clock;
    /* 0x028 */ StandardSteadyClockCore* steady_clock;
    /* 0x030 */ TimeZone* time_zone;
    /* 0x038 */ EphemeralNetworkSystemClockCore* ephemeral_network_clock;
    /* 0x040 */ TimeSharedMemory* shared_memory;
    /* 0x048 */ Alarms* alarms;
    /* 0x050 */ LocalSystemClockContextWriter* local_system_context_writer;
    /* 0x058 */ NetworkSystemClockContextWriter* network_system_context_writer;
    /* 0x060 */ EphemeralNetworkSystemClockContextWriter* ephemeral_system_context_writer;
    /* 0x068 */ Node local_node;
    /* 0x078 */ nn::os::SystemEventType local_event;
    /* 0x0A8 */ Node network_node;
    /* 0x0B8 */ nn::os::SystemEventType network_event;
    /* 0x0E8 */ Node ephemeral_node;
    /* 0x0F8 */ nn::os::SystemEventType ephemeral_event;
}; // size = 0x128

struct nn::timesrv::detail::service::ITimeServiceManager::vtbl {
    /* 0x00 */ void (*AddReference)(TimeServiceManager*);
    /* 0x08 */ void (*Release)(TimeServiceManager*);
    /* 0x10 */ void (*GetProxyInfo)(TimeServiceManager*);
    /* 0x18 */ void (*GetInterfaceTypeInfo)(TimeServiceManager*);

    /* 0x20 */ nn::Result (*GetStaticServiceAsUser)(TimeServiceManager*);
    /* 0x28 */ nn::Result (*GetStaticServiceAsAdmin)(TimeServiceManager*);
    /* 0x30 */ nn::Result (*GetStaticServiceAsRepair)(TimeServiceManager*);
    /* 0x38 */ nn::Result (*GetStaticServiceAsServiceManager)(TimeServiceManager*);
    /* 0x40 */ nn::Result (*SetupStandardSteadyClockCore)(TimeServiceManager*);
    /* 0x48 */ nn::Result (*SetupStandardLocalSystemClockCore)(TimeServiceManager*);
    /* 0x50 */ nn::Result (*SetupStandardNetworkSystemClockCore)(TimeServiceManager*);
    /* 0x58 */ nn::Result (*SetupStandardUserSystemClockCore)(TimeServiceManager*);
    /* 0x60 */ nn::Result (*SetupTimeZoneServiceCore)(TimeServiceManager*);
    /* 0x68 */ nn::Result (*SetupEphemeralNetworkSystemClockCore)(TimeServiceManager*);
    /* 0x70 */ nn::Result (*GetStandardLocalClockOperationEvent)(TimeServiceManager*);
    /* 0x78 */ nn::Result (*GetStandardNetworkClockOperationEventForServiceManager)(TimeServiceManager*);
    /* 0x80 */ nn::Result (*GetEphemeralNetworkClockOperationEventForServiceManager)(TimeServiceManager*);
    /* 0x88 */ nn::Result (*GetStandardUserSystemClockAutomaticCorrectionUpdatedEvent)(TimeServiceManager*);
    /* 0x90 */ nn::Result (*SetStandardSteadyClockBaseTime)(TimeServiceManager*);
    /* 0x98 */ nn::Result (*GetClosestAlarmUpdatedEvent)(TimeServiceManager*);
    /* 0xA0 */ nn::Result (*CheckAndSignalAlarms)(TimeServiceManager*);
    /* 0xA8 */ nn::Result (*GetClosestAlarmInfo)(TimeServiceManager*); 
};

struct TimeServiceManager_Wrap {
    /* 0x000 */ nn::timesrv::detail::service::ITimeServiceManager::vtbl* __vftable;
    /* 0x080 */ TimeServiceManager impl;
}; // size = 0x130

struct PowerStateRequestHandler {
    /* 0x00 */ struct Unk42A8* unk_42A8;
}; // size = 0x08

struct PowerStateRequestHandler_Wrap {
    /* 0x00 */ void* __vftable;
    /* 0x08 */ PowerStateRequestHandler impl;
}; // size = 0x10

struct Unk4440 {
    /* 0x0000 */ void* __vftable;
    /* 0x0008 */ char unk0008[0x98];
    /* 0x00A0 */ nn::os::EventType event;
    /* 0x00C8 */ char unk00C8[0x7310];
    /* 0x73D8 */ char heap_memory[0x1000];
    /* 0x83D8 */ nn::lmem::detail::HeapHead* heap;
    /* 0x83E0 */ nn::os::MutexType mutex;
    /* 0x8400 */ StaticService_Wrap static_service_su;
    /* 0x8450 */ StaticService_Wrap static_service_s;
    /* 0x84A0 */ AlarmService_Wrap alarm_service;
    /* 0x84B8 */ TimeServiceManager_Wrap time_service_manager;
    /* 0x85E8 */ PowerStateRequestHandler_Wrap power_state_service;
    /* 0x85F8 */ bool service_s_p_setup;
}; // size = 0x8600

struct Unk42A8 {
    /* 0x00 */ nn::os::SystemEventType event;
    /* 0x30 */ bool unk_30;
    /* 0x34 */ u32 priority1;
    /* 0x38 */ bool unk_38;
    /* 0x3C */ u32 priority2;
    /* 0x40 */ nn::os::SdkMutexType mutex;
    /* 0x44 */ char unk44[0x4];
}; // size = 0x48

struct TimeServer {
    /* 0x0000 */ StandardSteadyClockCore standard_steady_clock;
    /* 0x0078 */ TickBasedSteadyClockCore tick_steady_clock;
    /* 0x0098 */ StandardLocalSystemClockCore local_system_clock;
    /* 0x00D8 */ StandardNetworkSystemClockCore network_system_clock;
    /* 0x0120 */ StandardUserSystemClockCore user_system_clock;
    /* 0x01C0 */ TimeZone time_zone;
    /* 0x4220 */ EphemeralNetworkSystemClockCore ephemeral_network_clock;
    /* 0x4260 */ TimeSharedMemory shared_memory;
    /* 0x42A8 */ Unk42A8 unk_42A8;
    /* 0x42F0 */ Alarms alarms;
    /* 0x4350 */ LocalSystemClockContextWriter local_system_clock_context;
    /* 0x43A0 */ NetworkSystemClockContextWriter network_system_clock_context;
    /* 0x43F8 */ EphemeralNetworkSystemClockContextWriter ephemeral_network_clock_context;
    /* 0x4440 */ Unk4440 unk_4440;
}; // size = 0xCA40

struct SystemClock {
    /* 0x00 */ StandardUserSystemClockCore* system_clock_iface;
    /* 0x08 */ nn::lmem::detail::HeapHead* heap;
    /* 0x10 */ u8 unk_10; // unk_02 in StaticService
    /* 0x11 */ u8 unk_11; // unk_05 in StaticService
    /* 0x18 */ OperationEvent* operation_event;
}; // size = 0x20

struct nn::timesrv::detail::service::ISystemClock::vtbl {
    /* 0x00 */ void (*AddReference)(SystemClock*);
    /* 0x08 */ void (*Release)(SystemClock*);
    /* 0x10 */ void (*GetProxyInfo)(SystemClock*);
    /* 0x18 */ void (*GetInterfaceTypeInfo)(SystemClock*);

    /* 0x20 */ nn::Result (*GetCurrentTime)(SystemClock*);
    /* 0x20 */ nn::Result (*SetCurrentTime)(SystemClock*);
    /* 0x20 */ nn::Result (*GetSystemClockContext)(SystemClock*);
    /* 0x20 */ nn::Result (*SetSystemClockContext)(SystemClock*);
    /* 0x20 */ nn::Result (*GetOperationEventReadableHandle)(SystemClock*);
};

struct SystemClock_Wrap {
    /* 0x00 */ nn::timesrv::detail::service::ISystemClock::vtbl* __vftable;
    /* 0x08 */ SystemClock impl;
    /* 0x28 */ u32 heap_initialised;
    /* 0x30 */ void* heap;
}; // size = 0x38

struct SteadyClock {
    /* 0x00 */ SteadyClockCore* steady_clock;
    /* 0x08 */ u8 unk_08;
    /* 0x09 */ u8 unk_09;
    /* 0x0A */ char pad[0x6];
}; // size = 0x10

struct nn::timesrv::detail::service::ISteadyClock::vtbl {
    /* 0x00 */ void (*AddReference)(SteadyClock*);
    /* 0x08 */ void (*Release)(SteadyClock*);
    /* 0x10 */ void (*GetProxyInfo)(SteadyClock*);
    /* 0x18 */ void (*GetInterfaceTypeInfo)(SteadyClock*);

    /* 0x20 */ nn::Result (*GetCurrentTimePoint)(SteadyClock*, SteadyClockTimePoint*);
    /* 0x28 */ nn::Result (*GetTestOffset)(SteadyClock*, s64*);
    /* 0x30 */ nn::Result (*SetTestOffset)(SteadyClock*, s64);
    /* 0x38 */ nn::Result (*GetRtcValue)(SteadyClock*, s64*);
    /* 0x40 */ nn::Result (*IsRtcResetDetected)(SteadyClock*, bool*);
    /* 0x48 */ nn::Result (*GetSetupResultValue)(SteadyClock*);
    /* 0x50 */ nn::Result (*GetInternalOffset)(SteadyClock*);
};

struct SteadyClock_Wrap {
    /* 0x00 */ nn::timesrv::detail::service::ISteadyClock::vtbl* __vftable;
    /* 0x08 */ SteadyClock impl;
    /* 0x18 */ u32 heap_initialised;
    /* 0x20 */ void* heap;
}; // size = 0x28

struct TimeZoneService {
    /* 0x00 */ StandardSteadyClockCore* standard_steady_clock; 
    /* 0x08 */ TimeZone* time_zone;
    /* 0x10 */ u8 unk_10; // unk_03 in setup info
}; // size = 0x18

struct nn::timesrv::detail::service::ITimeZoneService::vtable {
    /* 0x00 */ void (*AddReference)(SteadyClock*);
    /* 0x08 */ void (*Release)(SteadyClock*);
    /* 0x10 */ void (*GetProxyInfo)(SteadyClock*);
    /* 0x18 */ void (*GetInterfaceTypeInfo)(SteadyClock*);

    /* 0x20 */ nn::Result (*GetDeviceLocationName)(TimeZoneService*);
    /* 0x28 */ nn::Result (*SetDeviceLocationName)(TimeZoneService*);
    /* 0x30 */ nn::Result (*GetTotalLocationNameCount)(TimeZoneService*);
    /* 0x38 */ nn::Result (*LoadLocationNameList)(TimeZoneService*);
    /* 0x40 */ nn::Result (*LoadTimeZoneRule)(TimeZoneService*);
    /* 0x48 */ nn::Result (*GetTimeZoneRuleVersion)(TimeZoneService*);
    /* 0x50 */ nn::Result (*GetDeviceLocationNameAndUpdatedTime)(TimeZoneService*);
    /* 0x58 */ nn::Result (*SetDeviceLocationNameWithTimeZoneRule)(TimeZoneService*);
    /* 0x60 */ nn::Result (*ParseTimeZoneBinary)(TimeZoneService*);
    /* 0x68 */ nn::Result (*GetDeviceLocationNameOperationEventReadableHandle)(TimeZoneService*);
    /* 0x70 */ nn::Result (*ToCalendarTime)(TimeZoneService*);
    /* 0x78 */ nn::Result (*ToCalendarTimeWithMyRule)(TimeZoneService*);
    /* 0x80 */ nn::Result (*ToPosixTime)(TimeZoneService*);
    /* 0x88 */ nn::Result (*ToPosixTimeWithMyRule)(TimeZoneService*);
};

struct TimeZoneService_Wrap {
    /* 0x00 */ nn::timesrv::detail::service::ITimeZoneService::vtable* __vftable;
    /* 0x08 */ TimeZoneService impl;
    /* 0x20 */ u32 heap_initialised;
    /* 0x28 */ void* heap;
}; // size = 0x30





// ========================== glue ============================

struct StandardSteadyClockResource {
    /* 0x00 */ void* __vftable;
    /* 0x08 */ nn::os::SdkMutexType;
    /* 0x10 */ char clock_source_id[16];
    /* 0x20 */ s64 time;
    /* 0x28 */ nn::Result set_time_result;
    /* 0x2C */ bool rtc_reset;
}; // size = 0x30

struct GlueLockFreeAtomics {
    /* 0x00 */ u32 unk_00;
    /* 0x00 */ LockFreeAtomic_SystemClockContext lock_free;
};

struct GlueTimeZoneService {
    /* 0x00 */ bool unk_00; // unk_03 from setup info
    /* 0x08 */ struct GlueTime40* unk_08;
    /* 0x10 */ TimeZoneService_Wrap* timezone_service;
    /* 0x18 */ nn::os::SdkRecursiveMutexType mutex;
    /* 0x20 */ bool event_initialied;
    /* 0x28 */ Node node;
    /* 0x38 */ nn::os::SystemEventType event;
}; // size = 0x68

struct GlueTimeZoneService_Wrap {
    /* 0x00 */ nn::timesrv::detail::service::ITimeZoneService::vtable* __vftable;
    /* 0x08 */ GlueTimeZoneService impl;
    /* 0x70 */ u32 heap_initialised;
    /* 0x78 */ void* heap;
}; // size = 0x80

struct GlueTime40 {
    /* 0x00 */ SystemClock_Wrap* standard_user_system_clock;
    /* 0x08 */ TimeZoneService_Wrap* timezone_service;
    /* 0x10 */ bool initialised;
    /* 0x11 */ char unk_11[0x7];
}; // size = 0x18

struct GlueStaticService {
    /* 0x00 */ StaticServiceSetupInfo setup_info;
    /* 0x08 */ StaticService_Wrap* static_service;
    /* 0x10 */ TimeZoneService_Wrap* timezone_service;
    /* 0x18 */ GlueTime40* unk_18;
    /* 0x20 */ StandardSteadyClockResource* steady_clock_resource;
}; // size = 0x28

struct GlueStaticService_Wrap {
    /* 0x00 */ nn::timesrv::detail::service::IStaticService::vtable* __vftable;
    /* 0x08 */ GlueStaticService impl;
    /* 0x30 */ nn::lmem::detail::HeapHead* heap;
}; // size = 0x38

// Related to alarms
struct GlueTime58Sub {
    /* 0x00 */ nn::os::SystemEventType event;
    /* 0x30 */ nn::os::TimerEventType timer_event;
    /* 0x70 */ char unk70[0x18];
    /* 0x88 */ StandardSteadyClockResource* steady_clock_resource;
}; // size = 0x90

struct GlueTime58PmStateChangeHandler {
    /* 0x00 */ struct nn::timemgr::detail::core::PmStateChangeHandler::vtable* __vftable;
    /* 0x08 */ GlueTime58Sub* sub58;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ char unk14[0x4];
}; // size = 0x18

struct nn::timemgr::detail::core::PmStateChangeHandler::vtable {
    /* 0x00 */ void (*nullsub_00)(); // FullAwake
    /* 0x08 */ void (*nullsub_08)();
    /* 0x10 */ void (*sub_7100059DE4)(); // MinimumAwake: set unk_10 to 0
    /* 0x18 */ void (*nullsub_18)();
    /* 0x20 */ void (*sub_7100059D9C)(); // SleepReady: set unk_10 to 1
    /* 0x28 */ void (*nullsub_28)();
    /* 0x30 */ void (*sub_7100059DA8)(); // EssentialServicesSleepReady: set unk_10 to 2, get closest alarm and re-enable it?
    /* 0x38 */ void (*nullsub_38)();
    /* 0x40 */ void (*nullsub_40)(); // EssentialServicesAwake
    /* 0x48 */ void (*sub_7100059DB8)(); // disable alarm id 0, stop event etc, set unk_10 to 1
    /* 0x50 */ void (*nullsub_50)(); // ShutdownReady
    /* 0x58 */ void (*nullsub_58)();
};

struct GlueTime58 {
    /* 0x000 */ nn::os::ThreadType thread;
    /* 0x1C0 */ nn::os::EventType event;
    /* 0x1E8 */ StaticService_Wrap* service_manager;
    /* 0x1F0 */ SystemClock_Wrap* network_system_clock;
    /* 0x1F8 */ SystemClock_Wrap* local_system_clock;
    /* 0x200 */ SystemClock_Wrap* ephemeral_system_clock;
    /* 0x208 */ StandardSteadyClockResource* steady_clock_resource;
    /* 0x210 */ GlueTime40* glue40;
    /* 0x218 */ nn::os::SystemEventType local_clock_event;
    /* 0x248 */ nn::os::SystemEventType network_clock_event;
    /* 0x278 */ nn::os::SystemEventType ephemeral_clock_event;
    /* 0x2A8 */ nn::os::SystemEventType standard_user_auto_correct_clock_event;
    /* 0x2D8 */ nn::os::TimerEventType timer_steady_clock;
    /* 0x318 */ nn::os::TimerEventType timer_file_system;
    /* 0x358 */ GlueTime58Sub unk_358;
    /* 0x3E8 */ GlueTime58PmStateChangeHandler power_state_change_handler;
}; // size = 0x400

struct GlueTime458 {
    /* 0x0000 */ char unk_0000[0x9B30];
    /* 0x9B30 */ GlueStaticService_Wrap time_u;
    /* 0x9B68 */ GlueStaticService_Wrap time_a;
    /* 0x9BA0 */ GlueStaticService_Wrap time_r;
    /* 0x9BD8 */ char unk_9BD8[0x1000];
    /* 0xABD8 */ nn::lmem::detail::HeapHead* heap;
    /* 0xABE0 */ nn::os::MutexType mutex;
}; // size = 0xAC10

struct GlueTime {
    /* 0x0000 */ void* unk_0000;
    /* 0x0008 */ StaticService_Wrap* service_manager;
    /* 0x0010 */ StandardSteadyClockResource steady_clock_resource;
    /* 0x0040 */ GlueTime40 unk_0040;
    /* 0x0058 */ GlueTime58 unk_0058; // TimeWorker thread related
    /* 0x0458 */ GlueTime458 unk_0458;
}; // size = 0xB058

struct GlueTimeServiceManager {
    /* 0x00 */ bool initialised;
    /* 0x08 */ void* unk_08;
    /* 0x10 */ u32 unk_10;
    /* 0x18 */ void* unk_vtable;
}; // size = 0x20

struct GlueTimeServiceManager_Wrap {
    /* 0x00 */ nn::timesrv::detail::service::ITimeServiceManager::vtbl* __vftable;
    /* 0x08 */ GlueTimeServiceManager impl;
    /* 0x28 */ u32 heap_initialised;
    /* 0x30 */ void* heap;
}; // size = 0x38

// Used in glue:notif
struct GlueTimeSharedMemory_Notif {
    /* 0x00 */ nn::os::SdkMutexType mutex;
    /* 0x04 */ char unk_04[0x4];
    /* 0x08 */ u32 index;
    /* 0x10 */ SystemClockContext clock_contexts[2];
}; // size = 0x50

struct NotifEventHandlerStruct {
    /* 0x00000 */ u8 unk_00000[0x10080];
    /* 0x10080 */ u8 unk_10080[0x1C78]; // related to time
    /* 0x11CF8 */ u8 unk_11CF8[0x10868];
}; // size >= 0x22560


// ========================== nim ============================

struct EnsureNetworkClockAvailabilityTask_NodeType {
    /* 0x00 */ Node node;
    /* 0x10 */ nn::os::MutexType mutex;
    /* 0x30 */ nn::os::EventType event;
}; // size = 0x58

struct EnsureNetworkClockAvailabilityTask {
    /* 0x000 */ nn::os::ThreadType thread;
    /* 0x1C0 */ nn::os::EventType event1;
    /* 0x1E0 */ EnsureNetworkClockAvailabilityTask_NodeType node;
}; // size >= 0x238

struct AutonomicEnsureNetworkClockAvailability {
    /* 0x000 */ nn::os::ThreadType thread;
    /* 0x1C0 */ nn::os::EventType event1;
    /* 0x1E8 */ nn::os::EventType event2;
    /* 0x210 */ nn::os::EventType event3;
    /* 0x238 */ nn::os::EventType event4;
    /* 0x260 */ nn::os::MutexType mutex;
    /* 0x280 */ char unk280[0x8];
    /* 0x288 */ nn::os::EventType event5;
    /* 0x2B0 */ s64 correction_interval_ns;
    /* 0x2B8 */ s64 failed_retry_time_ns;
    /* 0x2C0 */ s32 immediate_retry_count_max;
    /* 0x2C8 */ s64 immediate_retry_interval_ns;
}; // size >= 0x2D0

struct Ntc {
    /* 0x0000 */ char heap_memory[0x1000];
    /* 0x1000 */ nn::lmem::detail::HeapHead* heap;
    /* 0x1008 */ nn::os::MutexType mutex;
    /* 0x1028 */ AutonomicEnsureNetworkClockAvailability* availability;
}; // size >= 0x1030

struct Ntc_Wrap {
    /* 0x0000 */ struct nn::ntc::detail::service::IStaticService::vtable* __vftable;
    /* 0x0008 */ Ntc impl;
}; // size >= 0x1038

struct nn::ntc::detail::service::IStaticService::vtable {
    /* 0x00 */ void (*AddReference)(Ntc_Wrap*);
    /* 0x08 */ void (*Release)(Ntc_Wrap*);
    /* 0x10 */ void (*GetProxyInfo)(Ntc_Wrap*);
    /* 0x18 */ void (*GetInterfaceTypeInfo)(Ntc_Wrap*);

    /* 0x20 */ void (*OpenEnsureNetworkClockAvailabilityService)(Ntc_Wrap*);
    /* 0x28 */ void (*SuspendAutonomicTimeCorrection)(Ntc_Wrap*);
    /* 0x30 */ void (*ResumeAutonomicTimeCorrection)(Ntc_Wrap*);
};

struct Ntc_Wrap2 {
    /* 0x0000 */ char unk_0000[0x1450];
    /* 0x1450 */ Ntc_Wrap impl;
}; // size >= 0x2488

struct ServerTimeGetter_Base {
    /* 0x00 */ struct ServerTimeGetter_Base::vtable* __vftable;
};

struct ServerTimeGetter_Base::vtable {
    /* 0x00 */ void (*DoNetClockUpdate)(ServerTimeGetter_Base*);
};

struct ServerTimeGetter01 : ServerTimeGetter_Base {

};

struct ServerTimeGetter2 : ServerTimeGetter_Base {
    /* 0x08 */ nn::os::MutexType mutex;
    /* 0x10 */ bool is_set;
    /* 0x18 */ s64 time;
}; // size >= 0x20

struct IEnsureNetworkClockAvailabilityService_Base {
    /* 0x00 */ struct IEnsureNetworkClockAvailabilityService_Base::vtable* __vftable;
    /* 0x08 */ nn::os::SystemEventType event;
    /* 0x38 */ nn::Result result1;
    /* 0x3C */ nn::Result result2;
    /* 0x40 */ ServerTimeGetter_Base* callback; // called by EnsureNetworkClockAvailabilityTask's main thread
    /* 0x48 */ Node node;
    /* 0x58 */ struct IEnsureNetworkClockAvailabilityService* service;
}; // size = 0x60

struct IEnsureNetworkClockAvailabilityService_Base::vtable {
    /* 0x00 */ void (*D1)(IEnsureNetworkClockAvailabilityService_Base*);
    /* 0x08 */ void (*D0)(IEnsureNetworkClockAvailabilityService_Base*);
    /* 0x10 */ void (*GetServerTime)(IEnsureNetworkClockAvailabilityService_Base*, s64*);
};

struct IEnsureNetworkClockAvailabilityService {
    /* 0x00 */ IEnsureNetworkClockAvailabilityService_Base base;
    /* 0x60 */ u32 client_id;
}; // size = 0x68

struct IEnsureNetworkClockAvailabilityService_Wrap {
    /* 0x00 */ struct IEnsureNetworkClockAvailabilityService::vtable* __vftable;
    /* 0x08 */ IEnsureNetworkClockAvailabilityService impl;
    /* 0x70 */ u32 heap_initialised;
    /* 0x78 */ void* heap;
}; // size = 0x80

struct IEnsureNetworkClockAvailabilityService::vtable {
    /* 0x00 */ void (*AddReference)(IEnsureNetworkClockAvailabilityService*);
    /* 0x08 */ void (*Release)(IEnsureNetworkClockAvailabilityService*);
    /* 0x10 */ void (*GetProxyInfo)(IEnsureNetworkClockAvailabilityService*);
    /* 0x18 */ void (*GetInterfaceTypeInfo)(IEnsureNetworkClockAvailabilityService*);

    /* 0x20 */ nn::Result (*StartTask)(IEnsureNetworkClockAvailabilityService*);
    /* 0x28 */ nn::Result (*GetFinishNotificationEvent)(IEnsureNetworkClockAvailabilityService*);
    /* 0x30 */ nn::Result (*GetResult)(IEnsureNetworkClockAvailabilityService*);
    /* 0x38 */ nn::Result (*Cancel)(IEnsureNetworkClockAvailabilityService*);
    /* 0x40 */ nn::Result (*IsProcessing)(IEnsureNetworkClockAvailabilityService*);
    /* 0x48 */ nn::Result (*GetServerTime)(IEnsureNetworkClockAvailabilityService*);
};

