/* The special character of the message archive "sp_npc_missing1" (model npc_sp/model/los): a
 * scene object of class 0x020da088 (special_scene_object.h) with vtable 0x020e7c60, 0x72c
 * bytes, made by MissingNpc1_Create (its record at data_020e7b94). While it exists,
 * data_021fbbe0 points at it.
 *
 * It lives in a state machine of nine states (MISSING_NPC1_*), each a pair of C++ pointers to
 * member functions in the table data_021fbbfc (filled at start-up from data_020e7adc to
 * data_020e7b64): an entry, run by MissingNpc1_SetState, whose answer 0 refuses the state,
 * and an update, run each frame by its vtable slot 0x68 (MissingNpc1_Update).
 *
 * Where it starts depends on the scene (MissingNpc1_Start): in the town (scene 0) by the
 * town's gate (building 0x500b) or, when the middle spot of the town (middle_spot.h) is marked,
 * following the player; in scenes 0xb and 0xc following the player; in scene 0x2f it plays the
 * scripted walk of state MISSING_NPC1_SCENE_2F, at whose end the player leaves through a scene
 * exit. Each frame in scene 0 (and in scene 0xb while the player's paired town has flag 5,
 * paired_town.h) its position is kept in the middle spot.
 *
 * It talks through its own scene (MissingNpc1Talk, class vtable 0x020e7bd0, at 0x658): the
 * topic there (MISSING_NPC1_TOPIC_*) picks the lines of "sp_npc_missing1" it says
 * (MissingNpc1Talk_Line), and the player's answer to them (MissingNpc1Talk_OnAnswer) marks the
 * middle spot (answer 0) or notes the answer at 0x711 (answer 1). When the talk ends
 * (MissingNpc1_OnEvent, code 8) it follows the player when the spot is marked, else it takes
 * state MISSING_NPC1_ANIM_AB after answer 1 or state MISSING_NPC1_FACE_PLAYER. */
#ifndef CLEAN_MAIN_MISSING_NPC1_H
#define CLEAN_MAIN_MISSING_NPC1_H

#include "autoload_2/vector.h"
#include "scene_base.h"
#include "types.h"

/* The states. */
#define MISSING_NPC1_FACE_PLAYER 0 /* standing, looking at the player */
#define MISSING_NPC1_ANIM_53 1     /* animation 0x53 with effect 0x54, then the standard 0x54 */
#define MISSING_NPC1_ANIM_AB 2     /* animation 0xab, then the standard 0xac */
#define MISSING_NPC1_TALK 3        /* turns to the player and talks */
#define MISSING_NPC1_PAUSE 4       /* 40 frames, then MISSING_NPC1_FOLLOW */
#define MISSING_NPC1_FOLLOW 5      /* follows the player */
#define MISSING_NPC1_LOST 6        /* the player went too far: animations 0x122 and 0x123 */
#define MISSING_NPC1_TALKED 7      /* nothing: after its talk */
#define MISSING_NPC1_SCENE_2F 8    /* the scripted walk of scene 0x2f */
#define MISSING_NPC1_STATES 9

/* The topics of its talk (MissingNpc1Talk.topic): which lines it says. */
#define MISSING_NPC1_TOPIC_FIRST 0     /* line 0; the player's flag 0x33 set */
#define MISSING_NPC1_TOPIC_AGAIN 1     /* lines 1-3; flag 0x33 set */
#define MISSING_NPC1_TOPIC_TODAY 2     /* lines 4-6; the daily bit 0x29 set */
#define MISSING_NPC1_TOPIC_FOLLOWING 3 /* lines 7-9 */
#define MISSING_NPC1_TOPIC_LOST 4      /* lines 25-27 */
#define MISSING_NPC1_TOPIC_MARKED 5    /* lines 34-36 */
#define MISSING_NPC1_TOPIC_HOME 6      /* line 20 */

struct MissingNpc1;

/* Its talk scene (vtable 0x020e7bd0): a scene of class 0x020d9ff8 (obj_020d9ff8.h). */
typedef struct MissingNpc1Talk {
    SceneBase scene;           /* 0x00 */
    u8 unk_80[0x30];           /* 0x80 */
    struct MissingNpc1 *owner; /* 0xb0 */
    u32 topic;                 /* 0xb4: MISSING_NPC1_TOPIC_* */
} MissingNpc1Talk;

/* What its talk's slot 0x78 gives: the archive's name and the line to say. */
typedef struct MissingNpc1Line {
    u32 name;   /* 0x00: "sp_npc_missing1" */
    u8 message; /* 0x04 */
    u8 unk_05[3];
} MissingNpc1Line;

typedef struct MissingNpc1 {
    u8 unk_000[0x5c];     /* the scene object (special_scene_object.h, scene_object.h) */
    Vec3 position;        /* 0x05c */
    u8 unk_068[0x26];     /* 0x068 */
    s16 angle;            /* 0x08e: where it faces */
    u8 unk_090[4];        /* 0x090 */
    s16 walk_angle;       /* 0x094: where it walks */
    u8 unk_096[0x452];    /* 0x096: the members from 0x2a0 (missing_npc1.c names them) */
    u32 flags;            /* 0x4e8: the scene object's flags (2: held, scene_action.h) */
    u8 unk_4ec[0x24];     /* 0x4ec */
    u8 solid;             /* 0x510: it collides and moves with its carrier */
    u8 unk_511[0x52];     /* 0x511 */
    u8 local;             /* 0x563: not shared with a session */
    u8 unk_564[0xf0];     /* 0x564 */
    s32 state;            /* 0x654: MISSING_NPC1_* */
    MissingNpc1Talk talk; /* 0x658 */
    u8 unk_710;           /* 0x710 */
    u8 declined;          /* 0x711: the player gave answer 1 since the last line */
    u16 stuck_count;      /* 0x712: frames left before a stuck follower gives up */
    u16 pause_count;      /* 0x714: MISSING_NPC1_PAUSE's frames left */
    u8 unk_716[2];        /* 0x716 */
    Vec3 last_position;   /* 0x718: the position a frame before, while following */
    s32 effect;           /* 0x724: effect 0x54's handle, -1 for none */
    u8 step;              /* 0x728: MISSING_NPC1_SCENE_2F's step */
    u8 unk_729[3];        /* 0x729 */
} MissingNpc1;

/* The object's life and vtable slots. */
MissingNpc1 *MissingNpc1_Create(void);
int MissingNpc1_Start(MissingNpc1 *self);
int MissingNpc1_Init(MissingNpc1 *self);
int MissingNpc1_Leave(MissingNpc1 *self);
MissingNpc1 *MissingNpc1_Destruct(MissingNpc1 *self);
MissingNpc1 *MissingNpc1_DestructDelete(MissingNpc1 *self);
int MissingNpc1_MayAct(MissingNpc1 *self);
void MissingNpc1_OnEvent(MissingNpc1 *self, int code);
int MissingNpc1_Update(MissingNpc1 *self);
int MissingNpc1_ModelName(void);
int MissingNpc1_TextureName(void);
void MissingNpc1_SetState(MissingNpc1 *self, int state);

/* What overlay 48 asks of the one that exists. */
void MissingNpc1_StartFollowing(void);
void MissingNpc1_StopToFacePlayer(void);
int MissingNpc1_IsFacingPlayerAtBA(void);

/* The states' entries and updates. */
int MissingNpc1_EnterFacePlayer(MissingNpc1 *self);
int MissingNpc1_UpdateFacePlayer(void);
int MissingNpc1_EnterAnim53(MissingNpc1 *self);
int MissingNpc1_UpdateAnim53(MissingNpc1 *self);
int MissingNpc1_EnterAnimAB(MissingNpc1 *self);
int MissingNpc1_UpdateAnimAB(MissingNpc1 *self);
int MissingNpc1_EnterTalk(MissingNpc1 *self);
int MissingNpc1_UpdateTalk(MissingNpc1 *self);
int MissingNpc1_EnterPause(MissingNpc1 *self);
int MissingNpc1_UpdatePause(MissingNpc1 *self);
int MissingNpc1_EnterFollow(MissingNpc1 *self);
int MissingNpc1_UpdateFollow(MissingNpc1 *self);
int MissingNpc1_EnterLost(MissingNpc1 *self);
int MissingNpc1_UpdateLost(MissingNpc1 *self);
int MissingNpc1_EnterTalked(void);
int MissingNpc1_UpdateTalked(void);
char MissingNpc1_EnterScene2F(MissingNpc1 *self);
int MissingNpc1_UpdateScene2F(MissingNpc1 *self);

/* Its talk scene. */
MissingNpc1Talk *MissingNpc1Talk_Construct(MissingNpc1Talk *talk);
MissingNpc1Talk *MissingNpc1Talk_Destruct(MissingNpc1Talk *talk);
MissingNpc1Talk *MissingNpc1Talk_DestructDelete(MissingNpc1Talk *talk);
void MissingNpc1Talk_SetOwner(MissingNpc1Talk *talk, struct MissingNpc1 *owner);
u32 MissingNpc1Talk_Topic(MissingNpc1Talk *talk);
void MissingNpc1Talk_SetTopic(MissingNpc1Talk *talk, u32 topic);
int MissingNpc1Talk_PutTownNames(MissingNpc1Talk *talk);
void MissingNpc1Talk_OnMessage(MissingNpc1Talk *talk);
void MissingNpc1Talk_OnAnswer(MissingNpc1Talk *talk);
void MissingNpc1Talk_SetTalkStyle(MissingNpc1Talk *talk, int style);
void MissingNpc1Talk_Line(MissingNpc1Talk *talk, MissingNpc1Line *line);

#endif
