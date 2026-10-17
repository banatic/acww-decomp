/* The garden judge's talk scene (turtle_gardens_talk.h): its class, its lines, the player's
 * answers and the prize. */
#include "turtle_gardens_talk.h"

#include <stdint.h>

#include "autoload_2/heap.h"
#include "clean.h"
#include "main/block_021d27ac.h"
#include "main/calendar.h"
#include "main/current_pockets.h"
#include "main/date_time.h"
#include "main/main_random.h"
#include "main/message_receiver.h"
#include "main/obj_020d9ff8.h"
#include "main/player_field_2416.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/scene_base.h"
#include "main/scene_command.h"
#include "main/shops.h"
#include "main/talk_answers.h"
#include "main/talk_checks.h"
#include "main/talk_object.h"

static_assert(sizeof(SceneBase) == 0x80, "scene base");
static_assert(offsetof(TurtleGardensTalk, owner) == 0xb0 && offsetof(TurtleGardensTalk, slot_37e0) == 0xb4,
              "TurtleGardensTalk");
static_assert(offsetof(TurtleGardensTalk, prize) == 0xb8 && sizeof(TurtleGardensTalk) == 0xbc, "TurtleGardensTalk");
static_assert(sizeof(TurtleGardensTalkStart) == 8, "what a talk starts with");

/* The vtable of its class. */
extern const u8 data_ov083_022791fc[];
/* Its message files, "sp_npc_turtle3" and the shared "sp_npc_turtle". */
extern const char data_ov083_02279338[];
extern const char data_ov083_02279348[];

#define TURTLE_GARDENS_TALK_NO_ITEM 0xfff1
#define TURTLE_GARDENS_TALK_NO_LINE 0xff

/* The vtable slot of the scene that resets it (the scene base's reset). */
#define TURTLE_GARDENS_TALK_SLOT_RESET 0x08

/* The item he takes and the one he gives for it. */
#define TURTLE_GARDENS_TALK_ITEM_37E0 0x37e0
#define TURTLE_GARDENS_TALK_ITEM_1559 0x1559

/* The current player's daily bit of his prize. */
#define TURTLE_GARDENS_TALK_DAILY_BIT 0x1d

/* The flag of main's object at data_021d27ac set the first time he is talked to. */
#define TURTLE_GARDENS_TALK_BLOCK_FLAG 1

/* The hours he talks of the gardens: from 6:00 to before 18:00. */
#define TURTLE_GARDENS_TALK_FIRST_HOUR 6
#define TURTLE_GARDENS_TALK_END_HOUR 18

/* The last of the days of event 0x0e after its first with line 2. */
#define TURTLE_GARDENS_TALK_EARLY_DAYS_LAST 5

/* The values its item motions (SceneCommand_RequestMotion13 and 14) are asked with, the talk's
 * slot the prize's name is put in and the kind it is put as. */
#define TURTLE_GARDENS_TALK_MOTION_B 5
#define TURTLE_GARDENS_TALK_SLOT_PRIZE 0
#define TURTLE_GARDENS_TALK_ITEM_KIND 7

/* The answers to line 0xa: one time in TURTLE_GARDENS_TALK_ONE_IN line 0xc, else one of the
 * TURTLE_GARDENS_TALK_RANDOM_COUNT lines from 0x1c. */
#define TURTLE_GARDENS_TALK_ONE_IN 3
#define TURTLE_GARDENS_TALK_RANDOM_COUNT 0x0b

/* Its lines (the receiver's message), of "sp_npc_turtle3" unless said. */
#define TURTLE_GARDENS_TALK_LINE_OFF_HOURS 0
#define TURTLE_GARDENS_TALK_LINE_FIRST_DAY 1
#define TURTLE_GARDENS_TALK_LINE_EARLY_DAYS 2
#define TURTLE_GARDENS_TALK_LINE_LATER_DAYS 3
#define TURTLE_GARDENS_TALK_LINE_PRIZE_5 5
#define TURTLE_GARDENS_TALK_LINE_PRIZE_6 6
#define TURTLE_GARDENS_TALK_LINE_PRIZE 7
#define TURTLE_GARDENS_TALK_LINE_PRIZE_GIVEN 8
#define TURTLE_GARDENS_TALK_LINE_PRIZE_9 9
#define TURTLE_GARDENS_TALK_LINE_AGAIN 0x0a
#define TURTLE_GARDENS_TALK_LINE_AGAIN_SOMETIMES 0x0c
#define TURTLE_GARDENS_TALK_LINE_RANDOM_FIRST 0x1c
/* Of "sp_npc_turtle": the item 0x37e0 asked about, taken, and the item 0x1559 given. */
#define TURTLE_GARDENS_TALK_LINE_37E0_ASK 0
#define TURTLE_GARDENS_TALK_LINE_37E0_ANSWER_1 1
#define TURTLE_GARDENS_TALK_LINE_37E0_TAKEN 2
#define TURTLE_GARDENS_TALK_LINE_37E0_ANSWER_4 4

static TalkObject *turtle_gardens_talk_object(TurtleGardensTalk *talk)
{
    return (TalkObject *) (void *) talk->base.talk;
}

static SceneCommandScene *turtle_gardens_talk_scene(TurtleGardensTalk *talk)
{
    return (SceneCommandScene *) (void *) talk;
}

/* The line shown. */
static u8 turtle_gardens_talk_shown(const TurtleGardensTalk *talk)
{
    return ((const MessageReceiver *) (const void *) talk)->message;
}

/* The talk shows `line` of `file` unless it is TURTLE_GARDENS_TALK_NO_LINE. */
static void turtle_gardens_talk_say_unless_none(TurtleGardensTalk *talk, u8 line, const char *file)
{
    if (line != TURTLE_GARDENS_TALK_NO_LINE) {
        u8 message = line;
        TalkObject_SetMessage(turtle_gardens_talk_object(talk), &message, file);
    }
}

/* ---- The class */

/* func_ov083_02278d44 (vtable slot 0x04): the destructor of the scene class it derives from,
 * then the scene freed. */
TurtleGardensTalk *TurtleGardensTalk_DestructDelete(TurtleGardensTalk *talk)
{
    talk->base.vtable = data_ov083_022791fc;
    Obj020d9ff8_DestructBody(talk);
    Heap_OperatorDeleteB(talk);
    return talk;
}
CLEAN_AS(func_ov083_02278d44, TurtleGardensTalk_DestructDelete)

/* func_ov083_02278d64 (vtable slot 0x00): the destructor of the scene class it derives from. */
TurtleGardensTalk *TurtleGardensTalk_Destruct(TurtleGardensTalk *talk)
{
    talk->base.vtable = data_ov083_022791fc;
    Obj020d9ff8_DestructBody(talk);
    return talk;
}
CLEAN_AS(func_ov083_02278d64, TurtleGardensTalk_Destruct)

/* func_ov083_02278d7c: the constructor: a scene of class 0x020d9ff8 given this class's vtable;
 * no prize. */
TurtleGardensTalk *TurtleGardensTalk_Construct(TurtleGardensTalk *talk)
{
    Obj020d9ff8_Construct(talk);
    talk->base.vtable = data_ov083_022791fc;
    talk->prize = TURTLE_GARDENS_TALK_NO_ITEM;
    return talk;
}
CLEAN_AS(func_ov083_02278d7c, TurtleGardensTalk_Construct)

/* func_ov083_02278d20: the scene reset (its vtable slot 0x08) and given its owner; the item
 * 0x37e0 is not looked for yet. */
void TurtleGardensTalk_Begin(TurtleGardensTalk *talk, TurtleGardens *owner)
{
    u32 vtable = *(const u32 *) (const void *) talk;
    u32 code = *(const u32 *) (uintptr_t) (vtable + TURTLE_GARDENS_TALK_SLOT_RESET);
    ((void (*)(TurtleGardensTalk *))(uintptr_t) code)(talk);
    talk->owner = owner;
    talk->slot_37e0 = TURTLE_GARDENS_TALK_37E0_UNKNOWN;
}
CLEAN_AS(func_ov083_02278d20, TurtleGardensTalk_Begin)

/* ---- Its lines */

/* func_ov083_02278c60 (vtable slot 0x78): see turtle_gardens_talk.h.
 * QUIRK: the current player's villager part is asked for and not used. */
void TurtleGardensTalk_Line(TurtleGardensTalk *talk, TurtleGardensTalkStart *out)
{
    PlayerRecord_VillagerPart(PlayerRecords_Current());
    out->name = data_ov083_02279338;
    if (talk->slot_37e0 == TURTLE_GARDENS_TALK_37E0_UNKNOWN) {
        u16 item_37e0 = TURTLE_GARDENS_TALK_ITEM_37E0;
        talk->slot_37e0 = CurrentPockets_FindItem(&item_37e0);
        if (talk->slot_37e0 >= 0) {
            out->name = data_ov083_02279348;
            out->message = TURTLE_GARDENS_TALK_LINE_37E0_ASK;
            return;
        }
    }
    DateTime now = {0};
    DateTime_Now(&now);
    if (now.hour < TURTLE_GARDENS_TALK_FIRST_HOUR || now.hour >= TURTLE_GARDENS_TALK_END_HOUR) {
        out->message = TURTLE_GARDENS_TALK_LINE_OFF_HOURS;
        return;
    }
    if (Block021d27ac_TestFlag((u32 *) (void *) Block021d27ac_Get(), TURTLE_GARDENS_TALK_BLOCK_FLAG) != 0) {
        out->message = TURTLE_GARDENS_TALK_LINE_AGAIN;
        return;
    }
    Block021d27ac_SetFlag((u32 *) (void *) Block021d27ac_Get(), TURTLE_GARDENS_TALK_BLOCK_FLAG);
    u8 day = talk->owner->event_day;
    if (day == 0) {
        out->message = TURTLE_GARDENS_TALK_LINE_FIRST_DAY;
    } else if (day <= TURTLE_GARDENS_TALK_EARLY_DAYS_LAST) {
        out->message = TURTLE_GARDENS_TALK_LINE_EARLY_DAYS;
    } else {
        out->message = TURTLE_GARDENS_TALK_LINE_LATER_DAYS;
    }
}
CLEAN_AS(func_ov083_02278c60, TurtleGardensTalk_Line)

/* func_ov083_02278ab8 (vtable slot 0x18, the player answered): see turtle_gardens_talk.h.
 * With the item 0x37e0 in the pockets, the first answer to line 0 empties its pocket and he
 * takes it: line 2 of "sp_npc_turtle". */
void TurtleGardensTalk_OnAnswer(TurtleGardensTalk *talk)
{
    unsigned int answer = TalkAnswers_Picked((TalkAnswers *) (uintptr_t) (u32) SceneBase_TalkChoices(&talk->base));
    s32 slot = talk->slot_37e0;
    u8 shown = turtle_gardens_talk_shown(talk);

    if (slot >= 0) {
        if (shown == TURTLE_GARDENS_TALK_LINE_37E0_ASK && answer == 0) {
            CurrentPockets_Empty(slot);
            u16 item = TURTLE_GARDENS_TALK_ITEM_37E0;
            SceneCommand_RequestMotion14(turtle_gardens_talk_scene(talk), &item, 0, TURTLE_GARDENS_TALK_MOTION_B, 0);
            turtle_gardens_talk_say_unless_none(talk, TURTLE_GARDENS_TALK_LINE_37E0_TAKEN, data_ov083_02279348);
        }
        return;
    }

    u8 line = TURTLE_GARDENS_TALK_NO_LINE;
    if (shown == TURTLE_GARDENS_TALK_LINE_AGAIN && answer == 0) {
        if (MainRandom_Below(TURTLE_GARDENS_TALK_ONE_IN) == 0) {
            line = TURTLE_GARDENS_TALK_LINE_AGAIN_SOMETIMES;
        } else {
            line = (u8) (MainRandom_Below(TURTLE_GARDENS_TALK_RANDOM_COUNT) + TURTLE_GARDENS_TALK_LINE_RANDOM_FIRST);
        }
    }
    turtle_gardens_talk_say_unless_none(talk, line, data_ov083_02279338);
}
CLEAN_AS(func_ov083_02278ab8, TurtleGardensTalk_OnAnswer)

/* func_ov083_02278b64 (vtable slot 0x14, a line ended): see turtle_gardens_talk.h. With the
 * item 0x37e0 in the pockets: after line 1 or 4 of "sp_npc_turtle" it is no longer asked
 * about; after line 2 he gives the item 0x1559 (line 4). */
void TurtleGardensTalk_OnLineEnd(TurtleGardensTalk *talk)
{
    u8 shown = turtle_gardens_talk_shown(talk);

    if (talk->slot_37e0 >= 0) {
        if (shown == TURTLE_GARDENS_TALK_LINE_37E0_ANSWER_1 || shown == TURTLE_GARDENS_TALK_LINE_37E0_ANSWER_4) {
            talk->slot_37e0 = TURTLE_GARDENS_TALK_37E0_DONE;
        }
        if (shown == TURTLE_GARDENS_TALK_LINE_37E0_TAKEN) {
            u16 shown_item = TURTLE_GARDENS_TALK_ITEM_1559;
            SceneCommand_RequestMotion13(turtle_gardens_talk_scene(talk), &shown_item, 0, TURTLE_GARDENS_TALK_MOTION_B, 0);
            u16 given = TURTLE_GARDENS_TALK_ITEM_1559;
            CurrentPockets_Give(&given, 0);
            turtle_gardens_talk_say_unless_none(talk, TURTLE_GARDENS_TALK_LINE_37E0_ANSWER_4, data_ov083_02279348);
        }
        return;
    }

    u8 line = TURTLE_GARDENS_TALK_NO_LINE;
    if (shown == TURTLE_GARDENS_TALK_LINE_PRIZE_5 || shown == TURTLE_GARDENS_TALK_LINE_PRIZE_6 ||
        shown == TURTLE_GARDENS_TALK_LINE_PRIZE_9) {
        if (TalkChecks_TestSetDailyBit(TURTLE_GARDENS_TALK_DAILY_BIT, 1) == 0) {
            PlayerField2416_SetGardening((PlayerField2416 *) (void *) PlayerRecord_Field2416(PlayerRecords_Current()));
            if (CurrentPockets_FreeSlot() >= 0) {
                line = TURTLE_GARDENS_TALK_LINE_PRIZE;
                u16 picked;
                Shops_PickRandomItem(&picked);
                talk->prize = picked;
            }
        }
    }
    if (shown == TURTLE_GARDENS_TALK_LINE_PRIZE) {
        SceneCommand_RequestMotion13(turtle_gardens_talk_scene(talk), &talk->prize, 0, TURTLE_GARDENS_TALK_MOTION_B, 0);
        CurrentPockets_Give(&talk->prize, 0);
        SceneBase_PutItemName(&talk->base, (int) (uintptr_t) &talk->prize, TURTLE_GARDENS_TALK_SLOT_PRIZE,
                              TURTLE_GARDENS_TALK_ITEM_KIND);
        line = TURTLE_GARDENS_TALK_LINE_PRIZE_GIVEN;
    }
    turtle_gardens_talk_say_unless_none(talk, line, data_ov083_02279338);
}
CLEAN_AS(func_ov083_02278b64, TurtleGardensTalk_OnLineEnd)
