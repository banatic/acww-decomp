/* field_actor_place_states_2: 3 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0222b2a4 @ 0x0222b2a4, 0x34 bytes, Thumb
 * func_ov004_0222b288 @ 0x0222b288, 0x1a bytes, Thumb
 * func_ov004_0222b270 @ 0x0222b270, 0x18 bytes, Thumb
 */

#include "types.h"

extern int func_02056f94(void *);
extern int func_ov004_0222bdf0(void *, int, int, int);
extern int func_0200f554(void *self);
extern void func_02010f5c(void *self);

void func_ov004_0222b2a4(char *self)
{
    // DECLS
    // ENDDECLS
    if (func_02056f94(self + 0x2d0) != 0x0 && func_ov004_0222bdf0(self, 0x0, 0x6, -0x1) != 0x0) {
        *(u8 *) (self + 0x8ea) = 0x0;
        return;
    }
}

void func_ov004_0222b288(void *self)
{
    func_0200f554(self);
    func_02010f5c(self);
    func_ov004_0222b2a4((char *) self);
}

void func_ov004_0222b270(char *self, int a, int b, short c, u8 d, u8 e)
{
    *(int *) self = a;
    *(int *) (self + 4) = b;
    *(short *) (self + 8) = c;
    *(u8 *) (self + 0xa) = d;
    *(u8 *) (self + 0xb) = e;
}
