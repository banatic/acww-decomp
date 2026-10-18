/* A spot in the middle of the town (part 0x0c of the object at data_021d27ac,
 * block_021d27ac.h): the centre of a tile picked at random among the tiles TownSpot_TileSuits
 * accepts in the town's middle 2 x 2 acres (MiddleSpot_Pick, from the spawner's update while
 * this console is in the session), and a mark the main module's func_020c1904 sets and
 * func_020c1904 and func_020c2098 clear (in scene 0) and MiddleSpot_Pick clears;
 * func_020c1b9c clears the whole spot. The spawner's placers Spawner_PlaceFromPartC and
 * Spawner_PlaceFromPartCOrRoom put an actor there; Spawner_CheckD022In tests the mark. */
#ifndef CLEAN_MAIN_MIDDLE_SPOT_H
#define CLEAN_MAIN_MIDDLE_SPOT_H

#include "autoload_2/vector.h"
#include "types.h"

typedef struct MiddleSpot {
    fx32 x;  /* 0x00 */
    fx32 z;  /* 0x04 */
    u8 mark; /* 0x08 */
    u8 unused_09[3];
} MiddleSpot;

void MiddleSpot_ClearMark(MiddleSpot *spot);
void MiddleSpot_SetMark(MiddleSpot *spot);
int MiddleSpot_HasMark(const MiddleSpot *spot);
void MiddleSpot_ToPosition(const MiddleSpot *spot, Vec3 *position);
void MiddleSpot_SetFromPosition(MiddleSpot *spot, const Vec3 *position);
void MiddleSpot_Pick(MiddleSpot *spot);
void MiddleSpot_Clear(MiddleSpot *spot);
void MiddleSpot_Destruct(MiddleSpot *spot);
void MiddleSpot_Construct(MiddleSpot *spot);

#endif
