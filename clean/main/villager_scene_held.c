/* The item a villager scene object's villager holds (villager_scene_held.h). */
#include "villager_scene_held.h"

#include "clean.h"
#include "npc_id.h"
#include "town_villager.h"
#include "villager_state.h"
#include "villager_status.h"

#define VILLAGER_SCENE_HELD_NO_ITEM 0xfff1
/* The scene object's virtual function that gives its villager's town record, or 0. */
#define VILLAGER_SCENE_HELD_SLOT_RECORD 0x64

/* The object's town record, asked of its vtable each time as the game does. */
static u8 *held_record(void *object)
{
    const u8 *vtable = *(const u8 *const *) object;
    u32 code = *(const u32 *) (const void *) (vtable + VILLAGER_SCENE_HELD_SLOT_RECORD);
    return (u8 *) (uintptr_t) ((u32 (*)(void *))(uintptr_t) code)(object);
}

/* The state entry of the object's villager when it has a record of a valid villager with an
 * entry, else 0. The record is asked for once per step, as the game does. */
static VillagerState *held_entry(void *object)
{
    if (held_record(object) == NULL) {
        return NULL;
    }
    if (NpcId_IsValid(TownVillager_NpcId(held_record(object))) == 0) {
        return NULL;
    }
    return VillagerStatus_StateEntry(held_record(object));
}

/* func_0202e0c8: the item the villager holds set to `*item` (nothing without an entry). */
void VillagerSceneHeld_SetItem(void *object, const u16 *item)
{
    if (held_entry(object) == NULL) {
        return;
    }
    VillagerState_SetItem(VillagerStatus_StateEntry(held_record(object)), item);
}
CLEAN_AS(func_0202e0c8, VillagerSceneHeld_SetItem)

/* func_0202e118: the item the villager holds into `*item`, 0xfff1 without an entry. */
void VillagerSceneHeld_Item(u16 *item, void *object)
{
    *item = VILLAGER_SCENE_HELD_NO_ITEM;
    if (held_entry(object) == NULL) {
        return;
    }
    *item = *VillagerState_Item(VillagerStatus_StateEntry(held_record(object)));
}
CLEAN_AS(func_0202e118, VillagerSceneHeld_Item)
