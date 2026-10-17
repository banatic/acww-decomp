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
     * function (`this` comes first); 9-10: a floating-point result (1 float, 2 double), which
     * the PC returns in st(0); 16-31: index into native_module_names */
    uint32_t info;
} NativeFunction;

extern const NativeFunction native_functions[];
extern const uint32_t native_function_count;
/* The Clean functions that take the place of their Native ones (tools/run.py --clean), empty
 * without --clean. A Clean function on standby (CLEAN_STANDBY in `info`: registered, not
 * selected) does not run; a call to it goes on as its function would go. */
#define CLEAN_STANDBY (1u << 11)
extern const NativeFunction clean_functions[];
extern const uint32_t clean_function_count;
/* A Native function whose result is widened by a wrapper (tools/native.py): its code is in the
 * body, while the table's `host` is the wrapper. */
typedef struct NativeBody {
    const void *body;
    const void *wrapper;
} NativeBody;

extern const NativeBody native_bodies[];
extern const uint32_t native_body_count;
extern const NativeBody clean_bodies[];
extern const uint32_t clean_body_count;
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
static inline int native_floating(const NativeFunction *f)
{
    return (int) ((f->info >> 9) & 3);
}
static inline const char *native_module(const NativeFunction *f)
{
    return native_module_names[f->info >> 16];
}

#endif
