/* The halfword values at data_021dc5c0 (game_variables.h). */
#include "game_variables.h"

#include "clean.h"

#define GAME_VARIABLES_BANK_SIZE 0x100 /* bytes */

extern u8 data_021dc5c0[];

/* func_0209d358: the address of value `index` of `bank`.
 * QUIRK: neither the bank nor the index is checked. */
unsigned short *GameVariables_Slot(unsigned short bank, unsigned short index)
{
    return (unsigned short *) (void *) &data_021dc5c0[bank * GAME_VARIABLES_BANK_SIZE + index * sizeof(u16)];
}
CLEAN_AS(func_0209d358, GameVariables_Slot)

/* func_0209d368: the adjustment `id` and `index` name; always 0. Callers add it to positions
 * (for example func_02039b90 with ids 0x12e and 0x138, func_020a9e04 with 0x65). */
int GameVariables_Tweak(int id, int index)
{
    (void) id;
    (void) index;
    return 0;
}
CLEAN_AS(func_0209d368, GameVariables_Tweak)
