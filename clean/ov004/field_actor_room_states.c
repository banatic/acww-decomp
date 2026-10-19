/* More of overlay 4's states of the field actor (field_actor_room_states.h). */
#include "field_actor_room_states.h"

#include <stdint.h>

#include "autoload_2/approach.h"
#include "autoload_2/vector.h"
#include "clean.h"
#include "main/actor.h"
#include "main/angle_sector.h"
#include "main/collision_query.h"
#include "main/effect_system.h"
#include "main/event_queue.h"
#include "main/field_actor.h"
#include "main/field_actor_parts.h"
#include "main/field_collision.h"
#include "main/field_body.h"
#include "main/frame_ctrl.h"
#include "main/layered_model.h"
#include "main/message_receiver.h"
#include "main/music_queue.h"
#include "main/obj_020dd33c.h"
#include "main/packed_bytes.h"
#include "main/place_claim.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/scene_claim.h"
#include "main/scene_exit.h"
#include "main/scene_kinds.h"
#include "main/scene_object_base.h"
#include "main/scene_query.h"
#include "main/scene_tables.h"
#include "main/session.h"
#include "main/sound.h"
#include "ov004/field_actor_rooms.h"
#include "ov004/rmo_telephone.h"
#include "ov004/room_objects.h"
#include "ov004/room_point_sound.h"
#include "field_actor_room_states2.h"
#include "room_pushes.h"

static_assert(offsetof(FieldActor, anim) == 0x2d0, "animation control");
static_assert(offsetof(FieldActor, anim.end) == 0x2d4, "animation length");
static_assert(offsetof(FieldActor, anim.frame) == 0x2d8, "animation frame");
static_assert(offsetof(FieldActor, effect_point) == 0x6e0, "effect point");
static_assert(offsetof(FieldActor, state) == 0x7f0, "state");
static_assert(offsetof(FieldActor, next_state) == 0x7fc, "next state");
static_assert(sizeof(FieldActorHairWork) <= sizeof(FieldActorWork), "the hair states' work");
static_assert(sizeof(Vec3) <= sizeof(FieldActorWork), "state 0x7d's work");

/* The states of this file, and those they ask for. */
#define FARS_HAIR_OFF 0x7a
#define FARS_HAIR_WAIT 0x7b
#define FARS_HAIR_ON 0x7c
#define FARS_PICK_UP 0x7d
#define FARS_ON_PHONE 0x7e
#define FARS_HANG_UP 0x7f
#define FARS_SEQUENCE_8A 0x8a

#define FARS_PRIORITY 6
#define FARS_NO_ARG (-1)
/* State 2 asked for at a state's end (with 3 and priority 1). */
#define FARS_END_STATE2_ARG 3
#define FARS_END_PRIORITY 1

/* The animations the states play, and the blend into them. */
#define FARS_BLEND 3
#define FARS_ANIM_HAIR_OFF 0x6d
#define FARS_ANIM_HAIR_WAIT 0x6e
#define FARS_ANIM_HAIR_ON 0x6f
#define FARS_ANIM_PICK_UP 0x78
#define FARS_ANIM_ON_PHONE 0x79
#define FARS_ANIM_8A_FIRST 0x95
#define FARS_ANIM_8A_SECOND 0x96
#define FARS_ANIM_8A_THIRD 0x97
#define FARS_ANIM_8A_LAST 0x98

/* State 0x44: the alpha it fades in to and its step; the frames of its footsteps. */
#define FARS_FADE_IN_ALPHA 0x1f
#define FARS_FADE_IN_STEP 6

/* State 0x7a clears the head's kind from this frame; state 0x7c starts its effect at the
 * first frame and changes the head from the second. */
#define FARS_HAIR_OFF_FRAME 3
#define FARS_HAIR_EFFECT_FRAME 10
#define FARS_HAIR_ON_FRAME 11
#define FARS_HAIR_EFFECT_SET 0x60

/* State 0x7d: how far beyond the tile ahead (in z) the actor stands (2.0), and its yaw. */
#define FARS_PICK_UP_OFFSET 0x2000
#define FARS_PICK_UP_YAW (-0x8000)

/* State 0x7f: the pick-up animation played backwards (flags 3) at one frame a step. */
#define FARS_HANG_UP_FLAGS 3
#define FARS_HANG_UP_SPEED 0x1000

/* The session (main/session.h). */
extern NetSession *data_020ccf94;
/* The effect sets' default set-up functions. */
extern void *data_020e25d4;

static int fars_is_local(FieldActor *actor)
{
    return Session_IsLocalPlayer(data_020ccf94, actor->player);
}

static FieldActorHairWork *fars_hair_of(FieldActor *actor)
{
    return (FieldActorHairWork *) (void *) &actor->work;
}

static Vec3 *fars_point_of(FieldActor *actor)
{
    return (Vec3 *) (void *) &actor->work;
}

/* The whole frames of a 20.12 frame count, as 16 bits. */
static unsigned int fars_whole_frames(fx32 frames)
{
    return ((u32) frames << 4) >> 16;
}

/* A request for `state` with nothing to carry; whether it was queued. */
static int fars_request(FieldActor *actor, int state, int priority, int arg)
{
    StateRequest request;
    StateRequest_Construct(&request);
    StateRequest_Set(&request, state, priority, arg);
    int queued = FieldActor_QueueRequest(actor, &request);
    StateRequest_Destruct(&request);
    return queued;
}

/* A request for `state` carrying the head's kind and hair colour; whether it was queued. */
static int fars_request_hair(FieldActor *actor, int state, int kind, int hair_color, int priority, s16 arg)
{
    StateRequest request;
    StateRequest_Construct(&request);
    StateRequest_Set(&request, state, priority, arg);
    request.payload[0] = (u8) kind;
    request.payload[1] = (u8) hair_color;
    int queued = FieldActor_QueueRequest(actor, &request);
    StateRequest_Destruct(&request);
    return queued;
}

/* The two bytes of a hair request kept in the work. */
static void fars_keep_hair(FieldActor *actor, const StateRequest *request)
{
    FieldActorHairWork *work = fars_hair_of(actor);
    u8 hair_color = request->payload[1];
    work->kind = request->payload[0];
    work->hair_color = hair_color;
}

/* The head asked to change to its item with `kind` and `hair_color` (no face copied); whether
 * it was taken. */
static int fars_request_head(FieldActor *actor, int kind, int hair_color)
{
    u16 item[2];
    FieldActor_RecordHeadItem(&item[1], actor);
    item[0] = item[1];
    return FieldActor_RequestHead(actor, item, (u8) kind, (u8) hair_color, 0);
}

/* ---- State 0x44, fading in */

/* func_ov004_02227368 (state 0x44's update): the body and its footsteps, the models' alpha up
 * to 31 by 6, the contact bodies and the end of the animation. */
void FieldActorRoomStates_UpdateFadeIn(FieldActor *actor)
{
    FieldActorRoomStates_FadeInSteps(actor);
    FieldActorRooms_FadeAlpha(actor, FARS_FADE_IN_ALPHA, FARS_FADE_IN_STEP);
    FieldActor_EnterContact(actor);
    FieldActorRoomStates_EndFadeIn(actor);
}
CLEAN_AS(func_ov004_02227368, FieldActorRoomStates_UpdateFadeIn)

/* func_ov004_0222738c: once the animation is over: one thing nudged, the state's bar for
 * requests at its end value, state 2 asked for (3, priority 1), and for this console's actor
 * the event of kind 4 or 12 finished. 0 while the animation plays or for another console's
 * actor, else what finishing the event answered. */
int FieldActorRoomStates_EndFadeIn(FieldActor *actor)
{
    if (!FrameCtrl_IsDone(&actor->anim)) {
        return 0;
    }
    FieldActor_NudgeOne(actor);
    actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
    FieldActor_RequestState2(actor, FARS_END_STATE2_ARG, FARS_END_PRIORITY, FARS_NO_ARG);
    if (!fars_is_local(actor)) {
        return 0;
    }
    return EventQueue_FinishKind4Or12();
}
CLEAN_AS(func_ov004_0222738c, FieldActorRoomStates_EndFadeIn)

/* func_ov004_022273ec: the body updated, and a footstep as the animation passes frame 1, 6, 12
 * or 20. */
void FieldActorRoomStates_FadeInSteps(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    if (FrameCtrl_Passed(&actor->anim, 1) || FrameCtrl_Passed(&actor->anim, 6) || FrameCtrl_Passed(&actor->anim, 12) ||
        FrameCtrl_Passed(&actor->anim, 20)) {
        FieldActor_PlayFootstep(actor);
    }
}
CLEAN_AS(func_ov004_022273ec, FieldActorRoomStates_FadeInSteps)

/* ---- State 0x7a, the head's kind cleared */

/* func_ov004_02227254 (state 0x7a's update): the body, then the state's step. */
void FieldActorRoomStates_UpdateHairOff(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    FieldActorRoomStates_StepHairOff(actor);
}
CLEAN_AS(func_ov004_02227254, FieldActorRoomStates_UpdateHairOff)

/* func_ov004_02227268: once the animation is over, state 0x7b is asked for with the work's two
 * bytes (priority 6). Before, from frame 3, while the record gives the head a kind, the head
 * is asked to change to its item with kind 0 and the record's hair colour; once taken, the
 * record's head kind is 0 too. */
void FieldActorRoomStates_StepHairOff(FieldActor *actor)
{
    if (FrameCtrl_IsDone(&actor->anim)) {
        FieldActorHairWork *work = fars_hair_of(actor);
        FieldActorRoomStates_RequestHairWait(actor, work->kind, work->hair_color, FARS_PRIORITY, FARS_NO_ARG);
        return;
    }
    if (fars_whole_frames(actor->anim.frame) < FARS_HAIR_OFF_FRAME) {
        return;
    }
    if (FieldActor_RecordHeadKind(actor) == 0) {
        return;
    }
    u16 item[2];
    FieldActor_RecordHeadItem(&item[1], actor);
    item[0] = item[1];
    if (FieldActor_RequestHead(actor, item, 0, (u8) FieldActor_RecordHairColor(actor), 0)) {
        PlayerRecord_SetHeadKind(FieldActor_Record(actor), 0);
    }
}
CLEAN_AS(func_ov004_02227268, FieldActorRoomStates_StepHairOff)

/* func_ov004_022272f0 (state 0x7a's message handler): nothing. */
void FieldActorRoomStates_HairOffMessage(FieldActor *actor, int arg)
{
    (void) actor;
    (void) arg;
}
CLEAN_AS(func_ov004_022272f0, FieldActorRoomStates_HairOffMessage)

/* func_ov004_022272f4 (state 0x7a's entry): animation 0x6d plays once (blended over 3 frames);
 * the request's two bytes are kept. */
void FieldActorRoomStates_EnterHairOff(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    FieldActor_PlayAnimationOnce(actor, FARS_ANIM_HAIR_OFF, FARS_BLEND, 0);
    fars_keep_hair(actor, request);
}
CLEAN_AS(func_ov004_022272f4, FieldActorRoomStates_EnterHairOff)

/* func_ov004_02227324: state 0x7a asked for with the head's kind and hair colour; whether it
 * was queued. */
int FieldActorRoomStates_RequestHairOff(FieldActor *actor, int kind, int hair_color, int priority, s16 arg)
{
    return fars_request_hair(actor, FARS_HAIR_OFF, kind, hair_color, priority, arg);
}
CLEAN_AS(func_ov004_02227324, FieldActorRoomStates_RequestHairOff)

/* ---- State 0x7b, an animation before the new head */

/* func_ov004_02227190 (state 0x7b's update): the body, then the end of the animation. */
void FieldActorRoomStates_UpdateHairWait(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    FieldActorRoomStates_EndHairWait(actor);
}
CLEAN_AS(func_ov004_02227190, FieldActorRoomStates_UpdateHairWait)

/* func_ov004_022271a4: once the animation is over, state 0x7c is asked for with the work's two
 * bytes (priority 6). */
void FieldActorRoomStates_EndHairWait(FieldActor *actor)
{
    if (FrameCtrl_IsDone(&actor->anim)) {
        FieldActorHairWork *work = fars_hair_of(actor);
        FieldActorRoomStates_RequestHairOn(actor, work->kind, work->hair_color, FARS_PRIORITY, FARS_NO_ARG);
    }
}
CLEAN_AS(func_ov004_022271a4, FieldActorRoomStates_EndHairWait)

/* func_ov004_022271dc (state 0x7b's message handler): nothing. */
void FieldActorRoomStates_HairWaitMessage(FieldActor *actor, int arg)
{
    (void) actor;
    (void) arg;
}
CLEAN_AS(func_ov004_022271dc, FieldActorRoomStates_HairWaitMessage)

/* func_ov004_022271e0 (state 0x7b's entry): animation 0x6e plays once (blended over 3 frames);
 * the request's two bytes are kept. */
void FieldActorRoomStates_EnterHairWait(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    FieldActor_PlayAnimationOnce(actor, FARS_ANIM_HAIR_WAIT, FARS_BLEND, 0);
    fars_keep_hair(actor, request);
}
CLEAN_AS(func_ov004_022271e0, FieldActorRoomStates_EnterHairWait)

/* func_ov004_02227210: state 0x7b asked for with the head's kind and hair colour; whether it
 * was queued. */
int FieldActorRoomStates_RequestHairWait(FieldActor *actor, int kind, int hair_color, int priority, s16 arg)
{
    return fars_request_hair(actor, FARS_HAIR_WAIT, kind, hair_color, priority, arg);
}
CLEAN_AS(func_ov004_02227210, FieldActorRoomStates_RequestHairWait)

/* ---- State 0x7c, the new head */

/* func_ov004_02226fdc (state 0x7c's update): the state's step, then its end. */
void FieldActorRoomStates_UpdateHairOn(FieldActor *actor)
{
    FieldActorRoomStates_StepHairOn(actor);
    FieldActorRoomStates_EndHairOn(actor);
}
CLEAN_AS(func_ov004_02226fdc, FieldActorRoomStates_UpdateHairOn)

/* func_ov004_02226ff0: once the animation is over, with the stick pushed towards the sector
 * the actor faces, state 0x2c is asked for (priority 6). */
void FieldActorRoomStates_EndHairOn(FieldActor *actor)
{
    if (!FrameCtrl_IsDone(&actor->anim)) {
        return;
    }
    if ((int) FieldActor_Push(actor) <= 0) {
        return;
    }
    if (AngleSector_Four((s16) (FieldActor_PushYaw(actor) - actor->yaw)) == 0) {
        FieldActorRoomStates_RequestSpotStepOff(actor, FARS_PRIORITY, FARS_NO_ARG);
    }
}
CLEAN_AS(func_ov004_02226ff0, FieldActorRoomStates_EndHairOn)

/* func_ov004_02227038: the body updated; as the animation passes frame 10 the effect set 0x60
 * starts at the effect point; from frame 11, once, the head is asked to change to its item
 * with the work's kind and hair colour, and once taken both go into the player's record. */
void FieldActorRoomStates_StepHairOn(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    if (FrameCtrl_Passed(&actor->anim, FARS_HAIR_EFFECT_FRAME)) {
        EffectSystem_StartSet(FARS_HAIR_EFFECT_SET, &actor->effect_point, NULL, &data_020e25d4);
    }
    if (fars_whole_frames(actor->anim.frame) < FARS_HAIR_ON_FRAME) {
        return;
    }
    FieldActorHairWork *work = fars_hair_of(actor);
    if (work->applied != 0) {
        return;
    }
    if (fars_request_head(actor, work->kind, work->hair_color)) {
        u8 *record = FieldActor_Record(actor);
        PlayerRecord_SetHeadKind(record, work->kind);
        PlayerRecord_SetHairColor(record, work->hair_color);
        work->applied = 1;
    }
}
CLEAN_AS(func_ov004_02227038, FieldActorRoomStates_StepHairOn)

/* func_ov004_022270d0 (state 0x7c's exit): this console's actor sends its record's head kind
 * and hair colour to the session (FieldActorRooms_SendPair). */
void FieldActorRoomStates_LeaveHairOn(FieldActor *actor)
{
    if (!fars_is_local(actor)) {
        return;
    }
    u8 *record = PlayerRecords_OfPlayer(actor->player);
    unsigned int kind = PlayerRecord_HeadKind(record);
    FieldActorRooms_SendPair(actor, kind, PlayerRecord_HairColor(record));
}
CLEAN_AS(func_ov004_022270d0, FieldActorRoomStates_LeaveHairOn)

/* func_ov004_02227114 (state 0x7c's message handler): nothing. */
void FieldActorRoomStates_HairOnMessage(FieldActor *actor, int arg)
{
    (void) actor;
    (void) arg;
}
CLEAN_AS(func_ov004_02227114, FieldActorRoomStates_HairOnMessage)

/* func_ov004_02227118 (state 0x7c's entry): animation 0x6f plays once (blended over 3 frames);
 * the request's two bytes are kept, the head not changed yet. */
void FieldActorRoomStates_EnterHairOn(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    FieldActor_PlayAnimationOnce(actor, FARS_ANIM_HAIR_ON, FARS_BLEND, 0);
    fars_keep_hair(actor, request);
    fars_hair_of(actor)->applied = 0;
}
CLEAN_AS(func_ov004_02227118, FieldActorRoomStates_EnterHairOn)

/* func_ov004_0222714c: state 0x7c asked for with the head's kind and hair colour; whether it
 * was queued. */
int FieldActorRoomStates_RequestHairOn(FieldActor *actor, int kind, int hair_color, int priority, s16 arg)
{
    return fars_request_hair(actor, FARS_HAIR_ON, kind, hair_color, priority, arg);
}
CLEAN_AS(func_ov004_0222714c, FieldActorRoomStates_RequestHairOn)

/* ---- State 0x7d, the telephone picked up */

/* func_ov004_02226eb0 (state 0x7d's update): where the actor stands, the body, the contact
 * bodies and the end of the animation. */
void FieldActorRoomStates_UpdatePickUp(FieldActor *actor)
{
    FieldActorRoomStates_StandPickUp(actor);
    FieldActor_UpdateBody(actor);
    FieldActor_EnterContact(actor);
    FieldActorRoomStates_EndPickUp(actor);
}
CLEAN_AS(func_ov004_02226eb0, FieldActorRoomStates_UpdatePickUp)

/* func_ov004_02226ed0: once the animation is over, state 0x7e is asked for (priority 6). */
void FieldActorRoomStates_EndPickUp(FieldActor *actor)
{
    if (FrameCtrl_IsDone(&actor->anim)) {
        FieldActorRoomStates_RequestOnPhone(actor, FARS_PRIORITY, FARS_NO_ARG);
    }
}
CLEAN_AS(func_ov004_02226ed0, FieldActorRoomStates_EndPickUp)

/* func_ov004_02226ef8: this console's actor is put at the work's point (x and z) with yaw
 * 0x8000; another console's actor follows what is reported. */
void FieldActorRoomStates_StandPickUp(FieldActor *actor)
{
    const Vec3 *point = fars_point_of(actor);
    if (fars_is_local(actor)) {
        FieldActor_MoveToPose(actor, point->x, point->z, FARS_PICK_UP_YAW);
    } else {
        FieldActor_FollowReported(actor);
    }
}
CLEAN_AS(func_ov004_02226ef8, FieldActorRoomStates_StandPickUp)

/* func_ov004_02226f40 (state 0x7d's message handler): state 0x7d asked for (priority 6). */
void FieldActorRoomStates_PickUpMessage(FieldActor *actor, int arg)
{
    FieldActorRoomStates_RequestPickUp(actor, FARS_PRIORITY, arg);
}
CLEAN_AS(func_ov004_02226f40, FieldActorRoomStates_PickUpMessage)

/* func_ov004_02226f4c (state 0x7d's entry): animation 0x78 plays once (blended over 3 frames);
 * the work's point is the tile ahead moved 2.0 in z; the telephone's animation plays from its
 * start.
 * QUIRK: the current telephone is looked up and its answer not used. */
void FieldActorRoomStates_EnterPickUp(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) request;
    (void) previous;
    Vec3 point;
    FieldActor_PlayAnimationOnce(actor, FARS_ANIM_PICK_UP, FARS_BLEND, 0);
    FieldActor_TileAhead(&point, actor);
    point.z = (fx32) ((u32) point.z + FARS_PICK_UP_OFFSET);
    FieldActorRoomStates_PutPickUpPoint(fars_point_of(actor), point);
    (void) RmoTelephone_Current();
    RmoTelephone_PlayFromStart();
}
CLEAN_AS(func_ov004_02226f4c, FieldActorRoomStates_EnterPickUp)

/* func_ov004_02226f90: state 0x7d's work: the point. */
void FieldActorRoomStates_PutPickUpPoint(Vec3 *work, Vec3 point)
{
    *work = point;
}
CLEAN_AS(func_ov004_02226f90, FieldActorRoomStates_PutPickUpPoint)

/* func_ov004_02226fa4: state 0x7d asked for; whether it was queued. */
int FieldActorRoomStates_RequestPickUp(FieldActor *actor, int priority, int arg)
{
    return fars_request(actor, FARS_PICK_UP, priority, arg);
}
CLEAN_AS(func_ov004_02226fa4, FieldActorRoomStates_RequestPickUp)

/* ---- State 0x7e, on the telephone */

/* func_ov004_02226e34 (state 0x7e's update): the body, the contact bodies, and the actor
 * follows what is reported. */
void FieldActorRoomStates_UpdateOnPhone(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    FieldActor_EnterContact(actor);
    FieldActor_FollowReported(actor);
}
CLEAN_AS(func_ov004_02226e34, FieldActorRoomStates_UpdateOnPhone)

/* func_ov004_02226e50 (state 0x7e's message handler): state 0x7e asked for (priority 6). */
void FieldActorRoomStates_OnPhoneMessage(FieldActor *actor, int arg)
{
    FieldActorRoomStates_RequestOnPhone(actor, FARS_PRIORITY, arg);
}
CLEAN_AS(func_ov004_02226e50, FieldActorRoomStates_OnPhoneMessage)

/* func_ov004_02226e5c (state 0x7e's entry): animation 0x79 loops (blended over 3 frames); the
 * telephone's animation plays from its end.
 * QUIRK: the current telephone is looked up and its answer not used. */
void FieldActorRoomStates_EnterOnPhone(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) request;
    (void) previous;
    FieldActor_PlayAnimationLoop(actor, FARS_ANIM_ON_PHONE, FARS_BLEND, 0);
    (void) RmoTelephone_Current();
    RmoTelephone_PlayFromEnd();
}
CLEAN_AS(func_ov004_02226e5c, FieldActorRoomStates_EnterOnPhone)

/* func_ov004_02226e78: state 0x7e asked for; whether it was queued. */
int FieldActorRoomStates_RequestOnPhone(FieldActor *actor, int priority, int arg)
{
    return fars_request(actor, FARS_ON_PHONE, priority, arg);
}
CLEAN_AS(func_ov004_02226e78, FieldActorRoomStates_RequestOnPhone)

/* ---- State 0x7f, the telephone hung up */

/* func_ov004_02226d4c (state 0x7f's update): the body, the contact bodies and the end of the
 * animation. */
void FieldActorRoomStates_UpdateHangUp(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    FieldActor_EnterContact(actor);
    FieldActorRoomStates_EndHangUp(actor);
}
CLEAN_AS(func_ov004_02226d4c, FieldActorRoomStates_UpdateHangUp)

/* func_ov004_02226d68: once the animation is over, the state's bar for requests is its end
 * value and state 2 is asked for (3, priority 1). */
void FieldActorRoomStates_EndHangUp(FieldActor *actor)
{
    if (FrameCtrl_IsDone(&actor->anim)) {
        actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
        FieldActor_RequestState2(actor, FARS_END_STATE2_ARG, FARS_END_PRIORITY, FARS_NO_ARG);
    }
}
CLEAN_AS(func_ov004_02226d68, FieldActorRoomStates_EndHangUp)

/* func_ov004_02226da8 (state 0x7f's message handler): state 0x7f asked for (priority 6). */
void FieldActorRoomStates_HangUpMessage(FieldActor *actor, int arg)
{
    FieldActorRoomStates_RequestHangUp(actor, FARS_PRIORITY, arg);
}
CLEAN_AS(func_ov004_02226da8, FieldActorRoomStates_HangUpMessage)

/* func_ov004_02226db4 (state 0x7f's entry): the pick-up animation 0x78 (blended over 3 frames)
 * plays backwards from its last whole frame; the telephone's animation plays backwards from its
 * end.
 * QUIRK: the current telephone is looked up and its answer not used. */
void FieldActorRoomStates_EnterHangUp(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) request;
    (void) previous;
    FieldActor_PlayAnimationOnce(actor, FARS_ANIM_PICK_UP, FARS_BLEND, 0);
    unsigned int frames = fars_whole_frames(actor->anim.end);
    FrameCtrl_Init(&actor->anim, frames, FARS_HANG_UP_FLAGS, FARS_HANG_UP_SPEED, (u16) (frames - 1));
    (void) RmoTelephone_Current();
    RmoTelephone_PlayBackFromEnd();
}
CLEAN_AS(func_ov004_02226db4, FieldActorRoomStates_EnterHangUp)

/* func_ov004_02226dfc: state 0x7f asked for; whether it was queued. */
int FieldActorRoomStates_RequestHangUp(FieldActor *actor, int priority, int arg)
{
    return fars_request(actor, FARS_HANG_UP, priority, arg);
}
CLEAN_AS(func_ov004_02226dfc, FieldActorRoomStates_RequestHangUp)

/* ---- State 0x8a, three animations in a row */

/* func_ov004_02226c80 (state 0x8a's update): the body, then the state's step. */
void FieldActorRoomStates_UpdateSequence8A(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    FieldActorRoomStates_StepSequence8A(actor);
}
CLEAN_AS(func_ov004_02226c80, FieldActorRoomStates_UpdateSequence8A)

/* func_ov004_02226c94: once an animation is over the next plays (0x95, 0x96, 0x97, without a
 * blend); after 0x97 the actor stays; after 0x98 state 0x28 is asked for with 0 (priority 6). */
void FieldActorRoomStates_StepSequence8A(FieldActor *actor)
{
    if (!FrameCtrl_IsDone(&actor->anim)) {
        return;
    }
    switch (actor->animation) {
        case FARS_ANIM_8A_FIRST:
            FieldActor_PlayAnimationOnce(actor, FARS_ANIM_8A_SECOND, 0, 0);
            break;
        case FARS_ANIM_8A_SECOND:
            FieldActor_PlayAnimationOnce(actor, FARS_ANIM_8A_THIRD, 0, 0);
            break;
        case FARS_ANIM_8A_THIRD:
            break;
        case FARS_ANIM_8A_LAST:
            FieldActorRoomStates_RequestSpotStay(actor, 0, FARS_PRIORITY, FARS_NO_ARG);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov004_02226c94, FieldActorRoomStates_StepSequence8A)

/* func_ov004_02226cfc (state 0x8a's message handler): nothing. */
void FieldActorRoomStates_Sequence8AMessage(FieldActor *actor, int arg)
{
    (void) actor;
    (void) arg;
}
CLEAN_AS(func_ov004_02226cfc, FieldActorRoomStates_Sequence8AMessage)

/* func_ov004_02226d00 (state 0x8a's entry): animation 0x95 plays once (blended over 3
 * frames). */
void FieldActorRoomStates_EnterSequence8A(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) request;
    (void) previous;
    FieldActor_PlayAnimationOnce(actor, FARS_ANIM_8A_FIRST, FARS_BLEND, 0);
}
CLEAN_AS(func_ov004_02226d00, FieldActorRoomStates_EnterSequence8A)

/* func_ov004_02226d14: state 0x8a asked for; whether it was queued. */
int FieldActorRoomStates_RequestSequence8A(FieldActor *actor, int priority, int arg)
{
    return fars_request(actor, FARS_SEQUENCE_8A, priority, arg);
}
CLEAN_AS(func_ov004_02226d14, FieldActorRoomStates_RequestSequence8A)

/* ---- The states around the exits, the chests and the item shown */

static_assert(offsetof(FieldActor, receiver) == 0xec, "receiver");
static_assert(offsetof(FieldActor, receiver_unk_1E) == 0x10a, "receiver's byte 0x1e");
static_assert(offsetof(FieldActor, link) == 0x12c, "receiver's link");
static_assert(offsetof(FieldActor, anim.speed) == 0x2e0, "animation speed");
static_assert(offsetof(FieldActor, animation) == 0x704, "animation");
static_assert(offsetof(FieldActor, player) == 0x800, "player");
static_assert(offsetof(FieldActor, item) == 0x820, "item");
static_assert(offsetof(FieldActor, unk_822) == 0x822, "0x822");
static_assert(offsetof(FieldActor, saved) == 0x8f0, "saved");
static_assert(offsetof(Actor, last_position) == 0x68, "last position");
static_assert(sizeof(FieldActorExitWalk) <= sizeof(FieldActorWork), "state 0x40's work");
static_assert(offsetof(FieldActorExitWalk, x) == 0x08, "x");
static_assert(offsetof(FieldActorExitWalk, phase) == 0x10, "phase");
static_assert(sizeof(FieldActorExitWalkArgs) <= sizeof(((StateRequest *) 0)->payload), "state 0x40's arguments");
static_assert(sizeof(FieldActorItemOutArgs) <= sizeof(((StateRequest *) 0)->payload), "state 0x36's arguments");
static_assert(offsetof(FieldActorItemOutArgs, kind) == 0x08, "kind");
static_assert(offsetof(FieldActorItemOutArgs, second) == 0x0c, "second");

#define FARS_AT_CHEST 0x2e
#define FARS_CHEST_CLOSE 0x2f
#define FARS_ITEM_OUT 0x36
#define FARS_ITEM_BACK 0x37
#define FARS_EXIT_WALK 0x40
#define FARS_EXIT_RISE 0x41
#define FARS_EXIT_SINK 0x42
#define FARS_FADE_IN_43 0x43
#define FARS_FADE_IN 0x44

/* The priority the message handlers of states 0x41 to 0x44 ask for their state with. */
#define FARS_MESSAGE_PRIORITY 9

/* The animations: standing (loops), walking, the fade-ins of states 0x43 and 0x44, through an
 * exit rising and sinking, the item, the chests' first closing and looking ones. */
#define FARS_ANIM_STAND 0
#define FARS_ANIM_WALK 1
#define FARS_ANIM_FADE_IN_43 0x40
#define FARS_ANIM_FADE_IN 0x41
#define FARS_ANIM_EXIT_RISE 0x3e
#define FARS_ANIM_EXIT_SINK 0x3f
#define FARS_ANIM_ITEM 0x2e
#define FARS_ANIM_CHEST_CLOSE 0x38
#define FARS_ANIM_AT_CHEST 0x3b
#define FARS_CHESTS 3

/* The frames from which the models fade out (by 6 to alpha 0) and the exit is taken. */
#define FARS_EXIT_RISE_FADE_FRAME 6
#define FARS_EXIT_SINK_FADE_FRAME 9
#define FARS_EXIT_FADE_STEP 6
#define FARS_EXIT_TAKE_FRAME 5

/* State 0x40: the door kinds, how far beyond the door's point kind 2 stands (1.0) and the yaw
 * of kind 0; the walk's animation rate (0.23 of the distance moved, times 4), the move's
 * radius and flags, the height of the rise or sink near the point (at most 6/32 of 1.0). */
#define FARS_DOOR_PLAIN 0
#define FARS_DOOR_RISE 1
#define FARS_DOOR_SINK 2
#define FARS_DOOR_BEYOND 0x1000
#define FARS_DOOR_PLAIN_YAW (-0x8000)
#define FARS_WALK_ANIM_FACTOR 0x3ae1
#define FARS_WALK_RADIUS 0xfd7
#define FARS_WALK_FLAGS 0xf
#define FARS_WALK_NEAR 0x1000
#define FARS_WALK_SLOPE 6
/* Its flags: 3 on entering it, 0x18 (the walk keeps the actor's x) for a claimed exit, 0x11
 * while the refusal's talk holds the receiver. */
#define FARS_FLAG_EXIT 3
#define FARS_FLAG_CLAIMED 0x18
#define FARS_FLAG_TALK 0x11
/* The refusal's talk: the receiver's byte 0x1e, and the walk back (state 0x6f) at 0x333,
 * priority 5. */
#define FARS_TALK_KIND 0x15
#define FARS_WALK_BACK_ACCEL 0x333
#define FARS_WALK_BACK_PRIORITY 5

/* States 0x36 and 0x37: the scene with their sounds, the sounds, the frame of 0x63; state 0x10
 * asked for at their end (3, priority 5); the item that makes the byte at 0x8eb 4. */
#define FARS_ITEM_SCENE 9
#define FARS_ITEM_OUT_SOUND 0x4f
#define FARS_ITEM_OUT_LATE_SOUND 0x63
#define FARS_ITEM_OUT_LATE_FRAME 8
#define FARS_ITEM_BACK_SOUND 0x52
#define FARS_ITEM_END_FRAMES 3
#define FARS_ITEM_END_PRIORITY 5
#define FARS_ITEM_MARKED 0x1379
#define FARS_ITEM_MARK 4
#define FARS_ITEM_START_MODE 1

/* Animations played backwards (flags 3) at one frame a step from their last whole frame. */
#define FARS_BACK_FLAGS 3
#define FARS_BACK_SPEED 0x1000

/* The exit the actor takes (an index into the scene's exits). */
#define FARS_EXIT_INDEX(actor) FIELD_ACTOR_FIELD(actor, int, 0x804)
#define FARS_NO_EXIT (-1)

/* The screen's transition (main/screen_transition.h): its state, 0 while the screen is
 * closed. */
extern u8 data_021c75b8;
/* "obj_etc_error": the receiver's name for the refusal's talk. */
extern const char data_ov004_02254b00[];

extern int FX_MulFunc(int a, int b);
extern int FX_Div(int numerator, int denominator);

static FieldActorExitWalk *fars_exit_of(FieldActor *actor)
{
    return (FieldActorExitWalk *) (void *) &actor->work;
}

static SceneExit *fars_exits(void)
{
    return (SceneExit *) (uintptr_t) SceneTables_EntryRecord();
}

/* A footstep as the animation passes frame 1, 6, 11 or 16. */
static void fars_steps(FieldActor *actor)
{
    if (FrameCtrl_Passed(&actor->anim, 1) || FrameCtrl_Passed(&actor->anim, 6) || FrameCtrl_Passed(&actor->anim, 11) ||
        FrameCtrl_Passed(&actor->anim, 16)) {
        FieldActor_PlayFootstep(actor);
    }
}

/* From `frame` of the animation the exit (0x804) is taken, unless the screen is closed. */
static void fars_take_exit(FieldActor *actor)
{
    if (data_021c75b8 == 0) {
        return;
    }
    if (fars_whole_frames(actor->anim.frame) >= FARS_EXIT_TAKE_FRAME) {
        SceneExit_Take(fars_exits(), FARS_EXIT_INDEX(actor));
    }
}

/* While `animation` plays, from `frame` the models fade out. */
static void fars_fade_out(FieldActor *actor, int animation, unsigned int frame)
{
    if (actor->animation == animation && fars_whole_frames(actor->anim.frame) >= frame) {
        FieldActorRooms_FadeAlpha(actor, 0, FARS_EXIT_FADE_STEP);
    }
}

/* Another console's actor: once it moves, `animation` plays (unless it does already); the body;
 * footsteps while `stepping` plays. */
static void fars_follow_exit(FieldActor *actor, int moved, int animation, int stepping)
{
    if (moved != 0 && actor->animation != animation) {
        FieldActor_PlayAnimationOnce(actor, animation, FARS_BLEND, 0);
    }
    FieldActor_UpdateBody(actor);
    if (actor->animation == stepping) {
        fars_steps(actor);
    }
}

/* The animation just started played backwards from its last whole frame. */
static void fars_play_backwards(FieldActor *actor)
{
    unsigned int frames = fars_whole_frames(actor->anim.end);
    FrameCtrl_Init(&actor->anim, frames, FARS_BACK_FLAGS, FARS_BACK_SPEED, (u16) (frames - 1));
}

/* The state's bar for requests at its end value, and state 0x10 asked for (3, priority 5). */
static void fars_end_item(FieldActor *actor)
{
    actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
    FieldActor_RequestState10(actor, FARS_ITEM_END_FRAMES, FARS_ITEM_END_PRIORITY, FARS_NO_ARG);
}

/* ---- State 0x44, fading in (continued) */

/* func_ov004_0222743c (state 0x44's message handler): state 0x44 asked for (priority 9). */
void FieldActorRoomStates_FadeInMessage(FieldActor *actor, int arg)
{
    FieldActorRoomStates_RequestFadeIn(actor, FARS_MESSAGE_PRIORITY, arg);
}
CLEAN_AS(func_ov004_0222743c, FieldActorRoomStates_FadeInMessage)

/* func_ov004_02227448 (state 0x44's entry): animation 0x41 plays once (no blend); the models'
 * alpha is 0. */
void FieldActorRoomStates_EnterFadeIn(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) request;
    (void) previous;
    FieldActor_PlayAnimationOnce(actor, FARS_ANIM_FADE_IN, 0, 0);
    FIELD_ACTOR_BODY_ARG(actor) = 0;
}
CLEAN_AS(func_ov004_02227448, FieldActorRoomStates_EnterFadeIn)

/* func_ov004_02227468: state 0x44 asked for; whether it was queued. */
int FieldActorRoomStates_RequestFadeIn(FieldActor *actor, int priority, int arg)
{
    return fars_request(actor, FARS_FADE_IN, priority, arg);
}
CLEAN_AS(func_ov004_02227468, FieldActorRoomStates_RequestFadeIn)

/* ---- State 0x43, fading in with animation 0x40 */

/* func_ov004_022274a0 (state 0x43's update): the body and its footsteps, the models' alpha up
 * to 31 by 6, the contact bodies and the end of the animation. */
void FieldActorRoomStates_UpdateFadeIn43(FieldActor *actor)
{
    FieldActorRoomStates_FadeIn43Steps(actor);
    FieldActorRooms_FadeAlpha(actor, FARS_FADE_IN_ALPHA, FARS_FADE_IN_STEP);
    FieldActor_EnterContact(actor);
    FieldActorRoomStates_EndFadeIn43(actor);
}
CLEAN_AS(func_ov004_022274a0, FieldActorRoomStates_UpdateFadeIn43)

/* func_ov004_022274c4: once the animation is over: one thing nudged, the state's bar for
 * requests at its end value, state 2 asked for (3, priority 1), and for this console's actor
 * the event of kind 4 or 12 finished. 0 while the animation plays or for another console's
 * actor, else what finishing the event answered. */
int FieldActorRoomStates_EndFadeIn43(FieldActor *actor)
{
    if (!FrameCtrl_IsDone(&actor->anim)) {
        return 0;
    }
    FieldActor_NudgeOne(actor);
    actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
    FieldActor_RequestState2(actor, FARS_END_STATE2_ARG, FARS_END_PRIORITY, FARS_NO_ARG);
    if (!fars_is_local(actor)) {
        return 0;
    }
    return EventQueue_FinishKind4Or12();
}
CLEAN_AS(func_ov004_022274c4, FieldActorRoomStates_EndFadeIn43)

/* func_ov004_02227524: the body updated, and a footstep as the animation passes frame 1, 6, 12
 * or 20. */
void FieldActorRoomStates_FadeIn43Steps(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    if (FrameCtrl_Passed(&actor->anim, 1) || FrameCtrl_Passed(&actor->anim, 6) || FrameCtrl_Passed(&actor->anim, 12) ||
        FrameCtrl_Passed(&actor->anim, 20)) {
        FieldActor_PlayFootstep(actor);
    }
}
CLEAN_AS(func_ov004_02227524, FieldActorRoomStates_FadeIn43Steps)

/* func_ov004_02227574 (state 0x43's message handler): state 0x43 asked for (priority 9). */
void FieldActorRoomStates_FadeIn43Message(FieldActor *actor, int arg)
{
    FieldActorRoomStates_RequestFadeIn43(actor, FARS_MESSAGE_PRIORITY, arg);
}
CLEAN_AS(func_ov004_02227574, FieldActorRoomStates_FadeIn43Message)

/* func_ov004_02227580 (state 0x43's entry): animation 0x40 plays once (no blend); the models'
 * alpha is 0. */
void FieldActorRoomStates_EnterFadeIn43(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) request;
    (void) previous;
    FieldActor_PlayAnimationOnce(actor, FARS_ANIM_FADE_IN_43, 0, 0);
    FIELD_ACTOR_BODY_ARG(actor) = 0;
}
CLEAN_AS(func_ov004_02227580, FieldActorRoomStates_EnterFadeIn43)

/* func_ov004_022275a0: state 0x43 asked for; whether it was queued. */
int FieldActorRoomStates_RequestFadeIn43(FieldActor *actor, int priority, int arg)
{
    return fars_request(actor, FARS_FADE_IN_43, priority, arg);
}
CLEAN_AS(func_ov004_022275a0, FieldActorRoomStates_RequestFadeIn43)

/* ---- State 0x42, through an exit sinking */

/* func_ov004_022275d8 (state 0x42's update): this console's actor: the body and its
 * footsteps, the fading out and the exit; another console's: it follows what is reported,
 * then the fading out. */
void FieldActorRoomStates_UpdateExitSink(FieldActor *actor)
{
    if (fars_is_local(actor)) {
        FieldActorRoomStates_StepExitSink(actor);
        FieldActorRoomStates_FadeExitSink(actor);
        FieldActorRoomStates_TakeExitSink(actor);
    } else {
        FieldActorRoomStates_FollowExitSink(actor, FieldActor_StepTowardReported(actor));
        FieldActorRoomStates_FadeExitSink(actor);
    }
}
CLEAN_AS(func_ov004_022275d8, FieldActorRoomStates_UpdateExitSink)

/* func_ov004_02227624: from frame 5, unless the screen is closed, the scene's exit (0x804) is
 * taken. */
void FieldActorRoomStates_TakeExitSink(FieldActor *actor)
{
    fars_take_exit(actor);
}
CLEAN_AS(func_ov004_02227624, FieldActorRoomStates_TakeExitSink)

/* func_ov004_02227664: while animation 0x3f plays, from frame 9 the models fade out by 6. */
void FieldActorRoomStates_FadeExitSink(FieldActor *actor)
{
    fars_fade_out(actor, FARS_ANIM_EXIT_SINK, FARS_EXIT_SINK_FADE_FRAME);
}
CLEAN_AS(func_ov004_02227664, FieldActorRoomStates_FadeExitSink)

/* func_ov004_02227694: another console's actor: once it moves, animation 0x3f plays (blended
 * over 3 frames, unless it plays already); the body; the footsteps at frames 1, 6, 11 and 16.
 * QUIRK: the footsteps are those of animation 0x3e, which this state does not play. */
void FieldActorRoomStates_FollowExitSink(FieldActor *actor, int moved)
{
    fars_follow_exit(actor, moved, FARS_ANIM_EXIT_SINK, FARS_ANIM_EXIT_RISE);
}
CLEAN_AS(func_ov004_02227694, FieldActorRoomStates_FollowExitSink)

/* func_ov004_02227708: the body, and the footsteps at frames 1, 6, 11 and 16. */
void FieldActorRoomStates_StepExitSink(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    fars_steps(actor);
}
CLEAN_AS(func_ov004_02227708, FieldActorRoomStates_StepExitSink)

/* func_ov004_02227758 (state 0x42's message handler): state 0x42 asked for (priority 9). */
void FieldActorRoomStates_ExitSinkMessage(FieldActor *actor, int arg)
{
    FieldActorRoomStates_RequestExitSink(actor, FARS_MESSAGE_PRIORITY, arg);
}
CLEAN_AS(func_ov004_02227758, FieldActorRoomStates_ExitSinkMessage)

/* func_ov004_02227764 (state 0x42's entry): another console's actor stands (the standing
 * animation loops, blended over 3 frames); this console's goes on with what state 0x40
 * started. */
void FieldActorRoomStates_EnterExitSink(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) request;
    (void) previous;
    if (!fars_is_local(actor)) {
        FieldActor_PlayAnimationLoop(actor, FARS_ANIM_STAND, FARS_BLEND, FARS_BLEND);
    }
}
CLEAN_AS(func_ov004_02227764, FieldActorRoomStates_EnterExitSink)

/* func_ov004_02227794: state 0x42 asked for; whether it was queued. */
int FieldActorRoomStates_RequestExitSink(FieldActor *actor, int priority, int arg)
{
    return fars_request(actor, FARS_EXIT_SINK, priority, arg);
}
CLEAN_AS(func_ov004_02227794, FieldActorRoomStates_RequestExitSink)

/* ---- State 0x41, through an exit rising */

/* func_ov004_022277cc (state 0x41's update): this console's actor: the body and its
 * footsteps, the fading out and the exit; another console's: it follows what is reported,
 * then the fading out. */
void FieldActorRoomStates_UpdateExitRise(FieldActor *actor)
{
    if (fars_is_local(actor)) {
        FieldActorRoomStates_StepExitRise(actor);
        FieldActorRoomStates_FadeExitRise(actor);
        FieldActorRoomStates_TakeExitRise(actor);
    } else {
        FieldActorRoomStates_FollowExitRise(actor, FieldActor_StepTowardReported(actor));
        FieldActorRoomStates_FadeExitRise(actor);
    }
}
CLEAN_AS(func_ov004_022277cc, FieldActorRoomStates_UpdateExitRise)

/* func_ov004_02227818: from frame 5, unless the screen is closed, the scene's exit (0x804) is
 * taken. */
void FieldActorRoomStates_TakeExitRise(FieldActor *actor)
{
    fars_take_exit(actor);
}
CLEAN_AS(func_ov004_02227818, FieldActorRoomStates_TakeExitRise)

/* func_ov004_02227858: while animation 0x3e plays, from frame 6 the models fade out by 6. */
void FieldActorRoomStates_FadeExitRise(FieldActor *actor)
{
    fars_fade_out(actor, FARS_ANIM_EXIT_RISE, FARS_EXIT_RISE_FADE_FRAME);
}
CLEAN_AS(func_ov004_02227858, FieldActorRoomStates_FadeExitRise)

/* func_ov004_02227888: another console's actor: once it moves, animation 0x3e plays (blended
 * over 3 frames, unless it plays already); the body; while 0x3e plays, the footsteps at frames
 * 1, 6, 11 and 16. */
void FieldActorRoomStates_FollowExitRise(FieldActor *actor, int moved)
{
    fars_follow_exit(actor, moved, FARS_ANIM_EXIT_RISE, FARS_ANIM_EXIT_RISE);
}
CLEAN_AS(func_ov004_02227888, FieldActorRoomStates_FollowExitRise)

/* func_ov004_022278fc: the body, and the footsteps at frames 1, 6, 11 and 16. */
void FieldActorRoomStates_StepExitRise(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    fars_steps(actor);
}
CLEAN_AS(func_ov004_022278fc, FieldActorRoomStates_StepExitRise)

/* func_ov004_0222794c (state 0x41's message handler): state 0x41 asked for (priority 9). */
void FieldActorRoomStates_ExitRiseMessage(FieldActor *actor, int arg)
{
    FieldActorRoomStates_RequestExitRise(actor, FARS_MESSAGE_PRIORITY, arg);
}
CLEAN_AS(func_ov004_0222794c, FieldActorRoomStates_ExitRiseMessage)

/* func_ov004_02227958 (state 0x41's entry): for this console's actor animation 0x3e loops
 * (blended over 3 frames, unless it plays already); another console's stands (the standing
 * animation loops). */
void FieldActorRoomStates_EnterExitRise(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) request;
    (void) previous;
    if (fars_is_local(actor)) {
        if (actor->animation != FARS_ANIM_EXIT_RISE) {
            FieldActor_PlayAnimationLoop(actor, FARS_ANIM_EXIT_RISE, FARS_BLEND, 0);
        }
    } else {
        FieldActor_PlayAnimationLoop(actor, FARS_ANIM_STAND, FARS_BLEND, FARS_BLEND);
    }
}
CLEAN_AS(func_ov004_02227958, FieldActorRoomStates_EnterExitRise)

/* func_ov004_022279a0: state 0x41 asked for; whether it was queued. */
int FieldActorRoomStates_RequestExitRise(FieldActor *actor, int priority, int arg)
{
    return fars_request(actor, FARS_EXIT_RISE, priority, arg);
}
CLEAN_AS(func_ov004_022279a0, FieldActorRoomStates_RequestExitRise)

/* ---- State 0x40, walking to an exit */

/* func_ov004_022279d8 (state 0x40's update): the ease to the exit's point and yaw, the
 * animation, the move with the collider and the rise or sink, the contact bodies, then the
 * phase. */
void FieldActorRoomStates_UpdateExitWalk(FieldActor *actor)
{
    FieldActorRoomStates_StandExitWalk(actor);
    FieldActorRoomStates_AnimateExitWalk(actor);
    FieldActorRoomStates_MoveExitWalk(actor);
    FieldActor_EnterContact(actor);
    FieldActorRoomStates_RunExitWalk(actor);
}
CLEAN_AS(func_ov004_022279d8, FieldActorRoomStates_UpdateExitWalk)

/* func_ov004_02227a00: state 0x40's phase.
 * At the point: once the actor stands at the work's point at its yaw, state 0x41 (door kind 1)
 * or 0x42 is asked for (priority 6). Unless it walks (animation 1), while animation 0x3e
 * plays from frame 6 the models fade out by 6; then from frame 5, unless the screen is closed,
 * the scene's exit (0x804) is taken.
 * A claim (main's scene_claim.h): the exit is claimed (until SceneClaim_TakeExit agrees), then
 * its answer waited for. Given, the exit is taken, or, when the claimed exit is placed, the
 * phase is "at the point" again with animation 0x3e (blended over 3 frames). Refused, the
 * actor takes its receiver (flag 0x11, named "obj_etc_error", byte 0x1e 0x15) and asks its
 * link for the talk; once the talk has opened and closed, the receiver is let go (flag 0x11
 * cleared), the state's bar for requests is its end value and state 0x6f is asked for to the
 * claimed exit's next tile (0x333, priority 5), each frame until it is taken. */
void FieldActorRoomStates_RunExitWalk(FieldActor *actor)
{
    FieldActorExitWalk *work = fars_exit_of(actor);
    if (work->phase == FIELD_ACTOR_EXIT_AT_POINT) {
        if (actor->position.x == work->x && actor->position.z == work->z && work->yaw == actor->yaw) {
            if (work->door_kind == FARS_DOOR_RISE) {
                FieldActorRoomStates_RequestExitRise(actor, FARS_PRIORITY, FARS_NO_ARG);
            } else {
                FieldActorRoomStates_RequestExitSink(actor, FARS_PRIORITY, FARS_NO_ARG);
            }
        }
        if (actor->animation == FARS_ANIM_WALK) {
            return;
        }
        fars_fade_out(actor, FARS_ANIM_EXIT_RISE, FARS_EXIT_RISE_FADE_FRAME);
        fars_take_exit(actor);
        return;
    }

    SceneClaimExit *claim = (SceneClaimExit *) (uintptr_t) SceneClaim_Exit();
    switch (work->phase) {
        case FIELD_ACTOR_EXIT_CLAIM:
            if (!SceneClaim_TakeExit(FARS_EXIT_INDEX(actor))) {
                break;
            }
            work->phase++;
            /* fall through */
        case FIELD_ACTOR_EXIT_ANSWER:
            switch (SceneClaimExit_Answer(claim)) {
                case SCENE_CLAIM_WAITING:
                    break;
                case SCENE_CLAIM_GIVEN:
                    if (!SceneClaimExit_Placed(claim)) {
                        SceneExit_Take(fars_exits(), FARS_EXIT_INDEX(actor));
                    } else {
                        work->phase = FIELD_ACTOR_EXIT_AT_POINT;
                        FieldActor_PlayAnimationOnce(actor, FARS_ANIM_EXIT_RISE, FARS_BLEND, 0);
                    }
                    break;
                case SCENE_CLAIM_REFUSED:
                    SceneObjectBase_TakeReceiver((SceneObjectBase *) (void *) actor,
                                                 (TalkReceiver *) (void *) actor->receiver);
                    FieldActor_SetFlag(actor, FARS_FLAG_TALK);
                    MessageReceiver_SetName((MessageReceiver *) (void *) actor->receiver, data_ov004_02254b00);
                    actor->receiver_unk_1E = FARS_TALK_KIND;
                    actor->link->requested = 1;
                    work->phase++;
                    break;
                default:
                    break;
            }
            break;
        case FIELD_ACTOR_EXIT_TALK:
            if (actor->link != NULL && actor->link->open != 0) {
                work->phase++;
            }
            break;
        case FIELD_ACTOR_EXIT_TALKING:
            if (actor->link != NULL && actor->link->open == 0) {
                Vec3 tile = *(const Vec3 *) (uintptr_t) SceneClaimExit_NextTile(claim);
                SceneObjectBase_ReleaseReceiver((SceneObjectBase *) (void *) actor, (TalkReceiver *) (void *) actor->receiver);
                FieldActor_ClearFlag(actor, FARS_FLAG_TALK);
                actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
                FieldActor_RequestState6F(actor, &tile, FARS_WALK_BACK_ACCEL, FARS_WALK_BACK_PRIORITY, FARS_NO_ARG);
            }
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov004_02227a00, FieldActorRoomStates_RunExitWalk)

/* func_ov004_02227bf4: the move with the collider (the actor's own, 0x7a4, when the state's
 * flag at 0xb48 is set, else one made for the move; radius 0xfd7, flags 0xf), the height the
 * floor's; for door kinds 1 and 2, within 1.0 of the work's point the actor is raised (kind 1)
 * or lowered by 6/32 of how much nearer than 1.0 it is. */
void FieldActorRoomStates_MoveExitWalk(FieldActor *actor)
{
    Vec3 *position = &actor->position;
    CollisionContacts made;
    CollisionContacts_Construct(&made);
    s16 yaw = actor->yaw;
    CollisionContacts *contacts = &made;
    if (FieldActor_StateFlagB48(actor, actor->state) != 0) {
        contacts = (CollisionContacts *) (void *) ((u8 *) actor + FIELD_ACTOR_COLLIDER);
    }
    CollisionQuery_Move(contacts, position, &FieldActor_Base(actor)->last_position, yaw, FARS_WALK_RADIUS, actor,
                        FARS_WALK_FLAGS);
    CollisionContacts_Destroy(&made);
    position->y = CollisionQuery_FloorHeight(0);

    const FieldActorExitWalk *work = fars_exit_of(actor);
    int kind = work->door_kind;
    if (kind != FARS_DOOR_RISE && kind != FARS_DOOR_SINK) {
        return;
    }
    Vec3 point = {work->x, position->y, work->z};
    if (Vec_DistanceXZ(&point, position) >= FARS_WALK_NEAR) {
        return;
    }
    int height = FARS_WALK_SLOPE * FX_Div(FARS_WALK_NEAR - Vec_DistanceXZ(&point, position), FARS_WALK_NEAR);
    if (kind == FARS_DOOR_RISE) {
        position->y += height >> 5;
    } else {
        position->y -= height >> 5;
    }
}
CLEAN_AS(func_ov004_02227bf4, FieldActorRoomStates_MoveExitWalk)

/* func_ov004_02227cb0: the body; while walking (animation 1) the animation's rate is 0.23 of
 * the distance moved this frame, times 4 (taken unless it exceeds the animation's length), the
 * feet touch the ground, and once the actor does not move it stands (the standing animation
 * loops, blended over 3 frames); while another animation than standing plays, the footsteps at
 * frames 1, 6, 11 and 16. */
void FieldActorRoomStates_AnimateExitWalk(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    int animation = actor->animation;
    if (animation == FARS_ANIM_WALK) {
        Vec3 moved;
        Vec_Subtract(&moved, &actor->position, &FieldActor_Base(actor)->last_position);
        fx32 rate = (fx32) ((u32) FX_MulFunc(Vec_LengthXZ(&moved), FARS_WALK_ANIM_FACTOR) << 2);
        if (rate <= actor->anim.end) {
            actor->anim.speed = rate;
        }
        FieldActor_Footfall(actor);
        if (rate == 0) {
            FieldActor_PlayAnimationLoop(actor, FARS_ANIM_STAND, FARS_BLEND, 0);
        }
    } else if (animation != FARS_ANIM_STAND) {
        fars_steps(actor);
    }
}
CLEAN_AS(func_ov004_02227cb0, FieldActorRoomStates_AnimateExitWalk)

/* func_ov004_02227d60: the actor eased to the work's point and yaw. */
void FieldActorRoomStates_StandExitWalk(FieldActor *actor)
{
    const FieldActorExitWalk *work = fars_exit_of(actor);
    FieldActor_MoveToPose(actor, work->x, work->z, work->yaw);
}
CLEAN_AS(func_ov004_02227d60, FieldActorRoomStates_StandExitWalk)

/* func_ov004_02227d7c (state 0x40's message handler): nothing. */
void FieldActorRoomStates_ExitWalkMessage(FieldActor *actor, int arg)
{
    (void) actor;
    (void) arg;
}
CLEAN_AS(func_ov004_02227d7c, FieldActorRoomStates_ExitWalkMessage)

/* func_ov004_02227d80 (state 0x40's entry): flag 3 set; the point is the exit's door point
 * (0x804) seen from the actor; for door kind 2 it is 1.0 further the way the door faces (by its
 * four sectors), for kind 0 it is where the actor stands, at yaw 0x8000. The work keeps the
 * kind, the yaw, the point and whether the exit must be claimed. Unclaimed, animation 0x3e
 * (kind 1) or 0x3f plays (blended over 3 frames); claimed, flag 0x18 is set and the walk
 * (animation 1) plays. */
void FieldActorRoomStates_EnterExitWalk(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    const FieldActorExitWalkArgs *args = (const FieldActorExitWalkArgs *) (const void *) request->payload;
    Vec3 point;

    FieldActor_SetFlag(actor, FARS_FLAG_EXIT);
    SceneExit_DoorPoint(fars_exits(), FARS_EXIT_INDEX(actor), &point, &actor->position);
    int kind = args->door_kind;
    int yaw = args->door_angle;
    if (kind == FARS_DOOR_SINK) {
        switch (AngleSector_Four(yaw)) {
            case 2:
                point.z = (fx32) ((u32) point.z + FARS_DOOR_BEYOND);
                break;
            case 0:
                point.z = (fx32) ((u32) point.z - FARS_DOOR_BEYOND);
                break;
            case 3:
                point.x = (fx32) ((u32) point.x + FARS_DOOR_BEYOND);
                break;
            case 1:
                point.x = (fx32) ((u32) point.x - FARS_DOOR_BEYOND);
                break;
            default:
                break;
        }
    } else if (kind == FARS_DOOR_PLAIN) {
        yaw = FARS_DOOR_PLAIN_YAW;
        point.x = actor->position.x;
        point.z = actor->position.z;
    }
    u8 claimed = 0;
    if (SceneClaim_IsClaimedExit(FARS_EXIT_INDEX(actor)) != 0) {
        claimed = 1;
    }
    FieldActorRoomStates_SetExitWalkWork(fars_exit_of(actor), kind, (s16) yaw, point.x, point.z, claimed);
    if (!claimed) {
        FieldActor_PlayAnimationOnce(actor, kind == FARS_DOOR_RISE ? FARS_ANIM_EXIT_RISE : FARS_ANIM_EXIT_SINK, FARS_BLEND, 0);
    } else {
        FieldActor_SetFlag(actor, FARS_FLAG_CLAIMED);
        FieldActor_PlayAnimationOnce(actor, FARS_ANIM_WALK, FARS_BLEND, 0);
    }
}
CLEAN_AS(func_ov004_02227d80, FieldActorRoomStates_EnterExitWalk)

/* func_ov004_02227e7c: state 0x40's work: the door kind, the yaw, the point and the phase
 * (FIELD_ACTOR_EXIT_CLAIM for an exit to claim). */
void FieldActorRoomStates_SetExitWalkWork(FieldActorExitWalk *work, int door_kind, s16 yaw, fx32 x, fx32 z, u8 phase)
{
    work->door_kind = door_kind;
    work->yaw = yaw;
    work->x = x;
    work->z = z;
    work->phase = phase;
}
CLEAN_AS(func_ov004_02227e7c, FieldActorRoomStates_SetExitWalkWork)

/* func_ov004_02227e94: state 0x40 asked for with the kind and angle of the exit's door (0x804);
 * 0 without an exit or when the scene has no such door, else whether it was queued. */
int FieldActorRoomStates_RequestExitWalk(FieldActor *actor, int priority, s16 arg)
{
    int exit = FARS_EXIT_INDEX(actor);
    if (exit == FARS_NO_EXIT) {
        return 0;
    }
    int kind;
    s16 angle;
    if (SceneExit_DoorInfo(fars_exits(), exit, &kind, &angle) == 0) {
        return 0;
    }
    StateRequest request;
    StateRequest_Construct(&request);
    StateRequest_Set(&request, FARS_EXIT_WALK, priority, arg);
    FieldActorRoomStates_PutExitWalkArgs((FieldActorExitWalkArgs *) (void *) request.payload, kind, (u16) angle);
    int queued = FieldActor_QueueRequest(actor, &request);
    StateRequest_Destruct(&request);
    return queued;
}
CLEAN_AS(func_ov004_02227e94, FieldActorRoomStates_RequestExitWalk)

/* func_ov004_02227f00: a request's arguments for state 0x40. */
void FieldActorRoomStates_PutExitWalkArgs(FieldActorExitWalkArgs *args, int door_kind, u16 door_angle)
{
    args->door_kind = door_kind;
    args->door_angle = (s16) door_angle;
}
CLEAN_AS(func_ov004_02227f00, FieldActorRoomStates_PutExitWalkArgs)

/* ---- State 0x37, the item put back */

/* func_ov004_02227f08 (state 0x37's update): the body, the contact bodies and the end of the
 * animation. */
void FieldActorRoomStates_UpdateItemBack(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    FieldActor_EnterContact(actor);
    FieldActorRoomStates_EndItemBack(actor);
}
CLEAN_AS(func_ov004_02227f08, FieldActorRoomStates_UpdateItemBack)

/* func_ov004_02227f24: once the animation is over, the state's bar for requests is its end
 * value and state 0x10 is asked for (3, priority 5); for the object's item 0x1379 the byte at
 * 0x8eb becomes 4; the object is finished. */
void FieldActorRoomStates_EndItemBack(FieldActor *actor)
{
    if (!FrameCtrl_IsDone(&actor->anim)) {
        return;
    }
    fars_end_item(actor);
    u16 item[2];
    Obj020dd33c_Item(item);
    if (item[0] == FARS_ITEM_MARKED) {
        FIELD_ACTOR_UNK_8EB(actor) = FARS_ITEM_MARK;
    }
    Obj020dd33c_Finish(actor);
}
CLEAN_AS(func_ov004_02227f24, FieldActorRoomStates_EndItemBack)

/* func_ov004_02227f8c (state 0x37's message handler): nothing. */
void FieldActorRoomStates_ItemBackMessage(FieldActor *actor, int arg)
{
    (void) actor;
    (void) arg;
}
CLEAN_AS(func_ov004_02227f8c, FieldActorRoomStates_ItemBackMessage)

/* func_ov004_02227f90 (state 0x37's entry): animation 0x2e (blended over 3 frames) plays
 * backwards from its last whole frame; the actor is handed to the object in the mode of its
 * stage; sound 0x52 plays. */
void FieldActorRoomStates_EnterItemBack(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) request;
    (void) previous;
    FieldActor_PlayAnimationOnce(actor, FARS_ANIM_ITEM, FARS_BLEND, 0);
    fars_play_backwards(actor);
    Obj020dd33c_SetActorMode(Obj020dd33c_Stage(), actor);
    FieldActor_PlaySound(actor, FARS_ITEM_BACK_SOUND);
}
CLEAN_AS(func_ov004_02227f90, FieldActorRoomStates_EnterItemBack)

/* func_ov004_02227fe4: state 0x37 asked for; whether it was queued. */
int FieldActorRoomStates_RequestItemBack(FieldActor *actor, int priority, int arg)
{
    return fars_request(actor, FARS_ITEM_BACK, priority, arg);
}
CLEAN_AS(func_ov004_02227fe4, FieldActorRoomStates_RequestItemBack)

/* ---- State 0x36, an item taken out */

/* func_ov004_0222801c (state 0x36's update): the sound and the body, the contact bodies and the
 * end of the animation. */
void FieldActorRoomStates_UpdateItemOut(FieldActor *actor)
{
    FieldActorRoomStates_ItemOutSounds(actor);
    FieldActor_EnterContact(actor);
    FieldActorRoomStates_EndItemOut(actor);
}
CLEAN_AS(func_ov004_0222801c, FieldActorRoomStates_UpdateItemOut)

/* func_ov004_02228038: once the animation is over, the state's bar for requests is its end
 * value and state 0x10 is asked for (3, priority 5). */
void FieldActorRoomStates_EndItemOut(FieldActor *actor)
{
    if (FrameCtrl_IsDone(&actor->anim)) {
        fars_end_item(actor);
    }
}
CLEAN_AS(func_ov004_02228038, FieldActorRoomStates_EndItemOut)

/* func_ov004_02228078: as the animation passes frame 8 in scene 9 sound 0x63 plays; the body is
 * updated. */
void FieldActorRoomStates_ItemOutSounds(FieldActor *actor)
{
    if (FrameCtrl_Passed(&actor->anim, FARS_ITEM_OUT_LATE_FRAME) && SceneQuery_Current() == FARS_ITEM_SCENE) {
        FieldActor_PlaySound(actor, FARS_ITEM_OUT_LATE_SOUND);
    }
    FieldActor_UpdateBody(actor);
}
CLEAN_AS(func_ov004_02228078, FieldActorRoomStates_ItemOutSounds)

/* func_ov004_022280ac (state 0x36's message handler): nothing. */
void FieldActorRoomStates_ItemOutMessage(FieldActor *actor, int arg)
{
    (void) actor;
    (void) arg;
}
CLEAN_AS(func_ov004_022280ac, FieldActorRoomStates_ItemOutMessage)

/* func_ov004_022280b0 (state 0x36's entry): the object starts with the actor's item, the
 * request's look, stage and kind, the actor and the request's second actor; animation 0x2e
 * plays once (blended over 3 frames); the actor is handed to the object in mode 1; in scene 9
 * sound 0x4f plays. */
void FieldActorRoomStates_EnterItemOut(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    const FieldActorItemOutArgs *args = (const FieldActorItemOutArgs *) (const void *) request->payload;
    Obj020dd33c_Start(&actor->item, (int) args->look, args->stage, (int) args->kind, (Actor *) (void *) actor,
                      (Actor *) (uintptr_t) args->second);
    FieldActor_PlayAnimationOnce(actor, FARS_ANIM_ITEM, FARS_BLEND, 0);
    Obj020dd33c_SetActorMode(FARS_ITEM_START_MODE, actor);
    if (SceneQuery_Current() == FARS_ITEM_SCENE) {
        FieldActor_PlaySound(actor, FARS_ITEM_OUT_SOUND);
    }
}
CLEAN_AS(func_ov004_022280b0, FieldActorRoomStates_EnterItemOut)

/* func_ov004_02228100: state 0x36 asked for with an item and four values; whether it was
 * queued.
 * QUIRK: the item becomes the actor's (0x822, then 0x820) at once, taken or not. */
int FieldActorRoomStates_RequestItemOut(FieldActor *actor, const u16 *item, int look, int stage, int kind, int second,
                                        int priority, s16 arg)
{
    StateRequest request;
    StateRequest_Construct(&request);
    StateRequest_Set(&request, FARS_ITEM_OUT, priority, arg);
    actor->unk_822 = *item;
    actor->item = actor->unk_822;
    FieldActorRoomStates_SetItemOutArgs((FieldActorItemOutArgs *) (void *) request.payload, look, (u8) stage, kind, second);
    int queued = FieldActor_QueueRequest(actor, &request);
    StateRequest_Destruct(&request);
    return queued;
}
CLEAN_AS(func_ov004_02228100, FieldActorRoomStates_RequestItemOut)

/* func_ov004_02228164: a request's values for state 0x36. */
void FieldActorRoomStates_SetItemOutArgs(FieldActorItemOutArgs *args, int look, u8 stage, int kind, int second)
{
    args->look = (u32) look;
    args->stage = stage;
    args->kind = (u32) kind;
    args->second = (u32) second;
}
CLEAN_AS(func_ov004_02228164, FieldActorRoomStates_SetItemOutArgs)

/* ---- State 0x2f, closing a chest */

/* func_ov004_02228170 (state 0x2f's update): the body, the contact bodies and the end of the
 * animation. */
void FieldActorRoomStates_UpdateChestClose(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    FieldActor_EnterContact(actor);
    FieldActorRoomStates_EndChestClose(actor);
}
CLEAN_AS(func_ov004_02228170, FieldActorRoomStates_UpdateChestClose)

/* func_ov004_0222818c: once the animation is over the actor stands (the standing animation
 * loops, blended over 3 frames); for another console's actor the state's bar for requests is
 * its end value. */
void FieldActorRoomStates_EndChestClose(FieldActor *actor)
{
    if (!FrameCtrl_IsDone(&actor->anim)) {
        return;
    }
    FieldActor_PlayAnimationLoop(actor, FARS_ANIM_STAND, FARS_BLEND, FARS_BLEND);
    if (fars_is_local(actor)) {
        return;
    }
    actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
}
CLEAN_AS(func_ov004_0222818c, FieldActorRoomStates_EndChestClose)

/* func_ov004_022281e0 (state 0x2f's message handler): state 0x2f asked for (priority 6) with the
 * chest's index kept at 0x8f0. */
void FieldActorRoomStates_ChestCloseMessage(FieldActor *actor, int arg)
{
    u8 index;
    FieldActorRoomStates_GetChestCloseSaved(actor->saved.packed, &index);
    FieldActorRoomStates_RequestChestClose(actor, index, FARS_PRIORITY, arg);
}
CLEAN_AS(func_ov004_022281e0, FieldActorRoomStates_ChestCloseMessage)

/* func_ov004_0222820c (state 0x2f's entry): the request's chest index goes to the work and to
 * 0x8f0; animation 0x38 plus the index (blended over 3 frames) plays backwards from its last
 * whole frame; for another console's actor RoomObjects_Stub0223b334 is told its position and yaw.
 * REQUIRES: the index is 0 to 2 (the ROM picks no animation for others and plays whatever its
 * register held). */
void FieldActorRoomStates_EnterChestClose(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    u32 index = *(const u32 *) (const void *) request->payload;
    FieldActorRoomStates_PutChestCloseWork((u32 *) (void *) &actor->work, index);
    FieldActorRoomStates_PutChestCloseSaved(actor->saved.packed, (u8) index);
    FieldActor_PlayAnimationOnce(actor, FARS_ANIM_CHEST_CLOSE + (int) index, FARS_BLEND, 0);
    fars_play_backwards(actor);
    if (!fars_is_local(actor)) {
        RoomObjects_Stub0223b334(&actor->position, actor->yaw);
    }
}
CLEAN_AS(func_ov004_0222820c, FieldActorRoomStates_EnterChestClose)

/* func_ov004_022282b0: the chest's index kept for state 0x2f. */
void FieldActorRoomStates_GetChestCloseSaved(const u8 *saved, u8 *index)
{
    *index = *saved;
}
CLEAN_AS(func_ov004_022282b0, FieldActorRoomStates_GetChestCloseSaved)

/* func_ov004_022282b8: the chest's index of state 0x2f kept. */
void FieldActorRoomStates_PutChestCloseSaved(u8 *saved, u8 index)
{
    *saved = index;
}
CLEAN_AS(func_ov004_022282b8, FieldActorRoomStates_PutChestCloseSaved)

/* func_ov004_022282bc: state 0x2f's work: the chest's index. */
void FieldActorRoomStates_PutChestCloseWork(u32 *work, u32 index)
{
    *work = index;
}
CLEAN_AS(func_ov004_022282bc, FieldActorRoomStates_PutChestCloseWork)

/* func_ov004_022282c0: state 0x2f asked for with a chest's index; whether it was queued. */
int FieldActorRoomStates_RequestChestClose(FieldActor *actor, int index, int priority, int arg)
{
    StateRequest request;
    StateRequest_Construct(&request);
    StateRequest_Set(&request, FARS_CHEST_CLOSE, priority, arg);
    FieldActorRoomStates_PutChestCloseArgs((u32 *) (void *) request.payload, (u32) index);
    int queued = FieldActor_QueueRequest(actor, &request);
    StateRequest_Destruct(&request);
    return queued;
}
CLEAN_AS(func_ov004_022282c0, FieldActorRoomStates_RequestChestClose)

/* func_ov004_02228300: a request's chest index for state 0x2f. */
void FieldActorRoomStates_PutChestCloseArgs(u32 *payload, u32 index)
{
    *payload = index;
}
CLEAN_AS(func_ov004_02228300, FieldActorRoomStates_PutChestCloseArgs)

/* ---- State 0x2e, at a chest */

/* func_ov004_02228304 (state 0x2e's update): the body and the contact bodies. */
void FieldActorRoomStates_UpdateAtChest(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    FieldActor_EnterContact(actor);
}
CLEAN_AS(func_ov004_02228304, FieldActorRoomStates_UpdateAtChest)

/* func_ov004_02228318 (state 0x2e's message handler): state 0x2e asked for (priority 6) with the
 * chest's index kept at 0x8f0. */
void FieldActorRoomStates_AtChestMessage(FieldActor *actor, int arg)
{
    u8 index;
    FieldActorRoomStates_GetAtChestSaved(actor->saved.packed, &index);
    FieldActorRoomStates_RequestAtChest(actor, index, FARS_PRIORITY, arg);
}
CLEAN_AS(func_ov004_02228318, FieldActorRoomStates_AtChestMessage)

/* func_ov004_02228344 (state 0x2e's entry): the request's chest index (its first byte) goes to
 * the work and to 0x8f0; animation 0x3b plus the index loops (blended over 3 frames); for
 * another console's actor RoomObjects_Stub0223b338 is told its position and yaw.
 * REQUIRES: the index is 0 to 2 (the ROM picks no animation for others and plays whatever its
 * register held). */
void FieldActorRoomStates_EnterAtChest(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    u8 index = request->payload[0];
    FieldActorRoomStates_PutAtChestWork((u32 *) (void *) &actor->work, index);
    FieldActorRoomStates_PutAtChestSaved(actor->saved.packed, index);
    FieldActor_PlayAnimationLoop(actor, FARS_ANIM_AT_CHEST + index, FARS_BLEND, 0);
    if (!fars_is_local(actor)) {
        RoomObjects_Stub0223b338(&actor->position, actor->yaw);
    }
}
CLEAN_AS(func_ov004_02228344, FieldActorRoomStates_EnterAtChest)

/* func_ov004_022283bc: the chest's index kept for state 0x2e. */
void FieldActorRoomStates_GetAtChestSaved(const u8 *saved, u8 *index)
{
    *index = *saved;
}
CLEAN_AS(func_ov004_022283bc, FieldActorRoomStates_GetAtChestSaved)

/* func_ov004_022283c4: the chest's index of state 0x2e kept. */
void FieldActorRoomStates_PutAtChestSaved(u8 *saved, u8 index)
{
    *saved = index;
}
CLEAN_AS(func_ov004_022283c4, FieldActorRoomStates_PutAtChestSaved)

/* func_ov004_022283c8: state 0x2e's work: the chest's index. */
void FieldActorRoomStates_PutAtChestWork(u32 *work, u32 index)
{
    *work = index;
}
CLEAN_AS(func_ov004_022283c8, FieldActorRoomStates_PutAtChestWork)

/* func_ov004_022283cc: state 0x2e asked for with a chest's index; whether it was queued. */
int FieldActorRoomStates_RequestAtChest(FieldActor *actor, int index, int priority, int arg)
{
    StateRequest request;
    StateRequest_Construct(&request);
    StateRequest_Set(&request, FARS_AT_CHEST, priority, arg);
    FieldActorRoomStates_PutAtChestArgs(request.payload, (u8) index);
    int queued = FieldActor_QueueRequest(actor, &request);
    StateRequest_Destruct(&request);
    return queued;
}
CLEAN_AS(func_ov004_022283cc, FieldActorRoomStates_RequestAtChest)

/* func_ov004_0222840c: a request's chest index for state 0x2e (its first byte). */
void FieldActorRoomStates_PutAtChestArgs(u8 *payload, u8 index)
{
    *payload = index;
}
CLEAN_AS(func_ov004_0222840c, FieldActorRoomStates_PutAtChestArgs)

/* ---- State 0x2d, to a chest; the states of a spot (0x27 to 0x2c) */

static_assert(offsetof(FieldActor, unk_1C4) == FIELD_ACTOR_CONTACT_B, "second contact body");
static_assert(offsetof(FieldActor, has_other) == 0x200, "an object met");
static_assert(offsetof(FieldActor, anim.flags) == 0x2e4, "animation flags");
static_assert(offsetof(FieldActor, unk_C84) == 0xc84, "0xc84");
static_assert(offsetof(Actor, cull_flags) == 0xb0, "cull flags");
static_assert(offsetof(LayeredModel, base.frames) == 0x2d0 - FIELD_ACTOR_BODY, "the body's animation");
static_assert(offsetof(FieldActorChestApproach, index) == 0x0a, "the chest's index");
static_assert(sizeof(FieldActorChestApproach) <= sizeof(FieldActorWork), "state 0x2d's work");
static_assert(sizeof(FieldActorChestApproach) <= sizeof(((StateRequest *) 0)->payload), "state 0x2d's arguments");
static_assert(offsetof(FieldActorSpotClaim, way) == 0x0c, "the way");
static_assert(sizeof(FieldActorSpotClaim) <= sizeof(FieldActorWork), "state 0x2b's work");
static_assert(sizeof(FieldActorSpotStay) <= sizeof(FieldActorWork), "state 0x28's work");
static_assert(sizeof(FieldActorSpotEnter) <= sizeof(FieldActorWork), "state 0x27's work");
static_assert(sizeof(FieldActorSpotEnter) <= sizeof(((StateRequest *) 0)->payload), "state 0x27's arguments");

#define FARS_SPOT_ENTER 0x27
#define FARS_SPOT_STAY 0x28
#define FARS_SPOT_TURN_MINUS 0x29
#define FARS_SPOT_TURN_PLUS 0x2a
#define FARS_SPOT_CLAIM 0x2b
#define FARS_SPOT_STEP_OFF 0x2c
#define FARS_CHEST_APPROACH 0x2d

/* State 0x2d: the animation it may start from besides standing, and its flag (set while the
 * chest's animation is started, cleared at its end). */
#define FARS_ANIM_1A 0x1a
#define FARS_CHEST_APPROACH_FLAG 2

/* The animations and sounds of the spot's states; the frames of the sounds of 0x2c and 0x27. */
#define FARS_ANIM_SPOT_ENTER 0x23
#define FARS_ANIM_SPOT_STAY 0x24
#define FARS_ANIM_SPOT_TURN_PLUS 0x25
#define FARS_ANIM_SPOT_TURN_MINUS 0x26
#define FARS_ANIM_SPOT_STEP_OFF 0x27
#define FARS_SPOT_ENTER_SOUND 0x4c5
#define FARS_SPOT_STEP_OFF_SOUND 0x4c6
#define FARS_SPOT_TURN_SOUND 0x4c9
#define FARS_SPOT_STEP_OFF_SOUND_FRAME 13
#define FARS_SPOT_ENTER_SOUND_FRAME 12
#define FARS_QUARTER_TURN 0x4000

/* State 0x28 asked for after a refused claim (3) or after state 0x27 (0); state 2 at the end of
 * 0x2c (0, priority 1). */
#define FARS_SPOT_STAY_REFUSED 3
#define FARS_SPOT_STAY_AFTER_ENTER 0
#define FARS_STEP_OFF_STATE2_ARG 0

/* State 0x2c's second contact body (1.0 by 1.0) while another console's actor is in 0x2b. */
#define FARS_SPOT_CONTACT_SIZE 0x1000

/* The claim of state 0x2c's place, let go on leaving it. */
#define FARS_SPOT_CLAIM_SLOT 0

/* The musics whose beat the body follows in state 0x28, and the frames of the blend into it;
 * byte 3 of the sound's entry while it does not play (as for the cafe's master,
 * ov004/cafe_master.c); the body's animation speed afterwards. */
#define FARS_BEAT_MUSIC_FIRST 0x63
#define FARS_BEAT_MUSIC_LAST 0xab
#define FARS_BEAT_BLEND_FRAMES 10
#define FARS_SOUND_STOPPED 1
#define FARS_BEAT_SPEED_WORD 3
#define FARS_BEAT_AFTER_SPEED 0x1000

/* 1 while the game is in a room. */
extern u8 data_020e54a8;
/* How far ahead the spot's place is (2.0). */
extern const fx32 data_ov004_02247780;
/* The yaw subtracted for each way off a spot (FieldActorSpotWay): 0, -0x4000, 0x4000. */
extern const s16 data_ov004_0224776c[];

static int fars_in_room(void)
{
    return data_020e54a8 == 1;
}

static FieldActorChestApproach *fars_chest_approach_of(FieldActor *actor)
{
    return (FieldActorChestApproach *) (void *) &actor->work;
}

static FieldActorSpotClaim *fars_spot_claim_of(FieldActor *actor)
{
    return (FieldActorSpotClaim *) (void *) &actor->work;
}

static FieldActorSpotStay *fars_spot_stay_of(FieldActor *actor)
{
    return (FieldActorSpotStay *) (void *) &actor->work;
}

static FieldActorSpotEnter *fars_spot_enter_of(FieldActor *actor)
{
    return (FieldActorSpotEnter *) (void *) &actor->work;
}

static FieldBody *fars_contact_b(FieldActor *actor)
{
    return (FieldBody *) (void *) actor->unk_1C4;
}

/* func_ov004_02228410 (state 0x2d's update): the ease to the work's point and yaw, the
 * chest's animation, the body, the contact bodies and the end of the animation. */
void FieldActorRoomStates_UpdateChestApproach(FieldActor *actor)
{
    FieldActorRoomStates_StandChestApproach(actor);
    FieldActorRoomStates_AnimateChestApproach(actor);
    FieldActor_UpdateBody(actor);
    FieldActor_EnterContact(actor);
    FieldActorRoomStates_EndChestApproach(actor);
}
CLEAN_AS(func_ov004_02228410, FieldActorRoomStates_UpdateChestApproach)

/* func_ov004_02228438: once the chest's animation (not standing, not 0x1a) is over, flag 2 is
 * cleared and state 0x2e is asked for with the work's chest index (priority 6). */
void FieldActorRoomStates_EndChestApproach(FieldActor *actor)
{
    int animation = actor->animation;
    if (animation == FARS_ANIM_1A || animation == FARS_ANIM_STAND || !FrameCtrl_IsDone(&actor->anim)) {
        return;
    }
    FieldActor_ClearFlag(actor, FARS_CHEST_APPROACH_FLAG);
    FieldActorRoomStates_RequestAtChest(actor, fars_chest_approach_of(actor)->index, FARS_PRIORITY, FARS_NO_ARG);
}
CLEAN_AS(func_ov004_02228438, FieldActorRoomStates_EndChestApproach)

/* func_ov004_02228480: while animation 0x1a or the standing one plays, flag 2 is set and
 * animation 0x3b plus the work's chest index plays once (blended over 3 frames); for another
 * console's actor RoomObjects_Stub0223b33c is told its position and yaw.
 * QUIRK: the ROM also tests whether the animation is at its whole frame 0, and goes on either
 * way.
 * REQUIRES: the index is 0 to 2 (the ROM picks no animation for others and plays whatever its
 * register held). */
void FieldActorRoomStates_AnimateChestApproach(FieldActor *actor)
{
    int animation = actor->animation;
    if (animation != FARS_ANIM_1A && animation != FARS_ANIM_STAND) {
        return;
    }
    FieldActor_SetFlag(actor, FARS_CHEST_APPROACH_FLAG);
    FieldActor_PlayAnimationOnce(actor, FARS_ANIM_AT_CHEST + fars_chest_approach_of(actor)->index, FARS_BLEND, 0);
    if (!fars_is_local(actor)) {
        RoomObjects_Stub0223b33c(&actor->position, actor->yaw);
    }
}
CLEAN_AS(func_ov004_02228480, FieldActorRoomStates_AnimateChestApproach)

/* func_ov004_02228510: the actor eased to the work's point and yaw. */
void FieldActorRoomStates_StandChestApproach(FieldActor *actor)
{
    const FieldActorChestApproach *work = fars_chest_approach_of(actor);
    FieldActor_MoveToPose(actor, work->x, work->z, work->yaw);
}
CLEAN_AS(func_ov004_02228510, FieldActorRoomStates_StandChestApproach)

/* func_ov004_0222852c (state 0x2d's message handler): state 0x2d asked for (priority 6) with
 * the chest's index, point and yaw kept at 0x8f0. */
void FieldActorRoomStates_ChestApproachMessage(FieldActor *actor, s16 arg)
{
    u8 index;
    u32 x;
    u32 z;
    u16 yaw;
    FieldActorRoomStates_GetChestApproachSaved(actor->saved.packed, &index, &x, &z, &yaw);
    FieldActorRoomStates_RequestChestApproach(actor, index, (int) x, (int) z, (s16) yaw, FARS_PRIORITY, arg);
}
CLEAN_AS(func_ov004_0222852c, FieldActorRoomStates_ChestApproachMessage)

/* func_ov004_02228570 (state 0x2d's entry): the request's index, point and yaw go to the work
 * and to 0x8f0; the body's animation flags become "once". */
void FieldActorRoomStates_EnterChestApproach(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    const FieldActorChestApproach *args = (const FieldActorChestApproach *) (const void *) request->payload;
    char index = (char) args->index;
    FieldActorRoomStates_SetChestApproachWork(fars_chest_approach_of(actor), index, args->x, args->z, args->yaw);
    FieldActorRoomStates_PutChestApproachSaved(actor->saved.packed, index, args->x, args->z, args->yaw);
    actor->anim.flags = FRAME_CTRL_ONCE;
}
CLEAN_AS(func_ov004_02228570, FieldActorRoomStates_EnterChestApproach)

/* func_ov004_022285c4: the chest's index (byte 7), point (bytes 0 to 4) and yaw (bytes 5 and 6)
 * kept for state 0x2d; the yaw is also the result. */
u16 FieldActorRoomStates_GetChestApproachSaved(const u8 *saved, u8 *index, u32 *x, u32 *z, u16 *yaw)
{
    *index = saved[7];
    PackedBytes_UnpackPoint(saved, x, z);
    u16 value = (u16) PackedBytes_ReadS16(saved + 5);
    *yaw = value;
    return value;
}
CLEAN_AS(func_ov004_022285c4, FieldActorRoomStates_GetChestApproachSaved)

/* func_ov004_022285e8: the chest's index, point and yaw of state 0x2d kept. */
void FieldActorRoomStates_PutChestApproachSaved(u8 *saved, char index, int x, int z, s16 yaw)
{
    saved[7] = (u8) index;
    PackedBytes_PackPoint(saved, x, z);
    PackedBytes_WriteS16(saved + 5, yaw);
}
CLEAN_AS(func_ov004_022285e8, FieldActorRoomStates_PutChestApproachSaved)

/* func_ov004_02228610: state 0x2d's work: the chest's index, the point and the yaw. */
void FieldActorRoomStates_SetChestApproachWork(FieldActorChestApproach *work, char index, int x, int z, s16 yaw)
{
    work->index = (u8) index;
    work->x = x;
    work->z = z;
    work->yaw = yaw;
}
CLEAN_AS(func_ov004_02228610, FieldActorRoomStates_SetChestApproachWork)

/* func_ov004_02228628: state 0x2d asked for with a chest's index, point and yaw; whether it was
 * queued. */
int FieldActorRoomStates_RequestChestApproach(FieldActor *actor, int index, int x, int z, s16 yaw, int priority, s16 arg)
{
    StateRequest request;
    StateRequest_Construct(&request);
    StateRequest_Set(&request, FARS_CHEST_APPROACH, priority, arg);
    FieldActorRoomStates_PutChestApproachArgs((FieldActorChestApproach *) (void *) request.payload, (char) index, x, z, yaw);
    int queued = FieldActor_QueueRequest(actor, &request);
    StateRequest_Destruct(&request);
    return queued;
}
CLEAN_AS(func_ov004_02228628, FieldActorRoomStates_RequestChestApproach)

/* func_ov004_02228678: a request's arguments for state 0x2d. */
void FieldActorRoomStates_PutChestApproachArgs(FieldActorChestApproach *args, char index, int x, int z, s16 yaw)
{
    args->index = (u8) index;
    args->x = x;
    args->z = z;
    args->yaw = yaw;
}
CLEAN_AS(func_ov004_02228678, FieldActorRoomStates_PutChestApproachArgs)

/* ---- State 0x2c, off the spot */

/* func_ov004_02228690 (state 0x2c's update): the body and its sound, the contact bodies and the
 * end of the animation. */
void FieldActorRoomStates_UpdateSpotStepOff(FieldActor *actor)
{
    FieldActorRoomStates_StepSpotStepOff(actor);
    FieldActorRoomStates_ContactSpotStepOff(actor);
    FieldActorRoomStates_EndSpotStepOff(actor);
}
CLEAN_AS(func_ov004_02228690, FieldActorRoomStates_UpdateSpotStepOff)

/* func_ov004_022286ac: once the animation is over, the state's bar for requests is its end
 * value and state 2 is asked for (0, priority 1). */
void FieldActorRoomStates_EndSpotStepOff(FieldActor *actor)
{
    if (FrameCtrl_IsDone(&actor->anim)) {
        actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
        FieldActor_RequestState2(actor, FARS_STEP_OFF_STATE2_ARG, FARS_END_PRIORITY, FARS_NO_ARG);
    }
}
CLEAN_AS(func_ov004_022286ac, FieldActorRoomStates_EndSpotStepOff)

/* func_ov004_022286e8: the contact bodies of this console's actor; another console's has its
 * contact body at the work's point (the place it steps to). */
void FieldActorRoomStates_ContactSpotStepOff(FieldActor *actor)
{
    if (fars_is_local(actor)) {
        FieldActor_EnterContact(actor);
        return;
    }
    Vec3 point = *fars_point_of(actor);
    FieldActor_SetContactAt(actor, &point, &actor->state);
    FieldBody_Enter((FieldBody *) (void *) actor->unk_174);
}
CLEAN_AS(func_ov004_022286e8, FieldActorRoomStates_ContactSpotStepOff)

/* func_ov004_02228748: the body updated; as the animation passes frame 13 sound 0x4c6 plays.
 * What playing the sound answered, else 0. */
int FieldActorRoomStates_StepSpotStepOff(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    if (!FrameCtrl_Passed(&actor->anim, FARS_SPOT_STEP_OFF_SOUND_FRAME)) {
        return 0;
    }
    return FieldActor_PlaySound(actor, FARS_SPOT_STEP_OFF_SOUND);
}
CLEAN_AS(func_ov004_02228748, FieldActorRoomStates_StepSpotStepOff)

/* func_ov004_02228774 (state 0x2c's exit): this console's actor lets its place claim go; the
 * actor stands at the work's point. */
void FieldActorRoomStates_LeaveSpotStepOff(FieldActor *actor, int next)
{
    (void) next;
    if (fars_is_local(actor)) {
        PlaceClaim_Release(FARS_SPOT_CLAIM_SLOT);
    }
    actor->position = *fars_point_of(actor);
}
CLEAN_AS(func_ov004_02228774, FieldActorRoomStates_LeaveSpotStepOff)

/* func_ov004_022287b4 (state 0x2c's message handler): nothing in states 0x29 and 0x2a (they
 * lead to 0x2c); in 0x2c the argument is kept at 0xc84; else state 0x2c is asked for (priority
 * 6). */
void FieldActorRoomStates_SpotStepOffMessage(FieldActor *actor, int arg)
{
    int state = actor->state;
    if (state == FARS_SPOT_TURN_MINUS || state == FARS_SPOT_TURN_PLUS) {
        return;
    }
    if (state == FARS_SPOT_STEP_OFF) {
        actor->unk_C84 = (s16) arg;
    } else {
        FieldActorRoomStates_RequestSpotStepOff(actor, FARS_PRIORITY, arg);
    }
}
CLEAN_AS(func_ov004_022287b4, FieldActorRoomStates_SpotStepOffMessage)

/* func_ov004_022287e4 (state 0x2c's entry): animation 0x27 plays once (no blend); the work is
 * the point 2.0 ahead; in a room the object at the actor's position plays its sound 2. */
void FieldActorRoomStates_EnterSpotStepOff(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) request;
    (void) previous;
    Vec3 ahead;
    FieldActor_PlayAnimationOnce(actor, FARS_ANIM_SPOT_STEP_OFF, 0, 0);
    FieldActor_PointAhead(&ahead, actor, &actor->position, (const u16 *) &actor->yaw, &data_ov004_02247780);
    FieldActorRoomStates_PutSpotStepOffWork(fars_point_of(actor), &ahead);
    if (fars_in_room()) {
        RoomPointSound_Play2(&actor->position);
    }
}
CLEAN_AS(func_ov004_022287e4, FieldActorRoomStates_EnterSpotStepOff)

/* func_ov004_02228840: state 0x2c's work: the point; the work is the result. */
void *FieldActorRoomStates_PutSpotStepOffWork(Vec3 *work, const Vec3 *point)
{
    work->x = point->x;
    work->y = point->y;
    work->z = point->z;
    return work;
}
CLEAN_AS(func_ov004_02228840, FieldActorRoomStates_PutSpotStepOffWork)

/* func_ov004_02228850: state 0x2c asked for; whether it was queued. */
int FieldActorRoomStates_RequestSpotStepOff(FieldActor *actor, int priority, int arg)
{
    return fars_request(actor, FARS_SPOT_STEP_OFF, priority, arg);
}
CLEAN_AS(func_ov004_02228850, FieldActorRoomStates_RequestSpotStepOff)

/* ---- State 0x2b, the place off the spot claimed */

/* func_ov004_02228888 (state 0x2b's update): in a room the object at the actor's position plays
 * its sound 0; the body, the contact bodies, the claim's answer and the second contact body. */
void FieldActorRoomStates_UpdateSpotClaim(FieldActor *actor)
{
    if (fars_in_room()) {
        RoomPointSound_Play0(&actor->position);
    }
    FieldActor_UpdateBody(actor);
    FieldActor_EnterContact(actor);
    FieldActorRoomStates_RunSpotClaim(actor);
    FieldActorRoomStates_ContactSpotClaim(actor);
}
CLEAN_AS(func_ov004_02228888, FieldActorRoomStates_UpdateSpotClaim)

/* func_ov004_022288c8: the claim's answer: while it is not known nothing; refused, the state's
 * bar for requests is its end value and state 0x28 is asked for (3, priority 6). Given (and for
 * an answer of none of these) the bar is its end value (given only); then with an object met
 * state 0x28 is asked for (3, priority 6), else by the work's way state 0x2c, 0x2a or 0x29
 * (priority 6). */
void FieldActorRoomStates_RunSpotClaim(FieldActor *actor)
{
    switch (PlaceClaim_Answer4()) {
        case PLACE_CLAIM_WAITING:
            return;
        case PLACE_CLAIM_GIVEN:
            actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
            break;
        case PLACE_CLAIM_REFUSED:
            actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
            FieldActorRoomStates_RequestSpotStay(actor, FARS_SPOT_STAY_REFUSED, FARS_PRIORITY, FARS_NO_ARG);
            return;
        default:
            break;
    }
    if (actor->has_other != 0) {
        FieldActorRoomStates_RequestSpotStay(actor, FARS_SPOT_STAY_REFUSED, FARS_PRIORITY, FARS_NO_ARG);
        return;
    }
    switch (fars_spot_claim_of(actor)->way) {
        case FIELD_ACTOR_SPOT_STRAIGHT:
            FieldActorRoomStates_RequestSpotStepOff(actor, FARS_PRIORITY, FARS_NO_ARG);
            break;
        case FIELD_ACTOR_SPOT_PLUS:
            FieldActorRoomStates_RequestSpotTurnPlus(actor, FARS_PRIORITY, FARS_NO_ARG);
            break;
        case FIELD_ACTOR_SPOT_MINUS:
            FieldActorRoomStates_RequestSpotTurnMinus(actor, FARS_PRIORITY, FARS_NO_ARG);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov004_022288c8, FieldActorRoomStates_RunSpotClaim)

/* func_ov004_02228978: the second contact body (1.0 by 1.0) at the claimed place, entered for
 * the frame. */
void FieldActorRoomStates_ContactSpotClaim(FieldActor *actor)
{
    Vec3 point = fars_spot_claim_of(actor)->point;
    FieldActor_SetContactBSized(actor, &point, FARS_SPOT_CONTACT_SIZE, FARS_SPOT_CONTACT_SIZE);
    FieldBody_Enter(fars_contact_b(actor));
}
CLEAN_AS(func_ov004_02228978, FieldActorRoomStates_ContactSpotClaim)

/* func_ov004_022289b4 (state 0x2b's message handler): nothing. */
void FieldActorRoomStates_SpotClaimMessage(FieldActor *actor, int arg)
{
    (void) actor;
    (void) arg;
}
CLEAN_AS(func_ov004_022289b4, FieldActorRoomStates_SpotClaimMessage)

/* func_ov004_022289b8 (state 0x2b's entry): the place 2.0 ahead in the request's way (the yaw
 * less data_ov004_0224776c's entry) and the way go to the work; this console's actor claims
 * the place. */
void FieldActorRoomStates_EnterSpotClaim(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    int way = request->payload[0];
    s16 yaw = (s16) (actor->yaw - data_ov004_0224776c[way]);
    Vec3 ahead;
    FieldActor_PointAhead(&ahead, actor, &actor->position, (const u16 *) &yaw, &data_ov004_02247780);
    Vec3 point = ahead;
    FieldActorRoomStates_SetSpotClaimWork(fars_spot_claim_of(actor), &point, way);
    if (fars_is_local(actor)) {
        PlaceClaim_Request4(&ahead);
    }
}
CLEAN_AS(func_ov004_022289b8, FieldActorRoomStates_EnterSpotClaim)

/* func_ov004_02228a2c: state 0x2b's work: the place and the way; the work is the result. */
void *FieldActorRoomStates_SetSpotClaimWork(FieldActorSpotClaim *work, const Vec3 *point, int way)
{
    work->point.x = point->x;
    work->point.y = point->y;
    work->point.z = point->z;
    work->way = (u8) way;
    return work;
}
CLEAN_AS(func_ov004_02228a2c, FieldActorRoomStates_SetSpotClaimWork)

/* func_ov004_02228a3c: state 0x2b asked for with a way; whether it was queued. */
int FieldActorRoomStates_RequestSpotClaim(FieldActor *actor, int way, int priority, int arg)
{
    StateRequest request;
    StateRequest_Construct(&request);
    StateRequest_Set(&request, FARS_SPOT_CLAIM, priority, arg);
    FieldActorRoomStates_PutSpotClaimArgs(request.payload, (u8) way);
    int queued = FieldActor_QueueRequest(actor, &request);
    StateRequest_Destruct(&request);
    return queued;
}
CLEAN_AS(func_ov004_02228a3c, FieldActorRoomStates_RequestSpotClaim)

/* func_ov004_02228a7c: a request's way for state 0x2b (its first byte). */
void FieldActorRoomStates_PutSpotClaimArgs(u8 *payload, u8 way)
{
    *payload = way;
}
CLEAN_AS(func_ov004_02228a7c, FieldActorRoomStates_PutSpotClaimArgs)

/* ---- States 0x2a and 0x29, a quarter turn on the spot */

/* The yaw a turn ends at, kept in the work. */
static s16 *fars_turn_yaw_of(FieldActor *actor)
{
    return (s16 *) (void *) &actor->work;
}

/* At the end of a turn's animation state 0x2c is asked for (priority 6). */
static void fars_end_turn(FieldActor *actor)
{
    if (FrameCtrl_IsDone(&actor->anim)) {
        FieldActorRoomStates_RequestSpotStepOff(actor, FARS_PRIORITY, FARS_NO_ARG);
    }
}

/* A turn's entry: the yaw it ends at, its animation once (no blend) and sound 0x4c9. */
static void fars_enter_turn(FieldActor *actor, int turn, int animation)
{
    *fars_turn_yaw_of(actor) = (s16) (actor->yaw + turn);
    FieldActor_PlayAnimationOnce(actor, animation, 0, 0);
    FieldActor_PlaySound(actor, FARS_SPOT_TURN_SOUND);
}

/* func_ov004_02228a80 (state 0x2a's update): the body, the contact bodies and the end of the
 * animation. */
void FieldActorRoomStates_UpdateSpotTurnPlus(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    FieldActor_EnterContact(actor);
    FieldActorRoomStates_EndSpotTurnPlus(actor);
}
CLEAN_AS(func_ov004_02228a80, FieldActorRoomStates_UpdateSpotTurnPlus)

/* func_ov004_02228a9c: once the animation is over, state 0x2c is asked for (priority 6). */
void FieldActorRoomStates_EndSpotTurnPlus(FieldActor *actor)
{
    fars_end_turn(actor);
}
CLEAN_AS(func_ov004_02228a9c, FieldActorRoomStates_EndSpotTurnPlus)

/* func_ov004_02228ac4 (state 0x2a's exit): the actor takes the yaw the turn ends at. */
void FieldActorRoomStates_LeaveSpotTurnPlus(FieldActor *actor, int next)
{
    (void) next;
    FieldActor_SetYaw(actor, fars_turn_yaw_of(actor));
}
CLEAN_AS(func_ov004_02228ac4, FieldActorRoomStates_LeaveSpotTurnPlus)

/* func_ov004_02228ad4 (state 0x2a's message handler): state 0x2a asked for (priority 6). */
void FieldActorRoomStates_SpotTurnPlusMessage(FieldActor *actor, int arg)
{
    FieldActorRoomStates_RequestSpotTurnPlus(actor, FARS_PRIORITY, arg);
}
CLEAN_AS(func_ov004_02228ad4, FieldActorRoomStates_SpotTurnPlusMessage)

/* func_ov004_02228ae0 (state 0x2a's entry): the turn ends at the yaw plus 0x4000; animation
 * 0x25 plays once (no blend); sound 0x4c9. */
void FieldActorRoomStates_EnterSpotTurnPlus(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) request;
    (void) previous;
    fars_enter_turn(actor, FARS_QUARTER_TURN, FARS_ANIM_SPOT_TURN_PLUS);
}
CLEAN_AS(func_ov004_02228ae0, FieldActorRoomStates_EnterSpotTurnPlus)

/* func_ov004_02228b14: state 0x2a asked for; whether it was queued. */
int FieldActorRoomStates_RequestSpotTurnPlus(FieldActor *actor, int priority, int arg)
{
    return fars_request(actor, FARS_SPOT_TURN_PLUS, priority, arg);
}
CLEAN_AS(func_ov004_02228b14, FieldActorRoomStates_RequestSpotTurnPlus)

/* func_ov004_02228b4c (state 0x29's update): the body, the contact bodies and the end of the
 * animation. */
void FieldActorRoomStates_UpdateSpotTurnMinus(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    FieldActor_EnterContact(actor);
    FieldActorRoomStates_EndSpotTurnMinus(actor);
}
CLEAN_AS(func_ov004_02228b4c, FieldActorRoomStates_UpdateSpotTurnMinus)

/* func_ov004_02228b68: once the animation is over, state 0x2c is asked for (priority 6). */
void FieldActorRoomStates_EndSpotTurnMinus(FieldActor *actor)
{
    fars_end_turn(actor);
}
CLEAN_AS(func_ov004_02228b68, FieldActorRoomStates_EndSpotTurnMinus)

/* func_ov004_02228b90 (state 0x29's exit): the actor takes the yaw the turn ends at. */
void FieldActorRoomStates_LeaveSpotTurnMinus(FieldActor *actor, int next)
{
    (void) next;
    FieldActor_SetYaw(actor, fars_turn_yaw_of(actor));
}
CLEAN_AS(func_ov004_02228b90, FieldActorRoomStates_LeaveSpotTurnMinus)

/* func_ov004_02228ba0 (state 0x29's message handler): state 0x29 asked for (priority 6). */
void FieldActorRoomStates_SpotTurnMinusMessage(FieldActor *actor, int arg)
{
    FieldActorRoomStates_RequestSpotTurnMinus(actor, FARS_PRIORITY, arg);
}
CLEAN_AS(func_ov004_02228ba0, FieldActorRoomStates_SpotTurnMinusMessage)

/* func_ov004_02228bac (state 0x29's entry): the turn ends at the yaw less 0x4000; animation
 * 0x26 plays once (no blend); sound 0x4c9. */
void FieldActorRoomStates_EnterSpotTurnMinus(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) request;
    (void) previous;
    fars_enter_turn(actor, -FARS_QUARTER_TURN, FARS_ANIM_SPOT_TURN_MINUS);
}
CLEAN_AS(func_ov004_02228bac, FieldActorRoomStates_EnterSpotTurnMinus)

/* func_ov004_02228be0: state 0x29 asked for; whether it was queued. */
int FieldActorRoomStates_RequestSpotTurnMinus(FieldActor *actor, int priority, int arg)
{
    return fars_request(actor, FARS_SPOT_TURN_MINUS, priority, arg);
}
CLEAN_AS(func_ov004_02228be0, FieldActorRoomStates_RequestSpotTurnMinus)

/* ---- State 0x28, at the spot */

/* func_ov004_02228c18 (state 0x28's update): in a room the object at the actor's position plays
 * its sound 0; the body (on the music's beat), the shadow; this console's actor may leave the
 * spot, another console's has the state's bar for requests at its end value. */
void FieldActorRoomStates_UpdateSpotStay(FieldActor *actor)
{
    if (fars_in_room()) {
        RoomPointSound_Play0(&actor->position);
    }
    FieldActorRoomStates_BeatSpotStay(actor);
    FieldActor_PlaceShadow(actor);
    if (fars_is_local(actor)) {
        FieldActorRoomStates_TryLeaveSpotStay(actor);
    } else {
        actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
    }
}
CLEAN_AS(func_ov004_02228c18, FieldActorRoomStates_UpdateSpotStay)

/* func_ov004_02228c84: pushed, by the sector of the push seen from the yaw: ahead, where the
 * room is free ahead, state 0x2b straight; sector 3, where it is free at 90 degrees, the way
 * yaw + 0x4000; sector 1, where it is free at 270 degrees, the way yaw - 0x4000 (each priority
 * 6). */
void FieldActorRoomStates_TryLeaveSpotStay(FieldActor *actor)
{
    if ((int) FieldActor_Push(actor) <= 0) {
        return;
    }
    switch (AngleSector_Four((s16) (actor->yaw - FieldActor_PushYaw(actor)))) {
        case 0:
            if (RoomObjects_IsFreeAhead(&actor->position, actor->yaw)) {
                FieldActorRoomStates_RequestSpotClaim(actor, FIELD_ACTOR_SPOT_STRAIGHT, FARS_PRIORITY, FARS_NO_ARG);
            }
            break;
        case 3:
            if (RoomObjects_IsFreeAt90(&actor->position, actor->yaw)) {
                FieldActorRoomStates_RequestSpotClaim(actor, FIELD_ACTOR_SPOT_PLUS, FARS_PRIORITY, FARS_NO_ARG);
            }
            break;
        case 1:
            if (RoomObjects_IsFreeAt270(&actor->position, actor->yaw)) {
                FieldActorRoomStates_RequestSpotClaim(actor, FIELD_ACTOR_SPOT_MINUS, FARS_PRIORITY, FARS_NO_ARG);
            }
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov004_02228c84, FieldActorRoomStates_TryLeaveSpotStay)

/* func_ov004_02228d14: while one of the musics 0x63 to 0xab plays and its sound entry plays:
 * the first time, when the body's animation is past its first whole frame, it blends into the
 * beat over 10 frames; the body's animation is stepped from frame 0 by the entry's word at
 * 0xc, its speed then 1.0; the actor's cull flags are cleared. Otherwise the body is updated.
 * QUIRK: the blend tests only the low 16 bits of the animation's whole frame. */
void FieldActorRoomStates_BeatSpotStay(FieldActor *actor)
{
    if (Math_IsBetween(Music_CurrentMusic(), FARS_BEAT_MUSIC_FIRST, FARS_BEAT_MUSIC_LAST)) {
        const int *entry = SoundSys_FirstEntryData();
        if (entry != NULL && ((const s8 *) entry)[3] != FARS_SOUND_STOPPED) {
            LayeredModel *model = (LayeredModel *) (void *) actor->unk_234;
            FieldActorSpotStay *work = fars_spot_stay_of(actor);
            if (work->on_beat == 0) {
                work->on_beat = 1;
                if (fars_whole_frames(model->base.frames.frame) != 0) {
                    Ramp_Start((Ramp *) (void *) &model->base.ramp, FARS_BEAT_BLEND_FRAMES);
                }
            }
            model->base.frames.frame = 0;
            model->base.frames.speed = entry[FARS_BEAT_SPEED_WORD];
            LayeredModel_UpdateA(model);
            model->base.frames.speed = FARS_BEAT_AFTER_SPEED;
            FieldActor_Base(actor)->cull_flags = 0;
            return;
        }
    }
    FieldActor_UpdateBody(actor);
}
CLEAN_AS(func_ov004_02228d14, FieldActorRoomStates_BeatSpotStay)

/* func_ov004_02228da0 (state 0x28's exit): the actor's cull flags as they were on entering. */
void FieldActorRoomStates_LeaveSpotStay(FieldActor *actor)
{
    FieldActor_Base(actor)->cull_flags = fars_spot_stay_of(actor)->cull_flags;
}
CLEAN_AS(func_ov004_02228da0, FieldActorRoomStates_LeaveSpotStay)

/* func_ov004_02228db0 (state 0x28's message handler): state 0x28 asked for (0, priority 6). */
void FieldActorRoomStates_SpotStayMessage(FieldActor *actor, int arg)
{
    FieldActorRoomStates_RequestSpotStay(actor, 0, FARS_PRIORITY, arg);
}
CLEAN_AS(func_ov004_02228db0, FieldActorRoomStates_SpotStayMessage)

/* func_ov004_02228dc4 (state 0x28's entry): animation 0x24 loops (blended over the request's
 * frames) unless it plays already; the work keeps the cull flags, not yet on the beat. */
void FieldActorRoomStates_EnterSpotStay(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    u16 blend = *(const u16 *) (const void *) request->payload;
    if (actor->animation != FARS_ANIM_SPOT_STAY) {
        FieldActor_PlayAnimationLoop(actor, FARS_ANIM_SPOT_STAY, blend, 0);
    }
    FieldActorSpotStay *work = fars_spot_stay_of(actor);
    work->cull_flags = FieldActor_Base(actor)->cull_flags;
    work->on_beat = 0;
}
CLEAN_AS(func_ov004_02228dc4, FieldActorRoomStates_EnterSpotStay)

/* func_ov004_02228dfc: state 0x28 asked for with the frames its animation blends over; whether
 * it was queued. */
int FieldActorRoomStates_RequestSpotStay(FieldActor *actor, u16 blend, int priority, int arg)
{
    StateRequest request;
    StateRequest_Construct(&request);
    StateRequest_Set(&request, FARS_SPOT_STAY, priority, arg);
    *(u16 *) (void *) request.payload = blend;
    int queued = FieldActor_QueueRequest(actor, &request);
    StateRequest_Destruct(&request);
    return queued;
}
CLEAN_AS(func_ov004_02228dfc, FieldActorRoomStates_RequestSpotStay)

/* ---- State 0x27, set at the spot */

/* func_ov004_02228e38 (state 0x27's update): the body and its sound, what is reported, the
 * contact bodies and the end of the animation. */
void FieldActorRoomStates_UpdateSpotEnter(FieldActor *actor)
{
    FieldActorRoomStates_StepSpotEnter(actor);
    FieldActor_FollowReported(actor);
    FieldActor_EnterContact(actor);
    FieldActorRoomStates_EndSpotEnter(actor);
}
CLEAN_AS(func_ov004_02228e38, FieldActorRoomStates_UpdateSpotEnter)

/* func_ov004_02228e58: once the animation is over, state 0x28 is asked for (0, priority 6). */
void FieldActorRoomStates_EndSpotEnter(FieldActor *actor)
{
    if (FrameCtrl_IsDone(&actor->anim)) {
        FieldActorRoomStates_RequestSpotStay(actor, FARS_SPOT_STAY_AFTER_ENTER, FARS_PRIORITY, FARS_NO_ARG);
    }
}
CLEAN_AS(func_ov004_02228e58, FieldActorRoomStates_EndSpotEnter)

/* func_ov004_02228e80: the body updated; as the animation passes frame 12 in a room the object
 * at the work's point (at the actor's height) plays its sound 1. */
void FieldActorRoomStates_StepSpotEnter(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    if (FrameCtrl_Passed(&actor->anim, FARS_SPOT_ENTER_SOUND_FRAME) && fars_in_room()) {
        const FieldActorSpotEnter *work = fars_spot_enter_of(actor);
        Vec3 point = {work->x, actor->position.y, work->z};
        RoomPointSound_Play1(&point);
    }
}
CLEAN_AS(func_ov004_02228e80, FieldActorRoomStates_StepSpotEnter)

/* func_ov004_02228ed4 (state 0x27's exit): the actor stands at the work's point at its yaw. */
void FieldActorRoomStates_LeaveSpotEnter(FieldActor *actor, int next)
{
    (void) next;
    FieldActorSpotEnter *work = fars_spot_enter_of(actor);
    actor->position.x = work->x;
    actor->position.z = work->z;
    FieldActor_SetYaw(actor, &work->yaw);
}
CLEAN_AS(func_ov004_02228ed4, FieldActorRoomStates_LeaveSpotEnter)

/* func_ov004_02228ef4 (state 0x27's message handler): state 0x27 asked for (priority 6) with
 * the point and yaw kept at 0x8f0. */
void FieldActorRoomStates_SpotEnterMessage(FieldActor *actor, int arg)
{
    u32 x;
    u32 z;
    s16 yaw;
    FieldActorRoomStates_GetSpotEnterSaved(actor->saved.packed, &x, &z, &yaw);
    FieldActorRoomStates_RequestSpotEnter(actor, (const int *) (void *) &x, (const int *) (void *) &z, &yaw, FARS_PRIORITY,
                                          (s16) arg);
}
CLEAN_AS(func_ov004_02228ef4, FieldActorRoomStates_SpotEnterMessage)

/* func_ov004_02228f28 (state 0x27's entry): animation 0x23 plays once (no blend), sound 0x4c5;
 * the request's point and yaw go to the work and to 0x8f0. */
void FieldActorRoomStates_EnterSpotEnter(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    FieldActor_PlayAnimationOnce(actor, FARS_ANIM_SPOT_ENTER, 0, 0);
    FieldActor_PlaySound(actor, FARS_SPOT_ENTER_SOUND);
    const FieldActorSpotEnter *args = (const FieldActorSpotEnter *) (const void *) request->payload;
    s16 yaw = args->yaw;
    FieldActorRoomStates_SetSpotEnterWork(fars_spot_enter_of(actor), args->x, args->z, yaw);
    FieldActorRoomStates_PutSpotEnterSaved(actor->saved.packed, args->x, args->z, yaw);
}
CLEAN_AS(func_ov004_02228f28, FieldActorRoomStates_EnterSpotEnter)

/* func_ov004_02228f84: the point (bytes 0 to 4) and yaw (bytes 5 and 6) kept for state 0x27. */
void FieldActorRoomStates_GetSpotEnterSaved(const u8 *saved, u32 *x, u32 *z, s16 *yaw)
{
    PackedBytes_UnpackPoint(saved, x, z);
    *yaw = PackedBytes_ReadS16(saved + 5);
}
CLEAN_AS(func_ov004_02228f84, FieldActorRoomStates_GetSpotEnterSaved)

/* func_ov004_02228fa0: the point and yaw of state 0x27 kept. */
void FieldActorRoomStates_PutSpotEnterSaved(u8 *saved, int x, int z, int yaw)
{
    PackedBytes_PackPoint(saved, x, z);
    PackedBytes_WriteS16(saved + 5, yaw);
}
CLEAN_AS(func_ov004_02228fa0, FieldActorRoomStates_PutSpotEnterSaved)

/* func_ov004_02228fbc: state 0x27's work: the point and the yaw. */
void FieldActorRoomStates_SetSpotEnterWork(FieldActorSpotEnter *work, int x, int z, int yaw)
{
    work->x = x;
    work->z = z;
    work->yaw = (s16) yaw;
}
CLEAN_AS(func_ov004_02228fbc, FieldActorRoomStates_SetSpotEnterWork)

/* func_ov004_02228fc4: state 0x27 asked for with a point and a yaw; whether it was queued. */
int FieldActorRoomStates_RequestSpotEnter(FieldActor *actor, const int *x, const int *z, const s16 *yaw, int priority, s16 arg)
{
    StateRequest request;
    StateRequest_Construct(&request);
    StateRequest_Set(&request, FARS_SPOT_ENTER, priority, arg);
    FieldActorRoomStates_PutSpotEnterArgs((FieldActorSpotEnter *) (void *) request.payload, *x, *z, *yaw);
    int queued = FieldActor_QueueRequest(actor, &request);
    StateRequest_Destruct(&request);
    return queued;
}
CLEAN_AS(func_ov004_02228fc4, FieldActorRoomStates_RequestSpotEnter)

/* ---- States 0x24 to 0x26, onto a spot */

static_assert(sizeof(FieldActorSpotApproach) <= sizeof(FieldActorWork), "state 0x24's work");
static_assert(sizeof(FieldActorSpotApproach) <= sizeof(((StateRequest *) 0)->payload), "state 0x24's arguments");
static_assert(offsetof(FieldActorSpotApproach, way) == 0x0a, "the way");

#define FARS_SPOT_APPROACH 0x24
#define FARS_SPOT_ENTER_STRAIGHT 0x25
#define FARS_SPOT_ENTER_MINUS 0x26
#define FARS_ANIM_SPOT_ENTER_STRAIGHT 0x21
#define FARS_ANIM_SPOT_ENTER_MINUS 0x22

/* The yaw turns of the requests for states 0x27, 0x26 and 0x25 that state 0x24 makes: the
 * actor comes from one side of the spot and ends facing away from the spot's yaw. */
#define FARS_SPOT_ENTER_TURN (-0x4000)
#define FARS_SPOT_ENTER_MINUS_TURN 0x4000
#define FARS_SPOT_ENTER_STRAIGHT_TURN 0x8000

/* The distance from a spot to where state 0x24 stands (-2.0). */
extern const fx32 data_ov004_02254af8;

static FieldActorSpotApproach *fars_spot_approach_of(FieldActor *actor)
{
    return (FieldActorSpotApproach *) (void *) &actor->work;
}

/* A request for state 0x27, 0x26 or 0x25 (`state`) carrying the point 2.0 ahead and the yaw
 * turned by `turn`; whether it was queued. The three put their arguments the same way. */
static int fars_request_spot_ahead(FieldActor *actor, int state, int turn, int priority, int arg)
{
    StateRequest request;
    StateRequest_Construct(&request);
    StateRequest_Set(&request, state, priority, arg);
    Vec3 ahead;
    FieldActor_PointAhead(&ahead, actor, &actor->position, (const u16 *) &actor->yaw, &data_ov004_02247780);
    FieldActorSpotEnter *args = (FieldActorSpotEnter *) (void *) request.payload;
    int yaw = (s16) (actor->yaw + turn);
    if (state == FARS_SPOT_ENTER) {
        FieldActorRoomStates_PutSpotEnterArgs(args, ahead.x, ahead.z, yaw);
    } else if (state == FARS_SPOT_ENTER_MINUS) {
        FieldActorRoomStates_PutSpotEnterMinusArgs(args, ahead.x, ahead.z, yaw);
    } else {
        FieldActorRoomStates_PutSpotEnterStraightArgs(args, ahead.x, ahead.z, yaw);
    }
    int queued = FieldActor_QueueRequest(actor, &request);
    StateRequest_Destruct(&request);
    return queued;
}

/* func_ov004_02229010: state 0x27 asked for with the point 2.0 ahead and the yaw less 0x4000;
 * whether it was queued. */
int FieldActorRoomStates_RequestSpotEnterAhead(FieldActor *actor, int priority, int arg)
{
    return fars_request_spot_ahead(actor, FARS_SPOT_ENTER, FARS_SPOT_ENTER_TURN, priority, arg);
}
CLEAN_AS(func_ov004_02229010, FieldActorRoomStates_RequestSpotEnterAhead)

/* func_ov004_02229078: a request's point and yaw for state 0x27. */
void FieldActorRoomStates_PutSpotEnterArgs(FieldActorSpotEnter *args, int x, int z, int yaw)
{
    args->x = x;
    args->z = z;
    args->yaw = (s16) yaw;
}
CLEAN_AS(func_ov004_02229078, FieldActorRoomStates_PutSpotEnterArgs)

/* The step of states 0x26 and 0x25, as StepSpotEnter: the body updated; as the animation
 * passes frame 12 in a room the object at the work's point (at the actor's height) plays its
 * sound 1. */
static void fars_step_spot_enter(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    if (FrameCtrl_Passed(&actor->anim, FARS_SPOT_ENTER_SOUND_FRAME) && fars_in_room()) {
        const FieldActorSpotEnter *work = fars_spot_enter_of(actor);
        Vec3 point = {work->x, actor->position.y, work->z};
        RoomPointSound_Play1(&point);
    }
}

/* The end of states 0x26 and 0x25: once the animation is over, state 0x28 (0, priority 6). */
static void fars_end_spot_enter(FieldActor *actor)
{
    if (FrameCtrl_IsDone(&actor->anim)) {
        FieldActorRoomStates_RequestSpotStay(actor, FARS_SPOT_STAY_AFTER_ENTER, FARS_PRIORITY, FARS_NO_ARG);
    }
}

/* The exit of states 0x26 and 0x25: the actor stands at the work's point at its yaw. */
static void fars_leave_spot_enter(FieldActor *actor)
{
    FieldActorSpotEnter *work = fars_spot_enter_of(actor);
    actor->position.x = work->x;
    actor->position.z = work->z;
    FieldActor_SetYaw(actor, &work->yaw);
}

/* func_ov004_02229080 (state 0x26's update): the body and its sound, what is reported, the
 * contact bodies and the end of the animation. */
void FieldActorRoomStates_UpdateSpotEnterMinus(FieldActor *actor)
{
    FieldActorRoomStates_StepSpotEnterMinus(actor);
    FieldActor_FollowReported(actor);
    FieldActor_EnterContact(actor);
    FieldActorRoomStates_EndSpotEnterMinus(actor);
}
CLEAN_AS(func_ov004_02229080, FieldActorRoomStates_UpdateSpotEnterMinus)

/* func_ov004_022290a0: once the animation is over, state 0x28 is asked for (0, priority 6). */
void FieldActorRoomStates_EndSpotEnterMinus(FieldActor *actor)
{
    fars_end_spot_enter(actor);
}
CLEAN_AS(func_ov004_022290a0, FieldActorRoomStates_EndSpotEnterMinus)

/* func_ov004_022290c8: the body updated; as the animation passes frame 12 in a room the object
 * at the work's point (at the actor's height) plays its sound 1. */
void FieldActorRoomStates_StepSpotEnterMinus(FieldActor *actor)
{
    fars_step_spot_enter(actor);
}
CLEAN_AS(func_ov004_022290c8, FieldActorRoomStates_StepSpotEnterMinus)

/* func_ov004_0222911c (state 0x26's exit): the actor stands at the work's point at its yaw. */
void FieldActorRoomStates_LeaveSpotEnterMinus(FieldActor *actor, int next)
{
    (void) next;
    fars_leave_spot_enter(actor);
}
CLEAN_AS(func_ov004_0222911c, FieldActorRoomStates_LeaveSpotEnterMinus)

/* func_ov004_0222913c (state 0x26's message handler): state 0x26 asked for (priority 6) with the
 * point and yaw kept at 0x8f0. */
void FieldActorRoomStates_SpotEnterMinusMessage(FieldActor *actor, int arg)
{
    u32 x;
    u32 z;
    s16 yaw;
    FieldActorRoomStates_GetSpotEnterMinusSaved(actor->saved.packed, &x, &z, &yaw);
    FieldActorRoomStates_RequestSpotEnterMinus(actor, (const int *) (void *) &x, (const int *) (void *) &z, &yaw,
                                               FARS_PRIORITY, (s16) arg);
}
CLEAN_AS(func_ov004_0222913c, FieldActorRoomStates_SpotEnterMinusMessage)

/* func_ov004_02229170 (state 0x26's entry): animation 0x22 plays once (no blend), sound 0x4c5;
 * the request's point and yaw go to the work and to 0x8f0. */
void FieldActorRoomStates_EnterSpotEnterMinus(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    FieldActor_PlayAnimationOnce(actor, FARS_ANIM_SPOT_ENTER_MINUS, 0, 0);
    FieldActor_PlaySound(actor, FARS_SPOT_ENTER_SOUND);
    const FieldActorSpotEnter *args = (const FieldActorSpotEnter *) (const void *) request->payload;
    s16 yaw = args->yaw;
    FieldActorRoomStates_SetSpotEnterMinusWork(fars_spot_enter_of(actor), args->x, args->z, yaw);
    FieldActorRoomStates_PutSpotEnterMinusSaved(actor->saved.packed, args->x, args->z, yaw);
}
CLEAN_AS(func_ov004_02229170, FieldActorRoomStates_EnterSpotEnterMinus)

/* func_ov004_022291cc: the point (bytes 0 to 4) and yaw (bytes 5 and 6) kept for state 0x26. */
void FieldActorRoomStates_GetSpotEnterMinusSaved(const u8 *saved, u32 *x, u32 *z, s16 *yaw)
{
    PackedBytes_UnpackPoint(saved, x, z);
    *yaw = PackedBytes_ReadS16(saved + 5);
}
CLEAN_AS(func_ov004_022291cc, FieldActorRoomStates_GetSpotEnterMinusSaved)

/* func_ov004_022291e8: the point and yaw of state 0x26 kept. */
void FieldActorRoomStates_PutSpotEnterMinusSaved(u8 *saved, int x, int z, int yaw)
{
    PackedBytes_PackPoint(saved, x, z);
    PackedBytes_WriteS16(saved + 5, yaw);
}
CLEAN_AS(func_ov004_022291e8, FieldActorRoomStates_PutSpotEnterMinusSaved)

/* func_ov004_02229204: state 0x26's work: the point and the yaw. */
void FieldActorRoomStates_SetSpotEnterMinusWork(FieldActorSpotEnter *work, int x, int z, int yaw)
{
    work->x = x;
    work->z = z;
    work->yaw = (s16) yaw;
}
CLEAN_AS(func_ov004_02229204, FieldActorRoomStates_SetSpotEnterMinusWork)

/* func_ov004_0222920c: state 0x26 asked for with a point and a yaw; whether it was queued. */
int FieldActorRoomStates_RequestSpotEnterMinus(FieldActor *actor, const int *x, const int *z, const s16 *yaw, int priority,
                                               s16 arg)
{
    StateRequest request;
    StateRequest_Construct(&request);
    StateRequest_Set(&request, FARS_SPOT_ENTER_MINUS, priority, arg);
    FieldActorRoomStates_PutSpotEnterMinusArgs((FieldActorSpotEnter *) (void *) request.payload, *x, *z, *yaw);
    int queued = FieldActor_QueueRequest(actor, &request);
    StateRequest_Destruct(&request);
    return queued;
}
CLEAN_AS(func_ov004_0222920c, FieldActorRoomStates_RequestSpotEnterMinus)

/* func_ov004_02229258: state 0x26 asked for with the point 2.0 ahead and the yaw plus 0x4000;
 * whether it was queued. */
int FieldActorRoomStates_RequestSpotEnterMinusAhead(FieldActor *actor, int priority, int arg)
{
    return fars_request_spot_ahead(actor, FARS_SPOT_ENTER_MINUS, FARS_SPOT_ENTER_MINUS_TURN, priority, arg);
}
CLEAN_AS(func_ov004_02229258, FieldActorRoomStates_RequestSpotEnterMinusAhead)

/* func_ov004_022292c0: a request's point and yaw for state 0x26. */
void FieldActorRoomStates_PutSpotEnterMinusArgs(FieldActorSpotEnter *args, int x, int z, int yaw)
{
    args->x = x;
    args->z = z;
    args->yaw = (s16) yaw;
}
CLEAN_AS(func_ov004_022292c0, FieldActorRoomStates_PutSpotEnterMinusArgs)

/* func_ov004_022292c8 (state 0x25's update): the body and its sound, what is reported, the
 * contact bodies and the end of the animation. */
void FieldActorRoomStates_UpdateSpotEnterStraight(FieldActor *actor)
{
    FieldActorRoomStates_StepSpotEnterStraight(actor);
    FieldActor_FollowReported(actor);
    FieldActor_EnterContact(actor);
    FieldActorRoomStates_EndSpotEnterStraight(actor);
}
CLEAN_AS(func_ov004_022292c8, FieldActorRoomStates_UpdateSpotEnterStraight)

/* func_ov004_022292e8: once the animation is over, state 0x28 is asked for (0, priority 6). */
void FieldActorRoomStates_EndSpotEnterStraight(FieldActor *actor)
{
    fars_end_spot_enter(actor);
}
CLEAN_AS(func_ov004_022292e8, FieldActorRoomStates_EndSpotEnterStraight)

/* func_ov004_02229310: the body updated; as the animation passes frame 12 in a room the object
 * at the work's point (at the actor's height) plays its sound 1. */
void FieldActorRoomStates_StepSpotEnterStraight(FieldActor *actor)
{
    fars_step_spot_enter(actor);
}
CLEAN_AS(func_ov004_02229310, FieldActorRoomStates_StepSpotEnterStraight)

/* func_ov004_02229364 (state 0x25's exit): the actor stands at the work's point at its yaw. */
void FieldActorRoomStates_LeaveSpotEnterStraight(FieldActor *actor, int next)
{
    (void) next;
    fars_leave_spot_enter(actor);
}
CLEAN_AS(func_ov004_02229364, FieldActorRoomStates_LeaveSpotEnterStraight)

/* func_ov004_02229384 (state 0x25's message handler): state 0x25 asked for (priority 6) with the
 * point and yaw kept at 0x8f0. */
void FieldActorRoomStates_SpotEnterStraightMessage(FieldActor *actor, int arg)
{
    u32 x;
    u32 z;
    s16 yaw;
    FieldActorRoomStates_GetSpotEnterStraightSaved(actor->saved.packed, &x, &z, &yaw);
    FieldActorRoomStates_RequestSpotEnterStraight(actor, (const int *) (void *) &x, (const int *) (void *) &z, &yaw,
                                                  FARS_PRIORITY, (s16) arg);
}
CLEAN_AS(func_ov004_02229384, FieldActorRoomStates_SpotEnterStraightMessage)

/* func_ov004_022293b8 (state 0x25's entry): animation 0x21 plays once (blended over 3 frames),
 * sound 0x4c5; the request's point and yaw go to the work and to 0x8f0. */
void FieldActorRoomStates_EnterSpotEnterStraight(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    FieldActor_PlayAnimationOnce(actor, FARS_ANIM_SPOT_ENTER_STRAIGHT, FARS_BLEND, 0);
    FieldActor_PlaySound(actor, FARS_SPOT_ENTER_SOUND);
    const FieldActorSpotEnter *args = (const FieldActorSpotEnter *) (const void *) request->payload;
    s16 yaw = args->yaw;
    FieldActorRoomStates_SetSpotEnterStraightWork(fars_spot_enter_of(actor), args->x, args->z, yaw);
    FieldActorRoomStates_PutSpotEnterStraightSaved(actor->saved.packed, args->x, args->z, yaw);
}
CLEAN_AS(func_ov004_022293b8, FieldActorRoomStates_EnterSpotEnterStraight)

/* func_ov004_02229414: the point (bytes 0 to 4) and yaw (bytes 5 and 6) kept for state 0x25. */
void FieldActorRoomStates_GetSpotEnterStraightSaved(const u8 *saved, u32 *x, u32 *z, s16 *yaw)
{
    PackedBytes_UnpackPoint(saved, x, z);
    *yaw = PackedBytes_ReadS16(saved + 5);
}
CLEAN_AS(func_ov004_02229414, FieldActorRoomStates_GetSpotEnterStraightSaved)

/* func_ov004_02229430: the point and yaw of state 0x25 kept. */
void FieldActorRoomStates_PutSpotEnterStraightSaved(u8 *saved, int x, int z, int yaw)
{
    PackedBytes_PackPoint(saved, x, z);
    PackedBytes_WriteS16(saved + 5, yaw);
}
CLEAN_AS(func_ov004_02229430, FieldActorRoomStates_PutSpotEnterStraightSaved)

/* func_ov004_0222944c: state 0x25's work: the point and the yaw. */
void FieldActorRoomStates_SetSpotEnterStraightWork(FieldActorSpotEnter *work, int x, int z, int yaw)
{
    work->x = x;
    work->z = z;
    work->yaw = (s16) yaw;
}
CLEAN_AS(func_ov004_0222944c, FieldActorRoomStates_SetSpotEnterStraightWork)

/* func_ov004_02229454: state 0x25 asked for with a point and a yaw; whether it was queued. */
int FieldActorRoomStates_RequestSpotEnterStraight(FieldActor *actor, const int *x, const int *z, const s16 *yaw, int priority,
                                                  s16 arg)
{
    StateRequest request;
    StateRequest_Construct(&request);
    StateRequest_Set(&request, FARS_SPOT_ENTER_STRAIGHT, priority, arg);
    FieldActorRoomStates_PutSpotEnterStraightArgs((FieldActorSpotEnter *) (void *) request.payload, *x, *z, *yaw);
    int queued = FieldActor_QueueRequest(actor, &request);
    StateRequest_Destruct(&request);
    return queued;
}
CLEAN_AS(func_ov004_02229454, FieldActorRoomStates_RequestSpotEnterStraight)

/* func_ov004_022294a0: state 0x25 asked for with the point 2.0 ahead and the yaw turned round;
 * whether it was queued. */
int FieldActorRoomStates_RequestSpotEnterStraightAhead(FieldActor *actor, int priority, int arg)
{
    return fars_request_spot_ahead(actor, FARS_SPOT_ENTER_STRAIGHT, FARS_SPOT_ENTER_STRAIGHT_TURN, priority, arg);
}
CLEAN_AS(func_ov004_022294a0, FieldActorRoomStates_RequestSpotEnterStraightAhead)

/* func_ov004_02229508: a request's point and yaw for state 0x25. */
void FieldActorRoomStates_PutSpotEnterStraightArgs(FieldActorSpotEnter *args, int x, int z, int yaw)
{
    args->x = x;
    args->z = z;
    args->yaw = (s16) yaw;
}
CLEAN_AS(func_ov004_02229508, FieldActorRoomStates_PutSpotEnterStraightArgs)

/* ---- State 0x24, to a spot */

/* func_ov004_02229510 (state 0x24's update): the ease to the work's point and yaw, the body, the
 * contact bodies and the claim's answer. */
void FieldActorRoomStates_UpdateSpotApproach(FieldActor *actor)
{
    FieldActorRoomStates_StandSpotApproach(actor);
    FieldActor_UpdateBody(actor);
    FieldActor_EnterContact(actor);
    FieldActorRoomStates_RunSpotApproach(actor);
}
CLEAN_AS(func_ov004_02229510, FieldActorRoomStates_UpdateSpotApproach)

/* func_ov004_02229530: another console's actor has the state's bar for requests at its end
 * value. For this console's: while the claim's answer is not known nothing; refused, the bar
 * is its end value and state 2 is asked for (3, priority 1); given (or any other answer), once
 * the actor stands exactly at the work's point and yaw, by the way state 0x25, 0x27 or 0x26 with
 * the point 2.0 ahead (priority 6). */
void FieldActorRoomStates_RunSpotApproach(FieldActor *actor)
{
    if (!fars_is_local(actor)) {
        actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
        return;
    }
    switch (PlaceClaim_Answer()) {
        case PLACE_CLAIM_WAITING:
            return;
        case PLACE_CLAIM_REFUSED:
            actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
            FieldActor_RequestState2(actor, FARS_END_STATE2_ARG, FARS_END_PRIORITY, FARS_NO_ARG);
            return;
        default:
            break;
    }
    const FieldActorSpotApproach *work = fars_spot_approach_of(actor);
    if (actor->position.x != work->x || actor->position.z != work->z || work->yaw != actor->yaw) {
        return;
    }
    switch (work->way) {
        case FIELD_ACTOR_SPOT_STRAIGHT:
            FieldActorRoomStates_RequestSpotEnterStraightAhead(actor, FARS_PRIORITY, FARS_NO_ARG);
            break;
        case FIELD_ACTOR_SPOT_PLUS:
            FieldActorRoomStates_RequestSpotEnterAhead(actor, FARS_PRIORITY, FARS_NO_ARG);
            break;
        case FIELD_ACTOR_SPOT_MINUS:
            FieldActorRoomStates_RequestSpotEnterMinusAhead(actor, FARS_PRIORITY, FARS_NO_ARG);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov004_02229530, FieldActorRoomStates_RunSpotApproach)

/* func_ov004_022295f8: the actor eased to the work's point and yaw. */
void FieldActorRoomStates_StandSpotApproach(FieldActor *actor)
{
    const FieldActorSpotApproach *work = fars_spot_approach_of(actor);
    FieldActor_MoveToPose(actor, work->x, work->z, work->yaw);
}
CLEAN_AS(func_ov004_022295f8, FieldActorRoomStates_StandSpotApproach)

/* func_ov004_02229614 (state 0x24's exit): the actor stands at the work's point at its yaw. */
void FieldActorRoomStates_LeaveSpotApproach(FieldActor *actor, int next)
{
    (void) next;
    FieldActorSpotApproach *work = fars_spot_approach_of(actor);
    actor->position.x = work->x;
    actor->position.z = work->z;
    FieldActor_SetYaw(actor, &work->yaw);
}
CLEAN_AS(func_ov004_02229614, FieldActorRoomStates_LeaveSpotApproach)

/* func_ov004_02229634 (state 0x24's message handler): state 0x24 asked for (priority 6) with the
 * spot's point, yaw and way kept at 0x8f0. */
void FieldActorRoomStates_SpotApproachMessage(FieldActor *actor, s16 arg)
{
    u32 x;
    u32 z;
    s16 yaw;
    u8 way;
    FieldActorRoomStates_GetSpotApproachSaved(actor->saved.packed, &x, &z, &yaw, &way);
    FieldActorRoomStates_RequestSpotApproach(actor, (int) x, (int) z, yaw, way, FARS_PRIORITY, arg);
}
CLEAN_AS(func_ov004_02229634, FieldActorRoomStates_SpotApproachMessage)

/* func_ov004_02229678 (state 0x24's entry): the work is the point 2.0 from the request's spot
 * (at the actor's height) on the way's side, the yaw towards the spot from there and the way;
 * the spot's point, yaw and way are kept at 0x8f0; this console's actor claims the spot's
 * place; animation 0x1a loops (blended over 3 frames). */
void FieldActorRoomStates_EnterSpotApproach(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    const FieldActorSpotApproach *args = (const FieldActorSpotApproach *) (const void *) request->payload;
    s16 spot_yaw = args->yaw;
    u8 way = args->way;
    Vec3 spot = {args->x, actor->position.y, args->z};
    s16 yaw = (s16) (spot_yaw + data_ov004_0224776c[way]);
    Vec3 stand;
    FieldActor_PointAhead(&stand, actor, &spot, (const u16 *) &yaw, &data_ov004_02254af8);
    FieldActorRoomStates_SetSpotApproachWork(fars_spot_approach_of(actor), stand.x, stand.z, yaw, way);
    FieldActorRoomStates_PutSpotApproachSaved(actor->saved.packed, spot.x, spot.z, spot_yaw, way);
    if (fars_is_local(actor)) {
        PlaceClaim_Request(&spot);
    }
    FieldActor_PlayAnimationLoop(actor, FARS_ANIM_1A, FARS_BLEND, 0);
}
CLEAN_AS(func_ov004_02229678, FieldActorRoomStates_EnterSpotApproach)

/* func_ov004_02229718: the point (bytes 0 to 4), yaw (bytes 5 and 6) and way (byte 7) kept for
 * state 0x24. */
void FieldActorRoomStates_GetSpotApproachSaved(const u8 *saved, u32 *x, u32 *z, s16 *yaw, u8 *way)
{
    PackedBytes_UnpackPoint(saved, x, z);
    *yaw = PackedBytes_ReadS16(saved + 5);
    *way = saved[7];
}
CLEAN_AS(func_ov004_02229718, FieldActorRoomStates_GetSpotApproachSaved)

/* func_ov004_0222973c: the spot's point, yaw and way of state 0x24 kept. */
void FieldActorRoomStates_PutSpotApproachSaved(u8 *saved, int x, int z, int yaw, u8 way)
{
    PackedBytes_PackPoint(saved, x, z);
    PackedBytes_WriteS16(saved + 5, yaw);
    saved[7] = way;
}
CLEAN_AS(func_ov004_0222973c, FieldActorRoomStates_PutSpotApproachSaved)

/* func_ov004_02229760: state 0x24's work: the point, the yaw and the way. */
void FieldActorRoomStates_SetSpotApproachWork(FieldActorSpotApproach *work, int x, int z, s16 yaw, u8 way)
{
    work->x = x;
    work->z = z;
    work->yaw = yaw;
    work->way = way;
}
CLEAN_AS(func_ov004_02229760, FieldActorRoomStates_SetSpotApproachWork)

/* func_ov004_02229774: state 0x24 asked for with a spot's point, yaw and way; whether it was
 * queued. */
int FieldActorRoomStates_RequestSpotApproach(FieldActor *actor, int x, int z, int yaw, u8 way, int priority, s16 arg)
{
    StateRequest request;
    StateRequest_Construct(&request);
    StateRequest_Set(&request, FARS_SPOT_APPROACH, priority, arg);
    FieldActorRoomStates_PutSpotApproachArgs((FieldActorSpotApproach *) (void *) request.payload, x, z, (s16) yaw, way);
    int queued = FieldActor_QueueRequest(actor, &request);
    StateRequest_Destruct(&request);
    return queued;
}
CLEAN_AS(func_ov004_02229774, FieldActorRoomStates_RequestSpotApproach)

/* func_ov004_022297c4: a request's arguments for state 0x24. */
void FieldActorRoomStates_PutSpotApproachArgs(FieldActorSpotApproach *args, int x, int z, s16 yaw, u8 way)
{
    args->x = x;
    args->z = z;
    args->yaw = yaw;
    args->way = way;
}
CLEAN_AS(func_ov004_022297c4, FieldActorRoomStates_PutSpotApproachArgs)

/* ---- States 0x23 to 0x20, moving a room object */

static_assert(sizeof(FieldActorObjectStep) <= sizeof(FieldActorWork), "the steps' work");
static_assert(sizeof(FieldActorObjectMove) <= sizeof(FieldActorWork), "the moves' work");
static_assert(offsetof(FieldActor, player) == 0x800, "player");

#define FARS_PULL 0x21
#define FARS_PUSH_STEP 0x22
#define FARS_PULL_STEP 0x23
#define FARS_ANIM_PULL 0x1e
#define FARS_ANIM_PUSH_STEP 0x1f
#define FARS_ANIM_PULL_STEP 0x20

/* State 0x1e (holding the object) is asked for with two flags and priority 5. */
#define FARS_HOLD_PRIORITY 5

/* The sound of a move only the room's objects stop. */
#define FARS_MOVE_BLOCKED_SOUND 0x6d

/* Why a move is refused (bits). */
#define FARS_MOVE_BLOCKED 1     /* the object cannot move that way */
#define FARS_MOVE_NOT_ALLOWED 2 /* not a house's room, or not player 0 */

/* The quadrants of FieldActor_PushQuadrant that keep a refused push or pull going. */
#define FARS_PUSH_AHEAD 0
#define FARS_PULL_BACK 2

/* How far behind the step back ends (-2.0). */
extern const fx32 data_ov004_02254afc;

static FieldActorObjectStep *fars_object_step_of(FieldActor *actor)
{
    return (FieldActorObjectStep *) (void *) &actor->work;
}

static FieldActorObjectMove *fars_object_move_of(FieldActor *actor)
{
    return (FieldActorObjectMove *) (void *) &actor->work;
}

/* The end of a step: once the animation is over, the state's bar for requests is its end
 * value; while A is held state 0x1e is asked for (1, 0, priority 5), else state 2 (3, priority
 * 1). */
static void fars_end_object_step(FieldActor *actor)
{
    if (!FrameCtrl_IsDone(&actor->anim)) {
        return;
    }
    actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
    if (FIELD_ACTOR_HOLD(actor) != 0) {
        FieldActorRoomStates2_RequestFurnitureHold(actor, 1, 0, FARS_HOLD_PRIORITY, FARS_NO_ARG);
    } else {
        FieldActor_RequestState2(actor, FARS_END_STATE2_ARG, FARS_END_PRIORITY, FARS_NO_ARG);
    }
}

/* A push (`pull` 0) or a pull once its animation is over. Another console's actor has the
 * state's bar for requests at its end value. This console's, where the object can move that
 * way and it is player 0 in a house's room, asks for the step (priority 6) and moves the
 * object; else the first time sound 0x6d plays when only the room's objects stop it, and
 * unless the stick is still pushed that way the bar is its end value and state 0x1e is asked
 * for (0, 1, priority 5). */
static void fars_run_object_move(FieldActor *actor, int pull)
{
    if (!FrameCtrl_IsDone(&actor->anim)) {
        return;
    }
    if (!fars_is_local(actor)) {
        actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
        return;
    }
    u8 refused = 0;
    int can_move = pull ? RoomPushes_CanPull(RoomPushes_Records()) : RoomPushes_CanPush(RoomPushes_Records());
    if (can_move == 0) {
        refused = FARS_MOVE_BLOCKED;
    }
    if (SceneKinds_CurrentIsHouseRoom() == 0 || actor->player != 0) {
        refused |= FARS_MOVE_NOT_ALLOWED;
    }
    if (refused == 0) {
        if (pull) {
            FieldActorRoomStates_RequestPullStep(actor, FARS_PRIORITY, FARS_NO_ARG);
            RoomPushes_TryPull(RoomPushes_Records());
        } else {
            FieldActorRoomStates_RequestPushStep(actor, FARS_PRIORITY, FARS_NO_ARG);
            RoomPushes_TryPush(RoomPushes_Records());
        }
        return;
    }
    FieldActorObjectMove *work = fars_object_move_of(actor);
    if (work->warned == 0) {
        work->warned = 1;
        if (refused == FARS_MOVE_BLOCKED) {
            FieldActor_PlaySound(actor, FARS_MOVE_BLOCKED_SOUND);
        }
    }
    int pushed_to = FieldActor_PushQuadrant(actor);
    if ((int) FieldActor_Push(actor) > 0 && pushed_to == (pull ? FARS_PULL_BACK : FARS_PUSH_AHEAD)) {
        return;
    }
    actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
    FieldActorRoomStates2_RequestFurnitureHold(actor, 0, 1, FARS_HOLD_PRIORITY, FARS_NO_ARG);
}

/* func_ov004_022297d8 (state 0x23's update): the body, the move, the contact bodies, the shadow
 * and the end of the animation. */
void FieldActorRoomStates_UpdatePullStep(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    FieldActorRoomStates_MovePullStep(actor);
    FieldActor_EnterContact(actor);
    FieldActor_PlaceShadow(actor);
    FieldActorRoomStates_EndPullStep(actor);
}
CLEAN_AS(func_ov004_022297d8, FieldActorRoomStates_UpdatePullStep)

/* func_ov004_02229800: once the animation is over, state 0x1e while A is held, else state 2. */
void FieldActorRoomStates_EndPullStep(FieldActor *actor)
{
    fars_end_object_step(actor);
}
CLEAN_AS(func_ov004_02229800, FieldActorRoomStates_EndPullStep)

/* func_ov004_02229860: the actor set back to where the frame began (its height kept), which is
 * also its last position, and moved from there with the walls; then of where it was before,
 * the z comes back when the x was the frame's start x, else the x.
 * QUIRK: the comparison reads the frame's start x after the move. */
void FieldActorRoomStates_MovePullStep(FieldActor *actor)
{
    Vec3 before = actor->position;
    actor->position.x = actor->start_position.x;
    actor->position.y = before.y;
    actor->position.z = actor->start_position.z;
    FieldActor_Base(actor)->last_position = actor->position;
    FieldActor_MoveWithCollision(actor);
    if (before.x == actor->start_position.x) {
        actor->position.z = before.z;
    } else {
        actor->position.x = before.x;
    }
}
CLEAN_AS(func_ov004_02229860, FieldActorRoomStates_MovePullStep)

/* func_ov004_022298b8 (state 0x23's exit): the actor stands at the work's point, which is also
 * its last position. */
void FieldActorRoomStates_LeavePullStep(FieldActor *actor)
{
    const FieldActorObjectStep *work = fars_object_step_of(actor);
    actor->position.x = work->x;
    actor->position.z = work->z;
    FieldActor_Base(actor)->last_position = actor->position;
}
CLEAN_AS(func_ov004_022298b8, FieldActorRoomStates_LeavePullStep)

/* func_ov004_022298dc (state 0x23's message handler): nothing. */
void FieldActorRoomStates_PullStepMessage(FieldActor *actor, int arg)
{
    (void) actor;
    (void) arg;
}
CLEAN_AS(func_ov004_022298dc, FieldActorRoomStates_PullStepMessage)

/* func_ov004_022298e0 (state 0x23's entry): animation 0x20 plays once (blended over 3 frames);
 * the work is the point 2.0 behind. */
void FieldActorRoomStates_EnterPullStep(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) request;
    (void) previous;
    FieldActor_PlayAnimationOnce(actor, FARS_ANIM_PULL_STEP, FARS_BLEND, 0);
    Vec3 end;
    FieldActor_PointAhead(&end, actor, &actor->position, (const u16 *) &actor->yaw, &data_ov004_02254afc);
    FieldActorRoomStates_SetPullStepWork(fars_object_step_of(actor), end.x, end.z);
}
CLEAN_AS(func_ov004_022298e0, FieldActorRoomStates_EnterPullStep)

/* func_ov004_02229920: state 0x23's work: where the step ends. */
void FieldActorRoomStates_SetPullStepWork(FieldActorObjectStep *work, int x, int z)
{
    work->x = x;
    work->z = z;
}
CLEAN_AS(func_ov004_02229920, FieldActorRoomStates_SetPullStepWork)

/* func_ov004_02229928: state 0x23 asked for; whether it was queued. */
int FieldActorRoomStates_RequestPullStep(FieldActor *actor, int priority, int arg)
{
    return fars_request(actor, FARS_PULL_STEP, priority, arg);
}
CLEAN_AS(func_ov004_02229928, FieldActorRoomStates_RequestPullStep)

/* func_ov004_02229960 (state 0x22's update): the body, the contact bodies, the shadow and the
 * end of the animation. */
void FieldActorRoomStates_UpdatePushStep(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    FieldActor_EnterContact(actor);
    FieldActor_PlaceShadow(actor);
    FieldActorRoomStates_EndPushStep(actor);
}
CLEAN_AS(func_ov004_02229960, FieldActorRoomStates_UpdatePushStep)

/* func_ov004_02229980: once the animation is over, state 0x1e while A is held, else state 2. */
void FieldActorRoomStates_EndPushStep(FieldActor *actor)
{
    fars_end_object_step(actor);
}
CLEAN_AS(func_ov004_02229980, FieldActorRoomStates_EndPushStep)

/* func_ov004_022299e0 (state 0x22's exit): the actor stands at the work's point. */
void FieldActorRoomStates_LeavePushStep(FieldActor *actor)
{
    const FieldActorObjectStep *work = fars_object_step_of(actor);
    actor->position.x = work->x;
    actor->position.z = work->z;
}
CLEAN_AS(func_ov004_022299e0, FieldActorRoomStates_LeavePushStep)

/* func_ov004_022299f8 (state 0x22's message handler): nothing. */
void FieldActorRoomStates_PushStepMessage(FieldActor *actor, int arg)
{
    (void) actor;
    (void) arg;
}
CLEAN_AS(func_ov004_022299f8, FieldActorRoomStates_PushStepMessage)

/* func_ov004_022299fc (state 0x22's entry): animation 0x1f plays once (blended over 3 frames);
 * the work is the point 2.0 ahead. */
void FieldActorRoomStates_EnterPushStep(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) request;
    (void) previous;
    FieldActor_PlayAnimationOnce(actor, FARS_ANIM_PUSH_STEP, FARS_BLEND, 0);
    Vec3 end;
    FieldActor_PointAhead(&end, actor, &actor->position, (const u16 *) &actor->yaw, &data_ov004_02247780);
    FieldActorRoomStates_SetPushStepWork(fars_object_step_of(actor), end.x, end.z);
}
CLEAN_AS(func_ov004_022299fc, FieldActorRoomStates_EnterPushStep)

/* func_ov004_02229a3c: state 0x22's work: where the step ends. */
void FieldActorRoomStates_SetPushStepWork(FieldActorObjectStep *work, int x, int z)
{
    work->x = x;
    work->z = z;
}
CLEAN_AS(func_ov004_02229a3c, FieldActorRoomStates_SetPushStepWork)

/* func_ov004_02229a44: state 0x22 asked for; whether it was queued. */
int FieldActorRoomStates_RequestPushStep(FieldActor *actor, int priority, int arg)
{
    return fars_request(actor, FARS_PUSH_STEP, priority, arg);
}
CLEAN_AS(func_ov004_02229a44, FieldActorRoomStates_RequestPushStep)

/* func_ov004_02229a7c (state 0x21's update): the body, the move with the walls, the contact
 * bodies, the shadow and the pull. */
void FieldActorRoomStates_UpdatePull(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    FieldActor_MoveWithCollision(actor);
    FieldActor_EnterContact(actor);
    FieldActor_PlaceShadow(actor);
    FieldActorRoomStates_RunPull(actor);
}
CLEAN_AS(func_ov004_02229a7c, FieldActorRoomStates_UpdatePull)

/* func_ov004_02229aa4: once the animation is over, the object pulled back with the actor (state
 * 0x23) where it can be; else sound 0x6d the first time when only the room's objects stop it,
 * and while the stick is still pulled back nothing more, else state 0x1e (0, 1, priority 5). */
void FieldActorRoomStates_RunPull(FieldActor *actor)
{
    fars_run_object_move(actor, 1);
}
CLEAN_AS(func_ov004_02229aa4, FieldActorRoomStates_RunPull)

/* func_ov004_02229b88 (state 0x21's message handler): state 0x21 asked for (priority 6). */
void FieldActorRoomStates_PullMessage(FieldActor *actor, int arg)
{
    FieldActorRoomStates_RequestPull(actor, FARS_PRIORITY, arg);
}
CLEAN_AS(func_ov004_02229b88, FieldActorRoomStates_PullMessage)

/* func_ov004_02229b94 (state 0x21's entry): animation 0x1e plays once (blended over 3 frames);
 * no refusal yet. */
void FieldActorRoomStates_EnterPull(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) request;
    (void) previous;
    FieldActor_PlayAnimationOnce(actor, FARS_ANIM_PULL, FARS_BLEND, 0);
    fars_object_move_of(actor)->warned = 0;
}
CLEAN_AS(func_ov004_02229b94, FieldActorRoomStates_EnterPull)

/* func_ov004_02229bb4: state 0x21 asked for; whether it was queued. */
int FieldActorRoomStates_RequestPull(FieldActor *actor, int priority, int arg)
{
    return fars_request(actor, FARS_PULL, priority, arg);
}
CLEAN_AS(func_ov004_02229bb4, FieldActorRoomStates_RequestPull)

/* func_ov004_02229bec (state 0x20's update): the body, the move with the walls, the contact
 * bodies, the shadow and the push. */
void FieldActorRoomStates_UpdatePush(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    FieldActor_MoveWithCollision(actor);
    FieldActor_EnterContact(actor);
    FieldActor_PlaceShadow(actor);
    FieldActorRoomStates_RunPush(actor);
}
CLEAN_AS(func_ov004_02229bec, FieldActorRoomStates_UpdatePush)

/* func_ov004_02229c14: once the animation is over, the object pushed ahead with the actor
 * (state 0x22) where it can be; else sound 0x6d the first time when only the room's objects
 * stop it, and while the stick still pushes ahead nothing more, else state 0x1e (0, 1,
 * priority 5). */
void FieldActorRoomStates_RunPush(FieldActor *actor)
{
    fars_run_object_move(actor, 0);
}
CLEAN_AS(func_ov004_02229c14, FieldActorRoomStates_RunPush)
