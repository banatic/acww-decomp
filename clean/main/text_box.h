/* The base class of a label's text box (the C++ class with vtable data_020dcf28, 0x7c bytes):
 * its constructor and destructors. The box a label opens (TextBox, text_label.h) derives from
 * it (vtable data_020e3dac, 0x84 bytes; func_020a8f2c). */
#ifndef CLEAN_MAIN_TEXT_BOX_H
#define CLEAN_MAIN_TEXT_BOX_H

#include "types.h"

typedef struct TextBoxBase {
    const void *vtable;
    u32 unk_04;
    u32 unk_08[2];
    const char *text; /* 0x10: the characters it shows */
    u32 unk_14;
    s32 unk_18;
    s32 unk_1c;
    s32 cells; /* 0x20: its width in 8-pixel cells */
    s32 unk_24;
    const void *font; /* 0x28 */
    s32 style;
    u32 offset; /* 0x30: where the text starts, in pixels */
    u32 unk_34;
    u8 color_38;
    u8 color_39;
    u8 unk_3a[4];
    u8 pad_3e[2];
    u32 unk_40[5];
    u8 pending; /* 0x54 */
    u8 unk_55;
    u8 unk_56;
    u8 unk_57;
    u32 update_mode; /* 0x58 */
    s32 unk_5c;
    u32 cell_bytes; /* 0x60: 32 bytes for each cell */
    s32 unk_64;
    u32 unk_68[3];
    u8 unk_74;
    u8 unk_75;
    u8 pad_76[2];
    u32 unk_78;
} TextBoxBase;

TextBoxBase *TextBoxBase_Construct(TextBoxBase *box, int unk_1c, int cells, int unk_24);
void TextBoxBase_Destruct(unsigned int *box);
void TextBoxBase_DestructSlot(char **box);
void *TextBoxBase_DestructDelete(void *box);
TextBoxBase *TextBoxBase_ConstructInVram(TextBoxBase *box, u32 first_tile, u32 cells, u32 rows);

#endif
