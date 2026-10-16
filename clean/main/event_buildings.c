/* Buildings that come and go with the calendar's events (event_buildings.h). */
#include "event_buildings.h"

#include "clean.h"
#include "main/acre_map.h"
#include "main/acre_tile.h"

#define EVENT_BUILDINGS_FIRST 0x5000
#define EVENT_BUILDINGS_LAST 0x5021
#define EVENT_BUILDINGS_500A 0x500a
#define EVENT_BUILDINGS_5020 0x5020

/* The event spot: tile (10, 9) of the first acre whose model has this flag. */
#define EVENT_BUILDINGS_SPOT_ACRE_FLAG 0x200
#define EVENT_BUILDINGS_SPOT_X 10
#define EVENT_BUILDINGS_SPOT_Z 9

/* The town's inner acres, 1 to 4 each way. */
#define EVENT_BUILDINGS_INNER_FIRST 1
#define EVENT_BUILDINGS_INNER_LAST 4
#define EVENT_BUILDINGS_ACRE_TILES 16
/* An acre with any of these flags never has its 0x500a turned. */
#define EVENT_BUILDINGS_NO_TURN_FLAGS_1 0xe0
#define EVENT_BUILDINGS_NO_TURN_FLAGS_2 0x10
/* The event whose end turns 0x5020 back, and that EventBuildings_Place5020 marks. */
#define EVENT_BUILDINGS_EVENT_5020 0x44
/* A position's acre: its x and z over 0x20000. */
#define EVENT_BUILDINGS_ACRE_SHIFT 17

/* The function-local static item codes of EventBuildings_Revert5020, their guards and their
 * destruction records. */
extern u16 data_021f4b20; /* 0x5020 */
extern u32 data_021f4b38;
extern u8 data_021f4b88[];
extern u16 data_021f4b24; /* 0x500a */
extern u32 data_021f4b4c;
extern u8 data_021f4b94[];
/* A counter that EventBuildings_Place5020 clears (func_02087a78 reads it). */
extern u8 data_021ebcd2[];

extern void __register_global_object(void *object, void *destruct, void *record);
extern void func_020051b0(void *item); /* the item code's destructor (does nothing) */

/* Acre records: searching a layer for a code in [*first, *last] (the tile to *x, *z), whether
 * the acre has any of the flags, the code of tile (x, z) in a layer (or 0), and setting it. */
extern int func_02037da8(u8 *acre, int *x, int *z, u16 *first, u16 *last, u8 layer);
extern int func_02037d64(u8 *acre, int flags);
extern u16 *func_02037e0c(u8 *acre, int x, int z, u8 layer);
extern int func_02037e44(u8 *acre, u16 *code, int x, int z, u8 layer);
/* Item codes (item_code.h): whether a code has a variant, and its item. */
extern int func_0204bcdc(u16 *code);
extern int func_0204bc64(u16 *code);
/* A random number below `bound`. */
extern u32 func_020644cc(int bound);
/* Clears the byte at `counter` (MI_CpuFill8). */
extern void func_020871b0(u8 *counter);
/* Marks event `event` (func_020479e0 on data_021c779c). */
extern void func_02046640(int event);
/* Empties the tiles of the inner acres that hold item 0x1568. */
extern void func_02085f48(void);

/* Rounding down as the ARM's arithmetic shift does. */
static int event_buildings_shift_right(int value, int bits)
{
    return value >= 0 ? value >> bits : ~(~value >> bits);
}

/* Acre (x, z) of the map, or 0 outside it or without acre records. */
static u8 *event_buildings_acre(AcreMap *map, int x, int z)
{
    if ((u32) x < (u32) map->acres_wide && (u32) z < (u32) map->acres_high && map->acres != NULL) {
        return map->acres + ACRE_MAP_ACRE_SIZE * (x + z * map->acres_wide);
    }
    return NULL;
}

static int event_buildings_in_range(u16 code)
{
    return code >= EVENT_BUILDINGS_FIRST && code <= EVENT_BUILDINGS_LAST;
}

/* func_020b2a90: the first building 0x5020 found in the inner acres (row by row) turned back
 * into 0x500a; then the tiles holding item 0x1568 are emptied (func_02085f48). Whether one was
 * found and turned.
 * QUIRK: each code is a function-local static, built on first use and registered for
 * destruction (func_020051b0, which does nothing). */
int EventBuildings_Revert5020(void)
{
    AcreMap *town = (AcreMap *) (uintptr_t) AcreMap_Town();
    if (town == NULL) {
        return 0;
    }
    if ((data_021f4b38 & 1) == 0) {
        data_021f4b20 = EVENT_BUILDINGS_5020;
        __register_global_object(&data_021f4b20, (void *) func_020051b0, data_021f4b88);
        data_021f4b38 |= 1;
    }
    for (int z = EVENT_BUILDINGS_INNER_FIRST; z <= EVENT_BUILDINGS_INNER_LAST; z++) {
        for (int x = EVENT_BUILDINGS_INNER_FIRST; x <= EVENT_BUILDINGS_INNER_LAST; x++) {
            u8 *acre = event_buildings_acre(town, x, z);
            if (acre == NULL) {
                continue;
            }
            int tile_x = 0;
            int tile_z = 0;
            if (func_02037da8(acre, &tile_x, &tile_z, &data_021f4b20, &data_021f4b20, 0) == 0) {
                continue;
            }
            if ((data_021f4b4c & 1) == 0) {
                data_021f4b24 = EVENT_BUILDINGS_500A;
                __register_global_object(&data_021f4b24, (void *) func_020051b0, data_021f4b94);
                data_021f4b4c |= 1;
            }
            if (AcreMap_SetBuildingInAcre((int) (uintptr_t) town, x, z, tile_x, tile_z, (int) (uintptr_t) &data_021f4b24)) {
                func_02085f48();
                return 1;
            }
        }
    }
    return 0;
}
CLEAN_AS(func_020b2a90, EventBuildings_Revert5020)

/* One acre of EventBuildings_Place5020: whether a building 0x500a of acre (x, z) became
 * 0x5020; when it did, the counter at data_021ebcd2 is cleared and event 0x44 marked. */
static int event_buildings_place_in(AcreMap *town, int x, int z)
{
    if (EventBuildings_TurnRandom500a(event_buildings_acre(town, x, z), EVENT_BUILDINGS_5020) == 0) {
        return 0;
    }
    func_020871b0(data_021ebcd2);
    func_02046640(EVENT_BUILDINGS_EVENT_5020);
    return 1;
}

/* The inner acres of the columns from `from` towards `to` (by `step`, `to` included), row by
 * row from the first; whether one of them took building 0x5020. */
static int event_buildings_place_in_columns(AcreMap *town, int from, int to, int step)
{
    for (int x = from; step < 0 ? x >= to : x <= to; x += step) {
        for (int z = EVENT_BUILDINGS_INNER_FIRST; z <= EVENT_BUILDINGS_INNER_LAST; z++) {
            if (event_buildings_place_in(town, x, z)) {
                return 1;
            }
        }
    }
    return 0;
}

/* func_020b2b8c: a random building 0x500a of an inner acre becomes 0x5020, taken from the
 * first acre that has one, looking from the acre of `position`: first the columns on one side
 * (lower x first and moving away when `lower_first`, else higher x), then the other acres of
 * its own column, then the columns on the other side, and last its own acre. Whether one was
 * turned. */
int EventBuildings_Place5020(const Vec3 *position, int lower_first)
{
    AcreMap *town = (AcreMap *) (uintptr_t) AcreMap_Town();
    if (town == NULL) {
        return 0;
    }
    int x = event_buildings_shift_right(position->x, EVENT_BUILDINGS_ACRE_SHIFT);
    int z = event_buildings_shift_right(position->z, EVENT_BUILDINGS_ACRE_SHIFT);

    int found;
    if (lower_first != 0) {
        found = event_buildings_place_in_columns(town, x - 1, EVENT_BUILDINGS_INNER_FIRST, -1);
    } else {
        found = event_buildings_place_in_columns(town, x + 1, EVENT_BUILDINGS_INNER_LAST, 1);
    }
    if (found) {
        return 1;
    }

    for (int row = EVENT_BUILDINGS_INNER_FIRST; row <= EVENT_BUILDINGS_INNER_LAST; row++) {
        if (row != z && event_buildings_place_in(town, x, row)) {
            return 1;
        }
    }

    if (lower_first != 0) {
        found = event_buildings_place_in_columns(town, x + 1, EVENT_BUILDINGS_INNER_LAST, 1);
    } else {
        found = event_buildings_place_in_columns(town, x - 1, EVENT_BUILDINGS_INNER_FIRST, -1);
    }
    if (found) {
        return 1;
    }

    return event_buildings_place_in(town, x, z);
}
CLEAN_AS(func_020b2b8c, EventBuildings_Place5020)

/* func_020b2d98: a random one of the acre's buildings 0x500a becomes building `code`; whether
 * it did. Without any, no random number is drawn. */
int EventBuildings_TurnRandom500a(u8 *acre, int code)
{
    int count = EventBuildings_Count500a(acre);
    if (count == 0) {
        return 0;
    }
    int index = (int) func_020644cc(count);
    return EventBuildings_Turn500a(acre, index, code);
}
CLEAN_AS(func_020b2d98, EventBuildings_TurnRandom500a)

/* func_020b2dc4: the acre's building 0x500a number `index` (counting row by row) becomes
 * building `code` (cut to 16 bits); whether it did. An acre with flags 0xe0 or 0x10 has none
 * turned. */
int EventBuildings_Turn500a(u8 *acre, int index, int code)
{
    if (acre == NULL) {
        return 0;
    }
    if (func_02037d64(acre, EVENT_BUILDINGS_NO_TURN_FLAGS_1) != 0 ||
        func_02037d64(acre, EVENT_BUILDINGS_NO_TURN_FLAGS_2) != 0) {
        return 0;
    }
    int count = 0;
    for (int z = 0; z < EVENT_BUILDINGS_ACRE_TILES; z++) {
        for (int x = 0; x < EVENT_BUILDINGS_ACRE_TILES; x++) {
            u16 *tile = func_02037e0c(acre, x, z, 0);
            if (tile == NULL || *tile != EVENT_BUILDINGS_500A) {
                continue;
            }
            if (count == index) {
                u16 building = (u16) code;
                /* QUIRK: when the tile cannot be set, the search goes on and finds no other. */
                if (func_02037e44(acre, &building, x, z, 0) != 0) {
                    return 1;
                }
            }
            count++;
        }
    }
    return 0;
}
CLEAN_AS(func_020b2dc4, EventBuildings_Turn500a)

/* func_020b2e54: the number of the acre's tiles holding building 0x500a; 0 for an acre with
 * flags 0xe0 or 0x10. */
int EventBuildings_Count500a(u8 *acre)
{
    if (acre == NULL) {
        return 0;
    }
    if (func_02037d64(acre, EVENT_BUILDINGS_NO_TURN_FLAGS_1) != 0 ||
        func_02037d64(acre, EVENT_BUILDINGS_NO_TURN_FLAGS_2) != 0) {
        return 0;
    }
    int count = 0;
    for (int z = 0; z < EVENT_BUILDINGS_ACRE_TILES; z++) {
        for (int x = 0; x < EVENT_BUILDINGS_ACRE_TILES; x++) {
            u16 *tile = func_02037e0c(acre, x, z, 0);
            if (tile != NULL && *tile == EVENT_BUILDINGS_500A) {
                count++;
            }
        }
    }
    return count;
}
CLEAN_AS(func_020b2e54, EventBuildings_Count500a)

/* func_020b2eb8 */
void EventBuildings_Remove501e(void)
{
    EventBuildings_RemoveAtSpot(0x501e);
}
CLEAN_AS(func_020b2eb8, EventBuildings_Remove501e)

/* func_020b2ec8 */
void EventBuildings_Put501e(void)
{
    EventBuildings_PutAtSpot(0x501e);
}
CLEAN_AS(func_020b2ec8, EventBuildings_Put501e)

/* func_020b2ed8 */
void EventBuildings_Remove5021(void)
{
    EventBuildings_RemoveAtSpot(0x5021);
}
CLEAN_AS(func_020b2ed8, EventBuildings_Remove5021)

/* func_020b2ee8 */
void EventBuildings_Put5021(void)
{
    EventBuildings_PutAtSpot(0x5021);
}
CLEAN_AS(func_020b2ee8, EventBuildings_Put5021)

/* func_020b2ef8 */
void EventBuildings_Remove5013(void)
{
    EventBuildings_RemoveAtSpot(0x5013);
}
CLEAN_AS(func_020b2ef8, EventBuildings_Remove5013)

/* func_020b2f08 */
void EventBuildings_Put5013(void)
{
    EventBuildings_PutAtSpot(0x5013);
}
CLEAN_AS(func_020b2f08, EventBuildings_Put5013)

/* func_020b2f18: whether building 0x5012 was removed. */
int EventBuildings_Remove5012(void)
{
    return EventBuildings_RemoveAtSpot(0x5012);
}
CLEAN_AS(func_020b2f18, EventBuildings_Remove5012)

/* func_020b2f28 */
void EventBuildings_Put5012(void)
{
    EventBuildings_PutAtSpot(0x5012);
}
CLEAN_AS(func_020b2f28, EventBuildings_Put5012)

/* func_020b2f38: the building at the event spot removed when it is building `code` (for a code
 * with a variant, when their items are the same); what removing it answered, or 0.
 * QUIRK: the range is checked on the code cut to 16 bits, the plain comparison on the whole
 * int, so a code with high bits matches only through its item. */
int EventBuildings_RemoveAtSpot(int code)
{
    if (!event_buildings_in_range((u16) code)) {
        return 0;
    }
    int tile_x;
    int tile_z;
    u16 *spot = EventBuildings_FindSpot(&tile_x, &tile_z);
    if (spot == NULL) {
        return 0;
    }
    int same;
    if (func_0204bcdc(spot)) {
        u16 wanted = (u16) code;
        int own = func_0204bc64(spot);
        same = own == func_0204bc64(&wanted);
    } else {
        same = *spot == code;
    }
    if (!same) {
        return 0;
    }
    unsigned int town = AcreMap_Town();
    if (town == 0) {
        return 0;
    }
    return AcreMap_SetBuildingAt((int) town, tile_x, tile_z, 0);
}
CLEAN_AS(func_020b2f38, EventBuildings_RemoveAtSpot)

/* func_020b2fc4: building `code` (cut to 16 bits) put at the event spot, after removing the
 * building there, if any. */
void EventBuildings_PutAtSpot(int code)
{
    u16 building = (u16) code;
    if (!event_buildings_in_range(building)) {
        return;
    }
    int tile_x;
    int tile_z;
    u16 *spot = EventBuildings_FindSpot(&tile_x, &tile_z);
    if (spot == NULL) {
        return;
    }
    unsigned int town = AcreMap_Town();
    if (town == 0) {
        return;
    }
    if (event_buildings_in_range(*spot)) {
        AcreMap_SetBuildingAt((int) town, tile_x, tile_z, 0);
    }
    AcreMap_ClearBuildingAt((int) town, (int) (uintptr_t) &building, tile_x, tile_z);
}
CLEAN_AS(func_020b2fc4, EventBuildings_PutAtSpot)

/* func_020b3038: the event spot: tile (10, 9) of the first acre (row by row) whose model has
 * flag 0x200. Its tile on the town's map goes to *tile_x and *tile_z, and the address of its
 * code is returned; 0 without one, the tile then left at (0, 0). */
u16 *EventBuildings_FindSpot(int *tile_x, int *tile_z)
{
    *tile_x = 0;
    *tile_z = 0;
    AcreMap *town = (AcreMap *) (uintptr_t) AcreMap_Town();
    if (town == NULL) {
        return NULL;
    }

    int wide = town->acres_wide;
    int high = town->acres_high;
    int x = 0;
    int z = 0;
    int found = 0;
    for (z = 0; z < high; z++) {
        for (x = 0; x < wide; x++) {
            u32 flags = (u32) (uintptr_t) AcreTile_AcreFlags(town, (u32) x, (u32) z);
            if ((flags & EVENT_BUILDINGS_SPOT_ACRE_FLAG) != 0) {
                found = 1;
                break;
            }
        }
        if (found) {
            break;
        }
    }
    if (!found) {
        return NULL;
    }

    AcreTile_TileOfAcre(tile_x, tile_z, x, z, EVENT_BUILDINGS_SPOT_X, EVENT_BUILDINGS_SPOT_Z);
    u8 *acre = event_buildings_acre(town, x, z);
    if (acre == NULL) {
        return NULL;
    }
    return func_02037e0c(acre, EVENT_BUILDINGS_SPOT_X, EVENT_BUILDINGS_SPOT_Z, 0);
}
CLEAN_AS(func_020b3038, EventBuildings_FindSpot)
