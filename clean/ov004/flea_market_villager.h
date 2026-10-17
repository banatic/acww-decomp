/* The villager of a house at the flea market (class vtable 0x02253bb4, 0xa60 bytes, made by
 * func_ov004_0221ff70, the overlay's profile of kinds 0x86 and 0x8a; its lines come from the
 * message files "ev_fmarket2" and "q11_*"): a town villager scene object (main's
 * villager_scene_slots.h) that sells the furniture of its house to the player.
 *
 * Beyond the base class's members it holds the item the player asks about (0x898, 0xfff1 for
 * none) and its tile in the room (0x89c, -1 when it may not be sold), its talk scene (0x8a8,
 * a town villager's talk scene with a pointer back to it and the price asked, vtable
 * 0x02253b24), the stage of the trade (0xa54), whether its action sound was played (0xa56) and
 * the list of spots of its house's items (0xa58, with its count at 0xa5c,
 * main's villager_furniture.h).
 *
 * Its state (0x8a4) picks an entry and an update function (C++ members taking the villager) from
 * the table data_ov004_02257d58, filled at start-up (__sinit_ov004_0224e39c):
 *   0  call:   it stands, and asks for an event of kind 6 about it each frame;
 *   1  talk:   it turns to the talk's partner and talks; once its action is idle the trade's
 *              stage 0 becomes 1, the item asked about none, its event ends: state 2;
 *   2  wait:   nothing;
 *   3  bye:    it turns to the partner and talks (the camera kept); once idle the room's exit
 *              0 is taken: state 2;
 *   4  watch:  it stands looking at the player: far from them on a path it may take, state 6;
 *              turned away from them by more than an eighth of a turn, state 5; then it asks
 *              for the event of the player at the room's start point or of an item asked about;
 *   5  turn:   it turns to the player; far again, state 6; the turn done, state 4;
 *   6  follow: it walks (runs when far) to the player, asking first for the events of state 4;
 *              close or blocked, state 4;
 *   7  come:   it walks (runs when far) to the player for at most 50 frames, then readies its
 *              talk: state 1.
 *
 * The stages, as the code here reads them: 1 the villager asks whether the player wants to
 * buy ("q11_trade1"); 2 the player looks about the room and may ask about the item ahead of
 * them; 3 the player stands at the room's start point. The states of its machine are set by
 * func_ov004_0221fdf4. */
#ifndef CLEAN_OV004_FLEA_MARKET_VILLAGER_H
#define CLEAN_OV004_FLEA_MARKET_VILLAGER_H

#include "main/villager_furniture.h"
#include "main/villager_talk.h"
#include "types.h"

#include "member_pointer.h"

struct FleaMarketVillager;

/* A state's functions in data_ov004_02257d58. */
typedef struct FleaMarketVillagerStep {
    MemberPointer enter;  /* 0x00: int (villager) */
    MemberPointer update; /* 0x08: int (villager) */
} FleaMarketVillagerStep;

#define FLEA_MARKET_VILLAGER_STATES 8

/* Its talk scene (0x1ac bytes, vtable data_ov004_02253b24). */
typedef struct FleaMarketTalk {
    VillagerTalk base;                   /* 0x000 */
    struct FleaMarketVillager *villager; /* 0x1a4: the villager it belongs to */
    s32 price;                           /* 0x1a8: the price asked for the item, in bells */
} FleaMarketTalk;

/* The size of the town villager scene object it derives from, as far as it is used. */
#define FLEA_MARKET_VILLAGER_BASE_SIZE 0x898

typedef struct FleaMarketVillager {
    u8 base[FLEA_MARKET_VILLAGER_BASE_SIZE]; /* 0x000: the town villager scene object */
    u16 item;                                /* 0x898: the item asked about, 0xfff1 for none */
    u8 unk_89a[2];                           /* 0x89a */
    VillagerFurnitureTile tile;              /* 0x89c: its tile, (-1, -1) when not for sale */
    s32 state;                               /* 0x8a4: its state, FleaMarketVillager_SetState */
    FleaMarketTalk talk;                     /* 0x8a8 */
    u8 stage;                                /* 0xa54 */
    u8 walk_wait;                            /* 0xa55: frames left of state 7's walk */
    u8 sound_played;                         /* 0xa56 */
    u8 unk_a57;                              /* 0xa57 */
    const VillagerFurnitureSpot *spots;      /* 0xa58: the spots of its house's items */
    s32 spot_count;                          /* 0xa5c */
} FleaMarketVillager;

FleaMarketVillager *FleaMarketVillager_Destroy(FleaMarketVillager *villager);
FleaMarketVillager *FleaMarketVillager_Delete(FleaMarketVillager *villager);
int FleaMarketVillager_RequestIfStartClaimed(FleaMarketVillager *villager);
int FleaMarketVillager_RequestItemTalk(FleaMarketVillager *villager);
int FleaMarketVillager_PickItemAhead(FleaMarketVillager *villager);
void FleaMarketVillager_OnEvent(FleaMarketVillager *villager, int code);
int FleaMarketVillager_IsIdle(FleaMarketVillager *villager);
int FleaMarketVillager_MayAct(FleaMarketVillager *villager);
void FleaMarketTalk_OnAnswer(FleaMarketTalk *talk);
void FleaMarketTalk_OnMessageEnded(void);
FleaMarketVillager *FleaMarketVillager_ActionSoundPlayed(FleaMarketVillager *villager);
int FleaMarketVillager_HasActionSound(FleaMarketVillager *villager);
void FleaMarketTalk_Line(FleaMarketTalk *talk, VillagerTalkLine *out);
void FleaMarketTalk_Sell(FleaMarketTalk *talk);
void FleaMarketTalk_Start(FleaMarketTalk *talk, FleaMarketVillager *villager);
FleaMarketTalk *FleaMarketTalk_Delete(FleaMarketTalk *talk);
FleaMarketTalk *FleaMarketTalk_Destroy(FleaMarketTalk *talk);
FleaMarketTalk *FleaMarketTalk_Construct(FleaMarketTalk *talk);
int FleaMarketVillager_UpdateCome(FleaMarketVillager *villager);
int FleaMarketVillager_EnterCome(FleaMarketVillager *villager);
int FleaMarketVillager_UpdateWait(void);
int FleaMarketVillager_UpdateTalk(FleaMarketVillager *villager);
int FleaMarketVillager_EnterTalk(FleaMarketVillager *villager);
int FleaMarketVillager_UpdateBye(FleaMarketVillager *villager);
int FleaMarketVillager_EnterBye(FleaMarketVillager *villager);
int FleaMarketVillager_UpdateFollow(FleaMarketVillager *villager);
int FleaMarketVillager_EnterFollow(FleaMarketVillager *villager);
int FleaMarketVillager_UpdateTurn(FleaMarketVillager *villager);
int FleaMarketVillager_EnterTurn(FleaMarketVillager *villager);
int FleaMarketVillager_UpdateWatch(FleaMarketVillager *villager);
int FleaMarketVillager_EnterWatch(FleaMarketVillager *villager);
int FleaMarketVillager_UpdateCall(FleaMarketVillager *villager);
int FleaMarketVillager_EnterCall(FleaMarketVillager *villager);
void FleaMarketVillager_SetState(FleaMarketVillager *villager, int state);
int FleaMarketVillager_RunState(FleaMarketVillager *villager);
int FleaMarketVillager_Leave(FleaMarketVillager *villager);
int FleaMarketVillager_Start(FleaMarketVillager *villager);
int FleaMarketVillager_Init(FleaMarketVillager *villager);
FleaMarketVillager *FleaMarketVillager_New(void);

#endif
