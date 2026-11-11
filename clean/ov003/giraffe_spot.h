/* A scene object of overlay 3 (class Obj_ov003_022387a8, vtable 0x022387a8, receiver part
 * 0x0223886c, 0x2b4 bytes) that marks the spot of the giraffe (ov070/giraffe.h): when vtable
 * slot 0x70 runs while event 0x40, her visit, is on for the clock's date and time
 * (func_0203fc78), it asks main's spawner for an actor of profile 0x6c (the halfword at
 * data_ov003_02238784; the spawn table's code 0xd00b, in overlay 70) in the current scene,
 * where it stands (Spawner_RequestAt), as gull_spot.h does for the gull. It moves no player.
 * It is derived from overlay 9's town object actor (Obj_ov009_022658dc), which runs the rest.
 *
 * Its receiver keeps overlay 9's slot 0x14, entered through a thunk this overlay also gives
 * the checkpoint (GiraffeSpot_ReceiverSlot14). */
#ifndef CLEAN_OV003_GIRAFFE_SPOT_H
#define CLEAN_OV003_GIRAFFE_SPOT_H

#include "autoload_2/vector.h" /* Vec3 */
#include "types.h"

typedef struct GiraffeSpot {
    const void *vtable; /* data_ov003_022387a8 */
    u8 unk_04[0x5c - 0x04];
    Vec3 position;
    u8 unk_68[0xec - 0x68];
    const void *receiver_vtable; /* data_ov003_0223886c */
    u8 unk_F0[0x2b4 - 0xf0];
} GiraffeSpot;

void GiraffeSpot_ReceiverSlot14(void *receiver);
int GiraffeSpot_SetUp(GiraffeSpot *object);
GiraffeSpot *GiraffeSpot_Delete(GiraffeSpot *object);
GiraffeSpot *GiraffeSpot_Destruct(GiraffeSpot *object);
GiraffeSpot *GiraffeSpot_Construct(GiraffeSpot *object);
void GiraffeSpot_New(void);
GiraffeSpot *GiraffeSpot_ReceiverDelete(void *receiver);
GiraffeSpot *GiraffeSpot_ReceiverDestruct(void *receiver);

#endif
