/* The special character of the message archive "sp_npc_missing2" (model npc_sp/model/mum): a
 * scene object of class 0x020da088 (special_scene_object.h) with vtable 0x020e7ea4, 0x714
 * bytes, whose talk scene (vtable 0x020e7e14) is at 0x658. While it exists, data_021fbca0
 * points at it; "sp_npc_missing1" (missing_npc1.h) sets it to its states 4 and 6 during the
 * walk of scene 0x2f.
 *
 * Like that character it lives in a state machine of C++ pointers to member functions (an
 * entry and an update per state; the table data_021fbcd8, func_020c3690 sets a state). Two of
 * its states keep it wandering while the camera sees it:
 * - MISSING_NPC2_WANDER: now and then it walks (or turns, then walks) to a clear tile drawn at
 *   random 0xc000 away, stepping around what blocks the way ahead, and stands when the end
 *   point falls more than a quarter turn behind or its time runs out; out of the camera's box
 *   while moving, it takes MISSING_NPC2_OUT_OF_VIEW;
 * - MISSING_NPC2_OUT_OF_VIEW: standing, without footsteps, until the camera's box holds it. */
#ifndef CLEAN_MAIN_MISSING_NPC2_H
#define CLEAN_MAIN_MISSING_NPC2_H

#include "autoload_2/vector.h"
#include "types.h"

/* Its states handled here. */
#define MISSING_NPC2_WANDER 7
#define MISSING_NPC2_OUT_OF_VIEW 8

typedef struct MissingNpc2 {
    u8 unk_000[0x5c];  /* the scene object (special_scene_object.h, scene_object.h) */
    Vec3 position;     /* 0x05c */
    u8 unk_068[0x26];  /* 0x068 */
    s16 angle;         /* 0x08e: where it faces */
    u8 unk_090[4];     /* 0x090 */
    s16 walk_angle;    /* 0x094: where it walks */
    u8 unk_096[2];     /* 0x096 */
    fx32 speed;        /* 0x098: along its heading */
    u8 unk_09c[0x5b5]; /* 0x09c: the members from 0x2a0 (missing_npc2.c names them) */
    u8 wander_count;   /* 0x651: frames left of the current wander */
    u8 unk_652[2];     /* 0x652 */
    s32 state;         /* 0x654 */
    u8 talk[0xbc];     /* 0x658: its talk scene */
} MissingNpc2;

MissingNpc2 *MissingNpc2_Destruct(MissingNpc2 *self);
MissingNpc2 *MissingNpc2_DestructDelete(MissingNpc2 *self);
int MissingNpc2_UpdateOutOfView(MissingNpc2 *self);
int MissingNpc2_EnterOutOfView(MissingNpc2 *self);
int MissingNpc2_UpdateWander(MissingNpc2 *self);
int MissingNpc2_EnterWander(MissingNpc2 *self);
int MissingNpc2_AvoidAhead(MissingNpc2 *self);
int MissingNpc2_StepAside(MissingNpc2 *self);
int MissingNpc2_SidePoint(MissingNpc2 *self, Vec3 *out, const Vec3 *offset);
int MissingNpc2_PickWanderPoint(MissingNpc2 *self, fx32 *x, fx32 *z);
int MissingNpc2_InView(MissingNpc2 *self);
int MissingNpc2_InCameraBox(int unused, const Vec3 *camera, const Vec3 *point);
void MissingNpc2Talk_OnAnswer(void);

#endif
