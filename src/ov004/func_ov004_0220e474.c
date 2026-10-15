/* func_ov004_0220e474 @ 0x0220e474, 0x3c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *func_02055b00(void *);
extern void func_ov004_0220da54(void *);

void *func_ov004_0220e474(char *self)
{
    // DECLS
    // ENDDECLS
    func_02055b00(self + 0x10);
    func_ov004_0220da54(self + 0x44);
    *(u16 *) (self + 0x70) = 0xfff1;
    *(void **) (self) = 0x0;
    *(void **) (self + 0x4) = 0x0;
    *(void **) (self + 0x8) = 0x0;
    *(void **) (self + 0xc) = 0x0;
    *(u16 *) (self + 0x70) = 0xfff1;
    *(u8 *) (self + 0x72) = 0x0;
    return self;
}
