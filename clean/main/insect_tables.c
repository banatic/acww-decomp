/* What the game knows of each insect kind (insect_tables.h). */
#include "insect_tables.h"

#include "clean.h"

/* The six lists of each month, January first. */
extern const InsectDrawList *const data_020dded8[INSECT_TABLES_MONTHS];

/* The places of the kinds 0-59 (the original's switch); any other kind lives in place 4. */
#define INSECT_TABLES_PLACE_KINDS 60
#define INSECT_TABLES_PLACE_OTHER 4

static const u8 insect_tables_places[INSECT_TABLES_PLACE_KINDS] = {
    1,  1,  1,  1,  1,  1,  1,  1,  11, 14, 2, 12, 4,  4,  2,  2,  14, 14, 14, 14, /* 0-19 */
    14, 0,  0,  0,  4,  6,  2,  4,  4,  4,  9, 14, 2,  14, 14, 16, 13, 5,  14, 14, /* 20-39 */
    14, 14, 14, 14, 14, 13, 13, 13, 17, 10, 0, 8,  14, 12, 9,  9,  4,  4,  4,  7,  /* 40-59 */
};

/* The sizes of the kinds 0-55; any other kind's is 0. */
#define INSECT_TABLES_SIZED_KINDS 56

static const u16 insect_tables_sizes[INSECT_TABLES_SIZED_KINDS] = {
    50, 50, 90, 105, 85, 115, 42, 260, 60, 280, 13, 38, 73, 58, 82, 35, 58, 60,  44,  45,  70, 38, 76, 90, 5,  14, 45, 28,
    18, 43, 35, 85,  8,  23,  25, 35,  90, 15,  35, 30, 65, 60, 68, 59, 80, 120, 115, 160, 2,  10, 6,  9,  28, 25, 65, 160,
};

/* func_02061550: the place in the town insect kind `kind` lives. */
int InsectTables_Place(int kind)
{
    if (kind < 0 || kind >= INSECT_TABLES_PLACE_KINDS) {
        return INSECT_TABLES_PLACE_OTHER;
    }
    return insect_tables_places[kind];
}
CLEAN_AS(func_02061550, InsectTables_Place)

/* func_02061624: the size of insect kind `kind`. */
int InsectTables_Size(unsigned int kind)
{
    if (kind >= INSECT_TABLES_SIZED_KINDS) {
        return 0;
    }
    return insect_tables_sizes[kind];
}
CLEAN_AS(func_02061624, InsectTables_Size)

/* func_02061798: the time slot of an hour: 1 for 4-7, 2 for 8-15, 3 for 16, 4 for 17-18, 5 for
 * 19-22, and 0 for the rest of the day (0-3 and 23).
 * QUIRK: the test for 17-18 looks at the hour's low byte only, so 0x111, 0x112 and so on are
 * slot 4 too; the hours given are below 24. */
int InsectTables_TimeSlot(unsigned int hour)
{
    if (hour >= 4 && hour <= 7) {
        return 1;
    }
    if (hour >= 8 && hour <= 15) {
        return 2;
    }
    if (hour == 16) {
        return 3;
    }
    if ((u8) (hour - 17) <= 1) {
        return 4;
    }
    if (hour >= 19 && hour <= 22) {
        return 5;
    }
    return 0;
}
CLEAN_AS(func_02061798, InsectTables_TimeSlot)

/* func_020617d8: the six lists of month `month_index` (0-11; any other reads as 0, January). */
const InsectDrawList *InsectTables_MonthLists(int month_index)
{
    if (month_index < 0 || month_index >= INSECT_TABLES_MONTHS) {
        month_index = 0;
    }
    return data_020dded8[month_index];
}
CLEAN_AS(func_020617d8, InsectTables_MonthLists)
