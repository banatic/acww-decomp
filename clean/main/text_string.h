/* Copying and converting the game's text objects (the wide texts and labels of text_label.h,
 * reached through their vtable's capacity and buffer entries), and small functions over arrays
 * of 16-bit characters: trimmed lengths, line lengths and widths.
 *
 * A label's 8-bit text holds each 16-bit character as two bytes, little-endian
 * (TextCodes_DecodeChar, TextCodes_EncodeChar). A text's width counts 10 pixels for each
 * character except the newline (10) and the 0 that ends it (func_02051d30). */
#ifndef CLEAN_MAIN_TEXT_STRING_H
#define CLEAN_MAIN_TEXT_STRING_H

#include "text_label.h"
#include "types.h"

#define TEXT_STRING_NEWLINE 10

/* A wide text or a label, seen through its vtable. */
typedef struct TextObject {
    const TextVtable *vtable;
} TextObject;

/* What TextString_FitLine found. */
enum TextStringLine {
    TEXT_LINE_ENDED = 0,    /* the text ended before the line was full */
    TEXT_LINE_TOO_WIDE = 1, /* the characters do not fit the width */
    TEXT_LINE_FULL = 2,     /* the line has all the characters allowed */
    TEXT_LINE_NEWLINE = 3,  /* the line ends with a newline */
};

int TextString_CopyWideOut(TextObject *text, u16 *dst, int count);
int TextString_BytesToWide(TextObject *wide, TextObject *label);
int TextString_SetWide(TextObject *wide, const u16 *src, int length);
void TextString_ClearWide(TextObject *wide);
int TextString_WideToBytes(TextObject *label, TextObject *wide);
void TextString_CopyBytes(TextObject *dst, TextObject *src);
int TextString_SetBytes(TextObject *label, const char *src);
void TextString_ClearBytes(TextObject *label);
int TextString_EqualTrimmed(const u16 *a, const u16 *b, int max);
void TextString_ClearChars(u16 *dst, int count);
void TextString_CopyChars(const u16 *src, u16 *dst, int count);
int TextString_FitLine(const u16 *text, int max, int width, int *count, int newline_extra);
int TextString_FindEndFrom(u16 *text, int max, int unused, int start);
int TextString_TrimmedLength(u16 *text, int max);
int TextString_LineLength(u16 *text, int max, int newline_extra);
int TextString_Width(u16 *text, int count);

#endif
