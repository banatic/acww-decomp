/* A clock of overlay 3 (class Obj_ov003_022390e8, vtable 0x022390e8, receiver part 0x022391ac,
 * 0x2b8 bytes): a scene object whose model has two joints, "kh_j" and "km_j", turned like the
 * hands of a clock by the time of day: the hour hand by main's func_020b3220 (hours and
 * minutes), the minute hand by func_020b3188 (minutes). It is derived from overlay 9's scene
 * actor (Obj_ov009_022658dc), which runs the rest.
 *
 * Set up (slot 0x70), it finds the two joints of its model and, when both are there, gives its
 * model object a hook for each joint's description (func_ov003_0221db90), which hands the joint
 * to vtable slot 0x60 (OutdoorClock_TurnHand). */
#ifndef CLEAN_OV003_OUTDOOR_CLOCK_H
#define CLEAN_OV003_OUTDOOR_CLOCK_H

#include "main/g3d_render.h"
#include "types.h"

typedef struct OutdoorClock {
    const void *vtable; /* data_ov003_022390e8 */
    u8 unk_04[0xec - 0x04];
    const void *receiver_vtable; /* data_ov003_022391ac */
    u8 unk_F0[0x13c - 0xf0];
    u8 model_object[0x198 - 0x13c]; /* overlay 9's model object (Obj_020dd05c) */
    void *model;                    /* that model object's model */
    u8 unk_19C[0x2b4 - 0x19c];
    s8 hour_node;   /* the index of the joint "kh_j" in the model, -1 for none */
    s8 minute_node; /* the index of the joint "km_j" in the model, -1 for none */
    u8 unk_2B6[2];
} OutdoorClock;

int OutdoorClock_Slot98(void);
void OutdoorClock_TurnHand(OutdoorClock *clock, int node, G3dRenderState *state);
int OutdoorClock_Init(OutdoorClock *clock);
OutdoorClock *OutdoorClock_DestroyAndFree(OutdoorClock *clock);
OutdoorClock *OutdoorClock_Destroy(OutdoorClock *clock);
OutdoorClock *OutdoorClock_Construct(OutdoorClock *clock);
void OutdoorClock_RunNodeHook(G3dRenderState *state);
void OutdoorClock_New(void);
OutdoorClock *OutdoorClock_ReceiverDestroyAndFree(void *receiver);
OutdoorClock *OutdoorClock_ReceiverDestroy(void *receiver);

#endif
