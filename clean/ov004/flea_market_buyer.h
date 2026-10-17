/* A villager who comes to the player's house on the day of the flea market to buy an item of
 * the room (class vtable 0x02253e10, 0xaec bytes, made by func_ov004_022217fc; its lines come
 * from the message files "ev_fmarket3", "q10_call", "q10_wait" and "q_bye"): a town villager
 * scene object (main's villager_scene_slots.h).
 *
 * Beyond the base class's members it holds the item it wants (0x898, 0xfff1 for none), the
 * centre of that item's object (0x89c) and the object's number in the room's list of objects
 * (0x8a8, -1 after it is bought), the numbers of the last 100 objects it chose (0x8ac, the
 * newest last, 0xff when cleared), its state and the state before (0x910, 0x914), its talk
 * scene (0x918, a town villager's talk scene with a pointer back to it, the price and a step to
 * run, vtable 0x02253d80), the stage of its visit (0xac8), a countdown of frames to its leaving
 * (0xacc), the date and time of its last talk (0xad0), how close it walks to the item (0xad8),
 * two countdowns (0xadc, 0xadd), whether its action sound was played (0xade), how many items it
 * bought (0xae0), the count of the room's objects (0xae4) and its frames of looking about
 * (0xae8).
 *
 * The stages of its visit (0xac8), as the code here reads them:
 *   0  it has just come in and calls the player ("q10_call");
 *   1  it was greeted; its talk ends with it stepping in;
 *   2  it looks about the room for an item to buy, and offers for it ("ev_fmarket3");
 *   3  its time is up (the countdown at 0xacc, an hour since its last talk or 600 frames of
 *      looking about): it says goodbye ("ev_fmarket3", then "q_bye", stage 4) and leaves;
 *   5  the player stands at the room's way out: "q10_wait", then "q_bye" (stage 6) and it
 *      leaves with them.
 *
 * Its states (0x910), each an entry and an update function (C++ members taking the villager),
 * from the tables data_ov004_02257e90 (states 0 to 7, filled at start-up by
 * __sinit_ov004_0224e484) and data_ov004_02257f10 (state 8), set by func_ov004_02221550:
 *   2  step in:  facing into the room it walks 0x4000 ahead, waits, stands and its event ends;
 *   3  browse:   in stage 2 it picks an item (FleaMarketBuyer_PickItem) and walks to it
 *                (state 5) or turns to it (state 4);
 *   4  face:     it turns to the item: state 3;
 *   5  go:       it walks (runs when far) to the item: state 3; on its way an object it may buy
 *                on the tile ahead of it becomes the item;
 *   6  talk:     it turns to the talk's partner and talks; then the event ends: state 8;
 *   7  bye:      it turns to the partner and talks; then it takes the room's way out: state 8;
 *   8  done:     nothing.
 * States 3 to 5 first ask whether it should leave (FleaMarketBuyer_CheckLeave). */
#ifndef CLEAN_OV004_FLEA_MARKET_BUYER_H
#define CLEAN_OV004_FLEA_MARKET_BUYER_H

#include "autoload_2/vector.h"
#include "main/calendar.h"
#include "main/villager_talk.h"
#include "member_pointer.h"
#include "room_object.h"
#include "types.h"

struct FleaMarketBuyer;

/* Its talk scene (0x1b0 bytes, vtable data_ov004_02253d80). */
typedef struct FleaMarketBuyerTalk {
    VillagerTalk base;             /* 0x000 */
    struct FleaMarketBuyer *buyer; /* 0x1a4: the villager it belongs to */
    s32 price;                     /* 0x1a8: in bells */
    s32 step;                      /* 0x1ac: the entry of data_ov004_02257dd8 to run, 0 for none */
} FleaMarketBuyerTalk;

/* An entry of its talk's steps (data_ov004_02257dd8: 0 none, 1 FleaMarketBuyerTalk_Offer). */
typedef struct FleaMarketBuyerTalkStep {
    MemberPointer member; /* 0x00: (talk) */
    u8 before_each;       /* 0x08: run before each step of the talk, else once at its command's end */
    u8 unk_09[3];         /* 0x09 */
} FleaMarketBuyerTalkStep;

/* The number of its last chosen objects it keeps. */
#define FLEA_MARKET_BUYER_RECENT 100

/* The size of the town villager scene object it derives from, as far as it is used. */
#define FLEA_MARKET_BUYER_BASE_SIZE 0x898

typedef struct FleaMarketBuyer {
    u8 base[FLEA_MARKET_BUYER_BASE_SIZE]; /* 0x000: the town villager scene object */
    u16 item;                             /* 0x898: the item it wants, 0xfff1 for none */
    u8 unk_89a[2];                        /* 0x89a */
    Vec3 target;                          /* 0x89c: the centre of the item's object */
    s32 object;                           /* 0x8a8: the object's number, -1 for none */
    u8 recent[FLEA_MARKET_BUYER_RECENT];  /* 0x8ac: the numbers of the objects it chose */
    s32 state;                            /* 0x910 */
    s32 previous_state;                   /* 0x914 */
    FleaMarketBuyerTalk talk;             /* 0x918 */
    u8 stage;                             /* 0xac8 */
    u8 unk_ac9[3];                        /* 0xac9 */
    s32 leave_wait;                       /* 0xacc: frames until it leaves, 0 for no limit */
    DateTime talk_time;                   /* 0xad0: when it last talked */
    fx32 reach;                           /* 0xad8: how close it walks to the item */
    u8 step_wait;                         /* 0xadc: state 2's frames */
    u8 talk_wait;                         /* 0xadd: frames before state 6 turns to talk */
    u8 sound_played;                      /* 0xade */
    u8 unk_adf;                           /* 0xadf */
    u8 bought;                            /* 0xae0: the items it bought */
    u8 unk_ae1[3];                        /* 0xae1 */
    s32 object_count;                     /* 0xae4: the room's objects when it came */
    s32 browse_frames;                    /* 0xae8: counted while nonzero */
} FleaMarketBuyer;

FleaMarketBuyer *FleaMarketBuyer_Destroy(FleaMarketBuyer *buyer);
FleaMarketBuyer *FleaMarketBuyer_Delete(FleaMarketBuyer *buyer);
void FleaMarketBuyer_SetReach(FleaMarketBuyer *buyer, RoomObject *object);
void FleaMarketBuyer_Remember(FleaMarketBuyer *buyer, u8 number);
int FleaMarketBuyer_MayBuy(FleaMarketBuyer *buyer, int number);
int FleaMarketBuyer_PickItem(FleaMarketBuyer *buyer);
int FleaMarketBuyer_CheckLeave(FleaMarketBuyer *buyer);
void FleaMarketBuyer_OnEvent(FleaMarketBuyer *buyer, int code);
int FleaMarketBuyer_IsIdle(FleaMarketBuyer *buyer);
int FleaMarketBuyer_MayAct(FleaMarketBuyer *buyer);
void FleaMarketBuyerTalk_OnAnswer(FleaMarketBuyerTalk *talk);
int FleaMarketBuyerTalk_DropItem(FleaMarketBuyerTalk *talk);
void FleaMarketBuyerTalk_OnMessageEnded(FleaMarketBuyerTalk *talk);
FleaMarketBuyer *FleaMarketBuyer_ActionSoundPlayed(FleaMarketBuyer *buyer);
int FleaMarketBuyer_HasActionSound(FleaMarketBuyer *buyer);
void FleaMarketBuyerTalk_Line(FleaMarketBuyerTalk *talk, VillagerTalkLine *out);
void FleaMarketBuyerTalk_Buy(FleaMarketBuyerTalk *talk);
void FleaMarketBuyerTalk_Offer(FleaMarketBuyerTalk *talk);
void FleaMarketBuyerTalk_SetStep(FleaMarketBuyerTalk *talk, int step);
void FleaMarketBuyerTalk_OnCommandEnd(FleaMarketBuyerTalk *talk);
void FleaMarketBuyerTalk_BeforeStep(FleaMarketBuyerTalk *talk);
void FleaMarketBuyerTalk_Start(FleaMarketBuyerTalk *talk, FleaMarketBuyer *buyer);
FleaMarketBuyerTalk *FleaMarketBuyerTalk_Delete(FleaMarketBuyerTalk *talk);
FleaMarketBuyerTalk *FleaMarketBuyerTalk_Destroy(FleaMarketBuyerTalk *talk);
FleaMarketBuyerTalk *FleaMarketBuyerTalk_Construct(FleaMarketBuyerTalk *talk);
int FleaMarketBuyer_UpdateDone(void);
int FleaMarketBuyer_EnterDone(void);
int FleaMarketBuyer_UpdateTalk(FleaMarketBuyer *buyer);
int FleaMarketBuyer_EnterTalk(FleaMarketBuyer *buyer);
int FleaMarketBuyer_UpdateBye(FleaMarketBuyer *buyer);
int FleaMarketBuyer_EnterBye(FleaMarketBuyer *buyer);
int FleaMarketBuyer_UpdateGo(FleaMarketBuyer *buyer);
int FleaMarketBuyer_EnterGo(FleaMarketBuyer *buyer);
int FleaMarketBuyer_UpdateFace(FleaMarketBuyer *buyer);
int FleaMarketBuyer_EnterFace(FleaMarketBuyer *buyer);
int FleaMarketBuyer_UpdateBrowse(FleaMarketBuyer *buyer);
int FleaMarketBuyer_EnterBrowse(FleaMarketBuyer *buyer);
int FleaMarketBuyer_UpdateStepIn(FleaMarketBuyer *buyer);
int FleaMarketBuyer_EnterStepIn(FleaMarketBuyer *buyer);

/* Its states' functions (data_ov004_02257e90, states 0 to 7, then data_ov004_02257f10, state
 * 8), each called with the villager and answering an int:
 *   0  call:  it stands at the room's way in (stage 0); now and then, with the player away from
 *             it, it knocks (sound 0x4ca) and asks for its event for 30 frames;
 *   1  greet: it stands; once the talk is closed it faces into the room, plays its greeting's
 *             sounds 40 frames before the end of its wait and is put in place at 8; then 2. */
typedef struct FleaMarketBuyerStep {
    MemberPointer enter;  /* 0x00: run when the state is entered; it is taken unless it answers 0 */
    MemberPointer update; /* 0x08: run each frame */
} FleaMarketBuyerStep;

/* Its states: 0 to 8. */
#define FLEA_MARKET_BUYER_STATES 9

int FleaMarketBuyer_UpdateGreet(FleaMarketBuyer *buyer);
int FleaMarketBuyer_EnterGreet(FleaMarketBuyer *buyer);
int FleaMarketBuyer_UpdateCall(FleaMarketBuyer *buyer);
int FleaMarketBuyer_EnterCall(FleaMarketBuyer *buyer);
void FleaMarketBuyer_PlayGreeting(FleaMarketBuyer *buyer);
void FleaMarketBuyer_SetState(FleaMarketBuyer *buyer, int state);
int FleaMarketBuyer_RunState(FleaMarketBuyer *buyer);
int FleaMarketBuyer_Draw(FleaMarketBuyer *buyer);
int FleaMarketBuyer_Leave(FleaMarketBuyer *buyer);
int FleaMarketBuyer_Start(FleaMarketBuyer *buyer);
int FleaMarketBuyer_Init(FleaMarketBuyer *buyer);
FleaMarketBuyer *FleaMarketBuyer_New(void);

#endif
