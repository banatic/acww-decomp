/* More of overlay 4's states of the field actor in the rooms (field_actor_room_states2.h). */
#include "field_actor_room_states2.h"

#include <stdint.h>

#include "clean.h"
#include "main/acre_tile.h"
#include "main/angle_sector.h"
#include "main/camera_control.h"
#include "main/current_pockets.h"
#include "main/event_queue.h"
#include "main/field_actor.h"
#include "main/field_actor_parts.h"
#include "main/frame_ctrl.h"
#include "main/group_params.h"
#include "main/held_item.h"
#include "main/item_code.h"
#include "main/lookups.h"
#include "main/message_receiver.h"
#include "main/packed_bytes.h"
#include "main/place_claim.h"
#include "main/scene_kinds.h"
#include "main/scene_object_base.h"
#include "main/session.h"
#include "main/tile_changes.h"
#include "main/tile_requests.h"
#include "main/town_objects.h"
#include "ov004/room_objects.h"
#include "ov004/room_point_sound.h"
#include "ov004/room_pushes.h"

static_assert(offsetof(FieldActor, position) == 0x5c, "position");
static_assert(offsetof(FieldActor, yaw) == 0x8e, "yaw");
static_assert(offsetof(FieldActor, receiver) == 0xec, "receiver");
static_assert(offsetof(FieldActor, receiver_unk_1E) == 0x10a, "receiver's byte 0x1e");
static_assert(offsetof(FieldActor, link) == 0x12c, "receiver's link");
static_assert(offsetof(FieldActor, anim) == 0x2d0, "animation control");
static_assert(offsetof(FieldActor, anim.flags) == 0x2e4, "animation flags");
static_assert(offsetof(FieldActor, held) == 0x5a0, "held item");
static_assert(offsetof(FieldActor, animation) == 0x704, "animation");
static_assert(offsetof(FieldActor, work) == 0x7d4, "work");
static_assert(offsetof(FieldActor, state) == 0x7f0, "state");
static_assert(offsetof(FieldActor, next_state) == 0x7fc, "next state");
static_assert(offsetof(FieldActor, player) == 0x800, "player");
static_assert(offsetof(FieldActor, unk_810) == 0x810, "tile request");
static_assert(offsetof(FieldActor, unk_818) == 0x818, "verdict");
static_assert(offsetof(FieldActor, unk_81C) == 0x81c, "progress");
static_assert(offsetof(FieldActor, item) == 0x820, "item");
static_assert(offsetof(FieldActor, unk_824) == 0x824, "point 0x824");
static_assert(offsetof(FieldActor, unk_830) == 0x830, "factors");
static_assert(offsetof(FieldActor, saved) == 0x8f0, "saved");
static_assert(offsetof(FieldActor, unk_C84) == 0xc84, "0xc84");
static_assert(offsetof(StateRequest, payload) == 0xc, "request payload");
static_assert(sizeof(FieldActorClaimPlaceWork) <= sizeof(FieldActorWork), "state 0x0e's work");
static_assert(offsetof(FieldActorClaimPlaceWork, side) == 0xa, "state 0x0e's side");
static_assert(offsetof(FieldActorClaimPlaceWork, kind) == 0xb, "state 0x0e's kind");
static_assert(sizeof(FieldActorTakePlaceWork) <= sizeof(FieldActorWork), "state 0x0f's work");
static_assert(offsetof(FieldActorTakePlaceWork, kind) == 0xa, "state 0x0f's kind");
static_assert(offsetof(FieldActorTakePlaceArgs, kind) == 0xc, "state 0x0f's arguments");
static_assert(sizeof(FieldActorTakePlaceArgs) <= sizeof(((StateRequest *) 0)->payload), "state 0x0f's arguments");
static_assert(offsetof(FieldActorTakeItemWork, step) == 5, "state 0x1c's step");
static_assert(offsetof(FieldActorTakeItemArgs, number) == 4, "state 0x1c's arguments");
static_assert(offsetof(FieldActorFurnitureReachWork, toggled) == 0xa, "state 0x1d's work");
static_assert(sizeof(FieldActorFurnitureReachWork) <= sizeof(((StateRequest *) 0)->payload), "state 0x1d's arguments");

/* The states of this file, and those they ask for. */
#define FARS2_TAKE_PLACE 0x0f
#define FARS2_FIXED_POINT 0x12
#define FARS2_TAKE_ITEM 0x1c
#define FARS2_FURNITURE_REACH 0x1d
#define FARS2_FURNITURE_HOLD 0x1e
#define FARS2_FURNITURE_TURN 0x1f
#define FARS2_STATE_20 0x20

#define FARS2_PRIORITY 6
#define FARS2_FURNITURE_PRIORITY 5
#define FARS2_NO_ARG (-1)
/* State 2 asked for at a state's end (with 3 and priority 1). */
#define FARS2_END_STATE2_ARG 3
#define FARS2_END_PRIORITY 1

/* The animations, and the blend into them. */
#define FARS2_BLEND 3
#define FARS2_ANIM_STAND 0
#define FARS2_ANIM_PLACE_SIDE1 7
#define FARS2_ANIM_PLACE_SIDE0 8
#define FARS2_ANIM_TAKE_ITEM 0x19
#define FARS2_ANIM_FURNITURE 0x1a
#define FARS2_ANIM_TURN_PLUS 0x1b
#define FARS2_ANIM_TURN_MINUS 0x1c
#define FARS2_ANIM_STATE_20 0x1d
#define FARS2_ANIM_POCKETS_FULL 0x6c
#define FARS2_ANIM_FIXED_POINT 0x9b
/* The standing animation after a talk, blended over 6 frames (held item too). */
#define FARS2_BLEND_AFTER_TALK 6

/* The actor's flags (FieldActor_SetFlag). */
#define FARS2_FLAG_TAKING 0xd
#define FARS2_FLAG_TALK 0x11

/* Sounds (FieldActor_PlaySound). */
#define FARS2_SOUND_TAKE_ITEM 0x52
#define FARS2_SOUND_CANNOT_TURN 0x6d
#define FARS2_SOUND_TAKE_PLACE 0x4c5

/* How far the stick is pushed (0 to 1.0, FieldActor_Push): above the first a held piece of
 * furniture moves, below it the stick counts as let go; a turn's half of it. */
#define FARS2_PUSH_MOVE 0x333
#define FARS2_PUSH_TURN_DONE 0x19a

/* The item for none. */
#define FARS2_ITEM_NONE 0xfff1
/* The progress word at 0x81c: the pockets' talk has gone on, and its end. */
#define FARS2_PROGRESS_TALK 3
#define FARS2_PROGRESS_ASK_GROUP 5
#define FARS2_PROGRESS_OPEN_GROUP 6
#define FARS2_PROGRESS_DONE 15
/* The animation's speed (1.0) when the group opens. */
#define FARS2_ANIM_SPEED 0x1000

/* 1 while the game is in a room. */
extern u8 data_020e54a8;
/* The session (main/session.h). */
extern NetSession *data_020ccf94;
/* The scene's map. */
extern AcreMap *data_021c80bc;
/* The receiver's names: "obj_etc_error" and "obj_etc_player". */
extern const char data_ov004_02254b00[];
extern const char data_ov004_02254b10[];
/* State 0x12's point. */
extern const Vec3 data_ov004_02247774;

/* Elsewhere in the overlay. */
extern int func_ov004_02229bb4(FieldActor *actor, int priority, int arg);
extern int func_ov004_0222bdf0(FieldActor *actor, int kind, int priority, int arg);
extern void func_ov004_0222b1b4(const u8 *saved, int *x, int *z, s16 *yaw, u8 *side);
extern int func_ov004_0222b214(FieldActor *actor, int x, int z, int yaw, u8 side, int priority, s16 arg);

static int fars2_is_local(FieldActor *actor)
{
    return Session_IsLocalPlayer(data_020ccf94, actor->player);
}

/* The whole frames of a 20.12 frame count, as 16 bits. */
static unsigned int fars2_whole_frames(fx32 frames)
{
    return ((u32) frames << 4) >> 16;
}

/* The state's bar for requests drops to its end value. */
static void fars2_drop_priority(FieldActor *actor)
{
    actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
}

/* The state's end: the bar at its end value and state 2 asked for. */
static void fars2_end(FieldActor *actor)
{
    fars2_drop_priority(actor);
    FieldActor_RequestState2(actor, FARS2_END_STATE2_ARG, FARS2_END_PRIORITY, FARS2_NO_ARG);
}

/* A request for `state` with nothing to carry; whether it was queued. */
static int fars2_request(FieldActor *actor, int state, int priority, int arg)
{
    StateRequest request;
    StateRequest_Construct(&request);
    StateRequest_Set(&request, state, priority, arg);
    int queued = FieldActor_QueueRequest(actor, &request);
    StateRequest_Destruct(&request);
    return queued;
}

/* The three factors at 0x830. */
static void fars2_set_factors(FieldActor *actor, fx32 value)
{
    actor->unk_830[0] = value;
    actor->unk_830[1] = value;
    actor->unk_830[2] = value;
}

/* The receiver taken (flag 0x11), named `name` with `kind` at its byte 0x1e, and the talk
 * asked of its link.
 * REQUIRES: the link is set (the ROM writes through it unchecked). */
static void fars2_open_talk(FieldActor *actor, const char *name, u8 kind)
{
    SceneObjectBase_TakeReceiver((SceneObjectBase *) (void *) actor, (TalkReceiver *) (void *) actor->receiver);
    FieldActor_SetFlag(actor, FARS2_FLAG_TALK);
    MessageReceiver_SetName((MessageReceiver *) (void *) actor->receiver, name);
    actor->receiver_unk_1E = kind;
    actor->link->requested = 1;
}

/* The receiver let go (flag 0x11 cleared) and the talk event finished. */
static void fars2_close_talk(FieldActor *actor)
{
    SceneObjectBase_ReleaseReceiver((SceneObjectBase *) (void *) actor, (TalkReceiver *) (void *) actor->receiver);
    FieldActor_ClearFlag(actor, FARS2_FLAG_TALK);
    EventQueue_FinishKind9();
}

static BOOL fars2_talk_open(const FieldActor *actor)
{
    return actor->link != NULL && actor->link->open != 0;
}

static BOOL fars2_talk_closed(const FieldActor *actor)
{
    return actor->link != NULL && actor->link->open == 0;
}

/* Whether `item` is the item for none, comparing variants when it has them. */
static int fars2_is_no_item(const ItemCode *item)
{
    if (ItemCode_HasVariant(item)) {
        ItemCode none = FARS2_ITEM_NONE;
        int variant = ItemCode_VariantItem(item);
        return variant == ItemCode_VariantItem(&none);
    }
    return *item == FARS2_ITEM_NONE;
}

/* ---- State 0x0e, waiting for a place */

static FieldActorClaimPlaceWork *fars2_claim_of(FieldActor *actor)
{
    return (FieldActorClaimPlaceWork *) (void *) &actor->work;
}

/* func_ov004_0222afd0 (state 0x0e's update): the pose, the body, the contact bodies, then the
 * answer. */
void FieldActorRoomStates2_UpdateClaimPlace(FieldActor *actor)
{
    FieldActorRoomStates2_ClaimPlacePose(actor);
    FieldActor_UpdateBody(actor);
    FieldActor_EnterContact(actor);
    FieldActorRoomStates2_RunClaimPlace(actor);
}
CLEAN_AS(func_ov004_0222afd0, FieldActorRoomStates2_UpdateClaimPlace)

/* func_ov004_0222aff0: another console's actor drops the state's bar. This console's actor
 * reads the place's answer: waiting, nothing; refused, the state ends; given (or any other
 * answer), once the actor faces the work's yaw state 0x0f is asked for with the work's side,
 * point and kind (priority 6). */
void FieldActorRoomStates2_RunClaimPlace(FieldActor *actor)
{
    FieldActorClaimPlaceWork *work = fars2_claim_of(actor);
    if (!fars2_is_local(actor)) {
        fars2_drop_priority(actor);
        return;
    }
    switch (PlaceClaim_Answer3()) {
        case PLACE_CLAIM_WAITING:
            return;
        case PLACE_CLAIM_GIVEN:
            break;
        case PLACE_CLAIM_REFUSED:
            fars2_end(actor);
            return;
        default:
            break;
    }
    if (work->yaw == actor->yaw) {
        FieldActorRoomStates2_RequestTakePlace(actor, work->side, work->x, work->z, work->kind, FARS2_PRIORITY, FARS2_NO_ARG);
    }
}
CLEAN_AS(func_ov004_0222aff0, FieldActorRoomStates2_RunClaimPlace)

/* func_ov004_0222b08c: the actor where it stands, turned to the work's yaw. */
void FieldActorRoomStates2_ClaimPlacePose(FieldActor *actor)
{
    FieldActor_MoveToPose(actor, actor->position.x, actor->position.z, fars2_claim_of(actor)->yaw);
}
CLEAN_AS(func_ov004_0222b08c, FieldActorRoomStates2_ClaimPlacePose)

/* func_ov004_0222b0a8 (state 0x0e's exit): the actor takes the work's yaw. */
void FieldActorRoomStates2_LeaveClaimPlace(FieldActor *actor, int next)
{
    (void) next;
    FieldActor_SetYaw(actor, &fars2_claim_of(actor)->yaw);
}
CLEAN_AS(func_ov004_0222b0a8, FieldActorRoomStates2_LeaveClaimPlace)

/* func_ov004_0222b0b8 (state 0x0e's message handler): the saved point, yaw and side asked for
 * again (priority 6). */
void FieldActorRoomStates2_ClaimPlaceMessage(FieldActor *actor, s16 arg)
{
    int x;
    int z;
    s16 yaw;
    u8 side;
    func_ov004_0222b1b4(actor->saved.packed, &x, &z, &yaw, &side);
    func_ov004_0222b214(actor, x, z, yaw, side, FARS2_PRIORITY, arg);
}
CLEAN_AS(func_ov004_0222b0b8, FieldActorRoomStates2_ClaimPlaceMessage)

/* ---- State 0x0f, taking the place */

static FieldActorTakePlaceWork *fars2_take_place_of(FieldActor *actor)
{
    return (FieldActorTakePlaceWork *) (void *) &actor->work;
}

/* func_ov004_0222ad28 (state 0x0f's update): the ease, the sound, the contact bodies and the
 * end. */
void FieldActorRoomStates2_UpdateTakePlace(FieldActor *actor)
{
    FieldActorRoomStates2_EaseTakePlace(actor);
    FieldActorRoomStates2_SoundTakePlace(actor);
    FieldActor_EnterContact(actor);
    FieldActorRoomStates2_EndTakePlace(actor);
}
CLEAN_AS(func_ov004_0222ad28, FieldActorRoomStates2_UpdateTakePlace)

/* func_ov004_0222ad48: once the animation is over, func_ov004_0222bdf0 with the work's kind
 * (priority 6) and what it answered; 0 before. */
int FieldActorRoomStates2_EndTakePlace(FieldActor *actor)
{
    if (!FrameCtrl_IsDone(&actor->anim)) {
        return 0;
    }
    return func_ov004_0222bdf0(actor, fars2_take_place_of(actor)->kind, FARS2_PRIORITY, FARS2_NO_ARG);
}
CLEAN_AS(func_ov004_0222ad48, FieldActorRoomStates2_EndTakePlace)

/* func_ov004_0222ad78: the body updated; as the animation passes frame 0xd in a room, a sound
 * at the work's point (at the actor's height). */
void FieldActorRoomStates2_SoundTakePlace(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    if (!FrameCtrl_Passed(&actor->anim, 0xd)) {
        return;
    }
    if (data_020e54a8 == 1) {
        const FieldActorTakePlaceWork *work = fars2_take_place_of(actor);
        Vec3 point = {work->x, actor->position.y, work->z};
        RoomPointSound_Play1(&point);
    }
}
CLEAN_AS(func_ov004_0222ad78, FieldActorRoomStates2_SoundTakePlace)

/* func_ov004_0222adcc: this console's actor eases its x (the yaw's bit 0x4000 set) or its z to
 * the work's point (rate 0x399, steps 0x1ec to 0x31); another console's follows what is
 * reported. */
void FieldActorRoomStates2_EaseTakePlace(FieldActor *actor)
{
    if (!fars2_is_local(actor)) {
        FieldActor_FollowReported(actor);
        return;
    }
    const FieldActorTakePlaceWork *work = fars2_take_place_of(actor);
    if (work->yaw & 0x4000) {
        FieldActor_EaseValueBy(&actor->position.x, work->x, 0x399, 0x1ec, 0x31);
    } else {
        FieldActor_EaseValueBy(&actor->position.z, work->z, 0x399, 0x1ec, 0x31);
    }
}
CLEAN_AS(func_ov004_0222adcc, FieldActorRoomStates2_EaseTakePlace)

/* func_ov004_0222ae34 (state 0x0f's exit): the actor at the work's point and yaw. */
void FieldActorRoomStates2_LeaveTakePlace(FieldActor *actor, int next)
{
    (void) next;
    FieldActorTakePlaceWork *work = fars2_take_place_of(actor);
    actor->position.x = work->x;
    actor->position.z = work->z;
    FieldActor_SetYaw(actor, &work->yaw);
}
CLEAN_AS(func_ov004_0222ae34, FieldActorRoomStates2_LeaveTakePlace)

/* func_ov004_0222ae54 (state 0x0f's message handler): an actor already in state 0x0f keeps the
 * argument at 0xc84; otherwise state 0x0f is asked for with the saved side and point (kind 0,
 * priority 6). */
void FieldActorRoomStates2_TakePlaceMessage(FieldActor *actor, s16 arg)
{
    if (actor->state == FARS2_TAKE_PLACE) {
        actor->unk_C84 = arg;
        return;
    }
    u8 side;
    u32 x;
    u32 z;
    FieldActorRoomStates2_GetTakePlaceSaved(actor->saved.packed, &side, &x, &z);
    FieldActorRoomStates2_RequestTakePlace(actor, side, (int) x, (int) z, 0, FARS2_PRIORITY, arg);
}
CLEAN_AS(func_ov004_0222ae54, FieldActorRoomStates2_TakePlaceMessage)

/* func_ov004_0222aea4 (state 0x0f's entry): animation 8 (side 0) or 7, sound 0x4c5; the work
 * gets the request's point and kind and the yaw of the actor's quarter (AngleSector_Four)
 * turned a quarter up (side 0) or down; the side and point are saved. */
void FieldActorRoomStates2_EnterTakePlace(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    const FieldActorTakePlaceArgs *args = (const FieldActorTakePlaceArgs *) (const void *) request->payload;
    u8 side = args->side;
    FieldActor_PlayAnimationOnce(actor, side == 0 ? FARS2_ANIM_PLACE_SIDE0 : FARS2_ANIM_PLACE_SIDE1, FARS2_BLEND, 0);
    FieldActor_PlaySound(actor, FARS2_SOUND_TAKE_PLACE);
    /* QUIRK: the quarter's yaw and the turn wrap to 16 bits. */
    s16 quarter = (s16) (u16) ((u32) AngleSector_Four(actor->yaw) << 14);
    int x = args->x;
    int z = args->z;
    s16 yaw = side == 0 ? (s16) (u16) (quarter + 0x4000) : (s16) (u16) (quarter - 0x4000);
    FieldActorRoomStates2_SetTakePlaceWork(fars2_take_place_of(actor), x, z, yaw, args->kind);
    FieldActorRoomStates2_PutTakePlaceSaved(actor->saved.packed, side, x, z);
}
CLEAN_AS(func_ov004_0222aea4, FieldActorRoomStates2_EnterTakePlace)

/* func_ov004_0222af30: the saved side (byte 0) and point (packed from byte 1). */
void FieldActorRoomStates2_GetTakePlaceSaved(const u8 *saved, u8 *side, u32 *x, u32 *z)
{
    *side = saved[0];
    PackedBytes_UnpackPoint(saved + 1, x, z);
}
CLEAN_AS(func_ov004_0222af30, FieldActorRoomStates2_GetTakePlaceSaved)

/* func_ov004_0222af48: saves the side and the point. */
void FieldActorRoomStates2_PutTakePlaceSaved(u8 *saved, u8 side, int x, int z)
{
    saved[0] = side;
    PackedBytes_PackPoint(saved + 1, x, z);
}
CLEAN_AS(func_ov004_0222af48, FieldActorRoomStates2_PutTakePlaceSaved)

/* func_ov004_0222af58 */
void FieldActorRoomStates2_SetTakePlaceWork(FieldActorTakePlaceWork *work, int x, int z, s16 yaw, u8 kind)
{
    work->x = x;
    work->z = z;
    work->yaw = yaw;
    work->kind = kind;
}
CLEAN_AS(func_ov004_0222af58, FieldActorRoomStates2_SetTakePlaceWork)

/* func_ov004_0222af6c: state 0x0f asked for with a side, a point and a kind; whether it was
 * queued. */
int FieldActorRoomStates2_RequestTakePlace(FieldActor *actor, int side, int x, int z, u8 kind, int priority, s16 arg)
{
    StateRequest request;
    StateRequest_Construct(&request);
    StateRequest_Set(&request, FARS2_TAKE_PLACE, priority, arg);
    FieldActorRoomStates2_SetTakePlaceArgs((FieldActorTakePlaceArgs *) (void *) request.payload, (u8) side, x, z, kind);
    int queued = FieldActor_QueueRequest(actor, &request);
    StateRequest_Destruct(&request);
    return queued;
}
CLEAN_AS(func_ov004_0222af6c, FieldActorRoomStates2_RequestTakePlace)

/* func_ov004_0222afbc */
void FieldActorRoomStates2_SetTakePlaceArgs(FieldActorTakePlaceArgs *args, u8 side, int x, int z, u8 kind)
{
    args->side = side;
    args->x = x;
    args->z = z;
    args->kind = kind;
}
CLEAN_AS(func_ov004_0222afbc, FieldActorRoomStates2_SetTakePlaceArgs)

/* ---- State 0x12, at the overlay's fixed point */

/* func_ov004_0222ac80 (state 0x12's update) */
void FieldActorRoomStates2_UpdateFixedPoint(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    FieldActorRoomStates2_MoveFixedPoint(actor);
    FieldActor_EnterContact(actor);
}
CLEAN_AS(func_ov004_0222ac80, FieldActorRoomStates2_UpdateFixedPoint)

/* func_ov004_0222ac9c: the actor turns to the half turn (rate 0x400) and eases to the point's
 * x and z. */
void FieldActorRoomStates2_MoveFixedPoint(FieldActor *actor)
{
    FieldActor_TurnToHalfTurn(actor, 0x400);
    FieldActor_EaseToXZ(actor, data_ov004_02247774.x, data_ov004_02247774.z);
}
CLEAN_AS(func_ov004_0222ac9c, FieldActorRoomStates2_MoveFixedPoint)

/* func_ov004_0222acc0 (state 0x12's message handler): nothing. */
void FieldActorRoomStates2_FixedPointMessage(FieldActor *actor, int arg)
{
    (void) actor;
    (void) arg;
}
CLEAN_AS(func_ov004_0222acc0, FieldActorRoomStates2_FixedPointMessage)

/* func_ov004_0222acc4 (state 0x12's entry): animation 0x9b loops and the camera snaps to the
 * point. */
void FieldActorRoomStates2_EnterFixedPoint(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) request;
    (void) previous;
    FieldActor_PlayAnimationLoop(actor, FARS2_ANIM_FIXED_POINT, FARS2_BLEND, 0);
    Vec3 point = data_ov004_02247774;
    CameraControl_SnapToPoint(&point);
}
CLEAN_AS(func_ov004_0222acc4, FieldActorRoomStates2_EnterFixedPoint)

/* func_ov004_0222acf0: state 0x12 asked for; whether it was queued. */
int FieldActorRoomStates2_RequestFixedPoint(FieldActor *actor, int priority, int arg)
{
    return fars2_request(actor, FARS2_FIXED_POINT, priority, arg);
}
CLEAN_AS(func_ov004_0222acf0, FieldActorRoomStates2_RequestFixedPoint)

/* ---- State 0x1c, taking an item */

/* State 0x1c's steps. */
enum {
    FARS2_TAKE_WAIT = 0,        /* until the animation is over: into the pockets, or the talk */
    FARS2_TAKE_FULL_UP = 1,     /* the pockets' talk: until the link reports it open */
    FARS2_TAKE_FULL_TALK = 2,   /* the progress word at 0x81c (5, 6, 15) */
    FARS2_TAKE_ASK_TILE = 3,    /* ask for the actor's tile once */
    FARS2_TAKE_FULL_DOWN = 4,   /* until the link reports it closed */
    FARS2_TAKE_DONE = 5,        /* the state ends (each frame) */
    FARS2_TAKE_OPEN_PLAYER = 6, /* "obj_etc_player" once the talk event is allowed */
    FARS2_TAKE_PLAYER_UP = 7,   /* until the link reports it open */
    FARS2_TAKE_PLAYER_DOWN = 8, /* until the link reports it closed */
    FARS2_TAKE_PLAYER_DONE = 9, /* the state ends (each frame) */
    FARS2_TAKE_OPEN_ERROR = 10, /* "obj_etc_error" once the talk event is allowed */
    FARS2_TAKE_ERROR_UP = 11,   /* until the link reports it open */
    FARS2_TAKE_ERROR_DOWN = 12, /* until the link reports it closed, then the state ends */
};

/* The verdict at 0x818 (and the work's copy). */
#define FARS2_VERDICT_WAITING 0
#define FARS2_VERDICT_TAKEN 1
#define FARS2_VERDICT_REFUSED 2

static FieldActorTakeItemWork *fars2_take_item_of(FieldActor *actor)
{
    return (FieldActorTakeItemWork *) (void *) &actor->work;
}

/* The talk opened at `step` with `name` and `kind`, once the talk event is allowed. */
static void fars2_take_item_talk(FieldActor *actor, u8 step, const char *name, u8 kind)
{
    fars2_take_item_of(actor)->step = step;
    fars2_open_talk(actor, name, kind);
}

/* The actor's tile asked for the item once (the answer kept at 0x810), with the standing
 * animation. */
static void fars2_take_item_ask_tile(FieldActor *actor)
{
    if (actor->unk_810 != -1) {
        return;
    }
    fars2_take_item_of(actor)->step = FARS2_TAKE_FULL_DOWN;
    FieldActor_PlayAnimationLoop(actor, FARS2_ANIM_STAND, FARS2_BLEND_AFTER_TALK, FARS2_BLEND_AFTER_TALK);
    actor->unk_810 = TileRequests_AskAtActorTileFor(actor->player, actor->item);
}

/* func_ov004_0222a4e4 (state 0x1c's update) */
void FieldActorRoomStates2_UpdateTakeItem(FieldActor *actor)
{
    FieldActorRoomStates2_WaitTakeItem(actor);
    FieldActor_EnterContact(actor);
    FieldActorRoomStates2_ShrinkTakeItem(actor);
    FieldActorRoomStates2_RunTakeItem(actor);
}
CLEAN_AS(func_ov004_0222a4e4, FieldActorRoomStates2_UpdateTakeItem)

/* func_ov004_0222a504: state 0x1c's steps (FARS2_TAKE_...). At step 0, once the animation is
 * over: with full pockets (CurrentPockets_FreeSlot -1) and an item, the talk event is asked
 * for; allowed, animation 0x6c loops, the held tool acts (tool 4: 0, 9; tool 3: 0x13, 3) and
 * the receiver opens as "obj_etc_player" with kind 2. Otherwise the item goes into the pockets
 * (a copy of it to CurrentPockets_Receive) and the state ends.
 * QUIRK: steps 5 and 9 are not left: they ask for the end each frame until the state changes.
 * REQUIRES: the link is set where a talk opens. */
void FieldActorRoomStates2_RunTakeItem(FieldActor *actor)
{
    FieldActorTakeItemWork *work = fars2_take_item_of(actor);
    switch (work->step) {
        case FARS2_TAKE_WAIT: {
            if (!FrameCtrl_IsDone(&actor->anim)) {
                break;
            }
            if (CurrentPockets_FreeSlot() == -1 && !fars2_is_no_item(&actor->item)) {
                if (!EventQueue_RequestKind9()) {
                    break;
                }
                FieldActor_PlayAnimationLoop(actor, FARS2_ANIM_POCKETS_FULL, FARS2_BLEND, 0);
                int tool = FieldActor_HeldTool(actor);
                if (tool == 4) {
                    HeldItem_Act(actor->held, 0, 9, 0);
                } else if (tool == 3) {
                    HeldItem_Act(actor->held, 0x13, 3, 0);
                }
                fars2_take_item_talk(actor, FARS2_TAKE_FULL_UP, data_ov004_02254b10, 2);
                break;
            }
            u16 copy = actor->item;
            CurrentPockets_Receive(&copy);
            work->step = FARS2_TAKE_DONE;
            break;
        }
        case FARS2_TAKE_FULL_UP:
            if (fars2_talk_open(actor)) {
                work->step = FARS2_TAKE_FULL_TALK;
                actor->unk_81C = FARS2_PROGRESS_TALK;
            }
            break;
        case FARS2_TAKE_FULL_TALK:
            if (actor->unk_81C >= FARS2_PROGRESS_DONE) {
                work->step = FARS2_TAKE_ASK_TILE;
                fars2_take_item_ask_tile(actor);
            } else if (fars2_talk_closed(actor)) {
                if (actor->unk_81C == FARS2_PROGRESS_ASK_GROUP) {
                    if (GroupParams_OpenWithItem29(actor->item)) {
                        actor->unk_81C = FARS2_PROGRESS_OPEN_GROUP;
                    }
                } else if (actor->unk_81C == FARS2_PROGRESS_OPEN_GROUP) {
                    if (GroupParams_CanOpen()) {
                        actor->unk_81C = FARS2_PROGRESS_DONE;
                        actor->anim.speed = FARS2_ANIM_SPEED;
                        if (GroupParams_C4CIs1()) {
                            work->step = FARS2_TAKE_DONE;
                            fars2_close_talk(actor);
                        } else {
                            work->step = FARS2_TAKE_ASK_TILE;
                            fars2_take_item_ask_tile(actor);
                        }
                    }
                }
            }
            break;
        case FARS2_TAKE_ASK_TILE:
            fars2_take_item_ask_tile(actor);
            break;
        case FARS2_TAKE_FULL_DOWN:
            if (fars2_talk_closed(actor)) {
                fars2_close_talk(actor);
                work->step = FARS2_TAKE_DONE;
                FieldActor_PlayAnimationLoop(actor, FARS2_ANIM_STAND, FARS2_BLEND_AFTER_TALK, FARS2_BLEND_AFTER_TALK);
            }
            break;
        case FARS2_TAKE_DONE:
            fars2_end(actor);
            FieldActor_ClearFlag(actor, FARS2_FLAG_TAKING);
            actor->unk_81C = FARS2_PROGRESS_DONE;
            break;
        case FARS2_TAKE_OPEN_PLAYER:
            if (EventQueue_RequestKind9()) {
                fars2_take_item_talk(actor, FARS2_TAKE_PLAYER_UP, data_ov004_02254b10, 0);
            }
            break;
        case FARS2_TAKE_PLAYER_UP:
            if (fars2_talk_open(actor)) {
                work->step = FARS2_TAKE_PLAYER_DOWN;
            }
            break;
        case FARS2_TAKE_PLAYER_DOWN:
            if (fars2_talk_closed(actor)) {
                fars2_close_talk(actor);
                work->step = FARS2_TAKE_PLAYER_DONE;
            }
            break;
        case FARS2_TAKE_PLAYER_DONE:
            fars2_end(actor);
            FieldActor_ClearFlag(actor, FARS2_FLAG_TAKING);
            break;
        case FARS2_TAKE_OPEN_ERROR:
            if (EventQueue_RequestKind9()) {
                fars2_take_item_talk(actor, FARS2_TAKE_ERROR_UP, data_ov004_02254b00, 1);
            }
            break;
        case FARS2_TAKE_ERROR_UP:
            if (fars2_talk_open(actor)) {
                work->step = FARS2_TAKE_ERROR_DOWN;
            }
            break;
        case FARS2_TAKE_ERROR_DOWN:
            if (fars2_talk_closed(actor)) {
                fars2_close_talk(actor);
                fars2_end(actor);
            }
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov004_0222a504, FieldActorRoomStates2_RunTakeItem)

/* func_ov004_0222a94c: once the item's room object has vanished (RoomObjects_VanishPoint)
 * flag 0xd is set and the number forgotten; without the flag (and an object still there) the
 * factors stay. Outside animation 0x19 the factors are 0. From its frame 8 they go from 1.0
 * down by a seventh a frame (the point at 0x824 eased by them); at 0 flag 0xd is cleared. */
void FieldActorRoomStates2_ShrinkTakeItem(FieldActor *actor)
{
    FieldActorTakeItemWork *work = fars2_take_item_of(actor);
    if (!FieldActor_TestFlag(actor, FARS2_FLAG_TAKING)) {
        if (work->number < 0) {
            return;
        }
        if (RoomObjects_VanishPoint(work->number) == NULL) {
            return;
        }
        FieldActor_SetFlag(actor, FARS2_FLAG_TAKING);
        work->number = -1;
    }
    if (actor->animation != FARS2_ANIM_TAKE_ITEM) {
        fars2_set_factors(actor, 0);
        return;
    }
    unsigned int frame = fars2_whole_frames(actor->anim.frame);
    if (frame < 8) {
        return;
    }
    fx32 factor = 0x1000 - (int) ((frame - 8) << 12) / 7;
    if (factor < 0) {
        factor = 0;
        FieldActor_ClearFlag(actor, FARS2_FLAG_TAKING);
    }
    fars2_set_factors(actor, factor);
    FieldActor_EasePoint824(actor, factor);
}
CLEAN_AS(func_ov004_0222a94c, FieldActorRoomStates2_ShrinkTakeItem)

/* func_ov004_0222a9f4: the body updated. Before step 6: while waiting, before frame 7 of the
 * animation, the verdict at 0x818 is taken (1 sets flag 0xd); refused, the state ends as the
 * animation passes frame 7 (without the body's update that frame). */
void FieldActorRoomStates2_WaitTakeItem(FieldActor *actor)
{
    FieldActorTakeItemWork *work = fars2_take_item_of(actor);
    if (work->step >= FARS2_TAKE_OPEN_PLAYER) {
        FieldActor_UpdateBody(actor);
        return;
    }
    if (work->verdict == FARS2_VERDICT_REFUSED) {
        if (FrameCtrl_Passed(&actor->anim, 7)) {
            fars2_end(actor);
            return;
        }
    } else if (work->verdict == FARS2_VERDICT_WAITING) {
        if (fars2_whole_frames(actor->anim.frame) < 7) {
            if (actor->unk_818 == FARS2_VERDICT_REFUSED) {
                work->verdict = FARS2_VERDICT_REFUSED;
            } else if (actor->unk_818 == FARS2_VERDICT_TAKEN) {
                work->verdict = FARS2_VERDICT_TAKEN;
                FieldActor_SetFlag(actor, FARS2_FLAG_TAKING);
            }
        }
    }
    FieldActor_UpdateBody(actor);
}
CLEAN_AS(func_ov004_0222a9f4, FieldActorRoomStates2_WaitTakeItem)

/* func_ov004_0222aa8c (state 0x1c's message handler): nothing. */
void FieldActorRoomStates2_TakeItemMessage(FieldActor *actor, int arg)
{
    (void) actor;
    (void) arg;
}
CLEAN_AS(func_ov004_0222aa8c, FieldActorRoomStates2_TakeItemMessage)

/* func_ov004_0222aa90 (state 0x1c's entry): the work gets the number (step and verdict 0); the
 * tile's centre goes to 0x824 at the height of the room's objects there, the factors are 1.0.
 * From the floor (a negative number) the item on layer 1 at that point becomes the actor's
 * (0x822 and 0x820); with none there the state ends at once. With full pockets in a house's
 * room and an item, the standing animation loops, the item becomes none and the talk follows
 * (step 6). Else with at most one visitor flag 0xd is set and the tile's change finished (from
 * the floor) or the room object's item taken (RoomObjects_TakeWithItem), animation 0x19 and
 * sound 0x52; with more, the error talk (step 10). */
void FieldActorRoomStates2_EnterTakeItem(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    const FieldActorTakeItemArgs *args = (const FieldActorTakeItemArgs *) (const void *) request->payload;
    int number = args->number;
    FieldActorTakeItemWork *work = fars2_take_item_of(actor);
    work->verdict = FARS2_VERDICT_WAITING;
    work->step = FARS2_TAKE_WAIT;
    work->number = number;
    int x = args->x;
    int z = args->z;
    AcreTile_TileCentre(&actor->unk_824, (u32) x, (u32) z);
    actor->unk_824.y = RoomObjects_HeightAtPoint(&actor->unk_824);
    fars2_set_factors(actor, 0x1000);
    if (number < 0) {
        u16 *item = AcreTile_ItemAt(data_021c80bc, &actor->unk_824, 1);
        if (item == NULL) {
            fars2_end(actor);
            return;
        }
        actor->unk_822 = *item;
        actor->item = actor->unk_822;
    }
    if (CurrentPockets_FreeSlot() == -1 && SceneKinds_CurrentIsHouseRoom() != 0 && !fars2_is_no_item(&actor->item)) {
        FieldActor_PlayAnimationLoop(actor, FARS2_ANIM_STAND, FARS2_BLEND, 0);
        work->step = FARS2_TAKE_OPEN_PLAYER;
        actor->unk_822 = FARS2_ITEM_NONE;
        actor->item = actor->unk_822;
        return;
    }
    if ((unsigned int) TownObjects_VisitorsHere() <= 1) {
        if (number < 0) {
            FieldActor_SetFlag(actor, FARS2_FLAG_TAKING);
            TileChangesTile tile = {x, z};
            TileChanges_FinishAtTile(&tile, 1);
        } else {
            RoomObjects_TakeWithItem((unsigned int) number, &actor->item, &actor->unk_822);
        }
        FieldActor_PlayAnimationOnce(actor, FARS2_ANIM_TAKE_ITEM, FARS2_BLEND, 0);
        FieldActor_PlaySound(actor, FARS2_SOUND_TAKE_ITEM);
    } else {
        work->step = FARS2_TAKE_OPEN_ERROR;
        FieldActor_PlayAnimationLoop(actor, FARS2_ANIM_STAND, FARS2_BLEND, 0);
    }
}
CLEAN_AS(func_ov004_0222aa90, FieldActorRoomStates2_EnterTakeItem)

/* func_ov004_0222ac24: state 0x1c asked for with a tile and a number (negative: from the
 * floor); whether it was queued. */
int FieldActorRoomStates2_RequestTakeItem(FieldActor *actor, const int *tile, int number, int priority, s16 arg)
{
    StateRequest request;
    StateRequest_Construct(&request);
    StateRequest_Set(&request, FARS2_TAKE_ITEM, priority, arg);
    u32 copy[2] = {(u32) tile[0], (u32) tile[1]};
    FieldActorRoomStates2_SetTakeItemArgs((FieldActorTakeItemArgs *) (void *) request.payload, copy, (u32) number);
    int queued = FieldActor_QueueRequest(actor, &request);
    StateRequest_Destruct(&request);
    return queued;
}
CLEAN_AS(func_ov004_0222ac24, FieldActorRoomStates2_RequestTakeItem)

/* func_ov004_0222ac74 */
void FieldActorRoomStates2_SetTakeItemArgs(FieldActorTakeItemArgs *args, const u32 *tile, u32 number)
{
    args->x = (u8) tile[0];
    args->z = (u8) tile[1];
    args->number = (int) number;
}
CLEAN_AS(func_ov004_0222ac74, FieldActorRoomStates2_SetTakeItemArgs)

/* ---- State 0x1d, reaching a piece of furniture */

static FieldActorFurnitureReachWork *fars2_reach_of(FieldActor *actor)
{
    return (FieldActorFurnitureReachWork *) (void *) &actor->work;
}

/* func_ov004_0222a28c (state 0x1d's update): the pose, the body, the move, the contact bodies
 * and the shadow; then this console's actor goes on, another's drops the state's bar. */
void FieldActorRoomStates2_UpdateFurnitureReach(FieldActor *actor)
{
    FieldActorRoomStates2_FurnitureReachPose(actor);
    FieldActor_UpdateBody(actor);
    FieldActor_MoveWithCollision(actor);
    FieldActor_EnterContact(actor);
    FieldActor_PlaceShadow(actor);
    if (fars2_is_local(actor)) {
        FieldActorRoomStates2_RunFurnitureReach(actor);
    } else {
        fars2_drop_priority(actor);
    }
}
CLEAN_AS(func_ov004_0222a28c, FieldActorRoomStates2_UpdateFurnitureReach)

/* func_ov004_0222a2e8: with the animation over and the actor at the work's point and yaw,
 * state 0x1e is asked for (released, no blend, priority 5). Otherwise, with A let go: the first
 * time, the room's switch is toggled when the animation still plays; the next, the state
 * ends. */
void FieldActorRoomStates2_RunFurnitureReach(FieldActor *actor)
{
    FieldActorFurnitureReachWork *work = fars2_reach_of(actor);
    if (FrameCtrl_IsDone(&actor->anim) && actor->position.x == work->x && actor->position.z == work->z &&
        work->yaw == actor->yaw) {
        FieldActorRoomStates2_RequestFurnitureHold(actor, 1, 0, FARS2_FURNITURE_PRIORITY, FARS2_NO_ARG);
        return;
    }
    if (FIELD_ACTOR_HOLD(actor) != 0) {
        return;
    }
    if (work->toggled == 0) {
        work->toggled = 1;
        if (!FrameCtrl_IsDone(&actor->anim)) {
            RoomPushes_ToggleSwitch(RoomPushes_Records());
        }
    } else {
        fars2_end(actor);
    }
}
CLEAN_AS(func_ov004_0222a2e8, FieldActorRoomStates2_RunFurnitureReach)

/* func_ov004_0222a390: the actor moves to the work's point and yaw. */
void FieldActorRoomStates2_FurnitureReachPose(FieldActor *actor)
{
    FieldActorFurnitureReachWork *work = fars2_reach_of(actor);
    FieldActor_MoveToPose(actor, work->x, work->z, work->yaw);
}
CLEAN_AS(func_ov004_0222a390, FieldActorRoomStates2_FurnitureReachPose)

/* func_ov004_0222a3ac (state 0x1d's exit): the actor at the work's point and yaw. */
void FieldActorRoomStates2_LeaveFurnitureReach(FieldActor *actor, int next)
{
    (void) next;
    FieldActorFurnitureReachWork *work = fars2_reach_of(actor);
    actor->position.x = work->x;
    actor->position.z = work->z;
    FieldActor_SetYaw(actor, &work->yaw);
}
CLEAN_AS(func_ov004_0222a3ac, FieldActorRoomStates2_LeaveFurnitureReach)

/* func_ov004_0222a3cc (state 0x1d's message handler): the saved point and yaw asked for again
 * (priority 5). */
void FieldActorRoomStates2_FurnitureReachMessage(FieldActor *actor, int arg)
{
    u32 x;
    u32 z;
    s16 yaw;
    FieldActorRoomStates2_GetFurnitureReachSaved(actor->saved.packed, &x, &z, &yaw);
    FieldActorRoomStates2_RequestFurnitureReach(actor, (int) x, (int) z, yaw, FARS2_FURNITURE_PRIORITY, (s16) arg);
}
CLEAN_AS(func_ov004_0222a3cc, FieldActorRoomStates2_FurnitureReachMessage)

/* func_ov004_0222a404 (state 0x1d's entry): animation 0x1a once; the request's point and yaw
 * go to the work (not toggled) and are saved. */
void FieldActorRoomStates2_EnterFurnitureReach(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    FieldActor_PlayAnimationOnce(actor, FARS2_ANIM_FURNITURE, FARS2_BLEND, 0);
    const FieldActorFurnitureReachWork *args = (const FieldActorFurnitureReachWork *) (const void *) request->payload;
    int x = args->x;
    int z = args->z;
    s16 yaw = args->yaw;
    FieldActorRoomStates2_SetFurnitureReachWork(fars2_reach_of(actor), x, z, (u16) yaw);
    FieldActorRoomStates2_PutFurnitureReachSaved(actor->saved.packed, x, z, yaw);
}
CLEAN_AS(func_ov004_0222a404, FieldActorRoomStates2_EnterFurnitureReach)

/* func_ov004_0222a450: the saved point (packed) and yaw (from byte 5). */
void FieldActorRoomStates2_GetFurnitureReachSaved(const u8 *saved, u32 *x, u32 *z, s16 *yaw)
{
    PackedBytes_UnpackPoint(saved, x, z);
    *yaw = PackedBytes_ReadS16(saved + 5);
}
CLEAN_AS(func_ov004_0222a450, FieldActorRoomStates2_GetFurnitureReachSaved)

/* func_ov004_0222a46c: saves the point and yaw. */
void FieldActorRoomStates2_PutFurnitureReachSaved(u8 *saved, int x, int z, int yaw)
{
    PackedBytes_PackPoint(saved, x, z);
    PackedBytes_WriteS16(saved + 5, yaw);
}
CLEAN_AS(func_ov004_0222a46c, FieldActorRoomStates2_PutFurnitureReachSaved)

/* func_ov004_0222a488 */
void FieldActorRoomStates2_SetFurnitureReachWork(FieldActorFurnitureReachWork *work, int x, int z, u16 yaw)
{
    work->x = x;
    work->z = z;
    work->yaw = (s16) yaw;
    work->toggled = 0;
}
CLEAN_AS(func_ov004_0222a488, FieldActorRoomStates2_SetFurnitureReachWork)

/* func_ov004_0222a494: state 0x1d asked for with a point and a yaw; whether it was queued. */
int FieldActorRoomStates2_RequestFurnitureReach(FieldActor *actor, int x, int z, int yaw, int priority, s16 arg)
{
    StateRequest request;
    StateRequest_Construct(&request);
    StateRequest_Set(&request, FARS2_FURNITURE_REACH, priority, arg);
    FieldActorRoomStates2_SetFurnitureReachArgs((FieldActorFurnitureReachWork *) (void *) request.payload, x, z, yaw);
    int queued = FieldActor_QueueRequest(actor, &request);
    StateRequest_Destruct(&request);
    return queued;
}
CLEAN_AS(func_ov004_0222a494, FieldActorRoomStates2_RequestFurnitureReach)

/* func_ov004_0222a4dc: the point and yaw (16 bits) of a request (the work's layout). */
void FieldActorRoomStates2_SetFurnitureReachArgs(FieldActorFurnitureReachWork *args, int x, int z, int yaw)
{
    args->x = x;
    args->z = z;
    args->yaw = (s16) yaw;
}
CLEAN_AS(func_ov004_0222a4dc, FieldActorRoomStates2_SetFurnitureReachArgs)

/* ---- State 0x1e, holding a piece of furniture */

static FieldActorFurnitureHoldWork *fars2_hold_of(FieldActor *actor)
{
    return (FieldActorFurnitureHoldWork *) (void *) &actor->work;
}

/* func_ov004_02229f60 (state 0x1e's update): the body, the move, the contact bodies and the
 * shadow; then this console's actor goes on, another's drops the state's bar. */
void FieldActorRoomStates2_UpdateFurnitureHold(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    FieldActor_MoveWithCollision(actor);
    FieldActor_EnterContact(actor);
    FieldActor_PlaceShadow(actor);
    if (fars2_is_local(actor)) {
        FieldActorRoomStates2_RunFurnitureHold(actor);
    } else {
        fars2_drop_priority(actor);
    }
}
CLEAN_AS(func_ov004_02229f60, FieldActorRoomStates2_UpdateFurnitureHold)

/* func_ov004_02229fb8: state 0x1e's phases. Holding: the stick below 0x333 marks it released;
 * A let go ends the state; pushed above 0x333, with at most one visitor the state's bar drops
 * and the stick's quadrant asks (priority 6) for func_ov004_02229bb4 (2), state 0x20 (0), or,
 * when released, a turn (state 0x1f: 3 one way, 1 the other; refused, no longer released);
 * with more visitors, this console's first player in a house's room opens the talk
 * ("obj_etc_error", kind 1) once the talk event is allowed, waits for it to open and close,
 * lets it go and holds again.
 * REQUIRES: the link is set when the talk opens. */
void FieldActorRoomStates2_RunFurnitureHold(FieldActor *actor)
{
    FieldActorFurnitureHoldWork *work = fars2_hold_of(actor);
    switch (work->phase) {
        case 0:
            if (!work->released && (int) FieldActor_Push(actor) < FARS2_PUSH_MOVE) {
                work->released = 1;
            }
            if (FIELD_ACTOR_HOLD(actor) == 0) {
                fars2_end(actor);
                break;
            }
            if ((int) FieldActor_Push(actor) <= FARS2_PUSH_MOVE) {
                break;
            }
            if ((unsigned int) TownObjects_VisitorsHere() <= 1) {
                fars2_drop_priority(actor);
                switch (FieldActor_PushQuadrant(actor)) {
                    case 2:
                        func_ov004_02229bb4(actor, FARS2_PRIORITY, FARS2_NO_ARG);
                        break;
                    case 0:
                        FieldActorRoomStates2_RequestState20(actor, FARS2_PRIORITY, FARS2_NO_ARG);
                        break;
                    case 3:
                        if (work->released &&
                            !FieldActorRoomStates2_RequestFurnitureTurn(actor, 1, FARS2_PRIORITY, FARS2_NO_ARG)) {
                            work->released = 0;
                        }
                        break;
                    case 1:
                        if (work->released &&
                            !FieldActorRoomStates2_RequestFurnitureTurn(actor, 0, FARS2_PRIORITY, FARS2_NO_ARG)) {
                            work->released = 0;
                        }
                        break;
                    default:
                        break;
                }
            } else if (SceneKinds_CurrentIsHouseRoom() && actor->player == 0) {
                work->phase++;
            }
            break;
        case 1:
            if (EventQueue_RequestKind9()) {
                work->phase++;
                fars2_open_talk(actor, data_ov004_02254b00, 1);
            }
            break;
        case 2:
            if (fars2_talk_open(actor)) {
                work->phase++;
            }
            break;
        case 3:
            if (fars2_talk_closed(actor)) {
                fars2_close_talk(actor);
                work->phase = 0;
            }
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov004_02229fb8, FieldActorRoomStates2_RunFurnitureHold)

/* func_ov004_0222a178 (state 0x1e's message handler): the saved bytes asked for again
 * (priority 5). */
void FieldActorRoomStates2_FurnitureHoldMessage(FieldActor *actor, int arg)
{
    u8 bytes[2];
    FieldActorRoomStates2_GetFurnitureHoldSaved((const FieldActorFurnitureHoldArgs *) (const void *) actor->saved.packed,
                                                &bytes[0], &bytes[1]);
    FieldActorRoomStates2_RequestFurnitureHold(actor, bytes[0], bytes[1], FARS2_FURNITURE_PRIORITY, (s16) arg);
}
CLEAN_AS(func_ov004_0222a178, FieldActorRoomStates2_FurnitureHoldMessage)

/* func_ov004_0222a1ac (state 0x1e's entry): the work starts from the stick's push (0 when the
 * request says released); animation 0x1a loops, blended over 3 frames or not; the two bytes
 * are saved. */
void FieldActorRoomStates2_EnterFurnitureHold(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    const FieldActorFurnitureHoldArgs *args = (const FieldActorFurnitureHoldArgs *) (const void *) request->payload;
    u8 released = args->released;
    u8 blend = args->blend;
    int push = (int) FieldActor_Push(actor);
    if (released) {
        push = 0;
    }
    FieldActorRoomStates2_StartFurnitureHold(fars2_hold_of(actor), push);
    FieldActor_PlayAnimationLoop(actor, FARS2_ANIM_FURNITURE, blend ? FARS2_BLEND : 0, 0);
    FieldActorRoomStates2_PutFurnitureHoldSaved((FieldActorFurnitureHoldArgs *) (void *) actor->saved.packed, released, blend);
}
CLEAN_AS(func_ov004_0222a1ac, FieldActorRoomStates2_EnterFurnitureHold)

/* func_ov004_0222a20c */
void FieldActorRoomStates2_GetFurnitureHoldSaved(const FieldActorFurnitureHoldArgs *saved, u8 *released, u8 *blend)
{
    *released = saved->released;
    *blend = saved->blend;
}
CLEAN_AS(func_ov004_0222a20c, FieldActorRoomStates2_GetFurnitureHoldSaved)

/* func_ov004_0222a218 */
void FieldActorRoomStates2_PutFurnitureHoldSaved(FieldActorFurnitureHoldArgs *saved, u8 released, u8 blend)
{
    saved->released = released;
    saved->blend = blend;
}
CLEAN_AS(func_ov004_0222a218, FieldActorRoomStates2_PutFurnitureHoldSaved)

/* func_ov004_0222a220: released unless pushed above 0x333; phase 0. */
FieldActorFurnitureHoldWork *FieldActorRoomStates2_StartFurnitureHold(FieldActorFurnitureHoldWork *work, int push)
{
    work->released = push > FARS2_PUSH_MOVE ? 0 : 1;
    work->phase = 0;
    return work;
}
CLEAN_AS(func_ov004_0222a220, FieldActorRoomStates2_StartFurnitureHold)

/* func_ov004_0222a23c: state 0x1e asked for with its two bytes; whether it was queued. */
int FieldActorRoomStates2_RequestFurnitureHold(FieldActor *actor, int released, int blend, int priority, s16 arg)
{
    StateRequest request;
    StateRequest_Construct(&request);
    StateRequest_Set(&request, FARS2_FURNITURE_HOLD, priority, arg);
    FieldActorRoomStates2_SetFurnitureHoldArgs((FieldActorFurnitureHoldArgs *) (void *) request.payload, (u8) released,
                                               (u8) blend);
    int queued = FieldActor_QueueRequest(actor, &request);
    StateRequest_Destruct(&request);
    return queued;
}
CLEAN_AS(func_ov004_0222a23c, FieldActorRoomStates2_RequestFurnitureHold)

/* func_ov004_0222a284 */
void FieldActorRoomStates2_SetFurnitureHoldArgs(FieldActorFurnitureHoldArgs *args, u8 released, u8 blend)
{
    args->released = released;
    args->blend = blend;
}
CLEAN_AS(func_ov004_0222a284, FieldActorRoomStates2_SetFurnitureHoldArgs)

/* ---- State 0x1f, turning a piece of furniture */

/* func_ov004_02229d5c (state 0x1f's update) */
void FieldActorRoomStates2_UpdateFurnitureTurn(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    FieldActor_EnterContact(actor);
    FieldActor_PlaceShadow(actor);
    FieldActorRoomStates2_RunFurnitureTurn(actor);
}
CLEAN_AS(func_ov004_02229d5c, FieldActorRoomStates2_UpdateFurnitureTurn)

/* func_ov004_02229d7c: while the animation plays forwards, once it is over it plays back from
 * its end (once, backwards, at one frame a step). Playing back: the stick below 0x19a marks it
 * released and the state's bar drops; released and pushed above 0x19a towards quadrant 3 or 1,
 * state 0x1e is asked for (released, blended); else once the animation is over, state 0x1e (not
 * released, blended; A held) or the state's end. */
void FieldActorRoomStates2_RunFurnitureTurn(FieldActor *actor)
{
    u8 *released = &actor->work.bytes[0];
    if (actor->anim.flags != (FRAME_CTRL_ONCE | FRAME_CTRL_REVERSE)) {
        if (FrameCtrl_IsDone(&actor->anim)) {
            FrameCtrl_Init(&actor->anim, 0, FRAME_CTRL_ONCE | FRAME_CTRL_REVERSE, 0x1000,
                           (u16) fars2_whole_frames(actor->anim.end));
        }
        return;
    }
    if (*released == 0 && (int) FieldActor_Push(actor) < FARS2_PUSH_TURN_DONE) {
        FieldActorRoomStates2_SetFurnitureTurnReleased(released, 1);
    }
    fars2_drop_priority(actor);
    int quadrant = FieldActor_PushQuadrant(actor);
    if (*released != 0 && (int) FieldActor_Push(actor) > FARS2_PUSH_TURN_DONE && (quadrant == 3 || quadrant == 1)) {
        FieldActorRoomStates2_RequestFurnitureHold(actor, 1, 1, FARS2_FURNITURE_PRIORITY, FARS2_NO_ARG);
    } else if (FrameCtrl_IsDone(&actor->anim)) {
        if (FIELD_ACTOR_HOLD(actor) != 0) {
            FieldActorRoomStates2_RequestFurnitureHold(actor, 0, 1, FARS2_FURNITURE_PRIORITY, FARS2_NO_ARG);
        } else {
            FieldActor_RequestState2(actor, FARS2_END_STATE2_ARG, FARS2_END_PRIORITY, FARS2_NO_ARG);
        }
    }
}
CLEAN_AS(func_ov004_02229d7c, FieldActorRoomStates2_RunFurnitureTurn)

/* func_ov004_02229e70 (state 0x1f's message handler): nothing. */
void FieldActorRoomStates2_FurnitureTurnMessage(FieldActor *actor, int arg)
{
    (void) actor;
    (void) arg;
}
CLEAN_AS(func_ov004_02229e70, FieldActorRoomStates2_FurnitureTurnMessage)

/* func_ov004_02229e74 (state 0x1f's entry): animation 0x1b (the request's byte set) or 0x1c
 * once, not released. */
void FieldActorRoomStates2_EnterFurnitureTurn(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    if (request->payload[0] != 0) {
        FieldActor_PlayAnimationOnce(actor, FARS2_ANIM_TURN_PLUS, FARS2_BLEND, 0);
    } else {
        FieldActor_PlayAnimationOnce(actor, FARS2_ANIM_TURN_MINUS, FARS2_BLEND, 0);
    }
    FieldActorRoomStates2_SetFurnitureTurnReleased(&actor->work.bytes[0], 0);
}
CLEAN_AS(func_ov004_02229e74, FieldActorRoomStates2_EnterFurnitureTurn)

/* func_ov004_02229ea8 */
void FieldActorRoomStates2_SetFurnitureTurnReleased(u8 *released, u8 value)
{
    *released = value;
}
CLEAN_AS(func_ov004_02229ea8, FieldActorRoomStates2_SetFurnitureTurnReleased)

/* func_ov004_02229eac: in a room, when the room's furniture can turn that way
 * (RoomPushes_CanTurnPlus for `plus`, else RoomPushes_CanTurnMinus), the turn is started and
 * state 0x1f asked for with `plus`; whether it was queued. Otherwise 0, and this console's first
 * player in a house's room hears sound 0x6d. */
int FieldActorRoomStates2_RequestFurnitureTurn(FieldActor *actor, int plus, int priority, s16 arg)
{
    if (data_020e54a8 != 1) {
        return 0;
    }
    if ((plus != 0 && RoomPushes_CanTurnPlus(RoomPushes_Records())) ||
        (plus == 0 && RoomPushes_CanTurnMinus(RoomPushes_Records()))) {
        StateRequest request;
        StateRequest_Construct(&request);
        StateRequest_Set(&request, FARS2_FURNITURE_TURN, priority, arg);
        FieldActorRoomStates2_SetFurnitureTurnArgs(&request.payload[0], (u8) plus);
        if (plus != 0) {
            RoomPushes_TryTurnPlus(RoomPushes_Records());
        } else {
            RoomPushes_TryTurnMinus(RoomPushes_Records());
        }
        int queued = FieldActor_QueueRequest(actor, &request);
        StateRequest_Destruct(&request);
        return queued;
    }
    if (SceneKinds_CurrentIsHouseRoom() && actor->player == 0) {
        FieldActor_PlaySound(actor, FARS2_SOUND_CANNOT_TURN);
    }
    return 0;
}
CLEAN_AS(func_ov004_02229eac, FieldActorRoomStates2_RequestFurnitureTurn)

/* func_ov004_02229f5c */
void FieldActorRoomStates2_SetFurnitureTurnArgs(u8 *plus, u8 value)
{
    *plus = value;
}
CLEAN_AS(func_ov004_02229f5c, FieldActorRoomStates2_SetFurnitureTurnArgs)

/* ---- State 0x20 (its update is elsewhere) */

/* func_ov004_02229cf8 (state 0x20's message handler): state 0x20 asked for again (priority
 * 6). */
void FieldActorRoomStates2_State20Message(FieldActor *actor, int arg)
{
    FieldActorRoomStates2_RequestState20(actor, FARS2_PRIORITY, arg);
}
CLEAN_AS(func_ov004_02229cf8, FieldActorRoomStates2_State20Message)

/* func_ov004_02229d04 (state 0x20's entry): animation 0x1d once; the work's first byte
 * cleared. */
void FieldActorRoomStates2_EnterState20(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) request;
    (void) previous;
    FieldActor_PlayAnimationOnce(actor, FARS2_ANIM_STATE_20, FARS2_BLEND, 0);
    actor->work.bytes[0] = 0;
}
CLEAN_AS(func_ov004_02229d04, FieldActorRoomStates2_EnterState20)

/* func_ov004_02229d24: state 0x20 asked for; whether it was queued. */
int FieldActorRoomStates2_RequestState20(FieldActor *actor, int priority, int arg)
{
    return fars2_request(actor, FARS2_STATE_20, priority, arg);
}
CLEAN_AS(func_ov004_02229d24, FieldActorRoomStates2_RequestState20)
