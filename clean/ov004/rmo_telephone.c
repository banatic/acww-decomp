/* The room object of /roomObj/obj_telephone (rmo_telephone.h). */
#include "rmo_telephone.h"

#include <stdint.h>

#include "autoload_2/heap.h"
#include "autoload_2/vector.h"
#include "clean.h"
#include "main/animated_model.h"
#include "main/collision_box.h"
#include "main/control_mode_icon.h"
#include "main/event_queue.h"
#include "main/frame_ctrl.h"
#include "main/group_params.h"
#include "main/message_receiver.h"
#include "main/player_options.h"
#include "main/scene_object_base.h"
#include "main/scene_query.h"
#include "main/screen_transition.h"
#include "main/session.h"
#include "main/session_players.h"
#include "main/sound.h"
#include "main/state_block.h"
#include "main/talk_answers.h"
#include "main/talk_flow.h"
#include "main/talk_object.h"
#include "main/talk_voice.h"
#include "main/touch_pick_shapes.h"
#include "member_pointer.h"
#include "ov004/rmo_model.h"
#include "ov004/rmo_object_slots.h"
#include "ov004/room_player_actor.h"
#include "rmo_object_base.h"

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

/* State 14's messages in "sp_etc_sequence1", by GroupParams_C4CIs1 (GroupParams_C4CIs1); the scene
 * after which it goes on to state 12 instead of 4; the group whose screen state 13 opens. */
#define RMO_TELEPHONE_MESSAGE_IF_SET 0x10
#define RMO_TELEPHONE_MESSAGE_ELSE 0x18
#define RMO_TELEPHONE_SCENE_12 6
#define RMO_TELEPHONE_SCREEN_GROUP 0x30

/* The one that exists, NULL for none. */
extern RmoTelephone *data_ov004_022588c8;

/* "sp_etc_sequence1", the message file. */
extern const char data_ov004_022558ac[];

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
    AnimatedModel_Start(RmoTelephone_body(self), RmoModel_JointAnim(&self->base.body_model, 0), flags, RMO_TELEPHONE_ONE,
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
        RmoTelephone_EnterState(self, RMO_TELEPHONE_STATE_10);
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
 * again), talk 0 shows message 0x10 of "sp_etc_sequence1" (0x18 when GroupParams_C4CIs1 answers 0)
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
            RmoTelephone_EnterState(self, RMO_TELEPHONE_STATE_12);
        } else {
            RmoTelephone_EnterState(self, RMO_TELEPHONE_STATE_4);
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
        RmoTelephone_EnterState(self, RMO_TELEPHONE_STATE_14);
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
        RmoTelephone_EnterState(self, RMO_TELEPHONE_STATE_7);
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
        RmoTelephone_EnterState(self, RMO_TELEPHONE_STATE_11);
    }
}
CLEAN_AS(func_ov004_02230ef4, RmoTelephone_UpdateState10)

/* The rest of the class (rmo_telephone.h). */

static_assert(offsetof(RmoTelephone, unk_61c) == 0x61c, "touch sphere");
static_assert(offsetof(RmoTelephone, unk_640) == 0x640, "kept setting");
static_assert(offsetof(Actor, position) == 0x5c, "position");
static_assert(offsetof(Actor, angle) == 0x8c, "angle");
static_assert(offsetof(TalkObject, mode) == 0x14, "talk mode");
static_assert(offsetof(TalkObject, voice) == 0x1a2c, "talk voice");
static_assert(offsetof(TalkFlowTalk, next) == 0x08, "talk flow next");
static_assert(sizeof(RmoTelephoneAnswers) == 8, "answer list");

/* Its states' entries and updates (filled by __sinit_ov004_0224ebd8): member pointers whose
 * function is 0 for none. */
typedef struct RmoTelephoneState {
    MemberPointer entry;
    MemberPointer update;
} RmoTelephoneState;

#define RMO_TELEPHONE_STATE_0 0
#define RMO_TELEPHONE_STATE_1 1
#define RMO_TELEPHONE_STATE_2 2
#define RMO_TELEPHONE_STATE_3 3
#define RMO_TELEPHONE_STATE_5 5
#define RMO_TELEPHONE_STATE_6 6
#define RMO_TELEPHONE_STATE_8 8
#define RMO_TELEPHONE_STATE_9 9
#define RMO_TELEPHONE_STATE_13 13

/* Its touch-pick faces: a box 0x2000 on each side, of kind 13 and index 0xff. */
#define RMO_TELEPHONE_SIZE 0x2000
#define RMO_TELEPHONE_PICK_KIND 13
#define RMO_TELEPHONE_PICK_INDEX 0xff

/* The scene whose telephone answers the pen itself (states 7 to 14), and this system's player
 * (session_players.h), whose number in the session that scene also asks for. */
#define RMO_TELEPHONE_OWN_SCENE 6
#define RMO_TELEPHONE_OWN_PLAYER SESSION_PLAYERS_OWN

/* The state block's flags: 0, the telephone of scene 6 has rung; 0x13 and 0x14, two options
 * its talk sets. */
#define RMO_TELEPHONE_FLAG_RUNG 0
#define RMO_TELEPHONE_FLAG_13 0x13
#define RMO_TELEPHONE_FLAG_14 0x14

/* The sounds of states 1 and 5. */
#define RMO_TELEPHONE_SOUND_1 0x4d4
#define RMO_TELEPHONE_SOUND_5 0x4d5

/* The messages of "sp_etc_sequence1" these functions start or answer. */
#define RMO_TELEPHONE_MESSAGE_MENU 0x0e
#define RMO_TELEPHONE_MESSAGE_DONE 0x0f
#define RMO_TELEPHONE_MESSAGE_SETTING 0x11
#define RMO_TELEPHONE_MESSAGE_FLAG 0x14
#define RMO_TELEPHONE_MESSAGE_FLAG_13 0x17
#define RMO_TELEPHONE_MESSAGE_FLAG_14 0x1a
#define RMO_TELEPHONE_MESSAGE_SOUND 0x1b
#define RMO_TELEPHONE_MESSAGE_SOUND_ON 0x1c
#define RMO_TELEPHONE_MESSAGE_LINKED 0x1d
#define RMO_TELEPHONE_MESSAGE_SOUND_OFF 0x1e
#define RMO_TELEPHONE_MESSAGE_MENU_AGAIN 0x1f
#define RMO_TELEPHONE_MESSAGE_20 0x20
#define RMO_TELEPHONE_MESSAGE_RING 0x22
#define RMO_TELEPHONE_MESSAGE_KEEP_FIRST 0x2a
#define RMO_TELEPHONE_MESSAGE_KEEP_SECOND 0x2b
#define RMO_TELEPHONE_MESSAGE_KEEP_LAST 0x2c
/* Message 0x17 again, answered by one of these by flags 0x13 and 0x14 of the state block. */
#define RMO_TELEPHONE_MESSAGE_FLAGS_BOTH 0x42
#define RMO_TELEPHONE_MESSAGE_FLAGS_14 0x41
#define RMO_TELEPHONE_MESSAGE_FLAGS_13 0x40
#define RMO_TELEPHONE_MESSAGE_FLAGS_NONE 0x3f

/* The answers with sound kind 3 (TalkAnswers_Set), and the answers' message file. */
#define RMO_TELEPHONE_ANSWER_LOUD_FIRST 0x14
#define RMO_TELEPHONE_ANSWER_LOUD_LAST 0x15
#define RMO_TELEPHONE_ANSWER_LOUD_SOUND 3
#define RMO_TELEPHONE_ANSWER_FILE 1

/* What the scene's events (vtable slot 0x4c) are. */
#define RMO_TELEPHONE_EVENT_0 0
#define RMO_TELEPHONE_EVENT_1 1
#define RMO_TELEPHONE_EVENT_IDLE 8

/* Who may act on it (vtable slot 0x48): nearer than this to its point on the XZ plane, and
 * facing it within this much. */
#define RMO_TELEPHONE_REACH 0x2333
#define RMO_TELEPHONE_FACING 0x1000
#define RMO_TELEPHONE_HALF_TURN 0x8000

/* The vtable slot RmoTelephone_MayAct is called through. */
#define RMO_TELEPHONE_SLOT_MAY_ACT 0x48

/* TalkObject.mode set by message 0xf's end. */
#define RMO_TELEPHONE_TALK_MODE 1

extern RmoTelephoneState data_ov004_022588d8[];

/* Its point. */
extern const Vec3 data_ov004_022478d0;

/* The next message for each answer to message 0xe: in scene 6, and elsewhere. */
extern const u8 data_ov004_022478cc[];
extern const u8 data_ov004_022478c8[];
/* "sp_etc_sequence1" again (for TalkObject_SetMessage), and a pointer to the first copy. */
extern const char data_ov004_022478dc[];
extern const char *const data_ov004_022557b8;

/* The lists of answers to message 0xe (in scene 6: 4 answers, B picking the fourth; elsewhere:
 * 3, B picking the third) and to message 0x1b (2, B picking none). */
extern const RmoTelephoneAnswers data_ov004_022558d8, data_ov004_022558e0, data_ov004_022558e8;

/* The class's vtable and its receiver part's; its archive and texture file. */
extern const u8 data_ov004_022558f8[];
extern const u8 data_ov004_02255974[];
extern const char data_ov004_022559ec[];
extern const char data_ov004_02255a08[];

extern u8 data_021c75b8; /* the screen's transition (screen_transition.h) */
extern u8 data_021f6c38; /* the pen is down (touch_history.c) */
extern u8 data_021f6c34; /* the pen went down or up */
extern NetSession *data_020ccf94;
extern u32 data_021dc7a8[]; /* the state block (state_block.h) */
extern Heap *data_021c9b24;
extern u8 data_021f43f8;

/* The RMO family's base class (rmo_object.h). */

static void *RmoTelephone_sound_source(RmoTelephone *self)
{
    return &self->base.unk_24c[4];
}

static TouchPickSphere *RmoTelephone_touch_sphere(RmoTelephone *self)
{
    return (TouchPickSphere *) (void *) self->unk_61c;
}

static TalkObject *RmoTelephone_talk(RmoTelephone *self)
{
    return (TalkObject *) (void *) self->receiver.talk;
}

static TouchPick *RmoTelephone_field_pick(void)
{
    return (TouchPick *) (intptr_t) SceneQuery_FieldObject();
}

static int RmoTelephone_screen_shown(void)
{
    return data_021c75b8 == SCREEN_TRANSITION_SHOWN;
}

/* func_ov004_02230f18 (entry of state 10): the talk started with message 0xe, held.
 * QUIRK: answers 0x63c, the offset of RmoTelephone.talking. */
int RmoTelephone_EnterState10(RmoTelephone *self)
{
    RmoTelephone_StartTalk(self, data_ov004_022558ac, RMO_TELEPHONE_MESSAGE_MENU);
    self->talking = 1;
    return (int) offsetof(RmoTelephone, talking);
}
CLEAN_AS(func_ov004_02230f18, RmoTelephone_EnterState10)

/* func_ov004_02230f38 (update of state 9): once talk 0 has closed, its receiver let go, the
 * talk no longer held, and state 7. */
void RmoTelephone_UpdateState9(RmoTelephone *self)
{
    RmoTelephone_end_talk(self);
}
CLEAN_AS(func_ov004_02230f38, RmoTelephone_UpdateState9)

/* func_ov004_02230f64 (entry of state 9): the talk started with message 0x22. */
void RmoTelephone_EnterState9(RmoTelephone *self)
{
    RmoTelephone_StartTalk(self, data_ov004_022558ac, RMO_TELEPHONE_MESSAGE_RING);
}
CLEAN_AS(func_ov004_02230f64, RmoTelephone_EnterState9)

/* func_ov004_02230f74 (update of state 8): state 9 once the screen is shown. */
void RmoTelephone_UpdateState8(RmoTelephone *self)
{
    if (RmoTelephone_screen_shown()) {
        RmoTelephone_EnterState(self, RMO_TELEPHONE_STATE_9);
    }
}
CLEAN_AS(func_ov004_02230f74, RmoTelephone_UpdateState8)

/* func_ov004_02230f9c (entry of state 8): the talk held; answers the object. */
RmoTelephone *RmoTelephone_EnterState8(RmoTelephone *self)
{
    self->talking = 1;
    return self;
}
CLEAN_AS(func_ov004_02230f9c, RmoTelephone_EnterState8)

/* func_ov004_02230fa8 (update of state 7): while the screen is shown its pick faces are added
 * to the field object's picks; then, when the pen has just come down in the touch control mode
 * (in scene 6 only while this system's player number in the session is 4) and picks a face of
 * kind 13, state 10. */
void RmoTelephone_UpdateState7(RmoTelephone *self)
{
    Vec3 point;
    u32 kind;
    u8 index;

    if (!RmoTelephone_screen_shown()) {
        return;
    }
    TouchPick_AddFaces(RmoTelephone_field_pick(), self->pick_faces);
    if (SceneQuery_Current() == RMO_TELEPHONE_OWN_SCENE && data_020ccf94->local_player != RMO_TELEPHONE_OWN_PLAYER) {
        return;
    }
    if (!ControlModeIcon_IsTouch()) {
        return;
    }
    if (data_021f6c38 == 0 || data_021f6c34 == 0) {
        return;
    }
    if (TouchPick_GetPick(RmoTelephone_field_pick(), &point, &kind, &index) == 0) {
        return;
    }
    if (kind == RMO_TELEPHONE_PICK_KIND) {
        RmoTelephone_EnterState(self, RMO_TELEPHONE_STATE_10);
    }
}
CLEAN_AS(func_ov004_02230fa8, RmoTelephone_UpdateState7)

/* func_ov004_0223103c (entry of state 7): nothing. */
void RmoTelephone_EnterState7(void) {}
CLEAN_AS(func_ov004_0223103c, RmoTelephone_EnterState7)

/* func_ov004_02231040 (update of state 6): nothing. */
void RmoTelephone_UpdateState6(void) {}
CLEAN_AS(func_ov004_02231040, RmoTelephone_UpdateState6)

/* func_ov004_02231044 (entry of state 6): nothing. */
void RmoTelephone_EnterState6(void) {}
CLEAN_AS(func_ov004_02231044, RmoTelephone_EnterState6)

/* func_ov004_02231048 (update of state 5): once the body's animation has run out, its receiver
 * handed back, the event finished and state 6. */
void RmoTelephone_UpdateState5(RmoTelephone *self)
{
    if (FrameCtrl_IsDone(&self->base.body.frames)) {
        SceneObjectBase_ReleaseReceiver((SceneObjectBase *) (void *) self, RmoTelephone_receiver(self));
        EventQueue_FinishObjectEvent(self);
        RmoTelephone_EnterState(self, RMO_TELEPHONE_STATE_6);
    }
}
CLEAN_AS(func_ov004_02231048, RmoTelephone_UpdateState5)

/* func_ov004_02231084 (entry of state 5): the player's action 0x7f, then sound 0x4d5; the
 * sound's answer. */
int RmoTelephone_EnterState5(RmoTelephone *self)
{
    RoomPlayerActor_RequestHangUp();
    return RmoSound_Play(RmoTelephone_sound_source(self), RMO_TELEPHONE_SOUND_5);
}
CLEAN_AS(func_ov004_02231084, RmoTelephone_EnterState5)

/* State 5 once its receiver's talk has closed. */
static void RmoTelephone_after_talk(RmoTelephone *self)
{
    struct TalkFlowTalk *talk = self->receiver.talk;
    if (talk != NULL && talk->state == TALK_FLOW_CLOSED) {
        RmoTelephone_EnterState(self, RMO_TELEPHONE_STATE_5);
    }
}

/* func_ov004_022310a4 (update of state 4) */
void RmoTelephone_UpdateState4(RmoTelephone *self)
{
    RmoTelephone_after_talk(self);
}
CLEAN_AS(func_ov004_022310a4, RmoTelephone_UpdateState4)

/* func_ov004_022310c8 (entry of state 4): nothing. */
void RmoTelephone_EnterState4(void) {}
CLEAN_AS(func_ov004_022310c8, RmoTelephone_EnterState4)

/* func_ov004_022310cc (update of state 3) */
void RmoTelephone_UpdateState3(RmoTelephone *self)
{
    RmoTelephone_after_talk(self);
}
CLEAN_AS(func_ov004_022310cc, RmoTelephone_UpdateState3)

/* func_ov004_022310f0 (entry of state 3): nothing. */
void RmoTelephone_EnterState3(void) {}
CLEAN_AS(func_ov004_022310f0, RmoTelephone_EnterState3)

/* func_ov004_022310f4 (update of state 2): state 3 once its receiver's talk has opened. */
void RmoTelephone_UpdateState2(RmoTelephone *self)
{
    struct TalkFlowTalk *talk = self->receiver.talk;
    if (talk != NULL && talk->state != TALK_FLOW_CLOSED) {
        RmoTelephone_EnterState(self, RMO_TELEPHONE_STATE_3);
    }
}
CLEAN_AS(func_ov004_022310f4, RmoTelephone_UpdateState2)

/* func_ov004_02231118 (entry of state 2): takes its receiver, names it "sp_etc_sequence1" with
 * message 0x1d in a linked session, else 0xe, and asks its talk to open.
 * REQUIRES: the receiver has a talk once SceneObjectBase_TakeReceiver has taken it. */
void RmoTelephone_EnterState2(RmoTelephone *self)
{
    SceneObjectBase_TakeReceiver((SceneObjectBase *) (void *) self, RmoTelephone_receiver(self));
    MessageReceiver_SetName(&self->receiver.base, data_ov004_022557b8);
    if (Session_IsLinked(data_020ccf94)) {
        self->receiver.base.message = RMO_TELEPHONE_MESSAGE_LINKED;
    } else {
        self->receiver.base.message = RMO_TELEPHONE_MESSAGE_MENU;
    }
    self->receiver.talk->next = TALK_OBJECT_OPENING;
}
CLEAN_AS(func_ov004_02231118, RmoTelephone_EnterState2)

/* func_ov004_02231178 (update of state 1): state 2 once the body's animation has run out. */
void RmoTelephone_UpdateState1(RmoTelephone *self)
{
    if (FrameCtrl_IsDone(&self->base.body.frames)) {
        RmoTelephone_EnterState(self, RMO_TELEPHONE_STATE_2);
    }
}
CLEAN_AS(func_ov004_02231178, RmoTelephone_UpdateState1)

/* func_ov004_0223119c (entry of state 1): the player's action 0x7d, then sound 0x4d4; the
 * sound's answer. */
int RmoTelephone_EnterState1(RmoTelephone *self)
{
    RoomPlayerActor_RequestPickUp();
    return RmoSound_Play(RmoTelephone_sound_source(self), RMO_TELEPHONE_SOUND_1);
}
CLEAN_AS(func_ov004_0223119c, RmoTelephone_EnterState1)

/* Vtable slot 0x48 (RmoTelephone_MayAct for this class), called through the vtable. */
static int RmoTelephone_call_may_act(RmoTelephone *self, Actor *other)
{
    const u32 *vtable = self->base.actor.vtable;
    return ((int (*)(RmoTelephone *, Actor *))(uintptr_t) vtable[RMO_TELEPHONE_SLOT_MAY_ACT / 4])(self, other);
}

/* func_ov004_022311bc (update of state 0): when the pen has just come down on this system's
 * player's actor and that player may act on the telephone, an event of kind 6 about it asked
 * for; else its pick faces added to the field object's picks for this frame. */
void RmoTelephone_UpdateState0(RmoTelephone *self)
{
    int picked = TouchPick_ObjectOnPenDown(RmoTelephone_field_pick(), NULL, NULL);
    void *own = SessionPlayers_ActorOf(RMO_TELEPHONE_OWN_PLAYER);
    if (picked != 0 && own != NULL && picked == (int) (intptr_t) own &&
        RmoTelephone_call_may_act(self, (Actor *) (intptr_t) SessionPlayers_ActorHandle(RMO_TELEPHONE_OWN_PLAYER)) != 0) {
        EventQueue_RequestKind6(self, 0);
        return;
    }
    TouchPick_AddFaces(RmoTelephone_field_pick(), self->pick_faces);
}
CLEAN_AS(func_ov004_022311bc, RmoTelephone_UpdateState0)

/* func_ov004_02231218 (entry of state 0): nothing. */
void RmoTelephone_EnterState0(void) {}
CLEAN_AS(func_ov004_02231218, RmoTelephone_EnterState0)

/* func_ov004_0223121c: enters `state`: its entry run (when it has one, whatever it answers),
 * then RmoTelephone.state set.
 * REQUIRES: `state` is 0 to 14 (the table has 15 rows). */
void RmoTelephone_EnterState(RmoTelephone *self, int state)
{
    const RmoTelephoneState *row = &data_ov004_022588d8[state];
    if (row->entry.function != 0) {
        MemberPointer_CallVoid(&row->entry, self);
    }
    self->state = state;
}
CLEAN_AS(func_ov004_0223121c, RmoTelephone_EnterState)

/* Asks state block flag `flag`. */
static int RmoTelephone_flag(u32 flag)
{
    return StateBlock_TestFlag(data_021dc7a8, flag);
}

/* func_ov004_02231258 (receiver slot 0x18, the player's answer; primary slot 0x70): by the
 * message answered:
 * - 0xe and 0x1f: the next message from the answer's row of the scene's table; 0x17 becomes
 *   0x42, 0x41, 0x40 or 0x3f by flags 0x13 and 0x14 of the state block (both, 0x14 only, 0x13
 *   only, none);
 * - 0x14: the options' flag cleared (first answer) or set (second);
 * - 0x17 and 0x1a: state block flag 0x13 or 0x14 cleared (first) or set (second);
 * - 0x1b: the sound on and capture effect 0, then message 0x1c (first); the sound off and
 *   capture effect 1, then message 0x1e (second);
 * - 0x11: the setting in use kept, then set to the answer (0 to 2);
 * - 0x2a to 0x2c: the second answer puts the kept setting back.
 * Then, outside scene 6, the options stored in the player's record, and the next message shown
 * when there is one.
 * QUIRK: the flag tests of message 0x17 ask each flag again for each case.
 * REQUIRES: for messages 0xe and 0x1f the answer has a row in the table (0 to 3). */
void RmoTelephone_OnAnswer(RmoTelephone *self)
{
    TalkObject *talk = RmoTelephone_talk(self);
    unsigned int choice = TalkAnswers_Picked(TalkObject_Answers(talk));
    int next = 0;

    switch (self->receiver.base.message) {
        case RMO_TELEPHONE_MESSAGE_MENU:
        case RMO_TELEPHONE_MESSAGE_MENU_AGAIN:
            if (SceneQuery_Current() == RMO_TELEPHONE_OWN_SCENE) {
                next = data_ov004_022478cc[choice];
            } else {
                next = data_ov004_022478c8[choice];
            }
            if (next == RMO_TELEPHONE_MESSAGE_FLAG_13) {
                if (RmoTelephone_flag(RMO_TELEPHONE_FLAG_13) && RmoTelephone_flag(RMO_TELEPHONE_FLAG_14)) {
                    next = RMO_TELEPHONE_MESSAGE_FLAGS_BOTH;
                } else if (!RmoTelephone_flag(RMO_TELEPHONE_FLAG_13) && RmoTelephone_flag(RMO_TELEPHONE_FLAG_14)) {
                    next = RMO_TELEPHONE_MESSAGE_FLAGS_14;
                } else if (RmoTelephone_flag(RMO_TELEPHONE_FLAG_13) && !RmoTelephone_flag(RMO_TELEPHONE_FLAG_14)) {
                    next = RMO_TELEPHONE_MESSAGE_FLAGS_13;
                } else if (!RmoTelephone_flag(RMO_TELEPHONE_FLAG_13) && !RmoTelephone_flag(RMO_TELEPHONE_FLAG_14)) {
                    next = RMO_TELEPHONE_MESSAGE_FLAGS_NONE;
                }
            }
            break;
        case RMO_TELEPHONE_MESSAGE_FLAG:
            if (choice == 0) {
                PlayerOptions_ChangeFlag(0);
            } else if (choice == 1) {
                PlayerOptions_ChangeFlag(1);
            }
            break;
        case RMO_TELEPHONE_MESSAGE_FLAG_13:
            if (choice == 0) {
                StateBlock_ClearFlag(data_021dc7a8, RMO_TELEPHONE_FLAG_13);
            } else if (choice == 1) {
                StateBlock_SetFlag(data_021dc7a8, RMO_TELEPHONE_FLAG_13);
            }
            break;
        case RMO_TELEPHONE_MESSAGE_FLAG_14:
            if (choice == 0) {
                StateBlock_ClearFlag(data_021dc7a8, RMO_TELEPHONE_FLAG_14);
            } else if (choice == 1) {
                StateBlock_SetFlag(data_021dc7a8, RMO_TELEPHONE_FLAG_14);
            }
            break;
        case RMO_TELEPHONE_MESSAGE_SOUND:
            if (choice == 0) {
                PlayerOptions_ChangeSound(1);
                SoundSys_SetCaptureEffect(0);
                next = RMO_TELEPHONE_MESSAGE_SOUND_ON;
            } else if (choice == 1) {
                PlayerOptions_ChangeSound(0);
                SoundSys_SetCaptureEffect(1);
                next = RMO_TELEPHONE_MESSAGE_SOUND_OFF;
            }
            break;
        case RMO_TELEPHONE_MESSAGE_SETTING:
            self->unk_640 = PlayerOptions_CurrentSetting();
            if (choice <= 2) {
                PlayerOptions_ChangeSetting(choice);
            }
            break;
        case RMO_TELEPHONE_MESSAGE_KEEP_FIRST:
        case RMO_TELEPHONE_MESSAGE_KEEP_SECOND:
        case RMO_TELEPHONE_MESSAGE_KEEP_LAST:
            if (choice == 1) {
                PlayerOptions_ChangeSetting((unsigned int) self->unk_640);
            }
            break;
    }
    if (SceneQuery_Current() != RMO_TELEPHONE_OWN_SCENE) {
        PlayerOptions_Store();
    }
    if (next != 0) {
        u8 message = (u8) next;
        TalkObject_SetMessage(talk, &message, data_ov004_022478dc);
    }
}
CLEAN_AS(func_ov004_02231258, RmoTelephone_OnAnswer)

/* func_ov004_02231454: its talk offers the answers of `answers` (from message file 1, sound
 * kind 3 for answers 0x14 and 0x15), B picking `cancel` (-1: none), and opens its choices. */
void RmoTelephone_OfferAnswers(RmoTelephone *self, const RmoTelephoneAnswers *answers, int cancel)
{
    TalkObject *talk = RmoTelephone_talk(self);
    TalkAnswers *offered = TalkObject_Answers(talk);
    const u8 *messages = answers->messages;
    int count = answers->count;

    TalkAnswers_Reset(offered, count, cancel);
    for (int i = 0; i < count; i++) {
        u8 message = messages[i];
        int sound = 0;
        if (message >= RMO_TELEPHONE_ANSWER_LOUD_FIRST && message <= RMO_TELEPHONE_ANSWER_LOUD_LAST) {
            sound = RMO_TELEPHONE_ANSWER_LOUD_SOUND;
        }
        TalkAnswers_Set(offered, i, &message, RMO_TELEPHONE_ANSWER_FILE, &data_021f43f8, NULL, sound);
    }
    TalkAnswers_LoadTexts(offered);
    TalkObject_OpenChoices(talk, 1);
}
CLEAN_AS(func_ov004_02231454, RmoTelephone_OfferAnswers)

/* func_ov004_022314dc (receiver slot 0x14, after a message; primary slot 0x6c): by the message
 * shown: 0x1b and 0xe/0x1f offer their answers (0xe's by scene), 0xf sets the talk's mode to 1
 * and enters state 13, 0x20 ends the voice's forced mode, 0x2a to 0x2c its kind's override. */
void RmoTelephone_AfterMessage(RmoTelephone *self)
{
    TalkObject *talk = RmoTelephone_talk(self);
    switch (self->receiver.base.message) {
        case RMO_TELEPHONE_MESSAGE_SOUND:
            RmoTelephone_OfferAnswers(self, &data_ov004_022558e8, -1);
            break;
        case RMO_TELEPHONE_MESSAGE_MENU:
        case RMO_TELEPHONE_MESSAGE_MENU_AGAIN:
            if (SceneQuery_Current() == RMO_TELEPHONE_OWN_SCENE) {
                RmoTelephone_OfferAnswers(self, &data_ov004_022558d8, 3);
            } else {
                RmoTelephone_OfferAnswers(self, &data_ov004_022558e0, 2);
            }
            break;
        case RMO_TELEPHONE_MESSAGE_DONE:
            talk->mode = RMO_TELEPHONE_TALK_MODE;
            RmoTelephone_EnterState(self, RMO_TELEPHONE_STATE_13);
            break;
        case RMO_TELEPHONE_MESSAGE_20:
            TalkVoice_ClearForcedMode(&talk->voice);
            break;
        case RMO_TELEPHONE_MESSAGE_KEEP_FIRST:
        case RMO_TELEPHONE_MESSAGE_KEEP_SECOND:
        case RMO_TELEPHONE_MESSAGE_KEEP_LAST:
            TalkVoice_ClearKindOverride(&talk->voice);
            break;
    }
}
CLEAN_AS(func_ov004_022314dc, RmoTelephone_AfterMessage)

/* func_ov004_02231590 (receiver slot 0x10, a message begins; primary slot 0x68): message 0xe
 * forces the voice's mode 0, messages 0x2a to 0x2c override its kind with 0. */
void RmoTelephone_OnMessageBegun(RmoTelephone *self)
{
    TalkObject *talk = RmoTelephone_talk(self);
    switch (self->receiver.base.message) {
        case RMO_TELEPHONE_MESSAGE_MENU:
            TalkVoice_SetForcedMode(&talk->voice, 0);
            break;
        case RMO_TELEPHONE_MESSAGE_KEEP_FIRST:
        case RMO_TELEPHONE_MESSAGE_KEEP_SECOND:
        case RMO_TELEPHONE_MESSAGE_KEEP_LAST:
            TalkVoice_SetKindOverride(&talk->voice, 0);
            break;
    }
}
CLEAN_AS(func_ov004_02231590, RmoTelephone_OnMessageBegun)

/* func_ov004_022315e4 (vtable slot 0x50): its point. */
const Vec3 *RmoTelephone_Position(void)
{
    return &data_ov004_022478d0;
}
CLEAN_AS(func_ov004_022315e4, RmoTelephone_Position)

/* func_ov004_022315ec (vtable slot 0x4c): the scene's events; 0 and 1 enter state 1, 8 state
 * 0, others nothing. */
void RmoTelephone_OnSceneEvent(RmoTelephone *self, int event)
{
    switch (event) {
        case RMO_TELEPHONE_EVENT_0:
        case RMO_TELEPHONE_EVENT_1:
            RmoTelephone_EnterState(self, RMO_TELEPHONE_STATE_1);
            break;
        case RMO_TELEPHONE_EVENT_IDLE:
            RmoTelephone_EnterState(self, RMO_TELEPHONE_STATE_0);
            break;
    }
}
CLEAN_AS(func_ov004_022315ec, RmoTelephone_OnSceneEvent)

/* func_ov004_02231614 (vtable slot 0x48): whether `other` may act on it: there, nearer than
 * 0x2333 to its point on the XZ plane, and facing it (its Y angle within 0x1000 of the
 * telephone's turned round). */
int RmoTelephone_MayAct(RmoTelephone *self, Actor *other)
{
    if (other != NULL && Vec_DistanceXZ(&other->position, &data_ov004_022478d0) < RMO_TELEPHONE_REACH) {
        u16 off = (u16) (other->angle[1] - (self->base.actor.angle[1] + RMO_TELEPHONE_HALF_TURN));
        return off < RMO_TELEPHONE_FACING || off >= 0x10000 - RMO_TELEPHONE_FACING;
    }
    return 0;
}
CLEAN_AS(func_ov004_02231614, RmoTelephone_MayAct)

/* func_ov004_02231674 (vtable slot 0x0c): the archive released and no longer the one that
 * exists. */
int RmoTelephone_Release(RmoTelephone *self)
{
    RmoObjectSlots_ReleaseBody(&self->base);
    data_ov004_022588c8 = NULL;
    return 1;
}
CLEAN_AS(func_ov004_02231674, RmoTelephone_Release)

/* func_ov004_02231690 (vtable slot 0x24) */
int RmoTelephone_Draw(RmoTelephone *self)
{
    AnimatedModel_Draw(RmoTelephone_body(self), NULL);
    return 1;
}
CLEAN_AS(func_ov004_02231690, RmoTelephone_Draw)

/* func_ov004_022316a4 (vtable slot 0x18): the state's update (when it has one), then the body's
 * animation steps.
 * REQUIRES: the state is 0 to 14. */
int RmoTelephone_Update(RmoTelephone *self)
{
    const RmoTelephoneState *row = &data_ov004_022588d8[self->state];
    if (row->update.function != 0) {
        MemberPointer_CallVoid(&row->update, self);
    }
    AnimatedModel_StepFrames(RmoTelephone_body(self));
    return 1;
}
CLEAN_AS(func_ov004_022316a4, RmoTelephone_Update)

/* func_ov004_022316f4 (vtable slot 0x00): becomes the one that exists, stands at its point, has
 * scene object id 0, loads its archive and texture and, when it has a first joint animation
 * that the model can take, starts it once backwards from frame 0; its pick faces set round its
 * point and added to the field object's picks; then its first state (rmo_telephone.h). */
int RmoTelephone_Start(RmoTelephone *self)
{
    data_ov004_022588c8 = self;
    Vec3 position = data_ov004_022478d0;
    self->base.actor.position = position;
    SceneObjectBase_SetId((SceneObjectBase *) (void *) self, 0);
    RmoObjectSlots_Load(&self->base, data_ov004_022559ec, data_ov004_02255a08);
    if (RmoModel_JointAnim(&self->base.body_model, 0) != NULL &&
        AnimatedModel_LoadAnim(RmoTelephone_body(self), data_021c9b24) != 0) {
        RmoTelephone_play(self, FRAME_CTRL_ONCE | FRAME_CTRL_REVERSE, 0);
        AnimatedModel_Attach(RmoTelephone_body(self));
    }
    TouchPick_SetBoxAndAdd(RmoTelephone_field_pick(), self->pick_faces, &position, RMO_TELEPHONE_SIZE, RMO_TELEPHONE_SIZE,
                           RMO_TELEPHONE_SIZE, 0, RMO_TELEPHONE_PICK_KIND, RMO_TELEPHONE_PICK_INDEX);
    if (SceneQuery_Current() == RMO_TELEPHONE_OWN_SCENE) {
        if (!StateBlock_TestFlag(data_021dc7a8, RMO_TELEPHONE_FLAG_RUNG)) {
            RmoTelephone_EnterState(self, RMO_TELEPHONE_STATE_8);
            StateBlock_SetFlag(data_021dc7a8, RMO_TELEPHONE_FLAG_RUNG);
        } else {
            RmoTelephone_EnterState(self, RMO_TELEPHONE_STATE_7);
        }
    } else {
        RmoTelephone_EnterState(self, RMO_TELEPHONE_STATE_0);
    }
    return 1;
}
CLEAN_AS(func_ov004_022316f4, RmoTelephone_Start)

static void RmoTelephone_set_vtables(RmoTelephone *self)
{
    self->base.actor.vtable = data_ov004_022558f8;
    self->receiver.base.vtable = data_ov004_02255974;
}

/* Its parts taken down, the base class last. */
static void RmoTelephone_destruct_parts(RmoTelephone *self)
{
    RmoTelephone_set_vtables(self);
    TouchPickSphere_Destruct2(RmoTelephone_touch_sphere(self));
    TouchPickFaces_DestructBox(self->pick_faces);
    CollisionBox_Destruct(&self->box);
    TalkReceiver_Destruct(&self->receiver);
    RmoObjectSlots_Destruct(&self->base);
}

/* func_ov004_022317f4 (the deleting destructor, vtable slot 0x44) */
RmoTelephone *RmoTelephone_Delete(RmoTelephone *self)
{
    RmoTelephone_destruct_parts(self);
    Heap_FreeAux(self);
    return self;
}
CLEAN_AS(func_ov004_022317f4, RmoTelephone_Delete)

/* func_ov004_02231850 (the destructor, vtable slot 0x40) */
RmoTelephone *RmoTelephone_Destruct(RmoTelephone *self)
{
    RmoTelephone_destruct_parts(self);
    return self;
}
CLEAN_AS(func_ov004_02231850, RmoTelephone_Destruct)

/* func_ov004_022318a4 (the constructor). Its state is left as the allocation zeroed it. */
RmoTelephone *RmoTelephone_Construct(RmoTelephone *self)
{
    RmoObjectBase_Construct(&self->base);
    TalkReceiver_ConstructBase(&self->receiver);
    RmoTelephone_set_vtables(self);
    CollisionBox_Construct(&self->box);
    TouchPickFaces_ConstructBox(self->pick_faces);
    TouchPickSphere_Construct(RmoTelephone_touch_sphere(self));
    return self;
}
CLEAN_AS(func_ov004_022318a4, RmoTelephone_Construct)

/* func_ov004_022318f8: the one that exists (its address), 0 for none. */
u32 RmoTelephone_Current(void)
{
    return (u32) (uintptr_t) data_ov004_022588c8;
}
CLEAN_AS(func_ov004_022318f8, RmoTelephone_Current)

/* func_ov004_02231904: a new one from the room's heap; nothing when it has no room. */
void RmoTelephone_Create(void)
{
    RmoTelephone *self = Heap_AllocAuxZeroed(sizeof(RmoTelephone));
    if (self != NULL) {
        RmoTelephone_Construct(self);
    }
}
CLEAN_AS(func_ov004_02231904, RmoTelephone_Create)

/* The receiver part (at 0x290) enters the object's functions through its vtable with these:
 * each moves the pointer back to the object and goes on with the object's function. */
static RmoTelephone *RmoTelephone_from_receiver(void *receiver)
{
    return (RmoTelephone *) (void *) ((u8 *) receiver - offsetof(RmoTelephone, receiver));
}

/* func_ov004_02231920: the deleting destructor, entered from the receiver part. */
RmoTelephone *RmoTelephoneReceiver_Delete(void *receiver)
{
    return RmoTelephone_Delete(RmoTelephone_from_receiver(receiver));
}
CLEAN_AS(_ZThn656_N18Obj_ov004_022558f8D0Ev, RmoTelephoneReceiver_Delete)

/* func_ov004_0223193c: receiver slot 0x18 (RmoTelephone_OnAnswer). */
void RmoTelephoneReceiver_OnAnswer(void *receiver)
{
    RmoTelephone_OnAnswer(RmoTelephone_from_receiver(receiver));
}
CLEAN_AS(_ZThn656_N18Obj_ov004_022558f817vfunc_02066994_18Ev, RmoTelephoneReceiver_OnAnswer)

/* func_ov004_02231958: receiver slot 0x14 (RmoTelephone_AfterMessage). */
void RmoTelephoneReceiver_AfterMessage(void *receiver)
{
    RmoTelephone_AfterMessage(RmoTelephone_from_receiver(receiver));
}
CLEAN_AS(_ZThn656_N18Obj_ov004_022558f817vfunc_02066994_14Ev, RmoTelephoneReceiver_AfterMessage)

/* func_ov004_02231974: receiver slot 0x10 (RmoTelephone_OnMessageBegun). */
void RmoTelephoneReceiver_OnMessageBegun(void *receiver)
{
    RmoTelephone_OnMessageBegun(RmoTelephone_from_receiver(receiver));
}
CLEAN_AS(_ZThn656_N18Obj_ov004_022558f817vfunc_02066994_10Ev, RmoTelephoneReceiver_OnMessageBegun)

/* func_ov004_02231990: the destructor, entered from the receiver part. */
RmoTelephone *RmoTelephoneReceiver_Destruct(void *receiver)
{
    return RmoTelephone_Destruct(RmoTelephone_from_receiver(receiver));
}
CLEAN_AS(_ZThn656_N18Obj_ov004_022558f8D1Ev, RmoTelephoneReceiver_Destruct)
