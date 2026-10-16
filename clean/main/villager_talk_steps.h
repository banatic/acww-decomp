/* More members of the town villagers' talk scenes (VillagerTalk, villager_talk.h): line
 * functions for their member at 0xb0 (most draw a line of a text set for the villager's
 * personality into the talk's text at 0x104 and message at 0x122 and name them in a
 * VillagerTalkLine), steps that say the line of a table of three members (func_0202da88),
 * offer choices, ask the scene's command for a screen or a motion, and hand the player an
 * item or what a villager handed over (VillagerPartHandover, villager_part_handover.h).
 *
 * Several look at the object at 0x154 of the talk (an ItemObject, item_object.h, by its type:
 * 14, 16 or 17): its type picks the message and what the villager gives. */
#ifndef CLEAN_MAIN_VILLAGER_TALK_STEPS_H
#define CLEAN_MAIN_VILLAGER_TALK_STEPS_H

#include "types.h"
#include "villager_talk.h"

void VillagerTalkSteps_Line8a28(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkSteps_LineClearHandover(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkSteps_LineHandoverTime(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkSteps_HandOver(VillagerTalk *talk);
void VillagerTalkSteps_LineKeptTime(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkSteps_Line8bb0(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkSteps_Line8bc0(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkSteps_Line8bd0(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkSteps_SayByKeptTime(VillagerTalk *talk);
void VillagerTalkSteps_OpenScreen31(VillagerTalk *talk, int event);
void VillagerTalkSteps_Line89c0(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkSteps_OfferChoices1f(VillagerTalk *talk);
void VillagerTalkSteps_Line89b8(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkSteps_Line89a8Group2(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkSteps_SayByFreePocket2fd4(VillagerTalk *talk);
void VillagerTalkSteps_Line8aa8Group1(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkSteps_MarkMoveObject(void);
void VillagerTalkSteps_Line89e0(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkSteps_ClearMove(void);
void VillagerTalkSteps_Line8bf8(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkSteps_Say2f8c(VillagerTalk *talk);
void VillagerTalkSteps_GiveGiftToPockets(VillagerTalk *talk);
void VillagerTalkSteps_LineGift(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkSteps_SayByFreePocket2fa4(VillagerTalk *talk);
void VillagerTalkSteps_Line8c08(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkSteps_Line8c18(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkSteps_Line8cd8(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkSteps_LineByObjectType(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkSteps_Say2f14(VillagerTalk *talk);
void VillagerTalkSteps_GiveByObjectType(VillagerTalk *talk);
void VillagerTalkSteps_LineGiveByObjectType(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkSteps_TakePocketAndSay(VillagerTalk *talk);
void VillagerTalkSteps_AskPocket1561(VillagerTalk *talk, void *unused);
int VillagerTalkSteps_Is1561Item(u16 *item, int state);
void VillagerTalkSteps_NextStep(VillagerTalk *talk);

#endif
