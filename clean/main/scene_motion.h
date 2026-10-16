/* The motions of kinds 14 to 21 of a scene object (class 0x020d8c64, obj_020d8c64.h): its
 * member at 0x564, the motion (scene_action.h sets kinds 0, 3, 7 and 8 of it).
 *
 * A motion is asked for with a kind, a priority and arguments (`next_*`, func_02019d0c); each
 * frame func_02019af8 starts the one asked for when its priority is at least the running one's,
 * when the running one is done or has priority 3, copying `next_args` to `args`. A kind is an
 * entry of the table at data_021c1ad4 (22 entries of three C++ pointers to member functions,
 * filled at start-up): the start (func_02019d94 calls it once), the run (each frame,
 * func_0201998c) and the after-step (func_02019948); each is called with the motion and the
 * object. The runs here dispatch on `step` through tables of their own; a step past the table
 * ends the run.
 *
 * Kind 21 walks the object to the spot it is to stand on (func_0201bee0 gives the spot's point
 * and angle) through the object's mover (its member at 0x350): it walks when the spot is ahead,
 * turns first when it is behind, and turns to the spot's angle once there. Kinds 14 to 20 play
 * the object's animations (speaker_anim.h) in answer to the object at data_021c9350 (asked by
 * func_02057b90 to func_02057d34), with effects (func_02091230, func_020912d4: a kind, a point
 * and an angle; func_0209129c stops one, func_02091278 moves it) and sounds on the object's
 * emitter at 0x514; when one ends, the motion is done (func_02019af0 with 1). */
#ifndef CLEAN_MAIN_SCENE_MOTION_H
#define CLEAN_MAIN_SCENE_MOTION_H

#include "types.h"

/* A motion's arguments (0x34 bytes; func_02019ea0 clears them). */
typedef struct SceneMotionArgs {
    u8 unk_00[0x22];
    u16 item;    /* 0x22: an item code */
    u32 unk_24;  /* 0x24 */
    u32 partner; /* 0x28: what kind 14's last step hands to func_02057c20 */
    u8 unk_2c[8];
} SceneMotionArgs;

typedef struct SceneMotion {
    s32 pace;                  /* 0x00: 2 picks the mover's mode 2 over 1 for walking */
    u8 note_kind;              /* 0x04: written by SceneMotion_StartKind15 */
    u8 note_priority;          /* 0x05 */
    u8 note[0x0e];             /* 0x06: filled by func_020199ec */
    s32 priority;              /* 0x14 */
    u8 unk_18;                 /* 0x18 */
    u8 hold;                   /* 0x19 */
    u8 unk_1a[2];              /* 0x1a */
    s32 kind;                  /* 0x1c */
    u32 entry;                 /* 0x20: the kind's entry of data_021c1ad4 */
    s32 next_kind;             /* 0x24 */
    s32 next_priority;         /* 0x28 */
    SceneMotionArgs next_args; /* 0x2c */
    SceneMotionArgs args;      /* 0x60: func_02019de4 gives them */
    s32 done;                  /* 0x94: 1 once the motion ended (func_02019af0, func_02019de8) */
    u8 step;                   /* 0x98 */
    u8 unk_99[0x13];           /* 0x99 */
    s32 effect;                /* 0xac: the effect started by kinds 14 and 19, -1 for none */
} SceneMotion;

#define SCENE_MOTION_KIND_20 0x14

int SceneMotion_FinishAnimation(SceneMotion *self, u8 *object, u16 *item, int animation, u8 flag);

void SceneMotion_RunGoToSpot(SceneMotion *self, u8 *object);
void SceneMotion_GoToSpotTurnAtSpot(SceneMotion *self, u8 *object);
void SceneMotion_GoToSpotTurnFirst(SceneMotion *self, u8 *object);
void SceneMotion_GoToSpotWalk(SceneMotion *self, u8 *object);
void SceneMotion_GoToSpotStand(SceneMotion *self, u8 *object);
int SceneMotion_StartGoToSpot(SceneMotion *self, u8 *object);

void SceneMotion_Kind20After(SceneMotion *self, u8 *object);
int SceneMotion_StartKind20(SceneMotion *self, u8 *object);
int SceneMotion_RequestKind20(SceneMotion *self, int priority, u16 *item);

void SceneMotion_Kind19After(SceneMotion *self, u8 *object);
void SceneMotion_RunKind19(SceneMotion *self, u8 *object);
void SceneMotion_Kind19Step0(SceneMotion *self, u8 *object);
int SceneMotion_StartKind19(SceneMotion *self, u8 *object);

void SceneMotion_RunKind18(SceneMotion *self, u8 *object);
void SceneMotion_Kind18Step1(SceneMotion *self, u8 *object);
void SceneMotion_Kind18Step0(SceneMotion *self, u8 *object);
int SceneMotion_StartKind18(SceneMotion *self, u8 *object);

void SceneMotion_RunKind17(SceneMotion *self, u8 *object);
void SceneMotion_Kind17Step2(SceneMotion *self, u8 *object);
void SceneMotion_Kind17Step1(SceneMotion *self, u8 *object);
void SceneMotion_Kind17Step0(SceneMotion *self, u8 *object);
int SceneMotion_StartKind17(SceneMotion *self, u8 *object);

void SceneMotion_Kind16After(SceneMotion *self, u8 *object);
int SceneMotion_StartKind16(SceneMotion *self, u8 *object);

void SceneMotion_Kind15After(SceneMotion *self, u8 *object);
int SceneMotion_StartKind15(SceneMotion *self, u8 *object);

void SceneMotion_Kind14After(void);
void SceneMotion_RunKind14(SceneMotion *self, u8 *object);
void SceneMotion_Kind14Step0(SceneMotion *self, u8 *object);
void SceneMotion_Kind14Step1(SceneMotion *self, u8 *object);
void SceneMotion_Kind14Step2(SceneMotion *self, u8 *object);
void SceneMotion_Kind14Step3(SceneMotion *self, u8 *object);
void SceneMotion_Kind14Step4(SceneMotion *self, u8 *object);
void SceneMotion_Kind14Step5(SceneMotion *self, u8 *object);
void SceneMotion_Kind14Step6(SceneMotion *self, u8 *object);
void SceneMotion_Kind14Step7(SceneMotion *self, u8 *object);
void SceneMotion_Kind14Step8(SceneMotion *self, u8 *object);
void SceneMotion_Kind14Step9(SceneMotion *self, u8 *object);
void SceneMotion_Kind14Step10(SceneMotion *self, u8 *object);
void SceneMotion_Kind14Step11(SceneMotion *self, u8 *object);
void SceneMotion_Kind14Step12(SceneMotion *self, u8 *object);
void SceneMotion_Kind14Step13(SceneMotion *self, u8 *object);
void SceneMotion_Kind14Step14(SceneMotion *self, u8 *object);
void SceneMotion_Kind14Step15(SceneMotion *self, u8 *object);
void SceneMotion_Kind14Step16(SceneMotion *self, u8 *object);
void SceneMotion_Kind14Step17(SceneMotion *self, u8 *object);
void SceneMotion_Kind14Step18(SceneMotion *self, u8 *object);
void SceneMotion_Kind14Step19(SceneMotion *self, u8 *object);

#endif
