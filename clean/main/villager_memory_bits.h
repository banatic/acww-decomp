/* Bits of the flags of a villager's memory of a player (the halfword 0x7c, villager_memories.h)
 * with a test, a set and a clear each:
 *
 *   bit 5   set for the player's acquaintance picked by VillagerTown_FlagAcquaintance
 *   bit 11  set and tested by overlay 4
 *   bit 12  the villager's birthday letter to the player was sent (VillagerMail_SendBirthdayLetter)
 *   bit 13  its new year letter was sent (VillagerMail_SendNewYearLetter)
 *   bit 14  set by VillagerEntry_FlagMemory; a villager with it is left out of
 *           VillagerTown_PickOutsideAcquaintance
 *
 * All five are cleared each day (func_020790a8). */
#ifndef CLEAN_MAIN_VILLAGER_MEMORY_BITS_H
#define CLEAN_MAIN_VILLAGER_MEMORY_BITS_H

#include "types.h"
#include "villager_memories.h"

#define VILLAGER_MEMORY_BIT_5 0x0020
#define VILLAGER_MEMORY_BIT_11 0x0800
#define VILLAGER_MEMORY_BIRTHDAY_LETTER 0x1000
#define VILLAGER_MEMORY_NEW_YEAR_LETTER 0x2000
#define VILLAGER_MEMORY_BIT_14 0x4000

int VillagerMemoryBits_Bit5(VillagerMemory *memory);
void VillagerMemoryBits_ClearBit5(VillagerMemory *memory);
void VillagerMemoryBits_SetBit5(VillagerMemory *memory);
int VillagerMemoryBits_Bit14(VillagerMemory *memory);
void VillagerMemoryBits_ClearBit14(VillagerMemory *memory);
void VillagerMemoryBits_SetBit14(VillagerMemory *memory);
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
