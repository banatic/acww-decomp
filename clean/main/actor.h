/* The scene object with a place in the 3D world (the C++ class with vtable 0x020d7244, between
 * the root of the scene objects at 0x020da13c and Base_0203f080 in include/cpp/main): a
 * position, angles, a velocity driven by a speed along a heading and by gravity, and a check
 * of its distance from the camera that can keep it from running or from being drawn.
 *
 * Every such object is linked into one list (data_0213ff78) while it exists, which is searched
 * by class (profile) or by serial number. An object is made with Actor_Spawn, which hands the
 * constructor its position and angles through two globals. */
#ifndef CLEAN_MAIN_ACTOR_H
#define CLEAN_MAIN_ACTOR_H

#include "autoload_2/links.h"
#include "autoload_2/matrix.h"
#include "autoload_2/vector.h"
#include "types.h"

struct Actor;

/* An object's entry in the list of actors. */
typedef struct ActorLink {
    ListNode node;
    struct Actor *owner;
} ActorLink;

/* What the distance check does (Actor.cull_flags); the class's profile gives the first two. */
#define ACTOR_CULL_SKIP_RUN 1  /* far: Actor_CanRun refuses */
#define ACTOR_CULL_SKIP_DRAW 2 /* far: Actor_CanDraw refuses */
#define ACTOR_CULL_FAR 4       /* set by the check while the object is far */

typedef struct Actor {
    const void *vtable;
    int serial; /* 0x04: numbers the scene objects in the order they were made */
    u8 unk_08[4];
    u16 profile; /* 0x0c: the object's class: its index in the table at data_021fd044 */
    u8 unk_0e[0x42];
    ActorLink link;     /* 0x50 */
    Vec3 position;      /* 0x5c */
    Vec3 last_position; /* 0x68: the position at the start of the frame */
    Vec3 view_position; /* 0x74: the position as the distance check sees it (func_0203a7b8) */
    u8 unk_80[0xc];
    s16 angle[3];        /* 0x8c: x, y and z */
    s16 move_angle[3];   /* 0x92: y (0x94) is the heading of the movement */
    fx32 speed;          /* 0x98: along the heading */
    fx32 gravity;        /* 0x9c: added to the vertical velocity each step */
    fx32 min_y_velocity; /* 0xa0: the vertical velocity never falls below it */
    Vec3 velocity;       /* 0xa4 */
    u32 cull_flags;      /* 0xb0: ACTOR_CULL_... */
    fx32 cull_offset;    /* 0xb4: how far the checked point lies from the pivot, along `pitch` */
    fx32 cull_radius;    /* 0xb8: zero: no check */
    fx32 cull_depth;     /* 0xbc: farther than this is far */
    u8 unk_c0[4];
    Vec3 pivot; /* 0xc4 */
    u16 pitch;  /* 0xd0: an angle about X */
} Actor;

/* An object an actor moves along with (the second argument of Actor_Move): its displacement in
 * this frame. */
typedef struct ActorCarrier {
    u8 unk_00[0x10];
    fx32 shift_x;
    fx32 unused_y;
    fx32 shift_z;
} ActorCarrier;

Actor *Actor_Destruct(Actor *actor);
void *Actor_DestructDelete(void *actor);
void Actor_ModelMatrix(const Actor *actor, Mtx43 *out);
s16 Vec_YawTo(const Vec3 *from, const Vec3 *to);
void Actor_Move(Actor *actor, const ActorCarrier *carrier);
void Actor_UpdateVelocity(Actor *actor);
void Actor_ApplyVelocity(Actor *actor, const ActorCarrier *carrier);
void Actor_SetCull(Actor *actor, fx32 offset, fx32 radius, fx32 depth);
int Actor_Spawn(int profile, int group, const Vec3 *position, const s16 *angle, void *parent);
void Actor_SetSpawnPlacement(const Vec3 *position, const s16 *angle);
void *Actor_FindNextOfProfile(int profile, Actor *after);
int Actor_FindBySerial(int serial);
void Actor_Draw(Actor *actor, int status);
int Actor_CanDraw(Actor *actor);
void Actor_Run(Actor *actor, int status);
int Actor_CanRun(Actor *actor);
void Actor_Vfunc14(Actor *actor, int marker);
int Actor_Vfunc10(Actor *actor);
void Actor_Vfunc08(Actor *actor, int flag);
int Actor_Vfunc04(void);
Actor *Actor_Construct(Actor *actor);

#endif
