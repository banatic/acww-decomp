/* A villager's visit to the player's house, as the player's record keeps it (villager_house_visit.h). */
#include "villager_house_visit.h"

#include <string.h>

#include "clean.h"
#include "villager_errand.h"

static_assert(offsetof(VillagerHouseVisit, object) == 0x10, "object");
static_assert(offsetof(VillagerHouseVisit, date) == 0x1c, "date");
static_assert(offsetof(VillagerHouseVisit, rating) == 0x24, "rating");
static_assert(sizeof(VillagerHouseVisit) == 0x28, "size");

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern void MI_CpuFill8(void *dst, u8 value, u32 size);

/* func_0209ae70: the record emptied, then set: an errand of type 21 with no item, dated now; the
 * villager's NpcId; and `date`, the time agreed. */
void VillagerHouseVisit_Set(VillagerHouseVisit *visit, const NpcId *npc, const DateTime *date)
{
    VillagerHouseVisit_Clear(visit);
    u16 item = 0xfff1;
    VillagerErrand_Set((VillagerErrand *) (void *) visit->object, VILLAGER_HOUSE_VISIT_TYPE, &item, 0);
    VillagerErrand_StampNow((VillagerErrand *) (void *) visit->object, 0);
    NpcId_Copy(&visit->npc, npc);
    MI_CpuCopy8(date, &visit->date, sizeof(DateTime));
}
CLEAN_AS(func_0209ae70, VillagerHouseVisit_Set)

/* func_0209aebc: whether the record holds a visit by the villager `npc` (a valid NpcId with the
 * same town and number). */
int VillagerHouseVisit_IsFrom(VillagerHouseVisit *visit, const NpcId *npc)
{
    if (VillagerErrand_IsInUse((VillagerErrand *) (void *) visit->object) == 0 || NpcId_IsValid(npc) == 0) {
        return 0;
    }
    return npc->town.number == visit->npc.town.number &&
           memcmp(npc->town.name, visit->npc.town.name, sizeof(npc->town.name)) == 0 && npc->number == visit->npc.number;
}
CLEAN_AS(func_0209aebc, VillagerHouseVisit_IsFrom)

/* func_0209af04: the record emptied. */
void VillagerHouseVisit_Clear(VillagerHouseVisit *visit)
{
    VillagerErrand_Clear((VillagerErrand *) (void *) visit->object);
    NpcId_Clear(&visit->npc);
    visit->date = (DateTime){0};
    MI_CpuFill8(&visit->rating, 0, 1);
}
CLEAN_AS(func_0209af04, VillagerHouseVisit_Clear)

/* func_0209af2c: the destructor. */
VillagerHouseVisit *VillagerHouseVisit_Destruct(VillagerHouseVisit *visit)
{
    VillagerErrand_Destruct((VillagerErrand *) (void *) visit->object);
    NpcId_Destruct(&visit->npc);
    return visit;
}
CLEAN_AS(func_0209af2c, VillagerHouseVisit_Destruct)

/* func_0209af44: the constructor: the parts constructed, then the record emptied (the date
 * cleared both times). */
VillagerHouseVisit *VillagerHouseVisit_Construct(VillagerHouseVisit *visit)
{
    NpcId_Construct(&visit->npc);
    VillagerErrand_Construct((VillagerErrand *) (void *) visit->object);
    visit->date = (DateTime){0};
    NpcId_Clear(&visit->npc);
    VillagerErrand_Clear((VillagerErrand *) (void *) visit->object);
    visit->date = (DateTime){0};
    MI_CpuFill8(&visit->rating, 0, 1);
    return visit;
}
CLEAN_AS(func_0209af44, VillagerHouseVisit_Construct)
