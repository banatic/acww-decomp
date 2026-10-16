/* The process that builds the map of the scene shown (data_021c80bc, an AcreMap of acre_map.h)
 * when it is created and frees it when it is deleted. Its vtable is data_020db898 (a subclass
 * of the game's process class data_020da13c), its profile data_020db888; an object is 0x5c
 * bytes.
 *
 * The map's acres come, by the scene: for the town (scenes 0, 0x2c and 0x31) from the town's
 * layout (town_layout.h); for a room of the player's house from the house's records; for a
 * villager's house (SceneQuery_CurrentIn11) from that villager; for any other scene from the
 * scene setup's list of acre models, each acre's items filled from the item templates of the
 * current mode (acre_templates.h). The item arrays made for the acres are kept with the
 * process until it frees the map. */
#ifndef CLEAN_MAIN_SCENE_MAP_H
#define CLEAN_MAIN_SCENE_MAP_H

#include "acre_map.h"
#include "autoload_2/heap.h"
#include "autoload_2/process.h"
#include "types.h"

typedef struct SceneMap {
    Process process;  /* 0x00 */
    u16 param;        /* 0x50: the scene setup end's parameter */
    u8 unk_52[2];     /* 0x52 */
    u16 **acre_items; /* 0x54: per acre, the items made from the templates, or 0 */
    int acre_count;   /* 0x58 */
} SceneMap;

/* What the scene setup's end record (SceneSetupEnd, scene_setup.h) holds for the map. */
typedef struct SceneMapSetupEnd {
    int *acre_models; /* 0x00: acres_wide x acres_high models, row by row */
    u8 acres_wide;    /* 0x04 */
    u8 acres_high;    /* 0x05 */
    u16 param;        /* 0x06 */
} SceneMapSetupEnd;

SceneMap *SceneMap_Destroy(SceneMap *self);
SceneMap *SceneMap_Delete(SceneMap *self);
int SceneMap_Draw(void);
int SceneMap_Execute(void);
int SceneMap_DeleteMain(SceneMap *self);
int SceneMap_CreateMain(SceneMap *self);
int SceneMap_Build(SceneMap *self, Heap *heap);
void SceneMap_SetHouseModel(SceneMap *self, int *acre_models, int count);
void SceneMap_ClearRimGrowth(AcreMap *map);
AcreMapSource *SceneMap_MakeSources(SceneMap *self, int *acre_models, int count, int heap);
int SceneMap_AcreItems(SceneMap *self, int model, int index, int heap);
void SceneMap_SetAcreItems(SceneMap *self, int items, int index);
void SceneMap_FreeAcreItems(SceneMap *self, Heap *heap);
void SceneMap_AllocAcreItems(SceneMap *self, Heap *heap);
int SceneMap_OfScene(int scene);
SceneMap *SceneMap_Create(void);

#endif
