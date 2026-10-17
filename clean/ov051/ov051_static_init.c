/* Overlay 51's static initialiser, run when the overlay is loaded: the table of member
 * functions the taxi driver's states (taxi_driver.h) dispatch through, copied from the
 * overlay's constants (the compiler cannot place member pointers in initialised data). */
#include "clean.h"
#include "taxi_driver.h"
#include "types.h"

/* Its states: each one's entry, then its update. */
extern const MemberPointer data_ov051_02261674, data_ov051_022615e4, data_ov051_02261694, data_ov051_0226176c,
    data_ov051_022615c4, data_ov051_022615f4, data_ov051_02261774, data_ov051_02261794, data_ov051_0226178c,
    data_ov051_02261784;
extern TaxiDriverStep data_ov051_02261ba8[TAXI_DRIVER_STATES];

/* __sinit_ov051_0226150c: the entries and updates of the five states, in order. The address
 * of the states' table. */
int TaxiDriverInit_Tables(void)
{
    static const MemberPointer *const states[2 * TAXI_DRIVER_STATES] = {
        &data_ov051_02261674, &data_ov051_022615e4, /* 0: wait */
        &data_ov051_02261694, &data_ov051_0226176c, /* 1: talk */
        &data_ov051_022615c4, &data_ov051_022615f4, /* 2: done */
        &data_ov051_02261774, &data_ov051_02261794, /* 3: arrive */
        &data_ov051_0226178c, &data_ov051_02261784, /* 4: leave */
    };
    for (int i = 0; i < TAXI_DRIVER_STATES; i++) {
        data_ov051_02261ba8[i].enter = *states[2 * i];
        data_ov051_02261ba8[i].update = *states[2 * i + 1];
    }
    return (int) (u32) (uintptr_t) data_ov051_02261ba8;
}
CLEAN_AS(__sinit_ov051_0226150c, TaxiDriverInit_Tables)
