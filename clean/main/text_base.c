/* The text bases and their texts (text_base.h). */
#include "text_base.h"

#include <string.h>

#include "autoload_2/heap.h" /* Heap_OperatorDeleteB */
#include "clean.h"
#include "text_chars.h"
#include "text_codes.h"
#include "text_string.h"
#include "text_walker.h"

static_assert(offsetof(WideTextBase, attributes) == 0x04, "wide text base attributes");
static_assert(offsetof(TextBase, length) == 0x04, "text base length");
static_assert(offsetof(TextBase, attributes) == 0x08, "text base attributes");

/* The bytes TextChars_Encode writes at most, and room for the codes' one-character texts. */
#define TEXT_BASE_CODE_BYTES 8

extern const u8 data_020e3d7c[]; /* the wide text base's vtable */
extern const u8 data_020da6c4[]; /* the abstract wide text's */
extern const u8 data_020e3d94[]; /* the 8-bit text base's vtable */
extern const u8 data_020da6dc[]; /* the abstract 8-bit text's */

/* The game's text copier. */
extern TextCopier data_021f450c;

/* A text's attributes: destroyed, built, reset, copied from another's. */
extern void func_020a9b44(void *attributes);
extern void func_020a9b50(void *attributes);
extern void func_020a9b04(void *attributes);
extern void func_020a9b1c(void *dst, const void *src);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

typedef int TextBaseCapacity(void *text);
typedef void *TextBaseBuffer(void *text);

/* A text's capacity, in its own characters (vtable slot 2). */
static int text_base_capacity(void *text)
{
    const TextVtable *vtable = *(const TextVtable *const *) text;
    return ((TextBaseCapacity *) (uintptr_t) vtable->capacity)(text);
}

/* The address of its characters (vtable slot 3). */
static void *text_base_buffer(void *text)
{
    const TextVtable *vtable = *(const TextVtable *const *) text;
    return ((TextBaseBuffer *) (uintptr_t) vtable->buffer)(text);
}

/* The copier run over `chars` into `text` (TextCopier_Start's arguments), its result. */
static int text_base_copy_from(TextBase *text, const char *chars, int mode, u8 stop_at_newline)
{
    TextCopier_Start(&data_021f450c, text, (int) (uintptr_t) chars, mode, stop_at_newline);
    TextWalker_RunTo(&data_021f450c.walker, 0);
    int fitted = TextCopier_Fitted(&data_021f450c);
    TextCopier_Reset(&data_021f450c);
    return fitted;
}

/* ---- Wide texts */

/* func_020a87e0: the 8-bit text's characters (all its capacity, two bytes each) converted into
 * the wide text, the rest of it filled with 0, and its attributes copied; 0 when the wide
 * text filled up before a 0 byte of the source. */
int TextBase_BytesToWide(WideTextBase *dst, TextBase *src)
{
    const u8 *from = text_base_buffer(src);
    u32 from_size = (u32) text_base_capacity(src);
    u16 *to = text_base_buffer(dst);
    u32 to_count = (u32) text_base_capacity(dst);
    u32 read = 0;
    u32 written = 0;
    int ok = 1;

    while (read < from_size && written < to_count) {
        u16 character;
        int size = TextChars_Decode(&character, from);
        *to++ = character;
        written++;
        from += size;
        read += (u32) size;
    }
    if (written >= to_count && *from != 0) {
        ok = 0;
    }
    while (written < to_count) {
        *to++ = 0;
        written++;
    }
    func_020a9b1c(dst->attributes, src->attributes);
    return ok;
}
CLEAN_AS(func_020a87e0, TextBase_BytesToWide)

/* func_020a8874: the wide text set from `count` 16-bit characters. */
void TextBase_SetWide(void *dst, const void *chars, int count)
{
    TextString_SetWide(dst, chars, count);
}
CLEAN_AS(func_020a8874, TextBase_SetWide)

/* func_020a887c: the destructor the derived classes call. */
void *TextBase_WideDestruct(void *text)
{
    WideTextBase *wide = text;
    wide->vtable = (const TextVtable *) data_020e3d7c;
    func_020a9b44(wide->attributes);
    wide->vtable = (const TextVtable *) data_020da6c4;
    return text;
}
CLEAN_AS(func_020a887c, TextBase_WideDestruct)

/* func_020a88a0 (vtable slot 1): destructs and frees. */
void *TextBase_WideDelete(WideTextBase *text)
{
    text->vtable = (const TextVtable *) data_020e3d7c;
    func_020a9b44(text->attributes);
    text->vtable = (const TextVtable *) data_020da6c4;
    Heap_OperatorDeleteB(text);
    return text;
}
CLEAN_AS(func_020a88a0, TextBase_WideDelete)

/* func_020a88c8 (vtable slot 0): the destructor, the same as TextBase_WideDestruct. */
void *TextBase_WideDestructSlot(WideTextBase *text)
{
    text->vtable = (const TextVtable *) data_020e3d7c;
    func_020a9b44(text->attributes);
    text->vtable = (const TextVtable *) data_020da6c4;
    return text;
}
CLEAN_AS(func_020a88c8, TextBase_WideDestructSlot)

/* func_020a88ec: the constructor (the abstract class's vtable, then its own). */
void *TextBase_WideConstruct(void *text)
{
    WideTextBase *wide = text;
    wide->vtable = (const TextVtable *) data_020da6c4;
    wide->vtable = (const TextVtable *) data_020e3d7c;
    func_020a9b50(wide->attributes);
    return text;
}
CLEAN_AS(func_020a88ec, TextBase_WideConstruct)

/* ---- 8-bit texts */

/* func_020a8910: the bytes from `start` to `end` appended to the text; whether they fitted
 * with a byte to spare (for its 0), else as many as leave that byte are.
 * QUIRK: the sizes are compared unsigned, so a full text (no byte to spare) appends
 * 0xffffffff bytes. */
int TextBase_AppendRange(TextBase *text, int start, int end)
{
    u8 *chars = text_base_buffer(text);
    int capacity = text_base_capacity(text);
    u8 *at = chars + text->length;
    u32 room = (u32) capacity - text->length;
    u32 count = (u32) end - (u32) start;
    int fitted = count + 1 <= room;

    if (!fitted) {
        count = room - 1;
    }
    MI_CpuCopy8((const void *) (uintptr_t) start, at, count);
    text->length += count;
    return fitted;
}
CLEAN_AS(func_020a8910, TextBase_AppendRange)

/* func_020a895c: the text emptied, then set to the bytes from `start` to `end`; whether they
 * fitted with a byte to spare, else as many as leave that byte are. */
unsigned char TextBase_SetRange(TextBase *text, unsigned int start, unsigned int end)
{
    TextBase_Clear(text);
    u8 *chars = text_base_buffer(text);
    u32 capacity = (u32) text_base_capacity(text);
    u32 count = end - start;
    int fitted = count + 1 <= capacity;

    text->length = fitted ? count : capacity - 1;
    MI_CpuCopy8((const void *) (uintptr_t) start, chars, text->length);
    return (unsigned char) fitted;
}
CLEAN_AS(func_020a895c, TextBase_SetRange)

/* func_020a89ac: whether the two texts' characters are the same (to their 0). */
int TextBase_Equals(TextBase *a, TextBase *b)
{
    const char *b_chars = text_base_buffer(b);
    const char *a_chars = text_base_buffer(a);
    return strcmp(a_chars, b_chars) == 0;
}
CLEAN_AS(func_020a89ac, TextBase_Equals)

/* func_020a89dc: another text's characters appended. */
int TextBase_AppendText(void *dst, TextBase *src)
{
    return TextBase_AppendChars(dst, text_base_buffer(src));
}
CLEAN_AS(func_020a89dc, TextBase_AppendText)

/* func_020a89f8: the characters of a message text appended, to its end; whether they fitted. */
int TextBase_AppendChars(TextBase *text, const char *chars)
{
    return text_base_copy_from(text, chars, TEXT_COPIER_APPEND, 0);
}
CLEAN_AS(func_020a89f8, TextBase_AppendChars)

/* func_020a8a34: the text set to the first line of a message text (up to its newline or its
 * end); whether it fitted. */
int TextBase_SetLine(TextBase *text, const char *chars)
{
    return text_base_copy_from(text, chars, TEXT_COPIER_SET, 1);
}
CLEAN_AS(func_020a8a34, TextBase_SetLine)

/* func_020a8a70: the wide text's characters converted into the 8-bit text, two bytes each, up
 * to its first 0; the rest of the text filled with 0 and the attributes copied. With
 * `escape_newlines` each newline is written as the newline code's text (TextCodes_NewlineCode),
 * with `end_code` the end as the end code's (TextCodes_EndCode). Whether it all fitted with
 * its end; when it did not, the text's last byte is set to 0. */
int TextBase_WideToBytes(TextBase *dst, WideTextBase *src, int escape_newlines, int end_code)
{
    char code[TEXT_BASE_CODE_BYTES];
    int count = text_base_capacity(src);
    const u16 *from = text_base_buffer(src);
    char *chars = text_base_buffer(dst);
    u32 capacity = (u32) text_base_capacity(dst);
    u32 used = 0;
    int over = 0;
    int ended = 0;

    for (int i = 0; i < count; i++, from++) {
        char *at = chars + used;
        u32 size = (u32) TextChars_Encode((unsigned char *) code, *from);
        if (used + size > capacity) {
            over = 1;
        }
        if (!over) {
            if (code[0] == 0 && code[1] == 0) {
                ended = 1;
                if (end_code) {
                    strcpy(code, (const char *) (uintptr_t) TextCodes_EndCode());
                    size = (u32) strlen(code);
                    if (used + size > capacity) {
                        over = 1;
                    }
                }
            } else if (escape_newlines && code[0] == TEXT_STRING_NEWLINE && code[1] == 0) {
                strcpy(code, (const char *) (uintptr_t) TextCodes_NewlineCode());
                size = (u32) strlen(code);
                if (used + size > capacity) {
                    over = 1;
                }
            }
            if (!over) {
                for (u32 j = 0; j < size; j++) {
                    at[j] = code[j];
                }
            }
        }
        if (over) {
            break;
        }
        used += size;
        if (ended) {
            break;
        }
    }
    if (!over && used < capacity) {
        ended = 1;
        while (used < capacity) {
            chars[used++] = 0;
        }
    }
    if (!ended) {
        chars[capacity - 1] = 0;
    }
    func_020a9b1c(dst->attributes, src->attributes);
    return !over && ended;
}
CLEAN_AS(func_020a8a70, TextBase_WideToBytes)

/* func_020a8bb8: the text set to another's characters, and its attributes copied; whether the
 * characters fitted (1 or 0, as a pointer-sized value). */
void *TextBase_Copy(TextBase *dst, TextBase *src)
{
    int fitted = TextBase_SetChars(dst, text_base_buffer(src));
    func_020a9b1c(dst->attributes, src->attributes);
    return (void *) (uintptr_t) (unsigned int) fitted;
}
CLEAN_AS(func_020a8bb8, TextBase_Copy)

/* func_020a8be4: the text set to a message text, to its end; whether it fitted. */
int TextBase_SetChars(TextBase *text, const char *chars)
{
    return text_base_copy_from(text, chars, TEXT_COPIER_SET, 0);
}
CLEAN_AS(func_020a8be4, TextBase_SetChars)

/* func_020a8c1c: all the characters set to 0, nothing set, the attributes reset. */
void TextBase_Clear(void *text)
{
    TextBase *base = text;
    TextString_ClearBytes(text);
    base->length = 0;
    func_020a9b04(base->attributes);
}
CLEAN_AS(func_020a8c1c, TextBase_Clear)

/* func_020a8c38: the destructor the derived classes call. */
TextBase *TextBase_Destruct(TextBase *text)
{
    text->vtable = (const TextVtable *) data_020e3d94;
    func_020a9b44(text->attributes);
    text->vtable = (const TextVtable *) data_020da6dc;
    return text;
}
CLEAN_AS(func_020a8c38, TextBase_Destruct)

/* func_020a8c5c (vtable slot 1): destructs and frees. */
void *TextBase_Delete(void *text)
{
    TextBase *base = text;
    base->vtable = (const TextVtable *) data_020e3d94;
    func_020a9b44(base->attributes);
    base->vtable = (const TextVtable *) data_020da6dc;
    Heap_OperatorDeleteB(text);
    return text;
}
CLEAN_AS(func_020a8c5c, TextBase_Delete)

/* func_020a8c88 (vtable slot 0): the destructor, the same as TextBase_Destruct. */
TextBase *TextBase_DestructSlot(TextBase *text)
{
    text->vtable = (const TextVtable *) data_020e3d94;
    func_020a9b44(text->attributes);
    text->vtable = (const TextVtable *) data_020da6dc;
    return text;
}
CLEAN_AS(func_020a8c88, TextBase_DestructSlot)

/* func_020a8cac: the constructor (the abstract class's vtable, then its own); nothing set. The
 * characters are left as they are. */
void *TextBase_Construct(void *text)
{
    TextBase *base = text;
    base->vtable = (const TextVtable *) data_020da6dc;
    base->vtable = (const TextVtable *) data_020e3d94;
    base->length = 0;
    func_020a9b50(base->attributes);
    return text;
}
CLEAN_AS(func_020a8cac, TextBase_Construct)
