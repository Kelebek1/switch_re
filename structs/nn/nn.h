typedef uint32_t nn::Result;
typedef uint64_t nn::TimeSpan;

// this is not an official nnSdk type, but I like to have
// it to make it easier to keep track of where PIDs are.
typedef uint64_t pid_t;

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

#include "nn_svc.h"
#include "nn_os.h"
#include "nn_sf.h"
#include "nn_lmem.h"
