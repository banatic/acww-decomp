/* The giraffe's talk scene: her lines, the score of what the player wears, the advice and the
 * dressing (giraffe_talk.h). */
#include "giraffe_talk.h"

#include <stdint.h>

#include "autoload_2/heap.h"
#include "clean.h"
#include "main/block_021d27ac.h"
#include "main/current_pockets.h"
#include "main/event_schedule.h"
#include "main/group_params.h"
#include "main/item_code.h"
#include "main/item_lists.h"
#include "main/item_record.h"
#include "main/item_traits.h"
#include "main/letter.h"
#include "main/mail_text.h"
#include "main/main_random.h"
#include "main/message_receiver.h"
#include "main/message_texts.h"
#include "main/number_text.h"
#include "main/obj_020d9ff8.h"
#include "main/player_actor_ops.h"
#include "main/player_field_2416.h"
#include "main/player_id.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/scene_base.h"
#include "main/scene_bells.h"
#include "main/scene_command.h"
#include "main/screen_panels.h"
#include "main/talk_answers.h"
#include "main/talk_checks.h"
#include "main/talk_object.h"

static_assert(sizeof(SceneBase) == 0x80, "scene base");
static_assert(offsetof(GiraffeTalk, first) == 0xb0, "first");
static_assert(offsetof(GiraffeTalk, owner) == 0xb4, "owner");
static_assert(offsetof(GiraffeTalk, sequence) == 0xb8, "sequence");
static_assert(offsetof(GiraffeTalk, paid) == 0xc0, "paid");
static_assert(offsetof(GiraffeTalk, worn) == 0xc4, "worn");
static_assert(sizeof(GiraffeTalk) == 0xcc, "talk scene");
static_assert(sizeof(GiraffeLine) == 8, "a line");
static_assert(sizeof(GiraffeTier) == 0x10 && offsetof(GiraffeTier, max_paid) == 0x0c, "a tier");
static_assert(sizeof(MessageReceiver) == 0x20 && offsetof(MessageReceiver, message) == 0x1e, "the line shown");

/* The talk scene's vtable. */
extern const u8 data_ov070_02279dbc[];
/* The message file's name, "sp_npc_giraffe" (also the name of her letter's file). */
extern const char data_ov070_02279d58[];
/* The first lines (GiraffeTalkFirst) and the tiers of the dressing. */
extern const GiraffeLine data_ov070_02279ba8[GIRAFFE_TALK_FIRSTS];
extern const GiraffeTier data_ov070_02279be0[GIRAFFE_TIERS];
/* Her letter's tag and paper. */
extern const u8 data_ov070_02279d20[];
extern const u8 data_ov070_02279d24[];
/* The table of the talk's sequences (a function-local static of one entry, filled once from
 * the constant data_ov070_02279d40; bit 0 of data_ov070_02279f10 says it was). */
extern u32 data_ov070_02279f10;
extern MemberPointer data_ov070_02279f1c[1];
extern const MemberPointer data_ov070_02279d40;
/* The null member pointer (the C++ runtime's). */
extern const MemberPointer __ptmf_null;

/* The game's functions handed on: the empty pocket test (GiraffeTalk_IsEmptyPocket) and the
 * item code object's constructor and destructor (RoomInterior_ConstructCode,
 * TrivialObject_DestructItemCode). */
extern int func_ov070_02279224(void *item);
extern void func_02034ce0(void *code);
extern void func_020051b0(void *code);

extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern void MI_CpuFill8(void *dst, u8 value, u32 size);

/* The daily bits of the current player. */
#define GT_DAILY_TALKED 7
#define GT_DAILY_ADVICE_DONE 8
#define GT_DAILY_DRESSED 9

/* The flag of the object at data_021d27ac set when the player did not pay. */
#define GT_FLAG_NOT_PAID 10

/* The advice: lines said in a row before the round ends, and before the count's lines. */
#define GT_ADVICE_IN_A_ROW 5
#define GT_ADVICE_COUNTING 3

/* A score of at least this is a high one (GIRAFFE_TALK_FIRST_HIGH). */
#define GT_HIGH_SCORE 0x3d

/* Her letter: its message is 0 to 7, one for each ten points of the score above 21; item
 * 0x12a7 with messages 0-2, 0x1248 with 3-4. The item the talk asks for with it, and the pile
 * marked in the player's item record. */
#define GT_LETTER_SCORE_FROM 0x15
#define GT_LETTER_MESSAGES 7
#define GT_LETTER_ITEM_LOW 0x12a7
#define GT_LETTER_ITEM_MIDDLE 0x1248
#define GT_LETTER_MOTION_ITEM 0x1565
#define GT_LETTER_PILE_ITEM 0x10
#define GT_LETTER_PILE_COUNT 4

/* The payment screen (SceneCommand_RequestScreen) and its mode. */
#define GT_PAYMENT_SCREEN 2
#define GT_PAYMENT_SCREEN_MODE 0x39
#define GT_SEQUENCE_PAYMENT 0

/* The item list groups of the dressing's clothes: the special ones, and the others. */
#define GT_CLOTHES_KIND 2
#define GT_CLOTHES_SPECIAL 0x22
#define GT_CLOTHES_OTHER 0

/* The items worn that are never given back (nor counted in the room needed): codes 0x1429-0x1430
 * on the head, 0x12a8-0x12af as clothes; GiraffeTalk_Dress keeps both from any place. */
#define GT_KEPT_A_FIRST 0x1429
#define GT_KEPT_A_LAST 0x1430
#define GT_KEPT_B_FIRST 0x12a8
#define GT_KEPT_B_LAST 0x12af

/* The talk scene's vtable slot its talks call first. */
#define GT_TALK_SLOT_08 0x08

static u8 gt_line_shown(const GiraffeTalk *talk)
{
    return ((const MessageReceiver *) (const void *) talk)->message;
}

static TalkObject *gt_talk_object(GiraffeTalk *talk)
{
    return (TalkObject *) (void *) talk->base.talk;
}

static SceneCommandScene *gt_scene(GiraffeTalk *talk)
{
    return (SceneCommandScene *) (void *) talk;
}

/* Message `message` of "sp_npc_giraffe" shown in `object`. */
static void gt_say(TalkObject *object, u8 message)
{
    TalkObject_SetMessage(object, &message, data_ov070_02279d58);
}

static int gt_owner_word(const GiraffeTalk *talk)
{
    return (int) (u32) (uintptr_t) talk->owner;
}

static PlayerField2416 *gt_field(u8 *record)
{
    return (PlayerField2416 *) (void *) PlayerRecord_Field2416(record);
}

/* Whether `item` is "nothing": an item with variants is compared without its variant. */
static int gt_is_none(const u16 *item)
{
    if (ItemCode_HasVariant(item)) {
        u16 none = ITEM_CODE_NONE;
        int number = ItemCode_VariantItem(item);
        return number == ItemCode_VariantItem(&none);
    }
    return *item == ITEM_CODE_NONE;
}

static int gt_in(u16 item, u16 first, u16 last)
{
    return item >= first && item <= last;
}

/* A line of advice not said yet in the round, marked said; its line. */
static u8 gt_next_advice(Giraffe *owner)
{
    int index = GiraffeTalk_PickAdvice((int) (u32) (uintptr_t) owner, owner->advice_said, GIRAFFE_ADVICE_LINES);
    if (owner->advice_said[index] == 0) {
        owner->advice_said[index] = 1;
    }
    return (u8) (index + GIRAFFE_LINE_ADVICE_FIRST);
}

/* func_ov070_02278ab8 (slot 0x18, the player's answer), by the line shown:
 * - a line of advice (0x0f-0x22, whatever the answer): the next one while fewer than five were
 *   said in a row; else the round's marks cleared, daily bit 8 set and line 0x23;
 * - 0x09, answered 0: 0x0b when the pockets have a free letter, else 0x0c.
 * The line, when one was picked, is shown. */
void GiraffeTalk_OnAnswer(GiraffeTalk *talk)
{
    unsigned int answer = TalkAnswers_Picked((TalkAnswers *) (uintptr_t) (u32) SceneBase_TalkChoices(&talk->base));
    int next = GIRAFFE_NO_LINE;

    if (gt_line_shown(talk) >= GIRAFFE_LINE_ADVICE_FIRST && gt_line_shown(talk) <= GIRAFFE_LINE_ADVICE_LAST) {
        if (talk->owner->advice_count < GT_ADVICE_IN_A_ROW) {
            next = gt_next_advice(talk->owner);
        } else {
            MI_CpuFill8(talk->owner->advice_said, 0, GIRAFFE_ADVICE_LINES);
            TalkChecks_TestSetDailyBit(GT_DAILY_ADVICE_DONE, 1);
            next = GIRAFFE_LINE_ADVICE_DONE;
        }
    }
    if (gt_line_shown(talk) == GIRAFFE_LINE_LETTER_ASK && answer == 0) {
        next = CurrentPockets_FreeLetterIndex() != -1 ? GIRAFFE_LINE_LETTER_ROOM : GIRAFFE_LINE_LETTER_NO_ROOM;
    }
    if (next != GIRAFFE_NO_LINE) {
        gt_say(gt_talk_object(talk), (u8) next);
    }
}
CLEAN_AS(func_ov070_02278ab8, GiraffeTalk_OnAnswer)

/* Her letter (line 0x24), when the pockets have a free letter: the player scored first; its
 * message by the score (0 up to 21, then one more for each ten, at most 7), the score as its
 * part 0, the talk's motion of kind 13 with item 0x1565, a pile of item 0x10 marked in the
 * player's item record, and item 0x12a7 (messages 0-2) or 0x1248 (3-4) put in it. */
static void gt_write_letter(GiraffeTalk *talk, u8 *record)
{
    if (CurrentPockets_FreeLetterIndex() == -1) {
        return;
    }
    Letter *letter = CurrentPockets_FreeLetter();
    if (letter == NULL) {
        return;
    }
    PlayerField2416 *field = gt_field(record);
    MessageText46 text;
    MessageText46_Construct(&text);
    u8 message = 0;
    GiraffeTalk_Score(talk);
    if ((u32) PlayerField2416_Count0E(field) > GT_LETTER_SCORE_FROM) {
        message = (u8) ((u8) (PlayerField2416_Count0E(field) - GT_LETTER_SCORE_FROM) / 10);
    }
    if (message > GT_LETTER_MESSAGES) {
        message = GT_LETTER_MESSAGES;
    }
    u16 motion_item = GT_LETTER_MOTION_ITEM;
    SceneCommand_RequestMotion13(gt_scene(talk), &motion_item, 0, 5, 0);
    NumberText_Format(&text, PlayerField2416_Count0E(field), 10, 0, 0, 0);
    MailText_SetPartText(0, &text);
    Letter_WriteSpecialToPlayer(letter, &message, data_ov070_02279d58, data_ov070_02279d20, data_ov070_02279d24,
                                PlayerRecord_Player(record));
    if (record != NULL) {
        u16 pile = ItemCode_MakePile(GT_LETTER_PILE_ITEM, GT_LETTER_PILE_COUNT);
        ItemRecord_Mark((ItemRecord *) (void *) PlayerRecord_ItemRecord(record), &pile, 0);
    }
    if (message <= 2) {
        Letter_SetItem(letter, GT_LETTER_ITEM_LOW, 1);
    } else if (message <= 4) {
        Letter_SetItem(letter, GT_LETTER_ITEM_MIDDLE, 1);
    }
    MessageText46_Destruct(&text);
}

/* func_ov070_02278b64 (slot 0x14, a line ended), by the line shown:
 * - a line of advice (0x0f-0x22) while fewer than five were said: 0x46 plus that count;
 * - 0x0e and 0x47-0x4a: the next line of advice, one more said in a row;
 * - 0x24: her letter written (gt_write_letter);
 * - 0x00: one of two lines (a coin) of four pairs: 0x01 and 0x03 for clothes of item list
 *   group 0x22, 0x05 and 0x07 for others, the second of each when byte 0x1c of the player is
 *   not 0;
 * - 0x25: one of ten remarks (0x3a-0x43), the count of advice back to 0;
 * - 0x28, 0x2b: with room in the pockets 0x2c and the screen panels asked for, else 0x39;
 * - 0x2c, 0x31: with room, the payment screen (mode 0x39, screen 2) with sequence 0, else 0x39;
 * - 0x36: the panels' request cleared, the player dressed (0x34 with special clothes, else
 *   0x37) and daily bit 9 set;
 * - 0x38: event 0x40 marked taken part in.
 * The line, when one was picked, is shown. */
void GiraffeTalk_OnLineEnded(GiraffeTalk *talk)
{
    u8 *record = PlayerRecords_Current();
    int next = GIRAFFE_NO_LINE;
    u8 line = gt_line_shown(talk);

    if (line >= GIRAFFE_LINE_ADVICE_FIRST && line <= GIRAFFE_LINE_ADVICE_LAST) {
        u8 count = talk->owner->advice_count;
        if (count < GT_ADVICE_IN_A_ROW) {
            next = (u8) (count + GIRAFFE_LINE_ADVICE_NEXT);
        }
    }
    if (line == GIRAFFE_LINE_ADVICE_START || (line >= GIRAFFE_LINE_ADVICE_NEXT + 1 && line <= GIRAFFE_LINE_ADVICE_NEXT_LAST)) {
        next = gt_next_advice(talk->owner);
        talk->owner->advice_count++;
    }
    if (gt_line_shown(talk) == GIRAFFE_LINE_LETTER) {
        gt_write_letter(talk, record);
    }

    line = gt_line_shown(talk);
    switch (line) {
        case GIRAFFE_LINE_GREETING: {
            int special = ItemLists_GroupOf(PlayerRecord_Clothes(record), 0) == GT_CLOTHES_SPECIAL;
            int second = PlayerId_Byte1c((const s8 *) (const void *) PlayerRecord_Player(record)) != 0;
            unsigned int base = special ? (second ? 3 : 1) : (second ? 7 : 5);
            next = (u8) (MainRandom_Below(2) + base);
            break;
        }
        case GIRAFFE_LINE_REMARK:
            next = (u8) (MainRandom_Below(10) + GIRAFFE_LINE_REMARKS);
            talk->owner->advice_count = 0;
            break;
        case GIRAFFE_LINE_OFFER:
        case GIRAFFE_LINE_OFFER_2B:
            if (GiraffeTalk_HasRoom(talk)) {
                next = GIRAFFE_LINE_ASK_PAYMENT;
                ScreenPanels_Request();
            } else {
                next = GIRAFFE_LINE_NO_ROOM;
            }
            break;
        case GIRAFFE_LINE_ASK_PAYMENT:
        case GIRAFFE_LINE_ASK_PAYMENT_31:
            if (GiraffeTalk_HasRoom(talk)) {
                SceneCommand_SetScreenMode(gt_scene(talk), GT_PAYMENT_SCREEN_MODE, 0);
                SceneCommand_RequestScreen(gt_scene(talk), GT_PAYMENT_SCREEN);
                GiraffeTalk_SetSequence(talk, GT_SEQUENCE_PAYMENT);
            } else {
                next = GIRAFFE_LINE_NO_ROOM;
            }
            break;
        case GIRAFFE_LINE_DRESS:
            ScreenPanels_ClearRequest(line);
            next = GiraffeTalk_Dress(talk) == 0 ? GIRAFFE_LINE_CLOTHES : GIRAFFE_LINE_SPECIAL_CLOTHES;
            TalkChecks_TestSetDailyBit(GT_DAILY_DRESSED, 1);
            break;
        case GIRAFFE_LINE_LEAVE:
            EventSchedule_MarkTakenPart(0x40);
            break;
        default:
            break;
    }

    if (next != GIRAFFE_NO_LINE) {
        gt_say(gt_talk_object(talk), (u8) next);
    }
}
CLEAN_AS(func_ov070_02278b64, GiraffeTalk_OnLineEnded)

/* The player's hat and accessory, each shown on the player (the requests of state 7 of kinds 2
 * and 1) or set in the record, from a copy of `item`. */
static void gt_show_head(u16 item)
{
    PlayerActorOps_RequestState7Kind2Next10(&item);
}

static void gt_show_accessory(u16 item)
{
    PlayerActorOps_RequestState7Kind1Next10(&item);
}

static void gt_set_head(u8 *record, u16 item)
{
    PlayerRecord_SetHeadItem(record, &item);
}

static void gt_set_accessory(u8 *record, u16 item)
{
    PlayerRecord_SetPartCItem(record, &item);
}

/* func_ov070_02278e30: the player dressed for what was paid. The player scored first; the tier
 * is the first of seven whose bound is at least what was paid (the last one above all).
 * - one of four (at random): one of the tier's three hats or accessories, the other place
 *   emptied, both in the record and shown; the fourth empties both;
 * - with the tier's chance in percent (a number 0-100 not above it) the clothes are drawn
 *   from item list group 0x22, else from group 0; unless nothing was drawn they are shown and
 *   set, and their name put in the talk's part 0 (kind 7);
 * - the three items worn before go back into the pockets, unless they are nothing or of the
 *   codes kept (0x1429-0x1430, 0x12a8-0x12af).
 * Whether the clothes came from group 0x22. */
int GiraffeTalk_Dress(GiraffeTalk *talk)
{
    u8 pick = (u8) MainRandom_Below(4);
    int tier = GIRAFFE_TIERS - 1;
    u16 clothes = ITEM_CODE_NONE;

    GiraffeTalk_Score(talk);
    for (int i = 0; i < GIRAFFE_TIERS; i++) {
        if (data_ov070_02279be0[i].max_paid >= talk->paid) {
            tier = i;
            break;
        }
    }
    const GiraffeTier *dress = &data_ov070_02279be0[tier];

    u8 *record = PlayerRecords_Current();
    if (pick < 3) {
        u16 item = dress->items[pick];
        gt_set_accessory(record, ITEM_CODE_NONE);
        if (dress->is_accessory[pick] == 0) {
            gt_show_head(item);
            gt_set_head(record, item);
            gt_show_accessory(ITEM_CODE_NONE);
            gt_set_accessory(record, ITEM_CODE_NONE);
        } else {
            gt_show_accessory(item);
            gt_set_accessory(record, item);
            gt_show_head(ITEM_CODE_NONE);
            gt_set_head(record, ITEM_CODE_NONE);
        }
    } else {
        gt_set_accessory(record, ITEM_CODE_NONE);
        gt_set_head(record, ITEM_CODE_NONE);
        gt_show_accessory(ITEM_CODE_NONE);
        gt_show_head(ITEM_CODE_NONE);
    }

    unsigned int roll = MainRandom_Below(101);
    int special = dress->special_chance >= (u8) roll;
    ItemList list;
    u16 drawn;
    ItemList_Construct(&list, GT_CLOTHES_KIND, special ? GT_CLOTHES_SPECIAL : GT_CLOTHES_OTHER);
    ItemLists_Draw(&drawn, &list, 0, 0, 1, 1, 0);
    clothes = drawn;
    ItemList_Destruct(&list);

    if (!gt_is_none(&clothes)) {
        u16 shown = clothes;
        PlayerActorOps_RequestState7Kind0Next10(&shown);
        PlayerRecord_SetClothes(record, &clothes);
        SceneBase_PutItemName(&talk->base, (int) (u32) (uintptr_t) &clothes, 0, 7);
    }

    for (int i = 0; i < GIRAFFE_WORN_COUNT; i++) {
        u16 *worn = &talk->worn[i];
        if (gt_is_none(worn)) {
            continue;
        }
        if (!gt_in(*worn, GT_KEPT_A_FIRST, GT_KEPT_A_LAST) && !gt_in(*worn, GT_KEPT_B_FIRST, GT_KEPT_B_LAST)) {
            CurrentPockets_Give(worn, 0);
        }
    }
    return special;
}
CLEAN_AS(func_ov070_02278e30, GiraffeTalk_Dress)

/* func_ov070_022790cc: whether the pockets have room for what the player wears: the empty
 * pockets counted first, then the player scored (which notes what is worn); one place for the
 * hat unless it is nothing or of codes 0x1429-0x1430, one for the accessory unless it is
 * nothing, one for the clothes unless they are nothing or of codes 0x12a8-0x12af. */
int GiraffeTalk_HasRoom(GiraffeTalk *talk)
{
    PocketsMarks marks;
    u8 needed = 0;

    CurrentPockets_Mark(&marks, (int (*)(u16 *))(void (*)(void)) func_ov070_02279224);
    GiraffeTalk_Score(talk);
    if (!gt_is_none(&talk->worn[GIRAFFE_WORN_HEAD]) &&
        !gt_in(talk->worn[GIRAFFE_WORN_HEAD], GT_KEPT_A_FIRST, GT_KEPT_A_LAST)) {
        needed++;
    }
    if (!gt_is_none(&talk->worn[GIRAFFE_WORN_ACCESSORY])) {
        needed++;
    }
    if (!gt_is_none(&talk->worn[GIRAFFE_WORN_CLOTHES]) &&
        !gt_in(talk->worn[GIRAFFE_WORN_CLOTHES], GT_KEPT_B_FIRST, GT_KEPT_B_LAST)) {
        needed++;
    }
    return marks.count >= needed;
}
CLEAN_AS(func_ov070_022790cc, GiraffeTalk_HasRoom)

/* func_ov070_02279224 (the test GiraffeTalk_HasRoom marks the pockets with): whether the item
 * code at `item` is 0xfff1. */
int GiraffeTalk_IsEmptyPocket(void *item)
{
    return *(const u16 *) item == ITEM_CODE_NONE;
}
CLEAN_AS(func_ov070_02279224, GiraffeTalk_IsEmptyPocket)

/* What a place adds to the score: twice its grade by the price of what is worn there. */
static void gt_score_item(PlayerField2416 *field, GiraffeTalk *talk, u16 *item, int place)
{
    unsigned char grade = GiraffeTalk_Grade((int) (u32) (uintptr_t) talk, ItemTraits_Price(item), place);
    PlayerField2416_AddCount0E(field, (u8) (grade * 2));
}

/* An item of the kept codes adds twice a number 1 to 10; an empty place twice 1 to 3. */
static void gt_score_kept(PlayerField2416 *field)
{
    PlayerField2416_AddCount0E(field, (u8) ((MainRandom_Below(10) + 1) * 2));
}

static void gt_score_empty(PlayerField2416 *field)
{
    unsigned int number = MainRandom_Below(3);
    PlayerField2416_AddCount0E(field, (u8) ((u8) (number + 1) * 2));
}

/* func_ov070_02279238: what the current player wears noted (the hat, the accessory and the
 * clothes, GiraffeTalk.worn) and scored into the player record's count 0x0e:
 * - the hat: by its grade, a random amount for codes 0x1429-0x1430, or when nothing is worn;
 * - the accessory: by its grade, or a random amount when nothing is worn;
 * - the clothes: by their grade, or a random amount (see BUG); nothing when none are worn.
 * BUG: the clothes' codes kept (0x12a8-0x12af) are tested on the hat, not on the clothes. */
void GiraffeTalk_Score(GiraffeTalk *talk)
{
    u8 *record = PlayerRecords_Current();
    PlayerField2416 *field = gt_field(record);

    talk->worn[GIRAFFE_WORN_HEAD] = *PlayerRecord_HeadItem(record);
    if (gt_is_none(&talk->worn[GIRAFFE_WORN_HEAD])) {
        gt_score_empty(field);
    } else if (gt_in(talk->worn[GIRAFFE_WORN_HEAD], GT_KEPT_A_FIRST, GT_KEPT_A_LAST)) {
        gt_score_kept(field);
    } else {
        gt_score_item(field, talk, &talk->worn[GIRAFFE_WORN_HEAD], GIRAFFE_WORN_HEAD);
    }

    talk->worn[GIRAFFE_WORN_ACCESSORY] = *PlayerRecord_PartCItem(record);
    if (gt_is_none(&talk->worn[GIRAFFE_WORN_ACCESSORY])) {
        gt_score_empty(field);
    } else {
        gt_score_item(field, talk, &talk->worn[GIRAFFE_WORN_ACCESSORY], GIRAFFE_WORN_ACCESSORY);
    }

    talk->worn[GIRAFFE_WORN_CLOTHES] = *PlayerRecord_Clothes(record);
    if (!gt_is_none(&talk->worn[GIRAFFE_WORN_CLOTHES])) {
#ifdef BUGFIX
        u16 tested = talk->worn[GIRAFFE_WORN_CLOTHES];
#else
        u16 tested = talk->worn[GIRAFFE_WORN_HEAD];
#endif
        if (gt_in(tested, GT_KEPT_B_FIRST, GT_KEPT_B_LAST)) {
            gt_score_kept(field);
        } else {
            gt_score_item(field, talk, &talk->worn[GIRAFFE_WORN_CLOTHES], GIRAFFE_WORN_CLOTHES);
        }
    }
}
CLEAN_AS(func_ov070_02279238, GiraffeTalk_Score)

/* func_ov070_0227944c: the grade of an item worn at `place` by its price: a random number in a
 * band, higher for dearer items.
 *   hat (0):       free 1-3, under 200 3-5, under 1000 5-7, else 7-10;
 *   accessory (1): free 1-3, under 160 3-5, under 600 5-7, else 7-10;
 *   clothes (2):   under 350 1-3, under 400 4-6, else 7-10;
 * 0 for any other place. */
unsigned char GiraffeTalk_Grade(int unused, int price, int place)
{
    (void) unused;
    switch (place) {
        case GIRAFFE_WORN_HEAD:
            if (price == 0) {
                return (unsigned char) (MainRandom_Below(3) + 1);
            }
            if (price < 200) {
                return (unsigned char) (MainRandom_Below(3) + 3);
            }
            if (price < 1000) {
                return (unsigned char) (MainRandom_Below(3) + 5);
            }
            return (unsigned char) (MainRandom_Below(4) + 7);
        case GIRAFFE_WORN_ACCESSORY:
            if (price == 0) {
                return (unsigned char) (MainRandom_Below(3) + 1);
            }
            if (price < 160) {
                return (unsigned char) (MainRandom_Below(3) + 3);
            }
            if (price < 600) {
                return (unsigned char) (MainRandom_Below(3) + 5);
            }
            return (unsigned char) (MainRandom_Below(4) + 7);
        case GIRAFFE_WORN_CLOTHES:
            if (price < 350) {
                return (unsigned char) (MainRandom_Below(3) + 1);
            }
            if (price < 400) {
                return (unsigned char) (MainRandom_Below(3) + 4);
            }
            return (unsigned char) (MainRandom_Below(4) + 7);
        default:
            return 0;
    }
}
CLEAN_AS(func_ov070_0227944c, GiraffeTalk_Grade)

/* func_ov070_02279538 (slot 0x64): `value` added to the current player's score (count 0x0e,
 * PlayerField2416_AddCount0E keeps it at most 100). */
void GiraffeTalk_AddScore(void *talk, unsigned char value)
{
    (void) talk;
    PlayerField2416_AddCount0E(gt_field(PlayerRecords_Current()), value);
}
CLEAN_AS(func_ov070_02279538, GiraffeTalk_AddScore)

/* func_ov070_02279550 (slot 0x78, the line the talk starts with), of "sp_npc_giraffe", by what
 * the talk starts with (GiraffeTalk.first, data_ov070_02279ba8):
 *   the first talk today (daily bit 7, set now)      GIRAFFE_TALK_FIRST_TODAY;
 *   no round of advice ended today (daily bit 8)     GIRAFFE_TALK_FIRST_ADVICE;
 *   dressed today (daily bit 9)                      GIRAFFE_TALK_FIRST_DRESSED;
 *   fewer than three lines of advice said in a row   GIRAFFE_TALK_FIRST_COUNTING, whose line
 *                                                    is 0x4c plus the count, then one more;
 *   a score of 61 or more, or less                   GIRAFFE_TALK_FIRST_HIGH, _LOW;
 * the last three are GIRAFFE_TALK_FIRST_REFUSED once flag 10 of the object at data_021d27ac is
 * set (the player did not pay). */
void GiraffeTalk_FirstLine(GiraffeTalk *talk, GiraffeLine *out)
{
    PlayerField2416 *field = gt_field(PlayerRecords_Current());

    if (TalkChecks_TestSetDailyBit(GT_DAILY_TALKED, 1) == 0) {
        talk->first = GIRAFFE_TALK_FIRST_TODAY;
    } else if (TalkChecks_TestSetDailyBit(GT_DAILY_ADVICE_DONE, 0) == 0) {
        talk->first = GIRAFFE_TALK_FIRST_ADVICE;
    } else if (TalkChecks_TestSetDailyBit(GT_DAILY_DRESSED, 0) != 0) {
        talk->first = GIRAFFE_TALK_FIRST_DRESSED;
    } else if (talk->owner->advice_count < GT_ADVICE_COUNTING) {
        talk->first = GIRAFFE_TALK_FIRST_COUNTING;
    } else if ((u32) PlayerField2416_Count0E(field) >= GT_HIGH_SCORE) {
        talk->first = GIRAFFE_TALK_FIRST_HIGH;
    } else {
        talk->first = GIRAFFE_TALK_FIRST_LOW;
    }

    Block021d27ac *block = Block021d27ac_Get();
    if (Block021d27ac_TestFlag(&block->flags, GT_FLAG_NOT_PAID) != 0 && talk->first >= GIRAFFE_TALK_FIRST_COUNTING &&
        talk->first <= GIRAFFE_TALK_FIRST_LOW) {
        talk->first = GIRAFFE_TALK_FIRST_REFUSED;
    }
    if (talk->first < 0 || talk->first >= GIRAFFE_TALK_FIRSTS) {
        return;
    }
    out->message = data_ov070_02279ba8[talk->first].message;
    if (talk->first == GIRAFFE_TALK_FIRST_COUNTING) {
        out->message = (u8) (talk->owner->advice_count + GIRAFFE_LINE_COUNTING);
        talk->owner->advice_count++;
    }
    out->text = data_ov070_02279ba8[talk->first].text;
}
CLEAN_AS(func_ov070_02279550, GiraffeTalk_FirstLine)

/* func_ov070_02279654: her talk scene told through its vtable slot 0x08 and given its owner,
 * nothing noted as worn and the first line's choice 0. */
void GiraffeTalk_Begin(GiraffeTalk *talk, Giraffe *owner)
{
    u32 vtable = *(const u32 *) (const void *) talk;
    u32 code = *(const u32 *) (uintptr_t) (vtable + GT_TALK_SLOT_08);
    ((void (*)(GiraffeTalk *))(uintptr_t) code)(talk);
    talk->owner = owner;
    for (int i = 0; i < GIRAFFE_WORN_COUNT; i++) {
        talk->worn[i] = ITEM_CODE_NONE;
    }
    talk->first = GIRAFFE_TALK_FIRST_TODAY;
}
CLEAN_AS(func_ov070_02279654, GiraffeTalk_Begin)

/* func_ov070_0227968c (slot 0x04): its destructor (the three item codes destroyed, then the
 * scene class 0x020d9ff8's), then the scene freed. */
void *GiraffeTalk_Delete(void *talk)
{
    GiraffeTalk *self = talk;
    self->base.vtable = data_ov070_02279dbc;
    __cxa_vec_cleanup(self->worn, GIRAFFE_WORN_COUNT, sizeof(u16), func_020051b0);
    Obj020d9ff8_DestructBody(self);
    Heap_OperatorDeleteB(self);
    return self;
}
CLEAN_AS(func_ov070_0227968c, GiraffeTalk_Delete)

/* func_ov070_022796c0 (slot 0x00): the three item codes destroyed, then the scene class
 * 0x020d9ff8's destructor. */
void *GiraffeTalk_Destroy(void *talk)
{
    GiraffeTalk *self = talk;
    self->base.vtable = data_ov070_02279dbc;
    __cxa_vec_cleanup(self->worn, GIRAFFE_WORN_COUNT, sizeof(u16), func_020051b0);
    Obj020d9ff8_DestructBody(self);
    return self;
}
CLEAN_AS(func_ov070_022796c0, GiraffeTalk_Destroy)

/* func_ov070_022796ec: the constructor: a scene of class 0x020d9ff8 given this class's vtable,
 * and its three item codes constructed. */
void *GiraffeTalk_Construct(void *talk)
{
    GiraffeTalk *self = talk;
    Obj020d9ff8_Construct(self);
    self->base.vtable = data_ov070_02279dbc;
    __cxa_vec_ctor(self->worn, GIRAFFE_WORN_COUNT, sizeof(u16), func_02034ce0, func_020051b0);
    return self;
}
CLEAN_AS(func_ov070_022796ec, GiraffeTalk_Construct)

/* func_ov070_02279724: a line not said yet, at random: the n-th of the `count` marks of `said`
 * that are 0, n drawn below their number; 0 when there is none. */
int GiraffeTalk_PickAdvice(int unused, unsigned char *said, int count)
{
    int left = (int) MainRandom_Below(GiraffeTalk_CountUnsaid(unused, said, count));
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
CLEAN_AS(func_ov070_02279724, GiraffeTalk_PickAdvice)

/* func_ov070_02279758: how many of the `count` marks of `said` are 0. */
int GiraffeTalk_CountUnsaid(int unused, const unsigned char *said, int count)
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
CLEAN_AS(func_ov070_02279758, GiraffeTalk_CountUnsaid)

/* func_ov070_02279778 (sequence 0, when the payment screen's command ended): nothing paid yet;
 * when the player confirmed (GroupParams_C4CIs1), the bells chosen are paid and the line says
 * how many (0x2d up to 1000, 0x2e up to 2000, 0x2f up to 4000, else 0x30); else the panels'
 * request is cleared, flag 10 of the object at data_021d27ac set and the line is 0x4b. */
void GiraffeTalk_TakePayment(GiraffeTalk *talk)
{
    TalkObject *object = gt_talk_object(talk);
    u8 message = GIRAFFE_LINE_NOT_PAID;

    talk->paid = 0;
    int confirmed = GroupParams_C4CIs1();
    if (confirmed) {
        talk->paid = GroupParams_C78();
        s32 paid = talk->paid;
        message = GIRAFFE_LINE_PAID_UP_TO_1000;
        if (paid > 1000 && paid <= 2000) {
            message = GIRAFFE_LINE_PAID_UP_TO_2000;
        } else if (paid > 2000 && paid <= 4000) {
            message = GIRAFFE_LINE_PAID_UP_TO_4000;
        } else if (paid > 4000) {
            message = GIRAFFE_LINE_PAID_MORE;
        }
        SceneBells_Take(gt_owner_word(talk), talk->paid);
    } else {
        ScreenPanels_ClearRequest((unsigned int) confirmed);
        Block021d27ac_SetFlag(&Block021d27ac_Get()->flags, GT_FLAG_NOT_PAID);
    }
    gt_say(object, message);
}
CLEAN_AS(func_ov070_02279778, GiraffeTalk_TakePayment)

/* func_ov070_02279820: the talk's sequence set, from its table (filled the first time).
 * REQUIRES: `sequence` is 0 (the table has one entry). */
void GiraffeTalk_SetSequence(void *talk, int sequence)
{
    static const MemberPointer *const constants[1] = {&data_ov070_02279d40};
    MemberTable_InitOnce(&data_ov070_02279f10, data_ov070_02279f1c, constants, 1);
    ((GiraffeTalk *) talk)->sequence = data_ov070_02279f1c[sequence];
}
CLEAN_AS(func_ov070_02279820, GiraffeTalk_SetSequence)

/* func_ov070_0227986c (slot 0x84, a command of the scene ended): a sequence set runs, and the
 * talk then has none. */
void GiraffeTalk_RunSequence(GiraffeTalk *talk)
{
    if (talk->sequence.function == 0) {
        return;
    }
    MemberPointer_CallVoid(&talk->sequence, talk);
    talk->sequence = __ptmf_null;
}
CLEAN_AS(func_ov070_0227986c, GiraffeTalk_RunSequence)

/* func_ov070_022798b0 (slot 0x08): the scene base reset, and no sequence. */
void GiraffeTalk_Reset(GiraffeTalk *talk)
{
    SceneBase_Reset(&talk->base);
    talk->sequence = __ptmf_null;
}
CLEAN_AS(func_ov070_022798b0, GiraffeTalk_Reset)
