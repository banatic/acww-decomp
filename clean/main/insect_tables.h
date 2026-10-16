/* What the game knows of each insect kind (the item 0x12b0 + kind, kinds 0-0x37) and the
 * tables insect draws go by (insect_draw.h):
 *
 * - the place in the town each kind lives (InsectTables_Place, 0-17);
 * - each kind's size, the base a contest's random size is drawn around (event_winner.c);
 * - the time slot (0-5) of an hour, which picks one of a month's six lists;
 * - the month's lists themselves (data_020dded8), also read for villagers' outings
 *   (villager_outdoors.c). */
#ifndef CLEAN_MAIN_INSECT_TABLES_H
#define CLEAN_MAIN_INSECT_TABLES_H

#include "insect_draw.h" /* InsectDrawList */
#include "types.h"

#define INSECT_TABLES_MONTHS 12

int InsectTables_Place(int kind);
int InsectTables_Size(unsigned int kind);
int InsectTables_TimeSlot(unsigned int hour);
const InsectDrawList *InsectTables_MonthLists(int month_index);

#endif
