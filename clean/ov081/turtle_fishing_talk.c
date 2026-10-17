/* The fishing tourney host's talk scene (turtle_fishing_talk.h): its class, its lines, the
 * player's answers, the fish weighed and the record of the day. */
#include "turtle_fishing_talk.h"

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
static_assert(offsetof(TurtleFishingTalk, owner) == 0xb0 && offsetof(TurtleFishingTalk, after_command) == 0xb4,
              "TurtleFishingTalk");
static_assert(offsetof(TurtleFishingTalk, then_command) == 0xbc && offsetof(TurtleFishingTalk, item) == 0xc4,
              "TurtleFishingTalk");
static_assert(offsetof(TurtleFishingTalk, was_holder) == 0xc6 && offsetof(TurtleFishingTalk, slot_37e0) == 0xc8,
              "TurtleFishingTalk");
static_assert(sizeof(TurtleFishingTalk) == 0xcc, "TurtleFishingTalk");
static_assert(sizeof(TurtleFishingTalkStart) == 8, "what a talk starts with");
static_assert(sizeof(ItemList) == 8, "an item list");

/* The vtable of its class. */
extern const u8 data_ov081_0227972c[];
/* Its message files, "sp_npc_turtle1" and the shared "sp_npc_turtle". */
extern const char data_ov081_02279868[];
extern const char data_ov081_02279878[];
/* The functions TurtleFishingTalk_PickCommandFunction picks from: a table filled once (bit 0
 * of the guard word) from the overlay's constants (TurtleFishingTalk_AfterPockets,
 * TurtleFishingTalk_NextLine). */
extern u32 data_ov081_022798a0;
extern MemberPointer data_ov081_022798a4[2];
extern const MemberPointer data_ov081_022796b0;
extern const MemberPointer data_ov081_022796a8;
/* The null member pointer. */
extern const MemberPointer __ptmf_null;
/* The pockets' predicate, as the game hands it to the pockets' screen (the game's symbol of
 * TurtleFishingTalk_IsFish; its result is a halfword where the screen takes an int). */
extern u16 func_ov081_02279124(u16 *item, int state);
/* The town's record of the day's winner and the state block. */
extern EventWinner data_021f3aa4;
extern u32 data_021dc7a8[];

#define TURTLE_FISHING_TALK_NO_ITEM 0xfff1
#define TURTLE_FISHING_TALK_NO_LINE 0xff

/* The vtable slot of the scene that resets it (the scene base's reset). */
#define TURTLE_FISHING_TALK_SLOT_RESET 0x08

/* The fish (items 0x12e8 to 0x131f), the tourney's two rods, the item he takes and the one he
 * gives for it. */
#define TURTLE_FISHING_TALK_FISH_FIRST 0x12e8
#define TURTLE_FISHING_TALK_FISH_LAST 0x131f
#define TURTLE_FISHING_TALK_ROD 0x1374
#define TURTLE_FISHING_TALK_ROD_2 0x1375
#define TURTLE_FISHING_TALK_ITEM_37E0 0x37e0
#define TURTLE_FISHING_TALK_ITEM_1559 0x1559

/* The current player's daily bit of the tourney. */
#define TURTLE_FISHING_TALK_DAILY_BIT 0x1b

/* The hours of the tourney: from 12:00 to before 18:00. */
#define TURTLE_FISHING_TALK_FIRST_HOUR 12
#define TURTLE_FISHING_TALK_END_HOUR 18

/* The record's kind for the tourney, and the state block's flag of a winner to announce. */
#define TURTLE_FISHING_TALK_RECORD_KIND EVENT_WINNER_KIND_FISHING
#define TURTLE_FISHING_TALK_NOTICE_FLAG 0x0f

/* The pockets' screen: its predicate's argument, and the screen. */
#define TURTLE_FISHING_TALK_POCKETS_ARG 0xd
#define TURTLE_FISHING_TALK_POCKETS_SCREEN 0

/* The values its item motions (SceneCommand_RequestMotion13 and 14) are asked with. */
#define TURTLE_FISHING_TALK_MOTION_B 5
#define TURTLE_FISHING_TALK_MOTION_B_FISH 4

/* The talk's slots the fish's name, its size and the record's holder are put in, the kind an
 * item's name is put as, and the format of a size (a decimal with one place). */
#define TURTLE_FISHING_TALK_SLOT_SIZE 0
#define TURTLE_FISHING_TALK_SLOT_NAME 1
#define TURTLE_FISHING_TALK_SLOT_FISH 2
#define TURTLE_FISHING_TALK_SLOT_FISH_SIZE 4
#define TURTLE_FISHING_TALK_SLOT_PRIZE 0
#define TURTLE_FISHING_TALK_ITEM_KIND 7
#define TURTLE_FISHING_TALK_SIZE_FORMAT 1

/* The entries of the table of command functions. */
#define TURTLE_FISHING_TALK_AFTER_POCKETS 0
#define TURTLE_FISHING_TALK_NEXT_LINE 1

/* What TurtleFishingTalk_ShowRecord answers. */
#define TURTLE_FISHING_TALK_RECORD_NONE (-1)
#define TURTLE_FISHING_TALK_RECORD_MINE 0
#define TURTLE_FISHING_TALK_RECORD_PLAYER 1
#define TURTLE_FISHING_TALK_RECORD_VILLAGER 2

/* Its lines (the receiver's message), of "sp_npc_turtle1" unless said. */
#define TURTLE_FISHING_TALK_LINE_FULL 0
#define TURTLE_FISHING_TALK_LINE_GIVE_ROD 1
#define TURTLE_FISHING_TALK_LINE_OFF_HOURS 2
#define TURTLE_FISHING_TALK_LINE_ENTERED 3
#define TURTLE_FISHING_TALK_LINE_ROD_GIVEN 4
#define TURTLE_FISHING_TALK_LINE_AGAIN 8
#define TURTLE_FISHING_TALK_LINE_RECORD_MINE 9
#define TURTLE_FISHING_TALK_LINE_RECORD_OTHER 10
#define TURTLE_FISHING_TALK_LINE_8_FIRST 11
#define TURTLE_FISHING_TALK_LINE_SHOW_FISH 0x0b
#define TURTLE_FISHING_TALK_LINE_NO_FISH 0x0c
#define TURTLE_FISHING_TALK_LINE_WEIGHED 0x0d
#define TURTLE_FISHING_TALK_LINE_SHORTER 0x0e
#define TURTLE_FISHING_TALK_LINE_LONGER 0x10
#define TURTLE_FISHING_TALK_LINE_BEAT_OWN 0x11
#define TURTLE_FISHING_TALK_LINE_BEAT_OTHER 0x12
#define TURTLE_FISHING_TALK_LINE_RECORDED 0x13
#define TURTLE_FISHING_TALK_LINE_PRIZE_OWN 0x14
#define TURTLE_FISHING_TALK_LINE_PRIZE_OTHER 0x15
#define TURTLE_FISHING_TALK_LINE_SHORTER_OWN 0x16
/* Of "sp_npc_turtle": the item 0x37e0 asked about, taken, and the item 0x1559 given. */
#define TURTLE_FISHING_TALK_LINE_37E0_ASK 0
#define TURTLE_FISHING_TALK_LINE_37E0_ANSWER_1 1
#define TURTLE_FISHING_TALK_LINE_37E0_TAKEN 2
#define TURTLE_FISHING_TALK_LINE_37E0_ANSWER_4 4

static TalkObject *turtle_fishing_talk_object(TurtleFishingTalk *talk)
{
    return (TalkObject *) (void *) talk->base.talk;
}

static SceneCommandScene *turtle_fishing_talk_scene(TurtleFishingTalk *talk)
{
    return (SceneCommandScene *) (void *) talk;
}

/* The line shown. */
static u8 turtle_fishing_talk_shown(const TurtleFishingTalk *talk)
{
    return ((const MessageReceiver *) (const void *) talk)->message;
}

static int turtle_fishing_talk_is_fish(u16 item)
{
    return item >= TURTLE_FISHING_TALK_FISH_FIRST && item <= TURTLE_FISHING_TALK_FISH_LAST;
}

/* The talk shows `line` of `file` unless it is TURTLE_FISHING_TALK_NO_LINE. */
static void turtle_fishing_talk_say_unless_none(TurtleFishingTalk *talk, u8 line, const char *file)
{
    if (line != TURTLE_FISHING_TALK_NO_LINE) {
        u8 message = line;
        TalkObject_SetMessage(turtle_fishing_talk_object(talk), &message, file);
    }
}

/* The size of a fish in tenths, as the tourney compares them.
 * QUIRK: ten times the fx32 size, cut to a word, then the whole part. */
static s32 turtle_fishing_talk_tenths(s32 size)
{
    return (s32) ((u32) size * 10u) >> 12;
}

/* ---- The class */

/* func_ov081_02279004 (vtable slot 0x04): the destructor of the scene class it derives from,
 * then the scene freed. */
TurtleFishingTalk *TurtleFishingTalk_DestructDelete(TurtleFishingTalk *talk)
{
    talk->base.vtable = data_ov081_0227972c;
    Obj020d9ff8_DestructBody(talk);
    Heap_OperatorDeleteB(talk);
    return talk;
}
CLEAN_AS(func_ov081_02279004, TurtleFishingTalk_DestructDelete)

/* func_ov081_02279024 (vtable slot 0x00): the destructor of the scene class it derives from. */
TurtleFishingTalk *TurtleFishingTalk_Destruct(TurtleFishingTalk *talk)
{
    talk->base.vtable = data_ov081_0227972c;
    Obj020d9ff8_DestructBody(talk);
    return talk;
}
CLEAN_AS(func_ov081_02279024, TurtleFishingTalk_Destruct)

/* func_ov081_0227903c: the constructor: a scene of class 0x020d9ff8 given this class's vtable;
 * no item. */
TurtleFishingTalk *TurtleFishingTalk_Construct(TurtleFishingTalk *talk)
{
    Obj020d9ff8_Construct(talk);
    talk->base.vtable = data_ov081_0227972c;
    talk->item = TURTLE_FISHING_TALK_NO_ITEM;
    return talk;
}
CLEAN_AS(func_ov081_0227903c, TurtleFishingTalk_Construct)

/* func_ov081_02278fd8: the scene reset (its vtable slot 0x08) and given its owner; the player
 * did not hold the record, and the item 0x37e0 is not looked for yet. */
void TurtleFishingTalk_Begin(TurtleFishingTalk *talk, TurtleFishing *owner)
{
    u32 vtable = *(const u32 *) (const void *) talk;
    u32 code = *(const u32 *) (uintptr_t) (vtable + TURTLE_FISHING_TALK_SLOT_RESET);
    ((void (*)(TurtleFishingTalk *))(uintptr_t) code)(talk);
    talk->owner = owner;
    talk->was_holder = 0;
    talk->slot_37e0 = TURTLE_FISHING_TALK_37E0_UNKNOWN;
}
CLEAN_AS(func_ov081_02278fd8, TurtleFishingTalk_Begin)

/* func_ov081_0227916c: entry `index` of a table filled the first time from the overlay's
 * constants (0: TurtleFishingTalk_AfterPockets, 1: TurtleFishingTalk_NextLine) into `slot`.
 * The scene is not used.
 * REQUIRES: `index` is 0 or 1 (the table is not bounded). */
void TurtleFishingTalk_PickCommandFunction(TurtleFishingTalk *talk, MemberPointer *slot, int index)
{
    static const MemberPointer *const functions[2] = {&data_ov081_022796b0, &data_ov081_022796a8};
    (void) talk;
    MemberTable_InitOnce(&data_ov081_022798a0, data_ov081_022798a4, functions, 2);
    *slot = data_ov081_022798a4[index];
}
CLEAN_AS(func_ov081_0227916c, TurtleFishingTalk_PickCommandFunction)

/* func_ov081_0227915c: the function run when a command of the scene ends: entry `index`. */
void TurtleFishingTalk_SetAfterCommand(TurtleFishingTalk *talk, int index)
{
    TurtleFishingTalk_PickCommandFunction(talk, &talk->after_command, index);
}
CLEAN_AS(func_ov081_0227915c, TurtleFishingTalk_SetAfterCommand)

/* func_ov081_0227914c: the function run when the command after that one ends: entry
 * `index`. */
void TurtleFishingTalk_SetThenCommand(TurtleFishingTalk *talk, int index)
{
    TurtleFishingTalk_PickCommandFunction(talk, &talk->then_command, index);
}
CLEAN_AS(func_ov081_0227914c, TurtleFishingTalk_SetThenCommand)

/* func_ov081_022791c0 (vtable slot 0x84, a command of the scene ended): the function asked for
 * runs once, when there is one, and the one asked for after it takes its place. */
void TurtleFishingTalk_OnCommandEnded(TurtleFishingTalk *talk)
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
CLEAN_AS(func_ov081_022791c0, TurtleFishingTalk_OnCommandEnded)

/* func_ov081_02279060 (a command function): the talk's next line. */
void TurtleFishingTalk_NextLine(TurtleFishingTalk *talk)
{
    SceneCommand_RequestNextLine(turtle_fishing_talk_scene(talk));
}
CLEAN_AS(func_ov081_02279060, TurtleFishingTalk_NextLine)

/* ---- Its lines */

/* func_ov081_02279124 (the pockets' predicate): a fish in a slot of state 0. */
u16 TurtleFishingTalk_IsFish(u16 *item, int state)
{
    if (state != 0) {
        return 0;
    }
    return (u16) turtle_fishing_talk_is_fish(*item);
}
CLEAN_AS(func_ov081_02279124, TurtleFishingTalk_IsFish)

/* Whether the pockets hold `code` nowhere and the player at this console does not hold it. */
static int turtle_fishing_talk_lacks(u16 code, u16 held)
{
    u16 item = code;
    return CurrentPockets_FindItem(&item) < 0 && held != code;
}

/* func_ov081_02278eac (vtable slot 0x78): see turtle_fishing_talk.h.
 * QUIRK: the current player's villager part is asked for and not used. */
void TurtleFishingTalk_Line(TurtleFishingTalk *talk, TurtleFishingTalkStart *out)
{
    PlayerRecord_VillagerPart(PlayerRecords_Current());
    out->name = data_ov081_02279868;
    DateTime now = {0};
    DateTime_Now(&now);
    if (talk->slot_37e0 == TURTLE_FISHING_TALK_37E0_UNKNOWN) {
        u16 item_37e0 = TURTLE_FISHING_TALK_ITEM_37E0;
        talk->slot_37e0 = CurrentPockets_FindItem(&item_37e0);
        if (talk->slot_37e0 >= 0) {
            out->name = data_ov081_02279878;
            out->message = TURTLE_FISHING_TALK_LINE_37E0_ASK;
            return;
        }
    }
    if (now.hour < TURTLE_FISHING_TALK_FIRST_HOUR || now.hour >= TURTLE_FISHING_TALK_END_HOUR) {
        out->message = TURTLE_FISHING_TALK_LINE_OFF_HOURS;
        return;
    }
    u16 held;
    PlayerActorOps_HeldItem(&held, PlayerActors_OwnPlayer());
    out->message = TURTLE_FISHING_TALK_LINE_ENTERED;
    if (TalkChecks_TestSetDailyBit(TURTLE_FISHING_TALK_DAILY_BIT, 0) == 0 &&
        turtle_fishing_talk_lacks(TURTLE_FISHING_TALK_ROD, held) &&
        turtle_fishing_talk_lacks(TURTLE_FISHING_TALK_ROD_2, held)) {
        out->message = CurrentPockets_FreeSlot() >= 0 ? TURTLE_FISHING_TALK_LINE_GIVE_ROD : TURTLE_FISHING_TALK_LINE_FULL;
        return;
    }
    if (TalkChecks_TestSetDailyBit(TURTLE_FISHING_TALK_DAILY_BIT, 1) != 0) {
        out->message = TURTLE_FISHING_TALK_LINE_AGAIN;
    }
}
CLEAN_AS(func_ov081_02278eac, TurtleFishingTalk_Line)

/* func_ov081_02278da8: when the record of the day holds a fish, its name goes into the talk's
 * slot 1 and its size into slot 0 (a decimal with one place), then the holder's name into slot
 * 1: answers 0 when the holder is the current player, 1 for another player, 2 for a villager.
 * -1 when the record holds no fish or no holder. */
int TurtleFishingTalk_ShowRecord(TurtleFishingTalk *talk)
{
    EventWinner *record = &data_021f3aa4;
    u16 item;
    EventWinner_GetItem(&item, record);
    if (!turtle_fishing_talk_is_fish(item)) {
        return TURTLE_FISHING_TALK_RECORD_NONE;
    }
    DesignCreator *player = EventWinner_Player(record);
    NpcId *villager = EventWinner_Villager(record);
    u16 fish;
    EventWinner_GetItem(&fish, record);
    SceneBase_PutItemName(&talk->base, (int) (uintptr_t) &fish, TURTLE_FISHING_TALK_SLOT_NAME, TURTLE_FISHING_TALK_ITEM_KIND);
    SceneBase_PutDecimal(&talk->base, EventWinner_Size(record), TURTLE_FISHING_TALK_SLOT_SIZE, TURTLE_FISHING_TALK_SIZE_FORMAT,
                         3);
    if (PlayerId_IsSet(player) != 0) {
        SceneBase_PutNameAt10(&talk->base, EventWinner_Player(record), TURTLE_FISHING_TALK_SLOT_NAME);
        DesignCreator *mine = PlayerRecord_Player(PlayerRecords_Current());
        DesignCreator *holder = EventWinner_Player(record);
        if (holder->town_id != mine->town_id || memcmp(holder->town_name, mine->town_name, sizeof holder->town_name) != 0 ||
            PlayerId_SamePlayer(holder, mine) == 0) {
            return TURTLE_FISHING_TALK_RECORD_PLAYER;
        }
        return TURTLE_FISHING_TALK_RECORD_MINE;
    }
    if (NpcId_IsValid(villager) != 0) {
        PlayerIdText name;
        PlayerIdText_Construct(&name);
        NpcId_FormatName(villager, (char *) &name);
        TalkObject_SetPart(turtle_fishing_talk_object(talk), TURTLE_FISHING_TALK_SLOT_NAME, (TextBase *) (void *) &name);
        PlayerIdText_Destruct(&name);
        return TURTLE_FISHING_TALK_RECORD_VILLAGER;
    }
    return TURTLE_FISHING_TALK_RECORD_NONE;
}
CLEAN_AS(func_ov081_02278da8, TurtleFishingTalk_ShowRecord)

/* func_ov081_02278ab8 (vtable slot 0x18, the player answered): see turtle_fishing_talk.h.
 * With the item 0x37e0 in the pockets, the first answer to line 0 empties its pocket and he
 * takes it: line 2 of "sp_npc_turtle". */
void TurtleFishingTalk_OnAnswer(TurtleFishingTalk *talk)
{
    unsigned int answer = TalkAnswers_Picked((TalkAnswers *) (uintptr_t) (u32) SceneBase_TalkChoices(&talk->base));
    s32 slot = talk->slot_37e0;
    u8 shown = turtle_fishing_talk_shown(talk);

    if (slot >= 0) {
        if (shown == TURTLE_FISHING_TALK_LINE_37E0_ASK && answer == 0) {
            CurrentPockets_Empty(slot);
            u16 item = TURTLE_FISHING_TALK_ITEM_37E0;
            SceneCommand_RequestMotion14(turtle_fishing_talk_scene(talk), &item, 0, TURTLE_FISHING_TALK_MOTION_B, 0);
            turtle_fishing_talk_say_unless_none(talk, TURTLE_FISHING_TALK_LINE_37E0_TAKEN, data_ov081_02279878);
        }
        return;
    }

    u8 line = TURTLE_FISHING_TALK_NO_LINE;
    if (shown == TURTLE_FISHING_TALK_LINE_AGAIN) {
        if (answer != 0) {
            /* QUIRK: the record is shown twice when the current player does not hold it. */
            if (TurtleFishingTalk_ShowRecord(talk) == TURTLE_FISHING_TALK_RECORD_MINE) {
                line = TURTLE_FISHING_TALK_LINE_RECORD_MINE;
            } else if (TurtleFishingTalk_ShowRecord(talk) > 0) {
                line = TURTLE_FISHING_TALK_LINE_RECORD_OTHER;
            }
        } else {
            line = TURTLE_FISHING_TALK_LINE_8_FIRST;
        }
    }
    turtle_fishing_talk_say_unless_none(talk, line, data_ov081_02279868);
}
CLEAN_AS(func_ov081_02278ab8, TurtleFishingTalk_OnAnswer)

/* The prize: an item drawn from the item list of kind 0, group 0, motion 13 with it, its name
 * into the talk's slot 0, and the item into the pockets. */
static void turtle_fishing_talk_give_prize(TurtleFishingTalk *talk)
{
    ItemList list;
    u16 drawn;
    ItemList_Construct(&list, 0, 0);
    ItemLists_Draw(&drawn, &list, 0, 0, 1, 1, 0);
    u16 prize = drawn;
    ItemList_Destruct(&list);
    SceneCommand_RequestMotion13(turtle_fishing_talk_scene(talk), &prize, 0, TURTLE_FISHING_TALK_MOTION_B, 0);
    SceneBase_PutItemName(&talk->base, (int) (uintptr_t) &prize, TURTLE_FISHING_TALK_SLOT_PRIZE,
                          TURTLE_FISHING_TALK_ITEM_KIND);
    CurrentPockets_Give(&prize, 0);
}

/* The lines about the record (0xd, 0x10, 0x13); the line to show next, or
 * TURTLE_FISHING_TALK_NO_LINE. */
static u8 turtle_fishing_talk_record_line(TurtleFishingTalk *talk, u8 shown)
{
    EventWinner *record = &data_021f3aa4;
    u8 line = TURTLE_FISHING_TALK_NO_LINE;

    switch (shown) {
        case TURTLE_FISHING_TALK_LINE_WEIGHED: {
            SceneCommand_RequestMotion16(turtle_fishing_talk_scene(talk));
            PlayerField2416_SetFishing((PlayerField2416 *) (void *) PlayerRecord_Field2416(PlayerRecords_Current()), 1);
            int best = EventWinner_Size(record);
            if (turtle_fishing_talk_tenths(talk->owner->size) > turtle_fishing_talk_tenths(best)) {
                line = TURTLE_FISHING_TALK_LINE_LONGER;
            } else if (TurtleFishingTalk_ShowRecord(talk) == TURTLE_FISHING_TALK_RECORD_MINE) {
                line = TURTLE_FISHING_TALK_LINE_SHORTER_OWN;
            } else if (TurtleFishingTalk_ShowRecord(talk) > 0) {
                line = TURTLE_FISHING_TALK_LINE_SHORTER;
            }
            break;
        }
        case TURTLE_FISHING_TALK_LINE_LONGER:
            if (TurtleFishingTalk_ShowRecord(talk) == TURTLE_FISHING_TALK_RECORD_MINE) {
                line = TURTLE_FISHING_TALK_LINE_BEAT_OWN;
                talk->was_holder = 1;
            } else if (TurtleFishingTalk_ShowRecord(talk) > 0) {
                line = TURTLE_FISHING_TALK_LINE_BEAT_OTHER;
                talk->was_holder = 0;
            }
            break;
        case TURTLE_FISHING_TALK_LINE_RECORDED:
            line = talk->was_holder != 0 ? TURTLE_FISHING_TALK_LINE_PRIZE_OWN : TURTLE_FISHING_TALK_LINE_PRIZE_OTHER;
            EventWinner_SetItem(record, &talk->item);
            EventWinner_SetSize(record, talk->owner->size);
            EventWinner_SetPlayer(record, PlayerRecord_Player(PlayerRecords_Current()));
            EventWinner_SetKind(record, TURTLE_FISHING_TALK_RECORD_KIND);
            StateBlock_SetFlag(data_021dc7a8, TURTLE_FISHING_TALK_NOTICE_FLAG);
            turtle_fishing_talk_give_prize(talk);
            break;
    }
    return line;
}

/* func_ov081_02278b68 (vtable slot 0x14, a line ended): see turtle_fishing_talk.h. With the
 * item 0x37e0 in the pockets: after line 1 or 4 of "sp_npc_turtle" it is no longer asked
 * about; after line 2 he gives the item 0x1559 (line 4). */
void TurtleFishingTalk_OnLineEnd(TurtleFishingTalk *talk)
{
    u8 shown = turtle_fishing_talk_shown(talk);

    if (talk->slot_37e0 >= 0) {
        if (shown == TURTLE_FISHING_TALK_LINE_37E0_ANSWER_1 || shown == TURTLE_FISHING_TALK_LINE_37E0_ANSWER_4) {
            talk->slot_37e0 = TURTLE_FISHING_TALK_37E0_DONE;
        }
        if (shown == TURTLE_FISHING_TALK_LINE_37E0_TAKEN) {
            u16 shown_item = TURTLE_FISHING_TALK_ITEM_1559;
            SceneCommand_RequestMotion13(turtle_fishing_talk_scene(talk), &shown_item, 0, TURTLE_FISHING_TALK_MOTION_B, 0);
            u16 given = TURTLE_FISHING_TALK_ITEM_1559;
            CurrentPockets_Give(&given, 0);
            turtle_fishing_talk_say_unless_none(talk, TURTLE_FISHING_TALK_LINE_37E0_ANSWER_4, data_ov081_02279878);
        }
        return;
    }

    u8 line = turtle_fishing_talk_record_line(talk, shown);

    switch (shown) {
        case TURTLE_FISHING_TALK_LINE_GIVE_ROD: {
            u16 shown_rod = TURTLE_FISHING_TALK_ROD;
            SceneCommand_RequestMotion13(turtle_fishing_talk_scene(talk), &shown_rod, 0, TURTLE_FISHING_TALK_MOTION_B, 0);
            u16 rod = TURTLE_FISHING_TALK_ROD;
            CurrentPockets_Give(&rod, 0);
            line = TURTLE_FISHING_TALK_LINE_ROD_GIVEN;
            TalkChecks_TestSetDailyBit(TURTLE_FISHING_TALK_DAILY_BIT, 1);
            break;
        }
        case TURTLE_FISHING_TALK_LINE_SHOW_FISH:
            SceneCommand_SetPocketPredicate(turtle_fishing_talk_scene(talk),
                                            (PocketPredicate) (void (*)(void)) func_ov081_02279124,
                                            TURTLE_FISHING_TALK_POCKETS_ARG, 1);
            SceneCommand_RequestScreen(turtle_fishing_talk_scene(talk), TURTLE_FISHING_TALK_POCKETS_SCREEN);
            TurtleFishingTalk_SetAfterCommand(talk, TURTLE_FISHING_TALK_AFTER_POCKETS);
            break;
    }
    turtle_fishing_talk_say_unless_none(talk, line, data_ov081_02279868);
}
CLEAN_AS(func_ov081_02278b68, TurtleFishingTalk_OnLineEnd)

/* func_ov081_02279068 (after the pockets' screen of line 0xb): no item and no size yet; when a
 * pocket was picked (GroupParams_C4CIs1) its fish is weighed (a random size), shown by motion
 * 14, its name put into the talk's slot 2 and its size into slot 4, the talk's next line asked
 * for after that motion, and its pocket emptied: line 0xd. Else the next line, and line 0xc.
 * QUIRK: the picked pocket is emptied only when its number is not negative, which it always
 * is. */
void TurtleFishingTalk_AfterPockets(TurtleFishingTalk *talk)
{
    TalkObject *object = turtle_fishing_talk_object(talk);
    u8 line = TURTLE_FISHING_TALK_LINE_NO_FISH;

    talk->item = TURTLE_FISHING_TALK_NO_ITEM;
    talk->owner->size = 0;
    if (GroupParams_C4CIs1()) {
        int slot = GroupParams_Arg();
        talk->item = CurrentPockets_Item((u32) slot);
        talk->owner->size = EventWinner_RandomSize(&talk->item);
        SceneCommand_RequestMotion14(turtle_fishing_talk_scene(talk), &talk->item, 0, TURTLE_FISHING_TALK_MOTION_B_FISH, 0);
        TurtleFishingTalk_SetThenCommand(talk, TURTLE_FISHING_TALK_NEXT_LINE);
        SceneBase_PutItemName(&talk->base, (int) (uintptr_t) &talk->item, TURTLE_FISHING_TALK_SLOT_FISH,
                              TURTLE_FISHING_TALK_ITEM_KIND);
        SceneBase_PutDecimal(&talk->base, talk->owner->size, TURTLE_FISHING_TALK_SLOT_FISH_SIZE,
                             TURTLE_FISHING_TALK_SIZE_FORMAT, 3);
        if (slot >= 0) {
            CurrentPockets_Empty(slot);
        }
        line = TURTLE_FISHING_TALK_LINE_WEIGHED;
    } else {
        SceneCommand_RequestNextLine(turtle_fishing_talk_scene(talk));
    }
    TalkObject_SetMessage(object, &line, data_ov081_02279868);
}
CLEAN_AS(func_ov081_02279068, TurtleFishingTalk_AfterPockets)
