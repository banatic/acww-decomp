/* A gatekeeper indoors, drawn with the model npc_sp/model/pla and talking with the lines of
 * the message file "sp_npc_gatekeeper2": a special character's scene object (main's
 * special_scene_object.h) of vtable data_ov004_02254918, 0x714 bytes (made by
 * Gatekeeper2_Create), with its talk scene at 0x658 and the angle it faced at its start at
 * 0x710.
 *
 * Its states (0x654), each an entry and an update function (C++ members taking it), from the
 * table data_ov004_02258190 (filled at start-up by __sinit_ov004_0224e85c), set by
 * Gatekeeper2_SetState:
 *   0  stand:      it stands (priority 1);
 *   1  talk:       it turns to the talk's partner and talks; once its action is idle the
 *                  event ends: state 2;
 *   2  talked:     nothing;
 *   3  turn back:  it turns to the angle it faced at its start, then stands;
 *   4  await:      while the session decides who runs it: once this system owns and holds
 *                  it, it talks; once this system holds the scene and no system holds it, it
 *                  stands;
 *   5  other:      another system's player talks to it: once no system owns it and this one
 *                  holds the scene, it is this system's again and turns back;
 *   6  paused:     an event starts: nothing.
 * Its vtable slot 0x4c (Gatekeeper2_OnEvent) moves it between them as the cafe's master's
 * does (cafe_master.h).
 *
 * Its talk scene (Gatekeeper2Talk) answers about the special character visiting the town
 * today (main's spawner.h) or who joined the session last, and the items of the town's list A
 * (main's town_item_lists.h); after some lines it opens a screen of the overlay group 9 (main's
 * group_params.h), and once that screen's command ends one of three tasks runs (its states,
 * Gatekeeper2Talk.state): the player's design picked on the screen copied to, or swapped with,
 * the design of kind 5 (main's design.h), or the first item of the player's pockets named. */
#ifndef CLEAN_OV004_GATEKEEPER2_H
#define CLEAN_OV004_GATEKEEPER2_H

#include "main/scene_base.h"
#include "member_pointer.h"
#include "types.h"

enum Gatekeeper2State {
    GATEKEEPER2_STAND = 0,
    GATEKEEPER2_TALK = 1,
    GATEKEEPER2_TALKED = 2,
    GATEKEEPER2_TURN_BACK = 3,
    GATEKEEPER2_AWAIT = 4,
    GATEKEEPER2_OTHER = 5,
    GATEKEEPER2_PAUSED = 6,
    GATEKEEPER2_STATES = 7
};

/* The tasks of its talk scene (Gatekeeper2Talk.state), run when a command of the scene ends. */
enum Gatekeeper2TalkState {
    GATEKEEPER2_TALK_NONE = 0,
    GATEKEEPER2_TALK_COPY_DESIGN = 1, /* func_ov004_0222511c */
    GATEKEEPER2_TALK_SWAP_DESIGN = 2, /* func_ov004_02224ff4 */
    GATEKEEPER2_TALK_NAME_ITEM = 3,   /* func_ov004_02224f98 */
    GATEKEEPER2_TALK_STATES = 4
};

struct Gatekeeper2;

/* Its talk scene (0xb8 bytes, a scene base of main's scene_base.h, vtable
 * data_ov004_02254888). */
typedef struct Gatekeeper2Talk {
    SceneBase base;            /* 0x00 */
    u8 unk_80[0x30];           /* 0x80 */
    struct Gatekeeper2 *owner; /* 0xb0 */
    u32 state;                 /* 0xb4: enum Gatekeeper2TalkState */
} Gatekeeper2Talk;

/* What its talk scene's line function gives: the message file's name (an address) and the
 * message. */
typedef struct Gatekeeper2Line {
    u32 text;
    u8 message;
    u8 unk_05[3];
} Gatekeeper2Line;

/* A task's function in data_ov004_02258160, and when it runs: each step of the scene (slot
 * 0x80) when `each_step` is set, else when a command of the scene ends (slot 0x84). */
typedef struct Gatekeeper2TalkStep {
    MemberPointer run; /* void (talk) */
    u8 each_step;
    u8 unk_09[3];
} Gatekeeper2TalkStep;

/* The size of the special character's scene object it derives from, as far as it is used. */
#define GATEKEEPER2_BASE_SIZE 0x654

typedef struct Gatekeeper2 {
    u8 base[GATEKEEPER2_BASE_SIZE]; /* 0x000: the special character's scene object */
    s32 state;                      /* 0x654: enum Gatekeeper2State */
    Gatekeeper2Talk talk;           /* 0x658 */
    s16 home_yaw;                   /* 0x710: the angle it faced at its start */
    u8 unk_712[2];                  /* 0x712 */
} Gatekeeper2;

Gatekeeper2 *Gatekeeper2_Destroy(Gatekeeper2 *keeper);
Gatekeeper2 *Gatekeeper2_Delete(Gatekeeper2 *keeper);
void Gatekeeper2_OnEvent(Gatekeeper2 *keeper, unsigned int code, int participant);
int Gatekeeper2_MayActOrLocal(Gatekeeper2 *keeper);
int Gatekeeper2_MayAct(Gatekeeper2 *keeper);
void Gatekeeper2Talk_NameItem(Gatekeeper2Talk *talk);
void Gatekeeper2Talk_SwapDesign(Gatekeeper2Talk *talk);
void Gatekeeper2Talk_CopyDesign(Gatekeeper2Talk *talk);
void Gatekeeper2Talk_SetState(Gatekeeper2Talk *talk, u32 state);
void Gatekeeper2Talk_RunCommandState(Gatekeeper2Talk *talk);
void Gatekeeper2Talk_RunStepState(Gatekeeper2Talk *talk);
void Gatekeeper2Talk_OnAnswer(Gatekeeper2Talk *talk);
void Gatekeeper2Talk_OnMessageEnded(Gatekeeper2Talk *talk);
void Gatekeeper2Talk_Line(Gatekeeper2Talk *talk, Gatekeeper2Line *out);
void Gatekeeper2Talk_Begin(Gatekeeper2Talk *talk, Gatekeeper2 *owner);
Gatekeeper2Talk *Gatekeeper2Talk_Delete(Gatekeeper2Talk *talk);
Gatekeeper2Talk *Gatekeeper2Talk_Destroy(Gatekeeper2Talk *talk);
Gatekeeper2Talk *Gatekeeper2Talk_Construct(Gatekeeper2Talk *talk);
int Gatekeeper2_UpdatePaused(void);

/* A state's functions in data_ov004_02258190. */
typedef struct Gatekeeper2Step {
    MemberPointer enter;  /* 0x00: int (keeper); the state is taken unless it answers 0 */
    MemberPointer update; /* 0x08: int (keeper) */
} Gatekeeper2Step;

int Gatekeeper2_EnterPaused(void);
int Gatekeeper2_UpdateOther(Gatekeeper2 *keeper);
int Gatekeeper2_EnterOther(void);
int Gatekeeper2_UpdateAwait(Gatekeeper2 *keeper);
int Gatekeeper2_EnterAwait(void);
int Gatekeeper2_UpdateTurnBack(Gatekeeper2 *keeper);
int Gatekeeper2_EnterTurnBack(Gatekeeper2 *keeper);
int Gatekeeper2_UpdateTalked(void);
int Gatekeeper2_EnterTalked(void);
int Gatekeeper2_UpdateTalk(Gatekeeper2 *keeper);
int Gatekeeper2_EnterTalk(Gatekeeper2 *keeper);
int Gatekeeper2_UpdateStand(void);
int Gatekeeper2_EnterStand(Gatekeeper2 *keeper);
void Gatekeeper2_SetState(Gatekeeper2 *keeper, int state);
int Gatekeeper2_Update(Gatekeeper2 *keeper);
unsigned int Gatekeeper2_ModelName(void);
unsigned int Gatekeeper2_TextureName(void);
int Gatekeeper2_Leave(Gatekeeper2 *keeper);
int Gatekeeper2_Start(Gatekeeper2 *keeper);
int Gatekeeper2_Init(Gatekeeper2 *keeper);
Gatekeeper2 *Gatekeeper2_Create(void);

#endif
