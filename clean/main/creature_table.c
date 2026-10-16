/* The tables of the creatures that may appear (creature_table.h). */
#include "creature_table.h"

#include "clean.h"
#include "main/calendar.h"
#include "main/session.h"

static_assert(sizeof(CreatureTableList) == 8, "CreatureTableList size");

/* Each period's lists, by period - 1. */
extern CreatureTablePeriod data_020dc8b4[CREATURE_TABLE_PERIODS];
/* The session (Session_IsLinked). */
extern NetSession *data_020ccf94;

/* Today's day (byte 0) and month (byte 1). */
extern void func_0209df94(u8 *day_month);
/* The time of day (Calendar_Now). */
extern void func_0209def4(Time *now);
/* A random number below `bound`. */
extern int func_020644cc(int bound);

/* func_0204fa68: the group of a kind: 1 for kinds 0-8 and 12-34, 2 for 9-11, 3 for 35-55, 0
 * for a number that is no kind. */
int CreatureTable_Group(int kind)
{
    if (kind < 0 || kind >= CREATURE_TABLE_KINDS) {
        return 0;
    }
    if (kind >= 35) {
        return 3;
    }
    if (kind >= 9 && kind <= 11) {
        return 2;
    }
    return 1;
}
CLEAN_AS(func_0204fa68, CreatureTable_Group)

/* func_0204fa8c: the period of a month: the month for January to July, 8 or 9 for August and
 * 10 or 11 for September (the second of each from the 16th, today's day deciding), 12 to 14
 * for October to December; 1 for a number that is no month. */
unsigned char CreatureTable_Period(unsigned char month)
{
    u8 day_month[2];

    if (month >= 1 && month <= 7) {
        return month;
    }
    if (month == 8) {
        func_0209df94(day_month);
        return CreatureTable_IsSecondHalf(day_month[0]) ? 9 : 8;
    }
    if (month == 9) {
        func_0209df94(day_month);
        return CreatureTable_IsSecondHalf(day_month[0]) ? 11 : 10;
    }
    if (month >= 10 && month <= 12) {
        return (unsigned char) (month + 2);
    }
    return 1;
}
CLEAN_AS(func_0204fa8c, CreatureTable_Period)

/* func_0204fafc: whether a day is in the second half of its month (the 16th on). */
int CreatureTable_IsSecondHalf(unsigned int day)
{
    return day > 15;
}
CLEAN_AS(func_0204fafc, CreatureTable_IsSecondHalf)

/* func_0204fb08: the time of day of an hour: 0 for 4-8 and 16-20, 1 for 9-15, 2 for 21-24 and
 * 0-3; 0 past 24. */
int CreatureTable_TimeSlot(unsigned int hour)
{
    if ((hour >= 4 && hour < 9) || (hour >= 16 && hour < 21)) {
        return 0;
    }
    if (hour >= 9 && hour < 16) {
        return 1;
    }
    if ((hour >= 21 && hour <= 24) || hour < 4) {
        return 2;
    }
    return 0;
}
CLEAN_AS(func_0204fb08, CreatureTable_TimeSlot)

/* func_0204fb3c: CreatureTable_Pick for `place` at today's period and the time of day. */
int CreatureTable_PickNow(int *kind, int *second, int place)
{
    u8 day_month[2];
    Time now;

    func_0209df94(day_month);
    u8 month = day_month[1];
    func_0209def4(&now);
    u8 hour = now.hour;
    int period = CreatureTable_Period(month);
    int time_slot = CreatureTable_TimeSlot(hour);
    return CreatureTable_Pick(kind, second, place, period, time_slot);
}
CLEAN_AS(func_0204fb3c, CreatureTable_PickNow)

/* func_0204fb80: picks an entry of list [time_slot][place] of `period` at random by weight:
 * the first entry where the running sum of the weights passes a random number below 100
 * (below 96 while the session is linked, when the list's last three entries are left out).
 * Its kind to *kind, its second number to *second, and 1; 0 when the sum never passes it. */
int CreatureTable_Pick(int *kind, int *second, int place, int period, int time_slot)
{
    int left_out;
    int limit;

    if (Session_IsLinked(data_020ccf94)) {
        left_out = 3;
        limit = func_020644cc(0x60);
    } else {
        left_out = 0;
        limit = func_020644cc(0x64);
    }

    const CreatureTableList *list = &data_020dc8b4[period - 1][time_slot][place];
    int count = list->count - left_out;
    int sum = 0;
    for (int i = 0; i < count; i++) {
        const u8 *entry = list->entries + i * 3;
        sum += entry[2];
        if (sum > limit) {
            *kind = entry[0];
            *second = entry[1];
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_0204fb80, CreatureTable_Pick)

/* func_0204fc3c: the address of the lists of a month's period (August and September by
 * `second_half`, 0 or 1), or 0 for a number that is no month or a half that is neither. */
void *CreatureTable_Lists(unsigned int month, unsigned int second_half)
{
    if (month >= 1 && month <= 7) {
        return &data_020dc8b4[month - 1];
    }
    if (month == 8 || month == 9) {
        if (second_half > 1) {
            return NULL;
        }
        unsigned int first = month == 8 ? 7 : 9;
        return &data_020dc8b4[first + second_half];
    }
    if (month >= 10 && month <= 12) {
        return &data_020dc8b4[month + 1];
    }
    return NULL;
}
CLEAN_AS(func_0204fc3c, CreatureTable_Lists)
