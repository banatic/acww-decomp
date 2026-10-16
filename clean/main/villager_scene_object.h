/* The scene object of a town villager (vtable 0x020d9e88): a scene object of class 0x020d8c64
 * (scene_object.h) with members of its own, among them a talk scene of class 0x020d9df8 at
 * 0x680 (talk_choices.h), its town record at 0x830 (town_villager.h) and its mood at 0x83c
 * (villager_mood.h). Here: three of its vtable slots and the fields at 0x640 to 0x648.
 *
 * Byte 0x640 is the town event going on when the object started (VillagerTown_CurrentEvent,
 * 11 for none, and 11 while others share the session). */
#ifndef CLEAN_MAIN_VILLAGER_SCENE_OBJECT_H
#define CLEAN_MAIN_VILLAGER_SCENE_OBJECT_H

#include "types.h"

#define VILLAGER_SCENE_OBJECT_NO_EVENT 11

u8 VillagerSceneObject_Event(u8 *object);
void VillagerSceneObject_SetEvent(u8 *object);
u32 VillagerSceneObject_HasWord644(void *object);
int VillagerSceneObject_VfuncBc(void *object);
int VillagerSceneObject_VfuncB8(void *object);
int VillagerSceneObject_VfuncB4(void *object);
u8 VillagerSceneObject_Byte648(u8 *object);
void VillagerSceneObject_SetByte648(u8 *object, u8 value);
u32 VillagerSceneObject_Word644(u32 *object);
void VillagerSceneObject_SetWord644(u32 *object, u32 value);
int VillagerSceneObject_HasByte838(u8 *object);
void VillagerSceneObject_ClearByte838(u8 *object);
void VillagerSceneObject_SetByte838(u8 *object);

#endif
