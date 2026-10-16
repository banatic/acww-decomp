/* Messages between the players' consoles. A received message is handed to the handler its
 * first byte (its type) selects in the table at data_020df6bc (func_02070760), with the number
 * of the player who sent it; the rest of the message is its payload. The functions here are
 * that dispatch, the handlers of types 0-23 and the short replies some of them send back
 * (PlayerMessages_Send). */
#ifndef CLEAN_MAIN_PLAYER_MESSAGES_H
#define CLEAN_MAIN_PLAYER_MESSAGES_H

#include "types.h"

enum PlayerMessageType {
    PLAYER_MESSAGE_LOG_ENTRY = 0,    /* an entry for the log at data_021eed68 */
    PLAYER_MESSAGE_TURN = 1,         /* an angle for the sender's object (PlayerMessages_Turn) */
    PLAYER_MESSAGE_PLACE_ID = 2,     /* an id at a position (PlayerMessages_Place) */
    PLAYER_MESSAGE_BYTES_A = 3,      /* 30 bytes for data_021f3a68 */
    PLAYER_MESSAGE_BYTES_B = 4,      /* 30 bytes for data_021f3a86 */
    PLAYER_MESSAGE_PLACE = 5,        /* func_ov003_0222c3a8 at a position */
    PLAYER_MESSAGE_RECORD = 6,       /* a 0x100-byte record for data_021ee418 */
    PLAYER_MESSAGE_CLEAR_RECORD = 7, /* empty the record at data_021f36ec */
    PLAYER_MESSAGE_STORE_RECORD = 8, /* a 0x100-byte record to store; answered with 9-11 */
    PLAYER_MESSAGE_STORED = 9,       /* stored, and there is room for more */
    PLAYER_MESSAGE_STORED_FULL = 10, /* stored, and now there is no room */
    PLAYER_MESSAGE_NOT_STORED = 11,  /* there was no room */
    PLAYER_MESSAGE_NIBBLES = 12,     /* 16 values of four bits */
    PLAYER_MESSAGE_SET_MODE = 13,    /* 13-17: set the mode (0-4), answered with 18-22 */
    PLAYER_MESSAGE_MODE_SET = 18,    /* 18-22: the mode (0-4) was set */
    PLAYER_MESSAGE_KEY = 23,         /* func_02045d98 with the payload's byte */
    PLAYER_MESSAGE_NONE = 24,        /* no reply (func_02070778) */
};

/* The number of types the table at data_020df6bc has a handler for (0-23). */
#define PLAYER_MESSAGE_TYPES 24

/* The mode types 13-22 carry: a word of the object at data_021d3338 (func_0208d0bc sets it,
 * func_0208d12c tests it for 0). */
#define PLAYER_MESSAGE_MODES 5

/* The message category PlayerMessages_Send sends its replies under. */
#define PLAYER_MESSAGE_CATEGORY 22

void PlayerMessages_Key(const u8 *message, int player);
void PlayerMessages_ModeSet(const u8 *message, int player);
void PlayerMessages_SetMode(const u8 *message, int player);
void PlayerMessages_ApplyMode(int mode);
void PlayerMessages_Nibbles(const void *message, int player);
void PlayerMessages_StoreReply(const u8 *message, int player);
void PlayerMessages_StoreRecord(const u8 *message, int player);
void PlayerMessages_Send(int type, int player);
void PlayerMessages_SetReply(char reply);
u8 PlayerMessages_Reply(void);
void PlayerMessages_ClearRecord(const u8 *message, int player);
void PlayerMessages_Record(const char *message, int player);
void PlayerMessages_Bytes(const u8 *message, int player);
void PlayerMessages_Place(const u8 *message, int player);
void PlayerMessages_Turn(const u8 *message, int player);
void PlayerMessages_LogEntry(const u8 *message, int player);
void PlayerMessages_Dispatch(const u8 *message, int player);
void PlayerMessages_ClearReply(void);

#endif
