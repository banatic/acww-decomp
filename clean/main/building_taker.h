/* The slot of the object that takes the buildings put down while it exists (data_021f4b2c):
 * overlay 3's, which claims it when it starts (func_ov003_022207e0) and gives it up when it
 * ends (func_ov003_0222079c); AcreTile_StampBuildingNoting hands it each building. */
#ifndef CLEAN_MAIN_BUILDING_TAKER_H
#define CLEAN_MAIN_BUILDING_TAKER_H

int BuildingTaker_Get(void);
int BuildingTaker_Release(void *taker);
int BuildingTaker_Claim(void *taker);

#endif
