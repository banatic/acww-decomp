/* The fox's talk scene in his tent (fox_tent_talk.h): its class, the line it starts with, the
 * player's answers, the end of a line and the sale. */
#include "fox_tent_talk.h"

#include <stdint.h>
#include <string.h>

#include "autoload_2/heap.h"
#include "clean.h"
#include "main/current_pockets.h"
#include "main/design.h"
#include "main/fox_shop.h"
#include "main/item_code.h"
#include "main/item_traits.h"
#include "main/last_sale.h"
#include "main/main_random.h"
#include "main/message_receiver.h"
#include "main/obj_020d9ff8.h"
#include "main/player_id.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/scene_base.h"
#include "main/scene_bells.h"
#include "main/scene_command.h"
#include "main/session.h"
#include "main/shops.h"
#include "main/talk_answers.h"
#include "main/talk_checks.h"
#include "main/talk_object.h"

static_assert(sizeof(FoxTentTalkStart) == 8, "what a talk starts with");

/* The vtable of its class. */
extern const u8 data_ov052_02261eb0[];
/* Its message file, "sp_npc_fox". */
extern const char data_ov052_02261e50[];
/* The line each sequence starts with (FOX_TENT_TALK_*). */
extern const FoxTentTalkStart data_ov052_02261be0[FOX_TENT_TALK_SEQUENCES];
/* The fox's shop and its last sale (main's state block). */
extern FoxShop data_021f3b30;
extern LastSale data_021f3aec;
/* The session of the multiplayer game. */
extern NetSession *data_020ccf94;

extern void MI_CpuFill8(void *dst, u8 value, u32 size);

#define FOX_TENT_TALK_NO_ITEM 0xfff1
#define FOX_TENT_TALK_NO_LINE 0xff

/* FoxTentTalk.card_slot: not looked for yet, and done with. */
#define FOX_TENT_TALK_CARD_UNKNOWN (-1)
#define FOX_TENT_TALK_CARD_DONE (-2)

/* The vtable slot of the scene that resets it (FoxTentTalk_Reset). */
#define FOX_TENT_TALK_SLOT_RESET 0x08

/* The current player's flag of a member, and the daily bit of the first talk of the day. */
#define FOX_TENT_TALK_MEMBER_FLAG 0xc
#define FOX_TENT_TALK_DAILY_BIT 1

/* The items it asks for and hands over, the membership card and the shop's sold marker. */
#define FOX_TENT_TALK_ASKED_ITEM 0x34a8
#define FOX_TENT_TALK_GIVEN_ITEM 0x36fc
#define FOX_TENT_TALK_CARD 0x149d
#define FOX_TENT_TALK_SOLD_MARKER 0x1547

/* The membership's price, in bells. */
#define FOX_TENT_TALK_MEMBERSHIP 3000

/* How an item's name and its price are put into the talk (SceneBase_PutItemName,
 * SceneBase_PutValue): the value kind of a name, the slots and the price's format. */
#define FOX_TENT_TALK_NAME_KIND 7
#define FOX_TENT_TALK_SLOT_LAST_ITEM 0
#define FOX_TENT_TALK_SLOT_ITEM 1
#define FOX_TENT_TALK_SLOT_BUYER 1
#define FOX_TENT_TALK_SLOT_PRICE 2
#define FOX_TENT_TALK_PRICE_FORMAT 10

/* The values its item motions (SceneCommand_RequestMotion13 and 14) are asked with. */
#define FOX_TENT_TALK_MOTION_B 5

/* Its lines (the receiver's message). */
#define FOX_TENT_TALK_LINE_GREETING 0x06
#define FOX_TENT_TALK_LINE_OFFER 0x07
#define FOX_TENT_TALK_LINE_JOIN 0x08
#define FOX_TENT_TALK_LINE_DECLINED 0x09
#define FOX_TENT_TALK_LINE_CANNOT_JOIN 0x0a
#define FOX_TENT_TALK_LINE_NOT_JOINING 0x0c
#define FOX_TENT_TALK_LINE_JOINED 0x10
#define FOX_TENT_TALK_LINE_CARD 0x11
#define FOX_TENT_TALK_LINE_OFFER_AGAIN 0x12
#define FOX_TENT_TALK_LINE_PLAIN 0x17
#define FOX_TENT_TALK_LINE_PLAIN_4 0x1a
#define FOX_TENT_TALK_LINE_PLAIN_4_INSTEAD 0x30
#define FOX_TENT_TALK_LINE_TOLD 0x1d
#define FOX_TENT_TALK_LINE_ITEM_OFFERS 0x1e
#define FOX_TENT_TALK_LINE_ITEM_OFFERS_LAST 0x22
#define FOX_TENT_TALK_LINE_THANKS 0x24
#define FOX_TENT_TALK_LINE_THANKS_LAST 0x28
#define FOX_TENT_TALK_LINE_CANNOT_PAY 0x29
#define FOX_TENT_TALK_LINE_NO_ROOM 0x2a
#define FOX_TENT_TALK_LINE_ASK_ITEM 0x2c
#define FOX_TENT_TALK_LINE_ITEM_KEPT 0x2d
#define FOX_TENT_TALK_LINE_ITEM_TAKEN 0x2e
#define FOX_TENT_TALK_LINE_ITEM_GIVEN 0x2f

/* The plain talk's lines: four at random. */
#define FOX_TENT_TALK_PLAIN_LINES 4

static TalkObject *fox_tent_talk_object(FoxTentTalk *talk)
{
    return (TalkObject *) (void *) talk->base.talk;
}

static SceneCommandScene *fox_tent_talk_scene(FoxTentTalk *talk)
{
    return (SceneCommandScene *) (void *) talk;
}

/* The line shown. */
static u8 fox_tent_talk_shown(const FoxTentTalk *talk)
{
    return ((const MessageReceiver *) (const void *) talk)->message;
}

/* The answer picked in the talk's menu of choices. */
static unsigned int fox_tent_talk_answer(FoxTentTalk *talk)
{
    return TalkAnswers_Picked((TalkAnswers *) (uintptr_t) (u32) SceneBase_TalkChoices(&talk->base));
}

/* The talk shows `line` of "sp_npc_fox". */
static void fox_tent_talk_say(FoxTentTalk *talk, int line)
{
    u8 message = (u8) line;
    TalkObject_SetMessage(fox_tent_talk_object(talk), &message, data_ov052_02261e50);
}

/* Whether two item codes are the same: by ItemCode_VariantItem's number for the kinds that have
 * one, else by code. */
static int fox_tent_talk_same_item(const u16 *item, const u16 *other)
{
    if (ItemCode_HasVariant(item)) {
        int own = ItemCode_VariantItem(item);
        return own == ItemCode_VariantItem(other);
    }
    return *item == *other;
}

/* Whether a code is the empty one (compared as fox_tent_talk_same_item does). */
static int fox_tent_talk_no_item(const u16 *item)
{
    if (ItemCode_HasVariant(item)) {
        u16 none = FOX_TENT_TALK_NO_ITEM;
        int own = ItemCode_VariantItem(item);
        return own == ItemCode_VariantItem(&none);
    }
    return *item == FOX_TENT_TALK_NO_ITEM;
}

/* Whether two players are the same: the town's number, the town's name and PlayerId_SamePlayer. */
static int fox_tent_talk_same_player(const DesignCreator *a, const DesignCreator *b)
{
    return a->town_id == b->town_id && memcmp(a->town_name, b->town_name, sizeof(a->town_name)) == 0 &&
           PlayerId_SamePlayer(a, b);
}

/* One of the five variants of `used` not yet said, at random, noted as said (all of them cleared
 * first when that was the last one); when it is noted, `told` (when given) gets `item`. */
static int fox_tent_talk_pick_variant(FoxTent *fox, u8 *used, u16 *told, const u16 *item)
{
    int variant = FoxTent_PickUnused((int) (uintptr_t) fox, used, FOX_TENT_LINE_VARIANTS);
    if (told != NULL) {
        if (used[variant] == 0) {
            used[variant] = 1;
            *told = *item;
        }
    } else {
        used[variant] = 1;
    }
    if (FoxTent_CountUnused((int) (uintptr_t) fox, used, FOX_TENT_LINE_VARIANTS) == 0) {
        MI_CpuFill8(used, 0, FOX_TENT_LINE_VARIANTS);
        used[variant] = 1;
        if (told != NULL) {
            *told = *item;
        }
    }
    return variant;
}

/* ---- The class */

/* func_ov052_02261108 (vtable slot 0x04): its destructor, then the scene freed. */
FoxTentTalk *FoxTentTalk_DestructDelete(FoxTentTalk *talk)
{
    talk->base.vtable = data_ov052_02261eb0;
    Obj020d9ff8_DestructBody(talk);
    Heap_OperatorDeleteB(talk);
    return talk;
}
CLEAN_AS(func_ov052_02261108, FoxTentTalk_DestructDelete)

/* func_ov052_02261128 (vtable slot 0x00): the destructor of the scene class it derives from. */
FoxTentTalk *FoxTentTalk_Destruct(FoxTentTalk *talk)
{
    talk->base.vtable = data_ov052_02261eb0;
    Obj020d9ff8_DestructBody(talk);
    return talk;
}
CLEAN_AS(func_ov052_02261128, FoxTentTalk_Destruct)

/* func_ov052_02261140: the constructor: a scene of class 0x020d9ff8 given this class's vtable. */
FoxTentTalk *FoxTentTalk_Construct(FoxTentTalk *talk)
{
    Obj020d9ff8_Construct(talk);
    talk->base.vtable = data_ov052_02261eb0;
    return talk;
}
CLEAN_AS(func_ov052_02261140, FoxTentTalk_Construct)

/* func_ov052_02261100 (vtable slot 0x08): the scene base's reset. */
void FoxTentTalk_Reset(FoxTentTalk *talk)
{
    SceneBase_Reset(&talk->base);
}
CLEAN_AS(func_ov052_02261100, FoxTentTalk_Reset)

/* func_ov052_022610d4: the scene reset through its vtable slot 0x08 and given its owner; the
 * item 0x34a8 not looked for yet and the membership not declined. */
void FoxTentTalk_Begin(FoxTentTalk *talk, FoxTent *owner)
{
    u32 vtable = *(const u32 *) (const void *) talk;
    u32 code = *(const u32 *) (uintptr_t) (vtable + FOX_TENT_TALK_SLOT_RESET);
    ((void (*)(FoxTentTalk *))(uintptr_t) code)(talk);
    talk->owner = owner;
    talk->card_slot = FOX_TENT_TALK_CARD_UNKNOWN;
    talk->declined = 0;
}
CLEAN_AS(func_ov052_022610d4, FoxTentTalk_Begin)

/* func_ov052_022610c4: what the next talk starts with. */
u32 FoxTentTalk_Sequence(FoxTentTalk *talk)
{
    return talk->sequence;
}
CLEAN_AS(func_ov052_022610c4, FoxTentTalk_Sequence)

/* func_ov052_022610cc */
void FoxTentTalk_SetSequence(FoxTentTalk *talk, u32 sequence)
{
    talk->sequence = sequence;
}
CLEAN_AS(func_ov052_022610cc, FoxTentTalk_SetSequence)

/* ---- Picking a variant */

/* func_ov052_02261158: the place of one of the zero bytes among the `count` of `used`, at random
 * (MainRandom_Below of their number); 0 when there is none. */
int FoxTent_PickUnused(int unused, const u8 *used, int count)
{
    int left = (int) MainRandom_Below(FoxTent_CountUnused(unused, used, count));
    for (int i = 0; i < count; i++) {
        if (used[i] == 0) {
            if (left == 0) {
                return i;
            }
            left--;
        }
    }
    return 0;
}
CLEAN_AS(func_ov052_02261158, FoxTent_PickUnused)

/* func_ov052_0226118c: the number of zero bytes among the `count` of `used`. */
int FoxTent_CountUnused(int unused, const u8 *used, int count)
{
    (void) unused;
    int zeros = 0;
    for (int i = 0; i < count; i++) {
        if (used[i] == 0) {
            zeros++;
        }
    }
    return zeros;
}
CLEAN_AS(func_ov052_0226118c, FoxTent_CountUnused)

/* ---- The line it starts with */

/* func_ov052_02261054: whether the three items of the fox's shop are sold (each read as the
 * sold marker 0x1547). */
int FoxTentTalk_ShopSoldOut(FoxTentTalk *talk)
{
    (void) talk;
    for (int i = 0; i < FOX_SHOP_ITEMS; i++) {
        u16 *item = FoxShop_Item(&data_021f3b30, i, NULL);
        int sold;
        if (ItemCode_HasVariant(item)) {
            u16 marker = FOX_TENT_TALK_SOLD_MARKER;
            int own = ItemCode_VariantItem(item);
            sold = own == ItemCode_VariantItem(&marker);
        } else {
            sold = *item == FOX_TENT_TALK_SOLD_MARKER;
        }
        if (!sold) {
            return 0;
        }
    }
    return 1;
}
CLEAN_AS(func_ov052_02261054, FoxTentTalk_ShopSoldOut)

/* The last sale told, when there is one: its item's name in slot 0 and the buyer's name in slot
 * 1, sequence 8 when the current player is not the buyer, else 9 (the current player's name).
 * Whether there was one. */
static int fox_tent_talk_tell_last_sale(FoxTentTalk *talk, u8 *record)
{
    LastSale *sale = &data_021f3aec;
    u16 item;

    if (!PlayerId_IsSet(LastSale_Buyer(sale))) {
        return 0;
    }
    LastSale_GetItem(&item, sale);
    if (fox_tent_talk_no_item(&item)) {
        return 0;
    }
    u16 named;
    LastSale_GetItem(&named, sale);
    SceneBase_PutItemName(&talk->base, (int) (uintptr_t) &named, FOX_TENT_TALK_SLOT_LAST_ITEM, FOX_TENT_TALK_NAME_KIND);
    const DesignCreator *own = PlayerRecord_Player(PlayerRecords_Current());
    const DesignCreator *buyer = LastSale_Buyer(sale);
    if (!fox_tent_talk_same_player(buyer, own)) {
        SceneBase_PutNameAt10(&talk->base, LastSale_Buyer(sale), FOX_TENT_TALK_SLOT_BUYER);
        talk->sequence = FOX_TENT_TALK_LAST_SALE_OTHER;
    } else {
        SceneBase_PutNameAt10(&talk->base, PlayerRecord_Player(record), FOX_TENT_TALK_SLOT_BUYER);
        talk->sequence = FOX_TENT_TALK_LAST_SALE_OWN;
    }
    return 1;
}

/* func_ov052_02260c1c (vtable slot 0x78, the line to say), of "sp_npc_fox":
 * - closing (sequence 12): its line, and nothing else;
 * - else, unless the talk is at the greeting or the exit (0 to 2), when the player faces no item
 *   and is a member (the current player's flag 0xc), the sequence is chosen anew: the item
 *   0x34a8 is looked for in the pockets once (unlinked); with it, 5; else the shop sold out, 6;
 *   else the first talk today (setting the daily bit 1), 7; else the last sale, 8 or 9 (see
 *   fox_tent_talk_tell_last_sale); else 10;
 * - then the sequence's line (none past 12); for a member, the plain talk (10) is one of four
 *   lines at random, and an item faced is offered: its name in slot 1 and twice its price in
 *   slot 2, with line 0x1d when it was offered before (among FoxTent.told), else one of the
 *   five offers not said yet (0x1e + n), the item noted among the told ones.
 * QUIRK: the item is noted in the last free place of the three told ones, or in the first when
 * none is free; and it is noted again whenever the five offers have all been said. */
void FoxTentTalk_Line(FoxTentTalk *talk, FoxTentTalkStart *out)
{
    u8 *record = PlayerRecords_Current();
    FoxTent *fox;

    if (talk->sequence == FOX_TENT_TALK_CLOSING) {
        out->message = data_ov052_02261be0[talk->sequence].message;
        out->name = data_ov052_02261be0[talk->sequence].name;
        return;
    }
    if (talk->sequence != FOX_TENT_TALK_GREETING && talk->sequence != FOX_TENT_TALK_EXIT &&
        talk->sequence != FOX_TENT_TALK_EXIT_AFTER_SALE) {
        fox = talk->owner;
        if (fox_tent_talk_no_item(&fox->item) && PlayerRecord_TestFlag(record, FOX_TENT_TALK_MEMBER_FLAG)) {
            if (!Session_IsLinked(data_020ccf94) && talk->card_slot == FOX_TENT_TALK_CARD_UNKNOWN) {
                u16 asked = FOX_TENT_TALK_ASKED_ITEM;
                talk->card_slot = CurrentPockets_FindItem(&asked);
            }
            if (talk->card_slot >= 0) {
                talk->sequence = FOX_TENT_TALK_ASK_ITEM;
            } else if (FoxTentTalk_ShopSoldOut(talk)) {
                talk->sequence = FOX_TENT_TALK_SOLD_OUT;
            } else if (TalkChecks_TestSetDailyBit(FOX_TENT_TALK_DAILY_BIT, 1) == 0) {
                talk->sequence = FOX_TENT_TALK_FIRST_TODAY;
            } else if (!fox_tent_talk_tell_last_sale(talk, record)) {
                talk->sequence = FOX_TENT_TALK_PLAIN;
            }
        }
    }

    if (talk->sequence >= FOX_TENT_TALK_SEQUENCES) {
        return;
    }
    out->message = data_ov052_02261be0[talk->sequence].message;
    if (PlayerRecord_TestFlag(record, FOX_TENT_TALK_MEMBER_FLAG)) {
        if (talk->sequence == FOX_TENT_TALK_PLAIN) {
            out->message = (u8) (MainRandom_Below(FOX_TENT_TALK_PLAIN_LINES) + FOX_TENT_TALK_LINE_PLAIN);
            if (out->message == FOX_TENT_TALK_LINE_PLAIN_4) {
                out->message = FOX_TENT_TALK_LINE_PLAIN_4_INSTEAD;
            }
        }
        fox = talk->owner;
        if (!fox_tent_talk_no_item(&fox->item)) {
            int free_place = 0;
            talk->price = ItemTraits_Price(&fox->item) * 2;
            SceneBase_PutItemName(&talk->base, (int) (uintptr_t) &fox->item, FOX_TENT_TALK_SLOT_ITEM, FOX_TENT_TALK_NAME_KIND);
            SceneBase_PutValue(&talk->base, talk->price, FOX_TENT_TALK_SLOT_PRICE, FOX_TENT_TALK_PRICE_FORMAT, 0, 0);
            for (int i = 0; i < FOX_TENT_TOLD_ITEMS; i++) {
                if (fox_tent_talk_same_item(&fox->item, &fox->told[i])) {
                    out->message = FOX_TENT_TALK_LINE_TOLD;
                    break;
                }
                if (fox_tent_talk_no_item(&fox->told[i])) {
                    free_place = i;
                }
            }
            if (out->message != FOX_TENT_TALK_LINE_TOLD) {
                int variant = fox_tent_talk_pick_variant(fox, fox->offer_used, &fox->told[free_place], &fox->item);
                out->message = (u8) (variant + FOX_TENT_TALK_LINE_ITEM_OFFERS);
            }
        }
    }
    out->name = data_ov052_02261be0[talk->sequence].name;
}
CLEAN_AS(func_ov052_02260c1c, FoxTentTalk_Line)

/* ---- The player's answers */

/* func_ov052_0226095c (vtable slot 0x18, the player's answer to the line shown), the answer
 * picked being 0 for the first choice:
 * - 0x2c (the item 0x34a8 asked for), 0: the pocket it was found in emptied (when it was) and
 *   the scene's motion 14 with the item; line 0x2e;
 * - 7 and 0x12 (the membership offered), not 0: line 0xa when the player cannot pay 3,000 bells,
 *   else 8, or 0xc once declined;
 * - 9: declined; 0: line 0xc;
 * - 0x1d to 0x22 (an item offered), 0: with the price at hand and a free pocket, one of the five
 *   thanks not said yet (0x24 + n); without a free pocket 0x2a; without the price 0x29. Unless
 *   thanked, the player faces no item any more.
 * The line, when there is one, is shown. */
void FoxTentTalk_OnAnswer(FoxTentTalk *talk)
{
    int answer = (int) fox_tent_talk_answer(talk);
    int line = FOX_TENT_TALK_NO_LINE;
    FoxTent *fox;

    switch (fox_tent_talk_shown(talk)) {
        case FOX_TENT_TALK_LINE_ASK_ITEM:
            if (answer == 0) {
                if (talk->card_slot >= 0) {
                    CurrentPockets_Empty(talk->card_slot);
                    u16 asked = FOX_TENT_TALK_ASKED_ITEM;
                    SceneCommand_RequestMotion14(fox_tent_talk_scene(talk), &asked, 0, FOX_TENT_TALK_MOTION_B, 0);
                }
                line = FOX_TENT_TALK_LINE_ITEM_TAKEN;
            }
            break;
        case FOX_TENT_TALK_LINE_OFFER:
        case FOX_TENT_TALK_LINE_OFFER_AGAIN:
            if (answer != 0) {
                if (!SceneBells_CanPay((int) (uintptr_t) talk->owner, FOX_TENT_TALK_MEMBERSHIP)) {
                    line = FOX_TENT_TALK_LINE_CANNOT_JOIN;
                } else if (talk->declined == 0) {
                    line = FOX_TENT_TALK_LINE_JOIN;
                } else {
                    line = FOX_TENT_TALK_LINE_NOT_JOINING;
                }
            }
            break;
        case FOX_TENT_TALK_LINE_DECLINED:
            talk->declined = 1;
            if (answer == 0) {
                line = FOX_TENT_TALK_LINE_NOT_JOINING;
            }
            break;
        case FOX_TENT_TALK_LINE_TOLD:
        case FOX_TENT_TALK_LINE_ITEM_OFFERS:
        case FOX_TENT_TALK_LINE_ITEM_OFFERS + 1:
        case FOX_TENT_TALK_LINE_ITEM_OFFERS + 2:
        case FOX_TENT_TALK_LINE_ITEM_OFFERS + 3:
        case FOX_TENT_TALK_LINE_ITEM_OFFERS_LAST:
            if (answer == 0) {
                if (SceneBells_CanPay((int) (uintptr_t) talk->owner, talk->price)) {
                    if (CurrentPockets_FreeSlot() >= 0) {
                        fox = talk->owner;
                        int variant = fox_tent_talk_pick_variant(fox, fox->thanks_used, NULL, NULL);
                        line = (u8) (variant + FOX_TENT_TALK_LINE_THANKS);
                        break;
                    }
                    line = FOX_TENT_TALK_LINE_NO_ROOM;
                } else {
                    line = FOX_TENT_TALK_LINE_CANNOT_PAY;
                }
            }
            talk->owner->item = FOX_TENT_TALK_NO_ITEM;
            break;
        default:
            break;
    }
    if (line != FOX_TENT_TALK_NO_LINE) {
        fox_tent_talk_say(talk, line);
    }
}
CLEAN_AS(func_ov052_0226095c, FoxTentTalk_OnAnswer)

/* ---- The end of a line */

/* func_ov052_022608b4: the item faced sold: its price out of the current player's pockets, the
 * item into them, taken from the fox's shop at its tile (kind 0xf), and the last sale noted (the
 * current player and the item); the price in slot 2. The player faces no item any more and
 * something was sold. */
void FoxTentTalk_Sell(FoxTentTalk *talk)
{
    FoxTent *fox = talk->owner;
    LastSale *sale = &data_021f3aec;

    SceneBells_Take((int) (uintptr_t) fox, talk->price);
    CurrentPockets_Give(&fox->item, 0);
    Shops_TakeFromListB(fox->item_x, fox->item_z, 0xf);
    LastSale_SetBuyer(sale, PlayerRecord_Player(PlayerRecords_Current()));
    LastSale_SetItem(sale, &fox->item);
    SceneBase_PutValue(&talk->base, talk->price, FOX_TENT_TALK_SLOT_PRICE, FOX_TENT_TALK_PRICE_FORMAT, 0, 0);
    fox->item = FOX_TENT_TALK_NO_ITEM;
    fox->sold = 1;
}
CLEAN_AS(func_ov052_022608b4, FoxTentTalk_Sell)

/* func_ov052_02260ae0 (vtable slot 0x14, a line shown to its end):
 * - 0x2e (the item 0x34a8 taken): the scene's motion 13 with the item 0x36fc, which goes into
 *   the pockets; line 0x2f; then as 0x2d;
 * - 0x2d: the item 0x34a8 is not asked for again;
 * - 6 (the greeting): the next talk offers the membership (3) to a player without flag 0xc, else
 *   is the plain talk (10);
 * - 7 (the offer): the next offers it again (4);
 * - 0x10 (joined): the scene's motion 14 with the card 0x149d, the player faces no item; line
 *   0x11; 3,000 bells out of the pockets, the next talk is that of the first today (7), the
 *   current player becomes a member (flag 0xc) and the daily bit 1 is set;
 * - 0x24 to 0x28 (thanks): the item is sold (FoxTentTalk_Sell).
 * The line, when there is one, is shown. */
void FoxTentTalk_OnLineEnd(FoxTentTalk *talk)
{
    int line = FOX_TENT_TALK_NO_LINE;
    u8 *record = PlayerRecords_Current();

    switch (fox_tent_talk_shown(talk)) {
        case FOX_TENT_TALK_LINE_ITEM_TAKEN: {
            u16 shown_item = FOX_TENT_TALK_GIVEN_ITEM;
            SceneCommand_RequestMotion13(fox_tent_talk_scene(talk), &shown_item, 0, FOX_TENT_TALK_MOTION_B, 0);
            u16 given = FOX_TENT_TALK_GIVEN_ITEM;
            CurrentPockets_Give(&given, 0);
            line = FOX_TENT_TALK_LINE_ITEM_GIVEN;
            talk->card_slot = FOX_TENT_TALK_CARD_DONE;
            break;
        }
        case FOX_TENT_TALK_LINE_ITEM_KEPT:
            talk->card_slot = FOX_TENT_TALK_CARD_DONE;
            break;
        case FOX_TENT_TALK_LINE_GREETING:
            if (PlayerRecord_TestFlag(record, FOX_TENT_TALK_MEMBER_FLAG) == 0) {
                FoxTentTalk_SetSequence(talk, FOX_TENT_TALK_OFFER_MEMBERSHIP);
            } else {
                FoxTentTalk_SetSequence(talk, FOX_TENT_TALK_PLAIN);
            }
            break;
        case FOX_TENT_TALK_LINE_OFFER:
            FoxTentTalk_SetSequence(talk, FOX_TENT_TALK_OFFER_AGAIN);
            break;
        case FOX_TENT_TALK_LINE_JOINED: {
            u16 card = FOX_TENT_TALK_CARD;
            SceneCommand_RequestMotion14(fox_tent_talk_scene(talk), &card, 0, FOX_TENT_TALK_MOTION_B, 0);
            talk->owner->item = FOX_TENT_TALK_NO_ITEM;
            line = FOX_TENT_TALK_LINE_CARD;
            SceneBells_Take((int) (uintptr_t) talk->owner, FOX_TENT_TALK_MEMBERSHIP);
            FoxTentTalk_SetSequence(talk, FOX_TENT_TALK_FIRST_TODAY);
            PlayerRecord_SetFlag(record, FOX_TENT_TALK_MEMBER_FLAG);
            TalkChecks_TestSetDailyBit(FOX_TENT_TALK_DAILY_BIT, 1);
            break;
        }
        case FOX_TENT_TALK_LINE_THANKS:
        case FOX_TENT_TALK_LINE_THANKS + 1:
        case FOX_TENT_TALK_LINE_THANKS + 2:
        case FOX_TENT_TALK_LINE_THANKS + 3:
        case FOX_TENT_TALK_LINE_THANKS_LAST:
            FoxTentTalk_Sell(talk);
            break;
        default:
            break;
    }
    if (line != FOX_TENT_TALK_NO_LINE) {
        fox_tent_talk_say(talk, line);
    }
}
CLEAN_AS(func_ov052_02260ae0, FoxTentTalk_OnLineEnd)
