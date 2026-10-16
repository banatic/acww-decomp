/* The town villager scene object (vtable 0x020d9e88, villager_scene_object.h): its
 * constructor, destructors and the vtable slots it fills itself.
 *
 * Beyond the members of its base class (scene_object.h) it holds its clothes at 0x64c
 * (villager_clothes.h), its talk scene at 0x680 (villager_talk_scene.h), a random byte (0 or
 * 1) at 0x824 drawn when it starts, the link to its heap8 slot at 0x828 (pool_link.h, the
 * model's heap), its town record at 0x830 (town_villager.h) with that record's state entry at
 * 0x834 (villager_status.h), and its mood at 0x83c (villager_mood.h). Its person (the code at
 * 0xea) is one of kind 0xe; the record is the town's villager at the object's person index.
 *
 * Its vtable slots, beyond the base class's:
 * - 0x00 start, 0x04 init, 0x0c leave, 0x10 the deletion check, 0x40 and 0x44 destructors;
 * - 0x64 the town record; 0x6c and 0x70 the names of its texture and model files;
 * - 0x74 its name into a string; 0x78 its sort (the personality group);
 * - 0x7c, 0x80, 0x84: the sound of an action's start (always played; nothing to do once
 *   played; the villager's number);
 * - 0x88 told of frame 8 of an animation with an item: clothes of that item are put on;
 * - 0xa4 a mood asked for; 0xa8 to 0xb0 constant answers. */
#ifndef CLEAN_MAIN_VILLAGER_SCENE_SLOTS_H
#define CLEAN_MAIN_VILLAGER_SCENE_SLOTS_H

#include "types.h"

int VillagerSceneObject_Leave(u8 *object);
int VillagerSceneObject_CanDelete(u8 *object);
int VillagerSceneObject_Start(u8 *object);
int VillagerSceneObject_LoadModel(u8 *object);
int VillagerSceneObject_Init(u8 *object);
void VillagerSceneObject_TakeClothes(u8 *object, u16 *item, int share);
int VillagerSceneObject_VfuncB0(void *object);
int VillagerSceneObject_VfuncAc(void *object);
int VillagerSceneObject_VfuncA8(void *object);
void VillagerSceneObject_AskMood(u8 *object, int which, int units);
u32 VillagerSceneObject_Record(u32 *object);
char *VillagerSceneObject_ModelFile(void *object);
char *VillagerSceneObject_TextureFile(void *object);
int VillagerSceneObject_ActionSound(u8 *object);
void VillagerSceneObject_ActionSoundPlayed(void *object);
int VillagerSceneObject_HasActionSound(void *object);
int VillagerSceneObject_Sort(u8 *object);
void VillagerSceneObject_NameInto(u8 *object, char *name);
int VillagerSceneObject_NpcNumber(u8 *object);
void VillagerSceneObject_FindRecord(u8 *object);
u8 *VillagerSceneObject_DestructBody(u8 *object);
u8 *VillagerSceneObject_DestructDelete(u8 *object);
u8 *VillagerSceneObject_Destruct(u8 *object);
u8 *VillagerSceneObject_Construct(u8 *object);

#endif
