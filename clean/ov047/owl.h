/* Overlay 47: the museum's owl, loaded with scene 0x20 (the museum; scene 0x20's SceneInfo in
 * overlay 21 names overlay 47). The special character of the message archive "sp_npc_owl" with
 * the model npc_sp/model/owl, object profile 0x6e (its record at data_ov047_02262bd8, the main
 * module's profile table data_020e3134 points to it). A scene object of class 0x020da088
 * (special_scene_object.h) with vtable data_ov047_02262ca4, 0x740 bytes, made by Owl_Create.
 *
 * Its talk scene (OwlTalk, owl_talk.h, vtable data_ov047_02262c14, at 0x658) takes the gifts to
 * the museum's record (main's museum_record.h, data_021f38f8), assesses the fossils the player
 * digs up, tells how far the museum is, and tells the dated events of kind 1 (day_events.h)
 * from "sp_npc_drama1".
 *
 * Its own states (Owl.state, OWL_STATE_*) are a table of C++ pointers to member functions
 * (data_ov047_02263048, an entry and an update for each, filled at start-up by
 * __sinit_ov047_02262838), set by Owl_SetState and run each frame by Owl_Update:
 *   0  stand:      it stands and looks at the player; with a dated event of kind 1 today it
 *                  acts (state 5) after a few seconds; else, unlinked in the morning or the
 *                  afternoon, it falls asleep (state 2) after 120 frames;
 *   1  turn back:  it turns to the angle it started with, then stands;
 *   2  asleep:     it plays its animation 0xf0 with the effect of kind 0x3c at its head;
 *   3  talk:       it turns to the one it talks with and talks; then the event ends: state 4;
 *   4  talked:     nothing;
 *   5  act:        it plays its motion of kind 10, then stands;
 *   6  await:      while the session decides who runs it (as the cafe's master's state 5);
 *   7  other:      another system's player talks to it;
 *   8  paused:     an event starts: nothing. */
#ifndef CLEAN_OV047_OWL_H
#define CLEAN_OV047_OWL_H

#include "main/scene_base.h"
#include "ov004/member_pointer.h"
#include "types.h"

enum OwlState {
    OWL_STATE_STAND = 0,
    OWL_STATE_TURN_BACK = 1,
    OWL_STATE_ASLEEP = 2,
    OWL_STATE_TALK = 3,
    OWL_STATE_TALKED = 4,
    OWL_STATE_ACT = 5,
    OWL_STATE_AWAIT = 6,
    OWL_STATE_OTHER = 7,
    OWL_STATE_PAUSED = 8,
    OWL_STATES = 9
};

/* A state's functions in data_ov047_02263048. */
typedef struct OwlStep {
    MemberPointer enter;  /* 0x00: int (owl); the state is taken unless it answers 0 */
    MemberPointer update; /* 0x08: int (owl) */
} OwlStep;

struct Owl;

/* Its talk scene (0xd4 bytes): a scene of class 0x020d9ff8 (main's obj_020d9ff8.h). */
typedef struct OwlTalk {
    SceneBase base;      /* 0x00: the receiver's message (byte 0x1e) is the line shown */
    u8 unk_80[0x30];     /* 0x80: the scene's commands (scene_command.h) */
    s32 drama;           /* 0xb0: 1 while a dated event's line of "sp_npc_drama1" is shown */
    struct Owl *owner;   /* 0xb4 */
    MemberPointer after; /* 0xb8: run once the command of the scene ends (OwlTalk_RunAfter) */
    MemberPointer next;  /* 0xc0: the one after it */
    s32 slot;            /* 0xc8: the pocket the item handed over came from, -1 for none */
    u8 assessing;        /* 0xcc: the player asked for a fossil to be assessed */
    u8 unk_cd;           /* 0xcd */
    u16 item;            /* 0xce: the item handed over, 0xfff1 for none */
    s32 next_line;       /* 0xd0: the line the talk goes on with, 0xff for none */
} OwlTalk;

/* The size of the special character's scene object it derives from, as far as it is used. */
#define OWL_BASE_SIZE 0x654

typedef struct Owl {
    u8 base[OWL_BASE_SIZE]; /* 0x000: the special character's scene object */
    s32 state;              /* 0x654: enum OwlState */
    OwlTalk talk;           /* 0x658 */
    u8 drama_told;          /* 0x72c: a dated event of kind 1 was told since it started */
    u8 unk_72d;             /* 0x72d */
    u16 act_countdown;      /* 0x72e: the frames before it acts (state 5), 0xff for none */
    u16 stand_word;         /* 0x730: the word of its next stand (scene_motion_request.h) */
    u16 nap_countdown;      /* 0x732: the frames before it falls asleep */
    s16 home_angle;         /* 0x734: the angle it faced when it started */
    u8 asleep;              /* 0x736: it was asleep when the player talked to it */
    u8 unk_737;             /* 0x737 */
    u16 nap_word;           /* 0x738: the word of its animation asleep */
    u8 unk_73a[2];          /* 0x73a */
    s32 effect;             /* 0x73c: the handle of its effect asleep, -1 for none */
} Owl;

/* Its vtable slots and questions (owl.c). */
Owl *Owl_Destruct(Owl *owl);
void *Owl_DestructDelete(Owl *owl);
void Owl_OnEvent(Owl *owl, int code, int participant);
int Owl_MayAct(Owl *owl);
int Owl_Start(Owl *owl);
int Owl_Init(Owl *owl);
int Owl_Leave(Owl *owl);
int Owl_ModelName(void);
int Owl_TextureName(void);
void *Owl_Create(void);
void Owl_SetState(Owl *owl, int state);
int Owl_Update(Owl *owl);

/* Its states (owl.c). */
int Owl_EnterStand(Owl *owl);
int Owl_UpdateStand(Owl *owl);
int Owl_EnterTurnBack(Owl *owl);
int Owl_UpdateTurnBack(Owl *owl);
int Owl_EnterAsleep(Owl *owl);
int Owl_UpdateAsleep(Owl *owl);
int Owl_EnterTalk(Owl *owl);
int Owl_UpdateTalk(Owl *owl);
int Owl_UpdateTalked(void);
int Owl_EnterAct(Owl *owl);
int Owl_UpdateAct(Owl *owl);
int Owl_EnterAwait(Owl *owl);
int Owl_UpdateAwait(Owl *owl);
int Owl_EnterOther(Owl *owl);
int Owl_UpdateOther(Owl *owl);
int Owl_UpdatePaused(void);
int Owl_EnterPaused(void);

#endif
