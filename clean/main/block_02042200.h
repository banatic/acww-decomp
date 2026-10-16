/* Two flags of main (data_021c776c) taken from bits 7 and 6 of byte 0x30 of data_021c79c4 (the
 * town's object that func_0204678c updates through func_0204a3cc), and acted on in scenes 0
 * and 0x31 by overlay 3. What they stand for is not known yet. */
#ifndef CLEAN_MAIN_BLOCK_02042200_H
#define CLEAN_MAIN_BLOCK_02042200_H

#include "types.h"

void Block02042200_Update(void);
void Block02042200_Apply(u8 *flags);
void Block02042200_ReadFlags(u8 *flags);

#endif
