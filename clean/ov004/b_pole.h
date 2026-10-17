/* A room object of the RMO family (rmo_object.h; vtable 0x02255290, 0x290 bytes) built from
 * the archive /roomObj/obj_b_pole: its model plays its first joint animation over and over and
 * does nothing else. */
#ifndef CLEAN_OV004_B_POLE_H
#define CLEAN_OV004_B_POLE_H

#include "rmo_object.h"
#include "types.h"

typedef struct BPole {
    RmoObject base;
} BPole;

int BPole_Release(BPole *self);
int BPole_Draw(BPole *self);
int BPole_Update(BPole *self);
int BPole_Start(BPole *self);
BPole *BPole_Delete(BPole *self);
BPole *BPole_Destruct(BPole *self);
BPole *BPole_Construct(BPole *self);
void BPole_Create(void);

#endif
