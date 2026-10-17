/* The room object of /roomObj/obj_telephone (rmo_telephone.h). */
#include "rmo_telephone.h"

#include <stdint.h>

#include "clean.h"
#include "main/animated_model.h"
#include "main/group_params.h"
#include "main/message_receiver.h"
#include "main/scene_query.h"
#include "main/talk_flow.h"
#include "main/talk_object.h"

static_assert(sizeof(RmoObject) == 0x290, "RmoObject size");
static_assert(offsetof(RmoTelephone, receiver) == 0x290, "receiver");
static_assert(offsetof(RmoTelephone, receiver.base.message) == 0x2ae, "receiver message");
static_assert(offsetof(RmoTelephone, receiver.talk) == 0x2d0, "receiver talk");
static_assert(offsetof(RmoTelephone, box) == 0x2d8, "box");
static_assert(offsetof(RmoTelephone, pick_faces) == 0x374, "pick faces");
static_assert(offsetof(RmoTelephone, state) == 0x638, "state");
static_assert(offsetof(RmoTelephone, talking) == 0x63c, "talking");
static_assert(sizeof(RmoTelephone) == 0x644, "the size its class allocates");
static_assert(offsetof(RmoObject, body.frames.end) == 0x18c, "body frame count");
static_assert(offsetof(TalkObject, next_state) == 0x08, "talk next state");

#define RMO_TELEPHONE_ONE 0x1000 /* normal speed, 20.12 fixed point */
#define RMO_TELEPHONE_FRAME_SHIFT 12

/* The states these functions enter (rmo_telephone.h). */
#define RMO_TELEPHONE_STATE_4 4
#define RMO_TELEPHONE_STATE_7 7
#define RMO_TELEPHONE_STATE_10 10
#define RMO_TELEPHONE_STATE_11 11
#define RMO_TELEPHONE_STATE_12 12
#define RMO_TELEPHONE_STATE_14 14

/* The talk the field's objects use (TalkObject_Get). */
#define RMO_TELEPHONE_TALK 0

/* Its receiver's vtable slot 0x08: the reset (talk_receiver.h). */
#define RMO_TELEPHONE_RECEIVER_SLOT_RESET 0x08

/* State 14's messages in "sp_etc_sequence1", by func_0206fc6c (GroupParams_C4CIs1); the scene
 * after which it goes on to state 12 instead of 4; the group whose screen state 13 opens. */
#define RMO_TELEPHONE_MESSAGE_IF_SET 0x10
#define RMO_TELEPHONE_MESSAGE_ELSE 0x18
#define RMO_TELEPHONE_SCENE_12 6
#define RMO_TELEPHONE_SCREEN_GROUP 0x30

/* The one that exists, NULL for none. */
extern RmoTelephone *data_ov004_022588c8;

/* "sp_etc_sequence1", the message file. */
extern const char data_ov004_022558ac[];

/* Enters a state: its entry from the table data_ov004_022588d8, then RmoTelephone.state. */
extern void func_ov004_0223121c(RmoTelephone *self, int state);

extern const u8 *func_ov004_0222c3c4(RmoModel *model, int index); /* a joint animation */

static AnimatedModel *RmoTelephone_body(RmoTelephone *self)
{
    return (AnimatedModel *) (void *) &self->base.body;
}

/* The receiver part as C++ converts a pointer to the object to it: NULL stays NULL. */
static TalkReceiver *RmoTelephone_receiver(RmoTelephone *self)
{
    return self != NULL ? &self->receiver : NULL;
}

/* The body's first joint animation started played once with `flags` from whole frame `start`. */
static void RmoTelephone_play(RmoTelephone *self, int flags, u16 start)
{
    AnimatedModel_Start(RmoTelephone_body(self), func_ov004_0222c3c4(&self->base.body_model, 0), flags, RMO_TELEPHONE_ONE,
                        start, 0);
}

/* The body's frame count as whole frames: the frame its animation ends at. QUIRK: cut to 16
 * bits. */
static u16 RmoTelephone_last_frame(const RmoTelephone *self)
{
    return (u16) ((u32) self->base.body.frames.end >> RMO_TELEPHONE_FRAME_SHIFT);
}

/* func_ov004_02230c98: the one that exists plays its body's first joint animation once,
 * starting at its frame count's whole frames (its end); nothing when none exists. */
void RmoTelephone_PlayFromEnd(void)
{
    RmoTelephone *self = data_ov004_022588c8;
    if (self != NULL) {
        RmoTelephone_play(self, FRAME_CTRL_ONCE, RmoTelephone_last_frame(self));
    }
}
CLEAN_AS(func_ov004_02230c98, RmoTelephone_PlayFromEnd)

/* func_ov004_02230ce4: the one that exists plays its body's first joint animation once
 * backwards from its end (its frame count's whole frames); nothing when none exists. */
void RmoTelephone_PlayBackFromEnd(void)
{
    RmoTelephone *self = data_ov004_022588c8;
    if (self != NULL) {
        RmoTelephone_play(self, FRAME_CTRL_ONCE | FRAME_CTRL_REVERSE, RmoTelephone_last_frame(self));
    }
}
CLEAN_AS(func_ov004_02230ce4, RmoTelephone_PlayBackFromEnd)

/* func_ov004_02230d30: the one that exists plays its body's first joint animation once from its
 * start; nothing when none exists. */
void RmoTelephone_PlayFromStart(void)
{
    RmoTelephone *self = data_ov004_022588c8;
    if (self != NULL) {
        RmoTelephone_play(self, FRAME_CTRL_ONCE, 0);
    }
}
CLEAN_AS(func_ov004_02230d30, RmoTelephone_PlayFromStart)

/* func_ov004_02230d70: the one that exists enters state 10 (its talk); whether one exists. */
int RmoTelephone_EnterState10Current(void)
{
    RmoTelephone *self = data_ov004_022588c8;
    if (self != NULL) {
        func_ov004_0223121c(self, RMO_TELEPHONE_STATE_10);
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov004_02230d70, RmoTelephone_EnterState10Current)

/* func_ov004_02230d94: whether one exists and holds the talk. */
int RmoTelephone_IsTalking(void)
{
    RmoTelephone *self = data_ov004_022588c8;
    if (self != NULL && self->talking != 0) {
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov004_02230d94, RmoTelephone_IsTalking)

/* func_ov004_02230db8: its receiver reset (through its vtable), named `name` with message
 * `message` and attached to talk 0, which is asked to open. */
void RmoTelephone_StartTalk(RmoTelephone *self, const char *name, u8 message)
{
    TalkObject *talk = TalkObject_Get(RMO_TELEPHONE_TALK);
    const u32 *vtable = self->receiver.base.vtable;
    ((void (*)(TalkReceiver *))(uintptr_t) vtable[RMO_TELEPHONE_RECEIVER_SLOT_RESET / 4])(&self->receiver);
    MessageReceiver_SetName(&self->receiver.base, name);
    self->receiver.base.message = message;
    TalkObject_AttachReceiver(talk, RmoTelephone_receiver(self));
    talk->next_state = TALK_OBJECT_OPENING;
}
CLEAN_AS(func_ov004_02230db8, RmoTelephone_StartTalk)

/* func_ov004_02230e08 (update of state 14): once the group screen has closed (it could open
 * again), talk 0 shows message 0x10 of "sp_etc_sequence1" (0x18 when func_0206fc6c answers 0)
 * and is asked to open; then state 12 in scene 6, else state 4. */
void RmoTelephone_UpdateState14(RmoTelephone *self)
{
    if (GroupParams_CanOpen()) {
        TalkObject *talk = TalkObject_Get(RMO_TELEPHONE_TALK);
        u8 message = RMO_TELEPHONE_MESSAGE_IF_SET;
        if (!GroupParams_C4CIs1()) {
            message = RMO_TELEPHONE_MESSAGE_ELSE;
        }
        TalkObject_SetMessage(talk, &message, data_ov004_022558ac);
        talk->next_state = TALK_OBJECT_OPENING;
        if (SceneQuery_Current() == RMO_TELEPHONE_SCENE_12) {
            func_ov004_0223121c(self, RMO_TELEPHONE_STATE_12);
        } else {
            func_ov004_0223121c(self, RMO_TELEPHONE_STATE_4);
        }
    }
}
CLEAN_AS(func_ov004_02230e08, RmoTelephone_UpdateState14)

/* func_ov004_02230e68 (entry of state 14): nothing. */
void RmoTelephone_EnterState14(void) {}
CLEAN_AS(func_ov004_02230e68, RmoTelephone_EnterState14)

/* func_ov004_02230e6c (update of state 13): once talk 0 is gone, the screen of group 0x30
 * opened and state 14. */
void RmoTelephone_UpdateState13(RmoTelephone *self)
{
    if (TalkObject_Get(RMO_TELEPHONE_TALK)->state == TALK_OBJECT_GONE) {
        GroupParams_Open(RMO_TELEPHONE_SCREEN_GROUP);
        func_ov004_0223121c(self, RMO_TELEPHONE_STATE_14);
    }
}
CLEAN_AS(func_ov004_02230e6c, RmoTelephone_UpdateState13)

/* func_ov004_02230e90 (entry of state 13): nothing. */
void RmoTelephone_EnterState13(void) {}
CLEAN_AS(func_ov004_02230e90, RmoTelephone_EnterState13)

/* The talk's end: once talk 0 has closed, its receiver let go, the object no longer holds it,
 * and state 7. */
static void RmoTelephone_end_talk(RmoTelephone *self)
{
    TalkObject *talk = TalkObject_Get(RMO_TELEPHONE_TALK);
    if (talk->state == TALK_OBJECT_CLOSED) {
        TalkObject_DetachReceiver(talk);
        self->talking = 0;
        func_ov004_0223121c(self, RMO_TELEPHONE_STATE_7);
    }
}

/* func_ov004_02230e94 (update of state 12) */
void RmoTelephone_UpdateState12(RmoTelephone *self)
{
    RmoTelephone_end_talk(self);
}
CLEAN_AS(func_ov004_02230e94, RmoTelephone_UpdateState12)

/* func_ov004_02230ec0 (entry of state 12): nothing. */
void RmoTelephone_EnterState12(void) {}
CLEAN_AS(func_ov004_02230ec0, RmoTelephone_EnterState12)

/* func_ov004_02230ec4 (update of state 11) */
void RmoTelephone_UpdateState11(RmoTelephone *self)
{
    RmoTelephone_end_talk(self);
}
CLEAN_AS(func_ov004_02230ec4, RmoTelephone_UpdateState11)

/* func_ov004_02230ef0 (entry of state 11): nothing. */
void RmoTelephone_EnterState11(void) {}
CLEAN_AS(func_ov004_02230ef0, RmoTelephone_EnterState11)

/* func_ov004_02230ef4 (update of state 10): state 11 once its receiver's talk has opened. */
void RmoTelephone_UpdateState10(RmoTelephone *self)
{
    struct TalkFlowTalk *talk = self->receiver.talk;
    if (talk != NULL && talk->state != TALK_FLOW_CLOSED) {
        func_ov004_0223121c(self, RMO_TELEPHONE_STATE_11);
    }
}
CLEAN_AS(func_ov004_02230ef4, RmoTelephone_UpdateState10)
