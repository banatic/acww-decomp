/* A town villager's request (the talk scene of villager_talk.h): the villager asks the player
 * for something through a block of the player's villager part (villager_part_block.h) whose
 * object takes type 10 (the text sets "q06_*") or 19 ("q07_*"). The talk keeps:
 *
 *   0x154  its object (func_0202d9c4, item_object.h)
 *   0x158  a wait in minutes drawn from data_020d8d28 (10, 30 or 60)
 *   0x159  the place of that wait in data_020d8d28, kept as the object's three high bits
 *   0x15c  the NpcId of another resident the request names
 *   0x160  the block, or 0
 *
 * The members here are line functions (the talk's 0xb0, VillagerTalkLine) and steps the
 * talk's states run: the request accepted (the block set to the object's type, the item
 * handed over or a letter written), its object stamped with now plus the wait, or emptied. */
#ifndef CLEAN_MAIN_VILLAGER_TALK_REQUEST_H
#define CLEAN_MAIN_VILLAGER_TALK_REQUEST_H

#include "types.h"
#include "villager_talk.h"

void VillagerTalkRequest_LineOver(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkRequest_ReadType(VillagerTalk *talk);
void VillagerTalkRequest_Accept(VillagerTalk *talk);
void VillagerTalkRequest_StampWait(VillagerTalk *talk);
void VillagerTalkRequest_LineYes(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkRequest_Nothing(void);
void VillagerTalkRequest_LineFull(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkRequest_Drop(VillagerTalk *talk);
void VillagerTalkRequest_LineNo(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkRequest_OfferAccept(VillagerTalk *talk);
void VillagerTalkRequest_LineTime(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkRequest_Say2a04(VillagerTalk *talk);
void VillagerTalkRequest_PickOther(VillagerTalk *talk);
void VillagerTalkRequest_LineAsk(VillagerTalk *talk, VillagerTalkLine *out);

#endif
