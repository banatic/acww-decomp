/* What the town's day does to the families' codes, and how two family A codes make a third
 * (town_family.h). */
#include "town_family.h"

#include "clean.h"
#include "town_acre_count.h"
#include "town_place.h"
#include "town_tile_put.h"
#include "main_random.h"

extern const u8 data_020ca5d4[8]; /* the eight tiles around one: 0x10 * (8 - dx) + (8 - dz) */
/* The chance in 100, by code 0x00-0x1a, that the first day passed moves it to family B. */
extern const int data_020cb4e8[0x1b];
/* The same for the further days. */
extern const int data_020cb554[0x1b];
/* The codes two family A codes make, by their line and lower stage, then by the higher. */
extern const TownFamilyCrosses *const data_020db7c4[][TOWN_FAMILY_STAGES];

#define TOWN_FAMILY_A_TO_B 0x6e /* added to a code of family A (or 0x1a) to make family B's */
#define TOWN_FAMILY_C_TO_A 0x8a /* taken off a code of family C to make family A's */
#define TOWN_FAMILY_LAST_MOVED 0x1a
#define TOWN_FAMILY_A_LAST 0x19
#define TOWN_FAMILY_1D 0x1d
#define TOWN_FAMILY_1E 0x1e
#define TOWN_FAMILY_1D_PERCENT 30
#define TOWN_FAMILY_1E_PERCENT 30
#define TOWN_FAMILY_C_LAST 0xa4
#define TOWN_FAMILY_A5 0xa5
#define TOWN_FAMILY_A5_TO 0x1c
#define TOWN_FAMILY_WEEK 7
#define TOWN_FAMILY_NO_CHANGE 0xffff
#define TOWN_FAMILY_AROUND 8

/* Family B's codes and 0x88, 0x89. */
static int is_family_b_or_after(u16 code)
{
    return code >= 0x6e && code <= 0x89;
}

static int chance(int percent)
{
    return (int) MainRandom_Below(100) < percent;
}

/* func_020499cc: the families' codes of the map after a further day (`day` from the first,
 * every seventh one also taking family B's codes off). */
void TownFamily_Day(TownDay *town, AcreMap *map, u32 day)
{
    (void) town;
    int week_day = (int) day % TOWN_FAMILY_WEEK;
    int wide = map->acres_wide << 4;
    int high = map->acres_high << 4;
    for (int z = 0; z < high; z++) {
        for (int x = 0; x < wide; x++) {
            const u16 *code = TownAcreCount_CodeAt(map, x, z);
            if (code == NULL) {
                continue;
            }
            int next = TOWN_FAMILY_NO_CHANGE;
            u16 now = *code;
            if (is_family_b_or_after(now)) {
                if (week_day == 0) {
                    next = ACRE_MAP_ITEM_NONE;
                }
            } else if (now == TOWN_FAMILY_1E) {
                if (week_day == 0 && chance(TOWN_FAMILY_1E_PERCENT)) {
                    next = ACRE_MAP_ITEM_NONE;
                }
            } else if (now <= TOWN_FAMILY_LAST_MOVED) {
                if (chance(data_020cb554[now])) {
                    next = now + TOWN_FAMILY_A_TO_B;
                }
            } else if (now == TOWN_FAMILY_1D) {
                if (chance(TOWN_FAMILY_1D_PERCENT)) {
                    next = TOWN_FAMILY_1E;
                }
            }
            if (next != TOWN_FAMILY_NO_CHANGE) {
                TownTilePut_At(map, (u32) x, (u32) z, (u16) next, 0);
            }
        }
    }
}
CLEAN_AS(func_020499cc, TownFamily_Day)

/* func_02049ad0: the families' codes of the map after the first day passed. */
void TownFamily_FirstDay(TownDay *town, AcreMap *map)
{
    (void) town;
    int wide = map->acres_wide << 4;
    int high = map->acres_high << 4;
    for (int z = 0; z < high; z++) {
        for (int x = 0; x < wide; x++) {
            const u16 *code = TownAcreCount_CodeAt(map, x, z);
            if (code == NULL) {
                continue;
            }
            u16 next = TOWN_FAMILY_NO_CHANGE;
            u16 now = *code;
            if (is_family_b_or_after(now)) {
                next = ACRE_MAP_ITEM_NONE;
            } else if (now <= TOWN_FAMILY_LAST_MOVED) {
                if (chance(data_020cb4e8[now])) {
                    next = (u16) (now + TOWN_FAMILY_A_TO_B);
                }
            } else if (now == TOWN_FAMILY_1D) {
                if (chance(TOWN_FAMILY_1D_PERCENT)) {
                    next = TOWN_FAMILY_1E;
                }
            } else if (now >= TOWN_FAMILY_C_TO_A && now <= TOWN_FAMILY_C_LAST) {
                next = (u16) (now - TOWN_FAMILY_C_TO_A);
            } else if (now == TOWN_FAMILY_A5) {
                next = TOWN_FAMILY_A5_TO;
            }
            if (next != TOWN_FAMILY_NO_CHANGE) {
                TownTilePut_At(map, (u32) x, (u32) z, next, 0);
            }
        }
    }
}
CLEAN_AS(func_02049ad0, TownFamily_FirstDay)

/* func_02049bc4: the visit of TownGrowth_SpreadFamilyA: when `near` holds a family A code of
 * the line of the code at `tile`, the code they make (TownFamily_DrawCross) put on a free tile
 * around `tile`, or else around `near`; whether it was put.
 * REQUIRES: `tile` is on the map (its code is read without a check; the day lists it from the
 * map). */
int TownFamily_Cross(AcreMap *map, TownGrowthTiles *near, TownGrowthTiles *tile, TownGrowthTiles *size)
{
    const u16 *mate = TownAcreCount_CodeAt(map, near->x, near->z);
    if (mate == NULL || *mate > TOWN_FAMILY_A_LAST) {
        return 0;
    }
    const u16 *code = TownAcreCount_CodeAt(map, tile->x, tile->z);
    int line = TownFamily_Line(code);
    if (line != TownFamily_Line(mate)) {
        return 0;
    }
    int made = TownFamily_DrawCross(code, mate);
    if (made == ACRE_MAP_ITEM_NONE) {
        return 0;
    }
    TownGrowthTiles from = *tile;
    TownGrowthTiles map_size = *size;
    if (TownFamily_PutAround(map, &map_size, &from, made) != 0) {
        return 1;
    }
    from = *near;
    map_size = *size;
    return TownFamily_PutAround(map, &map_size, &from, made);
}
CLEAN_AS(func_02049bc4, TownFamily_Cross)

/* func_020498b0: `code` put on the first free tile around `tile` (TownFamily_PutOnFree) inside
 * the map's `size`, starting from one of the eight drawn at random; whether it was put. */
int TownFamily_PutAround(AcreMap *map, const TownGrowthTiles *size, const TownGrowthTiles *tile, int code)
{
    int index = (int) MainRandom_Below(TOWN_FAMILY_AROUND);
    for (int i = 0; i < TOWN_FAMILY_AROUND; i++) {
        u8 offset = data_020ca5d4[index];
        TownGrowthTiles near = {tile->x - ((offset >> 4) - 8), tile->z - ((offset & 15) - 8)};
        if (near.x >= 0 && near.x < size->x && near.z >= 0 && near.z < size->z) {
            TownGrowthTiles map_size = *size;
            TownGrowthTiles from = *tile;
            if (TownFamily_PutOnFree(map, &near, &from, &map_size, (u16) code) != 0) {
                return 1;
            }
        }
        index = (index + 1) % TOWN_FAMILY_AROUND;
    }
    return 0;
}
CLEAN_AS(func_020498b0, TownFamily_PutAround)

/* func_02049ca0: `code` put (unmarked) on `tile` when it is free and its unit has word 6 of 0 or
 * 1 (TownPlace_TestWord06Low); whether it was put. */
int TownFamily_PutOnFree(AcreMap *map, const TownGrowthTiles *tile, const TownGrowthTiles *from, const TownGrowthTiles *size,
                         u16 code)
{
    (void) from;
    (void) size;
    const u16 *now = TownAcreCount_CodeAt(map, tile->x, tile->z);
    if (now == NULL || *now != ACRE_MAP_ITEM_NONE) {
        return 0;
    }
    if (TownPlace_TestWord06Low(map, tile->x, tile->z) == 0) {
        return 0;
    }
    TownTilePut_At(map, (u32) tile->x, (u32) tile->z, code, 0);
    return 1;
}
CLEAN_AS(func_02049ca0, TownFamily_PutOnFree)

/* func_02049d04: the code two codes of a line make: drawn from the list data_020db7c4 gives for
 * the line of `code` and the two codes' stages (lower, then higher), each entry by its chance in
 * 100; 0xfff1 when the draw goes past the list or there is none. */
int TownFamily_DrawCross(const u16 *code, const u16 *mate)
{
    int left = (int) MainRandom_Below(100);
    int made = ACRE_MAP_ITEM_NONE;
    int line = TownFamily_Line(code);
    int low = TownFamily_Stage(code);
    int high = TownFamily_Stage(mate);
    if (low > high) {
        int stage = low;
        low = high;
        high = stage;
    }
    const TownFamilyCrosses *list = &data_020db7c4[line][low][high];
    const TownFamilyCross *entry = list->entries;
    if (entry != NULL) {
        for (int count = list->count; count != 0; count--, entry++) {
            left -= entry->chance;
            if (left <= 0) {
                made = entry->code;
                break;
            }
        }
    }
    return made;
}
CLEAN_AS(func_02049d04, TownFamily_DrawCross)

/* func_02049d78: the code's stage in its line (TownFamily_Line), from 1; 1 for a code of no
 * family's lines. */
int TownFamily_Stage(const u16 *code)
{
    u16 now = *code;
    int stage = 1;
    if (now <= 0x19 || now == 0x1c) {
        switch (TownFamily_Line(code)) {
            case 0:
                stage = *code + 1;
                break;
            case 1:
                stage = *code - 0x05;
                break;
            case 2:
                stage = *code - 0x0b;
                break;
            case 3:
                stage = *code == 0x1c ? 9 : *code - 0x11;
                break;
        }
    } else if (TownAcreCount_IsFamilyCCode(now)) {
        switch (TownFamily_Line(code)) {
            case 0:
                stage = *code - 0x89;
                break;
            case 1:
                stage = *code - 0x8f;
                break;
            case 2:
                stage = *code - 0x95;
                break;
            case 3:
                stage = *code == TOWN_FAMILY_A5 ? 7 : *code - 0x9b;
                break;
        }
    } else if (TownAcreCount_IsFamilyBCode(now)) {
        switch (TownFamily_Line(code)) {
            case 0:
                stage = *code - 0x6d;
                break;
            case 1:
                stage = *code - 0x73;
                break;
            case 2:
                stage = *code - 0x79;
                break;
            case 3:
                stage = *code - 0x7f;
                break;
        }
    }
    return stage;
}
CLEAN_AS(func_02049d78, TownFamily_Stage)

/* func_02049ec4: the line of the code in its family (0-3: 0x00 / 0x6e / 0x8a, 0x06 / 0x74 /
 * 0x90, 0x0c / 0x7a / 0x96, 0x12 / 0x80 / 0x9c and 0x1c, 0xa5); 4 for 0x1a, 0x88 and 0xa4, 5
 * for 0x1d, 6 for 0x1e, 7 for any other. */
int TownFamily_Line(const u16 *code)
{
    u16 now = *code;
    if (now <= 0x05 || (now >= 0x8a && now <= 0x8f) || (now >= 0x6e && now <= 0x73)) {
        return 0;
    }
    if ((now >= 0x06 && now <= 0x0b) || (now >= 0x90 && now <= 0x95) || (now >= 0x74 && now <= 0x79)) {
        return 1;
    }
    if ((now >= 0x0c && now <= 0x11) || (now >= 0x96 && now <= 0x9b) || (now >= 0x7a && now <= 0x7f)) {
        return 2;
    }
    if ((now >= 0x12 && now <= 0x19) || now == 0x1c || (now >= 0x9c && now <= 0xa3) || now == TOWN_FAMILY_A5 ||
        (now >= 0x80 && now <= 0x87)) {
        return 3;
    }
    switch (now) {
        case 0x1a:
        case 0x88:
        case 0xa4:
            return 4;
        case TOWN_FAMILY_1D:
            return 5;
        case TOWN_FAMILY_1E:
            return 6;
        default:
            return TOWN_FAMILY_LINE_OTHER;
    }
}
CLEAN_AS(func_02049ec4, TownFamily_Line)
