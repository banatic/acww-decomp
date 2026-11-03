/* room_object_02252f2c: 4 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0221a1b0 @ 0x0221a1b0, 0x24 bytes, Thumb
 * func_ov004_0221a17c @ 0x0221a17c, 0x34 bytes, Thumb
 * func_ov004_0221a158 @ 0x0221a158, 0x24 bytes, Thumb
 * func_ov004_0221a150 @ 0x0221a150, 0x8 bytes, Thumb
 */

#include "types.h"

extern void func_ov004_0220d280(void *, int, int);
extern int func_ov004_02210744(void *);
extern int func_ov004_0220d2a8(void *p);
extern int func_0205265c(void *self, u8 a, int b, int c);
extern int func_ov004_0221078c(void *);

int func_ov004_0221a1b0(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0220d280(self + 0x740, 0x0, 0x0);
    func_ov004_02210744(self);
    return 0x1;
}

void func_ov004_0221a17c(char *self)
{
    if (func_ov004_0220d2a8(self + 0x740) != 0) {
        func_0205265c(self, (u8) ((*(u8 *) (self + 0x844) + 1) & 1), 0xff, 1);
    }
}

int func_ov004_0221a158(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0220d280(self + 0x740, 0x1, 0x0);
    func_ov004_0221078c(self);
    return 0x1;
}

void func_ov004_0221a150(char *arg0)
{
    func_ov004_0221a17c((char *) arg0);
}
