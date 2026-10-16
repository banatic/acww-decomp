/* A spot of the town (part 0x04 of the object at data_021d27ac, block_021d27ac.h): a point in
 * the ground plane, picked at random among the tiles func_02088024 accepts in the town's inner
 * acres (TownSpot_PickRandom). The spawner places an actor there (Spawner_PlaceFromPart4). */
#ifndef CLEAN_MAIN_TOWN_SPOT_H
#define CLEAN_MAIN_TOWN_SPOT_H

#include "acre_map.h"
#include "autoload_2/vector.h"
#include "types.h"

typedef struct TownSpot {
    fx32 x; /* 0x00 */
    fx32 z; /* 0x04 */
} TownSpot;

/* An acre of a map, by its column and row. */
typedef struct TownSpotAcre {
    int x;
    int z;
} TownSpotAcre;

int TownSpot_ToPosition(const TownSpot *spot, Vec3 *position);
void TownSpot_Set(TownSpot *spot, u32 x, u32 z);
int TownSpot_PickRandom(TownSpot *spot);
int TownSpot_PickTileInAcre(TownSpot *spot, Vec3 *position, const TownSpotAcre *acre, AcreMap *map);
int TownSpot_CountTilesInAcre(TownSpot *spot, const TownSpotAcre *acre, AcreMap *map);
void TownSpot_Clear(TownSpot *spot);
void TownSpot_Construct(TownSpot *spot);
void TownSpot_Destruct(TownSpot *spot);
/* Whether an actor may be put on a tile: also used by the spots of near_spot.h and
 * middle_spot.h. */
int TownSpot_TileSuits(int x, int z, AcreMap *map);

#endif
