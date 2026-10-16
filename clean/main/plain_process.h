/* A process class that adds nothing to the game's process class (data_020da13c): its vtable
 * (data_020e587c) differs only by its destructors. Its profile is data_020e586c (execute order
 * 200, draw order 198); an object is 0x50 bytes, a bare Process. */
#ifndef CLEAN_MAIN_PLAIN_PROCESS_H
#define CLEAN_MAIN_PLAIN_PROCESS_H

#include "autoload_2/process.h"
#include "types.h"

Process *PlainProcess_Create(void);
Process *PlainProcess_Destroy(Process *self);
Process *PlainProcess_Delete(Process *self);

#endif
