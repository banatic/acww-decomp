/* The exchange blocks of a visit: each system's block (0x950 bytes, part_11c70 of the state
 * block, data_021ee418) holds what goes from one town to another (a letter in a bottle, a
 * villager moving, a constellation, a paired town, ...). The host keeps one for each slot
 * (func_02090040; 4 for its own) and decides which slot's block each slot is given
 * (Activity.block_source, func_020a2444; 4 for none), then sends each guest its block
 * (SystemPacket_SendSlotBlocks). */
#ifndef CLEAN_MAIN_EXCHANGE_BLOCKS_H
#define CLEAN_MAIN_EXCHANGE_BLOCKS_H

#include "activity.h"
#include "types.h"

#define EXCHANGE_BLOCK_NONE 4 /* Activity.block_source: no block */

int ExchangeBlocks_SendToGuests(Activity *activity);
void ExchangeBlocks_Rotate(Activity *activity);
void ExchangeBlocks_SwapWithRandom(Activity *activity);

#endif
