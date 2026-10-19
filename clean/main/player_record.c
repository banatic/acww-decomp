/* Fields of one player's record (player_record.h). */
#include "player_record.h"

#include "calendar.h"
#include "clean.h"
#include "npc_id.h"
#include "player_records.h"
#include "savings.h"
#include "state_block.h"
#include "activity.h"
#include "daily_bits.h"
#include "day_events.h"
#include "item_code.h"
#include "item_lists.h"
#include "item_record.h"
#include "letter.h"
#include "mail_text.h"
#include "main_random.h"
#include "message_reader.h"
#include "message_receiver.h"
#include "motion_slots.h"
#include "npc_letters.h"
#include "paired_town.h"
#include "player_field_2416.h"
#include "player_id.h"
#include "player_options.h"
#include "text_base.h"
#include "town_name.h"
#include "villager_letter.h"
#include "villager_part.h"
#include "villager_part_block.h"
#include "villager_part_entry.h"
#include "villager_part_handover.h"
#include "word_archives.h"

static_assert(offsetof(PlayerRecordVillager, villager) == 0xe, "PlayerRecordVillager layout");
static_assert(offsetof(PlayerRecordVillager, item) == 0x1e, "PlayerRecordVillager layout");
static_assert(offsetof(PlayerRecordVillager, unk_20) == 0x20, "PlayerRecordVillager layout");
static_assert(sizeof(PlayerStorage) == 0xb4, "PlayerStorage layout");

#define NO_ITEM 0xfff1

/* Offsets in the record. */
#define RECORD_MOM_LETTERS 0x243e
#define RECORD_DATED_LETTER 0x1d3c
#define RECORD_BYTES_23E8 0x23e8
#define RECORD_FLAGS 0x23f8
#define RECORD_BIRTHDAY 0x2414
#define RECORD_COUNT 0x2451
#define RECORD_BYTE_2452 0x2452
#define RECORD_BIRTHDAY_YEAR 0x2453
#define RECORD_VILLAGER_BYTES 0x2454
#define RECORD_VILLAGER 0x245c

/* PlayerRecord_RaiseCount's range above 0. */
#define COUNT_FIRST 2
#define COUNT_MAX 10

/* The letters each player keeps (letter_store.h), one after the other. */
#define KEPT_LETTERS_SIZE 0x3200

/* Flag 0x10 of the state block, cleared when the game is played on another day. */
#define STATE_FLAG_CLEARED_ON_NEW_DAY 0x10
/* An object of the state block at 0x173e2 that func_020882f0 resets when the clock went back. */
#define STATE_OBJECT_173E2 0x173e2

/* The message entries of the villager's letter: the player's name, the villager's, six words
 * drawn at random, then the villager's town. */
#define LETTER_ENTRY_PLAYER 0
#define LETTER_ENTRY_VILLAGER 1
#define LETTER_ENTRY_FIRST_WORD 2
#define LETTER_WORDS 6
#define LETTER_ENTRY_TOWN 8

extern MailBox data_021ef8ec[MAIL_PLAYERS];       /* the players' mailboxes */
extern PlayerStorage data_021f2fa8[MAIL_PLAYERS]; /* the players' storages */
extern u32 data_021dc7a8[];                       /* the state block (state_block.h) */
extern u8 data_020e3128[];                        /* passed to func_0207d3dc for the villager's letter */

/* The villager's letter. The texts are the game's objects: a player's name (0x20 bytes), an
 * 8-bit text (0x20 bytes) and a label (0x5c bytes, with a vtable). */
typedef struct PlayerRecordName {
    u32 words[0x20 / 4];
} PlayerRecordName;
typedef struct PlayerRecordText8 {
    u32 words[0x20 / 4];
} PlayerRecordText8;
typedef struct PlayerRecordLabel {
    u32 words[0x5c / 4];
} PlayerRecordLabel;

static u32 *player_record_flags(u8 *record)
{
    return (u32 *) (void *) (record + RECORD_FLAGS);
}

static int player_number(u8 *record)
{
    int number = PlayerRecord_Number(record);
    return number >= 0 && number < MAIL_PLAYERS ? number : -1;
}

/* func_02098930: set the mark of the record's player's mailbox (MailBox_SetMark). */
void PlayerRecord_SetMailMark(u8 *record, int mark)
{
    int number = player_number(record);
    if (number != -1) {
        MailBox_SetMark(&data_021ef8ec[number], (u32) mark);
    }
}
CLEAN_AS(func_02098930, PlayerRecord_SetMailMark)

/* func_0209895c: the mark of the record's player's mailbox; 0 without a player number. */
int PlayerRecord_MailMark(u8 *record)
{
    int number = player_number(record);
    if (number != -1) {
        return MailBox_Mark(&data_021ef8ec[number]);
    }
    return 0;
}
CLEAN_AS(func_0209895c, PlayerRecord_MailMark)

/* func_0209898c: the record's player's storage, or NULL. */
PlayerStorage *PlayerRecord_Storage(u8 *record)
{
    int number = player_number(record);
    return number != -1 ? &data_021f2fa8[number] : NULL;
}
CLEAN_AS(func_0209898c, PlayerRecord_Storage)

/* func_020989b4: the record's player's mailbox, or NULL. */
MailBox *PlayerRecord_Mailbox(u8 *record)
{
    int number = player_number(record);
    return number != -1 ? &data_021ef8ec[number] : NULL;
}
CLEAN_AS(func_020989b4, PlayerRecord_Mailbox)

/* func_020989e0: the letters the record's player keeps, or NULL (also without their block). */
Letter *PlayerRecord_KeptLetters(u8 *record)
{
    int number = player_number(record);
    if (number == -1) {
        return NULL;
    }
    int block = (int) (uintptr_t) Activity_CurrentLetters();
    if (block == 0) {
        return NULL;
    }
    return (Letter *) (uintptr_t) (u32) (block + KEPT_LETTERS_SIZE * number);
}
CLEAN_AS(func_020989e0, PlayerRecord_KeptLetters)

/* func_02098a0c */
MomLetterState *PlayerRecord_MomLetterState(u8 *record)
{
    return (MomLetterState *) (void *) (record + RECORD_MOM_LETTERS);
}
CLEAN_AS(func_02098a0c, PlayerRecord_MomLetterState)

/* func_02098a18 */
u8 *PlayerRecord_DatedLetter(u8 *record)
{
    return record + RECORD_DATED_LETTER;
}
CLEAN_AS(func_02098a18, PlayerRecord_DatedLetter)

/* func_02098fd0: clear one of the 64 flags (nothing for a larger number). */
void PlayerRecord_ClearFlag(u8 *record, u32 flag)
{
    u32 word = flag >> 5;
    if (word < PLAYER_RECORD_FLAG_WORDS) {
        player_record_flags(record)[word] &= ~(1u << (flag & 0x1f));
    }
}
CLEAN_AS(func_02098fd0, PlayerRecord_ClearFlag)

/* func_02098ff8: set one of the 64 flags (nothing for a larger number). */
void PlayerRecord_SetFlag(u8 *record, u32 flag)
{
    u32 word = flag >> 5;
    if (word < PLAYER_RECORD_FLAG_WORDS) {
        player_record_flags(record)[word] |= 1u << (flag & 0x1f);
    }
}
CLEAN_AS(func_02098ff8, PlayerRecord_SetFlag)

/* func_02099020: whether one of the 64 flags is set (0 for a larger number). */
int PlayerRecord_TestFlag(u8 *record, u32 flag)
{
    u32 word = flag >> 5;
    if (word >= PLAYER_RECORD_FLAG_WORDS) {
        return 0;
    }
    return (player_record_flags(record)[word] & (1u << (flag & 0x1f))) != 0;
}
CLEAN_AS(func_02099020, PlayerRecord_TestFlag)

/* func_02099050: when the record's player id and its villager (PlayerRecordVillager) are set,
 * have the villager write the player a letter (func_0207d3dc): the message is one of ten, or,
 * when the villager has an item for the player, one of five after those. Once written, the
 * villager is cleared. */
void PlayerRecord_SendVillagerLetter(u8 *record)
{
    void *player = PlayerRecord_Player(record);
    if (!PlayerId_IsSet(player)) {
        return;
    }
    PlayerRecordVillager *villager = PlayerRecord_Villager(record);
    if (!PlayerRecordVillager_IsSet(villager)) {
        return;
    }
    PlayerRecordName name;
    PlayerRecordText8 town;
    PlayerRecordLabel word;
    PlayerIdText_Construct((PlayerIdText *) &name);
    TownNameText_Construct((TownNameText *) &town);
    MessagePart_Construct((MessagePart *) &word);

    int first = 0;
    int count = 10;
    if (villager->item != NO_ITEM) {
        first = 10;
        count = 5;
    }

    PlayerId_NameToText(player, (TextBase *) &name);
    MailText_SetPartText(LETTER_ENTRY_PLAYER, &name);
    TextBase_Clear(&name);
    NpcId_FormatName((const NpcId *) (void *) villager->villager, (char *) &name);
    MailText_SetPartText(LETTER_ENTRY_VILLAGER, &name);

    int number = 0;
    for (int i = 0; i < LETTER_WORDS; i++) {
        int text = WordArchives_Random(&number, i);
        TextBase_Clear(&word);
        u8 digit = (u8) number;
        MessageReader_LoadDecoded(&word, &digit, (const char *) (uintptr_t) text);
        MailText_SetPartText(LETTER_ENTRY_FIRST_WORD + i, &word);
    }

    TownName_ToText((TownName *) (void *) villager->town, (TextBase *) &town);
    MailText_SetPartText(LETTER_ENTRY_TOWN, &town);
    if (VillagerLetter_PostDrawn((const char *) data_020e3128, first, count, player,
                                 (const NpcId *) (void *) villager->villager, &villager->item)) {
        PlayerRecordVillager_Clear(villager);
    }
    MessagePart_Destruct((MessagePart *) &word);
    TownNameText_Destruct((TownNameText *) &town);
    PlayerIdText_Destruct((PlayerIdText *) &name);
}
CLEAN_AS(func_02099050, PlayerRecord_SendVillagerLetter)

/* func_02099158 */
PlayerRecordVillager *PlayerRecord_Villager(u8 *record)
{
    return (PlayerRecordVillager *) (void *) (record + RECORD_VILLAGER);
}
CLEAN_AS(func_02099158, PlayerRecord_Villager)

/* func_02099164: the record's byte for the town's villager `villager` (0-7; nothing past). */
void PlayerRecord_SetVillagerByte(u8 *record, u32 villager, u8 value)
{
    if (villager < PLAYER_RECORD_VILLAGER_BYTES) {
        record[RECORD_VILLAGER_BYTES + villager] = value;
    }
}
CLEAN_AS(func_02099164, PlayerRecord_SetVillagerByte)

/* func_02099174: 0xff past 7. */
u8 PlayerRecord_VillagerByte(u8 *record, u32 villager)
{
    if (villager < PLAYER_RECORD_VILLAGER_BYTES) {
        return record[RECORD_VILLAGER_BYTES + villager];
    }
    return 0xff;
}
CLEAN_AS(func_02099174, PlayerRecord_VillagerByte)

/* func_02099188 */
void PlayerRecord_SetByte2452(u8 *record, u8 value)
{
    record[RECORD_BYTE_2452] = value;
}
CLEAN_AS(func_02099188, PlayerRecord_SetByte2452)

/* func_02099194 */
u8 PlayerRecord_Byte2452(const u8 *record)
{
    return record[RECORD_BYTE_2452];
}
CLEAN_AS(func_02099194, PlayerRecord_Byte2452)

/* func_020991a0: raise the count by one: from 0 to 2, and at most to 10. QUIRK: 255 wraps to
 * 0, which stays. */
void PlayerRecord_RaiseCount(u8 *record)
{
    u8 count = (u8) (record[RECORD_COUNT] + 1);
    if (count == 1) {
        count = COUNT_FIRST;
    }
    if (count > COUNT_MAX) {
        count = COUNT_MAX;
    }
    record[RECORD_COUNT] = count;
}
CLEAN_AS(func_020991a0, PlayerRecord_RaiseCount)

/* func_020991c8 */
u8 PlayerRecord_Count(u8 *record)
{
    return record[RECORD_COUNT];
}
CLEAN_AS(func_020991c8, PlayerRecord_Count)

/* func_020991d4: when the current player plays, catch up the record with the time since the
 * last play: the savings' interest for the months, their letters for the days, the letters of
 * func_02088810 and func_020889a8; on another day func_0209948c and the resets below, and in a
 * new year the birthday may be celebrated again. When the clock went back, two more objects are
 * reset. Today becomes the date of the last play. */
void PlayerRecord_UpdateSinceLastPlay(void)
{
    u8 *self = PlayerRecords_Current();
    if (self == NULL) {
        return;
    }

    Date today;
    Calendar_Today(&today);
    Date *last = PlayerRecord_LastPlayDate(self);
    int days = Calendar_DaysFrom(&today, last);

    Savings_PayInterest((today.month - last->month) + 12 * (today.year - last->year));
    Savings_SendMilestoneLetter(days);
    Savings_SendRankLetter(days);
    NpcLetters_SendInsurance((PlayerField2416 *) (void *) PlayerRecord_Field2416(self));
    /* QUIRK: the field is asked for once more, unused. */
    PlayerRecord_Field2416(self);
    NpcLetters_SendMissing();

    if (days != 0) {
        PlayerRecord_NewDayPocketItems(self);
    }
    if (today.year != PlayerRecord_BirthdayYear(self)) {
        PlayerRecord_SetBirthdayYear(self, PLAYER_RECORD_NO_YEAR);
    }
    if (days != 0) {
        DailyBits_ClearAll((DailyBits *) (void *) PlayerRecord_Field23EC(self));
        PlayerRecord_SetDayState(self, 0);
        PlayerField2416_ClearTally((PlayerField2416 *) (void *) PlayerRecord_Field2416(self));
        StateBlock_ClearFlag(data_021dc7a8, STATE_FLAG_CLEARED_ON_NEW_DAY);
    }
    if (days < 0) {
        PairedTown_Reset(PlayerRecord_Field242C(self));
        PairedTown_Reset((u8 *) data_021dc7a8 + STATE_OBJECT_173E2);
    }

    Calendar_Today(PlayerRecord_LastPlayDate(self));
}
CLEAN_AS(func_020991d4, PlayerRecord_UpdateSinceLastPlay)

/* func_020992ac */
u8 PlayerRecord_BirthdayYear(u8 *record)
{
    return record[RECORD_BIRTHDAY_YEAR];
}
CLEAN_AS(func_020992ac, PlayerRecord_BirthdayYear)

/* func_020992b8 */
u8 *PlayerRecord_SetBirthdayYear(u8 *record, u8 year)
{
    record[RECORD_BIRTHDAY_YEAR] = year;
    return record;
}
CLEAN_AS(func_020992b8, PlayerRecord_SetBirthdayYear)

/* func_020992c4: no birthday (day and month 0). */
void PlayerRecord_ClearBirthday(u8 *record)
{
    *(u16 *) (void *) (record + RECORD_BIRTHDAY) = 0;
}
CLEAN_AS(func_020992c4, PlayerRecord_ClearBirthday)

/* func_020992d0 */
void PlayerRecord_SetBirthday(u8 *record, u8 month, u8 day)
{
    record[RECORD_BIRTHDAY + 1] = month;
    record[RECORD_BIRTHDAY] = day;
}
CLEAN_AS(func_020992d0, PlayerRecord_SetBirthday)

/* func_020992e4: the birthday, day then month. */
u8 *PlayerRecord_Birthday(u8 *record)
{
    return record + RECORD_BIRTHDAY;
}
CLEAN_AS(func_020992e4, PlayerRecord_Birthday)

/* func_020992f0 */
u8 *PlayerRecord_Bytes23e8(u8 *record)
{
    return record + RECORD_BYTES_23E8;
}
CLEAN_AS(func_020992f0, PlayerRecord_Bytes23e8)

/* ---- The rest of the record's fields */

#define RECORD_POCKETS 0x11a8
#define RECORD_ITEM_RECORD 0x1c18
#define RECORD_FIELD_1D3B 0x1d3b
#define RECORD_VILLAGER_PART 0x1e40
#define RECORD_WIFI_ACCOUNT 0x1f0c
#define RECORD_WIFI_FRIENDS 0x1f5c
#define RECORD_SAVINGS 0x23e0
#define RECORD_FIELD_23EC 0x23ec
#define RECORD_LAST_PLAY 0x2400
#define RECORD_SHOP_POINTS 0x2404
#define RECORD_HELD_ITEM 0x2406
#define RECORD_CLOTHES 0x2408
#define RECORD_HEAD_ITEM 0x240a
#define RECORD_PART_C_ITEM 0x240c
#define RECORD_ITEM_240E 0x240e
#define RECORD_ITEM_2410 0x2410
#define RECORD_SUN_DATE 0x2412
#define RECORD_FIELD_2416 0x2416
#define RECORD_FIELD_2427 0x2427
#define RECORD_FIELD_242C 0x242c
#define RECORD_LOOKS 0x243c
#define RECORD_LOOKS_2 0x243d
#define RECORD_PLAYER 0x247e

/* The object at 0xa4 of the villagers' part (an NpcId, then an object). */
#define VILLAGER_PART_OBJECT_A4 0xa4

/* Byte 0x243c: the face and the head's kind. */
#define LOOKS_FACE_MASK 0x0f
#define LOOKS_HEAD_KIND_SHIFT 4
/* Byte 0x243d: the hair colour, the sun level and the day's state. */
#define LOOKS_HAIR_COLOR_MASK 0x07
#define LOOKS_SUN_LEVEL_SHIFT 3
#define LOOKS_SUN_LEVEL_MASK 0x38
#define LOOKS_DAY_STATE_SHIFT 6
#define LOOKS_DAY_STATE_MASK 0xc0

/* The record's flag that picks the second set of faces. */
#define RECORD_FLAG_0 0

/* What a new player starts with: item 0x3884 at 0x240e, the first clothes (0x11a8), item
 * 0x11fa at 0x2410 and a sun date of 1 January 2000. */
#define NEW_PLAYER_ITEM_240E 0x3884
#define NEW_PLAYER_CLOTHES 0x11a8
#define NEW_PLAYER_ITEM_2410 0x11fa
#define SUN_DATE_PACK(year, month, day) ((u16) (((year) & 0x7f) | ((month) & 0xf) << 7 | ((day) & 0x1f) << 11))

/* The villager's fondness when none is noted. */
#define VILLAGER_NO_FONDNESS (-128)
/* PlayerRecordVillager_Note: one chance in this many of a present, drawn from one of three
 * item lists. */
#define VILLAGER_PRESENT_DRAW 4
#define VILLAGER_PRESENT_LISTS 3

/* The clothes: items 0x11a8-0x12a7. */
#define CLOTHES_FIRST 0x11a8
#define CLOTHES_LAST 0x12a7
/* The pocket items that turn into another overnight (PlayerRecord_NewDayPocketItems), and the
 * items drawn for each: 0x1560 gives one of 0x1100-0x1143 (or one of item list 4), 0x155f one
 * of 0x1144-0x1187 (or one of item list 3). */
#define DAY_ITEM_B 0x155f
#define DAY_ITEM_A 0x1560
#define DAY_DRAW_A_FIRST 0x1100
#define DAY_DRAW_B_FIRST 0x1144
#define DAY_DRAW_COUNT 0x44
#define DAY_LIST_A 4
#define DAY_LIST_B 3
/* Pocket slot states: the state of the clothes PlayerRecord_ResetForNewTown changes and of the
 * items PlayerRecord_NewDayPocketItems replaces, and the states they get. */
#define SLOT_STATE_0 0
#define SLOT_STATE_1 1
#define SLOT_STATE_2 2
/* The letter states PlayerRecord_ResetForNewTown empties. */
#define LETTER_STATE_EMPTIED_FIRST 7
#define LETTER_STATE_EMPTIED_LAST 8

/* An item list: func_02063ccc constructs it, func_020638d4 draws an item of it,
 * func_02063cc8 destroys it. */
typedef struct PlayerRecordItemList {
    int kind;
    int group;
} PlayerRecordItemList;

extern void MI_CpuFill8(void *dst, u8 value, u32 size);
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));
/* The constructors and destructors of a letter and of an item code, handed to the array
 * helpers, so the game's symbols. */
extern void func_02066694(void *letter);
extern void func_02066688(void *letter);
extern void func_02034ce0(void *item);
extern void func_020051b0(void *item);

extern u8 data_021dc7bc[];                              /* the town's four records */
extern const int data_020d19c4[VILLAGER_PRESENT_LISTS]; /* the item lists of a villager's present */

static u16 *player_record_u16(u8 *record, u32 offset)
{
    return (u16 *) (void *) (record + offset);
}

static PlayerPockets *player_record_pockets_at(u8 *record)
{
    return (PlayerPockets *) (void *) (record + RECORD_POCKETS);
}

/* func_020992fc */
SavingsAccount *PlayerRecord_Savings(u8 *record)
{
    return (SavingsAccount *) (void *) (record + RECORD_SAVINGS);
}
CLEAN_AS(func_020992fc, PlayerRecord_Savings)

/* func_02099308 */
Date *PlayerRecord_LastPlayDate(u8 *record)
{
    return (Date *) (void *) (record + RECORD_LAST_PLAY);
}
CLEAN_AS(func_02099308, PlayerRecord_LastPlayDate)

/* func_02099314: the index of the first of `count` records without a player, or -1. */
int PlayerRecord_FindFree(u8 *records, int count)
{
    for (int i = 0; i < count; i++) {
        if (PlayerRecord_HasPlayer(records + i * PLAYER_RECORD_SIZE) == 0) {
            return i;
        }
    }
    return -1;
}
CLEAN_AS(func_02099314, PlayerRecord_FindFree)

/* func_02099348: when the record's player is one of the town's, the name of another of the
 * town's players, drawn at random, goes into `name`; whether there was one. */
int PlayerRecord_OtherPlayerName(u8 *record, PlayerRecordName *name)
{
    if (PlayerId_IndexInTown(PlayerRecord_Player(record)) == -1) {
        return 0;
    }
    u8 *other = PlayerRecord_RandomOther(record);
    if (other == NULL) {
        return 0;
    }
    PlayerId_NameToText(PlayerRecord_Player(other), (TextBase *) name);
    return 1;
}
CLEAN_AS(func_02099348, PlayerRecord_OtherPlayerName)

/* func_02099380: the record of one of the town's players drawn at random, other than this
 * record's player; NULL when there is none. */
u8 *PlayerRecord_RandomOther(u8 *record)
{
    const PlayerRecordsId *player = (const PlayerRecordsId *) (const void *) PlayerRecord_Player(record);
    return PlayerRecords_RandomOther(data_021dc7bc, player);
}
CLEAN_AS(func_02099380, PlayerRecord_RandomOther)

/* func_0209939c */
void PlayerRecord_SetItem2410(u8 *record, const u16 *item)
{
    *player_record_u16(record, RECORD_ITEM_2410) = *item;
}
CLEAN_AS(func_0209939c, PlayerRecord_SetItem2410)

/* func_020993a8 */
u16 *PlayerRecord_Item2410(u8 *record)
{
    return player_record_u16(record, RECORD_ITEM_2410);
}
CLEAN_AS(func_020993a8, PlayerRecord_Item2410)

/* func_020993b4: the player moved to another town (func_0209e974): the villagers' part is
 * emptied (both blocks and the NpcId and object at 0xa4); clothes in a pocket slot of state 2
 * go to state 1 and into the record of items; letters in states 7 and 8 are emptied. Nothing
 * when the record has no player. */
void PlayerRecord_ResetForNewTown(u8 *record)
{
    if (PlayerRecord_HasPlayer(record) == 0) {
        return;
    }
    PlayerPockets *pockets = PlayerRecord_Pockets(record);
    u16 *slot = PlayerPockets_Slot(pockets, 0);

    VillagerPartBlock_Clear(VillagerPart_Block((VillagerPart *) (void *) PlayerRecord_VillagerPart(record), 0));
    VillagerPartBlock_Clear(VillagerPart_Block((VillagerPart *) (void *) PlayerRecord_VillagerPart(record), 1));
    VillagerPartHandover_Clear(
        (VillagerPartHandover *) (void *) (PlayerRecord_VillagerPart(record) + VILLAGER_PART_OBJECT_A4));

    for (int i = 0; i < PLAYER_POCKETS_SLOTS; i++, slot++) {
        if (PlayerPockets_SlotState(pockets, i) != SLOT_STATE_2) {
            continue;
        }
        if (*slot >= CLOTHES_FIRST && *slot <= CLOTHES_LAST) {
            PlayerPockets_SetSlot(pockets, slot, i, SLOT_STATE_1);
            ItemRecord_SetBit((ItemRecord *) PlayerRecord_ItemRecord(record), slot, 0, 1);
        }
    }

    Letter *letter = PlayerPockets_Letter(pockets, 0);
    for (int i = 0; i < PLAYER_POCKETS_LETTERS; i++, letter++) {
        u8 state = Letter_State(letter);
        if (state >= LETTER_STATE_EMPTIED_FIRST && state <= LETTER_STATE_EMPTIED_LAST) {
            Letter_Clear(letter);
        }
    }
}
CLEAN_AS(func_020993b4, PlayerRecord_ResetForNewTown)

/* The item a pocket's 0x155f or 0x1560 turns into: one of DAY_DRAW_COUNT items from `first`,
 * else, when none is drawn, one of item list `list_kind`. */
static u16 player_record_draw_day_item(u8 *record, int first, int list_kind)
{
    u16 item;
    ItemLists_DrawRange(&item, first, DAY_DRAW_COUNT, 0, 0, record, 1, 10, 0, 1);
    if (item == PLAYER_RECORD_NO_ITEM) {
        PlayerRecordItemList list;
        u16 drawn;
        ItemList_Construct((ItemList *) &list, list_kind, 0);
        ItemLists_Draw(&drawn, (ItemList *) &list, 0, 0, 1, 1, 0);
        item = drawn;
        ItemList_Destruct(&list);
    }
    return item;
}

/* func_0209948c: on a new day (PlayerRecord_UpdateSinceLastPlay): the object at 0x94 of the
 * villagers' part is reset, and each pocket item 0x155f or 0x1560 in slot state 2 turns into
 * an item drawn for it, in state 0, marked in the record of items. Which of the two it is goes
 * by func_0204bc64's number for the kinds compared by number. Nothing when the record has no
 * player. */
void PlayerRecord_NewDayPocketItems(u8 *record)
{
    if (PlayerRecord_HasPlayer(record) == 0) {
        return;
    }
    VillagerPartEntry_Clear(
        (VillagerPartEntry *) (void *) VillagerPart_Object94((VillagerPart *) (void *) PlayerRecord_VillagerPart(record)));
    PlayerPockets *pockets = PlayerRecord_Pockets(record);
    u16 *slot = PlayerPockets_Slot(pockets, 0);

    for (int i = 0; i < PLAYER_POCKETS_SLOTS; i++, slot++) {
        if (*slot < DAY_ITEM_B || *slot > DAY_ITEM_A) {
            continue;
        }
        if (PlayerPockets_SlotState(pockets, i) != SLOT_STATE_2) {
            continue;
        }

        int is_a;
        if (ItemCode_HasVariant(slot) != 0) {
            u16 a = DAY_ITEM_A;
            int number = ItemCode_VariantItem(slot);
            is_a = number == ItemCode_VariantItem(&a);
        } else {
            is_a = *slot == DAY_ITEM_A;
        }

        u16 item;
        if (is_a) {
            item = player_record_draw_day_item(record, DAY_DRAW_A_FIRST, DAY_LIST_A);
        } else {
            item = player_record_draw_day_item(record, DAY_DRAW_B_FIRST, DAY_LIST_B);
        }

        PlayerPockets_SetSlot(pockets, &item, i, SLOT_STATE_0);
        if (item != PLAYER_RECORD_NO_ITEM) {
            ItemRecord_SetBit((ItemRecord *) PlayerRecord_ItemRecord(record), &item, 0, 1);
        }
    }
}
CLEAN_AS(func_0209948c, PlayerRecord_NewDayPocketItems)

/* func_02099640 */
u8 *PlayerRecord_VillagerPart(u8 *record)
{
    return record + RECORD_VILLAGER_PART;
}
CLEAN_AS(func_02099640, PlayerRecord_VillagerPart)

/* func_0209964c */
u8 *PlayerRecord_Field1D3B(u8 *record)
{
    return record + RECORD_FIELD_1D3B;
}
CLEAN_AS(func_0209964c, PlayerRecord_Field1D3B)

/* func_02099658 */
WifiFriendList *PlayerRecord_WifiFriends(u8 *record)
{
    return (WifiFriendList *) (void *) (record + RECORD_WIFI_FRIENDS);
}
CLEAN_AS(func_02099658, PlayerRecord_WifiFriends)

/* func_02099664 */
WifiAccount *PlayerRecord_WifiAccount(u8 *record)
{
    return (WifiAccount *) (void *) (record + RECORD_WIFI_ACCOUNT);
}
CLEAN_AS(func_02099664, PlayerRecord_WifiAccount)

/* func_02099670 */
u8 *PlayerRecord_Field2416(u8 *record)
{
    return record + RECORD_FIELD_2416;
}
CLEAN_AS(func_02099670, PlayerRecord_Field2416)

/* func_0209967c */
u8 *PlayerRecord_Field23EC(u8 *record)
{
    return record + RECORD_FIELD_23EC;
}
CLEAN_AS(func_0209967c, PlayerRecord_Field23EC)

/* func_02099688 */
u8 *PlayerRecord_Field242C(u8 *record)
{
    return record + RECORD_FIELD_242C;
}
CLEAN_AS(func_02099688, PlayerRecord_Field242C)

/* func_02099694 */
u8 *PlayerRecord_Field2427(u8 *record)
{
    return record + RECORD_FIELD_2427;
}
CLEAN_AS(func_02099694, PlayerRecord_Field2427)

/* func_020996a0 */
u16 *PlayerRecord_ShopPoints(u8 *record)
{
    return player_record_u16(record, RECORD_SHOP_POINTS);
}
CLEAN_AS(func_020996a0, PlayerRecord_ShopPoints)

/* func_020996ac */
u8 *PlayerRecord_ItemRecord(u8 *record)
{
    return record + RECORD_ITEM_RECORD;
}
CLEAN_AS(func_020996ac, PlayerRecord_ItemRecord)

/* func_020996b8: the designs are at the start of the record. */
PlayerDesigns *PlayerRecord_Designs(u8 *record)
{
    return (PlayerDesigns *) (void *) record;
}
CLEAN_AS(func_020996b8, PlayerRecord_Designs)

/* func_020996bc */
void PlayerRecord_SetItem240E(u8 *record, const u16 *item)
{
    *player_record_u16(record, RECORD_ITEM_240E) = *item;
}
CLEAN_AS(func_020996bc, PlayerRecord_SetItem240E)

/* func_020996c8 */
u16 *PlayerRecord_Item240E(u8 *record)
{
    return player_record_u16(record, RECORD_ITEM_240E);
}
CLEAN_AS(func_020996c8, PlayerRecord_Item240E)

/* func_020996d4 */
void PlayerRecord_SetPartCItem(u8 *record, const u16 *item)
{
    *player_record_u16(record, RECORD_PART_C_ITEM) = *item;
}
CLEAN_AS(func_020996d4, PlayerRecord_SetPartCItem)

/* func_020996e0 */
u16 *PlayerRecord_PartCItem(u8 *record)
{
    return player_record_u16(record, RECORD_PART_C_ITEM);
}
CLEAN_AS(func_020996e0, PlayerRecord_PartCItem)

/* func_020996ec */
void PlayerRecord_SetHeadItem(u8 *record, const u16 *item)
{
    *player_record_u16(record, RECORD_HEAD_ITEM) = *item;
}
CLEAN_AS(func_020996ec, PlayerRecord_SetHeadItem)

/* func_020996f8 */
u16 *PlayerRecord_HeadItem(u8 *record)
{
    return player_record_u16(record, RECORD_HEAD_ITEM);
}
CLEAN_AS(func_020996f8, PlayerRecord_HeadItem)

/* func_02099704 */
void PlayerRecord_SetClothes(u8 *record, const u16 *item)
{
    *player_record_u16(record, RECORD_CLOTHES) = *item;
}
CLEAN_AS(func_02099704, PlayerRecord_SetClothes)

/* func_02099710 */
u16 *PlayerRecord_Clothes(u8 *record)
{
    return player_record_u16(record, RECORD_CLOTHES);
}
CLEAN_AS(func_02099710, PlayerRecord_Clothes)

/* func_0209971c */
void PlayerRecord_SetHeldItem(u8 *record, const u16 *item)
{
    *player_record_u16(record, RECORD_HELD_ITEM) = *item;
}
CLEAN_AS(func_0209971c, PlayerRecord_SetHeldItem)

/* func_02099728 */
u16 *PlayerRecord_HeldItem(u8 *record)
{
    return player_record_u16(record, RECORD_HELD_ITEM);
}
CLEAN_AS(func_02099728, PlayerRecord_HeldItem)

/* func_02099734 */
PlayerPockets *PlayerRecord_Pockets(u8 *record)
{
    return player_record_pockets_at(record);
}
CLEAN_AS(func_02099734, PlayerRecord_Pockets)

/* func_02099740: set or clear flag 0. */
void PlayerRecord_SetFlag0(u8 *record, int set)
{
    if (set != 0) {
        PlayerRecord_SetFlag(record, RECORD_FLAG_0);
    } else {
        PlayerRecord_ClearFlag(record, RECORD_FLAG_0);
    }
}
CLEAN_AS(func_02099740, PlayerRecord_SetFlag0)

/* func_0209975c */
int PlayerRecord_Flag0(u8 *record)
{
    return PlayerRecord_TestFlag(record, RECORD_FLAG_0);
}
CLEAN_AS(func_0209975c, PlayerRecord_Flag0)

/* func_02099768: the two-bit state cleared on each new day (bits 6-7 of byte 0x243d). */
void PlayerRecord_SetDayState(u8 *record, int state)
{
    u8 *looks = &record[RECORD_LOOKS_2];
    *looks = (u8) ((*looks & ~LOOKS_DAY_STATE_MASK) | ((state & 3) << LOOKS_DAY_STATE_SHIFT));
}
CLEAN_AS(func_02099768, PlayerRecord_SetDayState)

/* func_02099784 */
u32 PlayerRecord_DayState(u8 *record)
{
    return (u32) record[RECORD_LOOKS_2] >> LOOKS_DAY_STATE_SHIFT;
}
CLEAN_AS(func_02099784, PlayerRecord_DayState)

/* func_02099794 */
void PlayerRecord_SetSunDate(u8 *record, PlayerRecordSunDate date)
{
    *player_record_u16(record, RECORD_SUN_DATE) = date.packed;
}
CLEAN_AS(func_02099794, PlayerRecord_SetSunDate)

/* func_020997a8: the packed date, as a signed halfword. */
s16 PlayerRecord_SunDate(u8 *record)
{
    return (s16) *player_record_u16(record, RECORD_SUN_DATE);
}
CLEAN_AS(func_020997a8, PlayerRecord_SunDate)

/* func_020997b4: the sun level, 0-7. */
void PlayerRecord_SetSunLevel(u8 *record, int level)
{
    u8 *looks = &record[RECORD_LOOKS_2];
    *looks = (u8) ((*looks & ~LOOKS_SUN_LEVEL_MASK) | ((level & 7) << LOOKS_SUN_LEVEL_SHIFT));
}
CLEAN_AS(func_020997b4, PlayerRecord_SetSunLevel)

/* func_020997d0 */
u32 PlayerRecord_SunLevel(u8 *record)
{
    return ((u32) record[RECORD_LOOKS_2] & LOOKS_SUN_LEVEL_MASK) >> LOOKS_SUN_LEVEL_SHIFT;
}
CLEAN_AS(func_020997d0, PlayerRecord_SunLevel)

/* func_020997e0: the hair colour, 0-7. */
void PlayerRecord_SetHairColor(u8 *record, int color)
{
    u8 *looks = &record[RECORD_LOOKS_2];
    *looks = (u8) ((*looks & ~LOOKS_HAIR_COLOR_MASK) | (color & LOOKS_HAIR_COLOR_MASK));
}
CLEAN_AS(func_020997e0, PlayerRecord_SetHairColor)

/* func_020997f8 */
u32 PlayerRecord_HairColor(u8 *record)
{
    return (u32) record[RECORD_LOOKS_2] & LOOKS_HAIR_COLOR_MASK;
}
CLEAN_AS(func_020997f8, PlayerRecord_HairColor)

/* func_02099808: the head's kind, 0-15. */
void PlayerRecord_SetHeadKind(u8 *record, int kind)
{
    u8 *looks = &record[RECORD_LOOKS];
    *looks = (u8) ((*looks & LOOKS_FACE_MASK) | ((kind & 0xf) << LOOKS_HEAD_KIND_SHIFT));
}
CLEAN_AS(func_02099808, PlayerRecord_SetHeadKind)

/* func_02099824 */
u32 PlayerRecord_HeadKind(const u8 *record)
{
    return (u32) record[RECORD_LOOKS] >> LOOKS_HEAD_KIND_SHIFT;
}
CLEAN_AS(func_02099824, PlayerRecord_HeadKind)

/* func_02099834: the face, 0-15. */
void PlayerRecord_SetFace(u8 *record, u32 face)
{
    u8 *looks = &record[RECORD_LOOKS];
    *looks = (u8) ((*looks & ~LOOKS_FACE_MASK) | (face & LOOKS_FACE_MASK));
}
CLEAN_AS(func_02099834, PlayerRecord_SetFace)

/* func_0209984c */
u32 PlayerRecord_Face(u8 *record)
{
    return (u32) record[RECORD_LOOKS] & LOOKS_FACE_MASK;
}
CLEAN_AS(func_0209984c, PlayerRecord_Face)

/* func_0209985c: the record's player's number among the town's records (0-3), or -1. */
int PlayerRecord_Number(u8 *record)
{
    return PlayerId_IndexInTown(PlayerRecord_Player(record));
}
CLEAN_AS(func_0209985c, PlayerRecord_Number)

/* func_02099870: the player: its town, id and name (laid out as a design's creator). */
DesignCreator *PlayerRecord_Player(u8 *record)
{
    return (DesignCreator *) (void *) (record + RECORD_PLAYER);
}
CLEAN_AS(func_02099870, PlayerRecord_Player)

/* func_0209987c: make a new player in the record: its name, id, byte 0x1c and town (this
 * town for NULL), its looks, flag 0, its bells and held item. Its pockets, designs, shop
 * points, record of items, dated letter, mother's letters and Wi-Fi data are reset; it gets
 * item 0x3884 at 0x240e, the first clothes, nothing on its head nor as part C, item 0x11fa at
 * 0x2410, a sun date of 1 January 2000, no birthday, a fresh savings account and date of last
 * play, and no byte for any villager. */
void PlayerRecord_NewPlayer(u8 *record, const void *name, int player_id, int byte_1c, const NpcIdHead *town, u8 face,
                            u8 head_kind, u8 hair_color, u8 sun_level, u8 flag0, int bells, const u16 *held_item)
{
    PlayerId_Make(PlayerRecord_Player(record), name, (u16) player_id, (u8) byte_1c, (const TownName *) town);
    PlayerRecord_SetFace(record, face);
    PlayerRecord_SetHeadKind(record, head_kind);
    PlayerRecord_SetHairColor(record, hair_color);
    PlayerRecord_SetSunLevel(record, sun_level);
    PlayerRecord_SetDayState(record, 0);
    PlayerRecord_SetFlag0(record, flag0);
    PlayerPockets_Init(player_record_pockets_at(record));
    PlayerPockets_SetBells(player_record_pockets_at(record), bells, PLAYER_POCKETS_USE_BAGS);
    *player_record_u16(record, RECORD_HELD_ITEM) = *held_item;
    PlayerDesigns_Reset((PlayerDesigns *) (void *) record, PlayerRecord_Player(record));
    ShopPoints_ResetA(record + RECORD_SHOP_POINTS);
    ItemRecord_Reset((ItemRecord *) (void *) (record + RECORD_ITEM_RECORD));
    MailDated_Init((MailDatedLetter *) (void *) (record + RECORD_DATED_LETTER));
    MomLetterState_Init((MomLetterState *) (void *) (record + RECORD_MOM_LETTERS));
    WifiAccount_Init((WifiAccount *) (void *) (record + RECORD_WIFI_ACCOUNT));
    WifiFriendList_ClearAll((WifiFriendList *) (void *) (record + RECORD_WIFI_FRIENDS));
    *player_record_u16(record, RECORD_ITEM_240E) = NEW_PLAYER_ITEM_240E;

    PlayerRecordSunDate sun_date = {SUN_DATE_PACK(0, 1, 1)};
    PlayerRecord_SetSunDate(record, sun_date);
    PlayerRecord_ClearBirthday(record);
    *player_record_u16(record, RECORD_CLOTHES) = NEW_PLAYER_CLOTHES;
    PlayerField2416_Reset((PlayerField2416 *) (void *) (record + RECORD_FIELD_2416));
    *player_record_u16(record, RECORD_PART_C_ITEM) = PLAYER_RECORD_NO_ITEM;
    *player_record_u16(record, RECORD_HEAD_ITEM) = PLAYER_RECORD_NO_ITEM;
    *player_record_u16(record, RECORD_ITEM_2410) = NEW_PLAYER_ITEM_2410;
    DayEvents_ClearMark((DayEventMark *) (void *) (record + RECORD_FIELD_2427));
    Savings_InitAccount((SavingsAccount *) (void *) (record + RECORD_SAVINGS));
    MotionSlots_Clear(record + RECORD_BYTES_23E8);
    Calendar_Today(PlayerRecord_LastPlayDate(record));
    MI_CpuFill8(record + RECORD_VILLAGER_BYTES, 0xff, PLAYER_RECORD_VILLAGER_BYTES);
}
CLEAN_AS(func_0209987c, PlayerRecord_NewPlayer)

/* func_02099a28: whether the record holds a player (its player id is set). */
int PlayerRecord_HasPlayer(u8 *record)
{
    return PlayerId_IsSet((DesignCreator *) (void *) (record + RECORD_PLAYER));
}
CLEAN_AS(func_02099a28, PlayerRecord_HasPlayer)

/* func_02099a38: empty the record: all zeros, then no player, empty pockets, record of items
 * and villagers' part, no held item, shop points reset, no item at 0x240e, no birthday
 * celebrated, no byte for any villager and no villager at 0x245c. */
void PlayerRecord_Clear(u8 *record)
{
    PlayerRecord_Zero(record);
    PlayerId_Clear(PlayerRecord_Player(record));
    PlayerPockets_Init(player_record_pockets_at(record));
    ItemRecord_Clear((ItemRecord *) (void *) (record + RECORD_ITEM_RECORD));
    VillagerPart_ClearAll((VillagerPart *) (void *) (record + RECORD_VILLAGER_PART));
    *player_record_u16(record, RECORD_HELD_ITEM) = PLAYER_RECORD_NO_ITEM;
    ShopPoints_ResetB(record + RECORD_SHOP_POINTS);
    *player_record_u16(record, RECORD_ITEM_240E) = PLAYER_RECORD_NO_ITEM;
    record[RECORD_BIRTHDAY_YEAR] = PLAYER_RECORD_NO_YEAR;
    MI_CpuFill8(record + RECORD_VILLAGER_BYTES, 0xff, PLAYER_RECORD_VILLAGER_BYTES);
    PlayerRecordVillager_Clear((PlayerRecordVillager *) (void *) (record + RECORD_VILLAGER));
}
CLEAN_AS(func_02099a38, PlayerRecord_Clear)

/* func_02099ac0 */
void PlayerRecord_Zero(u8 *record)
{
    MI_CpuFill8(record, 0, PLAYER_RECORD_SIZE);
}
CLEAN_AS(func_02099ac0, PlayerRecord_Zero)

/* func_02099ad0: the destructor: the parts' destructors, last part first. */
u8 *PlayerRecord_Destruct(u8 *record)
{
    PlayerPockets *pockets = player_record_pockets_at(record);

    PlayerId_Destruct(PlayerRecord_Player(record));
    PlayerRecordVillager_Destruct((PlayerRecordVillager *) (void *) (record + RECORD_VILLAGER));
    MomLetterState_Destruct((MomLetterState *) (void *) (record + RECORD_MOM_LETTERS));
    PairedTown_Destruct(record + RECORD_FIELD_242C);
    DayEvents_MarkDestruct((DayEventMark *) (void *) (record + RECORD_FIELD_2427));
    PlayerField2416_Destruct((PlayerField2416 *) (void *) (record + RECORD_FIELD_2416));
    ShopPoints_Destruct((u32) (uintptr_t) (record + RECORD_SHOP_POINTS));
    DailyBits_Destruct((DailyBits *) (void *) (record + RECORD_FIELD_23EC));
    Savings_DestructAccount((SavingsAccount *) (void *) (record + RECORD_SAVINGS));
    WifiFriendList_Destruct((WifiFriendList *) (void *) (record + RECORD_WIFI_FRIENDS));
    WifiAccount_Destruct((WifiAccount *) (void *) (record + RECORD_WIFI_ACCOUNT));
    VillagerPart_Destruct((VillagerPart *) (void *) (record + RECORD_VILLAGER_PART));
    MailDated_Destruct((MailDatedLetter *) (void *) (record + RECORD_DATED_LETTER));
    PlayerOptions_Destruct(record + RECORD_FIELD_1D3B);
    ItemRecord_Destruct((ItemRecord *) (void *) (record + RECORD_ITEM_RECORD));
    __cxa_vec_cleanup(pockets->items, PLAYER_POCKETS_SLOTS, sizeof(u16), func_020051b0);
    __cxa_vec_cleanup(pockets->letters, PLAYER_POCKETS_LETTERS, sizeof(Letter), func_02066688);
    PlayerDesigns_Destruct((PlayerDesigns *) (void *) record);
    return record;
}
CLEAN_AS(func_02099ad0, PlayerRecord_Destruct)

/* func_02099bc8: the constructor: the parts' constructors, first part first; the six items at
 * 0x2406-0x2410 are none. */
u8 *PlayerRecord_Construct(u8 *record)
{
    PlayerPockets *pockets = player_record_pockets_at(record);

    PlayerDesigns_Construct((PlayerDesigns *) (void *) record);
    __cxa_vec_ctor(pockets->letters, PLAYER_POCKETS_LETTERS, sizeof(Letter), func_02066694, func_02066688);
    __cxa_vec_ctor(pockets->items, PLAYER_POCKETS_SLOTS, sizeof(u16), func_02034ce0, func_020051b0);
    ItemRecord_Construct((ItemRecord *) (void *) (record + RECORD_ITEM_RECORD));
    PlayerOptions_Construct(record + RECORD_FIELD_1D3B);
    MailDated_Construct((MailDatedLetter *) (void *) (record + RECORD_DATED_LETTER));
    VillagerPart_Construct((VillagerPart *) (void *) (record + RECORD_VILLAGER_PART));
    WifiAccount_Construct((WifiAccount *) (void *) (record + RECORD_WIFI_ACCOUNT));
    WifiFriendList_Construct((WifiFriendList *) (void *) (record + RECORD_WIFI_FRIENDS));
    Savings_ConstructAccount((SavingsAccount *) (void *) (record + RECORD_SAVINGS));
    DailyBits_Construct((DailyBits *) (void *) (record + RECORD_FIELD_23EC));
    ShopPoints_ConstructAndReset((int) (uintptr_t) (record + RECORD_SHOP_POINTS));
    for (u32 offset = RECORD_HELD_ITEM; offset <= RECORD_ITEM_2410; offset += sizeof(u16)) {
        *player_record_u16(record, offset) = PLAYER_RECORD_NO_ITEM;
    }
    PlayerField2416_Construct((PlayerField2416 *) (void *) (record + RECORD_FIELD_2416));
    DayEvents_MarkConstruct((DayEventMark *) (void *) (record + RECORD_FIELD_2427));
    PairedTown_Construct(record + RECORD_FIELD_242C);
    MomLetterState_Construct((MomLetterState *) (void *) (record + RECORD_MOM_LETTERS));
    PlayerRecordVillager_Construct((PlayerRecordVillager *) (void *) (record + RECORD_VILLAGER));
    PlayerId_Construct(PlayerRecord_Player(record));
    return record;
}
CLEAN_AS(func_02099bc8, PlayerRecord_Construct)

/* ---- The villager at 0x245c (PlayerRecordVillager). Its byte 0x20 is how fond the villager
 * is of the player, -128 for none. */

static NpcId *player_record_villager_npc(PlayerRecordVillager *villager)
{
    return (NpcId *) (void *) villager->villager;
}

/* func_02099d08: a villager (`npc`) of `town` that is `fondness` fond of the player is noted
 * (func_0207d4bc), unless the villager noted already is fonder. With one chance in four it
 * has a present for the player, an item drawn from one of three item lists. Whether it was
 * noted; 0 for an invalid villager or a town that is not set. QUIRK: the present is drawn
 * also when the villager is then not noted. */
int PlayerRecordVillager_Note(PlayerRecordVillager *villager, const NpcId *npc, int fondness, const NpcIdHead *town)
{
    if (NpcId_IsValid(npc) == 0 || TownName_IsSet((const u16 *) town) == 0) {
        return 0;
    }

    u16 present = PLAYER_RECORD_NO_ITEM;
    if (MainRandom_Below(VILLAGER_PRESENT_DRAW) == 0) {
        int kind = data_020d19c4[MainRandom_Below(VILLAGER_PRESENT_LISTS)];
        PlayerRecordItemList list;
        ItemList_Construct((ItemList *) &list, kind, 0);
        /* QUIRK: the item is drawn from a plain copy of the list, and both are destroyed. */
        PlayerRecordItemList copy = list;
        u16 drawn;
        ItemLists_Draw(&drawn, (ItemList *) &copy, 0, 0, 1, 1, 0);
        present = drawn;
        ItemList_Destruct(&copy);
        ItemList_Destruct(&list);
    }

    if (PlayerRecordVillager_IsSet(villager) != 0 && fondness < (s8) villager->unk_20) {
        return 0;
    }
    PlayerRecordVillager_Set(villager, npc, (s8) fondness, town, &present);
    return 1;
}
CLEAN_AS(func_02099d08, PlayerRecordVillager_Note)

/* func_02099dcc */
void PlayerRecordVillager_Set(PlayerRecordVillager *villager, const NpcId *npc, s8 fondness, const NpcIdHead *town,
                              const u16 *item)
{
    TownName_Copy((TownName *) (void *) villager->town, (const TownName *) town);
    NpcId_Copy(player_record_villager_npc(villager), npc);
    villager->item = *item;
    villager->unk_20 = (u8) fondness;
}
CLEAN_AS(func_02099dcc, PlayerRecordVillager_Set)

/* func_02099df4: whether its town and villager are set. */
int PlayerRecordVillager_IsSet(PlayerRecordVillager *villager)
{
    return TownName_IsSet((const u16 *) (void *) villager->town) != 0 &&
           NpcId_IsValid(player_record_villager_npc(villager)) != 0;
}
CLEAN_AS(func_02099df4, PlayerRecordVillager_IsSet)

/* func_02099e18: no villager, no item, no fondness. */
void PlayerRecordVillager_Clear(PlayerRecordVillager *villager)
{
    TownName_Clear((TownName *) (void *) villager->town);
    NpcId_Clear(player_record_villager_npc(villager));
    villager->item = PLAYER_RECORD_NO_ITEM;
    villager->unk_20 = (u8) VILLAGER_NO_FONDNESS;
}
CLEAN_AS(func_02099e18, PlayerRecordVillager_Clear)

/* func_02099e40: the destructor. */
PlayerRecordVillager *PlayerRecordVillager_Destruct(PlayerRecordVillager *villager)
{
    NpcId_Destruct(player_record_villager_npc(villager));
    TownName_Destruct(villager->town);
    return villager;
}
CLEAN_AS(func_02099e40, PlayerRecordVillager_Destruct)

/* func_02099e58: the constructor; no item. */
PlayerRecordVillager *PlayerRecordVillager_Construct(PlayerRecordVillager *villager)
{
    TownName_Construct(villager->town);
    NpcId_Construct(player_record_villager_npc(villager));
    villager->item = PLAYER_RECORD_NO_ITEM;
    return villager;
}
CLEAN_AS(func_02099e58, PlayerRecordVillager_Construct)
