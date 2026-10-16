/* A scene object of overlay 3 (class Obj_ov003_022398e8, vtable 0x022398e8, receiver part
 * 0x022399ac, 0x2b4 bytes; profile 0x27) that only marks a spot: set up (vtable slot 0x70), it
 * asks main's spawner (main/spawner.h) for an actor of profile 0x60 (the spawn table's code
 * 0xd015, in overlay 72) in the current scene, where it stands. Its update, its drawing and its
 * slot 0x0c do nothing. It is derived from overlay 9's scene actor (ov009/scene_actor.h) and
 * adds nothing to it. What character profile 0x60 is, is not read from this code. */
#ifndef CLEAN_OV003_SPAWN_SPOT_H
#define CLEAN_OV003_SPAWN_SPOT_H

#include "ov009/scene_actor.h"
#include "types.h"

typedef struct SpawnSpot {
    SceneActor actor;
} SpawnSpot;

int SpawnSpot_Slot0C(void);
int SpawnSpot_Draw(void);
int SpawnSpot_Update(void);
int SpawnSpot_SetUp(SpawnSpot *spot);
SpawnSpot *SpawnSpot_DestroyAndFree(SpawnSpot *spot);
SpawnSpot *SpawnSpot_Destroy(SpawnSpot *spot);
SpawnSpot *SpawnSpot_Construct(SpawnSpot *spot);
void SpawnSpot_New(void);
SpawnSpot *SpawnSpot_ReceiverDestroyAndFree(void *receiver);
SpawnSpot *SpawnSpot_ReceiverDestroy(void *receiver);

#endif
