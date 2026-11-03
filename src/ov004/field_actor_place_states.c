/* field_actor_place_states: 3 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0222b1fc @ 0x0222b1fc, 0x18 bytes, Thumb
 * func_ov004_0222b1d8 @ 0x0222b1d8, 0x22 bytes, Thumb
 * func_ov004_0222b1b4 @ 0x0222b1b4, 0x22 bytes, Thumb
 */

#include "types.h"

extern void func_02077910(void *, int);
extern void func_020779b8(void *, int, int);
extern void func_02077978(char *p, int b, int c);
extern short func_020778f8(char *p);

void func_ov004_0222b1fc(char *self, int a, int b, short c, u8 d, u8 e)
{
    *(int *) self = a;
    *(int *) (self + 4) = b;
    *(short *) (self + 8) = c;
    *(u8 *) (self + 0xa) = d;
    *(u8 *) (self + 0xb) = e;
}

void func_ov004_0222b1d8(char *self, int a1, int a2, int a3, u8 flag)
{
    // DECLS
    // ENDDECLS
    func_020779b8(self, a1, a2);
    func_02077910(self + 0x5, a3);
    *(u8 *) (self + 0x7) = flag;
}

void func_ov004_0222b1b4(char *p, int b, int c, short *out, u8 *out2)
{
    func_02077978(p, b, c);
    *out = func_020778f8(p + 5);
    *out2 = *(u8 *) (p + 7);
}
