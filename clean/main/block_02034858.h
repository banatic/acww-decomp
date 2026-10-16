/* A small global object (data_021c5160, built by __sinit_020c4bdc and read by nothing else in
 * the main program) of three rows of three halfwords, and two words the scoring of a room
 * (func_0205b270) leaves behind. */
#ifndef CLEAN_MAIN_BLOCK_02034858_H
#define CLEAN_MAIN_BLOCK_02034858_H

#include "types.h"

typedef struct Block021c5160 {
    s16 unk_00[3];
    s16 unk_06[3]; /* from data_020c9f0c */
    s16 unk_0c[3]; /* from data_020c9f04 */
    u8 unk_12;
} Block021c5160;

void Block021c5160_SetDefaults(Block021c5160 *block);
void Block021c5160_SetColumn(Block021c5160 *block, int index, int a, int b);
void Block021c5160_Clear(Block021c5160 *block);
void Block021c5160_Destroy(Block021c5160 *block);
void *Block021c5160_Construct(Block021c5160 *block);
void RoomScore_SetBonusFlags(u32 flags);
void RoomScore_SetTotal(u32 total);
void Block02034858_AfterDraw(void);

#endif
