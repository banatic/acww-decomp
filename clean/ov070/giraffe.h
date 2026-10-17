/* Overlay 70: the giraffe, the special character of the message file "sp_npc_giraffe" with the
 * model npc_sp/model/grf (person code 0xd00b). Main's spawner (spawner.h) makes her in the
 * town while event 0x40 is on: its spawn table (data_020e1d8c) gives her object profile 0x6c
 * the code 0xd00b and overlay 70, loaded with her; the profile's record is at 0x02279d80, which
 * main's profile table data_020e3134 points to.
 *
 * She is a scene object of class 0x020da088 (main's special_scene_object.h) with vtable
 * 0x02279e4c, 0x73c bytes, made by Giraffe_Create, with her talk scene (GiraffeTalk,
 * giraffe_talk.h) at 0x658. In her talks she scores what the player wears (the player record's
 * count 0x0e, PlayerField2416), gives lines of advice, and for the bells the player chooses to
 * pay dresses the player: a hat or an accessory, and clothes, from a tier of what was paid;
 * what the player wore goes back into the pockets.
 *
 * Her states (Giraffe.state), each an entry and an update function (C++ members taking her)
 * from the table data_ov070_02279f24 (filled at start-up by __sinit_ov070_02279c50), set by
 * Giraffe_SetState:
 *   0  stand:  she takes motion 0 (priority 1);
 *   1  talk:   she turns to the talk's partner and talks; once her action is idle the event
 *              ends: state 2;
 *   2  talked: nothing. */
#ifndef CLEAN_OV070_GIRAFFE_H
#define CLEAN_OV070_GIRAFFE_H

#include "main/scene_base.h"
#include "ov004/member_pointer.h"
#include "types.h"

struct Giraffe;

/* The lines of advice her talk picks from (Giraffe.advice_said). */
#define GIRAFFE_ADVICE_LINES 20

/* The items the player wore when last scored (GiraffeTalk.worn). */
enum GiraffeWorn { GIRAFFE_WORN_HEAD = 0, GIRAFFE_WORN_ACCESSORY = 1, GIRAFFE_WORN_CLOTHES = 2, GIRAFFE_WORN_COUNT = 3 };

/* Her talk scene (0xcc bytes, a scene of main's class 0x020d9ff8, vtable 0x02279dbc). Its
 * receiver's message (byte 0x1e of the scene) is the line shown. */
typedef struct GiraffeTalk {
    SceneBase base;               /* 0x00 */
    u8 unk_80[0x30];              /* 0x80 */
    s32 first;                    /* 0xb0: GIRAFFE_TALK_FIRST_*, what the talk started with */
    struct Giraffe *owner;        /* 0xb4 */
    MemberPointer sequence;       /* 0xb8: void (talk), run when a command of the scene ends */
    s32 paid;                     /* 0xc0: the bells the player chose to pay */
    u16 worn[GIRAFFE_WORN_COUNT]; /* 0xc4: GiraffeWorn; ItemCode objects (0xfff1 when made) */
    u8 unk_ca[2];                 /* 0xca */
} GiraffeTalk;

/* The size of the special character's scene object she derives from, as far as it is used. */
#define GIRAFFE_BASE_SIZE 0x654

typedef struct Giraffe {
    u8 base[GIRAFFE_BASE_SIZE];           /* 0x000: the special character's scene object */
    s32 state;                            /* 0x654: GIRAFFE_* */
    GiraffeTalk talk;                     /* 0x658 */
    u8 advice_said[GIRAFFE_ADVICE_LINES]; /* 0x724: 1 for each line of advice said */
    u8 advice_count;                      /* 0x738: lines of advice said in a row */
    u8 unk_739[3];                        /* 0x739 */
} Giraffe;

enum GiraffeState { GIRAFFE_STAND = 0, GIRAFFE_TALKING = 1, GIRAFFE_TALKED = 2, GIRAFFE_STATES = 3 };

/* A state's functions in data_ov070_02279f24. */
typedef struct GiraffeStep {
    MemberPointer enter;  /* 0x00: int (giraffe); the state is taken when it answers 1 */
    MemberPointer update; /* 0x08: int (giraffe) */
} GiraffeStep;

Giraffe *Giraffe_Destroy(Giraffe *giraffe);
void *Giraffe_Delete(void *giraffe);
void Giraffe_OnEvent(Giraffe *giraffe, int code);
int Giraffe_MayAct(Giraffe *giraffe);
int Giraffe_EnterTalk(Giraffe *giraffe);
int Giraffe_UpdateStand(void);
int Giraffe_EnterStand(Giraffe *giraffe);
int Giraffe_UpdateTalked(void);
int Giraffe_UpdateTalk(Giraffe *giraffe);
void Giraffe_SetState(Giraffe *giraffe, int state);
int Giraffe_Update(Giraffe *giraffe);
int Giraffe_ModelName(void);
int Giraffe_TextureName(void);
int Giraffe_Start(Giraffe *giraffe);
int Giraffe_Init(Giraffe *giraffe);
void *Giraffe_Create(void);

#endif
