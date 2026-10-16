/* The tables of the creatures that may appear: 56 kinds (their items are 0x12e8-0x131f).
 * Overlay 3 picks one with CreatureTable_PickNow and places it at height -0x1333.
 *
 * The year is cut into 14 periods: the months, with August and September each cut in two at
 * the 16th. Each period has, for each of the three times of day (CreatureTable_TimeSlot), one
 * list per place (the caller's `place`, 0 or 1 here): entries of three bytes, the creature's
 * kind, a second number the caller keeps, and a weight. */
#ifndef CLEAN_MAIN_CREATURE_TABLE_H
#define CLEAN_MAIN_CREATURE_TABLE_H

#include "types.h"

#define CREATURE_TABLE_KINDS 56
#define CREATURE_TABLE_PERIODS 14

/* One list: `count` entries of three bytes. */
typedef struct CreatureTableList {
    const u8 *entries;
    u8 count;
} CreatureTableList;

/* A period's lists: lists[time_slot][place]. */
typedef CreatureTableList *const *CreatureTablePeriod;

int CreatureTable_Group(int kind);
unsigned char CreatureTable_Period(unsigned char month);
int CreatureTable_IsSecondHalf(unsigned int day);
int CreatureTable_TimeSlot(unsigned int hour);
int CreatureTable_PickNow(int *kind, int *second, int place);
int CreatureTable_Pick(int *kind, int *second, int place, int period, int time_slot);
void *CreatureTable_Lists(unsigned int month, unsigned int second_half);

/* Each kind's details (data_020cb784), for the 56 kinds and the three models after them
 * (0x38-0x3a, see fish_disp.h). */
typedef struct CreatureTableInfo {
    u8 offset_class; /* 0-6: picks the offset a held creature is moved by (func_02059cf8) */
    u8 unk_01;
    u8 unk_02;
    u8 unk_03;
    u16 base_value; /* scaled by a random 0.8 to 1.2 by func_02086564 */
} CreatureTableInfo;

int CreatureTable_OffsetClass(unsigned int kind);
unsigned short CreatureTable_BaseValue(unsigned int kind);

#endif
