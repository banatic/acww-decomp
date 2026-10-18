/* A villager's impression of a player (villager_impression.h). */
#include "villager_impression.h"

#include "calendar.h"
#include "clean.h"
#include "npc_id.h"
#include "player_pockets.h"
#include "player_records.h"
#include "villager_state.h"
#include "date_time.h"
#include "item_record.h"
#include "message_reader.h"
#include "player_id.h"
#include "player_record.h"
#include "town_villager.h"
#include "villager_memories.h"
#include "villager_memory_entry.h"
#include "villager_status.h"

static_assert(sizeof(VillagerImpressionRule) == 8, "rule");

/* The months of the seasons. */
#define VILLAGER_IMPRESSION_SUMMER_FIRST 6
#define VILLAGER_IMPRESSION_SUMMER_LAST 8
#define VILLAGER_IMPRESSION_AUTUMN_FIRST 9
#define VILLAGER_IMPRESSION_AUTUMN_LAST 11
#define VILLAGER_IMPRESSION_DECEMBER 12
#define VILLAGER_IMPRESSION_WINTER_LAST 2
/* What func_02094ffc gives for a player of this town. */
#define VILLAGER_IMPRESSION_THIS_TOWN 0
/* The head kinds come in two sets of eight (bits 4-7 of the record's byte 0x243c): kind n of the
 * second set is n + 8. */
#define VILLAGER_IMPRESSION_HEAD_SET 8
/* The items part C (slot 3) is tested against. */
#define VILLAGER_IMPRESSION_PART_C_FIRST 0x1431
#define VILLAGER_IMPRESSION_PART_C_LAST 0x1470
/* The fondness the tests look for. */
#define VILLAGER_IMPRESSION_VERY_FOND 110
#define VILLAGER_IMPRESSION_FOND 70
#define VILLAGER_IMPRESSION_DISLIKED (-30)

extern const VillagerImpressionRule data_020cd5c4[VILLAGER_IMPRESSION_COUNT];
extern char data_020e195c[]; /* "st_impress" */
extern u8 data_021dc7bc[];   /* the four players' records */

/* func_0207e008: the villager's impression of the player of `record` (the current player's when
 * NULL) loaded into the text label, when the villager knows the player and has one. */
void VillagerImpression_LoadText(u8 *villager, int label, u8 *record)
{
    if (record == NULL) {
        record = PlayerRecords_Current();
    }
    s8 *memory = NULL;
    if (record != NULL) {
        memory = (s8 *) VillagerMemory_Of(villager, PlayerRecord_Player(record));
    }
    if (memory == NULL) {
        return;
    }
    u32 impression = VillagerMemoryEntry_Impression((VillagerMemory *) (void *) memory);
    if (impression < VILLAGER_IMPRESSION_COUNT) {
        char number = (char) impression;
        MessageReader_LoadMessage(label, (unsigned char *) &number, (int) (uintptr_t) data_020e195c);
    }
}
CLEAN_AS(func_0207e008, VillagerImpression_LoadText)

/* func_0207e054: the villager's impression of the player picked afresh and kept in its memory
 * of the player (found from `record`, the current player's when NULL, unless given). Gives it,
 * or 0x58 when there is no villager or memory.
 * QUIRK: a memory given without a record (and no current player) is picked for with a NULL
 * record. */
int VillagerImpression_Choose(u8 *villager, s8 *memory, u8 *record)
{
    int impression = VILLAGER_IMPRESSION_COUNT;
    if (!NpcId_IsValid(TownVillager_NpcId(villager))) {
        return impression;
    }
    if (record == NULL) {
        record = PlayerRecords_Current();
    }
    if (record != NULL && memory == NULL) {
        memory = (s8 *) VillagerMemory_Of(villager, PlayerRecord_Player(record));
    }
    if (memory != NULL) {
        int fondness = VillagerMemoryEntry_Fondness((VillagerMemory *) (void *) memory);
        impression = VillagerImpression_Pick(record, fondness, VillagerState_GetByte18(VillagerStatus_StateEntry(villager)));
        VillagerMemoryEntry_SetImpression((VillagerMemory *) (void *) memory, (u8) impression);
    }
    return impression;
}
CLEAN_AS(func_0207e054, VillagerImpression_Choose)

/* func_0207e0c4: the first rule for the player's kind whose test passes, or 0x58. */
int VillagerImpression_Pick(u8 *record, int fondness, int byte_18)
{
    int kind = PlayerId_Byte1c((const s8 *) PlayerRecord_Player(record));
    for (int i = 0; i < VILLAGER_IMPRESSION_COUNT; i++) {
        const VillagerImpressionRule *rule = &data_020cd5c4[i];
        if (rule->kind != VILLAGER_IMPRESSION_ANY_KIND && rule->kind != kind) {
            continue;
        }
        if (rule->test(record, fondness, byte_18) != 0) {
            return i;
        }
    }
    return VILLAGER_IMPRESSION_COUNT;
}
CLEAN_AS(func_0207e0c4, VillagerImpression_Pick)

/* ---- The tests */

/* func_0207e118 */
int VillagerImpression_Always(void)
{
    return 1;
}
CLEAN_AS(func_0207e118, VillagerImpression_Always)

static int this_month(void)
{
    DateTime now = {0};
    DateTime_Now(&now);
    return now.month;
}

/* func_0207e11c: June to August. */
int VillagerImpression_IsSummer(void)
{
    int month = this_month();
    return month >= VILLAGER_IMPRESSION_SUMMER_FIRST && month <= VILLAGER_IMPRESSION_SUMMER_LAST;
}
CLEAN_AS(func_0207e11c, VillagerImpression_IsSummer)

/* func_0207e144: September to November. */
int VillagerImpression_IsAutumn(void)
{
    int month = this_month();
    return month >= VILLAGER_IMPRESSION_AUTUMN_FIRST && month <= VILLAGER_IMPRESSION_AUTUMN_LAST;
}
CLEAN_AS(func_0207e144, VillagerImpression_IsAutumn)

/* func_0207e16c: December to February. */
int VillagerImpression_IsWinter(void)
{
    int month = this_month();
    return month == VILLAGER_IMPRESSION_DECEMBER || (month >= 1 && month <= VILLAGER_IMPRESSION_WINTER_LAST);
}
CLEAN_AS(func_0207e16c, VillagerImpression_IsWinter)

/* func_0207e198: a player of this town, which has two or more players. */
int VillagerImpression_IsLocalAmongTwoOrMore(u8 *record)
{
    return PlayerId_WhichTown(PlayerRecord_Player(record)) == VILLAGER_IMPRESSION_THIS_TOWN &&
           PlayerRecords_CountTown(data_021dc7bc) >= 2;
}
CLEAN_AS(func_0207e198, VillagerImpression_IsLocalAmongTwoOrMore)

/* func_0207e1c4: a player of this town, which has all four players. */
int VillagerImpression_IsLocalAmongFour(u8 *record)
{
    return PlayerId_WhichTown(PlayerRecord_Player(record)) == VILLAGER_IMPRESSION_THIS_TOWN &&
           PlayerRecords_CountTown(data_021dc7bc) == PLAYER_RECORDS_TOWN;
}
CLEAN_AS(func_0207e1c4, VillagerImpression_IsLocalAmongFour)

/* Whether the head's kind is `kind` of either set; the kind is read once for each set. */
static int head_kind_is(u8 *record, u32 kind)
{
    return PlayerRecord_HeadKind(record) == kind || PlayerRecord_HeadKind(record) == kind + VILLAGER_IMPRESSION_HEAD_SET;
}

/* func_0207e1f0 */
int VillagerImpression_HeadKind7(u8 *record, int fondness, int byte_18)
{
    (void) fondness;
    (void) byte_18;
    return head_kind_is(record, 7);
}
CLEAN_AS(func_0207e1f0, VillagerImpression_HeadKind7)

/* func_0207e214 */
int VillagerImpression_HeadKind6(u8 *record, int fondness, int byte_18)
{
    (void) fondness;
    (void) byte_18;
    return head_kind_is(record, 6);
}
CLEAN_AS(func_0207e214, VillagerImpression_HeadKind6)

/* func_0207e238 */
int VillagerImpression_HeadKind5(u8 *record, int fondness, int byte_18)
{
    (void) fondness;
    (void) byte_18;
    return head_kind_is(record, 5);
}
CLEAN_AS(func_0207e238, VillagerImpression_HeadKind5)

/* func_0207e25c */
int VillagerImpression_HeadKind4(u8 *record, int fondness, int byte_18)
{
    (void) fondness;
    (void) byte_18;
    return head_kind_is(record, 4);
}
CLEAN_AS(func_0207e25c, VillagerImpression_HeadKind4)

/* func_0207e280 */
int VillagerImpression_HeadKind3(u8 *record, int fondness, int byte_18)
{
    (void) fondness;
    (void) byte_18;
    return head_kind_is(record, 3);
}
CLEAN_AS(func_0207e280, VillagerImpression_HeadKind3)

/* func_0207e2a4 */
int VillagerImpression_HeadKind2(u8 *record, int fondness, int byte_18)
{
    (void) fondness;
    (void) byte_18;
    return head_kind_is(record, 2);
}
CLEAN_AS(func_0207e2a4, VillagerImpression_HeadKind2)

/* func_0207e2c8 */
int VillagerImpression_HeadKind1(u8 *record, int fondness, int byte_18)
{
    (void) fondness;
    (void) byte_18;
    return head_kind_is(record, 1);
}
CLEAN_AS(func_0207e2c8, VillagerImpression_HeadKind1)

/* func_0207e2ec */
int VillagerImpression_HeadKind0(u8 *record, int fondness, int byte_18)
{
    (void) fondness;
    (void) byte_18;
    return head_kind_is(record, 0);
}
CLEAN_AS(func_0207e2ec, VillagerImpression_HeadKind0)

static int part_c_in_range(u8 *record)
{
    u16 item = *PlayerRecord_PartCItem(record);
    return item >= VILLAGER_IMPRESSION_PART_C_FIRST && item <= VILLAGER_IMPRESSION_PART_C_LAST;
}

/* func_0207e310: part C's item is one of 0x1431-0x1470 and the head's kind 0, 1, 3, 5 or 7. */
int VillagerImpression_PartCWithHeadKind01357(u8 *record, int fondness, int byte_18)
{
    if (!part_c_in_range(record)) {
        return 0;
    }
    return VillagerImpression_HeadKind0(record, fondness, byte_18) ||
           VillagerImpression_HeadKind1(record, fondness, byte_18) ||
           VillagerImpression_HeadKind3(record, fondness, byte_18) ||
           VillagerImpression_HeadKind5(record, fondness, byte_18) || VillagerImpression_HeadKind7(record, fondness, byte_18);
}
CLEAN_AS(func_0207e310, VillagerImpression_PartCWithHeadKind01357)

/* func_0207e390: the same with head kind 2, 4 or 6. */
int VillagerImpression_PartCWithHeadKind246(u8 *record, int fondness, int byte_18)
{
    if (!part_c_in_range(record)) {
        return 0;
    }
    return VillagerImpression_HeadKind2(record, fondness, byte_18) ||
           VillagerImpression_HeadKind4(record, fondness, byte_18) || VillagerImpression_HeadKind6(record, fondness, byte_18);
}
CLEAN_AS(func_0207e390, VillagerImpression_PartCWithHeadKind246)

/* func_0207e3f4: the same with head kind 2, 3 or 6. */
int VillagerImpression_PartCWithHeadKind236(u8 *record, int fondness, int byte_18)
{
    if (!part_c_in_range(record)) {
        return 0;
    }
    return VillagerImpression_HeadKind2(record, fondness, byte_18) ||
           VillagerImpression_HeadKind3(record, fondness, byte_18) || VillagerImpression_HeadKind6(record, fondness, byte_18);
}
CLEAN_AS(func_0207e3f4, VillagerImpression_PartCWithHeadKind236)

/* func_0207e458: the same with head kind 0, 1, 4, 5 or 7. */
int VillagerImpression_PartCWithHeadKind01457(u8 *record, int fondness, int byte_18)
{
    if (!part_c_in_range(record)) {
        return 0;
    }
    return VillagerImpression_HeadKind0(record, fondness, byte_18) ||
           VillagerImpression_HeadKind1(record, fondness, byte_18) ||
           VillagerImpression_HeadKind4(record, fondness, byte_18) ||
           VillagerImpression_HeadKind5(record, fondness, byte_18) || VillagerImpression_HeadKind7(record, fondness, byte_18);
}
CLEAN_AS(func_0207e458, VillagerImpression_PartCWithHeadKind01457)

/* The player's bells, those in bell bags included. */
static int bells_of(u8 *record)
{
    return PlayerPockets_Bells(PlayerRecord_Pockets(record), PLAYER_POCKETS_USE_BAGS);
}

/* func_0207e4d8: 60,000 bells or more. */
int VillagerImpression_Bells60000(u8 *record)
{
    return bells_of(record) >= 60000;
}
CLEAN_AS(func_0207e4d8, VillagerImpression_Bells60000)

/* func_0207e4fc: 40,000 to 59,999 bells. */
int VillagerImpression_Bells40000(u8 *record)
{
    int bells = bells_of(record);
    return bells >= 40000 && bells < 60000;
}
CLEAN_AS(func_0207e4fc, VillagerImpression_Bells40000)

/* func_0207e52c: 20,000 to 39,999 bells. */
int VillagerImpression_Bells20000(u8 *record)
{
    int bells = bells_of(record);
    return bells >= 20000 && bells < 40000;
}
CLEAN_AS(func_0207e52c, VillagerImpression_Bells20000)

/* func_0207e55c: 10,000 to 19,999 bells. */
int VillagerImpression_Bells10000(u8 *record)
{
    int bells = bells_of(record);
    return bells >= 10000 && bells < 20000;
}
CLEAN_AS(func_0207e55c, VillagerImpression_Bells10000)

/* func_0207e58c: 1,000 bells or fewer. */
int VillagerImpression_BellsAtMost1000(u8 *record)
{
    return bells_of(record) <= 1000;
}
CLEAN_AS(func_0207e58c, VillagerImpression_BellsAtMost1000)

/* func_0207e5b0: 300 bells or fewer. */
int VillagerImpression_BellsAtMost300(u8 *record)
{
    return bells_of(record) <= 300;
}
CLEAN_AS(func_0207e5b0, VillagerImpression_BellsAtMost300)

/* func_0207e5d4: the current player has collected all the fish. */
int VillagerImpression_CollectedAllFish(u8 *record, int fondness, int byte_18)
{
    (void) record;
    (void) fondness;
    (void) byte_18;
    return ItemRecord_HasAllFish();
}
CLEAN_AS(func_0207e5d4, VillagerImpression_CollectedAllFish)

/* func_0207e5dc: not all the fish, but at least half of them. */
int VillagerImpression_CollectedHalfFish(u8 *record, int fondness, int byte_18)
{
    if (VillagerImpression_CollectedAllFish(record, fondness, byte_18) != 0) {
        return 0;
    }
    int half = (int) (ItemRecord_FishKinds() >> 1);
    return ItemRecord_CountFish() >= half;
}
CLEAN_AS(func_0207e5dc, VillagerImpression_CollectedHalfFish)

/* func_0207e604: the current player has collected all the items from 0x12b0. */
int VillagerImpression_CollectedAll12B0(void)
{
    return ItemRecord_HasAllInsects();
}
CLEAN_AS(func_0207e604, VillagerImpression_CollectedAll12B0)

/* func_0207e60c: not all the items from 0x12b0, but at least half of them.
 * QUIRK: also not when all the fish are collected. */
int VillagerImpression_CollectedHalf12B0(u8 *record, int fondness, int byte_18)
{
    if (VillagerImpression_CollectedAll12B0() != 0) {
        return 0;
    }
    if (VillagerImpression_CollectedAllFish(record, fondness, byte_18) != 0) {
        return 0;
    }
    int half = (int) (ItemRecord_InsectKinds() >> 1);
    return ItemRecord_CountInsects() >= half;
}
CLEAN_AS(func_0207e60c, VillagerImpression_CollectedHalf12B0)

/* func_0207e648: the villager is very fond of the player (110 or more). */
int VillagerImpression_VeryFond(u8 *record, int fondness)
{
    (void) record;
    return fondness >= VILLAGER_IMPRESSION_VERY_FOND;
}
CLEAN_AS(func_0207e648, VillagerImpression_VeryFond)

/* func_0207e654: fond of the player (70 to 109). */
int VillagerImpression_Fond(u8 *record, int fondness)
{
    (void) record;
    return fondness >= VILLAGER_IMPRESSION_FOND && fondness < VILLAGER_IMPRESSION_VERY_FOND;
}
CLEAN_AS(func_0207e654, VillagerImpression_Fond)

/* func_0207e664: the villager dislikes the player (-30 or less). */
int VillagerImpression_Disliked(u8 *record, int fondness)
{
    (void) record;
    return fondness <= VILLAGER_IMPRESSION_DISLIKED;
}
CLEAN_AS(func_0207e664, VillagerImpression_Disliked)
