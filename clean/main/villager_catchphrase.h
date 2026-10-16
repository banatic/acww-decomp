/* The catchphrase of one of the town's villagers: four characters at 0x7c6 (town_villager.h),
 * cleared to 0. A new villager takes the one its number has in the message group
 * "st_npc_habit" (TownVillager_Setup).
 *
 * The catchphrase goes in and out through a wide text object of its own (vtable data_020e1934,
 * func_02082164 constructs it, func_0208214c destroys it, its characters at 0x0e) and through
 * the game's 8-bit text objects. */
#ifndef CLEAN_MAIN_VILLAGER_CATCHPHRASE_H
#define CLEAN_MAIN_VILLAGER_CATCHPHRASE_H

#include "types.h"

#define VILLAGER_CATCHPHRASE 0x7c6
#define VILLAGER_CATCHPHRASE_LENGTH 4
/* VillagerCatchphrase_ToLabel: how many lines "st_itchy" has to draw from. */
#define VILLAGER_CATCHPHRASE_ITCHY_LINES 0x10

/* The catchphrase's wide text object, as big as the game keeps it on its stack. */
typedef struct VillagerCatchphraseText {
    u32 words[7];
} VillagerCatchphraseText;

void VillagerCatchphrase_Set(u8 *villager, const u16 *chars, int count);
void VillagerCatchphrase_SetFromText(u8 *villager, VillagerCatchphraseText *text);
void VillagerCatchphrase_SetFromLabel(u8 *villager, void *label);
void VillagerCatchphrase_ToText(u8 *villager, VillagerCatchphraseText *text);
void VillagerCatchphrase_ToLabel(u8 *villager, void *label, int itchy);
void VillagerCatchphrase_Clear(u8 *villager);

#endif
