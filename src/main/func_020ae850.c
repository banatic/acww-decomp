/* func_020ae850 @ 0x020ae850, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern u16 *func_020ae8e4(void *a, unsigned int b, int c);
extern int func_0204bcdc(void *p);
extern unsigned int func_0204bc64(void *p);
extern int func_020ae8bc(void *a, unsigned int b);

static __inline int EqA(void *p, void *q)
{
    if (func_0204bc64(p) == func_0204bc64(q)) {
        return 1;
    }
    return 0;
}

static __inline int EqB(u16 x, u16 y)
{
    if (x == y) {
        return 1;
    }
    return 0;
}

int func_020ae850(void *a, u16 *b)
{
    unsigned int i;
    u16 *p;
    int result;

    for (i = 0; i < 6; i++) {
        p = func_020ae8e4(a, i, 0);
        if (func_0204bcdc(p)) {
            result = EqA(p, b);
        } else {
            result = EqB(p[0], b[0]);
        }
        if (result != 0) {
            return func_020ae8bc(a, i);
        }
    }
    return 0;
}
