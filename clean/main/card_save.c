/* Parts of the save written to the card on their own (card_save.h). */
#include "card_save.h"

#include "activity.h"
#include "backup_card.h"
#include "clean.h"
#include "letter_store.h"
#include "player_record.h"
#include "player_records.h"
#include "save_stamp.h"
#include "state_block.h"
#include "wifi_friends.h"
#include "activity_card.h"
#include "exchange_block.h"
#include "waiting_letter.h"

static_assert(offsetof(StateBlock, part_11c70) == 0x11c70 && offsetof(StateBlock, part_1704c) == 0x1704c, "state block");
static_assert(offsetof(StateBlock, part_173f8) == 0x173f8 && offsetof(StateBlock, players) == 0x14, "state block");

extern BackupCard data_021c8188;
extern StateBlock data_021dc7a8;
extern SaveStamp data_021f3ba0; /* the state block's part_173f8 */

/* Where each CardSavePart starts in the save memory. */
extern const u32 data_020d1c20[3];

/* The record number used for a guest's (data_020e37f8: 7, which no record has). */
extern const u8 data_020e37f8;

#define EXCHANGE_BLOCK_SIZE 0x950
#define PART_1704C_SIZE 0x104
#define FRIEND_ROSTER_SIZE 0x484
#define ACCOUNT_SIZE 0x50
#define STAMP_SIZE 4
#define LETTERS_STATE 0xc800 /* the letters block's state byte (letter_store.c) */
#define BYTE_3FFFC 0x3fffc   /* a byte near the end of the save memory (2^18 bytes) */

/* Where `part` of the state block goes in card part `copy`. */
static int card_offset(int copy, const void *part)
{
    return (int) (data_020d1c20[copy] + ((u32) (uintptr_t) part - (u32) (uintptr_t) &data_021dc7a8));
}

/* `length` bytes of the state block from `part` written to copy 0, then copy 1; whether a
 * write failed.
 * HW: each write waits until the card has written and verified it, and copy 1 is not touched
 * before copy 0 is done. */
static int write_both_copies(const void *part, int length)
{
    if (BackupCard_Write(&data_021c8188, card_offset(CARD_SAVE_COPY_0, part), part, length) == BACKUP_CARD_FAILED) {
        return 1;
    }
    if (BackupCard_Write(&data_021c8188, card_offset(CARD_SAVE_COPY_1, part), part, length) == BACKUP_CARD_FAILED) {
        return 1;
    }
    return 0;
}

/* func_020a145c: the exchange block (part_11c70) and the part at 0x1704c, each given the
 * checksum that brings its halfword sum to 0, written to both copies (the exchange block to
 * both first).
 * QUIRK: the part at 0x1704c keeps its checksum in a byte: only the low 8 bits are stored, so
 * its sum does not come out 0 in general. */
int CardSave_WriteExchangeBlock(void)
{
    u8 *exchange = data_021dc7a8.part_11c70;
    u8 *part = data_021dc7a8.part_1704c;
    ExchangeBlock_SetChecksum((ExchangeBlock *) (void *) exchange,
                              BackupCard_Checksum((const u16 *) exchange, EXCHANGE_BLOCK_SIZE,
                                                  ExchangeBlock_Checksum((ExchangeBlock *) (void *) exchange)));
    WaitingLetter_SetChecksum((WaitingLetter *) (void *) part,
                              (u8) BackupCard_Checksum((const u16 *) part, PART_1704C_SIZE,
                                                       WaitingLetter_Checksum((WaitingLetter *) (void *) part)));
    if (write_both_copies(exchange, EXCHANGE_BLOCK_SIZE) != 0) {
        return 1;
    }
    return write_both_copies(part, PART_1704C_SIZE);
}
CLEAN_AS(func_020a145c, CardSave_WriteExchangeBlock)

/* func_020a1518: this system's player's friend roster, given its checksum, written to both
 * copies where the roster of the player's town record is.
 * BUG: for a guest's record number (4 or more) the number becomes 7, which has no town record:
 * the place is worked out from a null record, both writes fall outside the save memory and 1
 * is given. */
int CardSave_WriteFriendRoster(void)
{
    int number = PlayerRecords_CurrentNumber();
    WifiFriendList *roster = PlayerRecord_WifiFriends(PlayerRecords_Current());
    if (number >= PLAYER_RECORDS_TOWN) {
        number = data_020e37f8;
    }
    WifiFriendList *saved = PlayerRecord_WifiFriends(PlayerRecords_TownRecord(data_021dc7a8.players, number));
    WifiFriendList_SetChecksum(
        roster, BackupCard_Checksum((const u16 *) roster, FRIEND_ROSTER_SIZE, WifiFriendList_GetChecksum(roster)));
    if (BackupCard_Write(&data_021c8188, card_offset(CARD_SAVE_COPY_0, saved), roster, FRIEND_ROSTER_SIZE) ==
        BACKUP_CARD_FAILED) {
        return 1;
    }
    if (BackupCard_Write(&data_021c8188, card_offset(CARD_SAVE_COPY_1, saved), roster, FRIEND_ROSTER_SIZE) ==
        BACKUP_CARD_FAILED) {
        return 1;
    }
    return 0;
}
CLEAN_AS(func_020a1518, CardSave_WriteFriendRoster)

/* func_020a15ac: the Wi-Fi account of this system's player's town record, given its checksum,
 * written to both copies.
 * REQUIRES: this system's player has a town record (number 0-3); for a guest's the record is
 * null. */
int CardSave_WriteAccount(void)
{
    int number = PlayerRecords_CurrentNumber();
    WifiAccount *account = PlayerRecord_WifiAccount(PlayerRecords_TownRecord(data_021dc7a8.players, number));
    WifiAccount_SetChecksum(account,
                            BackupCard_Checksum((const u16 *) account, ACCOUNT_SIZE, WifiAccount_GetChecksum(account)));
    return write_both_copies(account, ACCOUNT_SIZE);
}
CLEAN_AS(func_020a15ac, CardSave_WriteAccount)

/* func_020a1628: the state block's stamp cleared (SAVE_STAMP_NONE) and the letters block's state
 * byte set to 0x1c, then written: the stamp to both copies, then the state byte to the
 * letters' part.
 * REQUIRES: there is a current activity (Activity_CurrentLetters is not null). */
int CardSave_WriteClearedMarks(void)
{
    u8 *letters = Activity_CurrentLetters();
    SaveStamp_Clear(&data_021f3ba0);
    LetterStore_MarkBlock1C(letters);
    if (write_both_copies(&data_021f3ba0, STAMP_SIZE) != 0) {
        return 1;
    }
    int offset = (int) (data_020d1c20[CARD_SAVE_LETTERS] + LETTERS_STATE);
    if (BackupCard_Write(&data_021c8188, offset, letters + LETTERS_STATE, 1) == BACKUP_CARD_FAILED) {
        return 1;
    }
    return 0;
}
CLEAN_AS(func_020a1628, CardSave_WriteClearedMarks)

/* func_020a16b0: a 0 written to the save memory's byte 0x3fffc, outside the parts (the boot
 * screen does it when both copies are bad). */
int CardSave_ClearByte3FFFC(void)
{
    u8 zero = 0;
    if (BackupCard_Write(&data_021c8188, BYTE_3FFFC, &zero, 1) == BACKUP_CARD_FAILED) {
        return 1;
    }
    return 0;
}
CLEAN_AS(func_020a16b0, CardSave_ClearByte3FFFC)

/* func_020a16e0: whether the two copies' stamps on the card have the same serial (with both
 * good, the boot screen then uses copy 1).
 * QUIRK: the reads' results are not looked at: after a failed read the serial compared is
 * whatever the stamp's bytes held before. */
int CardSave_SameSerial(void)
{
    SaveStamp first;
    SaveStamp second;
    SaveStamp_Construct(&first);
    ActivityCard_ReadStamp(CARD_SAVE_COPY_0, &first);
    SaveStamp_Construct(&second);
    ActivityCard_ReadStamp(CARD_SAVE_COPY_1, &second);
    int same = SaveStamp_Serial(&first) == SaveStamp_Serial(&second);
    SaveStamp_Destruct(&second);
    SaveStamp_Destruct(&first);
    return same;
}
CLEAN_AS(func_020a16e0, CardSave_SameSerial)
