/* Members of the town villagers' talk scenes (VillagerTalk, villager_talk.h) for the talk
 * objects of types 10 and 19 (the step types of a block of the player's villager part,
 * villager_part_block.h: type 10 has an item drawn from item list 2, type 19 the item 0x1565
 * and a letter written from the block's two villagers). The talk holds that block at 0x160 and
 * its own object at 0x154 (func_0202d9c4, item_object.h).
 *
 * Type 10 goes with clothes (0x11a8-0x12a7): the villager's reaction to them is kept in the
 * block's byte 0x2c (VillagerTalkPart_ReactToClothes: 0 when their style value is the
 * villager's first style byte, 2 when it is the second, else 1) and picks the reward. Type 19
 * goes with the letters in the player's pockets whose state is 7 or 8 (func_0202d754, mail.h).
 * The members change the bond between the block's villagers and the talk's villager
 * (VillagerPair_AddBond) and clear the block when done.
 *
 * Also here: the line of the villager object's step for the place of the talk's object, the
 * item the player is handed (a bag of bells for an item of 0x1492-0x14fd), its name or amount
 * put into the talk's slot 1, and the bag of bells for an amount. */
#ifndef CLEAN_MAIN_VILLAGER_TALK_PART_H
#define CLEAN_MAIN_VILLAGER_TALK_PART_H

#include "types.h"
#include "villager_talk.h"

void VillagerTalkPart_LineByPlaceStep9cc0(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkPart_LineClearBlock(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkPart_Say2c74(VillagerTalk *talk);
void VillagerTalkPart_HandItem(VillagerTalk *talk);
void VillagerTalkPart_LinePutItem(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkPart_Say2c5c(VillagerTalk *talk);
void VillagerTalkPart_Line8b68(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkPart_SayByPocketRoom(VillagerTalk *talk);
void VillagerTalkPart_LineReward8d98(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkPart_LineReward8da0(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkPart_LineReward8da8(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkPart_SayChoice29d4(VillagerTalk *talk, int unused, int choice);
void VillagerTalkPart_StartByType(VillagerTalk *talk, int arg);
void VillagerTalkPart_BellBag(u16 *out, int bells);
void VillagerTalkPart_LineByType8dc8(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkPart_LineByType8de0(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkPart_LineTakeByType(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkPart_OpenLetter(VillagerTalk *talk, int event);
void VillagerTalkPart_Motion16Member9068(VillagerTalk *talk);
void VillagerTalkPart_Line8df8(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkPart_SayIfFond(VillagerTalk *talk);
void VillagerTalkPart_SayNextLine(VillagerTalk *talk);
void VillagerTalkPart_Line8e00(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkPart_LowerBondMotion16(VillagerTalk *talk);
void VillagerTalkPart_Line8e10(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkPart_Motion16Say2bb4(VillagerTalk *talk);
void VillagerTalkPart_Line8e20(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkPart_Motion16KeepItem(VillagerTalk *talk);
void VillagerTalkPart_LineStep1(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkPart_RaiseBondClothes(VillagerTalk *talk);
void VillagerTalkPart_Line8ba8(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkPart_ReactToClothes(VillagerTalk *talk);
void VillagerTalkPart_RaiseBondByType(VillagerTalk *talk);
void VillagerTalkPart_LineByType8e48(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkPart_TakeChosenItem(VillagerTalk *talk);
void VillagerTalkPart_NextLine(VillagerTalk *talk);
void VillagerTalkPart_Line8980(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkPart_AskPocketsByType(VillagerTalk *talk);
u16 VillagerTalkPart_IsClothesInState2(u16 *item, int state);
void VillagerTalkPart_Line8978(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkPart_ShowObjectItemLowerBond(VillagerTalk *talk);
void VillagerTalkPart_LinePutNames(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkPart_LowerBondClear(VillagerTalk *talk);
void VillagerTalkPart_LineByType8990(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkPart_ShowItemClear(VillagerTalk *talk);
void VillagerTalkPart_LineByType8e38(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkPart_TakeMatchingItem(VillagerTalk *talk);
void VillagerTalkPart_SayByLetter(VillagerTalk *talk);

#endif
