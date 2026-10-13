/* func_ov004_02237870 @ 0x02237870, 0x7c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

#pragma opt_propagation off
#define F(k) (*(int *) (self + k))
extern int func_ov004_02239460(int, int);

void func_ov004_02237870(char *self)
{
    int m;
    s8 x;
    F(0x1ac) = F(0x1ac) + F(0x224) * *(s8 *) (self + 0x1ca);
    if (func_ov004_02239460(0, 0x64) < 0xf) {
        x = *(s8 *) (self + 0x1ca);
        m = -1;
        *(s8 *) (self + 0x1ca) = (s8) (x * m);
    }
    if (F(0x1ac) > F(0x1cc)) {
        *(s8 *) (self + 0x1ca) = -1;
        F(0x1ac) = F(0x1cc);
    } else if (F(0x1ac) < F(0x228)) {
        *(s8 *) (self + 0x1ca) = 1;
        F(0x1ac) = F(0x228);
    }
}
