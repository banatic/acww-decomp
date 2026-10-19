/* The fox's shop and its password (fox_shop.h). */
#include "fox_shop.h"

#include "autoload_2/heap.h"
#include "clean.h"
#include "main/acre_map.h"
#include "main/calendar.h"
#include "main/date_time.h"
#include "main/mail.h"
#include "main/session.h"
#include "main/state_block.h"
#include "acre_record.h"
#include "acre_tile.h"
#include "item_code.h"
#include "item_lists.h"
#include "last_sale.h"
#include "letter.h"
#include "mail_text.h"
#include "main_random.h"
#include "message_reader.h"
#include "player_id.h"
#include "player_record.h"
#include "player_records.h"
#include "room_score.h"
#include "shop_stock.h"
#include "text_base.h"

static_assert(offsetof(FoxShop, password) == 0x08, "password");
static_assert(offsetof(FoxShop, sold) == 0x10, "sold");
static_assert(offsetof(FoxPassword, current) == 0x04, "current");
static_assert(offsetof(FoxPassword, players) == 0x05, "players");
static_assert(sizeof(FoxShopText) == 0x34, "text");

/* Flag 8 of the state block: the letters of the current password went out. */
#define FOX_LETTERS_SENT_FLAG 8
/* The flag of a player's record that lets the letter come to that player. */
#define FOX_LETTER_PLAYER_FLAG 0xc
/* Overlay 4's slot of a text variable func_0203d7c4 fills. */
#define FOX_TEXT_SLOT 2
#define FOX_LETTER_MESSAGES 3
/* The value func_02094ffc gives for a name of another town. */
#define FOX_OTHER_TOWN 1
/* The item a town map is searched for (FoxShop_Has5012AfterSix), and from which hour. */
#define FOX_TOWN_ITEM 0x5012
#define FOX_FROM_HOUR 6
#define FOX_TEXT_CAPACITY 34
#define FOX_TEXT_BUFFER 18

extern NetSession *data_020ccf94;
extern u32 data_021dc7a8[]; /* the state block (state_block.h) */
extern u8 data_021dc7bc[];  /* the four players' records */
extern FoxShop data_021f3b30;
/* The mark of a player from another town. */
extern u8 data_021f49e8;
/* What a sold item reads as. */
extern u16 data_021f49f4;
extern u16 data_021f3aec[];
/* The six orders the three items can be put in. */
extern const u8 data_020d1e48[6 * FOX_SHOP_ITEMS];
/* "sp_npc_foxmail", the letters' sender, and the two values func_02066024 takes with it. */
extern const char data_020e419c[];
extern const u8 data_020e4160[];
extern const u8 data_020e4164[];
/* "st_password" */
extern const char data_020e41ac[];
/* The vtable of FoxShopText. */
extern const u8 data_020e4170[];
/* The item FoxShop_Has5012AfterSix looks for, a static object made on its first call: its
 * guard (bit 0) and its record for __register_global_object. */
extern u16 data_021f49f8;
extern u32 data_021f49fc;
extern u8 data_021f4a14[];

/* An item lot: func_02063ccc constructs it, func_020638d4 draws an item of it, func_02063cc8
 * destroys it. */
typedef struct FoxItemLot {
    int unk_00;
    int group;
} FoxItemLot;

extern void __register_global_object(void *object, void *destruct, void *record);
extern void func_020051b0(void *object); /* a destructor that does nothing */
extern void func_02034ce0(void *item);   /* an item's constructor: 0xfff1 */
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));

/* Whether two item codes are the same: by func_0204bc64's number for the kinds that have
 * one, else by code. */
static int fox_same_item(u16 *item, u16 *other)
{
    if (ItemCode_HasVariant(item) != 0) {
        return ItemCode_VariantItem(item) == ItemCode_VariantItem(other);
    }
    return *item == *other;
}

/* func_020adf8c: the place of `item` among the items, or -1. */
int FoxShop_FindItem(FoxShop *shop, u16 *item)
{
    return ShopStock_Find(item, shop->items, shop->sold, FOX_SHOP_ITEMS);
}
CLEAN_AS(func_020adf8c, FoxShop_FindItem)

/* func_020adfa4: item `index` (data_021f49f4 when sold); its code also in `out` unless NULL. */
u16 *FoxShop_Item(FoxShop *shop, int index, u16 *out)
{
    return ShopStock_Item(index, shop->items, shop->sold, FOX_SHOP_ITEMS, out);
}
CLEAN_AS(func_020adfa4, FoxShop_Item)

/* func_020adfc0: marks sold the first item that is `*item`. Returns whether one was marked.
 * QUIRK: a sold item reads as data_021f49f4, so that marker matches the first sold item, which
 * stays sold (0). */
int FoxShop_TakeItem(FoxShop *shop, u16 *item)
{
    for (unsigned i = 0; i < FOX_SHOP_ITEMS; i++) {
        u16 *here = FoxShop_Item(shop, (int) i, NULL);
        if (fox_same_item(here, item)) {
            return FoxShop_MarkSold(shop, (int) i);
        }
    }
    return 0;
}
CLEAN_AS(func_020adfc0, FoxShop_TakeItem)

/* func_020ae02c: marks item `index` sold; whether it was not yet. */
int FoxShop_MarkSold(FoxShop *shop, int index)
{
    return ShopStock_MarkSold(index, FOX_SHOP_ITEMS, shop->sold);
}
CLEAN_AS(func_020ae02c, FoxShop_MarkSold)

/* One item drawn from `group` into `*out`. */
static void fox_draw(u16 *out, int group)
{
    FoxItemLot lot;
    u16 item;
    ItemList_Construct((ItemList *) &lot, 0, group);
    ItemLists_Draw(&item, (ItemList *) &lot, 0, 0, 0, 1, 0);
    *out = item;
    ItemList_Destruct(&lot);
}

/* func_020ae03c: new items, none sold. The first is of group 0x26 with a chance of 50% plus a
 * tenth of the edges of the house's five rooms summed over its three sides (RoomScore_HouseEdges),
 * else of group 0x27; each other one of group 5 with a chance of 50% plus a tenth of two of those
 * sums, else of group 0. Then they are put in one of six orders at random.
 * QUIRK: the second chance leaves out the low-x sum (RoomScore_HouseLowX) the first one adds.
 * REQUIRES: `items` is a shop (data_021f3b30): the sold bits after it are cleared too. */
void FoxShop_Stock(u16 *items)
{
    FoxShop_ClearItems((FoxShop *) items);

    unsigned chance = (unsigned) RoomScore_HouseEdges() / 10 + 50;
    fox_draw(&items[0], MainRandom_Below(100) < chance ? 0x26 : 0x27);

    int first = RoomScore_HouseHighX();
    int second = RoomScore_HouseHighZ();
    chance = (unsigned) ((first + second) / 10 + 50);
    for (unsigned i = 1; i < FOX_SHOP_ITEMS; i++) {
        fox_draw(&items[i], MainRandom_Below(100) < chance ? 5 : 0);
    }

    u16 drawn[FOX_SHOP_ITEMS];
    for (unsigned i = 0; i < FOX_SHOP_ITEMS; i++) {
        drawn[i] = items[i];
    }
    const u8 *order = &data_020d1e48[FOX_SHOP_ITEMS * MainRandom_Below(6)];
    for (unsigned i = 0; i < FOX_SHOP_ITEMS; i++) {
        items[i] = drawn[order[i]];
    }
}
CLEAN_AS(func_020ae03c, FoxShop_Stock)

/* func_020ae190: picks a password if there is none; if its letters have not gone out and the
 * system is not linked, sends one to each player of the town whose record has flag 0xc (one of
 * three messages of "sp_npc_foxmail" at random, with the password's letter text), held at the
 * post office when the mailbox is full, and marks the letters sent. */
void FoxShop_SendLetters(void)
{
    FoxPassword_Pick(FoxShop_Password(&data_021f3b30));
    if (FoxPassword_LettersDue(FoxShop_Password(&data_021f3b30)) == 0) {
        return;
    }
    if (Session_IsLinked(data_020ccf94) != 0) {
        return;
    }

    Letter letter;
    FoxShopText text;
    u8 message;
    Letter_Construct(&letter);
    message = (u8) MainRandom_Below(FOX_LETTER_MESSAGES);
    FoxShopText_Construct(&text);
    FoxPassword_LoadLetterText(FoxShop_Password(&data_021f3b30), &text);
    MailText_SetPartText(FOX_TEXT_SLOT, &text);

    for (int i = 0; i < MAIL_PLAYERS; i++) {
        void *player = PlayerRecords_TownRecord(data_021dc7bc, i);
        if (player == NULL || PlayerRecord_HasPlayer(player) == 0 ||
            PlayerRecord_TestFlag(player, FOX_LETTER_PLAYER_FLAG) == 0) {
            continue;
        }
        Letter_WriteSpecialToPlayer(&letter, &message, data_020e419c, data_020e4160, data_020e4164,
                                    PlayerRecord_Player(player));
        if (Mail_Post(&letter) == 0) {
            Mail_HoldAtPostOffice(&letter, 0);
        }
    }

    FoxPassword_SetLettersSent(FoxShop_Password(&data_021f3b30));
    FoxShopText_Destruct(&text);
    Letter_Destruct(&letter);
}
CLEAN_AS(func_020ae190, FoxShop_SendLetters)

/* func_020ae270: marks this system's player: a player from another town with the visitors'
 * mark (when there is a password), one of the town with the player's own. Returns 0 when there
 * is no player, else whether a mark was set (always for a player of the town). */
int FoxShop_MarkCurrentPlayer(void)
{
    void *player = PlayerRecords_Current();
    if (player == NULL) {
        return 0;
    }
    void *name = PlayerRecord_Player(player);
    if (PlayerId_WhichTown(name) == FOX_OTHER_TOWN) {
        return FoxPassword_MarkVisitor(FoxShop_Password(&data_021f3b30));
    }
    int index = (u8) (PlayerRecords_FindIndex(data_021dc7bc, name) & 3);
    FoxPassword_MarkPlayer(FoxShop_Password(&data_021f3b30), index);
    return 1;
}
CLEAN_AS(func_020ae270, FoxShop_MarkCurrentPlayer)

/* func_020ae2c4: whether this system's player has the mark FoxShop_MarkCurrentPlayer sets. */
int FoxShop_CurrentPlayerMarked(void)
{
    void *player = PlayerRecords_Current();
    if (player == NULL) {
        return 0;
    }
    void *name = PlayerRecord_Player(player);
    if (PlayerId_WhichTown(name) == FOX_OTHER_TOWN) {
        return FoxPassword_VisitorMarked();
    }
    int index = (u8) (PlayerRecords_FindIndex(data_021dc7bc, name) & 3);
    return FoxPassword_PlayerMarked(FoxShop_Password(&data_021f3b30), index);
}
CLEAN_AS(func_020ae2c4, FoxShop_CurrentPlayerMarked)

/* func_020ae310 */
void FoxShop_ClearPlayer(int player)
{
    FoxPassword_ClearPlayer(FoxShop_Password(&data_021f3b30), (u8) player);
}
CLEAN_AS(func_020ae310, FoxShop_ClearPlayer)

/* func_020ae32c: whether the town's map has an acre (func_0204f694 with 0x200) holding item
 * 0x5012 and the clock's hour is 6 or later. */
int FoxShop_Has5012AfterSix(void)
{
    unsigned int map = AcreMap_Town();
    if (map == 0) {
        return 0;
    }
    void *cell = AcreTile_FindAcreAnyFlag((AcreMap *) (uintptr_t) map, (void *) (uintptr_t) 0x200);
    if (cell == NULL) {
        return 0;
    }
    if ((data_021f49fc & 1) == 0) {
        data_021f49f8 = FOX_TOWN_ITEM;
        __register_global_object(&data_021f49f8, (void *) func_020051b0, data_021f4a14);
        data_021f49fc |= 1;
    }
    int x;
    int z;
    if (AcreRecord_FindCode(cell, &x, &z, &data_021f49f8, &data_021f49f8, 0) == 0) {
        return 0;
    }
    DateTime now = {0};
    DateTime_Now(&now);
    return now.hour >= FOX_FROM_HOUR;
}
CLEAN_AS(func_020ae32c, FoxShop_Has5012AfterSix)

/* func_020ae3b8 */
FoxPassword *FoxShop_Password(FoxShop *shop)
{
    return &shop->password;
}
CLEAN_AS(func_020ae3b8, FoxShop_Password)

/* func_020ae3bc */
void FoxShop_Init(FoxShop *shop)
{
    FoxShop_Reset(shop);
}
CLEAN_AS(func_020ae3bc, FoxShop_Init)

/* func_020ae3c4: no items, none sold. */
void FoxShop_ClearItems(FoxShop *shop)
{
    ShopStock_Clear(shop->items, shop->sold, FOX_SHOP_ITEMS);
}
CLEAN_AS(func_020ae3c4, FoxShop_ClearItems)

/* func_020ae3d4: no items and no password. */
void FoxShop_Reset(FoxShop *shop)
{
    FoxShop_ClearItems(shop);
    FoxPassword_Reset(&shop->password);
}
CLEAN_AS(func_020ae3d4, FoxShop_Reset)

/* func_020ae3ec: the destructor. */
FoxShop *FoxShop_Destruct(FoxShop *shop)
{
    FoxPassword_Destruct(&shop->password);
    __cxa_vec_cleanup(shop->items, FOX_SHOP_ITEMS, sizeof(u16), func_020051b0);
    return shop;
}
CLEAN_AS(func_020ae3ec, FoxShop_Destruct)

/* func_020ae410: the constructor. */
FoxShop *FoxShop_Construct(FoxShop *shop)
{
    __cxa_vec_ctor(shop->items, FOX_SHOP_ITEMS, sizeof(u16), func_02034ce0, func_020051b0);
    FoxPassword_Construct(&shop->password);
    return shop;
}
CLEAN_AS(func_020ae410, FoxShop_Construct)

/* func_020ae440 */
void FoxPassword_SetUsed(FoxPassword *password, int index)
{
    password->used |= 1u << (index & 31);
}
CLEAN_AS(func_020ae440, FoxPassword_SetUsed)

/* func_020ae458 */
unsigned int FoxPassword_IsUsed(FoxPassword *password, unsigned int index)
{
    return (password->used >> (index & 31)) & 1;
}
CLEAN_AS(func_020ae458, FoxPassword_IsUsed)

/* func_020ae470 */
int FoxPassword_CountUnused(FoxPassword *password)
{
    int count = 0;
    for (unsigned i = 0; i < FOX_PASSWORDS; i++) {
        if (FoxPassword_IsUsed(password, i) == 0) {
            count++;
        }
    }
    return count;
}
CLEAN_AS(func_020ae470, FoxPassword_CountUnused)

/* func_020ae494: when there is a password and this system's player is from another town, sets
 * the visitors' mark. Returns whether it did. */
int FoxPassword_MarkVisitor(FoxPassword *password)
{
    if (password->current != FOX_PASSWORD_NONE &&
        PlayerId_WhichTown(PlayerRecord_Player(PlayerRecords_Current())) == FOX_OTHER_TOWN) {
        data_021f49e8 = 1;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_020ae494, FoxPassword_MarkVisitor)

/* func_020ae4c8: the visitors' mark, 0 when this system's player is not from another town. */
u8 FoxPassword_VisitorMarked(void)
{
    if (PlayerId_WhichTown(PlayerRecord_Player(PlayerRecords_Current())) == FOX_OTHER_TOWN) {
        return data_021f49e8;
    }
    return 0;
}
CLEAN_AS(func_020ae4c8, FoxPassword_VisitorMarked)

/* func_020ae4f0 */
void FoxPassword_ClearVisitor(void)
{
    data_021f49e8 = 0;
}
CLEAN_AS(func_020ae4f0, FoxPassword_ClearVisitor)

/* func_020ae4fc */
void FoxPassword_ClearPlayer(FoxPassword *password, int player)
{
    password->players &= (u8) ~(1u << (player & 3));
}
CLEAN_AS(func_020ae4fc, FoxPassword_ClearPlayer)

/* func_020ae514: marks `player`, when there is a password. */
void FoxPassword_MarkPlayer(FoxPassword *password, int player)
{
    if (password->current != FOX_PASSWORD_NONE) {
        password->players |= (u8) (1u << (player & 3));
    }
}
CLEAN_AS(func_020ae514, FoxPassword_MarkPlayer)

/* func_020ae538: whether `player` is marked; never without a password. */
int FoxPassword_PlayerMarked(FoxPassword *password, int player)
{
    if (password->current == FOX_PASSWORD_NONE) {
        return 0;
    }
    return (password->players >> (player & 3)) & 1;
}
CLEAN_AS(func_020ae538, FoxPassword_PlayerMarked)

/* func_020ae564 */
void FoxPassword_ClearPlayers(FoxPassword *password)
{
    password->players = 0;
}
CLEAN_AS(func_020ae564, FoxPassword_ClearPlayers)

/* func_020ae56c: notes that the letters went out, when there is a password. */
void FoxPassword_SetLettersSent(FoxPassword *password)
{
    if (password->current != FOX_PASSWORD_NONE) {
        StateBlock_SetFlag(data_021dc7a8, FOX_LETTERS_SENT_FLAG);
    }
}
CLEAN_AS(func_020ae56c, FoxPassword_SetLettersSent)

/* func_020ae590: whether there is a password whose letters have not gone out. */
int FoxPassword_LettersDue(FoxPassword *password)
{
    return password->current != FOX_PASSWORD_NONE && StateBlock_TestFlag(data_021dc7a8, FOX_LETTERS_SENT_FLAG) == 0;
}
CLEAN_AS(func_020ae590, FoxPassword_LettersDue)

/* func_020ae5bc: loads text 2n + 1 of "st_password" into `text`, n the password. Returns 0 when
 * there is none. */
int FoxPassword_LoadLetterText(FoxPassword *password, FoxShopText *text)
{
    if (password->current == FOX_PASSWORD_NONE) {
        return 0;
    }
    u8 number = (u8) (((password->current & 0x1f) << 1) + 1);
    return (int) (uintptr_t) MessageReader_LoadDecoded(text, &number, data_020e41ac);
}
CLEAN_AS(func_020ae5bc, FoxPassword_LoadLetterText)

/* func_020ae5f4: the number of the password's letter text, 0 when there is none; the fox
 * opens its screen with it. */
int FoxPassword_LetterTextNumber(FoxPassword *password)
{
    if (password->current == FOX_PASSWORD_NONE) {
        return 0;
    }
    return (u8) (password->current * 2 + 1);
}
CLEAN_AS(func_020ae5f4, FoxPassword_LetterTextNumber)

/* func_020ae614: loads text 2n of "st_password" into `text`, n the password. Returns 0 when
 * there is none. */
int FoxPassword_LoadTalkText(FoxPassword *password, FoxShopText *text)
{
    if (password->current == FOX_PASSWORD_NONE) {
        return 0;
    }
    u8 number = (u8) ((password->current & 0x1f) << 1);
    return (int) (uintptr_t) MessageReader_LoadDecoded(text, &number, data_020e41ac);
}
CLEAN_AS(func_020ae614, FoxPassword_LoadTalkText)

/* func_020ae64c: no password any more; once all 32 have been used they all can be again. */
int FoxPassword_End(FoxPassword *password)
{
    password->current = FOX_PASSWORD_NONE;
    if (FoxPassword_CountUnused(password) == 0) {
        password->used = 0;
    }
    FoxPassword_ClearPlayers(password);
    StateBlock_ClearFlag(data_021dc7a8, FOX_LETTERS_SENT_FLAG);
    return 1;
}
CLEAN_AS(func_020ae64c, FoxPassword_End)

/* func_020ae67c: when there is no password, one of the unused ones at random, which restocks
 * the shop. Returns whether there is a password.
 * QUIRK: the shop restocked is always data_021f3b30's, whatever password this is. */
int FoxPassword_Pick(FoxPassword *password)
{
    if (password->current != FOX_PASSWORD_NONE) {
        return 1;
    }
    int unused = FoxPassword_CountUnused(password);
    if (unused == 0) {
        return 0;
    }
    int pick = (int) MainRandom_Below(unused);
    int seen = 0;
    for (unsigned i = 0; i < FOX_PASSWORDS; i++) {
        if (FoxPassword_IsUsed(password, i) != 0) {
            continue;
        }
        if (seen == pick) {
            password->current = (s8) i;
            FoxPassword_SetUsed(password, (int) i);
            LastSale_SetUp((LastSale *) data_021f3aec);
            FoxShop_Stock(data_021f3b30.items);
            FoxPassword_ClearPlayers(password);
            StateBlock_ClearFlag(data_021dc7a8, FOX_LETTERS_SENT_FLAG);
            return 1;
        }
        seen++;
    }
    return 0;
}
CLEAN_AS(func_020ae67c, FoxPassword_Pick)

/* func_020ae6fc: no password, none used. */
void FoxPassword_Reset(FoxPassword *password)
{
    password->used = 0;
    password->current = FOX_PASSWORD_NONE;
    FoxPassword_ClearPlayers(password);
    StateBlock_ClearFlag(data_021dc7a8, FOX_LETTERS_SENT_FLAG);
}
CLEAN_AS(func_020ae6fc, FoxPassword_Reset)

/* func_020ae720: the destructor, which does nothing. */
void FoxPassword_Destruct(FoxPassword *password)
{
    (void) password;
}
CLEAN_AS(func_020ae720, FoxPassword_Destruct)

/* func_020ae724: the constructor. */
FoxPassword *FoxPassword_Construct(FoxPassword *password)
{
    FoxPassword_Reset(password);
    return password;
}
CLEAN_AS(func_020ae724, FoxPassword_Construct)

/* func_020ae734: vtable entry 2, the size of the text's buffer. */
int FoxShopText_Capacity(void)
{
    return FOX_TEXT_CAPACITY;
}
CLEAN_AS(func_020ae734, FoxShopText_Capacity)

/* func_020ae738: vtable entry 3, the text's buffer. */
u8 *FoxShopText_Buffer(FoxShopText *text)
{
    return (u8 *) text + FOX_TEXT_BUFFER;
}
CLEAN_AS(func_020ae738, FoxShopText_Buffer)

/* func_020ae73c: vtable entry 1, the destructor that frees the text. */
FoxShopText *FoxShopText_DestructFree(FoxShopText *text)
{
    text->vtable = data_020e4170;
    TextBase_Destruct((TextBase *) text);
    Heap_OperatorDeleteB(text);
    return text;
}
CLEAN_AS(func_020ae73c, FoxShopText_DestructFree)

/* func_020ae75c: vtable entry 0, the destructor. */
FoxShopText *FoxShopText_Destruct(FoxShopText *text)
{
    text->vtable = data_020e4170;
    TextBase_Destruct((TextBase *) text);
    return text;
}
CLEAN_AS(func_020ae75c, FoxShopText_Destruct)

/* func_020ae774: the constructor. */
FoxShopText *FoxShopText_Construct(FoxShopText *text)
{
    TextBase_Construct(text);
    text->vtable = data_020e4170;
    TextBase_Clear(text);
    return text;
}
CLEAN_AS(func_020ae774, FoxShopText_Construct)
