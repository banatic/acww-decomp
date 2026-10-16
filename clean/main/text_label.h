/* Two text classes of main, and the text box a label draws through.
 *
 * Both classes derive from a text base whose vtable has four entries: the destructor, the
 * deleting destructor, the capacity in characters and the address of the characters.
 *
 * - A wide text (vtable data_020e1784, 0x60 bytes) holds up to 41 16-bit characters. Functions
 *   use one on the stack to convert between a label's 8-bit text and arrays of 16-bit
 *   characters (func_020a87e0 converts 8-bit to 16-bit, func_020a8a70 the other way).
 * - A label (vtable data_020e179c, 0x6c bytes) holds up to 84 8-bit characters and owns a text
 *   box (0x84 bytes, allocated by func_020a8fe8 or func_020a9034 and freed by func_020a8fb8)
 *   that shows them: it gives the box its characters, places them and asks for a redraw. Its
 *   text comes from the game's message archives (func_020b4980 reads archive "2d_menu" when
 *   given none, func_020b4a20 a named one). */
#ifndef CLEAN_MAIN_TEXT_LABEL_H
#define CLEAN_MAIN_TEXT_LABEL_H

#include "types.h"

#define WIDE_TEXT_CAPACITY 41
#define TEXT_LABEL_CAPACITY 84

/* The entries of a text vtable, as DS addresses. */
typedef struct TextVtable {
    u32 destruct;        /* returns the object */
    u32 destruct_delete; /* destructs and frees the object */
    u32 capacity;        /* int (void *self) */
    u32 buffer;          /* char *(void *self): the characters */
} TextVtable;

typedef struct WideText {
    const TextVtable *vtable; /* data_020e1784 */
    u8 base_04[0xa];          /* the text base's */
    u16 text[WIDE_TEXT_CAPACITY];
} WideText;

/* What a label's text box holds that the label sets (func_02050cb4 / func_02050d6c construct
 * it). */
typedef struct TextBox {
    const void *vtable;
    u8 unk_04[0xc];
    const char *text; /* 0x10: the characters it shows */
    u8 unk_14[0xc];
    u32 cells; /* 0x20: its width in 8-pixel cells */
    u32 unk_24;
    const void *font; /* 0x28: data_021c8230 when constructed */
    s32 style;        /* 0x2c: func_02002dc8 of the label's style */
    u32 offset;       /* 0x30: where the text starts, in pixels */
    u8 unk_34[4];
    u8 color_38;
    u8 color_39;
    u8 unk_3a[0x16];
    u32 unk_50; /* 2 for the styles func_02002e04 accepts, else 1 */
    u8 pending; /* 0x54: set by func_02051694, cleared once drawn */
    u8 unk_55;  /* 1 when the style is 4 */
    u8 unk_56;
    u8 unk_57;
    u32 update_mode; /* 0x58: func_02051694 draws at once when 2 */
} TextBox;

typedef struct TextLabel {
    const TextVtable *vtable; /* data_020e179c */
    u8 base_04[0xe];          /* the text base's */
    char text[TEXT_LABEL_CAPACITY];
    u8 unk_66[2];
    TextBox *box; /* 0x68, or NULL */
} TextLabel;

int WideText_Length(WideText *text);
int WideText_Buffer(int text);
int WideText_Capacity(void);
WideText *WideText_DestructDelete(WideText *text);
void *WideText_Destruct(void *text);
void *WideText_Construct(void *text);
int TextLabel_EqualsTrimmed(TextLabel *label, const u16 *text, u16 length);
void TextLabel_SetBoxParams(TextLabel *label, int a, int b, int c, int d);
void TextLabel_SetFromWideConverted(TextLabel *label, const u16 *text, int length, int escape_newlines, u8 end_code);
void TextLabel_CopyWide(void *label, u16 *out);
void TextLabel_SetFromWide(void *label, const u16 *text, void *length);
int TextLabel_Compose(int label, int a, int b, int kind, int extra, u8 raw);
void TextLabel_LoadMessage(int label, char *archive, char number);
int TextLabel_LoadMenuMessage(int label, char number);
int TextLabel_LoadMenuMessageAt(int label, int number);
int TextLabel_TextWidth(void *label);
void TextLabel_ShowAt(TextLabel *label, int offset);
void TextLabel_ShowRightAligned(TextLabel *label);
void TextLabel_ShowShifted(TextLabel *label, int center, int shift);
void TextLabel_Show(TextLabel *label, int center, int flag_57);
void TextLabel_OpenBox(TextLabel *label, int a, int b, int color_38, u8 color_39);
void TextLabel_OpenStyledBox(TextLabel *label, int style, int a, int b, u8 color_38, u8 color_39, int unused);
void TextLabel_OpenStyledBox2(TextLabel *label, int style, int a, int b, u8 color_38, u8 color_39, int other_font);
void TextLabel_SetStyle(TextLabel *label, int style, char color_38, char color_39);
void TextLabel_CloseBox(void *label);
int TextLabel_Buffer(int label);
int TextLabel_Capacity(void);
TextLabel *TextLabel_DestructCopy(TextLabel *label);
TextLabel *TextLabel_DestructDelete(TextLabel *label);
TextLabel *TextLabel_Destruct(TextLabel *label);
TextLabel *TextLabel_Construct(TextLabel *label);
TextLabel *TextLabel_ConstructCopy(TextLabel *label);

#endif
