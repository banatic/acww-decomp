/* The item codes of the town map's objects (map_code.h). */
#include "map_code.h"

#include "clean.h"

#define MAP_CODE_BUILDING 0x5000
#define MAP_CODE_BUILDINGS 0x22
#define MAP_CODE_VILLAGER_HOUSE 0x5001
#define MAP_CODE_VILLAGER_HOUSES 8
#define MAP_CODE_STORE 0x500d
#define MAP_CODE_STORES 4
#define MAP_CODE_PLAYER_HOUSE 0x5014
#define MAP_CODE_PLAYER_HOUSES 7
#define MAP_CODE_SNOWMAN 0xb001
#define MAP_CODE_SNOWMEN 3
/* A tile a building's shape covers (ACRE_TILE_ITEM_OCCUPIED). */
#define MAP_CODE_COVERED 0xf030
#define MAP_CODE_F031 0xf031
#define MAP_CODE_FFFD 0xfffd
#define MAP_CODE_FFFE 0xfffe
#define MAP_CODE_FFFF 0xffff

/* The code of number `index` of a group, its first for a number past it. */
static u16 code_of(u32 index, u16 first, u32 count)
{
    return (u16) (index < count ? first + index : first);
}

static int in_group(const u16 *code, u16 first, u32 count)
{
    return *code >= first && *code <= first + count - 1;
}

static int index_in(const u16 *code, u16 first, u32 count)
{
    return in_group(code, first, count) ? *code - first : -1;
}

/* func_0204bae8 */
u16 MapCode_PlayerHouse(u32 size)
{
    return code_of(size, MAP_CODE_PLAYER_HOUSE, MAP_CODE_PLAYER_HOUSES);
}
CLEAN_AS(func_0204bae8, MapCode_PlayerHouse)

/* func_0204bb00 */
int MapCode_IsPlayerHouse(const u16 *code)
{
    return in_group(code, MAP_CODE_PLAYER_HOUSE, MAP_CODE_PLAYER_HOUSES);
}
CLEAN_AS(func_0204bb00, MapCode_IsPlayerHouse)

/* func_0204bb14 */
u16 MapCode_Snowman(u32 index)
{
    return code_of(index, MAP_CODE_SNOWMAN, MAP_CODE_SNOWMEN);
}
CLEAN_AS(func_0204bb14, MapCode_Snowman)

/* func_0204bb54 */
int MapCode_IsSnowman(const u16 *code)
{
    return in_group(code, MAP_CODE_SNOWMAN, MAP_CODE_SNOWMEN);
}
CLEAN_AS(func_0204bb54, MapCode_IsSnowman)

/* func_0204bb2c */
int MapCode_SnowmanIndex(const u16 *code)
{
    return index_in(code, MAP_CODE_SNOWMAN, MAP_CODE_SNOWMEN);
}
CLEAN_AS(func_0204bb2c, MapCode_SnowmanIndex)

/* func_0204bb68 */
u16 MapCode_Store(u32 level)
{
    return code_of(level, MAP_CODE_STORE, MAP_CODE_STORES);
}
CLEAN_AS(func_0204bb68, MapCode_Store)

/* func_0204bba8 */
int MapCode_IsStore(const u16 *code)
{
    return in_group(code, MAP_CODE_STORE, MAP_CODE_STORES);
}
CLEAN_AS(func_0204bba8, MapCode_IsStore)

/* func_0204bb80 */
int MapCode_StoreLevel(const u16 *code)
{
    return index_in(code, MAP_CODE_STORE, MAP_CODE_STORES);
}
CLEAN_AS(func_0204bb80, MapCode_StoreLevel)

/* func_0204bbbc */
u16 MapCode_VillagerHouse(u32 villager)
{
    return code_of(villager, MAP_CODE_VILLAGER_HOUSE, MAP_CODE_VILLAGER_HOUSES);
}
CLEAN_AS(func_0204bbbc, MapCode_VillagerHouse)

/* func_0204bbd4 */
u16 MapCode_Building(u32 index)
{
    return code_of(index, MAP_CODE_BUILDING, MAP_CODE_BUILDINGS);
}
CLEAN_AS(func_0204bbd4, MapCode_Building)

/* func_0204bc14 */
int MapCode_IsBuilding(const u16 *code)
{
    return in_group(code, MAP_CODE_BUILDING, MAP_CODE_BUILDINGS);
}
CLEAN_AS(func_0204bc14, MapCode_IsBuilding)

/* func_0204bbec: a building or a tile one covers. */
int MapCode_IsBuildingOrCovered(const u16 *code)
{
    return *code == MAP_CODE_COVERED || MapCode_IsBuilding(code);
}
CLEAN_AS(func_0204bbec, MapCode_IsBuildingOrCovered)

/* func_0204c774 */
int MapCode_IsFfff(const u16 *code)
{
    return *code == MAP_CODE_FFFF;
}
CLEAN_AS(func_0204c774, MapCode_IsFfff)

/* func_0204c71c: one of the special codes. */
int MapCode_IsSpecial(const u16 *code)
{
    u16 value = *code;
    return value == MAP_CODE_COVERED || value == MAP_CODE_F031 || value == MAP_CODE_FFFD || value == MAP_CODE_FFFE ||
           MapCode_IsFfff(code);
}
CLEAN_AS(func_0204c71c, MapCode_IsSpecial)
