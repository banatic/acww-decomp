/* The Native functions, as tools/native.py describes them (build/adm-kr/native/natives.s). */
#ifndef RUNTIME_NATIVE_TABLE_H
#define RUNTIME_NATIVE_TABLE_H

#include <stdint.h>

enum NativeReturn {
    NATIVE_RET_VOID,
    NATIVE_RET_U8,
    NATIVE_RET_S8,
    NATIVE_RET_U16,
    NATIVE_RET_S16,
    NATIVE_RET_32,
    NATIVE_RET_64,
    NATIVE_RET_SKIP /* not compared: floating point, or a structure returned by value */
};

typedef struct NativeFunction {
    uint32_t address; /* DS address, bit 0 set for Thumb */
    uint32_t size;
    const void *host; /* the compiled function */
    /* bits 0-3: enum NativeReturn; 4-7: parameters (not counting `this`); 8: a C++ member
     * function (`this` comes first); 16-31: index into native_module_names */
    uint32_t info;
} NativeFunction;

extern const NativeFunction native_functions[];
extern const uint32_t native_function_count;
/* A function's own static data in the ROM: writes there are its private state. */
typedef struct NativePrivate {
    uint32_t function; /* DS address, bit 0 clear */
    uint32_t start, end;
} NativePrivate;

extern const NativePrivate native_private[];
extern const uint32_t native_private_count;
extern const char *const native_module_names[];
extern const uint32_t native_module_count;

static inline int native_return(const NativeFunction *f)
{
    return (int) (f->info & 15);
}
static inline int native_params(const NativeFunction *f)
{
    return (int) ((f->info >> 4) & 15);
}
static inline int native_member(const NativeFunction *f)
{
    return (int) ((f->info >> 8) & 1);
}
static inline const char *native_module(const NativeFunction *f)
{
    return native_module_names[f->info >> 16];
}

#endif
