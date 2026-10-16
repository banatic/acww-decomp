/* The eight places of the town's villagers (VillagerTown, villager_town.h): finding a villager
 * by index, NpcId, number, code or name, counting them, drawing one at random, and the
 * constructor, destructor and reset of the whole block.
 *
 * A place is filled when its NpcId (at 0x7a0, func_0208150c) is valid (NpcId_IsValid). A
 * villager is found by its NpcId when the first halfword, the 12 bytes after it and the number
 * agree (the personality is not compared). Places are drawn with VillagerRoster_PickBit: a
 * random one of the bits set in a mask. */
#ifndef CLEAN_MAIN_VILLAGER_ROSTER_H
#define CLEAN_MAIN_VILLAGER_ROSTER_H

#include "npc_id.h"
#include "types.h"
#include "villager_town.h"

/* The codes VillagerRoster_ForCode turns into places: 17-24 for places 0-7. */
#define VILLAGER_ROSTER_FIRST_CODE 17
/* The wide characters VillagerRoster_NameLength leaves off the end of a name. */
#define VILLAGER_ROSTER_NUL 0x0000
#define VILLAGER_ROSTER_WIDE_SPACE 0x3000
/* The longest name VillagerRoster_FindByName looks for. */
#define VILLAGER_ROSTER_NAME_CHARS 6

u8 *VillagerRoster_FindNumber(VillagerTown *town, int number);
void VillagerRoster_WakeUp(VillagerTown *town);
int VillagerRoster_IsOutside(VillagerTown *town, const NpcId *npc);
void VillagerRoster_UpdateOutdoors(VillagerTown *town, int keep_time);
int VillagerRoster_Count(VillagerTown *town);
int VillagerRoster_CountFilled(u8 *villagers);
u8 *VillagerRoster_FondestOrAny(VillagerTown *town, const void *player);
u8 *VillagerRoster_PickResident(VillagerTown *town, const NpcId *const *excluded, int count);
int VillagerRoster_PickBit(unsigned int mask, int count, int bits);
u8 *VillagerRoster_PickAny(VillagerTown *town, const NpcId *const *excluded, int count);
int VillagerRoster_FirstFree(VillagerTown *town);
u8 *VillagerRoster_ForCode(VillagerTown *town, int code);
u8 *VillagerRoster_FindByName(VillagerTown *town, const u16 *name, int length, const void *player);
int VillagerRoster_NameEquals(const u16 *a, const u16 *b, int length);
int VillagerRoster_NameLength(const u16 *name, int length);
u8 *VillagerRoster_Find(VillagerTown *town, const NpcId *npc);
u8 *VillagerRoster_At(VillagerTown *town, int index);
int VillagerRoster_IsFilled(VillagerTown *town, int index);
int VillagerRoster_IndexOf(VillagerTown *town, const NpcId *npc);
void VillagerRoster_Init(VillagerTown *town);
VillagerTown *VillagerRoster_Destruct(VillagerTown *town);
VillagerTown *VillagerRoster_Construct(VillagerTown *town);

#endif
