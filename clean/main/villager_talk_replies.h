/* More members of the town villagers' talk scenes (VillagerTalk, villager_talk.h): line
 * functions for their member at 0xb0, steps that say the line of a table of three members
 * (func_0202da88), offer two choices or ask the scene's command for a sound or a talk mode.
 *
 * Most line functions draw a line for the villager's personality from a text set
 * (func_0202da38) into the talk's text at 0x104 and message at 0x122 and name them in a
 * VillagerTalkLine. VillagerTalkReplies_LineForSituation is the line that takes precedence
 * over a talk's own (about the villager's state, the player, the session); other line
 * functions call it first (villager_talk_lines.h). */
#ifndef CLEAN_MAIN_VILLAGER_TALK_REPLIES_H
#define CLEAN_MAIN_VILLAGER_TALK_REPLIES_H

#include "types.h"
#include "villager_talk.h"

void VillagerTalkReplies_LineAb0Group17(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkReplies_LineAb0Group14(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkReplies_LineAb0Group12(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkReplies_LineAb0Group10(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkReplies_MarkVillager(VillagerTalk *talk, int event);
void VillagerTalkReplies_LineAb0Group8(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkReplies_OfferChoices44(VillagerTalk *talk, int event);
void VillagerTalkReplies_LineAb0Group6(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkReplies_Say249cNextLine(VillagerTalk *talk);
void VillagerTalkReplies_RequestSound(VillagerTalk *talk);
void VillagerTalkReplies_TalkMode3(VillagerTalk *talk, void *unused);
void VillagerTalkReplies_Say2484(VillagerTalk *talk, int event);
void VillagerTalkReplies_LineAb0Group20(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkReplies_OfferChoicesC4(VillagerTalk *talk, int event);
void VillagerTalkReplies_LineAb0Group3(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkReplies_LineFirstOfDay(VillagerTalk *talk, VillagerTalkLine *out);
int VillagerTalkReplies_LineForSituation(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkReplies_Line2454(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkReplies_Line8a98(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkReplies_Line8a88Group1(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkReplies_LineNewcomer(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkReplies_OfferChoices37(VillagerTalk *talk);
void VillagerTalkReplies_Line8a88Group0(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalkReplies_OfferChoicesByArrival(VillagerTalk *talk);
void VillagerTalkReplies_Say219c(VillagerTalk *talk);
void VillagerTalkReplies_NoteMemory(VillagerTalk *talk);

#endif
