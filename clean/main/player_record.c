/* Fields of one player's record (player_record.h). */
#include "player_record.h"

#include "calendar.h"
#include "clean.h"
#include "npc_id.h"
#include "player_records.h"
#include "savings.h"
#include "state_block.h"

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

extern int func_0209985c(u8 *record);   /* the record's player number (0-3), or -1 */
extern int func_020a1368(void);         /* the block of the letters kept (letter_store.h), or 0 */
extern void *func_02099870(u8 *record); /* the player's id (0x247e) */
extern int func_020951bc(void *player); /* whether the player id is set */

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
extern int func_02099df4(PlayerRecordVillager *villager); /* whether its town and villager are set */
extern void *func_02094fd4(PlayerRecordName *text);
extern void *func_02094fbc(PlayerRecordName *text);
extern void *func_020641c8(PlayerRecordText8 *text);
extern void *func_020641b0(PlayerRecordText8 *text);
extern void *func_020a8228(PlayerRecordLabel *label);
extern void *func_020a8210(PlayerRecordLabel *label);
extern void *func_02095074(void *player, PlayerRecordName *text); /* copy a player's name to a text */
extern int func_0203d7c4(int entry, void *text);                  /* set a message entry */
extern void func_020a8c1c(void *text);                            /* empty it */
extern int func_0209c54c(int *number, int word);                  /* a word for the letter, and a random number for it */
extern void *func_020b49d4(PlayerRecordLabel *label, const u8 *number, int word); /* load it */
extern void func_02064210(const u8 *town, PlayerRecordText8 *text);               /* a town's name as 8-bit text */
/* Write the letter from `villager` of `town` to `player`, its message drawn from `first` on
 * among `count`; whether it was written. */
extern int func_0207d3dc(void *letters, int first, int count, void *player, u8 *villager, u16 *item);
extern void func_02099e18(PlayerRecordVillager *villager); /* clear it */

/* What PlayerRecord_UpdateSinceLastPlay calls. */
extern Date *func_02099308(u8 *record);           /* the date of the last play (0x2400) */
extern u8 *func_02099670(u8 *record);             /* a field at 0x2416 */
extern u8 *func_0209967c(u8 *record);             /* a field at 0x23ec */
extern u8 *func_02099688(u8 *record);             /* a field at 0x242c */
extern void func_02099768(u8 *record, int value); /* set bits 6-7 of byte 0x243d */
extern void func_0209948c(u8 *record);
extern void func_02088810(u8 *field); /* letters on flags 0x17-0x1a of the record */
extern void func_020889a8(void);      /* a letter on flag 0x36 of the current record */
extern void func_020887f8(u8 *field); /* clear its bytes 4-11 */
extern void func_02088ac8(u8 *field); /* clear bits 2-5 of its byte 16 */
extern void func_020882f0(u8 *object);

static u32 *player_record_flags(u8 *record)
{
    return (u32 *) (void *) (record + RECORD_FLAGS);
}

static int player_number(u8 *record)
{
    int number = func_0209985c(record);
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
MailLetter *PlayerRecord_KeptLetters(u8 *record)
{
    int number = player_number(record);
    if (number == -1) {
        return NULL;
    }
    int block = func_020a1368();
    if (block == 0) {
        return NULL;
    }
    return (MailLetter *) (uintptr_t) (u32) (block + KEPT_LETTERS_SIZE * number);
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
    void *player = func_02099870(record);
    if (!func_020951bc(player)) {
        return;
    }
    PlayerRecordVillager *villager = PlayerRecord_Villager(record);
    if (!func_02099df4(villager)) {
        return;
    }
    PlayerRecordName name;
    PlayerRecordText8 town;
    PlayerRecordLabel word;
    func_02094fd4(&name);
    func_020641c8(&town);
    func_020a8228(&word);

    int first = 0;
    int count = 10;
    if (villager->item != NO_ITEM) {
        first = 10;
        count = 5;
    }

    func_02095074(player, &name);
    func_0203d7c4(LETTER_ENTRY_PLAYER, &name);
    func_020a8c1c(&name);
    NpcId_FormatName((const NpcId *) (void *) villager->villager, (char *) &name);
    func_0203d7c4(LETTER_ENTRY_VILLAGER, &name);

    int number = 0;
    for (int i = 0; i < LETTER_WORDS; i++) {
        int text = func_0209c54c(&number, i);
        func_020a8c1c(&word);
        u8 digit = (u8) number;
        func_020b49d4(&word, &digit, text);
        func_0203d7c4(LETTER_ENTRY_FIRST_WORD + i, &word);
    }

    func_02064210(villager->town, &town);
    func_0203d7c4(LETTER_ENTRY_TOWN, &town);
    if (func_0207d3dc(data_020e3128, first, count, player, villager->villager, &villager->item)) {
        func_02099e18(villager);
    }
    func_020a8210(&word);
    func_020641b0(&town);
    func_02094fbc(&name);
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
    Date *last = func_02099308(self);
    int days = Calendar_DaysFrom(&today, last);

    Savings_PayInterest((today.month - last->month) + 12 * (today.year - last->year));
    Savings_SendMilestoneLetter(days);
    Savings_SendRankLetter(days);
    func_02088810(func_02099670(self));
    /* QUIRK: the field is asked for once more, unused. */
    func_02099670(self);
    func_020889a8();

    if (days != 0) {
        func_0209948c(self);
    }
    if (today.year != PlayerRecord_BirthdayYear(self)) {
        PlayerRecord_SetBirthdayYear(self, PLAYER_RECORD_NO_YEAR);
    }
    if (days != 0) {
        func_020887f8(func_0209967c(self));
        func_02099768(self, 0);
        func_02088ac8(func_02099670(self));
        StateBlock_ClearFlag(data_021dc7a8, STATE_FLAG_CLEARED_ON_NEW_DAY);
    }
    if (days < 0) {
        func_020882f0(func_02099688(self));
        func_020882f0((u8 *) data_021dc7a8 + STATE_OBJECT_173E2);
    }

    Calendar_Today(func_02099308(self));
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
