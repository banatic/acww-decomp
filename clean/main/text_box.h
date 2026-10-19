/* The text box's own class (vtable data_020dcf28, 0x7c bytes; TextDrawBox, text_draw.h): its
 * constructors and destructors. The box a label opens (LabelBox, label_box.h) derives from it
 * (vtable data_020e3dac, 0x84 bytes; func_020a8f2c). */
#ifndef CLEAN_MAIN_TEXT_BOX_H
#define CLEAN_MAIN_TEXT_BOX_H

#include "text_draw.h"
#include "types.h"

TextDrawBox *TextBoxBase_Construct(TextDrawBox *box, int ram_dest, int cells, int rows);
void TextBoxBase_Destruct(TextDrawBox *box);
void TextBoxBase_DestructSlot(TextDrawBox *box);
void *TextBoxBase_DestructDelete(void *box);
TextDrawBox *TextBoxBase_ConstructInVram(TextDrawBox *box, u32 first_tile, u32 cells, u32 rows);

#endif
