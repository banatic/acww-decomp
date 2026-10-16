/* A byte kept between two steps of the code at 0x020b5xxx: func_020b5e44 stores it along with a
 * request (func_020a53ec) and func_020b5be4 hands it on with the next one. It is a C++ global
 * object with an empty constructor and destructor (__sinit_020c6464). */
#ifndef CLEAN_MAIN_GLOBAL_021DC5B0_H
#define CLEAN_MAIN_GLOBAL_021DC5B0_H

#include "types.h"

unsigned char Global021dc5b0_Get(void);
void Global021dc5b0_Set(unsigned char value);
void Global021dc5b0_Destruct(void *object);
void Global021dc5b0_Construct(void *object);

#endif
