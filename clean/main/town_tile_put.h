/* Putting an item code on a tile of a map: on a tile numbered across the map
 * (TownTilePut_At) or within an acre (TownTilePut_InAcre), marking or unmarking the tile; on
 * the map of a scene (TownTilePut_OnScene: the town in scenes 0 and 31, else the room of that
 * number); and telling the current scene's overlay of a tile's new item
 * (TownTilePut_TellScene). */
#ifndef CLEAN_MAIN_TOWN_TILE_PUT_H
#define CLEAN_MAIN_TOWN_TILE_PUT_H

#include "acre_map.h"
#include "town_day.h"
#include "types.h"

void TownTilePut_InAcre(TownDay *town, AcreMap *map, u32 acre_x, u32 acre_z, u32 x, u32 z, u16 code, u32 marked);
void TownTilePut_At(AcreMap *map, u32 x, u32 z, u16 code, u32 marked);
void TownTilePut_OnScene(int scene, int x, int z, int code, int marked);
void TownTilePut_TellScene(int x, int z, int code, int result);

#endif
