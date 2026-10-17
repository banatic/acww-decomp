/* The furniture's sounds (furniture_sounds.h). */
#include "furniture_sounds.h"

#include "clean.h"

static_assert(sizeof(FurnitureSoundRow) == 8, "a row");

/* The rows, and the row of no sounds given past the end. */
extern const FurnitureSoundRow data_ov004_02247fb4[FURNITURE_SOUND_ROWS];
extern const FurnitureSoundRow data_ov004_02247ce4;

/* func_ov004_0223a730 */
int FurnitureSounds_Sound3(int number)
{
    return FurnitureSounds_Row(number)->sounds[3];
}
CLEAN_AS(func_ov004_0223a730, FurnitureSounds_Sound3)

/* func_ov004_0223a740 */
int FurnitureSounds_Sound2(int number)
{
    return FurnitureSounds_Row(number)->sounds[2];
}
CLEAN_AS(func_ov004_0223a740, FurnitureSounds_Sound2)

/* func_ov004_0223a750 */
int FurnitureSounds_Sound1(int number)
{
    return FurnitureSounds_Row(number)->sounds[1];
}
CLEAN_AS(func_ov004_0223a750, FurnitureSounds_Sound1)

/* func_ov004_0223a760 */
u16 FurnitureSounds_Sound0(int number)
{
    return FurnitureSounds_Row(number)->sounds[0];
}
CLEAN_AS(func_ov004_0223a760, FurnitureSounds_Sound0)

/* func_ov004_0223a770: the furniture's row, or the row of no sounds for a number past the
 * last.
 * QUIRK: the number is compared signed, so a negative one reads a row before the table (the
 * address is formed the same way here). */
const FurnitureSoundRow *FurnitureSounds_Row(int number)
{
    if (number < FURNITURE_SOUND_ROWS) {
        return (const FurnitureSoundRow *) ((uintptr_t) data_ov004_02247fb4 + (u32) number * sizeof(FurnitureSoundRow));
    }
    return &data_ov004_02247ce4;
}
CLEAN_AS(func_ov004_0223a770, FurnitureSounds_Row)
