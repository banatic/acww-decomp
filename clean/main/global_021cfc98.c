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

/* The object: a date and time (the clock is set from it, StateBlock_SetClockOffset). */
extern DateTime data_021cfc98;
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

/* func_0206f80c: the date and time copied out to `when`. */
void Global021cfc98_CopyOut(DateTime *when)
{
    MI_CpuCopy8(&data_021cfc98, when, sizeof(DateTime));
}
CLEAN_AS(func_0206f80c, Global021cfc98_CopyOut)

/* func_0206f820: the date and time copied in from `when`. */
void Global021cfc98_CopyIn(const DateTime *when)
{
    MI_CpuCopy8(when, &data_021cfc98, sizeof(DateTime));
}
CLEAN_AS(func_0206f820, Global021cfc98_CopyIn)
