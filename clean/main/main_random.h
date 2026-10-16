/* The game's main random generator (data_021cb5a0, a Random of autoload_2/fx_math.h): set up
 * with seed 1 by its static initializer, and seeded from the clock at start-up. Its
 * destructor, which does nothing, also serves another generator (data_021cfb80). */
#ifndef CLEAN_MAIN_MAIN_RANDOM_H
#define CLEAN_MAIN_MAIN_RANDOM_H

#include "autoload_2/fx_math.h"
#include "types.h"

void MainRandom_SeedFromClock(void);
void MainRandom_Destruct(Random *random);

#endif
