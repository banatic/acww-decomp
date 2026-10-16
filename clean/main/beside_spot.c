/* A spot beside a requested position (beside_spot.h). */
#include "beside_spot.h"

#include "acre_tile.h"
#include "clean.h"
#include "item_1568_count.h"

/* The count of item 0x1568 that makes the actor face the request's position. */
#define BESIDE_SPOT_ITEM_1568_FACE 5
#define BESIDE_SPOT_SIDES 3

/* Per side: the offset from the request's position (two tiles to +z, -x, +x) and the angle
 * that faces back to it (0x8000, 0x4000, 0xc000).
 * QUIRK: the side has two bits but only 0-2 are picked; a side of 3 would read the words that
 * follow each table. */
extern const BesideSpotOffset data_020d06ec[];
extern const s16 data_020d06e4[];
/* The count of item 0x1568 (item_1568_count.h). */
extern u8 data_021ebcd2[];

extern void MI_CpuFill8(void *dst, u8 value, u32 size);
extern u32 func_020644cc(int bound); /* a random number below `bound` */

static int beside_spot_side(const u8 *spot)
{
    return (*spot & BESIDE_SPOT_SIDE_MASK) >> BESIDE_SPOT_SIDE_SHIFT;
}

/* func_02087a78: the side and the facing picked if they were not yet; the position set to the
 * centre of the tile at the side's offset from the request's position (at height 0), and the
 * angle: facing the request's position once 5 of item 0x1568 were counted, else 0 when the
 * count has its mark, else the quarter turn picked. */
void BesideSpot_Place(u8 *spot, Vec3 *position, u16 *angle_y, const SpawnerRequest *request)
{
    if ((*spot & BESIDE_SPOT_CHOSEN) == 0) {
        BesideSpot_Choose(spot);
    }
    const BesideSpotOffset *offset = &data_020d06ec[beside_spot_side(spot)];
    Vec3 beside = {request->position.x + offset->x, 0, request->position.z + offset->z};
    AcreTile_SnapToTileCentre(position, &beside);

    if (Item1568Count_Get(data_021ebcd2) >= BESIDE_SPOT_ITEM_1568_FACE) {
        *angle_y = (u16) data_020d06e4[beside_spot_side(spot)];
    } else if (Item1568Count_HasMark(data_021ebcd2) != 0) {
        *angle_y = 0;
    } else {
        *angle_y = (u16) (((*spot & BESIDE_SPOT_FACING_MASK) >> BESIDE_SPOT_FACING_SHIFT) << 14);
    }
}
CLEAN_AS(func_02087a78, BesideSpot_Place)

/* func_02087b04 */
void BesideSpot_SetServed(u8 *spot)
{
    *spot |= BESIDE_SPOT_SERVED;
}
CLEAN_AS(func_02087b04, BesideSpot_SetServed)

/* func_02087b10 */
void BesideSpot_ClearServed(u8 *spot)
{
    *spot = (u8) (*spot & ~BESIDE_SPOT_SERVED);
}
CLEAN_AS(func_02087b10, BesideSpot_ClearServed)

/* func_02087b1c */
int BesideSpot_WasServed(const u8 *spot)
{
    return (*spot & BESIDE_SPOT_SERVED) != 0;
}
CLEAN_AS(func_02087b1c, BesideSpot_WasServed)

/* func_02087b30: a side (0-2) and a quarter turn (0-3) picked at random, in that order, each
 * stored as it is drawn; then the spot marked chosen. */
void BesideSpot_Choose(u8 *spot)
{
    u32 side = func_020644cc(BESIDE_SPOT_SIDES) & 3;
    *spot = (u8) ((*spot & ~BESIDE_SPOT_SIDE_MASK) | (side << BESIDE_SPOT_SIDE_SHIFT));
    u32 facing = func_020644cc(4) & 3;
    *spot = (u8) ((*spot & ~BESIDE_SPOT_FACING_MASK) | (facing << BESIDE_SPOT_FACING_SHIFT));
    *spot |= BESIDE_SPOT_CHOSEN;
}
CLEAN_AS(func_02087b30, BesideSpot_Choose)

/* func_02087b78 */
void BesideSpot_Clear(u8 *spot)
{
    MI_CpuFill8(spot, 0, 1);
}
CLEAN_AS(func_02087b78, BesideSpot_Clear)

/* func_02087b84: the constructor does nothing. */
void BesideSpot_Construct(u8 *spot)
{
    (void) spot;
}
CLEAN_AS(func_02087b84, BesideSpot_Construct)

/* func_02087b88: the destructor does nothing. */
void BesideSpot_Destruct(u8 *spot)
{
    (void) spot;
}
CLEAN_AS(func_02087b88, BesideSpot_Destruct)
