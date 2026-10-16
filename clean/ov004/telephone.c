/* The telephone (telephone.h). */
#include "telephone.h"

#include "clean.h"
#include "member_pointer.h"
#include "room_object_anims.h"
#include "room_object_parts.h"

static_assert(offsetof(Telephone, entry_words) == 0x844, "entry words");
static_assert(offsetof(Telephone, wait) == 0x852, "wait");
static_assert(offsetof(Telephone, switch_state) == 0x854, "switch state");
static_assert(offsetof(Telephone, state) == 0x858, "state");
static_assert(sizeof(Telephone) == 0x85c, "the size func_ov004_02211c64 allocates");

#define RECEIVER_OFFSET 0xec
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

/* The two entries a telephone's values come from, and their parts. */
extern void *func_ov004_0223cb10(void);
extern void *func_ov004_0223ca9c(void *entries, Telephone *phone);
extern s32 *func_ov004_0223cb24(void *entry);
extern int func_ov004_0223cb18(void *entry);

/* The scene object's hooks. */
extern int func_0203e0a8(Telephone *phone, int a1);
extern int func_0203e020(Telephone *phone);
extern void func_0203ee08(Telephone *phone, void *receiver);
extern void func_0203ee14(Telephone *phone, void *receiver);
extern void func_020a8164(void *receiver, const char *name);

/* The receiver part as C++ converts a pointer to the telephone to it: NULL stays NULL. */
static void *receiver_of(Telephone *phone)
{
    return phone != NULL ? (u8 *) phone + RECEIVER_OFFSET : NULL;
}

/* Vtable slot 0x70: the telephone's (func_ov004_02211aa0) enters a state of its switch. */
static void switch_to(Telephone *phone, int state)
{
    phone->base.vtable->vfunc_70(&phone->base, state, SLOT_70_VALUE);
}

/* func_ov004_0221167c (update of TELEPHONE_CLOSE): once its frame has passed, lets the scene go
 * on (func_0203e020). */
void Telephone_UpdateClose(Telephone *phone)
{
    if (phone->wait == 0) {
        func_0203e020(phone);
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
 * receiver back (func_0203ee08) and closes. */
void Telephone_UpdateTalkEnd(Telephone *phone)
{
    if (phone->base.link != NULL && phone->base.link->open == 0) {
        func_0203ee08(phone, receiver_of(phone));
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
    if (phone->base.link != NULL && phone->base.link->open != 0) {
        Telephone_EnterState(phone, TELEPHONE_TALK_END);
    }
}
CLEAN_AS(func_ov004_022116fc, Telephone_UpdateTalk)

/* func_ov004_02211720 (entry of TELEPHONE_TALK): takes the receiver (func_0203ee14), raises the
 * link's request, names the receiver "obj_etc_tel" and resets its state byte.
 * REQUIRES: the receiver has a link once func_0203ee14 has taken it. */
int Telephone_EnterTalk(Telephone *phone)
{
    func_0203ee14(phone, receiver_of(phone));
    phone->base.link->requested = 1;
    func_020a8164(&phone->base.receiver_vtable, data_ov004_02253184);
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
 * values of the telephone's entry and asks the scene for an event (func_0203e0a8); the switch
 * is then set off, shown at once, every frame.
 * BUG: without an entry for it, func_ov004_0223cb24 is handed NULL and the words are read from
 * address 0x2c; kept. */
void Telephone_UpdateIdle(Telephone *phone)
{
    if (Switch_IsPending(&phone->base.light_switch)) {
        void *entry = func_ov004_0223ca9c(func_ov004_0223cb10(), phone);
        s32 *words = func_ov004_0223cb24(entry);
        phone->entry_words[0] = words[0];
        phone->entry_words[1] = words[1];
        phone->entry_words[2] = words[2];
        phone->entry_value = (u16) func_ov004_0223cb18(entry);
        func_0203e0a8(phone, 0);
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
