/* The scene actor's doors and the pen's faces (scene_actor.h). Its building's shape
 * (main/building_shapes.h) ends in triangles; for each, the actor keeps
 *
 * - an area (SceneActorArea, a collision area of main/collision_area.h with its own class,
 *   vtable data_ov009_022658c0) at the triangle's corners on the map, which the field's
 *   collision tells of the actors that move near it (SceneActorDoor_Touch): this console's
 *   player touching it while facing the actor's stand point marks the actor
 *   SCENE_ACTOR_FLAG_AT_DOOR (and SCENE_ACTOR_FLAG_RUN_IN when moving fast), which its mode 0
 *   takes as a wish to go in;
 * - a face for the pen (main/touch_pick_shapes.h, kind 7 and the actor's index in overlay 3's
 *   list) at the corners as drawn, registered each frame while it is in view.
 *
 * Positions are 20.12 fixed point. */
#ifndef CLEAN_OV009_SCENE_ACTOR_AREA_H
#define CLEAN_OV009_SCENE_ACTOR_AREA_H

#include "autoload_2/matrix.h"
#include "autoload_2/vector.h"
#include "scene_actor.h"

int SceneActorDoor_IsEntered(SceneActorArea *area, const Vec3 *position, fx32 radius, void *other);
void SceneActorDoor_Touch(SceneActorArea *area, const Vec3 *position, void *other, fx32 radius);
SceneActorArea *SceneActorDoor_Construct(SceneActorArea *area);
void SceneActor_ReleaseAreas(SceneActor *actor);
void SceneActor_AddPickFaces(SceneActor *actor);
void SceneActor_BuildAreas(SceneActor *actor, const Mtx43 *matrix);
void SceneActor_MapPoint(Vec3 *out, const Vec3 *point, const Mtx43 *matrix);

#endif
