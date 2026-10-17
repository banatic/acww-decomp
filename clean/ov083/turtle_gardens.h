/* Overlay 83: the turtle (message files "sp_npc_turtle3" and "sp_npc_turtle", the model
 * npc_sp/model/ttl) as the judge of the town's gardens. He is made by main's spawner
 * (spawner.h): while event 0x16 of its table data_020d06a4 is on, its check 3 asks for object
 * profile 0x59, whose spawn table entry (person code 0xd012) loads overlay 83 with him; his
 * profile record at 0x022791c0 (profile 0x59) has TurtleGardens_Create as its create function.
 * Overlays 81 (turtle_fishing.h) and 82 (turtle_insects.h) are the same person at the fishing
 * tourney and the insect contest.
 *
 * He is a scene object of class 0x020da088 (main's special_scene_object.h) with vtable
 * 0x0227928c, 0x71c bytes. On his start he plays animation 0x140, is held (flag 2 at 0x4e8),
 * notes the days since the start of the calendar's event 0x0e, and the town's record of the
 * day's winner (data_021f3aa4, main's event_winner.h) is dropped unless it is still of that
 * event (EventWinner_ExpireForEvent, event 0). While he stands, every 600 frames (the first
 * at once) the gardens are judged into the record (EventWinner_JudgeGardens) and a winner is
 * to be announced. The player may talk to him while his action is idle; his talk scene
 * (TurtleGardensTalk, turtle_gardens_talk.h) gives a prize once a day.
 *
 * His states (TurtleGardens.state), each an entry and an update function (C++ members taking
 * him) from the table data_ov083_02279360 (filled at start-up by __sinit_ov083_02279100), set
 * by TurtleGardens_SetState:
 *   0  stand:  he stands, and judges the gardens;
 *   1  talk:   he turns to the talk's partner and talks; once his action is idle his event is
 *              finished (state 2);
 *   2  talked: nothing. */
#ifndef CLEAN_OV083_TURTLE_GARDENS_H
#define CLEAN_OV083_TURTLE_GARDENS_H

#include "main/scene_base.h"
#include "ov004/member_pointer.h"
#include "types.h"

struct TurtleGardens;

/* His talk scene (0xbc bytes): a scene of class 0x020d9ff8 (main's obj_020d9ff8.h) with vtable
 * 0x022791fc (turtle_gardens_talk.h). */
typedef struct TurtleGardensTalk {
    SceneBase base;              /* 0x00: the receiver's message (byte 0x1e) is the line shown */
    u8 unk_80[0x30];             /* 0x80: the scene's commands (scene_command.h) */
    struct TurtleGardens *owner; /* 0xb0 */
    s32 slot_37e0;               /* 0xb4: TURTLE_GARDENS_TALK_37E0_*, or the pocket of item
                                  * 0x37e0 */
    u16 prize;                   /* 0xb8: the prize picked, 0xfff1 for none */
    u8 unk_ba[2];                /* 0xba */
} TurtleGardensTalk;

/* The size of the special character's scene object he derives from, as far as it is used. */
#define TURTLE_GARDENS_BASE_SIZE 0x654

typedef struct TurtleGardens {
    u8 base[TURTLE_GARDENS_BASE_SIZE]; /* 0x000: the special character's scene object */
    s32 countdown;                     /* 0x654: the frames until the gardens are judged again */
    s32 state;                         /* 0x658: enum TurtleGardensState */
    TurtleGardensTalk talk;            /* 0x65c */
    u8 event_day;                      /* 0x718: the days since event 0x0e started, cut to a
                                        * byte (0xff when it is not on) */
    u8 unk_719[3];                     /* 0x719 */
} TurtleGardens;

enum TurtleGardensState {
    TURTLE_GARDENS_STAND = 0,
    TURTLE_GARDENS_TALK = 1,
    TURTLE_GARDENS_TALKED = 2,
    TURTLE_GARDENS_STATES = 3
};

/* A state's functions in data_ov083_02279360. */
typedef struct TurtleGardensStep {
    MemberPointer enter;  /* 0x00: int (him); the state is taken unless it answers 0 */
    MemberPointer update; /* 0x08: int (him) */
} TurtleGardensStep;

/* His object. */
TurtleGardens *TurtleGardens_Destruct(TurtleGardens *turtle);
TurtleGardens *TurtleGardens_DestructDelete(TurtleGardens *turtle);
void TurtleGardens_OnEvent(TurtleGardens *turtle, int code);
int TurtleGardens_AgreesToTalk(TurtleGardens *turtle);
void TurtleGardens_SetState(TurtleGardens *turtle, int state);
int TurtleGardens_Update(TurtleGardens *turtle);
int TurtleGardens_ModelName(void);
int TurtleGardens_TextureName(void);
int TurtleGardens_Start(TurtleGardens *turtle);
int TurtleGardens_Init(TurtleGardens *turtle);
void *TurtleGardens_Create(void);
int TurtleGardens_CountDown(TurtleGardens *turtle, s32 *counter);

/* His states. */
int TurtleGardens_EnterStand(TurtleGardens *turtle);
int TurtleGardens_UpdateStand(TurtleGardens *turtle);
int TurtleGardens_EnterTalk(TurtleGardens *turtle);
int TurtleGardens_UpdateTalk(TurtleGardens *turtle);
int TurtleGardens_UpdateTalked(void);

#endif
