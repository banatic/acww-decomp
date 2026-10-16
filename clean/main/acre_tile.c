/* The tiles and acres of a map of acres (acre_tile.h). */
#include "acre_tile.h"

#include "clean.h"
#include "main/session.h"

/* The session (Session_IsLinked). */
extern NetSession *data_020ccf94;
/* The snowmen's records, handed to func_020b0650. */
extern u8 data_021f3b56[];

/* Makes entry `slot` of the table at data_021c31ec the current map of units (0 is the
 * default one). */
extern void func_02030e4c(int slot);
/* What the current map of units says of the unit at (x, z): the unit's type (func_01ffcb2c)
 * looked up in the table of 0x1e-byte records at data_020c907c. */
extern int func_02030a18(int x, int z); /* rewrites the unit's type: 3 to 0x1d, 9 to 0x1e, others by the table */
extern int func_02031a08(int x, int z); /* the unit's path directions, four bits */
extern int func_02031aa0(int x, int z); /* the halfword at 6: 1 when above 0; -1 outside the table */
extern u8 func_02031acc(int x, int z);  /* the byte at 9; 2 outside the table */
extern int func_02031a74(int x, int z); /* whether the byte at 0x17 is set */
extern int func_02031b14(int x, int z); /* the byte at 8 */
extern int func_02031af0(int x, int z); /* the byte at 5 */
extern u8 func_02031b38(int x, int z);  /* the byte at 4 */
/* The tile a position is on (Position_Tile). */
extern void func_0204f818(int *x, int *z, const Vec3 *position);

/* An acre record's parts. */
extern u16 *func_02037e0c(u8 *acre, int x, int z, u8 layer);           /* the code of tile (x, z) in a layer, or 0 */
extern int func_02037e44(u8 *acre, u16 *code, int x, int z, u8 layer); /* sets it; 0 without one */
extern int func_02037d2c(u8 *acre, int x, int z);                      /* clears the tile's bit */
extern int func_02037d48(u8 *acre, int x, int z);                      /* sets the tile's bit */
extern int func_02037d64(u8 *acre, int flags);                         /* whether the acre has any of the flags */
extern int func_02037d80(u8 *acre, int flags);                         /* whether it has all of them */
extern int func_02037d9c(u8 *acre);                                    /* its model's flags */
/* Searches the acre's layer for a code in [*first, *last]: the tile to (*x, *z). */
extern int func_02037da8(u8 *acre, int *x, int *z, u16 *first, u16 *last, u8 layer);

/* Item codes (item_code.h, map_item.h, snowman.c). */
extern int func_0204bd08(u16 *code); /* a code of kind 1 */
extern int func_0204bcdc(u16 *code); /* a code with a variant */
extern int func_0204bc64(u16 *code); /* a code's item without its variant */
extern int func_0204ba94(u16 *code); /* the first stage of a growth line */
extern int func_0204b5ac(u16 *code); /* the stage of a short line's code, or -1 */
extern int func_0204bb54(u16 *code); /* a snowman's map object */
extern int func_0204bb2c(u16 *code); /* the snowman's number */
/* Removes snowman `number`'s record when it is in use. */
extern int func_020b0650(u8 *records, unsigned int number);
/* Adds an item to the list of fifteen replaced items. */
extern void func_0203a76c(u16 code);

/* A building's shape (func_020b3b50): two lists of tiles given as offsets from the building's
 * tile; an entry at offset (0, 0) is skipped. */
extern void *func_020b3b50(u16 *building);
extern unsigned int func_020b3eb8(void *shape); /* the number of tiles the building covers */
extern int func_020b3e08(void *shape, int *x, int *z, unsigned int index);
extern unsigned int func_020b3f2c(void *shape); /* the number of tiles of the second list */
extern int func_020b3e58(void *shape, int *x, int *z, unsigned int index);

/* The object that takes the buildings put down while it exists (overlay 3), or 0. */
extern int func_020b3b14(void);
extern int func_ov003_02220460(int handler, int building, int x, int z, int unk);

/* Rounding down as the ARM's arithmetic shift does. */
static int acre_tile_shift(int value, int bits)
{
    return value >= 0 ? value >> bits : ~(~value >> bits);
}

/* The acre of a tile, and the tile within its acre. */
static int acre_tile_acre_of(int tile)
{
    return acre_tile_shift(tile, 4);
}

static int acre_tile_offset_of(int tile)
{
    return tile - acre_tile_acre_of(tile) * 16;
}

/* The acre (x, z) of the map, or 0 outside it or when it has none. */
static u8 *acre_tile_acre_at(const AcreMap *map, u32 x, u32 z)
{
    if (x < (u32) map->acres_wide && z < (u32) map->acres_high && map->acres != NULL) {
        return map->acres + ACRE_MAP_ACRE_SIZE * (x + z * (u32) map->acres_wide);
    }
    return NULL;
}

/* The code of tile (x, z) of the map, layer 0. */
static u16 *acre_tile_item(AcreMap *map, int x, int z)
{
    return AcreTile_ItemInAcre(map, (u32) acre_tile_acre_of(x), (u32) acre_tile_acre_of(z), acre_tile_offset_of(x),
                               acre_tile_offset_of(z), 0);
}

static int acre_tile_is_building(u16 code)
{
    return code >= ACRE_TILE_BUILDING_FIRST && code <= ACRE_TILE_BUILDING_LAST;
}

/* func_0204eb1c: puts building `building` down at (x, z) (AcreTile_StampBuilding) and adds
 * the code the tile held to the list of replaced items when it is of kind 1 or has a variant;
 * 1 when the building went down. With `to_handler` set and the object of overlay 3 present,
 * the building goes to that object instead (func_ov003_02220460) and its answer is returned.
 * QUIRK: AcreTile_PutBuilding has added that code to the list already, so it goes in twice. */
int AcreTile_StampBuildingNoting(AcreMap *map, u16 *building, int x, int z, u8 to_handler)
{
    u16 *tile = acre_tile_item(map, x, z);
    u16 replaced = ACRE_MAP_ITEM_NONE;

    if (tile != NULL) {
        replaced = *tile;
    }
    if (to_handler != 0 && func_020b3b14() != 0) {
        return func_ov003_02220460(func_020b3b14(), (int) (uintptr_t) building, x, z, 1);
    }
    if (AcreTile_StampBuilding(map, building, x, z) == 0) {
        return 0;
    }
    if (func_0204bd08(&replaced) || func_0204bcdc(&replaced)) {
        func_0203a76c(replaced);
    }
    return 1;
}
CLEAN_AS(func_0204eb1c, AcreTile_StampBuildingNoting)

/* ---- what the map's slot says of a unit: each question is asked with the map's slot made
 * the current map of units, and the default one (0) made current again after ---- */

/* func_0204ed08 */
int AcreTile_RetypeUnit(AcreMap *map, int x, int z)
{
    func_02030e4c(map->slot);
    int result = func_02030a18(x, z);
    func_02030e4c(0);
    return result;
}
CLEAN_AS(func_0204ed08, AcreTile_RetypeUnit)

/* func_0204ed30: the path directions of the tile a position is on. */
int AcreTile_PathDirectionsAt(AcreMap *map, const Vec3 *position)
{
    int x = 0;
    int z = 0;

    func_0204f818(&x, &z, position);
    return AcreTile_PathDirections(map, x, z);
}
CLEAN_AS(func_0204ed30, AcreTile_PathDirectionsAt)

/* func_0204ed58: the directions 1, 2, 4 and 8 a path leaves the tile in (path_walker.h). */
int AcreTile_PathDirections(AcreMap *map, int x, int z)
{
    func_02030e4c(map->slot);
    int result = func_02031a08(x, z);
    func_02030e4c(0);
    return result;
}
CLEAN_AS(func_0204ed58, AcreTile_PathDirections)

/* func_0204ed80 */
int AcreTile_UnitWord06(AcreMap *map, int x, int z)
{
    func_02030e4c(map->slot);
    int result = func_02031aa0(x, z);
    func_02030e4c(0);
    return result;
}
CLEAN_AS(func_0204ed80, AcreTile_UnitWord06)

/* func_0204eda8 */
int AcreTile_UnitByte09(AcreMap *map, int x, int z)
{
    func_02030e4c(map->slot);
    int result = func_02031acc(x, z);
    func_02030e4c(0);
    return result;
}
CLEAN_AS(func_0204eda8, AcreTile_UnitByte09)

/* func_0204edd0 */
int AcreTile_UnitHasByte17(AcreMap *map, int x, int z)
{
    func_02030e4c(map->slot);
    int result = func_02031a74(x, z);
    func_02030e4c(0);
    return result;
}
CLEAN_AS(func_0204edd0, AcreTile_UnitHasByte17)

/* func_0204edf8 */
int AcreTile_UnitByte08(AcreMap *map, int x, int z)
{
    func_02030e4c(map->slot);
    int result = func_02031b14(x, z);
    func_02030e4c(0);
    return result;
}
CLEAN_AS(func_0204edf8, AcreTile_UnitByte08)

/* func_0204ee20: (town_tile.c: whether the map takes the tile). */
int AcreTile_UnitByte05(AcreMap *map, int x, int z)
{
    func_02030e4c(map->slot);
    int result = func_02031af0(x, z);
    func_02030e4c(0);
    return result;
}
CLEAN_AS(func_0204ee20, AcreTile_UnitByte05)

/* func_0204ee48: AcreTile_UnitByte04 of tile (x, z) of acre (acre_x, acre_z). */
int AcreTile_UnitByte04InAcre(AcreMap *map, int acre_x, int acre_z, int x, int z)
{
    int tile_x = 0;
    int tile_z = 0;

    AcreTile_TileOfAcre(&tile_x, &tile_z, acre_x, acre_z, x, z);
    return AcreTile_UnitByte04(map, tile_x, tile_z);
}
CLEAN_AS(func_0204ee48, AcreTile_UnitByte04InAcre)

/* func_0204ee7c */
int AcreTile_UnitByte04(AcreMap *map, int x, int z)
{
    func_02030e4c(map->slot);
    int result = func_02031b38(x, z);
    func_02030e4c(0);
    return result;
}
CLEAN_AS(func_0204ee7c, AcreTile_UnitByte04)

/* ---- buildings ---- */

/* func_0204eea4: replaces the building on tile (x, z) with *code (nothing when `code` is 0):
 * the tiles the old building covered are emptied. 0 when the tile holds no building. */
int AcreTile_ReplaceBuilding(AcreMap *map, int x, int z, u16 *code)
{
    u16 *tile = acre_tile_item(map, x, z);

    if (tile == NULL || !acre_tile_is_building(*tile)) {
        return 0;
    }
    u16 replacement = ACRE_MAP_ITEM_NONE;
    if (code != NULL) {
        replacement = *code;
    }
    u16 fill = ACRE_MAP_ITEM_NONE;
    return AcreTile_PutBuilding(map, &replacement, tile, &fill, x, z);
}
CLEAN_AS(func_0204eea4, AcreTile_ReplaceBuilding)

/* func_0204ef24: puts building *building down with its tile at (x, z): the other tiles of its
 * shape become ACRE_TILE_ITEM_OCCUPIED. 0 when the code is not a building's. */
int AcreTile_StampBuilding(AcreMap *map, u16 *building, int x, int z)
{
    if (!acre_tile_is_building(*building)) {
        return 0;
    }
    u16 fill = ACRE_TILE_ITEM_OCCUPIED;
    return AcreTile_PutBuilding(map, building, building, &fill, x, z);
}
CLEAN_AS(func_0204ef24, AcreTile_StampBuilding)

/* Whether a code is one of the growth lines' (map_item.h): 0x26-0x2a, 0x2f-0x5b, 0x5d-0x61,
 * 0x66-0x6d or 0xc8-0xcf. */
static int acre_tile_grows(u32 code)
{
    return (code >= 0x26 && code <= 0x2a) || (code >= 0x5d && code <= 0x61) || (code >= 0x2f && code <= 0x5b) ||
           (code >= 0x66 && code <= 0x6d) || (code >= 0xc8 && code <= 0xcf);
}

/* Whether a code is ACRE_TILE_ITEM_OCCUPIED; for a code with a variant, whether its item is. */
static int acre_tile_is_occupied(u16 *code)
{
    if (func_0204bcdc(code)) {
        u16 occupied = ACRE_TILE_ITEM_OCCUPIED;
        int item = func_0204bc64(code);
        return item == func_0204bc64(&occupied);
    }
    return *code == ACRE_TILE_ITEM_OCCUPIED;
}

/* func_0204ef74: puts *code on tile (x, z) and *fill on the other tiles the shape of *building
 * (a building's code) covers; 1 when *building has a shape, else 0 and nothing changes.
 *
 * First the code tile (x, z) holds goes to the list of replaced items when it is of kind 1 or
 * has a variant (whatever the outcome). For each covered tile: its code goes to that list in
 * the same case unless the session is linked; a snowman's object there removes the snowman's
 * record; the tile gets *fill and loses its bit. When *fill is ACRE_TILE_ITEM_OCCUPIED (the
 * building is being put down), the tiles of the shape's second list are emptied, except those
 * that hold a code of no growth line or a growth line's first stage and are not on a short
 * line. */
int AcreTile_PutBuilding(AcreMap *map, u16 *code, u16 *building, u16 *fill, int x, int z)
{
    u16 *tile = acre_tile_item(map, x, z);
    void *shape = NULL;

    if (tile != NULL) {
        u16 replaced = *tile;
        if (func_0204bd08(&replaced) || func_0204bcdc(&replaced)) {
            func_0203a76c(replaced);
        }
    }
    if (acre_tile_is_building(*building)) {
        shape = func_020b3b50(building);
    }
    if (shape == NULL) {
        return 0;
    }

    int offset_x;
    int offset_z;
    unsigned int covered = func_020b3eb8(shape);
    for (unsigned int i = 0; i < covered; i++) {
        if (!func_020b3e08(shape, &offset_x, &offset_z, i)) {
            continue;
        }
        int tile_x = x + offset_x;
        int tile_z = z + offset_z;
        u16 *other = acre_tile_item(map, tile_x, tile_z);
        if (other != NULL) {
            if (func_0204bcdc(other) || func_0204bd08(other)) {
                if (!Session_IsLinked(data_020ccf94)) {
                    func_0203a76c(*other);
                }
            } else if (func_0204bb54(other)) {
                func_020b0650(data_021f3b56, (unsigned int) func_0204bb2c(other));
            }
        }
        AcreTile_SetItem(map, fill, tile_x, tile_z, 0);
        AcreTile_Unmark(map, tile_x, tile_z);
    }
    AcreTile_SetItem(map, code, x, z, 0);

    if (acre_tile_is_occupied(fill)) {
        unsigned int around = func_020b3f2c(shape);
        for (unsigned int i = 0; i < around; i++) {
            if (!func_020b3e58(shape, &offset_x, &offset_z, i)) {
                continue;
            }
            int tile_x = x + offset_x;
            int tile_z = z + offset_z;
            u16 *other = acre_tile_item(map, tile_x, tile_z);
            if (other == NULL) {
                continue;
            }
            if (!acre_tile_grows(*other) || func_0204ba94(other)) {
                if (func_0204b5ac(other) == -1) {
                    continue;
                }
            }
            u16 none = ACRE_MAP_ITEM_NONE;
            AcreTile_SetItem(map, &none, tile_x, tile_z, 0);
        }
    }
    return 1;
}
CLEAN_AS(func_0204ef74, AcreTile_PutBuilding)

/* ---- the tiles' bits ---- */

/* func_0204f260: whether the bit of the tile a position is on is set. */
int AcreTile_IsMarkedAt(AcreMap *map, const Vec3 *position)
{
    int acre[2] = {0, 0};
    int tile[2] = {0, 0};

    AcreTile_AcreAndTileOf(acre, tile, position);
    return AcreTile_IsMarkedInAcre(map, (u32) acre[0], (u32) acre[1], (u32) tile[0], (u32) tile[1]);
}
CLEAN_AS(func_0204f260, AcreTile_IsMarkedAt)

/* func_0204f294 */
int AcreTile_IsMarked(AcreMap *map, int x, int z)
{
    return AcreTile_IsMarkedInAcre(map, (u32) acre_tile_acre_of(x), (u32) acre_tile_acre_of(z), (u32) acre_tile_offset_of(x),
                                   (u32) acre_tile_offset_of(z));
}
CLEAN_AS(func_0204f294, AcreTile_IsMarked)

/* func_0204f2b8: whether tile (x, z) of acre (acre_x, acre_z) has its bit; 0 outside the map
 * or the acre, or when the acre has no bits. */
int AcreTile_IsMarkedInAcre(AcreMap *map, u32 acre_x, u32 acre_z, u32 x, u32 z)
{
    u8 *acre = acre_tile_acre_at(map, acre_x, acre_z);

    if (acre == NULL) {
        return 0;
    }
    const u16 *rows = *(u16 *const *) (acre + 0x24);
    if (rows == NULL || x >= 16 || z >= 16) {
        return 0;
    }
    return (rows[z] >> x) & 1;
}
CLEAN_AS(func_0204f2b8, AcreTile_IsMarkedInAcre)

/* func_0204f31c */
int AcreTile_Unmark(AcreMap *map, int x, int z)
{
    return AcreTile_UnmarkInAcre(map, (u32) acre_tile_acre_of(x), (u32) acre_tile_acre_of(z), acre_tile_offset_of(x),
                                 acre_tile_offset_of(z));
}
CLEAN_AS(func_0204f31c, AcreTile_Unmark)

/* func_0204f340: clears the bit of tile (x, z) of acre (acre_x, acre_z); 0 outside the map. */
int AcreTile_UnmarkInAcre(AcreMap *map, u32 acre_x, u32 acre_z, int x, int z)
{
    u8 *acre = acre_tile_acre_at(map, acre_x, acre_z);

    if (acre == NULL) {
        return 0;
    }
    return func_02037d2c(acre, x, z);
}
CLEAN_AS(func_0204f340, AcreTile_UnmarkInAcre)

/* func_0204f380 */
void AcreTile_Mark(AcreMap *map, int x, int z)
{
    AcreTile_MarkInAcre(map, (u32) acre_tile_acre_of(x), (u32) acre_tile_acre_of(z), acre_tile_offset_of(x),
                        acre_tile_offset_of(z));
}
CLEAN_AS(func_0204f380, AcreTile_Mark)

/* func_0204f3a4: sets the bit of tile (x, z) of acre (acre_x, acre_z); 0 outside the map. */
int AcreTile_MarkInAcre(AcreMap *map, u32 acre_x, u32 acre_z, int x, int z)
{
    u8 *acre = acre_tile_acre_at(map, acre_x, acre_z);

    if (acre == NULL) {
        return 0;
    }
    return func_02037d48(acre, x, z);
}
CLEAN_AS(func_0204f3a4, AcreTile_MarkInAcre)

/* ---- searches ---- */

/* func_0204f3e4: the first acre, row by row, that has any of `flags` (any acre when `flags` is
 * 0) and a tile in `layer` whose code is in [*first, *last]: the acre to (*acre_x, *acre_z),
 * the tile in it to (*x, *z), and 1; 0 when there is none. */
int AcreTile_FindItemAnyFlag(AcreMap *map, int *acre_x, int *acre_z, int *x, int *z, u16 *first, u16 *last, int flags,
                             int layer)
{
    int wide = map->acres_wide;
    int high = map->acres_high;

    for (int az = 0; az < high; az++) {
        for (int ax = 0; ax < wide; ax++) {
            u8 *acre = acre_tile_acre_at(map, (u32) ax, (u32) az);
            if (acre != NULL && (flags == 0 || func_02037d64(acre, flags)) &&
                func_02037da8(acre, x, z, first, last, (u8) layer)) {
                *acre_x = ax;
                *acre_z = az;
                return 1;
            }
        }
    }
    return 0;
}
CLEAN_AS(func_0204f3e4, AcreTile_FindItemAnyFlag)

/* func_0204f490: the same for the acres that have all of `flags`. */
int AcreTile_FindItemAllFlags(AcreMap *map, int *acre_x, int *acre_z, int *x, int *z, u16 *first, u16 *last, int flags,
                              int layer)
{
    int wide = map->acres_wide;
    int high = map->acres_high;

    for (int az = 0; az < high; az++) {
        for (int ax = 0; ax < wide; ax++) {
            u8 *acre = acre_tile_acre_at(map, (u32) ax, (u32) az);
            if (acre != NULL && func_02037d80(acre, flags) && func_02037da8(acre, x, z, first, last, (u8) layer)) {
                *acre_x = ax;
                *acre_z = az;
                return 1;
            }
        }
    }
    return 0;
}
CLEAN_AS(func_0204f490, AcreTile_FindItemAllFlags)

/* ---- the tiles' codes ---- */

/* func_0204f538: sets the code of tile (x, z) in `layer` to *code. */
int AcreTile_SetItem(AcreMap *map, u16 *code, int x, int z, u8 layer)
{
    return AcreTile_SetItemInAcre(map, code, (u32) acre_tile_acre_of(x), (u32) acre_tile_acre_of(z), acre_tile_offset_of(x),
                                  acre_tile_offset_of(z), layer);
}
CLEAN_AS(func_0204f538, AcreTile_SetItem)

/* func_0204f564: sets the code of tile (x, z) of acre (acre_x, acre_z) in `layer` to *code; 0
 * when there is no such tile. */
int AcreTile_SetItemInAcre(AcreMap *map, u16 *code, u32 acre_x, u32 acre_z, int x, int z, u8 layer)
{
    u8 *acre = acre_tile_acre_at(map, acre_x, acre_z);

    if (acre == NULL) {
        return 0;
    }
    return func_02037e44(acre, code, x, z, layer);
}
CLEAN_AS(func_0204f564, AcreTile_SetItemInAcre)

/* func_0204f5a8: the code of the tile a position is on, in `layer`, or 0. */
u16 *AcreTile_ItemAt(AcreMap *map, const Vec3 *position, int layer)
{
    int acre[2] = {0, 0};
    int tile[2] = {0, 0};

    AcreTile_AcreAndTileOf(acre, tile, position);
    return AcreTile_ItemInAcre(map, (u32) acre[0], (u32) acre[1], tile[0], tile[1], (u8) layer);
}
CLEAN_AS(func_0204f5a8, AcreTile_ItemAt)

/* func_0204f5e0: the code of tile (x, z) of acre (acre_x, acre_z) in `layer`, or 0. */
u16 *AcreTile_ItemInAcre(AcreMap *map, u32 acre_x, u32 acre_z, int x, int z, u8 layer)
{
    u8 *acre = acre_tile_acre_at(map, acre_x, acre_z);

    if (acre == NULL) {
        return NULL;
    }
    return func_02037e0c(acre, x, z, layer);
}
CLEAN_AS(func_0204f5e0, AcreTile_ItemInAcre)

/* ---- the acres' flags ---- */

/* func_0204f61c: whether acre (acre_x, acre_z) has all of `flags` (as a pointer-sized 0 or
 * 1); 0 outside the map. */
void *AcreTile_AcreHasFlags(AcreMap *map, u32 acre_x, u32 acre_z, u32 flags)
{
    u8 *acre = acre_tile_acre_at(map, acre_x, acre_z);

    if (acre == NULL) {
        return NULL;
    }
    return (void *) (uintptr_t) (u32) func_02037d80(acre, (int) flags);
}
CLEAN_AS(func_0204f61c, AcreTile_AcreHasFlags)

/* func_0204f658: the flags of acre (acre_x, acre_z) (as a pointer-sized number); 0 outside
 * the map. */
void *AcreTile_AcreFlags(AcreMap *map, u32 acre_x, u32 acre_z)
{
    u8 *acre = acre_tile_acre_at(map, acre_x, acre_z);

    if (acre == NULL) {
        return NULL;
    }
    return (void *) (uintptr_t) (u32) func_02037d9c(acre);
}
CLEAN_AS(func_0204f658, AcreTile_AcreFlags)

/* func_0204f694: the first acre, row by row, with any of `flags` (a number passed as a
 * pointer), or 0. */
void *AcreTile_FindAcreAnyFlag(AcreMap *map, void *flags)
{
    int wide = map->acres_wide;
    int high = map->acres_high;

    for (int az = 0; az < high; az++) {
        for (int ax = 0; ax < wide; ax++) {
            u8 *acre = acre_tile_acre_at(map, (u32) ax, (u32) az);
            if (acre != NULL && func_02037d64(acre, (int) (uintptr_t) flags)) {
                return acre;
            }
        }
    }
    return NULL;
}
CLEAN_AS(func_0204f694, AcreTile_FindAcreAnyFlag)

/* func_0204f704: the first acre, row by row, with all of `flags` (a number passed as a
 * pointer), or 0; 0 also when `flags` is 0. */
void *AcreTile_FindAcreAllFlags(AcreMap *map, void *flags)
{
    if (flags == NULL) {
        return NULL;
    }
    int wide = map->acres_wide;
    int high = map->acres_high;

    for (int az = 0; az < high; az++) {
        for (int ax = 0; ax < wide; ax++) {
            u8 *acre = acre_tile_acre_at(map, (u32) ax, (u32) az);
            if (acre != NULL && func_02037d80(acre, (int) (uintptr_t) flags)) {
                return acre;
            }
        }
    }
    return NULL;
}
CLEAN_AS(func_0204f704, AcreTile_FindAcreAllFlags)

/* ---- tiles and positions ---- */

/* func_0204f778: the x and z of the corner of tile (x, z) of acre (acre_x, acre_z); y is left
 * alone. */
void AcreTile_PositionInAcre(Vec3 *position, u32 acre_x, u32 acre_z, u32 x, u32 z)
{
    position->x = (fx32) ((acre_x << 17) + (x << 13));
    position->z = (fx32) ((acre_z << 17) + (z << 13));
}
CLEAN_AS(func_0204f778, AcreTile_PositionInAcre)

/* func_0204f794: the centre of tile (x, z), at height 0. */
void AcreTile_TileCentre(Vec3 *position, u32 x, u32 z)
{
    position->x = (fx32) ((x << 13) + 0x1000);
    position->z = (fx32) ((z << 13) + 0x1000);
    position->y = 0;
}
CLEAN_AS(func_0204f794, AcreTile_TileCentre)

/* func_0204f7ac: the centre of tile (x, z) of acre (acre_x, acre_z), at height 0. */
void AcreTile_TileCentreInAcre(Vec3 *position, int acre_x, int acre_z, int x, int z)
{
    int tile_x = 0;
    int tile_z = 0;

    AcreTile_TileOfAcre(&tile_x, &tile_z, acre_x, acre_z, x, z);
    AcreTile_TileCentre(position, (u32) tile_x, (u32) tile_z);
}
CLEAN_AS(func_0204f7ac, AcreTile_TileCentreInAcre)

/* func_0204f7e0: the centre of the tile `from` is on, at the height of `from`.
 * QUIRK: the centre is written before the height is read, so with `from` the same vector as
 * `position` the height becomes 0. */
void AcreTile_SnapToTileCentre(Vec3 *position, const Vec3 *from)
{
    AcreTile_TileCentre(position, (u32) acre_tile_shift(from->x, 13), (u32) acre_tile_shift(from->z, 13));
    position->y = from->y;
}
CLEAN_AS(func_0204f7e0, AcreTile_SnapToTileCentre)

/* func_0204f800: tile (offset_x, offset_z) of acre (acre_x, acre_z), numbered across the map. */
void AcreTile_TileOfAcre(int *x, int *z, int acre_x, int acre_z, int offset_x, int offset_z)
{
    *x = acre_x * 16 + offset_x;
    *z = acre_z * 16 + offset_z;
}
CLEAN_AS(func_0204f800, AcreTile_TileOfAcre)

/* func_0204f828: the acre a position is in to acre[0..1], the tile in it to tile[0..1]. */
void AcreTile_AcreAndTileOf(int *acre, int *tile, const Vec3 *position)
{
    AcreTile_SplitPosition(&acre[0], &acre[1], &tile[0], &tile[1], position);
}
CLEAN_AS(func_0204f828, AcreTile_AcreAndTileOf)

/* func_0204f840: the acre a position is in and the tile in that acre. Each coordinate is read
 * again after each write, as the original does. */
void AcreTile_SplitPosition(int *acre_x, int *acre_z, int *x, int *z, const Vec3 *position)
{
    *acre_x = acre_tile_shift(position->x, 17);
    *acre_z = acre_tile_shift(position->z, 17);
    *x = acre_tile_shift(position->x, 13) & 15;
    *z = acre_tile_shift(position->z, 13) & 15;
}
CLEAN_AS(func_0204f840, AcreTile_SplitPosition)
