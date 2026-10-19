/* Groups of kind 1 item codes numbered from a first code (item_group.h). */
#include "item_group.h"

#include "clean.h"

#define ITEM_GROUP_WALLPAPER 0x1100
#define ITEM_GROUP_WALLPAPERS 0x44
#define ITEM_GROUP_CARPET 0x1144
#define ITEM_GROUP_CARPETS 0x44
#define ITEM_GROUP_CLOTH 0x11a8
#define ITEM_GROUP_CLOTHS 0x100
#define ITEM_GROUP_1380 0x1380
#define ITEM_GROUP_1380S 0x20
#define ITEM_GROUP_HEAD_A 0x13a8
#define ITEM_GROUP_HEAD_AS 0x20
#define ITEM_GROUP_HEAD_B 0x13c8
#define ITEM_GROUP_HEAD_BS 0x40
#define ITEM_GROUP_PART_C 0x1431
#define ITEM_GROUP_PART_CS 0x40

/* The code of item `index` of a group, its first for an index past it. */
static u16 code_of(u32 index, u16 first, u32 count)
{
    return (u16) (index < count ? first + index : first);
}

static int in_group(const u16 *code, u16 first, u32 count)
{
    return *code >= first && *code <= first + count - 1;
}

/* func_0204b188 */
u16 ItemGroup_HeadA(u32 index)
{
    return code_of(index, ITEM_GROUP_HEAD_A, ITEM_GROUP_HEAD_AS);
}
CLEAN_AS(func_0204b188, ItemGroup_HeadA)

/* func_0204b1a0 */
u16 ItemGroup_Wallpaper(u16 index)
{
    return code_of(index, ITEM_GROUP_WALLPAPER, ITEM_GROUP_WALLPAPERS);
}
CLEAN_AS(func_0204b1a0, ItemGroup_Wallpaper)

/* func_0204b1b8 */
u16 ItemGroup_Item1380(u32 index)
{
    return code_of(index, ITEM_GROUP_1380, ITEM_GROUP_1380S);
}
CLEAN_AS(func_0204b1b8, ItemGroup_Item1380)

/* func_0204b350 */
u16 ItemGroup_PartC(u32 index)
{
    return code_of(index, ITEM_GROUP_PART_C, ITEM_GROUP_PART_CS);
}
CLEAN_AS(func_0204b350, ItemGroup_PartC)

/* func_0204b368 */
u16 ItemGroup_Cloth(u16 index)
{
    return code_of(index, ITEM_GROUP_CLOTH, ITEM_GROUP_CLOTHS);
}
CLEAN_AS(func_0204b368, ItemGroup_Cloth)

/* func_0204b1d8 */
int ItemGroup_IsHeadA(const u16 *code)
{
    return in_group(code, ITEM_GROUP_HEAD_A, ITEM_GROUP_HEAD_AS);
}
CLEAN_AS(func_0204b1d8, ItemGroup_IsHeadA)

/* func_0204b1d0 */
void ItemGroup_TestIsHeadA(const u16 *code)
{
    ItemGroup_IsHeadA(code);
}
CLEAN_AS(func_0204b1d0, ItemGroup_TestIsHeadA)

/* func_0204b208 */
int ItemGroup_IsWallpaper(const u16 *code)
{
    return in_group(code, ITEM_GROUP_WALLPAPER, ITEM_GROUP_WALLPAPERS);
}
CLEAN_AS(func_0204b208, ItemGroup_IsWallpaper)

/* func_0204b200 */
void ItemGroup_TestIsWallpaper(const u16 *code)
{
    ItemGroup_IsWallpaper(code);
}
CLEAN_AS(func_0204b200, ItemGroup_TestIsWallpaper)

/* func_0204b238 */
int ItemGroup_Is1380(const u16 *code)
{
    return in_group(code, ITEM_GROUP_1380, ITEM_GROUP_1380S);
}
CLEAN_AS(func_0204b238, ItemGroup_Is1380)

/* func_0204b230 */
void ItemGroup_TestIs1380(const u16 *code)
{
    ItemGroup_Is1380(code);
}
CLEAN_AS(func_0204b230, ItemGroup_TestIs1380)

/* func_0204b298 */
u16 ItemGroup_IsPartC(const u16 *code)
{
    return (u16) in_group(code, ITEM_GROUP_PART_C, ITEM_GROUP_PART_CS);
}
CLEAN_AS(func_0204b298, ItemGroup_IsPartC)

/* func_0204b290 */
void ItemGroup_TestIsPartC(const u16 *code)
{
    ItemGroup_IsPartC(code);
}
CLEAN_AS(func_0204b290, ItemGroup_TestIsPartC)

/* func_0204b2c8 */
int ItemGroup_IsCloth(const u16 *code)
{
    return in_group(code, ITEM_GROUP_CLOTH, ITEM_GROUP_CLOTHS);
}
CLEAN_AS(func_0204b2c8, ItemGroup_IsCloth)

/* func_0204b2c0 */
void ItemGroup_TestIsCloth(const u16 *code)
{
    ItemGroup_IsCloth(code);
}
CLEAN_AS(func_0204b2c0, ItemGroup_TestIsCloth)

/* func_0204b2f8 */
int ItemGroup_IsCarpet(const u16 *code)
{
    return in_group(code, ITEM_GROUP_CARPET, ITEM_GROUP_CARPETS);
}
CLEAN_AS(func_0204b2f8, ItemGroup_IsCarpet)

/* func_0204b2f0 */
void ItemGroup_TestIsCarpet(const u16 *code)
{
    ItemGroup_IsCarpet(code);
}
CLEAN_AS(func_0204b2f0, ItemGroup_TestIsCarpet)

/* func_0204b328 */
int ItemGroup_IsHeadB(const u16 *code)
{
    return in_group(code, ITEM_GROUP_HEAD_B, ITEM_GROUP_HEAD_BS);
}
CLEAN_AS(func_0204b328, ItemGroup_IsHeadB)

/* func_0204b320 */
void ItemGroup_TestIsHeadB(const u16 *code)
{
    ItemGroup_IsHeadB(code);
}
CLEAN_AS(func_0204b320, ItemGroup_TestIsHeadB)

#define ITEM_GROUP_DESIGN 0x1188
#define ITEM_GROUP_DESIGNS 0x20
#define ITEM_GROUP_DESIGNS_PER_PLAYER 8
#define ITEM_GROUP_DESIGN_PLAYERS 4
#define ITEM_GROUP_INSECT 0x12b0
#define ITEM_GROUP_INSECTS 0x38
#define ITEM_GROUP_FISH 0x12e8
#define ITEM_GROUP_FISHES 0x38
#define ITEM_GROUP_HEAD_C 0x1408
#define ITEM_GROUP_HEAD_CS 0x21
#define ITEM_GROUP_PART_C2 0x1471
#define ITEM_GROUP_PART_C2S 0x21
#define ITEM_GROUP_BELL_BAG 0x1492
#define ITEM_GROUP_BELL_BAGS 0x6c
#define ITEM_GROUP_ROOM_3894 0x3894
#define ITEM_GROUP_ROOM_3894_LAST 0x38e3
#define ITEM_GROUP_ROOM_450C 0x450c
#define ITEM_GROUP_ROOM_450C_LAST 0x45db
#define ITEM_GROUP_ROOM_45DC 0x45dc
#define ITEM_GROUP_ROOM_45DC_LAST 0x47d7

/* The index of a code in its group, -1 for a code outside it. */
static int index_in(const u16 *code, u16 first, u32 count)
{
    return in_group(code, first, count) ? *code - first : -1;
}

static int in_codes(const u16 *code, u16 first, u16 last)
{
    return *code >= first && *code <= last;
}

/* func_0204b384 */
u16 ItemGroup_Carpet(u16 index)
{
    return code_of(index, ITEM_GROUP_CARPET, ITEM_GROUP_CARPETS);
}
CLEAN_AS(func_0204b384, ItemGroup_Carpet)

/* func_0204b39c */
u16 ItemGroup_HeadB(u32 index)
{
    return code_of(index, ITEM_GROUP_HEAD_B, ITEM_GROUP_HEAD_BS);
}
CLEAN_AS(func_0204b39c, ItemGroup_HeadB)

/* func_0204b3b4 */
u16 ItemGroup_Insect(u32 index)
{
    return code_of(index, ITEM_GROUP_INSECT, ITEM_GROUP_INSECTS);
}
CLEAN_AS(func_0204b3b4, ItemGroup_Insect)

/* func_0204bdd0 */
u16 ItemGroup_HeadC(u32 index)
{
    return code_of(index, ITEM_GROUP_HEAD_C, ITEM_GROUP_HEAD_CS);
}
CLEAN_AS(func_0204bdd0, ItemGroup_HeadC)

/* func_0204bf20 */
u16 ItemGroup_PartC2(u32 index)
{
    return code_of(index, ITEM_GROUP_PART_C2, ITEM_GROUP_PART_C2S);
}
CLEAN_AS(func_0204bf20, ItemGroup_PartC2)

/* func_0204c078 */
u16 ItemGroup_Design(u32 index)
{
    return code_of(index, ITEM_GROUP_DESIGN, ITEM_GROUP_DESIGNS);
}
CLEAN_AS(func_0204c078, ItemGroup_Design)

/* func_0204c210 */
u16 ItemGroup_BellBag(u32 index)
{
    return code_of(index, ITEM_GROUP_BELL_BAG, ITEM_GROUP_BELL_BAGS);
}
CLEAN_AS(func_0204c210, ItemGroup_BellBag)

/* func_0204be88 */
int ItemGroup_IsHeadC(const u16 *code)
{
    return in_group(code, ITEM_GROUP_HEAD_C, ITEM_GROUP_HEAD_CS);
}
CLEAN_AS(func_0204be88, ItemGroup_IsHeadC)

/* func_0204be60 */
int ItemGroup_HeadCIndex(const u16 *code)
{
    return index_in(code, ITEM_GROUP_HEAD_C, ITEM_GROUP_HEAD_CS);
}
CLEAN_AS(func_0204be60, ItemGroup_HeadCIndex)

/* func_0204be10 */
int ItemGroup_IsPartC2(const u16 *code)
{
    return in_group(code, ITEM_GROUP_PART_C2, ITEM_GROUP_PART_C2S);
}
CLEAN_AS(func_0204be10, ItemGroup_IsPartC2)

/* func_0204bde8 */
int ItemGroup_PartC2Index(const u16 *code)
{
    return index_in(code, ITEM_GROUP_PART_C2, ITEM_GROUP_PART_C2S);
}
CLEAN_AS(func_0204bde8, ItemGroup_PartC2Index)

/* func_0204c0d8 */
int ItemGroup_IsDesign(const u16 *code)
{
    return in_group(code, ITEM_GROUP_DESIGN, ITEM_GROUP_DESIGNS);
}
CLEAN_AS(func_0204c0d8, ItemGroup_IsDesign)

/* func_0204c0b0: the design's index, eight per player in player order. */
int ItemGroup_DesignIndex(const u16 *code)
{
    return index_in(code, ITEM_GROUP_DESIGN, ITEM_GROUP_DESIGNS);
}
CLEAN_AS(func_0204c0b0, ItemGroup_DesignIndex)

/* func_0204c090: which of its player's eight designs (0-7), -1 for no design. */
int ItemGroup_DesignSlot(const u16 *code)
{
    int index = ItemGroup_DesignIndex(code);
    return index != -1 ? index % ITEM_GROUP_DESIGNS_PER_PLAYER : -1;
}
CLEAN_AS(func_0204c090, ItemGroup_DesignSlot)

/* func_0204c100: whose design (player 0-3), -1 for no design. */
int ItemGroup_DesignPlayer(const u16 *code)
{
    int index = ItemGroup_DesignIndex(code);
    return index != -1 ? index / ITEM_GROUP_DESIGNS_PER_PLAYER % ITEM_GROUP_DESIGN_PLAYERS : -1;
}
CLEAN_AS(func_0204c100, ItemGroup_DesignPlayer)

/* func_0204c064: the code of a player's design.
 * QUIRK: only the low two bits of `player` and the low three of `slot` count. */
int ItemGroup_DesignOf(int player, int slot)
{
    u32 index = ((u32) player & (ITEM_GROUP_DESIGN_PLAYERS - 1)) * ITEM_GROUP_DESIGNS_PER_PLAYER +
                ((u32) slot & (ITEM_GROUP_DESIGNS_PER_PLAYER - 1));
    return ItemGroup_Design(index);
}
CLEAN_AS(func_0204c064, ItemGroup_DesignOf)

/* func_0204c048: `code` made the player's design. */
void ItemGroup_ConstructDesign(u16 *code, int player, int slot)
{
    *code = (u16) ItemGroup_DesignOf(player, slot);
}
CLEAN_AS(func_0204c048, ItemGroup_ConstructDesign)

/* func_0204c358 */
int ItemGroup_IsInsect(const u16 *code)
{
    return in_group(code, ITEM_GROUP_INSECT, ITEM_GROUP_INSECTS);
}
CLEAN_AS(func_0204c358, ItemGroup_IsInsect)

/* func_0204c330: the insect's kind. */
int ItemGroup_InsectIndex(const u16 *code)
{
    return index_in(code, ITEM_GROUP_INSECT, ITEM_GROUP_INSECTS);
}
CLEAN_AS(func_0204c330, ItemGroup_InsectIndex)

/* func_0204c3c8 */
int ItemGroup_IsFish(const u16 *code)
{
    return in_group(code, ITEM_GROUP_FISH, ITEM_GROUP_FISHES);
}
CLEAN_AS(func_0204c3c8, ItemGroup_IsFish)

/* func_0204c3a0: the fish's kind. */
int ItemGroup_FishIndex(const u16 *code)
{
    return index_in(code, ITEM_GROUP_FISH, ITEM_GROUP_FISHES);
}
CLEAN_AS(func_0204c3a0, ItemGroup_FishIndex)

/* func_0204c5c4 */
int ItemGroup_IsRoom3894(const u16 *code)
{
    return in_codes(code, ITEM_GROUP_ROOM_3894, ITEM_GROUP_ROOM_3894_LAST);
}
CLEAN_AS(func_0204c5c4, ItemGroup_IsRoom3894)

/* func_0204c5ec */
int ItemGroup_IsRoom45dc(const u16 *code)
{
    return in_codes(code, ITEM_GROUP_ROOM_45DC, ITEM_GROUP_ROOM_45DC_LAST);
}
CLEAN_AS(func_0204c5ec, ItemGroup_IsRoom45dc)

/* func_0204c614 */
int ItemGroup_IsRoom450c(const u16 *code)
{
    return in_codes(code, ITEM_GROUP_ROOM_450C, ITEM_GROUP_ROOM_450C_LAST);
}
CLEAN_AS(func_0204c614, ItemGroup_IsRoom450c)
