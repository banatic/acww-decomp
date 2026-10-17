/* The room object of /roomObj/obj_r_box (trash_box.h). */
#include "trash_box.h"

#include <stdint.h>

#include "autoload_2/approach.h"
#include "autoload_2/heap.h"
#include "autoload_2/vector.h"
#include "clean.h"
#include "main/animated_model.h"
#include "main/event_queue.h"
#include "main/frame_ctrl.h"
#include "main/group_params.h"
#include "main/room_object_state.h"
#include "main/scene_object_base.h"
#include "main/scene_query.h"
#include "main/talk_flow.h"
#include "member_pointer.h"

static_assert(sizeof(RmoObject) == 0x290, "RmoObject size");
static_assert(offsetof(TrashBox, receiver) == 0x290, "receiver");
static_assert(offsetof(TalkReceiver, talk) == 0x40, "talk");
static_assert(offsetof(TrashBox, box) == 0x2d8, "box");
static_assert(offsetof(TrashBox, pick_faces) == 0x374, "pick faces");
static_assert(offsetof(TrashBox, state) == 0x61c, "state");
static_assert(sizeof(TrashBox) == 0x620, "the size TrashBox_Create allocates");
static_assert(offsetof(Actor, angle) == 0x8c, "angle");

#define TRASH_BOX_ONE 0x1000 /* normal speed, 20.12 fixed point */
#define TRASH_BOX_PLAY_ONCE FRAME_CTRL_ONCE

/* The joint animations: the lid opening (its first frame: closed) and closing (its first
 * frame: open). */
#define TRASH_BOX_ANIM_OPENING 0
#define TRASH_BOX_ANIM_CLOSING 1
#define TRASH_BOX_SOUND_OPENING 0x4d6
#define TRASH_BOX_SOUND_CLOSING 0x4d7

/* Its boxes: the collision box and the touch-pick faces. */
#define TRASH_BOX_WIDTH 0x2000
#define TRASH_BOX_DEPTH 0x4000
#define TRASH_BOX_HEIGHT 0x2000
#define TRASH_BOX_PICK_KIND 0xc
#define TRASH_BOX_PICK_INDEX 0xff

/* Its number among the room objects' shared values (RoomObject.state_number). */
#define TRASH_BOX_STATE_NUMBER 0

/* The scene's events (vtable slot 0x4c). */
#define TRASH_BOX_EVENT_TALK 0
#define TRASH_BOX_EVENT_IDLE 8

/* The pockets' screen's mode (GroupParams_Open). */
#define TRASH_BOX_POCKETS_MODE 0x20

/* Who may act on it (vtable slot 0x48): nearer than this on the XZ plane, facing it within
 * this angle. */
#define TRASH_BOX_REACH 0x299a
#define TRASH_BOX_FACING 0x1200
#define TRASH_BOX_HALF_TURN 0x8000

/* What the talk is asked for (TalkFlowTalk.next) when it starts. */
#define TRASH_BOX_TALK_OPEN 1

/* The vtable slot that enters a lid state (TrashBox_SetLid). */
#define TRASH_BOX_SLOT_SET_LID 0x60

/* The word of the field's sound and talk state (music_queue.h) that a talk's end reads, and
 * what the box's messages leave there. */
#define TRASH_BOX_TALK_END_WORD 0x248
#define TRASH_BOX_TALK_END_VALUE 0x1a

/* The one that exists, NULL for none. */
extern TrashBox *data_ov004_02258490;

/* The class's vtable and its receiver part's. */
extern const u8 data_ov004_022553d8[];
extern const u8 data_ov004_02255454[];

/* "obj_r_box", the archive's name; "sp_npc_trash", the message file's. */
extern const char data_ov004_022554cc[];
extern const char *const data_ov004_02255304;

extern Heap *data_021c9b24;
extern u8 *data_021c526c;
/* POWCNT1's swap bit (display_frame.c): 1 for the main engine on top. */
extern int data_021c8c9c;

/* The state tables (member_pointer.h): their guards, the tables and their constants. */
extern u32 data_ov004_02258494;
extern MemberPointer data_ov004_022584f4[TRASH_BOX_STATE_COUNT];
extern const MemberPointer data_ov004_02255360, data_ov004_022553a0, data_ov004_02255318, data_ov004_02255330,
    data_ov004_02255340, data_ov004_02255388;
extern u32 data_ov004_02258488;
extern MemberPointer data_ov004_02258524[TRASH_BOX_STATE_COUNT];
extern const MemberPointer data_ov004_02255390, data_ov004_02255398, data_ov004_02255308, data_ov004_02255310,
    data_ov004_02255320, data_ov004_02255328;
/* The lid's tables. */
extern u32 data_ov004_02258498;
extern MemberPointer data_ov004_022584d4[TRASH_BOX_LID_COUNT];
extern const MemberPointer data_ov004_02255350, data_ov004_02255338, data_ov004_02255348, data_ov004_02255358;
extern u32 data_ov004_022584a8;
extern MemberPointer data_ov004_022584b4[TRASH_BOX_LID_COUNT];
extern const MemberPointer data_ov004_02255380, data_ov004_02255378, data_ov004_02255370, data_ov004_02255368;

/* The RMO family's base class (rmo_object.h). */
extern int func_ov004_0222c5c8(RmoObject *object, const char *name); /* loads /roomObj/<name> */
extern void func_ov004_0222c598(RmoObject *object);
extern const u8 *func_ov004_0222c3c4(RmoModel *model, int index);
extern RmoObject *func_ov004_0222c87c(RmoObject *object);
extern RmoObject *func_ov004_0222c7a0(RmoObject *object);
/* The object's number among the shared values (byte 0xea), its value, and setting that. */
extern void func_ov004_0222c590(RmoObject *object, u8 number);
extern int func_ov004_0222c574(RmoObject *object);
extern int func_ov004_0222c558(RmoObject *object, u32 value);
/* Plays a sound at the object's sound source (at 0x250). */
extern int func_ov004_0222c2dc(void *source, int sound);

static AnimatedModel *TrashBox_body(TrashBox *self)
{
    return (AnimatedModel *) (void *) &self->base.body;
}

/* The lid's state byte, and the sound source after it. */
static u8 *TrashBox_lid(TrashBox *self)
{
    return &self->base.unk_24c[0];
}

static void *TrashBox_sound_source(TrashBox *self)
{
    return &self->base.unk_24c[4];
}

/* The receiver part as C++ converts a pointer to the box to it: NULL stays NULL. */
static TalkReceiver *TrashBox_receiver(TrashBox *self)
{
    return self != NULL ? &self->receiver : NULL;
}

/* Vtable slot 0x60 (TrashBox_SetLid for this class), called through the vtable. */
static int TrashBox_call_set_lid(TrashBox *self, u32 lid)
{
    const u32 *vtable = self->base.actor.vtable;
    return ((int (*)(TrashBox *, u32))(uintptr_t) vtable[TRASH_BOX_SLOT_SET_LID / 4])(self, lid);
}

/* func_ov004_0222f474: the collision box taken off the field. */
int TrashBox_RemoveBox(TrashBox *self)
{
    return CollisionBox_Remove(&self->box);
}
CLEAN_AS(func_ov004_0222f474, TrashBox_RemoveBox)

/* func_ov004_0222f484: the collision box put on the field at its position, then its pick faces
 * set to the same box and added to the field object's picks; the latter's result. */
int TrashBox_AddBox(TrashBox *self)
{
    Vec3 *position = &self->base.actor.position;
    CollisionBox_Add(&self->box, TRASH_BOX_WIDTH, TRASH_BOX_DEPTH, TRASH_BOX_HEIGHT, position, 0, NULL);
    TouchPick *pick = (TouchPick *) (intptr_t) SceneQuery_FieldObject();
    return TouchPick_SetBoxAndAdd(pick, self->pick_faces, position, TRASH_BOX_WIDTH, TRASH_BOX_DEPTH, TRASH_BOX_HEIGHT, 0,
                                  TRASH_BOX_PICK_KIND, TRASH_BOX_PICK_INDEX);
}
CLEAN_AS(func_ov004_0222f484, TrashBox_AddBox)

/* func_ov004_0222f4e0 (receiver slot 0x18, the player's answer; primary slot 0x70): nothing. */
void TrashBox_OnAnswer(TrashBox *self)
{
    (void) self;
}
CLEAN_AS(func_ov004_0222f4e0, TrashBox_OnAnswer)

/* func_ov004_0222f4e4 (receiver slot 0x14, after a message; primary slot 0x6c): leaves 0x1a in
 * the word at 0x248 of the field's sound and talk state (data_021c526c).
 * REQUIRES: that state exists (data_021c526c is not NULL). */
void TrashBox_AfterMessage(TrashBox *self)
{
    (void) self;
    *(s32 *) (void *) (data_021c526c + TRASH_BOX_TALK_END_WORD) = TRASH_BOX_TALK_END_VALUE;
}
CLEAN_AS(func_ov004_0222f4e4, TrashBox_AfterMessage)

/* func_ov004_0222f4f8 (receiver slot 0x10, the talk ignored; primary slot 0x68): nothing. */
void TrashBox_OnTalkIgnored(TrashBox *self)
{
    (void) self;
}
CLEAN_AS(func_ov004_0222f4f8, TrashBox_OnTalkIgnored)

/* func_ov004_0222f4fc (update of TRASH_BOX_CLOSE_LID): once the lid is closed, lets the scene
 * go on. The state stays until the scene sets another. */
void TrashBox_UpdateCloseLid(TrashBox *self)
{
    if (*TrashBox_lid(self) == TRASH_BOX_LID_CLOSED) {
        EventQueue_FinishObjectEvent(self);
    }
}
CLEAN_AS(func_ov004_0222f4fc, TrashBox_UpdateCloseLid)

/* func_ov004_0222f518 (entry of TRASH_BOX_CLOSE_LID): the lid closing, through the shared
 * values (which call vtable slot 0x60, TrashBox_SetLid); their answer. */
int TrashBox_EnterCloseLid(TrashBox *self)
{
    return RoomObjectState_Change((RoomObject *) (void *) self, TRASH_BOX_LID_CLOSING);
}
CLEAN_AS(func_ov004_0222f518, TrashBox_EnterCloseLid)

/* func_ov004_0222f524 (update of TRASH_BOX_POCKETS): on once the main engine is not on top
 * (data_021c8c9c is 0) and the pockets' screen could open again (it has closed). */
void TrashBox_UpdatePockets(TrashBox *self)
{
    if (data_021c8c9c == 0 && GroupParams_CanOpen()) {
        TrashBox_EnterState(self, TRASH_BOX_CLOSE_LID);
    }
}
CLEAN_AS(func_ov004_0222f524, TrashBox_UpdatePockets)

/* func_ov004_0222f54c (entry of TRASH_BOX_POCKETS): opens the pockets' screen in mode 0x20;
 * whether it opened. */
int TrashBox_EnterPockets(TrashBox *self)
{
    (void) self;
    return GroupParams_Open(TRASH_BOX_POCKETS_MODE) ? 1 : 0;
}
CLEAN_AS(func_ov004_0222f54c, TrashBox_EnterPockets)

/* func_ov004_0222f568 (update of TRASH_BOX_OPEN_LID): on once the lid is open. */
void TrashBox_UpdateOpenLid(TrashBox *self)
{
    if (*TrashBox_lid(self) == TRASH_BOX_LID_OPEN) {
        TrashBox_EnterState(self, TRASH_BOX_POCKETS);
    }
}
CLEAN_AS(func_ov004_0222f568, TrashBox_UpdateOpenLid)

/* func_ov004_0222f584 (entry of TRASH_BOX_OPEN_LID): the lid opening, through the shared values;
 * their answer. */
int TrashBox_EnterOpenLid(TrashBox *self)
{
    return RoomObjectState_Change((RoomObject *) (void *) self, TRASH_BOX_LID_OPENING);
}
CLEAN_AS(func_ov004_0222f584, TrashBox_EnterOpenLid)

/* func_ov004_0222f590 (update of TRASH_BOX_TALK_END): once the talk has closed, hands the
 * receiver back and opens the lid. */
void TrashBox_UpdateTalkEnd(TrashBox *self)
{
    struct TalkFlowTalk *talk = self->receiver.talk;
    if (talk != NULL && talk->state == TALK_FLOW_CLOSED) {
        SceneObjectBase_ReleaseReceiver((SceneObjectBase *) (void *) self, TrashBox_receiver(self));
        TrashBox_EnterState(self, TRASH_BOX_OPEN_LID);
    }
}
CLEAN_AS(func_ov004_0222f590, TrashBox_UpdateTalkEnd)

/* func_ov004_0222f5c8 (entry of TRASH_BOX_TALK_END) */
int TrashBox_EnterTalkEnd(TrashBox *self)
{
    (void) self;
    return 1;
}
CLEAN_AS(func_ov004_0222f5c8, TrashBox_EnterTalkEnd)

/* func_ov004_0222f5cc (update of TRASH_BOX_TALK): on once the talk has opened. */
void TrashBox_UpdateTalk(TrashBox *self)
{
    struct TalkFlowTalk *talk = self->receiver.talk;
    if (talk != NULL && talk->state != TALK_FLOW_CLOSED) {
        TrashBox_EnterState(self, TRASH_BOX_TALK_END);
    }
}
CLEAN_AS(func_ov004_0222f5cc, TrashBox_UpdateTalk)

/* func_ov004_0222f5f0 (entry of TRASH_BOX_TALK): takes the receiver, names it "sp_npc_trash"
 * with message 0 and asks its talk to open.
 * REQUIRES: the receiver has a talk once SceneObjectBase_TakeReceiver has taken it. */
int TrashBox_EnterTalk(TrashBox *self)
{
    SceneObjectBase_TakeReceiver((SceneObjectBase *) (void *) self, TrashBox_receiver(self));
    MessageReceiver_SetName(&self->receiver.base, data_ov004_02255304);
    self->receiver.base.message = 0;
    self->receiver.talk->next = TRASH_BOX_TALK_OPEN;
    return 1;
}
CLEAN_AS(func_ov004_0222f5f0, TrashBox_EnterTalk)

/* func_ov004_0222f638 (update of TRASH_BOX_IDLE): nothing. */
void TrashBox_UpdateIdle(TrashBox *self)
{
    (void) self;
}
CLEAN_AS(func_ov004_0222f638, TrashBox_UpdateIdle)

/* func_ov004_0222f63c (entry of TRASH_BOX_IDLE) */
int TrashBox_EnterIdle(TrashBox *self)
{
    (void) self;
    return 1;
}
CLEAN_AS(func_ov004_0222f63c, TrashBox_EnterIdle)

/* _ZN18Obj_ov004_022553d819func_ov004_0222f640Ev: the state's update, through its table.
 * REQUIRES: the state is not negative (TrashBox_EnterState only sets 0 to 5). */
void TrashBox_UpdateState(TrashBox *self)
{
    static const MemberPointer *const updates[TRASH_BOX_STATE_COUNT] = {
        &data_ov004_02255360, /* TrashBox_UpdateIdle */
        &data_ov004_022553a0, /* TrashBox_UpdateTalk */
        &data_ov004_02255318, /* TrashBox_UpdateTalkEnd */
        &data_ov004_02255330, /* TrashBox_UpdateOpenLid */
        &data_ov004_02255340, /* TrashBox_UpdatePockets */
        &data_ov004_02255388, /* TrashBox_UpdateCloseLid */
    };
    MemberTable_InitOnce(&data_ov004_02258494, data_ov004_022584f4, updates, TRASH_BOX_STATE_COUNT);
    if (self->state < TRASH_BOX_STATE_COUNT) {
        MemberPointer_CallVoid(&data_ov004_022584f4[self->state], self);
    }
}
CLEAN_AS(_ZN18Obj_ov004_022553d819func_ov004_0222f640Ev, TrashBox_UpdateState)

/* func_ov004_0222f6e8: enters `state` if its entry (through a table) agrees; whether it did.
 * States 6 and above do not exist.
 * REQUIRES: `state` is not negative. */
int TrashBox_EnterState(TrashBox *self, int state)
{
    static const MemberPointer *const entries[TRASH_BOX_STATE_COUNT] = {
        &data_ov004_02255390, /* TrashBox_EnterIdle */
        &data_ov004_02255398, /* TrashBox_EnterTalk */
        &data_ov004_02255308, /* TrashBox_EnterTalkEnd */
        &data_ov004_02255310, /* TrashBox_EnterOpenLid */
        &data_ov004_02255320, /* TrashBox_EnterPockets */
        &data_ov004_02255328, /* TrashBox_EnterCloseLid */
    };
    MemberTable_InitOnce(&data_ov004_02258488, data_ov004_02258524, entries, TRASH_BOX_STATE_COUNT);
    if (state < TRASH_BOX_STATE_COUNT && MemberPointer_CallInt(&data_ov004_02258524[state], self) != 0) {
        self->state = state;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov004_0222f6e8, TrashBox_EnterState)

/* func_ov004_0222f7a0 (update of TRASH_BOX_LID_CLOSING): closed once the closing has run out,
 * else the animation steps. */
void TrashBox_UpdateClosing(TrashBox *self)
{
    if (FrameCtrl_IsDone(&self->base.body.frames)) {
        TrashBox_call_set_lid(self, TRASH_BOX_LID_CLOSED);
    } else {
        AnimatedModel_StepFrames(TrashBox_body(self));
    }
}
CLEAN_AS(func_ov004_0222f7a0, TrashBox_UpdateClosing)

/* func_ov004_0222f7d0 (entry of TRASH_BOX_LID_CLOSING): the closing played once, with its
 * sound. */
int TrashBox_EnterClosing(TrashBox *self)
{
    AnimatedModel_Start(TrashBox_body(self), func_ov004_0222c3c4(&self->base.body_model, TRASH_BOX_ANIM_CLOSING),
                        TRASH_BOX_PLAY_ONCE, TRASH_BOX_ONE, 0, 0);
    func_ov004_0222c2dc(TrashBox_sound_source(self), TRASH_BOX_SOUND_CLOSING);
    return 1;
}
CLEAN_AS(func_ov004_0222f7d0, TrashBox_EnterClosing)

/* func_ov004_0222f818 (update of TRASH_BOX_LID_OPEN): nothing. */
void TrashBox_UpdateOpen(TrashBox *self)
{
    (void) self;
}
CLEAN_AS(func_ov004_0222f818, TrashBox_UpdateOpen)

/* func_ov004_0222f81c (entry of TRASH_BOX_LID_OPEN): the closing started from its first frame
 * (the lid open), without sound; nothing steps it in this state. */
int TrashBox_EnterOpen(TrashBox *self)
{
    AnimatedModel_Start(TrashBox_body(self), func_ov004_0222c3c4(&self->base.body_model, TRASH_BOX_ANIM_CLOSING),
                        TRASH_BOX_PLAY_ONCE, TRASH_BOX_ONE, 0, 0);
    return 1;
}
CLEAN_AS(func_ov004_0222f81c, TrashBox_EnterOpen)

/* func_ov004_0222f854 (update of TRASH_BOX_LID_OPENING): open once the opening has run out,
 * else the animation steps. */
void TrashBox_UpdateOpening(TrashBox *self)
{
    if (FrameCtrl_IsDone(&self->base.body.frames)) {
        TrashBox_call_set_lid(self, TRASH_BOX_LID_OPEN);
    } else {
        AnimatedModel_StepFrames(TrashBox_body(self));
    }
}
CLEAN_AS(func_ov004_0222f854, TrashBox_UpdateOpening)

/* func_ov004_0222f884 (entry of TRASH_BOX_LID_OPENING): the opening played once, with its
 * sound. */
int TrashBox_EnterOpening(TrashBox *self)
{
    AnimatedModel_Start(TrashBox_body(self), func_ov004_0222c3c4(&self->base.body_model, TRASH_BOX_ANIM_OPENING),
                        TRASH_BOX_PLAY_ONCE, TRASH_BOX_ONE, 0, 0);
    func_ov004_0222c2dc(TrashBox_sound_source(self), TRASH_BOX_SOUND_OPENING);
    return 1;
}
CLEAN_AS(func_ov004_0222f884, TrashBox_EnterOpening)

/* func_ov004_0222f8cc (update of TRASH_BOX_LID_CLOSED): nothing. */
void TrashBox_UpdateClosed(TrashBox *self)
{
    (void) self;
}
CLEAN_AS(func_ov004_0222f8cc, TrashBox_UpdateClosed)

/* func_ov004_0222f8d0 (entry of TRASH_BOX_LID_CLOSED): the opening started from its first
 * frame (the lid closed), without sound. */
int TrashBox_EnterClosed(TrashBox *self)
{
    AnimatedModel_Start(TrashBox_body(self), func_ov004_0222c3c4(&self->base.body_model, TRASH_BOX_ANIM_OPENING),
                        TRASH_BOX_PLAY_ONCE, TRASH_BOX_ONE, 0, 0);
    return 1;
}
CLEAN_AS(func_ov004_0222f8d0, TrashBox_EnterClosed)

/* _ZN18Obj_ov004_022553d819func_ov004_0222f908Ev: the lid's update, through its table; a lid
 * byte of 4 or more runs none. */
void TrashBox_UpdateLid(TrashBox *self)
{
    static const MemberPointer *const updates[TRASH_BOX_LID_COUNT] = {
        &data_ov004_02255350, /* TrashBox_UpdateClosed */
        &data_ov004_02255338, /* TrashBox_UpdateOpening */
        &data_ov004_02255348, /* TrashBox_UpdateOpen */
        &data_ov004_02255358, /* TrashBox_UpdateClosing */
    };
    MemberTable_InitOnce(&data_ov004_02258498, data_ov004_022584d4, updates, TRASH_BOX_LID_COUNT);
    u8 lid = *TrashBox_lid(self);
    if (lid < TRASH_BOX_LID_COUNT) {
        MemberPointer_CallVoid(&data_ov004_022584d4[lid], self);
    }
}
CLEAN_AS(_ZN18Obj_ov004_022553d819func_ov004_0222f908Ev, TrashBox_UpdateLid)

/* func_ov004_0222f994 (vtable slot 0x60): enters lid state `lid` when its entry (through a
 * table) agrees and the shared value takes it (func_ov004_0222c558); whether it did. */
int TrashBox_SetLid(TrashBox *self, u32 lid)
{
    static const MemberPointer *const entries[TRASH_BOX_LID_COUNT] = {
        &data_ov004_02255380, /* TrashBox_EnterClosed */
        &data_ov004_02255378, /* TrashBox_EnterOpening */
        &data_ov004_02255370, /* TrashBox_EnterOpen */
        &data_ov004_02255368, /* TrashBox_EnterClosing */
    };
    MemberTable_InitOnce(&data_ov004_022584a8, data_ov004_022584b4, entries, TRASH_BOX_LID_COUNT);
    if (lid < TRASH_BOX_LID_COUNT && MemberPointer_CallInt(&data_ov004_022584b4[lid], self) != 0 &&
        func_ov004_0222c558(&self->base, lid) != 0) {
        *TrashBox_lid(self) = (u8) lid;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov004_0222f994, TrashBox_SetLid)

/* func_ov004_0222fa3c (vtable slot 0x4c): the scene's events; event 0 starts the talk, event 8
 * makes it idle, others do nothing. */
void TrashBox_OnSceneEvent(TrashBox *self, int event)
{
    switch (event) {
        case TRASH_BOX_EVENT_TALK:
            TrashBox_EnterState(self, TRASH_BOX_TALK);
            break;
        case TRASH_BOX_EVENT_IDLE:
            TrashBox_EnterState(self, TRASH_BOX_IDLE);
            break;
    }
}
CLEAN_AS(func_ov004_0222fa3c, TrashBox_OnSceneEvent)

/* func_ov004_0222fa60 (vtable slot 0x48): whether `other` may act on it: there, nearer than
 * 0x299a on the XZ plane, and facing it (its Y angle within 0x1200 of the box's turned
 * round). */
int TrashBox_MayAct(TrashBox *self, Actor *other)
{
    if (other != NULL && Vec_DistanceXZ(&other->position, &self->base.actor.position) < TRASH_BOX_REACH) {
        s16 facing_box = (s16) (u16) (self->base.actor.angle[1] + TRASH_BOX_HALF_TURN);
        if (Math_AbsDiff16(facing_box, other->angle[1]) < TRASH_BOX_FACING) {
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_ov004_0222fa60, TrashBox_MayAct)

/* func_ov004_0222fab0 (vtable slot 0x0c): off the field, the archive released and no longer the
 * one that exists. */
int TrashBox_Release(TrashBox *self)
{
    TrashBox_RemoveBox(self);
    func_ov004_0222c598(&self->base);
    data_ov004_02258490 = NULL;
    return 1;
}
CLEAN_AS(func_ov004_0222fab0, TrashBox_Release)

/* func_ov004_0222fad0 (vtable slot 0x24) */
int TrashBox_Draw(TrashBox *self)
{
    AnimatedModel_Draw(TrashBox_body(self), NULL);
    return 1;
}
CLEAN_AS(func_ov004_0222fad0, TrashBox_Draw)

/* _ZN18Obj_ov004_022553d819func_ov004_0222fae4Ev (vtable slot 0x18): the lid's update, the
 * state's, then its pick faces added to the field object's picks for this frame. */
int TrashBox_Update(TrashBox *self)
{
    TrashBox_UpdateLid(self);
    TrashBox_UpdateState(self);
    TouchPick_AddFaces((TouchPick *) (intptr_t) SceneQuery_FieldObject(), self->pick_faces);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov004_022553d819func_ov004_0222fae4Ev, TrashBox_Update)

/* func_ov004_0222fb0c (vtable slot 0x00): becomes the one that exists, takes shared value 0,
 * loads its archive, goes on the field and, when it has a first joint animation that the model
 * can take, starts it once (the lid closed); then idle, with the lid in the state the shared
 * value holds. */
int TrashBox_Start(TrashBox *self)
{
    data_ov004_02258490 = self;
    func_ov004_0222c590(&self->base, TRASH_BOX_STATE_NUMBER);
    func_ov004_0222c5c8(&self->base, data_ov004_022554cc);
    TrashBox_AddBox(self);
    if (func_ov004_0222c3c4(&self->base.body_model, TRASH_BOX_ANIM_OPENING) != NULL &&
        AnimatedModel_LoadAnim(TrashBox_body(self), data_021c9b24) != 0) {
        AnimatedModel_Start(TrashBox_body(self), func_ov004_0222c3c4(&self->base.body_model, TRASH_BOX_ANIM_OPENING),
                            TRASH_BOX_PLAY_ONCE, TRASH_BOX_ONE, 0, 0);
        AnimatedModel_Attach(TrashBox_body(self));
    }
    TrashBox_EnterState(self, TRASH_BOX_IDLE);
    TrashBox_call_set_lid(self, (u32) func_ov004_0222c574(&self->base));
    return 1;
}
CLEAN_AS(func_ov004_0222fb0c, TrashBox_Start)

static void TrashBox_set_vtables(TrashBox *self)
{
    self->base.actor.vtable = data_ov004_022553d8;
    self->receiver.base.vtable = data_ov004_02255454;
}

/* func_ov004_0222fba4 (the deleting destructor, vtable slot 0x44) */
TrashBox *TrashBox_Delete(TrashBox *self)
{
    TrashBox_set_vtables(self);
    TouchPickFaces_DestructBox(self->pick_faces);
    CollisionBox_Destruct(&self->box);
    TalkReceiver_Destruct(&self->receiver);
    func_ov004_0222c7a0(&self->base);
    Heap_FreeAux(self);
    return self;
}
CLEAN_AS(func_ov004_0222fba4, TrashBox_Delete)

/* func_ov004_0222fbf4 (the destructor, vtable slot 0x40) */
TrashBox *TrashBox_Destruct(TrashBox *self)
{
    TrashBox_set_vtables(self);
    TouchPickFaces_DestructBox(self->pick_faces);
    CollisionBox_Destruct(&self->box);
    TalkReceiver_Destruct(&self->receiver);
    func_ov004_0222c7a0(&self->base);
    return self;
}
CLEAN_AS(func_ov004_0222fbf4, TrashBox_Destruct)

/* func_ov004_0222fc3c (the constructor). Its states are left as the allocation zeroed them. */
TrashBox *TrashBox_Construct(TrashBox *self)
{
    func_ov004_0222c87c(&self->base);
    TalkReceiver_ConstructBase(&self->receiver);
    TrashBox_set_vtables(self);
    CollisionBox_Construct(&self->box);
    TouchPickFaces_ConstructBox(self->pick_faces);
    return self;
}
CLEAN_AS(func_ov004_0222fc3c, TrashBox_Construct)

/* func_ov004_0222fc84: the one that exists (its address), 0 for none. */
u32 TrashBox_Current(void)
{
    return (u32) (uintptr_t) data_ov004_02258490;
}
CLEAN_AS(func_ov004_0222fc84, TrashBox_Current)

/* func_ov004_0222fc90: a new one from the room's heap; nothing when it has no room. */
void TrashBox_Create(void)
{
    TrashBox *self = Heap_AllocAuxZeroed(sizeof(TrashBox));
    if (self != NULL) {
        TrashBox_Construct(self);
    }
}
CLEAN_AS(func_ov004_0222fc90, TrashBox_Create)

/* The receiver part (at 0x290) enters TrashBox's functions through its vtable with these: each
 * moves the pointer back to the object and goes on with the object's function. */
static TrashBox *TrashBox_from_receiver(void *receiver)
{
    return (TrashBox *) (void *) ((u8 *) receiver - offsetof(TrashBox, receiver));
}

/* func_ov004_0222fcac: the deleting destructor, entered from the receiver part. */
TrashBox *TrashBoxReceiver_Delete(void *receiver)
{
    return TrashBox_Delete(TrashBox_from_receiver(receiver));
}
CLEAN_AS(_ZThn656_N18Obj_ov004_022553d8D0Ev, TrashBoxReceiver_Delete)

/* func_ov004_0222fcc8: receiver slot 0x18 (TrashBox_OnAnswer). */
void TrashBoxReceiver_OnAnswer(void *receiver)
{
    TrashBox_OnAnswer(TrashBox_from_receiver(receiver));
}
CLEAN_AS(_ZThn656_N18Obj_ov004_022553d817vfunc_02066994_18Ev, TrashBoxReceiver_OnAnswer)

/* func_ov004_0222fce4: receiver slot 0x14 (TrashBox_AfterMessage). */
void TrashBoxReceiver_AfterMessage(void *receiver)
{
    TrashBox_AfterMessage(TrashBox_from_receiver(receiver));
}
CLEAN_AS(_ZThn656_N18Obj_ov004_022553d817vfunc_02066994_14Ev, TrashBoxReceiver_AfterMessage)

/* func_ov004_0222fd00: receiver slot 0x10 (TrashBox_OnTalkIgnored). */
void TrashBoxReceiver_OnTalkIgnored(void *receiver)
{
    TrashBox_OnTalkIgnored(TrashBox_from_receiver(receiver));
}
CLEAN_AS(_ZThn656_N18Obj_ov004_022553d817vfunc_02066994_10Ev, TrashBoxReceiver_OnTalkIgnored)

/* func_ov004_0222fd1c: the destructor, entered from the receiver part. */
TrashBox *TrashBoxReceiver_Destruct(void *receiver)
{
    return TrashBox_Destruct(TrashBox_from_receiver(receiver));
}
CLEAN_AS(_ZThn656_N18Obj_ov004_022553d8D1Ev, TrashBoxReceiver_Destruct)
