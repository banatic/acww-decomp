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
Letter *PlayerRecord_KeptLetters(u8 *record);
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

/* More of the record, by offset:
 *   0x0000  the player's designs (PlayerDesigns, design_sets.h)
 *   0x1c18  the record of items the player has had (ItemRecord_SetBit sets an item's bit
 *           in it)
 *   0x1d3b  a byte object (func_0203d38c, func_0203d388)
 *   0x1e40  the villagers' part: two 48-byte blocks naming villagers (func_0209ad9c), an
 *           object at 0x94 and an NpcId with an object at 0xa4 (villager_kinds.h)
 *   0x1f0c  the Wi-Fi account, 0x1f5c the Wi-Fi friends (wifi_friends.h)
 *   0x23ec, 0x2416, 0x2427, 0x242c  objects of their own (func_0208880c, func_02088c10,
 *           func_02088764, func_02088460 construct them)
 *   0x2404  the shop points (shop_points.h)
 *   0x2406  the held item, 0x2408 the clothes, 0x240a the head's item, 0x240c part C's item,
 *           0x240e and 0x2410 two more items (0xfff1: none)
 *   0x2412  the date the sun level was last stored, packed (PlayerRecordSunDate)
 *   0x243c  the face (bits 0-3) and the head's kind (bits 4-7)
 *   0x243d  the hair colour (bits 0-2), the sun level (bits 3-5) and a two-bit state cleared
 *           on each new day (bits 6-7)
 * Flag 0 of the record adds 0x10 to the face (FieldActor_RecordFace). */

#include "calendar.h"
#include "design_sets.h"
#include "npc_id.h"
#include "player_pockets.h"
#include "savings.h"
#include "shop_points.h"
#include "wifi_friends.h"

#define PLAYER_RECORD_NO_ITEM 0xfff1

/* A date in 16 bits: the year (from 2000) in bits 0-6, the month in bits 7-10, the day in
 * bits 11-15. */
typedef struct PlayerRecordSunDate {
    u16 packed;
} PlayerRecordSunDate;

struct PlayerRecordName;

SavingsAccount *PlayerRecord_Savings(u8 *record);
Date *PlayerRecord_LastPlayDate(u8 *record);
int PlayerRecord_FindFree(u8 *records, int count);
int PlayerRecord_OtherPlayerName(u8 *record, struct PlayerRecordName *name);
u8 *PlayerRecord_RandomOther(u8 *record);
void PlayerRecord_SetItem2410(u8 *record, const u16 *item);
u16 *PlayerRecord_Item2410(u8 *record);
void PlayerRecord_ResetForNewTown(u8 *record);
void PlayerRecord_NewDayPocketItems(u8 *record);
u8 *PlayerRecord_VillagerPart(u8 *record);
u8 *PlayerRecord_Field1D3B(u8 *record);
WifiFriendList *PlayerRecord_WifiFriends(u8 *record);
WifiAccount *PlayerRecord_WifiAccount(u8 *record);
u8 *PlayerRecord_Field2416(u8 *record);
u8 *PlayerRecord_Field23EC(u8 *record);
u8 *PlayerRecord_Field242C(u8 *record);
u8 *PlayerRecord_Field2427(u8 *record);
u16 *PlayerRecord_ShopPoints(u8 *record);
u8 *PlayerRecord_ItemRecord(u8 *record);
PlayerDesigns *PlayerRecord_Designs(u8 *record);
void PlayerRecord_SetItem240E(u8 *record, const u16 *item);
u16 *PlayerRecord_Item240E(u8 *record);
void PlayerRecord_SetPartCItem(u8 *record, const u16 *item);
u16 *PlayerRecord_PartCItem(u8 *record);
void PlayerRecord_SetHeadItem(u8 *record, const u16 *item);
u16 *PlayerRecord_HeadItem(u8 *record);
void PlayerRecord_SetClothes(u8 *record, const u16 *item);
u16 *PlayerRecord_Clothes(u8 *record);
void PlayerRecord_SetHeldItem(u8 *record, const u16 *item);
u16 *PlayerRecord_HeldItem(u8 *record);
PlayerPockets *PlayerRecord_Pockets(u8 *record);
void PlayerRecord_SetFlag0(u8 *record, int set);
int PlayerRecord_Flag0(u8 *record);
void PlayerRecord_SetDayState(u8 *record, int state);
u32 PlayerRecord_DayState(u8 *record);
void PlayerRecord_SetSunDate(u8 *record, PlayerRecordSunDate date);
s16 PlayerRecord_SunDate(u8 *record);
void PlayerRecord_SetSunLevel(u8 *record, int level);
u32 PlayerRecord_SunLevel(u8 *record);
void PlayerRecord_SetHairColor(u8 *record, int color);
u32 PlayerRecord_HairColor(u8 *record);
void PlayerRecord_SetHeadKind(u8 *record, int kind);
u32 PlayerRecord_HeadKind(const u8 *record);
void PlayerRecord_SetFace(u8 *record, u32 face);
u32 PlayerRecord_Face(u8 *record);
int PlayerRecord_Number(u8 *record);
DesignCreator *PlayerRecord_Player(u8 *record);
void PlayerRecord_NewPlayer(u8 *record, const void *name, int player_id, int byte_1c, const NpcIdHead *town, u8 face,
                            u8 head_kind, u8 hair_color, u8 sun_level, u8 flag0, int bells, const u16 *held_item);
int PlayerRecord_HasPlayer(u8 *record);
void PlayerRecord_Clear(u8 *record);
void PlayerRecord_Zero(u8 *record);
u8 *PlayerRecord_Destruct(u8 *record);
u8 *PlayerRecord_Construct(u8 *record);

int PlayerRecordVillager_Note(PlayerRecordVillager *villager, const NpcId *npc, int fondness, const NpcIdHead *town);
void PlayerRecordVillager_Set(PlayerRecordVillager *villager, const NpcId *npc, s8 fondness, const NpcIdHead *town,
                              const u16 *item);
int PlayerRecordVillager_IsSet(PlayerRecordVillager *villager);
void PlayerRecordVillager_Clear(PlayerRecordVillager *villager);
PlayerRecordVillager *PlayerRecordVillager_Destruct(PlayerRecordVillager *villager);
PlayerRecordVillager *PlayerRecordVillager_Construct(PlayerRecordVillager *villager);

#endif
