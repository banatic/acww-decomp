/* Small wrappers of main over C library functions: formatting into a buffer (NitroSDK's
 * OS_VSNPrintf), the game's sprintf, and a byte comparison. */
#ifndef CLEAN_MAIN_C_LIBRARY_H
#define CLEAN_MAIN_C_LIBRARY_H

#include "types.h"

int CLib_VSNPrintf(char *buffer, u32 size, const char *format, const void *args);
int CLib_VSPrintf(char *buffer, const char *format, const void *args);
int CLib_SPrintf(char *buffer, const char *format, ...);
int CLib_BytesDiffer(const void *a, const void *b, unsigned int size);

#endif
