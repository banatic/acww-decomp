/* A spot in the middle of the town (middle_spot.h). */
#include "middle_spot.h"

#include "acre_map.h"
#include "acre_tile.h"
#include "clean.h"
#include "town_spot.h"

/* The area MiddleSpot_Pick searches: 32 x 32 tiles from the first tile of acre (2, 2). */
#define MIDDLE_SPOT_FIRST_ACRE 2
#define MIDDLE_SPOT_TILES 32

static_assert(sizeof(MiddleSpot) == 12, "part 0x0c");

/* A buffer of the main module: a row of 32 bits per tile row of the area, for the tiles
 * TownSpot_TileSuits accepts. */
extern u32 data_021d2890[MIDDLE_SPOT_TILES];

extern void MI_CpuFill8(void *dst, u8 value, u32 size);
extern u32 func_020644cc(int bound); /* a random number below `bound` */

/* func_02087f20 */
void MiddleSpot_ClearMark(MiddleSpot *spot)
{
    spot->mark = 0;
}
CLEAN_AS(func_02087f20, MiddleSpot_ClearMark)

/* func_02087f28 */
void MiddleSpot_SetMark(MiddleSpot *spot)
{
    spot->mark = 1;
}
CLEAN_AS(func_02087f28, MiddleSpot_SetMark)

/* func_02087f30 */
int MiddleSpot_HasMark(const MiddleSpot *spot)
{
    return spot->mark != 0;
}
CLEAN_AS(func_02087f30, MiddleSpot_HasMark)

/* func_02087f40: x and z into the position; its y is left alone. */
void MiddleSpot_ToPosition(const MiddleSpot *spot, Vec3 *position)
{
    position->x = spot->x;
    position->z = spot->z;
}
CLEAN_AS(func_02087f40, MiddleSpot_ToPosition)

/* func_02087f4c: x and z from the position. */
void MiddleSpot_SetFromPosition(MiddleSpot *spot, const Vec3 *position)
{
    spot->x = position->x;
    spot->z = position->z;
}
CLEAN_AS(func_02087f4c, MiddleSpot_SetFromPosition)

/* func_02087f58: with a town map, the tiles of the town's middle 32 x 32 tiles that
 * TownSpot_TileSuits accepts noted in data_021d2890 (cleared first), row by row, and one of
 * them picked at random: the spot set to its centre. The spot is left where it was when there
 * is no map or no such tile. The mark is cleared in every case. */
void MiddleSpot_Pick(MiddleSpot *spot)
{
    AcreMap *map = (AcreMap *) (uintptr_t) AcreMap_Town();
    if (map != NULL) {
        int count = 0;
        int first_x = 0;
        int first_z = 0;
        u32 *rows = data_021d2890;
        MI_CpuFill8(rows, 0, sizeof(data_021d2890));
        AcreTile_TileOfAcre(&first_x, &first_z, MIDDLE_SPOT_FIRST_ACRE, MIDDLE_SPOT_FIRST_ACRE, 0, 0);
        for (int z = 0; z < MIDDLE_SPOT_TILES; z++) {
            for (int x = 0; x < MIDDLE_SPOT_TILES; x++) {
                if (TownSpot_TileSuits(first_x + x, first_z + z, map) != 0) {
                    rows[z] |= 1u << x;
                    count++;
                }
            }
        }
        if (count > 0) {
            int pick = (int) func_020644cc(count);
            int found = 0;
            for (int z = 0; z < MIDDLE_SPOT_TILES && !found; z++) {
                for (int x = 0; x < MIDDLE_SPOT_TILES; x++) {
                    if (((rows[z] >> x) & 1) == 0) {
                        continue;
                    }
                    if (pick == 0) {
                        Vec3 centre;
                        AcreTile_TileCentre(&centre, (u32) (first_x + x), (u32) (first_z + z));
                        MiddleSpot_SetFromPosition(spot, &centre);
                        found = 1;
                        break;
                    }
                    pick--;
                }
            }
        }
    }
    spot->mark = 0;
}
CLEAN_AS(func_02087f58, MiddleSpot_Pick)

/* func_02088198: x, z and the mark cleared. */
void MiddleSpot_Clear(MiddleSpot *spot)
{
    spot->x = 0;
    spot->z = 0;
    spot->mark = 0;
}
CLEAN_AS(func_02088198, MiddleSpot_Clear)

/* func_020881a4: the constructor does nothing. */
void MiddleSpot_Construct(MiddleSpot *spot)
{
    (void) spot;
}
CLEAN_AS(func_020881a4, MiddleSpot_Construct)

/* func_020881a8: the destructor does nothing. */
void MiddleSpot_Destruct(MiddleSpot *spot)
{
    (void) spot;
}
CLEAN_AS(func_020881a8, MiddleSpot_Destruct)
