/* Where one of the town's villagers lives: the tile of its house (0x7ce, x then z, 0xff for
 * none, villager_plots.h) and the town it last lived in (0x7b8, a 14-byte town head as in
 * npc_id.h). */
#ifndef CLEAN_MAIN_VILLAGER_HOME_H
#define CLEAN_MAIN_VILLAGER_HOME_H

#include "npc_id.h"
#include "types.h"
#include "villager_plots.h"

void VillagerHome_FreePlot(u8 *villager);
void VillagerHome_SetTile(u8 *villager, const VillagerPlot *tile);
VillagerPlot *VillagerHome_Tile(u8 *villager);
int VillagerHome_HasTile(u8 *villager);
void VillagerHome_ClearTile(u8 *villager);
NpcIdHead *VillagerHome_LastTown(u8 *villager);

#endif
