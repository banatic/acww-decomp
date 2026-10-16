/* The two text bases of main: the classes the wide texts and the labels of text_label.h (and
 * the message parts of message_receiver.h) derive from, and what is done with their texts.
 *
 * Both have the four vtable entries of a text (TextVtable: destructor, deleting destructor,
 * capacity, characters) and carry a text's attributes (MessageAttributes of message_decoder.h,
 * class data_020e3d24: func_020a9b50 builds them, func_020a9b44 destroys them, func_020a9b04
 * resets them, func_020a9b1c copies them). They derive in turn from an abstract text class
 * whose vtable is data_020da6c4 (wide) or data_020da6dc (8-bit).
 *
 * - The wide text base (vtable data_020e3d7c): 16-bit characters, the attributes at 0x04.
 * - The 8-bit text base (vtable data_020e3d94): 8-bit characters, each 16-bit character of the
 *   game written as two bytes (TextChars_Encode); `length` counts the bytes set so far, the
 *   attributes are at 0x08.
 *
 * An 8-bit text is set from a message text by walking it with the text copier
 * (TextCopier, text_walker.h) to its end, or to its first newline for TextBase_SetLine. */
#ifndef CLEAN_MAIN_TEXT_BASE_H
#define CLEAN_MAIN_TEXT_BASE_H

#include "text_label.h"
#include "types.h"

/* The bytes of a text's attributes the bases hold. */
#define TEXT_BASE_ATTRIBUTES_SIZE 0x0a

typedef struct WideTextBase {
    const TextVtable *vtable;                 /* 0x00: data_020e3d7c, or a derived class's */
    u8 attributes[TEXT_BASE_ATTRIBUTES_SIZE]; /* 0x04 */
} WideTextBase;

typedef struct TextBase {
    const TextVtable *vtable;                 /* 0x00: data_020e3d94, or a derived class's */
    u32 length;                               /* 0x04: the bytes set */
    u8 attributes[TEXT_BASE_ATTRIBUTES_SIZE]; /* 0x08 */
} TextBase;

int TextBase_BytesToWide(WideTextBase *dst, TextBase *src);
void TextBase_SetWide(void *dst, const void *chars, int count);
void *TextBase_WideDestruct(void *text);
void *TextBase_WideDelete(WideTextBase *text);
void *TextBase_WideDestructSlot(WideTextBase *text);
void *TextBase_WideConstruct(void *text);
int TextBase_AppendRange(TextBase *text, int start, int end);
unsigned char TextBase_SetRange(TextBase *text, unsigned int start, unsigned int end);
int TextBase_Equals(TextBase *a, TextBase *b);
int TextBase_AppendText(void *dst, TextBase *src);
int TextBase_AppendChars(TextBase *text, const char *chars);
int TextBase_SetLine(TextBase *text, const char *chars);
int TextBase_WideToBytes(TextBase *dst, WideTextBase *src, int escape_newlines, int end_code);
void *TextBase_Copy(TextBase *dst, TextBase *src);
int TextBase_SetChars(TextBase *text, const char *chars);
void TextBase_Clear(void *text);
TextBase *TextBase_Destruct(TextBase *text);
void *TextBase_Delete(void *text);
TextBase *TextBase_DestructSlot(TextBase *text);
void *TextBase_Construct(void *text);

#endif
