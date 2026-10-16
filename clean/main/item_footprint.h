/* The cells an item covers (its footprint), from its item code: the shape its furniture data
 * gives (byte 5 of its entry, func_02053be0) and the side it faces (the code's variant,
 * func_0204bc7c). The game's table data_020dcfe0 has three shapes: one cell, two cells (in a
 * row that turns with the side) and two by two. Each lists, for each side, the cells as
 * offsets from the item's own cell. */
#ifndef CLEAN_MAIN_ITEM_FOOTPRINT_H
#define CLEAN_MAIN_ITEM_FOOTPRINT_H

#include "types.h"

#define ITEM_FOOTPRINT_SHAPES 3
#define ITEM_FOOTPRINT_SIDES 4
#define ITEM_FOOTPRINT_MAX_CELLS 4
#define ITEM_FOOTPRINT_NONE (-1) /* the shape of an item without a number */

/* A cell of a footprint, relative to the item's cell. */
typedef struct FootprintCell {
    s16 x;
    s16 y;
} FootprintCell;

/* An entry of data_020dcfe0. */
typedef struct FootprintShape {
    FootprintCell *cells[ITEM_FOOTPRINT_SIDES]; /* ITEM_FOOTPRINT_MAX_CELLS cells per side */
    u8 count;                                   /* 0x10 */
} FootprintShape;

typedef struct ItemFootprint {
    int shape; /* ITEM_FOOTPRINT_NONE or an index into data_020dcfe0 */
    int side;  /* 0-3 */
} ItemFootprint;

FootprintCell *ItemFootprint_Cell(ItemFootprint *footprint, u32 index);
u8 ItemFootprint_Count(ItemFootprint *footprint);
void ItemFootprint_Destruct(ItemFootprint *footprint);
ItemFootprint *ItemFootprint_Construct(ItemFootprint *footprint, u16 *code);

#endif
