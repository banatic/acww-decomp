/* The fox: its talk, the screen it opens and how it leaves (fox.h). */
#include "fox.h"

#include <stdint.h>

#include "autoload_2/heap.h"   /* Heap_FreeAux, Heap_AllocAuxZeroed */
#include "autoload_2/vector.h" /* Vec3 */
#include "clean.h"
#include "field_actor.h"       /* FieldActor_PlayerRequestState39 */
#include "main/calendar.h"     /* DateTime */
#include "main/group_params.h" /* GroupParams_CanOpen, GroupParams_C4CIs1, GroupParams_OpenWithArg */
#include "ov004/member_pointer.h"

static_assert(offsetof(Fox, receiver_vtable) == 0xec, "receiver");
static_assert(offsetof(Fox, message) == 0x10a, "receiver byte 0x1e");
static_assert(offsetof(Fox, link) == 0x12c, "link");
static_assert(offsetof(Fox, code) == 0x136, "code");
static_assert(offsetof(Fox, unk_22c) == 0x22c, "unk_22c");
static_assert(offsetof(Fox, flags_235) == 0x235, "flags 0x235");
static_assert(offsetof(Fox, flags) == 0x236, "flags");
static_assert(offsetof(Fox, state) == 0x2b4, "state");
static_assert(offsetof(Fox, frames) == 0x2b8, "frames");
static_assert(offsetof(Fox, asked) == 0x2ba, "asked");
static_assert(offsetof(Fox, hour) == 0x2bb, "hour");
static_assert(sizeof(Fox) == 0x2bc, "size");
static_assert(offsetof(FoxLink, unk_14) == 0x14, "link word 0x14");

#define FOX_RECEIVER_OFFSET 0xec

/* The scene events of vtable slot 0x4c. */
#define FOX_EVENT_TALK 0
#define FOX_EVENT_TALK_AGAIN 1
#define FOX_EVENT_BASE 6 /* handed to overlay 9's handler */
#define FOX_EVENT_IDLE 8

/* The messages it gives, and the ones whose end its receiver hears. */
#define FOX_MESSAGE_FIRST 0
#define FOX_MESSAGE_SCREEN 2     /* its end opens the screen */
#define FOX_MESSAGE_SCREEN_C4C 3 /* after the screen, when main's byte 0xc4c is 1; its end leaves */
#define FOX_MESSAGE_SCREEN_OTHER 4
#define FOX_MESSAGE_VISIT_2 0x31
#define FOX_MESSAGE_AGAIN 0x32 /* when func_020ae2c4 agrees; its end leaves */
#define FOX_MESSAGE_EARLY 0x34 /* before six */

#define FOX_LINK_SCREEN 5   /* the link's status FOX_SCREEN_ASK waits for */
#define FOX_SCREEN_MODE 0xe /* the mode of group 9 it opens */
#define FOX_HOUR_FROM 6
#define FOX_PLAYER_KIND 2 /* the kind of player state 0x39 it asks for */

/* "sp_npc_fox": the receiver's name and the speaker of its later messages. */
extern const char data_ov003_02238778[];
/* The vtables: the class's and its receiver part's. */
extern const u8 data_ov003_02238630[];
extern const u8 data_ov003_022386f4[];

/* The machine's tables (member_pointer.h): their guards, the tables and their constants. */
extern u32 data_ov003_0223c790;
extern MemberPointer data_ov003_0223c7f4[FOX_STATES];
extern const MemberPointer data_ov003_022385f0, data_ov003_02238590, data_ov003_02238598, data_ov003_022385a0,
    data_ov003_022385e0, data_ov003_02238600, data_ov003_02238570, data_ov003_02238588, data_ov003_022385a8,
    data_ov003_02238608;
extern u32 data_ov003_0223c794;
extern MemberPointer data_ov003_0223c7a4[FOX_STATES];
extern const MemberPointer data_ov003_02238578, data_ov003_02238580, data_ov003_022385d8, data_ov003_022385d0,
    data_ov003_022385c8, data_ov003_022385c0, data_ov003_022385b0, data_ov003_022385b8, data_ov003_022385e8,
    data_ov003_022385f8;

/* A block of the town's data; func_020ae3b8 gives the part at 8 of it. */
extern u8 data_021f3b30[];

extern int func_02096174(void);
extern int func_02096168(void);
extern void func_02095944(unsigned int arg);
/* Overlay 9's scene actor: its kind (from the character's code), something it counts by, the
 * point it stands at and the direction it faces (whether it has one), its event handler, its
 * destructor and its constructor. */
extern int func_ov009_02264c90(Fox *fox);
extern int func_ov009_022631b4(Fox *fox);
extern int func_ov009_0226321c(Fox *fox, Vec3 *point, s16 *angle);
extern void _ZN18Obj_ov009_022658dc19func_ov009_022633acEji(Fox *fox, unsigned int event, int arg);
extern void *func_ov009_0226539c(Fox *fox);
extern void *func_ov009_0226552c(Fox *fox);
/* Main's table at data_021f69d0 (func_020b5e10 gives it), whether it takes `id`, and adding to
 * it; the scene; a height that is always 0x200. */
extern void *func_020b5e10(void);
extern int func_020b6098(void *table, int id);
extern int func_020b5ea0(void *table, int scene, Vec3 *point, int p3, short angle, int p5, int p6);
extern u8 func_020b65c4(void);
extern int func_020310c8(int value);
/* Hands the receiver back, takes it, and lets the scene go on. */
extern void func_0203ee08(Fox *fox, void *receiver);
extern void func_0203ee14(Fox *fox, void *receiver);
extern int func_0203e020(Fox *fox);
extern int func_0203e0a8(Fox *fox, int arg);
/* Copies at most 25 characters of `name` into the receiver's name. */
extern void func_020a8164(void *receiver, const char *name);
extern void func_02066914(void *receiver, int arg);
/* Gives the link message `*message`, spoken by `name`. */
extern void func_0206844c(FoxLink *link, const u8 *message, const char *name);
/* The character's visit record: asking for it, its answer, clearing bit `bit` of its flags. */
extern void func_020b248c(u32 code);
extern int func_020b2470(u16 code);
extern void func_020b23ec(int code, int bit);
extern int func_020ae2c4(void);
extern int func_020ae270(void);
extern void *func_020ae3b8(void *block);
extern int func_020ae5f4(void *part);
/* A text of main (0x38 bytes): built by func_020ae774, destroyed by func_020ae75c; func_020ae614
 * loads into it from the part of data_021f3b30, and func_02068404 hands it to the link. */
extern void *func_020ae774(void *text);
extern void *func_020ae75c(void *text);
extern int func_020ae614(void *part, void *text);
extern void func_02068404(FoxLink *link, int index, void *text);
/* The clock's date and time (DateTime_Now). */
extern void func_0209e474(DateTime *now);

typedef struct FoxText {
    u32 words[0x38 / 4];
} FoxText;

/* The receiver part as C++ converts a pointer to the fox to it: NULL stays NULL. */
static void *fox_receiver(Fox *fox)
{
    return fox != NULL ? (u8 *) fox + FOX_RECEIVER_OFFSET : NULL;
}

/* The fox around its receiver part, as the receiver vtable's thunks find it. */
static Fox *fox_from_receiver(void *receiver)
{
    return (Fox *) (void *) ((u8 *) receiver - FOX_RECEIVER_OFFSET);
}

/* func_ov003_0221bac8 (update of FOX_GONE): counts the frames func_02096174 agrees on. From 15
 * of them (27 for kind 1, 20 for kind 2) on, when overlay 9 gives a point and main's table
 * takes the id func_ov009_022631b4 gives, it adds to the table at that point, one unit further
 * along z and at height func_020310c8 (0x200), turned half round, with the words at 0x22c and
 * 0x230, and sets FOX_FLAG_GONE.
 * QUIRK: the counter is 16 bits and wraps; nothing stops the update after the flag is set. */
void Fox_UpdateGone(Fox *fox)
{
    if (func_02096174()) {
        fox->frames++;
    }
    unsigned int wait = func_ov009_02264c90(fox) == 2 ? 20 : 15;
    if (func_ov009_02264c90(fox) == 1) {
        wait += 12;
    }
    if (fox->frames < wait) {
        return;
    }
    int id = func_ov009_022631b4(fox);
    Vec3 point;
    s16 angle;
    if (!func_ov009_0226321c(fox, &point, &angle)) {
        return;
    }
    if (!func_020b6098(func_020b5e10(), id)) {
        return;
    }
    point.y = func_020310c8(0);
    point.z += 0x1000;
    void *table = func_020b5e10();
    func_020b5ea0(table, func_020b65c4(), &point, 0x0f000000, (short) (angle + 0x8000), fox->unk_22c, fox->unk_230);
    fox->flags |= FOX_FLAG_GONE;
}
CLEAN_AS(func_ov003_0221bac8, Fox_UpdateGone)

/* func_ov003_0221bb9c (entry of FOX_GONE): the frame count starts again. */
int Fox_EnterGone(Fox *fox)
{
    fox->frames = 0;
    return 1;
}
CLEAN_AS(func_ov003_0221bb9c, Fox_EnterGone)

/* _ZN18Obj_ov003_0223863019func_ov003_0221bbacEv (update of FOX_WALK): on to FOX_GONE once
 * func_02096168 agrees. Until then, while the player has not been asked yet and overlay 9
 * gives a point, asks the player to stand there facing the direction it gives (player state
 * 0x39, kind 2), and remembers when the player agreed. */
void Fox_UpdateWalk(Fox *fox)
{
    if (func_02096168()) {
        Fox_SetState(fox, FOX_GONE);
        return;
    }
    if (fox->asked) {
        return;
    }
    Vec3 point;
    s16 angle;
    if (func_ov009_0226321c(fox, &point, &angle) &&
        FieldActor_PlayerRequestState39(FOX_PLAYER_KIND, (int *) &point.x, (int *) &point.z, angle)) {
        fox->asked = 1;
    }
}
CLEAN_AS(_ZN18Obj_ov003_0223863019func_ov003_0221bbacEv, Fox_UpdateWalk)

/* func_ov003_0221bc00 (entry of FOX_WALK) */
int Fox_EnterWalk(Fox *fox)
{
    fox->asked = 0;
    return 1;
}
CLEAN_AS(func_ov003_0221bc00, Fox_EnterWalk)

/* _ZN18Obj_ov003_0223863019func_ov003_0221bc10Ev (update of FOX_LEAVE): once func_02096174
 * agrees, moves to FOX_WALK and, when that worked, hands the receiver back. */
void Fox_UpdateLeave(Fox *fox)
{
    if (func_02096174() && Fox_SetState(fox, FOX_WALK)) {
        func_0203ee08(fox, fox_receiver(fox));
    }
}
CLEAN_AS(_ZN18Obj_ov003_0223863019func_ov003_0221bc10Ev, Fox_UpdateLeave)

/* func_ov003_0221bc3c (entry of FOX_LEAVE) */
int Fox_EnterLeave(Fox *fox)
{
    (void) fox;
    func_02095944(0);
    return 1;
}
CLEAN_AS(func_ov003_0221bc3c, Fox_EnterLeave)

/* _ZN18Obj_ov003_0223863019func_ov003_0221bc50Ev (update of FOX_TALK_CLOSE): on to FOX_LEAVE
 * once the link has closed. */
void Fox_UpdateTalkClose(Fox *fox)
{
    if (fox->link != NULL && fox->link->status == 0) {
        Fox_SetState(fox, FOX_LEAVE);
    }
}
CLEAN_AS(_ZN18Obj_ov003_0223863019func_ov003_0221bc50Ev, Fox_UpdateTalkClose)

/* func_ov003_0221bc74 (entry of FOX_TALK_CLOSE) */
int Fox_EnterTalkClose(Fox *fox)
{
    (void) fox;
    return 1;
}
CLEAN_AS(func_ov003_0221bc74, Fox_EnterTalkClose)

/* _ZN18Obj_ov003_0223863019func_ov003_0221bc78Ev (update of FOX_SCREEN): once the screen has
 * closed (GroupParams_CanOpen), gives the link message 3 after func_020ae270 when main's byte
 * 0xc4c is 1, else message 4, and ends the talk; after message 4 bit 0 of the character's
 * flags is cleared.
 * REQUIRES: the receiver has a link. */
void Fox_UpdateScreen(Fox *fox)
{
    if (!GroupParams_CanOpen()) {
        return;
    }
    u8 message;
    if (GroupParams_C4CIs1()) {
        func_020ae270();
        message = FOX_MESSAGE_SCREEN_C4C;
        func_0206844c(fox->link, &message, data_ov003_02238778);
        fox->link->requested = 1;
        Fox_SetState(fox, FOX_TALK_END);
    } else {
        message = FOX_MESSAGE_SCREEN_OTHER;
        func_0206844c(fox->link, &message, data_ov003_02238778);
        fox->link->requested = 1;
        Fox_SetState(fox, FOX_TALK_END);
        func_020b23ec(fox->code, 0);
    }
}
CLEAN_AS(_ZN18Obj_ov003_0223863019func_ov003_0221bc78Ev, Fox_UpdateScreen)

/* func_ov003_0221bcf8 (entry of FOX_SCREEN) */
int Fox_EnterScreen(Fox *fox)
{
    (void) fox;
    return 1;
}
CLEAN_AS(func_ov003_0221bcf8, Fox_EnterScreen)

/* _ZN18Obj_ov003_0223863019func_ov003_0221bcfcEv (update of FOX_SCREEN_ASK): once the link's
 * status is 5, opens group 9 in mode 0xe with func_020ae5f4 of the town's data as its argument
 * and moves to FOX_SCREEN, whether the screen opened or not.
 * REQUIRES: the receiver has a link. */
void Fox_UpdateScreenAsk(Fox *fox)
{
    if (fox->link->status == FOX_LINK_SCREEN) {
        GroupParams_OpenWithArg(FOX_SCREEN_MODE, func_020ae5f4(func_020ae3b8(data_021f3b30)));
        Fox_SetState(fox, FOX_SCREEN);
    }
}
CLEAN_AS(_ZN18Obj_ov003_0223863019func_ov003_0221bcfcEv, Fox_UpdateScreenAsk)

/* func_ov003_0221bd34 (entry of FOX_SCREEN_ASK) */
int Fox_EnterScreenAsk(Fox *fox)
{
    (void) fox;
    return 1;
}
CLEAN_AS(func_ov003_0221bd34, Fox_EnterScreenAsk)

/* func_ov003_0221bd38 (update of FOX_TALK_END): once the link has closed, hands the receiver
 * back and lets the scene go on. Its state stays FOX_TALK_END until the scene sets another. */
void Fox_UpdateTalkEnd(Fox *fox)
{
    if (fox->link != NULL && fox->link->status == 0) {
        func_0203ee08(fox, fox_receiver(fox));
        func_0203e020(fox);
    }
}
CLEAN_AS(func_ov003_0221bd38, Fox_UpdateTalkEnd)

/* func_ov003_0221bd68 (entry of FOX_TALK_END) */
int Fox_EnterTalkEnd(Fox *fox)
{
    (void) fox;
    return 1;
}
CLEAN_AS(func_ov003_0221bd68, Fox_EnterTalkEnd)

/* _ZN18Obj_ov003_0223863019func_ov003_0221bd6cEv (update of FOX_TALK): on to FOX_TALK_END
 * once the link has opened. */
void Fox_UpdateTalk(Fox *fox)
{
    if (fox->link != NULL && fox->link->status != 0) {
        Fox_SetState(fox, FOX_TALK_END);
    }
}
CLEAN_AS(_ZN18Obj_ov003_0223863019func_ov003_0221bd6cEv, Fox_UpdateTalk)

/* _ZN18Obj_ov003_0223863019func_ov003_0221bd90Ev (entry of FOX_TALK): takes the receiver,
 * names it "sp_npc_fox" and picks its message: FOX_MESSAGE_EARLY when vtable slot 0x8c
 * (Fox_IsAfterSix) says no, clearing bit 0 of the character's flags unless the visit record
 * said 2; else FOX_MESSAGE_VISIT_2 when it did, FOX_MESSAGE_AGAIN when func_020ae2c4 agrees,
 * else FOX_MESSAGE_FIRST. The link's request is raised and func_02066914 runs on the receiver.
 * REQUIRES: the receiver has a link once func_0203ee14 has taken it. */
int Fox_EnterTalk(Fox *fox)
{
    typedef int (*FoxSlot)(Fox *fox);

    func_0203ee14(fox, fox_receiver(fox));
    func_020a8164(&fox->receiver_vtable, data_ov003_02238778);
    FoxSlot after_six = (FoxSlot) (uintptr_t) *(const u32 *) ((const u8 *) fox->vtable + 0x8c);
    if (after_six(fox) == 0) {
        fox->message = FOX_MESSAGE_EARLY;
        if (!(fox->flags & FOX_FLAG_VISIT_2)) {
            func_020b23ec(fox->code, 0);
        }
    } else if (fox->flags & FOX_FLAG_VISIT_2) {
        fox->message = FOX_MESSAGE_VISIT_2;
    } else if (func_020ae2c4()) {
        fox->message = FOX_MESSAGE_AGAIN;
    } else {
        fox->message = FOX_MESSAGE_FIRST;
    }
    fox->link->requested = 1;
    func_02066914(&fox->receiver_vtable, 0);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov003_0223863019func_ov003_0221bd90Ev, Fox_EnterTalk)

/* _ZN18Obj_ov003_0223863019func_ov003_0221be34Ev (update of FOX_VISIT): once main has
 * answered (func_020b2470 nonzero), keeps whether the answer is 2 in FOX_FLAG_VISIT_2 and
 * starts the talk. */
void Fox_UpdateVisit(Fox *fox)
{
    int answer = func_020b2470(fox->code);
    if (answer != 0) {
        fox->flags = (u8) ((fox->flags & ~FOX_FLAG_VISIT_2) | (answer == 2 ? FOX_FLAG_VISIT_2 : 0));
        Fox_SetState(fox, FOX_TALK);
    }
}
CLEAN_AS(_ZN18Obj_ov003_0223863019func_ov003_0221be34Ev, Fox_UpdateVisit)

/* func_ov003_0221be7c (entry of FOX_VISIT): asks main for the character's visit record. */
int Fox_EnterVisit(Fox *fox)
{
    func_020b248c(fox->code);
    fox->flags &= (u8) ~FOX_FLAG_VISIT_2;
    return 1;
}
CLEAN_AS(func_ov003_0221be7c, Fox_EnterVisit)

/* func_ov003_0221bea4 (update of FOX_IDLE): func_0203e0a8 while bit 2 of the byte at 0x235 is
 * set. */
void Fox_UpdateIdle(Fox *fox)
{
    if (fox->flags_235 & 4) {
        func_0203e0a8(fox, 0);
    }
}
CLEAN_AS(func_ov003_0221bea4, Fox_UpdateIdle)

/* func_ov003_0221bec4 (entry of FOX_IDLE) */
int Fox_EnterIdle(Fox *fox)
{
    (void) fox;
    return 1;
}
CLEAN_AS(func_ov003_0221bec4, Fox_EnterIdle)

/* func_ov003_0221bec8: the state's update, through its table.
 * REQUIRES: the state is not negative (Fox_SetState only sets 0 to 9). */
void Fox_UpdateState(Fox *fox)
{
    static const MemberPointer *const updates[FOX_STATES] = {
        &data_ov003_022385f0, /* Fox_UpdateIdle */
        &data_ov003_02238590, /* Fox_UpdateVisit */
        &data_ov003_02238598, /* Fox_UpdateTalk */
        &data_ov003_022385a0, /* Fox_UpdateTalkEnd */
        &data_ov003_022385e0, /* Fox_UpdateScreenAsk */
        &data_ov003_02238600, /* Fox_UpdateScreen */
        &data_ov003_02238570, /* Fox_UpdateTalkClose */
        &data_ov003_02238588, /* Fox_UpdateLeave */
        &data_ov003_022385a8, /* Fox_UpdateWalk */
        &data_ov003_02238608, /* Fox_UpdateGone */
    };
    MemberTable_InitOnce(&data_ov003_0223c790, data_ov003_0223c7f4, updates, FOX_STATES);
    if (fox->state < FOX_STATES) {
        MemberPointer_CallVoid(&data_ov003_0223c7f4[fox->state], fox);
    }
}
CLEAN_AS(func_ov003_0221bec8, Fox_UpdateState)

/* _ZN18Obj_ov003_0223863019func_ov003_0221bfa8Ei: enters state `state` if its entry (through a
 * table) agrees; whether it did. States 10 and above do not exist.
 * REQUIRES: `state` is not negative. */
int Fox_SetState(Fox *fox, int state)
{
    static const MemberPointer *const entries[FOX_STATES] = {
        &data_ov003_02238578, /* Fox_EnterIdle */
        &data_ov003_02238580, /* Fox_EnterVisit */
        &data_ov003_022385d8, /* Fox_EnterTalk */
        &data_ov003_022385d0, /* Fox_EnterTalkEnd */
        &data_ov003_022385c8, /* Fox_EnterScreenAsk */
        &data_ov003_022385c0, /* Fox_EnterScreen */
        &data_ov003_022385b0, /* Fox_EnterTalkClose */
        &data_ov003_022385b8, /* Fox_EnterLeave */
        &data_ov003_022385e8, /* Fox_EnterWalk */
        &data_ov003_022385f8, /* Fox_EnterGone */
    };
    MemberTable_InitOnce(&data_ov003_0223c794, data_ov003_0223c7a4, entries, FOX_STATES);
    if (state < FOX_STATES && MemberPointer_CallInt(&data_ov003_0223c7a4[state], fox) != 0) {
        fox->state = state;
        return 1;
    }
    return 0;
}
CLEAN_AS(_ZN18Obj_ov003_0223863019func_ov003_0221bfa8Ei, Fox_SetState)

/* func_ov003_0221c098 (receiver slot 0x6c): always 0. */
int Fox_ReceiverSlot6C(Fox *fox)
{
    (void) fox;
    return 0;
}
CLEAN_AS(func_ov003_0221c098, Fox_ReceiverSlot6C)

/* func_ov003_0221c09c (receiver slot 0x18): nothing. */
void Fox_ReceiverSlot18(Fox *fox)
{
    (void) fox;
}
CLEAN_AS(func_ov003_0221c09c, Fox_ReceiverSlot18)

/* _ZN18Obj_ov003_0223863017vfunc_02066994_14Ev (receiver slot 0x14, also vtable slot 0x88):
 * after message 2 the link's word at 0x14 is set and the screen is asked for; after message 3
 * or 0x32 the talk closes.
 * REQUIRES: the receiver has a link when its message is 2. */
void Fox_OnMessageEnd(Fox *fox)
{
    switch (fox->message) {
        case FOX_MESSAGE_SCREEN:
            fox->link->unk_14 = 1;
            Fox_SetState(fox, FOX_SCREEN_ASK);
            break;
        case FOX_MESSAGE_SCREEN_C4C:
        case FOX_MESSAGE_AGAIN:
            Fox_SetState(fox, FOX_TALK_CLOSE);
            break;
        default:
            break;
    }
}
CLEAN_AS(_ZN18Obj_ov003_0223863017vfunc_02066994_14Ev, Fox_OnMessageEnd)

/* func_ov003_0221c0dc (receiver slot 0x10): while message 2 is shown, loads a text from the
 * part of the town's data at data_021f3b30 + 8 and, when it loaded, hands it to the link as
 * entry 0. */
void Fox_ReceiverSlot10(Fox *fox)
{
    if (fox->message != FOX_MESSAGE_SCREEN) {
        return;
    }
    FoxText text;
    func_020ae774(&text);
    if (func_020ae614(func_020ae3b8(data_021f3b30), &text) != 0) {
        func_02068404(fox->link, 0, &text);
    }
    func_020ae75c(&text);
}
CLEAN_AS(func_ov003_0221c0dc, Fox_ReceiverSlot10)

/* _ZN18Obj_ov003_0223863019func_ov003_0221c128Eji (vtable slot 0x4c): the scene's events: 0
 * and 1 start a visit, 8 makes the fox idle, 6 goes to overlay 9's handler; others do
 * nothing. */
void Fox_OnSceneEvent(Fox *fox, unsigned int event, int arg)
{
    switch (event) {
        case FOX_EVENT_BASE:
            _ZN18Obj_ov009_022658dc19func_ov009_022633acEji(fox, event, arg);
            break;
        case FOX_EVENT_TALK:
        case FOX_EVENT_TALK_AGAIN:
            Fox_SetState(fox, FOX_VISIT);
            break;
        case FOX_EVENT_IDLE:
            Fox_SetState(fox, FOX_IDLE);
            break;
        default:
            break;
    }
}
CLEAN_AS(_ZN18Obj_ov003_0223863019func_ov003_0221c128Eji, Fox_OnSceneEvent)

/* func_ov003_0221c16c (vtable slot 0x8c): whether both the clock's hour now and the hour
 * Fox_KeepHour kept are 6 or later. */
int Fox_IsAfterSix(Fox *fox)
{
    DateTime now = {0};
    func_0209e474(&now);
    return now.hour >= FOX_HOUR_FROM && fox->hour >= FOX_HOUR_FROM;
}
CLEAN_AS(func_ov003_0221c16c, Fox_IsAfterSix)

/* func_ov003_0221c1a4 (vtable slot 0x18): the state's update; always 1. */
int Fox_Update(Fox *fox)
{
    Fox_UpdateState(fox);
    return 1;
}
CLEAN_AS(func_ov003_0221c1a4, Fox_Update)

/* func_ov003_0221c1b4 (vtable slot 0x70): keeps the clock's hour now; always 1. */
int Fox_KeepHour(Fox *fox)
{
    DateTime now = {0};
    func_0209e474(&now);
    fox->hour = now.hour;
    return 1;
}
CLEAN_AS(func_ov003_0221c1b4, Fox_KeepHour)

/* The vtables set back, then overlay 9's destructor. */
static void fox_destroy_parts(Fox *fox)
{
    fox->vtable = data_ov003_02238630;
    fox->receiver_vtable = data_ov003_022386f4;
    func_ov009_0226539c(fox);
}

/* func_ov003_0221c1dc (the deleting destructor): the destructor's work, then the memory
 * freed. */
Fox *Fox_DestroyAndFree(Fox *fox)
{
    fox_destroy_parts(fox);
    Heap_FreeAux(fox);
    return fox;
}
CLEAN_AS(func_ov003_0221c1dc, Fox_DestroyAndFree)

/* func_ov003_0221c208: the destructor, without freeing. */
Fox *Fox_Destroy(Fox *fox)
{
    fox_destroy_parts(fox);
    return fox;
}
CLEAN_AS(func_ov003_0221c208, Fox_Destroy)

/* func_ov003_0221c22c: the constructor: overlay 9's, then the vtables. */
Fox *Fox_Construct(Fox *fox)
{
    func_ov009_0226552c(fox);
    fox->vtable = data_ov003_02238630;
    fox->receiver_vtable = data_ov003_022386f4;
    return fox;
}
CLEAN_AS(func_ov003_0221c22c, Fox_Construct)

/* func_ov003_0221c250: allocates and constructs one; nothing keeps the pointer here. */
void Fox_New(void)
{
    Fox *fox = Heap_AllocAuxZeroed(sizeof(Fox));
    if (fox != NULL) {
        Fox_Construct(fox);
    }
}
CLEAN_AS(func_ov003_0221c250, Fox_New)

/* ---- The receiver vtable's thunks: each finds the fox around `receiver`. */

/* _ZThn236_N18Obj_ov003_02238630D0Ev: Fox_DestroyAndFree. */
Fox *Fox_ReceiverDestroyAndFree(void *receiver)
{
    return Fox_DestroyAndFree(fox_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov003_02238630D0Ev, Fox_ReceiverDestroyAndFree)

/* _ZThn236_N18Obj_ov003_0223863017vfunc_02066994_6cEv: Fox_ReceiverSlot6C. */
int Fox_ReceiverThunk6C(void *receiver)
{
    return Fox_ReceiverSlot6C(fox_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov003_0223863017vfunc_02066994_6cEv, Fox_ReceiverThunk6C)

/* _ZThn236_N18Obj_ov003_0223863017vfunc_02066994_18Ev: Fox_ReceiverSlot18. */
void Fox_ReceiverThunk18(void *receiver)
{
    Fox_ReceiverSlot18(fox_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov003_0223863017vfunc_02066994_18Ev, Fox_ReceiverThunk18)

/* _ZThn236_N18Obj_ov003_0223863017vfunc_02066994_14Ev: Fox_OnMessageEnd. */
void Fox_ReceiverThunk14(void *receiver)
{
    Fox_OnMessageEnd(fox_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov003_0223863017vfunc_02066994_14Ev, Fox_ReceiverThunk14)

/* _ZThn236_N18Obj_ov003_0223863017vfunc_02066994_10Ev: Fox_ReceiverSlot10. */
void Fox_ReceiverThunk10(void *receiver)
{
    Fox_ReceiverSlot10(fox_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov003_0223863017vfunc_02066994_10Ev, Fox_ReceiverThunk10)

/* _ZThn236_N18Obj_ov003_02238630D1Ev: Fox_Destroy. */
Fox *Fox_ReceiverDestroy(void *receiver)
{
    return Fox_Destroy(fox_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov003_02238630D1Ev, Fox_ReceiverDestroy)
