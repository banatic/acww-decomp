/* field_actor_room_states2_4: 3 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0222a220 @ 0x0222a220, 0x1c bytes, Thumb
 * func_ov004_0222a218 @ 0x0222a218, 0x6 bytes, Thumb
 * func_ov004_0222a20c @ 0x0222a20c, 0xa bytes, Thumb
 */

#include "types.h"

struct Pair {
    u8 a;
    u8 b;
};

void *func_ov004_0222a220(char *self, int a1)
{
    // DECLS
    // ENDDECLS
    if (a1 > 0x333) {
        *(u8 *) (self) = 0x0;
    } else {
        *(u8 *) (self) = 0x1;
    }
    *(u8 *) (self + 0x1) = 0x0;
    return self;
}

void func_ov004_0222a218(struct Pair *p, u8 a, u8 b)
{
    p->a = a;
    p->b = b;
}

void func_ov004_0222a20c(u8 *s, u8 *a, u8 *b)
{
    *a = s[0];
    *b = s[1];
}
