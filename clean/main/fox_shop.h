/* The fox's shop (data_021f3b30, at 0x17388 of the state block data_021dc7a8): the three items
 * the fox of overlay 3 (ov003/fox.c) sells and its password, shared between linked players as
 * shops.h's list B.
 *
 * Items: three item codes (0xfff1 for none) with a bit each in `sold` (FoxShop_Item gives a
 * sold one as the marker data_021f49f4). FoxShop_Stock draws them: the first from the item
 * group 0x26 or 0x27, the other two from group 5 or 0, with chances that grow with the edge
 * counts of the player's house's five rooms (room_score.c: RoomScore_HouseHighX, _HouseLowX and
 * _HouseHighZ), then shuffled.
 *
 * Password: one of 32, each used once until all have been (`used`); `current` is the one in
 * force (-1 for none). Its texts are 2n and 2n + 1 of "st_password": the fox's talk loads the
 * first (FoxPassword_LoadTalkText), the letter that tells the players loads the second
 * (FoxPassword_LoadLetterText). Picking one restocks the items. The letters go out once per
 * password (FoxShop_SendLetters, flag 8 of the state block says they went), to each player of
 * the town whose record has flag 0xc.
 *
 * Each of the four players of the town has a mark in `players` (FoxShop_MarkCurrentPlayer);
 * a player from another town gets one mark for all, kept outside the shop (data_021f49e8).
 *
 * FoxShopText is the text object (vtable data_020e4170) the password's texts load into. */
#ifndef CLEAN_MAIN_FOX_SHOP_H
#define CLEAN_MAIN_FOX_SHOP_H

#include "types.h"

#define FOX_SHOP_ITEMS 3
#define FOX_PASSWORDS 32
#define FOX_PASSWORD_NONE (-1)

typedef struct FoxPassword {
    u32 used;   /* a bit for each password used since the last time all were */
    s8 current; /* 0x04: the password in force, FOX_PASSWORD_NONE for none */
    u8 players; /* 0x05: a bit for each of the four players of the town */
    u8 unk_06[2];
} FoxPassword;

typedef struct FoxShop {
    u16 items[FOX_SHOP_ITEMS];
    u8 unk_06[2];
    FoxPassword password; /* 0x08 */
    u8 sold[1];           /* 0x10: a bit for each item */
} FoxShop;

/* The text object: a base text of 0x34 bytes whose vtable is replaced. */
typedef struct FoxShopText {
    const void *vtable;
    u8 unk_04[0x30];
} FoxShopText;

int FoxShop_FindItem(FoxShop *shop, u16 *item);
u16 *FoxShop_Item(FoxShop *shop, int index, u16 *out);
int FoxShop_TakeItem(FoxShop *shop, u16 *item);
int FoxShop_MarkSold(FoxShop *shop, int index);
void FoxShop_Stock(u16 *items);
void FoxShop_SendLetters(void);
int FoxShop_MarkCurrentPlayer(void);
int FoxShop_CurrentPlayerMarked(void);
void FoxShop_ClearPlayer(int player);
int FoxShop_Has5012AfterSix(void);
FoxPassword *FoxShop_Password(FoxShop *shop);
void FoxShop_Init(FoxShop *shop);
void FoxShop_ClearItems(FoxShop *shop);
void FoxShop_Reset(FoxShop *shop);
FoxShop *FoxShop_Destruct(FoxShop *shop);
FoxShop *FoxShop_Construct(FoxShop *shop);

void FoxPassword_SetUsed(FoxPassword *password, int index);
unsigned int FoxPassword_IsUsed(FoxPassword *password, unsigned int index);
int FoxPassword_CountUnused(FoxPassword *password);
int FoxPassword_MarkVisitor(FoxPassword *password);
u8 FoxPassword_VisitorMarked(void);
void FoxPassword_ClearVisitor(void);
void FoxPassword_ClearPlayer(FoxPassword *password, int player);
void FoxPassword_MarkPlayer(FoxPassword *password, int player);
int FoxPassword_PlayerMarked(FoxPassword *password, int player);
void FoxPassword_ClearPlayers(FoxPassword *password);
void FoxPassword_SetLettersSent(FoxPassword *password);
int FoxPassword_LettersDue(FoxPassword *password);
int FoxPassword_LoadLetterText(FoxPassword *password, FoxShopText *text);
int FoxPassword_LetterTextNumber(FoxPassword *password);
int FoxPassword_LoadTalkText(FoxPassword *password, FoxShopText *text);
int FoxPassword_End(FoxPassword *password);
int FoxPassword_Pick(FoxPassword *password);
void FoxPassword_Reset(FoxPassword *password);
void FoxPassword_Destruct(FoxPassword *password);
FoxPassword *FoxPassword_Construct(FoxPassword *password);

int FoxShopText_Capacity(void);
u8 *FoxShopText_Buffer(FoxShopText *text);
FoxShopText *FoxShopText_DestructFree(FoxShopText *text);
FoxShopText *FoxShopText_Destruct(FoxShopText *text);
FoxShopText *FoxShopText_Construct(FoxShopText *text);

#endif
