/* Free house plots handed to the villagers that have none.
 *
 * A tile of the town's map holding item 0x500a is a free plot (TownLayout_HasNine500a); the
 * houses of the villagers are items 0x5001-0x5008, one for each villager index (func_0204bbbc).
 * Each villager keeps the tile of its house at 0x7ce (x, then z; 0xff for none, func_020800dc).
 *
 * The free plots are listed in a static array of 30 tiles (data_021d13a8), constructed the
 * first time it is used and destroyed with the program (VillagerPlot_DestroyList). */
#ifndef CLEAN_MAIN_VILLAGER_PLOTS_H
#define CLEAN_MAIN_VILLAGER_PLOTS_H

#include "types.h"

#define VILLAGER_PLOT_LIST 30
#define VILLAGER_PLOT_FREE 0x500a
#define VILLAGER_PLOT_NONE 0xff

/* A tile: its x and z, 0xff for none. */
typedef struct VillagerPlot {
    u8 x;
    u8 z;
} VillagerPlot;

typedef struct VillagerTown VillagerTown;

void VillagerPlot_GiveHouses(VillagerTown *town);
void VillagerPlot_DestroyList(void);
int VillagerPlot_Nth(VillagerPlot *plots, int count, int nth);

#endif
