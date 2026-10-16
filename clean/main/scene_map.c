/* The process that builds the map of the scene shown (scene_map.h). */
#include "scene_map.h"

#include "acre_templates.h"
#include "acre_tile.h"
#include "clean.h"
#include "house_record.h"
#include "map_item.h"
#include "room_score.h"
#include "scene_kinds.h"
#include "scene_query.h"
#include "town_layout.h"

static_assert(sizeof(Process) == 0x50, "Process");
static_assert(offsetof(SceneMap, acre_items) == 0x54 && sizeof(SceneMap) == 0x5c, "SceneMap");
static_assert(offsetof(SceneMapSetupEnd, param) == 6, "SceneMapSetupEnd");

extern const u32 data_020db898[]; /* this class's vtable */
extern const u32 data_020da13c[]; /* the game's process class's */
extern AcreMap *data_021c80bc;    /* the map of the scene shown, or 0 */
extern Heap *data_021fbe94;       /* the current heap */
/* The field's mode: 0 outdoors, 1 in a room (scene_kinds.c). */
extern u8 data_020e54a8;
extern u8 data_021e9aac[]; /* the town's layout (town_layout.h) */
extern u8 data_021ebcd4[]; /* the house rooms' records */

#define SCENE_MAP_MODE_OUTDOORS 0
#define SCENE_MAP_MODE_ROOM 1
/* The template set of each mode; none for the others. */
#define SCENE_MAP_SET_OUTDOORS 0
#define SCENE_MAP_SET_ROOM 1
#define SCENE_MAP_NO_SET 4
#define SCENE_MAP_VARIANT_MASK 0xfff
#define SCENE_MAP_ITEMS_ALIGN 4
/* The scenes whose map is the town's. */
#define SCENE_MAP_SCENE_TOWN 0
#define SCENE_MAP_SCENE_TOWN_2C 0x2c
#define SCENE_MAP_SCENE_TOWN_31 0x31
#define SCENE_MAP_ACRE_SHIFT 4 /* 16 tiles to an acre */
#define SCENE_MAP_ACRE_MASK 15
#define SCENE_MAP_ACRE_LAST_TILE 15
#define SCENE_MAP_LAYER 0

/* func_0204cf14 (vtable slot 16): the destructor, through the game's process class down to the
 * base's. */
SceneMap *SceneMap_Destroy(SceneMap *self)
{
    self->process.vtable = data_020db898;
    self->process.vtable = data_020da13c;
    Process_Destruct(&self->process);
    return self;
}
CLEAN_AS(func_0204cf14, SceneMap_Destroy)

/* func_0204cf34 (vtable slot 17): destroyed and freed to the auxiliary heap. */
SceneMap *SceneMap_Delete(SceneMap *self)
{
    self->process.vtable = data_020db898;
    self->process.vtable = data_020da13c;
    Process_Destruct(&self->process);
    Heap_FreeAux(self);
    return self;
}
CLEAN_AS(func_0204cf34, SceneMap_Delete)

/* func_0204cf5c (vtable slot 9): drawing has nothing to do. */
int SceneMap_Draw(void)
{
    return 1;
}
CLEAN_AS(func_0204cf5c, SceneMap_Draw)

/* func_0204cf60 (vtable slot 6): executing has nothing to do. */
int SceneMap_Execute(void)
{
    return 1;
}
CLEAN_AS(func_0204cf60, SceneMap_Execute)

/* func_0204cf64 (vtable slot 3): the map freed to the current heap with the acres' items. */
int SceneMap_DeleteMain(SceneMap *self)
{
    Heap *heap = data_021fbe94;
    if (data_021c80bc != NULL) {
        SceneMap_FreeAcreItems(self, heap);
        AcreMap_Release(data_021c80bc, heap);
        Heap_Free(heap, data_021c80bc);
        data_021c80bc = NULL;
    }
    return 1;
}
CLEAN_AS(func_0204cf64, SceneMap_DeleteMain)

/* func_0204cfa4 (vtable slot 0): the map built from the current heap, then the house's edges
 * counted (RoomScore_CountHouseEdges). */
int SceneMap_CreateMain(SceneMap *self)
{
    if (!SceneMap_Build(self, data_021fbe94)) {
        return 0;
    }
    RoomScore_CountHouseEdges();
    return 1;
}
CLEAN_AS(func_0204cfa4, SceneMap_CreateMain)

/* func_0204cfc8: the map made (0x20 bytes from `heap`) unless there is one, then built from
 * the scene's acres (SceneMap_MakeSources) with the current heap; outdoors the growth on the
 * town's rim is cleared (SceneMap_ClearRimGrowth). Without a running scene's setup end the map
 * is built with a size of 0 x 0. Always 1. */
int SceneMap_Build(SceneMap *self, Heap *heap)
{
    self->acre_items = NULL;
    self->acre_count = 0;

    if (data_021c80bc == NULL) {
        data_021c80bc = Heap_Alloc(heap, sizeof(AcreMap));
        if (data_021c80bc != NULL) {
            AcreMap_Init(data_021c80bc);
        }
    }
    if (data_021c80bc == NULL) {
        return 1;
    }

    const SceneMapSetupEnd *end = (const SceneMapSetupEnd *) (uintptr_t) (u32) SceneKinds_SetupEnd();
    Heap *current = data_021fbe94;
    int *models = NULL;
    AcreMapSize size = {0, 0};
    if (end != NULL) {
        size.wide = end->acres_wide;
        size.high = end->acres_high;
        self->acre_count = end->acres_wide * end->acres_high;
        SceneMap_AllocAcreItems(self, current);
        models = end->acre_models;
        SceneMap_SetHouseModel(self, models, self->acre_count);
        self->param = end->param;
    }

    AcreMapSource *sources = SceneMap_MakeSources(self, models, self->acre_count, (int) (uintptr_t) current);
    if (sources != NULL) {
        AcreMap_Build(data_021c80bc, sources, &size, current);
        if (data_020e54a8 == SCENE_MAP_MODE_OUTDOORS) {
            SceneMap_ClearRimGrowth(data_021c80bc);
        }
        Heap_Free(current, sources);
    }
    return 1;
}
CLEAN_AS(func_0204cfc8, SceneMap_Build)

/* func_0204d08c: in the scenes 6 to 8 the first acre's model becomes the one of the house's
 * size (HouseRecord_SizeModel).
 * QUIRK: `self` and `count` are not used. */
void SceneMap_SetHouseModel(SceneMap *self, int *acre_models, int count)
{
    (void) self;
    (void) count;
    if (SceneKinds_CurrentIn6To8()) {
        *acre_models = HouseRecord_SizeModel(data_021ebcd4);
    }
}
CLEAN_AS(func_0204d08c, SceneMap_SetHouseModel)

/* The codes that grow (the growth lines and 0x66-0x6d, map_item.h). */
static int scene_map_grows(u16 code)
{
    return (code >= 0x26 && code <= 0x2a) || (code >= 0x2f && code <= 0x5b) || (code >= 0x5d && code <= 0x61) ||
           (code >= 0x66 && code <= 0x6d) || (code >= 0xc8 && code <= 0xcf);
}

/* One tile of SceneMap_ClearRimGrowth: its unit retyped, then a growing code past its first
 * stage taken off. */
static void scene_map_clear_tile(AcreMap *map, int x, int z, u16 *none)
{
    AcreTile_RetypeUnit(map, x, z);
    u16 *code = AcreTile_ItemInAcre(map, (u32) (x >> SCENE_MAP_ACRE_SHIFT), (u32) (z >> SCENE_MAP_ACRE_SHIFT),
                                    x & SCENE_MAP_ACRE_MASK, z & SCENE_MAP_ACRE_MASK, SCENE_MAP_LAYER);
    if (code != NULL && scene_map_grows(*code) && !MapItem_IsStage0(code)) {
        AcreTile_SetItem(map, none, x, z, SCENE_MAP_LAYER);
    }
}

/* func_0204d0ac: on the edge of the map's inner acres (all but the outer ring of acres) every
 * growing code past its first stage is taken off: along the top row, then down the left and
 * right columns, row by row. Each tile's unit is retyped first (AcreTile_RetypeUnit).
 * QUIRK: the bottom row is not cleared (but for its two corners), and the top left corner is
 * done twice. */
void SceneMap_ClearRimGrowth(AcreMap *map)
{
    if (map == NULL) {
        return;
    }
    int wide = map->acres_wide;
    int high = map->acres_high;
    u16 none = ACRE_MAP_ITEM_NONE;
    int left = 0;
    int top = 0;
    int right = 0;
    int bottom = 0;
    AcreTile_TileOfAcre(&left, &top, 1, 1, 0, 0);
    AcreTile_TileOfAcre(&right, &bottom, wide - 2, high - 2, SCENE_MAP_ACRE_LAST_TILE, SCENE_MAP_ACRE_LAST_TILE);

    for (int x = left; x <= right; x++) {
        scene_map_clear_tile(map, x, top, &none);
    }
    for (int z = top; z <= bottom; z++) {
        scene_map_clear_tile(map, left, z, &none);
        scene_map_clear_tile(map, right, z, &none);
    }
}
CLEAN_AS(func_0204d0ac, SceneMap_ClearRimGrowth)

/* func_0204d3f0: the sources of the scene's acres, from `heap`: the town's, a house room's, a
 * villager's house's (its items, all empty, kept as the first acre's), or one per model of
 * `acre_models` with the items the templates give (SceneMap_AcreItems); 0 without models. */
AcreMapSource *SceneMap_MakeSources(SceneMap *self, int *acre_models, int count, int heap)
{
    if (SceneQuery_Current() == SCENE_MAP_SCENE_TOWN || SceneQuery_Current() == SCENE_MAP_SCENE_TOWN_31 ||
        SceneQuery_Current() == SCENE_MAP_SCENE_TOWN_2C) {
        return TownLayout_MakeSources(data_021e9aac, heap);
    }
    if (SceneKinds_CurrentIsHouseRoom()) {
        return HouseRecord_RoomSource((HouseRecord *) (void *) data_021ebcd4, SceneKinds_CurrentHouseRoomIndex(), heap);
    }
    if (SceneQuery_CurrentIn11()) {
        int villager = SceneQuery_CurrentIndexIn11();
        int items = (int) (uintptr_t) AcreTemplates_EmptyItems(heap, SCENE_MAP_ITEMS_ALIGN);
        SceneMap_SetAcreItems(self, items, 0);
        return AcreMap_MakeVillagerSource(items, villager, heap);
    }
    if (acre_models == NULL || count <= 0) {
        return NULL;
    }
    AcreMapSource *sources = AcreMap_MakeSources(count, heap);
    if (sources == NULL) {
        return NULL;
    }
    for (int i = 0; i < count; i++) {
        sources[i].model = acre_models[i];
        sources[i].items = (u16 *) (uintptr_t) (u32) SceneMap_AcreItems(self, sources[i].model, i, heap);
    }
    return sources;
}
CLEAN_AS(func_0204d3f0, SceneMap_MakeSources)

/* func_0204d4bc: the items of acre `index` of model `model`: outdoors and in a room, when the
 * mode's template set has the model's variant (its low 12 bits), the items made from it
 * (from `heap`) and kept as the acre's; else 0. */
int SceneMap_AcreItems(SceneMap *self, int model, int index, int heap)
{
    u8 mode = data_020e54a8;
    int set = SCENE_MAP_NO_SET;
    if (mode == SCENE_MAP_MODE_OUTDOORS) {
        set = SCENE_MAP_SET_OUTDOORS;
    } else if (mode == SCENE_MAP_MODE_ROOM) {
        set = SCENE_MAP_SET_ROOM;
    }
    int variant = model & SCENE_MAP_VARIANT_MASK;
    int items = 0;
    if (set != SCENE_MAP_NO_SET && AcreTemplates_HasVariant(set, variant) == 1) {
        items = AcreTemplates_NewItems(set, variant, heap, SCENE_MAP_ITEMS_ALIGN);
        SceneMap_SetAcreItems(self, items, index);
    }
    return items;
}
CLEAN_AS(func_0204d4bc, SceneMap_AcreItems)

/* func_0204d530: `items` kept as acre `index`'s (when the array is there and the index below
 * the count). */
void SceneMap_SetAcreItems(SceneMap *self, int items, int index)
{
    if (self->acre_items != NULL && index < self->acre_count) {
        self->acre_items[index] = (u16 *) (uintptr_t) (u32) items;
    }
}
CLEAN_AS(func_0204d530, SceneMap_SetAcreItems)

/* func_0204d544: the acres' items and their array freed to `heap`. */
void SceneMap_FreeAcreItems(SceneMap *self, Heap *heap)
{
    if (self->acre_items == NULL || self->acre_count <= 0) {
        return;
    }
    for (int i = 0; i < self->acre_count; i++) {
        if (self->acre_items[i] != NULL) {
            Heap_Free(heap, self->acre_items[i]);
            self->acre_items[i] = NULL;
        }
    }
    Heap_Free(heap, self->acre_items);
    self->acre_items = NULL;
    self->acre_count = 0;
}
CLEAN_AS(func_0204d544, SceneMap_FreeAcreItems)

/* func_0204d594: the array of the acres' items made from `heap`, all 0 (none for no acres). */
void SceneMap_AllocAcreItems(SceneMap *self, Heap *heap)
{
    if (self->acre_count <= 0) {
        return;
    }
    self->acre_items = Heap_Alloc(heap, (int) ((u32) self->acre_count * sizeof(u16 *)));
    if (self->acre_items != NULL) {
        for (int i = 0; i < self->acre_count; i++) {
            self->acre_items[i] = NULL;
        }
    }
}
CLEAN_AS(func_0204d594, SceneMap_AllocAcreItems)

/* func_0204d5c8: the map of a scene: the town's for 0, a house room's for 1-5, else 0. */
int SceneMap_OfScene(int scene)
{
    if (scene == SCENE_MAP_SCENE_TOWN) {
        return (int) AcreMap_Town();
    }
    if (SceneKinds_IsHouseRoom((unsigned int) scene) == 1) {
        return AcreMap_RoomByNumber(scene);
    }
    return 0;
}
CLEAN_AS(func_0204d5c8, SceneMap_OfScene)

/* func_0204d5f8 (the profile's create): a zeroed object from the auxiliary heap, constructed as
 * a process, then as the game's process class and as this one; NULL when the heap is full. */
SceneMap *SceneMap_Create(void)
{
    SceneMap *self = Heap_AllocAuxZeroed(sizeof(SceneMap));
    if (self != NULL) {
        Process_Construct(&self->process);
        self->process.vtable = data_020da13c;
        self->process.vtable = data_020db898;
    }
    return self;
}
CLEAN_AS(func_0204d5f8, SceneMap_Create)
