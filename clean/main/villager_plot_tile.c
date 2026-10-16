/* The tile of a villager's house (villager_plot_tile.h). */
#include "villager_plot_tile.h"

#include "clean.h"

/* func_02081f60: the tile set from the low bytes of two words. */
void VillagerPlotTile_SetFrom(VillagerPlot *plot, const VillagerPlotXZ *tile)
{
    VillagerPlotTile_Set(plot, (u8) tile->x, (u8) tile->z);
}
CLEAN_AS(func_02081f60, VillagerPlotTile_SetFrom)

/* func_02081f78 */
void VillagerPlotTile_Set(VillagerPlot *plot, int x, int z)
{
    plot->x = (u8) x;
    plot->z = (u8) z;
}
CLEAN_AS(func_02081f78, VillagerPlotTile_Set)

/* func_02081f80: whether neither byte is none. */
int VillagerPlotTile_IsSet(const VillagerPlot *plot)
{
    return plot->x != VILLAGER_PLOT_NONE && plot->z != VILLAGER_PLOT_NONE;
}
CLEAN_AS(func_02081f80, VillagerPlotTile_IsSet)

/* func_02081f94 */
void VillagerPlotTile_Clear(VillagerPlot *plot)
{
    plot->x = VILLAGER_PLOT_NONE;
    plot->z = VILLAGER_PLOT_NONE;
}
CLEAN_AS(func_02081f94, VillagerPlotTile_Clear)

/* func_02081f9c: the destructor, which has nothing to do. */
void VillagerPlotTile_Destruct(VillagerPlot *plot)
{
    (void) plot;
}
CLEAN_AS(func_02081f9c, VillagerPlotTile_Destruct)

/* func_02081fa0: the constructor; a tile starts as none. Gives the tile back (the source's
 * result is a word). */
int VillagerPlotTile_Construct(VillagerPlot *plot)
{
    VillagerPlotTile_Clear(plot);
    return (int) (uintptr_t) plot;
}
CLEAN_AS(func_02081fa0, VillagerPlotTile_Construct)
