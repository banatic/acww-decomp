/* func_ov004_0222c87c @ 0x0222c87c, 0x4c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *func_0203f130(void *);
extern void *func_02055210(void *);
extern int func_ov004_0222c32c(void *);
extern void func_ov004_0222c398(void *);
extern int func_ov004_0222c548(void *);
extern void *data_ov004_02254b28;

void *func_ov004_0222c87c(char *self)
{
    // DECLS
    // ENDDECLS
    func_0203f130(self);
    *(void **) (self) = &data_ov004_02254b28;
    func_02055210(self + 0xec);
    func_ov004_0222c548(self + 0x1a4);
    func_ov004_0222c398(self + 0x248);
    func_ov004_0222c32c(self + 0x250);
    *(u8 *) (self + 0xea) = 0xff;
    return self;
}
