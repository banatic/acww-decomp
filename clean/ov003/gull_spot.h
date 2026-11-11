/* The gull's spot: a scene object of overlay 3 (class Obj_ov003_022398e8, vtable 0x022398e8, receiver part
 * 0x022399ac, 0x2b4 bytes; profile 0x27) that only marks a spot: set up (vtable slot 0x70), it
 * asks main's spawner (main/spawner.h) for an actor of profile 0x60 (the spawn table's code
 * 0xd015, in overlay 72: the gull, ov072/gull.h) in the current scene, where it stands. Its
 * update, its drawing and its slot 0x0c do nothing. It is derived from overlay 9's town object actor
 * (ov009/town_object_actor.h) and adds nothing to it. giraffe_spot.h does the same for the giraffe. */
#ifndef CLEAN_OV003_GULL_SPOT_H
#define CLEAN_OV003_GULL_SPOT_H

#include "ov009/town_object_actor.h"
#include "types.h"

typedef struct GullSpot {
    TownObjectActor actor;
} GullSpot;

int GullSpot_Slot0c(void);
int GullSpot_Draw(void);
int GullSpot_Update(void);
int GullSpot_SetUp(GullSpot *spot);
GullSpot *GullSpot_Delete(GullSpot *spot);
GullSpot *GullSpot_Destruct(GullSpot *spot);
GullSpot *GullSpot_Construct(GullSpot *spot);
void GullSpot_New(void);
GullSpot *GullSpot_ReceiverDelete(void *receiver);
GullSpot *GullSpot_ReceiverDestruct(void *receiver);

#endif
