/* func_ov133_0229b660 @ 0x0229b660, 0x56 bytes, Thumb, module ov133
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *func_020984e8(void *self);
extern void *func_02099664(void *a);
extern long long func_02077be0(void *b);

int func_ov133_0229b660(u8 *self)
{
    void *a;
    long long acc;
    int i;

    a = func_020984e8(self);
    acc = 0;
    for (i = 0; i < 0xc; i++) {
        u8 *p = self + i;

        acc *= 10;
        acc += (long long) p[0xa4];
    }
    if (acc == func_02077be0(func_02099664(a))) {
        return 1;
    }
    return 0;
}
