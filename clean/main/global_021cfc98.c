/* The 8-byte global object at data_021cfc98: the start-up (__sinit_020c5c40) clears it and
 * registers its destructor; func_0206f80c and func_0206f820 copy it in and out whole. */
#include "global_021cfc98.h"

#include "clean.h"

/* func_02004b2c: the destructor, which has nothing to do. */
void Global021cfc98_Destruct(void *object)
{
    (void) object;
}
CLEAN_AS(func_02004b2c, Global021cfc98_Destruct)
