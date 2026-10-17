/* The "obj_etc_museum" scene object (etc_museum.h). */
#include "etc_museum.h"

#include <stdint.h>

#include "autoload_2/approach.h" /* Math_AbsDiff16 */
#include "autoload_2/heap.h"
#include "clean.h"
#include "itcm/vector.h" /* Vec_Add */
#include "main/actor.h"
#include "main/event_queue.h"
#include "main/museum_record.h"
#include "main/name_texts.h"
#include "main/player_id.h"
#include "main/scene_query.h"
#include "main/session.h"
#include "main/session_players.h"
#include "main/talk_object.h"

static_assert(offsetof(EtcMuseum, base.position) == 0x5c, "position");
static_assert(offsetof(EtcMuseum, base.yaw) == 0x8e, "yaw");
static_assert(offsetof(EtcMuseum, receiver) == 0xec, "receiver");
static_assert(offsetof(EtcMuseum, receiver.base.message) == 0x10a, "receiver's message");
static_assert(offsetof(EtcMuseum, receiver.talk) == 0x12c, "receiver's talk");
static_assert(offsetof(EtcMuseum, state) == 0x134, "state");
static_assert(offsetof(EtcMuseum, sphere) == 0x138, "sphere");
static_assert(offsetof(EtcMuseum, index) == 0x154, "index");
static_assert(offsetof(EtcMuseum, current) == 0x155, "current");
static_assert(offsetof(EtcMuseum, face_angle) == 0x158, "face angle");
static_assert(offsetof(EtcMuseum, kind) == 0x15c, "kind");
static_assert(offsetof(EtcMuseum, complete_message) == 0x160, "complete message");
static_assert(offsetof(EtcMuseum, items) == 0x164, "items");
static_assert(offsetof(EtcMuseum, count) == 0x168, "count");
static_assert(offsetof(EtcMuseum, talks) == 0x16c, "talks");
static_assert(sizeof(EtcMuseum) == 0x170, "the size its constructor's caller allocates");

/* The profile (class id) Actor_Spawn makes one from. */
#define ETC_MUSEUM_PROFILE 0x19
/* How far away it can be talked to from, and the angle 0 of facing it. */
#define ETC_MUSEUM_TALK_DISTANCE 0x2333
/* The item the lone one tells the giver of. */
#define ETC_MUSEUM_LONE_ITEM 0x12e4

/* The messages of "obj_etc_museum" (the receiver's message). */
#define ETC_MUSEUM_MESSAGE_NONE_GIVEN 0      /* none of the exhibits given */
#define ETC_MUSEUM_MESSAGE_GIVEN 1           /* the current exhibit, by a player of the town */
#define ETC_MUSEUM_MESSAGE_GIVEN_BY_FORMER 2 /* the current exhibit, by a player who left */
#define ETC_MUSEUM_MESSAGE_LONE_GIVEN 3      /* the lone one: item 0x12e4 and its giver */
#define ETC_MUSEUM_MESSAGE_LONE_NOT_GIVEN 4  /* the lone one: nobody gave it */
#define ETC_MUSEUM_MESSAGE_ONE 5             /* one exhibit named (also group A's lone exhibit) */
#define ETC_MUSEUM_MESSAGE_TWO 6             /* two exhibits named */
#define ETC_MUSEUM_MESSAGE_THREE 7           /* three exhibits named */
/* The two answers offered when exhibits are left. */
#define ETC_MUSEUM_ANSWER_GO_ON 0xe5
#define ETC_MUSEUM_ANSWER_STOP 0xe6
/* The kind TalkObject_SetValue is given for an exhibit's name. */
#define ETC_MUSEUM_VALUE_KIND 7
/* What a talk's next state is set to to open it. */
#define ETC_MUSEUM_TALK_OPENING TALK_OBJECT_OPENING

/* The museum's record of who gave what. */
extern MuseumRecord data_021f38f8;
/* The ones by index, and how many there are; whether the lone one exists. */
extern EtcMuseum *data_ov004_0225797c[ETC_MUSEUM_MAX];
extern u8 data_ov004_02257908;
extern u8 data_ov004_02257904;
/* What the spawns leave for the object's creation (func_ov004_0221bd28) to read: its kind,
 * group A's message, its exhibits and their count, and its face angle. */
extern s32 data_ov004_02257914;
extern s16 data_ov004_0225337c;
extern const u8 *data_ov004_02257918;
extern s32 data_ov004_02257928;
extern s32 data_ov004_02257938;
/* Where the lone one is made (it moves before the player when it is created). */
extern Vec3 data_021fbee8;
/* "obj_etc_museum" */
extern const char data_ov004_022534cc[];
/* The message number that ends the talk (0xfe), and the "no message" byte (0xff). */
extern u8 data_021f43e8;
extern u8 data_021f43f8;

/* The receiver part, as a C++ conversion makes it: null stays null. */
static TalkReceiver *receiver_of(EtcMuseum *museum)
{
    return museum != NULL ? &museum->receiver : NULL;
}

/* The talk showing the receiver. */
static TalkObject *talk_of(EtcMuseum *museum)
{
    return (TalkObject *) (void *) museum->receiver.talk;
}

/* The message naming `left` exhibits, one to three: 5, 6 or 7.
 * QUIRK: none left (never asked) gives 5, from the ROM's (left - 1) % 3 + 5 on unsigned. */
static u8 count_message(unsigned int left)
{
    if (left > 3) {
        left = 3;
    }
    return (u8) ((left - 1) % 3 + ETC_MUSEUM_MESSAGE_ONE);
}

/* The message about the current exhibit of groups C and D: given by a player of the town or by
 * one who left. */
static u8 giver_message(EtcMuseum *museum)
{
    u16 item = museum->items[museum->current];
    if (MuseumRecord_Giver(&data_021f38f8, &item) != MUSEUM_BY_FORMER_PLAYER) {
        return ETC_MUSEUM_MESSAGE_GIVEN;
    }
    return ETC_MUSEUM_MESSAGE_GIVEN_BY_FORMER;
}

/* func_ov004_0221b1cc: makes the lone one (kind 4, no exhibits) unless it exists; what
 * Actor_Spawn gave, or 0 when it exists. */
int EtcMuseum_SpawnLone(void)
{
    if (data_ov004_02257904 == 0) {
        data_ov004_02257914 = ETC_MUSEUM_LONE;
        data_ov004_0225337c = 0;
        data_ov004_02257918 = NULL;
        data_ov004_02257928 = 0;
        data_ov004_02257938 = 0;
        return Actor_Spawn(ETC_MUSEUM_PROFILE, 0, &data_021fbee8, NULL, NULL);
    }
    return 0;
}
CLEAN_AS(func_ov004_0221b1cc, EtcMuseum_SpawnLone)

/* func_ov004_0221b224: makes one of `kind` at `position`, turned `yaw` about the vertical axis,
 * for the `count` exhibits numbered in `exhibits`; the rest is left for its creation. */
void EtcMuseum_Spawn(int kind, Vec3 *position, int yaw, int face_angle, s16 complete_message, const u8 *exhibits, int count)
{
    s16 angle[3];

    data_ov004_02257914 = kind;
    data_ov004_0225337c = complete_message;
    data_ov004_02257918 = exhibits;
    data_ov004_02257928 = count;
    data_ov004_02257938 = face_angle;
    angle[0] = 0;
    angle[1] = (s16) yaw;
    angle[2] = 0;
    Actor_Spawn(ETC_MUSEUM_PROFILE, 0, position, angle, NULL);
}
CLEAN_AS(func_ov004_0221b224, EtcMuseum_Spawn)

/* func_ov004_0221b27c: the one with `index`, or null when there is none or `index` is out of
 * 0-31. */
EtcMuseum *EtcMuseum_Get(int index)
{
    if (index >= 0 && index < ETC_MUSEUM_MAX) {
        return data_ov004_0225797c[index];
    }
    return NULL;
}
CLEAN_AS(func_ov004_0221b27c, EtcMuseum_Get)

/* func_ov004_0221b294: state 3's update: on to state 2 once the talk is up. */
void EtcMuseum_UpdateLoneTalk(EtcMuseum *museum)
{
    if (museum->receiver.talk != NULL && talk_of(museum)->state != TALK_OBJECT_CLOSED) {
        EtcMuseum_SetState(museum, ETC_MUSEUM_OPEN);
    }
}
CLEAN_AS(func_ov004_0221b294, EtcMuseum_UpdateLoneTalk)

/* func_ov004_0221b2b8: entering state 3 (always succeeds). The receiver is taken and named;
 * when a player of the town gave item 0x12e4 the message names it with the giver's name as
 * part 0, when nobody (or a player who left) did the message says so. The talk is asked to
 * open, and the talk counted.
 * QUIRK: when the record names a giver it then has no name for, the message is left as it
 * was. REQUIRES: the receiver has a talk. */
int EtcMuseum_EnterLoneTalk(EtcMuseum *museum)
{
    u16 item;

    SceneObjectBase_TakeReceiver(&museum->base, receiver_of(museum));
    MessageReceiver_SetName(&museum->receiver.base, data_ov004_022534cc);
    item = ETC_MUSEUM_LONE_ITEM;
    /* The ROM compares the answer unsigned. */
    if ((unsigned int) MuseumRecord_Giver(&data_021f38f8, &item) <= MUSEUM_BY_OTHER_PLAYER) {
        PlayerIdText name;
        PlayerIdText_Construct(&name);
        if (MuseumRecord_GiverName(&data_021f38f8, &name, &item) != 0) {
            museum->receiver.base.message = ETC_MUSEUM_MESSAGE_LONE_GIVEN;
            TalkObject_SetPart(talk_of(museum), 0, (TextBase *) (void *) &name);
        }
        PlayerIdText_Destruct(&name);
    } else {
        museum->receiver.base.message = ETC_MUSEUM_MESSAGE_LONE_NOT_GIVEN;
    }
    talk_of(museum)->next_state = ETC_MUSEUM_TALK_OPENING;
    museum->talks++;
    return 1;
}
CLEAN_AS(func_ov004_0221b2b8, EtcMuseum_EnterLoneTalk)

/* func_ov004_0221b354: state 2's update. Once the talk has closed, the receiver is released and
 * the event ends. */
void EtcMuseum_UpdateOpen(EtcMuseum *museum)
{
    if (museum->receiver.talk != NULL && talk_of(museum)->state == TALK_OBJECT_CLOSED) {
        SceneObjectBase_ReleaseReceiver(&museum->base, receiver_of(museum));
        EventQueue_FinishObjectEvent(museum);
    }
}
CLEAN_AS(func_ov004_0221b354, EtcMuseum_UpdateOpen)

/* func_ov004_0221b384: entering state 2 always succeeds. */
int EtcMuseum_EnterOpen(EtcMuseum *museum)
{
    (void) museum;
    return 1;
}
CLEAN_AS(func_ov004_0221b384, EtcMuseum_EnterOpen)

/* func_ov004_0221b388: state 1's update: on to state 2 once the talk is up. */
void EtcMuseum_UpdateTalk(EtcMuseum *museum)
{
    if (museum->receiver.talk != NULL && talk_of(museum)->state != TALK_OBJECT_CLOSED) {
        EtcMuseum_SetState(museum, ETC_MUSEUM_OPEN);
    }
}
CLEAN_AS(func_ov004_0221b388, EtcMuseum_UpdateTalk)

/* func_ov004_0221b3ac: entering state 1 (always succeeds). The first exhibit given becomes the
 * current one (the first of all when none is), the receiver is taken and named, and its message
 * picked:
 *   - none given: message 0;
 *   - group A: message 5 for a list of one, else the one it was made with;
 *   - groups C and B: the message naming the given exhibits left from the current one (5-7);
 *   - else: whether a player of the town or one who left gave the current one (1 or 2).
 * The talk is asked to open. REQUIRES: the receiver has a talk. */
int EtcMuseum_EnterTalk(EtcMuseum *museum)
{
    museum->current = 0;
    for (u32 i = 0; i < museum->count; i++) {
        u16 item = museum->items[i];
        if (MuseumRecord_IsGiven(&data_021f38f8, &item) != 0) {
            museum->current = (u8) i;
            break;
        }
    }
    SceneObjectBase_TakeReceiver(&museum->base, receiver_of(museum));
    MessageReceiver_SetName(&museum->receiver.base, data_ov004_022534cc);
    if (EtcMuseum_AnyGiven(museum) == 0) {
        museum->receiver.base.message = ETC_MUSEUM_MESSAGE_NONE_GIVEN;
    } else if (museum->kind == ETC_MUSEUM_GROUP_A) {
        if (museum->count == 1) {
            museum->receiver.base.message = ETC_MUSEUM_MESSAGE_ONE;
        } else {
            museum->receiver.base.message = (u8) museum->complete_message;
        }
    } else if (museum->kind <= ETC_MUSEUM_GROUP_B) {
        museum->receiver.base.message = count_message((unsigned int) EtcMuseum_CountGivenLeft(museum));
    } else {
        museum->receiver.base.message = giver_message(museum);
    }
    talk_of(museum)->next_state = ETC_MUSEUM_TALK_OPENING;
    return 1;
}
CLEAN_AS(func_ov004_0221b3ac, EtcMuseum_EnterTalk)

/* func_ov004_0221b4b0: state 0's update. Only the lone one acts: before its talk it asks for an
 * event about itself (EventQueue_RequestKind6), after it it asks to be deleted. */
void EtcMuseum_UpdateIdle(EtcMuseum *museum)
{
    if (EtcMuseum_IsLone(museum)) {
        if (museum->talks == 0) {
            EventQueue_RequestKind6(museum, 0);
        } else {
            Process_RequestDelete(&museum->base.process);
        }
    }
}
CLEAN_AS(func_ov004_0221b4b0, EtcMuseum_UpdateIdle)

/* func_ov004_0221b4e0: entering state 0 always succeeds. */
int EtcMuseum_EnterIdle(EtcMuseum *museum)
{
    (void) museum;
    return 1;
}
CLEAN_AS(func_ov004_0221b4e0, EtcMuseum_EnterIdle)

/* func_ov004_0221b4e4: the update of the current state (the ROM picks it from a table of member
 * function pointers). REQUIRES: the state is 0-3, as EtcMuseum_SetState leaves it; the ROM
 * reads before its table for a negative one, while this does nothing. */
void EtcMuseum_Update(EtcMuseum *museum)
{
    switch (museum->state) {
        case ETC_MUSEUM_IDLE:
            EtcMuseum_UpdateIdle(museum);
            break;
        case ETC_MUSEUM_TALK:
            EtcMuseum_UpdateTalk(museum);
            break;
        case ETC_MUSEUM_OPEN:
            EtcMuseum_UpdateOpen(museum);
            break;
        case ETC_MUSEUM_LONE_TALK:
            EtcMuseum_UpdateLoneTalk(museum);
            break;
        default:
            break;
    }
}
CLEAN_AS(_ZN18Obj_ov004_022533e019func_ov004_0221b4e4Ev, EtcMuseum_Update)

/* func_ov004_0221b570: moves to `state` when entering it succeeds; whether it did.
 * REQUIRES: `state` is not negative (the callers pass 0-3); the ROM reads before its table of
 * entry functions for a negative one, while this refuses it. */
int EtcMuseum_SetState(EtcMuseum *museum, int state)
{
    int entered;

    switch (state) {
        case ETC_MUSEUM_IDLE:
            entered = EtcMuseum_EnterIdle(museum);
            break;
        case ETC_MUSEUM_TALK:
            entered = EtcMuseum_EnterTalk(museum);
            break;
        case ETC_MUSEUM_OPEN:
            entered = EtcMuseum_EnterOpen(museum);
            break;
        case ETC_MUSEUM_LONE_TALK:
            entered = EtcMuseum_EnterLoneTalk(museum);
            break;
        default:
            return 0;
    }
    if (entered) {
        museum->state = state;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov004_0221b570, EtcMuseum_SetState)

/* func_ov004_0221b60c (the receiver's slot 0x18, the player's answer): on the first answer (go
 * on) the talk is given the next message about the current exhibit (as EtcMuseum_EnterTalk picks
 * it for groups C, B and the others), on the other the message that ends the talk. The lone one
 * ignores answers. */
void EtcMuseum_OnAnswer(EtcMuseum *museum)
{
    u8 message;

    if (EtcMuseum_IsLone(museum)) {
        return;
    }
    if (TalkAnswers_Picked(TalkObject_Answers(talk_of(museum))) == 0) {
        if (museum->kind <= ETC_MUSEUM_GROUP_B) {
            message = count_message((unsigned int) EtcMuseum_CountGivenLeft(museum));
        } else {
            message = giver_message(museum);
        }
    } else {
        message = data_021f43e8;
    }
    TalkObject_SetMessage(talk_of(museum), &message, NULL);
}
CLEAN_AS(func_ov004_0221b60c, EtcMuseum_OnAnswer)

/* func_ov004_0221b6d8 (the receiver's slot 0x14, a message ended). For group A: once every
 * exhibit is given, the message it was made with is followed by the next one; anything else
 * ends the talk. For the others: while given exhibits are left, the player is offered to go on
 * (answers 0xe5 and 0xe6, B picking the second) and the choices open; else the talk ends. The
 * lone one does nothing. */
void EtcMuseum_OnMessageEnded(EtcMuseum *museum)
{
    u8 message;

    if (EtcMuseum_IsLone(museum)) {
        return;
    }
    if (museum->kind == ETC_MUSEUM_GROUP_A) {
        u8 shown = museum->receiver.base.message;
        if (shown != ETC_MUSEUM_MESSAGE_ONE && EtcMuseum_AllGiven(museum) && museum->complete_message == shown) {
            message = (u8) (shown + 1);
        } else {
            message = data_021f43e8;
        }
        TalkObject_SetMessage(talk_of(museum), &message, NULL);
    } else if (EtcMuseum_CountGivenLeft(museum) != 0) {
        TalkAnswers *answers = TalkObject_Answers(talk_of(museum));
        if (answers != NULL) {
            u8 go_on = ETC_MUSEUM_ANSWER_GO_ON;
            u8 stop = ETC_MUSEUM_ANSWER_STOP;
            TalkAnswers_Reset(answers, 2, 1);
            TalkAnswers_Set(answers, 0, &go_on, 0, &data_021f43f8, NULL, 0);
            TalkAnswers_Set(answers, 1, &stop, 0, &data_021f43f8, NULL, 0);
            TalkAnswers_LoadTexts(answers);
            TalkObject_OpenChoices(talk_of(museum), 1);
        }
    } else {
        message = data_021f43e8;
        TalkObject_SetMessage(talk_of(museum), &message, NULL);
    }
}
CLEAN_AS(func_ov004_0221b6d8, EtcMuseum_OnMessageEnded)

/* The name of `item` set as the talk's value `index`. */
static void set_item_value(EtcMuseum *museum, int index, u16 *item, NameText *name)
{
    NameText_ConstructItem(name, item);
    TalkObject_SetValue(talk_of(museum), index, (TextBase *) (void *) name, ETC_MUSEUM_VALUE_KIND);
}

/* func_ov004_0221b808 (the receiver's slot 0x10, a message begins). For groups C and B the
 * message names one to three exhibits (messages 5-7): the names of that many, from the current
 * one on, become the talk's values 0-2, the current one moving on to the next given after each.
 * For the others, while the current one is in the list: its giver's name becomes part 0 and its
 * name value 0, and (but for group A) the current one moves on. The lone one does nothing. */
void EtcMuseum_OnMessageBegun(EtcMuseum *museum)
{
    if (EtcMuseum_IsLone(museum)) {
        return;
    }
    if (museum->kind <= ETC_MUSEUM_GROUP_B) {
        u32 named;
        switch (museum->receiver.base.message) {
            case ETC_MUSEUM_MESSAGE_ONE:
                named = 1;
                break;
            case ETC_MUSEUM_MESSAGE_TWO:
                named = 2;
                break;
            case ETC_MUSEUM_MESSAGE_THREE:
                named = 3;
                break;
            default:
                named = 0;
                break;
        }
        for (u32 i = 0; i < named; i++) {
            NameText name;
            u16 item = museum->items[museum->current];
            set_item_value(museum, (int) i, &item, &name);
            EtcMuseum_NextGiven(museum);
            NameText_Destruct(&name);
        }
    } else if (museum->current < museum->count) {
        PlayerIdText giver;
        NameText name;
        u16 item = museum->items[museum->current];
        PlayerIdText_Construct(&giver);
        MuseumRecord_GiverName(&data_021f38f8, &giver, &item);
        TalkObject_SetPart(talk_of(museum), 0, (TextBase *) (void *) &giver);
        set_item_value(museum, 0, &item, &name);
        if (museum->kind != ETC_MUSEUM_GROUP_A) {
            EtcMuseum_NextGiven(museum);
        }
        NameText_Destruct(&name);
        PlayerIdText_Destruct(&giver);
    }
}
CLEAN_AS(func_ov004_0221b808, EtcMuseum_OnMessageBegun)

/* func_ov004_0221b908 (vtable slot 0x4c): event 1 starts the lone talk (state 3), event 0 the
 * talk (state 1), event 8 stops (state 0); other events are ignored. */
void EtcMuseum_HandleEvent(EtcMuseum *museum, int event)
{
    switch (event) {
        case 1:
            EtcMuseum_SetState(museum, ETC_MUSEUM_LONE_TALK);
            break;
        case 0:
            EtcMuseum_SetState(museum, ETC_MUSEUM_TALK);
            break;
        case 8:
            EtcMuseum_SetState(museum, ETC_MUSEUM_IDLE);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov004_0221b908, EtcMuseum_HandleEvent)

/* func_ov004_0221b938 (vtable slot 0x48): whether `viewer` stands closer than 0x2333 and faces
 * it: its direction less than the face angle from the object's own turned half a turn. */
int EtcMuseum_IsFacedBy(EtcMuseum *museum, const SceneObjectBase *viewer)
{
    return viewer != NULL && Vec_DistanceXZ(&viewer->position, &museum->base.position) < ETC_MUSEUM_TALK_DISTANCE &&
           Math_AbsDiff16((s16) (museum->base.yaw + 0x8000), viewer->yaw) < museum->face_angle;
}
CLEAN_AS(func_ov004_0221b938, EtcMuseum_IsFacedBy)

/* func_ov004_0221b98c: whether it is the lone one. */
int EtcMuseum_IsLone(EtcMuseum *museum)
{
    return museum->kind == ETC_MUSEUM_LONE;
}
CLEAN_AS(func_ov004_0221b98c, EtcMuseum_IsLone)

/* func_ov004_0221b9a0: the current exhibit moves on to the next given one after it, or past
 * the end of the list (its count, as a byte) when none is. */
void EtcMuseum_NextGiven(EtcMuseum *museum)
{
    for (u32 i = museum->current + 1u; i < museum->count; i++) {
        u16 item = museum->items[i];
        if (MuseumRecord_IsGiven(&data_021f38f8, &item) != 0) {
            museum->current = (u8) i;
            return;
        }
    }
    museum->current = (u8) museum->count;
}
CLEAN_AS(func_ov004_0221b9a0, EtcMuseum_NextGiven)

/* func_ov004_0221b9f4: how many exhibits from the current one on have been given. */
int EtcMuseum_CountGivenLeft(EtcMuseum *museum)
{
    int given = 0;

    for (u32 i = museum->current; i < museum->count; i++) {
        u16 item = museum->items[i];
        if (MuseumRecord_IsGiven(&data_021f38f8, &item) != 0) {
            given++;
        }
    }
    return given;
}
CLEAN_AS(func_ov004_0221b9f4, EtcMuseum_CountGivenLeft)

/* func_ov004_0221ba40: whether every exhibit of the list has been given (also for an empty
 * list). */
int EtcMuseum_AllGiven(EtcMuseum *museum)
{
    for (u32 i = 0; i < museum->count; i++) {
        u16 item = museum->items[i];
        if (!MuseumRecord_IsGiven(&data_021f38f8, &item)) {
            return 0;
        }
    }
    return 1;
}
CLEAN_AS(func_ov004_0221ba40, EtcMuseum_AllGiven)

/* func_ov004_0221ba88: whether any exhibit of the list has been given. */
int EtcMuseum_AnyGiven(EtcMuseum *museum)
{
    for (u32 i = 0; i < museum->count; i++) {
        u16 item = museum->items[i];
        if (MuseumRecord_IsGiven(&data_021f38f8, &item) != 0) {
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_ov004_0221ba88, EtcMuseum_AnyGiven)

/* The first item code of each group (EtcMuseumKind 0-3) and how many numbers the group has;
 * the codes of groups D and A are 4 apart. */
#define ETC_MUSEUM_GROUP_C_FIRST 0x12b0
#define ETC_MUSEUM_GROUP_B_FIRST 0x12e8
#define ETC_MUSEUM_GROUP_D_FIRST 0x3894
#define ETC_MUSEUM_GROUP_A_FIRST 0x450c
#define ETC_MUSEUM_GROUP_C_COUNT 0x38
#define ETC_MUSEUM_GROUP_B_COUNT 0x38
#define ETC_MUSEUM_GROUP_D_COUNT 0x14
#define ETC_MUSEUM_GROUP_A_COUNT 0x34
#define ETC_MUSEUM_WIDE_STEP 4

/* The item code of exhibit `number` of a group: `first` plus `number` steps.
 * QUIRK: a number out of the group names the group's first item. */
static u16 exhibit_code(u8 number, unsigned int count, unsigned int step, unsigned int first)
{
    if (number < count) {
        return (u16) (first + number * step);
    }
    return (u16) first;
}

/* func_ov004_0221bad0: makes the list of item codes from the exhibit numbers the spawn left
 * (data_ov004_02257918), in a block of the current heap; whether it did. The lone one has no
 * list and succeeds.
 * QUIRK: for a kind other than 0-3 the block is kept (the object's `items`) but left unfilled,
 * and it fails. */
int EtcMuseum_MakeItems(EtcMuseum *museum)
{
    if (EtcMuseum_IsLone(museum)) {
        return 1;
    }
    museum->items = Heap_AllocCurrent((int) museum->count * (int) sizeof(u16));
    if (museum->items == NULL) {
        return 0;
    }
    switch (museum->kind) {
        case ETC_MUSEUM_GROUP_C:
            for (u32 i = 0; i < museum->count; i++) {
                museum->items[i] = exhibit_code(data_ov004_02257918[i], ETC_MUSEUM_GROUP_C_COUNT, 1, ETC_MUSEUM_GROUP_C_FIRST);
            }
            return 1;
        case ETC_MUSEUM_GROUP_B:
            for (u32 i = 0; i < museum->count; i++) {
                museum->items[i] = exhibit_code(data_ov004_02257918[i], ETC_MUSEUM_GROUP_B_COUNT, 1, ETC_MUSEUM_GROUP_B_FIRST);
            }
            return 1;
        case ETC_MUSEUM_GROUP_D:
            for (u32 i = 0; i < museum->count; i++) {
                museum->items[i] = exhibit_code(data_ov004_02257918[i], ETC_MUSEUM_GROUP_D_COUNT, ETC_MUSEUM_WIDE_STEP,
                                                ETC_MUSEUM_GROUP_D_FIRST);
            }
            return 1;
        case ETC_MUSEUM_GROUP_A:
            for (u32 i = 0; i < museum->count; i++) {
                museum->items[i] = exhibit_code(data_ov004_02257918[i], ETC_MUSEUM_GROUP_A_COUNT, ETC_MUSEUM_WIDE_STEP,
                                                ETC_MUSEUM_GROUP_A_FIRST);
            }
            return 1;
        default:
            return 0;
    }
}
CLEAN_AS(func_ov004_0221bad0, EtcMuseum_MakeItems)

/* func_ov004_0221bbf8: takes it out of the table; whether it was in it. For the lone one it
 * only notes that the lone one is gone (and answers 0).
 * QUIRK: the count is a byte and wraps below 0. */
int EtcMuseum_Unregister(EtcMuseum *museum)
{
    if (EtcMuseum_IsLone(museum)) {
        data_ov004_02257904 = 0;
        return 0;
    }
    if (museum->index < ETC_MUSEUM_MAX) {
        data_ov004_0225797c[museum->index] = NULL;
        data_ov004_02257908--;
        museum->index = ETC_MUSEUM_NO_INDEX;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov004_0221bbf8, EtcMuseum_Unregister)

/* func_ov004_0221bc44: enters it in the table under the next index (the count); whether there
 * was room (the index is kept even when there was not). The lone one gets no index and only
 * notes that it exists. */
int EtcMuseum_Register(EtcMuseum *museum)
{
    if (EtcMuseum_IsLone(museum)) {
        museum->index = ETC_MUSEUM_NO_INDEX;
        data_ov004_02257904 = 1;
        return 1;
    }
    museum->index = data_ov004_02257908;
    if (museum->index < ETC_MUSEUM_MAX) {
        data_ov004_0225797c[museum->index] = museum;
        data_ov004_02257908++;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov004_0221bc44, EtcMuseum_Register)

/* func_ov004_0221bc98: empties the table when none is counted in it. */
void EtcMuseum_ClearTableIfEmpty(void)
{
    if (data_ov004_02257908 != 0) {
        return;
    }
    for (int i = 0; i < ETC_MUSEUM_MAX; i++) {
        data_ov004_0225797c[i] = NULL;
    }
}
CLEAN_AS(func_ov004_0221bc98, EtcMuseum_ClearTableIfEmpty)

/* func_ov004_0221bcbc (vtable slot 0x0c, the deletion's work): takes it out of the table and
 * frees its list of item codes; done at once. The pointer to the list is left as it was. */
int EtcMuseum_OnDelete(EtcMuseum *museum)
{
    EtcMuseum_Unregister(museum);
    if (museum->items != NULL) {
        Heap_FreeCurrent(museum->items);
    }
    return 1;
}
CLEAN_AS(func_ov004_0221bcbc, EtcMuseum_OnDelete)

/* func_ov004_0221bcdc (vtable slot 0x24, the drawing): nothing to draw; done. */
int EtcMuseum_Draw(void)
{
    return 1;
}
CLEAN_AS(func_ov004_0221bcdc, EtcMuseum_Draw)

/* The radius it is picked in, and its touch pick kind (TouchPick_RoomEntry20). */
#define ETC_MUSEUM_PICK_RADIUS 0xc00
#define ETC_MUSEUM_TOUCH_KIND 14

/* func_ov004_0221bce0 (vtable slot 0x18, each frame): the state's update, then (but for the lone
 * one) its sphere of radius 0xc00 at its position put in the field's pen picking (kind 14, its
 * index); always 1. */
int EtcMuseum_Execute(EtcMuseum *museum)
{
    EtcMuseum_Update(museum);
    if (!EtcMuseum_IsLone(museum)) {
        TouchPick_SetSphereAndAdd((TouchPick *) (uintptr_t) SceneQuery_FieldObject(), &museum->sphere, &museum->base.position,
                                  ETC_MUSEUM_PICK_RADIUS, ETC_MUSEUM_TOUCH_KIND, museum->index);
    }
    return 1;
}
CLEAN_AS(_ZN18Obj_ov004_022533e019func_ov004_0221bce0Ev, EtcMuseum_Execute)

/* The field actor of this console's player (SessionPlayers_ActorHandle). */
#define ETC_MUSEUM_PLAYER_ACTOR 4

/* The sines and cosines of 4096 angles (NitroSDK's FX_SinCosTable_). */
extern const fx16 FX_SinCosTable_[];
/* The session, whose slot of this system goes into the object's id. */
extern NetSession *data_020ccf94;

/* func_ov004_0221bd28 (vtable slot 0x00, the creation's work): takes what the spawn left (kind,
 * group A's message, count and face angle) and enters it in the table (emptying the table first
 * when it holds none). When there was room: the lone one moves one unit before this console's
 * player, along the player's direction (when the player has a field actor); its id becomes its
 * session slot (2 bits), the current scene (6 bits) and its index (8 bits); it starts idle and
 * makes its list of item codes, whose success it answers. Fails when the table is full. */
int EtcMuseum_OnCreate(EtcMuseum *museum)
{
    EtcMuseum_ClearTableIfEmpty();
    museum->kind = (u32) data_ov004_02257914;
    museum->complete_message = data_ov004_0225337c;
    museum->count = (u32) data_ov004_02257928;
    museum->face_angle = data_ov004_02257938;
    if (!EtcMuseum_Register(museum)) {
        return 0;
    }
    if (EtcMuseum_IsLone(museum)) {
        int handle = SessionPlayers_ActorHandle(ETC_MUSEUM_PLAYER_ACTOR);
        if (handle != 0) {
            const SceneObjectBase *player = (const SceneObjectBase *) (uintptr_t) handle;
            unsigned int angle = (u16) player->yaw >> 4;
            Vec3 ahead;
            Vec3 point;
            ahead.x = FX_SinCosTable_[angle * 2];
            ahead.y = 0;
            ahead.z = FX_SinCosTable_[angle * 2 + 1];
            Vec_Add(&point, &player->position, &ahead);
            museum->base.position = point;
        }
    }
    u32 id = (u32) data_020ccf94->local_slot & 3;
    id |= ((u32) SceneQuery_Current() & 0x3f) << 2;
    id |= (u32) museum->index << 8;
    SceneObjectBase_SetId(&museum->base, id);
    EtcMuseum_SetState(museum, ETC_MUSEUM_IDLE);
    return EtcMuseum_MakeItems(museum);
}
CLEAN_AS(func_ov004_0221bd28, EtcMuseum_OnCreate)

/* The vtables: the class's, and its receiver part's. */
extern const u32 data_ov004_022533e0[];
extern const u8 data_ov004_02253454[];

static void set_vtables(EtcMuseum *museum)
{
    museum->base.process.vtable = data_ov004_022533e0;
    museum->receiver.base.vtable = data_ov004_02253454;
}

/* func_ov004_0221be28 (vtable slot 0x44, the deleting destructor): the sphere, the receiver part
 * and the base destroyed in turn, then the memory freed. */
EtcMuseum *EtcMuseum_Delete(EtcMuseum *museum)
{
    set_vtables(museum);
    TouchPickSphere_Destruct2(&museum->sphere);
    TalkReceiver_Destruct(&museum->receiver);
    SceneObjectBase_DestructBase(&museum->base);
    Heap_FreeAux(museum);
    return museum;
}
CLEAN_AS(func_ov004_0221be28, EtcMuseum_Delete)

/* func_ov004_0221be68 (vtable slot 0x40): the destructor, without freeing. */
EtcMuseum *EtcMuseum_Destroy(EtcMuseum *museum)
{
    set_vtables(museum);
    TouchPickSphere_Destruct2(&museum->sphere);
    TalkReceiver_Destruct(&museum->receiver);
    SceneObjectBase_DestructBase(&museum->base);
    return museum;
}
CLEAN_AS(func_ov004_0221be68, EtcMuseum_Destroy)

/* func_ov004_0221bea4: the constructor: the base and the receiver part, then the vtables and the
 * sphere. Its own fields are left as the allocation zeroed them. */
EtcMuseum *EtcMuseum_Construct(EtcMuseum *museum)
{
    SceneObjectBase_Construct(&museum->base);
    TalkReceiver_ConstructBase(&museum->receiver);
    set_vtables(museum);
    TouchPickSphere_Construct(&museum->sphere);
    return museum;
}
CLEAN_AS(func_ov004_0221bea4, EtcMuseum_Construct)

/* func_ov004_0221bedc: allocates (zeroed) and constructs one; nothing keeps the pointer here. */
void EtcMuseum_New(void)
{
    EtcMuseum *museum = Heap_AllocAuxZeroed(sizeof(EtcMuseum));
    if (museum != NULL) {
        EtcMuseum_Construct(museum);
    }
}
CLEAN_AS(func_ov004_0221bedc, EtcMuseum_New)

/* The object a pointer to its receiver part belongs to (the receiver vtable's entries move the
 * pointer back by 0xec, without a null check). */
static EtcMuseum *museum_of(void *receiver)
{
    return (EtcMuseum *) (void *) ((u8 *) receiver - offsetof(EtcMuseum, receiver));
}

/* func_ov004_0221bef8 (the receiver vtable's deleting destructor): EtcMuseum_Delete on the
 * object around `receiver`. */
EtcMuseum *EtcMuseumReceiver_Delete(void *receiver)
{
    return EtcMuseum_Delete(museum_of(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov004_022533e0D0Ev, EtcMuseumReceiver_Delete)

/* func_ov004_0221bf14 (the receiver's slot 0x18, the player's answer): EtcMuseum_OnAnswer. */
void EtcMuseumReceiver_OnAnswer(void *receiver)
{
    EtcMuseum_OnAnswer(museum_of(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov004_022533e017vfunc_02066994_18Ev, EtcMuseumReceiver_OnAnswer)

/* func_ov004_0221bf30 (the receiver's slot 0x14, a message ended): EtcMuseum_OnMessageEnded. */
void EtcMuseumReceiver_OnMessageEnded(void *receiver)
{
    EtcMuseum_OnMessageEnded(museum_of(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov004_022533e017vfunc_02066994_14Ev, EtcMuseumReceiver_OnMessageEnded)

/* func_ov004_0221bf4c (the receiver's slot 0x10, a message begins): EtcMuseum_OnMessageBegun. */
void EtcMuseumReceiver_OnMessageBegun(void *receiver)
{
    EtcMuseum_OnMessageBegun(museum_of(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov004_022533e017vfunc_02066994_10Ev, EtcMuseumReceiver_OnMessageBegun)

/* func_ov004_0221bf68 (the receiver vtable's destructor): EtcMuseum_Destroy on the object around
 * `receiver`. */
EtcMuseum *EtcMuseumReceiver_Destroy(void *receiver)
{
    return EtcMuseum_Destroy(museum_of(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov004_022533e0D1Ev, EtcMuseumReceiver_Destroy)
