/* Letters a villager writes to a player, held at the post office for the next delivery
 * (Mail_HoldAtPostOffice, mail.h).
 *
 * The letter's text comes from a group of messages named by a resource name of the villager's
 * personality (NpcId_FormatResourceName, into a buffer of 40 characters), its paper from the
 * personality's set (MomLetters_PaperFromSet), and it may carry an item. */
#ifndef CLEAN_MAIN_VILLAGER_LETTER_H
#define CLEAN_MAIN_VILLAGER_LETTER_H

#include "npc_id.h"
#include "types.h"

#define VILLAGER_LETTER_NAME_SIZE 0x28
#define VILLAGER_LETTER_NO_ITEM 0xfff1
/* The parts of a letter VillagerLetter_PostDrawn draws. */
#define VILLAGER_LETTER_PARTS 4

int VillagerLetter_Post(const char *name, int text, const void *player, const NpcId *npc, const u16 *item);
int VillagerLetter_PostDrawn(const char *name, int first, int choices, const void *player, const NpcId *npc, const u16 *item);

#endif
