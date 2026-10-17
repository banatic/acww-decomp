/* The character drawn with the model npc_sp/model/hgs who sews at the tailor's machine
 * (tailor_object.h) and talks with the lines of the message file "sp_npc_osister": a special
 * character's scene object (main's special_scene_object.h) of vtable data_ov004_0225445c,
 * 0x714 bytes, made by func_ov004_0222353c (the create function its record at 0x02254378
 * names, after its model's file name).
 *
 * Its parts read here, beyond the special character's: its state at 0x654, its talk scene at
 * 0x658 (TailorSisterTalk below), the angle it faced at its start (the machine's), whether the
 * player's dated event of kind 2 was told today (main's day_events.h), the frame of its sewing
 * animation where it stopped, and how many whole turns (56 frames each) the machine's part has
 * run, which it shares with the session (SceneShare_SetExtra) each frame.
 *
 * Each player keeps how many days it has talked with it, up to 15 (the byte 8 of the player
 * record's object at 0x2416, main's player_field_2416.h; 15 qualifies the player for the dated
 * events of kind 2). Its first talk of a day counts one more day; from 6 days it turns to the
 * player and looks at them as it talks.
 *
 * Its states (0x654), each an entry and an update function (C++ members taking it), from the
 * table data_ov004_0225806c (filled at start-up by __sinit_ov004_0224e668), set by
 * TailorSister_SetState:
 *   0  sew:       it plays its sewing animation (0xe4) from where it stopped and runs the
 *                 machine in step with it; when it no longer faces the machine, state 3;
 *   1  talk:      the machine stops and it talks; once its action is idle a new day of talks
 *                 may be counted, the object's event ends: state 2;
 *   2  talked:    nothing;
 *   3  turn back: it turns to the machine, then sews (state 0);
 *   4  await:     while the session decides who runs it: once this system owns and holds it,
 *                 it talks (state 1); once this system holds the scene and no one holds it, it
 *                 sews. Run by another system, it runs or stops the machine with its
 *                 animation;
 *   5  other:     another system's player talks to it: once no system owns it and this one
 *                 holds the scene, it is this system's again and sews;
 *   6  paused:    an event starts: the machine stops and the frame of its animation is kept. */
#ifndef CLEAN_OV004_TAILOR_SISTER_H
#define CLEAN_OV004_TAILOR_SISTER_H

#include "main/scene_base.h"
#include "member_pointer.h"
#include "types.h"

enum TailorSisterState {
    TAILOR_SISTER_SEW = 0,
    TAILOR_SISTER_TALK = 1,
    TAILOR_SISTER_TALKED = 2,
    TAILOR_SISTER_TURN_BACK = 3,
    TAILOR_SISTER_AWAIT = 4,
    TAILOR_SISTER_OTHER = 5,
    TAILOR_SISTER_PAUSED = 6,
    TAILOR_SISTER_STATES = 7
};

struct TailorSister;

/* Its talk scene (0xb4 bytes, a scene of main's class 0x020d9ff8, vtable
 * data_ov004_022543cc). */
typedef struct TailorSisterTalk {
    SceneBase base;             /* 0x00 */
    u8 unk_80[0x30];            /* 0x80 */
    struct TailorSister *owner; /* 0xb0 */
} TailorSisterTalk;

/* What its talk scene's line function gives: the message file's name (an address) and the
 * message. */
typedef struct TailorSisterLine {
    u32 text;
    u8 message;
    u8 unk_05[3];
} TailorSisterLine;

/* A state's functions in data_ov004_0225806c. */
typedef struct TailorSisterStep {
    MemberPointer enter;  /* 0x00: int (sister); the state is taken unless it answers 0 */
    MemberPointer update; /* 0x08: int (sister) */
} TailorSisterStep;

/* The size of the special character's scene object it derives from, as far as it is used. */
#define TAILOR_SISTER_BASE_SIZE 0x654

typedef struct TailorSister {
    u8 base[TAILOR_SISTER_BASE_SIZE]; /* 0x000: the special character's scene object */
    s32 state;                        /* 0x654: enum TailorSisterState */
    TailorSisterTalk talk;            /* 0x658 */
    s16 home_yaw;                     /* 0x70c: the angle it faced at its start */
    u8 dated_event_told;              /* 0x70e: the player's dated event of kind 2 told today */
    u8 unk_70f;                       /* 0x70f */
    u16 sew_frame;                    /* 0x710: where its sewing animation stopped */
    u8 machine_turns;                 /* 0x712: the machine's part's whole turns */
    u8 unk_713;                       /* 0x713 */
} TailorSister;

TailorSister *TailorSister_Destroy(TailorSister *sister);
TailorSister *TailorSister_Delete(TailorSister *sister);
void TailorSister_SetTalkDays(TailorSister *sister, int days);
int TailorSister_TalkDays(TailorSister *sister);
void TailorSister_OnEvent(TailorSister *sister, int code, int participant);
int TailorSister_MayAct(TailorSister *sister);
void TailorSisterTalk_OnAnswer(void);
void TailorSisterTalk_OnMessageEnded(void);
void TailorSisterTalk_Line(TailorSisterTalk *talk, TailorSisterLine *out);
void TailorSisterTalk_Begin(TailorSisterTalk *talk, TailorSister *owner);
TailorSisterTalk *TailorSisterTalk_Delete(TailorSisterTalk *talk);
TailorSisterTalk *TailorSisterTalk_Destroy(TailorSisterTalk *talk);
TailorSisterTalk *TailorSisterTalk_Construct(TailorSisterTalk *talk);
void TailorSister_LookAhead(TailorSister *sister);
int TailorSister_UpdatePaused(void);
int TailorSister_EnterPaused(TailorSister *sister);
int TailorSister_UpdateOther(TailorSister *sister);
int TailorSister_EnterOther(TailorSister *sister);
int TailorSister_UpdateAwait(TailorSister *sister);
int TailorSister_EnterAwait(TailorSister *sister);
int TailorSister_UpdateTurnBack(TailorSister *sister);
int TailorSister_EnterTurnBack(TailorSister *sister);
int TailorSister_UpdateTalked(void);
int TailorSister_EnterTalked(void);
int TailorSister_UpdateTalk(TailorSister *sister);
int TailorSister_EnterTalk(TailorSister *sister);
int TailorSister_UpdateSew(TailorSister *sister);
int TailorSister_EnterSew(TailorSister *sister);
void TailorSister_SetState(TailorSister *sister, int state);
int TailorSister_Update(TailorSister *sister);
const char *TailorSister_ModelName(void);
const char *TailorSister_TextureName(void);
int TailorSister_Start(TailorSister *sister);
int TailorSister_Init(TailorSister *sister);
TailorSister *TailorSister_Create(void);

#endif
