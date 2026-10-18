/* Who gave each item of the record (museum_record.h). */
#include "museum_record.h"

#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "clean.h"
#include "date_time.h"
#include "state_block.h"
#include "furniture_info.h"
#include "letter.h"
#include "mail.h"
#include "mail_text.h"
#include "player_id.h"
#include "player_record.h"
#include "player_records.h"
#include "town_name.h"

static_assert(offsetof(MuseumRecord, group_b) == 0x1b, "group B");
static_assert(offsetof(MuseumRecord, group_c) == 0x38, "group C");
static_assert(offsetof(MuseumRecord, group_d) == 0x55, "group D");
static_assert(offsetof(MuseumRecord, day) == 0x60, "date");

/* The state block's flag set once the letters are posted. */
#define LETTERS_SENT_FLAG 3
/* The item the letters carry. */
#define LETTER_ITEM 0x3870
/* The message entry the town's name is put in for the letters. */
#define TOWN_NAME_ENTRY 2

#define PLAYERS 4

extern u32 data_021dc7a8[];        /* the state block (state_block.h) */
extern const u8 data_021dc7aa[];   /* the town, inside it */
extern u8 data_021dc7bc[];         /* the four players' records (0x249c bytes each), inside it */
extern const char data_020e17b4[]; /* "sp_npc_owl": the letters' sender */
extern const int data_020e17ac;    /* 4 */
extern const int data_020e17b0;    /* 0x10 */

extern int FX_Div(int numerator, int denominator);

typedef struct Text8 {
    u32 words[8];
} Text8;

/* The code of entry `index` of each group. */
static u16 group_a_item(unsigned int index)
{
    return (u16) (MUSEUM_A_FIRST + index * 4);
}

static u16 group_b_item(unsigned int index)
{
    return (u16) (MUSEUM_B_FIRST + index);
}

static u16 group_c_item(unsigned int index)
{
    return (u16) (MUSEUM_C_FIRST + index);
}

static u16 group_d_item(unsigned int index)
{
    return (u16) (MUSEUM_D_FIRST + index * 4);
}

/* Where entry `index`'s four bits are in its byte. */
static int bits_shift(int index)
{
    return (index & 1) * 4;
}

static u8 *locate(MuseumRecord *record, const u16 *item, int *index)
{
    return (u8 *) (uintptr_t) MuseumRecord_Locate(record, item, index);
}

/* func_02070d74: how many group A items whose kind (func_020535f0) is `kind` were given. */
int MuseumRecord_CountGroupAKind(MuseumRecord *record, int kind)
{
    int count = 0;
    for (unsigned int i = 0; i < MUSEUM_A_ITEMS; i++) {
        u16 item = group_a_item(i);
        if (kind == FurnitureInfo_MuseumKind(&item) && MuseumRecord_IsGiven(record, &item) != 0) {
            count++;
        }
    }
    return count;
}
CLEAN_AS(func_02070d74, MuseumRecord_CountGroupAKind)

/* func_02070dc0: the share of the 184 items given, in percent (20.12); groups D, B, C then A. */
int MuseumRecord_PercentGiven(MuseumRecord *record)
{
    int given = 0;
    u16 item;
    for (unsigned int i = 0; i < MUSEUM_D_ITEMS; i++) {
        item = group_d_item(i);
        if (MuseumRecord_IsGiven(record, &item) != 0) {
            given++;
        }
    }
    for (unsigned int i = 0; i < MUSEUM_B_ITEMS; i++) {
        item = group_b_item(i);
        if (MuseumRecord_IsGiven(record, &item) != 0) {
            given++;
        }
    }
    for (unsigned int i = 0; i < MUSEUM_C_ITEMS; i++) {
        item = group_c_item(i);
        if (MuseumRecord_IsGiven(record, &item) != 0) {
            given++;
        }
    }
    for (unsigned int i = 0; i < MUSEUM_A_ITEMS; i++) {
        item = group_a_item(i);
        if (MuseumRecord_IsGiven(record, &item) != 0) {
            given++;
        }
    }
    return FX_Div((100 * given) << 12, MUSEUM_ITEMS << 12);
}
CLEAN_AS(func_02070dc0, MuseumRecord_PercentGiven)

/* func_02070e98: whether every group B item was given (it stops at the first that was not). */
int MuseumRecord_GroupBComplete(MuseumRecord *record)
{
    for (unsigned int i = 0; i < MUSEUM_B_ITEMS; i++) {
        u16 item = group_b_item(i);
        if (MuseumRecord_IsGiven(record, &item) == 0) {
            return 0;
        }
    }
    return 1;
}
CLEAN_AS(func_02070e98, MuseumRecord_GroupBComplete)

/* func_02070edc */
unsigned int MuseumRecord_GroupDComplete(MuseumRecord *record)
{
    for (unsigned int i = 0; i < MUSEUM_D_ITEMS; i++) {
        u16 item = group_d_item(i);
        if (MuseumRecord_IsGiven(record, &item) == 0) {
            return 0;
        }
    }
    return 1;
}
CLEAN_AS(func_02070edc, MuseumRecord_GroupDComplete)

/* func_02070f1c */
int MuseumRecord_GroupAComplete(MuseumRecord *record)
{
    for (unsigned int i = 0; i < MUSEUM_A_ITEMS; i++) {
        u16 item = group_a_item(i);
        if (MuseumRecord_IsGiven(record, &item) == 0) {
            return 0;
        }
    }
    return 1;
}
CLEAN_AS(func_02070f1c, MuseumRecord_GroupAComplete)

/* func_02070f5c */
int MuseumRecord_GroupCComplete(MuseumRecord *record)
{
    for (unsigned int i = 0; i < MUSEUM_C_ITEMS; i++) {
        u16 item = group_c_item(i);
        if (MuseumRecord_IsGiven(record, &item) == 0) {
            return 0;
        }
    }
    return 1;
}
CLEAN_AS(func_02070f5c, MuseumRecord_GroupCComplete)

/* func_02070fa0: whether every item was given, asking groups D, B, C then A. */
int MuseumRecord_Complete(MuseumRecord *record)
{
    return MuseumRecord_GroupDComplete(record) != 0 && MuseumRecord_GroupBComplete(record) != 0 &&
           MuseumRecord_GroupCComplete(record) != 0 && MuseumRecord_GroupAComplete(record) != 0;
}
CLEAN_AS(func_02070fa0, MuseumRecord_Complete)

/* func_02070fe4: put the name of the player of the town who gave `item` in the text `name`;
 * 0 when nobody did or the player has left. */
int MuseumRecord_GiverName(MuseumRecord *record, void *name, const u16 *item)
{
    if ((unsigned int) MuseumRecord_Giver(record, item) > MUSEUM_BY_OTHER_PLAYER) {
        return 0;
    }
    int player = (MuseumRecord_GiverBits(record, item) - MUSEUM_GIVEN_BY_PLAYER_0) & 3;
    u8 *giver = PlayerRecords_TownRecord(data_021dc7bc, player);
    if (giver == NULL) {
        return 0;
    }
    PlayerId_NameToText(PlayerRecord_Player(giver), name);
    return 1;
}
CLEAN_AS(func_02070fe4, MuseumRecord_GiverName)

/* Mark the item as given by a former player if `giver` gave it. */
static void forget_if(MuseumRecord *record, const u16 *item, int giver)
{
    if (MuseumRecord_GiverBits(record, item) == giver) {
        MuseumRecord_SetFormer(record, item);
    }
}

/* func_02071028: the items player `player` (0-3) gave are now a former player's; groups A, B, C
 * then D. */
void MuseumRecord_ForgetPlayer(MuseumRecord *record, int player)
{
    int giver = (player & 3) + MUSEUM_GIVEN_BY_PLAYER_0;
    u16 item;
    for (unsigned int i = 0; i < MUSEUM_A_ITEMS; i++) {
        item = group_a_item(i);
        forget_if(record, &item, giver);
    }
    for (unsigned int i = 0; i < MUSEUM_B_ITEMS; i++) {
        item = group_b_item(i);
        forget_if(record, &item, giver);
    }
    for (unsigned int i = 0; i < MUSEUM_C_ITEMS; i++) {
        item = group_c_item(i);
        forget_if(record, &item, giver);
    }
    for (unsigned int i = 0; i < MUSEUM_D_ITEMS; i++) {
        item = group_d_item(i);
        forget_if(record, &item, giver);
    }
}
CLEAN_AS(func_02071028, MuseumRecord_ForgetPlayer)

/* func_02071110: the current player gives `item`; if the record is then complete, today's date
 * is stored. QUIRK: the date is stored again on every later call while the record is complete. */
void MuseumRecord_Give(MuseumRecord *record, const u16 *item)
{
    MuseumRecord_Clear(record, item);
    int index;
    u8 *bits = locate(record, item, &index);
    if (bits != NULL) {
        int giver = (PlayerRecords_CurrentNumber() & 3) + MUSEUM_GIVEN_BY_PLAYER_0;
        bits[index >> 1] |= (u8) (giver << bits_shift(index));
    }
    if (MuseumRecord_Complete(record) != 0) {
        DateTime now = {0};
        DateTime_Now(&now);
        record->year = now.year;
        record->month = now.month;
        record->day = now.day;
        record->unk_63 = 0;
    }
}
CLEAN_AS(func_02071110, MuseumRecord_Give)

/* func_02071188: send each player of the town the owl's letter with item 0x3870, with the
 * town's name in message entry 2; whether any letter was posted. QUIRK: `record` is not read. */
int MuseumRecord_SendLetters(void *record)
{
    (void) record;
    Text8 town;
    Letter letter;
    TownNameText_Construct((TownNameText *) &town);
    TownName_ToText((TownName *) (void *) data_021dc7aa, (TextBase *) &town);
    MailText_SetPartText(TOWN_NAME_ENTRY, &town);
    int posted = 0;
    for (int i = 0; i < PLAYERS; i++) {
        u8 *player = PlayerRecords_TownRecord(data_021dc7bc, i);
        if (player == NULL || PlayerRecord_HasPlayer(player) == 0) {
            continue;
        }
        Letter_Construct(&letter);
        char unk = 0;
        Letter_WriteSpecialToPlayer(&letter, (const u8 *) &unk, data_020e17b4, (const u8 *) &data_020e17ac,
                                    (const u8 *) &data_020e17b0, PlayerRecord_Player(player));
        Letter_SetItem(&letter, LETTER_ITEM, 1);
        if (Mail_Post((MailLetter *) &letter) != 0) {
            posted = 1;
        }
        Letter_Destruct(&letter);
    }
    TownNameText_Destruct((TownNameText *) &town);
    return posted;
}
CLEAN_AS(func_02071188, MuseumRecord_SendLetters)

/* func_0207122c: once the record is complete, on a day other than the one stored, send the
 * letters; when one is posted, set the state block's flag 3, which stops this. */
void MuseumRecord_CheckLetters(MuseumRecord *record)
{
    if (StateBlock_TestFlag(data_021dc7a8, LETTERS_SENT_FLAG) != 0) {
        return;
    }
    if (MuseumRecord_Complete(record) == 0) {
        return;
    }
    DateTime now = {0};
    DateTime_Now(&now);
    if (record->year == now.year && record->month == now.month && record->day == now.day) {
        return;
    }
    if (MuseumRecord_SendLetters(record) == 0) {
        return;
    }
    StateBlock_SetFlag(data_021dc7a8, LETTERS_SENT_FLAG);
}
CLEAN_AS(func_0207122c, MuseumRecord_CheckLetters)

/* func_02071298 */
int MuseumRecord_IsGiven(MuseumRecord *record, const u16 *item)
{
    return MuseumRecord_GiverBits(record, item) != 0;
}
CLEAN_AS(func_02071298, MuseumRecord_IsGiven)

/* func_020712b0: who gave `item` (MuseumGiverKind). */
int MuseumRecord_Giver(MuseumRecord *record, const u16 *item)
{
    int giver = MuseumRecord_GiverBits(record, item);
    if (giver == MUSEUM_NOT_GIVEN) {
        return MUSEUM_NOBODY;
    }
    if (giver == MUSEUM_GIVEN_BY_FORMER) {
        return MUSEUM_BY_FORMER_PLAYER;
    }
    int player = PlayerRecords_CurrentNumber();
    if (PlayerRecords_IsTownNumber((unsigned int) player) == 1 && giver == player + MUSEUM_GIVEN_BY_PLAYER_0) {
        return MUSEUM_BY_CURRENT_PLAYER;
    }
    return MUSEUM_BY_OTHER_PLAYER;
}
CLEAN_AS(func_020712b0, MuseumRecord_Giver)

/* func_020712ec: the item's four bits (MuseumGiver); 0 for an item of no group. */
int MuseumRecord_GiverBits(MuseumRecord *record, const u16 *item)
{
    int index;
    const u8 *bits = locate(record, item, &index);
    if (bits == NULL) {
        return 0;
    }
    return (bits[index >> 1] >> bits_shift(index)) & 0xf;
}
CLEAN_AS(func_020712ec, MuseumRecord_GiverBits)

/* func_02071318: the address of the group of `item` in the record, with the item's entry in
 * `index` when it is not NULL; 0 for an item of no group. */
int MuseumRecord_Locate(MuseumRecord *record, const u16 *item, int *index)
{
    u16 code = *item;
    u32 group;
    int entry;
    if (code >= MUSEUM_A_FIRST && code <= MUSEUM_A_LAST) {
        group = offsetof(MuseumRecord, group_a);
        entry = (code - MUSEUM_A_FIRST) >> 2;
    } else if (code >= MUSEUM_D_FIRST && code <= MUSEUM_D_LAST) {
        group = offsetof(MuseumRecord, group_d);
        entry = (code - MUSEUM_D_FIRST) >> 2;
    } else if (code >= MUSEUM_C_FIRST && code <= MUSEUM_C_LAST) {
        group = offsetof(MuseumRecord, group_c);
        entry = code - MUSEUM_C_FIRST;
    } else if (code >= MUSEUM_B_FIRST && code <= MUSEUM_B_LAST) {
        group = offsetof(MuseumRecord, group_b);
        entry = code - MUSEUM_B_FIRST;
    } else {
        return 0;
    }
    if (index != NULL) {
        *index = entry;
    }
    return (int) ((u32) (uintptr_t) record + group);
}
CLEAN_AS(func_02071318, MuseumRecord_Locate)

/* func_020713ec: mark the item as given by a former player. */
void MuseumRecord_SetFormer(MuseumRecord *record, const u16 *item)
{
    int index;
    u8 *bits = locate(record, item, &index);
    if (bits != NULL) {
        int shift = bits_shift(index);
        bits[index >> 1] &= (u8) ~(0xf << shift);
        bits[index >> 1] |= (u8) (MUSEUM_GIVEN_BY_FORMER << shift);
    }
}
CLEAN_AS(func_020713ec, MuseumRecord_SetFormer)

/* func_02071424: mark the item as not given. */
void MuseumRecord_Clear(MuseumRecord *record, const u16 *item)
{
    int index;
    u8 *bits = locate(record, item, &index);
    if (bits != NULL) {
        bits[index >> 1] &= (u8) ~(0xf << bits_shift(index));
    }
}
CLEAN_AS(func_02071424, MuseumRecord_Clear)

/* func_02071450: nothing given (the date is kept). */
void MuseumRecord_ClearAll(MuseumRecord *record)
{
    memset(record->group_a, 0, sizeof(record->group_a));
    memset(record->group_b, 0, sizeof(record->group_b));
    memset(record->group_c, 0, sizeof(record->group_c));
    memset(record->group_d, 0, sizeof(record->group_d));
}
CLEAN_AS(func_02071450, MuseumRecord_ClearAll)

/* func_0207148c: the record's destructor, which has nothing to release. */
void MuseumRecord_Destruct(MuseumRecord *record)
{
    (void) record;
}
CLEAN_AS(func_0207148c, MuseumRecord_Destruct)

/* func_02071490: the record's constructor: nothing given. */
MuseumRecord *MuseumRecord_Construct(MuseumRecord *record)
{
    MuseumRecord_ClearAll(record);
    return record;
}
CLEAN_AS(func_02071490, MuseumRecord_Construct)
