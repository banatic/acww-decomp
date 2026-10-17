/* Overlay 88: the special character of the message file "sp_npc_reaction" with the model
 * npc_sp/model/upa (person code 0xd021), who teaches the player reactions: the numbers of the
 * motions a player's record keeps in its four motion slots (main's motion_slots.h), named by
 * the messages of "st_learn". Main's spawner (spawner.h) asks for it while event 0x43 is on
 * (Spawner_CheckEvents3e); its spawn table (data_020e1d8c) gives its object profile 0x62 the
 * code 0xd021 and overlay 88, loaded with it; the profile's record is at 0x02279be0, which
 * main's profile table data_020e3134 points to. Teaching a reaction marks event 0x43 taken part
 * in.
 *
 * It is a scene object of class 0x020da088 (main's special_scene_object.h) with vtable
 * 0x02279cec, 0x73c bytes, made by ReactionNpc_Create, with its talk scene (ReactionNpcTalk,
 * reaction_npc_talk.h) at 0x658.
 *
 * Its states (ReactionNpc.state), each an entry and an update function (C++ members taking it)
 * from the table data_ov088_02279e28 (filled at start-up by __sinit_ov088_022799c4), set by
 * ReactionNpc_SetState and run each frame by ReactionNpc_Update:
 *   0  talk end: once its action is idle the event ends: state 1;
 *   1  talked:   nothing;
 *   2  wander:   while it is in the camera's view it stands or, one frame in eight, walks or
 *                turns toward a free tile 12.0 away; out of view while moving, state 3;
 *   3  wait:     it stands without footsteps until it is in the camera's view: state 2;
 *   4  talk:     it turns to the talk's partner and talks.
 * The events it is told of (ReactionNpc_OnEvent): code 0, state 0; code 3, the talk begins
 * (state 4); code 8, the event ended (state 2). */
#ifndef CLEAN_OV088_REACTION_NPC_H
#define CLEAN_OV088_REACTION_NPC_H

#include "autoload_2/vector.h"
#include "main/scene_base.h"
#include "ov004/member_pointer.h"
#include "types.h"

struct ReactionNpc;

/* The reactions there are: the messages 1 to 29 of "st_learn" (the motion numbers), with the
 * marks of ReactionNpcTalk.known indexed by number (mark 0 always set). */
#define REACTION_NPC_MARKS 0x1e
/* The reactions it offers at a time, and the room for a fifth answer. */
#define REACTION_NPC_OFFERED 4
#define REACTION_NPC_OFFERED_ROOM 5

/* Its talk scene (0xe0 bytes, a scene of main's class 0x020d9ff8, vtable 0x02279c58). Its
 * receiver's message (byte 0x1e of the scene) is the line shown. */
typedef struct ReactionNpcTalk {
    SceneBase base;                        /* 0x00 */
    u8 unk_80[0x30];                       /* 0x80: the scene's commands (scene_command.h) */
    s32 step;                              /* 0xb0: REACTION_NPC_STEP_* */
    u8 step_state;                         /* 0xb4: cleared with each step set */
    u8 unk_b5[3];                          /* 0xb5 */
    struct ReactionNpc *owner;             /* 0xb8 */
    u8 chosen;                             /* 0xbc: the reaction chosen, or the line offering */
    u8 known[REACTION_NPC_MARKS];          /* 0xbd: 1 for each reaction not to offer */
    u8 offered[REACTION_NPC_OFFERED_ROOM]; /* 0xdb: the reactions offered as answers */
} ReactionNpcTalk;

/* The size of the special character's scene object it derives from, as far as it is used. */
#define REACTION_NPC_BASE_SIZE 0x654

typedef struct ReactionNpc {
    u8 base[REACTION_NPC_BASE_SIZE]; /* 0x000: the special character's scene object */
    s32 state;                       /* 0x654: enum ReactionNpcState */
    ReactionNpcTalk talk;            /* 0x658 */
    u8 countdown;                    /* 0x738: the frames a walk or turn may go on; in a talk,
                                        the frames before the next line */
    u8 watch;                        /* 0x739: while not 0, its motion's number may be taken
                                        (ReactionNpc_MotionNumber); counts down while watched */
    u8 unk_73a[2];                   /* 0x73a */
} ReactionNpc;

enum ReactionNpcState {
    REACTION_NPC_TALK_END = 0,
    REACTION_NPC_TALKED = 1,
    REACTION_NPC_WANDER = 2,
    REACTION_NPC_WAIT = 3,
    REACTION_NPC_TALK = 4,
    REACTION_NPC_STATES = 5
};

/* A state's functions in data_ov088_02279e28. */
typedef struct ReactionNpcStep {
    MemberPointer enter;  /* 0x00: int (character); the state is taken unless it answers 0 */
    MemberPointer update; /* 0x08: int (character) */
} ReactionNpcStep;

void *ReactionNpc_Destroy(void *npc);
ReactionNpc *ReactionNpc_Delete(ReactionNpc *npc);
void ReactionNpc_PutReaction(ReactionNpc *npc, int slot, int reaction);
int ReactionNpc_MotionNumber(ReactionNpc *npc);
void ReactionNpc_OnEvent(ReactionNpc *npc, int code);
int ReactionNpc_MayAct(ReactionNpc *npc);
int ReactionNpc_UpdateTalk(void);
int ReactionNpc_EnterTalk(ReactionNpc *npc);
int ReactionNpc_UpdateWait(ReactionNpc *npc);
int ReactionNpc_EnterWait(ReactionNpc *npc);
int ReactionNpc_UpdateWander(ReactionNpc *npc);
int ReactionNpc_IsSteeringAside(ReactionNpc *npc);
int ReactionNpc_SteerAside(ReactionNpc *npc);
int ReactionNpc_SidePoint(ReactionNpc *npc, Vec3 *out, const Vec3 *offset);
int ReactionNpc_PickWalkPoint(ReactionNpc *npc, fx32 *x, fx32 *z);
int ReactionNpc_InView(ReactionNpc *npc);
int ReactionNpc_IsInViewOf(int unused, const Vec3 *focus, const Vec3 *at);
int ReactionNpc_EnterWander(ReactionNpc *npc);
int ReactionNpc_UpdateTalked(void);
int ReactionNpc_UpdateTalkEnd(ReactionNpc *npc);
int ReactionNpc_EnterTalkEnd(void);
void ReactionNpc_SetState(ReactionNpc *npc, int state);
int ReactionNpc_Update(ReactionNpc *npc);
int ReactionNpc_ModelName(void);
int ReactionNpc_TextureName(void);
int ReactionNpc_Leave(ReactionNpc *npc);
int ReactionNpc_Start(ReactionNpc *npc);
int ReactionNpc_Init(ReactionNpc *npc);
int ReactionNpc_AnimSpeed(void);
void *ReactionNpc_Create(void);

#endif
