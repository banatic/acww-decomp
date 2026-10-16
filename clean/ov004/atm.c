/* The ATM of overlay 4 (atm.h). */
#include "atm.h"

#include <assert.h>
#include <stddef.h>

#include "clean.h"
#include "member_pointer.h"

static_assert(offsetof(Atm, position) == 0x5c, "position");
static_assert(offsetof(Atm, angle) == 0x8e, "angle");
static_assert(offsetof(Atm, receiver_vtable) == 0xec, "receiver part");
static_assert(offsetof(Atm, talk_state) == 0xec + 0x1e, "receiver state byte");
static_assert(offsetof(Atm, talk) == 0xec + 0x40, "receiver's conversation");
static_assert(offsetof(Atm, state) == 0x134, "state");
static_assert(offsetof(Atm, unk_138) == 0x138, "list entry");
static_assert(offsetof(Atm, unk_1d4) == 0x1d4, "entries");
static_assert(sizeof(Atm) == 0x47c, "the size Atm_Create allocates");

#define ATM_RECEIVER_OFFSET 0xec
#define ATM_SIZE 0x47c

/* The near distance func_020ea990 returns, and the angles (atm.h) that count as facing. */
#define ATM_TALK_DISTANCE 0x2333
#define HALF_TURN 0x8000
#define FACING_TOLERANCE 0x1000

/* The message bytes the conversation reads (at 0x1e77 in it). */
enum {
    ATM_MESSAGE_LEVEL_0 = 1,
    ATM_MESSAGE_LEVEL_ABOVE_0 = 2,
    ATM_MESSAGE_BELOW_TOP_LEVEL = 3,
    ATM_MESSAGE_CHOICE_2 = 4,
    ATM_MESSAGE_TOP_LEVEL = 5,
    ATM_MESSAGE_CHOICE_1 = 6
};

#define ATM_TOP_LEVEL 4

/* The events Atm_HandleEvent acts on. */
#define ATM_EVENT_TALK 0
#define ATM_EVENT_IDLE 8

/* The ATM's vtables, its receiver's name and its messages' name. */
extern const u8 data_ov004_0224fc4c[];
extern const u8 data_ov004_0224fcc0[];
extern const char *data_ov004_0224fbe0; /* "sp_npc_atm" */
extern const char *data_ov004_0224fbe4; /* "st_atm" */

/* The ATM that is set up (Atm_Init), else NULL. */
extern Atm *data_ov004_02256c00;

/* The state tables (member_pointer.h): their guards, the tables and their constants. */
extern u32 data_ov004_02256c04;
extern MemberPointer data_ov004_02256c24[ATM_STATE_COUNT];
extern const MemberPointer data_ov004_0224fc08, data_ov004_0224fbf8, data_ov004_0224fc10;
extern u32 data_ov004_02256c08;
extern MemberPointer data_ov004_02256c0c[ATM_STATE_COUNT];
extern const MemberPointer data_ov004_0224fbf0, data_ov004_0224fc00, data_ov004_0224fc18;

/* The conversation: the player's choice in it (at 0x31c + 0x2d8), its message and its text. */
extern void *func_0206837c(void *talk);
extern unsigned int func_020ab504(void *menu);
extern void func_0206844c(void *talk, const u8 *message, const char *name);
extern void func_02068404(void *talk, int slot, void *text);
extern int func_020683e4(void *talk, int slot, const void *bytes, const char *name);
extern void func_020a8164(void *receiver, const char *name);

/* The player's record, and the count in it. */
extern int func_020984e8(void);
extern unsigned int func_020996a0(unsigned int record);
extern u16 *func_020adf50(void *count);
extern int func_020adde4(unsigned int count);
extern u16 func_020adda8(u16 *count);

/* A number written as text into a 0x40-byte buffer. */
extern void *func_020b5630(void *text);
extern int func_020b45d0(void *text, int value, int a2, int a3, int a4, u8 a5);
extern void *func_020b5618(void *text);

/* The scene object's hooks. */
extern void func_0203ee08(Atm *atm, void *receiver);
extern int func_0203e020(Atm *atm);
extern void func_0203ee14(Atm *atm, void *receiver);
extern void func_0203efb0(Atm *atm, unsigned int value);
extern int func_02032180(void *entry);
extern int func_020321bc(void *entry, int a2, int a3, int a4, Vec3 *position, short a6, int *scale);
extern int func_020b6590(void);
extern int func_020b7dc8(int list, void *entries, Vec3 *position, int p3, int p4, int p5, short p6, int p7, u8 p8);
extern int func_020b7e04(int list, void *entries);
extern int func_020ea990(const Vec3 *a, const Vec3 *b);

/* Construction, destruction and the heap. */
extern void *func_0203f130(Atm *atm);
extern void *func_02066a30(void *receiver);
extern void *func_020324fc(void *entry);
extern void *func_020b82ec(void *entries);
extern void *func_020b82d0(void *entries);
extern void *func_020324c4(void *entry);
extern void *func_02066994(void *receiver);
extern void *func_0203f080(Atm *atm);
extern void func_020edf54(Atm *atm);
extern void *func_020edf70(int size);

/* The receiver part as C++ converts a pointer to the ATM to it: NULL stays NULL. */
static void *receiver_of(Atm *atm)
{
    return atm != NULL ? (u8 *) atm + ATM_RECEIVER_OFFSET : NULL;
}

/* The player's count (atm.h). */
static u16 *player_count(void)
{
    return func_020adf50((void *) (uintptr_t) func_020996a0((unsigned int) func_020984e8()));
}

static void show_message(Atm *atm, u8 message)
{
    func_0206844c(atm->talk, &message, data_ov004_0224fbe0);
}

/* func_ov004_0220bf00 (the receiver's slot 0x18): after the player chose in the conversation,
 * the message for the choice, while the receiver is in state 0 or 7. The choice is read
 * whatever the state. */
void Atm_PickChoiceMessage(Atm *atm)
{
    u8 talk_state = atm->talk_state;
    unsigned int choice = func_020ab504(func_0206837c(atm->talk));

    if (talk_state != 0 && talk_state != 7) {
        return;
    }
    switch (choice) {
        case 0:
            if (func_020adde4(*player_count()) == 0) {
                show_message(atm, ATM_MESSAGE_LEVEL_0);
            } else {
                show_message(atm, ATM_MESSAGE_LEVEL_ABOVE_0);
            }
            break;
        case 1:
            show_message(atm, ATM_MESSAGE_CHOICE_1);
            break;
        case 2:
            show_message(atm, ATM_MESSAGE_CHOICE_2);
            break;
    }
}
CLEAN_AS(func_ov004_0220bf00, Atm_PickChoiceMessage)

/* func_ov004_0220bfb4 (the receiver's slot 0x14): in receiver states 1 and 2, the message for
 * whether the count is at the top level. */
void Atm_PickLevelMessage(Atm *atm)
{
    if (atm->talk_state == 1 || atm->talk_state == 2) {
        if (func_020adde4(*player_count()) == ATM_TOP_LEVEL) {
            show_message(atm, ATM_MESSAGE_TOP_LEVEL);
        } else {
            show_message(atm, ATM_MESSAGE_BELOW_TOP_LEVEL);
        }
    }
}
CLEAN_AS(func_ov004_0220bfb4, Atm_PickLevelMessage)

/* func_ov004_0220c01c (the receiver's slot 0x10): nothing to do. */
void Atm_IgnoreReceiverHook(void *object)
{
    (void) object;
}
CLEAN_AS(func_ov004_0220c01c, Atm_IgnoreReceiverHook)

/* func_ov004_0220c020 (update of ATM_TALK_END): once the conversation's unk_04 is clear, hands
 * the receiver back to the scene object (func_0203ee08) and lets the scene go on. */
void Atm_UpdateTalkEnd(Atm *atm)
{
    if (atm->talk != NULL && atm->talk->unk_04 == 0) {
        func_0203ee08(atm, receiver_of(atm));
        func_0203e020(atm);
    }
}
CLEAN_AS(func_ov004_0220c020, Atm_UpdateTalkEnd)

/* func_ov004_0220c050 (entry of ATM_TALK_END) */
int Atm_EnterTalkEnd(Atm *atm)
{
    (void) atm;
    return 1;
}
CLEAN_AS(func_ov004_0220c050, Atm_EnterTalkEnd)

/* func_ov004_0220c054 (update of ATM_TALK) */
void Atm_UpdateTalk(Atm *atm)
{
    if (atm->talk != NULL && atm->talk->unk_04 != 0) {
        Atm_EnterState(atm, ATM_TALK_END);
    }
}
CLEAN_AS(func_ov004_0220c054, Atm_UpdateTalk)

/* func_ov004_0220c078 (entry of ATM_TALK): takes the receiver (func_0203ee14), names it,
 * resets its state byte, fills in the count and starts the conversation. */
int Atm_EnterTalk(Atm *atm)
{
    func_0203ee14(atm, receiver_of(atm));
    func_020a8164((u8 *) atm + ATM_RECEIVER_OFFSET, data_ov004_0224fbe0);
    atm->talk_state = 0;
    Atm_ShowCount(atm);
    atm->talk->unk_08 = 1;
    return 1;
}
CLEAN_AS(_ZN18Obj_ov004_0224fc4c19func_ov004_0220c078Ev, Atm_EnterTalk)

/* func_ov004_0220c0c0 (update of ATM_IDLE) */
void Atm_UpdateIdle(void) {}
CLEAN_AS(func_ov004_0220c0c0, Atm_UpdateIdle)

/* func_ov004_0220c0c4 (entry of ATM_IDLE) */
int Atm_EnterIdle(Atm *atm)
{
    (void) atm;
    return 1;
}
CLEAN_AS(func_ov004_0220c0c4, Atm_EnterIdle)

/* func_ov004_0220c0c8: the current state's update, through the table of Atm_UpdateIdle,
 * Atm_UpdateTalk and Atm_UpdateTalkEnd.
 * REQUIRES: the state is not negative (Atm_EnterState only sets 0 to 2). */
void Atm_UpdateState(Atm *atm)
{
    static const MemberPointer *const updates[ATM_STATE_COUNT] = {&data_ov004_0224fbf0, &data_ov004_0224fc00,
                                                                  &data_ov004_0224fc18};
    MemberTable_InitOnce(&data_ov004_02256c08, data_ov004_02256c0c, updates, ATM_STATE_COUNT);
    if (atm->state < ATM_STATE_COUNT) {
        MemberPointer_CallVoid(&data_ov004_02256c0c[atm->state], atm);
    }
}
CLEAN_AS(func_ov004_0220c0c8, Atm_UpdateState)

/* func_ov004_0220c144: enters `state` if its entry (Atm_EnterIdle, Atm_EnterTalk,
 * Atm_EnterTalkEnd, through a table) agrees; whether it did. States 3 and above do not exist.
 * REQUIRES: `state` is not negative. */
int Atm_EnterState(Atm *atm, int state)
{
    static const MemberPointer *const entries[ATM_STATE_COUNT] = {&data_ov004_0224fc08, &data_ov004_0224fbf8,
                                                                  &data_ov004_0224fc10};
    MemberTable_InitOnce(&data_ov004_02256c04, data_ov004_02256c24, entries, ATM_STATE_COUNT);
    if (state < ATM_STATE_COUNT && MemberPointer_CallInt(&data_ov004_02256c24[state], atm) != 0) {
        atm->state = state;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov004_0220c144, Atm_EnterState)

/* func_ov004_0220c1d0 (vtable slot 0x4c): event 0 starts the conversation, event 8 ends it;
 * others are ignored. */
void Atm_HandleEvent(Atm *atm, int event)
{
    switch (event) {
        case ATM_EVENT_TALK:
            Atm_EnterState(atm, ATM_TALK);
            break;
        case ATM_EVENT_IDLE:
            Atm_EnterState(atm, ATM_IDLE);
            break;
    }
}
CLEAN_AS(func_ov004_0220c1d0, Atm_HandleEvent)

/* func_ov004_0220c1f4 (vtable slot 0x48): whether `other` (a scene object, or NULL) is near
 * the ATM and turned towards it: its angle within 0x1000 of the opposite of the ATM's. */
int Atm_IsFacedBy(const Atm *atm, const Atm *other)
{
    if (other == NULL || func_020ea990(&other->position, &atm->position) >= ATM_TALK_DISTANCE) {
        return 0;
    }
    u16 difference = (u16) (other->angle - (atm->angle + HALF_TURN));
    return difference < FACING_TOLERANCE || difference >= (u16) -FACING_TOLERANCE;
}
CLEAN_AS(func_ov004_0220c1f4, Atm_IsFacedBy)

/* func_ov004_0220c250: writes the count into the conversation's text slots: the count (slot
 * 0), what is left to the next level (slot 1), the level less one when there is a level
 * (slot 2) and the level (slot 3). The level is asked for again each time. */
void Atm_ShowCount(Atm *atm)
{
    u8 text[0x40];
    u8 previous_level;
    u8 level;

    if (atm->talk == NULL) {
        return;
    }
    u16 *count = player_count();
    func_020b5630(text);
    func_020b45d0(text, *count, 10, 0, 0, 0);
    func_02068404(atm->talk, 0, text);
    func_020b45d0(text, func_020adda8(count), 10, 0, 0, 0);
    func_02068404(atm->talk, 1, text);
    if (func_020adde4(*count) != 0) {
        previous_level = (u8) (func_020adde4(*count) - 1);
        func_020683e4(atm->talk, 2, &previous_level, data_ov004_0224fbe4);
    }
    level = (u8) func_020adde4(*count);
    func_020683e4(atm->talk, 3, &level, data_ov004_0224fbe4);
    func_020b5618(text);
}
CLEAN_AS(func_ov004_0220c250, Atm_ShowCount)

/* func_ov004_0220c308: takes the ATM's entry out of the list at data_021c30e4; whether it was
 * there. */
int Atm_Unregister(Atm *atm)
{
    return func_02032180(atm->unk_138);
}
CLEAN_AS(func_ov004_0220c308, Atm_Unregister)

/* func_ov004_0220c318: puts the ATM's entry into the list at data_021c30e4 and sets up its
 * entries at 0x1d4, both at its position with sizes of 0x2000. */
void Atm_Register(Atm *atm)
{
    func_020321bc(atm->unk_138, 0x2000, 0x2000, 0x2000, &atm->position, 0, NULL);
    func_020b7dc8(func_020b6590(), atm->unk_1d4, &atm->position, 0x2000, 0x2000, 0x2000, 0, 0xb, 0xff);
}
CLEAN_AS(func_ov004_0220c318, Atm_Register)

/* func_ov004_0220c36c (vtable slot 0x0c) */
int Atm_Exit(Atm *atm)
{
    Atm_Unregister(atm);
    return 1;
}
CLEAN_AS(func_ov004_0220c36c, Atm_Exit)

/* func_ov004_0220c37c (vtable slot 0x24) */
int Atm_Vfunc24(void)
{
    return 1;
}
CLEAN_AS(func_ov004_0220c37c, Atm_Vfunc24)

/* func_ov004_0220c380 (vtable slot 0x18): the state's update, then the entries at 0x1d4. */
int Atm_Update(Atm *atm)
{
    Atm_UpdateState(atm);
    func_020b7e04(func_020b6590(), atm->unk_1d4);
    return 1;
}
CLEAN_AS(func_ov004_0220c380, Atm_Update)

/* func_ov004_0220c3a0 (vtable slot 0x00): becomes the current ATM and starts idle. */
int Atm_Init(Atm *atm)
{
    data_ov004_02256c00 = atm;
    func_0203efb0(atm, 0);
    Atm_EnterState(atm, ATM_IDLE);
    Atm_Register(atm);
    return 1;
}
CLEAN_AS(func_ov004_0220c3a0, Atm_Init)

static void destroy(Atm *atm)
{
    atm->vtable = data_ov004_0224fc4c;
    atm->receiver_vtable = data_ov004_0224fcc0;
    func_020b82d0(atm->unk_1d4);
    func_020324c4(atm->unk_138);
    func_02066994(&atm->receiver_vtable);
    func_0203f080(atm);
}

/* func_ov004_0220c3c8 (the deleting destructor) */
Atm *Atm_Delete(Atm *atm)
{
    destroy(atm);
    func_020edf54(atm);
    return atm;
}
CLEAN_AS(func_ov004_0220c3c8, Atm_Delete)

/* func_ov004_0220c414 (the destructor) */
Atm *Atm_Destroy(Atm *atm)
{
    destroy(atm);
    return atm;
}
CLEAN_AS(func_ov004_0220c414, Atm_Destroy)

/* func_ov004_0220c45c (the constructor). It leaves no ATM current until Atm_Init. */
Atm *Atm_Construct(Atm *atm)
{
    func_0203f130(atm);
    func_02066a30(&atm->receiver_vtable);
    atm->vtable = data_ov004_0224fc4c;
    atm->receiver_vtable = data_ov004_0224fcc0;
    func_020324fc(atm->unk_138);
    func_020b82ec(atm->unk_1d4);
    data_ov004_02256c00 = NULL;
    return atm;
}
CLEAN_AS(func_ov004_0220c45c, Atm_Construct)

/* func_ov004_0220c4ac */
Atm *Atm_Current(void)
{
    return data_ov004_02256c00;
}
CLEAN_AS(func_ov004_0220c4ac, Atm_Current)

/* func_ov004_0220c4b8: a new ATM from the heap (func_020edf70); nothing when that fails. */
void Atm_Create(void)
{
    Atm *atm = func_020edf70(ATM_SIZE);
    if (atm != NULL) {
        Atm_Construct(atm);
    }
}
CLEAN_AS(func_ov004_0220c4b8, Atm_Create)

/* The receiver's vtable (0x0224fcc0) enters the ATM's functions through these: each moves the
 * pointer back from the receiver part to the ATM and goes on with the ATM's function. */
static Atm *atm_of(void *receiver)
{
    return (Atm *) ((u8 *) receiver - ATM_RECEIVER_OFFSET);
}

/* func_ov004_0220c4d4 */
Atm *AtmReceiver_Delete(void *receiver)
{
    return Atm_Delete(atm_of(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov004_0224fc4cD0Ev, AtmReceiver_Delete)

/* func_ov004_0220c4f0 */
void AtmReceiver_PickChoiceMessage(void *receiver)
{
    Atm_PickChoiceMessage(atm_of(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov004_0224fc4c17vfunc_02066994_18Ev, AtmReceiver_PickChoiceMessage)

/* func_ov004_0220c50c */
void AtmReceiver_PickLevelMessage(void *receiver)
{
    Atm_PickLevelMessage(atm_of(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov004_0224fc4c17vfunc_02066994_14Ev, AtmReceiver_PickLevelMessage)

/* func_ov004_0220c528. The tools have no Native version of this thunk: it is checked by
 * reading. */
void AtmReceiver_IgnoreHook(void *receiver)
{
    Atm_IgnoreReceiverHook(atm_of(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov004_0224fc4c17vfunc_02066994_10Ev, AtmReceiver_IgnoreHook)

/* func_ov004_0220c544 */
Atm *AtmReceiver_Destroy(void *receiver)
{
    return Atm_Destroy(atm_of(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov004_0224fc4cD1Ev, AtmReceiver_Destroy)
