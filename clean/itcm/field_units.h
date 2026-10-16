/* The field's ground in units: blocks of 16 by 16 units laid out in a grid. Each block of the
 * current map (data_020da1a8) has a byte per unit, its type; a second kind of grid (the one
 * at data_021c80bc) keeps one bit per unit, a row of 16 units in each halfword. Unit
 * coordinates are whole units, block coordinates the unit coordinates divided by 16. */
#ifndef CLEAN_ITCM_FIELD_UNITS_H
#define CLEAN_ITCM_FIELD_UNITS_H

#include "types.h"

/* The type a unit has outside the map's blocks. */
#define UNIT_TYPE_NONE 0x15

/* A block of the map: its units' types, 16 to a row, then 16 rows. */
typedef struct FieldBlock {
    const u8 *unit_types;
    u32 unk_04;
} FieldBlock;

/* One of the maps (an array of them at data_021c31ec, 0x138 bytes each); a grid of up to 6 by
 * 6 blocks, rows of 6 whatever its width. */
typedef struct FieldBlockMap {
    FieldBlock blocks[6][6];
    u32 unk_120;
    u32 width;  /* 0x124: in blocks */
    u32 height; /* 0x128: in blocks */
    u8 unk_12C[0x138 - 0x12c];
} FieldBlockMap;

/* A block of a bit grid: a halfword per row of 16 units, bit n for the unit n units in. */
typedef struct UnitBitsBlock {
    u8 unk_00[0x24];
    const u16 *rows;
} UnitBitsBlock;

/* A grid of such blocks, row by row, `width` blocks a row. */
typedef struct UnitBitsGrid {
    UnitBitsBlock *blocks;
    int width;
} UnitBitsGrid;

u8 FieldUnits_GetType(int x, int z);
FieldBlock *FieldUnits_GetBlock(int block_x, int block_z);
int FieldUnits_IsBitSet(UnitBitsGrid *grid, int x, int z);

#endif
