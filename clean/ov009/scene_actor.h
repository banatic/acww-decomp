/* Overlay 9's scene actor (class Obj_ov009_022658dc, vtable 0x022658dc, receiver part at 0xec
 * with vtable 0x022659a0, 0x2b4 bytes): the base class of the special characters and of many
 * scene objects of overlays 3 and 68 (the fox, the snowmen, the countdown board, ...). Each
 * stands for one special character, whose code (0x5000 to 0x5021) it keeps at 0x136; main's
 * table of their records (data_020d1f24, ten bytes each) gives its kind, its size and an id.
 *
 * It keeps a sound emitter of its own (SceneActorSound, at 0x238), a model, the tile it
 * stands on, and a list of areas (0x28c) built from the character's data in front of which
 * a player stands to talk to it (SceneActor_GetStandPoint).
 *
 * Two state machines run through tables of member pointers (ov004/member_pointer.h). The mode
 * (the byte at 0x134, set through vtable slot 0x6c, seven modes) is mostly the derived
 * classes'; modes 5 and 6 last one frame and go back to mode 0. The talk machine (the word
 * at 0x27c, enum SceneActorState) is run by SceneActor_UpdateState each frame:
 *
 *   0 idle:        nothing happens; scene event 0 or 1 starts a visit, event 8 ends here.
 *   1 visit:       entering it asks main for the character's visit record (func_020b248c)
 *                  unless the talk skips it (the byte at 0x280); once main answers
 *                  (func_020b2470, nonzero), 2 or 3 start the talk, else it leaves (state 7
 *                  for kind 1, else state 4).
 *   2 talk:        entering it takes the receiver, raises the link's request and prepares the
 *                  talk (vtable slot 0x78); once the link is open (slot 0x7c) it is state 3.
 *   3 talk end:    once the link closes (slot 0x84) it hands the receiver back and lets the
 *                  scene go on; until then slot 0x80 runs each frame.
 *   4 leave:       entering it calls func_02095944(0); once func_02096174 agrees, state 5.
 *   5 walk:        entering it asks the player to stand at the stand point (player state 0x38
 *                  or 0x39) and fails when the player refuses; once func_02096168 agrees,
 *                  kinds 2 and 3 move to state 6.
 *   6 gone:        counts frames; after 20 (32 for kind 1) it registers the character's id
 *                  in main's table at data_021f69d0 where it stood, turned half round, and
 *                  sets SCENE_ACTOR_FLAG_GONE.
 *   7 leave again: as state 4, but moves to state 8.
 *   8 walk again:  asks the player to stand at the stand point (player state 0x39, kind 2)
 *                  and moves to state 6 when the player agrees. */
#ifndef CLEAN_OV009_SCENE_ACTOR_H
#define CLEAN_OV009_SCENE_ACTOR_H

#include "autoload_2/matrix.h"              /* Mtx43 */
#include "autoload_2/sound_emitter_class.h" /* SoundEmitterObject */
#include "autoload_2/vector.h"              /* Vec3 */
#include "main/sound_emitter.h"             /* SoundEmitter */
#include "types.h"

enum SceneActorState {
    SCENE_ACTOR_IDLE,
    SCENE_ACTOR_VISIT,
    SCENE_ACTOR_TALK,
    SCENE_ACTOR_TALK_END,
    SCENE_ACTOR_LEAVE,
    SCENE_ACTOR_WALK,
    SCENE_ACTOR_GONE,
    SCENE_ACTOR_LEAVE_AGAIN,
    SCENE_ACTOR_WALK_AGAIN,
    SCENE_ACTOR_STATES
};

/* Bits of SceneActor.flags_235. */
#define SCENE_ACTOR_FLAG_OUT_OF_VIEW 0x01 /* outside the camera's box (SceneActor_UpdateOutOfView) */
#define SCENE_ACTOR_FLAG_TALKABLE 0x08    /* actors of a nonzero kind can be talked to */

/* Bits of SceneActor.flags. */
#define SCENE_ACTOR_FLAG_GONE 0x01    /* set at the end of SCENE_ACTOR_GONE */
#define SCENE_ACTOR_FLAG_VISIT_2 0x02 /* the visit record said 2 */

/* The sound emitter it keeps (kind 2 of autoload_2/sound_emitter_class.h, vtable 0x0213f090).
 * That class leaves the byte at 0x40 (the base class's volume) alone, and overlay 9 uses it as
 * an on flag: sounds play only while it is set. */
typedef union SceneActorSound {
    SoundEmitterObject object;
    SoundEmitter emitter;
    struct {
        u8 unk_00[0x40];
        u8 on;
        u8 unk_41[3];
    } state;
} SceneActorSound;

/* What the receiver's link (Base_02066994's word at 0x40) points at. */
typedef struct SceneActorLink {
    int unk_00;
    int status;    /* nonzero while what the request opened is up, 0 once it closed */
    int requested; /* set to 1 when a talk starts */
    int unk_0C;
    int unk_10; /* set to 100 when a message ends (SceneActor_OnMessageEnd) */
} SceneActorLink;

/* One of its areas (0x54 bytes), built from three points of the character's data. */
typedef struct SceneActorArea {
    u8 unk_00[0x28];
    fx32 facing_x; /* the direction the area faces, in the ground plane */
    fx32 unk_2C;
    fx32 facing_z;
    u8 unk_34[0x3c - 0x34];
    Vec3 origin; /* what func_02032754 gives */
    u8 unk_48[0x54 - 0x48];
} SceneActorArea;

/* A record of main's table data_020d1f24 (ten bytes), copied by func_020b2a68. */
typedef struct SceneActorRecord {
    u16 code;
    u8 bytes[8];
} SceneActorRecord;

typedef struct SceneActor {
    const void *vtable; /* data_ov009_022658dc */
    u8 unk_04[0x5c - 0x04];
    Vec3 position;
    u8 unk_68[0x8e - 0x68];
    s16 yaw; /* the direction it faces */
    u8 unk_90[0xec - 0x90];
    /* The message receiver (Base_02066994) */
    const void *receiver_vtable; /* data_ov009_022659a0 */
    char receiver_name[25];      /* written by func_020a8164 */
    u8 unk_109;
    u8 message; /* Base_02066994's byte at 0x1e: the message to show */
    u8 unk_10B[0x12c - 0x10b];
    SceneActorLink *link; /* Base_02066994's word at 0x40 */
    u8 unk_130[0x132 - 0x130];
    u16 unk_132;
    u8 mode; /* the mode machine's state */
    u8 unk_135;
    u16 code; /* the special character's code (0x5000 to 0x5021) */
    u8 unk_138[0x13c - 0x138];
    u8 model_object[0x198 - 0x13c]; /* main's model object (Obj_020dd05c) ... */
    void *model;                    /* ... its model, */
    u8 unk_19C[0x1a0 - 0x19c];
    Mtx43 model_matrix;           /* ... and the matrix it is drawn with */
    u8 unk_1D0[0x1f4 - 0x1d0];    /* ... up to its end */
    u8 member_1f4[0x22c - 0x1f4]; /* a member object of main's (Member_020b33b8, parts up to 0x34) */
    int tile_x;                   /* the position's x and z over 0x2000 */
    int tile_z;
    u8 unk_234; /* set to 1 by scene event 6 */
    u8 flags_235;
    u8 flags;
    u8 visit_3; /* the visit record said 3 */
    SceneActorSound sound;
    int state;     /* enum SceneActorState */
    u8 skip_visit; /* the talk starts without asking for the visit record */
    u8 unk_281;
    u16 frames; /* counted in SCENE_ACTOR_GONE */
    u8 unk_284[0x28c - 0x284];
    SceneActorArea *areas;
    u8 area_count;
    u8 unk_291[0x2a8 - 0x291];
    Vec3 talk_point; /* the stand point moved back by 4.0 along z (vtable slot 0x50) */
} SceneActor;

int SceneActor_SlotB8(SceneActor *actor);
void SceneActor_Position(Vec3 *out, SceneActor *actor);
void SceneActorSound_PlayEx(SceneActorSound *sound, int number);
void SceneActorSound_Play(SceneActorSound *sound, int number);
void SceneActorSound_TurnOff(SceneActorSound *sound);
void SceneActorSound_UpdateAt(SceneActorSound *sound, const Vec3 *pos);
void SceneActorSound_TurnOn(SceneActorSound *sound);
void *SceneActorSound_Destroy(SceneActorSound *sound);
void *SceneActorSound_Construct(SceneActorSound *sound);
int SceneActor_Member1F4IsSet(SceneActor *actor);
u32 SceneActor_TileZ(SceneActor *actor);
int SceneActor_TileX(SceneActor *actor);
int SceneActor_CodeAddress(SceneActor *actor);
int SceneActor_IdleSetModeByKindA(SceneActor *actor);
int SceneActor_SetModeByKindA(SceneActor *actor);
int SceneActor_IdleSetModeByKindB(SceneActor *actor);
int SceneActor_SetModeByKindB(SceneActor *actor);
int SceneActor_IsInMode0(SceneActor *actor);
void SceneActor_UpdateOutOfView(SceneActor *actor);
int SceneActor_IsOutOfView(SceneActor *actor);
int SceneActor_Slot98(SceneActor *actor);
int SceneActor_KeepsPointX(SceneActor *actor);
int SceneActor_DrawsModel(SceneActor *actor);
int SceneActor_WalksWithState38(SceneActor *actor);
int SceneActor_RecordByte5(SceneActor *actor);
int SceneActor_RecordId(SceneActor *actor);
int SceneActor_GetStandPoint(SceneActor *actor, Vec3 *point, s16 *angle);
void SceneActor_DrawModel(SceneActor *actor);
void SceneActor_OnTalkClosed(SceneActor *actor);
void SceneActor_OnTalkWait(SceneActor *actor);
void SceneActor_OnTalkOpen(SceneActor *actor);
void SceneActor_PrepareTalk(SceneActor *actor);
void SceneActor_OnMessageEnd(SceneActor *actor);
void SceneActor_OnSceneEvent(SceneActor *actor, unsigned int event, int arg);
int SceneActor_CanTalkTo(SceneActor *actor, SceneActor *other);
int SceneActor_TalkPointAddress(SceneActor *actor);
void SceneActor_UpdateWalkAgain(SceneActor *actor);
int SceneActor_EnterWalkAgain(SceneActor *actor);
void SceneActor_UpdateLeaveAgain(SceneActor *actor);
int SceneActor_EnterLeaveAgain(SceneActor *actor);
void SceneActor_UpdateGone(SceneActor *actor);
int SceneActor_EnterGone(SceneActor *actor);
void SceneActor_UpdateWalk(SceneActor *actor);
int SceneActor_EnterWalk(SceneActor *actor);
void SceneActor_UpdateLeave(SceneActor *actor);
int SceneActor_EnterLeave(SceneActor *actor);
void SceneActor_UpdateTalkEnd(SceneActor *actor);
int SceneActor_EnterTalkEnd(SceneActor *actor);
void SceneActor_UpdateTalk(SceneActor *actor);
int SceneActor_EnterTalk(SceneActor *actor);
void SceneActor_UpdateVisit(SceneActor *actor);
int SceneActor_EnterVisit(SceneActor *actor);
void SceneActor_UpdateIdle(SceneActor *actor);
int SceneActor_EnterIdle(SceneActor *actor);
void SceneActor_UpdateState(SceneActor *actor);
int SceneActor_SetState(SceneActor *actor, int state);
void SceneActor_RunMode6(SceneActor *actor);
int SceneActor_EnterMode6(void);
void SceneActor_RunMode5(SceneActor *actor);
int SceneActor_EnterMode5(void);

#endif
