/* The talk scene of overlay 73's character (boar_talk.h). */
#include "boar_talk.h"

#include <stdint.h>

#include "autoload_2/heap.h"
#include "boar.h"
#include "clean.h"
#include "main/current_pockets.h"
#include "main/group_params.h"
#include "main/message_receiver.h"
#include "main/obj_020d9ff8.h"
#include "main/scene_bells.h"
#include "main/scene_command.h"
#include "main/screen_panels.h"
#include "main/state_block.h"
#include "main/talk_answers.h"
#include "main/talk_checks.h"
#include "main/talk_object.h"
#include "main/turnip_prices.h"

static_assert(offsetof(BoarTalk, topic) == 0xb0 && offsetof(BoarTalk, after_screen) == 0xb8, "BoarTalk");
static_assert(offsetof(BoarTalk, price) == 0xc0 && offsetof(BoarTalk, sold_1567) == 0xc8, "BoarTalk");
static_assert(sizeof(BoarTalk) == 0xcc, "BoarTalk");
static_assert(sizeof(BoarTalkLine) == 8, "BoarTalkLine");

/* "sp_npc_boar", the archive of its lines. */
extern const char data_ov073_02279a10[];
/* The first line of each topic. */
extern const BoarTalkLine data_ov073_02279844[BOAR_TALK_TOPICS];
/* The week's turnip prices and the state block. */
extern TurnipPrices data_021f3b0c;
extern StateBlock data_021dc7a8;

/* The class's vtable. */
extern const u8 data_ov073_02279a70[];

/* BoarTalk_IsEmptySlot, handed to the pockets as the game's function. */
extern int func_ov073_02278e44(u16 *item);

/* The talk scene's vtable slot that resets it (BoarTalk_Reset). */
#define BOAR_TALK_SLOT_RESET 2

/* The player's daily bit of its first talk of the day (talk_checks.h). */
#define BOAR_TALK_DAILY_TALKED 3

/* The counted items: 0x1531 + n holds n + 1 tens; 0x153a ten tens. */
#define BOAR_TALK_TEN_FIRST 0x1531
#define BOAR_TALK_TEN_FULL 0x153a
#define BOAR_TALK_TENS_FULL 10
/* The item sold once a week for 1000 Bells, and flag 4 of the state block that marks it sold. */
#define BOAR_TALK_ITEM_1567 0x1567
#define BOAR_TALK_ITEM_1567_PRICE 1000
#define BOAR_TALK_FLAG_1567 4
/* What an empty slot of the pockets holds. */
#define BOAR_TALK_EMPTY 0xfff1

/* The parts of the talk the lines put values in (SceneBase_PutValue), and their formats. */
#define BOAR_TALK_PART_UNIT_PRICE 0
#define BOAR_TALK_PART_COUNT 1
#define BOAR_TALK_PART_PRICE 2
#define BOAR_TALK_FORMAT_BELLS 0xa
#define BOAR_TALK_FORMAT_COUNT 3

/* The screen the player picks the tens on (scene_command.h). */
#define BOAR_TALK_SCREEN_MODE 0x3a
#define BOAR_TALK_SCREEN SCENE_COMMAND_SCREEN_MODE

/* The scene command's motion of the item in hand (scene_command.h). */
#define BOAR_TALK_HAND_MOTION 5

#define BOAR_TALK_NO_LINE 0xff

static TalkObject *boar_talk_object(const BoarTalk *talk)
{
    return (TalkObject *) (void *) talk->scene.talk;
}

static SceneCommandScene *boar_talk_command(BoarTalk *talk)
{
    return (SceneCommandScene *) (void *) talk;
}

/* The number of the line shown (the receiver's message). */
static u8 boar_talk_shown(const BoarTalk *talk)
{
    return ((const MessageReceiver *) (const void *) talk)->message;
}

/* Line `line` of "sp_npc_boar" shown by `object`. */
static void boar_talk_say(TalkObject *object, u8 line)
{
    TalkObject_SetMessage(object, &line, data_ov073_02279a10);
}

/* The owner, as the word the Bells' functions take and do not use. */
static int boar_talk_owner_word(const BoarTalk *talk)
{
    return (int) (uintptr_t) talk->owner;
}

/* `item` in the character's hand (motion 13 of the scene's commands). */
static void boar_talk_hand(BoarTalk *talk, u16 item)
{
    SceneCommand_RequestMotion13(boar_talk_command(talk), &item, 0, BOAR_TALK_HAND_MOTION, 0);
}

/* ---- Its slots */

/* func_ov073_02278ac4 (slot 0x18): the player's answer (0 the first) to the line shown:
 * - 0x01: 0 goes to line 6, another to 2;
 * - 0x03: 0 puts the week's turnip price in part 0 and goes to 0x10; 1 goes to 0x17;
 * - 0x08, 0x0a, 0x0c: 0 goes to the next line;
 * - 0x10: 0 goes to 0x12 (the tens picked); 1 goes to 7;
 * - 0x13: 0 buys the tens picked: line 0x1b when the Bells are short, 0x1c with no free slot,
 *   0x14 without room for the items (BoarTalk_GiveTens), else the price taken, the first ten in
 *   its hand and line 0x15;
 * - 0x17: 0 goes to 0x18 when item 0x1567 was sold this week, else the screen panels are asked
 *   for and line 0x19;
 * - 0x19: 0 buys item 0x1567: line 0x1b when 1000 Bells are short, 0x1c when it does not fit
 *   the pockets, else 1000 Bells taken, the sale marked (flag 4), the item in its hand and line
 *   0x15.
 * The answer is read whatever the line. */
void BoarTalk_OnAnswer(BoarTalk *talk)
{
    unsigned int answer = TalkAnswers_Picked((TalkAnswers *) (uintptr_t) (u32) SceneBase_TalkChoices(&talk->scene));
    int line = BOAR_TALK_NO_LINE;

    switch (boar_talk_shown(talk)) {
        case 0x01:
            line = answer == 0 ? 0x06 : 0x02;
            break;
        case 0x03:
            if (answer == 0) {
                SceneBase_PutValue(&talk->scene, TurnipPrices_Current(&data_021f3b0c), BOAR_TALK_PART_UNIT_PRICE,
                                   BOAR_TALK_FORMAT_BELLS, 0, 0);
                line = 0x10;
            } else if (answer == 1) {
                line = 0x17;
            }
            break;
        case 0x08:
            if (answer == 0) {
                line = 0x09;
            }
            break;
        case 0x0a:
            if (answer == 0) {
                line = 0x0b;
            }
            break;
        case 0x0c:
            if (answer == 0) {
                line = 0x0d;
            }
            break;
        case 0x10:
            if (answer == 0) {
                line = 0x12;
            } else if (answer == 1) {
                line = 0x07;
            }
            break;
        case 0x13:
            if (answer == 0) {
                int free_slot = CurrentPockets_FreeSlot();
                if (SceneBells_CanPay(boar_talk_owner_word(talk), talk->price) == 0) {
                    line = 0x1b;
                } else if (free_slot < 0) {
                    line = 0x1c;
                } else if (BoarTalk_GiveTens(talk) == 0) {
                    line = 0x14;
                } else {
                    SceneBells_Take(boar_talk_owner_word(talk), talk->price);
                    boar_talk_hand(talk, BOAR_TALK_TEN_FIRST);
                    talk->sold_1567 = 0;
                    line = 0x15;
                }
            }
            break;
        case 0x17:
            if (answer == 0) {
                if (StateBlock_TestFlag((u32 *) (void *) &data_021dc7a8, BOAR_TALK_FLAG_1567) != 0) {
                    line = 0x18;
                } else {
                    ScreenPanels_Request();
                    line = 0x19;
                }
            }
            break;
        case 0x19:
            if (answer == 0) {
                if (SceneBells_CanPay(boar_talk_owner_word(talk), BOAR_TALK_ITEM_1567_PRICE) == 0) {
                    line = 0x1b;
                } else {
                    u16 item = BOAR_TALK_ITEM_1567;
                    if (CurrentPockets_Give(&item, 0) != 0) {
                        line = 0x15;
                        SceneBells_Take(boar_talk_owner_word(talk), BOAR_TALK_ITEM_1567_PRICE);
                        StateBlock_SetFlag((u32 *) (void *) &data_021dc7a8, BOAR_TALK_FLAG_1567);
                        talk->sold_1567 = 1;
                        boar_talk_hand(talk, BOAR_TALK_ITEM_1567);
                    } else {
                        line = 0x1c;
                    }
                }
            }
            break;
        default:
            break;
    }
    if (line != BOAR_TALK_NO_LINE) {
        boar_talk_say(boar_talk_object(talk), (u8) line);
    }
}
CLEAN_AS(func_ov073_02278ac4, BoarTalk_OnAnswer)

/* func_ov073_02278ca4 (slot 0x14): after line 0x12 the screen panels are asked for and the
 * screen of mode 0x3a opened (the talk left on its line), BoarTalk_AfterCountPicked to run
 * after it; after line 0x15, line 0x1a when item 0x1567 was sold, else 0x16. */
void BoarTalk_OnLineShown(BoarTalk *talk)
{
    int line = BOAR_TALK_NO_LINE;

    switch (boar_talk_shown(talk)) {
        case 0x12:
            ScreenPanels_Request();
            SceneCommand_SetScreenMode(boar_talk_command(talk), BOAR_TALK_SCREEN_MODE, 0);
            SceneCommand_RequestScreen(boar_talk_command(talk), BOAR_TALK_SCREEN);
            BoarTalk_SetAfterScreen(talk, BOAR_TALK_AFTER_COUNT_PICKED);
            break;
        case 0x15:
            line = talk->sold_1567 != 0 ? 0x1a : 0x16;
            break;
        default:
            break;
    }
    if (line != BOAR_TALK_NO_LINE) {
        boar_talk_say(boar_talk_object(talk), (u8) line);
    }
}
CLEAN_AS(func_ov073_02278ca4, BoarTalk_OnLineShown)

/* func_ov073_02278d08 (slot 0x78): in topic 0, once daily bit 3 is found set (it is set by the
 * test), topic 1; then the topic's archive and line. */
void BoarTalk_Line(BoarTalk *talk, BoarTalkLine *line)
{
    if (talk->topic == BOAR_TALK_TOPIC_FIRST && TalkChecks_TestSetDailyBit(BOAR_TALK_DAILY_TALKED, 1) != 0) {
        talk->topic = BOAR_TALK_TOPIC_AGAIN;
    }
    if (talk->topic < BOAR_TALK_TOPICS) {
        line->message = data_ov073_02279844[talk->topic].message;
        line->name = data_ov073_02279844[talk->topic].name;
    }
}
CLEAN_AS(func_ov073_02278d08, BoarTalk_Line)

/* func_ov073_02278d60: the talk reset (its vtable slot 2), `owner` its owner, topic 0 and no
 * purchase. */
void BoarTalk_Begin(BoarTalk *talk, struct Boar *owner)
{
    const u32 *vtable = (const u32 *) (const void *) talk->scene.vtable;
    ((void (*)(BoarTalk *))(uintptr_t) vtable[BOAR_TALK_SLOT_RESET])(talk);
    talk->owner = owner;
    talk->topic = BOAR_TALK_TOPIC_FIRST;
    talk->price = 0;
    talk->tens = 0;
    talk->sold_1567 = 0;
}
CLEAN_AS(func_ov073_02278d60, BoarTalk_Begin)

/* func_ov073_02278d94: the tens picked given as items when the pockets have room: one 0x153a
 * for each ten tens (up to ten of them) and one item for the rest, which needs a slot more.
 * Without a free slot or with fewer empty slots than items, nothing is given. Whether they
 * were given.
 * QUIRK: `tens` is used up: the full items taken off it before the check, and the rest less
 * one after. */
int BoarTalk_GiveTens(BoarTalk *talk)
{
    int free_slot = CurrentPockets_FreeSlot();
    int full = 0;
    int needed;
    PocketsMarks empty;

    for (int i = 0; i < BOAR_TALK_TENS_FULL; i++) {
        if (talk->tens >= BOAR_TALK_TENS_FULL) {
            talk->tens -= BOAR_TALK_TENS_FULL;
            full++;
        }
    }
    needed = full;
    if (talk->tens != 0) {
        needed = full + 1;
    }
    CurrentPockets_Mark(&empty, func_ov073_02278e44);
    if (free_slot < 0 || empty.count < needed) {
        return 0;
    }
    for (; full > 0; full--) {
        u16 item = BOAR_TALK_TEN_FULL;
        CurrentPockets_Give(&item, 0);
    }
    if (talk->tens > 0) {
        u16 item;
        talk->tens--;
        item = (u16) (talk->tens + BOAR_TALK_TEN_FIRST);
        CurrentPockets_Give(&item, 0);
    }
    return 1;
}
CLEAN_AS(func_ov073_02278d94, BoarTalk_GiveTens)

/* func_ov073_02278e44 (the test BoarTalk_GiveTens marks the pockets' slots with): whether the
 * slot is empty. */
int BoarTalk_IsEmptySlot(u16 *item)
{
    return *item == BOAR_TALK_EMPTY;
}
CLEAN_AS(func_ov073_02278e44, BoarTalk_IsEmptySlot)

/* ---- Its life */

extern const MemberPointer __ptmf_null;

/* func_ov073_02278e58 (slot 0x08): the scene base reset and nothing to run after a screen. */
void BoarTalk_Reset(BoarTalk *talk)
{
    SceneBase_Reset(&talk->scene);
    talk->after_screen = __ptmf_null;
}
CLEAN_AS(func_ov073_02278e58, BoarTalk_Reset)

/* func_ov073_02278e7c (slot 0x04): destructed, then freed. */
BoarTalk *BoarTalk_DestructDelete(BoarTalk *talk)
{
    talk->scene.vtable = data_ov073_02279a70;
    Obj020d9ff8_DestructBody(talk);
    Heap_OperatorDeleteB(talk);
    return talk;
}
CLEAN_AS(func_ov073_02278e7c, BoarTalk_DestructDelete)

/* func_ov073_02278e9c (slot 0x00): the destructor: its class's vtable, then the base class's
 * body. */
BoarTalk *BoarTalk_Destruct(BoarTalk *talk)
{
    talk->scene.vtable = data_ov073_02279a70;
    Obj020d9ff8_DestructBody(talk);
    return talk;
}
CLEAN_AS(func_ov073_02278e9c, BoarTalk_Destruct)

/* func_ov073_02278eb4: the base class constructed, then its class's vtable. */
BoarTalk *BoarTalk_Construct(BoarTalk *talk)
{
    Obj020d9ff8_Construct(talk);
    talk->scene.vtable = data_ov073_02279a70;
    return talk;
}
CLEAN_AS(func_ov073_02278eb4, BoarTalk_Construct)

/* ---- What runs after a screen */

/* func_ov073_02278ecc (after the screen of mode 0x3a): with the screen's result 1 the count
 * picked (GroupParams_C78, in tens) is kept, its price is the week's turnip price for ten
 * times as many, both put in parts 1 and 2, and line 0x13; else line 0x11. */
void BoarTalk_AfterCountPicked(BoarTalk *talk)
{
    TalkObject *object = boar_talk_object(talk);
    u8 line = 0x11;

    if (GroupParams_C4CIs1() != 0) {
        int count = GroupParams_C78() * 10;
        talk->tens = GroupParams_C78();
        talk->price = TurnipPrices_Current(&data_021f3b0c) * count;
        SceneBase_PutValue(&talk->scene, count, BOAR_TALK_PART_COUNT, BOAR_TALK_FORMAT_COUNT, 0, 0);
        SceneBase_PutValue(&talk->scene, talk->price, BOAR_TALK_PART_PRICE, BOAR_TALK_FORMAT_BELLS, 0, 0);
        line = 0x13;
    }
    TalkObject_SetMessage(object, &line, data_ov073_02279a10);
}
CLEAN_AS(func_ov073_02278ecc, BoarTalk_AfterCountPicked)

/* What runs after a screen, filled from its constant on the first call (bit 0 of the
 * guard). */
extern MemberPointer data_ov073_02279bdc[BOAR_TALK_AFTERS];
extern u32 data_ov073_02279bd0;
extern const MemberPointer data_ov073_022799c0;

/* func_ov073_02278f4c: `after` (BOAR_TALK_AFTER_*) to run once the screen's command ends.
 * REQUIRES: `after` is 0 (the game's is). */
void BoarTalk_SetAfterScreen(BoarTalk *talk, int after)
{
    static const MemberPointer *const afters[BOAR_TALK_AFTERS] = {
        &data_ov073_022799c0, /* BoarTalk_AfterCountPicked */
    };
    MemberTable_InitOnce(&data_ov073_02279bd0, data_ov073_02279bdc, afters, BOAR_TALK_AFTERS);
    talk->after_screen = data_ov073_02279bdc[after];
}
CLEAN_AS(func_ov073_02278f4c, BoarTalk_SetAfterScreen)

/* func_ov073_02278f98 (slot 0x84, a command of the scene ended): what was left to run after the
 * screen, once. */
void BoarTalk_RunAfterScreen(BoarTalk *talk)
{
    if (talk->after_screen.function != 0) {
        MemberPointer_CallVoid(&talk->after_screen, talk);
        talk->after_screen = __ptmf_null;
    }
}
CLEAN_AS(func_ov073_02278f98, BoarTalk_RunAfterScreen)
