/* func_ov004_022140c0 @ 0x022140c0, 0x50 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_020b9e58(void *);
extern void func_ov004_022110e4(void *);
extern void *data_ov004_02252374;
extern void *data_ov004_02252420;

void *func_ov004_022140c0(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_022110e4(self);
    *(void **) (self) = &data_ov004_02252374;
    *(void **) (self + 0xec) = &data_ov004_02252420;
    func_020b9e58(self + 0x848);
    *(void **) (self + 0x844) = 0x0;
    *(u8 *) (self + 0x871) = 0x0;
    *(u8 *) (self + 0x870) = *(u8 *) (self + 0x871);
    return self;
}
