/* Members of the town villagers' talk scenes (VillagerTalk, villager_talk.h) about the object
 * a villager keeps (its record's object at 0x24, villager_object.h, which the talk holds at
 * 0x164, and the talk's object at 0x154, func_0202d9c4, both item_object.h) of the types of
 * group 0, the ones that go through steps. Their type matches the villager's mode
 * (villager_house_items.h): 0 an insect (items 0x12b0-0x12e7), 1 a fish (0x12e8-0x131f), 2 an
 * item of 0x450c-0x45db (item_attributes.h), 3 clothes (0x11a8-0x12a7) and 4 furniture.
 *
 * Here: line functions for the talk's member at 0xb0 (most draw a line of a text set for the
 * villager's personality into the talk's text at 0x104 and message at 0x122, picked by the
 * object's type, its place in its group or its step), steps that say the line of a table of
 * three members (func_0202da88), ask for the pockets screen with the items the object wants,
 * take an item from the player's pockets or hand the player a reward for it, start the
 * villager's object and send it to the others in the session, and the item functions that
 * pick an item for a type (two tables of the game's functions). */
#ifndef CLEAN_MAIN_VILLAGER_TALK_OBJECT_H
#define CLEAN_MAIN_VILLAGER_TALK_OBJECT_H

#include "types.h"
#include "villager_object.h"
#include "villager_talk.h"

void VillagerTalkObject_LineByPlace9d38(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkObject_LineByPlace9d24(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkObject_MarkDone(VillagerTalk *talk);
void VillagerTalkObject_LineByGroupPlace(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkObject_LineByType8e74(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkObject_SayByLastStep(VillagerTalk *talk);
void VillagerTalkObject_ShowGift91a8(VillagerTalk *talk);
void VillagerTalkObject_LineTakeItemType3(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkObject_GiveReward(VillagerTalk *talk);
void VillagerTalkObject_SayIfOn2e6c(VillagerTalk *talk);
void VillagerTalkObject_Line8c60(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkObject_SayByType2e6c(VillagerTalk *talk);
void VillagerTalkObject_EmptyPocketAndMotion(VillagerTalk *talk);
void VillagerTalkObject_LineByType9a9c(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkObject_LineGroupByType(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkObject_Motion17(VillagerTalk *talk);
void VillagerTalkObject_LineByType96c4(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkObject_SayJudgeItem(VillagerTalk *talk);
void VillagerTalkObject_TakePocket9200(VillagerTalk *talk);
void VillagerTalkObject_AskPocketByType(VillagerTalk *talk);
void VillagerTalkObject_CountItem(VillagerTalk *talk);
void VillagerTalkObject_Line8d08(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkObject_ShowGift8f70(VillagerTalk *talk);
void VillagerTalkObject_SayByStep4(VillagerTalk *talk);
void VillagerTalkObject_LineKeepItem8b10(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkObject_SayIfOn2dc4(VillagerTalk *talk);
void VillagerTalkObject_Motion16(VillagerTalk *talk, int event);
void VillagerTalkObject_Line8ad0(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkObject_LineClearItem(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkObject_Say2dac(VillagerTalk *talk);
void VillagerTalkObject_TakePocket91c0(VillagerTalk *talk);
void VillagerTalkObject_SayOrAskCatch(VillagerTalk *talk);
void VillagerTalkObject_Line8ce0(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkObject_Motion17ClearItem(VillagerTalk *talk);
void VillagerTalkObject_Line8b58(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkObject_LineKeepItem8d58(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkObject_SayIfOn2d34(VillagerTalk *talk);
void VillagerTalkObject_EmptyPocketMotion16(VillagerTalk *talk);
void VillagerTalkObject_Line8aa0(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkObject_SayByPrice(VillagerTalk *talk);
void VillagerTalkObject_TakePocket92e8(VillagerTalk *talk);
void VillagerTalkObject_AskPocketCatch(VillagerTalk *talk);
void VillagerTalkObject_LineByStep9dd4(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkObject_SayIfOn2cec(VillagerTalk *talk);
void VillagerTalkObject_LineByPlaceStep(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkObject_Start(VillagerTalk *talk);
void VillagerTalkObject_Line8d48(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkObject_StartForPlayer(VillagerTalk *talk);
void VillagerTalkObject_Line8d50(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkObject_StartForPlayerAgain(VillagerTalk *talk);
void VillagerTalkObject_OfferChoices1f(VillagerTalk *talk);
void VillagerTalkObject_PutItemNames(VillagerTalk *talk);
void VillagerTalkObject_PickByStep(u16 *out, VillagerTalk *talk, unsigned int step);
void VillagerTalkObject_KindItem(u16 *out, VillagerObject *object, u8 *villager);
int VillagerTalkObject_ItemPart(u16 *item);
int VillagerTalkObject_KindPart(u16 *item, int kind);
void VillagerTalkObject_DrawKindItem(u16 *out, int unused_object, int unused_villager);
void VillagerTalkObject_PickClothesByStep(u16 *out, VillagerTalk *talk, unsigned int step);
void VillagerTalkObject_DrawClothes(u16 *out, u8 *data, int clothes);
void VillagerTalkObject_DrawClothesAnyPlayer(u16 *out, u8 *data, int clothes);

#endif
