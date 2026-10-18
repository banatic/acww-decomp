/* The telephone (telephone.h). */
#include "telephone.h"

#include "clean.h"
#include "member_pointer.h"
#include "room_object_anims.h"
#include "room_object_body.h"
#include "room_object_life.h"
#include "room_object_parts.h"
#include "main/event_queue.h"
#include "main/message_receiver.h"
#include "main/scene_object_base.h"
#include "room_pushes.h"

static_assert(offsetof(Telephone, entry_words) == 0x844, "entry words");
static_assert(offsetof(Telephone, wait) == 0x852, "wait");
static_assert(offsetof(Telephone, switch_state) == 0x854, "switch state");
static_assert(offsetof(Telephone, state) == 0x858, "state");
static_assert(sizeof(Telephone) == 0x85c, "the size Telephone_Create allocates");

#define RECEIVER_OFFSET 0xec
#define TELEPHONE_SIZE 0x85c
#define SLOT_70_VALUE 0xff /* the second argument the telephone gives vtable slot 0x70 */

/* "obj_etc_tel", the receiver's name. */
extern const char data_ov004_02253184[];

/* The call's state tables (member_pointer.h): their guards, the tables and their constants. */
extern u32 data_ov004_02257010;
extern MemberPointer data_ov004_02257584[TELEPHONE_STATE_COUNT];
extern const MemberPointer data_ov004_02250268, data_ov004_02250288, data_ov004_022502b0, data_ov004_02250208,
    data_ov004_02250028;
extern u32 data_ov004_02256ff8;
extern MemberPointer data_ov004_0225755c[TELEPHONE_STATE_COUNT];
extern const MemberPointer data_ov004_02250428, data_ov004_02250108, data_ov004_022503e0, data_ov004_022503d0,
    data_ov004_022503b0;

/* The switch's state tables. */
extern u32 data_ov004_022570a0;
extern MemberPointer data_ov004_0225736c[TELEPHONE_SWITCH_STATE_COUNT];
extern const MemberPointer data_ov004_02250098, data_ov004_022504c8, data_ov004_022500b0, data_ov004_02250140;
extern u32 data_ov004_02256ff0;
extern MemberPointer data_ov004_0225734c[TELEPHONE_SWITCH_STATE_COUNT];
extern const MemberPointer data_ov004_02250040, data_ov004_022501c0, data_ov004_02250060, data_ov004_02250068;

/* Whether each state of the switch shows it on (for vtable slot 0x74). */
extern const u8 data_ov004_02247684[TELEPHONE_SWITCH_STATE_COUNT];

/* The class's vtables, and its receiver part's. */
extern const u8 data_ov004_02252950[];
extern const u8 data_ov004_022529fc[];

/* The receiver part as C++ converts a pointer to the telephone to it: NULL stays NULL. */
static void *receiver_of(Telephone *phone)
{
    return phone != NULL ? (u8 *) phone + RECEIVER_OFFSET : NULL;
}

/* Vtable slot 0x70: the telephone's (Telephone_EnterSwitch) enters a state of its switch. */
static void switch_to(Telephone *phone, int state)
{
    phone->base.vtable->vfunc_70(&phone->base, state, SLOT_70_VALUE);
}

/* func_ov004_0221167c (update of TELEPHONE_CLOSE): once its frame has passed, lets the scene go
 * on (EventQueue_FinishObjectEvent). */
void Telephone_UpdateClose(Telephone *phone)
{
    if (phone->wait == 0) {
        EventQueue_FinishObjectEvent(phone);
    }
    if (phone->wait != 0) {
        phone->wait--;
    }
}
CLEAN_AS(func_ov004_0221167c, Telephone_UpdateClose)

/* func_ov004_022116a4 (entry of TELEPHONE_CLOSE): the switch starts to turn off; one frame. */
int Telephone_EnterClose(Telephone *phone)
{
    switch_to(phone, TELEPHONE_SWITCH_TURNING_OFF);
    phone->wait = 1;
    return 1;
}
CLEAN_AS(func_ov004_022116a4, Telephone_EnterClose)

/* func_ov004_022116c4 (update of TELEPHONE_TALK_END): once the link has closed, hands the
 * receiver back (SceneObjectBase_ReleaseReceiver) and closes. */
void Telephone_UpdateTalkEnd(Telephone *phone)
{
    if (phone->base.link != NULL && phone->base.link->state == 0) {
        SceneObjectBase_ReleaseReceiver(&phone->base.scene, receiver_of(phone));
        Telephone_EnterState(phone, TELEPHONE_CLOSE);
    }
}
CLEAN_AS(func_ov004_022116c4, Telephone_UpdateTalkEnd)

/* func_ov004_022116f8 (entry of TELEPHONE_TALK_END) */
int Telephone_EnterTalkEnd(Telephone *phone)
{
    (void) phone;
    return 1;
}
CLEAN_AS(func_ov004_022116f8, Telephone_EnterTalkEnd)

/* func_ov004_022116fc (update of TELEPHONE_TALK): on once the link has opened. */
void Telephone_UpdateTalk(Telephone *phone)
{
    if (phone->base.link != NULL && phone->base.link->state != 0) {
        Telephone_EnterState(phone, TELEPHONE_TALK_END);
    }
}
CLEAN_AS(func_ov004_022116fc, Telephone_UpdateTalk)

/* func_ov004_02211720 (entry of TELEPHONE_TALK): takes the receiver (SceneObjectBase_TakeReceiver), raises the
 * link's request, names the receiver "obj_etc_tel" and resets its state byte.
 * REQUIRES: the receiver has a link once SceneObjectBase_TakeReceiver has taken it. */
int Telephone_EnterTalk(Telephone *phone)
{
    SceneObjectBase_TakeReceiver(&phone->base.scene, receiver_of(phone));
    phone->base.link->next_state = 1;
    MessageReceiver_SetName(&phone->base.receiver.base, data_ov004_02253184);
    phone->base.receiver_state = 0;
    return 1;
}
CLEAN_AS(func_ov004_02211720, Telephone_EnterTalk)

/* func_ov004_02211764 (update of TELEPHONE_OPEN): talks once its frame has passed. */
void Telephone_UpdateOpen(Telephone *phone)
{
    if (phone->wait == 0) {
        Telephone_EnterState(phone, TELEPHONE_TALK);
    }
    if (phone->wait != 0) {
        phone->wait--;
    }
}
CLEAN_AS(func_ov004_02211764, Telephone_UpdateOpen)

/* func_ov004_02211790 (entry of TELEPHONE_OPEN): the switch starts to turn on; one frame. */
int Telephone_EnterOpen(Telephone *phone)
{
    switch_to(phone, TELEPHONE_SWITCH_TURNING_ON);
    phone->wait = 1;
    return 1;
}
CLEAN_AS(func_ov004_02211790, Telephone_EnterOpen)

/* func_ov004_022117b0 (update of TELEPHONE_IDLE): when the switch was asked to change, takes the
 * values of the telephone's entry and asks the scene for an event (EventQueue_RequestKind6); the switch
 * is then set off, shown at once, every frame.
 * BUG: without an entry for it, RoomPushes_Destination is handed NULL and the words are read from
 * address 0x2c; kept. */
void Telephone_UpdateIdle(Telephone *phone)
{
    if (Switch_IsPending(&phone->base.light_switch)) {
        void *entry = RoomPushes_FindObject(RoomPushes_Records(), &phone->base);
        Vec3 *destination = RoomPushes_Destination(entry);
        phone->entry_words[0] = destination->x;
        phone->entry_words[1] = destination->y;
        phone->entry_words[2] = destination->z;
        phone->entry_value = (u16) RoomPushes_Facing(entry);
        EventQueue_RequestKind6(phone, 0);
    }
    Switch_Set(&phone->base.light_switch, 0, 0);
}
CLEAN_AS(func_ov004_022117b0, Telephone_UpdateIdle)

/* func_ov004_02211820 (entry of TELEPHONE_IDLE) */
int Telephone_EnterIdle(Telephone *phone)
{
    (void) phone;
    return 1;
}
CLEAN_AS(func_ov004_02211820, Telephone_EnterIdle)

/* _ZN18Obj_ov004_0225295019func_ov004_02211824Ev: the call's update, through its table.
 * REQUIRES: the state is not negative (Telephone_EnterState only sets 0 to 4). */
void Telephone_UpdateState(Telephone *phone)
{
    static const MemberPointer *const updates[TELEPHONE_STATE_COUNT] = {
        &data_ov004_02250268, /* Telephone_UpdateIdle */
        &data_ov004_02250288, /* Telephone_UpdateOpen */
        &data_ov004_022502b0, /* Telephone_UpdateTalk */
        &data_ov004_02250208, /* Telephone_UpdateTalkEnd */
        &data_ov004_02250028, /* Telephone_UpdateClose */
    };
    MemberTable_InitOnce(&data_ov004_02257010, data_ov004_02257584, updates, TELEPHONE_STATE_COUNT);
    if (phone->state < TELEPHONE_STATE_COUNT) {
        MemberPointer_CallVoid(&data_ov004_02257584[phone->state], phone);
    }
}
CLEAN_AS(_ZN18Obj_ov004_0225295019func_ov004_02211824Ev, Telephone_UpdateState)

/* func_ov004_022118bc: enters `state` of the call if its entry (through a table) agrees;
 * whether it did. States 5 and above do not exist.
 * REQUIRES: `state` is not negative. */
int Telephone_EnterState(Telephone *phone, int state)
{
    static const MemberPointer *const entries[TELEPHONE_STATE_COUNT] = {
        &data_ov004_02250428, /* Telephone_EnterIdle */
        &data_ov004_02250108, /* Telephone_EnterOpen */
        &data_ov004_022503e0, /* Telephone_EnterTalk */
        &data_ov004_022503d0, /* Telephone_EnterTalkEnd */
        &data_ov004_022503b0, /* Telephone_EnterClose */
    };
    MemberTable_InitOnce(&data_ov004_02256ff8, data_ov004_0225755c, entries, TELEPHONE_STATE_COUNT);
    if (state < TELEPHONE_STATE_COUNT && MemberPointer_CallInt(&data_ov004_0225755c[state], phone) != 0) {
        phone->state = state;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov004_022118bc, Telephone_EnterState)

/* func_ov004_02211964 (update of TELEPHONE_SWITCH_TURNING_OFF): off. */
void Telephone_UpdateSwitchTurningOff(Telephone *phone)
{
    switch_to(phone, TELEPHONE_SWITCH_OFF);
}
CLEAN_AS(func_ov004_02211964, Telephone_UpdateSwitchTurningOff)

/* func_ov004_02211978 (entry of TELEPHONE_SWITCH_TURNING_OFF): the switch off, shown at once,
 * with sound 1. */
int Telephone_EnterSwitchTurningOff(Telephone *phone)
{
    Switch_Set(&phone->base.light_switch, 0, 0);
    RoomObject_PlaySound1(&phone->base);
    return 1;
}
CLEAN_AS(func_ov004_02211978, Telephone_EnterSwitchTurningOff)

/* func_ov004_0221199c (update of TELEPHONE_SWITCH_ON) */
void Telephone_UpdateSwitchOn(Telephone *phone)
{
    (void) phone;
}
CLEAN_AS(func_ov004_0221199c, Telephone_UpdateSwitchOn)

/* func_ov004_022119a0 (entry of TELEPHONE_SWITCH_ON): the switch on, shown at once. */
int Telephone_EnterSwitchOn(Telephone *phone)
{
    Switch_Set(&phone->base.light_switch, 1, 0);
    return 1;
}
CLEAN_AS(func_ov004_022119a0, Telephone_EnterSwitchOn)

/* func_ov004_022119bc (update of TELEPHONE_SWITCH_TURNING_ON): on. */
void Telephone_UpdateSwitchTurningOn(Telephone *phone)
{
    switch_to(phone, TELEPHONE_SWITCH_ON);
}
CLEAN_AS(func_ov004_022119bc, Telephone_UpdateSwitchTurningOn)

/* func_ov004_022119d0 (entry of TELEPHONE_SWITCH_TURNING_ON): the switch on, shown at once,
 * with sound 1. */
int Telephone_EnterSwitchTurningOn(Telephone *phone)
{
    Switch_Set(&phone->base.light_switch, 1, 0);
    RoomObject_PlaySound1(&phone->base);
    return 1;
}
CLEAN_AS(func_ov004_022119d0, Telephone_EnterSwitchTurningOn)

/* func_ov004_022119f4 (update of TELEPHONE_SWITCH_OFF) */
void Telephone_UpdateSwitchOff(Telephone *phone)
{
    (void) phone;
}
CLEAN_AS(func_ov004_022119f4, Telephone_UpdateSwitchOff)

/* func_ov004_022119f8 (entry of TELEPHONE_SWITCH_OFF): the switch off, shown at once. */
int Telephone_EnterSwitchOff(Telephone *phone)
{
    Switch_Set(&phone->base.light_switch, 0, 0);
    return 1;
}
CLEAN_AS(func_ov004_022119f8, Telephone_EnterSwitchOff)

/* _ZN18Obj_ov004_0225295019func_ov004_02211a14Ev: the switch's update, through its table. */
void Telephone_UpdateSwitch(Telephone *phone)
{
    static const MemberPointer *const updates[TELEPHONE_SWITCH_STATE_COUNT] = {
        &data_ov004_02250098, /* Telephone_UpdateSwitchOff */
        &data_ov004_022504c8, /* Telephone_UpdateSwitchTurningOn */
        &data_ov004_022500b0, /* Telephone_UpdateSwitchOn */
        &data_ov004_02250140, /* Telephone_UpdateSwitchTurningOff */
    };
    MemberTable_InitOnce(&data_ov004_022570a0, data_ov004_0225736c, updates, TELEPHONE_SWITCH_STATE_COUNT);
    if (phone->switch_state < TELEPHONE_SWITCH_STATE_COUNT) {
        MemberPointer_CallVoid(&data_ov004_0225736c[phone->switch_state], phone);
    }
}
CLEAN_AS(_ZN18Obj_ov004_0225295019func_ov004_02211a14Ev, Telephone_UpdateSwitch)

/* func_ov004_02211aa0 (vtable slot 0x70): the base class's (RoomObject_SetUnk77C, given `state`
 * and `value`), then enters `state` of the switch if its entry (through a table) agrees;
 * whether it did. States 4 and above do not exist. */
int Telephone_EnterSwitch(Telephone *phone, unsigned int state, int value)
{
    static const MemberPointer *const entries[TELEPHONE_SWITCH_STATE_COUNT] = {
        &data_ov004_02250040, /* Telephone_EnterSwitchOff */
        &data_ov004_022501c0, /* Telephone_EnterSwitchTurningOn */
        &data_ov004_02250060, /* Telephone_EnterSwitchOn */
        &data_ov004_02250068, /* Telephone_EnterSwitchTurningOff */
    };
    RoomObject_SetUnk77C(&phone->base, (int) state, value);
    MemberTable_InitOnce(&data_ov004_02256ff0, data_ov004_0225734c, entries, TELEPHONE_SWITCH_STATE_COUNT);
    if (state < TELEPHONE_SWITCH_STATE_COUNT && MemberPointer_CallInt(&data_ov004_0225734c[state], phone) != 0) {
        phone->switch_state = (u8) state;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov004_02211aa0, Telephone_EnterSwitch)

/* func_ov004_02211b40 (vtable slot 0x74): whether `state` of the switch shows it on (turning on
 * and on do); 0 for a state that does not exist. */
u8 Telephone_SwitchStateIsOn(Telephone *phone, unsigned int state)
{
    (void) phone;
    if (state < TELEPHONE_SWITCH_STATE_COUNT) {
        return data_ov004_02247684[state];
    }
    return 0;
}
CLEAN_AS(func_ov004_02211b40, Telephone_SwitchStateIsOn)

/* func_ov004_02211b54 (vtable slot 0x4c): the scene's answer to EventQueue_RequestKind6; events 0 and 1
 * open the telephone, event 8 makes it idle, others do nothing. */
void Telephone_OnSceneEvent(Telephone *phone, int event)
{
    switch (event) {
        case 0:
        case 1:
            Telephone_EnterState(phone, TELEPHONE_OPEN);
            break;
        case 8:
            Telephone_EnterState(phone, TELEPHONE_IDLE);
            break;
    }
}
CLEAN_AS(func_ov004_02211b54, Telephone_OnSceneEvent)

/* func_ov004_02211b7c (vtable slot 0x0c) */
int Telephone_Vfunc0C(void)
{
    return 1;
}
CLEAN_AS(func_ov004_02211b7c, Telephone_Vfunc0C)

/* _ZN18Obj_ov004_0225295019func_ov004_02211b80Ev (vtable slot 0x80, each frame while neither
 * appearing nor vanishing): the call, then the switch. */
int Telephone_Update(Telephone *phone)
{
    Telephone_UpdateState(phone);
    Telephone_UpdateSwitch(phone);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov004_0225295019func_ov004_02211b80Ev, Telephone_Update)

/* func_ov004_02211b98 (vtable slot 0x7c, once the model is bound): in mode 1 (unk_76C) the
 * switch is set off first; the switch then enters on or off as its value says, and the
 * telephone is idle; done at once. */
int Telephone_Start(Telephone *phone)
{
    if (phone->base.unk_76C == 1) {
        Switch_Set(&phone->base.light_switch, 0, 0);
    }
    if (Switch_Value(&phone->base.light_switch) != 0) {
        switch_to(phone, TELEPHONE_SWITCH_ON);
    } else {
        switch_to(phone, TELEPHONE_SWITCH_OFF);
    }
    Telephone_EnterState(phone, TELEPHONE_IDLE);
    return 1;
}
CLEAN_AS(func_ov004_02211b98, Telephone_Start)

static void set_vtables(Telephone *phone)
{
    phone->base.vtable = (const RoomObjectVtable *) data_ov004_02252950;
    phone->base.receiver_vtable = data_ov004_022529fc;
}

/* func_ov004_02211bf0 (the deleting destructor, vtable slot 0x44) */
Telephone *Telephone_Delete(Telephone *phone)
{
    set_vtables(phone);
    RoomObject_DestructBase(&phone->base);
    RoomObject_Free(phone);
    return phone;
}
CLEAN_AS(func_ov004_02211bf0, Telephone_Delete)

/* func_ov004_02211c1c (the destructor, vtable slot 0x40) */
Telephone *Telephone_Destroy(Telephone *phone)
{
    set_vtables(phone);
    RoomObject_DestructBase(&phone->base);
    return phone;
}
CLEAN_AS(func_ov004_02211c1c, Telephone_Destroy)

/* func_ov004_02211c40 (the constructor). Its own fields are left as the allocation zeroed
 * them. */
Telephone *Telephone_Construct(Telephone *phone)
{
    RoomObject_ConstructBase(&phone->base);
    set_vtables(phone);
    return phone;
}
CLEAN_AS(func_ov004_02211c40, Telephone_Construct)

/* func_ov004_02211c64: a new telephone from the room's heap; nothing when it has no room. */
void Telephone_Create(void)
{
    Telephone *phone = RoomObject_Alloc(TELEPHONE_SIZE);
    if (phone != NULL) {
        Telephone_Construct(phone);
    }
}
CLEAN_AS(func_ov004_02211c64, Telephone_Create)

/* The receiver part (at 0xec, RoomObject.receiver_vtable) enters Telephone's destructors through
 * its vtable with these: each moves the pointer back to the object and goes on with the
 * object's function. */
static Telephone *Telephone_from_receiver(void *receiver)
{
    return (Telephone *) (void *) ((u8 *) receiver - offsetof(RoomObject, receiver_vtable));
}

/* func_ov004_0221ac9c: the deleting destructor, entered from the receiver part. */
Telephone *TelephoneReceiver_Delete(void *receiver)
{
    return Telephone_Delete(Telephone_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov004_02252950D0Ev, TelephoneReceiver_Delete)

/* func_ov004_0221acb8: the destructor, entered from the receiver part. */
Telephone *TelephoneReceiver_Destroy(void *receiver)
{
    return Telephone_Destroy(Telephone_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov004_02252950D1Ev, TelephoneReceiver_Destroy)
