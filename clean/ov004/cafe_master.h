/* The cafe's master, drawn with the model npc_sp/model/pge: a special character's scene object
 * (main's special_scene_object.h) of vtable data_ov004_022546e0, 0x780 bytes, made by
 * CafeMaster_Create, with its talk scene at 0x658. data_ov004_022580dc points to it from its
 * start (CafeMaster_Start) until it may be deleted (CafeMaster_Leave).
 *
 * The cafe's props (cafe_props.h) follow it through the functions here: the number of the
 * animation it plays (its animation player at 0x334), that animation's frame (its model's
 * frame at 0x190, 20.12) and two of its matrices, at 0x718 and 0x748. */
#ifndef CLEAN_OV004_CAFE_MASTER_H
#define CLEAN_OV004_CAFE_MASTER_H

#include "autoload_2/matrix.h"
#include "main/scene_base.h"
#include "member_pointer.h"
#include "types.h"

u8 *CafeMaster_Destroy(u8 *master);
u8 *CafeMaster_Delete(u8 *master);
int CafeMaster_AnimNumber(void);
u16 CafeMaster_AnimFrame(void);
Mtx43 *CafeMaster_Matrix748(void);
Mtx43 *CafeMaster_Matrix718(void);

/* The master's states (CafeMaster.state), each an entry and an update function (C++ members
 * taking him), from the table data_ov004_022580e0 (filled at start-up by
 * __sinit_ov004_0224e734), set by CafeMaster_SetState:
 *   0  stand:      he stands behind the counter; once he has looked aside (more than an
 *                  eighth of a turn) he looks ahead again 20 frames later; unlinked, when this
 *                  console's player is in its field state 0x27 an event of kind 7 is asked
 *                  for him; when he no longer faces where he did at his start, state 3;
 *   1  talk:       he looks at the player and talks, turned to the talk's partner; once his
 *                  action is idle the event ends: state 2;
 *   2  talked:     nothing;
 *   3  turn back:  he turns to the angle he faced at his start, then stands (state 0);
 *   4  wait seat:  once this console's player is in its field state 0x28, he talks;
 *   5  await:      while the session decides who runs him: once this system owns and holds
 *                  him, he talks (state 1); once this system holds the scene and no system
 *                  holds him, he stands;
 *   6  other:      another system's player talks to him: once no system owns him and this one
 *                  holds the scene, he is this system's again and stands;
 *   7  paused:     an event starts: nothing.
 *
 * His talk scene (CafeMasterTalk) runs the coffee: after the player pays for one, the
 * sequences of its states 1 to 3 (CafeMasterTalk.sequence, from the table
 * data_ov004_02254618) move the master and the cafe's props (cafe_props.h) through the
 * making, the drinking and the clearing up, a step (CafeMasterTalk.step) at a time, the
 * frames counted in CafeMaster.talk_frames; each sequence ends with a message and state 0.
 * How many coffees the player has had is the count 0x09 of the player record's object at
 * 0x2416 (main's player_field_2416.h, up to 15); a quarter of it picks his lines. */
enum CafeMasterState {
    CAFE_MASTER_STAND = 0,
    CAFE_MASTER_TALKING = 1,
    CAFE_MASTER_TALKED = 2,
    CAFE_MASTER_TURN_BACK = 3,
    CAFE_MASTER_WAIT_SEAT = 4,
    CAFE_MASTER_AWAIT = 5,
    CAFE_MASTER_OTHER = 6,
    CAFE_MASTER_PAUSED = 7,
    CAFE_MASTER_STATES = 8
};

/* The sequences of his talk scene (CafeMasterTalk.sequence). */
enum CafeMasterTalkSequence {
    CAFE_MASTER_TALK_NONE = 0,
    CAFE_MASTER_TALK_BREW = 1,  /* func_ov004_02223dcc */
    CAFE_MASTER_TALK_DRINK = 2, /* func_ov004_02223c40 */
    CAFE_MASTER_TALK_CLEAR = 3, /* func_ov004_0222393c */
    CAFE_MASTER_TALK_SEQUENCES = 4
};

struct CafeMaster;

/* His talk scene (0xbc bytes, a scene base of main's scene_base.h, vtable
 * data_ov004_02254650). */
typedef struct CafeMasterTalk {
    SceneBase base;            /* 0x00 */
    u8 unk_80[0x30];           /* 0x80 */
    s32 sequence;              /* 0xb0: enum CafeMasterTalkSequence */
    struct CafeMaster *master; /* 0xb4 */
    u8 step;                   /* 0xb8: the step of the sequence */
    u8 saw_message_2d;         /* 0xb9: message 0x2d ended since the last clearing up */
    u8 unk_ba[2];              /* 0xba */
} CafeMasterTalk;

/* What his talk scene's line function gives: the message file's name (an address) and the
 * message. */
typedef struct CafeMasterLine {
    u32 text;
    u8 message;
    u8 unk_05[3];
} CafeMasterLine;

/* A state's functions in data_ov004_022580e0. */
typedef struct CafeMasterStep {
    MemberPointer enter;  /* 0x00: int (master); the state is taken unless it answers 0 */
    MemberPointer update; /* 0x08: int (master) */
} CafeMasterStep;

/* A sequence's function in data_ov004_02254618, and when it runs: each step of the scene
 * (slot 0x80) when `each_step` is set, else when a command of the scene ends (slot 0x84). */
typedef struct CafeMasterTalkStep {
    MemberPointer run; /* void (talk) */
    u8 each_step;
    u8 unk_09[3];
} CafeMasterTalkStep;

/* The size of the special character's scene object he derives from, as far as it is used. */
#define CAFE_MASTER_BASE_SIZE 0x654

typedef struct CafeMaster {
    u8 base[CAFE_MASTER_BASE_SIZE]; /* 0x000: the special character's scene object */
    s32 state;                      /* 0x654: enum CafeMasterState */
    CafeMasterTalk talk;            /* 0x658 */
    s16 home_yaw;                   /* 0x714: the angle he faced at his start */
    u8 unk_716[2];                  /* 0x716 */
    Mtx43 matrix_718;               /* 0x718: his model's joint 14, at each draw */
    Mtx43 matrix_748;               /* 0x748: his model's joint 11, at each draw */
    s32 look_timer;                 /* 0x778: 0 waiting for a look aside, then frames, -1 done */
    u16 talk_frames;                /* 0x77c: the frames of a step of his talk's sequences */
    u8 on_beat;                     /* 0x77e: a music with a beat plays (his model follows it) */
    u8 unk_77f;                     /* 0x77f */
} CafeMaster;

void CafeMaster_OnEvent(CafeMaster *master, int code, int participant);
int CafeMaster_MayAct(CafeMaster *master);
void CafeMasterTalk_ClearUp(CafeMasterTalk *talk);
void CafeMasterTalk_OnClose(CafeMasterTalk *talk);
void CafeMasterTalk_Drink(CafeMasterTalk *talk);
void CafeMasterTalk_Brew(CafeMasterTalk *talk);
void CafeMasterTalk_SetSequence(CafeMasterTalk *talk, int sequence);
void CafeMasterTalk_RunCommandSequence(CafeMasterTalk *talk);
void CafeMasterTalk_RunStepSequence(CafeMasterTalk *talk);
void CafeMasterTalk_OnAnswer(CafeMasterTalk *talk);
void CafeMasterTalk_OnMessageEnded(CafeMasterTalk *talk);
void CafeMasterTalk_Line(CafeMasterTalk *talk, CafeMasterLine *out);
void CafeMasterTalk_Begin(CafeMasterTalk *talk, CafeMaster *master);
CafeMasterTalk *CafeMasterTalk_Delete(CafeMasterTalk *talk);
CafeMasterTalk *CafeMasterTalk_Destroy(CafeMasterTalk *talk);
CafeMasterTalk *CafeMasterTalk_Construct(CafeMasterTalk *talk);
int CafeMaster_UpdatePaused(void);
int CafeMaster_EnterPaused(void);
int CafeMaster_UpdateOther(CafeMaster *master);
int CafeMaster_EnterOther(CafeMaster *master);
int CafeMaster_UpdateAwait(CafeMaster *master);
int CafeMaster_EnterAwait(CafeMaster *master);
int CafeMaster_UpdateWaitSeat(CafeMaster *master);
int CafeMaster_EnterWaitSeat(void);
int CafeMaster_UpdateTurnBack(CafeMaster *master);
int CafeMaster_EnterTurnBack(CafeMaster *master);
int CafeMaster_UpdateTalked(void);
int CafeMaster_EnterTalked(void);
int CafeMaster_UpdateTalk(CafeMaster *master);
int CafeMaster_EnterTalk(CafeMaster *master);
int CafeMaster_UpdateStand(CafeMaster *master);
int CafeMaster_EnterStand(CafeMaster *master);
void CafeMaster_SetState(CafeMaster *master, int state);
int CafeMaster_Update(CafeMaster *master);
const char *CafeMaster_TextureName(void);
const char *CafeMaster_ModelName(void);
int CafeMaster_Draw(CafeMaster *master);
int CafeMaster_Leave(CafeMaster *master);
int CafeMaster_Start(CafeMaster *master);
int CafeMaster_Init(CafeMaster *master);
CafeMaster *CafeMaster_Create(void);

#endif
