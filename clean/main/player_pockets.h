/* A player's pockets (0xa70 bytes, at 0x11a8 of the player's record, func_02099734): ten letters,
 * the player's letter defaults, 15 item slots with a two-bit state each, and the wallet.
 *
 * The wallet holds at most 99,999 bells. Bells beyond that can go into bell bags (items
 * 0x1492-0x14fd, each worth the bells func_0204c878 gives; 0x14fd is the biggest) in the item
 * slots, and a payment the wallet cannot cover can be taken from the bags, smallest first. Only
 * bags whose slot state is 0 count as money. */
#ifndef CLEAN_MAIN_PLAYER_POCKETS_H
#define CLEAN_MAIN_PLAYER_POCKETS_H

#include "mail.h"
#include "types.h"

#define PLAYER_POCKETS_LETTERS 10
#define PLAYER_POCKETS_SLOTS 15
#define PLAYER_POCKETS_LETTER_DEFAULTS_SIZE 0x4a
#define PLAYER_POCKETS_WALLET_MAX 99999

/* The item code of an empty slot. */
#define PLAYER_POCKETS_NO_ITEM 0xfff1
/* The bell bags, smallest to biggest. */
#define PLAYER_POCKETS_BAG_FIRST 0x1492
#define PLAYER_POCKETS_BAG_LAST 0x14fd

typedef struct PlayerPockets {
    MailLetter letters[PLAYER_POCKETS_LETTERS];              /* 0x000 */
    u8 letter_defaults[PLAYER_POCKETS_LETTER_DEFAULTS_SIZE]; /* 0xa00, set up by func_02065cc8 */
    u16 items[PLAYER_POCKETS_SLOTS];                         /* 0xa4a */
    int bells;                                               /* 0xa68, the wallet */
    u32 states;                                              /* 0xa6c, two bits for each slot */
} PlayerPockets;

/* Whether `use_bags` lets bells beyond the wallet's room go into bags, or a payment be taken
 * from them. */
#define PLAYER_POCKETS_USE_BAGS 1

void PlayerPockets_AddBells(PlayerPockets *pockets, int amount, int use_bags);
int PlayerPockets_CanChangeBells(PlayerPockets *pockets, int amount, int with_bags, int extra_bags);
void PlayerPockets_SetBells(PlayerPockets *pockets, int bells, int use_bags);
int PlayerPockets_PayFromBags(PlayerPockets *pockets, int owed);
u32 PlayerPockets_PutInBags(PlayerPockets *pockets, u32 bells);
int PlayerPockets_PlaceForBag(PlayerPockets *pockets);
int PlayerPockets_SmallestBag(PlayerPockets *pockets, int with_biggest);
int PlayerPockets_BellsRoom(PlayerPockets *pockets, int with_bags, int extra_bags);
int PlayerPockets_Bells(PlayerPockets *pockets, int with_bags);
int PlayerPockets_BagsRoom(PlayerPockets *pockets, int extra_bags);
int PlayerPockets_BagsBells(PlayerPockets *pockets);
u8 *PlayerPockets_LetterDefaults(PlayerPockets *pockets);
MailLetter *PlayerPockets_FreeLetter(PlayerPockets *pockets);
int PlayerPockets_FreeLetterIndex(PlayerPockets *pockets);
MailLetter *PlayerPockets_Letter(PlayerPockets *pockets, int index);
int PlayerPockets_IsLetterIndex(int index);
int PlayerPockets_SlotStateIsZero(PlayerPockets *pockets, int slot);
int PlayerPockets_SlotState(PlayerPockets *pockets, int slot);
int PlayerPockets_FreeSlot(PlayerPockets *pockets);
void PlayerPockets_SetSlotState(PlayerPockets *pockets, u32 slot, u32 state);
int PlayerPockets_SetSlot(PlayerPockets *pockets, const u16 *item, int slot, int state);
u16 *PlayerPockets_Slot(PlayerPockets *pockets, int slot);
int PlayerPockets_IsSlot(int slot);
void PlayerPockets_Init(PlayerPockets *pockets);

#endif
