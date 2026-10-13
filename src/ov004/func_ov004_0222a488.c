/* func_ov004_0222a488 @ 0x0222a488, 0xc bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0222a488 {
    int a;
    int b;
    u16 c;
    u8 d;
};

void func_ov004_0222a488(struct UnkStruct_0222a488 *s, int a, int b, u16 c)
{
    s->a = a;
    s->b = b;
    s->c = c;
    s->d = 0;
}
