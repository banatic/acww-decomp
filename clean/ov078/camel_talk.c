/* The camel's talk scene (camel_talk.h): her lines, the errand she hands over, its reward and
 * her trade for item 0x13ac. */
#include "camel_talk.h"

#include <stdint.h>

#include "autoload_2/heap.h"
#include "camel.h"
#include "clean.h"
#include "main/current_pockets.h"
#include "main/event_schedule.h"
#include "main/item_code.h"
#include "main/item_lists.h"
#include "main/item_object.h"
#include "main/main_random.h"
#include "main/message_receiver.h"
#include "main/obj_020d9ff8.h"
#include "main/player_id.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/scene_base.h"
#include "main/scene_command.h"
#include "main/talk_answers.h"
#include "main/talk_checks.h"
#include "main/talk_object.h"
#include "main/text_base.h"
#include "main/villager_part.h"
#include "main/villager_part_entry.h"

static_assert(offsetof(CamelTalk, owner) == 0xb0 && offsetof(CamelTalk, pocket) == 0xb4, "CamelTalk");
static_assert(offsetof(CamelTalk, rewards) == 0xb8 && sizeof(CamelTalk) == 0xbc, "CamelTalk");
static_assert(sizeof(CamelTalkLine) == 8, "CamelTalkLine");
static_assert(sizeof(MessageReceiver) == 0x20 && offsetof(MessageReceiver, message) == 0x1e, "the line shown");

/* "sp_npc_camel", the message file of her lines. */
extern const char data_ov078_02279bd8[];
/* The class's vtable. */
extern const u8 data_ov078_02279a9c[];

/* The item code object's constructor and destructor (RoomInterior_ConstructCode,
 * TrivialObject_DestructItemCode), handed to the C++ runtime as the game's functions. */
extern void func_02034ce0(void *code);
extern void func_020051b0(void *code);
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));

/* The talk scene's vtable slot that resets it. */
#define CAMEL_TALK_SLOT_RESET 2

/* The current player's daily bit of her first talk of the day. */
#define CAMEL_TALK_DAILY_TALKED 0x0b

/* The errand's steps (bits 0-4 of the entry's object, ItemObject_Low5). */
#define CAMEL_ERRAND_HANDED 0
#define CAMEL_ERRAND_DONE 1
#define CAMEL_ERRAND_OFFERED 2
#define CAMEL_ERRAND_REWARDED 3

/* The item the errand's line 6 is for, and the state the errand's item is given in. */
#define CAMEL_ERRAND_ITEM 0x155f
#define CAMEL_ERRAND_ITEM_STATE 2

/* The event marked taken part in once the reward is given. */
#define CAMEL_EVENT_REWARDED 0x3e

/* Her reward: one item each of the item lists of kinds 4 and 3, group 0x23, put in the talk's
 * parts 1 and 2 (kind 7, an item's name). */
#define CAMEL_REWARD_GROUP 0x23
#define CAMEL_REWARD_KIND_FIRST 4
#define CAMEL_REWARD_KIND_SECOND 3
#define CAMEL_NAME_KIND_ITEM 7

/* The trade: item 0x13ac taken, item 0x37e0 or (one time in two) 0x34a8 given. */
#define CAMEL_TRADE_TAKEN 0x13ac
#define CAMEL_TRADE_GIVEN 0x37e0
#define CAMEL_TRADE_GIVEN_2 0x34a8

/* The scene command's motion of the item in hand (scene_command.h). */
#define CAMEL_HAND_MOTION 5

/* No line to say. */
#define CAMEL_NO_LINE 0

static_assert(sizeof(ItemObject) == 12, "the errand's object");

static u8 camel_line_shown(const CamelTalk *talk)
{
    return ((const MessageReceiver *) (const void *) talk)->message;
}

static TalkObject *camel_talk_object(const CamelTalk *talk)
{
    return (TalkObject *) (void *) talk->scene.talk;
}

static SceneCommandScene *camel_command(CamelTalk *talk)
{
    return (SceneCommandScene *) (void *) talk;
}

/* Line `line` of "sp_npc_camel" shown. */
static void camel_say(const CamelTalk *talk, u8 line)
{
    TalkObject_SetMessage(camel_talk_object(talk), &line, data_ov078_02279bd8);
}

/* The current player's errand (the entry at 0x94 of the villager part). */
static VillagerPartEntry *camel_errand(void)
{
    u8 *part = PlayerRecord_VillagerPart(PlayerRecords_Current());
    return (VillagerPartEntry *) (void *) VillagerPart_Object94((VillagerPart *) (void *) part);
}

/* The errand's object (one call of VillagerPartEntry_Self each). */
static ItemObject *camel_object(VillagerPartEntry *errand)
{
    return (ItemObject *) (void *) VillagerPartEntry_Self(errand);
}

/* The name of the errand's villager, when it writes one, put in the talk's part 0. */
static void camel_put_villager_name(CamelTalk *talk, VillagerPartEntry *errand, PlayerIdText *name)
{
    if (VillagerPartEntry_WriteName(errand, name) != 0) {
        TalkObject_SetPart(camel_talk_object(talk), 0, (TextBase *) (void *) name);
    }
}

/* func_ov078_02278b00 (slot 0x18, the player's answer), by the line shown:
 * - 0x02, 0x04, answered 0: line 0x05, or 0x1d when the pockets have no free slot;
 * - 0x0d, 0x13: the first reward when answered 0, else the second, handed over (the item's
 *   motion of kind 13) and put in the pockets; line 0x0e;
 * - 0x14, answered 0: when item 0x13ac was found in the pockets its slot is emptied and the
 *   item's motion of kind 14 shown; line 0x16.
 * The line, when one was picked, is shown. */
void CamelTalk_OnAnswer(CamelTalk *talk)
{
    unsigned int answer = TalkAnswers_Picked((TalkAnswers *) (uintptr_t) (u32) SceneBase_TalkChoices(&talk->scene));
    u16 reward = ITEM_CODE_NONE;
    u8 line = CAMEL_NO_LINE;

    switch (camel_line_shown(talk)) {
        case CAMEL_LINE_OFFER:
        case CAMEL_LINE_NO_ERRAND:
            if (answer == 0) {
                line = CurrentPockets_FreeSlot() < 0 ? CAMEL_LINE_POCKETS_FULL : CAMEL_LINE_ERRAND;
            }
            break;
        case CAMEL_LINE_REWARD_CHOICE:
        case CAMEL_LINE_REWARD_CHOICE_2:
            reward = answer == 0 ? talk->rewards[0] : talk->rewards[1];
            SceneCommand_RequestMotion13(camel_command(talk), &reward, 0, CAMEL_HAND_MOTION, 0);
            CurrentPockets_Give(&reward, 0);
            line = CAMEL_LINE_REWARD_TAKEN;
            break;
        case CAMEL_LINE_TRADE_ASK:
            if (answer == 0) {
                if (talk->pocket >= 0) {
                    u16 taken = CAMEL_TRADE_TAKEN;
                    CurrentPockets_Empty(talk->pocket);
                    SceneCommand_RequestMotion14(camel_command(talk), &taken, 0, CAMEL_HAND_MOTION, 0);
                }
                line = CAMEL_LINE_TRADE;
            }
            break;
        default:
            break;
    }
    if (line != CAMEL_NO_LINE) {
        camel_say(talk, line);
    }
}
CLEAN_AS(func_ov078_02278b00, CamelTalk_OnAnswer)

/* The reward drawn from item list `kind`, group 0x23, kept in `slot` and its name put in the
 * talk's part `part`. */
static void camel_draw_reward(CamelTalk *talk, int kind, int slot, int part)
{
    ItemList list;
    u16 drawn;

    ItemList_Construct(&list, kind, CAMEL_REWARD_GROUP);
    ItemLists_Draw(&drawn, &list, 0, 0, 1, 1, 0);
    talk->rewards[slot] = drawn;
    ItemList_Destruct(&list);
    SceneBase_PutItemName(&talk->scene, (int) (u32) (uintptr_t) &talk->rewards[slot], part, CAMEL_NAME_KIND_ITEM);
}

/* Whether the errand's item is 0x155f (an item with variants compared without its variant). */
static int camel_is_errand_item(const u16 *item)
{
    if (ItemCode_HasVariant(item)) {
        u16 wanted = CAMEL_ERRAND_ITEM;
        int number = ItemCode_VariantItem(item);
        return number == ItemCode_VariantItem(&wanted);
    }
    return *item == CAMEL_ERRAND_ITEM;
}

/* The errand's item given into the pockets (in state 2) and handed over (its motion of kind
 * 13), its villager's name put in part 0; the next line: 0x08, or 0x0b after line 0x0a. */
static u8 camel_hand_errand(CamelTalk *talk, VillagerPartEntry *errand, PlayerIdText *name)
{
    CurrentPockets_Give(ItemObject_Item(camel_object(errand)), CAMEL_ERRAND_ITEM_STATE);
    SceneCommand_RequestMotion13(camel_command(talk), ItemObject_Item(camel_object(errand)), 2, CAMEL_HAND_MOTION, 0);
    camel_put_villager_name(talk, errand, name);
    return camel_line_shown(talk) != CAMEL_LINE_ERRAND_NEXT ? CAMEL_LINE_ERRAND_GIVEN : CAMEL_LINE_ERRAND_NEXT_GIVEN;
}

/* func_ov078_02278be0 (slot 0x14, a line ended), by the line shown:
 * - 0x05, 0x0a: with no free slot in the pockets, line 0x1d; else (for 0x05 the errand
 *   started first, VillagerPartEntry_Start) line 0x06 when the errand's item is 0x155f, else
 *   0x07; line 0x0a then goes on as 0x06 and 0x07 do, with line 0x0b;
 * - 0x06, 0x07: the errand's item given into the pockets (in state 2) and handed over (its
 *   motion of kind 13), its villager's name put in part 0; line 0x08;
 * - 0x0c: the two rewards drawn (lists of kinds 4 and 3) and named in parts 1 and 2; line 0x0d;
 * - 0x0e: the errand's step set to 3 and event 0x3e marked taken part in;
 * - 0x15: no trade any more in this visit;
 * - 0x16: item 0x37e0 (line 0x17), or one time in two 0x34a8 (line 0x18), named in part 0,
 *   handed over and put in the pockets; no trade any more in this visit.
 * The line, when one was picked, is shown. */
void CamelTalk_OnLineEnded(CamelTalk *talk)
{
    PlayerIdText name;
    u16 given = ITEM_CODE_NONE;
    u8 line = CAMEL_NO_LINE;

    PlayerIdText_Construct(&name);
    VillagerPartEntry *errand = camel_errand();
    u8 shown = camel_line_shown(talk);

    switch (shown) {
        case CAMEL_LINE_ERRAND:
        case CAMEL_LINE_ERRAND_NEXT:
            if (CurrentPockets_FreeSlot() < 0) {
                line = CAMEL_LINE_POCKETS_FULL;
                break;
            }
            if (camel_line_shown(talk) == CAMEL_LINE_ERRAND) {
                VillagerPartEntry_Start(errand);
            }
            line =
                camel_is_errand_item(ItemObject_Item(camel_object(errand))) ? CAMEL_LINE_ERRAND_155F : CAMEL_LINE_ERRAND_OTHER;
            /* line 0x0a hands the errand's item over at once */
            if (camel_line_shown(talk) == CAMEL_LINE_ERRAND_NEXT) {
                line = camel_hand_errand(talk, errand, &name);
            }
            break;
        case CAMEL_LINE_ERRAND_155F:
        case CAMEL_LINE_ERRAND_OTHER:
            line = camel_hand_errand(talk, errand, &name);
            break;
        case CAMEL_LINE_REWARD_DRAW:
            camel_draw_reward(talk, CAMEL_REWARD_KIND_FIRST, 0, 1);
            camel_draw_reward(talk, CAMEL_REWARD_KIND_SECOND, 1, 2);
            line = CAMEL_LINE_REWARD_CHOICE;
            break;
        case CAMEL_LINE_REWARD_TAKEN:
            ItemObject_SetLow5(camel_object(errand), CAMEL_ERRAND_REWARDED);
            EventSchedule_MarkTakenPart(CAMEL_EVENT_REWARDED);
            break;
        case CAMEL_LINE_TRADE_DECLINED:
            talk->pocket = CAMEL_TALK_POCKET_DONE;
            break;
        case CAMEL_LINE_TRADE:
            given = CAMEL_TRADE_GIVEN;
            line = CAMEL_LINE_TRADE_37E0;
            if (MainRandom_Below(2) == 0) {
                given = CAMEL_TRADE_GIVEN_2;
                line = CAMEL_LINE_TRADE_34A8;
            }
            talk->pocket = CAMEL_TALK_POCKET_DONE;
            SceneBase_PutItemName(&talk->scene, (int) (u32) (uintptr_t) &given, 0, CAMEL_NAME_KIND_ITEM);
            SceneCommand_RequestMotion13(camel_command(talk), &given, 0, CAMEL_HAND_MOTION, 0);
            CurrentPockets_Give(&given, 0);
            break;
        default:
            break;
    }
    if (line != CAMEL_NO_LINE) {
        camel_say(talk, line);
    }
    PlayerIdText_Destruct(&name);
}
CLEAN_AS(func_ov078_02278be0, CamelTalk_OnLineEnded)

/* func_ov078_02278e18 (slot 0x78, the line the talk starts with), of "sp_npc_camel". Item
 * 0x13ac is looked for in the pockets once a visit; the first that holds of:
 *   the pockets hold item 0x13ac                       line 0x14;
 *   the errand is set and at step 3                    line 0x00;
 *   the first talk of the day (daily bit 0x0b, set)    line 0x01;
 *   no errand is set                                   line 0x04;
 *   the errand at step 0: its villager named           line 0x09;
 *   no free slot in the pockets                        line 0x12;
 *   the errand advances (VillagerPartEntry_Advance):
 *   its next villager named                            line 0x0a;
 *   the errand at step 1: step 2 set                   line 0x0c;
 * else the line is left as it was. */
void CamelTalk_FirstLine(CamelTalk *talk, CamelTalkLine *out)
{
    VillagerPartEntry *errand = camel_errand();
    PlayerIdText name;

    PlayerIdText_Construct(&name);
    out->text = (u32) (uintptr_t) data_ov078_02279bd8;
    if (talk->pocket == CAMEL_TALK_POCKET_UNKNOWN) {
        u16 wanted = CAMEL_TRADE_TAKEN;
        talk->pocket = CurrentPockets_FindItem(&wanted);
    }
    if (talk->pocket >= 0) {
        out->message = CAMEL_LINE_TRADE_ASK;
    } else if (ItemObject_IsInUse(camel_object(errand)) != 0 &&
               ItemObject_Low5(camel_object(errand)) == CAMEL_ERRAND_REWARDED) {
        out->message = CAMEL_LINE_REWARD_GIVEN;
    } else if (TalkChecks_TestSetDailyBit(CAMEL_TALK_DAILY_TALKED, 1) == 0) {
        out->message = CAMEL_LINE_FIRST_TODAY;
    } else if (ItemObject_IsInUse(camel_object(errand)) == 0) {
        out->message = CAMEL_LINE_NO_ERRAND;
    } else if (ItemObject_IsInUse(camel_object(errand)) != 0 && ItemObject_Low5(camel_object(errand)) == CAMEL_ERRAND_HANDED) {
        camel_put_villager_name(talk, errand, &name);
        out->message = CAMEL_LINE_ERRAND_OPEN;
    } else if (CurrentPockets_FreeSlot() < 0) {
        out->message = CAMEL_LINE_NO_ROOM;
    } else if (VillagerPartEntry_Advance(errand) != 0) {
        camel_put_villager_name(talk, errand, &name);
        out->message = CAMEL_LINE_ERRAND_NEXT;
    } else if (ItemObject_Low5(camel_object(errand)) == CAMEL_ERRAND_DONE) {
        ItemObject_SetLow5(camel_object(errand), CAMEL_ERRAND_OFFERED);
        out->message = CAMEL_LINE_REWARD_DRAW;
    }
    PlayerIdText_Destruct(&name);
}
CLEAN_AS(func_ov078_02278e18, CamelTalk_FirstLine)

/* func_ov078_02278f74: the talk reset through its vtable slot 0x08 and given its owner, item
 * 0x13ac not looked for yet and no rewards. */
void CamelTalk_Begin(CamelTalk *talk, struct Camel *owner)
{
    const u32 *vtable = (const u32 *) (const void *) talk->scene.vtable;
    ((void (*)(CamelTalk *))(uintptr_t) vtable[CAMEL_TALK_SLOT_RESET])(talk);
    talk->owner = owner;
    talk->pocket = CAMEL_TALK_POCKET_UNKNOWN;
    for (int i = 0; i < CAMEL_TALK_REWARDS; i++) {
        talk->rewards[i] = ITEM_CODE_NONE;
    }
}
CLEAN_AS(func_ov078_02278f74, CamelTalk_Begin)

/* func_ov078_02278fb0 (slot 0x04): destructed (the two item codes, then the scene class's
 * body), then freed. */
CamelTalk *CamelTalk_DestructDelete(CamelTalk *talk)
{
    talk->scene.vtable = data_ov078_02279a9c;
    __cxa_vec_cleanup(talk->rewards, CAMEL_TALK_REWARDS, sizeof(u16), func_020051b0);
    Obj020d9ff8_DestructBody(talk);
    Heap_OperatorDeleteB(talk);
    return talk;
}
CLEAN_AS(func_ov078_02278fb0, CamelTalk_DestructDelete)

/* func_ov078_02278fe4 (slot 0x00): the destructor: the two item codes destroyed, then the scene
 * class's body. */
CamelTalk *CamelTalk_Destruct(CamelTalk *talk)
{
    talk->scene.vtable = data_ov078_02279a9c;
    __cxa_vec_cleanup(talk->rewards, CAMEL_TALK_REWARDS, sizeof(u16), func_020051b0);
    Obj020d9ff8_DestructBody(talk);
    return talk;
}
CLEAN_AS(func_ov078_02278fe4, CamelTalk_Destruct)

/* func_ov078_02279010: the constructor: a scene of class 0x020d9ff8 given this class's vtable,
 * and its two item codes constructed. */
CamelTalk *CamelTalk_Construct(CamelTalk *talk)
{
    Obj020d9ff8_Construct(talk);
    talk->scene.vtable = data_ov078_02279a9c;
    __cxa_vec_ctor(talk->rewards, CAMEL_TALK_REWARDS, sizeof(u16), func_02034ce0, func_020051b0);
    return talk;
}
CLEAN_AS(func_ov078_02279010, CamelTalk_Construct)
