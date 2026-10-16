/* The compass: a class of overlay 4's room objects (vtable 0x02251c6c, receiver part 0x02251d18,
 * 0x854 bytes) whose model has a node named "compass", its needle. When the model draws that
 * node, the needle is turned about Y against the object's facing (and that of what it stands
 * on), so that it keeps one direction in the room, plus a deflection that wobbles after the
 * object turns:
 *
 * - at the 8th frame of a turn the swing is set to +45 degrees (turning towards a lower angle)
 *   or -45 (the other way);
 * - each frame the swing decays towards 0 by 5.625 degrees, a phase advances while it is not 0,
 *   and the deflection follows the swing times the phase, by at most 5.625 degrees a frame. */
#ifndef CLEAN_OV004_COMPASS_H
#define CLEAN_OV004_COMPASS_H

#include "types.h"

#include "room_object.h"
#include "room_object_methods.h"

typedef struct Compass {
    RoomObject base;
    s16 needle;      /* the node "compass", -1 until the model is bound */
    s16 turn_frames; /* frames since the last turn started */
    u16 phase;       /* the wobble's phase, 0x960 a frame */
    u8 unk_84a[2];
    int swing;      /* degrees, 20.12 fixed point */
    int deflection; /* degrees, 20.12 fixed point */
} Compass;

void Compass_NeedleHook(Compass *compass, int node, NodeHookState *state);
void Compass_OnTurnFrame(Compass *compass, int down);
Compass *Compass_OnTurnStart(Compass *compass);
int Compass_Vfunc0C(void);
int Compass_Update(Compass *compass);
int Compass_Start(Compass *compass);
Compass *Compass_Delete(Compass *compass);
Compass *Compass_Destroy(Compass *compass);
Compass *Compass_Construct(Compass *compass);
void Compass_Create(void);

#endif
