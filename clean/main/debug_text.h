/* Text written straight into a background's screen map, one map entry per character: the
 * character's code added to a tile attribute (its palette bits), so the font's tiles sit at
 * the character codes. The debug screen (debug_screen.h) prints with it; its style is two
 * halfwords of which only the second, the attribute, is read. */
#ifndef CLEAN_MAIN_DEBUG_TEXT_H
#define CLEAN_MAIN_DEBUG_TEXT_H

#include "types.h"

/* A formatted text is cut to this many bytes (with its terminator). */
#define DEBUG_TEXT_MAX 0x81

void DebugText_Printf(u16 *style, short *dest, const char *format, ...);
void DebugText_Print(u16 *style, short *dest, const char *text);
void DebugText_VPrintf(short *dest, int attribute, const char *format, const void *args);
void DebugText_PutString(short *dest, int attribute, const signed char *text);
void DebugText_PutChar(short *dest, int attribute, int character);

#endif
