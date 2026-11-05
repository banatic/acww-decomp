/* The town object actor's modes (town_object_actor.h): the byte at 0x134, set through vtable slot 0x6c
 * (TownObjectActor_SetMode) and run each frame through slot 0x74 (TownObjectActor_RunMode). Each mode has
 * an entry, which may refuse it, and a run; both are member pointers in tables
 * (ov004/member_pointer.h). Main is told each new mode (TownObjects_SetRecordedMode), which
 * passes it on to the other systems of a session.
 *
 * The base class's modes move the building's door, playing the model's two animations (vtable
 * slots 0x64 and 0x68, the files "bca0" and "bca1"):
 *
 *   0 still:  the first animation loops. A player of this console who walks into a door of
 *             kind 1 or 3 fast enough, or who stands at its door and is touched with the pen,
 *             asks for an event of kind 6 to go in.
 *   1, 2:     the first (mode 1) or the second (mode 2) animation once, with sounds 0x7d1 and
 *             0x7d2 at the start and 0x7d3 and 0x7d4 at two of its frames; when vtable slot
 *             0x98 says so, the town's melody plays at it too (main/town_tune.h). Then
 *             mode 0.
 *   3 open:   the first animation once, with the door's sound (0x806 for a shop, else
 *             0x808); then mode 4.
 *   4 close:  26 frames later the door's closing sound (0x807 or 0x809), then the second
 *             animation once; then mode 0.
 *   5, 6:     back to mode 0 at once (town_object_actor.c). */
#ifndef CLEAN_OV009_TOWN_OBJECT_ACTOR_MODE_H
#define CLEAN_OV009_TOWN_OBJECT_ACTOR_MODE_H

#include "town_object_actor.h"

#define TOWN_OBJECT_ACTOR_MODES 7

void TownObjectActor_RunMode4(TownObjectActor *actor);
int TownObjectActor_EnterMode4(TownObjectActor *actor);
void TownObjectActor_RunMode3(TownObjectActor *actor);
int TownObjectActor_EnterMode3(TownObjectActor *actor);
void TownObjectActor_RunMode2(TownObjectActor *actor);
int TownObjectActor_EnterMode2(TownObjectActor *actor);
void TownObjectActor_RunMode1(TownObjectActor *actor);
int TownObjectActor_EnterMode1(TownObjectActor *actor);
void TownObjectActor_RunMode0(TownObjectActor *actor);
int TownObjectActor_EnterMode0(TownObjectActor *actor);
void TownObjectActor_RunMode(TownObjectActor *actor);
int TownObjectActor_SetMode(TownObjectActor *actor, unsigned int mode);

#endif
