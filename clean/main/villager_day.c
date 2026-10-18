/* The villagers' new day (villager_day.h). */
#include "villager_day.h"

#include "clean.h"
#include "npc_id.h"
#include "town_villager.h"
#include "villager_entry.h"
#include "villager_mail.h"
#include "villager_memories.h"
#include "villager_memory_bits.h"
#include "villager_memory_entry.h"
#include "villager_status.h"

/* func_020790a8: for each villager whose NpcId is valid: func_0207d634 when func_0207f150 says
 * 3; the day's flags of each of its eight entries in use cleared; then func_02080fc0 and
 * func_02080e5c with the date.
 *
 * QUIRK: the entries are walked from what func_020807c0 gives for entry 0 even when it refuses
 * it (0), so func_02081edc is then asked about the addresses 0x000-0x380. */
void VillagerDay_Begin(u8 *villagers, const DateTime *today)
{
    for (int i = 0; i < VILLAGER_DAY_VILLAGERS; i++) {
        u8 *villager = villagers + i * VILLAGER_DAY_VILLAGER_SIZE;
        unsigned int npc = (unsigned int) (uintptr_t) (TownVillager_NpcId((u8 *) (uintptr_t) villager));

        if (NpcId_IsValid((const NpcId *) (uintptr_t) npc) != 0) {
            uintptr_t memories;

            if (VillagerStatus_Stay(villager) == 3) {
                VillagerEntry_MarkItems(villager);
            }
            memories = (uintptr_t) (unsigned int) VillagerMemory_At((u8 *) (uintptr_t) villager, 0);
            for (int j = 0; j < VILLAGER_DAY_MEMORIES; j++) {
                unsigned short *memory = (unsigned short *) (memories + (uintptr_t) j * VILLAGER_DAY_MEMORY_SIZE);

                if (VillagerMemoryEntry_InUse((VillagerMemory *) memory) != 0) {
                    VillagerMemoryEntry_ClearBit6((VillagerMemory *) memory);
                    VillagerMemoryEntry_ClearBit7((VillagerMemory *) memory);
                    VillagerMemoryBits_ClearBit11((VillagerMemory *) memory);
                    VillagerMemoryBits_ClearBirthdayLetter((VillagerMemory *) memory);
                    VillagerMemoryBits_ClearNewYearLetter((VillagerMemory *) memory);
                    VillagerMemoryBits_ClearBit14((VillagerMemory *) memory);
                    VillagerMemoryBits_ClearBit5((VillagerMemory *) memory);
                }
            }
            VillagerMail_SendBirthdayLetters((u8 *) (uintptr_t) villager, (const DateTime *) (uintptr_t) today);
            VillagerMail_SendNewYearLetters((u8 *) (uintptr_t) villager, (const DateTime *) (uintptr_t) today);
        }
    }
}
CLEAN_AS(func_020790a8, VillagerDay_Begin)
