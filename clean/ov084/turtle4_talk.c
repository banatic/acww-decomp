/* The talk scene of overlay 84's turtle: his lines, the items he hands out and the fortune
 * letter (turtle4_talk.h). */
#include "turtle4_talk.h"

#include <stdint.h>

#include "autoload_2/heap.h"
#include "clean.h"
#include "main/activity_vars.h"
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
#include "main/player_actor_ops.h"
#include "main/player_field_2416.h"
#include "main/player_id.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/scene_base.h"
#include "main/scene_command.h"
#include "main/talk_answers.h"
#include "main/talk_checks.h"
#include "main/talk_object.h"

static_assert(sizeof(SceneBase) == 0x80, "scene base");
static_assert(offsetof(Turtle4Talk, owner) == 0xb0, "owner");
static_assert(offsetof(Turtle4Talk, item_slot) == 0xb4, "item slot");
static_assert(offsetof(Turtle4Talk, unk_b8) == 0xb8, "item code");
static_assert(sizeof(Turtle4Line) == 8, "a line");
static_assert(sizeof(Turtle4FortunePart) == 8, "a part of the fortune");
static_assert(sizeof(MessageReceiver) == 0x20 && offsetof(MessageReceiver, message) == 0x1e, "the line shown");

/* The talk scene's vtable. */
extern const u8 data_ov084_0227941c[];
/* The message files: "sp_npc_turtle4" (his) and "sp_npc_turtle" (the turtle's common one). */
extern const char data_ov084_02279558[];
extern const char data_ov084_02279568[];
/* The fortune letter: its message file "ev_fortune", its tag and paper, and the files of its
 * parts ("st_fortune" for part 0, "st_fortune2" for parts 1-3). */
extern const char data_ov084_02279578[];
extern const u8 data_ov084_02279384[];
extern const u8 data_ov084_02279380[];
extern const Turtle4FortunePart data_ov084_022792fc[TURTLE4_FORTUNE_PARTS];

/* The items exchanged while the pockets hold the item 0x37e0. */
#define T4T_ASKED_ITEM 0x37e0
#define T4T_EXCHANGE_ITEM 0x1559

/* The two items he hands out, and the most of them one player gets (the tally's cap). */
#define T4T_GIFT_A 0x137e
#define T4T_GIFT_B 0x137f
#define T4T_GIFTS_MAX 10

/* The item the scene's motion holds up after the fortune letter (the letters). */
#define T4T_LETTERS_ITEM 0x1565

/* The values the item motions (SceneCommand_RequestMotion13 and 14) are asked with, and the
 * kind of the item name put in the talk's part 0. */
#define T4T_MOTION_B 5
#define T4T_NAME_KIND 7

/* The current player's daily bit of a talk with him. */
#define T4T_DAILY_TALKED 0x1e

/* The flags of the object at data_021d27ac: the greeting said, the fortune written. */
#define T4T_FLAG_GREETED 2
#define T4T_FLAG_FORTUNE 3

/* The fortune: one of four, its part 0 from message 8 on of "st_fortune", each later part one
 * of four messages of "st_fortune2", 16 apart from part to part; the letter's message, and the
 * pile marked in the player's item record. */
#define T4T_FORTUNES 4
#define T4T_FORTUNE_FIRST_MESSAGE 8
#define T4T_FORTUNE_VARIANTS 4
#define T4T_FORTUNE_PART_STEP 16
#define T4T_FORTUNE_LETTER_MESSAGE 1
#define T4T_FORTUNE_PILE_ITEM 0x1d
#define T4T_FORTUNE_PILE_COUNT 4

/* The Saturdays (weekday 6) of the greeting, and the fifth one the month may have. */
#define T4T_SATURDAY 6
#define T4T_FIFTH 5

/* The talk scene's vtable slot its talks call first (SceneBase_Reset). */
#define T4T_TALK_SLOT_08 0x08

static u8 t4t_line_shown(const Turtle4Talk *talk)
{
    return ((const MessageReceiver *) (const void *) talk)->message;
}

static TalkObject *t4t_talk_object(Turtle4Talk *talk)
{
    return (TalkObject *) (void *) talk->base.talk;
}

static SceneCommandScene *t4t_scene(Turtle4Talk *talk)
{
    return (SceneCommandScene *) (void *) talk;
}

/* Message `message` of the file `name` shown in `object`. */
static void t4t_say(TalkObject *object, u8 message, const char *name)
{
    TalkObject_SetMessage(object, &message, name);
}

static Block021d27ac *t4t_block(void)
{
    return Block021d27ac_Get();
}

/* Whether the pockets lack `item`. */
static int t4t_lacks(u16 item)
{
    return CurrentPockets_FindItem(&item) == -1;
}

/* The fortune letter written into `letter` for the player of `record`: a fortune drawn, part
 * 0 its message of "st_fortune", parts 1-3 a message of "st_fortune2" each (a fifth number is
 * drawn after the last part and not used), then the letter from message 1 of "ev_fortune"; a
 * pile of item 0x1d marked in the player's item record, and flag 3 set. */
static void t4t_write_fortune(Letter *letter, u8 *record)
{
    MessagePart text;
    MessagePart_Construct(&text);
    int fortune = (int) MainRandom_Below(T4T_FORTUNES);
    int message = fortune + T4T_FORTUNE_FIRST_MESSAGE;
    for (int i = 0; i < TURTLE4_FORTUNE_PARTS; i++) {
        u8 number = (u8) message;
        const Turtle4FortunePart *part = &data_ov084_022792fc[i];
        MessageReader_LoadMessage(&text, &number, (const char *) (uintptr_t) part->name);
        MailText_SetPartText(part->part, &text);
        message = fortune * T4T_FORTUNE_VARIANTS + (int) MainRandom_Below(T4T_FORTUNE_VARIANTS) + i * T4T_FORTUNE_PART_STEP;
    }
    u8 letter_message = T4T_FORTUNE_LETTER_MESSAGE;
    Letter_WriteSpecialToPlayer(letter, &letter_message, data_ov084_02279578, data_ov084_02279384, data_ov084_02279380,
                                PlayerRecord_Player(record));
    if (record != NULL) {
        u16 pile = ItemCode_MakePile(T4T_FORTUNE_PILE_ITEM, T4T_FORTUNE_PILE_COUNT);
        ItemRecord_Mark((ItemRecord *) (void *) PlayerRecord_ItemRecord(record), &pile, 0);
    }
    Block021d27ac_SetFlag(&t4t_block()->flags, T4T_FLAG_FORTUNE);
    MessagePart_Destruct(&text);
}

/* func_ov084_02278ab8 (slot 0x18, the player's answer):
 * - while the pockets hold the item 0x37e0: line 0 answered 0 takes it (its slot emptied, the
 *   scene's motion 14 with it) and line 2 of "sp_npc_turtle" follows;
 * - else line 7 answered 0: with a free letter in the pockets the fortune letter is written
 *   into it, line 9; else line 0x0c.
 * The line, when one was picked, is shown. */
void Turtle4Talk_OnAnswer(Turtle4Talk *talk)
{
    unsigned int answer = TalkAnswers_Picked((TalkAnswers *) (uintptr_t) (u32) SceneBase_TalkChoices(&talk->base));
    int next = TURTLE4_NO_LINE;
    int slot = talk->item_slot;

    if (slot >= 0) {
        if (t4t_line_shown(talk) == TURTLE4_COMMON_LINE_ASK && answer == 0) {
            CurrentPockets_Empty(slot);
            u16 item = T4T_ASKED_ITEM;
            SceneCommand_RequestMotion14(t4t_scene(talk), &item, 0, T4T_MOTION_B, 0);
            next = TURTLE4_COMMON_LINE_TAKEN;
        }
        if (next != TURTLE4_NO_LINE) {
            t4t_say(t4t_talk_object(talk), (u8) next, data_ov084_02279568);
        }
        return;
    }

    if (t4t_line_shown(talk) == TURTLE4_LINE_OFFER_FORTUNE && answer == 0) {
        next = TURTLE4_LINE_NO_LETTER;
        if (CurrentPockets_FreeLetterIndex() != -1) {
            Letter *letter = CurrentPockets_FreeLetter();
            if (letter != NULL) {
                next = TURTLE4_LINE_FORTUNE;
                t4t_write_fortune(letter, PlayerRecords_Current());
            }
        }
    }
    if (next != TURTLE4_NO_LINE) {
        t4t_say(t4t_talk_object(talk), (u8) next, data_ov084_02279558);
    }
}
CLEAN_AS(func_ov084_02278ab8, Turtle4Talk_OnAnswer)

/* The item he hands out: the one of 0x137e and 0x137f the pockets lack (0x137f when they have
 * both, one of the two at random when they have neither). */
static u16 t4t_pick_gift(void)
{
    if (t4t_lacks(T4T_GIFT_A) && t4t_lacks(T4T_GIFT_B)) {
        return MainRandom_Below(2) == 0 ? T4T_GIFT_B : T4T_GIFT_A;
    }
    return t4t_lacks(T4T_GIFT_A) ? T4T_GIFT_A : T4T_GIFT_B;
}

/* func_ov084_02278c18 (slot 0x14, a line ended):
 * - while the pockets held the item 0x37e0 (lines of "sp_npc_turtle"): lines 1 and 4 end the
 *   exchange; line 2 shows (motion 13) and gives the item 0x1559, then line 4;
 * - lines 0, 1, 2 and 6: the gift (t4t_pick_gift). With a free slot in the pockets and fewer
 *   than ten given to the player, the tally is raised, the item shown, given and its name put
 *   in the talk's part 0: line 3, or 4 when byte 0x1c of the player is not 0; with ten given,
 *   line 0x0b; with no free slot, its name only: line 5;
 * - line 9: the scene's motion 13 with the letters (item 0x1565), line 0x0a.
 * The line, when one was picked, is shown. */
void Turtle4Talk_OnLineEnded(Turtle4Talk *talk)
{
    int next = TURTLE4_NO_LINE;

    if (talk->item_slot >= 0) {
        u8 line = t4t_line_shown(talk);
        if (line == TURTLE4_COMMON_LINE_DONE || line == TURTLE4_COMMON_LINE_GIVEN) {
            talk->item_slot = TURTLE4_TALK_SLOT_DONE;
        }
        if (t4t_line_shown(talk) != TURTLE4_COMMON_LINE_TAKEN) {
            return;
        }
        u16 shown = T4T_EXCHANGE_ITEM;
        SceneCommand_RequestMotion13(t4t_scene(talk), &shown, 0, T4T_MOTION_B, 0);
        u16 given = T4T_EXCHANGE_ITEM;
        CurrentPockets_Give(&given, 0);
        t4t_say(t4t_talk_object(talk), TURTLE4_COMMON_LINE_GIVEN, data_ov084_02279568);
        return;
    }

    switch (t4t_line_shown(talk)) {
        case TURTLE4_LINE_FIRST_SATURDAY:
        case TURTLE4_LINE_SATURDAY:
        case TURTLE4_LINE_LAST_SATURDAY:
        case TURTLE4_LINE_NOT_BOTH: {
            int free_slot = CurrentPockets_FreeSlot();
            u16 gift = t4t_pick_gift();
            if (free_slot >= 0) {
                PlayerField2416 *field = (PlayerField2416 *) (void *) PlayerRecord_Field2416(PlayerRecords_Current());
                if ((u32) PlayerField2416_Tally(field) < T4T_GIFTS_MAX) {
                    PlayerField2416_RaiseTally(field);
                    int other = PlayerId_Byte1c((const s8 *) (const void *) PlayerRecord_Player(PlayerRecords_Current()));
                    SceneCommand_RequestMotion13(t4t_scene(talk), &gift, 0, T4T_MOTION_B, 0);
                    CurrentPockets_Give(&gift, 0);
                    SceneBase_PutItemName(&talk->base, (int) (u32) (uintptr_t) &gift, 0, T4T_NAME_KIND);
                    next = other == 0 ? TURTLE4_LINE_GIVEN : TURTLE4_LINE_GIVEN_OTHER;
                } else {
                    next = TURTLE4_LINE_ALL_GIVEN;
                }
            } else {
                SceneBase_PutItemName(&talk->base, (int) (u32) (uintptr_t) &gift, 0, T4T_NAME_KIND);
                next = TURTLE4_LINE_NO_ROOM;
            }
            break;
        }
        case TURTLE4_LINE_FORTUNE: {
            u16 letters = T4T_LETTERS_ITEM;
            SceneCommand_RequestMotion13(t4t_scene(talk), &letters, 0, T4T_MOTION_B, 0);
            next = TURTLE4_LINE_FORTUNE_SENT;
            break;
        }
        default:
            break;
    }
    if (next != TURTLE4_NO_LINE) {
        t4t_say(t4t_talk_object(talk), (u8) next, data_ov084_02279558);
    }
}
CLEAN_AS(func_ov084_02278c18, Turtle4Talk_OnLineEnded)

/* func_ov084_02278dec (slot 0x78, the line the talk starts with), of "sp_npc_turtle4" unless
 * said otherwise. The current player's villager part is looked up first (and not used).
 * - The pockets are looked through for the item 0x37e0 once a talk (Turtle4Talk.item_slot);
 *   when they hold it, line 0 of "sp_npc_turtle".
 * - A later talk of the day (daily bit 0x1e set): line 6 unless the pockets have both items
 *   0x137e and 0x137f or the player holds one of them; then line 7 until the fortune was
 *   written (flag 3), after it one of lines 0x0d-0x10.
 * - The first talk of the day (daily bit 0x1e set now), unless the greeting was said (flag 2,
 *   set now): line 0 on the month's first Saturday, 2 on its last one (the fifth, or the
 *   fourth when there is no fifth), else 1.
 * QUIRK: when the greeting was said the message is left as it was. */
void Turtle4Talk_FirstLine(Turtle4Talk *talk, Turtle4Line *out)
{
    (void) PlayerRecord_VillagerPart(PlayerRecords_Current());
    out->text = (u32) (uintptr_t) data_ov084_02279558;

    if (talk->item_slot == TURTLE4_TALK_SLOT_UNKNOWN) {
        u16 asked = T4T_ASKED_ITEM;
        talk->item_slot = CurrentPockets_FindItem(&asked);
        if (talk->item_slot >= 0) {
            out->text = (u32) (uintptr_t) data_ov084_02279568;
            out->message = TURTLE4_COMMON_LINE_ASK;
            return;
        }
    }

    if (TalkChecks_TestSetDailyBit(T4T_DAILY_TALKED, 1) != 0) {
        u16 held;
        PlayerActorOps_HeldItem(&held, ActivityVars_Slot3C1C());
        int ready = !t4t_lacks(T4T_GIFT_A) && !t4t_lacks(T4T_GIFT_B);
        if (!ready && !(held >= T4T_GIFT_A && held <= T4T_GIFT_B)) {
            out->message = TURTLE4_LINE_NOT_BOTH;
            return;
        }
        if (Block021d27ac_TestFlag(&t4t_block()->flags, T4T_FLAG_FORTUNE) == 0) {
            out->message = TURTLE4_LINE_OFFER_FORTUNE;
            return;
        }
        out->message = (u8) (MainRandom_Below(4) + TURTLE4_LINE_AFTER_FORTUNE);
        return;
    }

    if (Block021d27ac_TestFlag(&t4t_block()->flags, T4T_FLAG_GREETED) != 0) {
        return;
    }
    Block021d27ac_SetFlag(&t4t_block()->flags, T4T_FLAG_GREETED);
    if (talk->owner->week == 1) {
        out->message = TURTLE4_LINE_FIRST_SATURDAY;
        return;
    }
    DateTime now = {0};
    DateTime_Now(&now);
    u8 last_week = Calendar_NthWeekday(now.year, now.month, T4T_SATURDAY, T4T_FIFTH) == -1 ? 4 : 5;
    out->message = talk->owner->week < last_week ? TURTLE4_LINE_SATURDAY : TURTLE4_LINE_LAST_SATURDAY;
}
CLEAN_AS(func_ov084_02278dec, Turtle4Talk_FirstLine)

/* func_ov084_02278f60: his talk scene told through its vtable slot 0x08 and given its owner,
 * the pockets not looked through yet. */
void Turtle4Talk_Begin(Turtle4Talk *talk, Turtle4 *owner)
{
    u32 vtable = *(const u32 *) (const void *) talk;
    u32 code = *(const u32 *) (uintptr_t) (vtable + T4T_TALK_SLOT_08);
    ((void (*)(Turtle4Talk *))(uintptr_t) code)(talk);
    talk->owner = owner;
    talk->item_slot = TURTLE4_TALK_SLOT_UNKNOWN;
}
CLEAN_AS(func_ov084_02278f60, Turtle4Talk_Begin)

/* func_ov084_02278f84 (slot 0x04): its destructor (the scene class 0x020d9ff8's), then the
 * scene freed. */
void *Turtle4Talk_Delete(void *talk)
{
    Turtle4Talk *self = talk;
    self->base.vtable = data_ov084_0227941c;
    Obj020d9ff8_DestructBody(self);
    Heap_OperatorDeleteB(self);
    return self;
}
CLEAN_AS(func_ov084_02278f84, Turtle4Talk_Delete)

/* func_ov084_02278fa4 (slot 0x00): the scene class 0x020d9ff8's destructor. */
void *Turtle4Talk_Destroy(void *talk)
{
    Turtle4Talk *self = talk;
    self->base.vtable = data_ov084_0227941c;
    Obj020d9ff8_DestructBody(self);
    return self;
}
CLEAN_AS(func_ov084_02278fa4, Turtle4Talk_Destroy)

/* func_ov084_02278fbc: the constructor: a scene of class 0x020d9ff8 given this class's vtable,
 * and its item code 0xfff1. */
Turtle4Talk *Turtle4Talk_Construct(Turtle4Talk *talk)
{
    Obj020d9ff8_Construct(talk);
    talk->base.vtable = data_ov084_0227941c;
    talk->unk_b8 = ITEM_CODE_NONE;
    return talk;
}
CLEAN_AS(func_ov084_02278fbc, Turtle4Talk_Construct)
