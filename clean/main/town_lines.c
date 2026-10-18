/* What the town's day does to the growth lines' codes besides moving them on (town_lines.h). */
#include "town_lines.h"

#include "acre_tile.h"
#include "clean.h"
#include "map_item.h"
#include "town_acre_count.h"
#include "town_tile_put.h"
#include "map_code.h"

extern const u8 data_020ca5d4[8];     /* the eight tiles around one: 0x10 * (8 - dx) + (8 - dz) */
extern const u8 data_020cacc0[48];    /* the tiles within three of one, the same way */
extern const int data_020cac3c[3][2]; /* the first x of the three patterns, in even and odd rows */
/* The summary's acre records as bytes (TownDayAcres.acres of data_021c779c). */
extern u8 data_021c7a08[];

#define TOWN_LINES_AROUND 8
#define TOWN_LINES_NEAR 48
#define TOWN_LINES_CROWD 8 /* line codes within three tiles that make a stage-0 code go back */
#define TOWN_LINES_PATTERNS 3
#define TOWN_LINES_PATTERN_STEP 4
#define TOWN_LINES_5D_ROWS 0x30 /* line 0x5d's stage-0 codes stay only above this row */
#define TOWN_LINES_C8_ROW 0x40  /* line 0xc8's only from this row on */
#define TOWN_LINES_GROUND 1     /* the unit word 6 a stage-0 code stays on */
#define TOWN_LINES_RECORD_SIZE 0x24
#define TOWN_LINES_COLUMN_SIZE (TOWN_DAY_ACRES_HIGH * TOWN_LINES_RECORD_SIZE)

static_assert(sizeof(TownAcreCount) == TOWN_LINES_RECORD_SIZE, "TownAcreCount");
static_assert(offsetof(TownAcreCount, lines) == 4, "TownAcreCount.lines");

/* The tile an offset of data_020ca5d4 or data_020cacc0 gives from (x, z). */
static TownGrowthTiles offset_tile(u8 offset, int x, int z)
{
    TownGrowthTiles near = {x - ((offset >> 4) - 8), z - ((offset & 15) - 8)};
    return near;
}

static int inside(const TownGrowthTiles *tile, const TownGrowthTiles *size)
{
    return tile->x >= 0 && tile->x < size->x && tile->z >= 0 && tile->z < size->z;
}

/* func_020493d4: each stage-0 line code of the map with eight or more line codes (of any
 * stage) on the 48 tiles within three of it goes back. */
void TownLines_ThinCrowded(TownDay *town, AcreMap *map, const TownGrowthTiles *size)
{
    (void) town;
    for (int z = 0; z < size->z; z++) {
        for (int x = 0; x < size->x; x++) {
            u16 *code = TownAcreCount_CodeAt(map, x, z);
            if (code == NULL || !TownAcreCount_IsLineCode(*code) || MapItem_IsStage0(code) == 0) {
                continue;
            }
            int crowd = 0;
            for (int i = 0; i < TOWN_LINES_NEAR; i++) {
                TownGrowthTiles near = offset_tile(data_020cacc0[i], x, z);
                if (!inside(&near, size)) {
                    continue;
                }
                const u16 *other = TownAcreCount_CodeAt(map, near.x, near.z);
                if (other != NULL && TownAcreCount_IsLineCode(*other)) {
                    crowd++;
                }
            }
            if (crowd >= TOWN_LINES_CROWD) {
                TownLines_PutBack(map, *code, x, z);
            }
        }
    }
}
CLEAN_AS(func_020493d4, TownLines_ThinCrowded)

/* func_02049638: on each of three patterns (every fourth tile of a row, from the x
 * data_020cac3c gives for even and odd rows), each stage-0 code makes the stage-0 codes around
 * it go back (TownLines_PutBackAround). */
void TownLines_ThinNeighbours(TownDay *town, AcreMap *map, const TownGrowthTiles *size)
{
    for (int pattern = 0; pattern < TOWN_LINES_PATTERNS; pattern++) {
        const int *first = data_020cac3c[pattern];
        for (int z = 0; z < size->z; z++) {
            for (int x = first[z & 1]; x < size->x; x += TOWN_LINES_PATTERN_STEP) {
                u16 *code = TownAcreCount_CodeAt(map, x, z);
                if (code == NULL || MapItem_IsStage0(code) == 0) {
                    continue;
                }
                TownGrowthTiles tile = {x, z};
                TownGrowthTiles map_size = *size;
                TownLines_PutBackAround(town, map, &map_size, &tile);
            }
        }
    }
}
CLEAN_AS(func_02049638, TownLines_ThinNeighbours)

/* func_020496cc: the stage-0 codes around `tile` gone back (func_02049f74 on each; 0). */
int TownLines_PutBackAround(TownDay *town, AcreMap *map, const TownGrowthTiles *size, const TownGrowthTiles *tile)
{
    (void) town;
    return TownLines_VisitAround(map, size, tile, func_02049f74);
}
CLEAN_AS(func_020496cc, TownLines_PutBackAround)

/* func_020496f8: each stage-0 code of the map checked for its ground (TownLines_Check5d for
 * code 0x5d, TownLines_CheckC8 for 0xc8, else TownLines_CheckTile). */
void TownLines_CheckGround(TownDay *town, AcreMap *map, const TownGrowthTiles *size)
{
    for (int z = 0; z < size->z; z++) {
        for (int x = 0; x < size->x; x++) {
            u16 *code = TownAcreCount_CodeAt(map, x, z);
            if (code == NULL || MapItem_IsStage0(code) == 0) {
                continue;
            }
            TownGrowthTiles map_size = *size;
            switch (*code) {
                case 0x5d:
                    TownLines_Check5d(town, map, code, &map_size, x, z);
                    break;
                case 0xc8:
                    TownLines_CheckC8(town, map, code, &map_size, x, z);
                    break;
                default:
                    TownLines_CheckTile(town, map, code, &map_size, x, z);
                    break;
            }
        }
    }
}
CLEAN_AS(func_020496f8, TownLines_CheckGround)

/* func_020497b0: a stage-0 code 0xc8 above row 64 goes back, else is checked as any. */
void TownLines_CheckC8(TownDay *town, AcreMap *map, u16 *code, const TownGrowthTiles *size, int x, int z)
{
    if (z < TOWN_LINES_C8_ROW) {
        TownLines_PutBack(map, *code, x, z);
        return;
    }
    TownGrowthTiles map_size = *size;
    TownLines_CheckTile(town, map, code, &map_size, x, z);
}
CLEAN_AS(func_020497b0, TownLines_CheckC8)

/* func_020497e4: a stage-0 code 0x5d from row 48 on goes back, else is checked as any. */
void TownLines_Check5d(TownDay *town, AcreMap *map, u16 *code, const TownGrowthTiles *size, int x, int z)
{
    if (z >= TOWN_LINES_5D_ROWS) {
        TownLines_PutBack(map, *code, x, z);
        return;
    }
    TownGrowthTiles map_size = *size;
    TownLines_CheckTile(town, map, code, &map_size, x, z);
}
CLEAN_AS(func_020497e4, TownLines_Check5d)

/* func_02049818: the stage-0 code at (x, z) goes back unless its tile's unit has word 6 of 1
 * and nothing around it stands in its way (TownLines_HasRoom). */
void TownLines_CheckTile(TownDay *town, AcreMap *map, u16 *code, const TownGrowthTiles *size, int x, int z)
{
    if (AcreTile_UnitWord06(map, x, z) != TOWN_LINES_GROUND) {
        TownLines_PutBack(map, *code, x, z);
        return;
    }
    TownGrowthTiles tile = {x, z};
    TownGrowthTiles map_size = *size;
    if (TownLines_HasRoom(town, map, &map_size, &tile) == 0) {
        TownLines_PutBack(map, *code, x, z);
    }
}
CLEAN_AS(func_02049818, TownLines_CheckTile)

/* func_02049878: whether none of the tiles around `tile` holds a grown line code, an occupied
 * tile, a short line's code or a rock (func_02049fbc on each). */
int TownLines_HasRoom(TownDay *town, AcreMap *map, const TownGrowthTiles *size, const TownGrowthTiles *tile)
{
    (void) town;
    return TownLines_VisitAround(map, size, tile, func_02049fbc) == 0;
}
CLEAN_AS(func_02049878, TownLines_HasRoom)

/* func_02049944: each of the eight tiles around `tile` (data_020ca5d4, in its order) inside the
 * map's `size` handed to `visit` with copies of the tile and the size, until an answer is not
 * 0; the last answer (0 for none). */
int TownLines_VisitAround(AcreMap *map, const TownGrowthTiles *size, const TownGrowthTiles *tile, TownLinesVisit visit)
{
    int answer = 0;
    for (int i = 0; i < TOWN_LINES_AROUND; i++) {
        TownGrowthTiles near = offset_tile(data_020ca5d4[i], tile->x, tile->z);
        if (!inside(&near, size)) {
            continue;
        }
        if (near.x == tile->x && near.z == tile->z) {
            continue;
        }
        TownGrowthTiles map_size = *size;
        TownGrowthTiles from = *tile;
        answer = visit(map, &near, &from, &map_size);
        if (answer != 0) {
            break;
        }
    }
    return answer;
}
CLEAN_AS(func_02049944, TownLines_VisitAround)

/* func_02049f74: a stage-0 code at `near` goes back; 0 (the visit goes on). */
int TownLines_PutBackStage0(AcreMap *map, const TownGrowthTiles *near)
{
    u16 *code = TownAcreCount_CodeAt(map, near->x, near->z);
    if (code != NULL && MapItem_IsStage0(code) != 0) {
        TownLines_PutBack(map, *code, near->x, near->z);
    }
    return 0;
}
CLEAN_AS(func_02049f74, TownLines_PutBackStage0)

/* func_02049fbc: whether `near` holds a code TownLines_IsGrownOrRock picks out. */
int TownLines_BlocksAt(AcreMap *map, const TownGrowthTiles *near)
{
    const u16 *code = TownAcreCount_CodeAt(map, near->x, near->z);
    if (code == NULL) {
        return 0;
    }
    return TownLines_IsGrownOrRock(code);
}
CLEAN_AS(func_02049fbc, TownLines_BlocksAt)

/* func_02049ff0: TownLines_IsGrownOrOccupied, or a rock: 0xe3-0xe7 or a money rock 0xe8-0xfb. */
int TownLines_IsGrownOrRock(const u16 *code)
{
    if (TownLines_IsGrownOrOccupied(code) != 0) {
        return 1;
    }
    return *code >= 0xe3 && *code <= 0xfb;
}
CLEAN_AS(func_02049ff0, TownLines_IsGrownOrRock)

/* func_0204a034: whether the code is an occupied tile or stands for one (func_0204bbec), a line
 * code past stage 0 (or a code at the last stage only), or a short line's code (0x2b-0x2e,
 * 0x62-0x65, 0xd0-0xd3, 0xff-0x102). */
int TownLines_IsGrownOrOccupied(const u16 *code)
{
    if (MapCode_IsBuildingOrCovered(code) != 0) {
        return 1;
    }
    if (TownAcreCount_IsLineCode(*code) && MapItem_IsStage0(code) == 0) {
        return 1;
    }
    u16 now = *code;
    return (now >= 0x2b && now <= 0x2e) || (now >= 0xff && now <= 0x102) || (now >= 0x62 && now <= 0x65) ||
           (now >= 0xd0 && now <= 0xd3);
}
CLEAN_AS(func_0204a034, TownLines_IsGrownOrOccupied)

/* func_0204a150: the code at (x, z) moved on a stage (unmarked): a line's eighth code back
 * three, else one on unless it is grown. */
void TownLines_Advance(AcreMap *map, const u16 *code, int x, int z)
{
    u16 next = *code;
    if (MapItem_IsEighth(code) != 0) {
        next -= 3;
    } else if (MapItem_IsGrown(code) == 0) {
        next += 1;
    }
    TownTilePut_At(map, (u32) x, (u32) z, next, 0);
}
CLEAN_AS(func_0204a150, TownLines_Advance)

/* func_0204a198: the stage-0 code `code` at (x, z) put back to the code before its line's first
 * (0x5c for 0x5d, 0xc7 for 0xc8, else 0x25), unmarked, and taken off its quarter's count.
 *
 * BUG: the count taken from is that of the summary's record [x / 16][z / 16], numbered by the
 * map's acre where the records are numbered by inner acre (the map's acre less one): the count
 * of the acre down and right of the tile's goes down, a tile of the map's fifth row of acres
 * reaches the next column's first record and one of its fifth column a byte past the records
 * (BUGFIX: the tile's own inner acre). */
void TownLines_PutBack(AcreMap *map, u16 code, int x, int z)
{
    u8 before = TOWN_LINES_BEFORE_26;
    switch (code) {
        case 0x5d:
            before = TOWN_LINES_BEFORE_5D;
            break;
        case 0xc8:
            before = TOWN_LINES_BEFORE_C8;
            break;
    }
    int acre_x = x >> 4;
    int acre_z = z >> 4;
#ifdef BUGFIX
    acre_x--;
    acre_z--;
#endif
    int quarter_x = (x & 15) >> 3;
    int quarter_z = (z & 15) >> 3;
    int at = acre_x * TOWN_LINES_COLUMN_SIZE + acre_z * TOWN_LINES_RECORD_SIZE + (int) offsetof(TownAcreCount, lines) +
             quarter_x * 2 + quarter_z;
    data_021c7a08[at]--;
    TownTilePut_At(map, (u32) x, (u32) z, before, 0);
}
CLEAN_AS(func_0204a198, TownLines_PutBack)
