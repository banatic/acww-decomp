/* The town object actor as a process (town_object_actor.h, autoload_2/process.h): made by its profile
 * (TownObjectActor_Create) and set up by vtable slot 0x00 (TownObjectActor_Init); each frame the check
 * before it runs (slot 0x1c, TownObjectActor_CanRun) does the frame's work, the slot told the run's
 * outcome (slot 0x20, TownObjectActor_AfterRun) moves its sound and its door flags on, and the check
 * before drawing (slot 0x28, TownObjectActor_CanDraw) draws its model; the check before deleting
 * (slot 0x10, TownObjectActor_CanDelete) takes its parts down. What its object's record
 * (data_020d1f24) tells of it is read here too.
 *
 * Set-up: it joins overlay 3's list of object actors, takes its tile and its id from its
 * position, its code from the spawn's parameter, loads its building's files (town_object_actor_files.h)
 * and its model, its bounds, its first animation and mode (TownObjectActor_StartModel), its model's
 * matrix, its shadows, its doors and the pen's faces (town_object_actor_area.h) and its lights
 * (main/building_lights.h); its talk point is the stand point moved back by 4.0 along z.
 *
 * Each frame: its sound on, a building 0x501d takes the mode main has recorded for it, its view
 * box, the entry machine (except in scene 0x2c), its mode, the pen's faces (except in scene
 * 0x2c), its lights (on at night when vtable slot 0x8c says so, flashing as byte 5 of its
 * record says) and the player's way out of it (TownObjectActor_UpdateExit). */
#ifndef CLEAN_OV009_TOWN_OBJECT_ACTOR_LIFE_H
#define CLEAN_OV009_TOWN_OBJECT_ACTOR_LIFE_H

#include "main/g3d_render.h"
#include "autoload_2/matrix.h"
#include "town_object_actor.h"

int TownObjectActor_IsNight(TownObjectActor *actor);
int TownObjectActor_IsOpen(TownObjectActor *actor);
int TownObjectActor_LightsOn(TownObjectActor *actor);
int TownObjectActor_Kind(TownObjectActor *actor);
int TownObjectActor_ViewRangeZAhead(const TownObjectActor *actor);
int TownObjectActor_ViewRangeZBehind(TownObjectActor *actor);
int TownObjectActor_ViewRangeX(TownObjectActor *actor);
void TownObjectActor_UpdateModelMatrix(TownObjectActor *actor, Mtx43 *out);
void TownObjectActor_PivotMatrix(TownObjectActor *actor, Mtx43 *out);
void TownObjectActor_UpdateExit(TownObjectActor *actor);
void TownObjectActor_StartModel(TownObjectActor *actor);
void TownObjectActor_SetBounds(TownObjectActor *actor);
int TownObjectActor_CanDelete(TownObjectActor *actor);
int TownObjectActor_CanDraw(TownObjectActor *actor);
void TownObjectActor_AfterRun(TownObjectActor *actor, int status);
int TownObjectActor_CanRun(TownObjectActor *actor);
int TownObjectActor_Init(TownObjectActor *actor);
int TownObjectActor_Slot70(TownObjectActor *actor);
void *TownObjectActor_Destruct(TownObjectActor *actor);
TownObjectActor *TownObjectActor_Delete(TownObjectActor *actor);
void *TownObjectActor_DestructComplete(TownObjectActor *actor);
void *TownObjectActor_Construct(TownObjectActor *actor);
void *TownObjectActor_ConstructBase(TownObjectActor *actor);
void TownObjectActor_SetNodeHook(G3dRenderState *state);
void TownObjectActor_AfterNode(G3dRenderState *state);
void TownObjectActor_Slot60(TownObjectActor *actor);
void TownObjectActor_Create(void);
TownObjectActor *TownObjectActor_ReceiverDelete(void *receiver);
void *TownObjectActor_ReceiverDestructComplete(void *receiver);

#endif
