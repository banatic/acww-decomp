/* The cells an item covers (item_footprint.h). */
#include "item_footprint.h"

#include "clean.h"

static_assert(offsetof(FootprintShape, count) == 0x10, "FootprintShape count");
static_assert(sizeof(ItemFootprint) == 8, "ItemFootprint size");

extern FootprintShape *data_020dcfe0[ITEM_FOOTPRINT_SHAPES];

/* A function-local static of the original: the cell (0, 0), built on first use (bit 0 of its
 * guard). */
extern u32 data_021c8744;
extern FootprintCell data_021c8748;

extern int func_0204bc64(u16 *code); /* the code's item number, or -1 */
extern u8 func_02053be0(int number); /* byte 5 of the furniture's data: its shape */
extern int func_0204bc7c(u16 *code); /* the side the code's variant faces (0-3) */

/* Entry `shape` of the table, read as the ROM does: a shape below 0 reads the words before it.
 * The address is formed as an integer so that no array is indexed out of its bounds. */
static FootprintShape *shape_entry(int shape)
{
    return *(FootprintShape *const *) ((uintptr_t) data_020dcfe0 + (uintptr_t) ((u32) shape * 4));
}

/* The list of cells for `side`, likewise read unchecked. */
static FootprintCell *side_cells(const FootprintShape *shape, int side)
{
    return *(FootprintCell *const *) ((uintptr_t) shape->cells + (uintptr_t) ((u32) side * 4));
}

/* func_02052dc0: the footprint's cell `index`; past the last cell, or for a footprint without a
 * shape from the table, the cell (0, 0) of a static.
 * QUIRK: only the low two bits of `index` pick the cell. */
FootprintCell *ItemFootprint_Cell(ItemFootprint *footprint, u32 index)
{
    if (footprint->shape < ITEM_FOOTPRINT_SHAPES && index < ItemFootprint_Count(footprint)) {
        return &side_cells(shape_entry(footprint->shape), footprint->side)[index & 3];
    }
    if ((data_021c8744 & 1) == 0) {
        data_021c8748.x = 0;
        data_021c8748.y = 0;
        data_021c8744 |= 1;
    }
    return &data_021c8748;
}
CLEAN_AS(func_02052dc0, ItemFootprint_Cell)

/* func_02052e20: the number of cells, 0 for a shape not in the table.
 * QUIRK: ITEM_FOOTPRINT_NONE (below 0) is not caught: it reads the count through the word
 * before the table. */
u8 ItemFootprint_Count(ItemFootprint *footprint)
{
    if (footprint->shape < ITEM_FOOTPRINT_SHAPES) {
        return shape_entry(footprint->shape)->count;
    }
    return 0;
}
CLEAN_AS(func_02052e20, ItemFootprint_Count)

/* func_02052e38: nothing to take down. */
void ItemFootprint_Destruct(ItemFootprint *footprint)
{
    (void) footprint;
}
CLEAN_AS(func_02052e38, ItemFootprint_Destruct)

/* func_02052e3c: the footprint of the item `code` holds: ITEM_FOOTPRINT_NONE (and the side
 * left as it was) for a code without an item number. */
ItemFootprint *ItemFootprint_Construct(ItemFootprint *footprint, u16 *code)
{
    footprint->shape = ITEM_FOOTPRINT_NONE;
    int number = func_0204bc64(code);
    if (number != -1) {
        footprint->shape = func_02053be0(number);
        footprint->side = func_0204bc7c(code);
    }
    return footprint;
}
CLEAN_AS(func_02052e3c, ItemFootprint_Construct)
