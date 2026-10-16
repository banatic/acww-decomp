/* A player's shop points: a 16-bit count kept in the player's record (at 0x2404 of the record
 * func_020984e8 returns, given by func_020996a0) that the ATM of overlay 4 shows (ov004/atm.c).
 *
 * Money spent at Nook's store adds one point per 100 (ShopPoints_AddSpent), five per 100 on
 * the days func_020afb24 picks. The count is capped at 50000 and falls in one of five levels
 * by the thresholds 0, 300, 5000, 10000 and 20000 (data_020d1e3c). Reaching a new level holds a
 * letter from "sp_npc_atm" at the post office for each level from 1 up to it that has not had
 * its letter yet, carrying that level's item (data_020d1e34); flag 0x1c + level - 1 of the
 * player's record says the letter went out. */
#ifndef CLEAN_MAIN_SHOP_POINTS_H
#define CLEAN_MAIN_SHOP_POINTS_H

#include "types.h"

#define SHOP_POINTS_LEVELS 5
#define SHOP_POINTS_TOP_LEVEL 4
#define SHOP_POINTS_MAX 50000

u16 ShopPoints_ToNextLevel(u16 *count);
u16 ShopPoints_Threshold(unsigned level);
int ShopPoints_Level(unsigned int count);
void ShopPoints_AddSpent(u16 *count, int spent);
void ShopPoints_Add(u16 *count, int points);
void ShopPoints_SendLevelLetters(void);
void ShopPoints_Clear(u16 *count);
void ShopPoints_DoNothing(void);
u32 ShopPoints_Construct(u32 count);
u16 *ShopPoints_Count(void *points);
void ShopPoints_ResetA(void *count);
void ShopPoints_ResetB(void *count);
u32 ShopPoints_Destruct(u32 count);
int ShopPoints_ConstructAndReset(int count);

#endif
