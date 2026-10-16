/* What the town's eight villagers (data_021e5a2c, 0x7ec bytes each) do when the game moves to a
 * new date (func_0204714c). */
#ifndef CLEAN_MAIN_VILLAGER_DAY_H
#define CLEAN_MAIN_VILLAGER_DAY_H

#include "calendar.h"
#include "types.h"

#define VILLAGER_DAY_VILLAGERS 8
#define VILLAGER_DAY_VILLAGER_SIZE 0x7ec
#define VILLAGER_DAY_MEMORIES 8 /* the entries of func_020807c0 */
#define VILLAGER_DAY_MEMORY_SIZE 0x80

void VillagerDay_Begin(u8 *villagers, const DateTime *today);

#endif
