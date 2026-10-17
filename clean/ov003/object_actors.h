/* Overlay 3's object actors: a process (vtable 0x02239b2c, 0x50 bytes, derived from the process
 * class of autoload_2/process.h with no members of its own) that sets the town's field up for
 * overlay 9's scene actors of the town's objects (codes 0x5000-0x5021, main/town_objects.h),
 * and the list of those actors overlay 3 keeps while they exist (data_ov003_0223cef0).
 *
 * Set up (vtable slot 0), it marks the objects' footprints, empties the list, claims main's
 * building slot (main/building_taker.h), makes the countdown heap, loads the houses' three sets
 * of files (house_files.h), spawns a scene actor for every object on the scene's map
 * (ObjectActors_PlaceAll) and spawns process class 0xf. Released (slot 3) it undoes that in
 * turn. Slots 6 (each frame) and 9 (draw) do nothing; 16 and 17 are the destructors.
 *
 * Each scene actor adds itself to the list when it is made (func_ov009_0226523c) and takes
 * itself off when it goes (func_ov009_02264fb8); the list is searched by code, by tile and by
 * position. */
#ifndef CLEAN_OV003_OBJECT_ACTORS_H
#define CLEAN_OV003_OBJECT_ACTORS_H

#include "autoload_2/process.h"
#include "autoload_2/vector.h"
#include "ov009/scene_actor.h"
#include "types.h"

/* The list's length. */
#define OBJECT_ACTORS_MAX 32

typedef struct ObjectActors {
    Process process; /* 0x00 */
} ObjectActors;

void ObjectActors_ReleaseList(void);
void ObjectActors_ClearList(void);
int ObjectActors_IndexOf(SceneActor *actor);
SceneActor *ObjectActors_FindByCode(u16 code);
SceneActor *ObjectActors_At(int index);
SceneActor *ObjectActors_FindAtTile(u32 x, u32 z);
int ObjectActors_Remove(SceneActor *actor);
int ObjectActors_Add(SceneActor *actor);
SceneActor *ObjectActors_FindNear(const Vec3 *position);
int ObjectActors_IdleSetHouseModeA(int villager);
int ObjectActors_IdleSetHouseModeB(int villager);
int ObjectActors_SetNearModeA(const Vec3 *position);
int ObjectActors_SetNearModeB(const Vec3 *position);
void ObjectActors_SetPoseFlag(u8 flag);
u8 ObjectActors_PoseFlag(void);
u16 ObjectActors_Mode1Count(void);
void ObjectActors_DestroyCountdownHeap(ObjectActors *self);
void ObjectActors_CreateCountdownHeap(ObjectActors *self);
int ObjectActors_RetypeShape(ObjectActors *self, u16 *code, int x, int z);
int ObjectActors_Place(ObjectActors *self, u16 *code, int x, int z, u8 stamp);
int ObjectActors_PlaceAll(ObjectActors *self);
void ObjectActors_SetUpNothingB(ObjectActors *self);
void ObjectActors_SetUpNothingA(ObjectActors *self);
int ObjectActors_Release(ObjectActors *self);
int ObjectActors_Draw(void);
int ObjectActors_Update(void);
int ObjectActors_SetUp(ObjectActors *self);
ObjectActors *ObjectActors_DestroyAndFree(ObjectActors *self);
ObjectActors *ObjectActors_Destroy(ObjectActors *self);
ObjectActors *ObjectActors_Construct(ObjectActors *self);
void ObjectActors_New(void);

#endif
