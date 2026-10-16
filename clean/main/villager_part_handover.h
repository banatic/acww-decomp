/* The record at 0xa4 of the villagers' part of a player's record (VillagerPart,
 * villager_part.h): what a villager handed over to the player (func_02023348 sets it with the
 * villager's NpcId and empties the villager's own object).
 *
 *   0x00  the villager's NpcId
 *   0x10  an object (12 bytes): type 21, no item, its date set when it was handed over
 *   0x1c  a date given with it
 *   0x24  a byte whose low three bits are a kind (VillagerTown_ExpirePlayerObjects)
 *
 * It is emptied when it expires (villager_town.c). */
#ifndef CLEAN_MAIN_VILLAGER_PART_HANDOVER_H
#define CLEAN_MAIN_VILLAGER_PART_HANDOVER_H

#include "calendar.h"
#include "npc_id.h"
#include "types.h"

/* The object's type. */
#define VILLAGER_PART_HANDOVER_TYPE 21

typedef struct VillagerPartHandover {
    NpcId npc;     /* 0x00 */
    u8 object[12]; /* 0x10 */
    DateTime date; /* 0x1c */
    u8 byte_24;    /* 0x24 */
    u8 unused_25[3];
} VillagerPartHandover;

void VillagerPartHandover_Set(VillagerPartHandover *handover, const NpcId *npc, const DateTime *date);
int VillagerPartHandover_IsFrom(VillagerPartHandover *handover, const NpcId *npc);
void VillagerPartHandover_Clear(VillagerPartHandover *handover);
VillagerPartHandover *VillagerPartHandover_Destruct(VillagerPartHandover *handover);
VillagerPartHandover *VillagerPartHandover_Construct(VillagerPartHandover *handover);

#endif
