/* The maps of units the collision code reads (collision_map.h). */
#include "collision_map.h"

#include "clean.h"
#include "itcm/field_units.h"

static_assert(sizeof(CollisionMapState) == sizeof(((FieldBlockMap *) 0)->unk_12C), "a map's words after its blocks");
static_assert(offsetof(CollisionWorld, maps) == 4 && offsetof(CollisionWorld, extra_posts) == 0x1f3c, "collision world");

/* The world of the collision code and its current map (one of world.maps). */
extern CollisionWorld data_021c31e8;
extern FieldBlockMap *data_020da1a8;

/* The rows of the unit type table (field_collision.h). */
extern const CollisionTypeInfo data_020c907c[];

/* The two objects of the world at 0x1a90 and 0x1a91 empty their lists. */
extern void func_0203242c(u8 *object);
extern void func_020326b0(u8 *object);
/* Byte 0x130 of map `slot`. */
extern u8 func_02031e48(int slot);

/* The side attribute CollisionMap_RetypeWithSides gives the sides it is asked for. */
#define UNIT_SIDE_0A 0x0a

/* Unit types that CollisionMap_RetypeToPlain turns into a fixed type. */
#define UNIT_TYPE_03 0x03
#define UNIT_TYPE_09 0x09
#define UNIT_TYPE_1D 0x1d
#define UNIT_TYPE_1E 0x1e

/* Map `slot` of the world, its address computed as the ARM does, in 32 bits. */
static FieldBlockMap *collision_map_slot(int slot)
{
    return (FieldBlockMap *) (uintptr_t) ((u32) (uintptr_t) data_021c31e8.maps + (u32) slot * sizeof(FieldBlockMap));
}

/* Block (x, z) of `map` in its rows of 6, the address computed in 32 bits for any x and z. */
static FieldBlock *collision_map_block(FieldBlockMap *map, int x, int z)
{
    u32 offset = (u32) z * sizeof(map->blocks[0]) + (u32) x * sizeof(FieldBlock);
    return (FieldBlock *) (uintptr_t) ((u32) (uintptr_t) map + offset);
}

static CollisionMapState *collision_map_state(FieldBlockMap *map)
{
    return (CollisionMapState *) (void *) map->unk_12C;
}

/* Row `index` of the type table; `index` is below 0x7c. */
static const CollisionTypeInfo *collision_map_type_info(int index)
{
    return &data_020c907c[index];
}

/* The halfword at 6 of a row (bytes 6 and 7). */
static s16 collision_map_word06(const CollisionTypeInfo *info)
{
    return (s16) (info->unk_00[6] | info->unk_00[7] << 8);
}

/* The object a unit type stands for, else COLLISION_MAP_NO_OBJECT. */
static int collision_map_object_of(int type)
{
    if (type >= COLLISION_MAP_OBJECT_FIRST && type <= COLLISION_MAP_OBJECT_LAST) {
        return type - COLLISION_MAP_OBJECT_FIRST;
    }
    return COLLISION_MAP_NO_OBJECT;
}

/* The byte holding the path directions of unit (x, z) of `block`, and whether they are its
 * high half. */
static u8 *collision_map_path_byte(const FieldBlock *block, int x, int z, int *high)
{
    int index = (x & 0xf) + ((z & 0xf) << 4);
    *high = index & 1;
    return (u8 *) (uintptr_t) (block->unk_04 + (u32) (index >> 1));
}

/* func_02030738: the bounds of the room in the default map (slot 0): from the first unit to
 * past the last one of the 32 by 32 units whose type is not UNIT_TYPE_NONE, on X and Z, as
 * positions. Only when map 0 is complete, and then the result is 1; else every bound is 0
 * (`max_z` may be NULL) and the result 0.
 * QUIRK: a unit only widens the maximum when it does not lower the minimum, so the first unit
 * found on an axis is never taken as its maximum (one column or row alone gives a maximum of
 * 0); the maximum Z is past the last unit, the maximum X too. */
int CollisionMap_GetRoomBounds(fx32 *min_x, fx32 *max_x, fx32 *min_z, fx32 *max_z)
{
    if (CollisionMap_IsComplete(0) == 0) {
        *min_z = 0;
        *max_x = 0;
        *min_x = 0;
        if (max_z != NULL) {
            *max_z = 0;
        }
        return 0;
    }

    int low_x = 16;
    int high_x = 0;
    int low_z = 16;
    int high_z = 0;
    for (int z = 0; z < 32; z++) {
        for (int x = 0; x < 32; x++) {
            if (FieldUnits_GetType(x, z) == UNIT_TYPE_NONE) {
                continue;
            }
            if (x < low_x) {
                low_x = x;
            } else if (x > high_x) {
                high_x = x;
            }
            if (z < low_z) {
                low_z = z;
            } else if (z > high_z) {
                high_z = z;
            }
        }
    }
    *min_x = low_x << COLLISION_UNIT_SHIFT;
    *max_x = (high_x << COLLISION_UNIT_SHIFT) + 2 * COLLISION_HALF_UNIT;
    *min_z = low_z << COLLISION_UNIT_SHIFT;
    if (max_z != NULL) {
        *max_z = (high_z << COLLISION_UNIT_SHIFT) + 2 * COLLISION_HALF_UNIT;
    }
    return 1;
}
CLEAN_AS(func_02030738, CollisionMap_GetRoomBounds)

/* func_020307f8: the current map's claimed object is released; whether there was one. */
int CollisionMap_ClearClaim(void)
{
    CollisionMapState *state = collision_map_state(data_020da1a8);
    if (state->claimed == COLLISION_MAP_NO_OBJECT) {
        return 0;
    }
    state->claimed = COLLISION_MAP_NO_OBJECT;
    return 1;
}
CLEAN_AS(func_020307f8, CollisionMap_ClearClaim)

/* func_02030818: whether the unit under `point` is the current map's claimed object. */
int CollisionMap_IsClaimedAtPoint(const Vec3 *point)
{
    int object =
        collision_map_object_of(FieldUnits_GetType(point->x >> COLLISION_UNIT_SHIFT, point->z >> COLLISION_UNIT_SHIFT));
    if (object < 0) {
        return 0;
    }
    return object == collision_map_state(data_020da1a8)->claimed;
}
CLEAN_AS(func_02030818, CollisionMap_IsClaimedAtPoint)

/* func_02030864: claims `object` in the current map when none is claimed; whether it did. */
int CollisionMap_Claim(int object)
{
    CollisionMapState *state = collision_map_state(data_020da1a8);
    if (state->claimed == COLLISION_MAP_NO_OBJECT) {
        state->claimed = object;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_02030864, CollisionMap_Claim)

/* func_02030890: CollisionMap_UnclaimedObjectAt of the unit under `point`. */
int CollisionMap_UnclaimedObjectAtPoint(const Vec3 *point)
{
    return CollisionMap_UnclaimedObjectAt(point->x >> COLLISION_UNIT_SHIFT, point->z >> COLLISION_UNIT_SHIFT);
}
CLEAN_AS(func_02030890, CollisionMap_UnclaimedObjectAtPoint)

/* func_020308a4: the object at unit (x, z) of the current map, COLLISION_MAP_NO_OBJECT for none
 * or for the claimed one. */
int CollisionMap_UnclaimedObjectAt(int x, int z)
{
    int object = collision_map_object_of(FieldUnits_GetType(x, z));
    if (object < 0 || object == collision_map_state(data_020da1a8)->claimed) {
        return COLLISION_MAP_NO_OBJECT;
    }
    return object;
}
CLEAN_AS(func_020308a4, CollisionMap_UnclaimedObjectAt)

/* func_020308e0: unit (x, z) gets no path directions, and its four neighbours lose the one
 * pointing at it (north, south, west, then east). */
void CollisionMap_UnlinkPathUnit(int x, int z)
{
    CollisionMap_SetPathDirections(x, z, 0);
    CollisionMap_ClearPathDirections((u32) x, (u32) (z - 1), COLLISION_PATH_PLUS_Z);
    CollisionMap_ClearPathDirections((u32) x, (u32) (z + 1), COLLISION_PATH_MINUS_Z);
    CollisionMap_ClearPathDirections((u32) (x - 1), (u32) z, COLLISION_PATH_PLUS_X);
    CollisionMap_ClearPathDirections((u32) (x + 1), (u32) z, COLLISION_PATH_MINUS_X);
}
CLEAN_AS(func_020308e0, CollisionMap_UnlinkPathUnit)

/* func_02030920: retypes unit (x, z) of the current map: the sides whose bit is set in `sides`
 * (bit n for side n, CollisionCell's order) are to be UNIT_SIDE_0A; the first type of the table
 * whose four side attributes are those becomes the unit's type (type 0 when none is), and the
 * result is 1. A unit of type 0 becomes type 0x0a instead, and the result is 0; so does a unit
 * outside the map's blocks, which is left alone.
 * QUIRK: the sides not in `sides` are matched against the unit's type number itself, not
 * against its row's sides. */
int CollisionMap_RetypeWithSides(int x, int z, int sides)
{
    FieldBlock *block = FieldUnits_GetBlock(x >> 4, z >> 4);
    if (block == NULL) {
        return 0;
    }
    u8 *unit = (u8 *) block->unit_types + (x & 0xf) + ((z & 0xf) << 4);
    int type = *unit;
    int want[4];
    for (int side = 0; side < 4; side++) {
        want[side] = (sides >> side) & 1 ? UNIT_SIDE_0A : type;
    }

    int found = 0;
    for (int i = 0; i < COLLISION_TYPE_COUNT; i++) {
        const CollisionTypeInfo *info = collision_map_type_info(i);
        if (want[0] == info->side_attr[0] && want[1] == info->side_attr[1] && want[2] == info->side_attr[2] &&
            want[3] == info->side_attr[3]) {
            found = i;
            break;
        }
    }
    if (type != 0) {
        *unit = (u8) found;
        return 1;
    }
    *unit = UNIT_SIDE_0A;
    return 0;
}
CLEAN_AS(func_02030920, CollisionMap_RetypeWithSides)

/* func_02030a18: when the type of unit (x, z) has a positive halfword 6 in its row, it is
 * replaced: type 3 by 0x1d, type 9 by 0x1e, any other by the first type whose halfword 6 is 0
 * and whose four side attributes are the same; the result is 0 only when no type is found (the
 * unit is then left alone). Any other unit is left alone with the result 1; one outside the
 * map's blocks gives 0. */
int CollisionMap_RetypeToPlain(int x, int z)
{
    FieldBlock *block = FieldUnits_GetBlock(x >> 4, z >> 4);
    if (block == NULL) {
        return 0;
    }
    u8 *unit = (u8 *) block->unit_types + (x & 0xf) + ((z & 0xf) << 4);
    int type = *unit;
    if (type >= COLLISION_TYPE_COUNT || collision_map_word06(collision_map_type_info(type)) <= 0) {
        return 1;
    }
    if (type == UNIT_TYPE_03) {
        *unit = UNIT_TYPE_1D;
        return 1;
    }
    if (type == UNIT_TYPE_09) {
        *unit = UNIT_TYPE_1E;
        return 1;
    }

    const CollisionTypeInfo *from = collision_map_type_info(type);
    for (int i = 0; i < COLLISION_TYPE_COUNT; i++) {
        const CollisionTypeInfo *info = collision_map_type_info(i);
        if (collision_map_word06(info) == 0 && from->side_attr[0] == info->side_attr[0] &&
            from->side_attr[1] == info->side_attr[1] && from->side_attr[2] == info->side_attr[2] &&
            from->side_attr[3] == info->side_attr[3]) {
            *unit = (u8) i;
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_02030a18, CollisionMap_RetypeToPlain)

/* func_02030b80: sets the current map's halfword 0x134 to `value`; when that changes it, the
 * former value is kept at 0x132. */
void CollisionMap_SetValue134(s16 value)
{
    CollisionMapState *state = collision_map_state(data_020da1a8);
    if (state->value != value) {
        state->value_old = state->value;
        state->value = value;
    }
}
CLEAN_AS(func_02030b80, CollisionMap_SetValue134)

/* func_02030bac: map `slot` loses its blocks and is reset. */
void CollisionMap_Release(int slot)
{
    CollisionMap_ClearBlocks(slot);
    CollisionMap_Reset(slot);
}
CLEAN_AS(func_02030bac, CollisionMap_Release)

/* func_02030bc0: the blocks within the size of map `slot` get no data.
 * QUIRK: the size is read again for every block, and past 6 rows the blocks' entries run into
 * the words after them: row 6 starts with 0x120 and the width, which it clears, ending the
 * walk. */
void CollisionMap_ClearBlocks(int slot)
{
    FieldBlockMap *map = collision_map_slot(slot);
    for (u32 z = 0; z < map->height; z++) {
        for (u32 x = 0; x < map->width; x++) {
            FieldBlock *block = collision_map_block(map, (int) x, (int) z);
            block->unit_types = NULL;
            block->unk_04 = 0;
        }
    }
}
CLEAN_AS(func_02030bc0, CollisionMap_ClearBlocks)

/* func_02030c34: map `slot` is emptied (CollisionBlockMap_Clear), and so are the world's walls,
 * floors, posts, the two lists at 0x1a90 and 0x1a91 and the extra posts. */
void CollisionMap_Reset(int slot)
{
    CollisionBlockMap_Clear(collision_map_slot(slot));
    data_021c31e8.walls.count = 0;
    data_021c31e8.floors.count = 0;
    data_021c31e8.posts.count = 0;
    func_0203242c(&data_021c31e8.unk_1a90);
    func_020326b0(&data_021c31e8.unk_1a91);
    CollisionExtraPosts_Clear(&data_021c31e8.extra_posts);
}
CLEAN_AS(func_02030c34, CollisionMap_Reset)

/* func_02030c84: block (x, z) of map `slot` gets `data`: its unit types there and its path
 * directions 0x100 bytes on. The map is then complete when every block of its size has both.
 * The result is 1, or 0 when (x, z) is outside the map's size (nothing changes then). */
int CollisionMap_SetBlock(int x, int z, int data, int slot)
{
    FieldBlockMap *map = collision_map_slot(slot);
    if (x < 0 || z < 0 || (u32) x >= map->width || (u32) z >= map->height) {
        return 0;
    }
    FieldBlock *block = collision_map_block(map, x, z);
    block->unit_types = (const u8 *) (uintptr_t) (u32) data;
    block->unk_04 = (u32) data + 0x100;

    int complete = 1;
    for (int row = (int) map->height - 1; row >= 0 && complete; row--) {
        for (int column = (int) map->width - 1; column >= 0; column--) {
            const FieldBlock *other = collision_map_block(map, column, row);
            if (other->unit_types == NULL || other->unk_04 == 0) {
                complete = 0;
                break;
            }
        }
    }
    collision_map_state(map)->complete = (u8) complete;
    return 1;
}
CLEAN_AS(func_02030c84, CollisionMap_SetBlock)

/* func_02030d48: unit (x, z) loses the path directions in `directions`. */
void CollisionMap_ClearPathDirections(u32 x, u32 z, u32 directions)
{
    u32 kept = (u32) CollisionMap_PathDirections((int) x, (int) z) & ~directions;
    CollisionMap_SetPathDirections((int) x, (int) z, (int) kept);
}
CLEAN_AS(func_02030d48, CollisionMap_ClearPathDirections)

/* func_02030d68: sets the path directions of unit (x, z) of the current map (nothing outside
 * its blocks).
 * QUIRK: `directions` is not cut to four bits: for an even unit its higher bits go into the odd
 * unit's half. */
void CollisionMap_SetPathDirections(int x, int z, int directions)
{
    FieldBlock *block = FieldUnits_GetBlock(x >> 4, z >> 4);
    if (block == NULL) {
        return;
    }
    int high;
    u8 *byte = collision_map_path_byte(block, x, z, &high);
    if (high) {
        *byte = (u8) ((*byte & 0x0f) | ((u32) directions << 4));
    } else {
        *byte = (u8) ((*byte & 0xf0) | (u32) directions);
    }
}
CLEAN_AS(func_02030d68, CollisionMap_SetPathDirections)

/* func_02030db8: puts one of the world's extra posts on unit (x, z) (CollisionExtraPosts_Add). */
int CollisionMap_AddExtraPost(int x, int z)
{
    return CollisionExtraPosts_Add(&data_021c31e8.extra_posts, x, z);
}
CLEAN_AS(func_02030db8, CollisionMap_AddExtraPost)

/* func_02030dcc: the world's extra posts age by a frame. */
void CollisionMap_AgeExtraPosts(void)
{
    CollisionExtraPosts_Age(&data_021c31e8.extra_posts);
}
CLEAN_AS(func_02030dcc, CollisionMap_AgeExtraPosts)

/* func_02030ddc: map `slot` is reset (CollisionMap_Reset) and set up for `blocks_wide` by
 * `blocks_high` blocks with `source` telling its posts; then the default map (slot 0) becomes
 * the current one. A size above 6 is not taken (that side keeps 0) and makes the result 0, else
 * it is 1. */
int CollisionMap_Setup(u32 blocks_wide, u32 blocks_high, CollisionPostSource *source, int slot)
{
    FieldBlockMap *map = collision_map_slot(slot);
    int result = 1;

    CollisionMap_Reset(slot);
    if (blocks_wide <= 6) {
        map->width = blocks_wide;
    } else {
        result = 0;
    }
    if (blocks_high <= 6) {
        map->height = blocks_high;
    } else {
        result = 0;
    }
    map->unk_120 = (u32) (uintptr_t) source;
    collision_map_state(map)->complete = 0;
    CollisionMap_Select(0);
    return result;
}
CLEAN_AS(func_02030ddc, CollisionMap_Setup)

/* func_02030e4c: map `slot` becomes the current map; a slot outside 0 to 7 selects map 0 when
 * negative and map 7 when too large. */
void CollisionMap_Select(int slot)
{
    if (CollisionMaps_SetIndex(&data_021c31e8.map_index, slot) == 0) {
        CollisionMaps_SetIndex(&data_021c31e8.map_index, slot < 0 ? 0 : COLLISION_BLOCK_MAPS - 1);
    }
    data_020da1a8 = collision_map_slot(data_021c31e8.map_index);
}
CLEAN_AS(func_02030e4c, CollisionMap_Select)

/* func_0203160c: whether map `slot` is complete (every block of its size has its data). */
u8 CollisionMap_IsComplete(int slot)
{
    return func_02031e48(slot);
}
CLEAN_AS(func_0203160c, CollisionMap_IsComplete)

/* func_02031a08: the path directions of unit (x, z) of the current map; 0 outside its
 * blocks. */
int CollisionMap_PathDirections(int x, int z)
{
    FieldBlock *block = FieldUnits_GetBlock(x >> 4, z >> 4);
    if (block == NULL) {
        return 0;
    }
    int high;
    const u8 *byte = collision_map_path_byte(block, x, z, &high);
    return high ? *byte >> 4 : *byte & 0x0f;
}
CLEAN_AS(func_02031a08, CollisionMap_PathDirections)
