/* A small global object and two words of a room's score (block_02034858.h). */
#include "block_02034858.h"

#include "clean.h"

static_assert(offsetof(Block021c5160, unk_0c) == 0x0c, "third row");
static_assert(sizeof(Block021c5160) == 0x14, "block size");

#define BLOCK_COLUMNS 3

/* The defaults of the second and third rows. */
extern const s16 data_020c9f0c[BLOCK_COLUMNS];
extern const s16 data_020c9f04[BLOCK_COLUMNS];

/* What func_0205b270 found scoring a room: the bits of the bonuses it gave, and the total. */
extern u32 data_021c5140;
extern u32 data_021c5144;

/* func_02034858: the second and third rows from their tables. */
void Block021c5160_SetDefaults(Block021c5160 *block)
{
    int i;

    for (i = 0; i < BLOCK_COLUMNS; i++) {
        Block021c5160_SetColumn(block, (u8) i, data_020c9f0c[i], data_020c9f04[i]);
    }
}
CLEAN_AS(func_02034858, Block021c5160_SetDefaults)

/* func_0203488c: column `index` of the second and third rows.
 * REQUIRES: index < 3. */
void Block021c5160_SetColumn(Block021c5160 *block, int index, int a, int b)
{
    block->unk_06[index] = (s16) a;
    block->unk_0c[index] = (s16) b;
}
CLEAN_AS(func_0203488c, Block021c5160_SetColumn)

/* func_02034898: everything 0. */
void Block021c5160_Clear(Block021c5160 *block)
{
    int i;

    block->unk_12 = 0;
    for (i = 0; i < BLOCK_COLUMNS; i++) {
        block->unk_0c[i] = 0;
        block->unk_06[i] = 0;
        block->unk_00[i] = 0;
    }
}
CLEAN_AS(func_02034898, Block021c5160_Clear)

/* func_020348c4: the destructor; nothing to do. */
void Block021c5160_Destroy(Block021c5160 *block)
{
    (void) block;
}
CLEAN_AS(func_020348c4, Block021c5160_Destroy)

/* func_020348c8: the constructor: cleared, then the defaults. */
void *Block021c5160_Construct(Block021c5160 *block)
{
    Block021c5160_Clear(block);
    Block021c5160_SetDefaults(block);
    return block;
}
CLEAN_AS(func_020348c8, Block021c5160_Construct)

/* func_020348e0 */
void RoomScore_SetBonusFlags(u32 flags)
{
    data_021c5140 = flags;
}
CLEAN_AS(func_020348e0, RoomScore_SetBonusFlags)

/* func_020348ec */
void RoomScore_SetTotal(u32 total)
{
    data_021c5144 = total;
}
CLEAN_AS(func_020348ec, RoomScore_SetTotal)

/* func_020348f8: called by func_020b6a2c after the frame's 3D is drawn; does nothing. */
void Block02034858_AfterDraw(void) {}
CLEAN_AS(func_020348f8, Block02034858_AfterDraw)
