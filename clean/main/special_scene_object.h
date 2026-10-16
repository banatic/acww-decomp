/* The scene object class with vtable 0x020da088 (include/cpp/main/Obj_020da088.h): a scene
 * object of class 0x020d8c64 (obj_020d8c64.h, scene_object.h) for a person of kind 0xd (a
 * special character, npc_lookup.h), from which the overlays derive their characters' objects.
 *
 * Its own members: the link to its heap4 slot at 0x640 (pool_link.h, the model's heap), the
 * radius and height of its body at 0x648 and 0x64c (1.0 and 2.0 from its init), and at 0x650
 * a byte set once its action-start sound has played.
 *
 * Its vtable slots, beyond the base class's:
 * - 0x00 start, 0x04 init, 0x0c leave, 0x10 the deletion check, 0x40 and 0x44 destructors;
 * - 0x74 its name into a string; 0x78 its sort (Lookups_KindDFirst of its person);
 * - 0x7c, 0x80, 0x84: the sound of an action's start: played unless the field is the rooms'
 *   (data_020e54a8 1) and it has played already; noted as played; the sound, 0xc8 plus the
 *   person's index;
 * - 0xa8 the speed scale of its animation player (data_021c30ac). */
#ifndef CLEAN_MAIN_SPECIAL_SCENE_OBJECT_H
#define CLEAN_MAIN_SPECIAL_SCENE_OBJECT_H

#include "types.h"

u32 *SpecialSceneObject_AnimSpeed(void *object);
u16 SpecialSceneObject_ActionSound(const void *object);
void SpecialSceneObject_ActionSoundPlayed(u8 *object);
int SpecialSceneObject_HasActionSound(u8 *object);
int SpecialSceneObject_Sort(u8 *object);
void SpecialSceneObject_NameInto(char *object, char *name);
int SpecialSceneObject_Leave(void *object);
int SpecialSceneObject_CanDelete(void *object);
int SpecialSceneObject_Start(void *object);
int SpecialSceneObject_Init(void *object);
void SpecialSceneObject_SetBodySize(u8 *object, u32 radius, u32 height);
int SpecialSceneObject_LoadModel(u8 *object);
void *SpecialSceneObject_DestructBody(void *object);
void *SpecialSceneObject_DestructDelete(void *object);
void *SpecialSceneObject_Destruct(void *object);

#endif
