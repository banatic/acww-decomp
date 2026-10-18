/* The bottle with a letter a player throws into the water (thrown_bottle.h). */
#include "thrown_bottle.h"

#include "clean.h"
#include "fish_shadow.h" /* PlayerFish_ArcStep */
#include "main/actor.h"  /* Vec_YawTo */
#include "main/collision_query.h"
#include "main/session.h"
#include "main/session_players.h"
#include "ov004/member_pointer.h"
#include "town_item_models.h"

static_assert(offsetof(ThrownBottle, state) == 0x30 && offsetof(ThrownBottle, position) == 0x34, "ThrownBottle");
static_assert(offsetof(ThrownBottle, to) == 0x4c && offsetof(ThrownBottle, local) == 0x5c, "ThrownBottle");
static_assert(sizeof(ThrownBottle) == 0x60, "ThrownBottle");

#define THROWN_BOTTLE_ARC_HEIGHT 0x14cd
#define THROWN_BOTTLE_ARC_FRAMES 15
#define THROWN_BOTTLE_LANDING 15 /* ThrownBottle_SoundCue's frame of the splash */
#define THROWN_BOTTLE_TARGET_Y (-0x3800)
#define THROWN_BOTTLE_SCARE 0x2800     /* the reach of the shadows that flee its landing */
#define THROWN_BOTTLE_BLINK_FRAMES 100 /* floating: shown steadily up to here, then blinking */
#define THROWN_BOTTLE_FLOAT_FRAMES 120
#define THROWN_BOTTLE_RADIUS_MAX 0x199a /* its collision radius grows to 1.6 over 32 frames */
#define THROWN_BOTTLE_COLLISION_FLAGS 0xb
#define THROWN_BOTTLE_VIEW_X 0x8000 /* the box around the camera's point it is seen in */
#define THROWN_BOTTLE_VIEW_Z 0x6000

/* The method at slot 0x5c (word 23) of an actor's vtable: its hold point written to `out`
 * (not 0), or 0 when it has none. */
typedef int (*ThrownBottleHoldPointFn)(Actor *actor, Vec3 *out);
#define THROWN_BOTTLE_SLOT_HOLD_POINT 23

typedef void (*ThrownBottleStepFn)(void *self, ThrownBottle *bottle);

extern ThrownBottle data_ov003_0225f35c[THROWN_BOTTLE_COUNT];
/* Each state's step, member functions of the fish process taking the bottle. */
extern MemberPointer data_ov003_0225f100[THROWN_BOTTLE_STATES];
extern NetSession *data_020ccf94;
/* The camera (itcm/camera.h) and the point it follows. */
extern int data_021c67a4;
extern const Vec3 data_021c67d0;
/* How far the floating bottle drifts with the current, and sinks, a frame. */
extern const int data_ov003_0223bda8;
extern const int data_ov003_0223bda4;

extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));
/* The bottle's destructor, handed to __cxa_vec_cleanup: the game's symbol
 * (ThrownBottle_Destruct). */
extern void func_ov003_0222c3d0(void *bottle);

/* The bottle's model drawn where it is, at full size. */
static void thrown_bottle_draw(const ThrownBottle *bottle)
{
    Vec3 at = bottle->position;
    Vec3 scale = {0x1000, 0x1000, 0x1000};
    TownItemModels_DrawCodeAt(THROWN_BOTTLE_ITEM, &at, &scale, 0, 0, 0);
}

/* The bottle's collision with the ground and walls, facing from where it lands back to the
 * throw, its radius growing with its frames. */
static void thrown_bottle_collide(ThrownBottle *bottle)
{
    int radius = bottle->frames * THROWN_BOTTLE_RADIUS_MAX >> 5;
    if (radius > THROWN_BOTTLE_RADIUS_MAX) {
        radius = THROWN_BOTTLE_RADIUS_MAX;
    }
    CollisionQuery_Move(&bottle->contacts, &bottle->position, &bottle->position, Vec_YawTo(&bottle->to, &bottle->from), radius,
                        NULL, THROWN_BOTTLE_COLLISION_FLAGS);
}

/* The bottle lands: floating from its frame 0; the shadows near it flee when it is this
 * console's player's. */
static void thrown_bottle_land(ThrownBottle *bottle)
{
    bottle->state = THROWN_BOTTLE_FLOATING;
    bottle->frames = 0;
    if (bottle->local != 0) {
        FishShadow_ScareNear(&bottle->position, THROWN_BOTTLE_SCARE);
    }
}

/* func_ov003_0222beec: THROWN_BOTTLE_FLOATING: drawn (every other frame after frame 100, or
 * from then on once out of view), drifted with the current and sunk a little, kept off the
 * walls; after 120 frames it is gone (THROWN_BOTTLE_NONE) and its target reset to (1.0, 1.0,
 * 1.0). */
void ThrownBottle_StepFloating(void *self, ThrownBottle *bottle)
{
    (void) self;
    if (bottle->frames < THROWN_BOTTLE_BLINK_FRAMES) {
        thrown_bottle_draw(bottle);
        if (ThrownBottle_OutOfView(bottle)) {
            bottle->frames = THROWN_BOTTLE_BLINK_FRAMES;
        }
    } else if (bottle->frames & 1) {
        thrown_bottle_draw(bottle);
    }
    FishShadow_Drift(&bottle->position, data_ov003_0223bda8);
    bottle->position.y -= data_ov003_0223bda4;
    thrown_bottle_collide(bottle);
    bottle->frames++;
    if (bottle->frames >= THROWN_BOTTLE_FLOAT_FRAMES) {
        bottle->state = THROWN_BOTTLE_NONE;
        bottle->to.x = 0x1000;
        bottle->to.y = 0x1000;
        bottle->to.z = 0x1000;
    }
}
CLEAN_AS(func_ov003_0222beec, ThrownBottle_StepFloating)

/* func_ov003_0222bfe0: THROWN_BOTTLE_FLYING: past the end of its line it lands at once;
 * otherwise it moves on its arc (PlayerFish_ArcStep, 15 frames peaking 1.3 up) and lands when
 * that is over; then it is kept off the walls and drawn. */
void ThrownBottle_StepFlying(int self, ThrownBottle *bottle)
{
    (void) self;
    Vec3 from = bottle->from;
    Vec3 to = bottle->to;
    Vec3 at = bottle->position;
    if (FishShadow_ReachedXZ(&at, &from, &to)) {
        thrown_bottle_land(bottle);
        return;
    }
    if (PlayerFish_ArcStep(&bottle->position, &from, &to, bottle->frames, THROWN_BOTTLE_ARC_HEIGHT,
                           THROWN_BOTTLE_ARC_FRAMES) == 0) {
        thrown_bottle_land(bottle);
    }
    thrown_bottle_collide(bottle);
    thrown_bottle_draw(bottle);
    bottle->frames++;
}
CLEAN_AS(func_ov003_0222bfe0, ThrownBottle_StepFlying)

/* func_ov003_0222c12c: THROWN_BOTTLE_NONE: nothing. */
void ThrownBottle_StepNone(void) {}
CLEAN_AS(func_ov003_0222c12c, ThrownBottle_StepNone)

/* State `state`'s step, the address computed without a bound. */
static const MemberPointer *thrown_bottle_step(unsigned int state)
{
    return (const MemberPointer *) (uintptr_t) ((u32) (uintptr_t) data_ov003_0225f100 + state * (u32) sizeof(MemberPointer));
}

/* func_ov003_0222c130: the bottle's step by its state (data_ov003_0225f100), when it has one,
 * called on the fish process `self`. */
void ThrownBottle_Step(void *self, ThrownBottle *bottle)
{
    const MemberPointer *step = thrown_bottle_step(bottle->state);
    if (step->function != 0) {
        void *object = MemberPointer_Object(step, self);
        ((ThrownBottleStepFn) (uintptr_t) MemberPointer_Code(step, object))(object, bottle);
    }
}
CLEAN_AS(func_ov003_0222c130, ThrownBottle_Step)

/* func_ov003_0222c16c: whether the bottle is out of view: there is no camera, or it is not in
 * the box around the camera's point (8.0 across, 6.0 ahead and behind). */
int ThrownBottle_OutOfView(ThrownBottle *bottle)
{
    if (data_021c67a4 == 0) {
        return 1;
    }
    Vec3 camera = data_021c67d0;
    return FishShadow_InBox(&bottle->position, &camera, THROWN_BOTTLE_VIEW_X, THROWN_BOTTLE_VIEW_Z, THROWN_BOTTLE_VIEW_Z) == 0;
}
CLEAN_AS(func_ov003_0222c16c, ThrownBottle_OutOfView)

/* func_ov003_0222c1bc: the sound player `player`'s (0-3) bottle asks for while it flies: 1 at
 * its first frame (the throw), 2 at frame 15 (the splash); else 0. */
int ThrownBottle_SoundCue(int player)
{
    if (player < 0 || player >= THROWN_BOTTLE_COUNT) {
        return 0;
    }
    const ThrownBottle *bottle = &data_ov003_0225f35c[player];
    if (bottle->state == THROWN_BOTTLE_FLYING) {
        if (bottle->frames == 0) {
            return 1;
        }
        if (bottle->frames == THROWN_BOTTLE_LANDING) {
            return 2;
        }
    }
    return 0;
}
CLEAN_AS(func_ov003_0222c1bc, ThrownBottle_SoundCue)

/* func_ov003_0222c1f4: player `player`'s bottle's position.
 * QUIRK: for a player outside 0-3 it is player 0's bottle's. */
Vec3 *ThrownBottle_PositionOf(int player)
{
    if (player < 0 || player >= THROWN_BOTTLE_COUNT) {
        return &data_ov003_0225f35c[0].position;
    }
    return &data_ov003_0225f35c[player].position;
}
CLEAN_AS(func_ov003_0222c1f4, ThrownBottle_PositionOf)

/* The actor's hold point (vtable slot 23) into `out`; whether it has one. */
static int thrown_bottle_hold_point(Actor *actor, Vec3 *out)
{
    const u32 *vtable = (const u32 *) actor->vtable;
    return ((ThrownBottleHoldPointFn) (uintptr_t) vtable[THROWN_BOTTLE_SLOT_HOLD_POINT])(actor, out);
}

/* func_ov003_0222c214: player `player`'s (0-3; else 0) bottle is thrown (2) from the player's
 * hold point, or from the actor's position when it has none or (in a session) is out of sight;
 * one already thrown stays (1); 0 without the player's actor. It is this console's in a session
 * when the player is, always out of one. It flies (THROWN_BOTTLE_FLYING) from frame 0 to its
 * target lowered to -3.5.
 * BUG: in the ROM its position is copied from a local that only the hold point fills, so
 * without one it starts from what that stack word held; here it starts from where it is
 * thrown from. */
int ThrownBottle_Throw(int player)
{
    if (player < 0 || player >= THROWN_BOTTLE_COUNT) {
        return 0;
    }
    ThrownBottle *bottle = &data_ov003_0225f35c[player];
    if (bottle->state != THROWN_BOTTLE_NONE) {
        return 1;
    }
    Actor *actor = (Actor *) (uintptr_t) SessionPlayers_ActorHandle(player);
    if (actor == NULL) {
        return 0;
    }
    NetSession *session = data_020ccf94;
    Vec3 hold;
    int held = 0;
    if (Session_IsLinked(session)) {
        bottle->local = Session_IsLocalSlot(session, player) ? 1 : 0;
        u32 flags = actor->cull_flags;
        if ((flags & ACTOR_CULL_FAR) != 0 && (flags & ACTOR_CULL_SKIP_DRAW) != 0) {
            bottle->from = actor->position;
        } else if (thrown_bottle_hold_point(actor, &hold)) {
            bottle->from = hold;
            held = 1;
        } else {
            bottle->from = actor->position;
        }
    } else {
        bottle->local = 1;
        if (thrown_bottle_hold_point(actor, &hold)) {
            bottle->from = hold;
            held = 1;
        } else {
            bottle->from = actor->position;
        }
    }
    bottle->state = THROWN_BOTTLE_FLYING;
    bottle->position = held ? hold : bottle->from;
    bottle->frames = 0;
    bottle->to.y = THROWN_BOTTLE_TARGET_Y;
    return 2;
}
CLEAN_AS(func_ov003_0222c214, ThrownBottle_Throw)

/* func_ov003_0222c364: whether player `player`'s (0-3) bottle is still to be followed: flying,
 * or floating up to its frame 100, and in view. */
int ThrownBottle_IsActive(int player)
{
    if (player < 0 || player >= THROWN_BOTTLE_COUNT) {
        return 0;
    }
    ThrownBottle *bottle = &data_ov003_0225f35c[player];
    int state = bottle->state;
    if (state == THROWN_BOTTLE_NONE || (state == THROWN_BOTTLE_FLOATING && bottle->frames > THROWN_BOTTLE_BLINK_FRAMES) ||
        ThrownBottle_OutOfView(bottle) != 0) {
        return 0;
    }
    return 1;
}
CLEAN_AS(func_ov003_0222c364, ThrownBottle_IsActive)

/* func_ov003_0222c3a8: player `player`'s (0-3; else nothing) bottle's target set to `to`. */
void ThrownBottle_SetTarget(Vec3 *to, int player)
{
    if (player >= 0 && player < THROWN_BOTTLE_COUNT) {
        data_ov003_0225f35c[player].to = *to;
    }
}
CLEAN_AS(func_ov003_0222c3a8, ThrownBottle_SetTarget)

/* func_ov003_0222c3d0: the destructor. */
ThrownBottle *ThrownBottle_Destruct(ThrownBottle *bottle)
{
    CollisionContacts_Destroy(&bottle->contacts);
    return bottle;
}
CLEAN_AS(func_ov003_0222c3d0, ThrownBottle_Destruct)

/* func_ov003_0222c3e0: the constructor: none, its points (1.0, 1.0, 1.0), frame 0. */
ThrownBottle *ThrownBottle_Construct(ThrownBottle *bottle)
{
    CollisionContacts_Construct(&bottle->contacts);
    bottle->state = THROWN_BOTTLE_NONE;
    bottle->position.x = 0x1000;
    bottle->position.y = 0x1000;
    bottle->position.z = 0x1000;
    bottle->from.x = 0x1000;
    bottle->from.y = 0x1000;
    bottle->from.z = 0x1000;
    bottle->to.x = 0x1000;
    bottle->to.y = 0x1000;
    bottle->to.z = 0x1000;
    bottle->frames = 0;
    return bottle;
}
CLEAN_AS(func_ov003_0222c3e0, ThrownBottle_Construct)

/* func_ov003_0222c454 (registered at the overlay's start): the four bottles destroyed. */
void ThrownBottle_DestroyAll(void *object)
{
    (void) object;
    __cxa_vec_cleanup(data_ov003_0225f35c, THROWN_BOTTLE_COUNT, sizeof(ThrownBottle), func_ov003_0222c3d0);
}
CLEAN_AS(func_ov003_0222c454, ThrownBottle_DestroyAll)
