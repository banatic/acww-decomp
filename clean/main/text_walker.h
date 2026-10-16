/* Walkers of message texts (MessageWalker, message_cursor.h) that hand what they meet to
 * another object, and the walkers built on them.
 *
 * - A text walker (class data_020e3de4, 0x2c bytes) has a handler and a flag that makes a
 *   newline end the text like its 0 (TextWalker_RunTo passes it to each step,
 *   func_020a9368).
 * - The text copier (class data_020e3e04, 0x3c bytes; the game's one is data_021f450c) walks
 *   a message text to its end, then sets or appends the bytes it walked into an 8-bit text
 *   (text_base.h) and keeps whether they fitted.
 * - The box walker (class data_020e3dc4, 0x30 bytes; the game's default is data_021f44dc)
 *   walks a label box's text for drawing or measuring (label_box.h): each character goes to
 *   the box, tags 0/x put one of the fixed one-character texts in their place, 2/x tags skip
 *   the texts they carry, and a 0xff/2 tag can replace the characters after it with its own. */
#ifndef CLEAN_MAIN_TEXT_WALKER_H
#define CLEAN_MAIN_TEXT_WALKER_H

#include "message_cursor.h"
#include "text_base.h"
#include "types.h"

typedef struct TextWalker {
    MessageWalker base;
    void *handler;      /* 0x24: the label box walked for, or NULL */
    u8 stop_at_newline; /* 0x28 */
    u8 unk_29[3];
} TextWalker;

/* What the text copier does with the bytes it walked. */
enum TextCopierMode {
    TEXT_COPIER_SET = 0,
    TEXT_COPIER_APPEND = 1,
};

typedef struct TextCopier {
    TextWalker walker;
    TextBase *target; /* 0x2c: the text set, or NULL */
    u32 source;       /* 0x30: the address of the message text walked */
    s32 mode;         /* 0x34: enum TextCopierMode */
    u8 fitted;        /* 0x38: whether all the bytes fitted */
    u8 unk_39[3];
} TextCopier;

typedef struct BoxWalker {
    TextWalker walker;
    u32 return_at; /* 0x2c: where a 0xff/2 tag's own text ends, or 0 */
} BoxWalker;

void TextCopier_OnEnd(TextCopier *copier);
unsigned char TextCopier_Fitted(TextCopier *copier);
void TextCopier_Reset(TextCopier *copier);
void TextCopier_Start(TextCopier *copier, TextBase *target, int source, int mode, unsigned char stop_at_newline);
void *TextCopier_Delete(TextCopier *copier);
void *TextCopier_Destruct(void *copier);
TextCopier *TextCopier_Construct(TextCopier *copier);

void BoxWalker_OnTag(BoxWalker *walker, int position);
void BoxWalker_OnCharacter(BoxWalker *walker, int character);
void BoxWalker_OnEnd(void *walker);
void BoxWalker_OnText(void *walker);
void *BoxWalker_Delete(void *walker);
void *BoxWalker_Destruct(void *walker);
BoxWalker *BoxWalker_Construct(BoxWalker *walker);

void TextWalker_StopAtNewlineOff(TextWalker *walker);
void TextWalker_StopAtNewlineOn(TextWalker *walker);
void TextWalker_ClearHandler(TextWalker *walker);
void TextWalker_SetHandler(TextWalker *walker, void *handler);
int TextWalker_RunTo(TextWalker *walker, int end);
void *TextWalker_Destruct(void *walker);
void *TextWalker_Delete(void *walker);
TextWalker *TextWalker_DestructSlot(TextWalker *walker);
TextWalker *TextWalker_Construct(TextWalker *walker, char stop_at_newline);
int TextWalker_Run(MessageWalker *walker, int end);

#endif
