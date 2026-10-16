/* More members of the town villagers' talk scenes (VillagerTalk, villager_talk.h): the line
 * functions their member at 0xb0 holds, the steps that say the line of a table, offer
 * choices, give or take items and note the player in the villager's memory.
 *
 * A line function draws a line for the villager's personality from a text set (func_0202da38)
 * into the talk's text at 0x104 and message at 0x122 and names them in a VillagerTalkLine.
 * Several of them first let func_02020a5c say a line that takes precedence (one about the
 * talk's state), and use bit 6 of the villager's memory of the player (set once the talk of
 * the day was had, cleared each day) to pick a table of three members (func_0202da88), whose
 * line function then writes the line.
 *
 * Some read the record at data_021f3aa4: a person's NpcId at 0x1e and another at 0x2e, an
 * item at 0x3e and its size (fixed point, 12 bits of fraction) at 0x40; its address is also
 * taken as a player (func_020951bc). */
#ifndef CLEAN_MAIN_VILLAGER_TALK_LINES_H
#define CLEAN_MAIN_VILLAGER_TALK_LINES_H

#include "types.h"
#include "villager_talk.h"

void VillagerTalk_Line2bdb4(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalk_LineByDayWindow(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalk_OfferChoices1e14A(VillagerTalk *talk);
void VillagerTalk_Line2a5e8A(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalk_Say208c(VillagerTalk *talk);
void VillagerTalk_Line8d60(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalk_Line8d60AboutNpc(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalk_Line8d60SinceEvent17(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalk_LineRandom2044(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalk_Line8ba0Group15(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalk_GiveItemFor1546(VillagerTalk *talk);
void VillagerTalk_Line8ba0Group19(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalk_SayIfFond(VillagerTalk *talk);
void VillagerTalk_Line8ba0Group17(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalk_Say25bcNext(VillagerTalk *talk);
void VillagerTalk_TakePocketOrSay(VillagerTalk *talk);
void VillagerTalk_AskPocket1542(VillagerTalk *talk);
void VillagerTalk_OfferChoices5b(VillagerTalk *talk);
void VillagerTalk_Line8ba0Group13(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalk_OfferChoices1e14B(VillagerTalk *talk);
void VillagerTalk_Line2a5e8B(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalk_Say2574(VillagerTalk *talk);
void VillagerTalk_Line8ba0Group7(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalk_Line8ba0Group10(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalk_Line8ba0SinceEvent16(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalk_LineRandom252c(VillagerTalk *talk, VillagerTalkLine *out);
u16 VillagerTalk_Pick1542Item(u16 *item, int state);
int VillagerTalk_Is1542Item(u16 *item);
void VillagerTalk_OfferChoices1e14C(VillagerTalk *talk);
void VillagerTalk_Line2a5e8C(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalk_Say202c(VillagerTalk *talk);
void VillagerTalk_Line8bd8Group10(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalk_Line8bd8Group13(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalk_Line8bd8SinceEvent14(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalk_LineRandom1fe4(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalk_NoteAndMarkMemory(VillagerTalk *talk);
void VillagerTalk_LineItem12b0(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalk_NoteAndMarkMemoryAgain(VillagerTalk *talk);
void VillagerTalk_LineItem12e8(VillagerTalk *talk, VillagerTalkLine *out);
int VillagerTalk_GroupForHour(int hour);
void VillagerTalk_OfferChoices1e14D(VillagerTalk *talk);
void VillagerTalk_Line2a5e8D(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalk_Say237c(VillagerTalk *talk);
void VillagerTalk_Line8ce8Group4(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalk_Line8ce8Group10(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalk_Line8ce8Group14(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalk_StoreTextSay2334(VillagerTalk *talk);
void VillagerTalk_ShowText9430(VillagerTalk *talk, int event);
void VillagerTalk_Line8ce8Group12(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalk_OfferChoices5a(VillagerTalk *talk);
void VillagerTalk_Line8ce8Group7(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalk_Line8ce8Group2(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalk_StoreTextSay22ec(VillagerTalk *talk);
void VillagerTalk_StoreText(VillagerTalk *talk);
void VillagerTalk_ShowText9310(VillagerTalk *talk, int event);
void VillagerTalk_Line8ce8(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalk_LineRandom22d4(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalk_NoteMemoryOnEvent(VillagerTalk *talk, void *event);
void VillagerTalk_LineByCalendar(VillagerTalk *talk, VillagerTalkLine *out);
void VillagerTalk_OfferChoices1e14(VillagerTalk *talk);

#endif
