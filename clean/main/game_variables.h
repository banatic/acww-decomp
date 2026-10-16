/* A table of halfword values at data_021dc5c0, in banks of 0x100 bytes (128 halfwords) that
 * GameVariables_Slot addresses by bank and index. The game asks only bank 0: overlays 46, 47
 * and 49 test index 0x4a (with the session linked, among other conditions, before they go on),
 * and the sun level's date is stored at index 0x50 (FieldActor_StoreSunDate). What the values
 * stand for is not known.
 *
 * Also here, a value by (id, index) that is always 0 (GameVariables_Tweak); the game adds it to
 * screen positions. */
#ifndef CLEAN_MAIN_GAME_VARIABLES_H
#define CLEAN_MAIN_GAME_VARIABLES_H

#include "types.h"

unsigned short *GameVariables_Slot(unsigned short bank, unsigned short index);
int GameVariables_Tweak(int id, int index);

#endif
