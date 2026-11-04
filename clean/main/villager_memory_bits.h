/* Bits of the flags of a villager's memory of a player (the halfword 0x7c, villager_memories.h)
 * with a test, a set and a clear each:
 *
 *   bit 5   the villager is to hand the player a lucky item at its next greeting (the
 *           "ai_fortune" lines, villager_talk_greeting.c); set for the one
 *           VillagerTown_PickFortuneGiver picks
 *   bit 11  set and tested by overlay 4's birthday villager (birthday_villager.c)
 *   bit 12  the villager's birthday letter to the player was sent (VillagerMail_SendBirthdayLetter)
 *   bit 13  its new year letter was sent (VillagerMail_SendNewYearLetter)
 *   bit 14  the villager has been to the player's flea market today (set by overlay 4's
 *           buyer, VillagerEntry_MarkFleaMarketDone); it is left out of the next visitor's
 *           pick (VillagerTown_PickOutsideAcquaintance)
 *
 * All five are cleared each day (func_020790a8). */
#ifndef CLEAN_MAIN_VILLAGER_MEMORY_BITS_H
#define CLEAN_MAIN_VILLAGER_MEMORY_BITS_H

#include "types.h"
#include "villager_memories.h"

#define VILLAGER_MEMORY_FORTUNE_DUE 0x0020
#define VILLAGER_MEMORY_BIT_11 0x0800
#define VILLAGER_MEMORY_BIRTHDAY_LETTER 0x1000
#define VILLAGER_MEMORY_NEW_YEAR_LETTER 0x2000
#define VILLAGER_MEMORY_FLEA_MARKET_DONE 0x4000

int VillagerMemoryBits_FortuneDue(VillagerMemory *memory);
void VillagerMemoryBits_ClearFortuneDue(VillagerMemory *memory);
void VillagerMemoryBits_SetFortuneDue(VillagerMemory *memory);
int VillagerMemoryBits_FleaMarketDone(VillagerMemory *memory);
void VillagerMemoryBits_ClearFleaMarketDone(VillagerMemory *memory);
void VillagerMemoryBits_SetFleaMarketDone(VillagerMemory *memory);
u32 VillagerMemoryBits_NewYearLetterSent(VillagerMemory *memory);
void VillagerMemoryBits_ClearNewYearLetter(VillagerMemory *memory);
void VillagerMemoryBits_SetNewYearLetter(VillagerMemory *memory);
int VillagerMemoryBits_BirthdayLetterSent(VillagerMemory *memory);
void VillagerMemoryBits_ClearBirthdayLetter(VillagerMemory *memory);
void VillagerMemoryBits_SetBirthdayLetter(VillagerMemory *memory);
int VillagerMemoryBits_Bit11(VillagerMemory *memory);
void VillagerMemoryBits_ClearBit11(VillagerMemory *memory);
void VillagerMemoryBits_SetBit11(VillagerMemory *memory);

#endif
