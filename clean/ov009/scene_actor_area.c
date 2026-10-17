/* The scene actor's doors and the pen's faces (scene_actor_area.h). */
#include "scene_actor_area.h"

#include <stdint.h>

#include "autoload_2/approach.h" /* Math_AbsDiff16 */
#include "autoload_2/heap.h"     /* Heap_Alloc */
#include "clean.h"
#include "itcm/vector.h"             /* Vec_Add */
#include "main/actor.h"              /* Actor */
#include "main/building_shapes.h"    /* BuildingShapes_* */
#include "main/collision_area.h"     /* CollisionArea */
#include "main/collision_triangle.h" /* CollisionTriangle_Distance, CollisionTriangle_LineHit */
#include "main/globe.h"              /* Globe_Unbend */
#include "main/scene_query.h"        /* SceneQuery_FieldObject */
#include "main/session_players.h"    /* SessionPlayers_ActorOf */
#include "main/touch_pick_shapes.h"  /* TouchPick_*, TouchPickFace */
#include "ov003/object_actors.h"     /* ObjectActors_IndexOf */
#include "scene_actor_life.h"        /* SceneActor_Kind */

static_assert(offsetof(SceneActorArea, owner) == 0x4c, "area owner");
static_assert(offsetof(SceneActorArea, kind) == 0x50, "area kind");
static_assert(sizeof(SceneActorArea) == 0x54, "area size");
static_assert(sizeof(CollisionArea) == offsetof(SceneActorArea, owner), "an area starts with a collision area");
static_assert(offsetof(CollisionTriangle, normal) == offsetof(SceneActorArea, facing_x), "area facing");
static_assert(sizeof(TouchPickFace) == 0x44, "pick face size");
static_assert(offsetof(SceneActor, shadows) == 0x284, "shadows");
static_assert(offsetof(SceneActor, faces) == 0x288, "faces");
static_assert(offsetof(Actor, profile) == 0x0c && offsetof(Actor, angle) == 0x8c && offsetof(Actor, speed) == 0x98,
              "actor fields");

/* The class of the player's actor (Actor.profile). */
#define SCENE_ACTOR_PLAYER_PROFILE 9
/* This console's player. */
#define SCENE_ACTOR_AREA_PLAYER 4
/* SceneActorDoor_IsEntered: how far past the actor's radius the triangle may be (0.4), how far
 * the player's direction may be from the stand point's, and how far ahead the line it casts
 * reaches (2.0). */
#define SCENE_ACTOR_DOOR_SLACK 0x666
#define SCENE_ACTOR_DOOR_ANGLE 0x1100
#define SCENE_ACTOR_DOOR_AHEAD 0x2000
/* SceneActorDoor_Touch: the speed from which a touch is a walk in. */
#define SCENE_ACTOR_RUN_IN_SPEED 0x200
/* The areas' reach (3.0) and the faces' kind (touch_pick.h). */
#define SCENE_ACTOR_AREA_REACH 0x3000
#define SCENE_ACTOR_FACE_KIND 7

/* The class of the actor's areas. */
extern const u8 data_ov009_022658c0[];
/* The heap the areas and faces are made on. */
extern Heap *data_021c9b1c;
/* NitroSDK's MTX_MultVec43: `vec` moved by `m`. */
extern void MTX_MultVec43(const Vec3 *vec, const Mtx43 *m, Vec3 *dst);
extern fx32 FX_MulFunc(fx32 a, fx32 b);

static CollisionArea *door_collision(SceneActorArea *area)
{
    return (CollisionArea *) (void *) area;
}

static TouchPick *area_pick(void)
{
    return (TouchPick *) (uintptr_t) SceneQuery_FieldObject();
}

/* func_ov009_02264264: whether `other`, at `position` with `radius`, goes in at the area: it is
 * this console's player, the area's triangle is in front of it no further than its radius and
 * 0.4 more, the owner has a stand point whose direction is within 0x1100 of the player's, and
 * the line from its position (raised by its radius) to 2.0 behind it along the area's facing
 * meets the triangle. */
int SceneActorDoor_IsEntered(SceneActorArea *area, const Vec3 *position, fx32 radius, void *other)
{
    Actor *actor = other;
    if (actor == NULL || area->owner == NULL) {
        return 0;
    }
    if (actor->profile != SCENE_ACTOR_PLAYER_PROFILE || SessionPlayers_ActorOf(SCENE_ACTOR_AREA_PLAYER) != other) {
        return 0;
    }
    fx32 distance = CollisionTriangle_Distance(&door_collision(area)->triangle, position);
    if (distance < 0 || distance > radius + SCENE_ACTOR_DOOR_SLACK) {
        return 0;
    }
    Vec3 point;
    s16 angle;
    if (!SceneActor_GetStandPoint(area->owner, &point, &angle)) {
        return 0;
    }
    if (Math_AbsDiff16(angle, actor->angle[1]) > SCENE_ACTOR_DOOR_ANGLE) {
        return 0;
    }
    Vec3 start = *position;
    start.y += radius;
    Vec3 end = start;
    end.x -= FX_MulFunc(area->facing_x, SCENE_ACTOR_DOOR_AHEAD);
    end.z -= FX_MulFunc(area->facing_z, SCENE_ACTOR_DOOR_AHEAD);
    Vec3 hit;
    return CollisionTriangle_LineHit(&door_collision(area)->triangle, &hit, &start, &end) != 0;
}
CLEAN_AS(func_ov009_02264264, SceneActorDoor_IsEntered)

/* func_ov009_02264328 (the area's slot 0x10, told of an actor near it): when the actor goes in
 * there, the owner is marked SCENE_ACTOR_FLAG_AT_DOOR, and SCENE_ACTOR_FLAG_RUN_IN too when the
 * actor's speed is 0x200 or more. */
void SceneActorDoor_Touch(SceneActorArea *area, const Vec3 *position, void *other, fx32 radius)
{
    if (!SceneActorDoor_IsEntered(area, position, radius, other)) {
        return;
    }
    area->owner->flags_235 |= SCENE_ACTOR_FLAG_AT_DOOR;
    if (((Actor *) other)->speed >= SCENE_ACTOR_RUN_IN_SPEED) {
        area->owner->flags_235 |= SCENE_ACTOR_FLAG_RUN_IN;
    }
}
CLEAN_AS(func_ov009_02264328, SceneActorDoor_Touch)

/* func_ov009_02264370: an area's constructor: the collision area's, then its class's vtable. */
SceneActorArea *SceneActorDoor_Construct(SceneActorArea *area)
{
    CollisionArea_Construct(door_collision(area));
    door_collision(area)->triangle.vtable = data_ov009_022658c0;
    return area;
}
CLEAN_AS(func_ov009_02264370, SceneActorDoor_Construct)

/* func_ov009_02264398: its pen's faces forgotten, its areas taken out of the field's list and
 * forgotten, and the count cleared.
 * BUG: the loop steps two areas at a time, so only every other area leaves the list (and has
 * its owner cleared); the others stay in it after the actor is gone. */
void SceneActor_ReleaseAreas(SceneActor *actor)
{
    if (actor->faces != NULL) {
        actor->faces = NULL;
    }
    if (actor->areas != NULL) {
#ifdef BUGFIX
        const u32 step = 1;
#else
        const u32 step = 2;
#endif
        for (u32 i = 0; i < actor->area_count; i += step) {
            SceneActorArea *area = &actor->areas[i];
            CollisionArea_Remove(door_collision(area));
            area->owner = NULL;
        }
        actor->areas = NULL;
    }
    actor->area_count = 0;
}
CLEAN_AS(func_ov009_02264398, SceneActor_ReleaseAreas)

/* func_ov009_022643f4: while it is in view, each of its faces added to the pen's list. */
void SceneActor_AddPickFaces(SceneActor *actor)
{
    if (actor->flags_235 & SCENE_ACTOR_FLAG_OUT_OF_VIEW) {
        return;
    }
    if (actor->faces == NULL) {
        return;
    }
    for (TouchPickFace *face = actor->faces; face < actor->faces + actor->area_count; face++) {
        TouchPick_AddFace(area_pick(), face);
    }
}
CLEAN_AS(func_ov009_022643f4, SceneActor_AddPickFaces)

/* func_ov009_02264444: an area and a face for each triangle of its building's shape (none
 * without a shape), both arrays on the scene's heap. A triangle's corners are moved by
 * `matrix` (where the actor is drawn) and taken back to the map for the face; the area's are
 * its position plus the corners. The faces have kind 7 and the actor's index in overlay 3's
 * list, the areas the actor and its kind.
 * REQUIRES: the heap has room for both arrays (the areas are written through even when the
 * allocation failed). */
void SceneActor_BuildAreas(SceneActor *actor, const Mtx43 *matrix)
{
    actor->area_count = 0;
    BuildingShapeEntry *shape = BuildingShapes_Of(&actor->code);
    if (shape == NULL) {
        return;
    }
    actor->area_count = (u8) BuildingShapes_TriangleCount(shape);
    if (actor->area_count == 0) {
        return;
    }
    actor->faces = Heap_Alloc(data_021c9b1c, actor->area_count * (int) sizeof(TouchPickFace));
    actor->areas = Heap_Alloc(data_021c9b1c, actor->area_count * (int) sizeof(SceneActorArea));
    SceneActorArea *area = actor->areas;
    TouchPickFace *face = actor->faces;
    u8 index = (u8) ObjectActors_IndexOf(actor);
    for (u32 i = 0; i < actor->area_count; i++, area++, face++) {
        Vec3 corner[3];
        if (BuildingShapes_Triangle(shape, &corner[0], &corner[1], &corner[2], i) == 0) {
            continue;
        }
        Vec3 drawn[3];
        Vec3 placed[3];
        for (int k = 0; k < 3; k++) {
            SceneActor_MapPoint(&drawn[k], &corner[k], matrix);
        }
        for (int k = 0; k < 3; k++) {
            Vec_Add(&placed[k], &actor->position, &corner[k]);
        }
        if (face != NULL) {
            face = TouchPickFace_Construct(face);
        }
        TouchPick_SetFaceAndAdd(area_pick(), face, &drawn[0], &drawn[1], &drawn[2], SCENE_ACTOR_FACE_KIND, index);
        if (area != NULL) {
            area = SceneActorDoor_Construct(area);
        }
        area->owner = actor;
        area->kind = SceneActor_Kind(actor);
        CollisionArea_Set(door_collision(area), &placed[0], &placed[1], &placed[2], SCENE_ACTOR_AREA_REACH);
        CollisionArea_Add(door_collision(area));
    }
}
CLEAN_AS(func_ov009_02264444, SceneActor_BuildAreas)

/* func_ov009_02265660: `point` moved by `matrix` (into the drawn world) and taken back to the
 * map. */
void SceneActor_MapPoint(Vec3 *out, const Vec3 *point, const Mtx43 *matrix)
{
    Vec3 moved;
    MTX_MultVec43(point, matrix, &moved);
    Globe_Unbend(out, &moved);
}
CLEAN_AS(func_ov009_02265660, SceneActor_MapPoint)
