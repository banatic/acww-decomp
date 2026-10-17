/* Mabel's talk scene (mabel_talk.h): its class, the line it starts with, the deals, the
 * sequences after the screens, the player's answers and the ends of lines. */
#include "mabel_talk.h"

#include <stdint.h>
#include <string.h>

#include "autoload_2/heap.h"
#include "clean.h"
#include "main/actor_table.h"
#include "main/camera_control.h"
#include "main/current_pockets.h"
#include "main/design.h"
#include "main/design_info.h"
#include "main/design_sets.h"
#include "main/game_variables.h"
#include "main/group_params.h"
#include "main/item_code.h"
#include "main/item_object.h"
#include "main/item_traits.h"
#include "main/main_random.h"
#include "main/message_receiver.h"
#include "main/name_texts.h"
#include "main/obj_020d9ff8.h"
#include "main/player_actor_ops.h"
#include "main/player_id.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/pockets.h"
#include "main/scene_bells.h"
#include "main/scene_command.h"
#include "main/session.h"
#include "main/shops.h"
#include "main/start_kind.h"
#include "main/talk_answers.h"
#include "main/talk_checks.h"
#include "main/talk_object.h"
#include "main/text_base.h"
#include "main/town_name.h"
#include "main/villager_events.h"
#include "main/villager_part.h"
#include "main/villager_part_entry.h"

static_assert(sizeof(MabelTalkStep) == 12, "a sequence's function");
static_assert(sizeof(MabelTalkLine) == 8, "a line");
static_assert(sizeof(MabelTalkChoices) == 8, "a list of answers");
static_assert(sizeof(MessageReceiver) == 0x20 && offsetof(MessageReceiver, message) == 0x1e, "the line shown");
static_assert(sizeof(NameText) == 0x28, "the design's title");
static_assert(sizeof(DesignCreator) == 0x1e && sizeof(TownName) == 0x0e, "who made a design");

/* The vtable of its class. */
extern const u8 data_ov049_022634b4[];
/* Its message files: "sp_npc_ysister", "sp_npc_drama4" and "sp_etc_sequence4". */
extern const char *const data_ov049_02263298[3];
#define MABEL_TALK_FILE_OWN 0
#define MABEL_TALK_FILE_DRAMA 1
#define MABEL_TALK_FILE_SEQUENCE 2
/* The line after an answer to a dated event's line, by the answer (the answer 2 is the
 * event's); the line the talk starts with by talk mode; the line of each dated event of kind
 * 2 and its part, seven parts a row; the kinds a design is given (MabelTalk_SetDesignKind). */
extern const u8 data_ov049_02262dc0[];
extern const u8 data_ov049_02262dc8[];
extern const u8 data_ov049_02262dd0[];
#define MABEL_TALK_DRAMA_PARTS 7
extern const u32 data_ov049_02262dec[];
/* The answers offered for an item on display: buy it, try it on (not for umbrellas), or not. */
extern const MabelTalkChoices data_ov049_02263324; /* clothes */
extern const MabelTalkChoices data_ov049_0226332c; /* hats */
extern const MabelTalkChoices data_ov049_02263334; /* accessories */
extern const MabelTalkChoices data_ov049_0226333c; /* umbrellas */
/* The sequences' functions (filled at start-up by __sinit_ov049_02262e14; their flags are the
 * overlay's data). */
extern MabelTalkStep data_ov049_022633b0[MABEL_TALK_SEQUENCES];
/* The state block (its shop designs at 0x10ad0) and the session of the multiplayer game. */
extern u8 data_021dc7a8[];
#define MABEL_TALK_SHOP_DESIGNS 0x10ad0
extern NetSession *data_020ccf94;

/* The test of the items the pockets offer for the errand (the game's function). */
extern unsigned short func_ov049_02261224(unsigned short *r0, int r1);

/* Overlay 4: a question asked before the room object on a tile is changed for a try-on
 * (func_ov004_0222c2bc), and the changes while the player tries it on and after. */
extern int func_ov004_0222c2bc(void);
extern int func_ov004_0223b340(char *self, int a1);
extern int func_ov004_0223b39c(char *self, int a1);

/* The handlers by line; each table is a function-local static the compiler fills from the
 * constants on the first call (bit 0 of its guard says it was). */
typedef struct MabelTalkHandler {
    s32 line;
    MemberPointer handler;
} MabelTalkHandler;
static_assert(sizeof(MabelTalkHandler) == 0xc, "a line's handler");

/* The answers to her own lines: void (talk, int answer). */
#define MABEL_TALK_ANSWERS 11
extern MabelTalkHandler data_ov049_02263428[MABEL_TALK_ANSWERS];
extern u32 data_ov049_0226360c;
extern const MemberPointer data_ov049_022631d0, data_ov049_02263270, data_ov049_02263090, data_ov049_02263098,
    data_ov049_022630a8, data_ov049_022630b8, data_ov049_02263180, data_ov049_02263120, data_ov049_02263288,
    data_ov049_02263278, data_ov049_022630a0;

/* The ends of her own lines: void (talk). */
#define MABEL_TALK_LINE_ENDS 9
extern MabelTalkHandler data_ov049_02263344[MABEL_TALK_LINE_ENDS];
extern u32 data_ov049_02263604;
extern const MemberPointer data_ov049_02263178, data_ov049_022631a0, data_ov049_022631b0, data_ov049_022631c0,
    data_ov049_02263220, data_ov049_02263258, data_ov049_02263108, data_ov049_02263100, data_ov049_022630f8;

/* The answers and the ends of lines by file: her own, or another. */
extern MemberPointer data_ov049_02263628[2];
extern u32 data_ov049_02263608;
extern const MemberPointer data_ov049_02263168, data_ov049_02263130;
extern MemberPointer data_ov049_02263610[2];
extern u32 data_ov049_02263600;
extern const MemberPointer data_ov049_02263158, data_ov049_02263128;

#define MABEL_TALK_NO_ITEM 0xfff1

/* The vtable slot of the scene that resets it. */
#define MABEL_TALK_SLOT_RESET 0x08

/* The game variable (bank 0) that, when set, makes her act as when linked. */
#define MABEL_TALK_VARIABLE 0x4a
/* The dated events of kind 2, and the special character (Actors_GetDByIndex) who joins her
 * talks as the second speaker when unlinked. */
#define MABEL_TALK_EVENT_KIND 2
#define MABEL_TALK_SECOND_SPEAKER 5

/* The player's field actor and the state its actor is in once a try-on is over. */
#define MABEL_TALK_PLAYER 4
#define MABEL_TALK_PLAYER_STATE_TRIED 16

/* The fee of line 0x0b, and the shop kind its stock is taken from (Shops_TakeFromListA). */
#define MABEL_TALK_FEE 0x15e
#define MABEL_TALK_SHOP_KIND 10

/* The screens (SceneCommand_RequestScreen): 0 the pockets, 2 in a mode
 * (SceneCommand_SetScreenMode): a design of the player's picked to be given a kind (4), the
 * screen before the fee (0xb), the player's clothes to sell (0x1e), a design of the player's
 * shown in the shop (5), one of the shop's bought (7) or swapped (8). */
#define MABEL_TALK_SCREEN_POCKETS 0
#define MABEL_TALK_SCREEN 2
#define MABEL_TALK_MODE_DESIGN_PICK 4
#define MABEL_TALK_MODE_SCREEN_B 0xb
#define MABEL_TALK_MODE_SELL 0x1e
#define MABEL_TALK_MODE_SHOW_DESIGN 5
#define MABEL_TALK_MODE_BUY_DESIGN 7
#define MABEL_TALK_MODE_SWAP_DESIGN 8
/* The pockets' test argument of the errand. */
#define MABEL_TALK_POCKET_ARG 0xd

/* The answers' attribute byte (TalkAnswers_Set). */
#define MABEL_TALK_ANSWER_ATTRIBUTE 6

/* What a value put in the talk is shown as (SceneBase_PutValue, SceneBase_PutItemName,
 * TalkObject_SetValue). */
#define MABEL_TALK_VALUE_BELLS 10
#define MABEL_TALK_VALUE_ITEM 7
#define MABEL_TALK_VALUE_TEXT 7

/* The item classes she deals in (by code). */
#define MABEL_CLOTHES_FIRST 0x11a8
#define MABEL_CLOTHES_LAST 0x12a7
#define MABEL_HAT_A_FIRST 0x13a8 /* hats that take an accessory off */
#define MABEL_HAT_A_LAST 0x13c7
#define MABEL_HAT_B_FIRST 0x13c8
#define MABEL_HAT_B_LAST 0x1407
#define MABEL_ACCESSORY_FIRST 0x1431
#define MABEL_ACCESSORY_LAST 0x1470
#define MABEL_UMBRELLA_FIRST 0x1380
#define MABEL_UMBRELLA_LAST 0x139f
/* The clothes and the hats of the player's eight designs. */
#define MABEL_DESIGN_CLOTHES 0x12a8
#define MABEL_DESIGN_CLOTHES_LAST 0x12af
#define MABEL_DESIGN_HAT 0x1429
#define MABEL_DESIGN_HAT_LAST 0x1430
/* The shop's designs on display (four codes each). */
#define MABEL_TALK_DESIGN_FIRST 0x3e04
#define MABEL_TALK_DESIGN_LAST 0x3e23
/* The items of a villager's errand. */
#define MABEL_ERRAND_FIRST 0x155f
#define MABEL_ERRAND_LAST 0x1560
#define MABEL_ERRAND_STATE 2

static TalkObject *mtalk_object(MabelTalk *talk)
{
    return (TalkObject *) (void *) talk->base.talk;
}

static SceneCommandScene *mtalk_scene(MabelTalk *talk)
{
    return (SceneCommandScene *) (void *) talk;
}

static int mtalk_owner(MabelTalk *talk)
{
    return (int) (uintptr_t) talk->owner;
}

/* The line shown. */
static u8 mtalk_shown(const MabelTalk *talk)
{
    return ((const MessageReceiver *) (const void *) talk)->message;
}

/* The answer picked in the talk's choices. */
static int mtalk_answer(MabelTalk *talk)
{
    return (int) TalkAnswers_Picked(TalkObject_Answers(mtalk_object(talk)));
}

/* Line `line` of "sp_npc_ysister" shown. */
static void mtalk_say(MabelTalk *talk, u8 line)
{
    TalkObject_SetMessage(mtalk_object(talk), &line, data_ov049_02263298[MABEL_TALK_FILE_OWN]);
}

/* Whether the session is linked or the game variable 0x4a is set. */
static int mtalk_linked_or_variable(NetSession *session)
{
    return Session_IsLinked(session) || *GameVariables_Slot(0, MABEL_TALK_VARIABLE) != 0;
}

/* Unlinked, the special character 5 (when there is one) joins as the second speaker. */
static void mtalk_add_second_speaker(MabelTalk *talk, NetSession *session)
{
    if (!mtalk_linked_or_variable(session)) {
        u8 *speaker = (u8 *) Actors_GetDByIndex(MABEL_TALK_SECOND_SPEAKER);
        if (speaker != NULL) {
            SceneBase_SetSecondSpeaker(&talk->base, speaker);
        }
    }
}

static int mtalk_in(u16 item, u16 first, u16 last)
{
    return item >= first && item <= last;
}

static int mtalk_is_clothes(u16 item)
{
    return mtalk_in(item, MABEL_CLOTHES_FIRST, MABEL_CLOTHES_LAST);
}

static int mtalk_is_hat_a(u16 item)
{
    return mtalk_in(item, MABEL_HAT_A_FIRST, MABEL_HAT_A_LAST);
}

static int mtalk_is_hat(u16 item)
{
    return mtalk_in(item, MABEL_HAT_B_FIRST, MABEL_HAT_B_LAST) || mtalk_is_hat_a(item);
}

static int mtalk_is_accessory(u16 item)
{
    return mtalk_in(item, MABEL_ACCESSORY_FIRST, MABEL_ACCESSORY_LAST);
}

/* The player put in `item`: as clothes, a hat or an accessory. */
static void mtalk_wear_clothes(u16 item)
{
    PlayerActorOps_RequestState7Kind0Next10(&item);
}

static void mtalk_wear_hat(u16 item)
{
    PlayerActorOps_RequestState7Kind2Next10(&item);
}

static void mtalk_wear_accessory(u16 item)
{
    PlayerActorOps_RequestState7Kind1Next10(&item);
}

/* The item on display bought when the player has a free pocket slot and the bells: line 0x2c
 * (no room), 0x2b (no bells) or 0x29 (bought, MabelTalk_Buy). */
static void mtalk_try_buy(MabelTalk *talk)
{
    if (CurrentPockets_FreeSlot() == -1) {
        mtalk_say(talk, MABEL_LINE_NO_ROOM);
    } else if (SceneBells_CanPay(mtalk_owner(talk), talk->price) == 0) {
        mtalk_say(talk, MABEL_LINE_NO_BELLS);
    } else {
        mtalk_say(talk, MABEL_LINE_BOUGHT);
        MabelTalk_Buy(talk);
    }
}

/* The index (in the player's set) of the design at the place the screen gave
 * (GroupParams_Arg) in the current player's order. */
static unsigned int mtalk_picked_design(u8 *record)
{
    u8 place = GroupParams_Arg();
    PlayerDesigns *designs = PlayerRecord_Designs(record);
    return DesignOrder_Get((unsigned char *) (uintptr_t) (u32) PlayerDesigns_Order(designs), place);
}

/* After the player's design `index` changed: a player wearing its clothes or its hat (the
 * items 0x12a8 and 0x1429 plus the index, the first of them for an index past 7) is dressed
 * in it again. */
static void mtalk_redress(u8 *record, unsigned int index)
{
    u16 clothes = (u16) (index < DESIGNS_PER_SET ? MABEL_DESIGN_CLOTHES + index : MABEL_DESIGN_CLOTHES);
    u16 hat = (u16) (index < DESIGNS_PER_SET ? MABEL_DESIGN_HAT + index : MABEL_DESIGN_HAT);
    int worn = *PlayerRecord_Clothes(record);
    int worn_hat = *PlayerRecord_HeadItem(record);
    if (clothes == worn && mtalk_in(*PlayerRecord_Clothes(record), MABEL_DESIGN_CLOTHES, MABEL_DESIGN_CLOTHES_LAST)) {
        mtalk_wear_clothes(clothes);
    }
    if (hat == worn_hat && mtalk_in(*PlayerRecord_HeadItem(record), MABEL_DESIGN_HAT, MABEL_DESIGN_HAT_LAST)) {
        mtalk_wear_hat(hat);
    }
}

/* Its screen asked for: screen 2 in `mode`, then `sequence` when its command ends. */
static void mtalk_open(MabelTalk *talk, char mode, unsigned long sequence)
{
    SceneCommand_SetScreenMode(mtalk_scene(talk), mode, 0);
    SceneCommand_RequestScreen(mtalk_scene(talk), MABEL_TALK_SCREEN);
    MabelTalk_SetSequence(talk, sequence);
}

/* Calls `handler` with the talk (adjusted) and `arg`. */
static void mtalk_call(const MemberPointer *handler, MabelTalk *talk, int arg)
{
    void *self = MemberPointer_Object(handler, talk);
    ((void (*)(void *, int))(uintptr_t) MemberPointer_Code(handler, self))(self, arg);
}

/* ---- The deals */

/* func_ov049_02260780: the player's design at the place the screen gave (GroupParams_Arg, in
 * the current player's order) gets `kind` (DesignInfo_SetKind). */
void MabelTalk_SetDesignKind(int unused, int kind)
{
    (void) unused;
    u8 *record = PlayerRecords_Current();
    u8 place = GroupParams_Arg();
    unsigned int design = (unsigned int) PlayerDesigns_InOrder(PlayerRecord_Designs(record), place);
    DesignInfo_SetKind((u8 *) (uintptr_t) Design_Info(design), kind);
}
CLEAN_AS(func_ov049_02260780, MabelTalk_SetDesignKind)

/* func_ov049_02260ac4: the item on display bought: noted, its price taken, the item put in the
 * pockets, taken from the shop's stock at its tile (kind 10), and the villagers told
 * (VillagerEvent_Report3). */
void MabelTalk_Buy(MabelTalk *talk)
{
    talk->owner->bought = 1;
    SceneBells_Take(mtalk_owner(talk), talk->price);
    CurrentPockets_Give(&talk->owner->item, 0);
    Shops_TakeFromListA(talk->owner->tile_x, talk->owner->tile_z, MABEL_TALK_SHOP_KIND);
    VillagerEvent_Report3();
}
CLEAN_AS(func_ov049_02260ac4, MabelTalk_Buy)

/* func_ov049_02260b20: the answers of `choices` offered (messages of "sp_npc_ysister" with
 * the attribute 6), the answer `cancel` the one cancelling, and the choices opened. */
void MabelTalk_OfferChoices(MabelTalk *talk, const MabelTalkChoices *choices, int cancel)
{
    TalkObject *object = mtalk_object(talk);
    TalkAnswers *answers = TalkObject_Answers(object);
    const u8 *messages = choices->messages;
    u8 count = choices->count;

    TalkAnswers_Reset(answers, count, cancel);
    for (int i = 0; i < count; i++) {
        u8 message[2] = {messages[i], MABEL_TALK_ANSWER_ATTRIBUTE};
        TalkAnswers_Set(answers, i, &message[0], 0, &message[1], data_ov049_02263298[MABEL_TALK_FILE_OWN], 0);
    }
    TalkAnswers_LoadTexts(answers);
    TalkObject_OpenChoices(object, 1);
}
CLEAN_AS(func_ov049_02260b20, MabelTalk_OfferChoices)

/* ---- The sequences */

/* func_ov049_02260b9c (sequence 9, after the pockets' screen of the errand): when the player
 * picked an item and this console leads (or is alone), the item of the slot picked is taken
 * from the pockets; unless it is empty she takes it (SceneCommand_RequestMotion14), the
 * current player's errand is marked done (ItemObject_SetLow5 1) and the line is 0x2f; else
 * 0x30.
 * QUIRK: the slot is a byte, so the test that it is not negative before emptying it always
 * passes. */
void MabelTalk_TakeErrand(MabelTalk *talk)
{
    TalkObject *object = mtalk_object(talk);
    u8 line = MABEL_LINE_NO_ERRAND;

    if (GroupParams_C4CIs1()) {
        u8 *errand = VillagerPart_Object94((VillagerPart *) (void *) PlayerRecord_VillagerPart(PlayerRecords_Current()));
        if (TalkChecks_IsHostOrAlone()) {
            u8 slot = GroupParams_Arg();
            u16 item = CurrentPockets_Item(slot);
            CurrentPockets_Empty(slot);
            int empty;
            if (ItemCode_HasVariant(&item)) {
                u16 none = MABEL_TALK_NO_ITEM;
                empty = ItemCode_VariantItem(&item) == ItemCode_VariantItem(&none);
            } else {
                empty = item == MABEL_TALK_NO_ITEM;
            }
            if (!empty) {
                SceneCommand_RequestMotion14(mtalk_scene(talk), &item, 2, 5, 0);
                line = MABEL_LINE_ERRAND_TAKEN;
                ItemObject_SetLow5((ItemObject *) (void *) VillagerPartEntry_Self((VillagerPartEntry *) (void *) errand), 1);
            }
        }
    }
    TalkObject_SetMessage(object, &line, data_ov049_02263298[MABEL_TALK_FILE_OWN]);
}
CLEAN_AS(func_ov049_02260b9c, MabelTalk_TakeErrand)

/* func_ov049_02260c60 (sequence 8, each step, after a try-on): when overlay 4 lets it, the
 * room object at the item's tile is put back (func_ov004_0223b340) and the sequence ends. */
void MabelTalk_EndTryOn(MabelTalk *talk)
{
    if (func_ov004_0222c2bc() != 0) {
        func_ov004_0223b340((char *) (uintptr_t) talk->owner->tile_x, talk->owner->tile_z);
        MabelTalk_SetSequence(talk, MABEL_TALK_SEQUENCE_NONE);
    }
}
CLEAN_AS(func_ov049_02260c60, MabelTalk_EndTryOn)

/* func_ov049_02260c94 (sequence 7, each step, while the player tries an item on): when overlay
 * 4 lets it, the room object at the item's tile is changed (func_ov004_0223b39c); once the
 * player's actor is in state 16 the talk is let go, line 0x2d is shown and the sequence ends. */
void MabelTalk_WatchTryOn(MabelTalk *talk)
{
    if (func_ov004_0222c2bc() != 0) {
        func_ov004_0223b39c((char *) (uintptr_t) talk->owner->tile_x, talk->owner->tile_z);
    }
    if (PlayerActorOps_InState(MABEL_TALK_PLAYER_STATE_TRIED, MABEL_TALK_PLAYER) != 0) {
        TalkObject *object = mtalk_object(talk);
        TalkObject_Release(object);
        u8 line = MABEL_LINE_TRIED_ON;
        TalkObject_SetMessage(object, &line, data_ov049_02263298[MABEL_TALK_FILE_OWN]);
        MabelTalk_SetSequence(talk, MABEL_TALK_SEQUENCE_NONE);
    }
}
CLEAN_AS(func_ov049_02260c94, MabelTalk_WatchTryOn)

/* func_ov049_02260cf8 (sequence 6, after the screen of the clothes to sell): the price and the
 * extra bags start at 0; when the player confirmed, the price is the sum of a quarter of the
 * price of each item listed (up to 15, until an empty one): 0 gives line 0x17, else the price
 * is put in part 1 and the line is 0x1b. Without a confirmation, 0x15. */
void MabelTalk_PriceSale(MabelTalk *talk)
{
    TalkObject *object = mtalk_object(talk);
    u8 line;

    talk->price = 0;
    talk->extra_bags = 0;
    if (GroupParams_C4CIs1()) {
        u16 *items = Pockets_List();
        for (int i = 0; i < POCKET_SLOTS; i++) {
            if (items[i] == MABEL_TALK_NO_ITEM) {
                break;
            }
            u16 item = items[i];
            talk->price = talk->price + ItemTraits_Price(&item) / 4;
        }
        if (talk->price == 0) {
            line = MABEL_LINE_NOTHING_TO_SELL;
        } else {
            SceneBase_PutValue(&talk->base, talk->price, 1, MABEL_TALK_VALUE_BELLS, 0, 0);
            line = MABEL_LINE_SALE_PRICE;
        }
    } else {
        line = MABEL_LINE_NO_SALE;
    }
    TalkObject_SetMessage(object, &line, data_ov049_02263298[MABEL_TALK_FILE_OWN]);
}
CLEAN_AS(func_ov049_02260cf8, MabelTalk_PriceSale)

/* func_ov049_02260dac (sequence 5, after the screen of a swap): when the player picked a
 * design, it and the shop's design talked about are swapped (and the session told), the
 * player dressed again in it if worn, and the line is 0x21; else 0x22. */
void MabelTalk_SwapDesign(MabelTalk *talk)
{
    if (GroupParams_C4CIs1()) {
        u8 *record = PlayerRecords_Current();
        unsigned int index = mtalk_picked_design(record);
        Design_Swap(DESIGN_KIND_LOCAL, (int) index, DESIGN_KIND_SHOP, talk->owner->design_slot, 1);
        mtalk_redress(record, index);
        mtalk_say(talk, MABEL_LINE_SWAPPED);
    } else {
        mtalk_say(talk, MABEL_LINE_NO_PICK);
    }
}
CLEAN_AS(func_ov049_02260dac, MabelTalk_SwapDesign)

/* func_ov049_02260ec8 (sequence 4, after the screen of a purchase): when the player picked a
 * place, the shop's design talked about is copied there (and the session told), the player
 * dressed again in it if worn, and the line is 0x27; else 0x22. */
void MabelTalk_BuyDesign(MabelTalk *talk)
{
    if (GroupParams_C4CIs1()) {
        u8 *record = PlayerRecords_Current();
        unsigned int index = mtalk_picked_design(record);
        Design_Copy(DESIGN_KIND_SHOP, talk->owner->design_slot, DESIGN_KIND_LOCAL, (int) index, 1);
        mtalk_redress(record, index);
        mtalk_say(talk, MABEL_LINE_DESIGN_BOUGHT);
    } else {
        mtalk_say(talk, MABEL_LINE_NO_PICK);
    }
}
CLEAN_AS(func_ov049_02260ec8, MabelTalk_BuyDesign)

/* func_ov049_02260fe4 (sequence 3, after the screen of a design to show): when the player
 * picked a design, it is copied to the shop's design talked about (and the session told) and
 * the line is 0x24; else 0x22. */
void MabelTalk_ShowDesign(MabelTalk *talk)
{
    if (GroupParams_C4CIs1()) {
        u8 *record = PlayerRecords_Current();
        unsigned int index = mtalk_picked_design(record);
        Design_Copy(DESIGN_KIND_LOCAL, (int) index, DESIGN_KIND_SHOP, talk->owner->design_slot, 1);
        mtalk_say(talk, MABEL_LINE_SHOWN);
    } else {
        mtalk_say(talk, MABEL_LINE_NO_PICK);
    }
}
CLEAN_AS(func_ov049_02260fe4, MabelTalk_ShowDesign)

/* func_ov049_02261060 (sequence 2, after the screen in mode 0xb): line 0x12. */
void MabelTalk_SayAfterScreenB(MabelTalk *talk)
{
    mtalk_say(talk, MABEL_LINE_FEE);
}
CLEAN_AS(func_ov049_02261060, MabelTalk_SayAfterScreenB)

/* func_ov049_02261080 (sequence 1, after the screen in mode 4): line 0x10 when the player
 * picked a design, else 0x0f. */
void MabelTalk_SayDesignPicked(MabelTalk *talk)
{
    mtalk_say(talk, GroupParams_C4CIs1() ? MABEL_LINE_DESIGN_KIND : MABEL_LINE_NO_DESIGN);
}
CLEAN_AS(func_ov049_02261080, MabelTalk_SayDesignPicked)

/* func_ov049_022610c4: its sequence set. */
void MabelTalk_SetSequence(MabelTalk *talk, unsigned long sequence)
{
    talk->sequence = (u32) sequence;
}
CLEAN_AS(func_ov049_022610c4, MabelTalk_SetSequence)

/* func_ov049_022610cc (slot 0x84, a command of the scene ended): a sequence not run each step
 * and with a function runs, and the sequence goes back to 0.
 * REQUIRES: the sequence is 0 to 9. */
void MabelTalk_RunCommandSequence(MabelTalk *talk)
{
    const MabelTalkStep *step = &data_ov049_022633b0[talk->sequence];
    if (step->each_step != 0 || step->run.function == 0) {
        return;
    }
    MemberPointer_CallVoid(&step->run, talk);
    MabelTalk_SetSequence(talk, MABEL_TALK_SEQUENCE_NONE);
}
CLEAN_AS(func_ov049_022610cc, MabelTalk_RunCommandSequence)

/* func_ov049_0226111c (slot 0x80, before each step of the scene): a sequence run each step
 * runs, when it has a function.
 * REQUIRES: the sequence is 0 to 9. */
void MabelTalk_RunStepSequence(MabelTalk *talk)
{
    const MabelTalkStep *step = &data_ov049_022633b0[talk->sequence];
    if (step->each_step != 0 && step->run.function != 0) {
        MemberPointer_CallVoid(&step->run, talk);
    }
}
CLEAN_AS(func_ov049_0226111c, MabelTalk_RunStepSequence)

/* ---- The answers */

/* func_ov049_02261160 (the answers to the lines of the other files): at the lines 0 to 0x11,
 * the answer picked gives her next line (data_ov049_02262dc0), except the answer 2, with which
 * the player's dated event of kind 2 today (if any) is marked. Unlinked (and without the game
 * variable 0x4a) the special character 5 joins as the second speaker. */
void MabelTalk_OnDramaAnswer(MabelTalk *talk)
{
    u8 shown = mtalk_shown(talk);
    if (shown <= 0x11) {
        unsigned int answer = (unsigned int) mtalk_answer(talk);
        if (answer != 2) {
            mtalk_say(talk, data_ov049_02262dc0[answer]);
        } else {
            u8 event;
            if (TalkChecks_TodaysEventOfKind(mtalk_owner(talk), &event, MABEL_TALK_EVENT_KIND)) {
                TalkChecks_MarkDayEvent(mtalk_owner(talk), &event);
            }
        }
    }
    mtalk_add_second_speaker(talk, data_020ccf94);
}
CLEAN_AS(func_ov049_02261160, MabelTalk_OnDramaAnswer)

/* func_ov049_022611f8 (the answer at line 0x2e, the errand): the first answer opens the
 * pockets' screen offering the errand's items (func_ov049_02261224), then sequence 9. */
void MabelTalk_OnAnswerErrand(MabelTalk *talk, int answer)
{
    if (answer == 0) {
        SceneCommand_SetPocketPredicate(mtalk_scene(talk), (PocketPredicate) (uintptr_t) func_ov049_02261224,
                                        MABEL_TALK_POCKET_ARG, 0);
        SceneCommand_RequestScreen(mtalk_scene(talk), MABEL_TALK_SCREEN_POCKETS);
        MabelTalk_SetSequence(talk, MABEL_TALK_SEQUENCE_ERRAND);
    }
}
CLEAN_AS(func_ov049_022611f8, MabelTalk_OnAnswerErrand)

/* func_ov049_02261224 (the pockets' test of the errand): an item in state 2 that is 0x155f or
 * 0x1560. */
unsigned short MabelTalk_IsErrandItem(unsigned short *item, int state)
{
    if (state == MABEL_ERRAND_STATE) {
        return (unsigned short) (*item >= MABEL_ERRAND_FIRST && *item <= MABEL_ERRAND_LAST);
    }
    return 0;
}
CLEAN_AS(func_ov049_02261224, MabelTalk_IsErrandItem)

/* func_ov049_0226124c (the answer at line 0x2d, after a try-on): what the player wore before
 * is put back on (the clothes, the hat or the accessory, as the item tried), and the second
 * item taken off for it, if any; the player's flag 0x0e cleared, sequence 8, the camera's
 * previous mode; then the first answer buys the item (mtalk_try_buy). */
void MabelTalk_OnAnswerTriedOn(MabelTalk *talk, int answer)
{
    if (mtalk_is_clothes(talk->owner->item)) {
        mtalk_wear_clothes(talk->owner->worn);
    }
    if (mtalk_is_hat(talk->owner->item)) {
        mtalk_wear_hat(talk->owner->worn);
    }
    if (mtalk_is_accessory(talk->owner->item)) {
        mtalk_wear_accessory(talk->owner->worn);
    }
    if (talk->owner->worn_second != MABEL_TALK_NO_ITEM) {
        u16 second = talk->owner->worn_second;
        if (mtalk_is_hat(second)) {
            mtalk_wear_hat(talk->owner->worn_second);
        } else if (mtalk_is_accessory(second)) {
            mtalk_wear_accessory(talk->owner->worn_second);
        }
    }
    PlayerActorOps_SwitchFlag0e(0, MABEL_TALK_PLAYER);
    MabelTalk_SetSequence(talk, MABEL_TALK_SEQUENCE_TRIED_ON);
    CameraControl_SetPreviousMode();
    if (answer == 0) {
        mtalk_try_buy(talk);
    }
}
CLEAN_AS(func_ov049_0226124c, MabelTalk_OnAnswerTriedOn)

/* func_ov049_02261410 (the answer at line 0x28, an item on display): the first buys it
 * (mtalk_try_buy); the second, for clothes, hats and accessories, has the player try it on:
 * what the player wears in its place is kept and the item put on. A hat of 0x13a8 to 0x13c7
 * (unless its trait byte 7 is 8) takes the accessory off, and an accessory such a hat, which
 * is kept as the second item. Then the player's flag 0x0e set, the camera's mode 4, the talk
 * held, and sequence 7 until the try-on is over. */
void MabelTalk_OnAnswerItem(MabelTalk *talk, int answer)
{
    u8 *record = PlayerRecords_Current();

    if (answer == 0) {
        mtalk_try_buy(talk);
        return;
    }
    if (answer != 1) {
        return;
    }
    talk->owner->worn_second = MABEL_TALK_NO_ITEM;
    Mabel *owner = talk->owner;
    u16 item = owner->item;
    if (!mtalk_is_clothes(item) && !mtalk_is_hat(item) && !mtalk_is_accessory(item)) {
        return;
    }
    if (mtalk_is_clothes(item)) {
        talk->owner->worn = *PlayerRecord_Clothes(record);
        mtalk_wear_clothes(talk->owner->item);
    } else if (mtalk_is_hat(item)) {
        if (mtalk_is_hat_a(item) && ItemTraits_IsHeadAUnk07Is8(&owner->item) == 0) {
            talk->owner->worn_second = *PlayerRecord_PartCItem(record);
            mtalk_wear_accessory(MABEL_TALK_NO_ITEM);
        }
        talk->owner->worn = *PlayerRecord_HeadItem(record);
        mtalk_wear_hat(talk->owner->item);
    } else {
        talk->owner->worn = *PlayerRecord_PartCItem(record);
        mtalk_wear_accessory(talk->owner->item);
        u16 hat = *PlayerRecord_HeadItem(record);
        if (mtalk_is_hat_a(hat) && ItemTraits_IsHeadAUnk07Is8(&hat) == 0) {
            talk->owner->worn_second = *PlayerRecord_HeadItem(record);
            mtalk_wear_hat(MABEL_TALK_NO_ITEM);
        }
    }
    PlayerActorOps_SwitchFlag0e(1, MABEL_TALK_PLAYER);
    CameraControl_SetMode4();
    TalkObject_Hold(mtalk_object(talk));
    MabelTalk_SetSequence(talk, MABEL_TALK_SEQUENCE_TRYING_ON);
}
CLEAN_AS(func_ov049_02261410, MabelTalk_OnAnswerItem)

/* func_ov049_0226166c (the answer at line 0x17): the second leaves the listed items as they
 * are (Pockets_ConvertListed 0). */
void MabelTalk_OnAnswerNoSale(int unused, int answer)
{
    (void) unused;
    if (answer == 1) {
        Pockets_ConvertListed(0);
    }
}
CLEAN_AS(func_ov049_0226166c, MabelTalk_OnAnswerNoSale)

/* func_ov049_02261680 (the answer at line 0x1b, the price offered for the items): the first,
 * by where the bells fit: the wallet, they are paid and the line is 0x1a; the bags too, 0x1e
 * (paid at its end); nowhere, 0x38 and the listed items left as they are. The second leaves
 * them as they are. */
void MabelTalk_OnAnswerSalePrice(MabelTalk *talk, int answer)
{
    switch (answer) {
        case 0:
            switch (SceneBells_Fit(mtalk_owner(talk), talk->price, talk->extra_bags)) {
                case SCENE_BELLS_FIT_WALLET:
                    SceneBells_Give(mtalk_owner(talk), talk->price);
                    mtalk_say(talk, MABEL_LINE_SOLD);
                    break;
                case SCENE_BELLS_FIT_BAGS:
                    mtalk_say(talk, MABEL_LINE_SOLD_BAGS);
                    break;
                case SCENE_BELLS_FIT_NONE:
                    mtalk_say(talk, MABEL_LINE_NO_ROOM_SALE);
                    Pockets_ConvertListed(0);
                    break;
                default:
                    break;
            }
            break;
        case 1:
            Pockets_ConvertListed(0);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov049_02261680, MabelTalk_OnAnswerSalePrice)

/* func_ov049_0226171c (the answer at line 0x10): the design picked gets a kind at random from
 * data_ov049_02262dec: one of the entries 0 to 2 for the first answer, 3 to 5 for the second,
 * 6 to 9 for the third, the entry 0 for any other. */
void MabelTalk_OnAnswerDesignKind(MabelTalk *talk, int answer)
{
    int entry = 0;
    switch (answer) {
        case 0:
            entry = (int) MainRandom_Below(3);
            break;
        case 1:
            entry = (int) MainRandom_Below(3) + 3;
            break;
        case 2:
            entry = (int) MainRandom_Below(4) + 6;
            break;
        default:
            break;
    }
    MabelTalk_SetDesignKind(mtalk_owner(talk), (int) data_ov049_02262dec[entry]);
}
CLEAN_AS(func_ov049_0226171c, MabelTalk_OnAnswerDesignKind)

/* func_ov049_02261764 (the answer at line 0x0b): the first gives line 0x0e when the player
 * can pay 350 bells, else 0x0d. */
void MabelTalk_OnAnswerFee(MabelTalk *talk, int answer)
{
    if (answer != 0) {
        return;
    }
    mtalk_say(talk, SceneBells_CanPay(mtalk_owner(talk), MABEL_TALK_FEE) == 0 ? MABEL_LINE_NO_BELLS_FEE : MABEL_LINE_FEE_OK);
}
CLEAN_AS(func_ov049_02261764, MabelTalk_OnAnswerFee)

/* func_ov049_022617b4 (the answers at lines 0x04, 0x15, 0x1a and 0x38): linked (or with the
 * game variable 0x4a), the third answer gives line 0x1c and the first 0x37; unlinked the
 * special character 5 joins as the second speaker. */
void MabelTalk_OnAnswerLinked(MabelTalk *talk, int answer)
{
    NetSession *session = data_020ccf94;
    if (mtalk_linked_or_variable(session)) {
        if (answer == 2) {
            mtalk_say(talk, MABEL_LINE_LINKED_ANSWER_2);
        } else if (answer == 0) {
            mtalk_say(talk, MABEL_LINE_LINKED_ANSWER_0);
        }
    }
    mtalk_add_second_speaker(talk, session);
}
CLEAN_AS(func_ov049_022617b4, MabelTalk_OnAnswerLinked)

/* func_ov049_02261848 (the answers to her own lines): each handler whose line is the one
 * shown is called with the answer picked. */
void MabelTalk_OnPlainAnswer(MabelTalk *talk)
{
    static const MemberPointer *const handlers[MABEL_TALK_ANSWERS] = {
        &data_ov049_022631d0, /* 0x04: MabelTalk_OnAnswerLinked */
        &data_ov049_02263270, /* 0x15: MabelTalk_OnAnswerLinked */
        &data_ov049_02263090, /* 0x1a: MabelTalk_OnAnswerLinked */
        &data_ov049_02263098, /* 0x0b: MabelTalk_OnAnswerFee */
        &data_ov049_022630a8, /* 0x10: MabelTalk_OnAnswerDesignKind */
        &data_ov049_022630b8, /* 0x1b: MabelTalk_OnAnswerSalePrice */
        &data_ov049_02263180, /* 0x17: MabelTalk_OnAnswerNoSale */
        &data_ov049_02263120, /* 0x28: MabelTalk_OnAnswerItem */
        &data_ov049_02263288, /* 0x2d: MabelTalk_OnAnswerTriedOn */
        &data_ov049_02263278, /* 0x2e: MabelTalk_OnAnswerErrand */
        &data_ov049_022630a0, /* 0x38: MabelTalk_OnAnswerLinked */
    };
    u32 flags = data_ov049_0226360c;
    if ((flags & 1) == 0) {
        for (int i = 0; i < MABEL_TALK_ANSWERS; i++) {
            data_ov049_02263428[i].handler = *handlers[i];
        }
        data_ov049_0226360c = flags | 1;
    }
    for (u32 i = 0; i < MABEL_TALK_ANSWERS; i++) {
        const MabelTalkHandler *entry = &data_ov049_02263428[i];
        if (entry->line == mtalk_shown(talk)) {
            mtalk_call(&entry->handler, talk, mtalk_answer(talk));
        }
    }
}
CLEAN_AS(func_ov049_02261848, MabelTalk_OnPlainAnswer)

/* func_ov049_02261960 (slot 0x18, the player's answer): not while a game is being started
 * anew in talk mode 2; else to MabelTalk_OnPlainAnswer when the talk's file is
 * "sp_npc_ysister", to MabelTalk_OnDramaAnswer otherwise, with `arg`. */
void MabelTalk_OnAnswer(MabelTalk *talk, int arg)
{
    static const MemberPointer *const kinds[2] = {
        &data_ov049_02263168, /* MabelTalk_OnPlainAnswer */
        &data_ov049_02263130, /* MabelTalk_OnDramaAnswer */
    };

    if (MabelTalk_Mode(talk) == MABEL_TALK_MODE_TALKED && StartKind_IsSet() != 0) {
        return;
    }
    MemberTable_InitOnce(&data_ov049_02263608, data_ov049_02263628, kinds, 2);
    const char *own = data_ov049_02263298[MABEL_TALK_FILE_OWN];
    size_t length = strlen(own);
    int other = strncmp((const char *) talk->base.receiver, own, length) != 0;
    mtalk_call(&data_ov049_02263628[other], talk, arg);
}
CLEAN_AS(func_ov049_02261960, MabelTalk_OnAnswer)

/* ---- The ends of lines */

/* func_ov049_022619fc (the end of a line of the other files): nothing. */
void MabelTalk_OnOtherLineEnded(void) {}
CLEAN_AS(func_ov049_022619fc, MabelTalk_OnOtherLineEnded)

/* func_ov049_02261a00 (the end of line 0x23): the screen of a swap (mode 8), sequence 5. */
void MabelTalk_OpenSwap(MabelTalk *talk)
{
    mtalk_open(talk, MABEL_TALK_MODE_SWAP_DESIGN, MABEL_TALK_SEQUENCE_SWAP_DESIGN);
}
CLEAN_AS(func_ov049_02261a00, MabelTalk_OpenSwap)

/* func_ov049_02261a24 (the end of line 0x26): the screen of a purchase (mode 7), sequence 4. */
void MabelTalk_OpenBuyDesign(MabelTalk *talk)
{
    mtalk_open(talk, MABEL_TALK_MODE_BUY_DESIGN, MABEL_TALK_SEQUENCE_BUY_DESIGN);
}
CLEAN_AS(func_ov049_02261a24, MabelTalk_OpenBuyDesign)

/* func_ov049_02261a48 (the end of line 0x36): the screen of a design to show (mode 5),
 * sequence 3. */
void MabelTalk_OpenShowDesign(MabelTalk *talk)
{
    mtalk_open(talk, MABEL_TALK_MODE_SHOW_DESIGN, MABEL_TALK_SEQUENCE_SHOW_DESIGN);
}
CLEAN_AS(func_ov049_02261a48, MabelTalk_OpenShowDesign)

/* func_ov049_02261a6c (the end of line 0x28, an item's price): the answers for the item's
 * class offered, the last one cancelling: clothes, hats, accessories (buy, try on, no) or
 * umbrellas (buy, no); nothing for another item. */
void MabelTalk_OfferItemChoices(MabelTalk *talk)
{
    u16 item = talk->owner->item;
    const MabelTalkChoices *choices;

    if (mtalk_is_clothes(item)) {
        choices = &data_ov049_02263324;
    } else if (mtalk_is_hat(item)) {
        choices = &data_ov049_0226332c;
    } else if (mtalk_is_accessory(item)) {
        choices = &data_ov049_02263334;
    } else if (mtalk_in(item, MABEL_UMBRELLA_FIRST, MABEL_UMBRELLA_LAST)) {
        choices = &data_ov049_0226333c;
    } else {
        return;
    }
    MabelTalk_OfferChoices(talk, choices, choices->count - 1);
}
CLEAN_AS(func_ov049_02261a6c, MabelTalk_OfferItemChoices)

/* func_ov049_02261b34 (the end of line 0x1e): the price of the items sold paid. */
void MabelTalk_PaySale(MabelTalk *talk)
{
    SceneBells_Give(mtalk_owner(talk), talk->price);
}
CLEAN_AS(func_ov049_02261b34, MabelTalk_PaySale)

/* func_ov049_02261b48 (the end of line 0x14): the screen of the clothes to sell (mode 0x1e),
 * sequence 6. */
void MabelTalk_OpenSell(MabelTalk *talk)
{
    mtalk_open(talk, MABEL_TALK_MODE_SELL, MABEL_TALK_SEQUENCE_PRICE_SALE);
}
CLEAN_AS(func_ov049_02261b48, MabelTalk_OpenSell)

/* func_ov049_02261b6c (the end of line 0x12): 350 bells taken. */
void MabelTalk_TakeFee(MabelTalk *talk)
{
    SceneBells_Take(mtalk_owner(talk), MABEL_TALK_FEE);
}
CLEAN_AS(func_ov049_02261b6c, MabelTalk_TakeFee)

/* func_ov049_02261b80 (the end of line 0x11): the screen in mode 0xb, sequence 2. */
void MabelTalk_OpenScreenB(MabelTalk *talk)
{
    mtalk_open(talk, MABEL_TALK_MODE_SCREEN_B, MABEL_TALK_SEQUENCE_SCREEN_B);
}
CLEAN_AS(func_ov049_02261b80, MabelTalk_OpenScreenB)

/* func_ov049_02261ba4 (the end of line 0x0e): the screen to pick a design (mode 4),
 * sequence 1. */
void MabelTalk_OpenDesignPick(MabelTalk *talk)
{
    mtalk_open(talk, MABEL_TALK_MODE_DESIGN_PICK, MABEL_TALK_SEQUENCE_DESIGN_PICKED);
}
CLEAN_AS(func_ov049_02261ba4, MabelTalk_OpenDesignPick)

/* func_ov049_02261bc8 (the ends of her own lines): each handler whose line is the one shown
 * is called. */
void MabelTalk_OnPlainLineEnded(MabelTalk *talk)
{
    static const MemberPointer *const handlers[MABEL_TALK_LINE_ENDS] = {
        &data_ov049_02263178, /* 0x0e: MabelTalk_OpenDesignPick */
        &data_ov049_022631a0, /* 0x11: MabelTalk_OpenScreenB */
        &data_ov049_022631b0, /* 0x12: MabelTalk_TakeFee */
        &data_ov049_022631c0, /* 0x14: MabelTalk_OpenSell */
        &data_ov049_02263220, /* 0x1e: MabelTalk_PaySale */
        &data_ov049_02263258, /* 0x28: MabelTalk_OfferItemChoices */
        &data_ov049_02263108, /* 0x36: MabelTalk_OpenShowDesign */
        &data_ov049_02263100, /* 0x26: MabelTalk_OpenBuyDesign */
        &data_ov049_022630f8, /* 0x23: MabelTalk_OpenSwap */
    };
    u32 flags = data_ov049_02263604;
    if ((flags & 1) == 0) {
        for (int i = 0; i < MABEL_TALK_LINE_ENDS; i++) {
            data_ov049_02263344[i].handler = *handlers[i];
        }
        data_ov049_02263604 = flags | 1;
    }
    for (u32 i = 0; i < MABEL_TALK_LINE_ENDS; i++) {
        const MabelTalkHandler *entry = &data_ov049_02263344[i];
        if (entry->line == mtalk_shown(talk)) {
            MemberPointer_CallVoid(&entry->handler, talk);
        }
    }
}
CLEAN_AS(func_ov049_02261bc8, MabelTalk_OnPlainLineEnded)

/* func_ov049_02261cb0 (slot 0x14, a line ended): not while a game is being started anew in
 * talk mode 2; else to MabelTalk_OnPlainLineEnded when the talk's file is "sp_npc_ysister",
 * to MabelTalk_OnOtherLineEnded otherwise, with `arg`. */
void MabelTalk_OnLineEnded(MabelTalk *talk, void *arg)
{
    static const MemberPointer *const kinds[2] = {
        &data_ov049_02263158, /* MabelTalk_OnPlainLineEnded */
        &data_ov049_02263128, /* MabelTalk_OnOtherLineEnded */
    };

    if (MabelTalk_Mode(talk) == MABEL_TALK_MODE_TALKED && StartKind_IsSet() != 0) {
        return;
    }
    MemberTable_InitOnce(&data_ov049_02263600, data_ov049_02263610, kinds, 2);
    const char *own = data_ov049_02263298[MABEL_TALK_FILE_OWN];
    size_t length = strlen(own);
    int other = strncmp((const char *) talk->base.receiver, own, length) != 0;
    const MemberPointer *handler = &data_ov049_02263610[other];
    void *self = MemberPointer_Object(handler, talk);
    ((void (*)(void *, void *))(uintptr_t) MemberPointer_Code(handler, self))(self, arg);
}
CLEAN_AS(func_ov049_02261cb0, MabelTalk_OnLineEnded)

/* ---- The line it starts with, and its class */

/* func_ov049_02261d4c (slot 0x78, the line the talk starts with):
 * - talk mode 2 while a game is being started anew: line 6 of "sp_etc_sequence4";
 * - talk mode 2 with the current player's errand for her (VillagerPartEntry_Accepts her
 *   person code): line 0x2e;
 * - talk mode 2 with a dated event of kind 2 today: noted, and its part's line of
 *   "sp_npc_drama4";
 * - else the line of the talk mode (data_ov049_02262dc8): in mode 4 the item's price
 *   (ItemTraits_Price) is kept and put in part 0 with the item's name (line
 *   0x1e of "sp_etc_sequence4" while a game is being started anew); in mode 5 the shop's
 *   design of the item's code is noted, its title put in value 2, and whoever made it: in
 *   another town, the maker in part 2 and the town in part 3 (line 0x33); another player
 *   of the town, the maker in part 2 (line 0x32); else the player's own (0x31). While a game
 *   is being started anew, line 0x1d of "sp_etc_sequence4".
 * QUIRK: the line of a dated event is read from a table of rows of seven (by the event and
 * the part); the event 4's row runs into the next table. */
void MabelTalk_Line(MabelTalk *talk, MabelTalkLine *out)
{
    u8 *record = PlayerRecords_Current();
    u8 *errand = VillagerPart_Object94((VillagerPart *) (void *) PlayerRecord_VillagerPart(record));
    Mabel *owner;

    if (StartKind_IsSet() != 0 && MabelTalk_Mode(talk) == MABEL_TALK_MODE_TALKED) {
        out->text = data_ov049_02263298[MABEL_TALK_FILE_SEQUENCE];
        out->message = 6;
        return;
    }
    if (MabelTalk_Mode(talk) == MABEL_TALK_MODE_TALKED &&
        VillagerPartEntry_Accepts((VillagerPartEntry *) (void *) errand,
                                  (const u16 *) (const void *) (talk->owner->base + 0xea)) != 0) {
        out->message = MABEL_LINE_ERRAND;
        out->text = data_ov049_02263298[MABEL_TALK_FILE_OWN];
        return;
    }
    u8 event;
    if (MabelTalk_Mode(talk) == MABEL_TALK_MODE_TALKED &&
        TalkChecks_TodaysEventOfKind(mtalk_owner(talk), &event, MABEL_TALK_EVENT_KIND) != 0) {
        talk->owner->has_event = 1;
        out->message = data_ov049_02262dd0[((event >> 2) & 7) * MABEL_TALK_DRAMA_PARTS + ((event >> 5) & 7)];
        out->text = data_ov049_02263298[MABEL_TALK_FILE_DRAMA];
        return;
    }

    out->message = data_ov049_02262dc8[talk->mode];
    out->text = data_ov049_02263298[MABEL_TALK_FILE_OWN];

    if (MabelTalk_Mode(talk) == MABEL_TALK_MODE_ITEM) {
        talk->price = ItemTraits_Price(&talk->owner->item);
        SceneBase_PutValue(&talk->base, talk->price, 0, MABEL_TALK_VALUE_BELLS, 0, 0);
        SceneBase_PutItemName(&talk->base, (int) (uintptr_t) &talk->owner->item, 0, MABEL_TALK_VALUE_ITEM);
        if (StartKind_IsSet() != 0) {
            out->text = data_ov049_02263298[MABEL_TALK_FILE_SEQUENCE];
            out->message = 0x1e;
        }
        return;
    }
    if (MabelTalk_Mode(talk) != MABEL_TALK_MODE_SHOP_DESIGN) {
        return;
    }

    owner = talk->owner;
    u16 code = owner->item;
    int slot = mtalk_in(code, MABEL_TALK_DESIGN_FIRST, MABEL_TALK_DESIGN_LAST) ? (code - MABEL_TALK_DESIGN_FIRST) >> 2 : -1;
    owner->design_slot = (u8) slot;

    unsigned int design =
        ShopDesigns_At((unsigned int) (uintptr_t) (data_021dc7a8 + MABEL_TALK_SHOP_DESIGNS), talk->owner->design_slot);
    NameText title;
    NameText_Construct(&title);
    DesignInfo_TitleToText((DesignInfo *) (uintptr_t) Design_Info(design), &title);
    TalkObject_SetValue(mtalk_object(talk), 2, (TextBase *) (void *) &title, MABEL_TALK_VALUE_TEXT);
    DesignCreator maker = *DesignInfo_Creator((DesignInfo *) (uintptr_t) Design_Info(design));
    DesignCreator player = *PlayerRecord_Player(record);
    TownName maker_town = *PlayerId_Town(&maker);
    TownName player_town = *PlayerId_Town(&player);

    if (StartKind_IsSet() != 0) {
        out->text = data_ov049_02263298[MABEL_TALK_FILE_SEQUENCE];
        out->message = 0x1d;
    } else if (maker_town.number != player_town.number || memcmp(maker_town.name, player_town.name, 12) != 0) {
        SceneBase_PutNameAt10(&talk->base, &maker, 2);
        SceneBase_PutNameAt2(&talk->base, (unsigned int) (uintptr_t) &maker_town, 3);
        out->message = MABEL_LINE_DESIGN_ELSEWHERE;
    } else if (maker.town_id != player.town_id || memcmp(maker.town_name, player.town_name, 12) != 0 ||
               PlayerId_SamePlayer(&maker, &player) == 0) {
        SceneBase_PutNameAt10(&talk->base, &maker, 2);
        out->message = MABEL_LINE_DESIGN_TOWN;
    }

    TownName_Destruct(&player_town);
    TownName_Destruct(&maker_town);
    PlayerId_Destruct(&player);
    PlayerId_Destruct(&maker);
    NameText_Destruct(&title);
}
CLEAN_AS(func_ov049_02261d4c, MabelTalk_Line)

/* func_ov049_02262084: its talk mode. */
unsigned long MabelTalk_Mode(MabelTalk *talk)
{
    return talk->mode;
}
CLEAN_AS(func_ov049_02262084, MabelTalk_Mode)

/* func_ov049_0226208c: its talk mode set. */
void MabelTalk_SetMode(MabelTalk *talk, unsigned long mode)
{
    talk->mode = (u32) mode;
}
CLEAN_AS(func_ov049_0226208c, MabelTalk_SetMode)

/* func_ov049_02262094: the scene reset through its vtable slot 0x08 and given its owner. */
void MabelTalk_Begin(MabelTalk *talk, Mabel *owner)
{
    u32 vtable = *(const u32 *) (const void *) talk;
    u32 code = *(const u32 *) (uintptr_t) (vtable + MABEL_TALK_SLOT_RESET);
    ((void (*)(MabelTalk *))(uintptr_t) code)(talk);
    talk->owner = owner;
}
CLEAN_AS(func_ov049_02262094, MabelTalk_Begin)

/* func_ov049_022620b0 (slot 0x04): its destructor, then the scene freed. */
void *MabelTalk_DestructDelete(MabelTalk *talk)
{
    *(const u8 **) (void *) talk = data_ov049_022634b4;
    Obj020d9ff8_DestructBody(talk);
    Heap_OperatorDeleteB(talk);
    return talk;
}
CLEAN_AS(func_ov049_022620b0, MabelTalk_DestructDelete)

/* func_ov049_022620d0 (slot 0x00): the scene class's destructor. */
MabelTalk *MabelTalk_Destruct(MabelTalk *talk)
{
    *(const u8 **) (void *) talk = data_ov049_022634b4;
    Obj020d9ff8_DestructBody(talk);
    return talk;
}
CLEAN_AS(func_ov049_022620d0, MabelTalk_Destruct)

/* func_ov049_022620e8: the constructor: a scene of class 0x020d9ff8 given this class's
 * vtable. */
void *MabelTalk_Construct(void *talk)
{
    Obj020d9ff8_Construct(talk);
    *(const u8 **) talk = data_ov049_022634b4;
    return talk;
}
CLEAN_AS(func_ov049_022620e8, MabelTalk_Construct)
