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
 * The stages, as the code here reads them: 1 the villager asks whether the player wants to
 * buy ("q11_trade1"); 2 the player looks about the room and may ask about the item ahead of
 * them; 3 the player stands at the room's start point. The states of its machine are set by
 * func_ov004_0221fdf4. */
#ifndef CLEAN_OV004_FLEA_MARKET_VILLAGER_H
#define CLEAN_OV004_FLEA_MARKET_VILLAGER_H

#include "main/villager_furniture.h"
#include "main/villager_talk.h"
#include "types.h"

struct FleaMarketVillager;

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
    u8 unk_8a4[4];                           /* 0x8a4 */
    FleaMarketTalk talk;                     /* 0x8a8 */
    u8 stage;                                /* 0xa54 */
    u8 unk_a55;                              /* 0xa55 */
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

#endif
