/* The scene actor of overlay 68 whose talk is the message file "sp_etc_sequence4" (class
 * Obj_ov068_02277750, include/cpp/ov068/Obj_ov068_02277750.h; a SceneActor of overlay 9). It
 * leads this console's player through one of two sequences with the building 0x5000 (its scene
 * actor, ObjectActors_FindByCode), by seventeen states, each an entry (whose answer says whether
 * the state is taken) and an update run each frame (data_ov068_02278774), changed by its member
 * func_ov068_02272a7c. Its slot 0x70 picks the first state by two flags of main
 * (Block020b220c_Flag4b18: state 1; Block020b220c_Flag4b1c: state 10; else state 0).
 *
 * Its animations are those of its vtable's slots 0x64 and 0x68 and of func_ov068_02272dc8
 * (overlay 9's), each started once (AnimatedModel_Start) and stepped each frame until done.
 *
 * The first sequence (states 1-9):
 *   1 waits for the player; 2 plays the animation of slot 0x64 (sound 0x888); 3 that of slot
 *   0x68 (sound 0x88a) while the player steps out (field actor state 0x87), then turns the
 *   player to it; 4 starts its talk; 5 waits for the talk to close;
 *   6 plays the third animation (sound 0x88b, sound 0x889 each frame) while the player turns
 *     its head to it; 16 frames into a look elsewhere the player walks to building 0x5000's
 *     stand point;
 *   7 waits until the player is no longer busy;
 *   8 asks the player to stand at that point facing 0x8000 (player state 0x39) and sets the
 *     building's mode by kind (SceneActor_SetModeByKindB);
 *   9 20 frames later the player goes into the building: the entry record's exit 9 is taken
 *     and the marked place set 1.0 beyond the stand point, turned half round from it.
 *
 * The second sequence (states 10-16):
 *   10 event flag 1 and object actors' pose flag set;
 *   11 the building's mode set by kind (SceneActor_SetModeByKindA); once it is back in mode 0
 *      and 16 frames have passed, the player walks to 4.0 along z from where it stands;
 *   12 plays the animation of slot 0x64 (sound 0x888 each frame) while the player looks at it;
 *   13 plays that of slot 0x68 (sound 0x88a);
 *   14 the player steps in (field actor state 0x88), looking straight for 30 frames;
 *   15 plays the third animation (sound 0x88b, sound 0x889 each frame);
 *   16 0x41 frames later the current player is gone from the town: event flag 1 cleared, the
 *      entry record's exit set to scene 0x2c, the player's record cleared and forgotten
 *      (StateBlock_ForgetPlayer). */
#ifndef CLEAN_OV068_SEQUENCE4_H
#define CLEAN_OV068_SEQUENCE4_H

#include "autoload_2/vector.h"
#include "ov009/scene_actor.h"
#include "types.h"

typedef struct Sequence4 {
    SceneActor base;   /* vtable data_ov068_02277750 */
    s32 state;         /* 0x2b4: 0-16 */
    int tile_x;        /* 0x2b8: building 0x5000's tile (state 8) */
    int tile_z;        /* 0x2bc */
    Vec3 stand;        /* 0x2c0: where the player stands (states 6 and 8) */
    Vec3 effect_point; /* 0x2cc: where its effects are moved to */
    u16 timer;         /* 0x2d8: state 9 */
    u8 look_frames;    /* 0x2da: state 14 */
    u8 wait;           /* 0x2db: state 11 */
    u8 frames;         /* 0x2dc: state 6, counted up to 200 */
    u8 frames_2dd;     /* 0x2dd: state 3 */
    u8 flag_2de;       /* 0x2de: set when a sequence starts */
} Sequence4;

void Sequence4_UpdateState16(Sequence4 *actor);
int Sequence4_EnterState16(Sequence4 *actor);
void Sequence4_UpdateState15(Sequence4 *actor);
int Sequence4_EnterState15(Sequence4 *actor);
void Sequence4_UpdateState14(Sequence4 *actor);
int Sequence4_EnterState14(Sequence4 *actor);
void Sequence4_UpdateState13(Sequence4 *actor);
int Sequence4_EnterState13(Sequence4 *actor);
void Sequence4_UpdateState12(Sequence4 *actor);
int Sequence4_EnterState12(Sequence4 *actor);
void Sequence4_UpdateState11(Sequence4 *actor);
int Sequence4_EnterState11(Sequence4 *actor);
void Sequence4_UpdateState10(Sequence4 *actor);
int Sequence4_EnterState10(Sequence4 *actor);
void Sequence4_UpdateState9(Sequence4 *actor);
int Sequence4_EnterState9(Sequence4 *actor);
void Sequence4_UpdateState8(Sequence4 *actor);
int Sequence4_EnterState8(Sequence4 *actor);
void Sequence4_UpdateState7(Sequence4 *actor);
int Sequence4_EnterState7(Sequence4 *actor);
void Sequence4_UpdateState6(Sequence4 *actor);
int Sequence4_EnterState6(Sequence4 *actor);
void Sequence4_UpdateState5(Sequence4 *actor);
int Sequence4_EnterState5(Sequence4 *actor);
void Sequence4_UpdateState4(Sequence4 *actor);

#endif
