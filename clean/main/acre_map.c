/* Maps made of acres (acre_map.h). */
#include "acre_map.h"

#include "autoload_2/heap.h"
#include "clean.h"
#include "town_layout.h"
#include "acre_record.h"
#include "acre_templates.h"
#include "acre_tile.h"
#include "bg_models.h"
#include "building_shapes.h"
#include "collision_map.h"
#include "collision_query.h"
#include "house_record.h"
#include "item_code.h"
#include "rom_file.h"
#include "scene_heaps.h"
#include "scene_kinds.h"
#include "town_posts.h"
#include "villager_furniture.h"
#include "villager_house_items.h"
#include "villager_roster.h"

extern AcreMapTemplate *data_021c80c8;           /* the item templates, or 0 */
extern AcreMapVillager *data_021c80cc;           /* the villager's map, or 0 */
extern AcreMap *data_021c80c0;                   /* the town's map, or 0 */
extern AcreMap *data_021c80e0[ACRE_MAP_ROOMS];   /* the rooms' maps */
extern u32 data_020cb764[ACRE_MAP_TEMPLATES][2]; /* per template: its file, and its records file (AcreTemplates_Read) */
extern int data_020ca0ec;                        /* an acre's width in world units */
extern int data_020ca0e8;                        /* and depth */
extern u8 data_021e5a2c[];                       /* the villagers (0x7ec bytes each) */
extern u8 data_021ebcd4[];                       /* the rooms' records */
extern u8 data_021e9aac[];                       /* the town's layout (town_layout.h) */
extern Heap *data_021c9b34;                      /* the heap of the rooms' acre data */
extern Heap *data_021c9ab0;                      /* the heap of the town's acre data */

extern fx32 FX_Div(fx32 numerator, fx32 denominator);

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
    if (ItemCode_HasVariant(item)) {
        u16 none = ACRE_MAP_ITEM_NONE;
        int own = ItemCode_VariantItem(item);
        return own == ItemCode_VariantItem(&none);
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
        templates[i].data =
            RomFile_Load((const char *) (uintptr_t) data_020cb764[i][0], (struct Heap *) (uintptr_t) heap, 4, &size);
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
        AcreTemplates_FreeAll(data_021c80c8, heap);
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
    CollisionMap_Release(map->map.slot);
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
        map->map.acres = (u8 *) (AcreRecord_NewArray(1, (Heap *) (uintptr_t) heap, -4));
    }
    if (map->items == NULL) {
        map->items = AcreTemplates_EmptyItems(heap, -4);
    }
    AcreMapSource *source = AcreMap_MakeVillagerSource((int) (uintptr_t) map->items, villager, heap);
    if (map->map.acres == NULL || source == NULL || map->items == NULL) {
        return 0;
    }

    map->map.acres_wide = 1;
    map->map.acres_high = 1;
    map->map.world_wide = data_020ca0ec;
    map->map.world_high = data_020ca0e8;
    AcreTile_TileOfAcre(&map->map.tiles_wide, &map->map.tiles_high, map->map.acres_wide, map->map.acres_high, 0, 0);
    CollisionMap_Setup(map->map.acres_wide, map->map.acres_high, 0, map->map.slot);
    void *cache = (void *) (uintptr_t) BgModels_Get();
    int data = BgModels_Data(cache, source->model);
    Vec3 origin = {0, 0, 0};
    AcreRecord_SetUp((AcreRecord *) (void *) map->map.acres, source->model, &origin, source->items,
                     (u16 *) (uintptr_t) source->unk_08, source->extra, 0, data, 0, 0, map->map.slot);
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

    void *record = VillagerRoster_At((VillagerTown *) (void *) data_021e5a2c, (int) (uintptr_t) villager);
    if (record != NULL) {
        VillagerHouseItems_Template(record, &template_set, &variant);
    }
    if (record != NULL && AcreTemplates_FillItems((int) (uintptr_t) items, template_set, variant, (int) (uintptr_t) heap)) {
        VillagerFurniture_FillTemplate(record, items);
        return 1;
    }
    return 0;
}
CLEAN_AS(func_0204dbe4, AcreMap_FillVillagerItems)

/* func_0204dc34: the source of the villager's acre: its model (0x1010 without a villager), and
 * `items` filled for it. 0 when the record cannot be allocated. */
AcreMapSource *AcreMap_MakeVillagerSource(int items, int villager, int heap)
{
    AcreMapSource *source = AcreMap_MakeSources(1, heap);

    if (source != NULL) {
        void *record = VillagerRoster_At((VillagerTown *) (void *) data_021e5a2c, villager);
        source->model = record != NULL ? VillagerHouseItems_RoomModel(record) : 0x1010;
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
        map->acres = (u8 *) (AcreRecord_NewArray(1, (Heap *) (uintptr_t) heap, 4));
    }
    AcreMapSource *source = HouseRecord_RoomSource((HouseRecord *) (void *) data_021ebcd4, room, heap);
    if (map->acres == NULL || source == NULL) {
        return 0;
    }

    map->acres_wide = 1;
    map->acres_high = 1;
    map->world_wide = data_020ca0ec;
    map->world_high = data_020ca0e8;
    AcreTile_TileOfAcre(&map->tiles_wide, &map->tiles_high, map->acres_wide, map->acres_high, 0, 0);
    CollisionMap_Setup(map->acres_wide, map->acres_high, 0, map->slot);
    Vec3 origin = {0, 0, 0};
    AcreRecord_SetUp((AcreRecord *) (void *) map->acres, source->model, &origin, source->items,
                     (u16 *) (uintptr_t) source->unk_08, source->extra, 0, 0, 0, 0, map->slot);
    Heap_Free((Heap *) (uintptr_t) heap, source);
    return 1;
}
CLEAN_AS(func_0204dcb8, AcreMap_BuildRoom)

/* func_0204dd78: releases the map's slot. */
void AcreMap_ReleaseRoomSlot(unsigned int *map)
{
    CollisionMap_Release((int) ((AcreMap *) map)->slot);
}
CLEAN_AS(func_0204dd78, AcreMap_ReleaseRoomSlot)

/* func_0204dd84: sets the room's slot up again and gives its acre its data from
 * data_021c9b34. */
void AcreMap_LoadRoomData(AcreMap *map)
{
    CollisionMap_Setup(map->acres_wide, map->acres_high, 0, map->slot);
    u8 *acre = (u32) map->acres_wide > 0 && (u32) map->acres_high > 0 ? map->acres : NULL;
    if (acre != NULL) {
        int model = AcreRecord_Model((const AcreRecord *) (void *) acre);
        Heap *heap = data_021c9b34;
        BgModels_Get();
        AcreRecord_SetBgModel((AcreRecord *) (void *) acre, 0, (int) (uintptr_t) BgModels_LoadData(model, heap), map->slot);
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
    int model = HouseRecord_RoomModel((int) (uintptr_t) data_021ebcd4, room);
    u8 *acres = ((AcreMap *) map)->acres;
    if (acres != NULL) {
        AcreRecord_SetModel((AcreRecord *) (void *) acres, model);
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
    SceneHeaps_DestroyAcreRooms();
}
CLEAN_AS(func_0204de5c, AcreMap_FreeRooms)

/* func_0204dea0: creates the heap of the rooms' data, then each room that has no map yet; on
 * the first failure frees all the rooms and returns 0. */
int AcreMap_CreateRooms(void *heap)
{
    int ok = 1;

    SceneHeaps_CreateAcreRooms(heap);
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
    if (SceneKinds_IsHouseRoom((unsigned int) number) == 0) {
        return 0;
    }
    return AcreMap_Room(SceneKinds_HouseRoomIndex((unsigned int) number));
}
CLEAN_AS(func_0204df08, AcreMap_RoomByNumber)

/* func_0204df30: room 0-4's map, or 0. */
int AcreMap_Room(int room)
{
    if (HouseRecord_IsRoom(room)) {
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
        shape = BuildingShapes_Of(&item);
    }
    if (shape == NULL) {
        *out = ACRE_MAP_ITEM_NONE;
        return;
    }

    u32 triangles = BuildingShapes_TriangleCount(shape);
    u32 sum_x = 0;
    u32 sum_z = 0;
    for (u32 i = 0; i < triangles; i++) {
        Vec3 a;
        Vec3 b;
        Vec3 c;
        if (BuildingShapes_Triangle(shape, &a, &b, &c, i)) {
            sum_x += (u32) a.x + (u32) b.x + (u32) c.x;
            sum_z += (u32) a.z + (u32) b.z + (u32) c.z;
        }
    }
    fx32 corners = (fx32) ((3u * BuildingShapes_TriangleCount(shape)) << 12);
    fx32 mean_x = FX_Div((fx32) sum_x, corners);
    fx32 front_z = (fx32) ((u32) tile.z + (u32) FX_Div((fx32) sum_z, corners) + 0x1000u);
    int height = CollisionQuery_FloorHeight(0);
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

    if (AcreTile_FindItemAnyFlag(map, &acre_x, &acre_z, &x, &z, &range[0], &range[1], flags, 0)) {
        AcreTile_TileOfAcre(tile_x, tile_z, acre_x, acre_z, x, z);
        AcreTile_TileCentre((Vec3 *) (uintptr_t) position, *tile_x, *tile_z);
        int found_x = *tile_x;
        int found_z = *tile_z;
        u16 *item =
            AcreTile_ItemInAcre(map, acre_map_acre_of(found_x), acre_map_acre_of(found_z), found_x & 15, found_z & 15, 0);
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

    AcreTile_TileOfAcre(&tile_x, &tile_z, acre_x, acre_z, x, z);
    return AcreMap_SetBuildingAt(map, tile_x, tile_z, item);
}
CLEAN_AS(func_0204e3bc, AcreMap_SetBuildingInAcre)

/* func_0204e3f4: func_0204eea4, which puts building `item` (a code's address; empty when 0) on
 * a tile that holds a building. */
int AcreMap_SetBuildingAt(int map, int tile_x, int tile_z, int item)
{
    return AcreTile_ReplaceBuilding((AcreMap *) (uintptr_t) map, tile_x, tile_z, (u16 *) (uintptr_t) item);
}
CLEAN_AS(func_0204e3f4, AcreMap_SetBuildingAt)

/* func_0204e404: func_0204ef24, which replaces building `item` (a code's address) at the tile
 * with code 0xf030. */
int AcreMap_ClearBuildingAt(int map, int item, int tile_x, int tile_z)
{
    return AcreTile_StampBuilding((AcreMap *) (uintptr_t) map, (u16 *) (uintptr_t) item, tile_x, tile_z);
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
    CollisionMap_Release(map->slot);
}
CLEAN_AS(func_0204e420, AcreMap_ReleaseTownSlot)

/* func_0204e42c: empties the heap of the town's data, sets the slot up again and gives every
 * acre its data. */
void AcreMap_LoadTownData(AcreMap *map)
{
    Heap_FreeAll(data_021c9ab0);
    CollisionMap_Setup(map->acres_wide, map->acres_high, 0, map->slot);
    for (int z = 0; z < map->acres_high; z++) {
        for (int x = 0; x < map->acres_wide; x++) {
            u8 *acre = acre_map_acre_at(map, x, z);
            if (acre != NULL) {
                int model = AcreRecord_Model((const AcreRecord *) (void *) acre);
                Heap *heap = data_021c9ab0;
                BgModels_Get();
                AcreRecord_SetBgModel((AcreRecord *) (void *) acre, 0, (int) (uintptr_t) BgModels_LoadData(model, heap),
                                      map->slot);
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
                AcreRecord_SetModel((AcreRecord *) (void *) ((u8 *) acre), *models);
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
        map->acres = (u8 *) (AcreRecord_NewArray(TOWN_LAYOUT_ACRES, (Heap *) (uintptr_t) heap, 4));
    }
    AcreMapSource *sources = TownLayout_MakeSources(data_021e9aac, heap);
    if (map->acres != NULL && sources != NULL) {
        u8 *acre = map->acres;
        AcreMapSource *source = sources;
        map->acres_wide = TOWN_LAYOUT_SIDE;
        map->acres_high = TOWN_LAYOUT_SIDE;
        map->world_wide = (int) ((u32) map->acres_wide * (u32) data_020ca0ec);
        map->world_high = (int) ((u32) map->acres_high * (u32) data_020ca0e8);
        AcreTile_TileOfAcre(&map->tiles_wide, &map->tiles_high, map->acres_wide, map->acres_high, 0, 0);
        for (int z = 0; z < map->acres_high; z++) {
            for (int x = 0; x < map->acres_wide; x++) {
                int coordinates[2] = {x, z};
                Vec3 position = {x << 17, 0, z << 17};
                AcreRecord_SetUpAt((AcreRecord *) (void *) acre, source->model, &position, source->items,
                                   (u16 *) (uintptr_t) source->unk_08, source->extra, 0, 0, coordinates, map->slot);
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
    SceneHeaps_DestroyAcreTown();
}
CLEAN_AS(func_0204e624, AcreMap_FreeTown)

/* func_0204e65c: creates the heap of the town's data, then the town's map when there is none.
 * QUIRK: 1 also when the map already exists or cannot be allocated; a map that fails to build
 * stays allocated. */
int AcreMap_CreateTown(void *heap)
{
    SceneHeaps_CreateAcreTown(heap);
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
extern void *func_020b3ae4(void *object);
extern void __register_global_object(void *object, void *destruct, void *record);

/* func_0204ebb0: builds `map` (slot 0) of size[0] x size[1] acres from `sources`, one per acre
 * row by row, acre (x, z) at (x, 0, z) * 0x20000 with its model's data from the cache.
 * Allocates the acres from `heap` when the map has none; 0 when that fails. */
int AcreMap_Build(AcreMap *map, AcreMapSource *sources, const AcreMapSize *size, void *heap)
{
    int count = size->wide * size->high;

    map->slot = 0;
    if (map->acres == NULL) {
        map->acres = (u8 *) (AcreRecord_NewArray(count, (Heap *) (uintptr_t) heap, 4));
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
    AcreTile_TileOfAcre(&map->tiles_wide, &map->tiles_high, map->acres_wide, map->acres_high, 0, 0);
    if (!(data_021c80d0 & 1)) {
        TownPosts_ConstructSource((CollisionPostSource *) (void *) data_021c80c4);
        __register_global_object(data_021c80c4, (void *) (uintptr_t) func_020b3ae4, data_021c80d4);
        data_021c80d0 |= 1;
    }
    CollisionMap_Setup(map->acres_wide, map->acres_high, (CollisionPostSource *) (uintptr_t) data_021c80c4, map->slot);
    for (int z = 0; z < map->acres_high; z++) {
        for (int x = 0; x < map->acres_wide; x++) {
            int coordinates[2] = {x, z};
            Vec3 position = {(fx32) ((u32) x << 17), 0, (fx32) ((u32) z << 17)};
            int data = (int) (uintptr_t) BgModels_Load((BgModels *) (uintptr_t) BgModels_Get(), source->model);
            AcreRecord_SetUpAt((AcreRecord *) (void *) acre, source->model, &position, source->items,
                               (u16 *) (uintptr_t) source->unk_08, source->extra, (BgModel *) (uintptr_t) data, 0, coordinates,
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
    CollisionMap_Release(map->slot);
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
