/* The letters one of the town's villagers gets from the players and writes to them
 * (villager_mail.h). */
#include "villager_mail.h"

#include <string.h>

#include "clean.h"
#include "npc_id.h"
#include "player_record.h"
#include "player_records.h"
#include "town_villager.h"
#include "villager_items.h"
#include "villager_letter.h"
#include "villager_memories.h"
#include "villager_memory_bits.h"

#define VILLAGER_MAIL_TOWN_PLAYERS 4
#define VILLAGER_MAIL_NO_ITEM 0xfff1
/* PlayerRecord_TestFlag: a record that gets no letters from villagers. */
#define VILLAGER_MAIL_RECORD_FLAG 1
/* func_02094ffc of a player of this town. */
#define VILLAGER_MAIL_THIS_TOWN 0
/* How fond the villager must be of a player to write on new year's day and its birthday, and
 * the hour from which it does. */
#define VILLAGER_MAIL_FONDNESS 0x40
#define VILLAGER_MAIL_FIRST_HOUR 6
/* The calendar's event of new year's day (func_0203fc78). */
#define VILLAGER_MAIL_EVENT_NEW_YEAR 0x13
/* The texts each letter is drawn from, and its paper (-1: the personality's). */
#define VILLAGER_MAIL_FAREWELL_TEXTS 5
#define VILLAGER_MAIL_LETTER_TEXTS 3
#define VILLAGER_MAIL_ANY_PAPER (-1)
#define VILLAGER_MAIL_NEW_YEAR_PAPER 2
/* The text slots (func_0203d7c4) the letters fill: the player's name, then words. */
#define VILLAGER_MAIL_SLOT_PLAYER 0
#define VILLAGER_MAIL_SLOT_TOWN 2
#define VILLAGER_MAIL_SLOT_YEAR 2
#define VILLAGER_MAIL_SLOT_WORDS 2
#define VILLAGER_MAIL_REPLY_WORDS 6
/* A reply to a good letter: its texts, 10 more of them with a present. */
#define VILLAGER_MAIL_REPLY_TEXTS 10
#define VILLAGER_MAIL_REPLY_PRESENT_FIRST 10
/* How the fondness changes with a reply. */
#define VILLAGER_MAIL_BAD_FONDNESS (-3)
#define VILLAGER_MAIL_GOOD_FONDNESS 3
#define VILLAGER_MAIL_GIFT_FONDNESS 5
/* The present of a reply to a good letter with an item, by how long the letter is: up to 0x20
 * characters one of item list 2 or a drawn item, up to 0x2f one of list 0, else one of the
 * lists data_020cd43c names. */
#define VILLAGER_MAIL_SHORT_LETTER 0x20
#define VILLAGER_MAIL_MIDDLE_LETTER 0x2f
#define VILLAGER_MAIL_SHORT_LIST 2
#define VILLAGER_MAIL_MIDDLE_LIST 0
/* An item that came with a letter joins the house's items when func_0204bcdc accepts it, or it
 * is a wallpaper or a carpet. */
#define VILLAGER_MAIL_WALLPAPER_FIRST 0x1100
#define VILLAGER_MAIL_WALLPAPER_LAST 0x1143
#define VILLAGER_MAIL_CARPET_FIRST 0x1144
#define VILLAGER_MAIL_CARPET_LAST 0x1187
#define VILLAGER_MAIL_YEAR_BASE 2000
#define VILLAGER_MAIL_YEAR_DIGITS 4

/* The text objects the letters are filled with, as big as the game keeps them on its stack: a
 * player's name (func_02094fd4), a label (func_020a8228), a town's name (func_020641c8) and a
 * number (func_020b5630). */
typedef struct VillagerMailName {
    u32 words[8];
} VillagerMailName;
typedef struct VillagerMailLabel {
    u32 words[0x5c / 4];
} VillagerMailLabel;
typedef struct VillagerMailTownName {
    u32 words[8];
} VillagerMailTownName;
typedef struct VillagerMailNumber {
    u32 words[16];
} VillagerMailNumber;
/* An item list: func_02063ccc constructs it, func_020638d4 draws an item of it, func_02063cc8
 * destroys it. */
typedef struct VillagerMailItemList {
    int kind;
    int group;
} VillagerMailItemList;

extern const char data_020e1974[]; /* "byebye" */
extern const char data_020e197c[]; /* "ev_newyear" */
extern const char data_020e1988[]; /* "ev_birth" */
extern const char data_020e1994[]; /* "re_bad" */
extern const char data_020e199c[]; /* "re_normal" */
/* The item lists of a birthday present and of a present for a long letter, three each. */
extern const int data_020cd448[VILLAGER_MAIL_LETTER_TEXTS];
extern const int data_020cd43c[VILLAGER_MAIL_LETTER_TEXTS];
extern const NpcIdHead data_021dc7aa; /* this town */
extern u8 data_021dc7bc[];            /* the town's four players' records */

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern u32 func_020644cc(int bound); /* a random number below `bound` */
extern void func_0209e474(DateTime *now);
extern int func_0203fc78(int event, const DateTime *when, int arg); /* whether the event is on the date */
/* A player id: constructed from another, destroyed; whether it is set; whether two are the same
 * player; whose town it is (VILLAGER_MAIL_THIS_TOWN, 1 another, 2 none). */
extern DesignCreator *func_0209527c(DesignCreator *id, const DesignCreator *from);
extern int func_0209526c(DesignCreator *id);
extern int func_020951bc(const DesignCreator *id);
extern int func_0209518c(const DesignCreator *a, const DesignCreator *b);
extern int func_02094ffc(const DesignCreator *id);
/* A memory's bit 0 (a letter of the player held), set; its fondness, and changed (within -128 to
 * 127). */
extern int func_02081cd8(const VillagerMemory *memory);
extern void func_02081cc4(VillagerMemory *memory);
extern int func_02081d20(const VillagerMemory *memory);
extern s8 func_02081cec(VillagerMemory *memory, int delta);
/* A letter's sender (NULL for none), its item, the length of its text, its grade
 * (VILLAGER_MAIL_GRADE_*), and a copy of it. */
extern const DesignCreator *func_02065f7c(MailLetter *letter);
extern u16 func_02065f18(MailLetter *letter);
extern int func_0206d7a0(MailLetter *letter);
extern int func_0206d7ac(MailLetter *letter);
extern int func_02066830(MailLetter *dst, MailLetter *src);
/* A letter from the villager `npc` of message `text` of the group `name`, carrying `item` when it
 * is not NULL, on paper `paper`, delivered to `player`; whether it was. */
extern int func_0205a240(const char *name, int text, const DesignCreator *player, const NpcId *npc, const u16 *item,
                         int paper);
extern int func_0203d7c4(int slot, void *text); /* a text slot of the letters set */
extern void *func_02094fd4(VillagerMailName *text);
extern void *func_02094fbc(VillagerMailName *text);
extern void *func_02095074(const DesignCreator *player, VillagerMailName *text);
extern void *func_020a8228(VillagerMailLabel *label);
extern void *func_020a8210(VillagerMailLabel *label);
extern void func_020a8c1c(VillagerMailLabel *label);
extern int func_020b49d4(VillagerMailLabel *label, const u8 *message, const char *group);
/* Word `word` of a reply: the group it comes from, and a random message of it in `number`. */
extern const char *func_0209c54c(int *number, int word);
extern void *func_020641c8(VillagerMailTownName *text);
extern void *func_020641b0(VillagerMailTownName *text);
extern u32 func_02064294(const NpcIdHead *town); /* whether it is set */
extern void func_02064210(const NpcIdHead *town, VillagerMailTownName *text);
extern void func_020642d0(NpcIdHead *dst, const NpcIdHead *src);
extern void *func_020b5630(VillagerMailNumber *text);
extern void *func_020b5618(VillagerMailNumber *text);
extern int func_020b45d0(VillagerMailNumber *text, u32 value, int digits, int a, int b, int c);
extern void func_02063ccc(VillagerMailItemList *list, int kind, int group);
extern void func_020638d4(u16 *item, VillagerMailItemList *list, int a, int b, int c, int d, int e);
extern void func_02063cc8(VillagerMailItemList *list);
extern void func_02063414(u16 *item, int a, int b, int c, int d, int e, int f, int g, int h, int i);
extern void func_02061b1c(u16 *out, const u16 *code, int always); /* the item a code stands for */
extern int func_0204bcdc(const u16 *item);

static MailLetter *villager_mail_held(u8 *villager)
{
    return (MailLetter *) (void *) (villager + TOWN_VILLAGER_LETTER);
}

/* An item drawn from item list `kind`, as the game does it: from a copy of the list. */
static u16 villager_mail_draw(int kind)
{
    VillagerMailItemList list;
    func_02063ccc(&list, kind, 0);
    VillagerMailItemList copy = list;
    u16 item;
    func_020638d4(&item, &copy, 0, 0, 1, 1, 0);
    func_02063cc8(&copy);
    func_02063cc8(&list);
    return item;
}

/* func_02080cf0: whether the villager holds a letter it can answer (VillagerMail_HeldLetterMemory). */
int VillagerMail_HasHeldLetter(u8 *villager)
{
    return VillagerMail_HeldLetterMemory(villager) != -1;
}
CLEAN_AS(func_02080cf0, VillagerMail_HasHeldLetter)

/* func_02080d0c: the villager's memory of the sender of the letter it holds, when the letter has
 * a set sender the villager knows and the memory's bit 0 is set; -1 otherwise. */
int VillagerMail_HeldLetterMemory(u8 *villager)
{
    const DesignCreator *sender = func_02065f7c(villager_mail_held(villager));
    if (sender == NULL) {
        return -1;
    }
    DesignCreator id;
    func_0209527c(&id, sender);
    int index = -1;
    if (func_020951bc(&id)) {
        int found = VillagerMemory_IndexOf(villager, &id);
        VillagerMemory *memory = VillagerMemory_At(villager, found);
        if (memory != NULL && func_02081cd8(memory)) {
            index = found;
        }
    }
    func_0209526c(&id);
    return index;
}
CLEAN_AS(func_02080d0c, VillagerMail_HeldLetterMemory)

/* func_02080d70: a farewell to each of the town's players whose id is set, when the villager's
 * NpcId is valid.
 * QUIRK: the game also tests that the players' records are not at address 0. */
void VillagerMail_SendFarewells(u8 *villager)
{
    if (!NpcId_IsValid(TownVillager_NpcId(villager))) {
        return;
    }
    for (int i = 0; i < VILLAGER_MAIL_TOWN_PLAYERS; i++) {
        u8 *record = PlayerRecords_TownRecord(data_021dc7bc, i);
        if (record != NULL && func_020951bc(PlayerRecord_Player(record))) {
            VillagerMail_SendFarewell(villager, record);
        }
    }
}
CLEAN_AS(func_02080d70, VillagerMail_SendFarewells)

/* func_02080dc0: the villager's farewell ("byebye", with this town's name in slot 2 when it is
 * set) to the player of `record`, when the player is set, of this town and known to it.
 * QUIRK: the game also tests that this town's head is not at address 0. */
void VillagerMail_SendFarewell(u8 *villager, u8 *record)
{
    NpcId *npc = TownVillager_NpcId(villager);
    if (!NpcId_IsValid(npc) || record == NULL) {
        return;
    }
    DesignCreator *player = PlayerRecord_Player(record);
    if (!func_020951bc(player) || func_02094ffc(player) != VILLAGER_MAIL_THIS_TOWN) {
        return;
    }
    if (VillagerMemory_Of(villager, player) == NULL) {
        return;
    }
    VillagerMailTownName town;
    func_020641c8(&town);
    if (func_02064294(&data_021dc7aa)) {
        func_02064210(&data_021dc7aa, &town);
        func_0203d7c4(VILLAGER_MAIL_SLOT_TOWN, &town);
    }
    func_0205a240(data_020e1974, (u8) func_020644cc(VILLAGER_MAIL_FAREWELL_TEXTS), player, npc, NULL, VILLAGER_MAIL_ANY_PAPER);
    func_020641b0(&town);
}
CLEAN_AS(func_02080dc0, VillagerMail_SendFarewell)

/* func_02080e5c: VillagerMail_SendNewYearLetter for each of the town's players whose id is set.
 * QUIRK: the game also tests that the players' records are not at address 0. */
void VillagerMail_SendNewYearLetters(u8 *villager, const DateTime *today)
{
    for (int i = 0; i < VILLAGER_MAIL_TOWN_PLAYERS; i++) {
        u8 *record = PlayerRecords_TownRecord(data_021dc7bc, i);
        if (record != NULL && func_020951bc(PlayerRecord_Player(record))) {
            VillagerMail_SendNewYearLetter(villager, record, today);
        }
    }
}
CLEAN_AS(func_02080e5c, VillagerMail_SendNewYearLetters)

/* The checks both day letters make of the player of `record` (the current one when NULL): a
 * valid villager, a record, its player set and of this town, its flag 1 clear. The record's
 * player, or NULL. */
static DesignCreator *villager_mail_day_player(NpcId *npc, u8 **record)
{
    if (*record == NULL) {
        *record = PlayerRecords_Current();
    }
    if (!NpcId_IsValid(npc) || *record == NULL) {
        return NULL;
    }
    DesignCreator *player = PlayerRecord_Player(*record);
    if (!func_020951bc(player) || func_02094ffc(player) != VILLAGER_MAIL_THIS_TOWN ||
        PlayerRecord_TestFlag(*record, VILLAGER_MAIL_RECORD_FLAG) != 0) {
        return NULL;
    }
    return player;
}

/* The villager's memory of the player, when it is fond enough of the player and has not written
 * it today the birthday letter (with `birthday`) or the new year letter; else NULL. */
static VillagerMemory *villager_mail_day_memory(u8 *villager, DesignCreator *player, int birthday)
{
    VillagerMemory *memory = VillagerMemory_Of(villager, player);
    if (memory == NULL || func_02081d20(memory) < VILLAGER_MAIL_FONDNESS) {
        return NULL;
    }
    int sent = birthday ? VillagerMemoryBits_BirthdayLetterSent(memory) : (int) VillagerMemoryBits_NewYearLetterSent(memory);
    return sent ? NULL : memory;
}

/* func_02080ea4: the villager's new year letter ("ev_newyear", the year in slot 2, paper 2) to
 * the player of `record` (the current one when NULL) on new year's day from 6 o'clock of `today`
 * (the clock when NULL), when the villager is fond enough of the player and has not written it
 * today; bit 13 of its memory set once it is delivered. */
void VillagerMail_SendNewYearLetter(u8 *villager, u8 *record, const DateTime *today)
{
    NpcId *npc = TownVillager_NpcId(villager);
    DesignCreator *player = villager_mail_day_player(npc, &record);
    if (player == NULL) {
        return;
    }
    DateTime now = {0};
    if (today == NULL) {
        func_0209e474(&now);
    } else {
        MI_CpuCopy8(today, &now, sizeof(now));
    }
    DateTime when;
    MI_CpuCopy8(&now, &when, sizeof(when));
    if (!func_0203fc78(VILLAGER_MAIL_EVENT_NEW_YEAR, &when, 0) || now.hour < VILLAGER_MAIL_FIRST_HOUR) {
        return;
    }
    VillagerMemory *memory = villager_mail_day_memory(villager, player, 0);
    if (memory == NULL) {
        return;
    }
    VillagerMailNumber year;
    func_020b5630(&year);
    func_020b45d0(&year, (u32) (now.year + VILLAGER_MAIL_YEAR_BASE), VILLAGER_MAIL_YEAR_DIGITS, 0, 0, 0);
    func_0203d7c4(VILLAGER_MAIL_SLOT_YEAR, &year);
    if (func_0205a240(data_020e197c, (u8) func_020644cc(VILLAGER_MAIL_LETTER_TEXTS), player, npc, NULL,
                      VILLAGER_MAIL_NEW_YEAR_PAPER)) {
        VillagerMemoryBits_SetNewYearLetter(memory);
    }
    func_020b5618(&year);
}
CLEAN_AS(func_02080ea4, VillagerMail_SendNewYearLetter)

/* func_02080fc0: VillagerMail_SendBirthdayLetter for each of the town's players.
 * QUIRK: the game also tests that the players' records are not at address 0. */
void VillagerMail_SendBirthdayLetters(u8 *villager, const DateTime *today)
{
    for (int i = 0; i < VILLAGER_MAIL_TOWN_PLAYERS; i++) {
        u8 *record = PlayerRecords_TownRecord(data_021dc7bc, i);
        if (record != NULL) {
            VillagerMail_SendBirthdayLetter(villager, record, today);
        }
    }
}
CLEAN_AS(func_02080fc0, VillagerMail_SendBirthdayLetters)

/* func_02080ff8: the villager's birthday letter ("ev_birth", with a present drawn from one of
 * the lists of data_020cd448 when one comes out) to the player of `record` (the current one when
 * NULL) on the player's birthday from 6 o'clock of `today` (the clock when NULL), when the
 * villager is fond enough of the player and has not written it today; bit 12 of its memory set
 * once it is delivered. */
void VillagerMail_SendBirthdayLetter(u8 *villager, u8 *record, const DateTime *today)
{
    NpcId *npc = TownVillager_NpcId(villager);
    DesignCreator *player = villager_mail_day_player(npc, &record);
    if (player == NULL) {
        return;
    }
    DateTime now = {0};
    const u8 *birthday = PlayerRecord_Birthday(record); /* day, month */
    if (today == NULL) {
        func_0209e474(&now);
    } else {
        MI_CpuCopy8(today, &now, sizeof(now));
    }
    if (birthday[1] != now.month || birthday[0] != now.day || now.hour < VILLAGER_MAIL_FIRST_HOUR) {
        return;
    }
    VillagerMemory *memory = villager_mail_day_memory(villager, player, 1);
    if (memory == NULL) {
        return;
    }
    VillagerMailItemList list;
    func_02063ccc(&list, data_020cd448[func_020644cc(VILLAGER_MAIL_LETTER_TEXTS)], 0);
    VillagerMailItemList copy = list;
    u16 present;
    func_020638d4(&present, &copy, 0, 0, 1, 1, 0);
    func_02063cc8(&copy);
    const u16 *item = present != VILLAGER_MAIL_NO_ITEM ? &present : NULL;
    if (func_0205a240(data_020e1988, (u8) func_020644cc(VILLAGER_MAIL_LETTER_TEXTS), player, npc, item,
                      VILLAGER_MAIL_ANY_PAPER)) {
        VillagerMemoryBits_SetBirthdayLetter(memory);
    }
    func_02063cc8(&list);
}
CLEAN_AS(func_02080ff8, VillagerMail_SendBirthdayLetter)

/* func_02081144: the villager's answer to a player's letter, when the record's flag 1 is clear,
 * the villager's NpcId valid and the player set. A bad letter gets "re_bad" and the villager
 * likes the player 3 less; a good one "re_normal" with the player's name and six drawn words,
 * a present when the letter carried an item, and the villager likes the player 3 more (5 with
 * an item). A letter graded neither gets nothing. */
void VillagerMail_Reply(u8 *villager, u8 *record, MailLetter *letter)
{
    NpcId *npc = TownVillager_NpcId(villager);
    if (record == NULL || PlayerRecord_TestFlag(record, VILLAGER_MAIL_RECORD_FLAG) != 0) {
        return;
    }
    if (!NpcId_IsValid(npc)) {
        return;
    }
    DesignCreator *player = PlayerRecord_Player(record);
    if (!func_020951bc(player)) {
        return;
    }
    VillagerMemory *memory = VillagerMemory_Of(villager, player);
    int grade = func_0206d7ac(letter);
    VillagerMailName name;
    func_02094fd4(&name);
    if (grade == VILLAGER_MAIL_GRADE_BAD) {
        VillagerLetter_Post(data_020e1994, (int) func_020644cc(VILLAGER_MAIL_LETTER_TEXTS), player, npc, NULL);
        if (memory != NULL) {
            func_02081cec(memory, VILLAGER_MAIL_BAD_FONDNESS);
        }
    } else if (grade == VILLAGER_MAIL_GRADE_GOOD) {
        u16 present = VILLAGER_MAIL_NO_ITEM;
        VillagerMailLabel label;
        func_020a8228(&label);
        int first = 0;
        int number = 0;
        func_02095074(player, &name);
        func_0203d7c4(VILLAGER_MAIL_SLOT_PLAYER, &name);
        for (int i = 0; i < VILLAGER_MAIL_REPLY_WORDS; i++) {
            const char *group = func_0209c54c(&number, i);
            func_020a8c1c(&label);
            u8 message = (u8) number;
            func_020b49d4(&label, &message, group);
            func_0203d7c4(VILLAGER_MAIL_SLOT_WORDS + i, &label);
        }
        if (func_02065f18(letter) != VILLAGER_MAIL_NO_ITEM) {
            int length = func_0206d7a0(letter);
            if (length <= VILLAGER_MAIL_SHORT_LETTER) {
                if (func_020644cc(2) == 0) {
                    present = villager_mail_draw(VILLAGER_MAIL_SHORT_LIST);
                } else {
                    u16 drawn;
                    func_02063414(&drawn, 0x1518, 5, 0, 0, 0, 1, 0xa, 0, 1);
                    present = drawn;
                }
            } else if (length <= VILLAGER_MAIL_MIDDLE_LETTER) {
                present = villager_mail_draw(VILLAGER_MAIL_MIDDLE_LIST);
            } else {
                present = villager_mail_draw(data_020cd43c[func_020644cc(VILLAGER_MAIL_LETTER_TEXTS)]);
            }
            if (present != VILLAGER_MAIL_NO_ITEM) {
                first = VILLAGER_MAIL_REPLY_PRESENT_FIRST;
            }
        }
        VillagerLetter_PostDrawn(data_020e199c, first, VILLAGER_MAIL_REPLY_TEXTS, player, npc, &present);
        if (memory != NULL) {
            int delta =
                func_02065f18(letter) != VILLAGER_MAIL_NO_ITEM ? VILLAGER_MAIL_GIFT_FONDNESS : VILLAGER_MAIL_GOOD_FONDNESS;
            func_02081cec(memory, delta);
        }
        func_020a8210(&label);
    }
    func_02094fbc(&name);
}
CLEAN_AS(func_02081144, VillagerMail_Reply)

/* func_02081398: whether the letter the villager holds is from `player` (a set player, the same
 * town, number and name) and its memory of the player has bit 0 set. */
int VillagerMail_HoldsLetterFrom(u8 *villager, const DesignCreator *player)
{
    const DesignCreator *sender = func_02065f7c(villager_mail_held(villager));
    if (!func_020951bc(player) || sender == NULL) {
        return 0;
    }
    DesignCreator held;
    func_0209527c(&held, sender);
    int result = 0;
    if (player->town_id == held.town_id && memcmp(player->town_name, held.town_name, sizeof(held.town_name)) == 0 &&
        func_0209518c(player, &held)) {
        VillagerMemory *memory = VillagerMemory_Of(villager, player);
        result = memory != NULL && func_02081cd8(memory);
    }
    func_0209526c(&held);
    return result;
}
CLEAN_AS(func_02081398, VillagerMail_HoldsLetterFrom)

/* func_02081418: a player's letter given to the villager, when the villager knows its set
 * sender: the memory's bit 0 set, the letter kept with this town as the town it came in, and its
 * item added to the house's items (VillagerItems_Add) when the item it stands for is one
 * func_0204bcdc accepts, a wallpaper or a carpet. Whether the villager took it. */
int VillagerMail_Receive(u8 *villager, MailLetter *letter)
{
    VillagerMemory *memory = NULL;
    const DesignCreator *sender = func_02065f7c(letter);
    if (sender != NULL) {
        DesignCreator id;
        func_0209527c(&id, sender);
        if (func_020951bc(&id)) {
            memory = VillagerMemory_Of(villager, &id);
        }
        func_0209526c(&id);
    }
    if (memory == NULL) {
        return 0;
    }
    func_02081cc4(memory);
    func_02066830(villager_mail_held(villager), letter);
    func_020642d0((NpcIdHead *) (void *) (villager + TOWN_VILLAGER_LETTER_TOWN), &data_021dc7aa);
    u16 item = func_02065f18(letter);
    if (item != VILLAGER_MAIL_NO_ITEM) {
        u16 stands_for;
        func_02061b1c(&stands_for, &item, 1);
        if (func_0204bcdc(&stands_for) ||
            (stands_for >= VILLAGER_MAIL_WALLPAPER_FIRST && stands_for <= VILLAGER_MAIL_WALLPAPER_LAST) ||
            (stands_for >= VILLAGER_MAIL_CARPET_FIRST && stands_for <= VILLAGER_MAIL_CARPET_LAST)) {
            VillagerItems_Add(villager, &item);
        }
    }
    return 1;
}
CLEAN_AS(func_02081418, VillagerMail_Receive)
