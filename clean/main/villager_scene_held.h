/* The item a villager scene object's villager holds (villager_scene_object.h): the item of its
 * running state entry (VillagerStatus_StateEntry, villager_state.h), found through the object's
 * town record (its vtable slot 0x64) when the record's villager is a valid one. */
#ifndef CLEAN_MAIN_VILLAGER_SCENE_HELD_H
#define CLEAN_MAIN_VILLAGER_SCENE_HELD_H

#include "types.h"

void VillagerSceneHeld_SetItem(void *object, const u16 *item);
void VillagerSceneHeld_Item(u16 *item, void *object);

#endif
