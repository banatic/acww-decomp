/* More of overlay 4's states of the field actor (field_actor_room_states.h). */
#include "field_actor_room_states.h"

#include "clean.h"
#include "main/angle_sector.h"
#include "main/effect_system.h"
#include "main/event_queue.h"
#include "main/field_actor.h"
#include "main/field_actor_parts.h"
#include "main/frame_ctrl.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/session.h"
#include "ov004/field_actor_rooms.h"
#include "ov004/rmo_telephone.h"

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

/* Requests elsewhere in the overlay: state 0x2c, and state 0x28 with a halfword. */
extern int func_ov004_02228850(FieldActor *actor, int priority, int arg);
extern int func_ov004_02228dfc(void *actor, unsigned short value, void *priority, void *arg);

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
        func_ov004_02228850(actor, FARS_PRIORITY, FARS_NO_ARG);
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
            func_ov004_02228dfc(actor, 0, (void *) (intptr_t) FARS_PRIORITY, (void *) (intptr_t) FARS_NO_ARG);
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
