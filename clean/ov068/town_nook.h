/* The character drawn with the models npc_sp/model/rcn, rcc, rcs and rcd who meets a new
 * player in the town and talks of the house and its loan (Tom Nook): a special character's
 * scene object (main's special_scene_object.h) of vtable data_ov068_02277574, 0x728 bytes,
 * made by func_ov068_0226eaac. Its parts read here:
 *
 * - 0x654 its state (one of a table of member functions, data_ov068_02278658; changed by
 *   func_ov068_0226e878, which runs the new state's start first);
 * - 0x658 its talk scene (TownNookScene below);
 * - 0x718 the point it walks to.
 *
 * Its vtable slots here: 0x40 and 0x44 the destructors, 0x48 whether the player may act on it
 * (in state 0 only), 0x4c told of an event (1 gives state 2, 8 state 5).
 *
 * Its talk scene (a scene of main's class 0x020d9ff8, vtable data_ov068_022774e4) runs the
 * talk's messages from the file "sp_etc_sequence4". Starting the talk (its slot 0x78) gives
 * message 0x22; once that ends the talk window closes and the scene's step 1 runs each frame:
 * when the window is gone the music changes, the player is held (flag 0x0e off), the
 * character walks 6.0 along x and stands, and then the talk opens again with message 0xd in a
 * new town (else 0xa) and the camera looks at the character. After that the messages follow on
 * from one another (TownNookScene_OnMessageEnded): the loan of the house is put into the talk
 * (message 0xf when there is none), then by whether the town is new and how many players live
 * in it, and whether the player is new.
 *
 * The scene's steps are a table of member functions with a flag (data_ov068_02277454): a step
 * with the flag runs each frame while the talk's link is open (slot 0x80), one without runs
 * once it closes (slot 0x84) and the scene goes back to step 0. */
#ifndef CLEAN_OV068_TOWN_NOOK_H
#define CLEAN_OV068_TOWN_NOOK_H

#include "autoload_2/vector.h"
#include "main/scene_base.h"
#include "types.h"

/* The talk scene (0xd0 bytes). */
typedef struct TownNookScene {
    SceneBase base;
    u8 unk_80[0x30];
    s32 step; /* 0xb0: of the table data_ov068_02277454 */
    u8 state; /* 0xb4: of step 1 */
    u8 unk_b5[3];
    u8 *owner; /* 0xb8: the character */
    u8 unk_bc[0x14];
} TownNookScene;

/* What the talk starts with (the scene's slot 0x78). */
typedef struct TownNookTalkStart {
    const char *name; /* the message file */
    u8 message;
} TownNookTalkStart;

u8 *TownNook_Destruct(u8 *object);
u8 *TownNook_DestructDelete(u8 *object);
void TownNook_OnEvent(u8 *object, int code);
int TownNook_MayAct(u8 *object);
void TownNookScene_WalkAndTalk(TownNookScene *scene);
void TownNookScene_SetStep(TownNookScene *scene, int step);
void TownNookScene_OnTalkClosed(TownNookScene *scene);
void TownNookScene_WhileTalkOpen(TownNookScene *scene);
void TownNookScene_OnAnswer(void);
void TownNookScene_OnMessageEnded(TownNookScene *scene);
void TownNookScene_StartTalk(TownNookScene *scene, TownNookTalkStart *start);
void TownNookScene_Begin(TownNookScene *scene, u8 *owner);
TownNookScene *TownNookScene_DestructDelete(TownNookScene *scene);
TownNookScene *TownNookScene_Destruct(TownNookScene *scene);
TownNookScene *TownNookScene_Construct(TownNookScene *scene);

/* The character's states (each with a start and an update in data_ov068_02278658):
 *   0 waits: each frame it asks main's event queue for an event of kind 6 about it and, once
 *     given one, sets the player's flag 0x0e back on;
 *   1 turns to the scene's other speaker and talks (its scene action); once that ends the
 *     camera's mode is reset, music 0x47 dropped and state 3 follows;
 *   2 (after event 1) the player walks to 2.0 south of its starting point; once the player is
 *     free the talk scene is reset, given the player's object, and state 1 follows;
 *   3 turns (motion kind 3), then state 4;
 *   4 walks off to 2.0 west and 10.0 south of where it stands; once there, or after 60
 *     frames, its event is finished;
 *   5 (after event 8) 10 frames later the music is set back and it is deleted. */
#define TOWN_NOOK_WAIT 0
#define TOWN_NOOK_TALK 1
#define TOWN_NOOK_CALL_PLAYER 2
#define TOWN_NOOK_TURN 3
#define TOWN_NOOK_LEAVE 4
#define TOWN_NOOK_END 5
#define TOWN_NOOK_STATES 6

int TownNook_UpdateEnd(u8 *object);
int TownNook_StartEnd(u8 *object);
int TownNook_UpdateLeave(u8 *object);
int TownNook_StartLeave(u8 *object);
int TownNook_UpdateTurn(u8 *object);
int TownNook_StartTurn(u8 *object);
int TownNook_UpdateCallPlayer(u8 *object);
int TownNook_StartCallPlayer(void);
int TownNook_UpdateTalk(u8 *object);
int TownNook_StartTalk(u8 *object);
int TownNook_UpdateWait(u8 *object);
int TownNook_StartWait(void);
void TownNook_SetState(u8 *object, int state);
int TownNook_Update(u8 *object);
int TownNook_ModelName(void);
int TownNook_TextureName(void);
int TownNook_Start(u8 *object);
int TownNook_Init(u8 *object);
u8 *TownNook_Create(void);

#endif
