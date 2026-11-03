/* chest_6: 4 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02217848 @ 0x02217848, 0x1c bytes, Thumb
 * func_ov004_0221780c @ 0x0221780c, 0x3c bytes, Thumb
 * func_ov004_022177d8 @ 0x022177d8, 0x34 bytes, Thumb
 * func_ov004_022177a0 @ 0x022177a0, 0x38 bytes, Thumb
 */

#include "types.h"

extern int func_ov004_0221152c(unsigned int size);
extern char *func_ov004_0220d268(void *);
extern void *func_ov004_022110e4(void *);
extern void *const data_ov004_0225211c[];
extern void *const data_ov004_022521c8[];
extern int func_ov004_0220d258(void *p);
extern void *func_ov004_02210cf0(void *p);
extern void func_ov004_02211518(void *p);

void *func_ov004_0221780c(char *self);

void func_ov004_02217848(void)
{
    char *conditionInput0;

    if ((conditionInput0 = (char *) (func_ov004_0221152c(0x868)))) {
        func_ov004_0221780c((char *) conditionInput0);
    }
}

void *func_ov004_0221780c(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_022110e4(self);
    *(void **) (self) = ((void * *) data_ov004_0225211c);
    *(void **) (self + 0xec) = ((void * *) data_ov004_022521c8);
    func_ov004_0220d268(self + 0x844);
    *(u8 *) (self + 0x860) = 0x0;
    return self;
}

void *func_ov004_022177d8(char *self)
{
    *(const void **) (self) = data_ov004_0225211c;
    *(const void **) (self + 0xec) = data_ov004_022521c8;
    func_ov004_0220d258(self + 0x844);
    func_ov004_02210cf0(self);
    return self;
}

void *func_ov004_022177a0(char *self)
{
    *(const void **) (self) = data_ov004_0225211c;
    *(const void **) (self + 0xec) = data_ov004_022521c8;
    func_ov004_0220d258(self + 0x844);
    func_ov004_02210cf0(self);
    func_ov004_02211518(self);
    return self;
}
