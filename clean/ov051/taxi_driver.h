/* Overlay 51: the taxi's driver of the opening, the special character with the model
 * npc_sp/model/wip and the lines of the message file "sp_etc_sequence3", object profile 0x7b
 * (its record at data_ov051_022617c8, which main's profile table data_020e3134 points to).
 * Overlay 51 is the extra overlay of scene 0x2d (its SceneInfo, data_ov044_022600c8 of
 * data_020e55bc), the scene the start menu's job 0xe enters (main's activity_jobs.h) when a
 * game is started; the taxi itself is overlay 68's (ov068/taxi.h), whose handle follows the
 * animation this character plays (TaxiDriver_CurrentAnim) and whose rain and figure this
 * character's talk starts and stops.
 *
 * A scene object of class 0x020da088 (main's special_scene_object.h) with vtable 0x0226193c,
 * 0x71c bytes, made by TaxiDriver_Create. data_ov051_02261b80 points to the one started last.
 *
 * Its talk scene (TaxiDriverTalk, taxi_driver_talk.h, at 0x658) asks the player the
 * questions of a new game: the time (the screen it opens in mode 0x30), two more screens
 * (modes 0x0f and 0x10), the player's kind and three questions whose answers make the
 * player's face (TaxiDriver.points).
 *
 * Its states (TaxiDriver.state, TAXI_DRIVER_*), each an entry and an update function (C++
 * members taking it) from the table data_ov051_02261ba8 (filled at start-up by
 * __sinit_ov051_0226150c), set by TaxiDriver_SetState and run each frame by
 * TaxiDriver_Update:
 *   0  wait:    once the screen's transition has shown the screen, it waits 0x29 frames and
 *               talks (state 1);
 *   1  talk:    it talks (TaxiDriverTalk);
 *   2  done:    nothing;
 *   3  arrive:  once the screen is closed: the game is started in the kind the start menu
 *               chose (StateBlock_Start) and the player is put out in front of the town's
 *               building 0x5000 (scene 0); state 2;
 *   4  leave:   set by the talk's end; once talk 0 is closed, one time in four the taxi's
 *               figure plays and the driver's animation 0x8f follows 10 frames later; the
 *               screen closes (a fade to black over 15 frames) and the scene's sound stops;
 *               state 3. */
#ifndef CLEAN_OV051_TAXI_DRIVER_H
#define CLEAN_OV051_TAXI_DRIVER_H

#include "main/scene_base.h"
#include "ov004/member_pointer.h"
#include "types.h"

struct TaxiDriver;

/* Its talk scene (0xbc bytes, a scene base of main's scene_base.h, vtable 0x02261804). Its
 * receiver's message (byte 0x1e of the scene) is the line shown. */
typedef struct TaxiDriverTalk {
    SceneBase base;           /* 0x00 */
    u8 unk_80[0x30];          /* 0x80: the scene's commands (scene_command.h) */
    struct TaxiDriver *owner; /* 0xb0 */
    MemberPointer after;      /* 0xb4: run once a command of the scene ends, then cleared */
} TaxiDriverTalk;

/* The size of the special character's scene object it derives from, as far as it is used. */
#define TAXI_DRIVER_BASE_SIZE 0x654

typedef struct TaxiDriver {
    u8 base[TAXI_DRIVER_BASE_SIZE]; /* 0x000: the special character's scene object */
    s32 state;                      /* 0x654: enum TaxiDriverState */
    TaxiDriverTalk talk;            /* 0x658 */
    s32 points;                     /* 0x714: the answers' points (1, 2 and 4), 0 to 7: the face */
    u16 wait;                       /* 0x718: state 0's frames left before it talks */
    u8 anim_wait;                   /* 0x71a: the frames left before its animation 0x8f */
    u8 unk_71b;                     /* 0x71b */
} TaxiDriver;

enum TaxiDriverState {
    TAXI_DRIVER_WAIT = 0,
    TAXI_DRIVER_TALK = 1,
    TAXI_DRIVER_DONE = 2,
    TAXI_DRIVER_ARRIVE = 3,
    TAXI_DRIVER_LEAVE = 4,
    TAXI_DRIVER_STATES = 5
};

/* A state's functions in data_ov051_02261ba8. */
typedef struct TaxiDriverStep {
    MemberPointer enter;  /* 0x00: int (driver); the state is taken unless it answers 0 */
    MemberPointer update; /* 0x08: int (driver) */
} TaxiDriverStep;

void *TaxiDriver_Destroy(void *driver);
void *TaxiDriver_Delete(void *driver);
int TaxiDriver_CurrentAnim(void);
unsigned int TaxiDriver_CurrentFrame(void);
int TaxiDriver_UpdateLeave(TaxiDriver *driver);
int TaxiDriver_EnterLeave(void);
int TaxiDriver_UpdateArrive(TaxiDriver *driver);
int TaxiDriver_EnterArrive(void);
int TaxiDriver_UpdateDone(void);
int TaxiDriver_EnterDone(void);
int TaxiDriver_UpdateTalk(void);
int TaxiDriver_EnterTalk(TaxiDriver *driver);
int TaxiDriver_UpdateWait(TaxiDriver *driver);
int TaxiDriver_EnterWait(void);
int TaxiDriver_SoundNumber(void);
int TaxiDriver_ActionSound(void);
void TaxiDriver_SetState(TaxiDriver *driver, int state);
int TaxiDriver_Update(TaxiDriver *driver);
int TaxiDriver_ModelName(void);
int TaxiDriver_TextureName(void);
int TaxiDriver_Leave(void *driver);
int TaxiDriver_Start(TaxiDriver *driver);
int TaxiDriver_Init(TaxiDriver *driver);
void *TaxiDriver_Create(void);

#endif
