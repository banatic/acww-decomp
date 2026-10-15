/* func_ov004_02232a20 @ 0x02232a20, 0x46 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

#pragma opt_loop_invariants off
extern int func_020658a0(void);

void func_ov004_02232a20(void *a0, char *h)
{
    u8 cnt = *(u8 *) (h + 0x18);
    char *base = h + *(int *) (h + 8);
    unsigned i;
    for (i = 0; i < cnt; i++) {
        char *p = base + 4;
        u16 n = *(u16 *) (base + 0xa);
        char *q = p + n;
        u16 w = *(u16 *) (p + n);
        char *e = base + *(int *) (q + w * i + 4);
        int m = 0xf;
        int v = *(int *) (e + 0xc);
        int t = v & m;
        if (t != 0) {
            *(int *) (e + 0xc) &= ~m;
            *(int *) (e + 0xc) = *(int *) (e + 0xc) | func_020658a0();
        }
    }
}
