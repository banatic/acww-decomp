/* Questions about one tile of the town's map (town_tile.h). */
#include "town_tile.h"

#include "clean.h"

#define ACRE_TILES 16 /* an acre is 16 x 16 tiles */
#define PLAYERS 4

extern void *data_021c80bc; /* the town's map; null while there is none */
extern u8 data_020e54a8;    /* 0 or 1, a mode many scenes test */

/* The tile's object on `layer` of the map, or null. */
extern u16 *func_0204f5e0(void *map, int acre_x, int acre_z, int x, int z, int layer);
/* The tile a position is on. */
extern void func_0204f818(int *x, int *z, const int *position);
/* Whether the map takes the tile (its own test, func_02031af0, made with the map's 0x1c). */
extern int func_0204ee20(void *map, int x, int z);
extern int func_0204bd08(u16 *object); /* a code of kind 1 (ItemCode_IsKind1) */
extern int func_0204bcdc(u16 *object); /* a code of kind 3 or 4 (ItemCode_HasVariant) */
/* The first stage of a growth line: 0x26, 0x2f, 0x37, 0x3f, 0x47, 0x4f, 0x57, 0x5d or 0xc8. */
extern int func_0204ba94(u16 *object);
/* The position of player `slot` (an actor's 0x6f4), or 0 when the slot has no player. */
extern int func_02095794(int slot);
extern int func_02096190(int slot); /* what stands for player `slot` */
/* What of the game's actor table (data_021d1d4c) stands on the tile, or 0. */
extern int func_0208259c(int x, int z);

/* The acre a tile coordinate is in, rounded down for negative coordinates as the ARM's
 * arithmetic shift does. The tile within the acre is then the low four bits. */
static int acre_of(int tile)
{
    return tile >= 0 ? tile / ACRE_TILES : -1 - (-1 - tile) / ACRE_TILES;
}

static u16 *object_at(void *map, int x, int z, int layer)
{
    return func_0204f5e0(map, acre_of(x), acre_of(z), x & (ACRE_TILES - 1), z & (ACRE_TILES - 1), layer);
}

/* func_02078dd4: TownTile_FindItem5000Above from the tile `position` is on. */
int TownTile_FindItem5000AboveAt(const Vec3 *position, int rows, int *out_x, int *out_z)
{
    int x = 0;
    int z = 0;

    func_0204f818(&x, &z, (const int *) position);
    return TownTile_FindItem5000Above(x, z, rows, out_x, out_z);
}
CLEAN_AS(func_02078dd4, TownTile_FindItem5000AboveAt)

/* func_02078e08: whether one of the `rows` + 1 tiles above (x, z) (z - 1, z - 2, ...), nearest
 * first, holds an object 0x5000-0x5021 on the map's layer 0. The first such tile goes to
 * (*out_x, *out_z) when both pointers are given. 0 without a map or for negative `rows`. */
int TownTile_FindItem5000Above(int x, int z, int rows, int *out_x, int *out_z)
{
    void *map = data_021c80bc;

    if (map == NULL || rows < 0) {
        return 0;
    }
    for (int i = 0; i <= rows; i++) {
        int row = z - (i + 1);
        u16 *object = object_at(map, x, row, 0);

        if (object != NULL && *object >= TOWN_TILE_ITEM_5000_FIRST && *object <= TOWN_TILE_ITEM_5000_LAST) {
            if (out_x != NULL && out_z != NULL) {
                *out_x = x;
                *out_z = row;
            }
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_02078e08, TownTile_FindItem5000Above)

/* func_02078e98: TownTile_IsClear on the tile `position` is on. */
int TownTile_IsClearAt(const Vec3 *position, void *map)
{
    int x = 0;
    int z = 0;

    func_0204f818(&x, &z, (const int *) position);
    return TownTile_IsClear(x, z, map);
}
CLEAN_AS(func_02078e98, TownTile_IsClearAt)

/* The plain object codes TownTile_IsClear also lets through (map_item.h): family A and the codes
 * after it (0x00-0x1a, 0x1c, 0x1d), family C and the codes after it (0x8a-0xa5), and 0x25,
 * 0x5c and 0xc7. */
static int is_open_code(u16 code)
{
    return code <= 0x1a || code == 0x1c || code == 0x1d || (code >= 0x8a && code <= 0xa5) || code == 0x25 || code == 0x5c ||
           code == 0xc7;
}

/* func_02078ec0: whether tile (x, z) of `map` (the town's map when null) is taken by the map,
 * holds nothing or an object that does not stand in the way, and has no one on it.
 *
 * The objects that do not stand in the way: nothing (0xfff1), codes of kind 1, 0xa7-0xc6, codes
 * of kinds 3 and 4 only while data_020e54a8 is 0, the first stage of a growth line, and the plain
 * codes of is_open_code. They are asked in that order, each test called only when the ones
 * before it failed. */
int TownTile_IsClear(int x, int z, void *map)
{
    u16 *object;
    int open;

    if (map == NULL) {
        map = data_021c80bc;
    }
    if (map == NULL || func_0204ee20(map, x, z) == 0) {
        return 0;
    }
    object = object_at(map, x, z, 0);
    if (object == NULL) {
        return 0;
    }
    open = *object == 0xfff1 || func_0204bd08(object) != 0 || (*object >= 0xa7 && *object <= 0xc6) ||
           (data_020e54a8 == 0 && func_0204bcdc(object) != 0) || func_0204ba94(object) != 0 || is_open_code(*object);
    if (!open) {
        return 0;
    }
    return TownTile_Occupant(x, z) == 0;
}
CLEAN_AS(func_02078ec0, TownTile_IsClear)

/* func_0207903c: what stands on tile (x, z): a player (TownTile_PlayerOccupant), else an actor
 * of the game's actor table; 0 when nothing does. */
int TownTile_Occupant(int x, int z)
{
    int occupant = TownTile_PlayerOccupant(x, z);

    if (occupant == 0) {
        return func_0208259c(x, z);
    }
    return occupant;
}
CLEAN_AS(func_0207903c, TownTile_Occupant)

/* func_0207905c: what func_02096190 gives for the first of the four player slots whose player
 * is on tile (x, z), or 0. */
int TownTile_PlayerOccupant(int x, int z)
{
    for (int slot = 0; slot < PLAYERS; slot++) {
        int position = func_02095794(slot);

        if (position != 0) {
            int tile_x = 0;
            int tile_z = 0;

            func_0204f818(&tile_x, &tile_z, (const int *) (uintptr_t) position);
            if (tile_x == x && tile_z == z) {
                return func_02096190(slot);
            }
        }
    }
    return 0;
}
CLEAN_AS(func_0207905c, TownTile_PlayerOccupant)
