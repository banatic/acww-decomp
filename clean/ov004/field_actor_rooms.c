/* Overlay 4's part of the field actor in the rooms (field_actor_rooms.h). */
#include "field_actor_rooms.h"

#include <stdint.h>

#include "autoload_2/fx_math.h"
#include "clean.h"
#include "itcm/vector.h"
#include "main/acre_tile.h"
#include "main/actor_table.h"
#include "main/angle_sector.h"
#include "main/current_pockets.h"
#include "main/field_actor.h"
#include "main/field_actor_parts.h"
#include "main/item_code.h"
#include "main/packed_bytes.h"
#include "main/scene_exit.h"
#include "main/scene_kinds.h"
#include "main/scene_tables.h"
#include "main/session.h"
#include "main/session_players.h"
#include "main/town_objects.h"

static_assert(offsetof(FieldActor, position) == 0x5c, "position");
static_assert(offsetof(FieldActor, yaw) == 0x8e, "yaw");
static_assert(offsetof(FieldActor, unk_098) == 0x98, "speed");
static_assert(offsetof(FieldActor, unk_148) == 0x148, "0x148");
static_assert(offsetof(FieldActor, aim_point) == 0x158, "aim point");
static_assert(offsetof(FieldActor, aim_mode) == 0x170, "aim mode");
static_assert(offsetof(FieldActor, anim.speed) == 0x2e0, "animation speed");
static_assert(offsetof(FieldActor, animation) == 0x704, "animation");
static_assert(offsetof(FieldActor, work) == 0x7d4, "work");
static_assert(offsetof(FieldActor, player) == 0x800, "player");
static_assert(offsetof(FieldActor, item) == 0x820, "item");
static_assert(offsetof(FieldActor, unk_822) == 0x822, "0x822");
static_assert(offsetof(FieldActor, saved) == 0x8f0, "saved");
static_assert(sizeof(FieldActorRoomsWalk) <= sizeof(FieldActorWork), "the door states' work");
static_assert(offsetof(FieldActorRoomsWalk, speed) == 0x0c, "speed");
static_assert(offsetof(FieldActorRoomsWalk, max_speed) == 0x10, "max speed");
static_assert(offsetof(FieldActorRoomsWalk, frames) == 0x14, "frames");
static_assert(offsetof(FieldActorRoomsWalk, kind) == 0x15, "kind");
static_assert(offsetof(StateRequest, payload) == 0x0c, "payload");

/* The door states. */
#define FIELD_ACTOR_ROOMS_EXIT 0x8c
#define FIELD_ACTOR_ROOMS_STEP_OFF 0x8d
#define FIELD_ACTOR_ROOMS_WALK_IN 0x8e

/* The states the tools ask for (with priority 6, or 5 for the room's object entry). */
#define FIELD_ACTOR_ROOMS_PRIORITY 6
#define FIELD_ACTOR_ROOMS_ENTRY_PRIORITY 5
#define FIELD_ACTOR_ROOMS_NO_ARG (-1)
/* The numbers state 0x18 is asked with for an item on the floor: with full pockets, and with
 * more than one visitor. */
#define FIELD_ACTOR_ROOMS_POCKETS_FULL (-1)
#define FIELD_ACTOR_ROOMS_VISITORS (-3)

/* What func_ov004_0223bbc0 answers besides an object's index: an item on the floor ahead. */
#define FIELD_ACTOR_ROOMS_FLOOR_ITEM (-2)
/* The tools' reaches (FieldActor_InToolReach) for the floor's item and the last try. */
#define FIELD_ACTOR_ROOMS_REACH_ITEM 14
#define FIELD_ACTOR_ROOMS_REACH_LAST 12
/* The layers of the map tried (AcreTile_ItemAt). */
#define FIELD_ACTOR_ROOMS_LAYER_ITEM 1
#define FIELD_ACTOR_ROOMS_LAYER_LAST 0

/* The walk: how near (1.0) the point must be for the speed to fall, and how it eases. */
#define FIELD_ACTOR_ROOMS_NEAR 0x1000
#define FIELD_ACTOR_ROOMS_EASE_RATE 0x800
#define FIELD_ACTOR_ROOMS_EASE_MIN 0x31

/* How far behind its place the actor starts walking in (6.0), and the door states' speed. */
#define FIELD_ACTOR_ROOMS_WALK_IN_DISTANCE 0x6000
#define FIELD_ACTOR_ROOMS_DOOR_SPEED 0x400
/* The animation the door states play (a loop), and their flag. */
#define FIELD_ACTOR_ROOMS_WALK_ANIMATION 1
#define FIELD_ACTOR_ROOMS_STEP_OFF_BLEND 3
#define FIELD_ACTOR_ROOMS_DOOR_FLAG 5

/* State 0x8c: the frame another console's actor plays the door's sound at, and that sound;
 * the frame this console's actor takes the exit at. */
#define FIELD_ACTOR_ROOMS_EXIT_SOUND_FRAME 15
#define FIELD_ACTOR_ROOMS_EXIT_SOUND 0x4d3
#define FIELD_ACTOR_ROOMS_EXIT_FRAME 10
/* The exit state 0x8c takes (an index into the scene's exits). */
#define FIELD_ACTOR_ROOMS_EXIT_INDEX(actor) FIELD_ACTOR_FIELD(actor, int, 0x804)

/* The session message FieldActorRooms_SendPair sends: its handler and kind. */
#define FIELD_ACTOR_ROOMS_MESSAGE_HANDLER 0x2c
#define FIELD_ACTOR_ROOMS_MESSAGE_KIND 4

/* A point packed in 20 bits per coordinate (PackedBytes_PackPoint): its sign bit and the bits
 * that extend it. */
#define FIELD_ACTOR_ROOMS_PACKED_SIGN 0x80000u
#define FIELD_ACTOR_ROOMS_PACKED_EXTEND 0xfff00000u

/* The session (main/session.h). */
extern NetSession *data_020ccf94;
/* The town's map (main/acre_map.h). */
extern void *data_021c80bc;
/* How far ahead the floor's item is looked for (2.0), and the last try (0.8). */
extern const fx32 data_ov004_02247780;
extern const fx32 data_ov004_02254aec;
/* The door states' speed (0x400). */
extern const int data_ov004_02254ae8;
extern const s16 FX_SinCosTable_[];

extern int FX_MulFunc(int a, int b);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *sum);

/* The room's objects: the index of the one in front of this console's player's actor (its
 * tile in `x` and `z`; -1 for none, -2 for an item on the floor), and whether one goes with a
 * tile (its byte 0x288). */
extern int func_ov004_0223bbc0(int *x, int *z, u16 *item, u16 *item_2);
extern int func_ov004_0223bb88(unsigned int index);
/* The room's two object entries (0x40 bytes each, data_ov004_02259784): the first when it is
 * in use, its point (0x2c) and angle (0x38). */
extern void *func_ov004_0223cb10(void);
extern void *func_ov004_0223cadc(void *entries, int index);
extern int *func_ov004_0223cb24(void *entry);
extern int func_ov004_0223cb18(void *entry);
/* Requests for states 0x1d (a point and an angle) and 0x1c (a tile and an object). */
extern int func_ov004_0222a494(FieldActor *actor, int x, int z, int angle, int priority, s16 arg);
extern int func_ov004_0222ac24(FieldActor *actor, const int *tile, int index, int priority, s16 arg);
/* The rest of the door states' frame, elsewhere in the overlay: the walk of state 0x8c, the
 * animation by the speed, and the end of the walk. */
extern void func_ov004_022266c4(FieldActor *actor);
extern void func_ov004_02226920(FieldActor *actor);
extern void func_ov004_022268b8(FieldActor *actor);

static FieldActorRoomsWalk *far_walk_of(FieldActor *actor)
{
    return (FieldActorRoomsWalk *) (void *) &actor->work;
}

static int far_is_local(FieldActor *actor)
{
    return Session_IsLocalPlayer(data_020ccf94, actor->player);
}

static Vec3 far_vec(fx32 x, fx32 y, fx32 z)
{
    Vec3 v;
    v.x = x;
    v.y = y;
    v.z = z;
    return v;
}

/* func_ov004_02225de0: a step of the walk to `target` at `*speed` (up to `*max_speed`). Far
 * (1.0 or more on the ground) the speed rises; near, it falls while above the most, else it is
 * how far the position would ease towards the target this frame (the position kept), or 0 on
 * reaching it exactly. While it moves the actor turns towards the target; its speed is the
 * part of `*speed` along its yaw (its size). */
void FieldActorRooms_WalkToward(FieldActor *actor, const Vec3 *target, fx32 *speed, const fx32 *max_speed)
{
    Vec3 saved = actor->position;
    Vec3 delta =
        far_vec((fx32) ((u32) target->x - (u32) actor->position.x), 0, (fx32) ((u32) target->z - (u32) actor->position.z));

    if (Vec_LengthXZ(&delta) < FIELD_ACTOR_ROOMS_NEAR) {
        if (*speed <= *max_speed) {
            FieldActor_EaseValueBy(&actor->position.x, target->x, FIELD_ACTOR_ROOMS_EASE_RATE, *max_speed,
                                   FIELD_ACTOR_ROOMS_EASE_MIN);
            FieldActor_EaseValueBy(&actor->position.z, target->z, FIELD_ACTOR_ROOMS_EASE_RATE, *max_speed,
                                   FIELD_ACTOR_ROOMS_EASE_MIN);
            if (target->x == actor->position.x && target->z == actor->position.z) {
                *speed = 0;
            } else {
                *speed = Vec_DistanceXZ(&actor->position, &saved);
                actor->position = saved;
            }
        } else {
            *speed = FieldActor_Slow(*speed, *max_speed);
        }
    } else {
        *speed = FieldActor_SpeedUp(*speed, *max_speed);
    }

    s16 angle = Math_Atan2(delta.x, delta.z);
    s16 yaw = actor->yaw;
    if (*speed != 0) {
        FieldActor_TurnAngleStep(&yaw, angle);
        FieldActor_SetYaw(actor, &yaw);
    }
    u16 off = (u16) (s16) (yaw - angle);
    int along = FX_MulFunc(*speed, FX_SinCosTable_[(off >> 4) * 2 + 1]);
    int forward = along < 0 ? (int) (0u - (u32) along) : along;
    FieldActor_SetSpeed(actor, &forward);
}
CLEAN_AS(func_ov004_02225de0, FieldActorRooms_WalkToward)

/* func_ov004_02225ef8: what the held tool does in a room; whether an action started. With
 * A held (0x141) the room's first object entry, when in use, asks for state 0x1d to its point
 * and angle (priority 5); else with 0x148 set the tool acts at the aim
 * (FieldActor_TryTargetInScene). */
int FieldActorRooms_TryTool(FieldActor *actor)
{
    if (FIELD_ACTOR_HOLD(actor) != 0) {
        void *entry = func_ov004_0223cadc(func_ov004_0223cb10(), 0);
        if (entry == NULL) {
            return 0;
        }
        const int *point = func_ov004_0223cb24(entry);
        int x = point[0];
        int z = point[2];
        return func_ov004_0222a494(actor, x, z, func_ov004_0223cb18(entry), FIELD_ACTOR_ROOMS_ENTRY_PRIORITY,
                                   FIELD_ACTOR_ROOMS_NO_ARG);
    }
    if (actor->unk_148 != 0) {
        return FieldActor_TryTargetInScene(actor, FieldActor_HeldTool(actor));
    }
    return 0;
}
CLEAN_AS(func_ov004_02225ef8, FieldActorRooms_TryTool)

/* func_ov004_02225f70: linked, a message of one byte (`low` and `high` joined, two values of
 * four bits) goes to the session (handler 0x2c, kind 4). The actor is not used. */
void FieldActorRooms_SendPair(FieldActor *actor, unsigned int low, unsigned int high)
{
    (void) actor;
    if (!Session_IsLinked(data_020ccf94)) {
        return;
    }
    u8 frame[4];
    SessionPlayers_JoinLowHigh(frame, low, high);
    NetSession *session = data_020ccf94;
    Session_BeginMessage(session);
    Session_AppendMessage(session, frame, 1);
    Session_EndMessage(session, FIELD_ACTOR_ROOMS_MESSAGE_HANDLER, FIELD_ACTOR_ROOMS_MESSAGE_KIND);
}
CLEAN_AS(func_ov004_02225f70, FieldActorRooms_SendPair)

/* State 0x18 asked for at the tile of `point` with `number`. */
static void far_request_18_at(FieldActor *actor, const Vec3 *point, int number)
{
    int tile[2] = {0, 0};
    Position_Tile(&tile[0], &tile[1], (const Position *) (const void *) point);
    FieldActor_RequestState18(actor, tile, number, FIELD_ACTOR_ROOMS_PRIORITY, FIELD_ACTOR_ROOMS_NO_ARG);
}

/* The point tried: ahead of the actor by `*distance` when it aims ahead (aim mode 1), else its
 * aim point when within the reach of `reach`. Whether there is one. */
static int far_point(FieldActor *actor, Vec3 *point, const fx32 *distance, int reach)
{
    if (actor->aim_mode == 1) {
        FieldActor_PointAhead(point, actor, &actor->position, (const u16 *) (const void *) &actor->yaw, distance);
        return 1;
    }
    *point = actor->aim_point;
    return FieldActor_InToolReach(actor, point, reach);
}

/* func_ov004_02225fb8: an action on what lies at the aim in a room, for this console's first
 * player in a house's room only; whether one started.
 * - The room's object in front of the player (when it is the one picked, or the actor aims
 *   ahead): state 0x18 with it (no tile), or state 0x1c with its tile when it goes with one.
 * - An item on the floor: at the point (2.0 ahead, or the aim point within reach 14) on layer
 *   1, an item of kind 1: with full pockets state 0x18 at its tile with -1; else with at most
 *   one visitor the tool's target there (FieldActor_FindTarget, FieldActor_ActOnTarget mode
 *   1), with more state 0x18 with -3.
 * - Last, the same at 0.8 ahead (or within reach 12) on layer 0, the target acted on in mode
 *   0. `mode` is not used. */
int FieldActorRooms_TryTarget(FieldActor *actor, int tool, int mode)
{
    (void) mode;
    int x;
    int z;
    Vec3 point;

    if (!SceneKinds_CurrentIsHouseRoom()) {
        return 0;
    }
    if (actor->player != 0) {
        return 0;
    }
    int index = func_ov004_0223bbc0(&x, &z, &actor->item, &actor->unk_822);
    if (index >= 0 && (index == FIELD_ACTOR_PICK_EXTRA(actor) || actor->aim_mode == 1)) {
        if (!func_ov004_0223bb88((unsigned int) index)) {
            int none[2] = {0, 0};
            FieldActor_RequestState18(actor, none, index, FIELD_ACTOR_ROOMS_PRIORITY, FIELD_ACTOR_ROOMS_NO_ARG);
        } else {
            int tile[2] = {(u8) x, (u8) z};
            func_ov004_0222ac24(actor, tile, index, FIELD_ACTOR_ROOMS_PRIORITY, FIELD_ACTOR_ROOMS_NO_ARG);
        }
        return 1;
    }

    AcreMap *map = (AcreMap *) data_021c80bc;
    if (index == FIELD_ACTOR_ROOMS_FLOOR_ITEM &&
        far_point(actor, &point, &data_ov004_02247780, FIELD_ACTOR_ROOMS_REACH_ITEM)) {
        u16 *item = AcreTile_ItemAt(map, &point, FIELD_ACTOR_ROOMS_LAYER_ITEM);
        if (CurrentPockets_FreeSlot() == -1) {
            if (item != NULL && ItemCode_IsKind1((const ItemCode *) item)) {
                far_request_18_at(actor, &point, FIELD_ACTOR_ROOMS_POCKETS_FULL);
                return 1;
            }
        } else if (item != NULL && ItemCode_IsKind1((const ItemCode *) item)) {
            if ((unsigned int) TownObjects_VisitorsHere() <= 1) {
                if (FieldActor_FindTarget(actor, &point, 0, tool) && FieldActor_ActOnTarget(actor, &point, 1)) {
                    return 1;
                }
            } else {
                far_request_18_at(actor, &point, FIELD_ACTOR_ROOMS_VISITORS);
                return 1;
            }
        }
    }

    if (!far_point(actor, &point, &data_ov004_02254aec, FIELD_ACTOR_ROOMS_REACH_LAST)) {
        return 0;
    }
    u16 *item = AcreTile_ItemAt(map, &point, FIELD_ACTOR_ROOMS_LAYER_LAST);
    if (item == NULL || !ItemCode_IsKind1((const ItemCode *) item)) {
        return 0;
    }
    if (CurrentPockets_FreeSlot() == -1) {
        far_request_18_at(actor, &point, FIELD_ACTOR_ROOMS_POCKETS_FULL);
        return 1;
    }
    if ((unsigned int) TownObjects_VisitorsHere() > 1) {
        far_request_18_at(actor, &point, FIELD_ACTOR_ROOMS_VISITORS);
        return 1;
    }
    return FieldActor_FindTarget(actor, &point, 0, tool) && FieldActor_ActOnTarget(actor, &point, 0);
}
CLEAN_AS(func_ov004_02225fb8, FieldActorRooms_TryTarget)

/* func_ov004_0222626c: the alpha of the actor's models (0x8e9, 0 to 31) moved by `step`
 * towards `target`, not past it.
 * QUIRK: going down, the alpha is compared as a signed byte, so a step past 0 also stops at
 * `target`. */
void FieldActorRooms_FadeAlpha(FieldActor *actor, unsigned int target, unsigned int step)
{
    u8 *alpha = &FIELD_ACTOR_BODY_ARG(actor);
    if (*alpha == target) {
        return;
    }
    if (*alpha < target) {
        *alpha = (u8) (*alpha + step);
        if (*alpha > target) {
            *alpha = (u8) target;
        }
    } else {
        *alpha = (u8) (*alpha - step);
        if ((int) (s8) *alpha < (int) target) {
            *alpha = (u8) target;
        }
    }
}
CLEAN_AS(func_ov004_0222626c, FieldActorRooms_FadeAlpha)

/* ---- State 0x8e, walking in */

/* func_ov004_0222629c (state 0x8e's update): the walk's step, the animation by the speed, the
 * move with the collider, the contact bodies and the end of the walk. */
void FieldActorRooms_UpdateWalkIn(FieldActor *actor)
{
    FieldActorRooms_StepWalkIn(actor);
    func_ov004_02226920(actor);
    FieldActor_MoveFree(actor);
    FieldActor_EnterContact(actor);
    func_ov004_022268b8(actor);
}
CLEAN_AS(func_ov004_0222629c, FieldActorRooms_UpdateWalkIn)

/* A step of the walk of the work. */
static void far_step(FieldActor *actor)
{
    FieldActorRoomsWalk *walk = far_walk_of(actor);
    fx32 max_speed = walk->max_speed;
    Vec3 target = walk->point;
    FieldActorRooms_WalkToward(actor, &target, &walk->speed, &max_speed);
}

/* func_ov004_022262c4: a step of the walk to the work's point. */
void FieldActorRooms_StepWalkIn(FieldActor *actor)
{
    far_step(actor);
}
CLEAN_AS(func_ov004_022262c4, FieldActorRooms_StepWalkIn)

/* func_ov004_022262f0 (state 0x8e's message handler): another console's actor asked for state
 * 0x8e (priority 6) to the point kept at 0x8f0.
 * BUG: the point's y is not set: the request carries whatever the stack held there. */
void FieldActorRooms_WalkInMessage(FieldActor *actor, int arg)
{
    Vec3 point;
#ifdef BUGFIX
    point.y = 0;
#endif
    FieldActorRooms_UnpackWalkInPoint(actor->saved.packed, (u32 *) (void *) &point.x, (u32 *) (void *) &point.z);
    FieldActorRooms_RequestWalkIn(actor, &point, FIELD_ACTOR_ROOMS_PRIORITY, arg);
}
CLEAN_AS(func_ov004_022262f0, FieldActorRooms_WalkInMessage)

/* func_ov004_0222631c (state 0x8e's entry): the walk's animation loops from a stop. The actor
 * of this console walks to where it stands (kept packed at 0x8f0) from 6.0 behind it, its
 * facing sorted into four sectors; another console's from 6.0 behind the request's point to
 * it. The work's speeds are 0x400, as is the actor's, and flag 5 is set. */
void FieldActorRooms_EnterWalkIn(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    const Vec3 *requested = (const Vec3 *) (const void *) request->payload;
    Vec3 behind = far_vec(0, 0, 0);
    Vec3 target;

    FieldActor_PlayAnimationLoop(actor, FIELD_ACTOR_ROOMS_WALK_ANIMATION, 0, 0);
    actor->anim.speed = 0;
    switch (AngleSector_Four(actor->yaw)) {
        case 2:
            behind.z += FIELD_ACTOR_ROOMS_WALK_IN_DISTANCE;
            break;
        case 0:
            behind.z -= FIELD_ACTOR_ROOMS_WALK_IN_DISTANCE;
            break;
        case 3:
            behind.x += FIELD_ACTOR_ROOMS_WALK_IN_DISTANCE;
            break;
        case 1:
            behind.x -= FIELD_ACTOR_ROOMS_WALK_IN_DISTANCE;
            break;
        default:
            break;
    }
    if (far_is_local(actor)) {
        target = actor->position;
        FieldActorRooms_PackWalkInPoint(actor->saved.packed, target.x, target.z);
        VEC_Add(&actor->position, &behind, &actor->position);
    } else {
        target = *requested;
        Vec3 start;
        Vec_Add(&start, &target, &behind);
        actor->position = start;
    }
    FieldActorRooms_SetWalkInWork(far_walk_of(actor), target, FIELD_ACTOR_ROOMS_DOOR_SPEED);
    FieldActor_SetSpeed(actor, &data_ov004_02254ae8);
    FieldActor_SetFlag(actor, FIELD_ACTOR_ROOMS_DOOR_FLAG);
}
CLEAN_AS(func_ov004_0222631c, FieldActorRooms_EnterWalkIn)

/* func_ov004_0222642c: the point kept for state 0x8e, unpacked. */
void FieldActorRooms_UnpackWalkInPoint(const u8 *packed, u32 *x, u32 *z)
{
    PackedBytes_UnpackPoint(packed, x, z);
}
CLEAN_AS(func_ov004_0222642c, FieldActorRooms_UnpackWalkInPoint)

/* func_ov004_02226434: the point of state 0x8e kept, packed. */
void FieldActorRooms_PackWalkInPoint(u8 *packed, int x, int z)
{
    PackedBytes_PackPoint(packed, x, z);
}
CLEAN_AS(func_ov004_02226434, FieldActorRooms_PackWalkInPoint)

/* func_ov004_0222643c: state 0x8e's work: the point, and `speed` as the speed and the most. */
void FieldActorRooms_SetWalkInWork(FieldActorRoomsWalk *work, Vec3 point, fx32 speed)
{
    work->point = point;
    work->speed = speed;
    work->max_speed = speed;
}
CLEAN_AS(func_ov004_0222643c, FieldActorRooms_SetWalkInWork)

/* func_ov004_02226454: state 0x8e asked for to `point`; whether it was queued. */
int FieldActorRooms_RequestWalkIn(FieldActor *actor, const Vec3 *point, int priority, int arg)
{
    StateRequest request;
    StateRequest_Construct(&request);
    StateRequest_Set(&request, FIELD_ACTOR_ROOMS_WALK_IN, priority, arg);
    FieldActorRooms_PutWalkInPoint((Vec3 *) (void *) request.payload, *point);
    int queued = FieldActor_QueueRequest(actor, &request);
    StateRequest_Destruct(&request);
    return queued;
}
CLEAN_AS(func_ov004_02226454, FieldActorRooms_RequestWalkIn)

/* func_ov004_02226494: a request's point for state 0x8e. */
void FieldActorRooms_PutWalkInPoint(Vec3 *payload, Vec3 point)
{
    *payload = point;
}
CLEAN_AS(func_ov004_02226494, FieldActorRooms_PutWalkInPoint)

/* ---- State 0x8d, stepping off a door */

/* func_ov004_022264a8 (state 0x8d's update): the walk's step, the animation by the speed, the
 * move with the collider and the contact bodies. */
void FieldActorRooms_UpdateStepOff(FieldActor *actor)
{
    FieldActorRooms_StepStepOff(actor);
    func_ov004_02226920(actor);
    FieldActor_MoveFree(actor);
    FieldActor_EnterContact(actor);
}
CLEAN_AS(func_ov004_022264a8, FieldActorRooms_UpdateStepOff)

/* func_ov004_022264c8: a step of the walk to the work's point. */
void FieldActorRooms_StepStepOff(FieldActor *actor)
{
    far_step(actor);
}
CLEAN_AS(func_ov004_022264c8, FieldActorRooms_StepStepOff)

/* A coordinate of 20 bits made a signed word. */
static u32 far_sign_extend_20(u32 value)
{
    if (value & FIELD_ACTOR_ROOMS_PACKED_SIGN) {
        value |= FIELD_ACTOR_ROOMS_PACKED_EXTEND;
    }
    return value;
}

/* func_ov004_022264f4 (state 0x8d's message handler): another console's actor asked for state
 * 0x8d (priority 6) to the point kept at 0x8f0, its coordinates signed.
 * BUG: the point's y is not set: the request carries whatever the stack held there. */
void FieldActorRooms_StepOffMessage(FieldActor *actor, int arg)
{
    u32 x;
    u32 z;
    Vec3 point;
#ifdef BUGFIX
    point.y = 0;
#endif
    FieldActorRooms_UnpackStepOffPoint(actor->saved.packed, &x, &z);
    point.x = (fx32) far_sign_extend_20(x);
    point.z = (fx32) far_sign_extend_20(z);
    FieldActorRooms_RequestStepOff(actor, &point, FIELD_ACTOR_ROOMS_PRIORITY, arg);
}
CLEAN_AS(func_ov004_022264f4, FieldActorRooms_StepOffMessage)

/* func_ov004_0222654c (state 0x8d's entry): the walk's animation loops (blended over 3 frames,
 * unless it plays already); the work walks to the request's point from the actor's speed, at
 * most 0x400, and the point is kept packed at 0x8f0. */
void FieldActorRooms_EnterStepOff(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    if (actor->animation != FIELD_ACTOR_ROOMS_WALK_ANIMATION) {
        FieldActor_PlayAnimationLoop(actor, FIELD_ACTOR_ROOMS_WALK_ANIMATION, FIELD_ACTOR_ROOMS_STEP_OFF_BLEND, 0);
    }
    Vec3 point = *(const Vec3 *) (const void *) request->payload;
    FieldActorRooms_SetStepOffWork(far_walk_of(actor), point, actor->unk_098, FIELD_ACTOR_ROOMS_DOOR_SPEED);
    FieldActorRooms_PackStepOffPoint(actor->saved.packed, point.x, point.z);
}
CLEAN_AS(func_ov004_0222654c, FieldActorRooms_EnterStepOff)

/* func_ov004_022265b0: the point kept for state 0x8d, unpacked. */
void FieldActorRooms_UnpackStepOffPoint(const u8 *packed, u32 *x, u32 *z)
{
    PackedBytes_UnpackPoint(packed, x, z);
}
CLEAN_AS(func_ov004_022265b0, FieldActorRooms_UnpackStepOffPoint)

/* func_ov004_022265b8: the point of state 0x8d kept, packed. */
void FieldActorRooms_PackStepOffPoint(u8 *packed, int x, int z)
{
    PackedBytes_PackPoint(packed, x, z);
}
CLEAN_AS(func_ov004_022265b8, FieldActorRooms_PackStepOffPoint)

/* func_ov004_022265c0: state 0x8d's work: the point, the speed and the most. */
void FieldActorRooms_SetStepOffWork(FieldActorRoomsWalk *work, Vec3 point, fx32 speed, fx32 max_speed)
{
    work->point = point;
    work->speed = speed;
    work->max_speed = max_speed;
}
CLEAN_AS(func_ov004_022265c0, FieldActorRooms_SetStepOffWork)

/* func_ov004_022265dc: state 0x8d asked for to `point`; whether it was queued. */
int FieldActorRooms_RequestStepOff(FieldActor *actor, const Vec3 *point, int priority, int arg)
{
    StateRequest request;
    StateRequest_Construct(&request);
    StateRequest_Set(&request, FIELD_ACTOR_ROOMS_STEP_OFF, priority, arg);
    FieldActorRooms_PutStepOffPoint((Vec3 *) (void *) request.payload, *point);
    int queued = FieldActor_QueueRequest(actor, &request);
    StateRequest_Destruct(&request);
    return queued;
}
CLEAN_AS(func_ov004_022265dc, FieldActorRooms_RequestStepOff)

/* func_ov004_0222661c: a request's point for state 0x8d. */
void FieldActorRooms_PutStepOffPoint(Vec3 *payload, Vec3 point)
{
    *payload = point;
}
CLEAN_AS(func_ov004_0222661c, FieldActorRooms_PutStepOffPoint)

/* ---- State 0x8c, through a door */

/* func_ov004_02226630 (state 0x8c's update): its walk's step, the animation by the speed, the
 * move with the collider and the contact bodies. At the 15th frame another console's actor
 * going through in way 1 plays the door's sound 0x4d3; at the 10th this console's actor going
 * through in way 1 or 2 takes the scene's exit (0x804). The frames counted. */
void FieldActorRooms_UpdateExit(FieldActor *actor)
{
    func_ov004_022266c4(actor);
    func_ov004_02226920(actor);
    FieldActor_MoveFree(actor);
    FieldActor_EnterContact(actor);

    FieldActorRoomsWalk *walk = far_walk_of(actor);
    unsigned int kind = walk->kind;
    NetSession *session = data_020ccf94;
    if (!Session_IsLocalPlayer(session, actor->player) && walk->frames == FIELD_ACTOR_ROOMS_EXIT_SOUND_FRAME && kind == 1) {
        FieldActor_PlaySound(actor, FIELD_ACTOR_ROOMS_EXIT_SOUND);
    }
    if (Session_IsLocalPlayer(session, actor->player) && kind - 1 <= 1 && walk->frames == FIELD_ACTOR_ROOMS_EXIT_FRAME) {
        SceneExit *exits = (SceneExit *) (uintptr_t) SceneTables_EntryRecord();
        SceneExit_Take(exits, FIELD_ACTOR_ROOMS_EXIT_INDEX(actor));
    }
    walk->frames++;
}
CLEAN_AS(func_ov004_02226630, FieldActorRooms_UpdateExit)
