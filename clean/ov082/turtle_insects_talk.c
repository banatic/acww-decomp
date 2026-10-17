/* The insect contest host's talk scene (turtle_insects_talk.h): its class, its lines, the
 * player's answers, the insect measured and the record of the day. */
#include "turtle_insects_talk.h"

#include <stdint.h>
#include <string.h>

#include "autoload_2/heap.h"
#include "clean.h"
#include "main/calendar.h"
#include "main/current_pockets.h"
#include "main/date_time.h"
#include "main/design.h"
#include "main/event_winner.h"
#include "main/group_params.h"
#include "main/item_lists.h"
#include "main/message_receiver.h"
#include "main/npc_id.h"
#include "main/obj_020d9ff8.h"
#include "main/player_actor_ops.h"
#include "main/player_actors.h"
#include "main/player_field_2416.h"
#include "main/player_id.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/pockets.h"
#include "main/scene_base.h"
#include "main/scene_command.h"
#include "main/state_block.h"
#include "main/talk_answers.h"
#include "main/talk_checks.h"
#include "main/talk_object.h"
#include "ov004/member_pointer.h"

static_assert(sizeof(SceneBase) == 0x80, "scene base");
static_assert(offsetof(TurtleInsectsTalk, owner) == 0xb0 && offsetof(TurtleInsectsTalk, after_command) == 0xb4,
              "TurtleInsectsTalk");
static_assert(offsetof(TurtleInsectsTalk, then_command) == 0xbc && offsetof(TurtleInsectsTalk, item) == 0xc4,
              "TurtleInsectsTalk");
static_assert(offsetof(TurtleInsectsTalk, was_holder) == 0xc6 && offsetof(TurtleInsectsTalk, slot_37e0) == 0xc8,
              "TurtleInsectsTalk");
static_assert(sizeof(TurtleInsectsTalk) == 0xcc, "TurtleInsectsTalk");
static_assert(sizeof(TurtleInsectsTalkStart) == 8, "what a talk starts with");
static_assert(sizeof(ItemList) == 8, "an item list");

/* The vtable of its class. */
extern const u8 data_ov082_0227978c[];
/* Its message files, "sp_npc_turtle2" and the shared "sp_npc_turtle". */
extern const char data_ov082_022798c8[];
extern const char data_ov082_022798d8[];
/* The functions TurtleInsectsTalk_PickCommandFunction picks from: a table filled once (bit 0
 * of the guard word) from the overlay's constants (TurtleInsectsTalk_AfterPockets,
 * TurtleInsectsTalk_NextLine). */
extern u32 data_ov082_02279900;
extern MemberPointer data_ov082_02279904[2];
extern const MemberPointer data_ov082_02279710;
extern const MemberPointer data_ov082_02279708;
/* The null member pointer. */
extern const MemberPointer __ptmf_null;
/* The pockets' predicate, as the game hands it to the pockets' screen (the game's symbol of
 * TurtleInsectsTalk_IsInsect; its result is a halfword where the screen takes an int). */
extern u16 func_ov082_02279168(u16 *item, int state);
/* The town's record of the day's winner and the state block. */
extern EventWinner data_021f3aa4;
extern u32 data_021dc7a8[];

#define TURTLE_INSECTS_TALK_NO_ITEM 0xfff1
#define TURTLE_INSECTS_TALK_NO_LINE 0xff

/* The vtable slot of the scene that resets it (the scene base's reset). */
#define TURTLE_INSECTS_TALK_SLOT_RESET 0x08

/* The insects (items 0x12b0 to 0x12e7), the contest's two nets, the item he takes and the one
 * he gives for it. */
#define TURTLE_INSECTS_TALK_INSECT_FIRST 0x12b0
#define TURTLE_INSECTS_TALK_INSECT_LAST 0x12e7
#define TURTLE_INSECTS_TALK_NET 0x1376
#define TURTLE_INSECTS_TALK_NET_2 0x1377
#define TURTLE_INSECTS_TALK_ITEM_37E0 0x37e0
#define TURTLE_INSECTS_TALK_ITEM_1559 0x1559

/* The current player's daily bit of the contest. */
#define TURTLE_INSECTS_TALK_DAILY_BIT 0x1c

/* The hours of the contest: from 12:00 to before 18:00. */
#define TURTLE_INSECTS_TALK_FIRST_HOUR 12
#define TURTLE_INSECTS_TALK_END_HOUR 18

/* The record's kind for the contest, and the state block's flag of a winner to announce. */
#define TURTLE_INSECTS_TALK_RECORD_KIND EVENT_WINNER_KIND_INSECTS
#define TURTLE_INSECTS_TALK_NOTICE_FLAG 0x0f

/* The pockets' screen: its predicate's argument, and the screen. */
#define TURTLE_INSECTS_TALK_POCKETS_ARG 0xd
#define TURTLE_INSECTS_TALK_POCKETS_SCREEN 0

/* The values its item motions (SceneCommand_RequestMotion13 and 14) are asked with. */
#define TURTLE_INSECTS_TALK_MOTION_B 5
#define TURTLE_INSECTS_TALK_MOTION_B_INSECT 4

/* The talk's slots the insect's name, its size and the record's holder are put in, the kind an
 * item's name is put as, and the format of a size (a whole number). */
#define TURTLE_INSECTS_TALK_SLOT_SIZE 0
#define TURTLE_INSECTS_TALK_SLOT_NAME 1
#define TURTLE_INSECTS_TALK_SLOT_INSECT 2
#define TURTLE_INSECTS_TALK_SLOT_INSECT_SIZE 4
#define TURTLE_INSECTS_TALK_SLOT_PRIZE 0
#define TURTLE_INSECTS_TALK_ITEM_KIND 7
#define TURTLE_INSECTS_TALK_SIZE_FORMAT 3

/* The entries of the table of command functions. */
#define TURTLE_INSECTS_TALK_AFTER_POCKETS 0
#define TURTLE_INSECTS_TALK_NEXT_LINE 1

/* What TurtleInsectsTalk_ShowRecord answers. */
#define TURTLE_INSECTS_TALK_RECORD_NONE (-1)
#define TURTLE_INSECTS_TALK_RECORD_MINE 0
#define TURTLE_INSECTS_TALK_RECORD_PLAYER 1
#define TURTLE_INSECTS_TALK_RECORD_VILLAGER 2

/* Its lines (the receiver's message), of "sp_npc_turtle2" unless said. */
#define TURTLE_INSECTS_TALK_LINE_FULL 0
#define TURTLE_INSECTS_TALK_LINE_GIVE_NET 1
#define TURTLE_INSECTS_TALK_LINE_OFF_HOURS 2
#define TURTLE_INSECTS_TALK_LINE_ENTERED 3
#define TURTLE_INSECTS_TALK_LINE_NET_GIVEN 4
#define TURTLE_INSECTS_TALK_LINE_AGAIN 8
#define TURTLE_INSECTS_TALK_LINE_RECORD_MINE 9
#define TURTLE_INSECTS_TALK_LINE_RECORD_OTHER 10
#define TURTLE_INSECTS_TALK_LINE_8_FIRST 11
#define TURTLE_INSECTS_TALK_LINE_SHOW_INSECT 0x0b
#define TURTLE_INSECTS_TALK_LINE_NO_INSECT 0x0c
#define TURTLE_INSECTS_TALK_LINE_MEASURED 0x0d
#define TURTLE_INSECTS_TALK_LINE_SHORTER 0x0e
#define TURTLE_INSECTS_TALK_LINE_LONGER 0x10
#define TURTLE_INSECTS_TALK_LINE_BEAT_OWN 0x11
#define TURTLE_INSECTS_TALK_LINE_BEAT_OTHER 0x12
#define TURTLE_INSECTS_TALK_LINE_RECORDED 0x13
#define TURTLE_INSECTS_TALK_LINE_PRIZE_OWN 0x14
#define TURTLE_INSECTS_TALK_LINE_PRIZE_OTHER 0x15
#define TURTLE_INSECTS_TALK_LINE_NO_RECORD 0x16 /* its end records the insect as line 0x13's */
#define TURTLE_INSECTS_TALK_LINE_SHORTER_OWN 0x1d
#define TURTLE_INSECTS_TALK_LINE_RECORD_NONE 0x1e
/* Of "sp_npc_turtle": the item 0x37e0 asked about, taken, and the item 0x1559 given. */
#define TURTLE_INSECTS_TALK_LINE_37E0_ASK 0
#define TURTLE_INSECTS_TALK_LINE_37E0_ANSWER_1 1
#define TURTLE_INSECTS_TALK_LINE_37E0_TAKEN 2
#define TURTLE_INSECTS_TALK_LINE_37E0_ANSWER_4 4

static TalkObject *turtle_insects_talk_object(TurtleInsectsTalk *talk)
{
    return (TalkObject *) (void *) talk->base.talk;
}

static SceneCommandScene *turtle_insects_talk_scene(TurtleInsectsTalk *talk)
{
    return (SceneCommandScene *) (void *) talk;
}

/* The line shown. */
static u8 turtle_insects_talk_shown(const TurtleInsectsTalk *talk)
{
    return ((const MessageReceiver *) (const void *) talk)->message;
}

static int turtle_insects_talk_is_insect(u16 item)
{
    return item >= TURTLE_INSECTS_TALK_INSECT_FIRST && item <= TURTLE_INSECTS_TALK_INSECT_LAST;
}

/* The talk shows `line` of `file` unless it is TURTLE_INSECTS_TALK_NO_LINE. */
static void turtle_insects_talk_say_unless_none(TurtleInsectsTalk *talk, u8 line, const char *file)
{
    if (line != TURTLE_INSECTS_TALK_NO_LINE) {
        u8 message = line;
        TalkObject_SetMessage(turtle_insects_talk_object(talk), &message, file);
    }
}

/* The whole part of a size (fx32), as the contest compares and shows them. */
static s32 turtle_insects_talk_whole(s32 size)
{
    return size >> 12;
}

/* ---- The class */

/* func_ov082_02279044 (vtable slot 0x04): the destructor of the scene class it derives from,
 * then the scene freed. */
TurtleInsectsTalk *TurtleInsectsTalk_DestructDelete(TurtleInsectsTalk *talk)
{
    talk->base.vtable = data_ov082_0227978c;
    Obj020d9ff8_DestructBody(talk);
    Heap_OperatorDeleteB(talk);
    return talk;
}
CLEAN_AS(func_ov082_02279044, TurtleInsectsTalk_DestructDelete)

/* func_ov082_02279064 (vtable slot 0x00): the destructor of the scene class it derives from. */
TurtleInsectsTalk *TurtleInsectsTalk_Destruct(TurtleInsectsTalk *talk)
{
    talk->base.vtable = data_ov082_0227978c;
    Obj020d9ff8_DestructBody(talk);
    return talk;
}
CLEAN_AS(func_ov082_02279064, TurtleInsectsTalk_Destruct)

/* func_ov082_0227907c: the constructor: a scene of class 0x020d9ff8 given this class's vtable;
 * no item. */
TurtleInsectsTalk *TurtleInsectsTalk_Construct(TurtleInsectsTalk *talk)
{
    Obj020d9ff8_Construct(talk);
    talk->base.vtable = data_ov082_0227978c;
    talk->item = TURTLE_INSECTS_TALK_NO_ITEM;
    return talk;
}
CLEAN_AS(func_ov082_0227907c, TurtleInsectsTalk_Construct)

/* func_ov082_02279018: the scene reset (its vtable slot 0x08) and given its owner; the player
 * did not hold the record, and the item 0x37e0 is not looked for yet. */
void TurtleInsectsTalk_Begin(TurtleInsectsTalk *talk, TurtleInsects *owner)
{
    u32 vtable = *(const u32 *) (const void *) talk;
    u32 code = *(const u32 *) (uintptr_t) (vtable + TURTLE_INSECTS_TALK_SLOT_RESET);
    ((void (*)(TurtleInsectsTalk *))(uintptr_t) code)(talk);
    talk->owner = owner;
    talk->was_holder = 0;
    talk->slot_37e0 = TURTLE_INSECTS_TALK_37E0_UNKNOWN;
}
CLEAN_AS(func_ov082_02279018, TurtleInsectsTalk_Begin)

/* func_ov082_022791b0: entry `index` of a table filled the first time from the overlay's
 * constants (0: TurtleInsectsTalk_AfterPockets, 1: TurtleInsectsTalk_NextLine) into `slot`.
 * The scene is not used.
 * REQUIRES: `index` is 0 or 1 (the table is not bounded). */
void TurtleInsectsTalk_PickCommandFunction(TurtleInsectsTalk *talk, MemberPointer *slot, int index)
{
    static const MemberPointer *const functions[2] = {&data_ov082_02279710, &data_ov082_02279708};
    (void) talk;
    MemberTable_InitOnce(&data_ov082_02279900, data_ov082_02279904, functions, 2);
    *slot = data_ov082_02279904[index];
}
CLEAN_AS(func_ov082_022791b0, TurtleInsectsTalk_PickCommandFunction)

/* func_ov082_022791a0: the function run when a command of the scene ends: entry `index`. */
void TurtleInsectsTalk_SetAfterCommand(TurtleInsectsTalk *talk, int index)
{
    TurtleInsectsTalk_PickCommandFunction(talk, &talk->after_command, index);
}
CLEAN_AS(func_ov082_022791a0, TurtleInsectsTalk_SetAfterCommand)

/* func_ov082_02279190: the function run when the command after that one ends: entry
 * `index`. */
void TurtleInsectsTalk_SetThenCommand(TurtleInsectsTalk *talk, int index)
{
    TurtleInsectsTalk_PickCommandFunction(talk, &talk->then_command, index);
}
CLEAN_AS(func_ov082_02279190, TurtleInsectsTalk_SetThenCommand)

/* func_ov082_02279204 (vtable slot 0x84, a command of the scene ended): the function asked for
 * runs once, when there is one, and the one asked for after it takes its place. */
void TurtleInsectsTalk_OnCommandEnded(TurtleInsectsTalk *talk)
{
    if (talk->after_command.function == 0) {
        return;
    }
    MemberPointer_CallVoid(&talk->after_command, talk);
    MemberPointer none = __ptmf_null;
    talk->after_command = none;
    if (talk->then_command.function != 0) {
        talk->after_command = talk->then_command;
        talk->then_command = none;
    }
}
CLEAN_AS(func_ov082_02279204, TurtleInsectsTalk_OnCommandEnded)

/* func_ov082_022790a0 (a command function): the talk's next line. */
void TurtleInsectsTalk_NextLine(TurtleInsectsTalk *talk)
{
    SceneCommand_RequestNextLine(turtle_insects_talk_scene(talk));
}
CLEAN_AS(func_ov082_022790a0, TurtleInsectsTalk_NextLine)

/* ---- Its lines */

/* func_ov082_02279168 (the pockets' predicate): an insect in a slot of state 0. */
u16 TurtleInsectsTalk_IsInsect(u16 *item, int state)
{
    if (state != 0) {
        return 0;
    }
    return (u16) turtle_insects_talk_is_insect(*item);
}
CLEAN_AS(func_ov082_02279168, TurtleInsectsTalk_IsInsect)

/* Whether the pockets hold `code` nowhere and the player at this console does not hold it. */
static int turtle_insects_talk_lacks(u16 code, u16 held)
{
    u16 item = code;
    return CurrentPockets_FindItem(&item) < 0 && held != code;
}

/* func_ov082_02278ef0 (vtable slot 0x78): see turtle_insects_talk.h.
 * QUIRK: the current player's villager part is asked for and not used. */
void TurtleInsectsTalk_Line(TurtleInsectsTalk *talk, TurtleInsectsTalkStart *out)
{
    PlayerRecord_VillagerPart(PlayerRecords_Current());
    out->name = data_ov082_022798c8;
    DateTime now = {0};
    DateTime_Now(&now);
    if (talk->slot_37e0 == TURTLE_INSECTS_TALK_37E0_UNKNOWN) {
        u16 item_37e0 = TURTLE_INSECTS_TALK_ITEM_37E0;
        talk->slot_37e0 = CurrentPockets_FindItem(&item_37e0);
        if (talk->slot_37e0 >= 0) {
            out->name = data_ov082_022798d8;
            out->message = TURTLE_INSECTS_TALK_LINE_37E0_ASK;
            return;
        }
    }
    if (now.hour < TURTLE_INSECTS_TALK_FIRST_HOUR || now.hour >= TURTLE_INSECTS_TALK_END_HOUR) {
        out->message = TURTLE_INSECTS_TALK_LINE_OFF_HOURS;
        return;
    }
    out->message = TURTLE_INSECTS_TALK_LINE_ENTERED;
    u16 held;
    PlayerActorOps_HeldItem(&held, PlayerActors_OwnPlayer());
    if (TalkChecks_TestSetDailyBit(TURTLE_INSECTS_TALK_DAILY_BIT, 0) == 0 &&
        turtle_insects_talk_lacks(TURTLE_INSECTS_TALK_NET, held) &&
        turtle_insects_talk_lacks(TURTLE_INSECTS_TALK_NET_2, held)) {
        out->message = CurrentPockets_FreeSlot() >= 0 ? TURTLE_INSECTS_TALK_LINE_GIVE_NET : TURTLE_INSECTS_TALK_LINE_FULL;
        return;
    }
    if (TalkChecks_TestSetDailyBit(TURTLE_INSECTS_TALK_DAILY_BIT, 1) != 0) {
        out->message = TURTLE_INSECTS_TALK_LINE_AGAIN;
    }
}
CLEAN_AS(func_ov082_02278ef0, TurtleInsectsTalk_Line)

/* func_ov082_02278dec: when the record of the day holds an insect, its name goes into the
 * talk's slot 1 and its whole size into slot 0, then the holder's name into slot 1: answers 0
 * when the holder is the current player, 1 for another player, 2 for a villager. -1 when the
 * record holds no insect or no holder. */
int TurtleInsectsTalk_ShowRecord(TurtleInsectsTalk *talk)
{
    EventWinner *record = &data_021f3aa4;
    u16 item;
    EventWinner_GetItem(&item, record);
    if (!turtle_insects_talk_is_insect(item)) {
        return TURTLE_INSECTS_TALK_RECORD_NONE;
    }
    DesignCreator *player = EventWinner_Player(record);
    NpcId *villager = EventWinner_Villager(record);
    u16 insect;
    EventWinner_GetItem(&insect, record);
    SceneBase_PutItemName(&talk->base, (int) (uintptr_t) &insect, TURTLE_INSECTS_TALK_SLOT_NAME,
                          TURTLE_INSECTS_TALK_ITEM_KIND);
    SceneBase_PutValue(&talk->base, turtle_insects_talk_whole(EventWinner_Size(record)), TURTLE_INSECTS_TALK_SLOT_SIZE,
                       TURTLE_INSECTS_TALK_SIZE_FORMAT, 0, 0);
    if (PlayerId_IsSet(player) != 0) {
        SceneBase_PutNameAt10(&talk->base, EventWinner_Player(record), TURTLE_INSECTS_TALK_SLOT_NAME);
        DesignCreator *mine = PlayerRecord_Player(PlayerRecords_Current());
        DesignCreator *holder = EventWinner_Player(record);
        if (holder->town_id != mine->town_id || memcmp(holder->town_name, mine->town_name, sizeof holder->town_name) != 0 ||
            PlayerId_SamePlayer(holder, mine) == 0) {
            return TURTLE_INSECTS_TALK_RECORD_PLAYER;
        }
        return TURTLE_INSECTS_TALK_RECORD_MINE;
    }
    if (NpcId_IsValid(villager) != 0) {
        PlayerIdText name;
        PlayerIdText_Construct(&name);
        NpcId_FormatName(villager, (char *) &name);
        TalkObject_SetPart(turtle_insects_talk_object(talk), TURTLE_INSECTS_TALK_SLOT_NAME, (TextBase *) (void *) &name);
        PlayerIdText_Destruct(&name);
        return TURTLE_INSECTS_TALK_RECORD_VILLAGER;
    }
    return TURTLE_INSECTS_TALK_RECORD_NONE;
}
CLEAN_AS(func_ov082_02278dec, TurtleInsectsTalk_ShowRecord)

/* func_ov082_02278ab8 (vtable slot 0x18, the player answered): see turtle_insects_talk.h.
 * With the item 0x37e0 in the pockets, the first answer to line 0 empties its pocket and he
 * takes it: line 2 of "sp_npc_turtle". */
void TurtleInsectsTalk_OnAnswer(TurtleInsectsTalk *talk)
{
    unsigned int answer = TalkAnswers_Picked((TalkAnswers *) (uintptr_t) (u32) SceneBase_TalkChoices(&talk->base));
    s32 slot = talk->slot_37e0;
    u8 shown = turtle_insects_talk_shown(talk);

    if (slot >= 0) {
        if (shown == TURTLE_INSECTS_TALK_LINE_37E0_ASK && answer == 0) {
            CurrentPockets_Empty(slot);
            u16 item = TURTLE_INSECTS_TALK_ITEM_37E0;
            SceneCommand_RequestMotion14(turtle_insects_talk_scene(talk), &item, 0, TURTLE_INSECTS_TALK_MOTION_B, 0);
            turtle_insects_talk_say_unless_none(talk, TURTLE_INSECTS_TALK_LINE_37E0_TAKEN, data_ov082_022798d8);
        }
        return;
    }

    u8 line = TURTLE_INSECTS_TALK_NO_LINE;
    if (shown == TURTLE_INSECTS_TALK_LINE_AGAIN) {
        if (answer != 0) {
            int holder = TurtleInsectsTalk_ShowRecord(talk);
            if (holder == TURTLE_INSECTS_TALK_RECORD_MINE) {
                line = TURTLE_INSECTS_TALK_LINE_RECORD_MINE;
            } else if (holder > 0) {
                line = TURTLE_INSECTS_TALK_LINE_RECORD_OTHER;
            } else {
                line = TURTLE_INSECTS_TALK_LINE_RECORD_NONE;
            }
        } else {
            line = TURTLE_INSECTS_TALK_LINE_8_FIRST;
        }
    }
    turtle_insects_talk_say_unless_none(talk, line, data_ov082_022798c8);
}
CLEAN_AS(func_ov082_02278ab8, TurtleInsectsTalk_OnAnswer)

/* The prize: an item drawn from the item list of kind 0, group 0, motion 13 with it, its name
 * into the talk's slot 0, and the item into the pockets. */
static void turtle_insects_talk_give_prize(TurtleInsectsTalk *talk)
{
    ItemList list;
    u16 drawn;
    ItemList_Construct(&list, 0, 0);
    ItemLists_Draw(&drawn, &list, 0, 0, 1, 1, 0);
    u16 prize = drawn;
    ItemList_Destruct(&list);
    SceneCommand_RequestMotion13(turtle_insects_talk_scene(talk), &prize, 0, TURTLE_INSECTS_TALK_MOTION_B, 0);
    SceneBase_PutItemName(&talk->base, (int) (uintptr_t) &prize, TURTLE_INSECTS_TALK_SLOT_PRIZE,
                          TURTLE_INSECTS_TALK_ITEM_KIND);
    CurrentPockets_Give(&prize, 0);
}

/* The lines about the record (0xd, 0x10, 0x13, 0x16); the line to show next, or
 * TURTLE_INSECTS_TALK_NO_LINE. */
static u8 turtle_insects_talk_record_line(TurtleInsectsTalk *talk, u8 shown)
{
    EventWinner *record = &data_021f3aa4;
    u8 line = TURTLE_INSECTS_TALK_NO_LINE;

    switch (shown) {
        case TURTLE_INSECTS_TALK_LINE_MEASURED: {
            SceneCommand_RequestMotion16(turtle_insects_talk_scene(talk));
            u16 recorded;
            EventWinner_GetItem(&recorded, record);
            if (!turtle_insects_talk_is_insect(recorded)) {
                line = TURTLE_INSECTS_TALK_LINE_NO_RECORD;
                break;
            }
            PlayerField2416_SetInsects((PlayerField2416 *) (void *) PlayerRecord_Field2416(PlayerRecords_Current()), 1);
            int best = EventWinner_Size(record);
            if (turtle_insects_talk_whole(talk->owner->size) > turtle_insects_talk_whole(best)) {
                line = TURTLE_INSECTS_TALK_LINE_LONGER;
            } else if (TurtleInsectsTalk_ShowRecord(talk) == TURTLE_INSECTS_TALK_RECORD_MINE) {
                line = TURTLE_INSECTS_TALK_LINE_SHORTER_OWN;
            } else if (TurtleInsectsTalk_ShowRecord(talk) > 0) {
                line = TURTLE_INSECTS_TALK_LINE_SHORTER;
            }
            break;
        }
        case TURTLE_INSECTS_TALK_LINE_LONGER:
            if (TurtleInsectsTalk_ShowRecord(talk) == TURTLE_INSECTS_TALK_RECORD_MINE) {
                line = TURTLE_INSECTS_TALK_LINE_BEAT_OWN;
                talk->was_holder = 1;
            } else if (TurtleInsectsTalk_ShowRecord(talk) > 0) {
                line = TURTLE_INSECTS_TALK_LINE_BEAT_OTHER;
                talk->was_holder = 0;
            }
            break;
        case TURTLE_INSECTS_TALK_LINE_RECORDED:
        case TURTLE_INSECTS_TALK_LINE_NO_RECORD:
            line = talk->was_holder != 0 ? TURTLE_INSECTS_TALK_LINE_PRIZE_OWN : TURTLE_INSECTS_TALK_LINE_PRIZE_OTHER;
            EventWinner_SetItem(record, &talk->item);
            EventWinner_SetSize(record, talk->owner->size);
            EventWinner_SetPlayer(record, PlayerRecord_Player(PlayerRecords_Current()));
            EventWinner_SetKind(record, TURTLE_INSECTS_TALK_RECORD_KIND);
            StateBlock_SetFlag(data_021dc7a8, TURTLE_INSECTS_TALK_NOTICE_FLAG);
            turtle_insects_talk_give_prize(talk);
            break;
    }
    return line;
}

/* func_ov082_02278b64 (vtable slot 0x14, a line ended): see turtle_insects_talk.h. With the
 * item 0x37e0 in the pockets: after line 1 or 4 of "sp_npc_turtle" it is no longer asked
 * about; after line 2 he gives the item 0x1559 (line 4). */
void TurtleInsectsTalk_OnLineEnd(TurtleInsectsTalk *talk)
{
    u8 shown = turtle_insects_talk_shown(talk);

    if (talk->slot_37e0 >= 0) {
        if (shown == TURTLE_INSECTS_TALK_LINE_37E0_ANSWER_1 || shown == TURTLE_INSECTS_TALK_LINE_37E0_ANSWER_4) {
            talk->slot_37e0 = TURTLE_INSECTS_TALK_37E0_DONE;
        }
        if (shown == TURTLE_INSECTS_TALK_LINE_37E0_TAKEN) {
            u16 shown_item = TURTLE_INSECTS_TALK_ITEM_1559;
            SceneCommand_RequestMotion13(turtle_insects_talk_scene(talk), &shown_item, 0, TURTLE_INSECTS_TALK_MOTION_B, 0);
            u16 given = TURTLE_INSECTS_TALK_ITEM_1559;
            CurrentPockets_Give(&given, 0);
            turtle_insects_talk_say_unless_none(talk, TURTLE_INSECTS_TALK_LINE_37E0_ANSWER_4, data_ov082_022798d8);
        }
        return;
    }

    u8 line = turtle_insects_talk_record_line(talk, shown);

    switch (shown) {
        case TURTLE_INSECTS_TALK_LINE_GIVE_NET: {
            u16 shown_net = TURTLE_INSECTS_TALK_NET;
            SceneCommand_RequestMotion13(turtle_insects_talk_scene(talk), &shown_net, 0, TURTLE_INSECTS_TALK_MOTION_B, 0);
            u16 net = TURTLE_INSECTS_TALK_NET;
            CurrentPockets_Give(&net, 0);
            line = TURTLE_INSECTS_TALK_LINE_NET_GIVEN;
            TalkChecks_TestSetDailyBit(TURTLE_INSECTS_TALK_DAILY_BIT, 1);
            break;
        }
        case TURTLE_INSECTS_TALK_LINE_SHOW_INSECT:
            SceneCommand_SetPocketPredicate(turtle_insects_talk_scene(talk),
                                            (PocketPredicate) (void (*)(void)) func_ov082_02279168,
                                            TURTLE_INSECTS_TALK_POCKETS_ARG, 1);
            SceneCommand_RequestScreen(turtle_insects_talk_scene(talk), TURTLE_INSECTS_TALK_POCKETS_SCREEN);
            TurtleInsectsTalk_SetAfterCommand(talk, TURTLE_INSECTS_TALK_AFTER_POCKETS);
            break;
    }
    turtle_insects_talk_say_unless_none(talk, line, data_ov082_022798c8);
}
CLEAN_AS(func_ov082_02278b64, TurtleInsectsTalk_OnLineEnd)

/* func_ov082_022790a8 (after the pockets' screen of line 0xb): no item and no size yet; when a
 * pocket was picked (GroupParams_C4CIs1) its insect is measured (a random size), shown by
 * motion 14, its name put into the talk's slot 2 and its whole size into slot 4, the talk's
 * next line asked for after that motion, and its pocket emptied: line 0xd. Else the next line,
 * and line 0xc.
 * QUIRK: the picked pocket is emptied only when its number is not negative, which it always
 * is. */
void TurtleInsectsTalk_AfterPockets(TurtleInsectsTalk *talk)
{
    TalkObject *object = turtle_insects_talk_object(talk);
    u8 line = TURTLE_INSECTS_TALK_LINE_NO_INSECT;

    talk->item = TURTLE_INSECTS_TALK_NO_ITEM;
    talk->owner->size = 0;
    if (GroupParams_C4CIs1()) {
        int slot = GroupParams_Arg();
        talk->item = CurrentPockets_Item((u32) slot);
        talk->owner->size = EventWinner_RandomSize(&talk->item);
        SceneCommand_RequestMotion14(turtle_insects_talk_scene(talk), &talk->item, 0, TURTLE_INSECTS_TALK_MOTION_B_INSECT, 0);
        TurtleInsectsTalk_SetThenCommand(talk, TURTLE_INSECTS_TALK_NEXT_LINE);
        SceneBase_PutItemName(&talk->base, (int) (uintptr_t) &talk->item, TURTLE_INSECTS_TALK_SLOT_INSECT,
                              TURTLE_INSECTS_TALK_ITEM_KIND);
        SceneBase_PutValue(&talk->base, turtle_insects_talk_whole(talk->owner->size), TURTLE_INSECTS_TALK_SLOT_INSECT_SIZE,
                           TURTLE_INSECTS_TALK_SIZE_FORMAT, 0, 0);
        if (slot >= 0) {
            CurrentPockets_Empty(slot);
        }
        line = TURTLE_INSECTS_TALK_LINE_MEASURED;
    } else {
        SceneCommand_RequestNextLine(turtle_insects_talk_scene(talk));
    }
    TalkObject_SetMessage(object, &line, data_ov082_022798c8);
}
CLEAN_AS(func_ov082_022790a8, TurtleInsectsTalk_AfterPockets)
