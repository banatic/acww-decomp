/* The otter's talk scene (otter_talk.h): its class, its lines, the player's answers and the
 * items given and taken. */
#include "otter_talk.h"

#include <stdint.h>

#include "autoload_2/heap.h"
#include "clean.h"
#include "main/current_pockets.h"
#include "main/event_schedule.h"
#include "main/group_params.h"
#include "main/item_code.h"
#include "main/item_lists.h"
#include "main/main_random.h"
#include "main/message_receiver.h"
#include "main/obj_020d9ff8.h"
#include "main/pockets.h"
#include "main/scene_base.h"
#include "main/scene_command.h"
#include "main/talk_answers.h"
#include "main/talk_checks.h"
#include "main/talk_object.h"
#include "ov004/member_pointer.h"

static_assert(sizeof(SceneBase) == 0x80, "scene base");
static_assert(offsetof(OtterTalk, sequence) == 0xb0 && offsetof(OtterTalk, owner) == 0xb4, "OtterTalk");
static_assert(offsetof(OtterTalk, item) == 0xb8 && offsetof(OtterTalk, after_command) == 0xbc, "OtterTalk");
static_assert(sizeof(OtterTalk) == 0xc4, "OtterTalk");
static_assert(sizeof(OtterTalkStart) == 8, "what a talk starts with");
static_assert(sizeof(ItemList) == 8, "an item list");

/* The vtable of its class. */
extern const u8 data_ov076_02279744[];
/* Its message file, "sp_npc_otter". */
extern const char data_ov076_022796e0[];
/* The line each sequence starts with (OTTER_TALK_*). */
extern const OtterTalkStart data_ov076_02279594[OTTER_TALK_SEQUENCES];
/* The functions OtterTalk_SetAfterCommand picks from: a table filled once (bit 0 of the guard
 * word) from the overlay's constant (OtterTalk_AfterPockets). */
extern u32 data_ov076_02279880;
extern MemberPointer data_ov076_02279884[1];
extern const MemberPointer data_ov076_02279688;
/* The null member pointer. */
extern const MemberPointer __ptmf_null;
/* The pockets' predicate, as the game hands it to Pockets_Select and the pockets' screen (the
 * game's symbol of OtterTalk_IsAskedItem). */
extern int func_ov076_02278f0c(u16 *item, int state);

#define OTTER_TALK_NO_ITEM 0xfff1
#define OTTER_TALK_NO_LINE 0xff

/* The vtable slot of the scene that resets it (OtterTalk_Reset). */
#define OTTER_TALK_SLOT_RESET 0x08

/* The item he asks for, and those he gives at lines 10 and 11. */
#define OTTER_TALK_ASKED_ITEM 0x1559
#define OTTER_TALK_GIFT_10 0x4a38
#define OTTER_TALK_GIFT_11 0x1373

/* The current player's daily bit of a talk with him. */
#define OTTER_TALK_DAILY_BIT 0x18

/* The event the current player takes part in at lines 13 and 14 (event_schedule.h). */
#define OTTER_TALK_EVENT 0x42

/* The pockets' screen: its predicate's argument, and the screen. */
#define OTTER_TALK_POCKETS_ARG 0xd
#define OTTER_TALK_POCKETS_SCREEN 0

/* The values its item motions (SceneCommand_RequestMotion13 and 14) are asked with. */
#define OTTER_TALK_MOTION_B 5

/* The item lists the gift of lines 13 and 14 is drawn from: kind 0 for a draw of 0-6 of 9,
 * kind 4 for 7, kind 3 for 8; all of group 0x15. */
#define OTTER_TALK_DRAWS 9
#define OTTER_TALK_DRAW_KIND_0_LAST 6
#define OTTER_TALK_DRAW_KIND_4 7
#define OTTER_TALK_GIFT_GROUP 0x15

/* Its lines (the receiver's message). */
#define OTTER_TALK_LINE_ASK 4
#define OTTER_TALK_LINE_NOT_GIVEN 5
#define OTTER_TALK_LINE_GIVEN 6
#define OTTER_TALK_LINE_8 8
#define OTTER_TALK_LINE_8_SECOND 9
#define OTTER_TALK_LINE_8_OTHER 0x0a
#define OTTER_TALK_LINE_8_FIRST 0x0b
#define OTTER_TALK_LINE_GIFT_10 10
#define OTTER_TALK_LINE_GIFT_11 11
#define OTTER_TALK_LINE_GIFT_CHECK 12
#define OTTER_TALK_LINE_GIFTED 0x0c
#define OTTER_TALK_LINE_AFTER_RANDOM 0x0d /* or 0x0e */
#define OTTER_TALK_LINE_DRAW_13 13
#define OTTER_TALK_LINE_DRAW_14 14
#define OTTER_TALK_LINE_RANDOM_FIRST 0x0f
#define OTTER_TALK_LINE_RANDOM_LAST 0xfc
#define OTTER_TALK_LINE_RANDOM_COUNT (OTTER_TALK_LINE_RANDOM_LAST - OTTER_TALK_LINE_RANDOM_FIRST + 1)
#define OTTER_TALK_LINE_FD 0xfd
#define OTTER_TALK_LINE_GIFT_KNOWN 0x33

static TalkObject *otter_talk_object(OtterTalk *talk)
{
    return (TalkObject *) (void *) talk->base.talk;
}

static SceneCommandScene *otter_talk_scene(OtterTalk *talk)
{
    return (SceneCommandScene *) (void *) talk;
}

/* The line shown. */
static u8 otter_talk_shown(const OtterTalk *talk)
{
    return ((const MessageReceiver *) (const void *) talk)->message;
}

/* Whether an item is `code`: by its variant's item for an item with a variant, else by code. */
static int otter_talk_is_item(const u16 *item, u16 code)
{
    if (ItemCode_HasVariant(item)) {
        int own = ItemCode_VariantItem(item);
        return own == ItemCode_VariantItem(&code);
    }
    return *item == code;
}

/* The talk shows `line` of "sp_npc_otter" unless it is OTTER_TALK_NO_LINE. */
static void otter_talk_say_unless_none(OtterTalk *talk, u8 line)
{
    if (line != OTTER_TALK_NO_LINE) {
        u8 message = line;
        TalkObject_SetMessage(otter_talk_object(talk), &message, data_ov076_022796e0);
    }
}

/* ---- The class */

/* func_ov076_02278e34 (vtable slot 0x08): the scene base's reset, and nothing to run after a
 * command. */
void OtterTalk_Reset(OtterTalk *talk)
{
    SceneBase_Reset(&talk->base);
    talk->after_command = __ptmf_null;
}
CLEAN_AS(func_ov076_02278e34, OtterTalk_Reset)

/* func_ov076_02278e58 (vtable slot 0x04): the destructor of the scene class it derives from,
 * then the scene freed. */
OtterTalk *OtterTalk_DestructDelete(OtterTalk *talk)
{
    talk->base.vtable = data_ov076_02279744;
    Obj020d9ff8_DestructBody(talk);
    Heap_OperatorDeleteB(talk);
    return talk;
}
CLEAN_AS(func_ov076_02278e58, OtterTalk_DestructDelete)

/* func_ov076_02278e78 (vtable slot 0x00): the destructor of the scene class it derives from. */
OtterTalk *OtterTalk_Destruct(OtterTalk *talk)
{
    talk->base.vtable = data_ov076_02279744;
    Obj020d9ff8_DestructBody(talk);
    return talk;
}
CLEAN_AS(func_ov076_02278e78, OtterTalk_Destruct)

/* func_ov076_02278e90: the constructor: a scene of class 0x020d9ff8 given this class's vtable;
 * no item given. */
OtterTalk *OtterTalk_Construct(OtterTalk *talk)
{
    Obj020d9ff8_Construct(talk);
    talk->base.vtable = data_ov076_02279744;
    talk->item = OTTER_TALK_NO_ITEM;
    return talk;
}
CLEAN_AS(func_ov076_02278e90, OtterTalk_Construct)

/* func_ov076_02278e04: the scene reset (its vtable slot 0x08) and given its owner, who has
 * given nothing yet; sequence 0. */
void OtterTalk_Begin(OtterTalk *talk, Otter *owner)
{
    u32 vtable = *(const u32 *) (const void *) talk;
    u32 code = *(const u32 *) (uintptr_t) (vtable + OTTER_TALK_SLOT_RESET);
    ((void (*)(OtterTalk *))(uintptr_t) code)(talk);
    talk->owner = owner;
    talk->owner->gave = 0;
    talk->sequence = OTTER_TALK_HAS_ITEM;
}
CLEAN_AS(func_ov076_02278e04, OtterTalk_Begin)

/* func_ov076_02278f5c: the function run when a command of the scene ends: entry `index` of a
 * table filled the first time from the overlay's constant (entry 0, OtterTalk_AfterPockets).
 * REQUIRES: `index` is 0 (the table has one entry and is not bounded). */
void OtterTalk_SetAfterCommand(OtterTalk *talk, int index)
{
    static const MemberPointer *const functions[1] = {&data_ov076_02279688};
    MemberTable_InitOnce(&data_ov076_02279880, data_ov076_02279884, functions, 1);
    talk->after_command = data_ov076_02279884[index];
}
CLEAN_AS(func_ov076_02278f5c, OtterTalk_SetAfterCommand)

/* func_ov076_02278fa8 (vtable slot 0x84, a command of the scene ended): the function asked for
 * runs once, when there is one. */
void OtterTalk_OnCommandEnded(OtterTalk *talk)
{
    if (talk->after_command.function == 0) {
        return;
    }
    MemberPointer_CallVoid(&talk->after_command, talk);
    talk->after_command = __ptmf_null;
}
CLEAN_AS(func_ov076_02278fa8, OtterTalk_OnCommandEnded)

/* ---- Its lines */

/* func_ov076_02278f0c (the pockets' predicate): an item in a slot of state 0 that is 0x1559. */
int OtterTalk_IsAskedItem(u16 *item, int state)
{
    if (state != 0) {
        return 0;
    }
    return otter_talk_is_item(item, OTTER_TALK_ASKED_ITEM);
}
CLEAN_AS(func_ov076_02278f0c, OtterTalk_IsAskedItem)

/* func_ov076_02278d94 (vtable slot 0x78): with the item 0x1559 in the pockets the talk starts
 * with its line 2, else with line 0 or 1 at random. */
void OtterTalk_Line(OtterTalk *talk, OtterTalkStart *out)
{
    if (Pockets_Select(func_ov076_02278f0c) != 0) {
        talk->sequence = OTTER_TALK_HAS_ITEM;
    } else if (MainRandom_Below(2) == 0) {
        talk->sequence = OTTER_TALK_FIRST;
    } else {
        talk->sequence = OTTER_TALK_SECOND;
    }
    if (talk->sequence >= 0 && talk->sequence < OTTER_TALK_SEQUENCES) {
        out->message = data_ov076_02279594[talk->sequence].message;
        out->name = data_ov076_02279594[talk->sequence].name;
    }
}
CLEAN_AS(func_ov076_02278d94, OtterTalk_Line)

/* func_ov076_02278af0 (vtable slot 0x18, the player answered): see otter_talk.h. */
void OtterTalk_OnAnswer(OtterTalk *talk)
{
    unsigned int answer = TalkAnswers_Picked((TalkAnswers *) (uintptr_t) (u32) SceneBase_TalkChoices(&talk->base));
    u8 line = OTTER_TALK_NO_LINE;

    switch (otter_talk_shown(talk)) {
        case 0:
        case 1:
            if (answer == 0) {
                line = (u8) (MainRandom_Below(OTTER_TALK_LINE_RANDOM_COUNT) + OTTER_TALK_LINE_RANDOM_FIRST);
            } else {
                line = OTTER_TALK_LINE_NOT_GIVEN;
            }
            break;
        case 2:
            if (answer == 2) {
                line = OTTER_TALK_LINE_ASK;
            }
            break;
        case OTTER_TALK_LINE_8:
            if (answer == 0) {
                line = OTTER_TALK_LINE_8_FIRST;
            } else if (answer == 1) {
                line = OTTER_TALK_LINE_8_SECOND;
            } else {
                line = OTTER_TALK_LINE_8_OTHER;
            }
            break;
    }
    otter_talk_say_unless_none(talk, line);
}
CLEAN_AS(func_ov076_02278af0, OtterTalk_OnAnswer)

/* He hands talk->item to the player: the item motion, the item into the pockets and the daily
 * bit set. */
static void otter_talk_hand_over(OtterTalk *talk)
{
    SceneCommand_RequestMotion13(otter_talk_scene(talk), &talk->item, 0, OTTER_TALK_MOTION_B, 0);
    CurrentPockets_Give(&talk->item, 0);
}

/* func_ov076_02278b78 (vtable slot 0x14, a line ended): see otter_talk.h. */
void OtterTalk_OnLineEnd(OtterTalk *talk)
{
    u8 shown = otter_talk_shown(talk);
    u8 line = OTTER_TALK_NO_LINE;

    if (shown == OTTER_TALK_LINE_FD || (shown >= OTTER_TALK_LINE_RANDOM_FIRST && shown <= OTTER_TALK_LINE_RANDOM_LAST)) {
        line = (u8) (MainRandom_Below(2) + OTTER_TALK_LINE_AFTER_RANDOM);
    }

    switch (shown) {
        case OTTER_TALK_LINE_ASK:
            SceneCommand_SetPocketPredicate(otter_talk_scene(talk), func_ov076_02278f0c, OTTER_TALK_POCKETS_ARG, 0);
            SceneCommand_RequestScreen(otter_talk_scene(talk), OTTER_TALK_POCKETS_SCREEN);
            OtterTalk_SetAfterCommand(talk, 0);
            break;
        case OTTER_TALK_LINE_GIFT_10:
        case OTTER_TALK_LINE_GIFT_11:
            talk->item = shown == OTTER_TALK_LINE_GIFT_10 ? OTTER_TALK_GIFT_10 : OTTER_TALK_GIFT_11;
            otter_talk_hand_over(talk);
            talk->owner->gave = 1;
            TalkChecks_TestSetDailyBit(OTTER_TALK_DAILY_BIT, 1);
            line = OTTER_TALK_LINE_GIFTED;
            break;
        case OTTER_TALK_LINE_GIFT_CHECK:
            line = otter_talk_is_item(&talk->item, OTTER_TALK_GIFT_10) ? OTTER_TALK_LINE_GIFT_KNOWN : OTTER_TALK_LINE_FD;
            break;
        case OTTER_TALK_LINE_DRAW_13:
        case OTTER_TALK_LINE_DRAW_14:
            if (talk->owner->gave == 0) {
                if (CurrentPockets_FreeSlot() >= 0) {
                    unsigned int draw = MainRandom_Below(OTTER_TALK_DRAWS);
                    int kind = draw <= OTTER_TALK_DRAW_KIND_0_LAST ? 0 : draw == OTTER_TALK_DRAW_KIND_4 ? 4 : 3;
                    ItemList list;
                    u16 drawn;
                    ItemList_Construct(&list, kind, OTTER_TALK_GIFT_GROUP);
                    ItemLists_Draw(&drawn, &list, 0, 0, 1, 1, 0);
                    talk->item = drawn;
                    ItemList_Destruct(&list);
                    otter_talk_hand_over(talk);
                    TalkChecks_TestSetDailyBit(OTTER_TALK_DAILY_BIT, 1);
                }
                talk->owner->gave = 1;
            }
            EventSchedule_MarkTakenPart(OTTER_TALK_EVENT);
            break;
    }
    otter_talk_say_unless_none(talk, line);
}
CLEAN_AS(func_ov076_02278b78, OtterTalk_OnLineEnd)

/* func_ov076_02278eb4 (after the pockets' screen of line 4): when a pocket was picked
 * (GroupParams_C4CIs1), it is emptied and the item 0x1559 handed to him: line 6; else line 5.
 * QUIRK: the picked pocket is emptied only when its number is not negative, which it always
 * is. */
void OtterTalk_AfterPockets(OtterTalk *talk)
{
    TalkObject *object = otter_talk_object(talk);
    u8 line = OTTER_TALK_LINE_NOT_GIVEN;

    if (GroupParams_C4CIs1()) {
        int slot = GroupParams_Arg();
        if (slot >= 0) {
            CurrentPockets_Empty(slot);
        }
        u16 asked = OTTER_TALK_ASKED_ITEM;
        SceneCommand_RequestMotion14(otter_talk_scene(talk), &asked, 0, OTTER_TALK_MOTION_B, 0);
        line = OTTER_TALK_LINE_GIVEN;
    }
    TalkObject_SetMessage(object, &line, data_ov076_022796e0);
}
CLEAN_AS(func_ov076_02278eb4, OtterTalk_AfterPockets)
