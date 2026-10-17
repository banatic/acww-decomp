/* The scene actor as a process (scene_actor.h, autoload_2/process.h): made by its profile
 * (SceneActor_Create) and set up by vtable slot 0x00 (SceneActor_Init); each frame the check
 * before it runs (slot 0x1c, SceneActor_CanRun) does the frame's work, the slot told the run's
 * outcome (slot 0x20, SceneActor_AfterRun) moves its sound and its door flags on, and the check
 * before drawing (slot 0x28, SceneActor_CanDraw) draws its model; the check before deleting
 * (slot 0x10, SceneActor_CanDelete) takes its parts down. What its character's record
 * (data_020d1f24) tells of it is read here too.
 *
 * Set-up: it joins overlay 3's list of object actors, takes its tile and its id from its
 * position, its code from the spawn's parameter, loads its building's files (scene_actor_files.h)
 * and its model, its bounds, its first animation and mode (SceneActor_StartModel), its model's
 * matrix, its shadows, its doors and the pen's faces (scene_actor_area.h) and its lights
 * (main/building_lights.h); its talk point is the stand point moved back by 4.0 along z.
 *
 * Each frame: its sound on, a building 0x501d takes the mode main has recorded for it, its view
 * box, the talk machine (except in scene 0x2c), its mode, the pen's faces (except in scene
 * 0x2c), its lights (on at night when vtable slot 0x8c says so, flashing as byte 5 of its
 * record says) and the player's way out of it (SceneActor_UpdateExit). */
#ifndef CLEAN_OV009_SCENE_ACTOR_LIFE_H
#define CLEAN_OV009_SCENE_ACTOR_LIFE_H

#include "autoload_2/matrix.h"
#include "scene_actor.h"

/* The render state handed to the model's node callbacks (NitroSystem's NNSG3dRS, the parts
 * used here). */
typedef struct SceneActorRenderState {
    const u8 *command; /* 0x00: the model's command being run; byte 1 of NODEDESC is its node */
    const u8 *object;  /* 0x04: the render object; its word 0x2c is the model object's user */
    u8 unk_08[0x24 - 0x08];
    void *node_callback; /* 0x24: the callback of command 6 (NODEDESC) */
    u8 unk_28[0x92 - 0x28];
    u8 node_timing; /* 0x92: when it runs (2: after the command) */
} SceneActorRenderState;

int SceneActor_IsNight(SceneActor *actor);
int SceneActor_AsksToVisit(SceneActor *actor);
int SceneActor_LightsOn(SceneActor *actor);
int SceneActor_Kind(SceneActor *actor);
int SceneActor_ViewRangeZAhead(const SceneActor *actor);
int SceneActor_ViewRangeZBehind(SceneActor *actor);
int SceneActor_ViewRangeX(SceneActor *actor);
void SceneActor_UpdateModelMatrix(SceneActor *actor, Mtx43 *out);
void SceneActor_PivotMatrix(SceneActor *actor, Mtx43 *out);
void SceneActor_UpdateExit(SceneActor *actor);
void SceneActor_StartModel(SceneActor *actor);
void SceneActor_SetBounds(SceneActor *actor);
int SceneActor_CanDelete(SceneActor *actor);
int SceneActor_CanDraw(SceneActor *actor);
void SceneActor_AfterRun(SceneActor *actor, int status);
int SceneActor_CanRun(SceneActor *actor);
int SceneActor_Init(SceneActor *actor);
int SceneActor_Slot70(SceneActor *actor);
void *SceneActor_Destruct(SceneActor *actor);
SceneActor *SceneActor_DestructDelete(SceneActor *actor);
void *SceneActor_DestructComplete(SceneActor *actor);
void *SceneActor_Construct(SceneActor *actor);
void *SceneActor_ConstructBase(SceneActor *actor);
void SceneActor_SetNodeHook(SceneActorRenderState *state);
void SceneActor_AfterNode(SceneActorRenderState *state);
void SceneActor_Slot60(SceneActor *actor);
void SceneActor_Create(void);
SceneActor *SceneActor_ReceiverDestructDelete(void *receiver);
void *SceneActor_ReceiverDestructComplete(void *receiver);

#endif
