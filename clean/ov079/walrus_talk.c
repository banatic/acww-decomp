/* The walrus's talk scene (walrus_talk.h). */
#include "walrus_talk.h"

#include <stdint.h>

#include "autoload_2/heap.h"
#include "clean.h"
#include "main/current_pockets.h"
#include "main/design.h"
#include "main/design_info.h"
#include "main/design_sets.h"
#include "main/event_schedule.h"
#include "main/group_params.h"
#include "main/item_code.h"
#include "main/item_traits.h"
#include "main/main_random.h"
#include "main/message_receiver.h"
#include "main/name_texts.h"
#include "main/obj_020d9ff8.h"
#include "main/player_actor_ops.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/scene_base.h"
#include "main/scene_command.h"
#include "main/talk_answers.h"
#include "main/talk_checks.h"
#include "main/talk_object.h"
#include "walrus.h"

static_assert(offsetof(WalrusTalk, owner) == 0xb0 && offsetof(WalrusTalk, after_command) == 0xb4, "WalrusTalk");
static_assert(offsetof(WalrusTalk, next_after) == 0xbc && offsetof(WalrusTalk, item) == 0xc4, "WalrusTalk");
static_assert(offsetof(WalrusTalk, slot) == 0xc8 && sizeof(WalrusTalk) == 0xcc, "WalrusTalk");
static_assert(sizeof(WalrusTalkLine) == 8, "WalrusTalkLine");
static_assert(sizeof(NameText) == 0x28, "NameText");

/* "sp_npc_walrus", the archive of his lines. */
extern const char data_ov079_0227a1b0[];
/* The class's vtable. */
extern const u8 data_ov079_0227a074[];
/* The null member pointer (the C++ runtime's). */
extern const MemberPointer __ptmf_null;

/* What runs after a command: a function-local static filled from its constants the first time
 * (bit 0 of the guard says it was). */
extern u32 data_ov079_0227a1c4;
extern MemberPointer data_ov079_0227a20c[WALRUS_TALK_AFTERS];
extern const MemberPointer data_ov079_02279fc0, data_ov079_02279fc8, data_ov079_02279fe0;

/* WalrusTalk_IsOfferable, handed to the pockets' screen as the game's function. */
extern int func_ov079_022794fc(u16 *item, int state);

/* The talk scene's vtable slot that resets it (WalrusTalk_Reset). */
#define WALRUS_TALK_SLOT_RESET 2

/* The player's daily bit that marks he took an item today (talk_checks.h). */
#define WALRUS_TALK_DAILY_TOOK 10

#define WALRUS_TALK_NO_ITEM 0xfff1
#define WALRUS_TALK_NO_SLOT (-1)
#define WALRUS_TALK_NO_LINE 0xff

/* The pockets' screen (its predicate's argument) and the designs' screen (scene_command.h). */
#define WALRUS_TALK_POCKETS_ARG 0xd
#define WALRUS_TALK_DESIGNS_MODE 10

/* The scene command's motions of an item: taken from the player, and in his hand. */
#define WALRUS_TALK_TAKE_MOTION 4
#define WALRUS_TALK_HAND_MOTION 5
#define WALRUS_TALK_SHOW_MOTION 5

/* The kind the name of an item is put in with (SceneBase_PutItemName), and the part and kind
 * of the design's title (TalkObject_SetValue). */
#define WALRUS_TALK_ITEM_NAME_KIND 7
#define WALRUS_TALK_TITLE_PART 1
#define WALRUS_TALK_TITLE_KIND 7

/* The lines of "sp_npc_walrus". */
#define WALRUS_TALK_LINE_FIRST 0x00     /* answered 0: the pockets' screen */
#define WALRUS_TALK_LINE_NOT_GIVEN 0x01 /* the player gave nothing */
#define WALRUS_TALK_LINE_TAKEN 0x02     /* he takes the item */
#define WALRUS_TALK_LINE_SPECIAL 0x03   /* he takes one of his special items: then line 0x0f */
#define WALRUS_TALK_LINE_OFFER 0x04     /* answered 0: line 0x0e */
#define WALRUS_TALK_LINE_GIVEN 0x05     /* the design given */
#define WALRUS_TALK_LINE_AGAIN 0x06     /* 0x06-0x08: a later talk the same day */
#define WALRUS_TALK_LINES_AGAIN 3
#define WALRUS_TALK_LINE_GIFT 0x09 /* an item given, then line 0x0a */
#define WALRUS_TALK_LINE_GIFT_END 0x0a
#define WALRUS_TALK_LINE_ASIDE 0x0b     /* a tool he does not take */
#define WALRUS_TALK_LINE_NONE 0x0d      /* no design given */
#define WALRUS_TALK_LINE_DESIGNS 0x0e   /* the designs' screen */
#define WALRUS_TALK_LINE_MOTION_19 0x0f /* motion 19 while it shows, then line 0x04 or 0x09 */

/* His special items (line 3). */
#define WALRUS_TALK_FISH_FIRST 0x12e8
#define WALRUS_TALK_FISH_LAST 0x131f
#define WALRUS_TALK_SPOILING_FIRST 0x1531
#define WALRUS_TALK_SPOILING_LAST 0x153a
#define WALRUS_TALK_FRUIT_FIRST 0x1518
#define WALRUS_TALK_FRUIT_LAST 0x151c
#define WALRUS_TALK_1542_FIRST 0x1542
#define WALRUS_TALK_1542_LAST 0x1546
#define WALRUS_TALK_1548 0x1548
#define WALRUS_TALK_153B_FIRST 0x153b
#define WALRUS_TALK_153B_LAST 0x1541

/* For one of 0x153b-0x1541 he gives item 0x13ac, or 0x3530 one time in two. */
#define WALRUS_TALK_GIFT 0x13ac
#define WALRUS_TALK_GIFT_OTHER 0x3530
#define WALRUS_TALK_GIFT_ODDS 2
/* The item shown in his hand when he gives a design. */
#define WALRUS_TALK_DESIGN_ITEM 0x3530

/* The event his talk takes part in. */
#define WALRUS_TALK_EVENT 0x41

/* The design items of a player's design slot n: clothes 0x12a8 + n, a hat 0x1429 + n and an
 * umbrella 0x13a0 + n (item_texture.h). */
#define WALRUS_TALK_CLOTHES_FIRST 0x12a8
#define WALRUS_TALK_HAT_FIRST 0x1429
#define WALRUS_TALK_UMBRELLA_FIRST 0x13a0
#define WALRUS_TALK_DESIGN_SLOTS 8

/* The design samples (DESIGN_KIND_SAMPLE) he gives for some fish, by the item. */
typedef struct WalrusTalkFishDesign {
    u16 item;
    u8 sample;
} WalrusTalkFishDesign;

static const WalrusTalkFishDesign walrus_talk_fish_designs[] = {
    {0x131f, 0x15}, {0x12ff, 0x16}, {0x12f6, 0x17}, {0x12f8, 0x18}, {0x12fc, 0x19}, {0x1309, 0x1a},
    {0x1312, 0x1b}, {0x131c, 0x1d}, {0x131d, 0x1d}, {0x131e, 0x1d}, {0x1302, 0x1e}, {0x1303, 0x1f},
};

/* The samples for the other items. */
#define WALRUS_TALK_SAMPLE_1548 0x0b
#define WALRUS_TALK_SAMPLE_1542 0x08
#define WALRUS_TALK_SAMPLE_SPOILING 0x0a
#define WALRUS_TALK_SAMPLE_FRUIT 0x09
#define WALRUS_TALK_SAMPLE_OTHER 0x00
/* By ItemTraits_FishGroupOrder: 0 one of 0-7, 1 one of 0x0c-0x14, 2 0x1c. */
#define WALRUS_TALK_SAMPLES_GROUP_0 8
#define WALRUS_TALK_SAMPLE_GROUP_1 0x0c
#define WALRUS_TALK_SAMPLES_GROUP_1 9
#define WALRUS_TALK_SAMPLE_GROUP_2 0x1c

static TalkObject *walrus_talk_object(const WalrusTalk *talk)
{
    return (TalkObject *) (void *) talk->scene.talk;
}

static SceneCommandScene *walrus_talk_command(WalrusTalk *talk)
{
    return (SceneCommandScene *) (void *) talk;
}

/* The number of the line shown (the receiver's message). */
static u8 walrus_talk_shown(const WalrusTalk *talk)
{
    return ((const MessageReceiver *) (const void *) talk)->message;
}

/* Line `line` of "sp_npc_walrus" shown by `object`. */
static void walrus_talk_say(TalkObject *object, u8 line)
{
    TalkObject_SetMessage(object, &line, data_ov079_0227a1b0);
}

static int walrus_talk_in(u16 item, u16 first, u16 last)
{
    return item >= first && item <= last;
}

/* Whether `item` is `other`: an item with variants is compared without its variant. */
static int walrus_talk_is(const u16 *item, u16 other)
{
    if (ItemCode_HasVariant(item)) {
        int number = ItemCode_VariantItem(item);
        return number == ItemCode_VariantItem(&other);
    }
    return *item == other;
}

/* The sample he gives for `item`. */
static int walrus_talk_sample(const u16 *item)
{
    for (unsigned int i = 0; i < sizeof walrus_talk_fish_designs / sizeof walrus_talk_fish_designs[0]; i++) {
        if (walrus_talk_is(item, walrus_talk_fish_designs[i].item)) {
            return walrus_talk_fish_designs[i].sample;
        }
    }
    if (*item == WALRUS_TALK_1548) {
        return WALRUS_TALK_SAMPLE_1548;
    }
    if (walrus_talk_in(*item, WALRUS_TALK_1542_FIRST, WALRUS_TALK_1542_LAST)) {
        return WALRUS_TALK_SAMPLE_1542;
    }
    if (walrus_talk_in(*item, WALRUS_TALK_SPOILING_FIRST, WALRUS_TALK_SPOILING_LAST)) {
        return WALRUS_TALK_SAMPLE_SPOILING;
    }
    if (ItemTraits_FishGroupOrder(item) == 0) {
        return (u8) MainRandom_Below(WALRUS_TALK_SAMPLES_GROUP_0);
    }
    if (ItemTraits_FishGroupOrder(item) == 1) {
        return (u8) (MainRandom_Below(WALRUS_TALK_SAMPLES_GROUP_1) + WALRUS_TALK_SAMPLE_GROUP_1);
    }
    if (ItemTraits_FishGroupOrder(item) == 2) {
        return WALRUS_TALK_SAMPLE_GROUP_2;
    }
    if (walrus_talk_in(*item, WALRUS_TALK_FRUIT_FIRST, WALRUS_TALK_FRUIT_LAST)) {
        return WALRUS_TALK_SAMPLE_FRUIT;
    }
    return WALRUS_TALK_SAMPLE_OTHER;
}

/* The design item of slot `slot` from `first` (the first when the slot is 8 or more). */
static u16 walrus_talk_design_item(unsigned int slot, u16 first)
{
    return slot < WALRUS_TALK_DESIGN_SLOTS ? (u16) (first + slot) : first;
}

/* ---- Its slots */

/* func_ov079_02278ac4 (slot 0x18): the player's answer (0 the first) to the line shown:
 * - 0x00: 0 opens the pockets' screen (any item of a slot of state 0, argument 0xd, staying on
 *   the line) and WalrusTalk_TakeOffering runs after it;
 * - 0x04: 0 goes to line 0x0e.
 * The answer is read whatever the line. */
void WalrusTalk_OnAnswer(WalrusTalk *talk)
{
    unsigned int answer = TalkAnswers_Picked((TalkAnswers *) (uintptr_t) (u32) SceneBase_TalkChoices(&talk->scene));
    int line = WALRUS_TALK_NO_LINE;

    switch (walrus_talk_shown(talk)) {
        case WALRUS_TALK_LINE_FIRST:
            if (answer == 0) {
                SceneCommand_SetPocketPredicate(walrus_talk_command(talk), func_ov079_022794fc, WALRUS_TALK_POCKETS_ARG, 1);
                SceneCommand_RequestScreen(walrus_talk_command(talk), SCENE_COMMAND_SCREEN_POCKETS);
                WalrusTalk_SetAfterCommand(talk, WALRUS_TALK_AFTER_OFFERING);
            }
            break;
        case WALRUS_TALK_LINE_OFFER:
            if (answer == 0) {
                line = WALRUS_TALK_LINE_DESIGNS;
            }
            break;
        default:
            break;
    }
    if (line != WALRUS_TALK_NO_LINE) {
        walrus_talk_say(walrus_talk_object(talk), (u8) line);
    }
}
CLEAN_AS(func_ov079_02278ac4, WalrusTalk_OnAnswer)

/* func_ov079_02278b2c (slot 0x14): what follows the line shown:
 * - 0x03: line 0x0f;
 * - 0x02: motion 16 of the scene's commands;
 * - 0x0f: line 0x04; but when the item he took is one of 0x153b-0x1541, it becomes 0x13ac (or
 *   0x3530 one time in two), its name goes in part 0 and line 0x09; event 0x41 marked as taken
 *   part in either way;
 * - 0x0e: the designs' screen (mode 10, not staying on the line) and WalrusTalk_GiveDesign
 *   after it;
 * - 0x0b: motion 17 of the scene's commands;
 * - 0x09: the item given to the player and, when it fit, shown in his hand; line 0x0a;
 * - 0x05, 0x0a, 0x0d: daily bit 10 set. */
void WalrusTalk_OnLineShown(WalrusTalk *talk)
{
    int line = WALRUS_TALK_NO_LINE;

    switch (walrus_talk_shown(talk)) {
        case WALRUS_TALK_LINE_SPECIAL:
            line = WALRUS_TALK_LINE_MOTION_19;
            break;
        case WALRUS_TALK_LINE_TAKEN:
            SceneCommand_RequestMotion16(walrus_talk_command(talk));
            break;
        case WALRUS_TALK_LINE_MOTION_19:
            line = WALRUS_TALK_LINE_OFFER;
            if (walrus_talk_in(talk->item, WALRUS_TALK_153B_FIRST, WALRUS_TALK_153B_LAST)) {
                talk->item = WALRUS_TALK_GIFT;
                if (MainRandom_Below(WALRUS_TALK_GIFT_ODDS) != 0) {
                    talk->item = WALRUS_TALK_GIFT_OTHER;
                }
                line = WALRUS_TALK_LINE_GIFT;
                SceneBase_PutItemName(&talk->scene, (int) (u32) (uintptr_t) &talk->item, 0, WALRUS_TALK_ITEM_NAME_KIND);
            }
            EventSchedule_MarkTakenPart(WALRUS_TALK_EVENT);
            break;
        case WALRUS_TALK_LINE_DESIGNS:
            SceneCommand_SetScreenMode(walrus_talk_command(talk), WALRUS_TALK_DESIGNS_MODE, 0);
            SceneCommand_RequestScreen(walrus_talk_command(talk), SCENE_COMMAND_SCREEN_MODE);
            WalrusTalk_SetAfterCommand(talk, WALRUS_TALK_AFTER_DESIGN);
            break;
        case WALRUS_TALK_LINE_ASIDE:
            SceneCommand_RequestMotion17(walrus_talk_command(talk));
            break;
        case WALRUS_TALK_LINE_GIFT:
            if (CurrentPockets_Give(&talk->item, 0) != 0) {
                SceneCommand_RequestMotion13(walrus_talk_command(talk), &talk->item, 0, WALRUS_TALK_HAND_MOTION, 0);
            }
            line = WALRUS_TALK_LINE_GIFT_END;
            break;
        case WALRUS_TALK_LINE_GIVEN:
        case WALRUS_TALK_LINE_GIFT_END:
        case WALRUS_TALK_LINE_NONE:
            TalkChecks_TestSetDailyBit(WALRUS_TALK_DAILY_TOOK, 1);
            break;
        default:
            break;
    }
    if (line != WALRUS_TALK_NO_LINE) {
        walrus_talk_say(walrus_talk_object(talk), (u8) line);
    }
}
CLEAN_AS(func_ov079_02278b2c, WalrusTalk_OnLineShown)

/* func_ov079_02278c38 (slot 0x10): while line 0x0f is shown, motion 19 of the scene's
 * commands. */
void WalrusTalk_Slot10(WalrusTalk *talk)
{
    if (walrus_talk_shown(talk) == WALRUS_TALK_LINE_MOTION_19) {
        SceneCommand_RequestMotion19(walrus_talk_command(talk));
    }
}
CLEAN_AS(func_ov079_02278c38, WalrusTalk_Slot10)

/* func_ov079_02278c4c (slot 0x78): "sp_npc_walrus", line 0; once he took an item today (daily bit 10,
 * only tested), one of the lines 6-8. */
void WalrusTalk_Line(WalrusTalk *talk, WalrusTalkLine *line)
{
    (void) talk;
    line->name = data_ov079_0227a1b0;
    if (TalkChecks_TestSetDailyBit(WALRUS_TALK_DAILY_TOOK, 0) == 0) {
        line->message = WALRUS_TALK_LINE_FIRST;
    } else {
        line->message = (u8) (MainRandom_Below(WALRUS_TALK_LINES_AGAIN) + WALRUS_TALK_LINE_AGAIN);
    }
}
CLEAN_AS(func_ov079_02278c4c, WalrusTalk_Line)

/* func_ov079_02278c7c: the talk reset (its vtable slot 2), `owner` its owner, no item and no
 * slot. */
void WalrusTalk_Begin(WalrusTalk *talk, struct Walrus *owner)
{
    const u32 *vtable = (const u32 *) (const void *) talk->scene.vtable;
    ((void (*)(WalrusTalk *))(uintptr_t) vtable[WALRUS_TALK_SLOT_RESET])(talk);
    talk->owner = owner;
    talk->item = WALRUS_TALK_NO_ITEM;
    talk->slot = WALRUS_TALK_NO_SLOT;
}
CLEAN_AS(func_ov079_02278c7c, WalrusTalk_Begin)

/* func_ov079_02278cac (slot 0x08): the scene base reset, no slot, no item and nothing to run
 * after a command. */
void WalrusTalk_Reset(WalrusTalk *talk)
{
    SceneBase_Reset(&talk->scene);
    talk->slot = WALRUS_TALK_NO_SLOT;
    talk->item = WALRUS_TALK_NO_ITEM;
    MemberPointer none = __ptmf_null;
    talk->after_command = none;
    talk->next_after = none;
}
CLEAN_AS(func_ov079_02278cac, WalrusTalk_Reset)

/* func_ov079_0227958c (slot 0x84, a command of the scene ended): what was left to run, once;
 * then what was left to run after it takes its place. */
void WalrusTalk_RunAfterCommand(WalrusTalk *talk)
{
    if (talk->after_command.function == 0) {
        return;
    }
    MemberPointer_CallVoid(&talk->after_command, talk);
    MemberPointer none = __ptmf_null;
    talk->after_command = none;
    if (talk->next_after.function != 0) {
        talk->after_command = talk->next_after;
        talk->next_after = none;
    }
}
CLEAN_AS(func_ov079_0227958c, WalrusTalk_RunAfterCommand)

/* func_ov079_022794fc (the pockets' predicate): any item of a slot of state 0. */
int WalrusTalk_IsOfferable(u16 *item, int state)
{
    (void) item;
    return state == 0;
}
CLEAN_AS(func_ov079_022794fc, WalrusTalk_IsOfferable)

/* ---- Its life */

/* func_ov079_02278cfc (slot 0x04): destructed, then freed. */
WalrusTalk *WalrusTalk_DestructDelete(WalrusTalk *talk)
{
    talk->scene.vtable = data_ov079_0227a074;
    Obj020d9ff8_DestructBody(talk);
    Heap_OperatorDeleteB(talk);
    return talk;
}
CLEAN_AS(func_ov079_02278cfc, WalrusTalk_DestructDelete)

/* func_ov079_02278d1c (slot 0x00): the destructor: its class's vtable, then the base class's
 * body. */
WalrusTalk *WalrusTalk_Destruct(WalrusTalk *talk)
{
    talk->scene.vtable = data_ov079_0227a074;
    Obj020d9ff8_DestructBody(talk);
    return talk;
}
CLEAN_AS(func_ov079_02278d1c, WalrusTalk_Destruct)

/* func_ov079_02278d34: the base class constructed, then its class's vtable and no item. */
WalrusTalk *WalrusTalk_Construct(WalrusTalk *talk)
{
    Obj020d9ff8_Construct(talk);
    talk->scene.vtable = data_ov079_0227a074;
    talk->item = WALRUS_TALK_NO_ITEM;
    return talk;
}
CLEAN_AS(func_ov079_02278d34, WalrusTalk_Construct)

/* ---- What runs after a command */

/* func_ov079_02278d58 (after the designs' screen): line 0x0d; when the player picked a slot
 * (GroupParams_C4CIs1, the slot's place GroupParams_Arg in the order of the player's designs),
 * the sample of the item he took (walrus_talk_sample) copied into that design slot (announced),
 * item 0x3530 shown in his hand and line 0x05. Then, for the clothes, the hat and the umbrella
 * the player has on (read in that order): one that is the design item of that slot is put on
 * again (PlayerActorOps). The design's title goes in part 1 of the talk.
 * QUIRK: the line is shown in the talk the scene had at the start (the title goes in the one it
 * has then); each item the player has on is read twice. */
void WalrusTalk_GiveDesign(WalrusTalk *talk)
{
    TalkObject *object = walrus_talk_object(talk);
    u8 message = WALRUS_TALK_LINE_NONE;

    if (GroupParams_C4CIs1() != 0) {
        u8 *player = PlayerRecords_Current();
        int place = GroupParams_Arg();
        unsigned int slot =
            DesignOrder_Get((unsigned char *) (uintptr_t) (u32) PlayerDesigns_Order(PlayerRecord_Designs(player)), place);

        Design_Copy(DESIGN_KIND_SAMPLE, walrus_talk_sample(&talk->item), DESIGN_KIND_LOCAL, (int) slot, 1);
        message = WALRUS_TALK_LINE_GIVEN;
        u16 shown = WALRUS_TALK_DESIGN_ITEM;
        SceneCommand_RequestMotion13(walrus_talk_command(talk), &shown, 0, WALRUS_TALK_SHOW_MOTION, 0);

        u16 clothes = walrus_talk_design_item(slot, WALRUS_TALK_CLOTHES_FIRST);
        u16 hat = walrus_talk_design_item(slot, WALRUS_TALK_HAT_FIRST);
        u16 umbrella = walrus_talk_design_item(slot, WALRUS_TALK_UMBRELLA_FIRST);
        u16 worn_clothes = *PlayerRecord_Clothes(player);
        u16 worn_hat = *PlayerRecord_HeadItem(player);
        u16 held = *PlayerRecord_HeldItem(player);

        if (clothes == worn_clothes &&
            walrus_talk_in(*PlayerRecord_Clothes(player), WALRUS_TALK_CLOTHES_FIRST, WALRUS_TALK_CLOTHES_FIRST + 7)) {
            u16 item = clothes;
            PlayerActorOps_RequestState7Kind0Next10(&item);
        }
        if (hat == worn_hat &&
            walrus_talk_in(*PlayerRecord_HeadItem(player), WALRUS_TALK_HAT_FIRST, WALRUS_TALK_HAT_FIRST + 7)) {
            u16 item = hat;
            PlayerActorOps_RequestState7Kind2Next10(&item);
        }
        if (umbrella == held &&
            walrus_talk_in(*PlayerRecord_HeldItem(player), WALRUS_TALK_UMBRELLA_FIRST, WALRUS_TALK_UMBRELLA_FIRST + 7)) {
            u16 item = umbrella;
            PlayerActorOps_RequestState3F(&item);
        }

        int design = PlayerDesigns_At(PlayerRecord_Designs(player), (int) slot);
        NameText title;
        NameText_Construct(&title);
        DesignInfo_TitleToText((DesignInfo *) (uintptr_t) Design_Info((unsigned int) design), &title);
        TalkObject_SetValue(walrus_talk_object(talk), WALRUS_TALK_TITLE_PART, (TextBase *) (void *) &title,
                            WALRUS_TALK_TITLE_KIND);
        NameText_Destruct(&title);
    }
    TalkObject_SetMessage(object, &message, data_ov079_0227a1b0);
}
CLEAN_AS(func_ov079_02278d58, WalrusTalk_GiveDesign)

/* func_ov079_0227936c (after a command): the scene's next line. */
void WalrusTalk_NextLine(WalrusTalk *talk)
{
    SceneCommand_RequestNextLine(walrus_talk_command(talk));
}
CLEAN_AS(func_ov079_0227936c, WalrusTalk_NextLine)

/* func_ov079_02279374 (after the pockets' screen): no slot; when the player gave an item
 * (GroupParams_C4CIs1, its slot GroupParams_Arg), the item noted and line 0x02, or 0x03 for
 * one of his special items; for one of the six tools 0x136a, 0x1373, 0x1375, 0x1377, 0x1379,
 * 0x137b line 0x0b and the item is not taken (no slot). An item taken is emptied from its slot
 * (no slot after); the item goes from the player to him (motion 14) and the next line follows
 * after that command. Without an item, the next line and line 0x01. */
void WalrusTalk_TakeOffering(WalrusTalk *talk)
{
    TalkObject *object = walrus_talk_object(talk);
    u8 message = WALRUS_TALK_LINE_NOT_GIVEN;

    talk->slot = WALRUS_TALK_NO_SLOT;
    if (GroupParams_C4CIs1() != 0) {
        talk->slot = GroupParams_Arg();
        talk->item = CurrentPockets_Item((u32) talk->slot);
        message = WALRUS_TALK_LINE_TAKEN;

        u16 item = talk->item;
        if (walrus_talk_in(item, WALRUS_TALK_FISH_FIRST, WALRUS_TALK_FISH_LAST) ||
            walrus_talk_in(item, WALRUS_TALK_SPOILING_FIRST, WALRUS_TALK_SPOILING_LAST) ||
            walrus_talk_in(item, WALRUS_TALK_FRUIT_FIRST, WALRUS_TALK_FRUIT_LAST) ||
            walrus_talk_in(item, WALRUS_TALK_1542_FIRST, WALRUS_TALK_1542_LAST) || item == WALRUS_TALK_1548 ||
            walrus_talk_in(item, WALRUS_TALK_153B_FIRST, WALRUS_TALK_153B_LAST)) {
            message = WALRUS_TALK_LINE_SPECIAL;
        }
        item = talk->item;
        if (item == 0x136a || item == 0x1373 || item == 0x1375 || item == 0x1377 || item == 0x1379 || item == 0x137b) {
            message = WALRUS_TALK_LINE_ASIDE;
            talk->slot = WALRUS_TALK_NO_SLOT;
        }
        if (talk->slot >= 0) {
            CurrentPockets_Empty(talk->slot);
            talk->slot = WALRUS_TALK_NO_SLOT;
        }
        SceneCommand_RequestMotion14(walrus_talk_command(talk), &talk->item, 0, WALRUS_TALK_TAKE_MOTION, 0);
        WalrusTalk_SetNextAfterCommand(talk, WALRUS_TALK_AFTER_NEXT_LINE);
    } else {
        SceneCommand_RequestNextLine(walrus_talk_command(talk));
    }
    TalkObject_SetMessage(object, &message, data_ov079_0227a1b0);
}
CLEAN_AS(func_ov079_02279374, WalrusTalk_TakeOffering)

/* func_ov079_02279508: `after` (WALRUS_TALK_AFTER_*) to run once what is left to run ran. */
void WalrusTalk_SetNextAfterCommand(WalrusTalk *talk, int after)
{
    WalrusTalk_FromTable(talk, &talk->next_after, after);
}
CLEAN_AS(func_ov079_02279508, WalrusTalk_SetNextAfterCommand)

/* func_ov079_02279518: `after` (WALRUS_TALK_AFTER_*) to run once a command of the scene
 * ends. */
void WalrusTalk_SetAfterCommand(WalrusTalk *talk, int after)
{
    WalrusTalk_FromTable(talk, &talk->after_command, after);
}
CLEAN_AS(func_ov079_02279518, WalrusTalk_SetAfterCommand)

/* func_ov079_02279528: the member function `after` of the table (filled the first time) given
 * in `out`.
 * REQUIRES: `after` is below 3 (the game's are). */
void WalrusTalk_FromTable(WalrusTalk *unused, MemberPointer *out, int after)
{
    static const MemberPointer *const constants[WALRUS_TALK_AFTERS] = {
        &data_ov079_02279fc0, /* WalrusTalk_TakeOffering */
        &data_ov079_02279fc8, /* WalrusTalk_NextLine */
        &data_ov079_02279fe0, /* WalrusTalk_GiveDesign */
    };
    (void) unused;
    MemberTable_InitOnce(&data_ov079_0227a1c4, data_ov079_0227a20c, constants, WALRUS_TALK_AFTERS);
    *out = data_ov079_0227a20c[after];
}
CLEAN_AS(func_ov079_02279528, WalrusTalk_FromTable)
