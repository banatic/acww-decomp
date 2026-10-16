/* A villager's errand of catching an insect or a fish (types 0 and 1 of its object,
 * villager_object.h): while the errand runs, the villager catches now and then, and what it
 * caught becomes the object's item (an insect 0x12b0-0x12e7, a fish 0x12e8-0x131f). Overlays 4
 * and 68 update the villager of a scene object through VillagerErrandCatch_Update.
 *
 * At each step of the errand (1 to 4) there is a chance in 100 from the caller's table: at
 * steps 1, 3 and 4 the villager catches the creature the errand names, when it can be had at
 * this hour of the date (func_0202cef4 for insects, CreatureDraw_FishAvailable for fish); at
 * step 2 it catches a creature drawn from two weight bands next to each other, the first drawn
 * by the caller's weights (func_0202d190, CreatureDraw_FishOfBands). The catch's time is kept
 * in the object's date. With `check_time`, a catch also waits for the minutes of
 * data_020c8958 by step since the last one. */
#ifndef CLEAN_MAIN_VILLAGER_ERRAND_CATCH_H
#define CLEAN_MAIN_VILLAGER_ERRAND_CATCH_H

#include "calendar.h"
#include "types.h"
#include "villager_object.h"

#define VILLAGER_ERRAND_CATCH_STEPS 5

void VillagerErrandCatch_Update(void *scene, int chances, int weights, int check_time);
void VillagerErrandCatch_Fish(void *scene, VillagerObject *object, u8 *chances, void *weights, u8 check_time, DateTime *now);
void VillagerErrandCatch_Insect(void *scene, VillagerObject *object, u8 *chances, void *weights, u8 check_time, DateTime *now);
int VillagerErrandCatch_CanCatch(void *scene, VillagerObject *object, DateTime *now, u8 check_time);

#endif
