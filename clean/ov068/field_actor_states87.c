/* Overlay 68's states 0x87 and 0x88 of the field actor (field_actor_states87.h). */
#include "field_actor_states87.h"

#include "clean.h"
#include "main/calendar.h"
#include "main/date_time.h"
#include "main/field_actor.h"
#include "main/frame_ctrl.h"
#include "main/session_players.h"

static_assert(offsetof(FieldActor, position) == 0x5c, "position");
static_assert(offsetof(FieldActor, yaw) == 0x8e, "yaw");
static_assert(offsetof(FieldActor, anim) == 0x2d0, "anim");
static_assert(offsetof(FieldActor, state) == 0x7f0, "state");
static_assert(offsetof(FieldActor, next_state) == 0x7fc, "next_state");

#define FIELD_ACTOR_87_PLAYER 4 /* this console's player */
#define FIELD_ACTOR_87_STATE_87 0x87
#define FIELD_ACTOR_87_STATE_88 0x88
#define FIELD_ACTOR_87_ANIMATION_87 0x82
#define FIELD_ACTOR_87_ANIMATION_88 0x83
#define FIELD_ACTOR_87_BLEND_88 3
#define FIELD_ACTOR_87_STEP_87 0x16 /* the frame of the footstep */
#define FIELD_ACTOR_87_STEP_88 8
#define FIELD_ACTOR_87_SHIFT_X 0x1c00 /* where each state's end puts the actor */
#define FIELD_ACTOR_87_SHIFT_Z 0x2c00
#define FIELD_ACTOR_87_HALF_TURN 0x8000
#define FIELD_ACTOR_87_PRIORITY 6 /* of the requests FieldActor_PlayerRequest* make */
#define FIELD_ACTOR_87_NO_ARG (-1)

/* ---- State 0x88 */

/* func_ov068_02271e24: the body's frame (FieldActor_UpdateBody) and a footstep at frame 8. */
void FieldActor_StepState88(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    if (FrameCtrl_Passed(&actor->anim, FIELD_ACTOR_87_STEP_88) != 0) {
        FieldActor_PlayFootstep(actor);
    }
}
CLEAN_AS(func_ov068_02271e24, FieldActor_StepState88)

/* func_ov068_02271de8: at the animation's end the bar for requests drops and the actor asks for
 * state 1 (priority 9). */
void FieldActor_EndState88(FieldActor *actor)
{
    if (FrameCtrl_IsDone(&actor->anim) != 0) {
        actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
        FieldActor_RequestState1(actor, 9, FIELD_ACTOR_87_NO_ARG);
    }
}
CLEAN_AS(func_ov068_02271de8, FieldActor_EndState88)

/* func_ov068_02271dd4: state 0x88's update. */
void FieldActor_UpdateState88(FieldActor *actor)
{
    FieldActor_StepState88(actor);
    FieldActor_EndState88(actor);
}
CLEAN_AS(func_ov068_02271dd4, FieldActor_UpdateState88)

/* func_ov068_02271e4c: state 0x88's exit: the actor moves by -1.75 along x and 2.75 along z and
 * turns half round. */
void FieldActor_ExitState88(FieldActor *actor)
{
    actor->position.x -= FIELD_ACTOR_87_SHIFT_X;
    actor->position.z += FIELD_ACTOR_87_SHIFT_Z;
    actor->yaw = (s16) (actor->yaw + FIELD_ACTOR_87_HALF_TURN);
}
CLEAN_AS(func_ov068_02271e4c, FieldActor_ExitState88)

/* func_ov068_02271e78: state 0x88's message handler. */
void FieldActor_State88Message(FieldActor *actor, int arg)
{
    (void) actor;
    (void) arg;
}
CLEAN_AS(func_ov068_02271e78, FieldActor_State88Message)

/* func_ov068_02271e7c: entering state 0x88: animation 0x83 once, blended over 3 frames, at yaw
 * 0. */
void FieldActor_EnterState88(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) request;
    (void) previous;
    FieldActor_PlayAnimationOnce(actor, FIELD_ACTOR_87_ANIMATION_88, FIELD_ACTOR_87_BLEND_88, 0);
    actor->yaw = 0;
}
CLEAN_AS(func_ov068_02271e7c, FieldActor_EnterState88)

/* func_ov068_02271e98: asks for state 0x88; whether it was queued.
 * BUG: the bytes of the request nothing sets are whatever the stack held, and the queue copies
 * them into the actor. */
u32 FieldActor_RequestState88(FieldActor *actor, unsigned int priority, unsigned int arg)
{
    StateRequest request;
#ifdef BUGFIX
    request = (StateRequest){0};
#endif
    StateRequest_Construct(&request);
    StateRequest_Set(&request, FIELD_ACTOR_87_STATE_88, (int) priority, (int) arg);
    u32 queued = (u32) FieldActor_QueueRequest(actor, &request);
    StateRequest_Destruct(&request);
    return queued;
}
CLEAN_AS(func_ov068_02271e98, FieldActor_RequestState88)

/* ---- State 0x87 */

/* func_ov068_02271f28: the body's frame and a footstep at frame 0x16. */
void FieldActor_StepState87(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    if (FrameCtrl_Passed(&actor->anim, FIELD_ACTOR_87_STEP_87) != 0) {
        FieldActor_PlayFootstep(actor);
    }
}
CLEAN_AS(func_ov068_02271f28, FieldActor_StepState87)

/* func_ov068_02271ee4: at the animation's end the bar for requests drops, the actor asks for
 * state 0x10 (no frames, priority 5) and the player's sun flags are cleared. */
void FieldActor_EndState87(FieldActor *actor)
{
    if (FrameCtrl_IsDone(&actor->anim) != 0) {
        actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
        FieldActor_RequestState10(actor, 0, 5, FIELD_ACTOR_87_NO_ARG);
        *SessionPlayers_SunFlags() = 0;
    }
}
CLEAN_AS(func_ov068_02271ee4, FieldActor_EndState87)

/* func_ov068_02271ed0: state 0x87's update. */
void FieldActor_UpdateState87(FieldActor *actor)
{
    FieldActor_StepState87(actor);
    FieldActor_EndState87(actor);
}
CLEAN_AS(func_ov068_02271ed0, FieldActor_UpdateState87)

/* func_ov068_02271f50: state 0x87's exit: the actor moves by 1.75 along x and -2.75 along z and
 * turns half round. */
void FieldActor_ExitState87(FieldActor *actor)
{
    actor->position.x += FIELD_ACTOR_87_SHIFT_X;
    actor->position.z -= FIELD_ACTOR_87_SHIFT_Z;
    actor->yaw = (s16) (actor->yaw + FIELD_ACTOR_87_HALF_TURN);
}
CLEAN_AS(func_ov068_02271f50, FieldActor_ExitState87)

/* func_ov068_02271f7c: state 0x87's message handler. */
void FieldActor_State87Message(FieldActor *actor, int arg)
{
    (void) actor;
    (void) arg;
}
CLEAN_AS(func_ov068_02271f7c, FieldActor_State87Message)

/* func_ov068_02271f80: entering state 0x87: animation 0x82 once at yaw 0, and flag 0 cleared.
 * For a player with a record, the sun date becomes yesterday (the clock's date less a day,
 * packed as the record keeps it: the year in bits 0-6, the month in 7-10, the day in 11-15). */
void FieldActor_EnterState87(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) request;
    (void) previous;
    FieldActor_PlayAnimationOnce(actor, FIELD_ACTOR_87_ANIMATION_87, 0, 0);
    actor->yaw = 0;
    FieldActor_ClearFlag(actor, 0);
    u8 *record = FieldActor_Record(actor);
    if (record == NULL) {
        return;
    }
    DateTime yesterday = {0};
    DateTime_Now(&yesterday);
    DateTime_SubtractDays(&yesterday, 1);
    u16 date = (u16) ((yesterday.year & 0x7f) | (yesterday.month & 0xf) << 7 | (yesterday.day & 0x1f) << 11);
    FieldActor_StoreSunDate(actor, (int) (uintptr_t) record, &date);
}
CLEAN_AS(func_ov068_02271f80, FieldActor_EnterState87)

/* func_ov068_0227200c: asks for state 0x87; whether it was queued.
 * BUG: as FieldActor_RequestState88, the unset bytes of the request are the stack's. */
void *FieldActor_RequestState87(FieldActor *actor, int priority, int arg)
{
    StateRequest request;
#ifdef BUGFIX
    request = (StateRequest){0};
#endif
    StateRequest_Construct(&request);
    StateRequest_Set(&request, FIELD_ACTOR_87_STATE_87, priority, arg);
    int queued = FieldActor_QueueRequest(actor, &request);
    StateRequest_Destruct(&request);
    return (void *) (intptr_t) queued;
}
CLEAN_AS(func_ov068_0227200c, FieldActor_RequestState87)

/* ---- This console's player */

/* func_ov068_02272044: this console's actor (when there is one) lowers its bar for requests and
 * asks for state 0x88 (priority 6); whether it was queued, 0 without an actor. */
int FieldActor_PlayerRequestState88(void)
{
    FieldActor *actor = SessionPlayers_FieldActor(FIELD_ACTOR_87_PLAYER);
    if (actor == NULL) {
        return 0;
    }
    actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
    return (int) FieldActor_RequestState88(actor, FIELD_ACTOR_87_PRIORITY, (unsigned int) FIELD_ACTOR_87_NO_ARG);
}
CLEAN_AS(func_ov068_02272044, FieldActor_PlayerRequestState88)

/* func_ov068_0227207c: the same for state 0x87. */
void *FieldActor_PlayerRequestState87(void)
{
    FieldActor *actor = SessionPlayers_FieldActor(FIELD_ACTOR_87_PLAYER);
    if (actor == NULL) {
        return NULL;
    }
    actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
    return FieldActor_RequestState87(actor, FIELD_ACTOR_87_PRIORITY, FIELD_ACTOR_87_NO_ARG);
}
CLEAN_AS(func_ov068_0227207c, FieldActor_PlayerRequestState87)
