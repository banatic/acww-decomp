/* Small wrappers over C library functions (c_library.h). */
#include "c_library.h"

#include <stdarg.h>
#include <string.h>

#include "clean.h"

extern int OS_VSNPrintf(char *dest, u32 size, const char *format, const void *args);

/* The size CLib_VSPrintf gives: no limit. */
#define C_LIBRARY_UNLIMITED 0x7fffffff

/* func_02064300: `format` with `args` into `buffer`, at most `size` bytes. */
int CLib_VSNPrintf(char *buffer, u32 size, const char *format, const void *args)
{
    return OS_VSNPrintf(buffer, size, format, args);
}
CLEAN_AS(func_02064300, CLib_VSNPrintf)

/* func_02064310: `format` with `args` into `buffer`, without a limit. */
int CLib_VSPrintf(char *buffer, const char *format, const void *args)
{
    return CLib_VSNPrintf(buffer, C_LIBRARY_UNLIMITED, format, args);
}
CLEAN_AS(func_02064310, CLib_VSPrintf)

/* func_02064328: sprintf.
 * REQUIRES: a va_list that is the address of the arguments in memory (the ARM's, and the
 * 32-bit x86 one's), as CLib_VSPrintf hands it to OS_VSNPrintf. */
int CLib_SPrintf(char *buffer, const char *format, ...)
{
    va_list args;

    va_start(args, format);
    int written = CLib_VSPrintf(buffer, format, (const void *) args);
    va_end(args);
    return written;
}
CLEAN_AS(func_02064328, CLib_SPrintf)

/* func_02064344: 1 when the `size` bytes at `a` and `b` differ, else 0. */
int CLib_BytesDiffer(const void *a, const void *b, unsigned int size)
{
    return memcmp(a, b, size) != 0;
}
CLEAN_AS(func_02064344, CLib_BytesDiffer)
