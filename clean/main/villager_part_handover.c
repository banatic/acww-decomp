/* What a villager handed over to the player (villager_part_handover.h). */
#include "villager_part_handover.h"

#include <string.h>

#include "clean.h"
#include "item_object.h"

static_assert(offsetof(VillagerPartHandover, object) == 0x10, "object");
static_assert(offsetof(VillagerPartHandover, date) == 0x1c, "date");
static_assert(offsetof(VillagerPartHandover, byte_24) == 0x24, "byte 24");
static_assert(sizeof(VillagerPartHandover) == 0x28, "size");

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern void MI_CpuFill8(void *dst, u8 value, u32 size);

/* func_0209ae70: the record emptied, then set: an object of type 21 with no item, dated now; the
 * villager's NpcId; and `date`. */
void VillagerPartHandover_Set(VillagerPartHandover *handover, const NpcId *npc, const DateTime *date)
{
    VillagerPartHandover_Clear(handover);
    u16 item = 0xfff1;
    ItemObject_Set((ItemObject *) (void *) handover->object, VILLAGER_PART_HANDOVER_TYPE, &item, 0);
    ItemObject_StampNow((ItemObject *) (void *) handover->object, 0);
    NpcId_Copy(&handover->npc, npc);
    MI_CpuCopy8(date, &handover->date, sizeof(DateTime));
}
CLEAN_AS(func_0209ae70, VillagerPartHandover_Set)

/* func_0209aebc: whether the record holds something from the villager `npc` (a valid NpcId with
 * the same head and number). */
int VillagerPartHandover_IsFrom(VillagerPartHandover *handover, const NpcId *npc)
{
    if (ItemObject_IsInUse((ItemObject *) (void *) handover->object) == 0 || NpcId_IsValid(npc) == 0) {
        return 0;
    }
    return npc->head.id == handover->npc.head.id &&
           memcmp(npc->head.data, handover->npc.head.data, sizeof(npc->head.data)) == 0 && npc->number == handover->npc.number;
}
CLEAN_AS(func_0209aebc, VillagerPartHandover_IsFrom)

/* func_0209af04: the record emptied. */
void VillagerPartHandover_Clear(VillagerPartHandover *handover)
{
    ItemObject_Clear((ItemObject *) (void *) handover->object);
    NpcId_Clear(&handover->npc);
    handover->date = (DateTime){0};
    MI_CpuFill8(&handover->byte_24, 0, 1);
}
CLEAN_AS(func_0209af04, VillagerPartHandover_Clear)

/* func_0209af2c: the destructor. */
VillagerPartHandover *VillagerPartHandover_Destruct(VillagerPartHandover *handover)
{
    ItemObject_Destruct((ItemObject *) (void *) handover->object);
    NpcId_Destruct(&handover->npc);
    return handover;
}
CLEAN_AS(func_0209af2c, VillagerPartHandover_Destruct)

/* func_0209af44: the constructor: the parts constructed, then the record emptied (the date
 * cleared both times). */
VillagerPartHandover *VillagerPartHandover_Construct(VillagerPartHandover *handover)
{
    NpcId_Construct(&handover->npc);
    ItemObject_Construct((ItemObject *) (void *) handover->object);
    handover->date = (DateTime){0};
    NpcId_Clear(&handover->npc);
    ItemObject_Clear((ItemObject *) (void *) handover->object);
    handover->date = (DateTime){0};
    MI_CpuFill8(&handover->byte_24, 0, 1);
    return handover;
}
CLEAN_AS(func_0209af44, VillagerPartHandover_Construct)
