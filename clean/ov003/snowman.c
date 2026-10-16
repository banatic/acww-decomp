/* The snowman's talk (snowman.h). */
#include "snowman.h"

#include <stdint.h>

#include "autoload_2/vector.h" /* Vec_DistanceXZ */
#include "clean.h"
#include "main/text_label.h" /* TextVtable */
#include "ov004/member_pointer.h"

static_assert(offsetof(Snowman, position) == 0x5c, "position");
static_assert(offsetof(Snowman, receiver_vtable) == 0xec, "receiver");
static_assert(offsetof(Snowman, message) == 0x10a, "receiver byte 0x1e");
static_assert(offsetof(Snowman, link) == 0x12c, "link");
static_assert(offsetof(Snowman, flags) == 0x378, "flags");
static_assert(offsetof(Snowman, scene_state) == 0x39c, "first state");
static_assert(offsetof(Snowman, talk_state) == 0x3a0, "talk state");
static_assert(offsetof(SnowmanVisitor, position) == 0x5c, "visitor position");

#define SNOWMAN_RECEIVER_OFFSET 0xec

/* The scene events of vtable slot 0x4c. */
#define SNOWMAN_EVENT_TALK 0
#define SNOWMAN_EVENT_TALK_AGAIN 1
#define SNOWMAN_EVENT_IDLE 8

/* The first machine's state in which the snowman can be talked to. */
#define SNOWMAN_SCENE_STATE_READY 0xb

/* The speaker's name: message 0x26 of the archive "st_spnpc_name". */
#define SNOWMAN_NAME_MESSAGE 0x26

/* "sp_npc_snowman", the receiver's name, and "st_spnpc_name". */
extern const char data_ov003_0223838c[];
extern const char data_ov003_0223839c[];

/* The talk machine's tables (member_pointer.h): their guards, the tables and their constants. */
extern u32 data_ov003_0223c61c;
extern MemberPointer data_ov003_0223c63c[SNOWMAN_TALK_STATES];
extern const MemberPointer data_ov003_022381a8, data_ov003_02238168, data_ov003_022381f0;
extern u32 data_ov003_0223c620;
extern MemberPointer data_ov003_0223c624[SNOWMAN_TALK_STATES];
extern const MemberPointer data_ov003_02238198, data_ov003_022381e8, data_ov003_02238180;

extern void func_0203ee08(Snowman *snowman, void *receiver);
extern void func_0203ee14(Snowman *snowman, void *receiver);
extern int func_0203e020(Snowman *snowman);
extern void func_0203edd0(Snowman *snowman);
/* Copies at most 25 characters of `name` into the receiver's name. */
extern void func_020a8164(void *receiver, const char *name);
/* A random number below `range`. */
extern int func_020644cc(int range);
/* Sets the receiver's speaker name. */
extern void func_02066954(void *receiver, const char *name, int a);
/* A text label of main (vtable data_020e51d0, 0x118 bytes): built by func_020b55d0, destroyed
 * by func_020b55b8; func_020b4a20 loads message `*number` of a named archive into it. */
extern void *func_020b55d0(void *text);
extern void *func_020b55b8(void *text);
extern int func_020b4a20(void *text, char *number, const char *archive);
extern fx32 FX_Div(fx32 numerator, fx32 denominator);
extern fx32 FX_MulFunc(fx32 a, fx32 b);

typedef struct SnowmanNameText {
    const TextVtable *vtable;
    u8 unk_04[0x114];
} SnowmanNameText;

typedef const char *(*SnowmanTextBuffer)(void *text);

/* The receiver part as C++ converts a pointer to the snowman to it: NULL stays NULL. */
static void *snowman_receiver(Snowman *snowman)
{
    return snowman != NULL ? (u8 *) snowman + SNOWMAN_RECEIVER_OFFSET : NULL;
}

/* func_ov003_02219e64 (update of SNOWMAN_TALK_END): once the link has closed, hands the
 * receiver back (func_0203ee08) and lets the scene go on (func_0203e020). Its state stays
 * SNOWMAN_TALK_END until the scene sets another. */
void SnowmanTalk_UpdateEnd(Snowman *snowman)
{
    if (snowman->link != NULL && snowman->link->open == 0) {
        func_0203ee08(snowman, snowman_receiver(snowman));
        func_0203e020(snowman);
    }
}
CLEAN_AS(func_ov003_02219e64, SnowmanTalk_UpdateEnd)

/* func_ov003_02219e94 (entry of SNOWMAN_TALK_END) */
int SnowmanTalk_EnterEnd(void)
{
    return 1;
}
CLEAN_AS(func_ov003_02219e94, SnowmanTalk_EnterEnd)

/* func_ov003_02219e98 (update of SNOWMAN_TALK_OPEN): on once the link has opened. */
void SnowmanTalk_UpdateOpen(Snowman *snowman)
{
    if (snowman->link != NULL && snowman->link->open != 0) {
        SnowmanTalk_SetState(snowman, SNOWMAN_TALK_END);
    }
}
CLEAN_AS(func_ov003_02219e98, SnowmanTalk_UpdateOpen)

/* func_ov003_02219ebc (entry of SNOWMAN_TALK_OPEN): takes the receiver (func_0203ee14), names
 * it "sp_npc_snowman" and gives it one of the three messages of the snowman's kind, drawn at
 * random: 0-0xb while SNOWMAN_FLAG_FIRST_TALK is set, else 0xc-0x17. The link's request is
 * raised, the receiver's speaker name is set from "st_spnpc_name", and the flag is cleared.
 * REQUIRES: the receiver has a link once func_0203ee14 has taken it. */
int SnowmanTalk_EnterOpen(Snowman *snowman)
{
    func_0203ee14(snowman, snowman_receiver(snowman));
    int kind = (snowman->flags >> SNOWMAN_KIND_SHIFT) & 3;
    int message;
    if (snowman->flags & SNOWMAN_FLAG_FIRST_TALK) {
        message = func_020644cc(3) + kind * 3;
    } else {
        message = func_020644cc(3) + kind * 3 + 0xc;
    }
    func_020a8164(&snowman->receiver_vtable, data_ov003_0223838c);
    snowman->message = (u8) message;
    snowman->link->requested = 1;

    char number = SNOWMAN_NAME_MESSAGE;
    SnowmanNameText name;
    func_020b55d0(&name);
    func_020b4a20(&name, &number, data_ov003_0223839c);
    const char *text = ((SnowmanTextBuffer) (uintptr_t) name.vtable->buffer)(&name);
    func_02066954(&snowman->receiver_vtable, text, 0);
    snowman->flags &= (u16) ~SNOWMAN_FLAG_FIRST_TALK;
    func_020b55b8(&name);
    return 1;
}
CLEAN_AS(func_ov003_02219ebc, SnowmanTalk_EnterOpen)

/* func_ov003_02219f80 (update of SNOWMAN_TALK_IDLE) */
void SnowmanTalk_UpdateIdle(Snowman *snowman)
{
    (void) snowman;
}
CLEAN_AS(func_ov003_02219f80, SnowmanTalk_UpdateIdle)

/* func_ov003_02219f84 (entry of SNOWMAN_TALK_IDLE) */
int SnowmanTalk_EnterIdle(void)
{
    return 1;
}
CLEAN_AS(func_ov003_02219f84, SnowmanTalk_EnterIdle)

/* _ZN18Obj_ov003_022382ac19func_ov003_02219f88Ev: the talk state's update, through its table.
 * REQUIRES: the state is not negative (SnowmanTalk_SetState only sets 0 to 2). */
void SnowmanTalk_Update(Snowman *snowman)
{
    static const MemberPointer *const updates[SNOWMAN_TALK_STATES] = {
        &data_ov003_022381a8, /* SnowmanTalk_UpdateIdle */
        &data_ov003_02238168, /* SnowmanTalk_UpdateOpen */
        &data_ov003_022381f0, /* SnowmanTalk_UpdateEnd */
    };
    MemberTable_InitOnce(&data_ov003_0223c61c, data_ov003_0223c63c, updates, SNOWMAN_TALK_STATES);
    if (snowman->talk_state < SNOWMAN_TALK_STATES) {
        MemberPointer_CallVoid(&data_ov003_0223c63c[snowman->talk_state], snowman);
    }
}
CLEAN_AS(_ZN18Obj_ov003_022382ac19func_ov003_02219f88Ev, SnowmanTalk_Update)

/* func_ov003_0221a004: enters talk state `state` if its entry (through a table) agrees; whether
 * it did. States 3 and above do not exist.
 * REQUIRES: `state` is not negative. */
int SnowmanTalk_SetState(Snowman *snowman, int state)
{
    static const MemberPointer *const entries[SNOWMAN_TALK_STATES] = {
        &data_ov003_02238198, /* SnowmanTalk_EnterIdle */
        &data_ov003_022381e8, /* SnowmanTalk_EnterOpen */
        &data_ov003_02238180, /* SnowmanTalk_EnterEnd */
    };
    MemberTable_InitOnce(&data_ov003_0223c620, data_ov003_0223c624, entries, SNOWMAN_TALK_STATES);
    if (state < SNOWMAN_TALK_STATES && MemberPointer_CallInt(&data_ov003_0223c624[state], snowman) != 0) {
        snowman->talk_state = state;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov003_0221a004, SnowmanTalk_SetState)

/* func_ov003_0221a090 (vtable slot 0x4c): the scene's events: 0 and 1 start a talk (1 then
 * clears SNOWMAN_FLAG_FIRST_TALK, which the talk has already cleared when it started), 8 makes
 * the snowman idle; others do nothing. */
void SnowmanTalk_OnSceneEvent(Snowman *snowman, int event)
{
    switch (event) {
        case SNOWMAN_EVENT_TALK:
            SnowmanTalk_SetState(snowman, SNOWMAN_TALK_OPEN);
            break;
        case SNOWMAN_EVENT_TALK_AGAIN:
            SnowmanTalk_SetState(snowman, SNOWMAN_TALK_OPEN);
            snowman->flags &= (u16) ~SNOWMAN_FLAG_FIRST_TALK;
            break;
        case SNOWMAN_EVENT_IDLE:
            SnowmanTalk_SetState(snowman, SNOWMAN_TALK_IDLE);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov003_0221a090, SnowmanTalk_OnSceneEvent)

/* func_ov003_0221a0d4 (vtable slot 0x48): whether `visitor` stands closer than 2.5 (2 times
 * 500/400, computed with FX_Div and FX_MulFunc) to the snowman across the ground while the first
 * machine is in state 0xb. func_0203edd0 runs on the snowman first in any case. */
int SnowmanTalk_CanTalkTo(Snowman *snowman, const SnowmanVisitor *visitor)
{
    func_0203edd0(snowman);
    fx32 reach = FX_MulFunc(0x2000, FX_Div(0x7d000, 0x64000));
    return visitor != NULL && Vec_DistanceXZ(&visitor->position, &snowman->position) < reach &&
           snowman->scene_state == SNOWMAN_SCENE_STATE_READY;
}
CLEAN_AS(func_ov003_0221a0d4, SnowmanTalk_CanTalkTo)
