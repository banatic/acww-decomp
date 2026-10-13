/* func_ov004_0222a218 @ 0x0222a218, 0x6 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct Pair {
    u8 a;
    u8 b;
};

void func_ov004_0222a218(struct Pair *p, u8 a, u8 b)
{
    p->a = a;
    p->b = b;
}
