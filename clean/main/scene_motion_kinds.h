/* The motions of kinds 0 to 13 of a scene object (class 0x020d8c64, obj_020d8c64.h), and kind
 * 14's start: its member at 0x564, the motion (scene_motion.h, scene_motion_core.h).
 *
 * The motions move the object through its mover (its member at 0x350): a mode set with a rate
 * and a word (func_0201b1a4: 0 stands, 1 walks, 2 walks in the second way, 3 turns in place to
 * the angle set by func_0201aff4), a start point (func_0201b044) and an end point
 * (func_0201afd4). A start that leaves the object where it is sets both points to the origin.
 * Most starts also set the second half-word of the object's member at 0x3aa (func_0201b350: -2,
 * or 1 for a walk) and pass the word on to the item the object holds (its link at 0x628).
 *
 * - 0: stand, facing the object's own angle; done on the first run.
 * - 1 and 2: walk (mode 1 or 2) from the start point to the end point; at the end, when the
 *   mover's two points differ, kind 1 starts again with the start point as both its points,
 *   else the motion is done.
 * - 3: turn in place to the angle; then stand, done.
 * - 4: turn in place to the angle, then kind 1.
 * - 5 and 6: walk (mode 1 or 2) to the end point, turning first when it is more than a quarter
 *   turn away; when the end point falls behind on the way, turn to it again.
 * - 7: turn in place to the angle, then one of five gestures (an animation and a sound).
 * - 8: an act from the table at data_020c8290 (60 records of two parts: an animation and
 *   effects), the record's first part, then its second.
 * - 9: stand and play animation 0xd8.
 * - 10: stand and play animations 0x77 then 0x78, starting a sound.
 * - 11: stand and play the object's two animations of its vtable slots 0x94 and 0x98.
 * - 12: stand and play the animation given.
 * - 13: an exchange with the object at data_021c9350 (func_02057d58).
 * The motion ends (SceneMotion_SetDone with 1) as each kind says. */
#ifndef CLEAN_MAIN_SCENE_MOTION_KINDS_H
#define CLEAN_MAIN_SCENE_MOTION_KINDS_H

#include "scene_motion.h"
#include "types.h"

/* A motion's arguments as kinds 0 to 14 read them (SceneMotionArgs, 0x34 bytes; func_02019d0c
 * fills 0x04 to 0x1e, func_02019c20 kind 12's, func_02019b80 and func_02019bd0 kinds 13 and
 * 14's, func_02019cc8 kind 7's 0x14). */
typedef struct SceneMotionPlan {
    u32 animation; /* 0x00: kind 12's */
    s32 from_x;    /* 0x04: the start point, in the ground plane */
    s32 from_z;    /* 0x08 */
    s32 to_x;      /* 0x0c: the end point */
    s32 to_z;      /* 0x10 */
    s32 gesture;   /* 0x14: kind 7's */
    s16 angle;     /* 0x18 */
    s16 rate;      /* 0x1a: the mover's rate, 0 for its mode's own */
    u16 word;      /* 0x1c: the word the mover's mode is set with */
    u16 frame;     /* 0x1e: kind 12's first frame */
    u8 mode;       /* 0x20: kind 12's play mode */
    u8 act;        /* 0x21: kind 8's record */
    u16 item;      /* 0x22: kinds 13 and 14's */
    u32 unk_24;    /* 0x24 */
    u32 partner;   /* 0x28 */
    u8 unk_2c;     /* 0x2c */
    u8 unk_2d[3];
    s32 variant; /* 0x30: kinds 13 and 14 */
} SceneMotionPlan;

/* A part of an act: the body's animation (0x137 for none) and the effects started with it. */
typedef struct SceneMotionActPart {
    u32 animation;
    u32 effect;
    u8 unk_08;
    u8 restart;
    u8 unk_0a[2];
} SceneMotionActPart;

typedef struct SceneMotionAct {
    SceneMotionActPart part[2];
    u8 mode; /* 0x18: the play mode of the first part */
    u8 unk_19[3];
} SceneMotionAct;

int SceneMotion_StartKind14(SceneMotion *self, u8 *object);

void SceneMotion_Kind13After(void);
void SceneMotion_RunKind13(SceneMotion *self, u8 *object);
void SceneMotion_Kind13Step4(SceneMotion *self, u8 *object);
void SceneMotion_Kind13Step3(SceneMotion *self, u32 *object);
void SceneMotion_Kind13Step2(SceneMotion *self, u8 *object);
void SceneMotion_Kind13Step1(SceneMotion *self, u8 *object);
void SceneMotion_Kind13Step0(SceneMotion *self, u8 *object);
int SceneMotion_StartKind13(SceneMotion *self, u8 *object);

void SceneMotion_Kind12After(SceneMotion *self, u8 *object);
int SceneMotion_StartKind12(SceneMotion *self, u8 *object);

void SceneMotion_Kind11After(SceneMotion *self, u8 *object);
void SceneMotion_RunKind11(SceneMotion *self, u8 *object);
void SceneMotion_Kind11Step0(SceneMotion *self, u8 *object);
int SceneMotion_StartKind11(SceneMotion *self, u8 *object);

void SceneMotion_Kind10After(SceneMotion *self, u8 *object);
void SceneMotion_RunKind10(SceneMotion *self, u8 *object);
void SceneMotion_Kind10Step0(SceneMotion *self, u8 *object);
void SceneMotion_StartKind10(SceneMotion *self, u8 *object);

void SceneMotion_RunKind9(SceneMotion *self, u8 *object);
int SceneMotion_StartKind9(SceneMotion *self, u8 *object);

void SceneMotion_RunKind8(SceneMotion *self, u8 *object);
int SceneMotion_StartKind8(SceneMotion *self, u8 *object);
SceneMotionAct *SceneMotion_Act(u32 number);

void SceneMotion_Kind7After(SceneMotion *self, u8 *object);
void SceneMotion_RunKind7(SceneMotion *self, u8 *object);
void SceneMotion_Kind7Step0(SceneMotion *self, u8 *object);
int SceneMotion_StartKind7(SceneMotion *self, u8 *object);

int SceneMotion_StartKind6(SceneMotion *self, u8 *object);
int SceneMotion_StartKind5(SceneMotion *self, u8 *object);
void SceneMotion_RunKind5(SceneMotion *self, u8 *object);
void SceneMotion_Kind5Step1(SceneMotion *self, u8 *object);
void SceneMotion_Kind5Step0(SceneMotion *self, u8 *object);
int SceneMotion_StartWalkTo(SceneMotion *self, u8 *object, int mode, int half_3ac);

void SceneMotion_RunKind4(SceneMotion *self, u8 *object);
void SceneMotion_Kind4Step1(SceneMotion *self, u8 *object);
void SceneMotion_Kind4Step0(SceneMotion *self, u8 *object);
int SceneMotion_StartKind4(SceneMotion *self, u8 *object);

void SceneMotion_RunKind3(SceneMotion *self, u8 *object);
int SceneMotion_StartKind3(SceneMotion *self, u8 *object);

void SceneMotion_RunKind2(SceneMotion *self, u8 *object);
int SceneMotion_StartKind2(SceneMotion *self, u8 *object);
void SceneMotion_RunKind1(SceneMotion *self, u8 *object);
int SceneMotion_StartKind1(SceneMotion *self, u8 *object);

void SceneMotion_RunKind0(SceneMotion *self, u8 *object);
int SceneMotion_StartKind0(SceneMotion *self, u8 *object);

#endif
