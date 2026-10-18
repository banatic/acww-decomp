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
#include "date_time.h"
#include "event_calendar.h"
#include "item_code.h"
#include "item_form.h"
#include "item_lists.h"
#include "letter.h"
#include "letter_grade.h"
#include "mail_text.h"
#include "main_random.h"
#include "message_reader.h"
#include "message_receiver.h"
#include "message_texts.h"
#include "number_text.h"
#include "player_id.h"
#include "text_base.h"
#include "town_name.h"
#include "villager_memory_entry.h"
#include "villager_post.h"
#include "word_archives.h"

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

static MailLetter *villager_mail_held(u8 *villager)
{
    return (MailLetter *) (void *) (villager + TOWN_VILLAGER_LETTER);
}

/* An item drawn from item list `kind`, as the game does it: from a copy of the list. */
static u16 villager_mail_draw(int kind)
{
    VillagerMailItemList list;
    ItemList_Construct((ItemList *) &list, kind, 0);
    VillagerMailItemList copy = list;
    u16 item;
    ItemLists_Draw(&item, (ItemList *) &copy, 0, 0, 1, 1, 0);
    ItemList_Destruct(&copy);
    ItemList_Destruct(&list);
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
    const DesignCreator *sender =
        (const DesignCreator *) (uintptr_t) (Letter_PlayerSender((Letter *) villager_mail_held(villager)));
    if (sender == NULL) {
        return -1;
    }
    DesignCreator id;
    PlayerId_CopyConstruct(&id, (DesignCreator *) sender);
    int index = -1;
    if (PlayerId_IsSet(&id)) {
        int found = VillagerMemory_IndexOf(villager, &id);
        VillagerMemory *memory = VillagerMemory_At(villager, found);
        if (memory != NULL && VillagerMemoryEntry_LetterHeld(memory)) {
            index = found;
        }
    }
    PlayerId_Destruct(&id);
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
        if (record != NULL && PlayerId_IsSet(PlayerRecord_Player(record))) {
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
    if (!PlayerId_IsSet(player) || PlayerId_WhichTown(player) != VILLAGER_MAIL_THIS_TOWN) {
        return;
    }
    if (VillagerMemory_Of(villager, player) == NULL) {
        return;
    }
    VillagerMailTownName town;
    TownNameText_Construct((TownNameText *) &town);
    if (TownName_IsSet((const u16 *) &data_021dc7aa)) {
        TownName_ToText((TownName *) &data_021dc7aa, (TextBase *) &town);
        MailText_SetPartText(VILLAGER_MAIL_SLOT_TOWN, &town);
    }
    VillagerPost_Send(data_020e1974, (u8) MainRandom_Below(VILLAGER_MAIL_FAREWELL_TEXTS), player, npc, NULL,
                      VILLAGER_MAIL_ANY_PAPER);
    TownNameText_Destruct((TownNameText *) &town);
}
CLEAN_AS(func_02080dc0, VillagerMail_SendFarewell)

/* func_02080e5c: VillagerMail_SendNewYearLetter for each of the town's players whose id is set.
 * QUIRK: the game also tests that the players' records are not at address 0. */
void VillagerMail_SendNewYearLetters(u8 *villager, const DateTime *today)
{
    for (int i = 0; i < VILLAGER_MAIL_TOWN_PLAYERS; i++) {
        u8 *record = PlayerRecords_TownRecord(data_021dc7bc, i);
        if (record != NULL && PlayerId_IsSet(PlayerRecord_Player(record))) {
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
    if (!PlayerId_IsSet(player) || PlayerId_WhichTown(player) != VILLAGER_MAIL_THIS_TOWN ||
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
    if (memory == NULL || VillagerMemoryEntry_Fondness(memory) < VILLAGER_MAIL_FONDNESS) {
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
        DateTime_Now(&now);
    } else {
        MI_CpuCopy8(today, &now, sizeof(now));
    }
    DateTime when;
    MI_CpuCopy8(&now, &when, sizeof(when));
    if (!EventCalendar_State(VILLAGER_MAIL_EVENT_NEW_YEAR, &when, 0) || now.hour < VILLAGER_MAIL_FIRST_HOUR) {
        return;
    }
    VillagerMemory *memory = villager_mail_day_memory(villager, player, 0);
    if (memory == NULL) {
        return;
    }
    VillagerMailNumber year;
    MessageText46_Construct((MessageText46 *) &year);
    NumberText_Format(&year, (u32) (now.year + VILLAGER_MAIL_YEAR_BASE), VILLAGER_MAIL_YEAR_DIGITS, 0, 0, 0);
    MailText_SetPartText(VILLAGER_MAIL_SLOT_YEAR, &year);
    if (VillagerPost_Send(data_020e197c, (u8) MainRandom_Below(VILLAGER_MAIL_LETTER_TEXTS), player, npc, NULL,
                          VILLAGER_MAIL_NEW_YEAR_PAPER)) {
        VillagerMemoryBits_SetNewYearLetter(memory);
    }
    MessageText46_Destruct((MessageText46 *) &year);
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
        DateTime_Now(&now);
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
    ItemList_Construct((ItemList *) &list, data_020cd448[MainRandom_Below(VILLAGER_MAIL_LETTER_TEXTS)], 0);
    VillagerMailItemList copy = list;
    u16 present;
    ItemLists_Draw(&present, (ItemList *) &copy, 0, 0, 1, 1, 0);
    ItemList_Destruct(&copy);
    const u16 *item = present != VILLAGER_MAIL_NO_ITEM ? &present : NULL;
    if (VillagerPost_Send(data_020e1988, (u8) MainRandom_Below(VILLAGER_MAIL_LETTER_TEXTS), player, npc, item,
                          VILLAGER_MAIL_ANY_PAPER)) {
        VillagerMemoryBits_SetBirthdayLetter(memory);
    }
    ItemList_Destruct(&list);
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
    if (!PlayerId_IsSet(player)) {
        return;
    }
    VillagerMemory *memory = VillagerMemory_Of(villager, player);
    int grade = LetterGrade_Grade(letter);
    VillagerMailName name;
    PlayerIdText_Construct((PlayerIdText *) &name);
    if (grade == VILLAGER_MAIL_GRADE_BAD) {
        VillagerLetter_Post(data_020e1994, (int) MainRandom_Below(VILLAGER_MAIL_LETTER_TEXTS), player, npc, NULL);
        if (memory != NULL) {
            VillagerMemoryEntry_ChangeFondness(memory, VILLAGER_MAIL_BAD_FONDNESS);
        }
    } else if (grade == VILLAGER_MAIL_GRADE_GOOD) {
        u16 present = VILLAGER_MAIL_NO_ITEM;
        VillagerMailLabel label;
        MessagePart_Construct((MessagePart *) &label);
        int first = 0;
        int number = 0;
        PlayerId_NameToText(player, (TextBase *) &name);
        MailText_SetPartText(VILLAGER_MAIL_SLOT_PLAYER, &name);
        for (int i = 0; i < VILLAGER_MAIL_REPLY_WORDS; i++) {
            const char *group = (const char *) (uintptr_t) WordArchives_Random(&number, i);
            TextBase_Clear(&label);
            u8 message = (u8) number;
            MessageReader_LoadDecoded(&label, &message, group);
            MailText_SetPartText(VILLAGER_MAIL_SLOT_WORDS + i, &label);
        }
        if (Letter_Item((const Letter *) letter) != VILLAGER_MAIL_NO_ITEM) {
            int length = LetterGrade_BodyLength(letter);
            if (length <= VILLAGER_MAIL_SHORT_LETTER) {
                if (MainRandom_Below(2) == 0) {
                    present = villager_mail_draw(VILLAGER_MAIL_SHORT_LIST);
                } else {
                    u16 drawn;
                    ItemLists_DrawRange(&drawn, 0x1518, 5, 0, 0, 0, 1, 0xa, 0, 1);
                    present = drawn;
                }
            } else if (length <= VILLAGER_MAIL_MIDDLE_LETTER) {
                present = villager_mail_draw(VILLAGER_MAIL_MIDDLE_LIST);
            } else {
                present = villager_mail_draw(data_020cd43c[MainRandom_Below(VILLAGER_MAIL_LETTER_TEXTS)]);
            }
            if (present != VILLAGER_MAIL_NO_ITEM) {
                first = VILLAGER_MAIL_REPLY_PRESENT_FIRST;
            }
        }
        VillagerLetter_PostDrawn(data_020e199c, first, VILLAGER_MAIL_REPLY_TEXTS, player, npc, &present);
        if (memory != NULL) {
            int delta = Letter_Item((const Letter *) letter) != VILLAGER_MAIL_NO_ITEM ? VILLAGER_MAIL_GIFT_FONDNESS
                                                                                      : VILLAGER_MAIL_GOOD_FONDNESS;
            VillagerMemoryEntry_ChangeFondness(memory, delta);
        }
        MessagePart_Destruct((MessagePart *) &label);
    }
    PlayerIdText_Destruct((PlayerIdText *) &name);
}
CLEAN_AS(func_02081144, VillagerMail_Reply)

/* func_02081398: whether the letter the villager holds is from `player` (a set player, the same
 * town, number and name) and its memory of the player has bit 0 set. */
int VillagerMail_HoldsLetterFrom(u8 *villager, const DesignCreator *player)
{
    const DesignCreator *sender =
        (const DesignCreator *) (uintptr_t) (Letter_PlayerSender((Letter *) villager_mail_held(villager)));
    if (!PlayerId_IsSet((DesignCreator *) player) || sender == NULL) {
        return 0;
    }
    DesignCreator held;
    PlayerId_CopyConstruct(&held, (DesignCreator *) sender);
    int result = 0;
    if (player->town_id == held.town_id && memcmp(player->town_name, held.town_name, sizeof(held.town_name)) == 0 &&
        PlayerId_SamePlayer(player, &held)) {
        VillagerMemory *memory = VillagerMemory_Of(villager, player);
        result = memory != NULL && VillagerMemoryEntry_LetterHeld(memory);
    }
    PlayerId_Destruct(&held);
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
    const DesignCreator *sender = (const DesignCreator *) (uintptr_t) Letter_PlayerSender((Letter *) letter);
    if (sender != NULL) {
        DesignCreator id;
        PlayerId_CopyConstruct(&id, (DesignCreator *) sender);
        if (PlayerId_IsSet(&id)) {
            memory = VillagerMemory_Of(villager, &id);
        }
        PlayerId_Destruct(&id);
    }
    if (memory == NULL) {
        return 0;
    }
    VillagerMemoryEntry_SetLetterHeld(memory);
    Letter_Assign((Letter *) villager_mail_held(villager), (const Letter *) letter);
    TownName_Copy((TownName *) ((NpcIdHead *) (void *) (villager + TOWN_VILLAGER_LETTER_TOWN)),
                  (const TownName *) &data_021dc7aa);
    u16 item = Letter_Item((const Letter *) letter);
    if (item != VILLAGER_MAIL_NO_ITEM) {
        u16 stands_for;
        ItemForm_ToPlaced(&stands_for, &item, 1);
        if (ItemCode_HasVariant(&stands_for) ||
            (stands_for >= VILLAGER_MAIL_WALLPAPER_FIRST && stands_for <= VILLAGER_MAIL_WALLPAPER_LAST) ||
            (stands_for >= VILLAGER_MAIL_CARPET_FIRST && stands_for <= VILLAGER_MAIL_CARPET_LAST)) {
            VillagerItems_Add(villager, &item);
        }
    }
    return 1;
}
CLEAN_AS(func_02081418, VillagerMail_Receive)
