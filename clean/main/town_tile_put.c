/* Putting an item code on a tile of a map (town_tile_put.h). */
#include "town_tile_put.h"

#include "acre_tile.h"
#include "clean.h"
#include "scene_query.h"
#include "ov003/tile_event.h"
#include "ov004/dropped_items.h"

/* func_0204a200: `code` put on tile (x, z) of acre (acre_x, acre_z) of the map (layer 0), the
 * tile marked or unmarked. */
void TownTilePut_InAcre(TownDay *town, AcreMap *map, u32 acre_x, u32 acre_z, u32 x, u32 z, u16 code, u32 marked)
{
    (void) town;
    u16 item = code;
    AcreTile_SetItemInAcre(map, &item, acre_x, acre_z, (int) x, (int) z, 0);
    if (marked != 0) {
        AcreTile_MarkInAcre(map, acre_x, acre_z, (int) x, (int) z);
    } else {
        AcreTile_UnmarkInAcre(map, acre_x, acre_z, (int) x, (int) z);
    }
}
CLEAN_AS(func_0204a200, TownTilePut_InAcre)

/* func_0204a25c: `code` put on tile (x, z) of the map (layer 0), the tile marked or unmarked. */
void TownTilePut_At(AcreMap *map, u32 x, u32 z, u16 code, u32 marked)
{
    u16 item = code;
    AcreTile_SetItem(map, &item, (int) x, (int) z, 0);
    if (marked != 0) {
        AcreTile_Mark(map, (int) x, (int) z);
    } else {
        AcreTile_Unmark(map, (int) x, (int) z);
    }
}
CLEAN_AS(func_0204a25c, TownTilePut_At)

/* func_0204a2a4: `code` put on tile (x, z) of the map of `scene`: the town's in scenes 0 and 31
 * (the tile marked or unmarked), else the room of that number (its mark left as it is); nothing
 * when there is no such map. */
void TownTilePut_OnScene(int scene, int x, int z, int code, int marked)
{
    u16 item = (u16) code;
    if (SceneQuery_Is0(scene) != 0 || SceneQuery_Is31(scene) != 0) {
        AcreMap *town = (AcreMap *) (uintptr_t) AcreMap_Town();
        if (town != NULL) {
            AcreTile_SetItem(town, &item, x, z, 0);
            if (marked != 0) {
                AcreTile_Mark(town, x, z);
            } else {
                AcreTile_Unmark(town, x, z);
            }
        }
        return;
    }
    AcreMap *room = (AcreMap *) (uintptr_t) AcreMap_RoomByNumber(scene);
    if (room != NULL) {
        AcreTile_SetItem(room, &item, x, z, 0);
    }
}
CLEAN_AS(func_0204a2a4, TownTilePut_OnScene)

/* func_0204a330: the current scene's overlay told that tile (x, z) has `code`: the town's field
 * in scenes 0 and 31 (with `result`), else the room's (with layer 0). */
void TownTilePut_TellScene(int x, int z, int code, int result)
{
    if (SceneQuery_CurrentIs0() != 0 || SceneQuery_CurrentIs31() != 0) {
        TileEvent_SetTownItem(x, z, code, result);
    } else {
        DroppedItems_PutOnMap(x, z, code, 0);
    }
}
CLEAN_AS(func_0204a330, TownTilePut_TellScene)
