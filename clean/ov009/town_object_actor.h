/* Overlay 9's town object actor (class Obj_ov009_022658dc, vtable 0x022658dc, receiver part at
 * 0xec with vtable 0x022659a0, 0x2b4 bytes): the base class of the actors of the town's objects
 * (codes 0x5000 to 0x5021, main/town_objects.h): the buildings, the villagers' and the player's
 * houses, the shops, the gate's checkpoint, the bulletin board, the signs, the clock, the
 * mailbox, the visitors' tents and spots, which overlays 3 and 68 derive from it (the fox, the
 * panther, the countdown board, ...). The game keeps their files under "/str/" (structures,
 * town_object_actor_files.h). Each keeps its object's code at 0x136; main's table of the
 * objects' records (data_020d1f24, ten bytes each) gives its kind, its size and an id.
 *
 * It keeps a sound emitter of its own (TownObjectActorSound, at 0x238), a model, the tile it
 * stands on, and a list of areas (0x28c) built from the object's data: its doors and the faces
 * in front of which a player stands to check or enter it (TownObjectActor_GetStandPoint).
 *
 * Two state machines run through tables of member pointers (ov004/member_pointer.h). The mode
 * (the byte at 0x134, set through vtable slot 0x6c, seven modes) is mostly the derived
 * classes'; modes 5 and 6 last one frame and go back to mode 0. The entry machine (the word
 * at 0x27c, enum TownObjectActorState) takes a player in through the object's door, or shows
 * the object's message when it cannot be entered (or is only checked); it is run by
 * TownObjectActor_UpdateState each frame:
 *
 *   0 idle:        nothing happens; scene event 0 or 1 starts a visit, event 8 ends here.
 *   1 visit:       entering it asks main to let the player in (the object's visit record,
 *                  func_020b248c: the players inside each object) unless the talk skips it
 *                  (the byte at 0x280); once main answers (func_020b2470, nonzero), "full"
 *                  (2) or "asleep" (3) start the talk, else the player goes in (state 7 for
 *                  kind 1, else state 4).
 *   2 talk:        entering it takes the receiver, raises the link's request and prepares the
 *                  object's message (vtable slot 0x78); once the link is open (slot 0x7c) it is
 *                  state 3.
 *   3 talk end:    once the link closes (slot 0x84) it hands the receiver back and lets the
 *                  scene go on; until then slot 0x80 runs each frame.
 *   4 leave:       the player leaves the town scene for the object's: entering it calls
 *                  func_02095944(0); once func_02096174 agrees, state 5.
 *   5 walk:        entering it asks the player to walk to the stand point at the door (player
 *                  state 0x38 or 0x39) and fails when the player refuses; once func_02096168
 *                  agrees, kinds 2 and 3 move to state 6.
 *   6 gone:        counts frames; after 20 (32 for kind 1) it takes the scene exit of the
 *                  object's id (main's table at data_021f69d0) and marks where the player stood,
 *                  turned half round, to come back out there; then sets
 *                  TOWN_OBJECT_ACTOR_FLAG_GONE.
 *   7 leave again: as state 4, but moves to state 8.
 *   8 walk again:  asks the player to stand at the stand point (player state 0x39, kind 2)
 *                  and moves to state 6 when the player agrees.
 *
 * The objects' shapes are main/building_shapes.h. Overlay 9 is loaded with the town's scenes
 * (scenes 0 and 49, through the SceneInfo of overlay 5). Its files
 * (town_object_actor_files.h), its doors and the pen's faces (town_object_actor_area.h), its
 * modes (town_object_actor_mode.h) and its life as a process (town_object_actor_life.h) are in
 * the files next to this one. */
#ifndef CLEAN_OV009_TOWN_OBJECT_ACTOR_H
#define CLEAN_OV009_TOWN_OBJECT_ACTOR_H

#include "autoload_2/matrix.h"              /* Mtx43 */
#include "autoload_2/sound_emitter_class.h" /* SoundEmitterObject */
#include "autoload_2/vector.h"              /* Vec3 */
#include "main/sound_emitter.h"             /* SoundEmitter */
#include "types.h"

enum TownObjectActorState {
    TOWN_OBJECT_ACTOR_IDLE,
    TOWN_OBJECT_ACTOR_VISIT,
    TOWN_OBJECT_ACTOR_TALK,
    TOWN_OBJECT_ACTOR_TALK_END,
    TOWN_OBJECT_ACTOR_LEAVE,
    TOWN_OBJECT_ACTOR_WALK,
    TOWN_OBJECT_ACTOR_GONE,
    TOWN_OBJECT_ACTOR_LEAVE_AGAIN,
    TOWN_OBJECT_ACTOR_WALK_AGAIN,
    TOWN_OBJECT_ACTOR_STATES
};

/* Bits of TownObjectActor.flags_235. */
#define TOWN_OBJECT_ACTOR_FLAG_OUT_OF_VIEW 0x01 /* outside the camera's box (TownObjectActor_UpdateOutOfView) */
#define TOWN_OBJECT_ACTOR_FLAG_AT_DOOR 0x02     /* this console's player touched an area facing it this frame */
#define TOWN_OBJECT_ACTOR_FLAG_RUN_IN 0x04      /* ... moving at a speed of 0x200 or more */
#define TOWN_OBJECT_ACTOR_FLAG_TALKABLE 0x08    /* actors of a nonzero kind can be talked to (AT_DOOR last frame) */

/* Bits of TownObjectActor.flags. */
#define TOWN_OBJECT_ACTOR_FLAG_GONE 0x01 /* set at the end of TOWN_OBJECT_ACTOR_GONE */
#define TOWN_OBJECT_ACTOR_FLAG_FULL 0x02 /* the visit record said 2: too many visitors inside */

/* The sound emitter it keeps (kind 2 of autoload_2/sound_emitter_class.h, vtable 0x0213f090).
 * That class leaves the byte at 0x40 (the base class's volume) alone, and overlay 9 uses it as
 * an on flag: sounds play only while it is set. */
typedef union TownObjectActorSound {
    SoundEmitterObject object;
    SoundEmitter emitter;
    struct {
        u8 unk_00[0x40];
        u8 on;
        u8 unk_41[3];
    } state;
} TownObjectActorSound;

/* What the receiver's link (Base_02066994's word at 0x40) points at. */
typedef struct TownObjectActorLink {
    int unk_00;
    int status;    /* nonzero while what the request opened is up, 0 once it closed */
    int requested; /* set to 1 when a talk starts */
    int unk_0c;
    int unk_10; /* set to 100 when a message ends (TownObjectActor_OnMessageEnd) */
} TownObjectActorLink;

/* One of its areas (0x54 bytes), built from three points of the object's data. */
typedef struct TownObjectActorArea {
    u8 unk_00[0x28];
    fx32 facing_x; /* the direction the area faces, in the ground plane */
    fx32 unk_2c;
    fx32 facing_z;
    u8 unk_34[0x3c - 0x34];
    Vec3 origin; /* what func_02032754 gives */
    u8 unk_48[0x4c - 0x48];
    struct TownObjectActor *owner; /* the actor whose door it is (TownObjectActorDoor_Construct's caller) */
    int kind;                      /* the owner's kind (TownObjectActor_Kind) */
} TownObjectActorArea;

/* A record of main's table data_020d1f24 (ten bytes), copied by func_020b2a68. */
typedef struct TownObjectActorRecord {
    u16 code;
    u8 bytes[8];
} TownObjectActorRecord;

typedef struct TownObjectActor {
    const void *vtable; /* data_ov009_022658dc */
    u8 unk_04[0x5c - 0x04];
    Vec3 position;
    u8 unk_68[0x8e - 0x68];
    s16 yaw; /* the direction it faces */
    u8 unk_90[0xc4 - 0x90];
    Vec3 pivot; /* the position bent onto the drawn world (TownObjectActor_UpdateModelMatrix) */
    s16 pitch;  /* the angle about x it is drawn at there */
    u8 unk_D2[0xec - 0xd2];
    /* The message receiver (Base_02066994) */
    const void *receiver_vtable; /* data_ov009_022659a0 */
    char receiver_name[25];      /* written by func_020a8164 */
    u8 unk_109;
    u8 message; /* Base_02066994's byte at 0x1e: the message to show */
    u8 unk_10b[0x12c - 0x10b];
    TownObjectActorLink *link; /* Base_02066994's word at 0x40 */
    u8 unk_130[0x132 - 0x130];
    u16 close_wait; /* mode 4: the frames before the door closes */
    u8 mode;        /* the mode machine's state */
    u8 unk_135;
    u16 code;                       /* the town object's code (0x5000 to 0x5021) */
    u32 index;                      /* the code's low 12 bits: the building's number in its files' names */
    u8 model_object[0x198 - 0x13c]; /* main's model object (Obj_020dd05c) ... */
    void *model;                    /* ... its model, */
    u8 unk_19c[0x1a0 - 0x19c];
    Mtx43 model_matrix;        /* ... and the matrix it is drawn with */
    u8 unk_1d0[0x1f4 - 0x1d0]; /* ... up to its end */
    u8 lights[0x22c - 0x1f4];  /* a member object of main's (Member_020b33b8, parts up to 0x34) */
    int tile_x;                /* the position's x and z over 0x2000 */
    int tile_z;
    u8 exit_step; /* set to 1 by scene event 6, counts to 3 (TownObjectActor_UpdateExit) */
    u8 flags_235;
    u8 flags;
    u8 villager_asleep; /* the visit record said 3 (TOWN_OBJECTS_ANSWER_ASLEEP): the villager is asleep */
    TownObjectActorSound sound;
    int state;     /* enum TownObjectActorState */
    u8 skip_visit; /* the talk starts without asking for the visit record */
    u8 unk_281;
    u16 frames;                  /* counted in TOWN_OBJECT_ACTOR_GONE */
    struct ObjShadow *shadows;   /* its long shadows (TownObjectActor_InitShadows) */
    struct TouchPickFace *faces; /* one per area, for the pen (TownObjectActor_BuildAreas) */
    TownObjectActorArea *areas;
    u8 area_count;
    u8 unk_291;
    u16 model_slot;     /* main's model pool slot (model_pool.h) */
    Vec3 bounds_centre; /* the centre of its shape (TownObjectActor_SetBounds) */
    fx32 bounds_width;
    fx32 bounds_depth;
    Vec3 talk_point; /* the stand point moved back by 4.0 along z (vtable slot 0x50) */
} TownObjectActor;

int TownObjectActor_SlotB8(TownObjectActor *actor);
void TownObjectActor_Position(Vec3 *out, TownObjectActor *actor);
void TownObjectActorSound_PlayEx(TownObjectActorSound *sound, int number);
void TownObjectActorSound_Play(TownObjectActorSound *sound, int number);
void TownObjectActorSound_TurnOff(TownObjectActorSound *sound);
void TownObjectActorSound_UpdateAt(TownObjectActorSound *sound, const Vec3 *pos);
void TownObjectActorSound_TurnOn(TownObjectActorSound *sound);
void *TownObjectActorSound_Destroy(TownObjectActorSound *sound);
void *TownObjectActorSound_Construct(TownObjectActorSound *sound);
int TownObjectActor_LightsLit(TownObjectActor *actor);
u32 TownObjectActor_TileZ(TownObjectActor *actor);
int TownObjectActor_TileX(TownObjectActor *actor);
int TownObjectActor_CodeAddress(TownObjectActor *actor);
int TownObjectActor_IdleSetModeByKindA(TownObjectActor *actor);
int TownObjectActor_SetModeByKindA(TownObjectActor *actor);
int TownObjectActor_IdleSetModeByKindB(TownObjectActor *actor);
int TownObjectActor_SetModeByKindB(TownObjectActor *actor);
int TownObjectActor_IsInMode0(TownObjectActor *actor);
void TownObjectActor_UpdateOutOfView(TownObjectActor *actor);
int TownObjectActor_IsOutOfView(TownObjectActor *actor);
int TownObjectActor_Slot98(TownObjectActor *actor);
int TownObjectActor_KeepsPointX(TownObjectActor *actor);
int TownObjectActor_DrawsModel(TownObjectActor *actor);
int TownObjectActor_WalksWithState38(TownObjectActor *actor);
int TownObjectActor_RecordByte5(TownObjectActor *actor);
int TownObjectActor_RecordId(TownObjectActor *actor);
int TownObjectActor_GetStandPoint(TownObjectActor *actor, Vec3 *point, s16 *angle);
void TownObjectActor_DrawModel(TownObjectActor *actor);
void TownObjectActor_OnTalkClosed(TownObjectActor *actor);
void TownObjectActor_OnTalkWait(TownObjectActor *actor);
void TownObjectActor_OnTalkOpen(TownObjectActor *actor);
void TownObjectActor_PrepareTalk(TownObjectActor *actor);
void TownObjectActor_OnMessageEnd(TownObjectActor *actor);
void TownObjectActor_OnSceneEvent(TownObjectActor *actor, unsigned int event, int arg);
int TownObjectActor_CanTalkTo(TownObjectActor *actor, TownObjectActor *other);
int TownObjectActor_TalkPointAddress(TownObjectActor *actor);
void TownObjectActor_UpdateWalkAgain(TownObjectActor *actor);
int TownObjectActor_EnterWalkAgain(TownObjectActor *actor);
void TownObjectActor_UpdateLeaveAgain(TownObjectActor *actor);
int TownObjectActor_EnterLeaveAgain(TownObjectActor *actor);
void TownObjectActor_UpdateGone(TownObjectActor *actor);
int TownObjectActor_EnterGone(TownObjectActor *actor);
void TownObjectActor_UpdateWalk(TownObjectActor *actor);
int TownObjectActor_EnterWalk(TownObjectActor *actor);
void TownObjectActor_UpdateLeave(TownObjectActor *actor);
int TownObjectActor_EnterLeave(TownObjectActor *actor);
void TownObjectActor_UpdateTalkEnd(TownObjectActor *actor);
int TownObjectActor_EnterTalkEnd(TownObjectActor *actor);
void TownObjectActor_UpdateTalk(TownObjectActor *actor);
int TownObjectActor_EnterTalk(TownObjectActor *actor);
void TownObjectActor_UpdateVisit(TownObjectActor *actor);
int TownObjectActor_EnterVisit(TownObjectActor *actor);
void TownObjectActor_UpdateIdle(TownObjectActor *actor);
int TownObjectActor_EnterIdle(TownObjectActor *actor);
void TownObjectActor_UpdateState(TownObjectActor *actor);
int TownObjectActor_SetState(TownObjectActor *actor, int state);
void TownObjectActor_RunMode6(TownObjectActor *actor);
int TownObjectActor_EnterMode6(void);
void TownObjectActor_RunMode5(TownObjectActor *actor);
int TownObjectActor_EnterMode5(void);

#endif
