/* The talk scene of overlay 86's turtle: his lines at the turn of the year, the item he gives
 * and the fortune letter (turtle6_talk.h). */
#include "turtle6_talk.h"

#include <stdint.h>

#include "autoload_2/heap.h"
#include "clean.h"
#include "main/block_021d27ac.h"
#include "main/calendar.h"
#include "main/current_pockets.h"
#include "main/date_time.h"
#include "main/item_code.h"
#include "main/item_record.h"
#include "main/letter.h"
#include "main/mail_text.h"
#include "main/main_random.h"
#include "main/message_reader.h"
#include "main/message_receiver.h"
#include "main/obj_020d9ff8.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/scene_base.h"
#include "main/scene_command.h"
#include "main/talk_answers.h"
#include "main/talk_object.h"

static_assert(sizeof(SceneBase) == 0x80, "scene base");
static_assert(offsetof(Turtle6Talk, owner) == 0xb0, "owner");
static_assert(offsetof(Turtle6Talk, item_slot) == 0xb4, "item slot");
static_assert(sizeof(Turtle6Line) == 8, "a line");
static_assert(sizeof(Turtle6FortunePart) == 8, "a part of the fortune");
static_assert(sizeof(MessageReceiver) == 0x20 && offsetof(MessageReceiver, message) == 0x1e, "the line shown");

/* The talk scene's vtable. */
extern const u8 data_ov086_022792fc[];
/* The message files: "sp_npc_turtle6" (his) and "sp_npc_turtle" (the turtle's common one). */
extern const char data_ov086_02279448[];
extern const char data_ov086_02279438[];
/* The fortune letter: its message file "ev_fortune", its tag and paper, and the files of its
 * parts ("st_fortune" for part 0, "st_fortune2" for parts 1-3). */
extern const char data_ov086_02279458[];
extern const u8 data_ov086_02279260[];
extern const u8 data_ov086_02279264[];
extern const Turtle6FortunePart data_ov086_022791d0[TURTLE6_FORTUNE_PARTS];

/* The items exchanged while the pockets hold the item 0x37e0. */
#define T6T_ASKED_ITEM 0x37e0
#define T6T_EXCHANGE_ITEM 0x1559

/* The item he gives at lines 0x19-0x1b. */
#define T6T_GIFT 0x137d

/* The item the scene's motion holds up after the fortune letter (the letters). */
#define T6T_LETTERS_ITEM 0x1565

/* The values the item motions (SceneCommand_RequestMotion13 and 14) are asked with. */
#define T6T_MOTION_B 5

/* The flag of the object at data_021d27ac set once the fortune was written. */
#define T6T_FLAG_FORTUNE 4

/* The fortune: one of four, its part 0 from message 0 on of "st_fortune", each later part one
 * of four messages of "st_fortune2", 16 apart from part to part; the letter's message, and the
 * pile marked in the player's item record. */
#define T6T_FORTUNES 4
#define T6T_FORTUNE_VARIANTS 4
#define T6T_FORTUNE_PART_STEP 16
#define T6T_FORTUNE_LETTER_MESSAGE 0
#define T6T_FORTUNE_PILE_ITEM 0x1d
#define T6T_FORTUNE_PILE_COUNT 4

/* The clock: December, the last hour of the year and its minutes, and the hour January's
 * fortune starts. */
#define T6T_DECEMBER 12
#define T6T_LAST_HOUR 23
#define T6T_HALF_HOUR 30
#define T6T_FIVE_MINUTES_LEFT 55
#define T6T_LAST_MINUTE 59
#define T6T_MORNING_HOUR 6

/* The talk scene's vtable slot its talks call first (SceneBase_Reset). */
#define T6T_TALK_SLOT_08 0x08

static u8 t6t_line_shown(const Turtle6Talk *talk)
{
    return ((const MessageReceiver *) (const void *) talk)->message;
}

static TalkObject *t6t_talk_object(Turtle6Talk *talk)
{
    return (TalkObject *) (void *) talk->base.talk;
}

static SceneCommandScene *t6t_scene(Turtle6Talk *talk)
{
    return (SceneCommandScene *) (void *) talk;
}

/* Message `message` of the file `name` shown in `object`. */
static void t6t_say(TalkObject *object, u8 message, const char *name)
{
    TalkObject_SetMessage(object, &message, name);
}

/* func_ov086_02278ab8 (slot 0x18, the player's answer): only while the pockets hold the item
 * 0x37e0: line 0 answered 0 takes it (its slot emptied, the scene's motion 14 with it) and
 * line 2 of "sp_npc_turtle" follows. */
void Turtle6Talk_OnAnswer(Turtle6Talk *talk)
{
    unsigned int answer = TalkAnswers_Picked((TalkAnswers *) (uintptr_t) (u32) SceneBase_TalkChoices(&talk->base));
    int slot = talk->item_slot;
    if (slot < 0) {
        return;
    }
    if (t6t_line_shown(talk) == TURTLE6_COMMON_LINE_ASK && answer == 0) {
        CurrentPockets_Empty(slot);
        u16 item = T6T_ASKED_ITEM;
        SceneCommand_RequestMotion14(t6t_scene(talk), &item, 0, T6T_MOTION_B, 0);
        t6t_say(t6t_talk_object(talk), TURTLE6_COMMON_LINE_TAKEN, data_ov086_02279438);
    }
}
CLEAN_AS(func_ov086_02278ab8, Turtle6Talk_OnAnswer)

/* The fortune letter written into `letter` for the player of `record`: a fortune drawn, part
 * 0 its message of "st_fortune", parts 1-3 a message of "st_fortune2" each (a fifth number is
 * drawn after the last part and not used), then the letter from message 0 of "ev_fortune"; a
 * pile of item 0x1d marked in the player's item record, flag 4 set and the scene's motion 13
 * with the letters (item 0x1565). */
static void t6t_write_fortune(Turtle6Talk *talk, Letter *letter, u8 *record)
{
    MessagePart text;
    MessagePart_Construct(&text);
    int fortune = (int) MainRandom_Below(T6T_FORTUNES);
    int message = fortune;
    for (int i = 0; i < TURTLE6_FORTUNE_PARTS; i++) {
        u8 number = (u8) message;
        const Turtle6FortunePart *part = &data_ov086_022791d0[i];
        MessageReader_LoadMessage(&text, &number, (const char *) (uintptr_t) part->name);
        MailText_SetPartText(part->part, &text);
        message = fortune * T6T_FORTUNE_VARIANTS + (int) MainRandom_Below(T6T_FORTUNE_VARIANTS) + i * T6T_FORTUNE_PART_STEP;
    }
    u8 letter_message = T6T_FORTUNE_LETTER_MESSAGE;
    Letter_WriteSpecialToPlayer(letter, &letter_message, data_ov086_02279458, data_ov086_02279260, data_ov086_02279264,
                                PlayerRecord_Player(record));
    if (record != NULL) {
        u16 pile = ItemCode_MakePile(T6T_FORTUNE_PILE_ITEM, T6T_FORTUNE_PILE_COUNT);
        ItemRecord_Mark((ItemRecord *) (void *) PlayerRecord_ItemRecord(record), &pile, 0);
    }
    Block021d27ac_SetFlag(&Block021d27ac_Get()->flags, T6T_FLAG_FORTUNE);
    u16 letters = T6T_LETTERS_ITEM;
    SceneCommand_RequestMotion13(t6t_scene(talk), &letters, 0, T6T_MOTION_B, 0);
    MessagePart_Destruct(&text);
}

/* func_ov086_02278b24 (slot 0x14, a line ended):
 * - while the pockets held the item 0x37e0 (lines of "sp_npc_turtle"): lines 1 and 4 end the
 *   exchange; line 2 shows (motion 13) and gives the item 0x1559, then line 4;
 * - else the pockets' free letter is looked for, and by the line:
 *   0x13: with a free letter the fortune letter is written into it, line 0x15; else 0x14;
 *   0x19-0x1b: the item 0x137d shown (motion 13) and given, one of lines 0x1c-0x1e.
 * The line, when one was picked, is shown. */
void Turtle6Talk_OnLineEnded(Turtle6Talk *talk)
{
    int next = TURTLE6_NO_LINE;

    if (talk->item_slot >= 0) {
        u8 line = t6t_line_shown(talk);
        if (line == TURTLE6_COMMON_LINE_DONE || line == TURTLE6_COMMON_LINE_GIVEN) {
            talk->item_slot = TURTLE6_TALK_SLOT_DONE;
        }
        if (t6t_line_shown(talk) == TURTLE6_COMMON_LINE_TAKEN) {
            u16 shown = T6T_EXCHANGE_ITEM;
            SceneCommand_RequestMotion13(t6t_scene(talk), &shown, 0, T6T_MOTION_B, 0);
            u16 given = T6T_EXCHANGE_ITEM;
            CurrentPockets_Give(&given, 0);
            t6t_say(t6t_talk_object(talk), TURTLE6_COMMON_LINE_GIVEN, data_ov086_02279438);
        }
        return;
    }

    int letter_index = CurrentPockets_FreeLetterIndex();
    switch (t6t_line_shown(talk)) {
        case TURTLE6_LINE_OFFER_FORTUNE: {
            next = TURTLE6_LINE_NO_LETTER;
            if (letter_index == -1) {
                break;
            }
            Letter *letter = CurrentPockets_FreeLetter();
            if (letter == NULL) {
                break;
            }
            t6t_write_fortune(talk, letter, PlayerRecords_Current());
            next = TURTLE6_LINE_FORTUNE;
            break;
        }
        case TURTLE6_LINE_GIFT:
        case TURTLE6_LINE_GIFT + 1:
        case TURTLE6_LINE_GIFT + 2: {
            u16 shown = T6T_GIFT;
            SceneCommand_RequestMotion13(t6t_scene(talk), &shown, 0, T6T_MOTION_B, 0);
            u16 given = T6T_GIFT;
            CurrentPockets_Give(&given, 0);
            next = (u8) (MainRandom_Below(3) + TURTLE6_LINE_GIVEN);
            break;
        }
        default:
            break;
    }
    if (next != TURTLE6_NO_LINE) {
        t6t_say(t6t_talk_object(talk), (u8) next, data_ov086_02279448);
    }
}
CLEAN_AS(func_ov086_02278b24, Turtle6Talk_OnLineEnded)

/* A number below 3 moved up by `by` unless it is 0. */
static u8 t6t_zero_or(u8 by)
{
    u8 number = (u8) MainRandom_Below(3);
    if (number != 0) {
        number += by;
    }
    return number;
}

/* func_ov086_02278cf0 (slot 0x78, the line the talk starts with), of "sp_npc_turtle6" unless
 * said otherwise. The current player's villager part is looked up first (and not used).
 * - The pockets are looked through for the item 0x37e0 once a talk (Turtle6Talk.item_slot);
 *   when they hold it, line 0 of "sp_npc_turtle".
 * - In December, by the clock: in the morning one of lines 0-2, in the afternoon 0, 3 or 4,
 *   before 23:00 0, 5 or 6, before 23:30 0, 7 or 8, before 23:55 9-11; before 23:59 0x0c-0x0d
 *   and at 23:59 0x0e-0x0f, both final.
 * - In another month (January 1), all final: before 6:00 one of 0x10-0x12; once the fortune
 *   was written (flag 4) one of 0x16-0x18; else line 0x13.
 * A line that is not final is, when the pockets have a free slot, one of 0x19-0x1b half the
 * time. */
void Turtle6Talk_FirstLine(Turtle6Talk *talk, Turtle6Line *out)
{
    (void) PlayerRecord_VillagerPart(PlayerRecords_Current());
    out->text = (u32) (uintptr_t) data_ov086_02279448;

    if (talk->item_slot == TURTLE6_TALK_SLOT_UNKNOWN) {
        u16 asked = T6T_ASKED_ITEM;
        talk->item_slot = CurrentPockets_FindItem(&asked);
        if (talk->item_slot >= 0) {
            out->text = (u32) (uintptr_t) data_ov086_02279438;
            out->message = TURTLE6_COMMON_LINE_ASK;
            return;
        }
    }

    Date today;
    Calendar_Today(&today);
    DateTime now = {0};
    DateTime_Now(&now);

    if (today.month == T6T_DECEMBER) {
        if (Calendar_PartOfDay() == PART_OF_DAY_MORNING) {
            out->message = (u8) MainRandom_Below(3);
        } else if (Calendar_PartOfDay() == PART_OF_DAY_AFTERNOON) {
            out->message = t6t_zero_or(2);
        } else if (now.hour < T6T_LAST_HOUR) {
            out->message = t6t_zero_or(4);
        } else if (now.hour == T6T_LAST_HOUR && now.minute < T6T_HALF_HOUR) {
            out->message = t6t_zero_or(6);
        } else if (now.hour == T6T_LAST_HOUR && now.minute < T6T_FIVE_MINUTES_LEFT) {
            out->message = (u8) (MainRandom_Below(3) + TURTLE6_LINE_HALF_HOUR_LEFT);
        } else if (now.hour == T6T_LAST_HOUR && now.minute < T6T_LAST_MINUTE) {
            out->message = (u8) (MainRandom_Below(2) + TURTLE6_LINE_MINUTES_LEFT);
            return;
        } else {
            out->message = (u8) (MainRandom_Below(2) + TURTLE6_LINE_LAST_MINUTE);
            return;
        }
    } else {
        if (now.hour < T6T_MORNING_HOUR) {
            out->message = (u8) (MainRandom_Below(3) + TURTLE6_LINE_EARLY);
        } else if (Block021d27ac_TestFlag(&Block021d27ac_Get()->flags, T6T_FLAG_FORTUNE) != 0) {
            out->message = (u8) (MainRandom_Below(3) + TURTLE6_LINE_AFTER_FORTUNE);
        } else {
            out->message = TURTLE6_LINE_OFFER_FORTUNE;
        }
        return;
    }

    if (CurrentPockets_FreeSlot() == -1) {
        return;
    }
    if (MainRandom_Below(2) != 0) {
        return;
    }
    out->message = (u8) (MainRandom_Below(3) + TURTLE6_LINE_GIFT);
}
CLEAN_AS(func_ov086_02278cf0, Turtle6Talk_FirstLine)

/* func_ov086_02278e6c: his talk scene told through its vtable slot 0x08 and given its owner,
 * the pockets not looked through yet. */
void Turtle6Talk_Begin(Turtle6Talk *talk, Turtle6 *owner)
{
    u32 vtable = *(const u32 *) (const void *) talk;
    u32 code = *(const u32 *) (uintptr_t) (vtable + T6T_TALK_SLOT_08);
    ((void (*)(Turtle6Talk *))(uintptr_t) code)(talk);
    talk->owner = owner;
    talk->item_slot = TURTLE6_TALK_SLOT_UNKNOWN;
}
CLEAN_AS(func_ov086_02278e6c, Turtle6Talk_Begin)

/* func_ov086_02278e90 (slot 0x04): its destructor (the scene class 0x020d9ff8's), then the
 * scene freed. */
void *Turtle6Talk_Delete(void *talk)
{
    Turtle6Talk *self = talk;
    self->base.vtable = data_ov086_022792fc;
    Obj020d9ff8_DestructBody(self);
    Heap_OperatorDeleteB(self);
    return self;
}
CLEAN_AS(func_ov086_02278e90, Turtle6Talk_Delete)

/* func_ov086_02278eb0 (slot 0x00): the scene class 0x020d9ff8's destructor. */
void *Turtle6Talk_Destroy(void *talk)
{
    Turtle6Talk *self = talk;
    self->base.vtable = data_ov086_022792fc;
    Obj020d9ff8_DestructBody(self);
    return self;
}
CLEAN_AS(func_ov086_02278eb0, Turtle6Talk_Destroy)

/* func_ov086_02278ec8: the constructor: a scene of class 0x020d9ff8 given this class's
 * vtable. */
Turtle6Talk *Turtle6Talk_Construct(Turtle6Talk *talk)
{
    Obj020d9ff8_Construct(talk);
    talk->base.vtable = data_ov086_022792fc;
    return talk;
}
CLEAN_AS(func_ov086_02278ec8, Turtle6Talk_Construct)
