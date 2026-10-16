/* Main's code at 020ba298: the destructors of a process class (vtable data_020e69a4, 0x60
 * bytes, created by func_020c1538), and two calls of the town's state code: a byte of
 * data_021fba68 set, and flag 0x32 of this console's player set with a call into
 * data_021f8b48. */
#ifndef CLEAN_MAIN_BLOCK_020BA298_H
#define CLEAN_MAIN_BLOCK_020BA298_H

#include "autoload_2/process.h"
#include "types.h"

Process *Block020ba298_Destruct(Process *process);
Process *Block020ba298_DestructFree(Process *process);
void Block020ba298_SetByte9(void);
void Block020ba298_SetPlayerFlag32(void);

#endif
