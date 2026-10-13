#ifndef TYPES_H
#define TYPES_H

// Basic types, with the names and definitions NitroSDK uses.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef unsigned long long u64;

typedef signed char s8;
typedef signed short s16;
typedef signed long s32;
typedef signed long long s64;

typedef volatile u8 vu8;
typedef volatile u16 vu16;
typedef volatile u32 vu32;
typedef volatile u64 vu64;

typedef volatile s8 vs8;
typedef volatile s16 vs16;
typedef volatile s32 vs32;
typedef volatile s64 vs64;

typedef float f32;
typedef volatile f32 vf32;

typedef int BOOL;
#define TRUE 1
#define FALSE 0

#ifndef NULL
#ifdef __cplusplus
#define NULL 0
#else
#define NULL ((void *) 0)
#endif
#endif

// Fixed-point numbers (fx32 is 20.12, fx16 is 4.12).
typedef s16 fx16;
typedef s32 fx32;
typedef s64 fx64;
typedef s64 fx64c;

#endif // TYPES_H
