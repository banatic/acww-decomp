/* func_ov004_02232754 @ 0x02232754, 0x40 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_0203cbcc(void *);
extern void func_020574b4(void *);
extern void func_020b9e58(void *);

void *func_ov004_02232754(char *self)
{
    // DECLS
    // ENDDECLS
    *(u16 *) (self) = 0xfff1;
    *(u16 *) (self + 0x2) = 0xfff1;
    func_020b9e58(self + 0x4);
    func_0203cbcc(self + 0x2c);
    func_020574b4(self + 0x20f4);
    *(u16 *) (self) = 0xfff1;
    *(u16 *) (self + 0x2) = 0xfff1;
    *(void **) (self + 0x20f0) = 0x0;
    return self;
}
