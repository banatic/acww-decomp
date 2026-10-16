/* Scene objects with a place in the 3D world (actor.h). */
#include "actor.h"

#include <assert.h>
#include <stddef.h>
#include <stdint.h>

#include "autoload_2/fx_math.h"
#include "clean.h"

static_assert(offsetof(Actor, profile) == 0x0c, "Actor layout");
static_assert(offsetof(Actor, link) == 0x50, "Actor layout");
static_assert(offsetof(Actor, position) == 0x5c, "Actor layout");
static_assert(offsetof(Actor, view_position) == 0x74, "Actor layout");
static_assert(offsetof(Actor, angle) == 0x8c, "Actor layout");
static_assert(offsetof(Actor, move_angle) == 0x92, "Actor layout");
static_assert(offsetof(Actor, velocity) == 0xa4, "Actor layout");
static_assert(offsetof(Actor, cull_flags) == 0xb0, "Actor layout");
static_assert(offsetof(Actor, pivot) == 0xc4, "Actor layout");
static_assert(offsetof(Actor, pitch) == 0xd0, "Actor layout");
static_assert(offsetof(ActorCarrier, shift_z) == 0x18, "ActorCarrier layout");

/* The vtables of this class and of the root of the scene objects. */
extern const u8 data_020d7244[];
extern const u8 data_020da13c[];

/* Every actor, linked through Actor.link. */
extern List data_0213ff78;

/* The position and angles the next actor is made with (Actor_SetSpawnPlacement); NULL: none. */
extern const Vec3 *data_0213ff74;
extern const s16 *data_0213ff70;

/* The parent of an actor spawned without one. */
extern int data_021f42f4;

/* What the table of classes holds for a class of actors. */
typedef struct ActorProfile {
    u8 unk_00[8];
    u32 cull_flags;
    fx32 cull_offset;
    fx32 cull_radius;
    fx32 cull_depth;
} ActorProfile;

extern const ActorProfile **data_021fd044;

/* Sine and cosine of each of 4096 angles, interleaved (NitroSDK's table). */
extern const fx16 FX_SinCosTable_[4096 * 2];
/* What the distance check measures with: the camera's planes with its near and far distances,
 * and its view matrix. */
extern u8 data_021f6a6c[];
extern u8 data_0213fee4[];

extern fx32 FX_MulFunc(fx32 a, fx32 b);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *sum);

/* The scene objects' own functions (the root class, vtable 0x020da13c). */
extern void *func_020ee660(void *object);                              /* constructor */
extern void func_020ee62c(void *object);                               /* destructor */
extern void func_020edf54(void *object);                               /* operator delete */
extern int func_0202f134(int profile, int parent, int group, int arg); /* make an object */
extern ActorLink *func_020ee7a4(List *list, int profile, ActorLink *after);
extern ActorLink *func_020ee7f0(List *list, int serial);
extern void func_01ffd3e4(void *object);
extern int func_01ffd3e8(void *object);
extern void func_01ffd418(void *object);
extern int func_01ffd41c(void *object);
extern void func_020ee4d8(void *object, int marker);
extern int func_020ee550(void *object);
extern void func_0202f144(void *object, int flag);
extern int func_020ee61c(void);
/* The depth of `point` seen through `view_matrix`, 0x7fffffff outside the near and far
 * distances of `frustum` widened by `radius`; the point in view space goes to `view`. */
extern int func_0203a7b8(void *frustum, void *view_matrix, Vec3 *point, fx32 radius, Vec3 *view);

/* The sine and cosine table's entries for `angle`: its top 12 bits. */
static fx32 sin_of(u16 angle)
{
    return FX_SinCosTable_[2 * (angle >> 4)];
}

static fx32 cos_of(u16 angle)
{
    return FX_SinCosTable_[2 * (angle >> 4) + 1];
}

/* What both destructors do before freeing. */
static void destruct(Actor *actor)
{
    actor->vtable = data_020d7244;
    List_Remove(&data_0213ff78, &actor->link.node);
    actor->vtable = data_020da13c;
    func_020ee62c(actor);
}

/* func_0200316c: the destructor; takes the actor out of the list. */
Actor *Actor_Destruct(Actor *actor)
{
    destruct(actor);
    return actor;
}
CLEAN_AS(func_0200316c, Actor_Destruct)

/* func_0200319c: the destructor that also frees the object. */
void *Actor_DestructDelete(void *actor)
{
    destruct(actor);
    func_020edf54(actor);
    return actor;
}
CLEAN_AS(func_0200319c, Actor_DestructDelete)

/* func_020031d4: the matrix that places the actor: translated to its pivot, turned by its pitch,
 * then about Y by its y angle and about X by its x angle when it has one. */
void Actor_ModelMatrix(const Actor *actor, Mtx43 *out)
{
    Mtx43 mtx;
    Mtx43_Translation(&mtx, actor->pivot.x, actor->pivot.y, actor->pivot.z);
    Mtx43_RotateX(&mtx, (s16) actor->pitch);
    Mtx43_RotateY(&mtx, actor->angle[1]);
    if (actor->angle[0] != 0) {
        Mtx43_RotateX(&mtx, actor->angle[0]);
    }
    *out = mtx;
}
CLEAN_AS(func_020031d4, Actor_ModelMatrix)

/* func_0200322c: the heading from one point to another in the ground plane (an angle about Y,
 * zero towards +Z). */
s16 Vec_YawTo(const Vec3 *from, const Vec3 *to)
{
    return Math_Atan2(to->x - from->x, to->z - from->z);
}
CLEAN_AS(func_0200322c, Vec_YawTo)

/* func_02003244: one step of movement. */
void Actor_Move(Actor *actor, const ActorCarrier *carrier)
{
    Actor_UpdateVelocity(actor);
    Actor_ApplyVelocity(actor, carrier);
}
CLEAN_AS(func_02003244, Actor_Move)

/* func_02003260: the velocity from the speed along the heading, and gravity added to the
 * vertical velocity down to its minimum. */
void Actor_UpdateVelocity(Actor *actor)
{
    if (actor->speed == 0) {
        fx32 vy = actor->velocity.y + actor->gravity;
        actor->velocity.x = 0;
        actor->velocity.y = vy >= actor->min_y_velocity ? vy : actor->min_y_velocity;
        actor->velocity.z = 0;
        return;
    }
    u16 heading = (u16) actor->move_angle[1];
    fx32 vz = FX_MulFunc(actor->speed, cos_of(heading));
    fx32 vy = actor->velocity.y + actor->gravity;
    actor->velocity.x = FX_MulFunc(actor->speed, sin_of(heading));
    actor->velocity.y = vy >= actor->min_y_velocity ? vy : actor->min_y_velocity;
    actor->velocity.z = vz;
}
CLEAN_AS(func_02003260, Actor_UpdateVelocity)

/* func_02003300: the position moved by the velocity, and by what the carrier moved in X and Z
 * when there is one. */
void Actor_ApplyVelocity(Actor *actor, const ActorCarrier *carrier)
{
    VEC_Add(&actor->position, &actor->velocity, &actor->position);
    if (carrier != NULL) {
        actor->position.x += carrier->shift_x;
        actor->position.z += carrier->shift_z;
    }
}
CLEAN_AS(func_02003300, Actor_ApplyVelocity)

/* func_02003330 */
void Actor_SetCull(Actor *actor, fx32 offset, fx32 radius, fx32 depth)
{
    actor->cull_offset = offset;
    actor->cull_radius = radius;
    actor->cull_depth = depth;
}
CLEAN_AS(func_02003330, Actor_SetCull)

/* func_02003348: make an actor of class `profile` at `position` facing `angle` (either may be
 * NULL) under `parent`, or under the game's default parent without one; what func_0202f134
 * returns.
 * QUIRK: the placement stays set afterwards (it points into the callers' stacks); an actor made
 * any other way copies whatever it still points at. */
int Actor_Spawn(int profile, int group, const Vec3 *position, const s16 *angle, void *parent)
{
    int owner = parent != NULL ? (int) (intptr_t) parent : data_021f42f4;
    Actor_SetSpawnPlacement(position, angle);
    return func_0202f134(profile, owner, group, 3);
}
CLEAN_AS(func_02003348, Actor_Spawn)

/* func_02003378 */
void Actor_SetSpawnPlacement(const Vec3 *position, const s16 *angle)
{
    data_0213ff74 = position;
    data_0213ff70 = angle;
}
CLEAN_AS(func_02003378, Actor_SetSpawnPlacement)

/* func_0200338c: the first actor of class `profile` after `after` in the list (from its start
 * without one), NULL when there is none. */
void *Actor_FindNextOfProfile(int profile, Actor *after)
{
    ActorLink *link = func_020ee7a4(&data_0213ff78, profile, after != NULL ? &after->link : NULL);
    return link != NULL ? link->owner : NULL;
}
CLEAN_AS(func_0200338c, Actor_FindNextOfProfile)

/* func_020033c4: the actor with this serial number (its address), 0 when there is none. */
int Actor_FindBySerial(int serial)
{
    ActorLink *link = func_020ee7f0(&data_0213ff78, serial);
    return link != NULL ? (int) (intptr_t) link->owner : 0;
}
CLEAN_AS(func_020033c4, Actor_FindBySerial)

/* func_020033e4: vtable slot 0x2c; the root class's, which does nothing. */
void Actor_Draw(Actor *actor, int status)
{
    (void) status;
    func_01ffd3e4(actor);
}
CLEAN_AS(func_020033e4, Actor_Draw)

/* func_020033ec: vtable slot 0x28, asked before Actor_Draw: the root class's answer, and no when
 * the distance check found the actor far and its class skips drawing then. */
int Actor_CanDraw(Actor *actor)
{
    if (func_01ffd3e8(actor) == 0) {
        return 0;
    }
    if ((actor->cull_flags & ACTOR_CULL_FAR) && (actor->cull_flags & ACTOR_CULL_SKIP_DRAW)) {
        return 0;
    }
    return 1;
}
CLEAN_AS(func_020033ec, Actor_CanDraw)

/* func_02003420: vtable slot 0x20; the root class's, which does nothing. */
void Actor_Run(Actor *actor, int status)
{
    (void) status;
    func_01ffd418(actor);
}
CLEAN_AS(func_02003420, Actor_Run)

/* func_02003428: vtable slot 0x1c, asked before Actor_Run: when the root class agrees, remember
 * the position at the start of the frame and run the distance check; no when the actor is far
 * and its class skips running then.
 *
 * The point checked lies `cull_offset` from the pivot, turned by `pitch` in the YZ plane.
 * BUG: without a radius no depth is measured, and an actor whose class still asks for the check
 * is compared with whatever the original's caller left in a register; here it counts as near.
 * REQUIRES: a class asking for the check has a radius. */
int Actor_CanRun(Actor *actor)
{
    if (func_01ffd41c(actor) == 0) {
        return 0;
    }
    actor->last_position = actor->position;

    int depth = 0;
    if (actor->cull_radius != 0) {
        fx32 dz = FX_MulFunc(actor->cull_offset, sin_of(actor->pitch));
        fx32 dy = FX_MulFunc(actor->cull_offset, cos_of(actor->pitch));
        Vec3 point = {actor->pivot.x, actor->pivot.y + dy, actor->pivot.z + dz};
        depth = func_0203a7b8(data_021f6a6c, data_0213fee4, &point, actor->cull_radius, &actor->view_position);
    }

    actor->cull_flags &= ~(u32) ACTOR_CULL_FAR;
    if ((actor->cull_flags & (ACTOR_CULL_SKIP_RUN | ACTOR_CULL_SKIP_DRAW)) == 0 || depth <= actor->cull_depth) {
        return 1;
    }
    actor->cull_flags |= ACTOR_CULL_FAR;
    return (actor->cull_flags & ACTOR_CULL_SKIP_RUN) ? 0 : 1;
}
CLEAN_AS(func_02003428, Actor_CanRun)

/* func_02003510: vtable slot 0x14; the root class's. */
void Actor_Vfunc14(Actor *actor, int marker)
{
    func_020ee4d8(actor, marker);
}
CLEAN_AS(func_02003510, Actor_Vfunc14)

/* func_02003518: vtable slot 0x10; the root class's answer as 0 or 1. */
int Actor_Vfunc10(Actor *actor)
{
    return func_020ee550(actor) != 0;
}
CLEAN_AS(func_02003518, Actor_Vfunc10)

/* func_02003530: vtable slot 0x08; the root class's, then the actor counts as far. */
void Actor_Vfunc08(Actor *actor, int flag)
{
    func_0202f144(actor, flag);
    actor->cull_flags |= ACTOR_CULL_FAR;
}
CLEAN_AS(func_02003530, Actor_Vfunc08)

/* func_0200354c: vtable slot 0x04; the root class's answer as 0 or 1. */
int Actor_Vfunc04(void)
{
    return func_020ee61c() != 0;
}
CLEAN_AS(func_0200354c, Actor_Vfunc04)

/* func_02003564: the constructor. Links the actor into the list, takes its position and angles
 * from the spawn placement when set (both angle sets from the same three), and its distance
 * check from its class's profile. */
Actor *Actor_Construct(Actor *actor)
{
    func_020ee660(actor);
    actor->vtable = data_020da13c;
    actor->vtable = data_020d7244;
    actor->link.node.prev = NULL;
    actor->link.node.next = NULL;
    actor->link.owner = actor;
    List_PushBack(&data_0213ff78, &actor->link.node);

    const Vec3 *position = data_0213ff74;
    if (position != NULL) {
        actor->position = *position;
    }
    const s16 *angle = data_0213ff70;
    if (angle != NULL) {
        for (int i = 0; i < 3; i++) {
            actor->angle[i] = angle[i];
        }
        for (int i = 0; i < 3; i++) {
            actor->move_angle[i] = angle[i];
        }
    }

    const ActorProfile *profile = data_021fd044[actor->profile];
    actor->cull_flags = profile->cull_flags;
    Actor_SetCull(actor, profile->cull_offset, profile->cull_radius, profile->cull_depth);
    return actor;
}
CLEAN_AS(func_02003564, Actor_Construct)
