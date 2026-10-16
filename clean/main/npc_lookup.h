/* What the game looks up about a villager by its number (0-149, npc_id.h) and about a person by
 * its code (an ItemCode, lookups.h): its name and first catchphrase from the message groups
 * "st_npc_name" and "st_npc_habit", its data (villager_data.h), and the hours of the night its
 * personality sleeps.
 *
 * A person's code has a kind in its top four bits and an index in the rest:
 *   0xd  a special character: index 0-37 of the records of kind 0xd (func_020824d0, three bytes
 *        each: byte 1 a personality kind, byte 2 a species byte), whose names are the group
 *        "st_spnpc_name";
 *   0xe  one of the town's villagers: index 0-7, its place (VillagerRoster_At). */
#ifndef CLEAN_MAIN_NPC_LOOKUP_H
#define CLEAN_MAIN_NPC_LOOKUP_H

#include "calendar.h"
#include "lookups.h"
#include "types.h"
#include "villager_data.h"

#define NPC_CODE_KIND_SPECIAL 0xd
#define NPC_CODE_KIND_VILLAGER 0xe
/* How many special characters have a name and a record. */
#define NPC_SPECIAL_COUNT 0x26

/* What NpcLookup_PersonalityKind gives for a code of no person, and NpcLookup_SpeciesByte. */
#define NPC_LOOKUP_NO_KIND 5
#define NPC_LOOKUP_NO_SPECIES 0

int NpcLookup_IsInNightWindow(int personality, const DateTime *when);
int NpcLookup_FourUnlessSlotTaken(void);
int NpcLookup_CatchphraseToWide(void *wide, int number);
int NpcLookup_FormatCatchphrase(void *label, int number);
int NpcLookup_SpeciesByte(const ItemCode *code);
int NpcLookup_PersonalityKind(ItemCode *code);
int NpcLookup_FormatPersonName(void *label, ItemCode *code);
int NpcLookup_FormatName(char *label, int number);
const VillagerData *NpcLookup_Data(int number);

#endif
