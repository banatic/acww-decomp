/* The "obj_etc_museum" scene object (etc_museum.h). */
#include "etc_museum.h"

#include "autoload_2/approach.h" /* Math_AbsDiff16 */
#include "clean.h"
#include "main/actor.h"
#include "main/museum_record.h"
#include "main/name_texts.h"
#include "main/player_id.h"
#include "main/talk_object.h"

static_assert(offsetof(EtcMuseum, position) == 0x5c, "position");
static_assert(offsetof(EtcMuseum, yaw) == 0x8e, "yaw");
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
static_assert(offsetof(EtcMuseumViewer, position) == 0x5c, "viewer's position");
static_assert(offsetof(EtcMuseumViewer, yaw) == 0x8e, "viewer's yaw");

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

/* Whether any, or every, exhibit of the list has been given. */
extern int func_ov004_0221ba88(EtcMuseum *museum);
extern int func_ov004_0221ba40(EtcMuseum *museum);
/* The scene object's receiver taken (SceneObjectBase_TakeReceiver) and released
 * (SceneObjectBase_ReleaseReceiver), its event ended (EventQueue_FinishObjectEvent) and asked
 * for (EventQueue_RequestKind6), by symbol: their headers declare another MessageReceiver than
 * talk_receiver.h's. */
extern void func_0203ee14(EtcMuseum *museum, void *receiver);
extern void func_0203ee08(EtcMuseum *museum, void *receiver);
extern int func_0203e020(EtcMuseum *museum);
extern int func_0203e0a8(EtcMuseum *museum, int blocked);

/* The receiver part, as a C++ conversion makes it: null stays null. */
static void *receiver_of(EtcMuseum *museum)
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

    func_0203ee14(museum, receiver_of(museum));
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
        func_0203ee08(museum, receiver_of(museum));
        func_0203e020(museum);
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
    func_0203ee14(museum, receiver_of(museum));
    MessageReceiver_SetName(&museum->receiver.base, data_ov004_022534cc);
    if (func_ov004_0221ba88(museum) == 0) {
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
            func_0203e0a8(museum, 0);
        } else {
            Process_RequestDelete(&museum->process);
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
        if (shown != ETC_MUSEUM_MESSAGE_ONE && func_ov004_0221ba40(museum) && museum->complete_message == shown) {
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
int EtcMuseum_IsFacedBy(EtcMuseum *museum, const EtcMuseumViewer *viewer)
{
    return viewer != NULL && Vec_DistanceXZ(&viewer->position, &museum->position) < ETC_MUSEUM_TALK_DISTANCE &&
           Math_AbsDiff16((s16) (museum->yaw + 0x8000), viewer->yaw) < museum->face_angle;
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
