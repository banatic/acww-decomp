/* Bits of the flags of a villager's memory of a player (villager_memory_bits.h). */
#include "villager_memory_bits.h"

#include "clean.h"

static int villager_memory_bits_test(const VillagerMemory *memory, u16 bit)
{
    return (memory->flags & bit) != 0;
}

/* func_02081864 */
int VillagerMemoryBits_Bit5(VillagerMemory *memory)
{
    return villager_memory_bits_test(memory, VILLAGER_MEMORY_BIT_5);
}
CLEAN_AS(func_02081864, VillagerMemoryBits_Bit5)

/* func_02081878 */
void VillagerMemoryBits_ClearBit5(VillagerMemory *memory)
{
    memory->flags &= (u16) ~VILLAGER_MEMORY_BIT_5;
}
CLEAN_AS(func_02081878, VillagerMemoryBits_ClearBit5)

/* func_02081888 */
void VillagerMemoryBits_SetBit5(VillagerMemory *memory)
{
    memory->flags |= VILLAGER_MEMORY_BIT_5;
}
CLEAN_AS(func_02081888, VillagerMemoryBits_SetBit5)

/* func_02081898 */
int VillagerMemoryBits_Bit14(VillagerMemory *memory)
{
    return villager_memory_bits_test(memory, VILLAGER_MEMORY_BIT_14);
}
CLEAN_AS(func_02081898, VillagerMemoryBits_Bit14)

/* func_020818ac */
void VillagerMemoryBits_ClearBit14(VillagerMemory *memory)
{
    memory->flags &= (u16) ~VILLAGER_MEMORY_BIT_14;
}
CLEAN_AS(func_020818ac, VillagerMemoryBits_ClearBit14)

/* func_020818c0 */
void VillagerMemoryBits_SetBit14(VillagerMemory *memory)
{
    memory->flags |= VILLAGER_MEMORY_BIT_14;
}
CLEAN_AS(func_020818c0, VillagerMemoryBits_SetBit14)

/* func_020818d4 */
u32 VillagerMemoryBits_NewYearLetterSent(VillagerMemory *memory)
{
    return (u32) villager_memory_bits_test(memory, VILLAGER_MEMORY_NEW_YEAR_LETTER);
}
CLEAN_AS(func_020818d4, VillagerMemoryBits_NewYearLetterSent)

/* func_020818e8 */
void VillagerMemoryBits_ClearNewYearLetter(VillagerMemory *memory)
{
    memory->flags &= (u16) ~VILLAGER_MEMORY_NEW_YEAR_LETTER;
}
CLEAN_AS(func_020818e8, VillagerMemoryBits_ClearNewYearLetter)

/* func_020818fc */
void VillagerMemoryBits_SetNewYearLetter(VillagerMemory *memory)
{
    memory->flags |= VILLAGER_MEMORY_NEW_YEAR_LETTER;
}
CLEAN_AS(func_020818fc, VillagerMemoryBits_SetNewYearLetter)

/* func_02081910 */
int VillagerMemoryBits_BirthdayLetterSent(VillagerMemory *memory)
{
    return villager_memory_bits_test(memory, VILLAGER_MEMORY_BIRTHDAY_LETTER);
}
CLEAN_AS(func_02081910, VillagerMemoryBits_BirthdayLetterSent)

/* func_02081924 */
void VillagerMemoryBits_ClearBirthdayLetter(VillagerMemory *memory)
{
    memory->flags &= (u16) ~VILLAGER_MEMORY_BIRTHDAY_LETTER;
}
CLEAN_AS(func_02081924, VillagerMemoryBits_ClearBirthdayLetter)

/* func_02081938 */
void VillagerMemoryBits_SetBirthdayLetter(VillagerMemory *memory)
{
    memory->flags |= VILLAGER_MEMORY_BIRTHDAY_LETTER;
}
CLEAN_AS(func_02081938, VillagerMemoryBits_SetBirthdayLetter)

/* func_0208194c */
int VillagerMemoryBits_Bit11(VillagerMemory *memory)
{
    return villager_memory_bits_test(memory, VILLAGER_MEMORY_BIT_11);
}
CLEAN_AS(func_0208194c, VillagerMemoryBits_Bit11)

/* func_02081960 */
void VillagerMemoryBits_ClearBit11(VillagerMemory *memory)
{
    memory->flags &= (u16) ~VILLAGER_MEMORY_BIT_11;
}
CLEAN_AS(func_02081960, VillagerMemoryBits_ClearBit11)

/* func_02081974 */
void VillagerMemoryBits_SetBit11(VillagerMemory *memory)
{
    memory->flags |= VILLAGER_MEMORY_BIT_11;
}
CLEAN_AS(func_02081974, VillagerMemoryBits_SetBit11)
