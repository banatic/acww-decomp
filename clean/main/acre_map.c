/* Maps made of acres (acre_map.h). */
#include "acre_map.h"

#include "autoload_2/heap.h"
#include "clean.h"
#include "town_layout.h"

extern AcreMapTemplate *data_021c80c8;           /* the item templates, or 0 */
extern AcreMapVillager *data_021c80cc;           /* the villager's map, or 0 */
extern AcreMap *data_021c80c0;                   /* the town's map, or 0 */
extern AcreMap *data_021c80e0[ACRE_MAP_ROOMS];   /* the rooms' maps */
extern u32 data_020cb764[ACRE_MAP_TEMPLATES][2]; /* the templates' file numbers (the second word unused) */
extern int data_020ca0ec;                        /* an acre's width in world units */
extern int data_020ca0e8;                        /* and depth */
extern u8 data_021e5a2c[];                       /* the villagers (0x7ec bytes each) */
extern u8 data_021ebcd4[];                       /* the rooms' records */
extern u8 data_021e9aac[];                       /* the town's layout (town_layout.h) */
extern Heap *data_021c9b34;                      /* the heap of the rooms' acre data */
extern Heap *data_021c9ab0;                      /* the heap of the town's acre data */

/* A file loaded whole into `heap`, aligned to `align`; its size goes to *size. */
extern void *func_02064b2c(u32 file, u32 heap, int align, u32 *size);
/* Frees the four templates (stops at the first empty one, as it only steps on after a free). */
extern void func_0204d934(AcreMapTemplate *templates, int heap);
/* `count` acre records (func_02037f5c) from `heap`, aligned to `align`, or 0. */
extern u8 *func_02037e90(int count, int heap, int align);
/* 256 item codes, all empty, from `heap`, or 0. */
extern u16 *func_0204d858(int heap, int align);
/* `count` AcreMapSource records from the back of `heap` (model 0x102a, the rest 0), or 0. */
extern AcreMapSource *func_0204f86c(int count, int heap);
/* Fills `items` from item template `template_set` / `variant` (func_0204d708 on the templates);
 * 0 without templates. */
extern int func_0204d7f8(void *items, int template_set, int variant, void *heap);
/* A villager's record, or 0 when there is none. */
extern void *func_0207cec0(void *villagers, int villager);
/* The template set and variant of a villager's items (left alone when it has none). */
extern int func_0207ffdc(void *villager, int *template_set, int *variant);
/* Copies a villager's own items over `items`. */
extern void func_0207f4c8(void *villager, void *items);
/* The model number of a villager's acre: 0x1010 + 0-4. */
extern int func_0207ffac(void *villager);
/* Sets up entry `slot` of the table at data_021c31ec for a map of acres_wide x acres_high. */
extern int func_02030ddc(int acres_wide, int acres_high, int unk, int slot);
/* Releases entry `slot`. */
extern void func_02030bac(int slot);
/* data_021c52c0, a cache of acre data the next call looks up in. */
extern void *func_0203750c(void);
extern int func_0203776c(void *cache, int model);
/* Sets up an acre: its model, position, items, the rest of the record and its data. */
extern void func_02037f28(u8 *acre, int model, const Vec3 *position, u16 *items, int unk_08, void *extra, int unk_20, int data,
                          int unk_04, int unk_08b, int slot);
/* The same with the acre's coordinates given as a pair. */
extern void func_02037eec(u8 *acre, int model, const Vec3 *position, u16 *items, int unk_08, void *extra, int unk_20, int data,
                          const int *coordinates, int slot);
extern int func_02037e84(u8 *acre);             /* the acre's model number */
extern void func_02037e88(u8 *acre, int model); /* sets it */
/* Gives an acre its data (the 0x180 bytes func_020377d8 loads) and registers it with the slot. */
extern void func_02037ecc(u8 *acre, int unk_20, int data, int slot);
extern int func_020377d8(int model, Heap *heap); /* the 0x180 bytes of the model's data, from `heap` */
/* The rooms' records: room `room`'s acre source (from the back of `heap`), its model number. */
extern AcreMapSource *func_02060eac(void *records, int room, int heap);
extern int func_02060da8(void *records, int room);
extern int func_02060f30(int room);            /* whether 0 <= room < 5 */
extern int func_020b67e8(unsigned int number); /* whether 1 <= number <= 5 */
extern int func_020b6818(unsigned int number); /* number - 1, or -1 */
/* Creates and destroys the heaps of the rooms' and the town's acre data. */
extern void func_0205c10c(void *heap);
extern void func_0205c0f0(void);
extern void func_0205c158(void *heap);
extern void func_0205c13c(void);
/* Item codes (item_code.h): whether a code has a variant (kinds 3 and 4), and its item. */
extern int func_0204bcdc(u16 *item);
extern int func_0204bc64(u16 *item);
/* Searches the map for a tile whose item is in [*first, *last] and passes `flags`: its acre to
 * (*acre_x, *acre_z) and the tile in the acre to (*x, *z). */
extern int func_0204f3e4(void *map, int *acre_x, int *acre_z, int *x, int *z, u16 *first, u16 *last, u32 flags, int unk);
/* The tile (acre * 16 + offset) on each axis. */
extern void func_0204f800(int *x, int *z, int acre_x, int acre_z, int offset_x, int offset_z);
/* The point at the centre of a tile, at height 0. */
extern void func_0204f794(u32 position, int x, int z);
extern u16 *func_0204f5e0(void *map, int acre_x, int acre_z, int x, int z, int layer);
/* A building's shape (codes 0x5000-0x5021): its triangles. */
extern void *func_020b3b50(u16 *item);
extern u32 func_020b3d90(void *shape);
extern int func_020b3d04(void *shape, Vec3 *a, Vec3 *b, Vec3 *c, u32 index);
extern fx32 FX_Div(fx32 numerator, fx32 denominator);
extern int func_020310c8(int unused); /* 0x200 */
/* Puts building `item` on the tile that holds a building; and takes the building `item` off. */
extern int func_0204eea4(int map, int x, int z, int item);
extern int func_0204ef24(int map, int item, int x, int z);

/* Rounding down as the ARM's arithmetic shift does. */
static int acre_map_acre_of(int tile)
{
    return tile >= 0 ? tile / 16 : -1 - (-1 - tile) / 16;
}

/* The acre (x, z) of the map, or 0 outside it or when it has none. */
static u8 *acre_map_acre_at(const AcreMap *map, int x, int z)
{
    if ((u32) x < (u32) map->acres_wide && (u32) z < (u32) map->acres_high && map->acres != NULL) {
        return map->acres + ACRE_MAP_ACRE_SIZE * (x + z * map->acres_wide);
    }
    return NULL;
}

/* Whether a code is the empty one: for a code with a variant, whether its item is the empty
 * code's item. */
static int acre_map_item_is_none(u16 *item)
{
    if (func_0204bcdc(item)) {
        u16 none = ACRE_MAP_ITEM_NONE;
        int own = func_0204bc64(item);
        return own == func_0204bc64(&none);
    }
    return *item == ACRE_MAP_ITEM_NONE;
}

/* ---- the item templates ---- */

/* func_0204d960: loads the four template files (data_020cb764) into `heap`, aligned to 4. Stops
 * at the first that does not load, leaving it 0 and returning 0. */
int AcreMap_LoadTemplates(AcreMapTemplate *templates, u32 heap)
{
    u32 size = 0;

    for (int i = 0; i < ACRE_MAP_TEMPLATES; i++) {
        templates[i].data = func_02064b2c(data_020cb764[i][0], heap, 4, &size);
        if (templates[i].data == NULL) {
            templates[i].halfwords = 0;
            return 0;
        }
        templates[i].halfwords = size >> 1;
    }
    return 1;
}
CLEAN_AS(func_0204d960, AcreMap_LoadTemplates)

/* func_0204d9ac: frees the templates and their array. */
void AcreMap_FreeTemplateSet(int heap)
{
    if (data_021c80c8 != NULL) {
        func_0204d934(data_021c80c8, heap);
        Heap_Free((Heap *) (uintptr_t) heap, data_021c80c8);
        data_021c80c8 = NULL;
    }
}
CLEAN_AS(func_0204d9ac, AcreMap_FreeTemplateSet)

/* func_0204d9d8: allocates the templates' array (0x20 bytes) and loads them; on failure frees
 * what was loaded. 1 when they are loaded; 0 also when they already were. */
int AcreMap_CreateTemplateSet(int heap)
{
    if (data_021c80c8 != NULL) {
        return 0;
    }
    data_021c80c8 = Heap_Alloc((Heap *) (uintptr_t) heap, sizeof(AcreMapTemplate) * ACRE_MAP_TEMPLATES);
    if (data_021c80c8 == NULL) {
        return 0;
    }
    AcreMap_ClearTemplates(data_021c80c8);
    if (AcreMap_LoadTemplates(data_021c80c8, (u32) heap)) {
        return 1;
    }
    AcreMap_FreeTemplateSet(heap);
    data_021c80c8 = NULL;
    return 0;
}
CLEAN_AS(func_0204d9d8, AcreMap_CreateTemplateSet)

/* func_0204da2c */
void AcreMap_ClearTemplates(AcreMapTemplate *templates)
{
    for (int i = 0; i < ACRE_MAP_TEMPLATES; i++) {
        templates[i].data = NULL;
        templates[i].halfwords = 0;
    }
}
CLEAN_AS(func_0204da2c, AcreMap_ClearTemplates)

/* ---- the villager's map ---- */

/* func_0204da48: releases the villager's map and frees it. */
void AcreMap_FreeVillagerMap(int heap)
{
    if (data_021c80cc != NULL) {
        AcreMap_ReleaseVillager(data_021c80cc, (void *) (uintptr_t) heap);
        Heap_Free((Heap *) (uintptr_t) heap, data_021c80cc);
        data_021c80cc = NULL;
    }
}
CLEAN_AS(func_0204da48, AcreMap_FreeVillagerMap)

/* func_0204da74: frees the acre and the items and releases the map's slot. */
void AcreMap_ReleaseVillager(AcreMapVillager *map, void *heap)
{
    if (map->map.acres != NULL) {
        Heap_Free(heap, map->map.acres);
        map->map.acres = NULL;
    }
    if (map->items != NULL) {
        Heap_Free(heap, map->items);
        map->items = NULL;
    }
    func_02030bac(map->map.slot);
}
CLEAN_AS(func_0204da74, AcreMap_ReleaseVillager)

/* func_0204daac: allocates the villager's map from the back of `heap` and builds it for
 * `villager`; returns it, or 0 (also when it already exists). A map that fails to build is
 * freed. */
int AcreMap_CreateVillagerMap(int villager, int heap)
{
    int result = 0;

    if (data_021c80cc == NULL) {
        data_021c80cc = Heap_AllocBack((Heap *) (uintptr_t) heap, sizeof(AcreMapVillager));
        if (data_021c80cc != NULL) {
            AcreMap_InitVillager(data_021c80cc);
            if (AcreMap_BuildVillager(data_021c80cc, villager, heap)) {
                result = (int) (uintptr_t) data_021c80cc;
            } else {
                AcreMap_FreeVillagerMap(heap);
            }
        }
    }
    return result;
}
CLEAN_AS(func_0204daac, AcreMap_CreateVillagerMap)

/* func_0204dafc: one acre (slot 7) whose items come from the villager's record. Allocates the
 * acre and the items when the map has none, then sets the acre up at the origin.
 * BUG: the source record is freed only on success; when the acre or the items could not be
 * allocated it stays allocated. */
int AcreMap_BuildVillager(AcreMapVillager *map, int villager, int heap)
{
    map->map.slot = ACRE_MAP_SLOT_VILLAGER;
    if (map->map.acres == NULL) {
        map->map.acres = func_02037e90(1, heap, -4);
    }
    if (map->items == NULL) {
        map->items = func_0204d858(heap, -4);
    }
    AcreMapSource *source = AcreMap_MakeVillagerSource((int) (uintptr_t) map->items, villager, heap);
    if (map->map.acres == NULL || source == NULL || map->items == NULL) {
        return 0;
    }

    map->map.acres_wide = 1;
    map->map.acres_high = 1;
    map->map.world_wide = data_020ca0ec;
    map->map.world_high = data_020ca0e8;
    func_0204f800(&map->map.tiles_wide, &map->map.tiles_high, map->map.acres_wide, map->map.acres_high, 0, 0);
    func_02030ddc(map->map.acres_wide, map->map.acres_high, 0, map->map.slot);
    void *cache = func_0203750c();
    int data = func_0203776c(cache, source->model);
    Vec3 origin = {0, 0, 0};
    func_02037f28(map->map.acres, source->model, &origin, source->items, source->unk_08, source->extra, 0, data, 0, 0,
                  map->map.slot);
    Heap_Free((Heap *) (uintptr_t) heap, source);
    return 1;
}
CLEAN_AS(func_0204dafc, AcreMap_BuildVillager)

/* func_0204dbe4: fills `items` from the template set the villager names (set 2, variant 0 when
 * it names none), then puts the villager's own items over them. 0 when there is no such
 * villager or no templates. */
int AcreMap_FillVillagerItems(void *items, void *villager, void *heap)
{
    int template_set = 2;
    int variant = 0;

    void *record = func_0207cec0(data_021e5a2c, (int) (uintptr_t) villager);
    if (record != NULL) {
        func_0207ffdc(record, &template_set, &variant);
    }
    if (record != NULL && func_0204d7f8(items, template_set, variant, heap)) {
        func_0207f4c8(record, items);
        return 1;
    }
    return 0;
}
CLEAN_AS(func_0204dbe4, AcreMap_FillVillagerItems)

/* func_0204dc34: the source of the villager's acre: its model (0x1010 without a villager), and
 * `items` filled for it. 0 when the record cannot be allocated. */
AcreMapSource *AcreMap_MakeVillagerSource(int items, int villager, int heap)
{
    AcreMapSource *source = func_0204f86c(1, heap);

    if (source != NULL) {
        void *record = func_0207cec0(data_021e5a2c, villager);
        source->model = record != NULL ? func_0207ffac(record) : 0x1010;
        AcreMap_FillVillagerItems((void *) (uintptr_t) items, (void *) (uintptr_t) villager, (void *) (uintptr_t) heap);
        source->items = (u16 *) (uintptr_t) items;
        source->unk_08 = 0;
        source->extra = NULL;
    }
    return source;
}
CLEAN_AS(func_0204dc34, AcreMap_MakeVillagerSource)

/* func_0204dc88 */
void AcreMap_InitVillager(AcreMapVillager *map)
{
    map->map.acres = NULL;
    map->map.acres_wide = 0;
    map->map.acres_high = 0;
    map->map.tiles_wide = 0;
    map->map.tiles_high = 0;
    map->map.slot = ACRE_MAP_SLOT_VILLAGER;
    map->items = NULL;
}
CLEAN_AS(func_0204dc88, AcreMap_InitVillager)

/* ---- the rooms ---- */

/* func_0204dc9c: frees a map's acres. */
void AcreMap_FreeAcres(void *map, void *heap)
{
    AcreMap *self = map;

    if (self->acres != NULL) {
        Heap_Free(heap, self->acres);
        self->acres = NULL;
    }
}
CLEAN_AS(func_0204dc9c, AcreMap_FreeAcres)

/* func_0204dcb8: room `room`'s map: one acre (slot 2 + room) from the room's record, set up at
 * the origin.
 * BUG: the source record is freed only on success, as in AcreMap_BuildVillager. */
int AcreMap_BuildRoom(AcreMap *map, int room, int heap)
{
    map->slot = room + ACRE_MAP_SLOT_FIRST_ROOM;
    if (map->acres == NULL) {
        map->acres = func_02037e90(1, heap, 4);
    }
    AcreMapSource *source = func_02060eac(data_021ebcd4, room, heap);
    if (map->acres == NULL || source == NULL) {
        return 0;
    }

    map->acres_wide = 1;
    map->acres_high = 1;
    map->world_wide = data_020ca0ec;
    map->world_high = data_020ca0e8;
    func_0204f800(&map->tiles_wide, &map->tiles_high, map->acres_wide, map->acres_high, 0, 0);
    func_02030ddc(map->acres_wide, map->acres_high, 0, map->slot);
    Vec3 origin = {0, 0, 0};
    func_02037f28(map->acres, source->model, &origin, source->items, source->unk_08, source->extra, 0, 0, 0, 0, map->slot);
    Heap_Free((Heap *) (uintptr_t) heap, source);
    return 1;
}
CLEAN_AS(func_0204dcb8, AcreMap_BuildRoom)

/* func_0204dd78: releases the map's slot. */
void AcreMap_ReleaseRoomSlot(unsigned int *map)
{
    func_02030bac((int) ((AcreMap *) map)->slot);
}
CLEAN_AS(func_0204dd78, AcreMap_ReleaseRoomSlot)

/* func_0204dd84: sets the room's slot up again and gives its acre its data from
 * data_021c9b34. */
void AcreMap_LoadRoomData(AcreMap *map)
{
    func_02030ddc(map->acres_wide, map->acres_high, 0, map->slot);
    u8 *acre = (u32) map->acres_wide > 0 && (u32) map->acres_high > 0 ? map->acres : NULL;
    if (acre != NULL) {
        int model = func_02037e84(acre);
        Heap *heap = data_021c9b34;
        func_0203750c();
        func_02037ecc(acre, 0, func_020377d8(model, heap), map->slot);
    }
}
CLEAN_AS(func_0204dd84, AcreMap_LoadRoomData)

/* func_0204dde0: empties the heap of the rooms' data and loads it again for every room. */
void AcreMap_LoadRoomsData(void)
{
    Heap_FreeAll(data_021c9b34);
    for (int i = 0; i < ACRE_MAP_ROOMS; i++) {
        if (data_021c80e0[i] != NULL) {
            AcreMap_LoadRoomData(data_021c80e0[i]);
        }
    }
}
CLEAN_AS(func_0204dde0, AcreMap_LoadRoomsData)

/* func_0204de14: gives the room's acre the model its record now names. */
void AcreMap_SetRoomModel(int *map, int room)
{
    int model = func_02060da8(data_021ebcd4, room);
    u8 *acres = ((AcreMap *) map)->acres;
    if (acres != NULL) {
        func_02037e88(acres, model);
    }
}
CLEAN_AS(func_0204de14, AcreMap_SetRoomModel)

/* func_0204de34 */
void AcreMap_SetRoomsModels(void)
{
    for (int i = 0; i < ACRE_MAP_ROOMS; i++) {
        if (data_021c80e0[i] != NULL) {
            AcreMap_SetRoomModel((int *) data_021c80e0[i], i);
        }
    }
}
CLEAN_AS(func_0204de34, AcreMap_SetRoomsModels)

/* func_0204de5c: releases and frees every room, then the heap of their data. */
void AcreMap_FreeRooms(int heap)
{
    for (int i = 0; i < ACRE_MAP_ROOMS; i++) {
        if (data_021c80e0[i] != NULL) {
            AcreMap_ReleaseRoomSlot((unsigned int *) data_021c80e0[i]);
            AcreMap_FreeAcres(data_021c80e0[i], (void *) (uintptr_t) heap);
            Heap_Free((Heap *) (uintptr_t) heap, data_021c80e0[i]);
            data_021c80e0[i] = NULL;
        }
    }
    func_0205c0f0();
}
CLEAN_AS(func_0204de5c, AcreMap_FreeRooms)

/* func_0204dea0: creates the heap of the rooms' data, then each room that has no map yet; on
 * the first failure frees all the rooms and returns 0. */
int AcreMap_CreateRooms(void *heap)
{
    int ok = 1;

    func_0205c10c(heap);
    for (int i = 0; i < ACRE_MAP_ROOMS; i++) {
        if (data_021c80e0[i] != NULL) {
            continue;
        }
        data_021c80e0[i] = Heap_Alloc(heap, sizeof(AcreMap));
        if (data_021c80e0[i] == NULL) {
            ok = 0;
            break;
        }
        AcreMap_InitRoom(data_021c80e0[i]);
        if (!AcreMap_BuildRoom(data_021c80e0[i], i, (int) (uintptr_t) heap)) {
            ok = 0;
            break;
        }
    }
    if (!ok) {
        AcreMap_FreeRooms((int) (uintptr_t) heap);
    }
    return ok;
}
CLEAN_AS(func_0204dea0, AcreMap_CreateRooms)

/* func_0204df08: the room numbered 1-5, or 0. */
int AcreMap_RoomByNumber(int number)
{
    if (func_020b67e8((unsigned int) number) == 0) {
        return 0;
    }
    return AcreMap_Room(func_020b6818((unsigned int) number));
}
CLEAN_AS(func_0204df08, AcreMap_RoomByNumber)

/* func_0204df30: room 0-4's map, or 0. */
int AcreMap_Room(int room)
{
    if (func_02060f30(room)) {
        return (int) (uintptr_t) data_021c80e0[room];
    }
    return 0;
}
CLEAN_AS(func_0204df30, AcreMap_Room)

/* func_0204df54: a room's map before it is built (slot 2; the world size is left alone). */
void AcreMap_InitRoom(AcreMap *map)
{
    map->acres = NULL;
    map->acres_wide = 0;
    map->acres_high = 0;
    map->tiles_wide = 0;
    map->tiles_high = 0;
    map->slot = ACRE_MAP_SLOT_FIRST_ROOM;
}
CLEAN_AS(func_0204df54, AcreMap_InitRoom)

/* ---- buildings on a map ---- */

/* func_0204df68: whether the map holds building 0x5020; its tile's centre goes to `position`
 * (a Vec3). */
int AcreMap_FindBuilding5020(int map, int position)
{
    u16 item;
    int tile_x;
    int tile_z;

    AcreMap_FindItem(&item, (void *) (uintptr_t) map, (u32) position, &tile_x, &tile_z, 0x5020, 0x5020, 0);
    return !acre_map_item_is_none(&item);
}
CLEAN_AS(func_0204df68, AcreMap_FindBuilding5020)

/* func_0204dfe0: AcreMap_FindBuildingPoint for building 0x5000 (flags 0x200), moved one tile
 * left and four tiles further along z; the tile too when asked for. */
int AcreMap_FindBuilding5000Front(int map, int *position, int *tile_x, int *tile_z)
{
    u16 item;

    AcreMap_FindBuildingPoint(&item, (void *) (uintptr_t) map, position, tile_x, tile_z, 0x5000, 0x5000, 0x200);
    if (acre_map_item_is_none(&item)) {
        return 0;
    }
    position[0] = (int) ((u32) position[0] - 0x2000u);
    position[2] = (int) ((u32) position[2] + 0x8000u);
    if (tile_x != NULL) {
        (*tile_x)--;
    }
    if (tile_z != NULL) {
        *tile_z += 4;
    }
    return 1;
}
CLEAN_AS(func_0204dfe0, AcreMap_FindBuilding5000Front)

/* func_0204e08c: AcreMap_FindBuildingPoint for building 0x500b (flags 0x400); whether found. */
int AcreMap_HasBuilding500b(int map, int position, int tile_x, int tile_z)
{
    u16 item;

    AcreMap_FindBuildingPoint(&item, (void *) (uintptr_t) map, (int *) (uintptr_t) position, (int *) (uintptr_t) tile_x,
                              (int *) (uintptr_t) tile_z, 0x500b, 0x500b, 0x400);
    return !acre_map_item_is_none(&item);
}
CLEAN_AS(func_0204e08c, AcreMap_HasBuilding500b)

/* func_0204e108: the same for buildings 0x5014-0x501a (flags 1). */
int AcreMap_HasBuilding5014(int map, int position, int tile_x, int tile_z)
{
    u16 item;

    AcreMap_FindBuildingPoint(&item, (void *) (uintptr_t) map, (int *) (uintptr_t) position, (int *) (uintptr_t) tile_x,
                              (int *) (uintptr_t) tile_z, 0x5014, 0x501a, 1);
    return !acre_map_item_is_none(&item);
}
CLEAN_AS(func_0204e108, AcreMap_HasBuilding5014)

/* func_0204e188: the same for building 0x5000 (flags 0x200). */
int AcreMap_HasBuilding5000(int map, int position, int tile_x, int tile_z)
{
    u16 item;

    AcreMap_FindBuildingPoint(&item, (void *) (uintptr_t) map, (int *) (uintptr_t) position, (int *) (uintptr_t) tile_x,
                              (int *) (uintptr_t) tile_z, 0x5000, 0x5000, 0x200);
    return !acre_map_item_is_none(&item);
}
CLEAN_AS(func_0204e188, AcreMap_HasBuilding5000)

/* func_0204e204: finds a building in [first, last] (AcreMap_FindItem) and gives the point in
 * front of it: the tile's centre moved by the mean x and z of the corners of its shape's
 * triangles and one tile further along z, at height 0x200. *out is the building's code, or
 * empty when there is none or it has no shape; then nothing else is written.
 * QUIRK: the sums wrap at 32 bits; a shape without triangles has FX_Div divide by zero. */
void AcreMap_FindBuildingPoint(u16 *out, void *map, int *position, int *tile_x, int *tile_z, u16 first, u16 last, u32 flags)
{
    u16 item;
    Vec3 tile;
    int x;
    int z;

    AcreMap_FindItem(&item, map, (u32) (uintptr_t) &tile, &x, &z, first, last, flags);
    void *shape = NULL;
    if (!acre_map_item_is_none(&item)) {
        shape = func_020b3b50(&item);
    }
    if (shape == NULL) {
        *out = ACRE_MAP_ITEM_NONE;
        return;
    }

    u32 triangles = func_020b3d90(shape);
    u32 sum_x = 0;
    u32 sum_z = 0;
    for (u32 i = 0; i < triangles; i++) {
        Vec3 a;
        Vec3 b;
        Vec3 c;
        if (func_020b3d04(shape, &a, &b, &c, i)) {
            sum_x += (u32) a.x + (u32) b.x + (u32) c.x;
            sum_z += (u32) a.z + (u32) b.z + (u32) c.z;
        }
    }
    fx32 corners = (fx32) ((3u * func_020b3d90(shape)) << 12);
    fx32 mean_x = FX_Div((fx32) sum_x, corners);
    fx32 front_z = (fx32) ((u32) tile.z + (u32) FX_Div((fx32) sum_z, corners) + 0x1000u);
    int height = func_020310c8(0);
    position[0] = (int) ((u32) tile.x + (u32) mean_x);
    position[1] = height;
    position[2] = front_z;
    if (tile_x != NULL) {
        *tile_x = x;
    }
    if (tile_z != NULL) {
        *tile_z = z;
    }
    *out = item;
}
CLEAN_AS(func_0204e204, AcreMap_FindBuildingPoint)

/* func_0204e328: finds a tile whose item is in [first, last] and passes `flags`
 * (func_0204f3e4): the tile to (*tile_x, *tile_z), the centre of the tile to `position` (a
 * Vec3), and its item (layer 0) to *out; empty when there is none, then nothing else is
 * written. */
void AcreMap_FindItem(u16 *out, void *map, u32 position, int *tile_x, int *tile_z, u16 first, u16 last, u32 flags)
{
    u16 range[2] = {first, last};
    int acre_x;
    int acre_z;
    int x;
    int z;

    if (func_0204f3e4(map, &acre_x, &acre_z, &x, &z, &range[0], &range[1], flags, 0)) {
        func_0204f800(tile_x, tile_z, acre_x, acre_z, x, z);
        func_0204f794(position, *tile_x, *tile_z);
        int found_x = *tile_x;
        int found_z = *tile_z;
        u16 *item = func_0204f5e0(map, acre_map_acre_of(found_x), acre_map_acre_of(found_z), found_x & 15, found_z & 15, 0);
        if (item != NULL) {
            *out = *item;
            return;
        }
    }
    *out = ACRE_MAP_ITEM_NONE;
}
CLEAN_AS(func_0204e328, AcreMap_FindItem)

/* func_0204e3bc: AcreMap_SetBuildingAt on the tile (x, z) of acre (acre_x, acre_z). */
int AcreMap_SetBuildingInAcre(int map, int acre_x, int acre_z, int x, int z, int item)
{
    int tile_x = 0;
    int tile_z = 0;

    func_0204f800(&tile_x, &tile_z, acre_x, acre_z, x, z);
    return AcreMap_SetBuildingAt(map, tile_x, tile_z, item);
}
CLEAN_AS(func_0204e3bc, AcreMap_SetBuildingInAcre)

/* func_0204e3f4: func_0204eea4, which puts building `item` (a code's address; empty when 0) on
 * a tile that holds a building. */
int AcreMap_SetBuildingAt(int map, int tile_x, int tile_z, int item)
{
    return func_0204eea4(map, tile_x, tile_z, item);
}
CLEAN_AS(func_0204e3f4, AcreMap_SetBuildingAt)

/* func_0204e404: func_0204ef24, which replaces building `item` (a code's address) at the tile
 * with code 0xf030. */
int AcreMap_ClearBuildingAt(int map, int item, int tile_x, int tile_z)
{
    return func_0204ef24(map, item, tile_x, tile_z);
}
CLEAN_AS(func_0204e404, AcreMap_ClearBuildingAt)

/* ---- the town ---- */

/* func_0204e414: the town's map, or 0. */
unsigned int AcreMap_Town(void)
{
    return (unsigned int) (uintptr_t) data_021c80c0;
}
CLEAN_AS(func_0204e414, AcreMap_Town)

/* func_0204e420 */
void AcreMap_ReleaseTownSlot(AcreMap *map)
{
    func_02030bac(map->slot);
}
CLEAN_AS(func_0204e420, AcreMap_ReleaseTownSlot)

/* func_0204e42c: empties the heap of the town's data, sets the slot up again and gives every
 * acre its data. */
void AcreMap_LoadTownData(AcreMap *map)
{
    Heap_FreeAll(data_021c9ab0);
    func_02030ddc(map->acres_wide, map->acres_high, 0, map->slot);
    for (int z = 0; z < map->acres_high; z++) {
        for (int x = 0; x < map->acres_wide; x++) {
            u8 *acre = acre_map_acre_at(map, x, z);
            if (acre != NULL) {
                int model = func_02037e84(acre);
                Heap *heap = data_021c9ab0;
                func_0203750c();
                func_02037ecc(acre, 0, func_020377d8(model, heap), map->slot);
            }
        }
    }
}
CLEAN_AS(func_0204e42c, AcreMap_LoadTownData)

/* func_0204e4bc: gives every acre the model the town's layout now names, one layout byte per
 * acre in order.
 * QUIRK: the acres are stepped through from the array's address even when it is 0: only the
 * first is then skipped, and the next ones are written at 0x28, 0x50, ... */
void AcreMap_SetTownModels(AcreMap *map)
{
    u8 *models = TownLayout_Get(data_021e9aac);

    if (models == NULL) {
        return;
    }
    uintptr_t acre = (uintptr_t) map->acres;
    for (int z = 0; z < map->acres_high; z++) {
        for (int x = 0; x < map->acres_wide; x++) {
            if (acre != 0) {
                func_02037e88((u8 *) acre, *models);
            }
            acre += ACRE_MAP_ACRE_SIZE;
            models++;
        }
    }
}
CLEAN_AS(func_0204e4bc, AcreMap_SetTownModels)

/* func_0204e510: frees the town's acres. */
void AcreMap_FreeTownAcres(void *map, void *heap)
{
    AcreMap *self = map;

    if (self->acres != NULL) {
        Heap_Free(heap, self->acres);
        self->acres = NULL;
    }
}
CLEAN_AS(func_0204e510, AcreMap_FreeTownAcres)

/* func_0204e52c: the town's map: 6 x 6 acres (slot 1) built from the town's layout
 * (TownLayout_MakeSources), acre (x, z) at (x, 0, z) * 0x20000. Allocates the acres when the map
 * has none. The sources are freed in any case. */
int AcreMap_BuildTown(AcreMap *map, int heap)
{
    int result = 0;

    map->slot = ACRE_MAP_SLOT_TOWN;
    if (map->acres == NULL) {
        map->acres = func_02037e90(TOWN_LAYOUT_ACRES, heap, 4);
    }
    AcreMapSource *sources = TownLayout_MakeSources(data_021e9aac, heap);
    if (map->acres != NULL && sources != NULL) {
        u8 *acre = map->acres;
        AcreMapSource *source = sources;
        map->acres_wide = TOWN_LAYOUT_SIDE;
        map->acres_high = TOWN_LAYOUT_SIDE;
        map->world_wide = (int) ((u32) map->acres_wide * (u32) data_020ca0ec);
        map->world_high = (int) ((u32) map->acres_high * (u32) data_020ca0e8);
        func_0204f800(&map->tiles_wide, &map->tiles_high, map->acres_wide, map->acres_high, 0, 0);
        for (int z = 0; z < map->acres_high; z++) {
            for (int x = 0; x < map->acres_wide; x++) {
                int coordinates[2] = {x, z};
                Vec3 position = {x << 17, 0, z << 17};
                func_02037eec(acre, source->model, &position, source->items, source->unk_08, source->extra, 0, 0, coordinates,
                              map->slot);
                acre += ACRE_MAP_ACRE_SIZE;
                source++;
            }
        }
        result = 1;
    }
    if (sources != NULL) {
        Heap_Free((Heap *) (uintptr_t) heap, sources);
    }
    return result;
}
CLEAN_AS(func_0204e52c, AcreMap_BuildTown)

/* func_0204e624: releases and frees the town's map, then the heap of its data. */
void AcreMap_FreeTown(void *heap)
{
    if (data_021c80c0 != NULL) {
        AcreMap_ReleaseTownSlot(data_021c80c0);
        AcreMap_FreeTownAcres(data_021c80c0, heap);
        Heap_Free(heap, data_021c80c0);
        data_021c80c0 = NULL;
    }
    func_0205c13c();
}
CLEAN_AS(func_0204e624, AcreMap_FreeTown)

/* func_0204e65c: creates the heap of the town's data, then the town's map when there is none.
 * QUIRK: 1 also when the map already exists or cannot be allocated; a map that fails to build
 * stays allocated. */
int AcreMap_CreateTown(void *heap)
{
    func_0205c158(heap);
    if (data_021c80c0 != NULL) {
        return 1;
    }
    data_021c80c0 = Heap_Alloc(heap, sizeof(AcreMap));
    if (data_021c80c0 == NULL) {
        return 1;
    }
    AcreMap_InitTown(data_021c80c0);
    return AcreMap_BuildTown(data_021c80c0, (int) (uintptr_t) heap);
}
CLEAN_AS(func_0204e65c, AcreMap_CreateTown)

/* func_0204e6a4: the town's map before it is built (slot 1; the world size is left alone). */
void AcreMap_InitTown(AcreMap *map)
{
    map->acres = NULL;
    map->acres_wide = 0;
    map->acres_high = 0;
    map->tiles_wide = 0;
    map->tiles_high = 0;
    map->slot = ACRE_MAP_SLOT_TOWN;
}
CLEAN_AS(func_0204e6a4, AcreMap_InitTown)

static_assert(sizeof(AcreMap) == 0x20, "AcreMap size");
static_assert(offsetof(AcreMap, slot) == 0x1c, "AcreMap slot");
static_assert(sizeof(AcreMapVillager) == 0x24, "AcreMapVillager size");
static_assert(sizeof(AcreMapSource) == 0x10, "AcreMapSource size");
static_assert(sizeof(AcreMapTemplate) == 8, "AcreMapTemplate size");

/* ---- maps built from a list of sources ---- */

/* An object the maps hand to func_02030ddc, constructed once (func_020b3afc) and destroyed at
 * exit (func_020b3ae4, registered with the C++ runtime). */
extern u8 data_021c80c4[];
extern u32 data_021c80d0;  /* bit 0: data_021c80c4 is constructed */
extern u8 data_021c80d4[]; /* its record for the C++ runtime */
extern void *func_020b3afc(void *object);
extern void *func_020b3ae4(void *object);
extern void __register_global_object(void *object, void *destruct, void *record);
/* The data of an acre's model, looked up in the cache of acre data (func_0203750c). */
extern int func_02037608(void *cache, int model);

/* func_0204ebb0: builds `map` (slot 0) of size[0] x size[1] acres from `sources`, one per acre
 * row by row, acre (x, z) at (x, 0, z) * 0x20000 with its model's data from the cache.
 * Allocates the acres from `heap` when the map has none; 0 when that fails. */
int AcreMap_Build(AcreMap *map, AcreMapSource *sources, const AcreMapSize *size, void *heap)
{
    int count = size->wide * size->high;

    map->slot = 0;
    if (map->acres == NULL) {
        map->acres = func_02037e90(count, (int) (uintptr_t) heap, 4);
    }
    if (map->acres == NULL) {
        return 0;
    }

    u8 *acre = map->acres;
    AcreMapSource *source = sources;
    map->acres_wide = size->wide;
    map->acres_high = size->high;
    map->world_wide = (int) ((u32) map->acres_wide * (u32) data_020ca0ec);
    map->world_high = (int) ((u32) map->acres_high * (u32) data_020ca0e8);
    func_0204f800(&map->tiles_wide, &map->tiles_high, map->acres_wide, map->acres_high, 0, 0);
    if (!(data_021c80d0 & 1)) {
        func_020b3afc(data_021c80c4);
        __register_global_object(data_021c80c4, (void *) (uintptr_t) func_020b3ae4, data_021c80d4);
        data_021c80d0 |= 1;
    }
    func_02030ddc(map->acres_wide, map->acres_high, (int) (uintptr_t) data_021c80c4, map->slot);
    for (int z = 0; z < map->acres_high; z++) {
        for (int x = 0; x < map->acres_wide; x++) {
            int coordinates[2] = {x, z};
            Vec3 position = {(fx32) ((u32) x << 17), 0, (fx32) ((u32) z << 17)};
            int data = func_02037608(func_0203750c(), source->model);
            func_02037eec(acre, source->model, &position, source->items, source->unk_08, source->extra, data, 0, coordinates,
                          0);
            acre += ACRE_MAP_ACRE_SIZE;
            source++;
        }
    }
    return 1;
}
CLEAN_AS(func_0204ebb0, AcreMap_Build)

/* func_0204ecd4: frees the map's acres to `heap` (when it has them) and releases its slot. */
void AcreMap_Release(AcreMap *map, void *heap)
{
    if (map->acres != NULL) {
        Heap_Free(heap, map->acres);
        map->acres = NULL;
    }
    func_02030bac(map->slot);
}
CLEAN_AS(func_0204ecd4, AcreMap_Release)

/* func_0204ecf8: a map before it is built (slot 0; the world size is left alone). */
void AcreMap_Init(AcreMap *map)
{
    map->acres_wide = 0;
    map->acres_high = 0;
    map->tiles_wide = 0;
    map->tiles_high = 0;
    map->acres = NULL;
    map->slot = 0;
}
CLEAN_AS(func_0204ecf8, AcreMap_Init)

/* The model number a source starts with. */
#define ACRE_MAP_SOURCE_MODEL_DEFAULT 0x102a

/* func_0204f86c: `count` sources from the back of `heap`, each set up by AcreMap_InitSource;
 * 0 when they cannot be allocated. */
AcreMapSource *AcreMap_MakeSources(int count, int heap)
{
    AcreMapSource *sources = Heap_AllocBack((Heap *) (uintptr_t) heap, (int) ((u32) count << 4));

    if (sources != NULL) {
        for (int i = 0; i < count; i++) {
            /* QUIRK: each source's address is checked against 0 before it is set up. */
            uintptr_t source = (uintptr_t) sources + (uintptr_t) ((u32) i << 4);
            if (source != 0) {
                AcreMap_InitSource((AcreMapSource *) source);
            }
        }
    }
    return sources;
}
CLEAN_AS(func_0204f86c, AcreMap_MakeSources)

/* func_0204f89c: model 0x102a, no items, the rest 0. */
void AcreMap_InitSource(AcreMapSource *source)
{
    source->model = ACRE_MAP_SOURCE_MODEL_DEFAULT;
    source->items = NULL;
    source->unk_08 = 0;
    source->extra = NULL;
}
CLEAN_AS(func_0204f89c, AcreMap_InitSource)
