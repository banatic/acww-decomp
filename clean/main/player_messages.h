/* Messages between the players' consoles. A received message is handed to the handler its
 * first byte (its type) selects in the table at data_020df6bc (func_02070760), with the number
 * of the player who sent it; the rest of the message is its payload. The functions here are
 * that dispatch, the handlers of types 0-23 and the short replies some of them send back
 * (PlayerMessages_Send). */
#ifndef CLEAN_MAIN_PLAYER_MESSAGES_H
#define CLEAN_MAIN_PLAYER_MESSAGES_H

#include "types.h"

enum PlayerMessageType {
    PLAYER_MESSAGE_BBS_POST = 0,               /* a post for the bulletin board (Bbs_PostText) */
    PLAYER_MESSAGE_RELEASE_INSECT = 1,         /* the sender lets an insect go (PlayerMessages_ReleaseInsect) */
    PLAYER_MESSAGE_PLACE_FISH = 2,             /* a fish put down from the pockets (PlayerMessages_Place) */
    PLAYER_MESSAGE_LOST_AND_FOUND = 3,         /* the lost and found's list of 30 bytes (data_021f3a68) */
    PLAYER_MESSAGE_RECYCLE_BIN = 4,            /* the recycle bin's list of 30 bytes (data_021f3a86) */
    PLAYER_MESSAGE_THROW_BOTTLE = 5,           /* a bottle thrown at a position (ThrownBottle_SetTarget) */
    PLAYER_MESSAGE_BOTTLE_LETTER = 6,          /* a bottle's letter (0x100 bytes) for data_021ee418 */
    PLAYER_MESSAGE_CLEAR_BOTTLE_LETTER = 7,    /* empty the bottle's letter at data_021f36ec */
    PLAYER_MESSAGE_HOLD_LETTER = 8,            /* a letter to hold at the post office; answered with 9-11 */
    PLAYER_MESSAGE_STORED = 9,                 /* stored, and there is room for more */
    PLAYER_MESSAGE_STORED_FULL = 10,           /* stored, and now there is no room */
    PLAYER_MESSAGE_NOT_STORED = 11,            /* there was no room */
    PLAYER_MESSAGE_TOWN_TUNE = 12,             /* the town tune: 16 notes of four bits */
    PLAYER_MESSAGE_SET_COUNTDOWN = 13,         /* 13-17: countdown 0-4 (0 stops it), answered with 18-22 */
    PLAYER_MESSAGE_COUNTDOWN_SET = 18,         /* 18-22: the countdown (0-4) was set */
    PLAYER_MESSAGE_FREE_HELD_TILE_CHANGE = 23, /* TileChanges_FreeHeld of the payload's byte */
    PLAYER_MESSAGE_NONE = 24,                  /* no reply (func_02070778) */
};

/* The number of types the table at data_020df6bc has a handler for (0-23). */
#define PLAYER_MESSAGE_TYPES 24

/* The countdowns types 13-22 carry: 0 stops the second panel's countdown (CatchPanel_Start with
 * the time of data_020df6a8, CatchPanel_IsStopped tests it). */
#define PLAYER_MESSAGE_COUNTDOWNS 5

/* The message category PlayerMessages_Send sends its replies under. */
#define PLAYER_MESSAGE_CATEGORY 22

void PlayerMessages_FreeHeldTileChange(const u8 *message, int player);
void PlayerMessages_CountdownSet(const u8 *message, int player);
void PlayerMessages_SetCountdown(const u8 *message, int player);
void PlayerMessages_ApplyCountdown(int mode);
void PlayerMessages_TownTune(const void *message, int player);
void PlayerMessages_StoreReply(const u8 *message, int player);
void PlayerMessages_HoldLetter(const u8 *message, int player);
void PlayerMessages_Send(int type, int player);
void PlayerMessages_SetReply(char reply);
u8 PlayerMessages_Reply(void);
void PlayerMessages_ClearBottleLetter(const u8 *message, int player);
void PlayerMessages_BottleLetter(const char *message, int player);
void PlayerMessages_ItemList(const u8 *message, int player);
void PlayerMessages_Place(const u8 *message, int player);
void PlayerMessages_ReleaseInsect(const u8 *message, int player);
void PlayerMessages_BbsPost(const u8 *message, int player);
void PlayerMessages_Dispatch(const u8 *message, int player);
void PlayerMessages_ClearReply(void);

#endif
