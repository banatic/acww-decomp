/* Text written into a screen map (debug_text.h). */
#include "debug_text.h"

#include <stdarg.h>

#include "clean.h"

extern int OS_VSNPrintf(char *dest, u32 size, const char *format, const void *args);

/* func_020b97b4: `format` with its arguments, at `dest` with the style's attribute.
 * REQUIRES: a va_list that is the address of the arguments in memory (the ARM's, and the
 * 32-bit x86 one's), as DebugText_VPrintf hands it to OS_VSNPrintf. */
void DebugText_Printf(u16 *style, short *dest, const char *format, ...)
{
    va_list args;

    va_start(args, format);
    DebugText_VPrintf(dest, style[1], format, (const void *) args);
    va_end(args);
}
CLEAN_AS(func_020b97b4, DebugText_Printf)

/* func_020b97d4: `text` at `dest` with the style's attribute. */
void DebugText_Print(u16 *style, short *dest, const char *text)
{
    DebugText_PutString(dest, style[1], (const signed char *) text);
}
CLEAN_AS(func_020b97d4, DebugText_Print)

/* func_020b97e4: `format` with `args` formatted (at most 0x80 characters), then written. */
void DebugText_VPrintf(short *dest, int attribute, const char *format, const void *args)
{
    char text[DEBUG_TEXT_MAX];

    OS_VSNPrintf(text, DEBUG_TEXT_MAX, format, args);
    DebugText_PutString(dest, attribute, (const signed char *) text);
}
CLEAN_AS(func_020b97e4, DebugText_VPrintf)

/* func_020b9808: each character of `text` into the next map entry.
 * QUIRK: the characters are signed, so one of 0x80 or more takes from the attribute. */
void DebugText_PutString(short *dest, int attribute, const signed char *text)
{
    for (; *text != 0; text++, dest++) {
        DebugText_PutChar(dest, attribute, *text);
    }
}
CLEAN_AS(func_020b9808, DebugText_PutString)

/* func_020b9834: one map entry: the attribute plus the character, cut to 16 bits. */
void DebugText_PutChar(short *dest, int attribute, int character)
{
    *dest = (short) (attribute + character);
}
CLEAN_AS(func_020b9834, DebugText_PutChar)
