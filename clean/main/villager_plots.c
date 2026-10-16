/* Free house plots handed to the villagers that have none (villager_plots.h). */
#include "villager_plots.h"

#include <stdint.h>

#include "acre_map.h"
#include "clean.h"
#include "villager_town.h"

static_assert(sizeof(VillagerPlot) == 2, "plot");

/* A tile as func_02081f60 reads it. */
typedef struct VillagerPlotTile {
    int x;
    int z;
} VillagerPlotTile;

extern VillagerPlot data_021d13a8[VILLAGER_PLOT_LIST]; /* the free plots found */
extern u32 data_021d1244;                              /* bit 0: the list is constructed */
extern u8 data_021d1298[];                             /* the list's node in the global destructor chain */

extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));
extern void __register_global_object(int object, void *destruct, void *node);
/* A plot's constructor (none, giving the plot back) and destructor (nothing), and the list's
 * destructor: handed to the C++ runtime as the game hands them. */
extern int func_02081fa0(VillagerPlot *plot);
extern void func_02081f9c(VillagerPlot *plot);
extern void func_0207bd28(void);
extern void func_02081f94(VillagerPlot *plot);                               /* none */
extern int func_02081f80(const VillagerPlot *plot);                          /* whether it is set */
extern void func_02081f60(VillagerPlot *plot, const VillagerPlotTile *tile); /* set from the tile */
extern u16 *func_0204f5e0(AcreMap *map, int acre_x, int acre_z, int x, int z, int layer);
extern u16 func_0204bbbc(u32 villager);                            /* the house of villager index `villager` */
extern NpcId *func_0208150c(const void *villager);                 /* the villager's NpcId, at 0x7a0 */
extern int func_020800dc(const u8 *villager);                      /* whether its house tile (0x7ce) is set */
extern void func_020800b8(u8 *villager, const VillagerPlot *plot); /* sets it */
extern unsigned int func_020644cc(int bound);                      /* a random number below `bound` */

/* func_0207bbb8: every villager without a house tile gets a random free plot of the town's
 * map, in villager order, while plots are left: the villager's house is put there
 * (AcreMap_ClearBuildingAt with its code) and, when that succeeds, the plot becomes the
 * villager's house tile. The plot is used up either way. Nothing without the town's map.
 * REQUIRES: the map has at most 30 free plots, as the town's layouts do. */
void VillagerPlot_GiveHouses(VillagerTown *town)
{
    AcreMap *map = (AcreMap *) (uintptr_t) AcreMap_Town();
    if ((data_021d1244 & 1) == 0) {
        __cxa_vec_ctor(data_021d13a8, VILLAGER_PLOT_LIST, sizeof(VillagerPlot), (void (*)(void *))(uintptr_t) func_02081fa0,
                       (void (*)(void *))(uintptr_t) func_02081f9c);
        __register_global_object(0, (void *) (uintptr_t) func_0207bd28, data_021d1298);
        data_021d1244 |= 1;
    }
    if (map == NULL) {
        return;
    }
    int count = 0;
    int wide = map->tiles_wide;
    int high = map->tiles_high;
    VillagerPlotTile tile = {0, 0};
    for (int i = 0; i < VILLAGER_PLOT_LIST; i++) {
        func_02081f94(&data_021d13a8[i]);
    }
    for (tile.z = 0; tile.z < high; tile.z++) {
        for (tile.x = 0; tile.x < wide; tile.x++) {
            const u16 *item = func_0204f5e0(map, tile.x >> 4, tile.z >> 4, tile.x & 15, tile.z & 15, 0);
            if (item != NULL && *item == VILLAGER_PLOT_FREE) {
                func_02081f60(&data_021d13a8[count], &tile);
                count++;
            }
        }
    }
    if (count <= 0) {
        return;
    }
    for (int j = 0; j < VILLAGER_TOWN_VILLAGERS; j++) {
        u8 *villager = town->villagers[j];
        if (!NpcId_IsValid(func_0208150c(villager)) || func_020800dc(villager) != 0) {
            continue;
        }
        int nth = (int) func_020644cc(count);
        VillagerPlot *plot = &data_021d13a8[VillagerPlot_Nth(data_021d13a8, VILLAGER_PLOT_LIST, nth)];
        u16 house = func_0204bbbc((u32) j);
        if (AcreMap_ClearBuildingAt((int) (uintptr_t) map, (int) (uintptr_t) &house, plot->x, plot->z) != 0) {
            func_020800b8(villager, plot);
        }
        func_02081f94(plot);
        count--;
        if (count <= 0) {
            return;
        }
    }
}
CLEAN_AS(func_0207bbb8, VillagerPlot_GiveHouses)

/* func_0207bd28: the list destroyed. */
void VillagerPlot_DestroyList(void)
{
    __cxa_vec_cleanup(data_021d13a8, VILLAGER_PLOT_LIST, sizeof(VillagerPlot), (void (*)(void *))(uintptr_t) func_02081f9c);
}
CLEAN_AS(func_0207bd28, VillagerPlot_DestroyList)

/* func_0207bd48: the place of the `nth` (from 0) set plot of the first `count`, or -1. */
int VillagerPlot_Nth(VillagerPlot *plots, int count, int nth)
{
    for (int i = 0; i < count; i++) {
        if (func_02081f80(&plots[i])) {
            if (nth == 0) {
                return i;
            }
            nth--;
        }
    }
    return -1;
}
CLEAN_AS(func_0207bd48, VillagerPlot_Nth)
