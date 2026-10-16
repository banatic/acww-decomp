/* A town villager's nickname for the player and its catchphrase, in the talk scene
 * (villager_talk.h): the villager's memory of the player (the talk's 0x12c, villager_memories.h)
 * keeps the nickname.
 *
 * The player types a nickname of up to six characters on the text screen
 * (VillagerTalkNickname_AskText, into data_021c1e84) and it is kept when the screen was
 * confirmed (VillagerTalkNickname_Keep); or the villager picks one of the nickname messages for
 * its personality (VillagerTalkNickname_Pick, eight messages from a base of data_020c8968), the
 * player's own name when none loads. The lines here draw the texts "ap_nickn" and "ap_habit"
 * (the catchphrase) by the villager's personality (Personality_FormatResourceName).
 *
 * Also here: a line of the text set "etc_connect" other talks use. */
#ifndef CLEAN_MAIN_VILLAGER_TALK_NICKNAME_H
#define CLEAN_MAIN_VILLAGER_TALK_NICKNAME_H

#include "types.h"
#include "villager_talk.h"

void VillagerTalkNickname_LineConnect(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkNickname_Line1(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkNickname_Line5(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkNickname_AskTextLine(VillagerTalk *talk, VillagerTalkLine *unused);
void VillagerTalkNickname_OfferRetype(VillagerTalk *talk);
void VillagerTalkNickname_Line4(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkNickname_Keep(VillagerTalk *talk);
void VillagerTalkNickname_AskText(VillagerTalk *talk, int unused);
void VillagerTalkNickname_Line3(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkNickname_OfferIfFond(VillagerTalk *talk);
void VillagerTalkNickname_Pick(VillagerTalk *talk);
int VillagerTalkNickname_Load(void *text, void *name, unsigned int personality);
void VillagerTalkNickname_Line2(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkNickname_OfferChange(VillagerTalk *talk);
void VillagerTalkNickname_LineHabit(VillagerTalk *talk, VillagerTalkLine *out);

void VillagerTalkNickname_LineHabitFlip(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkNickname_OfferRetypeHabit(VillagerTalk *talk);
void VillagerTalkNickname_LineHabit6(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkNickname_AskHabitTextLine(VillagerTalk *talk, VillagerTalkLine *unused);
void VillagerTalkNickname_KeepHabit(VillagerTalk *talk);
void VillagerTalkNickname_AskHabitText(VillagerTalk *talk, int unused);
void VillagerTalkNickname_LineHabitGroup1(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkNickname_OfferHabit(VillagerTalk *talk);

#endif
