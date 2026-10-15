/* func_ov004_022329e0 @ 0x022329e0, 0x40 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_020574b4(void *);
extern void *func_020b9e58(void *);
extern void *func_020ba294(void *);

void *func_ov004_022329e0(char *self)
{
    // DECLS
    // ENDDECLS
    *(u16 *) (self) = 0xfff1;
    *(u16 *) (self + 0x2) = 0xfff1;
    func_020b9e58(self + 0x4);
    func_020ba294(self + 0x2c);
    func_020574b4(self + 0x10f4);
    *(u16 *) (self) = 0xfff1;
    *(u16 *) (self + 0x2) = 0xfff1;
    *(void **) (self + 0x10f0) = 0x0;
    return self;
}
