/* The day the town was started, kept at 0x173dd of the state block (data_021f3b85): a date and
 * whether it is set. StateBlock_StartMode0 and StateBlock_StartMode6 set it to the day they
 * make the new town; it stays set until 6:00 the next morning (TownStartDay_Expire). Some of
 * the town's events look at it (func_02047898, func_02083fa4, func_02085c2c). */
#ifndef CLEAN_MAIN_TOWN_START_DAY_H
#define CLEAN_MAIN_TOWN_START_DAY_H

#include "calendar.h"
#include "types.h"

typedef struct TownStartDay {
    u8 day;
    u8 month;
    u8 year; /* from 2000 */
    u8 set;  /* 1 while the day counts */
} TownStartDay;

int TownStartDay_IsSet(TownStartDay *start);
void TownStartDay_Expire(TownStartDay *start);
int TownStartDay_Set(TownStartDay *start, const Date *date);
void TownStartDay_Init(TownStartDay *start);
void TownStartDay_Destruct(TownStartDay *start);
void TownStartDay_Construct(TownStartDay *start);

#endif
