/* The entry at 0x94 of the villagers' part of a player's record (VillagerPart, villager_part.h):
 * an object naming one of five kind-0xd codes (data_020d1a54), and the choices still open.
 *
 *   0x00  an object (12 bytes): type 20 while an entry is set, with item 0x155f or 0x1560
 *   0x0c  the index of the code named (0-4; 5: none)
 *   0x0d  the choices still open, bits 0-4
 *
 * Index 0 names the codes 0xd019-0xd01c, the others one code each. When a choice is drawn
 * (VillagerPartEntry_PickChoice), choices 0 and 1 are left out outside the shops' hours, and
 * choice 0 also on the days the Nook store is closed. */
#ifndef CLEAN_MAIN_VILLAGER_PART_ENTRY_H
#define CLEAN_MAIN_VILLAGER_PART_ENTRY_H

#include "types.h"

#define VILLAGER_PART_ENTRY_CHOICES 5
#define VILLAGER_PART_ENTRY_NONE 5
/* The object's type while an entry is set. */
#define VILLAGER_PART_ENTRY_TYPE 20

typedef struct VillagerPartEntry {
    u8 object[12]; /* 0x00 */
    u8 index;      /* 0x0c: VILLAGER_PART_ENTRY_NONE for none */
    u8 choices;    /* 0x0d: bits 0-4 */
    u8 unused_0e[2];
} VillagerPartEntry;

int VillagerPartEntry_Accepts(VillagerPartEntry *entry, const u16 *code);
int VillagerPartEntry_Advance(VillagerPartEntry *entry);
int VillagerPartEntry_WriteName(VillagerPartEntry *entry, void *text);
VillagerPartEntry *VillagerPartEntry_Self(VillagerPartEntry *entry);
void VillagerPartEntry_Start(VillagerPartEntry *entry);
void VillagerPartEntry_CloseChoice(VillagerPartEntry *entry, int choice);
int VillagerPartEntry_PickChoice(VillagerPartEntry *entry, int choices);
u8 VillagerPartEntry_CountLeft(VillagerPartEntry *entry, int choices);
u8 VillagerPartEntry_CountChoices(VillagerPartEntry *entry, int choices);
void VillagerPartEntry_Clear(VillagerPartEntry *entry);

#endif
