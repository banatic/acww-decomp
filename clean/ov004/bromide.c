/* The bromide (bromide.h). */
#include "bromide.h"

#include "clean.h"
#include "member_pointer.h"
#include "room_object_body.h"
#include "room_object_life.h"
#include "room_object_parts.h"

static_assert(offsetof(Bromide, state) == 0x844, "state");
static_assert(sizeof(Bromide) == 0x848, "the size of a bromide");

#define BROMIDE_RECEIVER_OFFSET 0xec
#define BROMIDE_SIZE 0x848

/* The item codes of the photos: four codes (variants) each, from the first. */
#define BROMIDE_ITEM_FIRST 0x47d8
#define BROMIDE_ITEM_LAST 0x4a47
#define BROMIDE_NO_PHOTO (-1)

/* The scene events that open the bromide and that make it idle (vtable slot 0x4c). */
#define BROMIDE_EVENT_OPEN 1
#define BROMIDE_EVENT_IDLE 8

/* "obj_etc_bromide", the receiver's name. */
extern const char data_ov004_022531b0[];

/* The state tables (member_pointer.h): their guards, the tables and their constants. */
extern u32 data_ov004_0225705c;
extern MemberPointer data_ov004_0225732c[BROMIDE_STATE_COUNT];
extern const MemberPointer data_ov004_022501b0, data_ov004_022501a8, data_ov004_022501a0, data_ov004_02250198;
extern u32 data_ov004_02257090;
extern MemberPointer data_ov004_0225730c[BROMIDE_STATE_COUNT];
extern const MemberPointer data_ov004_022501e0, data_ov004_02250030, data_ov004_022501d0, data_ov004_022501c8;

/* The class's vtables, and its receiver part's. */
extern const u8 data_ov004_02251b40[];
extern const u8 data_ov004_02251bec[];

/* The scene object's hooks. */
extern int func_0203e0a8(Bromide *bromide, int a1);
extern int func_0203e020(Bromide *bromide);
extern void func_0203ee08(Bromide *bromide, void *receiver);
extern void func_0203ee14(Bromide *bromide, void *receiver);
extern void func_020a8164(void *receiver, const char *name);
/* The item code of furniture `item` in `variant`. */
extern u16 func_0204bc50(int item, int variant);

/* The receiver part as C++ converts a pointer to the bromide to it: NULL stays NULL. */
static void *Bromide_receiver(Bromide *bromide)
{
    return bromide != NULL ? (u8 *) bromide + BROMIDE_RECEIVER_OFFSET : NULL;
}

/* func_ov004_022133f8 (update of BROMIDE_TALK_END): once the link has closed, hands the
 * receiver back (func_0203ee08) and lets the scene go on (func_0203e020). Its state stays
 * BROMIDE_TALK_END until the scene sets another. */
void Bromide_UpdateTalkEnd(Bromide *bromide)
{
    if (bromide->base.link != NULL && bromide->base.link->open == 0) {
        func_0203ee08(bromide, Bromide_receiver(bromide));
        func_0203e020(bromide);
    }
}
CLEAN_AS(func_ov004_022133f8, Bromide_UpdateTalkEnd)

/* func_ov004_02213428 (entry of BROMIDE_TALK_END) */
int Bromide_EnterTalkEnd(Bromide *bromide)
{
    (void) bromide;
    return 1;
}
CLEAN_AS(func_ov004_02213428, Bromide_EnterTalkEnd)

/* func_ov004_0221342c (update of BROMIDE_TALK): on once the link has opened. */
void Bromide_UpdateTalk(Bromide *bromide)
{
    if (bromide->base.link != NULL && bromide->base.link->open != 0) {
        Bromide_EnterState(bromide, BROMIDE_TALK_END);
    }
}
CLEAN_AS(func_ov004_0221342c, Bromide_UpdateTalk)

/* func_ov004_02213450 (entry of BROMIDE_TALK): takes the receiver (func_0203ee14), raises the
 * link's request, names the receiver "obj_etc_bromide" and puts the photo's number in its state
 * byte: the item code's distance from the first photo's, in fours, or 0xff for a code that is
 * no photo.
 * REQUIRES: the receiver has a link once func_0203ee14 has taken it. */
int Bromide_EnterTalk(Bromide *bromide)
{
    func_0203ee14(bromide, Bromide_receiver(bromide));
    bromide->base.link->requested = 1;
    u16 item = func_0204bc50(RoomObject_Number(&bromide->base), 0);
    int photo = BROMIDE_NO_PHOTO;
    if (item >= BROMIDE_ITEM_FIRST && item <= BROMIDE_ITEM_LAST) {
        photo = (item - BROMIDE_ITEM_FIRST) >> 2;
    }
    func_020a8164(&bromide->base.receiver_vtable, data_ov004_022531b0);
    bromide->base.receiver_state = (u8) photo;
    return 1;
}
CLEAN_AS(func_ov004_02213450, Bromide_EnterTalk)

/* func_ov004_022134cc (update of BROMIDE_OPEN): talks at once. */
void Bromide_UpdateOpen(Bromide *bromide)
{
    Bromide_EnterState(bromide, BROMIDE_TALK);
}
CLEAN_AS(func_ov004_022134cc, Bromide_UpdateOpen)

/* func_ov004_022134d8 (entry of BROMIDE_OPEN) */
int Bromide_EnterOpen(Bromide *bromide)
{
    (void) bromide;
    return 1;
}
CLEAN_AS(func_ov004_022134d8, Bromide_EnterOpen)

/* func_ov004_022134dc (update of BROMIDE_IDLE): when the switch was asked to change, asks the
 * scene for an event (func_0203e0a8) and gives its answer; else 0. */
int Bromide_UpdateIdle(Bromide *bromide)
{
    if (Switch_IsPending(&bromide->base.light_switch)) {
        return func_0203e0a8(bromide, 0);
    }
    return 0;
}
CLEAN_AS(func_ov004_022134dc, Bromide_UpdateIdle)

/* func_ov004_02213500 (entry of BROMIDE_IDLE) */
int Bromide_EnterIdle(Bromide *bromide)
{
    (void) bromide;
    return 1;
}
CLEAN_AS(func_ov004_02213500, Bromide_EnterIdle)

/* _ZN18Obj_ov004_02251b4019func_ov004_02213504Ev: the state's update, through its table.
 * REQUIRES: the state is not negative (Bromide_EnterState only sets 0 to 3). */
void Bromide_UpdateState(Bromide *bromide)
{
    static const MemberPointer *const updates[BROMIDE_STATE_COUNT] = {
        &data_ov004_022501b0, /* Bromide_UpdateIdle */
        &data_ov004_022501a8, /* Bromide_UpdateOpen */
        &data_ov004_022501a0, /* Bromide_UpdateTalk */
        &data_ov004_02250198, /* Bromide_UpdateTalkEnd */
    };
    MemberTable_InitOnce(&data_ov004_0225705c, data_ov004_0225732c, updates, BROMIDE_STATE_COUNT);
    if (bromide->state < BROMIDE_STATE_COUNT) {
        MemberPointer_CallVoid(&data_ov004_0225732c[bromide->state], bromide);
    }
}
CLEAN_AS(_ZN18Obj_ov004_02251b4019func_ov004_02213504Ev, Bromide_UpdateState)

/* func_ov004_02213590: enters `state` if its entry (through a table) agrees; whether it did.
 * States 4 and above do not exist.
 * REQUIRES: `state` is not negative. */
int Bromide_EnterState(Bromide *bromide, int state)
{
    static const MemberPointer *const entries[BROMIDE_STATE_COUNT] = {
        &data_ov004_022501e0, /* Bromide_EnterIdle */
        &data_ov004_02250030, /* Bromide_EnterOpen */
        &data_ov004_022501d0, /* Bromide_EnterTalk */
        &data_ov004_022501c8, /* Bromide_EnterTalkEnd */
    };
    MemberTable_InitOnce(&data_ov004_02257090, data_ov004_0225730c, entries, BROMIDE_STATE_COUNT);
    if (state < BROMIDE_STATE_COUNT && MemberPointer_CallInt(&data_ov004_0225730c[state], bromide) != 0) {
        bromide->state = state;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov004_02213590, Bromide_EnterState)

/* func_ov004_0221362c (vtable slot 0x4c): the scene's answer to func_0203e0a8; event 1 opens
 * the bromide, event 8 makes it idle, others do nothing. */
void Bromide_OnSceneEvent(Bromide *bromide, int event)
{
    switch (event) {
        case BROMIDE_EVENT_OPEN:
            Bromide_EnterState(bromide, BROMIDE_OPEN);
            break;
        case BROMIDE_EVENT_IDLE:
            Bromide_EnterState(bromide, BROMIDE_IDLE);
            break;
    }
}
CLEAN_AS(func_ov004_0221362c, Bromide_OnSceneEvent)

/* func_ov004_02213650 (vtable slot 0x0c) */
int Bromide_Vfunc0C(void)
{
    return 1;
}
CLEAN_AS(func_ov004_02213650, Bromide_Vfunc0C)

/* _ZN18Obj_ov004_02251b4019func_ov004_02213654Ev (vtable slot 0x80, each frame while neither
 * appearing nor vanishing): the state's update. */
int Bromide_Update(Bromide *bromide)
{
    Bromide_UpdateState(bromide);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov004_02251b4019func_ov004_02213654Ev, Bromide_Update)

/* func_ov004_02213664 (vtable slot 0x7c, once the model is bound): done at once. The state is
 * left as the allocation zeroed it: BROMIDE_IDLE, without its entry having run. */
int Bromide_Start(void)
{
    return 1;
}
CLEAN_AS(func_ov004_02213664, Bromide_Start)

static void Bromide_set_vtables(Bromide *bromide)
{
    bromide->base.vtable = (const RoomObjectVtable *) data_ov004_02251b40;
    bromide->base.receiver_vtable = data_ov004_02251bec;
}

/* func_ov004_02213668 (the deleting destructor, vtable slot 0x44) */
Bromide *Bromide_Delete(Bromide *bromide)
{
    Bromide_set_vtables(bromide);
    RoomObject_DestructBase(&bromide->base);
    RoomObject_Free(bromide);
    return bromide;
}
CLEAN_AS(func_ov004_02213668, Bromide_Delete)

/* func_ov004_02213694 (the destructor, vtable slot 0x40) */
Bromide *Bromide_Destroy(Bromide *bromide)
{
    Bromide_set_vtables(bromide);
    RoomObject_DestructBase(&bromide->base);
    return bromide;
}
CLEAN_AS(func_ov004_02213694, Bromide_Destroy)

/* func_ov004_022136b8 (the constructor). Its state is left as the allocation zeroed it. */
Bromide *Bromide_Construct(Bromide *bromide)
{
    RoomObject_ConstructBase(&bromide->base);
    Bromide_set_vtables(bromide);
    return bromide;
}
CLEAN_AS(func_ov004_022136b8, Bromide_Construct)

/* func_ov004_022136dc: a new bromide from the room's heap; nothing when it has no room. */
void Bromide_Create(void)
{
    Bromide *bromide = RoomObject_Alloc(BROMIDE_SIZE);
    if (bromide != NULL) {
        Bromide_Construct(bromide);
    }
}
CLEAN_AS(func_ov004_022136dc, Bromide_Create)
