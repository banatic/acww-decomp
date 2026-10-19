/* The hands of a clock model, turned by the time of day: hooks that overlay 3's clock
 * (ov003/outdoor_clock.h) and overlay 4's room objects (ov004/room_object_methods.h) run while
 * NitroSystem describes the joint of a hand, turning the joint's rotation about z. The hour
 * hand's angle is worked out once per frame (data_021fbdd0) and kept for every clock. */
#ifndef CLEAN_MAIN_CLOCK_HANDS_H
#define CLEAN_MAIN_CLOCK_HANDS_H

#include "main/g3d_render.h"
#include "types.h"

void ClockHands_TurnMinuteHand(G3dRenderState *state);
void ClockHands_TurnHourHand(G3dRenderState *state);

#endif
