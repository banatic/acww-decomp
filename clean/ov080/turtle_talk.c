/* The turtle's talk scene (turtle_talk.h). */
#include "turtle_talk.h"

#include <stdint.h>

#include "autoload_2/heap.h"
#include "clean.h"
#include "main/current_pockets.h"
#include "main/item_record.h"
#include "main/main_random.h"
#include "main/message_receiver.h"
#include "main/obj_020d9ff8.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/scene_base.h"
#include "main/scene_command.h"
#include "main/talk_answers.h"
#include "main/talk_object.h"
#include "turtle.h"

static_assert(offsetof(TurtleTalk, owner) == 0xb0 && offsetof(TurtleTalk, slot) == 0xb4, "TurtleTalk");
static_assert(sizeof(TurtleTalk) == 0xb8, "TurtleTalk");
static_assert(sizeof(TurtleTalkLine) == 8, "TurtleTalkLine");

/* The archives of his lines: "sp_npc_turtle", "sp_etc_sequence5_2" and "sp_npc_turtle7". */
extern const char data_ov080_02279398[];
extern const char data_ov080_022793a8[];
extern const char data_ov080_022793bc[];
/* The class's vtable. */
extern const u8 data_ov080_0227925c[];
/* The town's four players' records (player_records.h). */
extern u8 data_021dc7bc[];

/* The talk scene's vtable slot that resets it (SceneBase_Reset). */
#define TURTLE_TALK_SLOT_RESET 2

#define TURTLE_TALK_NO_LINE 0xff

/* The flags of the player's record (player_record.h) the talk reads and sets. */
#define TURTLE_TALK_FLAG_1 1
#define TURTLE_TALK_FLAG_SEQUENCE_TALKED 0xa
#define TURTLE_TALK_FLAG_SEQUENCE_MET 0xd
#define TURTLE_TALK_FLAG_FISH_GIFT 0x21
#define TURTLE_TALK_FLAG_INSECT_GIFT 0x22

/* The item he asks for and the one he gives for it; the gifts for all the fish and all the
 * insects recorded. */
#define TURTLE_TALK_ASKED 0x37e0
#define TURTLE_TALK_TRADED 0x1559
#define TURTLE_TALK_FISH_GIFT 0x1375
#define TURTLE_TALK_INSECT_GIFT 0x1377

/* The scene command's motions of an item: taken from the player, and in his hand. */
#define TURTLE_TALK_TAKE_MOTION 5
#define TURTLE_TALK_HAND_MOTION 5
/* The kind the name of an item is put in with (SceneBase_PutItemName). */
#define TURTLE_TALK_ITEM_NAME_KIND 7

/* The lines of "sp_npc_turtle". */
#define TURTLE_TALK_LINE_ASK 0x00 /* answered 0: the item taken */
#define TURTLE_TALK_LINE_REFUSED 0x01
#define TURTLE_TALK_LINE_TAKEN 0x02 /* then the item given in return */
#define TURTLE_TALK_LINE_TRADED 0x04

/* The lines of "sp_etc_sequence5_2": the first, then one of four. */
#define TURTLE_TALK_SEQUENCE_FIRST 0x00
#define TURTLE_TALK_SEQUENCE_AGAIN 0x03
#define TURTLE_TALK_SEQUENCE_LINES 4

/* The lines of "sp_npc_turtle7". */
#define TURTLE_TALK_LINE_FISH 0x00 /* the gift for all the fish */
#define TURTLE_TALK_LINE_FISH_GIVEN 0x01
#define TURTLE_TALK_LINE_FISH_OTHER 0x02 /* another player of the town had it */
#define TURTLE_TALK_LINE_INSECTS 0x03    /* the gift for all the insects */
#define TURTLE_TALK_LINE_INSECTS_GIVEN 0x04
#define TURTLE_TALK_LINE_INSECTS_OTHER 0x05
#define TURTLE_TALK_LINE_CHAT 0x06 /* 0x06-0x08 */
#define TURTLE_TALK_LINES_CHAT 3
#define TURTLE_TALK_LINE_FISH_NO_ROOM 0x09
#define TURTLE_TALK_LINE_INSECTS_NO_ROOM 0x0a

static TalkObject *turtle_talk_object(const TurtleTalk *talk)
{
    return (TalkObject *) (void *) talk->scene.talk;
}

static SceneCommandScene *turtle_talk_command(TurtleTalk *talk)
{
    return (SceneCommandScene *) (void *) talk;
}

/* The number of the line shown (the receiver's message). */
static u8 turtle_talk_shown(const TurtleTalk *talk)
{
    return ((const MessageReceiver *) (const void *) talk)->message;
}

/* Line `line` of the archive `name` shown by the talk. */
static void turtle_talk_say(TurtleTalk *talk, u8 line, const char *name)
{
    TalkObject_SetMessage(turtle_talk_object(talk), &line, name);
}

/* Whether another of the town's players than `player` is in use and has `flag`. */
static int turtle_talk_other_has(const u8 *player, u32 flag)
{
    for (int i = 0; i < PLAYER_RECORDS_TOWN; i++) {
        u8 *other = PlayerRecords_TownRecord(data_021dc7bc, i);
        if (other != NULL && PlayerRecord_HasPlayer(other) != 0 && other != player &&
            PlayerRecord_TestFlag(other, flag) != 0) {
            return 1;
        }
    }
    return 0;
}

/* `item` given to the player; when it fit, shown in his hand, `flag` set and its name in part
 * 0. Whether it fit. */
static int turtle_talk_give(TurtleTalk *talk, u8 *player, u16 item, u32 flag)
{
    if (CurrentPockets_Give(&item, 0) == 0) {
        return 0;
    }
    SceneCommand_RequestMotion13(turtle_talk_command(talk), &item, 0, TURTLE_TALK_HAND_MOTION, 0);
    PlayerRecord_SetFlag(player, flag);
    SceneBase_PutItemName(&talk->scene, (int) (u32) (uintptr_t) &item, 0, TURTLE_TALK_ITEM_NAME_KIND);
    return 1;
}

/* ---- Its slots */

/* func_ov080_02278ab8 (slot 0x18): with item 0x37e0 found in the pockets, line 0 answered 0
 * takes it: its slot emptied, the item going from the player to him and line 2 of
 * "sp_npc_turtle". The answer is read whatever the line.
 * QUIRK: without the item, flag 1 of the player's record is tested and the result dropped. */
void TurtleTalk_OnAnswer(TurtleTalk *talk)
{
    unsigned int answer = TalkAnswers_Picked((TalkAnswers *) (uintptr_t) (u32) SceneBase_TalkChoices(&talk->scene));
    u8 *player = PlayerRecords_Current();
    int slot = talk->slot;

    if (slot < 0) {
        PlayerRecord_TestFlag(player, TURTLE_TALK_FLAG_1);
        return;
    }
    if (turtle_talk_shown(talk) == TURTLE_TALK_LINE_ASK && answer == 0) {
        CurrentPockets_Empty(slot);
        u16 item = TURTLE_TALK_ASKED;
        SceneCommand_RequestMotion14(turtle_talk_command(talk), &item, 0, TURTLE_TALK_TAKE_MOTION, 0);
        turtle_talk_say(talk, TURTLE_TALK_LINE_TAKEN, data_ov080_02279398);
    }
}
CLEAN_AS(func_ov080_02278ab8, TurtleTalk_OnAnswer)

/* func_ov080_02278b30 (slot 0x14): what follows the line shown.
 * With item 0x37e0 found in the pockets: after line 1 or 4 the trade is done for this visit;
 * after line 2 item 0x1559 is shown in his hand and given, and line 4 of "sp_npc_turtle".
 * Else, unless the player record has flag 1: after line 0 or 2 of "sp_npc_turtle7" item
 * 0x1375 is given (flag 0x21, line 1), after line 3 or 5 item 0x1377 (flag 0x22, line 4); when
 * it does not fit, nothing follows. */
void TurtleTalk_OnLineShown(TurtleTalk *talk)
{
    int line = TURTLE_TALK_NO_LINE;

    if (talk->slot >= 0) {
        if (turtle_talk_shown(talk) == TURTLE_TALK_LINE_REFUSED || turtle_talk_shown(talk) == TURTLE_TALK_LINE_TRADED) {
            talk->slot = TURTLE_TALK_SLOT_DONE;
        }
        if (turtle_talk_shown(talk) != TURTLE_TALK_LINE_TAKEN) {
            return;
        }
        u16 shown = TURTLE_TALK_TRADED;
        SceneCommand_RequestMotion13(turtle_talk_command(talk), &shown, 0, TURTLE_TALK_HAND_MOTION, 0);
        u16 given = TURTLE_TALK_TRADED;
        CurrentPockets_Give(&given, 0);
        turtle_talk_say(talk, TURTLE_TALK_LINE_TRADED, data_ov080_02279398);
        return;
    }

    u8 *player = PlayerRecords_Current();
    if (PlayerRecord_TestFlag(player, TURTLE_TALK_FLAG_1) != 0) {
        return;
    }
    switch (turtle_talk_shown(talk)) {
        case TURTLE_TALK_LINE_FISH:
        case TURTLE_TALK_LINE_FISH_OTHER:
            if (turtle_talk_give(talk, player, TURTLE_TALK_FISH_GIFT, TURTLE_TALK_FLAG_FISH_GIFT)) {
                line = TURTLE_TALK_LINE_FISH_GIVEN;
            }
            break;
        case TURTLE_TALK_LINE_INSECTS:
        case TURTLE_TALK_LINE_INSECTS_OTHER:
            if (turtle_talk_give(talk, player, TURTLE_TALK_INSECT_GIFT, TURTLE_TALK_FLAG_INSECT_GIFT)) {
                line = TURTLE_TALK_LINE_INSECTS_GIVEN;
            }
            break;
        default:
            break;
    }
    if (line != TURTLE_TALK_NO_LINE) {
        turtle_talk_say(talk, (u8) line, data_ov080_022793bc);
    }
}
CLEAN_AS(func_ov080_02278b30, TurtleTalk_OnLineShown)

/* func_ov080_02278c88 (slot 0x78): the first line, by the current player's record:
 * - flag 1: "sp_etc_sequence5_2", line 0 when flag 0xd is clear (and set now), else one of
 *   the lines 3-6; flag 0xa set;
 * - when the pockets were not found holding item 0x37e0 yet in this visit and now do (the slot
 *   kept): line 0 of "sp_npc_turtle";
 * - else "sp_npc_turtle7": without flag 0x21 and with all the fish recorded, line 0, or 9
 *   without a free slot, or 2 when another player of the town has flag 0x21; else without flag
 *   0x22 and with all the insects recorded, line 3, or 0x0a, or 5 by flag 0x22; else one of
 *   the lines 6-8. */
void TurtleTalk_Line(TurtleTalk *talk, TurtleTalkLine *line)
{
    u8 *player = PlayerRecords_Current();

    if (PlayerRecord_TestFlag(player, TURTLE_TALK_FLAG_1) != 0) {
        line->name = data_ov080_022793a8;
        if (PlayerRecord_TestFlag(player, TURTLE_TALK_FLAG_SEQUENCE_MET) == 0) {
            line->message = TURTLE_TALK_SEQUENCE_FIRST;
            PlayerRecord_SetFlag(player, TURTLE_TALK_FLAG_SEQUENCE_MET);
        } else {
            line->message = (u8) (MainRandom_Below(TURTLE_TALK_SEQUENCE_LINES) + TURTLE_TALK_SEQUENCE_AGAIN);
        }
        PlayerRecord_SetFlag(player, TURTLE_TALK_FLAG_SEQUENCE_TALKED);
        return;
    }

    if (talk->slot == TURTLE_TALK_SLOT_UNKNOWN) {
        u16 asked = TURTLE_TALK_ASKED;
        talk->slot = CurrentPockets_FindItem(&asked);
        if (talk->slot >= 0) {
            line->name = data_ov080_02279398;
            line->message = TURTLE_TALK_LINE_ASK;
            return;
        }
    }

    line->name = data_ov080_022793bc;
    if (PlayerRecord_TestFlag(player, TURTLE_TALK_FLAG_FISH_GIFT) == 0 && ItemRecord_HasAllFish() != 0) {
        line->message = TURTLE_TALK_LINE_FISH;
        if (CurrentPockets_FreeSlot() < 0) {
            line->message = TURTLE_TALK_LINE_FISH_NO_ROOM;
        } else if (turtle_talk_other_has(player, TURTLE_TALK_FLAG_FISH_GIFT)) {
            line->message = TURTLE_TALK_LINE_FISH_OTHER;
        }
        return;
    }
    if (PlayerRecord_TestFlag(player, TURTLE_TALK_FLAG_INSECT_GIFT) == 0 && ItemRecord_HasAllInsects() != 0) {
        line->message = TURTLE_TALK_LINE_INSECTS;
        if (CurrentPockets_FreeSlot() < 0) {
            line->message = TURTLE_TALK_LINE_INSECTS_NO_ROOM;
        } else if (turtle_talk_other_has(player, TURTLE_TALK_FLAG_INSECT_GIFT)) {
            line->message = TURTLE_TALK_LINE_INSECTS_OTHER;
        }
        return;
    }
    line->message = (u8) (MainRandom_Below(TURTLE_TALK_LINES_CHAT) + TURTLE_TALK_LINE_CHAT);
}
CLEAN_AS(func_ov080_02278c88, TurtleTalk_Line)

/* func_ov080_02278dec: the talk reset (its vtable slot 2), `owner` its owner and the pockets
 * not looked at. */
void TurtleTalk_Begin(TurtleTalk *talk, struct Turtle *owner)
{
    const u32 *vtable = (const u32 *) (const void *) talk->scene.vtable;
    ((void (*)(TurtleTalk *))(uintptr_t) vtable[TURTLE_TALK_SLOT_RESET])(talk);
    talk->owner = owner;
    talk->slot = TURTLE_TALK_SLOT_UNKNOWN;
}
CLEAN_AS(func_ov080_02278dec, TurtleTalk_Begin)

/* ---- Its life */

/* func_ov080_02278e10 (slot 0x04): destructed, then freed. */
TurtleTalk *TurtleTalk_DestructDelete(TurtleTalk *talk)
{
    talk->scene.vtable = data_ov080_0227925c;
    Obj020d9ff8_DestructBody(talk);
    Heap_OperatorDeleteB(talk);
    return talk;
}
CLEAN_AS(func_ov080_02278e10, TurtleTalk_DestructDelete)

/* func_ov080_02278e30 (slot 0x00): the destructor: its class's vtable, then the base class's
 * body. */
TurtleTalk *TurtleTalk_Destruct(TurtleTalk *talk)
{
    talk->scene.vtable = data_ov080_0227925c;
    Obj020d9ff8_DestructBody(talk);
    return talk;
}
CLEAN_AS(func_ov080_02278e30, TurtleTalk_Destruct)

/* func_ov080_02278e48: the base class constructed, then its class's vtable. */
TurtleTalk *TurtleTalk_Construct(TurtleTalk *talk)
{
    Obj020d9ff8_Construct(talk);
    talk->scene.vtable = data_ov080_0227925c;
    return talk;
}
CLEAN_AS(func_ov080_02278e48, TurtleTalk_Construct)
