/* The score of a room's furniture (room_score.h). */
#include "room_score.h"

#include "acre_tile.h"
#include "block_02034858.h"
#include "clean.h"
#include "furniture_info.h"
#include "game_variables.h"
#include "item_code.h"
#include "item_footprint.h"
#include "villager_furniture.h"
#include "villager_roster.h"

static_assert(offsetof(RoomScoreRoom, bottom) == 0x0c, "RoomScoreRoom bottom");
static_assert(offsetof(RoomScoreRoom, carpet) == 0x12, "RoomScoreRoom carpet");
static_assert(sizeof(RoomScoreRoom) == 0x14, "RoomScoreRoom size");

#define ROOM_SCORE_TILES 16 /* a room's acre is 16 x 16 tiles */
#define ROOM_SCORE_LAYERS 2
#define ROOM_SCORE_NO_ITEM 0xfff1
/* The distinct pieces RoomScore_FlagBitsBonus and RoomScore_ColorBonus keep apart. */
#define ROOM_SCORE_DISTINCT 0x18
#define ROOM_SCORE_NO_PIECE 0xffff
/* Below this many pieces the shares are not looked at. */
#define ROOM_SCORE_SHARE_PIECES 10
/* The shares (20.12): 90% and 70%. */
#define ROOM_SCORE_SHARE_HIGH 0xe66
#define ROOM_SCORE_SHARE_LOW 0xb33
/* What func_020622a0 gives for a group. */
#define ROOM_SCORE_GROUP_KIND0 0
#define ROOM_SCORE_GROUP_KIND1 1
#define ROOM_SCORE_GROUP_KIND2 2
/* The wallpapers and the carpets. */
#define ROOM_SCORE_WALLPAPER_FIRST 0x1100
#define ROOM_SCORE_WALLPAPER_LAST 0x1143
#define ROOM_SCORE_CARPET_FIRST 0x1144
#define ROOM_SCORE_CARPET_LAST 0x1187
#define ROOM_SCORE_DESIGNS 0x44
/* The marks of RoomScore_MarkSpecialItems: a bit per furniture number. */
#define ROOM_SCORE_MARK_WORDS (0xe0 / 4)
#define ROOM_SCORE_SPECIAL_POINTS 7777
/* The five rooms of the player's house. */
#define ROOM_SCORE_HOUSE_ROOMS 5
/* The game variable (bank 0) that has the letters sent whatever the week. */
#define ROOM_SCORE_VARIABLE_ALWAYS 0x22

/* Each group's best score of the rooms, by group. */
extern u32 data_021c9854[ROOM_SCORE_GROUPS];
/* The special items' marks. */
extern u32 data_021c9774[ROOM_SCORE_MARK_WORDS];
/* The categories (bits 0-3 for 1-4) each group's pieces have, by group; the word that
 * follows them (word 10 of data_021c9a7c) has the categories of all the rooms' furniture. */
extern u32 data_021c997c[ROOM_SCORE_GROUPS];
extern u32 data_021c9a7c[];
#define ROOM_SCORE_ALL_CATEGORIES data_021c9a7c[10]
/* The villager's room's map while it is scored (0 for none), and the heap it is made from. */
extern u32 data_021c95f0;
extern void *data_021fbe94;
/* The town's villagers; the house's five rooms' records (0x450 bytes each). */
extern VillagerTown data_021e5a2c;
extern u8 data_021ebcd4[];
/* When the house's rooms were last judged (func_0205be9c, func_0205be64). */
extern u8 data_021f3b70[];
/* The vtables of the room sources: the base one's, the villager's room's and the house's. */
extern const u32 data_020dd404[];
extern const u32 data_020dd3a4[];
extern const u32 data_020dd3b8[];
/* The bits a group's wallpaper (0x400) and carpet (0x800) stand for among its pieces. */
extern const u16 data_020cbff0;
extern const u16 data_020cbff4;
/* The town's counts of RoomScore_CountHouseEdges. */
extern u8 data_021c95e0, data_021c95e4, data_021c95e8;

extern void MI_CpuFill8(void *dst, u8 value, u32 size);
extern void MIi_CpuClearFast(u32 data, void *dest, u32 size);
extern fx32 FX_Div(fx32 numerator, fx32 denominator);
extern u8 MATH_CountPopulation(u32 x);
extern u32 func_020644cc(int bound); /* a random number below `bound` */
/* A group's kind (ROOM_SCORE_GROUP_KIND*, 3 for none). */
extern u8 func_020622a0(int group);
/* The group of a wallpaper's or a carpet's item code. */
extern u8 func_02062998(const u16 *item);
/* The points of a value of FurnitureInfo_Unk04 (0 from 46). */
extern int func_0206226c(int value);
/* Whether a week has passed since the date at `when` (and the hour is past 6). */
extern int func_0205be9c(u8 *when);
/* The date at `when` set to today's. */
extern void func_0205be64(u8 *when);
/* The house's 3-bit value at 0x15a0 the low scores' message goes by. */
extern u32 func_02060e78(u8 *house);
/* One of the house's rooms' records, or 0; its wallpaper and its carpet. */
extern int func_02060ee0(void *records, int index);
extern u16 *func_02061204(void *record, int *flag);
extern u16 *func_020611e8(void *record, unsigned int *flag);

/* The acre of tile `tile` (rounded down, as the ARM's arithmetic shift does). */
static u32 tile_acre(u32 tile)
{
    u32 acre = tile >> 4;
    if ((tile & 0x80000000u) != 0) {
        acre |= 0xf0000000u;
    }
    return acre;
}

/* The item code at tile (x, z) of `layer`, NULL outside the map. */
static u16 *tile_item(AcreMap *map, u32 x, u32 z, u8 layer)
{
    return AcreTile_ItemInAcre(map, tile_acre(x), tile_acre(z), (int) (x & 15), (int) (z & 15), layer);
}

/* What a scan does with each item it finds. */
typedef void (*RoomScoreVisit)(void *context, u16 *item, u32 x, u32 z);

/* `visit` for each item of the square (x from `left` to `right`, z from `top` to `bottom`),
 * layer by layer, row by row. The bounds compare unsigned, as the original's do. */
static void scan_square(AcreMap *map, u32 left, u32 top, u32 right, u32 bottom, RoomScoreVisit visit, void *context)
{
    for (u8 layer = 0; layer < ROOM_SCORE_LAYERS; layer++) {
        for (u32 z = top; z <= bottom; z++) {
            for (u32 x = left; x <= right; x++) {
                u16 *item = tile_item(map, x, z, layer);
                if (item != NULL) {
                    visit(context, item, x, z);
                }
            }
        }
    }
}

static void scan_room(const RoomScoreRoom *room, AcreMap *map, RoomScoreVisit visit, void *context)
{
    scan_square(map, (u32) room->left, (u32) room->top, (u32) room->right, (u32) room->bottom, visit, context);
}

/* `id` kept among the distinct pieces (the first free place, when it is not there yet). */
static void keep_distinct(u16 *ids, int id)
{
    for (int i = 0; i < ROOM_SCORE_DISTINCT; i++) {
        if (id == ids[i]) {
            return;
        }
        if (ids[i] == ROOM_SCORE_NO_PIECE) {
            ids[i] = (u16) id;
            return;
        }
    }
}

static void clear_distinct(u16 *ids)
{
    for (int i = 0; i < ROOM_SCORE_DISTINCT; i++) {
        ids[i] = ROOM_SCORE_NO_PIECE;
    }
}

static int count_distinct(const u16 *ids)
{
    int count = 0;
    for (int i = 0; i < ROOM_SCORE_DISTINCT; i++) {
        if (ids[i] != ROOM_SCORE_NO_PIECE) {
            count++;
        }
    }
    return count;
}

/* The group's best score raised to `score`; whether it was below it. */
static int raise_group(u32 group, u32 score)
{
    if (data_021c9854[group] < score) {
        data_021c9854[group] = score;
        return 1;
    }
    return 0;
}

/* The bits of the first `count` pieces of a group, as the original builds the mask (16 bits). */
static u16 group_mask(u32 count)
{
    u16 mask = 0;
    for (u32 i = 0; i < count; i++) {
        mask |= (u16) (1u << i);
    }
    return mask;
}

/* func_0205a370: the square of the room's tiles with byte 4 set (AcreTile_UnitByte04): the
 * least and greatest x and z among them. Whether there was one; when not, the bounds are left
 * at 16 and -16. */
int RoomScore_Bounds(int *left, int *right, int *top, int *bottom, AcreMap *map)
{
    *top = ROOM_SCORE_TILES;
    *left = *top;
    *bottom = -ROOM_SCORE_TILES;
    *right = *bottom;

    int found_left = 0;
    int found_right = 0;
    int found_top = 0;
    int found_bottom = 0;
    for (int z = 0; z < ROOM_SCORE_TILES; z++) {
        for (int x = 0; x < ROOM_SCORE_TILES; x++) {
            if (AcreTile_UnitByte04(map, x, z) == 0) {
                continue;
            }
            if (x <= *left) {
                *left = x;
                found_left = 1;
            }
            if (x >= *right) {
                *right = x;
                found_right = 1;
            }
            if (z <= *top) {
                *top = z;
                found_top = 1;
            }
            if (z >= *bottom) {
                *bottom = z;
                found_bottom = 1;
            }
        }
    }
    return found_left && found_right && found_top && found_bottom;
}
CLEAN_AS(func_0205a370, RoomScore_Bounds)

static void mark_special(void *context, u16 *item, u32 x, u32 z)
{
    (void) context;
    (void) x;
    (void) z;
    if (!ItemCode_HasVariant(item)) {
        return;
    }
    int number = ItemCode_VariantItem(item);
    if (FurnitureInfo_IndoorBit0(number) != 0) {
        ((u8 *) data_021c9774)[(u32) number >> 3] |= (u8) (1u << ((u32) number & 7));
    }
}

/* func_0205a65c: each piece of furniture of the room whose indoor record has bit 0 marked in
 * data_021c9774 by its number. */
void RoomScore_MarkSpecialItems(RoomScoreRoom *room, AcreMap *map)
{
    scan_room(room, map, mark_special, NULL);
}
CLEAN_AS(func_0205a65c, RoomScore_MarkSpecialItems)

typedef struct WallPenalty {
    const RoomScoreRoom *room;
    u8 *facing;
    u8 *loose;
    int total;
} WallPenalty;

static void wall_penalty(void *context, u16 *item, u32 x, u32 z)
{
    WallPenalty *p = context;
    if (!ItemCode_HasVariant(item)) {
        if (ItemCode_IsKind1(item)) {
            *p->loose = 1;
            p->total += 1;
        }
        return;
    }
    if (FurnitureInfo_FlagBit4(ItemCode_VariantItem(item)) == 0) {
        return;
    }
    int side = ItemCode_Variant(item);
    /* Each edge, and the side a piece there faces it with. */
    if (x == (u32) p->room->left && side == 3) {
        *p->facing = 1;
        p->total += 100;
    }
    if (x == (u32) p->room->right && side == 1) {
        *p->facing = 1;
        p->total += 100;
    }
    if (z == (u32) p->room->top && side == 2) {
        *p->facing = 1;
        p->total += 100;
    }
    if (z == (u32) p->room->bottom && side == 0) {
        *p->facing = 1;
        p->total += 100;
    }
}

/* func_0205a6f0: the room's penalty: 100 for each edge a piece of furniture with FlagBit4
 * stands at and faces (then *facing = 1), and 1 for each item of kind 1 (then *loose = 1). */
int RoomScore_WallPenalty(RoomScoreRoom *room, AcreMap *map, u8 *facing, u8 *loose)
{
    WallPenalty p = {room, facing, loose, 0};
    scan_room(room, map, wall_penalty, &p);
    return p.total;
}
CLEAN_AS(func_0205a6f0, RoomScore_WallPenalty)

#define ROOM_SCORE_THEMES 5
#define ROOM_SCORE_THEME_PIECES 8

static void count_theme(void *context, u16 *item, u32 x, u32 z)
{
    u8 *counts = context;
    (void) x;
    (void) z;
    if (ItemCode_HasVariant(item)) {
        counts[FurnitureInfo_ItemUnk03(item)]++;
    }
}

/* func_0205a7d4: 400 for each piece of each value 0-3 of FurnitureInfo_ItemUnk03 that 8 or
 * more pieces of the room have (value 4 counts for nothing); *theme is set to the last such
 * value.
 * REQUIRES: FurnitureInfo_ItemUnk03 is below 5. */
int RoomScore_ThemeBonus(RoomScoreRoom *room, AcreMap *map, int *theme)
{
    u8 counts[ROOM_SCORE_THEMES];
    MI_CpuFill8(counts, 0, sizeof(counts));
    scan_room(room, map, count_theme, counts);
    int total = 0;
    for (u32 i = 0; i < ROOM_SCORE_THEMES; i++) {
        if (i != ROOM_SCORE_THEMES - 1 && counts[i] >= ROOM_SCORE_THEME_PIECES) {
            *theme = (int) i;
            total += 400 * counts[i];
        }
    }
    return total;
}
CLEAN_AS(func_0205a7d4, RoomScore_ThemeBonus)

typedef struct ShareCount {
    u16 *ids;
    u8 *histogram;
    int (*value)(const ItemCode *item);
    u32 count;
} ShareCount;

static void count_share(void *context, u16 *item, u32 x, u32 z)
{
    ShareCount *s = context;
    (void) x;
    (void) z;
    if (!ItemCode_HasVariant(item)) {
        return;
    }
    keep_distinct(s->ids, ItemCode_VariantItem(item));
    s->histogram[s->value(item)]++;
    s->count++;
}

/* The bonus of one share: for values 1 and 2 of the histogram, 300 per distinct piece when
 * the value has 90% of the pieces, 100 when 70% (then *category = the value). */
static int share_bonus(const u16 *ids, const u8 *histogram, u32 count, int *category)
{
    if (count < ROOM_SCORE_SHARE_PIECES) {
        return 0;
    }
    int distinct = count_distinct(ids);
    int score = 0;
    for (u32 i = 1; i < 3; i++) {
        fx32 share = FX_Div((fx32) histogram[i] << 12, (fx32) (count << 12));
        if (share >= ROOM_SCORE_SHARE_HIGH) {
            *category = (int) i;
            score += distinct * 300;
        } else if (share >= ROOM_SCORE_SHARE_LOW) {
            *category = (int) i;
            score += distinct * 100;
        }
    }
    return score;
}

/* func_0205a87c: the bonuses of the shares of the room's furniture by
 * FurnitureInfo_ItemFlagBits01 (*first) and by FurnitureInfo_ItemFlagBits23 (*second), each
 * for 10 or more pieces.
 * REQUIRES: both values are below 3. */
int RoomScore_FlagBitsBonus(RoomScoreRoom *room, AcreMap *map, int *first, int *second)
{
    u8 first_histogram[3];
    u8 second_histogram[3];
    u16 ids[ROOM_SCORE_DISTINCT];
    MI_CpuFill8(first_histogram, 0, sizeof(first_histogram));
    MI_CpuFill8(second_histogram, 0, sizeof(second_histogram));

    clear_distinct(ids);
    ShareCount s = {ids, first_histogram, FurnitureInfo_ItemFlagBits01, 0};
    scan_room(room, map, count_share, &s);
    int score = share_bonus(ids, first_histogram, s.count, first);

    clear_distinct(ids);
    ShareCount t = {ids, second_histogram, FurnitureInfo_ItemFlagBits23, 0};
    scan_room(room, map, count_share, &t);
    score += share_bonus(ids, second_histogram, t.count, second);
    return score;
}
CLEAN_AS(func_0205a87c, RoomScore_FlagBitsBonus)

#define ROOM_SCORE_COLORS_COUNT 13

typedef struct ColorCount {
    u16 ids[ROOM_SCORE_DISTINCT];
    u8 counts[ROOM_SCORE_COLORS_COUNT];
    u32 count;
} ColorCount;

static void count_colors(void *context, u16 *item, u32 x, u32 z)
{
    ColorCount *c = context;
    (void) x;
    (void) z;
    if (!ItemCode_HasVariant(item)) {
        return;
    }
    int number = ItemCode_VariantItem(item);
    keep_distinct(c->ids, number);
    int first = FurnitureInfo_Unk01(number);
    int second = FurnitureInfo_Unk02(number);
    c->counts[first]++;
    c->counts[second]++;
    c->count++;
}

/* func_0205ab10: for 10 or more pieces of furniture, each with two values (FurnitureInfo_Unk01
 * and _Unk02): the first value 1-12 with 90% of the values gives 600 per distinct piece, else
 * the first with 70% 200; else 0.
 * QUIRK: the values are looked at in order, and the first one with 70% ends the search even
 * when a later one has 90%.
 * REQUIRES: both values are below 13. */
int RoomScore_ColorBonus(RoomScoreRoom *room, AcreMap *map)
{
    ColorCount c;
    MI_CpuFill8(c.counts, 0, sizeof(c.counts));
    clear_distinct(c.ids);
    c.count = 0;
    scan_room(room, map, count_colors, &c);
    if (c.count < ROOM_SCORE_SHARE_PIECES) {
        return 0;
    }
    int distinct = count_distinct(c.ids);
    fx32 all = (fx32) (c.count << 13); /* two values per piece */
    for (u32 i = 1; i < ROOM_SCORE_COLORS_COUNT; i++) {
        fx32 share = FX_Div((fx32) c.counts[i] << 12, all);
        if (share >= ROOM_SCORE_SHARE_HIGH) {
            return 600 * distinct;
        }
        if (share >= ROOM_SCORE_SHARE_LOW) {
            return 200 * distinct;
        }
    }
    return 0;
}
CLEAN_AS(func_0205ab10, RoomScore_ColorBonus)

/* func_0205ac5c: 100 for each piece counted along the edges. `room` is not used. */
int RoomScore_EdgeBonus(RoomScoreRoom *room, RoomScoreEdges *edges)
{
    (void) room;
    int high_x = RoomScoreEdges_HighX(edges);
    int low_x = RoomScoreEdges_LowX(edges);
    return 100 * (high_x + (low_x + RoomScoreEdges_HighZ(edges)));
}
CLEAN_AS(func_0205ac5c, RoomScore_EdgeBonus)

static void add_points(void *context, u16 *item, u32 x, u32 z)
{
    int *total = context;
    (void) x;
    (void) z;
    if (ItemCode_HasVariant(item)) {
        *total += func_0206226c(FurnitureInfo_Unk04(ItemCode_VariantItem(item)));
    }
}

/* func_0205ac84: the points of the room's furniture, by FurnitureInfo_Unk04 (func_0206226c). */
int RoomScore_ItemPoints(RoomScoreRoom *room, AcreMap *map)
{
    int total = 0;
    scan_room(room, map, add_points, &total);
    return total;
}
CLEAN_AS(func_0205ac84, RoomScore_ItemPoints)

static void mark_category(void *context, u16 *item, u32 x, u32 z)
{
    (void) context;
    (void) x;
    (void) z;
    if (!ItemCode_HasVariant(item)) {
        return;
    }
    int number = ItemCode_VariantItem(item);
    int category = FurnitureInfo_Category(number);
    int group = FurnitureInfo_Group(number);
    u32 bit = 0;
    if (category == 1) {
        bit = 1;
    } else if (category == 2) {
        bit = 2;
    } else if (category == 3) {
        bit = 4;
    } else if (category == 4) {
        bit = 8;
    }
    data_021c997c[group] |= bit;
    ROOM_SCORE_ALL_CATEGORIES |= bit;
}

/* func_0205ad00: the categories 1-4 of the room's furniture marked for its group
 * (data_021c997c) and for all (ROOM_SCORE_ALL_CATEGORIES).
 * REQUIRES: the groups are below ROOM_SCORE_GROUPS. */
void RoomScore_MarkCategories(RoomScoreRoom *room, AcreMap *map)
{
    scan_room(room, map, mark_category, NULL);
}
CLEAN_AS(func_0205ad00, RoomScore_MarkCategories)

typedef struct GroupPieces {
    int kind;
    u16 bits[ROOM_SCORE_GROUPS];
} GroupPieces;

static void mark_piece(void *context, u16 *item, u32 x, u32 z)
{
    GroupPieces *g = context;
    (void) x;
    (void) z;
    if (!ItemCode_HasVariant(item)) {
        return;
    }
    int group = FurnitureInfo_ItemGroup(item);
    if (func_020622a0(group) == g->kind) {
        g->bits[group] |= (u16) (1u << FurnitureInfo_IndexInGroup(item));
    }
}

/* The pieces of each group of `kind` in the room, a bit per piece of its group (cleared
 * first by clear_pieces). */
static void clear_pieces(GroupPieces *g, int kind)
{
    MI_CpuFill8(g->bits, 0, sizeof(g->bits));
    g->kind = kind;
}

static void mark_pieces(GroupPieces *g, RoomScoreRoom *room, AcreMap *map)
{
    scan_room(room, map, mark_piece, g);
}

/* func_0205adc0: each group of kind 2 complete in the room raised to 1000 per piece; whether
 * there was one.
 * QUIRK: a group counts as complete when its bits, as a number, are at least those of all
 * its pieces.
 * REQUIRES: the groups are below ROOM_SCORE_GROUPS. */
int RoomScore_Kind2Sets(RoomScoreRoom *room, AcreMap *map)
{
    GroupPieces g;
    clear_pieces(&g, ROOM_SCORE_GROUP_KIND2);
    mark_pieces(&g, room, map);
    int found = 0;
    for (u32 k = 0; k < ROOM_SCORE_GROUPS; k++) {
        if (func_020622a0((int) k) != ROOM_SCORE_GROUP_KIND2) {
            continue;
        }
        u32 count = FurnitureInfo_CountInGroup(k);
        if (g.bits[k] >= group_mask(count)) {
            found = 1;
            raise_group(k, 1000 * count);
        }
    }
    return found;
}
CLEAN_AS(func_0205adc0, RoomScore_Kind2Sets)

/* func_0205aec0: each group of kind 1 whose wallpaper and carpet are the room's: complete in
 * the room raised to 3000 per piece and 3000 more (and then 1 is returned), else to 3000.
 * QUIRK: complete as in RoomScore_Kind2Sets. */
int RoomScore_Kind1Sets(RoomScoreRoom *room, AcreMap *map)
{
    GroupPieces g;
    clear_pieces(&g, ROOM_SCORE_GROUP_KIND1);
    u32 wallpaper_group = func_02062998(&room->wallpaper);
    u32 carpet_group = func_02062998(&room->carpet);
    mark_pieces(&g, room, map);
    int found = 0;
    for (u32 i = 0; i < ROOM_SCORE_GROUPS; i++) {
        if (func_020622a0((int) i) != ROOM_SCORE_GROUP_KIND1) {
            continue;
        }
        u32 count = FurnitureInfo_CountInGroup(i);
        int matches = i == wallpaper_group && i == carpet_group;
        if (g.bits[i] >= group_mask(count)) {
            if (matches) {
                raise_group(i, 3000 * (count + 1));
                found = 1;
            }
        } else if (matches) {
            raise_group(i, 3000);
        }
    }
    return found;
}
CLEAN_AS(func_0205aec0, RoomScore_Kind1Sets)

/* The pieces of a group of kind 0: its first 10, the 11th and the 12th (which a wallpaper and a
 * carpet of the group stand for too). */
#define ROOM_SCORE_KIND0_TEN_BITS 0x3ff
#define ROOM_SCORE_KIND0_ALL_BITS 0xfff
#define ROOM_SCORE_KIND0_PIECES 12

/* The first group of kind 0 whose pieces are exactly `exact_bits` (or, for -1, its first 10
 * and its 11th or 12th) and whose best is below `score`, raised to it; ROOM_SCORE_GROUPS for
 * none. */
static u32 raise_kind0(const u16 *bits, u32 score, int exact_bits)
{
    for (u32 i = 0; i < ROOM_SCORE_GROUPS; i++) {
        if (func_020622a0((int) i) != ROOM_SCORE_GROUP_KIND0) {
            continue;
        }
        int h = bits[i];
        int match;
        if (exact_bits >= 0) {
            match = h == exact_bits;
        } else {
            match = (h & ROOM_SCORE_KIND0_TEN_BITS) == ROOM_SCORE_KIND0_TEN_BITS && (h & 0xc00) != 0;
        }
        if (match && raise_group(i, score)) {
            return i;
        }
    }
    return ROOM_SCORE_GROUPS;
}

/* func_0205affc: the groups of kind 0: their pieces in the room, a wallpaper and a carpet of
 * the group counting as its 11th and 12th. `*most` (when not NULL) gets the most pieces of the
 * first 12 of a group. Then the first group complete with all 12 is raised to 30000 and
 * returned; else the first with its first 10 and the 11th or 12th to 25000; else the first
 * with exactly its first 10 to 20000; ROOM_SCORE_GROUPS is returned but for the first (and
 * for a group at its best already, which is passed over).
 * BUG: in counting `*most` each group is passed over by the kind of the carpet's group, not by
 * its own (BUGFIX: by its own).
 * REQUIRES: the groups are below ROOM_SCORE_GROUPS. */
int RoomScore_Kind0Sets(RoomScoreRoom *room, AcreMap *map, u32 *most)
{
    GroupPieces g;
    clear_pieces(&g, ROOM_SCORE_GROUP_KIND0);
    mark_pieces(&g, room, map);

    if (room->wallpaper >= ROOM_SCORE_WALLPAPER_FIRST && room->wallpaper <= ROOM_SCORE_WALLPAPER_LAST) {
        u32 group = func_02062998(&room->wallpaper);
        if (func_020622a0((int) group) == ROOM_SCORE_GROUP_KIND0) {
            g.bits[group] |= data_020cbff0;
        }
    }
    if (room->carpet >= ROOM_SCORE_CARPET_FIRST && room->carpet <= ROOM_SCORE_CARPET_LAST) {
        u32 group = func_02062998(&room->carpet);
        if (func_020622a0((int) group) == ROOM_SCORE_GROUP_KIND0) {
            g.bits[group] |= data_020cbff4;
        }
    }

    u32 best = 0;
    for (u32 i = 0; i < ROOM_SCORE_GROUPS; i++) {
#ifdef BUGFIX
        if (func_020622a0((int) i) != ROOM_SCORE_GROUP_KIND0) {
            continue;
        }
#else
        if (func_020622a0(func_02062998(&room->carpet)) != ROOM_SCORE_GROUP_KIND0) {
            continue;
        }
#endif
        u32 pieces = 0;
        for (u32 j = 0; j < ROOM_SCORE_KIND0_PIECES; j++) {
            if (((g.bits[i] >> j) & 1) != 0) {
                pieces++;
            }
        }
        if (pieces > best) {
            best = pieces;
        }
    }
    if (most != NULL) {
        *most = best;
    }

    u32 full = raise_kind0(g.bits, 30000, ROOM_SCORE_KIND0_ALL_BITS);
    if (full != ROOM_SCORE_GROUPS) {
        return (int) full;
    }
    if (raise_kind0(g.bits, 25000, -1) != ROOM_SCORE_GROUPS) {
        return ROOM_SCORE_GROUPS;
    }
    raise_kind0(g.bits, 20000, ROOM_SCORE_KIND0_TEN_BITS);
    return ROOM_SCORE_GROUPS;
}
CLEAN_AS(func_0205affc, RoomScore_Kind0Sets)

/* The slots of a RoomScoreSource's vtable. */
typedef u32 (*RoomScoreMapMethod)(RoomScoreSource *source, int index);
typedef void (*RoomScoreItemMethod)(u16 *out, RoomScoreSource *source, int index);
#define ROOM_SCORE_SLOT_MAP 0
#define ROOM_SCORE_SLOT_WALLPAPER 1
#define ROOM_SCORE_SLOT_CARPET 2

/* The `n`th (from 0) group with a best score and of kind `kind`. */
static u32 pick_group(int n, int kind)
{
    int seen = 0;
    for (u32 m = 0; m < ROOM_SCORE_GROUPS; m++) {
        if (data_021c9854[m] != 0 && func_020622a0((int) m) == kind) {
            if (seen == n) {
                return m;
            }
            seen++;
        }
    }
    return 0;
}

/* The bonus flags of a group of kind 0 by its best. */
static u16 kind0_flag(u32 score)
{
    if (score == 30000) {
        return ROOM_SCORE_KIND0_FULL;
    }
    if (score == 25000) {
        return ROOM_SCORE_KIND0_TEN_AND_WALL;
    }
    return ROOM_SCORE_KIND0_TEN;
}

/* func_0205b270: the score of rooms `first_index` to `first_index + count - 1` of `source`,
 * each measured into `room` (its bounds, wallpaper and carpet): the furniture's points, the
 * edges, the colours, the flag bits' shares (*first, *second), the themes (*theme), less the
 * penalty, plus each group's best (data_021c9854), 5000 when one group has all four
 * categories (1000 when the rooms have them only together), and 7777 for each special item;
 * never below 0. `*bonuses` gets the bonuses found (ROOM_SCORE_*), and a random group of kind
 * 0 with a best is kept, as one of kind 1 over 3000.
 * With `judge`, when a week has passed since the last judgement (or game variable 0x22 is
 * set): the total and the letter's bonuses (with higher thresholds and the two penalties) are
 * kept (RoomScore_SetTotal, RoomScore_SetBonusFlags), and a letter picked: when there is no
 * bonus or by an even chance, by the total (message 0 for none, the house's value + 1 up to
 * 19999, 8 up to 69999, 9 up to 99999, else 10), else message 11 + a random one of the
 * bonuses. It names the group of kind 0 (for messages 11-13) or of kind 1, and the theme.
 * When it is sent, the prizes are too (RoomScoreMail_SendPrize) and the date is kept.
 * QUIRK: the group of kind 1 is drawn among all those with a best, not only over 3000.
 * REQUIRES: `bonuses` is not NULL (it is written before it is tested). */
int RoomScore_Total(RoomScoreRoom *room, u16 *bonuses, int *theme, int *first, int *second, RoomScoreSource *source, int count,
                    int first_index, u8 judge)
{
    *bonuses = 0;
    *theme = 0;
    *first = 0;
    *second = 0;
    MI_CpuFill8(data_021c9854, 0, sizeof(data_021c9854));
    MIi_CpuClearFast(0, data_021c9774, sizeof(data_021c9774));
    for (u32 k = 0; k < ROOM_SCORE_GROUPS; k++) {
        data_021c997c[k] = 0;
    }
    ROOM_SCORE_ALL_CATEGORIES = 0;

    int points = 0;
    int edges_score = 0;
    int colors = 0;
    int flag_bits = 0;
    int themes = 0;
    int penalty = 0;
    int facing = 0;
    int loose = 0;
    for (int i = 0; i < count; i++) {
        int index = first_index + i;
        const u32 *vtable = source->vtable;
        AcreMap *map = (AcreMap *) (uintptr_t) ((RoomScoreMapMethod) (uintptr_t) vtable[ROOM_SCORE_SLOT_MAP])(source, index);
        u16 design;
        ((RoomScoreItemMethod) (uintptr_t) source->vtable[ROOM_SCORE_SLOT_WALLPAPER])(&design, source, index);
        room->wallpaper = design;
        ((RoomScoreItemMethod) (uintptr_t) source->vtable[ROOM_SCORE_SLOT_CARPET])(&design, source, index);
        room->carpet = design;
        RoomScore_Bounds(&room->left, &room->right, &room->top, &room->bottom, map);

        RoomScoreEdges edges;
        RoomScoreEdges_Construct(&edges);
        RoomScore_CountEdges(&edges, map);
        RoomScore_Kind0Sets(room, map, NULL);
        RoomScore_Kind1Sets(room, map);
        RoomScore_Kind2Sets(room, map);
        RoomScore_MarkSpecialItems(room, map);
        RoomScore_MarkCategories(room, map);
        points += RoomScore_ItemPoints(room, map);
        edges_score += RoomScore_EdgeBonus(room, &edges);
        colors += RoomScore_ColorBonus(room, map);
        flag_bits += RoomScore_FlagBitsBonus(room, map, first, second);
        themes += RoomScore_ThemeBonus(room, map, theme);
        u8 faces = 0;
        u8 loose_items = 0;
        penalty += RoomScore_WallPenalty(room, map, &faces, &loose_items);
        if (faces != 0) {
            facing = 1;
        }
        if (loose_items != 0) {
            loose = 1;
        }
        RoomScoreEdges_Destruct(&edges);
    }
    int total = points + edges_score + colors + flag_bits + themes - penalty;

    int kind0_groups = 0;
    int kind1_groups = 0;
    int kind2_total = 0;
    for (u32 j = 0; j < ROOM_SCORE_GROUPS; j++) {
        int v = (int) data_021c9854[j];
        if (v != 0) {
            switch (func_020622a0((int) j)) {
                case ROOM_SCORE_GROUP_KIND0:
                    kind0_groups++;
                    break;
                case ROOM_SCORE_GROUP_KIND1:
                    if ((u32) v > 3000) {
                        kind1_groups++;
                    }
                    break;
                case ROOM_SCORE_GROUP_KIND2:
                    kind2_total += v;
                    break;
                default:
                    break;
            }
        }
        total += v;
    }
    u32 kind0_group = 0;
    if (kind0_groups != 0) {
        kind0_group = pick_group((int) func_020644cc(kind0_groups), ROOM_SCORE_GROUP_KIND0);
    }
    u32 kind1_group = 0;
    if (kind1_groups != 0) {
        kind1_group = pick_group((int) func_020644cc(kind1_groups), ROOM_SCORE_GROUP_KIND1);
    }

    int categories = 0;
    if ((ROOM_SCORE_ALL_CATEGORIES & 0xf) == 0xf) {
        int one_group = 0;
        for (u32 q = 0; q < ROOM_SCORE_GROUPS; q++) {
            if ((data_021c997c[q] & 0xf) == 0xf) {
                one_group = 1;
                break;
            }
        }
        categories = one_group ? 5000 : 1000;
        total += categories;
    }
    int special = RoomScore_SpecialItemsScore(data_021c9774);
    total += special;
    if (total < 0) {
        total = 0;
    }

    if (bonuses != NULL) {
        if (kind0_groups != 0) {
            *bonuses |= kind0_flag(data_021c9854[kind0_group]);
        }
        if (kind1_groups != 0) {
            *bonuses |= ROOM_SCORE_KIND1;
        }
        if (kind2_total >= 3000) {
            *bonuses |= ROOM_SCORE_KIND2;
        }
        if (categories > 0) {
            *bonuses |= ROOM_SCORE_CATEGORIES;
        }
        if (edges_score >= 500) {
            *bonuses |= ROOM_SCORE_EDGES;
        }
        if (colors >= 2000) {
            *bonuses |= ROOM_SCORE_COLORS;
        }
        if (flag_bits >= 2000) {
            *bonuses |= ROOM_SCORE_FLAG_BITS;
        }
        if (themes >= 3000) {
            *bonuses |= ROOM_SCORE_THEME;
        }
        if ((u32) special >= 7000) {
            *bonuses |= ROOM_SCORE_SPECIAL;
        }
    }

    if (judge == 0) {
        return total;
    }
    if (func_0205be9c(data_021f3b70) == 0 && *GameVariables_Slot(0, ROOM_SCORE_VARIABLE_ALWAYS) == 0) {
        return total;
    }
    int house_value = (int) func_02060e78(data_021ebcd4);
    u16 found = 0;
    if (kind0_groups != 0) {
        found |= kind0_flag(data_021c9854[kind0_group]);
    }
    if (kind1_groups != 0) {
        found |= ROOM_SCORE_KIND1;
    }
    if (kind2_total >= 5000) {
        found |= ROOM_SCORE_KIND2;
    }
    if (categories > 0) {
        found |= ROOM_SCORE_CATEGORIES;
    }
    if (edges_score >= 2000) {
        found |= ROOM_SCORE_EDGES;
    }
    if (colors >= 6000) {
        found |= ROOM_SCORE_COLORS;
    }
    if (flag_bits >= 6000) {
        found |= ROOM_SCORE_FLAG_BITS;
    }
    if (themes >= 3200) {
        found |= ROOM_SCORE_THEME;
    }
    if ((u32) special >= 7000) {
        found |= ROOM_SCORE_SPECIAL;
    }
    if (facing) {
        found |= ROOM_SCORE_FACING_WALL;
    }
    if (loose) {
        found |= ROOM_SCORE_LOOSE_ITEMS;
    }
    int found_count = 0;
    for (u32 b = 0; b < ROOM_SCORE_BONUS_BITS; b++) {
        if ((found & (1u << b)) != 0) {
            found_count++;
        }
    }
    RoomScore_SetTotal((u32) total);
    RoomScore_SetBonusFlags(found);

    int by_total = found_count == 0 || func_020644cc(2) == 0;
    int message = 0;
    if (by_total) {
        if (total == 0) {
            message = 0;
        } else if (total <= 19999) {
            message = house_value + 1;
        } else if (total <= 69999) {
            message = 8;
        } else if (total <= 99999) {
            message = 9;
        } else {
            message = 10;
        }
    } else {
        int pick = (int) func_020644cc(found_count);
        int seen = 0;
        for (u32 b = 0; b < ROOM_SCORE_BONUS_BITS; b++) {
            if ((found & (1u << b)) != 0) {
                if (pick == seen) {
                    message = (int) b + 11;
                    break;
                }
                seen++;
            }
        }
    }
    /* Messages 11-13 tell of the kind 0 bonuses. */
    u32 group = (u32) message - 11 > 2 ? kind1_group : kind0_group;
    if (RoomScoreMail_SendJudgement(room, message, total, (int) group, *theme) != 0) {
        RoomScoreMail_SendPrize(room, total);
        func_0205be64(data_021f3b70);
    }
    return total;
}
CLEAN_AS(func_0205b270, RoomScore_Total)

/* func_0205b868: the score of villager `villager`'s room (RoomScore_Total, not judged), its map
 * made for it from the heap data_021fbe94 when there is none and freed after. */
u32 RoomScore_ScoreVillager(RoomScoreRoom *room, int villager, u16 *bonuses, int *theme, int *first, int *second)
{
    if (data_021c95f0 == 0) {
        data_021c95f0 = (u32) AcreMap_CreateVillagerMap(villager, (int) (uintptr_t) data_021fbe94);
    }
    RoomScoreSource source;
    RoomScore_ConstructVillagerSource(&source);
    int total = RoomScore_Total(room, bonuses, theme, first, second, &source, 1, villager, 0);
    if (data_021c95f0 != 0) {
        AcreMap_FreeVillagerMap((int) (uintptr_t) data_021fbe94);
        data_021c95f0 = 0;
    }
    RoomScore_DestructVillagerSource(&source);
    return (u32) total;
}
CLEAN_AS(func_0205b868, RoomScore_ScoreVillager)

/* func_0205b8e0: the five rooms of the player's house scored and judged (RoomScore_Total). */
void RoomScore_JudgeHouse(RoomScoreRoom *room)
{
    RoomScoreSource source;
    u16 bonuses;
    int theme;
    int first;
    int second;
    RoomScore_ConstructHouseSource(&source);
    RoomScore_Total(room, &bonuses, &theme, &first, &second, &source, ROOM_SCORE_HOUSE_ROOMS, 0, 1);
    RoomScore_DestructHouseSource(&source);
}
CLEAN_AS(func_0205b8e0, RoomScore_JudgeHouse)

/* func_0205b91c: what the first room of the house lacks, as flags, and in *count (when not
 * NULL) a count that starts at 3: 1 loose items (count - 1), 2 furniture facing an edge
 * (- 1), 4 all four categories (+ 1), 8 a complete group of kind 1 or 2 (+ 1), 0x40 not
 * both, 0x10 a complete group of kind 0 (+ 2), else 0x20 one with 5 or more of its pieces.
 * Without the room 0, and the count 3. The room's wallpaper and carpet are the record's (the
 * first wallpaper and carpet without it). */
int RoomScore_Advice(RoomScoreRoom *room, int *count)
{
    AcreMap *map = (AcreMap *) (uintptr_t) AcreMap_Room(0);
    int n = 3;
    int flags = 0;
    if (map != NULL) {
        for (u32 i = 0; i < ROOM_SCORE_GROUPS; i++) {
            data_021c997c[i] = 0;
        }
        ROOM_SCORE_ALL_CATEGORIES = 0;
        MI_CpuFill8(data_021c9854, 0, sizeof(data_021c9854));
        RoomScore_Bounds(&room->left, &room->right, &room->top, &room->bottom, map);
        room->wallpaper = ROOM_SCORE_WALLPAPER_FIRST;
        room->carpet = ROOM_SCORE_CARPET_FIRST;
        void *record = (void *) (uintptr_t) func_02060ee0(data_021ebcd4, 0);
        if (record != NULL) {
            room->wallpaper = *func_02061204(record, NULL);
            room->carpet = *func_020611e8(record, NULL);
        }
        u8 facing = 0;
        u8 loose = 0;
        RoomScore_WallPenalty(room, map, &facing, &loose);
        RoomScore_MarkCategories(room, map);
        u32 most = 0;
        int kind0 = RoomScore_Kind0Sets(room, map, &most);
        int kind1 = RoomScore_Kind1Sets(room, map);
        int kind2 = RoomScore_Kind2Sets(room, map);
        if (loose != 0) {
            n--;
            flags |= 1;
        }
        if (facing != 0) {
            n--;
            flags |= 2;
        }
        if ((ROOM_SCORE_ALL_CATEGORIES & 0xf) == 0xf) {
            n++;
            flags |= 4;
        }
        if (kind1 != 0 || kind2 != 0) {
            flags |= 8;
            n++;
        }
        if (kind1 == 0 || kind2 == 0) {
            flags |= 0x40;
        }
        if (kind0 != ROOM_SCORE_GROUPS) {
            n += 2;
            flags |= 0x10;
        } else if (most >= 5) {
            flags |= 0x20;
        }
    }
    if (count != NULL) {
        *count = n;
    }
    return flags;
}
CLEAN_AS(func_0205b91c, RoomScore_Advice)

/* func_0205ba60: the room's destructor; nothing to do. */
void RoomScore_DestructRoom(RoomScoreRoom *room)
{
    (void) room;
}
CLEAN_AS(func_0205ba60, RoomScore_DestructRoom)

/* func_0205ba64: the room without a wallpaper or a carpet (the rest is left). */
void RoomScore_InitRoom(RoomScoreRoom *room)
{
    room->wallpaper = ROOM_SCORE_NO_ITEM;
    room->carpet = ROOM_SCORE_NO_ITEM;
}
CLEAN_AS(func_0205ba64, RoomScore_InitRoom)

/* func_0205ba70: 7777 for each special item marked. */
int RoomScore_SpecialItemsScore(const u32 *marks)
{
    int sum = 0;
    for (u32 i = 0; i < ROOM_SCORE_MARK_WORDS; i++) {
        sum += MATH_CountPopulation(marks[i]);
    }
    return sum * ROOM_SCORE_SPECIAL_POINTS;
}
CLEAN_AS(func_0205ba70, RoomScore_SpecialItemsScore)

/* ---- The room sources */

/* A wallpaper or carpet number of a villager's house as an item code from `first`; the first
 * for a number past the last. */
static u16 design_code(u32 number, u16 first)
{
    return number < ROOM_SCORE_DESIGNS ? (u16) (number + first) : first;
}

/* func_0205baac: the villager's room's slot 2: the carpet of villager `villager`'s house, the
 * first carpet without the villager. */
void RoomScore_VillagerCarpet(u16 *out, RoomScoreSource *source, int villager)
{
    (void) source;
    u8 *found = VillagerRoster_At(&data_021e5a2c, villager);
    if (found != NULL) {
        *out = design_code(VillagerFurniture_Carpet(found), ROOM_SCORE_CARPET_FIRST);
    } else {
        *out = ROOM_SCORE_CARPET_FIRST;
    }
}
CLEAN_AS(func_0205baac, RoomScore_VillagerCarpet)

/* func_0205bae8: the villager's room's slot 1: its wallpaper, the first without the
 * villager. */
void RoomScore_VillagerWallpaper(u16 *out, RoomScoreSource *source, int villager)
{
    (void) source;
    u8 *found = VillagerRoster_At(&data_021e5a2c, villager);
    if (found != NULL) {
        *out = design_code(VillagerFurniture_Wallpaper(found), ROOM_SCORE_WALLPAPER_FIRST);
    } else {
        *out = ROOM_SCORE_WALLPAPER_FIRST;
    }
}
CLEAN_AS(func_0205bae8, RoomScore_VillagerWallpaper)

/* func_0205bb24: the villager's room's slot 0: the map made for the score, whatever the room
 * asked for. */
u32 RoomScore_VillagerMap(void)
{
    return data_021c95f0;
}
CLEAN_AS(func_0205bb24, RoomScore_VillagerMap)

/* func_0205bb30: the villager's room source's destructor. */
RoomScoreSource *RoomScore_DestructVillagerSource(RoomScoreSource *source)
{
    source->vtable = data_020dd3a4;
    RoomScore_DestructSource(source);
    return source;
}
CLEAN_AS(func_0205bb30, RoomScore_DestructVillagerSource)

/* func_0205bb48: the villager's room source's constructor. */
RoomScoreSource *RoomScore_ConstructVillagerSource(RoomScoreSource *source)
{
    RoomScore_ConstructSource(source);
    source->vtable = data_020dd3a4;
    return source;
}
CLEAN_AS(func_0205bb48, RoomScore_ConstructVillagerSource)

/* func_0205bb60: the house's slot 2: the carpet of room `room`'s record.
 * REQUIRES: the room has a record. */
void RoomScore_HouseCarpet(u16 *out, RoomScoreSource *source, int room)
{
    (void) source;
    *out = *func_020611e8((void *) (uintptr_t) func_02060ee0(data_021ebcd4, room), NULL);
}
CLEAN_AS(func_0205bb60, RoomScore_HouseCarpet)

/* func_0205bb80: the house's slot 1: the wallpaper of room `room`'s record.
 * REQUIRES: the room has a record. */
void RoomScore_HouseWallpaper(u16 *out, RoomScoreSource *source, int room)
{
    (void) source;
    *out = *func_02061204((void *) (uintptr_t) func_02060ee0(data_021ebcd4, room), NULL);
}
CLEAN_AS(func_0205bb80, RoomScore_HouseWallpaper)

/* func_0205bba0: the house's slot 0: the map of room `room` (AcreMap_Room).
 * QUIRK: declared without a result, as its matching source is; the ROM's code is a tail call,
 * which leaves the map in r0, where RoomScore_Total reads it. */
void RoomScore_HouseMap(RoomScoreSource *source, int room)
{
    (void) source;
    AcreMap_Room(room);
}
CLEAN_AS(func_0205bba0, RoomScore_HouseMap)

/* func_0205bbac: the house's room source's destructor. */
RoomScoreSource *RoomScore_DestructHouseSource(RoomScoreSource *source)
{
    source->vtable = data_020dd3b8;
    RoomScore_DestructSource(source);
    return source;
}
CLEAN_AS(func_0205bbac, RoomScore_DestructHouseSource)

/* func_0205bbc4: the house's room source's constructor. */
RoomScoreSource *RoomScore_ConstructHouseSource(RoomScoreSource *source)
{
    RoomScore_ConstructSource(source);
    source->vtable = data_020dd3b8;
    return source;
}
CLEAN_AS(func_0205bbc4, RoomScore_ConstructHouseSource)

/* func_0205bbdc: the base room source's destructor. */
void RoomScore_DestructSource(RoomScoreSource *source)
{
    source->vtable = data_020dd404;
}
CLEAN_AS(func_0205bbdc, RoomScore_DestructSource)

/* func_0205bbe8: the base room source's constructor. */
void RoomScore_ConstructSource(RoomScoreSource *source)
{
    source->vtable = data_020dd404;
}
CLEAN_AS(func_0205bbe8, RoomScore_ConstructSource)

/* ---- The edges */

/* func_0205bbf4: the edges of the room of `map` counted: its two columns of the least x for
 * value 1, its two rows of the greatest z for 4, its two columns of the greatest x for 2. */
void RoomScore_CountEdges(RoomScoreEdges *edges, AcreMap *map)
{
    int left;
    int right;
    int top;
    int bottom;
    RoomScore_Bounds(&left, &right, &top, &bottom, map);
    edges->low_x =
        (u8) RoomScore_CountInside((int) (uintptr_t) edges, map, (u32) left, (u32) (left + 1), (u32) top, (u32) bottom, 1);
    edges->high_z =
        (u8) RoomScore_CountInside((int) (uintptr_t) edges, map, (u32) left, (u32) right, (u32) (bottom - 1), (u32) bottom, 4);
    edges->high_x =
        (u8) RoomScore_CountInside((int) (uintptr_t) edges, map, (u32) (right - 1), (u32) right, (u32) top, (u32) bottom, 2);
}
CLEAN_AS(func_0205bbf4, RoomScore_CountEdges)

typedef struct InsideCount {
    int left;
    int right;
    int top;
    int bottom;
    int value;
    u32 count;
} InsideCount;

static void count_inside(void *context, u16 *item, u32 x, u32 z)
{
    InsideCount *c = context;
    if (!ItemCode_HasVariant(item)) {
        return;
    }
    int number = ItemCode_VariantItem(item);
    ItemFootprint footprint;
    ItemFootprint_Construct(&footprint, item);
    u32 cells = ItemFootprint_Count(&footprint);
    int inside = 1;
    for (u32 i = 0; i < cells; i++) {
        int cell_x = (int) x + ItemFootprint_Cell(&footprint, i)->x;
        int cell_z = (int) z + ItemFootprint_Cell(&footprint, i)->y;
        if (cell_x < c->left || cell_x > c->right || cell_z < c->top || cell_z > c->bottom) {
            inside = 0;
            break;
        }
    }
    if (inside) {
        if (c->value == FurnitureInfo_Unk01(number)) {
            c->count++;
        }
        if (c->value == FurnitureInfo_Unk02(number)) {
            c->count++;
        }
    }
    ItemFootprint_Destruct(&footprint);
}

/* func_0205bc60: the furniture wholly inside the square (all the cells of its footprint) with
 * Unk01 or Unk02 at `value`, once for each; at most 255. `unused` is not used. */
int RoomScore_CountInside(int unused, AcreMap *map, u32 left, u32 right, u32 top, u32 bottom, int value)
{
    (void) unused;
    InsideCount c = {(int) left, (int) right, (int) top, (int) bottom, value, 0};
    scan_square(map, left, top, right, bottom, count_inside, &c);
    return c.count < 0x100 ? (int) c.count : 0xff;
}
CLEAN_AS(func_0205bc60, RoomScore_CountInside)

/* func_0205bd80 */
int RoomScoreEdges_HighX(const RoomScoreEdges *edges)
{
    return edges->high_x;
}
CLEAN_AS(func_0205bd80, RoomScoreEdges_HighX)

/* func_0205bd84 */
int RoomScoreEdges_HighZ(const RoomScoreEdges *edges)
{
    return edges->high_z;
}
CLEAN_AS(func_0205bd84, RoomScoreEdges_HighZ)

/* func_0205bd88 */
int RoomScoreEdges_LowX(const RoomScoreEdges *edges)
{
    return edges->low_x;
}
CLEAN_AS(func_0205bd88, RoomScoreEdges_LowX)

/* func_0205bd8c: the destructor; nothing to do. */
void RoomScoreEdges_Destruct(RoomScoreEdges *edges)
{
    (void) edges;
}
CLEAN_AS(func_0205bd8c, RoomScoreEdges_Destruct)

/* func_0205bd90: the constructor: the counts cleared; the address back (as an int). */
int RoomScoreEdges_Construct(RoomScoreEdges *edges)
{
    RoomScoreEdges_Clear(edges);
    return (int) (uintptr_t) edges;
}
CLEAN_AS(func_0205bd90, RoomScoreEdges_Construct)

/* func_0205bda0 */
void RoomScoreEdges_Clear(RoomScoreEdges *edges)
{
    edges->high_x = 0;
    edges->high_z = 0;
    edges->low_x = 0;
}
CLEAN_AS(func_0205bda0, RoomScoreEdges_Clear)

/* func_0205bdb0: the edges of the house's five rooms counted, summed into data_021c95e4 (low
 * x), data_021c95e8 (high z) and data_021c95e0 (high x); a room without a map adds nothing.
 * QUIRK: the sums are bytes, and wrap. */
void RoomScore_CountHouseEdges(void)
{
    data_021c95e0 = 0;
    data_021c95e8 = 0;
    data_021c95e4 = 0;
    for (u32 i = 0; i < ROOM_SCORE_HOUSE_ROOMS; i++) {
        RoomScoreEdges edges;
        RoomScoreEdges_Construct(&edges);
        AcreMap *map = (AcreMap *) (uintptr_t) AcreMap_Room((int) i);
        if (map != NULL) {
            RoomScore_CountEdges(&edges, map);
            data_021c95e4 += (u8) RoomScoreEdges_LowX(&edges);
            data_021c95e8 += (u8) RoomScoreEdges_HighZ(&edges);
            data_021c95e0 += (u8) RoomScoreEdges_HighX(&edges);
        }
        RoomScoreEdges_Destruct(&edges);
    }
}
CLEAN_AS(func_0205bdb0, RoomScore_CountHouseEdges)

/* func_0205be20 */
u8 RoomScore_HouseHighX(void)
{
    return data_021c95e0;
}
CLEAN_AS(func_0205be20, RoomScore_HouseHighX)

/* func_0205be2c */
u8 RoomScore_HouseHighZ(void)
{
    return data_021c95e8;
}
CLEAN_AS(func_0205be2c, RoomScore_HouseHighZ)

/* func_0205be38 */
u8 RoomScore_HouseLowX(void)
{
    return data_021c95e4;
}
CLEAN_AS(func_0205be38, RoomScore_HouseLowX)

/* func_0205be44: the three sums together. */
int RoomScore_HouseEdges(void)
{
    int high_x = RoomScore_HouseHighX();
    int low_x = RoomScore_HouseLowX();
    return high_x + (low_x + RoomScore_HouseHighZ());
}
CLEAN_AS(func_0205be44, RoomScore_HouseEdges)
