/* Overlay 3's search for a spot an insect settles on (insect_spot.h). */
#include "insect_spot.h"

#include "clean.h"
#include "main/acre_map.h"
#include "main/acre_tile.h"
#include "main/actor_table.h" /* Position, Position_Tile */
#include "main/town_day.h"
#include "main/town_family.h"

/* The town's map. */
extern AcreMap *data_021c80bc;
/* The 9 x 9 tiles around a tile, nearest first, each a byte: x + 8 in the high nibble, z + 8 in
 * the low. */
extern const u8 data_ov003_02236ca0[81];

#define INSECT_SPOT_AROUND 81

/* func_ov003_02224718: the day's spot (TownDay_RafflesiaPosition, from zero) in `target`; whether
 * there is one, as TownDay_RafflesiaPosition answers.
 * QUIRK: the difference to `from` is computed and its squared length in x and z (in 32 bits)
 * compared with 0x90000000 as a signed number; that can only make the answer 1, which it
 * already is. */
int InsectSpot_DaySpot(Vec3 *target, const Vec3 *from)
{
    target->x = 0;
    target->y = 0;
    target->z = 0;
    int found = TownDay_RafflesiaPosition(target);
    if (found != 0) {
        Vec3 difference;
        Vec_Subtract(&difference, target, from);
        u32 squared = (u32) difference.x * (u32) difference.x + (u32) difference.z * (u32) difference.z;
        if ((s32) squared < (s32) 0x90000000u) {
            found = 1;
        }
    }
    return found;
}
CLEAN_AS(func_ov003_02224718, InsectSpot_DaySpot)

/* Flower codes, fresh or watered (not wilted): the flower lines and the codes after them
 * (main/map_item.h). */
static int insect_spot_code_is_flower(u16 code)
{
    return code <= 0x1a || code == 0x1c || code == 0x1d || (code >= 0x8a && code <= 0xa5);
}

/* func_ov003_02224768: on the town's map (else 0), of the 9 x 9 tiles around the tile of `from`
 * (nearest first, data_ov003_02236ca0) the first holding a flower code whose kind
 * (TownFamily_Kind) has its bit set in `lines`: `target` becomes that tile's center and the
 * answer is 1; 0 when there is none. */
int InsectSpot_NearFlower(Vec3 *target, const Vec3 *from, int lines)
{
    AcreMap *map = data_021c80bc;
    if (map == NULL) {
        return 0;
    }
    int x = 0;
    int z = 0;
    Position_Tile(&x, &z, (const Position *) (const void *) from);
    for (int i = 0; i < INSECT_SPOT_AROUND; i++) {
        u8 around = data_ov003_02236ca0[i];
        int tile_x = x + ((around >> 4) - 8);
        int tile_z = z + ((around & 0xf) - 8);
        int acre_x = tile_x >> 4;
        int acre_z = tile_z >> 4;
        u16 *item = AcreTile_ItemInAcre(map, (u32) acre_x, (u32) acre_z, tile_x & 0xf, tile_z & 0xf, 0);
        if (item == NULL || !insect_spot_code_is_flower(*item)) {
            continue;
        }
        if (((lines >> TownFamily_Kind(item)) & 1) != 0) {
            AcreTile_TileCenter(target, (u32) tile_x, (u32) tile_z);
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_ov003_02224768, InsectSpot_NearFlower)
