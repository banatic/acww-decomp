/* The message texts' character codec (text_chars.h). */
#include "text_chars.h"

#include "clean.h"
#include "text_codes.h"

/* func_020a7984: a character from two bytes; the bytes it took (2). */
unsigned short TextChars_Decode(u16 *out, const u8 *bytes)
{
    return TextCodes_DecodeChar(out, bytes);
}
CLEAN_AS(func_020a7984, TextChars_Decode)

/* func_020a798c: a character as two bytes; the bytes it wrote (2). */
int TextChars_Encode(unsigned char *bytes, int c)
{
    return TextCodes_EncodeChar(bytes, c);
}
CLEAN_AS(func_020a798c, TextChars_Encode)
