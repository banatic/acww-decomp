/* The parts of one memory a villager keeps of a player (VillagerMemory, villager_memories.h),
 * each read and written through its own small function.
 *
 * Besides what villager_memories.h lists, a memory holds:
 *
 *   0x70  a word marking which of 32 numbers have been drawn (VillagerMemoryEntry_DrawUnused)
 *   0x74  8 bytes copied from data_021f3b68 (type 12's values, packed) when it is updated
 *
 * and these bits of its flags (0x7c; villager_memory_bits.h has bits 5 and 11-14):
 *
 *   bit 0     a letter of the player is held (villager_mail.h)
 *   bit 1     the text at 0x2a is set
 *   bit 2     the 8 bytes at 0x74 are set
 *   bit 3     the text at 0x3e is set
 *   bit 4     tested and set by func_0202b800
 *   bit 6     tested and set by the scenes of func_0201e898 and others
 *   bit 7     set by overlay 4
 *
 * Bits 6 and 7 are cleared each day (villager_day.h).
 *   bits 8-10 on how many days in a row the player has been met, at most 4
 *
 * Each new day the villager meets the player it grows fonder of the player by one more than
 * that count (VillagerMemoryEntry_Update). */
#ifndef CLEAN_MAIN_VILLAGER_MEMORY_ENTRY_H
#define CLEAN_MAIN_VILLAGER_MEMORY_ENTRY_H

#include "calendar.h"
#include "design.h"
#include "npc_id.h"
#include "types.h"
#include "villager_memories.h"
#include "villager_memory_text.h"

#define VILLAGER_MEMORY_LETTER_HELD 0x0001
#define VILLAGER_MEMORY_TEXT_2A_SET 0x0002
#define VILLAGER_MEMORY_VALUES_SET 0x0004
#define VILLAGER_MEMORY_TEXT_3E_SET 0x0008
#define VILLAGER_MEMORY_BIT_4 0x0010
#define VILLAGER_MEMORY_BIT_6 0x0040
#define VILLAGER_MEMORY_BIT_7 0x0080
#define VILLAGER_MEMORY_DAYS_SHIFT 8
#define VILLAGER_MEMORY_DAYS_MASK 0x0700
#define VILLAGER_MEMORY_DAYS_MAX 4

#define VILLAGER_MEMORY_TEXT_LENGTH 10
#define VILLAGER_MEMORY_NICKNAME_LENGTH 6

int VillagerMemoryEntry_Bit7(VillagerMemory *memory);
void VillagerMemoryEntry_ClearBit7(VillagerMemory *memory);
void VillagerMemoryEntry_SetBit7(VillagerMemory *memory);
int VillagerMemoryEntry_Bit6(VillagerMemory *memory);
void VillagerMemoryEntry_ClearBit6(VillagerMemory *memory);
void VillagerMemoryEntry_SetBit6(VillagerMemory *memory);
int VillagerMemoryEntry_Bit4(VillagerMemory *memory);
void VillagerMemoryEntry_SetBit4(VillagerMemory *memory);
int VillagerMemoryEntry_DrawUnused(VillagerMemory *memory);
void VillagerMemoryEntry_SetImpression(VillagerMemory *memory, u8 impression);
u8 VillagerMemoryEntry_Impression(VillagerMemory *memory);
void VillagerMemoryEntry_SetValues(VillagerMemory *memory, const void *values);
int VillagerMemoryEntry_ValuesSet(VillagerMemory *memory);
int VillagerMemoryEntry_Item(VillagerMemory *memory);
void VillagerMemoryEntry_SetItem(VillagerMemory *memory, const u16 *item);
void VillagerMemoryEntry_SetText3E(VillagerMemory *memory, const u16 *text, int length);
void VillagerMemoryEntry_Text3EToWide(VillagerMemory *memory, void *wide);
void VillagerMemoryEntry_Text3EToLabel(VillagerMemory *memory, void *label);
int VillagerMemoryEntry_Text3ESet(VillagerMemory *memory);
void VillagerMemoryEntry_SetText2A(VillagerMemory *memory, const u16 *text, int length);
void VillagerMemoryEntry_Text2AToWide(VillagerMemory *memory, void *wide);
void *VillagerMemoryEntry_Text2AToLabel(VillagerMemory *memory, void *label);
int VillagerMemoryEntry_Text2ASet(VillagerMemory *memory);
void VillagerMemoryEntry_SetNicknameChars(VillagerMemory *memory, const u16 *chars, int length);
void *VillagerMemoryEntry_SetNickname(VillagerMemory *memory, void *label);
void VillagerMemoryEntry_NicknameToWide(VillagerMemory *memory, void *wide);
void VillagerMemoryEntry_NicknameToLabel(VillagerMemory *memory, void *label);
void VillagerMemoryEntry_SetLetterHeld(VillagerMemory *memory);
int VillagerMemoryEntry_LetterHeld(VillagerMemory *memory);
s8 VillagerMemoryEntry_ChangeFondness(VillagerMemory *memory, int delta);
void VillagerMemoryEntry_SetFondness(VillagerMemory *memory, u8 fondness);
int VillagerMemoryEntry_Fondness(VillagerMemory *memory);
int VillagerMemoryEntry_IsPlayer(const VillagerMemory *memory, const DesignCreator *player);
DesignCreator *VillagerMemoryEntry_Player(VillagerMemory *memory);
int VillagerMemoryEntry_Town(VillagerMemory *memory);
int VillagerMemoryEntry_RaiseFondness(VillagerMemory *memory);
int VillagerMemoryEntry_CountDays(VillagerMemory *memory, const DateTime *now);
int VillagerMemoryEntry_When(VillagerMemory *memory);
void VillagerMemoryEntry_Update(VillagerMemory *memory, const DesignCreator *player, const NpcIdHead *town,
                                const DateTime *now);
int VillagerMemoryEntry_Take(VillagerMemory *memory, const DesignCreator *player, const NpcIdHead *town, const DateTime *now);
int VillagerMemoryEntry_InUse(VillagerMemory *memory);
void VillagerMemoryEntry_Clear(VillagerMemory *memory);
VillagerMemory *VillagerMemoryEntry_Destruct(VillagerMemory *memory);
VillagerMemory *VillagerMemoryEntry_Construct(VillagerMemory *memory);

#endif
