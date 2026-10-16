/* The message texts' character codec: a 16-bit character read from or written as two bytes
 * (text_codes.h does the work). */
#ifndef CLEAN_MAIN_TEXT_CHARS_H
#define CLEAN_MAIN_TEXT_CHARS_H

#include "types.h"

unsigned short TextChars_Decode(u16 *out, const u8 *bytes);
int TextChars_Encode(unsigned char *bytes, int c);

#endif
