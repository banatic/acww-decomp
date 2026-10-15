/* func_020012ec @ 0x020012ec, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern u64 OS_GetTick(void);
extern u32 _ll_udiv(u64 a, u32 b, u32 c);
extern void func_02001324(void);
extern u32 data_0213fdd4;

void func_020012ec(void)
{
    volatile u16 *reg;
    u64 tick;

    reg = (volatile u16 *) 0x04000208;
    (void) *reg;
    *reg = 0;
    tick = OS_GetTick();
    tick <<= 6;
    data_0213fdd4 = _ll_udiv(tick, 0x82ea, 0);
    while (1) {
        func_02001324();
    }
}
