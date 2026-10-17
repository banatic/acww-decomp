/* Overlay 53: the barber, the special character of the message archive "sp_npc_barber" with the
 * model npc_sp/model/poo, object profile 0x61 (its record at data_ov053_02261a5c, which the
 * main module's profile table data_020e3134 points to). The scenes 0x1f, 0x21 and 0x29 name
 * overlay 53 in their SceneInfo (data_ov013_022600e8, data_020e55bc). A scene object of class
 * 0x020da088 (special_scene_object.h) with vtable data_ov053_02261b98, 0x720 bytes, made by
 * Barber_Create. Overlay 4's room object BarberMachine (barber_machine.h) is the machine she
 * sets running during a cut.
 *
 * Its talk scene (BarberTalk, barber_talk.h, vtable data_ov053_02261b08, at 0x658) sells the
 * cut: the hair style and colour the player picks are applied to the player's field actor
 * when she cuts.
 *
 * Its states (Barber.state, BARBER_STATE_*) are a table of C++ pointers to member functions
 * (data_ov053_02261c64, an entry and an update for each, filled at start-up by
 * __sinit_ov053_0226182c), set by Barber_SetState and run each frame by Barber_Update:
 *   0  call:       each frame she asks for an event of kind 6 (to call the player over);
 *   1  stand:      she stands and watches the player: seated in the chair, walking to the door
 *                  with the cut paid for, or on the map's claimed object, she asks for an event;
 *   2  talk:       she turns to the one she talks with and talks; then by the topic: she walks
 *                  to the chair (state 7), walks back to put the hat on again (state 6), or the
 *                  event ends (state 3);
 *   3  talked:     nothing;
 *   4  turn back:  she turns to the angle at 0x71c, then stands;
 *   5  walk A:     she turns to 0x4000 and walks the points of route A, then turns back;
 *   6  walk B:     she turns to route B's first point and walks it, then talks;
 *   7  to cut:     she looks ahead, turns to 0x4000 and walks route A, turns to -0x4000, then
 *                  cuts;
 *   8  cut:        her animation 0xf1 for 100 frames; at the 15th the player's hair changes,
 *                  the machine runs and a sound plays; then she talks (the topic cut);
 *   9  send back:  the player is walked back to (16.0, 27.0), then the event ends and she
 *                  turns back;
 *   10 paused:     an event starts: nothing. */
#ifndef CLEAN_OV053_BARBER_H
#define CLEAN_OV053_BARBER_H

#include "barber_talk.h"
#include "ov004/member_pointer.h"
#include "types.h"

enum BarberState {
    BARBER_STATE_CALL = 0,
    BARBER_STATE_STAND = 1,
    BARBER_STATE_TALK = 2,
    BARBER_STATE_TALKED = 3,
    BARBER_STATE_TURN_BACK = 4,
    BARBER_STATE_WALK_A = 5,
    BARBER_STATE_WALK_B = 6,
    BARBER_STATE_TO_CUT = 7,
    BARBER_STATE_CUT = 8,
    BARBER_STATE_SEND_BACK = 9,
    BARBER_STATE_PAUSED = 10,
    BARBER_STATES = 11
};

/* A state's functions in data_ov053_02261c64. */
typedef struct BarberStep {
    MemberPointer enter;  /* 0x00: int (barber); the state is taken unless it answers 0 */
    MemberPointer update; /* 0x08: int (barber) */
} BarberStep;

/* The size of the special character's scene object it derives from, as far as it is used. */
#define BARBER_BASE_SIZE 0x654

typedef struct Barber {
    u8 base[BARBER_BASE_SIZE]; /* 0x000: the special character's scene object */
    s32 state;                 /* 0x654: enum BarberState */
    BarberTalk talk;           /* 0x658 */
    u8 send_step;              /* 0x718: state 9's step */
    u8 waypoint;               /* 0x719: the point of the route walked to */
    u8 cut_countdown;          /* 0x71a: the frames left of the cut */
    u8 music_countdown;        /* 0x71b: the frames before the music's priority 0xe is dropped */
    s16 home_angle;            /* 0x71c: the angle she turns back to */
    u8 unk_71e[2];             /* 0x71e */
} Barber;

/* Its vtable slots (barber.c). */
Barber *Barber_Destruct(Barber *barber);
void *Barber_DestructDelete(void *barber);
void Barber_OnEvent(Barber *barber, unsigned int code, u8 participant);
int Barber_MayTalk(Barber *barber);
int Barber_MayAct(Barber *barber);
int Barber_Update(Barber *barber);
int Barber_ModelName(void);
int Barber_TextureName(void);
int Barber_Start(Barber *barber);
int Barber_Init(Barber *barber);
void *Barber_Create(void);
void Barber_SetState(Barber *barber, int state);

/* What it asks about the player (barber.c). */
int Barber_IsPaid(int unused);
int Barber_WearsHat(void *unused);
int Barber_CheckClaimed(Barber *barber);
int Barber_CheckLeaving(Barber *barber);
int Barber_CheckSeated(Barber *barber);

/* Its states (barber.c). */
int Barber_EnterCall(Barber *barber);
int Barber_UpdateCall(Barber *barber);
int Barber_EnterStand(Barber *barber);
int Barber_UpdateStand(Barber *barber);
int Barber_EnterTalk(Barber *barber);
int Barber_UpdateTalk(Barber *barber);
int Barber_EnterTalked(void);
int Barber_UpdateTalked(void);
int Barber_EnterTurnBack(Barber *barber);
int Barber_UpdateTurnBack(Barber *barber);
int Barber_EnterWalkA(Barber *barber);
int Barber_UpdateWalkA(Barber *barber);
int Barber_EnterWalkB(Barber *barber);
int Barber_UpdateWalkB(Barber *barber);
int Barber_EnterToCut(Barber *barber);
int Barber_UpdateToCut(Barber *barber);
int Barber_EnterCut(Barber *barber);
int Barber_UpdateCut(Barber *barber);
int Barber_EnterSendBack(Barber *barber);
int Barber_UpdateSendBack(Barber *barber);
int Barber_EnterPaused(void);
int Barber_UpdatePaused(void);

#endif
