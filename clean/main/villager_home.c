/* Where one of the town's villagers lives (villager_home.h). */
#include "villager_home.h"

#include "acre_map.h"
#include "clean.h"

#define VILLAGER_HOME_TILE 0x7ce
#define VILLAGER_HOME_LAST_TOWN 0x7b8

extern int func_02081f80(const VillagerPlot *plot); /* whether it is set */
extern void func_02081f94(VillagerPlot *plot);      /* none */

/* func_02080078: a free plot (item 0x500a) put on the tile of the villager's house, when the
 * town's map is there and the villager has a house tile. */
void VillagerHome_FreePlot(u8 *villager)
{
    unsigned int town = AcreMap_Town();
    if (town == 0) {
        return;
    }
    if (!VillagerHome_HasTile(villager)) {
        return;
    }
    const VillagerPlot *tile = VillagerHome_Tile(villager);
    u16 plot = VILLAGER_PLOT_FREE;
    AcreMap_SetBuildingAt((int) town, tile->x, tile->z, (int) (uintptr_t) &plot);
}
CLEAN_AS(func_02080078, VillagerHome_FreePlot)

/* func_020800b8: the tile of the villager's house set. */
void VillagerHome_SetTile(u8 *villager, const VillagerPlot *tile)
{
    villager[VILLAGER_HOME_TILE] = tile->x;
    villager[VILLAGER_HOME_TILE + 1] = tile->z;
}
CLEAN_AS(func_020800b8, VillagerHome_SetTile)

/* func_020800d0: the tile of the villager's house. */
VillagerPlot *VillagerHome_Tile(u8 *villager)
{
    return (VillagerPlot *) (void *) (villager + VILLAGER_HOME_TILE);
}
CLEAN_AS(func_020800d0, VillagerHome_Tile)

/* func_020800dc: whether the villager has a house tile. */
int VillagerHome_HasTile(u8 *villager)
{
    return func_02081f80(VillagerHome_Tile(villager));
}
CLEAN_AS(func_020800dc, VillagerHome_HasTile)

/* func_020800ec: the villager's house tile set to none. */
void VillagerHome_ClearTile(u8 *villager)
{
    func_02081f94(VillagerHome_Tile(villager));
}
CLEAN_AS(func_020800ec, VillagerHome_ClearTile)

/* func_020800fc: the town the villager last lived in. */
NpcIdHead *VillagerHome_LastTown(u8 *villager)
{
    return (NpcIdHead *) (void *) (villager + VILLAGER_HOME_LAST_TOWN);
}
CLEAN_AS(func_020800fc, VillagerHome_LastTown)
