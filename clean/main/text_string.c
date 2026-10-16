/* Copying and converting text objects, and arrays of 16-bit characters (text_string.h). */
#include "text_string.h"

#include <string.h>

#include "clean.h"
#include "text_codes.h"

/* The width of one character in pixels: 0 for the newline and the end, else 10. */
extern int func_02051d30(int c);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern void MI_CpuFill8(void *dst, u8 value, u32 size);

/* The wide space, trimmed like the space 0x20. */
#define WIDE_SPACE 0x3000

typedef int TextCapacity(TextObject *text);
typedef void *TextBuffer(TextObject *text);

/* The text's capacity, in its own characters (vtable slot 2). */
static int capacity_of(TextObject *text)
{
    return ((TextCapacity *) (uintptr_t) text->vtable->capacity)(text);
}

/* The address of its characters (vtable slot 3). */
static void *buffer_of(TextObject *text)
{
    return ((TextBuffer *) (uintptr_t) text->vtable->buffer)(text);
}

/* func_0205182c: the wide text's characters copied into `count` 16-bit characters, the rest
 * filled with 0; whether `count` holds all its capacity. */
int TextString_CopyWideOut(TextObject *text, u16 *dst, int count)
{
    const u16 *src = buffer_of(text);
    int capacity = capacity_of(text);
    int all = count >= capacity;
    int n = all ? capacity : count;
    int i;

    for (i = 0; i < n; i++) {
        dst[i] = src[i];
    }
    for (; i < count; i++) {
        dst[i] = 0;
    }
    return all;
}
CLEAN_AS(func_0205182c, TextString_CopyWideOut)

/* func_02051880: the label's bytes decoded, two to a character, into the wide text, whose
 * remaining characters are set to 0. Returns 0 when the wide text filled up before a byte that
 * is not 0, else 1. QUIRK: that byte is the one after the last pair decoded, past the label's
 * capacity when it was used up too. */
int TextString_BytesToWide(TextObject *wide, TextObject *label)
{
    const u8 *in = buffer_of(label);
    u32 in_size = (u32) capacity_of(label);
    u16 *out = buffer_of(wide);
    u32 out_size = (u32) capacity_of(wide);
    u32 read = 0;
    u32 written = 0;
    int result = 1;

    while (read < in_size && written < out_size) {
        u16 c;
        u32 used = TextCodes_DecodeChar(&c, in);
        out[written++] = c;
        in += used;
        read += used;
    }
    if (written >= out_size && *in != 0) {
        result = 0;
    }
    while (written < out_size) {
        out[written++] = 0;
    }
    return result;
}
CLEAN_AS(func_02051880, TextString_BytesToWide)

/* func_02051908: the wide text set from `length` characters (as many as fit), the rest of it
 * set to 0; whether they all fit. */
int TextString_SetWide(TextObject *wide, const u16 *src, int length)
{
    int capacity = capacity_of(wide);
    u16 *buffer = buffer_of(wide);
    int room = capacity - length;
    int fits = room >= 0;

    if (!fits) {
        length = capacity;
    }
    MI_CpuCopy8(src, buffer, (u32) length * 2);
    if (room > 0) {
        MI_CpuFill8(buffer + length, 0, (u32) room * 2);
    }
    return fits;
}
CLEAN_AS(func_02051908, TextString_SetWide)

/* func_0205195c: every character of the wide text set to 0. */
void TextString_ClearWide(TextObject *wide)
{
    u32 size = (u32) capacity_of(wide) * 2;
    MI_CpuFill8(buffer_of(wide), 0, size);
}
CLEAN_AS(func_0205195c, TextString_ClearWide)

/* func_02051984: the wide text encoded into the label's bytes, up to its 0 or until a character
 * does not fit; the rest of the label filled with 0. A text cut short ends with a 0 in the
 * label's last byte. Returns 1 when every character up to the end fit and the label holds the
 * end, else 0. */
int TextString_WideToBytes(TextObject *label, TextObject *wide)
{
    int length = capacity_of(wide);
    const u16 *chars = buffer_of(wide);
    u8 *bytes = buffer_of(label);
    u32 size = (u32) capacity_of(label);
    u32 used = 0;
    int overflow = 0;
    int ended = 0;

    for (int i = 0; i < length; i++) {
        u8 encoded[2];
        u32 n = (u32) TextCodes_EncodeChar(encoded, chars[i]);
        if (used + n > size) {
            overflow = 1;
            break;
        }
        if (n == 1) {
            bytes[used] = encoded[0];
            ended = encoded[0] == 0;
        } else if (n == 2) {
            bytes[used] = encoded[0];
            bytes[used + 1] = encoded[1];
            ended = encoded[0] == 0 && encoded[1] == 0;
        }
        used += n;
        if (ended) {
            break;
        }
    }
    if (!overflow && used < size) {
        ended = 1;
        while (used < size) {
            bytes[used++] = 0;
        }
    }
    if (!ended) {
        bytes[size - 1] = 0;
    }
    return !overflow && ended;
}
CLEAN_AS(func_02051984, TextString_WideToBytes)

/* func_02051a78: label `dst` set from the characters of `src`. */
void TextString_CopyBytes(TextObject *dst, TextObject *src)
{
    TextString_SetBytes(dst, buffer_of(src));
}
CLEAN_AS(func_02051a78, TextString_CopyBytes)

/* func_02051a94: the label's whole capacity copied from `src`, its last byte set to 0.
 * QUIRK: the result is meant to say whether the text fit, but the last byte is tested after it
 * is set to 0, so it is always 1. */
int TextString_SetBytes(TextObject *label, const char *src)
{
    int size = capacity_of(label);
    char *buffer = buffer_of(label);

    memcpy(buffer, src, (size_t) size);
    buffer[size - 1] = 0;
    return 1;
}
CLEAN_AS(func_02051a94, TextString_SetBytes)

/* func_02051ad8: every byte of the label set to 0. */
void TextString_ClearBytes(TextObject *label)
{
    int size = capacity_of(label);
    MI_CpuFill8(buffer_of(label), 0, (u32) size);
}
CLEAN_AS(func_02051ad8, TextString_ClearBytes)

/* func_02051bb4: whether `a` and `b`, each of at most `max` characters, are equal without their
 * trailing spaces. */
int TextString_EqualTrimmed(const u16 *a, const u16 *b, int max)
{
    int length = TextString_TrimmedLength((u16 *) a, max);
    if (length != TextString_TrimmedLength((u16 *) b, max)) {
        return 0;
    }
    for (int i = 0; i < length; i++) {
        if (a[i] != b[i]) {
            return 0;
        }
    }
    return 1;
}
CLEAN_AS(func_02051bb4, TextString_EqualTrimmed)

/* func_02051bf8: `count` characters set to 0. */
void TextString_ClearChars(u16 *dst, int count)
{
    MI_CpuFill8(dst, 0, (u32) count << 1);
}
CLEAN_AS(func_02051bf8, TextString_ClearChars)

/* func_02051c08: `count` characters copied. */
void TextString_CopyChars(const u16 *src, u16 *dst, int count)
{
    MI_CpuCopy8(src, dst, (u32) count << 1);
}
CLEAN_AS(func_02051c08, TextString_CopyChars)

/* func_02051c14: how much of `text` (at most `max` characters) goes on a line `width` pixels
 * wide. `*count` gets the characters that fit; the result is a TextStringLine. The line is the
 * characters before the end or the first newline (with the newline when `newline_extra` is 1).
 * QUIRK: a line that is full or ends with a newline is found by its last character; with
 * `max` 0 that is the character before `text`. */
int TextString_FitLine(const u16 *text, int max, int width, int *count, int newline_extra)
{
    int total = 0;
    int length = TextString_LineLength((u16 *) text, max, newline_extra);

    for (int i = 0; i < length; i++) {
        total += func_02051d30(text[i]);
        if (total > width) {
            *count = i;
            return TEXT_LINE_TOO_WIDE;
        }
    }
    *count = length;
    if (length == max) {
        return text[length - 1] == TEXT_STRING_NEWLINE ? TEXT_LINE_NEWLINE : TEXT_LINE_FULL;
    }
    if (length == 0) {
        return TEXT_LINE_ENDED;
    }
    return text[length - 1] == TEXT_STRING_NEWLINE ? TEXT_LINE_NEWLINE : TEXT_LINE_ENDED;
}
CLEAN_AS(func_02051c14, TextString_FitLine)

/* func_02051c90: the index of the first 0 from `start` on, or where the search stopped at `max`.
 * QUIRK: the character at `start` is looked at even when `start` is already `max` or past it
 * (then the result is `start` + 1 unless it is 0). */
int TextString_FindEndFrom(u16 *text, int max, int unused, int start)
{
    (void) unused;
    int i = start;
    do {
        if (text[i] == 0) {
            return i;
        }
        i++;
    } while (i < max);
    return i;
}
CLEAN_AS(func_02051c90, TextString_FindEndFrom)

/* func_02051ca8: the length of `text` (at most `max` characters, ending at a 0) without its
 * trailing spaces (0x20 and the wide space 0x3000). */
int TextString_TrimmedLength(u16 *text, int max)
{
    int length = 0;
    for (int i = 0; i < max; i++) {
        if (text[i] == 0) {
            break;
        }
        if (text[i] != WIDE_SPACE && text[i] != ' ') {
            length = i + 1;
        }
    }
    return length;
}
CLEAN_AS(func_02051ca8, TextString_TrimmedLength)

/* func_02051ce0: the characters before the end (a 0) or the first newline, at most `max`; a
 * newline adds `newline_extra`. */
int TextString_LineLength(u16 *text, int max, int newline_extra)
{
    int i;
    for (i = 0; i < max; i++) {
        if (text[i] == 0) {
            return i;
        }
        if (text[i] == TEXT_STRING_NEWLINE) {
            return i + newline_extra;
        }
    }
    return i;
}
CLEAN_AS(func_02051ce0, TextString_LineLength)

/* func_02051d08: the width of `count` characters, in pixels. */
int TextString_Width(u16 *text, int count)
{
    int width = 0;
    for (int i = 0; i < count; i++) {
        width += func_02051d30(text[i]);
    }
    return width;
}
CLEAN_AS(func_02051d08, TextString_Width)
