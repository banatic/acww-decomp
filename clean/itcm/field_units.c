/* The field's ground in units (field_units.h). */
#include "field_units.h"

#include <assert.h>
#include <stddef.h>
#include <stdint.h>

#include "clean.h"

static_assert(sizeof(FieldBlock) == 8, "a block's entry");
static_assert(offsetof(FieldBlockMap, width) == 0x124, "the map's width");
static_assert(offsetof(FieldBlockMap, height) == 0x128, "the map's height");
static_assert(sizeof(FieldBlockMap) == 0x138, "a map");
static_assert(offsetof(UnitBitsBlock, rows) == 0x24, "the block's rows of bits");
static_assert(sizeof(UnitBitsBlock) == 0x28, "a bit grid's block");

/* The current map. */
extern FieldBlockMap *data_020da1a8;

/* func_01ffcb2c: the type of the unit at (`x`, `z`) in the current map, UNIT_TYPE_NONE outside
 * its blocks. */
u8 FieldUnits_GetType(int x, int z)
{
    FieldBlock *block = FieldUnits_GetBlock(x >> 4, z >> 4);
    if (block == NULL) {
        return UNIT_TYPE_NONE;
    }
    return block->unit_types[(x & 0xf) + ((z & 0xf) << 4)];
}
CLEAN_AS(func_01ffcb2c, FieldUnits_GetType)

/* func_01ffcb5c: the current map's block at (`block_x`, `block_z`); NULL outside its width and
 * height. QUIRK: the place is found in rows of 6 blocks whatever the width; the address is
 * computed as the ARM does, in 32 bits, for a width or height above 6 too. */
FieldBlock *FieldUnits_GetBlock(int block_x, int block_z)
{
    FieldBlockMap *map = data_020da1a8;
    if (block_x < 0 || block_z < 0 || (u32) block_x >= map->width || (u32) block_z >= map->height) {
        return NULL;
    }
    u32 offset = (u32) block_z * sizeof(map->blocks[0]) + (u32) block_x * sizeof(FieldBlock);
    return (FieldBlock *) ((uintptr_t) map + offset);
}
CLEAN_AS(func_01ffcb5c, FieldUnits_GetBlock)

/* func_01ffcbd8: whether the bit of the unit at (`x`, `z`) is set in `grid`.
 * REQUIRES: (`x`, `z`) is in the grid; nothing is checked (the address is computed as the ARM
 * does, in 32 bits). */
int FieldUnits_IsBitSet(UnitBitsGrid *grid, int x, int z)
{
    u32 index = (u32) (z >> 4) * (u32) grid->width + (u32) (x >> 4);
    const UnitBitsBlock *block = (const UnitBitsBlock *) ((uintptr_t) grid->blocks + index * sizeof(UnitBitsBlock));
    return (block->rows[z & 0xf] & (1u << (x & 0xf))) != 0;
}
CLEAN_AS(func_01ffcbd8, FieldUnits_IsBitSet)
