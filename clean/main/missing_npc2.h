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

/* Its other states (the entry and update of each in the table data_021fbcd8). */
#define MISSING_NPC2_IDLE 0          /* standing; in the town it starts wandering */
#define MISSING_NPC2_TALK 1          /* its action runs; when it ends, MISSING_NPC2_TALKED */
#define MISSING_NPC2_TALKED 2        /* nothing: after its talk */
#define MISSING_NPC2_SPEAKER 3       /* standing: it joined a talk as a speaker */
#define MISSING_NPC2_SCENE_2F_WALK 4 /* the walk of scene 0x2f to (0xf400, 0x14600) */
#define MISSING_NPC2_TURN 5          /* a turn, then standing */
#define MISSING_NPC2_SCENE_2F_EXIT 6 /* a turn and a walk to (0x10000, 0x1d000), then standing */
#define MISSING_NPC2_TURN_AND_TALK 9 /* turns to the object its talk names and talks */
#define MISSING_NPC2_STATES 10

/* The topics of its talk (MissingNpc2Talk.topic): which lines it says. */
#define MISSING_NPC2_TOPIC_FIRST 0 /* line 0; the player's flag 0x33 set */
#define MISSING_NPC2_TOPIC_AGAIN 1 /* lines 1-3 (after the walk of scene 0x2f); flag 0x33 set */
#define MISSING_NPC2_TOPIC_TODAY 2 /* lines 4-6; the daily bit 0x2a set */
#define MISSING_NPC2_TOPIC_LATER 3 /* lines 7-9 */

/* Its talk scene (vtable 0x020e7e14): a scene of class 0x020d9ff8 (obj_020d9ff8.h), at 0x658. */
#include "scene_base.h"

typedef struct MissingNpc2Talk {
    SceneBase scene;           /* 0x00 */
    u8 unk_80[0x30];           /* 0x80 */
    struct MissingNpc2 *owner; /* 0xb0 */
    u32 topic;                 /* 0xb4: MISSING_NPC2_TOPIC_* */
} MissingNpc2Talk;

/* What its talk's slot 0x78 gives: the archive's name and the line to say. */
typedef struct MissingNpc2Line {
    u32 name;   /* 0x00: "sp_npc_missing2" */
    u8 message; /* 0x04 */
    u8 unk_05[3];
} MissingNpc2Line;

/* The object's life and vtable slots. */
MissingNpc2 *MissingNpc2_Create(void);
int MissingNpc2_Start(MissingNpc2 *self);
int MissingNpc2_Init(MissingNpc2 *self);
int MissingNpc2_Leave(MissingNpc2 *self);
int MissingNpc2_MayAct(MissingNpc2 *self);
void MissingNpc2_OnEvent(MissingNpc2 *self, int code);
int MissingNpc2_Update(MissingNpc2 *self);
int MissingNpc2_ModelName(void);
int MissingNpc2_TextureName(void);
int MissingNpc2_AnimSpeed(MissingNpc2 *self);
void MissingNpc2_OnSpeakerJoined(MissingNpc2 *self);
void MissingNpc2_OnTalkEnd(MissingNpc2 *self);
void MissingNpc2_SetState(MissingNpc2 *self, int state);

/* What "sp_npc_missing1" asks of the one that exists. */
void MissingNpc2_StartScene2FWalk(void);
void MissingNpc2_StartScene2FExit(void);

/* The states' entries and updates. */
int MissingNpc2_EnterIdle(MissingNpc2 *self);
int MissingNpc2_UpdateIdle(MissingNpc2 *self);
int MissingNpc2_EnterTalk(void);
int MissingNpc2_UpdateTalk(MissingNpc2 *self);
int MissingNpc2_EnterTalked(void);
int MissingNpc2_UpdateTalked(void);
void MissingNpc2_EnterSpeaker(MissingNpc2 *self);
int MissingNpc2_UpdateSpeaker(void);
int MissingNpc2_EnterScene2FWalk(MissingNpc2 *self);
int MissingNpc2_UpdateScene2FWalk(MissingNpc2 *self);
int MissingNpc2_EnterTurn(MissingNpc2 *self);
int MissingNpc2_UpdateTurn(MissingNpc2 *self);
int MissingNpc2_EnterScene2FExit(MissingNpc2 *self);
int MissingNpc2_UpdateScene2FExit(MissingNpc2 *self);
int MissingNpc2_EnterTurnAndTalk(MissingNpc2 *self);
int MissingNpc2_UpdateTurnAndTalk(void);

/* Its talk scene. */
MissingNpc2Talk *MissingNpc2Talk_Construct(MissingNpc2Talk *talk);
MissingNpc2Talk *MissingNpc2Talk_Destruct(MissingNpc2Talk *talk);
MissingNpc2Talk *MissingNpc2Talk_DestructDelete(MissingNpc2Talk *talk);
void MissingNpc2Talk_SetOwner(MissingNpc2Talk *talk, struct MissingNpc2 *owner);
u32 MissingNpc2Talk_Topic(MissingNpc2Talk *talk);
void MissingNpc2Talk_SetTopic(MissingNpc2Talk *talk, u32 topic);
void MissingNpc2Talk_PutTownNames(MissingNpc2Talk *talk);
void MissingNpc2Talk_OnMessage(void);
void MissingNpc2Talk_Line(MissingNpc2Talk *talk, MissingNpc2Line *line);

#endif
