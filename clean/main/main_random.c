/* The game's main random generator (main_random.h). */
#include "main_random.h"

#include "clean.h"
#include "clock.h"

extern Random data_021cb5a0;

/* func_02061530: the generator seeded from the clock (Clock_Seed). */
void MainRandom_SeedFromClock(void)
{
    Random_Init(&data_021cb5a0, Clock_Seed());
}
CLEAN_AS(func_02061530, MainRandom_SeedFromClock)

/* func_0206154c: a generator's destructor: nothing to do. */
void MainRandom_Destruct(Random *random)
{
    (void) random;
}
CLEAN_AS(func_0206154c, MainRandom_Destruct)

/* func_020644b4: a number below `bound` from the generator; the same as MainRandom_Below. */
unsigned int MainRandom_BelowB(int bound)
{
    return Random_Below(&data_021cb5a0, (u32) bound);
}
CLEAN_AS(func_020644b4, MainRandom_BelowB)

/* func_020644cc: a number below `bound` from the generator. */
unsigned int MainRandom_Below(int bound)
{
    return Random_Below(&data_021cb5a0, (u32) bound);
}
CLEAN_AS(func_020644cc, MainRandom_Below)
