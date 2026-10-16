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
