/* The slot of the object that takes the buildings put down (building_taker.h). */
#include "building_taker.h"

#include "clean.h"

extern void *data_021f4b2c; /* the object, or NULL */

/* func_020b3b14: the object, as an address (0 when there is none). */
int BuildingTaker_Get(void)
{
    return (int) (uintptr_t) data_021f4b2c;
}
CLEAN_AS(func_020b3b14, BuildingTaker_Get)

/* func_020b3b20: the slot emptied; whether there was an object in it.
 * QUIRK: `taker` is not compared with the object in the slot; whoever asks empties it. */
int BuildingTaker_Release(void *taker)
{
    (void) taker;
    if (data_021f4b2c == NULL) {
        return 0;
    }
    data_021f4b2c = NULL;
    return 1;
}
CLEAN_AS(func_020b3b20, BuildingTaker_Release)

/* func_020b3b38: `taker` put in the slot when it is empty; whether it was. */
int BuildingTaker_Claim(void *taker)
{
    if (data_021f4b2c != NULL) {
        return 0;
    }
    data_021f4b2c = taker;
    return 1;
}
CLEAN_AS(func_020b3b38, BuildingTaker_Claim)
