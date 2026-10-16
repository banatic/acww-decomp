/* The letters one of the town's villagers gets from the players and writes to them.
 *
 * A villager keeps the last letter a player sent it (0x634, town_villager.h) and the town it
 * got it in (0x7dc); its memory of the sender gets bit 0 of its flags (villager_memories.h),
 * and an item that came with it can join the items of its house. It answers the letter with
 * "re_bad" (and likes the player 3 less) or "re_normal" (and likes the player 3 more, 5 for a
 * letter with an item, which brings a present in return), by how func_0206d7ac grades it.
 *
 * Without being written to it sends the town's players it likes enough (fondness 0x40 and
 * more) a letter on new year's day ("ev_newyear") and on their birthday ("ev_birth", with a
 * present), from 6 o'clock and once that day (villager_memory_bits.h), and to every player of
 * this town it knows a farewell when it leaves ("byebye"). */
#ifndef CLEAN_MAIN_VILLAGER_MAIL_H
#define CLEAN_MAIN_VILLAGER_MAIL_H

#include "calendar.h"
#include "design.h"
#include "mail.h"
#include "types.h"

/* What func_0206d7ac makes of a letter's text. */
#define VILLAGER_MAIL_GRADE_NONE 0
#define VILLAGER_MAIL_GRADE_BAD 1
#define VILLAGER_MAIL_GRADE_GOOD 2

int VillagerMail_HasHeldLetter(u8 *villager);
int VillagerMail_HeldLetterMemory(u8 *villager);
void VillagerMail_SendFarewells(u8 *villager);
void VillagerMail_SendFarewell(u8 *villager, u8 *record);
void VillagerMail_SendNewYearLetters(u8 *villager, const DateTime *today);
void VillagerMail_SendNewYearLetter(u8 *villager, u8 *record, const DateTime *today);
void VillagerMail_SendBirthdayLetters(u8 *villager, const DateTime *today);
void VillagerMail_SendBirthdayLetter(u8 *villager, u8 *record, const DateTime *today);
void VillagerMail_Reply(u8 *villager, u8 *record, MailLetter *letter);
int VillagerMail_HoldsLetterFrom(u8 *villager, const DesignCreator *player);
int VillagerMail_Receive(u8 *villager, MailLetter *letter);

#endif
