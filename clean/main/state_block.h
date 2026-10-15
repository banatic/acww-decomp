/* The large block of the game's state that func_0209f0f0 clears (0x173fc bytes). What it holds
 * is not known yet; its last words are 32 flags and a value func_0209f180 checks. */
#ifndef CLEAN_MAIN_STATE_BLOCK_H
#define CLEAN_MAIN_STATE_BLOCK_H

#include "types.h"

void StateBlock_ClearFlag(u32 *block, u32 flag);
void StateBlock_SetFlag(u32 *block, u32 flag);
int StateBlock_TestFlag(u32 *block, u32 flag);

#endif
