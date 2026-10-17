/* Overlay 45: the fortune teller, the special character of the message file "sp_npc_panther"
 * with the model npc_sp/model/bpt (person code 0xd00a, special character 10; overlay 3's
 * panther.h is the same character outdoors). Scene 0x10, her tent, names overlay 45 in its
 * SceneInfo (data_020e55bc, scene_process.h), and its setup (overlay 17) makes her (object
 * profile 0x70: her record at 0x022613f4, which main's profile table data_020e3134 points to)
 * and the tarot cards she reads from (profile 0x71, ov004's tarot_object.h).
 *
 * She is a scene object of class 0x020da088 (main's special_scene_object.h) with vtable
 * 0x022614f0, 0x75c bytes, made by FortuneTeller_Create. data_ov045_022615a0 points to her
 * from her start to her leaving; the tarot object asks it for her animation's frame and the
 * matrix of her joint 14 (FortuneTeller_CurrentFrame, FortuneTeller_CurrentMatrix).
 *
 * Her states (FortuneTeller.state), each an entry and an update function (C++ members taking
 * her) from the table data_ov045_022615bc (filled at start-up by __sinit_ov045_022612d8), set
 * by FortuneTeller_SetState:
 *   0  sit:     she takes motion 0 (priority 1); before 6 a.m. she asks for an event of kind 6;
 *   1  talk:    she turns to the talk's partner and talks; once her action is idle the event
 *               ends: state 2;
 *   2  talked:  nothing;
 *   3  closing: once her action is idle, main's entry record takes exit 0 (the player is put
 *               out of the tent).
 *
 * Her talk scene (FortuneTellerTalk, fortune_teller_talk.h) sells the readings: for 100 bells
 * a reading of the day's luck or of a villager's friendship, each once a day, drawn from 22
 * tarot cards upright or reversed; and for 10,000 bells she clears the day's luck. */
#ifndef CLEAN_OV045_FORTUNE_TELLER_H
#define CLEAN_OV045_FORTUNE_TELLER_H

#include "autoload_2/matrix.h"
#include "main/scene_base.h"
#include "ov004/member_pointer.h"
#include "types.h"

struct FortuneTeller;

/* Her talk scene (0xb8 bytes, a scene base of main's scene_base.h, vtable 0x02261460). Its
 * receiver's message (byte 0x1e of the scene) is the line shown. */
typedef struct FortuneTellerTalk {
    SceneBase base;              /* 0x00 */
    u8 unk_80[0x30];             /* 0x80 */
    u32 sequence;                /* 0xb0: FORTUNE_TELLER_TALK_SEQUENCE_* */
    struct FortuneTeller *owner; /* 0xb4 */
} FortuneTellerTalk;

/* The size of the special character's scene object she derives from, as far as it is used. */
#define FORTUNE_TELLER_BASE_SIZE 0x654

/* FortuneTeller.reading: what the reading of the day is about. */
#define FORTUNE_TELLER_READING_LUCK 0       /* the player's luck of the day */
#define FORTUNE_TELLER_READING_FRIENDSHIP 1 /* a villager's friendship, named by the player */

/* No message (card_message, result_message). */
#define FORTUNE_TELLER_NO_MESSAGE 0xff

typedef struct FortuneTeller {
    u8 base[FORTUNE_TELLER_BASE_SIZE]; /* 0x000: the special character's scene object */
    s32 effect;                        /* 0x654: the handle of her effect 0x3d, or -1 */
    s32 state;                         /* 0x658: FORTUNE_TELLER_* */
    Mtx43 joint14;                     /* 0x65c: her model's joint 14, at each draw */
    FortuneTellerTalk talk;            /* 0x68c */
    u8 card_message;                   /* 0x744: the line that shows the card drawn */
    u8 result_message;                 /* 0x745: the line that tells what it means */
    u8 unk_746[2];                     /* 0x746 */
    s32 reading;                       /* 0x748: FORTUNE_TELLER_READING_* */
    u8 card;                           /* 0x74c: the card drawn, 0 to 21 */
    u8 unk_74d[3];                     /* 0x74d */
    u32 reversed;                      /* 0x750: 1 when the card was drawn reversed */
    u32 villager_name;                 /* 0x754: the address of the name the player typed */
    u8 effect_frames;                  /* 0x758: the frames her effect has left */
    u8 unk_759[3];                     /* 0x759 */
} FortuneTeller;

enum FortuneTellerState {
    FORTUNE_TELLER_SIT = 0,
    FORTUNE_TELLER_TALKING = 1,
    FORTUNE_TELLER_TALKED = 2,
    FORTUNE_TELLER_CLOSING = 3,
    FORTUNE_TELLER_STATES = 4
};

/* A state's functions in data_ov045_022615bc. */
typedef struct FortuneTellerStep {
    MemberPointer enter;  /* 0x00: int (teller); the state is taken unless it answers 0 */
    MemberPointer update; /* 0x08: int (teller) */
} FortuneTellerStep;

/* A card that tells good or bad luck: the card and whether it is reversed. */
typedef struct FortuneTellerCard {
    u8 card;
    u8 unk_01[3];
    u32 reversed;
} FortuneTellerCard;

/* What a card drawn tells (FortuneTeller_CardLuck); the luck of the day it sets
 * (PlayerRecord_SetDayState). */
#define FORTUNE_TELLER_LUCK_NONE 0
#define FORTUNE_TELLER_LUCK_GOOD 1
#define FORTUNE_TELLER_LUCK_BAD 2

FortuneTeller *FortuneTeller_Destroy(FortuneTeller *teller);
void *FortuneTeller_Delete(void *teller);
int FortuneTeller_CardLuck(FortuneTeller *teller);
void FortuneTeller_DrawCard(FortuneTeller *teller);
unsigned int FortuneTeller_CurrentFrame(void);
int FortuneTeller_CurrentMatrix(void);
int FortuneTeller_BeforeSix(void);
void FortuneTeller_OnEvent(FortuneTeller *teller, int code);
int FortuneTeller_MayAct(FortuneTeller *teller);
int FortuneTeller_UpdateTalked(void);
int FortuneTeller_EnterTalked(void);
int FortuneTeller_UpdateClosing(FortuneTeller *teller);
int FortuneTeller_EnterClosing(void);
int FortuneTeller_UpdateTalk(FortuneTeller *teller);
int FortuneTeller_EnterTalk(FortuneTeller *teller);
int FortuneTeller_UpdateSit(int teller);
int FortuneTeller_EnterSit(FortuneTeller *teller);
void FortuneTeller_SetState(FortuneTeller *teller, int state);
int FortuneTeller_Update(FortuneTeller *teller);
int FortuneTeller_ModelName(void);
int FortuneTeller_TextureName(void);
int FortuneTeller_Draw(FortuneTeller *teller);
int FortuneTeller_Leave(FortuneTeller *teller);
int FortuneTeller_Start(FortuneTeller *teller);
int FortuneTeller_Init(FortuneTeller *teller);
void *FortuneTeller_Create(void);

#endif
