/* Fields of one player's record (0x249c bytes; player_records.h has the records themselves),
 * and the things of the town's players kept outside it, found by the record's player number
 * (func_0209985c, 0-3): the mailbox (mail.h), a storage of 90 items and the letters kept
 * (letter_store.h).
 *
 * Fields known so far, by offset in the record:
 *   0x11a8  the pockets (player_pockets.h)
 *   0x1d3c  a letter kept for a date (mail.h)
 *   0x23e0  the savings account (savings.h)
 *   0x23e8  four bytes (0xff for none), read by func_0203fa98
 *   0x23f8  64 flags
 *   0x2400  the date of the last play
 *   0x2414  the birthday: day, month
 *   0x243e  the mother's letters' state (mom_letters.h)
 *   0x2451  a count, 0 or 2-10, raised by PlayerRecord_RaiseCount
 *   0x2452  a byte (func_020be9dc tests it against 16)
 *   0x2453  the year of the last birthday celebrated, 0xff for none this year
 *   0x2454  one byte for each of the town's 8 villagers (villager_town.h)
 *   0x245c  a villager to write a letter (PlayerRecordVillager)
 *   0x247e  the player's id: town and player (player_records.h) */
#ifndef CLEAN_MAIN_PLAYER_RECORD_H
#define CLEAN_MAIN_PLAYER_RECORD_H

#include "mail.h"
#include "mom_letters.h"
#include "types.h"

#define PLAYER_RECORD_FLAG_WORDS 2
#define PLAYER_RECORD_VILLAGER_BYTES 8
#define PLAYER_RECORD_NO_YEAR 0xff

/* The town's 90-item storage of one player (0xb4 bytes, data_021f2fa8). */
#define PLAYER_STORAGE_ITEMS 90
typedef struct PlayerStorage {
    u16 items[PLAYER_STORAGE_ITEMS];
} PlayerStorage;

/* The villager kept at 0x245c of the record, a letter from whom PlayerRecord_SendVillagerLetter
 * writes: its town (func_02064294 tests it), the villager (an NpcId) and an item for the
 * letter (0xfff1: none). func_0207d4bc records it; func_02099e18 clears it once written. */
typedef struct PlayerRecordVillager {
    u8 town[14];
    u8 villager[16]; /* an NpcId (npc_id.h) */
    u16 item;
    u8 unk_20;
} PlayerRecordVillager;

void PlayerRecord_SetMailMark(u8 *record, int mark);
int PlayerRecord_MailMark(u8 *record);
PlayerStorage *PlayerRecord_Storage(u8 *record);
MailBox *PlayerRecord_Mailbox(u8 *record);
MailLetter *PlayerRecord_KeptLetters(u8 *record);
MomLetterState *PlayerRecord_MomLetterState(u8 *record);
u8 *PlayerRecord_DatedLetter(u8 *record);
void PlayerRecord_ClearFlag(u8 *record, u32 flag);
void PlayerRecord_SetFlag(u8 *record, u32 flag);
int PlayerRecord_TestFlag(u8 *record, u32 flag);
void PlayerRecord_SendVillagerLetter(u8 *record);
PlayerRecordVillager *PlayerRecord_Villager(u8 *record);
void PlayerRecord_SetVillagerByte(u8 *record, u32 villager, u8 value);
u8 PlayerRecord_VillagerByte(u8 *record, u32 villager);
void PlayerRecord_SetByte2452(u8 *record, u8 value);
u8 PlayerRecord_Byte2452(const u8 *record);
void PlayerRecord_RaiseCount(u8 *record);
u8 PlayerRecord_Count(u8 *record);
void PlayerRecord_UpdateSinceLastPlay(void);
u8 PlayerRecord_BirthdayYear(u8 *record);
u8 *PlayerRecord_SetBirthdayYear(u8 *record, u8 year);
void PlayerRecord_ClearBirthday(u8 *record);
void PlayerRecord_SetBirthday(u8 *record, u8 month, u8 day);
u8 *PlayerRecord_Birthday(u8 *record);
u8 *PlayerRecord_Bytes23e8(u8 *record);

#endif
