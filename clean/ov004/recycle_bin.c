/* The town hall's recycle bin, /roomObj/obj_r_box (recycle_bin.h). */
#include "recycle_bin.h"

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
#include "ov004/rmo_model.h"
#include "ov004/rmo_object_slots.h"
#include "rmo_object_base.h"

static_assert(sizeof(RmoObject) == 0x290, "RmoObject size");
static_assert(offsetof(RecycleBin, receiver) == 0x290, "receiver");
static_assert(offsetof(TalkReceiver, talk) == 0x40, "talk");
static_assert(offsetof(RecycleBin, box) == 0x2d8, "box");
static_assert(offsetof(RecycleBin, pick_faces) == 0x374, "pick faces");
static_assert(offsetof(RecycleBin, state) == 0x61c, "state");
static_assert(sizeof(RecycleBin) == 0x620, "the size RecycleBin_Create allocates");
static_assert(offsetof(Actor, angle) == 0x8c, "angle");

#define RECYCLE_BIN_PLAY_ONCE FRAME_CTRL_ONCE

/* The joint animations: the lid opening (its first frame: closed) and closing (its first
 * frame: open). */
#define RECYCLE_BIN_ANIM_OPENING 0
#define RECYCLE_BIN_ANIM_CLOSING 1
#define RECYCLE_BIN_SOUND_OPENING 0x4d6
#define RECYCLE_BIN_SOUND_CLOSING 0x4d7

/* Its boxes: the collision box and the touch-pick faces. */
#define RECYCLE_BIN_WIDTH 0x2000
#define RECYCLE_BIN_DEPTH 0x4000
#define RECYCLE_BIN_HEIGHT 0x2000
#define RECYCLE_BIN_PICK_KIND 0xc
#define RECYCLE_BIN_PICK_INDEX 0xff

/* Its number among the room objects' shared values (RoomObject.state_number). */
#define RECYCLE_BIN_STATE_NUMBER 0

/* The scene's events (vtable slot 0x4c). */
#define RECYCLE_BIN_EVENT_TALK 0
#define RECYCLE_BIN_EVENT_IDLE 8

/* The recycle bin's screen's mode (GroupParams_Open; overlay 110's PUBLIC_BOX_MODE_RECYCLE). */
#define RECYCLE_BIN_SCREEN_MODE 0x20

/* Who may act on it (vtable slot 0x48): nearer than this on the XZ plane, facing it within
 * this angle. */
#define RECYCLE_BIN_REACH 0x299a
#define RECYCLE_BIN_FACING 0x1200
#define RECYCLE_BIN_HALF_TURN 0x8000

/* What the talk is asked for (TalkObject.next_state) when it starts. */
#define RECYCLE_BIN_TALK_OPEN 1

/* The vtable slot that enters a lid state (RecycleBin_SetLid). */
#define RECYCLE_BIN_SLOT_SET_LID 0x60

/* The word of the field's sound and talk state (music_queue.h) that a talk's end reads, and
 * what the box's messages leave there. */
#define RECYCLE_BIN_TALK_END_WORD 0x248
#define RECYCLE_BIN_TALK_END_VALUE 0x1a

/* The one that exists, NULL for none. */
extern RecycleBin *data_ov004_02258490;

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
extern MemberPointer data_ov004_022584f4[RECYCLE_BIN_STATE_COUNT];
extern const MemberPointer data_ov004_02255360, data_ov004_022553a0, data_ov004_02255318, data_ov004_02255330,
    data_ov004_02255340, data_ov004_02255388;
extern u32 data_ov004_02258488;
extern MemberPointer data_ov004_02258524[RECYCLE_BIN_STATE_COUNT];
extern const MemberPointer data_ov004_02255390, data_ov004_02255398, data_ov004_02255308, data_ov004_02255310,
    data_ov004_02255320, data_ov004_02255328;
/* The lid's tables. */
extern u32 data_ov004_02258498;
extern MemberPointer data_ov004_022584d4[RECYCLE_BIN_LID_COUNT];
extern const MemberPointer data_ov004_02255350, data_ov004_02255338, data_ov004_02255348, data_ov004_02255358;
extern u32 data_ov004_022584a8;
extern MemberPointer data_ov004_022584b4[RECYCLE_BIN_LID_COUNT];
extern const MemberPointer data_ov004_02255380, data_ov004_02255378, data_ov004_02255370, data_ov004_02255368;

/* The RMO family's base class (rmo_object.h). */

static AnimatedModel *recycle_bin_body(RecycleBin *self)
{
    return (AnimatedModel *) (void *) &self->base.body;
}

/* The lid's state byte, and the sound source after it. */
static u8 *recycle_bin_lid(RecycleBin *self)
{
    return &self->base.unk_24c[0];
}

static void *recycle_bin_sound_source(RecycleBin *self)
{
    return &self->base.unk_24c[4];
}

/* The receiver part as C++ converts a pointer to the box to it: NULL stays NULL. */
static TalkReceiver *recycle_bin_receiver(RecycleBin *self)
{
    return self != NULL ? &self->receiver : NULL;
}

/* Vtable slot 0x60 (RecycleBin_SetLid for this class), called through the vtable. */
static int recycle_bin_call_set_lid(RecycleBin *self, u32 lid)
{
    const u32 *vtable = self->base.actor.vtable;
    return ((int (*)(RecycleBin *, u32))(uintptr_t) vtable[RECYCLE_BIN_SLOT_SET_LID / 4])(self, lid);
}

/* func_ov004_0222f474: the collision box taken off the field. */
int RecycleBin_RemoveBox(RecycleBin *self)
{
    return CollisionBox_Remove(&self->box);
}
CLEAN_AS(func_ov004_0222f474, RecycleBin_RemoveBox)

/* func_ov004_0222f484: the collision box put on the field at its position, then its pick faces
 * set to the same box and added to the field object's picks; the latter's result. */
int RecycleBin_AddBox(RecycleBin *self)
{
    Vec3 *position = &self->base.actor.position;
    CollisionBox_Add(&self->box, RECYCLE_BIN_WIDTH, RECYCLE_BIN_DEPTH, RECYCLE_BIN_HEIGHT, position, 0, NULL);
    TouchPick *pick = (TouchPick *) (intptr_t) SceneQuery_FieldObject();
    return TouchPick_SetBoxAndAdd(pick, self->pick_faces, position, RECYCLE_BIN_WIDTH, RECYCLE_BIN_DEPTH, RECYCLE_BIN_HEIGHT,
                                  0, RECYCLE_BIN_PICK_KIND, RECYCLE_BIN_PICK_INDEX);
}
CLEAN_AS(func_ov004_0222f484, RecycleBin_AddBox)

/* func_ov004_0222f4e0 (receiver slot 0x18, the player's answer; primary slot 0x70): nothing. */
void RecycleBin_OnAnswer(RecycleBin *self)
{
    (void) self;
}
CLEAN_AS(func_ov004_0222f4e0, RecycleBin_OnAnswer)

/* func_ov004_0222f4e4 (receiver slot 0x14, after a message; primary slot 0x6c): leaves 0x1a in
 * the word at 0x248 of the field's sound and talk state (data_021c526c).
 * REQUIRES: that state exists (data_021c526c is not NULL). */
void RecycleBin_AfterMessage(RecycleBin *self)
{
    (void) self;
    *(s32 *) (void *) (data_021c526c + RECYCLE_BIN_TALK_END_WORD) = RECYCLE_BIN_TALK_END_VALUE;
}
CLEAN_AS(func_ov004_0222f4e4, RecycleBin_AfterMessage)

/* func_ov004_0222f4f8 (receiver slot 0x10, the talk ignored; primary slot 0x68): nothing. */
void RecycleBin_OnTalkIgnored(RecycleBin *self)
{
    (void) self;
}
CLEAN_AS(func_ov004_0222f4f8, RecycleBin_OnTalkIgnored)

/* func_ov004_0222f4fc (update of RECYCLE_BIN_CLOSE_LID): once the lid is closed, lets the scene
 * go on. The state stays until the scene sets another. */
void RecycleBin_UpdateCloseLid(RecycleBin *self)
{
    if (*recycle_bin_lid(self) == RECYCLE_BIN_LID_CLOSED) {
        EventQueue_FinishObjectEvent(self);
    }
}
CLEAN_AS(func_ov004_0222f4fc, RecycleBin_UpdateCloseLid)

/* func_ov004_0222f518 (entry of RECYCLE_BIN_CLOSE_LID): the lid closing, through the shared
 * values (which call vtable slot 0x60, RecycleBin_SetLid); their answer. */
int RecycleBin_EnterCloseLid(RecycleBin *self)
{
    return RoomObjectState_Change((RoomObject *) (void *) self, RECYCLE_BIN_LID_CLOSING);
}
CLEAN_AS(func_ov004_0222f518, RecycleBin_EnterCloseLid)

/* func_ov004_0222f524 (update of RECYCLE_BIN_SCREEN): on once the main engine is not on top
 * (data_021c8c9c is 0) and the recycle bin's screen could open again (it has closed). */
void RecycleBin_UpdateScreen(RecycleBin *self)
{
    if (data_021c8c9c == 0 && GroupParams_CanOpen()) {
        RecycleBin_EnterState(self, RECYCLE_BIN_CLOSE_LID);
    }
}
CLEAN_AS(func_ov004_0222f524, RecycleBin_UpdateScreen)

/* func_ov004_0222f54c (entry of RECYCLE_BIN_SCREEN): opens the recycle bin's screen in mode 0x20;
 * whether it opened. */
int RecycleBin_EnterScreen(RecycleBin *self)
{
    (void) self;
    return GroupParams_Open(RECYCLE_BIN_SCREEN_MODE) ? 1 : 0;
}
CLEAN_AS(func_ov004_0222f54c, RecycleBin_EnterScreen)

/* func_ov004_0222f568 (update of RECYCLE_BIN_OPEN_LID): on once the lid is open. */
void RecycleBin_UpdateOpenLid(RecycleBin *self)
{
    if (*recycle_bin_lid(self) == RECYCLE_BIN_LID_OPEN) {
        RecycleBin_EnterState(self, RECYCLE_BIN_SCREEN);
    }
}
CLEAN_AS(func_ov004_0222f568, RecycleBin_UpdateOpenLid)

/* func_ov004_0222f584 (entry of RECYCLE_BIN_OPEN_LID): the lid opening, through the shared values;
 * their answer. */
int RecycleBin_EnterOpenLid(RecycleBin *self)
{
    return RoomObjectState_Change((RoomObject *) (void *) self, RECYCLE_BIN_LID_OPENING);
}
CLEAN_AS(func_ov004_0222f584, RecycleBin_EnterOpenLid)

/* func_ov004_0222f590 (update of RECYCLE_BIN_TALK_END): once the talk has closed, hands the
 * receiver back and opens the lid. */
void RecycleBin_UpdateTalkEnd(RecycleBin *self)
{
    TalkObject *talk = self->receiver.talk;
    if (talk != NULL && talk->state == TALK_OBJECT_CLOSED) {
        SceneObjectBase_ReleaseReceiver((SceneObjectBase *) (void *) self, recycle_bin_receiver(self));
        RecycleBin_EnterState(self, RECYCLE_BIN_OPEN_LID);
    }
}
CLEAN_AS(func_ov004_0222f590, RecycleBin_UpdateTalkEnd)

/* func_ov004_0222f5c8 (entry of RECYCLE_BIN_TALK_END) */
int RecycleBin_EnterTalkEnd(RecycleBin *self)
{
    (void) self;
    return 1;
}
CLEAN_AS(func_ov004_0222f5c8, RecycleBin_EnterTalkEnd)

/* func_ov004_0222f5cc (update of RECYCLE_BIN_TALK): on once the talk has opened. */
void RecycleBin_UpdateTalk(RecycleBin *self)
{
    TalkObject *talk = self->receiver.talk;
    if (talk != NULL && talk->state != TALK_OBJECT_CLOSED) {
        RecycleBin_EnterState(self, RECYCLE_BIN_TALK_END);
    }
}
CLEAN_AS(func_ov004_0222f5cc, RecycleBin_UpdateTalk)

/* func_ov004_0222f5f0 (entry of RECYCLE_BIN_TALK): takes the receiver, names it "sp_npc_trash"
 * with message 0 and asks its talk to open.
 * REQUIRES: the receiver has a talk once SceneObjectBase_TakeReceiver has taken it. */
int RecycleBin_EnterTalk(RecycleBin *self)
{
    SceneObjectBase_TakeReceiver((SceneObjectBase *) (void *) self, recycle_bin_receiver(self));
    MessageReceiver_SetName(&self->receiver.base, data_ov004_02255304);
    self->receiver.base.message = 0;
    self->receiver.talk->next_state = RECYCLE_BIN_TALK_OPEN;
    return 1;
}
CLEAN_AS(func_ov004_0222f5f0, RecycleBin_EnterTalk)

/* func_ov004_0222f638 (update of RECYCLE_BIN_IDLE): nothing. */
void RecycleBin_UpdateIdle(RecycleBin *self)
{
    (void) self;
}
CLEAN_AS(func_ov004_0222f638, RecycleBin_UpdateIdle)

/* func_ov004_0222f63c (entry of RECYCLE_BIN_IDLE) */
int RecycleBin_EnterIdle(RecycleBin *self)
{
    (void) self;
    return 1;
}
CLEAN_AS(func_ov004_0222f63c, RecycleBin_EnterIdle)

/* _ZN18Obj_ov004_022553d819func_ov004_0222f640Ev: the state's update, through its table.
 * REQUIRES: the state is not negative (RecycleBin_EnterState only sets 0 to 5). */
void RecycleBin_UpdateState(RecycleBin *self)
{
    static const MemberPointer *const updates[RECYCLE_BIN_STATE_COUNT] = {
        &data_ov004_02255360, /* RecycleBin_UpdateIdle */
        &data_ov004_022553a0, /* RecycleBin_UpdateTalk */
        &data_ov004_02255318, /* RecycleBin_UpdateTalkEnd */
        &data_ov004_02255330, /* RecycleBin_UpdateOpenLid */
        &data_ov004_02255340, /* RecycleBin_UpdateScreen */
        &data_ov004_02255388, /* RecycleBin_UpdateCloseLid */
    };
    MemberTable_InitOnce(&data_ov004_02258494, data_ov004_022584f4, updates, RECYCLE_BIN_STATE_COUNT);
    if (self->state < RECYCLE_BIN_STATE_COUNT) {
        MemberPointer_CallVoid(&data_ov004_022584f4[self->state], self);
    }
}
CLEAN_AS(_ZN18Obj_ov004_022553d819func_ov004_0222f640Ev, RecycleBin_UpdateState)

/* func_ov004_0222f6e8: enters `state` if its entry (through a table) agrees; whether it did.
 * States 6 and above do not exist.
 * REQUIRES: `state` is not negative. */
int RecycleBin_EnterState(RecycleBin *self, int state)
{
    static const MemberPointer *const entries[RECYCLE_BIN_STATE_COUNT] = {
        &data_ov004_02255390, /* RecycleBin_EnterIdle */
        &data_ov004_02255398, /* RecycleBin_EnterTalk */
        &data_ov004_02255308, /* RecycleBin_EnterTalkEnd */
        &data_ov004_02255310, /* RecycleBin_EnterOpenLid */
        &data_ov004_02255320, /* RecycleBin_EnterScreen */
        &data_ov004_02255328, /* RecycleBin_EnterCloseLid */
    };
    MemberTable_InitOnce(&data_ov004_02258488, data_ov004_02258524, entries, RECYCLE_BIN_STATE_COUNT);
    if (state < RECYCLE_BIN_STATE_COUNT && MemberPointer_CallInt(&data_ov004_02258524[state], self) != 0) {
        self->state = state;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov004_0222f6e8, RecycleBin_EnterState)

/* func_ov004_0222f7a0 (update of RECYCLE_BIN_LID_CLOSING): closed once the closing has run out,
 * else the animation steps. */
void RecycleBin_UpdateClosing(RecycleBin *self)
{
    if (FrameCtrl_IsDone(&self->base.body.frames)) {
        recycle_bin_call_set_lid(self, RECYCLE_BIN_LID_CLOSED);
    } else {
        AnimatedModel_StepFrames(recycle_bin_body(self));
    }
}
CLEAN_AS(func_ov004_0222f7a0, RecycleBin_UpdateClosing)

/* func_ov004_0222f7d0 (entry of RECYCLE_BIN_LID_CLOSING): the closing played once, with its
 * sound. */
int RecycleBin_EnterClosing(RecycleBin *self)
{
    AnimatedModel_Start(recycle_bin_body(self), RmoModel_JointAnim(&self->base.body_model, RECYCLE_BIN_ANIM_CLOSING),
                        RECYCLE_BIN_PLAY_ONCE, FX32_ONE, 0, 0);
    RmoSound_Play(recycle_bin_sound_source(self), RECYCLE_BIN_SOUND_CLOSING);
    return 1;
}
CLEAN_AS(func_ov004_0222f7d0, RecycleBin_EnterClosing)

/* func_ov004_0222f818 (update of RECYCLE_BIN_LID_OPEN): nothing. */
void RecycleBin_UpdateOpen(RecycleBin *self)
{
    (void) self;
}
CLEAN_AS(func_ov004_0222f818, RecycleBin_UpdateOpen)

/* func_ov004_0222f81c (entry of RECYCLE_BIN_LID_OPEN): the closing started from its first frame
 * (the lid open), without sound; nothing steps it in this state. */
int RecycleBin_EnterOpen(RecycleBin *self)
{
    AnimatedModel_Start(recycle_bin_body(self), RmoModel_JointAnim(&self->base.body_model, RECYCLE_BIN_ANIM_CLOSING),
                        RECYCLE_BIN_PLAY_ONCE, FX32_ONE, 0, 0);
    return 1;
}
CLEAN_AS(func_ov004_0222f81c, RecycleBin_EnterOpen)

/* func_ov004_0222f854 (update of RECYCLE_BIN_LID_OPENING): open once the opening has run out,
 * else the animation steps. */
void RecycleBin_UpdateOpening(RecycleBin *self)
{
    if (FrameCtrl_IsDone(&self->base.body.frames)) {
        recycle_bin_call_set_lid(self, RECYCLE_BIN_LID_OPEN);
    } else {
        AnimatedModel_StepFrames(recycle_bin_body(self));
    }
}
CLEAN_AS(func_ov004_0222f854, RecycleBin_UpdateOpening)

/* func_ov004_0222f884 (entry of RECYCLE_BIN_LID_OPENING): the opening played once, with its
 * sound. */
int RecycleBin_EnterOpening(RecycleBin *self)
{
    AnimatedModel_Start(recycle_bin_body(self), RmoModel_JointAnim(&self->base.body_model, RECYCLE_BIN_ANIM_OPENING),
                        RECYCLE_BIN_PLAY_ONCE, FX32_ONE, 0, 0);
    RmoSound_Play(recycle_bin_sound_source(self), RECYCLE_BIN_SOUND_OPENING);
    return 1;
}
CLEAN_AS(func_ov004_0222f884, RecycleBin_EnterOpening)

/* func_ov004_0222f8cc (update of RECYCLE_BIN_LID_CLOSED): nothing. */
void RecycleBin_UpdateClosed(RecycleBin *self)
{
    (void) self;
}
CLEAN_AS(func_ov004_0222f8cc, RecycleBin_UpdateClosed)

/* func_ov004_0222f8d0 (entry of RECYCLE_BIN_LID_CLOSED): the opening started from its first
 * frame (the lid closed), without sound. */
int RecycleBin_EnterClosed(RecycleBin *self)
{
    AnimatedModel_Start(recycle_bin_body(self), RmoModel_JointAnim(&self->base.body_model, RECYCLE_BIN_ANIM_OPENING),
                        RECYCLE_BIN_PLAY_ONCE, FX32_ONE, 0, 0);
    return 1;
}
CLEAN_AS(func_ov004_0222f8d0, RecycleBin_EnterClosed)

/* _ZN18Obj_ov004_022553d819func_ov004_0222f908Ev: the lid's update, through its table; a lid
 * byte of 4 or more runs none. */
void RecycleBin_UpdateLid(RecycleBin *self)
{
    static const MemberPointer *const updates[RECYCLE_BIN_LID_COUNT] = {
        &data_ov004_02255350, /* RecycleBin_UpdateClosed */
        &data_ov004_02255338, /* RecycleBin_UpdateOpening */
        &data_ov004_02255348, /* RecycleBin_UpdateOpen */
        &data_ov004_02255358, /* RecycleBin_UpdateClosing */
    };
    MemberTable_InitOnce(&data_ov004_02258498, data_ov004_022584d4, updates, RECYCLE_BIN_LID_COUNT);
    u8 lid = *recycle_bin_lid(self);
    if (lid < RECYCLE_BIN_LID_COUNT) {
        MemberPointer_CallVoid(&data_ov004_022584d4[lid], self);
    }
}
CLEAN_AS(_ZN18Obj_ov004_022553d819func_ov004_0222f908Ev, RecycleBin_UpdateLid)

/* func_ov004_0222f994 (vtable slot 0x60): enters lid state `lid` when its entry (through a
 * table) agrees and the shared value takes it (RmoObjectSlots_SetSharedValue); whether it did. */
int RecycleBin_SetLid(RecycleBin *self, u32 lid)
{
    static const MemberPointer *const entries[RECYCLE_BIN_LID_COUNT] = {
        &data_ov004_02255380, /* RecycleBin_EnterClosed */
        &data_ov004_02255378, /* RecycleBin_EnterOpening */
        &data_ov004_02255370, /* RecycleBin_EnterOpen */
        &data_ov004_02255368, /* RecycleBin_EnterClosing */
    };
    MemberTable_InitOnce(&data_ov004_022584a8, data_ov004_022584b4, entries, RECYCLE_BIN_LID_COUNT);
    if (lid < RECYCLE_BIN_LID_COUNT && MemberPointer_CallInt(&data_ov004_022584b4[lid], self) != 0 &&
        RmoObjectSlots_SetSharedValue(&self->base, lid) != 0) {
        *recycle_bin_lid(self) = (u8) lid;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov004_0222f994, RecycleBin_SetLid)

/* func_ov004_0222fa3c (vtable slot 0x4c): the scene's events; event 0 starts the talk, event 8
 * makes it idle, others do nothing. */
void RecycleBin_OnSceneEvent(RecycleBin *self, int event)
{
    switch (event) {
        case RECYCLE_BIN_EVENT_TALK:
            RecycleBin_EnterState(self, RECYCLE_BIN_TALK);
            break;
        case RECYCLE_BIN_EVENT_IDLE:
            RecycleBin_EnterState(self, RECYCLE_BIN_IDLE);
            break;
    }
}
CLEAN_AS(func_ov004_0222fa3c, RecycleBin_OnSceneEvent)

/* func_ov004_0222fa60 (vtable slot 0x48): whether `other` may act on it: there, nearer than
 * 0x299a on the XZ plane, and facing it (its Y angle within 0x1200 of the box's turned
 * round). */
int RecycleBin_MayAct(RecycleBin *self, Actor *other)
{
    if (other != NULL && Vec_DistanceXZ(&other->position, &self->base.actor.position) < RECYCLE_BIN_REACH) {
        s16 facing_box = (s16) (u16) (self->base.actor.angle[1] + RECYCLE_BIN_HALF_TURN);
        if (Math_AbsDiff16(facing_box, other->angle[1]) < RECYCLE_BIN_FACING) {
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_ov004_0222fa60, RecycleBin_MayAct)

/* func_ov004_0222fab0 (vtable slot 0x0c): off the field, the archive released and no longer the
 * one that exists. */
int RecycleBin_Release(RecycleBin *self)
{
    RecycleBin_RemoveBox(self);
    RmoObjectSlots_ReleaseBody(&self->base);
    data_ov004_02258490 = NULL;
    return 1;
}
CLEAN_AS(func_ov004_0222fab0, RecycleBin_Release)

/* func_ov004_0222fad0 (vtable slot 0x24) */
int RecycleBin_Draw(RecycleBin *self)
{
    AnimatedModel_Draw(recycle_bin_body(self), NULL);
    return 1;
}
CLEAN_AS(func_ov004_0222fad0, RecycleBin_Draw)

/* _ZN18Obj_ov004_022553d819func_ov004_0222fae4Ev (vtable slot 0x18): the lid's update, the
 * state's, then its pick faces added to the field object's picks for this frame. */
int RecycleBin_Update(RecycleBin *self)
{
    RecycleBin_UpdateLid(self);
    RecycleBin_UpdateState(self);
    TouchPick_AddFaces((TouchPick *) (intptr_t) SceneQuery_FieldObject(), self->pick_faces);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov004_022553d819func_ov004_0222fae4Ev, RecycleBin_Update)

/* func_ov004_0222fb0c (vtable slot 0x00): becomes the one that exists, takes shared value 0,
 * loads its archive, goes on the field and, when it has a first joint animation that the model
 * can take, starts it once (the lid closed); then idle, with the lid in the state the shared
 * value holds. */
int RecycleBin_Start(RecycleBin *self)
{
    data_ov004_02258490 = self;
    RmoObjectSlots_SetValueNumber(&self->base, RECYCLE_BIN_STATE_NUMBER);
    RmoObjectSlots_LoadNamed(&self->base, data_ov004_022554cc);
    RecycleBin_AddBox(self);
    if (RmoModel_JointAnim(&self->base.body_model, RECYCLE_BIN_ANIM_OPENING) != NULL &&
        AnimatedModel_LoadAnim(recycle_bin_body(self), data_021c9b24) != 0) {
        AnimatedModel_Start(recycle_bin_body(self), RmoModel_JointAnim(&self->base.body_model, RECYCLE_BIN_ANIM_OPENING),
                            RECYCLE_BIN_PLAY_ONCE, FX32_ONE, 0, 0);
        AnimatedModel_Attach(recycle_bin_body(self));
    }
    RecycleBin_EnterState(self, RECYCLE_BIN_IDLE);
    recycle_bin_call_set_lid(self, (u32) RmoObjectSlots_SharedValue(&self->base));
    return 1;
}
CLEAN_AS(func_ov004_0222fb0c, RecycleBin_Start)

static void recycle_bin_set_vtables(RecycleBin *self)
{
    self->base.actor.vtable = data_ov004_022553d8;
    self->receiver.base.vtable = data_ov004_02255454;
}

/* func_ov004_0222fba4 (the deleting destructor, vtable slot 0x44) */
RecycleBin *RecycleBin_Delete(RecycleBin *self)
{
    recycle_bin_set_vtables(self);
    TouchPickFaces_DestructBox(self->pick_faces);
    CollisionBox_Destruct(&self->box);
    TalkReceiver_Destruct(&self->receiver);
    RmoObjectSlots_Destruct(&self->base);
    Heap_FreeAux(self);
    return self;
}
CLEAN_AS(func_ov004_0222fba4, RecycleBin_Delete)

/* func_ov004_0222fbf4 (the destructor, vtable slot 0x40) */
RecycleBin *RecycleBin_Destruct(RecycleBin *self)
{
    recycle_bin_set_vtables(self);
    TouchPickFaces_DestructBox(self->pick_faces);
    CollisionBox_Destruct(&self->box);
    TalkReceiver_Destruct(&self->receiver);
    RmoObjectSlots_Destruct(&self->base);
    return self;
}
CLEAN_AS(func_ov004_0222fbf4, RecycleBin_Destruct)

/* func_ov004_0222fc3c (the constructor). Its states are left as the allocation zeroed them. */
RecycleBin *RecycleBin_Construct(RecycleBin *self)
{
    RmoObjectBase_Construct(&self->base);
    TalkReceiver_ConstructBase(&self->receiver);
    recycle_bin_set_vtables(self);
    CollisionBox_Construct(&self->box);
    TouchPickFaces_ConstructBox(self->pick_faces);
    return self;
}
CLEAN_AS(func_ov004_0222fc3c, RecycleBin_Construct)

/* func_ov004_0222fc84: the one that exists (its address), 0 for none. */
u32 RecycleBin_Current(void)
{
    return (u32) (uintptr_t) data_ov004_02258490;
}
CLEAN_AS(func_ov004_0222fc84, RecycleBin_Current)

/* func_ov004_0222fc90: a new one from the room's heap; nothing when it has no room. */
void RecycleBin_Create(void)
{
    RecycleBin *self = Heap_AllocAuxZeroed(sizeof(RecycleBin));
    if (self != NULL) {
        RecycleBin_Construct(self);
    }
}
CLEAN_AS(func_ov004_0222fc90, RecycleBin_Create)

/* The receiver part (at 0x290) enters RecycleBin's functions through its vtable with these: each
 * moves the pointer back to the object and goes on with the object's function. */
static RecycleBin *recycle_bin_from_receiver(void *receiver)
{
    return (RecycleBin *) (void *) ((u8 *) receiver - offsetof(RecycleBin, receiver));
}

/* func_ov004_0222fcac: the deleting destructor, entered from the receiver part. */
RecycleBin *RecycleBinReceiver_Delete(void *receiver)
{
    return RecycleBin_Delete(recycle_bin_from_receiver(receiver));
}
CLEAN_AS(_ZThn656_N18Obj_ov004_022553d8D0Ev, RecycleBinReceiver_Delete)

/* func_ov004_0222fcc8: receiver slot 0x18 (RecycleBin_OnAnswer). */
void RecycleBinReceiver_OnAnswer(void *receiver)
{
    RecycleBin_OnAnswer(recycle_bin_from_receiver(receiver));
}
CLEAN_AS(_ZThn656_N18Obj_ov004_022553d817vfunc_02066994_18Ev, RecycleBinReceiver_OnAnswer)

/* func_ov004_0222fce4: receiver slot 0x14 (RecycleBin_AfterMessage). */
void RecycleBinReceiver_AfterMessage(void *receiver)
{
    RecycleBin_AfterMessage(recycle_bin_from_receiver(receiver));
}
CLEAN_AS(_ZThn656_N18Obj_ov004_022553d817vfunc_02066994_14Ev, RecycleBinReceiver_AfterMessage)

/* func_ov004_0222fd00: receiver slot 0x10 (RecycleBin_OnTalkIgnored). */
void RecycleBinReceiver_OnTalkIgnored(void *receiver)
{
    RecycleBin_OnTalkIgnored(recycle_bin_from_receiver(receiver));
}
CLEAN_AS(_ZThn656_N18Obj_ov004_022553d817vfunc_02066994_10Ev, RecycleBinReceiver_OnTalkIgnored)

/* func_ov004_0222fd1c: the destructor, entered from the receiver part. */
RecycleBin *RecycleBinReceiver_Destruct(void *receiver)
{
    return RecycleBin_Destruct(recycle_bin_from_receiver(receiver));
}
CLEAN_AS(_ZThn656_N18Obj_ov004_022553d8D1Ev, RecycleBinReceiver_Destruct)
