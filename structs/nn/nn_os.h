typedef s64 nn::os::Tick;

// forward declarations
struct nn::os::ThreadType;

struct nn::os::detail::InternalCriticalSectionImplByHorizon {
  uint32_t image;
};

struct nn::os::detail::InternalConditionVariableImplByHorizon {
  uint32_t image;
};

struct nn::os::detail::InternalCriticalSection {
  // constructor/destructor/methods seem to be all inlined
  nn::os::detail::InternalCriticalSectionImplByHorizon impl;
};

struct nn::os::detail::InternalConditionVariable {
  // constructor/destructor/methods seem to be all inlined
  nn::os::detail::InternalConditionVariableImplByHorizon impl;
};

struct nn::os::detail::InternalCriticalSectionStorage {
  // This is a typedef of nn::util::TypedStorage<nn::os::detail::InternalCriticalSection, 4, 4>, which is a typedef of std::aligned_storage<4, 4>.
  // Used with placement new for nn::os::detail::InternalCriticalSection.
  // For simplicitly, I include the InternalCriticalSection here directly.
  nn::os::detail::InternalCriticalSection storage;
};

struct nn::os::MutexType {
  uint8_t _state;
  bool _isRecursive;
  int _lockLevel;
  int _nestCount;
  nn::os::ThreadType *_ownerThread;
  union {
    int32_t _mutexImage[1];
    nn::os::detail::InternalCriticalSectionStorage _mutex;
  };
}; // size = 0x20

struct nn::os::SdkMutexType {
  u32 mutex;
}; // size = 0x4

struct nn::os::SdkRecursiveMutexType {
  u32 mutex;
  u32 count;
}; // size = 0x8

// all wrong
struct nn::os::ThreadType {
  __int64 field_8;
  __int64 field_10;
  __int64 field_18;
  char field_20[32];
  uint32_t thread_status;
  char field_41;
  __int16 field_42;
  uint32_t thread_prio_shift;
  uint64_t thread_stack_base_addr;
  uint64_t thread_stack_base_addr_mirror;
  uint64_t thread_stack_size;
  uint64_t thread_param;
  uint64_t thread_func;
  __int64 field_70;
  __int64 field_78;
  __int64 field_80;
  char field_88[0x100];
  char thread_name[0x20];
  const char *thread_name_addr;
  nn::os::detail::InternalCriticalSection crit;
  nn::os::detail::InternalConditionVariable condvar;
  nn::svc::Handle thread_handle;
  // some sdk versions have more fields?
};

struct nn::os::ConditionVariableType {
  char field_0;
  int internal_impl;
};

struct nn::os::EventType {
  nn::os::EventType *field_0;
  nn::os::EventType *field_8;
  bool is_signalled;
  bool is_initially_signaled;
  bool should_autoclear;
  bool is_initialized;
  uint32_t signal_counter;
  uint32_t signal_counter_2;
  nn::os::detail::InternalCriticalSectionImplByHorizon crit;
  nn::os::detail::InternalConditionVariableImplByHorizon condvar;
}; // size = 0x28

struct nn::os::detail::InterProcessEventType {
  nn::os::EventType *field_0;
  nn::os::EventType *field_8;
  bool unk2;
  bool is_initially_signaled;
  bool should_autoclear;
  bool unk3;
  uint32_t readable_handle;
  uint32_t writable_handle;
  nn::os::detail::InternalCriticalSectionImplByHorizon crit;
  nn::os::detail::InternalConditionVariableImplByHorizon condvar;
}; // size = 0x28

struct nn::os::SystemEventType {
  union {
    nn::os::EventType event;
    nn::os::detail::InterProcessEventType ipe;
  };
  uint8_t state;
}; // size = 0x30


struct nn::os::TransferMemoryType {
  u8 state;
  bool allocated;
  void* address;
  size_t size;
  struct nn::sf::NativeHandle handle;
  char unk18[0x1C];
  nn::os::detail::InternalCriticalSectionStorage cs_transfer_memory;
}; // size = 0x40

struct nn::os::SharedMemoryType {
    /* 0x00 */ u8 state;
    /* 0x01 */ bool managed;
    /* 0x02 */ bool mapped;
    /* 0x08 */ void* address;
    /* 0x10 */ size_t size;
    /* 0x18 */ uint32_t handle;
    /* 0x1C */ char unk1C[0x20];
    /* 0x3C */ nn::os::detail::InternalCriticalSectionImplByHorizon crit;
}; // size = 0x40


struct nn::os::TimerEventType {
    /* 0x00 */ void* head;
    /* 0x08 */ void* tail;
    /* 0x10 */ u8 state;
    /* 0x11 */ u8 clear_mode;
    /* 0x12 */ bool signalled;
    /* 0x13 */ u8 timer_state;
    /* 0x14 */ u32 broadcast_counter_low;
    /* 0x18 */ u32 broadcast_counter_high;
    /* 0x20 */ s64 next_time_to_wakeup;
    /* 0x28 */ s64 first;
    /* 0x30 */ s64 interval;
    /* 0x38 */ nn::os::detail::InternalCriticalSectionImplByHorizon cs_timer_event;
    /* 0x3C */ nn::os::detail::InternalConditionVariableImplByHorizon cv_signaled;
}; // size = 0x40
