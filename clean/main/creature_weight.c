/* The band of a creature list entry's weight (creature_weight.h). */
#include "creature_weight.h"

#include "clean.h"

extern const u8 data_020d1a24[CREATURE_WEIGHT_BANDS]; /* 17, 11, 6, 3 */
extern const u8 data_020d1a2c[CREATURE_WEIGHT_BANDS]; /* 15, 10, 6, 3 */

/* func_0209a478: the band of the weight's low byte against 17, 11, 6, 3. */
int CreatureWeight_BandA(u32 weight)
{
    return CreatureWeight_Band((u8) weight, data_020d1a24, CREATURE_WEIGHT_BANDS);
}
CLEAN_AS(func_0209a478, CreatureWeight_BandA)

/* func_0209a488: the band of the weight's low byte against 15, 10, 6, 3. */
int CreatureWeight_BandB(u32 weight)
{
    return CreatureWeight_Band((u8) weight, data_020d1a2c, CREATURE_WEIGHT_BANDS);
}
CLEAN_AS(func_0209a488, CreatureWeight_BandB)

/* func_0209a498: the index of the first of `count` thresholds that `weight` reaches, else
 * `count`. */
int CreatureWeight_Band(u8 weight, const u8 *thresholds, int count)
{
    for (int i = 0; i < count; i++) {
        if (weight >= thresholds[i]) {
            return i;
        }
    }
    return count;
}
CLEAN_AS(func_0209a498, CreatureWeight_Band)
