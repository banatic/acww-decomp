/* The base class of a label's text box (text_box.h). */
#include "text_box.h"

#include "autoload_2/heap.h" /* Heap_OperatorDeleteB */
#include "clean.h"

static_assert(offsetof(TextBoxBase, text) == 0x10, "TextBoxBase text");
static_assert(offsetof(TextBoxBase, cells) == 0x20, "TextBoxBase cells");
static_assert(offsetof(TextBoxBase, font) == 0x28, "TextBoxBase font");
static_assert(offsetof(TextBoxBase, color_38) == 0x38, "TextBoxBase color_38");
static_assert(offsetof(TextBoxBase, unk_40) == 0x40, "TextBoxBase unk_40");
static_assert(offsetof(TextBoxBase, pending) == 0x54, "TextBoxBase pending");
static_assert(offsetof(TextBoxBase, cell_bytes) == 0x60, "TextBoxBase cell_bytes");
static_assert(offsetof(TextBoxBase, unk_74) == 0x74, "TextBoxBase unk_74");
static_assert(sizeof(TextBoxBase) == 0x7c, "TextBoxBase size");

extern const u8 data_020dcf28[]; /* the class's vtable */
extern const u8 data_021c8230[]; /* the font a box starts with */

extern void *func_02137550(void *dst, u32 size); /* clears size bytes */

/* func_02050cb4: the constructor. The box starts empty with the font data_021c8230, style 5,
 * colours 1 and 15, `cells` cells wide; the 8 bytes at 0x08 are copied from a buffer
 * func_02137550 cleared. Fields 0x14, 0x3e-0x3f and 0x76-0x77 are left as they were. */
TextBoxBase *TextBoxBase_Construct(TextBoxBase *box, int unk_1c, int cells, int unk_24)
{
    u32 cleared[2];

    box->vtable = data_020dcf28;
    box->unk_04 = 0;
    const u32 *zero = func_02137550(cleared, sizeof(cleared));
    box->unk_08[0] = zero[0];
    box->unk_08[1] = zero[1];
    box->text = NULL;
    box->unk_18 = -1;
    box->unk_1c = unk_1c;
    box->cells = cells;
    box->unk_24 = unk_24;
    box->font = data_021c8230;
    box->style = 5;
    box->offset = 0;
    box->unk_34 = 1;
    box->color_38 = 1;
    box->color_39 = 0xf;
    for (int i = 0; i < 4; i++) {
        box->unk_3a[i] = 0;
    }
    for (int i = 0; i < 5; i++) {
        box->unk_40[i] = 0;
    }
    box->pending = 0;
    box->unk_55 = 0;
    box->unk_56 = 0;
    box->unk_57 = 0;
    box->update_mode = 0;
    box->unk_5c = -1;
    box->cell_bytes = (u32) cells << 5;
    box->unk_64 = -1;
    for (int i = 0; i < 3; i++) {
        box->unk_68[i] = 0;
    }
    box->unk_74 = 1;
    box->unk_75 = 0;
    box->unk_78 = 0;
    return box;
}
CLEAN_AS(func_02050cb4, TextBoxBase_Construct)

/* func_02050c84: the destructor the derived classes' call: the class's vtable put back. */
void TextBoxBase_Destruct(unsigned int *box)
{
    *(const u8 **) box = data_020dcf28;
}
CLEAN_AS(func_02050c84, TextBoxBase_Destruct)

/* func_02050ca8 (vtable slot 0): the destructor, the same. */
void TextBoxBase_DestructSlot(char **box)
{
    *(const u8 **) box = data_020dcf28;
}
CLEAN_AS(func_02050ca8, TextBoxBase_DestructSlot)

/* func_02050c90 (vtable slot 1): the destructor, and the box freed (operator delete). */
void *TextBoxBase_DestructDelete(void *box)
{
    *(const u8 **) box = data_020dcf28;
    Heap_OperatorDeleteB(box);
    return box;
}
CLEAN_AS(func_02050c90, TextBoxBase_DestructDelete)
