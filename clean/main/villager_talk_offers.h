/* The choices a town villager's talk (villager_talk.h) offers when the player starts it
 * (VillagerTalkOffer_Start): five member functions are tried in turn, each given the
 * villager's town record and the current player's villager part (villager_part.h), and the
 * first that offers choices ends the search; when none does, the plain two choices are offered
 * (data_020c8928 running data_021c1e14, data_020c8924 running data_021c1d6c). The five look at:
 *
 * - block 0 of the part naming the villager in its first-pick types (VillagerTalkOffer_FirstPick);
 * - the villager's plan to move away, finished in the last days (VillagerTalkOffer_AfterMove);
 * - a block of the part whose first villager is this one (VillagerTalkOffer_PartBlock);
 * - the object something holds for the villager (VillagerKind_Known, VillagerTalkOffer_ByKnown);
 * - the object of the villager's entry in the running state table (VillagerTalkOffer_ByState).
 *
 * Each offer ends with the reply func_020288bc (VillagerTalkOffer_Reply), which sets the talk's
 * line functions from the table the chosen choice runs and says the line.
 *
 * The villager object's errands of group 0 (types 0-4, villager_object.h) ask for an insect
 * (0x12b0-0x12e7), a fish (0x12e8-0x131f), an item of a kind (0x450c-0x45db, type 2), clothes
 * (0x11a8-0x12a7, type 3) or an item with a variant (type 4); the predicates here test pockets
 * for them (CurrentPockets_Mark and the pockets screen take them as the game's functions). */
#ifndef CLEAN_MAIN_VILLAGER_TALK_OFFERS_H
#define CLEAN_MAIN_VILLAGER_TALK_OFFERS_H

#include "calendar.h"
#include "types.h"
#include "villager_object.h"
#include "villager_part.h"
#include "villager_talk.h"

void VillagerTalkOffer_Reply(VillagerTalk *talk, int unused, int choice);
void VillagerTalkOffer_Start(VillagerTalk *talk);
int VillagerTalkOffer_AfterMove(VillagerTalk *talk, u8 *record);
int VillagerTalkOffer_ByState(VillagerTalk *talk, u8 *record, VillagerPart *part);
int VillagerTalkOffer_StateHandover(VillagerTalk *talk, u8 *record, VillagerPart *part);
int VillagerTalkOffer_StateGroup0(VillagerTalk *talk, u8 *record, int unused);
int VillagerTalkOffer_StateClass1(VillagerTalk *talk, u8 *record, VillagerPart *part);
int VillagerTalkOffer_HasOtherResident(VillagerTalk *talk);
int VillagerTalkOffer_ByKnown(VillagerTalk *talk, u8 *record, VillagerPart *part);
int VillagerTalkOffer_KnownHandover(VillagerTalk *talk, u8 *record, VillagerPart *part, unsigned int type);
void VillagerTalkOffer_PutTime(VillagerTalk *talk, const DateTime *when);
int VillagerTalkOffer_KnownGroup0(VillagerTalk *talk, u8 *record, int unused, unsigned int type);
int VillagerTalkOffer_ChoicesKind(VillagerTalk *talk);
u16 VillagerTalkOffer_PocketsOfKind(VillagerObject *object);
u16 VillagerTalkOffer_PocketsLike(u16 *item);
int VillagerTalkOffer_ChoicesClothes(VillagerTalk *talk);
int VillagerTalkOffer_ChoicesVariant(VillagerTalk *talk);
int VillagerTalkOffer_IsKindItemFree(u16 *item, int state);
int VillagerTalkOffer_IsKindItem(u16 *item);
int VillagerTalkOffer_IsClothesFree(u16 *item, int state);
int VillagerTalkOffer_IsClothes(u16 *item);
int VillagerTalkOffer_IsVariantFree(u16 *item, int state);
int VillagerTalkOffer_IsVariant(u16 *item);
int VillagerTalkOffer_ChoicesByPredicate(VillagerTalk *talk, int (*test)(u16 *item), int message_named, int message_have);
u16 VillagerTalkOffer_IsFishFree(u16 *item, int state);
u16 VillagerTalkOffer_IsFish(u16 *item);
u16 VillagerTalkOffer_IsInsectFree(u16 *item, int state);
int VillagerTalkOffer_IsInsect(u16 *item);
int VillagerTalkOffer_KnownBlock(VillagerTalk *talk, int unused, VillagerPart *part, int type);
int VillagerTalkOffer_PartBlock(VillagerTalk *talk, u8 *record, VillagerPart *part);
int VillagerTalkOffer_FirstPick(VillagerTalk *talk, u8 *record, VillagerPart *part);

#endif
