/* The tile of a villager's house (VillagerPlot, villager_plots.h): an x and a z byte, 0xff for
 * none. A villager keeps one at 0x7ce (villager_home.h); the free plots are a list of them. */
#ifndef CLEAN_MAIN_VILLAGER_PLOT_TILE_H
#define CLEAN_MAIN_VILLAGER_PLOT_TILE_H

#include "types.h"
#include "villager_plots.h"

/* A tile as VillagerPlotTile_SetFrom reads it: two words. */
typedef struct VillagerPlotXZ {
    u32 x;
    u32 z;
} VillagerPlotXZ;

void VillagerPlotTile_SetFrom(VillagerPlot *plot, const VillagerPlotXZ *tile);
void VillagerPlotTile_Set(VillagerPlot *plot, int x, int z);
int VillagerPlotTile_IsSet(const VillagerPlot *plot);
void VillagerPlotTile_Clear(VillagerPlot *plot);
void VillagerPlotTile_Destruct(VillagerPlot *plot);
int VillagerPlotTile_Construct(VillagerPlot *plot);

#endif
