/* The insurance seller's talk scene: his lines, the insurance, the explanations and the
 * claims (insurer_talk.h). */
#include "insurer_talk.h"

#include <stdint.h>

#include "autoload_2/heap.h"
#include "clean.h"
#include "main/calendar.h"
#include "main/current_pockets.h"
#include "main/event_schedule.h"
#include "main/group_params.h"
#include "main/item_code.h"
#include "main/main_random.h"
#include "main/message_receiver.h"
#include "main/obj_020d9ff8.h"
#include "main/player_field_2416.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/pockets.h"
#include "main/scene_base.h"
#include "main/scene_bells.h"
#include "main/scene_command.h"
#include "main/screen_panels.h"
#include "main/talk_answers.h"
#include "main/talk_checks.h"
#include "main/talk_object.h"

static_assert(sizeof(SceneBase) == 0x80, "scene base");
static_assert(offsetof(InsurerTalk, first) == 0xb0, "first");
static_assert(offsetof(InsurerTalk, owner) == 0xb4, "owner");
static_assert(offsetof(InsurerTalk, explained_count) == 0xb8, "explained count");
static_assert(offsetof(InsurerTalk, sequence) == 0xbc, "sequence");
static_assert(offsetof(InsurerTalk, next_sequence) == 0xc4, "next sequence");
static_assert(sizeof(InsurerTalk) == 0xcc, "talk scene");
static_assert(sizeof(InsurerLine) == 8, "a line");
static_assert(offsetof(EventSchedule, fox_day) == 0x10, "the fox's weekday");
static_assert(sizeof(MessageReceiver) == 0x20 && offsetof(MessageReceiver, message) == 0x1e, "the line shown");

/* The talk scene's vtable. */
extern const u8 data_ov071_0227a1e8[];
/* The message file's name, "sp_npc_insurance". */
extern const char data_ov071_0227a180[];
/* The first lines (InsurerTalkFirst). */
extern const InsurerLine data_ov071_02279fbc[INSURER_TALK_FIRSTS];
/* The table of the talk's sequences (a function-local static, filled once from two constants;
 * bit 0 of data_ov071_0227a344 says it was). */
extern u32 data_ov071_0227a344;
extern MemberPointer data_ov071_0227a364[INSURER_TALK_SEQUENCES];
extern const MemberPointer data_ov071_0227a170, data_ov071_0227a130;
/* The null member pointer (the C++ runtime's). */
extern const MemberPointer __ptmf_null;
/* The event schedule (main's state block at 0x17218). */
extern EventSchedule data_021f39c0;

/* The claims' pocket test (InsurerTalk_IsClaimItem), handed on as the game's function. */
extern unsigned short func_ov071_022790f0(unsigned short *item, int state);

extern void MI_CpuFill8(void *dst, u8 value, u32 size);

/* The daily bit of the current player set once he pitched to the player today, and the player
 * record's flags of the insurance and of the cover. */
#define IT_DAILY_PITCHED 0x28
#define IT_FLAG_INSURED 0x17
#define IT_FLAG_COVERED 0x18

/* The prices, and the items the talk asks for with each (its motion of kind 14). */
#define IT_INSURANCE_PRICE 3000
#define IT_COVER_PRICE 6000
#define IT_INSURANCE_ITEM 0x149d
#define IT_COVER_ITEM 0x14a0

/* The explanations said in a row before the question that follows them. */
#define IT_EXPLANATIONS_IN_A_ROW 4

/* The answer of line 0x0c that bars his event for a week. */
#define IT_ANSWER_BAR 4

/* The claims: the items of these codes, the pockets' screen (SceneCommand_RequestScreen) and
 * the argument of its pocket test. */
#define IT_CLAIM_FIRST 0x3934
#define IT_CLAIM_LAST 0x3983
#define IT_POCKETS_SCREEN 0
#define IT_POCKETS_ARG 0x0d

/* The talk scene's vtable slot his talks call first. */
#define IT_TALK_SLOT_08 0x08

static u8 it_line_shown(const InsurerTalk *talk)
{
    return ((const MessageReceiver *) (const void *) talk)->message;
}

static TalkObject *it_talk_object(InsurerTalk *talk)
{
    return (TalkObject *) (void *) talk->base.talk;
}

static SceneCommandScene *it_scene(InsurerTalk *talk)
{
    return (SceneCommandScene *) (void *) talk;
}

/* Message `message` of "sp_npc_insurance" shown in `object`. */
static void it_say(TalkObject *object, u8 message)
{
    TalkObject_SetMessage(object, &message, data_ov071_0227a180);
}

static int it_owner_word(const InsurerTalk *talk)
{
    return (int) (u32) (uintptr_t) talk->owner;
}

static PocketPredicate it_claim_test(void)
{
    return (PocketPredicate) (void (*)(void)) func_ov071_022790f0;
}

/* Whether `item` is "nothing": an item with variants is compared without its variant. */
static int it_is_none(const u16 *item)
{
    if (ItemCode_HasVariant(item)) {
        u16 none = ITEM_CODE_NONE;
        int number = ItemCode_VariantItem(item);
        return number == ItemCode_VariantItem(&none);
    }
    return *item == ITEM_CODE_NONE;
}

/* The pockets' screen for a claim, with sequence 0 to take it. */
static void it_ask_claim(InsurerTalk *talk)
{
    SceneCommand_SetPocketPredicate(it_scene(talk), it_claim_test(), IT_POCKETS_ARG, 1);
    SceneCommand_RequestScreen(it_scene(talk), IT_POCKETS_SCREEN);
    InsurerTalk_SetSequence(talk, INSURER_TALK_SEQUENCE_CLAIM);
}

/* The price asked, once the player agreed (daily bit 0x28 set): 0x18 when the player can pay
 * it, else 0x16. */
static int it_ask_price(InsurerTalk *talk, int price)
{
    TalkChecks_TestSetDailyBit(IT_DAILY_PITCHED, 1);
    return SceneBells_CanPay(it_owner_word(talk), price) != 0 ? INSURER_LINE_CAN_PAY : INSURER_LINE_NO_BELLS;
}

/* func_ov071_02278ac4 (slot 0x18, the player's answer), by the line shown and the answer:
 * - 0x28-0x2c: the first answer 0x04, the second 0x02;
 * - 0x08: the fox's weekday is the answer plus 1 (EventSchedule.fox_day), and 0x09;
 * - 0x0c, answers 0-4: 0x0d, the explanations start afresh, and his event 0x3c is barred for
 *   the week from the Sunday after (answer 4) or no longer barred (EventSchedule_Bar3c);
 * - 0x15, 0x17, answered 0: the insurance's 3000 bells asked; 0x1d, 0x27: the cover's 6000;
 * - 0x20, 0x21, answered 0: 0x23;
 * - 0x23: the pockets' screen for a claim.
 * The line, when one was picked, is shown. */
void InsurerTalk_OnAnswer(InsurerTalk *talk)
{
    int answer = (int) TalkAnswers_Picked((TalkAnswers *) (uintptr_t) (u32) SceneBase_TalkChoices(&talk->base));
    int next = INSURER_NO_LINE;
    u8 line = it_line_shown(talk);

    switch (line) {
        case INSURER_LINE_GREETINGS:
        case INSURER_LINE_GREETINGS + 1:
        case INSURER_LINE_GREETINGS + 2:
        case INSURER_LINE_GREETINGS + 3:
        case INSURER_LINE_GREETINGS_LAST:
            if (answer == 0) {
                next = 0x04;
            } else if (answer == 1) {
                next = 0x02;
            }
            break;
        case INSURER_LINE_FOX_DAY:
            next = INSURER_LINE_FOX_DAY_TAKEN;
            data_021f39c0.fox_day = (u8) (answer + 1);
            break;
        case INSURER_LINE_BAR_EVENT:
            if (answer >= 0 && answer <= IT_ANSWER_BAR) {
                next = INSURER_LINE_EXPLAIN_START;
                MI_CpuFill8(talk->owner->explained, 0, INSURER_EXPLANATIONS);
                talk->explained_count = 0;
                EventSchedule_Bar3c(0, answer == IT_ANSWER_BAR ? 1 : 0);
            }
            break;
        case INSURER_LINE_OFFER:
        case INSURER_LINE_OFFER_17:
            if (answer == 0) {
                next = it_ask_price(talk, IT_INSURANCE_PRICE);
            }
            break;
        case INSURER_LINE_OFFER_COVER_1D:
        case INSURER_LINE_OFFER_COVER_27:
            if (answer == 0) {
                next = it_ask_price(talk, IT_COVER_PRICE);
            }
            break;
        case INSURER_LINE_ASK_CLAIM_20:
        case INSURER_LINE_ASK_CLAIM_21:
            if (answer == 0) {
                next = INSURER_LINE_CLAIM_SCREEN;
            }
            break;
        case INSURER_LINE_CLAIM_SCREEN:
            it_ask_claim(talk);
            break;
        default:
            break;
    }

    if (next != INSURER_NO_LINE) {
        it_say(it_talk_object(talk), (u8) next);
    }
}
CLEAN_AS(func_ov071_02278ac4, InsurerTalk_OnAnswer)

/* An explanation not said yet in the round, marked said (lines 0x0d-0x12); after four in a
 * row, without the cover 0x13, with it 0x1b and daily bit 0x28 set, the round starting afresh.
 * The line. */
static int it_explain(InsurerTalk *talk, u8 *record)
{
    Insurer *owner = talk->owner;
    int index = InsurerTalk_PickExplanation((int) (u32) (uintptr_t) owner, owner->explained, INSURER_EXPLANATIONS);
    if (owner->explained[index] == 0) {
        owner->explained[index] = 1;
    }
    int next = (u8) (index + INSURER_LINE_EXPLAIN_FIRST);
    talk->explained_count = (u8) (talk->explained_count + 1);
    if (talk->explained_count >= IT_EXPLANATIONS_IN_A_ROW) {
        if (PlayerRecord_TestFlag(record, IT_FLAG_COVERED) == 0) {
            next = INSURER_LINE_EXPLAINED;
        } else {
            next = INSURER_LINE_EXPLAINED_COVERED;
            TalkChecks_TestSetDailyBit(IT_DAILY_PITCHED, 1);
        }
        talk->explained_count = 0;
        MI_CpuFill8(talk->owner->explained, 0, INSURER_EXPLANATIONS);
    }
    return next;
}

/* The insurance or the cover taken: the talk's motion of kind 14 with its item, its bells
 * taken. */
static void it_take(InsurerTalk *talk, u16 item, int price)
{
    SceneCommand_RequestMotion14(it_scene(talk), &item, 0, 5, 0);
    SceneBells_Take(it_owner_word(talk), price);
}

/* func_ov071_02278c4c (slot 0x14, a line ended), by the line shown:
 * - 0x05, 0x14, 0x1c: the screen panels asked for; 0x15 (the insurance), or 0x1d (the cover)
 *   for an insured player;
 * - 0x0d-0x12: the next explanation (it_explain);
 * - 0x13: 0x14, or 0x1c for an insured player; 0x18: 0x19, or 0x1e for an insured player;
 * - 0x19: the insurance taken (item 0x149d, 3000 bells), the player record's flag 0x17 set
 *   and its date today; 0x1a;
 * - 0x1e: the cover taken (item 0x14a0, 6000 bells) and flag 0x18 set; 0x1f;
 * - 0x16, 0x1a, 0x1f: the panels' request cleared;
 * - 0x23: the pockets' screen for a claim;
 * - 0x25: the talk's motion of kind 16; 0x21 while the pockets hold another claim, else 0x26.
 * The line, when one was picked, is shown. */
void InsurerTalk_OnLineEnded(InsurerTalk *talk)
{
    int next = INSURER_NO_LINE;
    u8 *record = PlayerRecords_Current();

    switch (it_line_shown(talk)) {
        case 0x05:
        case INSURER_LINE_EXPLAINED_UNINSURED:
        case INSURER_LINE_EXPLAINED_INSURED:
            ScreenPanels_Request();
            next = INSURER_LINE_OFFER;
            if (PlayerRecord_TestFlag(record, IT_FLAG_INSURED) != 0) {
                next = INSURER_LINE_OFFER_COVER_1D;
            }
            break;
        case INSURER_LINE_EXPLAIN_START:
        case INSURER_LINE_EXPLAIN_FIRST:
        case INSURER_LINE_EXPLAIN_FIRST + 1:
        case INSURER_LINE_EXPLAIN_FIRST + 2:
        case INSURER_LINE_EXPLAIN_FIRST + 3:
        case INSURER_LINE_EXPLAIN_END:
            next = it_explain(talk, record);
            break;
        case INSURER_LINE_EXPLAINED:
            next = PlayerRecord_TestFlag(record, IT_FLAG_INSURED) == 0 ? INSURER_LINE_EXPLAINED_UNINSURED
                                                                       : INSURER_LINE_EXPLAINED_INSURED;
            break;
        case INSURER_LINE_CAN_PAY:
            next = PlayerRecord_TestFlag(record, IT_FLAG_INSURED) == 0 ? INSURER_LINE_INSURE : INSURER_LINE_COVER;
            break;
        case INSURER_LINE_INSURE:
            it_take(talk, IT_INSURANCE_ITEM, IT_INSURANCE_PRICE);
            next = INSURER_LINE_INSURED;
            PlayerRecord_SetFlag(record, IT_FLAG_INSURED);
            PlayerField2416_SetToday((PlayerField2416 *) (void *) PlayerRecord_Field2416(record));
            break;
        case INSURER_LINE_NO_BELLS:
        case INSURER_LINE_INSURED:
        case INSURER_LINE_COVERED:
            ScreenPanels_ClearRequest((unsigned int) (uintptr_t) record);
            break;
        case INSURER_LINE_COVER:
            it_take(talk, IT_COVER_ITEM, IT_COVER_PRICE);
            next = INSURER_LINE_COVERED;
            PlayerRecord_SetFlag(record, IT_FLAG_COVERED);
            break;
        case INSURER_LINE_CLAIM_SCREEN:
            it_ask_claim(talk);
            break;
        case INSURER_LINE_CLAIM_TAKEN:
            SceneCommand_RequestMotion16(it_scene(talk));
            next = Pockets_Select(it_claim_test()) != 0 ? INSURER_LINE_ASK_CLAIM_21 : INSURER_LINE_NO_CLAIM_ITEM;
            break;
        default:
            break;
    }

    if (next != INSURER_NO_LINE) {
        it_say(it_talk_object(talk), (u8) next);
    }
}
CLEAN_AS(func_ov071_02278c4c, InsurerTalk_OnLineEnded)

/* func_ov071_02278e40 (slot 0x78, the line the talk starts with), of "sp_npc_insurance", by
 * what the talk starts with (InsurerTalk.first, data_ov071_02279fbc): an insured player
 * insured today, INSURER_TALK_FIRST_TODAY; else once he pitched to the player today (daily bit
 * 0x28), INSURER_TALK_FIRST_COVERED for a covered player, else INSURER_TALK_FIRST_PITCHED;
 * before that one of five greetings (0x28-0x2c) instead of the line.
 * QUIRK: with a greeting the choice is not written: it keeps its last value (0 from the
 * talk's start), whose text is given with the greeting. */
void InsurerTalk_FirstLine(InsurerTalk *talk, InsurerLine *out)
{
    int greet = 0;
    u8 *record = PlayerRecords_Current();

    if (PlayerRecord_TestFlag(record, IT_FLAG_INSURED) != 0) {
        const Date *insured =
            (const Date *) (const void *) PlayerField2416_Date((PlayerField2416 *) (void *) PlayerRecord_Field2416(record));
        Date today;
        Calendar_Today(&today);
        if (Calendar_DaysFrom(&today, insured) < 1) {
            talk->first = INSURER_TALK_FIRST_TODAY;
        } else if (PlayerRecord_TestFlag(record, IT_FLAG_COVERED) != 0) {
            if (TalkChecks_TestSetDailyBit(IT_DAILY_PITCHED, 0) != 0) {
                talk->first = INSURER_TALK_FIRST_COVERED;
            } else {
                greet = 1;
            }
        } else if (TalkChecks_TestSetDailyBit(IT_DAILY_PITCHED, 0) != 0) {
            talk->first = INSURER_TALK_FIRST_PITCHED;
        } else {
            greet = 1;
        }
    } else if (TalkChecks_TestSetDailyBit(IT_DAILY_PITCHED, 0) != 0) {
        talk->first = INSURER_TALK_FIRST_PITCHED;
    } else {
        greet = 1;
    }

    if (talk->first < 0 || talk->first >= INSURER_TALK_FIRSTS) {
        return;
    }
    out->message = data_ov071_02279fbc[talk->first].message;
    if (greet) {
        out->message = (u8) (MainRandom_Below(5) + INSURER_LINE_GREETINGS);
    }
    out->text = data_ov071_02279fbc[talk->first].text;
}
CLEAN_AS(func_ov071_02278e40, InsurerTalk_FirstLine)

/* func_ov071_02278f1c: his talk scene told through its vtable slot 0x08 and given its owner,
 * the first line's choice 0 and no explanation in a row. */
void InsurerTalk_Begin(InsurerTalk *talk, void *owner)
{
    u32 vtable = *(const u32 *) (const void *) talk;
    u32 code = *(const u32 *) (uintptr_t) (vtable + IT_TALK_SLOT_08);
    ((void (*)(InsurerTalk *))(uintptr_t) code)(talk);
    talk->owner = owner;
    talk->first = INSURER_TALK_FIRST_PITCHED;
    talk->explained_count = 0;
}
CLEAN_AS(func_ov071_02278f1c, InsurerTalk_Begin)

/* func_ov071_02278f44 (slot 0x08): the scene base reset, and no sequences. */
void InsurerTalk_Reset(InsurerTalk *talk)
{
    SceneBase_Reset(&talk->base);
    MemberPointer none = __ptmf_null;
    talk->sequence = none;
    talk->next_sequence = none;
}
CLEAN_AS(func_ov071_02278f44, InsurerTalk_Reset)

/* func_ov071_02278f80 (slot 0x04): the scene class 0x020d9ff8's destructor, then the scene
 * freed. */
void *InsurerTalk_Delete(void *talk)
{
    *(const u8 **) talk = data_ov071_0227a1e8;
    Obj020d9ff8_DestructBody(talk);
    Heap_OperatorDeleteB(talk);
    return talk;
}
CLEAN_AS(func_ov071_02278f80, InsurerTalk_Delete)

/* func_ov071_02278fa0 (slot 0x00): the scene class 0x020d9ff8's destructor. */
void *InsurerTalk_Destroy(void *talk)
{
    *(const u8 **) talk = data_ov071_0227a1e8;
    Obj020d9ff8_DestructBody(talk);
    return talk;
}
CLEAN_AS(func_ov071_02278fa0, InsurerTalk_Destroy)

/* func_ov071_02278fb8: the constructor: a scene of class 0x020d9ff8 given this class's
 * vtable. */
void *InsurerTalk_Construct(void *talk)
{
    Obj020d9ff8_Construct(talk);
    *(const u8 **) talk = data_ov071_0227a1e8;
    return talk;
}
CLEAN_AS(func_ov071_02278fb8, InsurerTalk_Construct)

/* func_ov071_02278fd0: a line not said yet, at random: the n-th of the `count` marks of `said`
 * that are 0, n drawn below their number; 0 when there is none. */
int InsurerTalk_PickExplanation(int unused, unsigned char *said, int count)
{
    int left = (int) MainRandom_Below(InsurerTalk_CountUnsaid(unused, said, count));
    for (int i = 0; i < count; i++) {
        if (said[i] == 0) {
            if (left == 0) {
                return i;
            }
            left--;
        }
    }
    return 0;
}
CLEAN_AS(func_ov071_02278fd0, InsurerTalk_PickExplanation)

/* func_ov071_02279004: how many of the `count` marks of `said` are 0. */
int InsurerTalk_CountUnsaid(int unused, const unsigned char *said, int count)
{
    (void) unused;
    int unsaid = 0;
    for (int i = 0; i < count; i++) {
        if (said[i] == 0) {
            unsaid++;
        }
    }
    return unsaid;
}
CLEAN_AS(func_ov071_02279004, InsurerTalk_CountUnsaid)

/* func_ov071_02279024 (sequence 1): the talk's next line asked for. */
void InsurerTalk_NextLine(int talk)
{
    SceneCommand_RequestNextLine((SceneCommandScene *) (uintptr_t) (u32) talk);
}
CLEAN_AS(func_ov071_02279024, InsurerTalk_NextLine)

/* func_ov071_0227902c (sequence 0, when the pockets' screen's command ended): when the player
 * confirmed a pocket (GroupParams_C4CIs1) holding something, the claim is taken: line 0x25,
 * the player record's count of claims raised, the talk's motion of kind 14 with the item, the
 * pocket emptied and sequence 1 next; else the talk's next line asked for and line 0x24.
 * QUIRK: the pocket is emptied only when its number is 0 or more, which a byte always is. */
void InsurerTalk_TakeClaim(InsurerTalk *talk)
{
    TalkObject *object = it_talk_object(talk);
    u8 message = INSURER_LINE_NO_CLAIM;

    if (GroupParams_C4CIs1() == 0) {
        SceneCommand_RequestNextLine(it_scene(talk));
    } else {
        int slot = GroupParams_Arg();
        u16 item = CurrentPockets_Item((u32) slot);
        if (it_is_none(&item)) {
            SceneCommand_RequestNextLine(it_scene(talk));
        } else {
            PlayerField2416 *field = (PlayerField2416 *) (void *) PlayerRecord_Field2416(PlayerRecords_Current());
            message = INSURER_LINE_CLAIM_TAKEN;
            PlayerField2416_RaiseClaims(field);
            SceneCommand_RequestMotion14(it_scene(talk), &item, 0, 4, 0);
            if (slot >= 0) {
                CurrentPockets_Empty(slot);
            }
            InsurerTalk_SetNextSequence(talk, INSURER_TALK_SEQUENCE_NEXT_LINE);
        }
    }
    it_say(object, message);
}
CLEAN_AS(func_ov071_0227902c, InsurerTalk_TakeClaim)

/* func_ov071_022790f0 (the claims' pocket test): whether the item at `item` is of the codes
 * 0x3934-0x3983, asked in state 0; 0 in any other. */
unsigned short InsurerTalk_IsClaimItem(unsigned short *item, int state)
{
    if (state != 0) {
        return 0;
    }
    return *item >= IT_CLAIM_FIRST && *item <= IT_CLAIM_LAST;
}
CLEAN_AS(func_ov071_022790f0, InsurerTalk_IsClaimItem)

/* func_ov071_02279118: the sequence to follow the current one set. */
void InsurerTalk_SetNextSequence(InsurerTalk *talk, int sequence)
{
    InsurerTalk_SequenceInto((int) (u32) (uintptr_t) talk, &talk->next_sequence, sequence);
}
CLEAN_AS(func_ov071_02279118, InsurerTalk_SetNextSequence)

/* func_ov071_02279128: the sequence set. */
void InsurerTalk_SetSequence(void *talk, int sequence)
{
    InsurerTalk *self = talk;
    InsurerTalk_SequenceInto((int) (u32) (uintptr_t) self, &self->sequence, sequence);
}
CLEAN_AS(func_ov071_02279128, InsurerTalk_SetSequence)

/* func_ov071_02279138: sequence `sequence`'s function, from the table (filled the first time),
 * into `out`.
 * REQUIRES: `sequence` is 0 or 1. */
void InsurerTalk_SequenceInto(int talk, MemberPointer *out, int sequence)
{
    static const MemberPointer *const constants[INSURER_TALK_SEQUENCES] = {&data_ov071_0227a170, &data_ov071_0227a130};
    (void) talk;
    MemberTable_InitOnce(&data_ov071_0227a344, data_ov071_0227a364, constants, INSURER_TALK_SEQUENCES);
    *out = data_ov071_0227a364[sequence];
}
CLEAN_AS(func_ov071_02279138, InsurerTalk_SequenceInto)

/* func_ov071_0227918c (slot 0x84, a command of the scene ended): a sequence set runs, and the
 * one to follow it, if any, becomes the sequence. */
void InsurerTalk_RunSequence(InsurerTalk *talk)
{
    if (talk->sequence.function == 0) {
        return;
    }
    MemberPointer_CallVoid(&talk->sequence, talk);
    MemberPointer none = __ptmf_null;
    talk->sequence = none;
    if (talk->next_sequence.function != 0) {
        talk->sequence = talk->next_sequence;
        talk->next_sequence = none;
    }
}
CLEAN_AS(func_ov071_0227918c, InsurerTalk_RunSequence)
