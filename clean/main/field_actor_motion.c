/* The field actor's moves and contacts (field_actor.h): acting on what is ahead with the tool
 * (overlay 3 outdoors, overlay 4 indoors), how fast it walks, its speed, lean and yaw, moving
 * with and without its collider, following the position another console reports, its shadow,
 * and its contact bodies (field_actor_parts.h) that other objects touch. */
#include "field_actor.h"

#include <assert.h>
#include <stddef.h>
#include <stdint.h>

#include "autoload_2/approach.h"
#include "autoload_2/fx_math.h"
#include "autoload_2/vector.h"
#include "clean.h"
#include "field_actor_parts.h"
#include "main/session.h"
#include "collision_query.h"
#include "event_queue.h"
#include "field_body.h"
#include "field_collision.h"
#include "ov004/field_actor_rooms.h"
#include "scene_kinds.h"
#include "scene_object_base.h"
#include "scene_query.h"
#include "touch_pick_shapes.h"

static_assert(offsetof(FieldActor, position) == 0x5c, "position");
static_assert(offsetof(FieldActor, yaw) == 0x8e, "yaw");
static_assert(offsetof(FieldActor, unk_140) == 0x140, "aim at a point ahead");
static_assert(offsetof(FieldActor, aim_point) == 0x158, "aim point");
static_assert(offsetof(FieldActor, aim_mode) == 0x170, "aim mode");
static_assert(offsetof(FieldActor, start_position) == 0x6f4, "start position");
static_assert(offsetof(FieldActor, state) == 0x7f0, "state");

/* The session (main/session.h). */
extern NetSession *data_020ccf94;
/* The scene: 0 outdoors (overlay 3), 1 indoors (overlay 4). */
extern u8 data_020e54a8;
/* The reach of each tool (FieldActor_InToolReach). */
extern const int data_020c766c[];
/* Per state: nonzero for a contact with flag 2. */
extern const u8 data_020c798c[];
/* How far ahead (0.8) a point ahead is aimed at. */
extern const fx32 data_020d72f8;

/* An angle a tool reaches to either side of the yaw (60 degrees). */
#define TOOL_REACH_ANGLE 0x2aaa
/* The fastest walk (20.12), what is too slow to walk, and the limits against a wall ahead and on
 * the collider's flag 3. */
#define WALK_SPEED_MAX 0x6e2
#define WALK_SPEED_MIN 0x108
#define WALK_SPEED_BLOCKED 0x245
#define WALK_SPEED_COLLIDER_3 0x307
/* The collider's and the contact body's size and height. */
#define COLLIDER_SIZE 0xfd7
#define CONTACT_HEIGHT 0x2800
#define SHADOW_LIFT 0xb33

extern int FX_MulFunc(int a, int b);

/* A temporary collider (func_02032c64 makes it, func_02032c50 destroys it). */
typedef struct FieldActorCollider {
    u32 words[0x34 / 4];
} FieldActorCollider;

/* The byte `offset` into the actor. */
static u8 *field_actor_motion_at(FieldActor *actor, u32 offset)
{
    return (u8 *) actor + offset;
}

static int field_actor_motion_sub32(int a, int b)
{
    return (int) ((u32) a - (u32) b);
}

static int field_actor_motion_add32(int a, int b)
{
    return (int) ((u32) a + (u32) b);
}

/* The virtual function at `offset` in the C++ object's vtable. */
static u32 field_actor_motion_virtual(const void *object, u32 offset)
{
    u32 vtable = *(const u32 *) object;
    return *(const u32 *) (uintptr_t) (vtable + offset);
}

typedef int (*FieldActorPickedMethod)(void *object, FieldActor *actor);

/* ---- Acting with the tool */

/* func_02010004: the actor acts with `tool` on what is at its aim: indoors (scene exactly 1)
 * through func_ov004_02225fb8 (mode 0), else FieldActor_TryTarget; their answer. */
int FieldActor_TryTargetInScene(FieldActor *actor, int tool)
{
    if (data_020e54a8 == 1) {
        return FieldActorRooms_TryTarget(actor, tool, 0);
    }
    return FieldActor_TryTarget(actor, tool);
}
CLEAN_AS(func_02010004, FieldActor_TryTargetInScene)

/* func_02010030: the same for the tool held: func_ov004_02225ef8 or FieldActor_TryTool. */
int FieldActor_TryToolInScene(FieldActor *actor)
{
    if (data_020e54a8 == 1) {
        return FieldActorRooms_TryTool(actor);
    }
    return FieldActor_TryTool(actor);
}
CLEAN_AS(func_02010030, FieldActor_TryToolInScene)

/* func_0201005c: whether `point` is in reach of `tool`: nearer (on the ground) to the start
 * position than twice the tool's reach, and less than 60 degrees from the yaw.
 * QUIRK: the reach is doubled by shifts that keep only its low 19 bits. */
int FieldActor_InToolReach(FieldActor *actor, const Vec3 *point, int tool)
{
    int reach = (int) ((u32) data_020c766c[tool] << 13) >> 12;
    if (Vec_DistanceXZ(&actor->start_position, point) >= reach) {
        return 0;
    }
    int dx = field_actor_motion_sub32(point->x, actor->start_position.x);
    int dz = field_actor_motion_sub32(point->z, actor->start_position.z);
    if (Math_AbsDiff16(Math_Atan2(dx, dz), actor->yaw) >= TOOL_REACH_ANGLE) {
        return 0;
    }
    return 1;
}
CLEAN_AS(func_0201005c, FieldActor_InToolReach)

/* func_02010538: what the actor of this console does this frame; 1 when it did something.
 * Nothing while func_0203e31c is set or with flag 0x13. On an act (FieldActor_Act), the object
 * picked (0x13c) goes to func_0203e0e0; then, with none picked, func_0203ef5c decides; with one,
 * func_0203ee34 or else the object's virtual function at 0x54. Otherwise the tool held is tried
 * (FieldActor_TryToolInScene), and in aim mode 2 with the byte at 0x140 set, the point 0.8
 * ahead stands in for the aim point while tool 0 is tried on it. */
int FieldActor_TryAct(FieldActor *actor)
{
    if (EventQueue_TestFlag8() || FieldActor_TestFlag(actor, 0x13)) {
        return 0;
    }
    if (FieldActor_Act(actor)) {
        EventQueue_RequestAct(actor, FIELD_ACTOR_FIELD(actor, void *, 0x13c));
        void *picked = FIELD_ACTOR_FIELD(actor, void *, 0x13c);
        if (picked == NULL) {
            if (SceneObjectBase_FindActable(actor)) {
                return 1;
            }
        } else if (SceneObjectBase_CanAct(FIELD_ACTOR_FIELD(actor, void *, 0x13c), (SceneObjectBase *) actor) != 0) {
            return 1;
        } else {
            void *object = FIELD_ACTOR_FIELD(actor, void *, 0x13c);
            FieldActorPickedMethod method = (FieldActorPickedMethod) (uintptr_t) field_actor_motion_virtual(object, 0x54);
            if (method(object, actor)) {
                return 1;
            }
        }
    }
    if (FieldActor_TryToolInScene(actor)) {
        return 1;
    }
    if (actor->unk_140 && actor->aim_mode == 2) {
        Vec3 saved = actor->aim_point;
        Vec3 ahead;
        FieldActor_PointAhead(&ahead, actor, &actor->position, (const u16 *) &actor->yaw, &data_020d72f8);
        actor->aim_point = ahead;
        int result = FieldActor_TryTargetInScene(actor, 0);
        actor->aim_point = saved;
        return result;
    }
    return 0;
}
CLEAN_AS(func_02010538, FieldActor_TryAct)

/* ---- Speed, lean and yaw */

/* func_02010718: the walking speed the push gives: the push times WALK_SPEED_MAX, at most that
 * and 0 below WALK_SPEED_MIN; at most WALK_SPEED_BLOCKED when the contact body has a contact of
 * flag 8 that the yaw faces (func_02089cc0, func_0208a038), else at most WALK_SPEED_COLLIDER_3
 * with the collider's flag 3. */
int FieldActor_WalkSpeed(FieldActor *actor)
{
    int speed = FX_MulFunc((int) FieldActor_Push(actor), WALK_SPEED_MAX);
    if (speed > WALK_SPEED_MAX) {
        speed = WALK_SPEED_MAX;
    } else if (speed < WALK_SPEED_MIN) {
        speed = 0;
    }
    u8 *contact = field_actor_motion_at(actor, FIELD_ACTOR_CONTACT);
    if (FieldBody_TouchedWith((FieldBody *) (void *) contact, 8) != 0 &&
        FieldBody_TouchedAhead((FieldBody *) (void *) contact, actor->yaw) != 0) {
        if (speed > WALK_SPEED_BLOCKED) {
            speed = WALK_SPEED_BLOCKED;
        }
    } else if (FIELD_ACTOR_COLLIDER_FLAGS(actor) & 8) {
        if (speed > WALK_SPEED_COLLIDER_3) {
            speed = WALK_SPEED_COLLIDER_3;
        }
    }
    return speed;
}
CLEAN_AS(func_02010718, FieldActor_WalkSpeed)

/* func_0201107c: the speed along the heading becomes `*speed`; the velocity follows. */
void FieldActor_SetSpeed(FieldActor *actor, const int *speed)
{
    FieldActor_Base(actor)->speed = *speed;
    Actor_UpdateVelocity(FieldActor_Base(actor));
}
CLEAN_AS(func_0201107c, FieldActor_SetSpeed)

/* func_0201108c: the lean (the angle about X) turns a step towards `target` (FieldActor_TurnAngleStep). */
void FieldActor_LeanTowards(FieldActor *actor, int target)
{
    FieldActor_TurnAngleStep(&FieldActor_Base(actor)->angle[0], target);
}
CLEAN_AS(func_0201108c, FieldActor_LeanTowards)

/* func_02011098: the lean becomes `lean`. */
void FieldActor_SetLean(FieldActor *actor, u16 lean)
{
    FieldActor_Base(actor)->angle[0] = (s16) lean;
}
CLEAN_AS(func_02011098, FieldActor_SetLean)

/* func_020110a0: the yaw and the heading of the movement become `*yaw`. */
void FieldActor_SetYaw(FieldActor *actor, const s16 *yaw)
{
    Actor *base = FieldActor_Base(actor);
    base->angle[1] = *yaw;
    base->move_angle[1] = base->angle[1];
}
CLEAN_AS(func_020110a0, FieldActor_SetYaw)

/* ---- Moving */

/* func_02010f6c: a step towards where another console reports its actor
 * (FieldActor_ReportedPosition), when it reports one in this scene; 0 otherwise. The yaw turns
 * a step towards the reported one, X and Z move a step towards the reported point
 * (FieldActor_EaseValue); 1 once the yaw had arrived and the point is reached. */
int FieldActor_StepTowardReported(FieldActor *actor)
{
    u8 scene;
    int x;
    int z;
    s16 reported_yaw;
    if (FieldActor_ReportedPosition(actor, &scene, &x, &z, &reported_yaw) == 0) {
        return 0;
    }
    if (scene != SceneQuery_Current()) {
        return 0;
    }
    s16 yaw = actor->yaw;
    int arrived = FieldActor_TurnAngleSlowly(&yaw, reported_yaw) == 0;
    FieldActor_SetYaw(actor, &yaw);
    FieldActor_EaseValue(&actor->position.x, x);
    FieldActor_EaseValue(&actor->position.z, z);
    if (arrived) {
        arrived = x == actor->position.x && z == actor->position.z;
    }
    return arrived;
}
CLEAN_AS(func_02010f6c, FieldActor_StepTowardReported)

/* func_02010ff4: the actor moves by its velocity alone (Actor_ApplyVelocity, nothing carrying
 * it) and is put on the ground's height; that height. */
int FieldActor_MoveFree(FieldActor *actor)
{
    Actor_ApplyVelocity(FieldActor_Base(actor), NULL);
    int ground = CollisionQuery_FloorHeight(0);
    actor->position.y = ground;
    return ground;
}
CLEAN_AS(func_02010ff4, FieldActor_MoveFree)

/* func_0201100c: the actor moves by its velocity and what its contact body carries it by, is
 * kept out of walls from where it was (func_02031288, with its own collider in states with
 * FieldActor_StateFlagB48, else a fresh one made for the call), and is put on the ground's
 * height; that height. */
int FieldActor_MoveWithCollision(FieldActor *actor)
{
    Actor *base = FieldActor_Base(actor);
    Actor_ApplyVelocity(base, (const ActorCarrier *) field_actor_motion_at(actor, FIELD_ACTOR_CONTACT));
    FieldActorCollider fresh;
    CollisionContacts_Construct((CollisionContacts *) &fresh);
    s16 yaw = actor->yaw;
    void *collider = &fresh;
    if (FieldActor_StateFlagB48(actor, actor->state) != 0) {
        collider = field_actor_motion_at(actor, FIELD_ACTOR_COLLIDER);
    }
    CollisionQuery_Move(collider, &base->position, &base->last_position, yaw, COLLIDER_SIZE, actor, 0xf);
    CollisionContacts_Destroy((CollisionContacts *) &fresh);
    int ground = CollisionQuery_FloorHeight(0);
    actor->position.y = ground;
    return ground;
}
CLEAN_AS(func_0201100c, FieldActor_MoveWithCollision)

/* func_02010ca4: the actor's shadow (func_020b7d3c at 0x214, of size 0xa00, at the position
 * lifted by SHADOW_LIFT); its answer. For another console's actor only while func_020b67ac is
 * set and in state 8.
 * QUIRK: otherwise the answer is 0 or the state the actor is in. */
int FieldActor_PlaceShadow(FieldActor *actor)
{
    if (!Session_IsLocalPlayer(data_020ccf94, actor->player)) {
        if (SceneKinds_CurrentIn6To8() == 0) {
            return 0;
        }
        if (actor->state != 8) {
            return actor->state;
        }
    }
    Vec3 point = actor->position;
    point.y = field_actor_motion_add32(point.y, SHADOW_LIFT);
    void *shadows = (void *) (uintptr_t) SceneQuery_FieldObject();
    return (int) (uintptr_t) TouchPick_SetCylinderAndAdd(shadows,
                                                         (TouchPickCylinder *) (void *) field_actor_motion_at(actor, 0x214),
                                                         &point, 0xa00, 0x15cf, 1, (u8) actor->player);
}
CLEAN_AS(func_02010ca4, FieldActor_PlaceShadow)

/* ---- The contact bodies */

/* func_02010eb4: the contact's flags for the state: 2 when data_020c798c says so, else 0. */
int FieldActor_ContactFlags(FieldActor *actor, const int *state)
{
    (void) actor;
    return data_020c798c[*state] != 0 ? 2 : 0;
}
CLEAN_AS(func_02010eb4, FieldActor_ContactFlags)

/* func_02010e58: the contact body at `point`, for the state, with the player. */
void FieldActor_SetContactAt(FieldActor *actor, const Vec3 *point, const int *state)
{
    int flags = FieldActor_ContactFlags(actor, state);
    FieldOwnedPointBody_Set((FieldOwnedPointBody *) (void *) field_actor_motion_at(actor, FIELD_ACTOR_CONTACT),
                            (Actor *) actor, point, COLLIDER_SIZE, CONTACT_HEIGHT, flags | 4, 0x2fc, 0x15, (u8) actor->player,
                            FX32_ONE);
}
CLEAN_AS(func_02010e58, FieldActor_SetContactAt)

/* func_02010e48: the contact body at the position. */
void FieldActor_SetContact(FieldActor *actor, const int *state)
{
    FieldActor_SetContactAt(actor, &actor->position, state);
}
CLEAN_AS(func_02010e48, FieldActor_SetContact)

/* func_02010e10: the contact body at the start position, on the ground's height. */
void FieldActor_SetContactOnGround(FieldActor *actor, const int *state)
{
    Vec3 point;
    point.x = actor->start_position.x;
    point.y = CollisionQuery_FloorHeight(0);
    point.z = actor->start_position.z;
    FieldActor_SetContactAt(actor, &point, state);
}
CLEAN_AS(func_02010e10, FieldActor_SetContactOnGround)

/* func_02010d64: the contact body at the position, entered for the frame. */
void FieldActor_EnterContact(FieldActor *actor)
{
    FieldActor_SetContact(actor, &actor->state);
    FieldBody_Enter((FieldBody *) (void *) field_actor_motion_at(actor, FIELD_ACTOR_CONTACT));
}
CLEAN_AS(func_02010d64, FieldActor_EnterContact)

/* func_02010d28: the contact body on the ground at the start position and the second one at
 * `point`, both entered for the frame. */
void FieldActor_EnterContacts(FieldActor *actor, const Vec3 *point)
{
    FieldActor_SetContactOnGround(actor, &actor->state);
    FieldBody_Enter((FieldBody *) (void *) field_actor_motion_at(actor, FIELD_ACTOR_CONTACT));
    FieldActor_SetContactB(actor, point);
    FieldBody_Enter((FieldBody *) (void *) field_actor_motion_at(actor, FIELD_ACTOR_CONTACT_B));
}
CLEAN_AS(func_02010d28, FieldActor_EnterContacts)

/* func_02010d88: the second contact body at `point`, of `size` and `height`. */
void FieldActor_SetContactBSized(FieldActor *actor, const Vec3 *point, int size, int height)
{
    FieldOwnedPointBody_Set((FieldOwnedPointBody *) (void *) field_actor_motion_at(actor, FIELD_ACTOR_CONTACT_B),
                            (Actor *) actor, point, size, height, 0x11, 0x2c, 0, 0xff, FX32_ONE);
}
CLEAN_AS(func_02010d88, FieldActor_SetContactBSized)

/* func_02010dc8: the second contact body at `point`, of the actor's size. */
void FieldActor_SetContactB(FieldActor *actor, const Vec3 *point)
{
    FieldOwnedPointBody_Set((FieldOwnedPointBody *) (void *) field_actor_motion_at(actor, FIELD_ACTOR_CONTACT_B),
                            (Actor *) actor, point, COLLIDER_SIZE, CONTACT_HEIGHT, 6, 0x2fc, 0, 0xff, FX32_ONE);
}
CLEAN_AS(func_02010dc8, FieldActor_SetContactB)
