/* More of the tests of the table of impressions (villager_impression_tests.h). */
#include "villager_impression_tests.h"

#include "acre_map.h"
#include "acre_tile.h"
#include "calendar.h"
#include "clean.h"
#include "player_pockets.h"
#include "player_record.h"
#include "villager_roster.h"
#include "villager_town.h"

/* The actor whose position func_02095794 gives for the player. */
#define VILLAGER_IMPRESSION_PLAYER_ACTOR 4
/* An acre is 16 x 16 tiles. */
#define VILLAGER_IMPRESSION_ACRE_TILES 16

extern u8 data_021e5a2c[];  /* the town's villagers (VillagerTown) */
extern u8 data_020e54a8;    /* 0 or 1, a mode many scenes test (0 in the town) */
extern void *data_021c80bc; /* the town's map; null while there is none */

extern int func_0209dcac(void); /* the part of the day (Calendar_PartOfDay) */
/* 1 or 2 from word 0x34 of data_021f8ab0 while its word 0x24 is 2-4, else 0. */
extern int func_020ba4e4(void);
extern int func_0204bcdc(u16 *item); /* whether the code is of kind 3 or 4 (ItemCode_HasVariant) */
extern int func_0204bc64(u16 *item); /* the code without its variant (ItemCode_VariantItem) */
/* The position of the actor, or 0 when there is none. */
extern const int *func_02095794(int actor);
extern void func_0204f818(int *x, int *z, const int *position); /* the tile a position is on */

/* ---- The player and the clock */

/* func_0207e674: the villager hates the player (-80 or less). */
int VillagerImpression_Hated(u8 *record, int fondness)
{
    (void) record;
    return fondness <= VILLAGER_IMPRESSION_HATED;
}
CLEAN_AS(func_0207e674, VillagerImpression_Hated)

/* func_0207e684: the player's pockets have no free slot. */
int VillagerImpression_PocketsFull(u8 *record)
{
    return PlayerPockets_FreeSlot(PlayerRecord_Pockets(record)) == VILLAGER_IMPRESSION_NO_FREE_SLOT;
}
CLEAN_AS(func_0207e684, VillagerImpression_PocketsFull)

/* func_0207e6a4: it is night (0:00-4:59). */
int VillagerImpression_IsNight(void)
{
    return func_0209dcac() == PART_OF_DAY_NIGHT;
}
CLEAN_AS(func_0207e6a4, VillagerImpression_IsNight)

/* func_0207e6bc: it is morning (5:00-11:59). */
int VillagerImpression_IsMorning(void)
{
    return func_0209dcac() == PART_OF_DAY_MORNING;
}
CLEAN_AS(func_0207e6bc, VillagerImpression_IsMorning)

/* func_0207e6d4: the player wears clothes 0x12a8-0x12af. */
int VillagerImpression_Clothes12A8(u8 *record)
{
    u16 clothes = *PlayerRecord_Clothes(record);
    return clothes >= 0x12a8 && clothes <= 0x12af;
}
CLEAN_AS(func_0207e6d4, VillagerImpression_Clothes12A8)

/* func_0207e708: func_020ba4e4 gives 2. */
int VillagerImpression_State8AB0Is2(void)
{
    return func_020ba4e4() == 2;
}
CLEAN_AS(func_0207e708, VillagerImpression_State8AB0Is2)

/* func_0207e720: func_020ba4e4 gives 1. */
int VillagerImpression_State8AB0Is1(void)
{
    return func_020ba4e4() == 1;
}
CLEAN_AS(func_0207e720, VillagerImpression_State8AB0Is1)

/* ---- The player's looks */

static int VillagerImpression_InRange(u16 code, u16 first, u16 last)
{
    return code >= first && code <= last;
}

/* Whether the head's item is `wanted`, whatever its variant for a code of kind 3 or 4. */
static int VillagerImpression_HeadIs(u8 *record, u16 wanted)
{
    u16 *head = PlayerRecord_HeadItem(record);
    if (func_0204bcdc(head)) {
        int item = func_0204bc64(head);
        return item == func_0204bc64(&wanted);
    }
    return *head == wanted;
}

/* func_0207e738: the held item is one of 0x1380-0x13a7 (two ranges in the original,
 * 0x1380-0x139f and 0x13a0-0x13a7). */
int VillagerImpression_Held1380(u8 *record)
{
    return VillagerImpression_InRange(*PlayerRecord_HeldItem(record), 0x1380, 0x13a7);
}
CLEAN_AS(func_0207e738, VillagerImpression_Held1380)

/* func_0207e780: the held item is 0x137c, else the head's item is one of 0x1408-0x1428, else
 * part C's item is one of 0x1471-0x1491 (each looked up only when the one before fails). */
int VillagerImpression_Held137COrHeadOrPartC(u8 *record)
{
    return *PlayerRecord_HeldItem(record) == 0x137c ||
           VillagerImpression_InRange(*PlayerRecord_HeadItem(record), 0x1408, 0x1428) ||
           VillagerImpression_InRange(*PlayerRecord_PartCItem(record), 0x1471, 0x1491);
}
CLEAN_AS(func_0207e780, VillagerImpression_Held137COrHeadOrPartC)

/* func_0207e7fc */
int VillagerImpression_HeadIs1406(u8 *record)
{
    return VillagerImpression_HeadIs(record, 0x1406);
}
CLEAN_AS(func_0207e7fc, VillagerImpression_HeadIs1406)

/* func_0207e848 */
int VillagerImpression_HeadIs13E4(u8 *record)
{
    return VillagerImpression_HeadIs(record, 0x13e4);
}
CLEAN_AS(func_0207e848, VillagerImpression_HeadIs13E4)

/* func_0207e894 */
int VillagerImpression_HeadIs13E3(u8 *record)
{
    return VillagerImpression_HeadIs(record, 0x13e3);
}
CLEAN_AS(func_0207e894, VillagerImpression_HeadIs13E3)

/* func_0207e8e0 */
int VillagerImpression_HeadIs13F5(u8 *record)
{
    return VillagerImpression_HeadIs(record, 0x13f5);
}
CLEAN_AS(func_0207e8e0, VillagerImpression_HeadIs13F5)

/* func_0207e92c */
int VillagerImpression_HeadIs13EA(u8 *record)
{
    return VillagerImpression_HeadIs(record, 0x13ea);
}
CLEAN_AS(func_0207e92c, VillagerImpression_HeadIs13EA)

/* func_0207e978 */
int VillagerImpression_HeadIs13E6(u8 *record)
{
    return VillagerImpression_HeadIs(record, 0x13e6);
}
CLEAN_AS(func_0207e978, VillagerImpression_HeadIs13E6)

/* func_0207e9c4 */
int VillagerImpression_HeadIs1405(u8 *record)
{
    return VillagerImpression_HeadIs(record, 0x1405);
}
CLEAN_AS(func_0207e9c4, VillagerImpression_HeadIs1405)

/* func_0207ea10 */
int VillagerImpression_HeadIs13BC(u8 *record)
{
    return VillagerImpression_HeadIs(record, 0x13bc);
}
CLEAN_AS(func_0207ea10, VillagerImpression_HeadIs13BC)

/* func_0207ea5c */
int VillagerImpression_HeadIs13A8(u8 *record)
{
    return VillagerImpression_HeadIs(record, 0x13a8);
}
CLEAN_AS(func_0207ea5c, VillagerImpression_HeadIs13A8)

/* func_0207eaa8 */
int VillagerImpression_HeadIs13B2(u8 *record)
{
    return VillagerImpression_HeadIs(record, 0x13b2);
}
CLEAN_AS(func_0207eaa8, VillagerImpression_HeadIs13B2)

/* func_0207eaf4 */
int VillagerImpression_HeadIs13C1(u8 *record)
{
    return VillagerImpression_HeadIs(record, 0x13c1);
}
CLEAN_AS(func_0207eaf4, VillagerImpression_HeadIs13C1)

/* func_0207eb40: the held item is 0x1378 or 0x1379. */
int VillagerImpression_Held1378(u8 *record)
{
    return VillagerImpression_InRange(*PlayerRecord_HeldItem(record), 0x1378, 0x1379);
}
CLEAN_AS(func_0207eb40, VillagerImpression_Held1378)

/* func_0207eb7c: the held item is 0x1374 or 0x1375. */
int VillagerImpression_Held1374(u8 *record)
{
    return VillagerImpression_InRange(*PlayerRecord_HeldItem(record), 0x1374, 0x1375);
}
CLEAN_AS(func_0207eb7c, VillagerImpression_Held1374)

/* func_0207ebb8: the held item is one of 0x136b-0x1373. */
int VillagerImpression_Held136B(u8 *record)
{
    return VillagerImpression_InRange(*PlayerRecord_HeldItem(record), 0x136b, 0x1373);
}
CLEAN_AS(func_0207ebb8, VillagerImpression_Held136B)

/* func_0207ebf8: the held item is 0x1376 or 0x1377. */
int VillagerImpression_Held1376(u8 *record)
{
    return VillagerImpression_InRange(*PlayerRecord_HeldItem(record), 0x1376, 0x1377);
}
CLEAN_AS(func_0207ebf8, VillagerImpression_Held1376)

/* ---- The villager and the town */

/* func_0207ec34: the state entry's byte 0x18 is 2 or 4. */
int VillagerImpression_Byte18Is2Or4(u8 *record, int fondness, int byte_18)
{
    (void) record;
    (void) fondness;
    return byte_18 == 2 || byte_18 == 4;
}
CLEAN_AS(func_0207ec34, VillagerImpression_Byte18Is2Or4)

/* func_0207ec44: the state entry's byte 0x18 is 1. */
int VillagerImpression_Byte18Is1(u8 *record, int fondness, int byte_18)
{
    (void) record;
    (void) fondness;
    return byte_18 == 1;
}
CLEAN_AS(func_0207ec44, VillagerImpression_Byte18Is1)

/* func_0207ec50: one of the calendar's events the town looks for is on now. */
int VillagerImpression_EventToday(void)
{
    return VillagerTown_CurrentEvent() != VILLAGER_TOWN_EVENTS;
}
CLEAN_AS(func_0207ec50, VillagerImpression_EventToday)

/* func_0207ec68: the town has four villagers or fewer. */
int VillagerImpression_FewVillagers(void)
{
    return VillagerRoster_Count((VillagerTown *) (void *) data_021e5a2c) <= VILLAGER_IMPRESSION_FEW_VILLAGERS;
}
CLEAN_AS(func_0207ec68, VillagerImpression_FewVillagers)

/* ---- The tiles around the player */

/* The acre a tile coordinate is in, rounded down for negative coordinates as the ARM's
 * arithmetic shift does. The tile within the acre is then the low four bits. */
static int VillagerImpression_AcreOf(int tile)
{
    return tile >= 0 ? tile / VILLAGER_IMPRESSION_ACRE_TILES : -1 - (-1 - tile) / VILLAGER_IMPRESSION_ACRE_TILES;
}

/* Family A and the codes after it (0x00-0x1a, 0x1c, 0x1d), family C and the codes after it
 * (0x8a-0xa5) (map_item.h). */
static int VillagerImpression_IsFamilyAC(u16 code)
{
    return code <= 0x1a || code == 0x1c || code == 0x1d || (code >= 0x8a && code <= 0xa5);
}

static int VillagerImpression_IsCode21To24(u16 code)
{
    return code >= 0x21 && code <= 0x24;
}

/* Whether at least `needed` of the nine tiles around the player (row by row, from the one
 * above and to the left) hold a code `wanted` takes, on the town map's layer 0. 0 when not in
 * the town (data_020e54a8), without the player's actor or without a map. */
static int VillagerImpression_CountNear(int (*wanted)(u16 code), int needed)
{
    const int *position = func_02095794(VILLAGER_IMPRESSION_PLAYER_ACTOR);
    if (data_020e54a8 != 0 || position == NULL) {
        return 0;
    }
    AcreMap *map = data_021c80bc;
    if (map == NULL) {
        return 0;
    }
    int count = 0;
    int px = 0;
    int pz = 0;
    func_0204f818(&px, &pz, position);
    for (int z = pz - 1; z <= pz + 1; z++) {
        for (int x = px - 1; x <= px + 1; x++) {
            int acre_x = VillagerImpression_AcreOf(x);
            int acre_z = VillagerImpression_AcreOf(z);
            u16 *code = AcreTile_ItemInAcre(map, (u32) acre_x, (u32) acre_z, x - acre_x * VILLAGER_IMPRESSION_ACRE_TILES,
                                            z - acre_z * VILLAGER_IMPRESSION_ACRE_TILES, 0);
            if (code != NULL && wanted(*code)) {
                count++;
                if (count >= needed) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

/* func_0207ec84: at least two of the nine tiles around the player hold a code of family A or
 * C or one after them. */
int VillagerImpression_NearFamilyAC(void)
{
    return VillagerImpression_CountNear(VillagerImpression_IsFamilyAC, VILLAGER_IMPRESSION_NEAR_FAMILY_AC);
}
CLEAN_AS(func_0207ec84, VillagerImpression_NearFamilyAC)

/* func_0207edcc: at least three of the nine tiles around the player hold one of codes
 * 0x21-0x24. */
int VillagerImpression_NearCodes21To24(void)
{
    return VillagerImpression_CountNear(VillagerImpression_IsCode21To24, VILLAGER_IMPRESSION_NEAR_CODES_21);
}
CLEAN_AS(func_0207edcc, VillagerImpression_NearCodes21To24)

/* ---- The player's flag */

/* func_0207ee70: flag 0 of the player's record (PlayerRecord_Flag0).
 * QUIRK: the source defines it as void, yet it stands in the table of tests: the ROM's code
 * hands the flag back in r0 as the result of its last call, and the table's caller reads it. */
void VillagerImpression_HasFlag0(u8 *record)
{
    (void) PlayerRecord_Flag0(record);
}
CLEAN_AS(func_0207ee70, VillagerImpression_HasFlag0)
