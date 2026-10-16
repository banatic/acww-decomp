/* The name of another of the town's villagers (villager_names.h). */
#include "villager_names.h"

#include "clean.h"
#include "npc_id.h"
#include "villager_pairs.h"
#include "villager_roster.h"
#include "villager_town.h"

extern u8 data_021e5a2c[]; /* the town's villagers (VillagerTown) */

extern NpcId *func_0208150c(const void *villager); /* the villager's NpcId, at 0x7a0 */
extern void *func_02137550(void *dst, u32 size);   /* clears size bytes */

static VillagerTown *VillagerNames_Town(void)
{
    return (VillagerTown *) (void *) data_021e5a2c;
}

/* The name of `other` into `dst`, when there is such a villager and its NpcId is valid. */
static void VillagerNames_Format(const u8 *other, char *dst)
{
    if (other != NULL && NpcId_IsValid(func_0208150c(other))) {
        NpcId_FormatName(func_0208150c(other), dst);
    }
}

/* func_0207ee78: the name of one of the town's villagers other than `villager`, drawn at
 * random (VillagerRoster_PickAny). */
void VillagerNames_FormatOther(u8 *villager, char *dst)
{
    const NpcId *excluded[1];
    func_02137550(excluded, sizeof(excluded));
    excluded[0] = func_0208150c(villager);
    VillagerNames_Format(VillagerRoster_PickAny(VillagerNames_Town(), excluded, 1), dst);
}
CLEAN_AS(func_0207ee78, VillagerNames_FormatOther)

/* func_0207eec4: the name of the villager `villager` gets on worst with. */
void VillagerNames_FormatWorstMatch(u8 *villager, char *dst)
{
    VillagerNames_Format(VillagerPair_WorstFor(VillagerNames_Town(), villager), dst);
}
CLEAN_AS(func_0207eec4, VillagerNames_FormatWorstMatch)

/* func_0207ef00: the name of the villager `villager` gets on best with. */
void VillagerNames_FormatBestMatch(u8 *villager, char *dst)
{
    VillagerNames_Format(VillagerPair_BestFor(VillagerNames_Town(), villager), dst);
}
CLEAN_AS(func_0207ef00, VillagerNames_FormatBestMatch)
