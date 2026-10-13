/* func_ov004_0222b6a0 @ 0x0222b6a0, 0x8 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct Pair {
    u8 a;
    u8 b;
};

void func_ov004_0222b6a0(struct Pair *p, u8 b)
{
    p->a = 0;
    p->b = b;
}
