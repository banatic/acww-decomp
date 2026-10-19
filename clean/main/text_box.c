/* The base class of a label's text box (text_box.h). */
#include "text_box.h"

#include "autoload_2/heap.h" /* Heap_OperatorDeleteB */
#include "clean.h"

static_assert(offsetof(TextDrawBox, text) == 0x10, "box text");
static_assert(offsetof(TextDrawBox, cells) == 0x20, "box cells");
static_assert(offsetof(TextDrawBox, font) == 0x28, "box font");
static_assert(offsetof(TextDrawBox, color) == 0x38, "box colour");
static_assert(offsetof(TextDrawBox, marks) == 0x40, "box marks");
static_assert(offsetof(TextDrawBox, screens) == 0x50, "box screens");
static_assert(offsetof(TextDrawBox, pending) == 0x54, "box pending");
static_assert(offsetof(TextDrawBox, row_bytes) == 0x60, "box row bytes");
static_assert(offsetof(TextDrawBox, start_color) == 0x74, "box start colour");
static_assert(sizeof(TextDrawBox) == 0x7c, "box size");

extern const u32 data_020dcf28[]; /* the class's vtable */
extern TextFont data_021c8230;    /* the font a box starts with */

extern void *func_02137550(void *dst, u32 size); /* clears size bytes */

/* func_02050cb4: the constructor of a box drawn into RAM at `ram_dest`. The box starts empty
 * with the font data_021c8230, layer 5, colours 1 and 15, `cells` tiles wide and `rows` high;
 * the 8 bytes at 0x08 are copied from a buffer func_02137550 cleared. Fields 0x14, 0x3e-0x3f
 * and 0x76-0x77 are left as they were. */
TextDrawBox *TextBoxBase_Construct(TextDrawBox *box, int ram_dest, int cells, int rows)
{
    u32 cleared[2];

    box->vtable = data_020dcf28;
    box->unk_04 = 0;
    const u32 *zero = func_02137550(cleared, sizeof(cleared));
    box->link[0] = zero[0];
    box->link[1] = zero[1];
    box->text = NULL;
    box->first_tile = -1;
    box->ram_dest = (u32) ram_dest;
    box->cells = (u32) cells;
    box->rows = (u32) rows;
    box->font = &data_021c8230;
    box->layer = 5;
    box->offset = 0;
    box->spacing = 1;
    box->color = 1;
    box->background = 0xf;
    for (int i = 0; i < 2; i++) {
        box->mark_colors[i].color = 0;
        box->mark_colors[i].background = 0;
    }
    for (int i = 0; i < 2; i++) {
        box->marks[i].first = 0;
        box->marks[i].count = 0;
    }
    box->screens = TEXT_DRAW_TO_RAM;
    box->pending = 0;
    box->rows_full_width = 0;
    box->merge = 0;
    box->underline = 0;
    box->update_mode = TEXT_DRAW_GROUP_0;
    box->clear_cells = -1;
    box->row_bytes = (u32) cells << 5;
    box->glyph = -1;
    box->pen = 0;
    box->strip_y = 0;
    box->dest_offset = 0;
    box->start_color = 1;
    box->last_strip = 0;
    box->char_index = 0;
    return box;
}
CLEAN_AS(func_02050cb4, TextBoxBase_Construct)

/* func_02050c84: the destructor the derived classes' call: the class's vtable put back. */
void TextBoxBase_Destruct(TextDrawBox *box)
{
    box->vtable = data_020dcf28;
}
CLEAN_AS(func_02050c84, TextBoxBase_Destruct)

/* func_02050ca8 (vtable slot 0): the destructor, the same. */
void TextBoxBase_DestructSlot(TextDrawBox *box)
{
    box->vtable = data_020dcf28;
}
CLEAN_AS(func_02050ca8, TextBoxBase_DestructSlot)

/* func_02050c90 (vtable slot 1): the destructor, and the box freed (operator delete). */
void *TextBoxBase_DestructDelete(void *box)
{
    ((TextDrawBox *) box)->vtable = data_020dcf28;
    Heap_OperatorDeleteB(box);
    return box;
}
CLEAN_AS(func_02050c90, TextBoxBase_DestructDelete)

/* func_02050d6c: the constructor of a box drawn into VRAM: `rows` tiles high and `cells` wide,
 * from tile `first_tile` of BG2's tiles on the sub screen, with no RAM destination; otherwise
 * as TextBoxBase_Construct. */
TextDrawBox *TextBoxBase_ConstructInVram(TextDrawBox *box, u32 first_tile, u32 cells, u32 rows)
{
    u32 cleared[2];

    box->vtable = data_020dcf28;
    box->unk_04 = 0;
    const u32 *zero = func_02137550(cleared, sizeof(cleared));
    box->link[0] = zero[0];
    box->link[1] = zero[1];
    box->text = NULL;
    box->first_tile = (s32) first_tile;
    box->ram_dest = 0;
    box->cells = cells;
    box->rows = rows;
    box->font = &data_021c8230;
    box->layer = 2;
    box->offset = 0;
    box->spacing = 1;
    box->color = 1;
    box->background = 0xf;
    for (int i = 0; i < 2; i++) {
        box->mark_colors[i].color = 0;
        box->mark_colors[i].background = 0;
    }
    for (int i = 0; i < 2; i++) {
        box->marks[i].first = 0;
        box->marks[i].count = 0;
    }
    box->screens = TEXT_DRAW_TO_SUB;
    box->pending = 0;
    box->rows_full_width = 0;
    box->merge = 0;
    box->underline = 0;
    box->update_mode = TEXT_DRAW_GROUP_0;
    box->clear_cells = -1;
    box->row_bytes = cells << 5;
    box->glyph = -1;
    box->pen = 0;
    box->strip_y = 0;
    box->dest_offset = 0;
    box->start_color = 1;
    box->last_strip = 0;
    box->char_index = 0;
    return box;
}
CLEAN_AS(func_02050d6c, TextBoxBase_ConstructInVram)
