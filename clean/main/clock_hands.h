/* The hands of a clock model, turned by the time of day: hooks that overlay 3's clock
 * (ov003/outdoor_clock.h) and overlay 4's room objects (ov004/room_object_methods.h) run while
 * NitroSystem describes the joint of a hand, turning the joint's rotation about z. The hour
 * hand's angle is worked out once per frame (data_021fbdd0) and kept for every clock. */
#ifndef CLEAN_MAIN_CLOCK_HANDS_H
#define CLEAN_MAIN_CLOCK_HANDS_H

#include "main/model_matrix.h" /* Mtx33 */
#include "types.h"

/* A joint's animation result (NitroSystem's NNSG3dJntAnmResult). */
typedef struct ClockHandsJoint {
    u32 flags; /* CLOCK_HANDS_ROTATION_ZERO */
    u8 unk_04[0x28 - 0x04];
    Mtx33 rotation; /* 0x28 */
} ClockHandsJoint;

/* The joint's rotation is the identity and need not be applied
 * (NNS_G3D_JNTANM_RESULTFLAG_ROT_ZERO). */
#define CLOCK_HANDS_ROTATION_ZERO 2

/* What the hook gets: the state of the model being drawn (NitroSystem's NNSG3dRS). */
typedef struct ClockHandsRenderState {
    u8 unk_00[0xb4];
    ClockHandsJoint *joint; /* the joint being described */
} ClockHandsRenderState;

void ClockHands_TurnMinuteHand(ClockHandsRenderState *state);
void ClockHands_TurnHourHand(ClockHandsRenderState *state);

#endif
