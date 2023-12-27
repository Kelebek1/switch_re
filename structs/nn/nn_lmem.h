struct nn::lmem::detail::HeapHead {
    uint magic;
    __int64 field_8;
    __int64 field_10;
    __int64 field_18;
    __int64 field_20;
    __int64 field_28;
    void *heap_start;
    void *heap_end;
    nn::os::SdkMutexType mutex;
    char option;
    __int64 impl;
    __int64 field_70;
    __int64 field_78;
    __int64 field_80;
    __int64 field_88;
};

struct nn::lmem::detail::HeapHead_Wrap {
    /* 0x00 */ nn::lmem::detail::HeapHead* heapHead;
    /* 0x08 */ s64 size;
}; // size = 0x10

struct nn::err::detail::ExpHeapBase::vtable {
    /* 0x00 */ void (*D1)();
    /* 0x08 */ void (*D0)();
    /* 0x10 */ void (*do_allocate)();
    /* 0x18 */ void (*do_deallocate)();
    /* 0x20 */ void (*is_equal)();
};
