/* The process that answers the START button (start_menu.h). */
#include "start_menu.h"

#include "autoload_2/heap.h"  /* Heap_FreeAux, Heap_OperatorDeleteB */
#include "autoload_2/input.h" /* PadState */
#include "clean.h"
#include "game_variables.h"
#include "player_pockets.h"
#include "player_record.h"
#include "player_records.h"
#include "quick_message.h"
#include "savings.h"
#include "session.h"
#include "session_link.h"

static_assert(sizeof(StartMenuReceiver) == 0x50 && offsetof(StartMenuReceiver, talk) == 0x40, "receiver");
static_assert(offsetof(StartMenuReceiver, owner) == 0x48 && offsetof(StartMenuReceiver, unk_4c) == 0x4c, "receiver");
static_assert(offsetof(StartMenu, state) == 0x50 && offsetof(StartMenu, receiver) == 0x54, "start menu");
static_assert(sizeof(StartMenu) == 0xa4 && sizeof(StartMenuStateFns) == 16, "start menu");

/* Vtables: the process's, its base class's, and the receiver's. */
extern const u32 data_020e3708[];
extern const u32 data_020da13c[];
extern const u32 data_020e3758[];

/* Each state's entry and update (filled at start-up, __sinit_020c66e0). */
extern StartMenuStateFns data_021f3ba4[START_MENU_STATES];

extern const char data_020e37d0[]; /* "sp_etc_sequence2" */
extern const char data_020e37e4[]; /* "sp_etc_sequence4" */
/* The message number that ends a talk, given with no file. */
extern u8 data_021f43e8;

extern PadState data_021fbe40;
extern NetSession *data_020ccf94;
extern u8 data_021c75b8;
/* The savings total each level of game variable 0x4c sets (1-21). */
extern const s32 data_020d1b98[];

/* The receiver's base class. */
extern StartMenuReceiver *func_02066a30(StartMenuReceiver *receiver); /* constructor */
extern void *func_02066994(StartMenuReceiver *receiver);              /* destructor */
extern void func_020a8164(StartMenuReceiver *receiver, const char *name);

/* The talks: talk `index`; unlinking its receiver; linking a receiver to it. */
extern StartMenuTalk *func_020682e0(int index);
extern void func_02068320(StartMenuTalk *talk);
extern void func_02068340(StartMenuTalk *talk, StartMenuReceiver *receiver);
extern void func_02068358(StartMenuTalk *talk);
extern void func_02068364(StartMenuTalk *talk, int value);
extern void func_02068388(StartMenuTalk *talk, int value);
extern void func_02068434(StartMenuTalk *talk);
extern void func_02068440(StartMenuTalk *talk);
/* Gives the talk message `*message` of file `name`. */
extern void func_0206844c(StartMenuTalk *talk, const u8 *message, const char *name);
/* A talk's choices (at 0x31c of the talk): the one taken, and setting them up. */
extern void *func_0206837c(StartMenuTalk *talk);
extern u32 func_020ab504(void *choices);
extern void func_020ab5f8(void *choices);
extern void func_020ab628(void *choices, int index, const u8 *message, int a, const u8 *b, int c, int d);
extern void func_020ab670(void *choices, int count, int a);

/* Main's event queue (func_020b5e10 gives it): posting an event. */
extern void *func_020b5e10(void);
extern int func_020b6434(void *queue, u8 event, u8 a, u8 b);
extern int func_020b5ee4(void *queue, int value);

extern int func_0203e21c(void);
extern int func_0203e228(void);
extern int func_0203e31c(void);
extern int func_0203e340(void);
extern int func_0203ec98(void);
extern void func_0203e210(void);
extern u8 func_020b65c4(void); /* the scene */
extern int func_020a12c0(void);
extern int func_020a12d4(void);
extern void func_020a18ac(void);
extern void func_020a1948(void);
extern void func_020a01e0(u8 value);
extern void func_020a6ef0(void *object);
extern void *func_020a6f00(void);
extern void func_020a6f20(int a, int b);

#define PAD_START 0x0008
#define SCENE_45 45 /* a scene in which START does nothing */
#define START_MENU_EVENT 46
#define START_MENU_TALK_INDEX 0
#define START_MENU_STATUS_TIMER 200 /* StartMenuReceiver.unk_4c when a status is sent */

/* The messages of the talk. */
enum StartMenuMessage {
    START_MENU_ASK = 0,        /* "sp_etc_sequence2", alone */
    START_MENU_ASK_LINKED = 4, /* "sp_etc_sequence4" in modes 1 and 2, else "sp_etc_sequence2" */
    START_MENU_REFUSED = 5,    /* "sp_etc_sequence2": the session answered 6 */
    START_MENU_ASK_AGAIN = 8,  /* "sp_etc_sequence2": after a no to START_MENU_ASK_LINKED */
};

/* The local statuses the session answers with. */
#define SESSION_STATUS_AGREED 5
#define SESSION_STATUS_REFUSED 6

/* `fn` called on `object` (MemberFn, autoload_2/process.h). */
static void call_member(const MemberFn *fn, void *object)
{
    uintptr_t self = (uintptr_t) object + (uintptr_t) (intptr_t) ((fn->adj - (fn->adj & 1)) / 2);
    uintptr_t target = fn->ptr;
    if ((fn->adj & 1) != 0) {
        uintptr_t vtable = *(const u32 *) self;
        target = *(const u32 *) (vtable + fn->ptr);
    }
    ((void (*)(void *)) target)((void *) self);
}

/* func_0209f374: the destructor. */
StartMenu *StartMenu_Destruct(StartMenu *menu)
{
    menu->process.vtable = data_020e3708;
    StartMenuReceiver_Destruct(&menu->receiver);
    menu->process.vtable = data_020da13c;
    Process_Destruct(&menu->process);
    return menu;
}
CLEAN_AS(func_0209f374, StartMenu_Destruct)

/* func_0209f3a0: the destructor, then the object freed. */
StartMenu *StartMenu_DestructFree(StartMenu *menu)
{
    menu->process.vtable = data_020e3708;
    StartMenuReceiver_Destruct(&menu->receiver);
    menu->process.vtable = data_020da13c;
    Process_Destruct(&menu->process);
    Heap_FreeAux(menu);
    return menu;
}
CLEAN_AS(func_0209f3a0, StartMenu_DestructFree)

/* func_0209f3d0 (receiver slot 6): the answer to the talk's question. To START_MENU_ASK_LINKED,
 * yes (0) ends the talk and sends local status 2, no (1) asks START_MENU_ASK_AGAIN; to that,
 * yes ends the talk and sends local status 3, no ends it; to START_MENU_ASK, yes ends the talk
 * and leaves. */
void StartMenuReceiver_OnAnswer(StartMenuReceiver *receiver)
{
    StartMenuTalk *talk = receiver->talk;
    u32 answer = func_020ab504(func_0206837c(talk));
    u8 message;

    switch (receiver->message) {
        case START_MENU_ASK_LINKED:
            if (answer == 0) {
                func_02068440(talk);
                func_02068364(talk, 1);
                StartMenu_SetState(receiver->owner, START_MENU_WAIT_2);
            } else if (answer == 1) {
                message = START_MENU_ASK_AGAIN;
                func_0206844c(talk, &message, data_020e37d0);
            }
            break;
        case START_MENU_ASK_AGAIN:
            if (answer == 0) {
                func_02068440(talk);
                func_02068364(talk, 1);
                StartMenu_SetState(receiver->owner, START_MENU_WAIT_3);
            } else if (answer == 1) {
                func_0206844c(talk, &data_021f43e8, NULL);
            }
            break;
        case START_MENU_ASK:
            if (answer == 0) {
                func_0206844c(talk, &data_021f43e8, NULL);
                StartMenu_SetState(receiver->owner, START_MENU_LEAVE);
            }
            break;
    }
}
CLEAN_AS(func_0209f3d0, StartMenuReceiver_OnAnswer)

/* func_0209f47c (receiver slot 5): for START_MENU_ASK, the talk's two choices set up, messages
 * 0xc and 0xd. */
void StartMenuReceiver_SetUpChoices(StartMenuReceiver *receiver)
{
    if (receiver->message != START_MENU_ASK) {
        return;
    }
    StartMenuTalk *talk = receiver->talk;
    void *choices = func_0206837c(talk);
    func_020ab670(choices, 2, 1);
    u8 first[2] = {0xc, data_021f43e8};
    func_020ab628(choices, 0, &first[0], 1, &first[1], 0, 2);
    u8 second[2] = {0xd, data_021f43e8};
    func_020ab628(choices, 1, &second[0], 1, &second[1], 0, 0);
    func_020ab5f8(choices);
    func_02068388(talk, 1);
}
CLEAN_AS(func_0209f47c, StartMenuReceiver_SetUpChoices)

/* func_0209f4fc */
void StartMenuReceiver_SetOwner(StartMenuReceiver *receiver, StartMenu *owner)
{
    receiver->owner = owner;
}
CLEAN_AS(func_0209f4fc, StartMenuReceiver_SetOwner)

/* func_0209f500: the destructor, then the object freed. */
StartMenuReceiver *StartMenuReceiver_DestructFree(StartMenuReceiver *receiver)
{
    receiver->vtable = data_020e3758;
    func_02066994(receiver);
    Heap_OperatorDeleteB(receiver);
    return receiver;
}
CLEAN_AS(func_0209f500, StartMenuReceiver_DestructFree)

/* func_0209f520: the destructor. */
StartMenuReceiver *StartMenuReceiver_Destruct(StartMenuReceiver *receiver)
{
    receiver->vtable = data_020e3758;
    func_02066994(receiver);
    return receiver;
}
CLEAN_AS(func_0209f520, StartMenuReceiver_Destruct)

/* func_0209f538: the constructor. */
StartMenuReceiver *StartMenuReceiver_Construct(StartMenuReceiver *receiver)
{
    func_02066a30(receiver);
    receiver->vtable = data_020e3758;
    return receiver;
}
CLEAN_AS(func_0209f538, StartMenuReceiver_Construct)

/* The update of both waits: when the session answered (5 or 6), the talk's two flags reset;
 * on 5 event 0 is cleared, func_020a01e0 gets `choice`, the talk ends and the menu leaves; on
 * 6 the talk shows START_MENU_REFUSED. */
static void update_wait(StartMenu *menu, u8 choice)
{
    StartMenuTalk *talk = menu->receiver.talk;
    int status = Session_GetLocalStatus();
    if (status != SESSION_STATUS_AGREED && status != SESSION_STATUS_REFUSED) {
        return;
    }
    func_02068358(talk);
    func_02068434(talk);
    if (status == SESSION_STATUS_AGREED) {
        func_020a6f20(0, 6);
        func_020a6ef0(func_020a6f00());
        func_0206844c(talk, &data_021f43e8, NULL);
        func_020a01e0(choice);
        StartMenu_SetState(menu, START_MENU_LEAVE);
    } else {
        u8 message = START_MENU_REFUSED;
        func_0206844c(talk, &message, data_020e37d0);
        StartMenu_SetState(menu, START_MENU_TALK);
    }
    Session_FinishLocalStatus();
}

/* func_0209f550 (update of START_MENU_WAIT_3) */
void StartMenu_UpdateWait3(StartMenu *menu)
{
    update_wait(menu, 1);
}
CLEAN_AS(func_0209f550, StartMenu_UpdateWait3)

/* func_0209f5cc (entry of START_MENU_WAIT_3) */
void StartMenu_EnterWait3(StartMenu *menu)
{
    menu->receiver.unk_4c = START_MENU_STATUS_TIMER;
    Session_SendLocalStatus(3);
}
CLEAN_AS(func_0209f5cc, StartMenu_EnterWait3)

/* func_0209f5dc (update of START_MENU_WAIT_2) */
void StartMenu_UpdateWait2(StartMenu *menu)
{
    update_wait(menu, 0);
}
CLEAN_AS(func_0209f5dc, StartMenu_UpdateWait2)

/* func_0209f658 (entry of START_MENU_WAIT_2) */
void StartMenu_EnterWait2(StartMenu *menu)
{
    menu->receiver.unk_4c = START_MENU_STATUS_TIMER;
    Session_SendLocalStatus(2);
}
CLEAN_AS(func_0209f658, StartMenu_EnterWait2)

/* func_0209f668 (update of START_MENU_LEAVE): once the talk closed, it is let go and event 46
 * posted; in a linked session func_020b5ee4 and func_020a18ac follow, alone func_020a1948. */
void StartMenu_UpdateLeave(void)
{
    StartMenuTalk *talk = func_020682e0(START_MENU_TALK_INDEX);
    if (talk->state != 0) {
        return;
    }
    func_02068320(talk);
    func_020b6434(func_020b5e10(), START_MENU_EVENT, 2, 3);
    if (Session_IsLinked(data_020ccf94)) {
        func_020b5ee4(func_020b5e10(), 0);
        func_020a18ac();
    } else {
        func_020a1948();
    }
}
CLEAN_AS(func_0209f668, StartMenu_UpdateLeave)

/* func_0209f6b4 (entry of START_MENU_LEAVE) */
void StartMenu_EnterLeave(void) {}
CLEAN_AS(func_0209f6b4, StartMenu_EnterLeave)

/* func_0209f6b8 (update of START_MENU_TALK): once the talk closed, it is let go,
 * func_0203e210 called, and the menu is idle again. */
void StartMenu_UpdateTalk(StartMenu *menu)
{
    StartMenuTalk *talk = func_020682e0(START_MENU_TALK_INDEX);
    if (talk->state == 0) {
        func_02068320(talk);
        func_0203e210();
        StartMenu_SetState(menu, START_MENU_IDLE);
    }
}
CLEAN_AS(func_0209f6b8, StartMenu_UpdateTalk)

/* func_0209f6e0 (entry of START_MENU_TALK) */
void StartMenu_EnterTalk(void) {}
CLEAN_AS(func_0209f6e0, StartMenu_EnterTalk)

/* func_0209f6e4 (update of START_MENU_OPEN): when func_0203e21c allows, the receiver (after its
 * vtable slot 2) is given its question and handed to talk 0, which is asked to start; else
 * the menu is idle again. */
void StartMenu_UpdateOpen(StartMenu *menu)
{
    if (func_0203e21c() == 0) {
        StartMenu_SetState(menu, START_MENU_IDLE);
        return;
    }
    StartMenuTalk *talk = func_020682e0(START_MENU_TALK_INDEX);
    StartMenuReceiver *receiver = &menu->receiver;
    ((void (*)(StartMenuReceiver *))(uintptr_t) receiver->vtable[2])(receiver);
    if (func_020a12d4() != 0 || func_020a12c0() != 0) {
        func_020a8164(receiver, data_020e37e4);
        receiver->message = START_MENU_ASK_LINKED;
    } else if (Session_IsLinked(data_020ccf94)) {
        func_020a8164(receiver, data_020e37d0);
        receiver->message = START_MENU_ASK_LINKED;
    } else {
        func_020a8164(receiver, data_020e37d0);
        receiver->message = START_MENU_ASK;
    }
    func_02068340(talk, receiver);
    talk->request = 1;
    StartMenu_SetState(menu, START_MENU_TALK);
}
CLEAN_AS(func_0209f6e4, StartMenu_UpdateOpen)

/* func_0209f790 (entry of START_MENU_OPEN) */
void StartMenu_EnterOpen(void) {}
CLEAN_AS(func_0209f790, StartMenu_EnterOpen)

/* func_0209f794 (update of START_MENU_IDLE): START opens the menu, but not in scene 45, nor
 * while func_0203e31c, func_0203e340 or func_0203ec98 say so, only while data_021c75b8 is 2,
 * and when func_0203e228 allows. In a linked session a system not in slot 0 posts the
 * default quick message instead. */
void StartMenu_UpdateIdle(StartMenu *menu)
{
    if ((data_021fbe40.pressed & PAD_START) == 0) {
        return;
    }
    if (func_020b65c4() == SCENE_45 || func_0203e31c() != 0 || func_0203e340() != 0) {
        return;
    }
    if (data_021c75b8 != 2 || func_0203ec98() != 0) {
        return;
    }
    NetSession *session = data_020ccf94;
    if (Session_IsLinked(session) && Session_IsLocalSlot(session, 0) == 0) {
        QuickMessage_PostDefault();
        return;
    }
    if (func_0203e228() != 0) {
        StartMenu_SetState(menu, START_MENU_OPEN);
    }
}
CLEAN_AS(func_0209f794, StartMenu_UpdateIdle)

/* func_0209f81c (entry of START_MENU_IDLE) */
void StartMenu_EnterIdle(void) {}
CLEAN_AS(func_0209f81c, StartMenu_EnterIdle)

/* func_0209f820: the entry of `state` called (when it has one), then the state set. */
void StartMenu_SetState(StartMenu *menu, int state)
{
    const StartMenuStateFns *fns = &data_021f3ba4[state];
    if (fns->enter.ptr != 0) {
        call_member(&fns->enter, menu);
    }
    menu->state = (u32) state;
}
CLEAN_AS(func_0209f820, StartMenu_SetState)

/* Game variable `index` of bank 0, as the signed number the game reads. */
static s16 variable(u16 index)
{
    return (s16) *GameVariables_Slot(0, index);
}

#define VARIABLE_BALANCE 0x4b /* 1-5: the savings balance set to one of five amounts */
#define VARIABLE_TOTAL 0x4c   /* a level (1-21) of data_020d1b98 the savings total is raised to */
#define VARIABLE_BELLS 0x48   /* bells added to the pockets, then cleared */
#define SAVINGS_TOTAL_LEVELS 21
#define POCKET_BELLS_MAX 99999

/* func_0209f858 (vtable slot 6): three game variables applied to the current player, then the
 * state's update called (when it has one); done.
 * QUIRK: the variables are read again after each check, and the bells variable is applied
 * without checking that there is a current player. */
int StartMenu_Execute(StartMenu *menu)
{
    static const s32 balances[] = {0, 1000000, 10000000, 100000000, 500000000, 999999999};

    u8 *record;
    if (variable(VARIABLE_BALANCE) != 0 && (record = PlayerRecords_Current()) != NULL) {
        SavingsAccount *account = PlayerRecord_Savings(record);
        int level = variable(VARIABLE_BALANCE);
        if (level >= 1 && level <= 5) {
            Savings_SetBalance(account, balances[level]);
        }
    }

    if (variable(VARIABLE_TOTAL) != 0 && (record = PlayerRecords_Current()) != NULL) {
        PlayerRecord_Savings(record);
        if (variable(VARIABLE_TOTAL) != 0) {
            int level = variable(VARIABLE_TOTAL);
            if (level < 1) {
                level = 1;
            } else if (level > SAVINGS_TOTAL_LEVELS) {
                level = SAVINGS_TOTAL_LEVELS;
            }
            s32 total = (s32) Savings_Total();
            if (data_020d1b98[level] > total) {
                Savings_SetTotal(data_020d1b98[level] - 100);
            }
        }
    }

    if (variable(VARIABLE_BELLS) != 0) {
        record = PlayerRecords_Current();
        int bells = PlayerPockets_Bells(PlayerRecord_Pockets(record), 1);
        bells += variable(VARIABLE_BELLS);
        if (bells < 0) {
            bells = 0;
        } else if (bells > POCKET_BELLS_MAX) {
            bells = POCKET_BELLS_MAX;
        }
        PlayerPockets_SetBells(PlayerRecord_Pockets(record), bells, 1);
        *GameVariables_Slot(0, VARIABLE_BELLS) = 0;
    }

    const StartMenuStateFns *fns = &data_021f3ba4[menu->state];
    if (fns->update.ptr != 0) {
        call_member(&fns->update, menu);
    }
    return 1;
}
CLEAN_AS(func_0209f858, StartMenu_Execute)
