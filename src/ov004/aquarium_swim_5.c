/* aquarium_swim_5: 6 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02239c40 @ 0x02239c40, 0x1c bytes, Thumb
 * func_ov004_02239c28 @ 0x02239c28, 0x18 bytes, Thumb
 * func_ov004_02239c00 @ 0x02239c00, 0x28 bytes, Thumb
 * func_ov004_02239bd4 @ 0x02239bd4, 0x2c bytes, Thumb
 * func_ov004_02239bb4 @ 0x02239bb4, 0x1e bytes, Thumb
 * func_ov004_02239b80 @ 0x02239b80, 0x34 bytes, Thumb
 */

#include "types.h"

extern void *func_02089b68(void *);
extern void *data_ov004_02255d28;
extern void *func_02089b20(void *);
extern short FX_SinCosTable_[];
int FX_MulFunc(int a, int b);
extern int func_ov004_022392a0(void *arg0);
extern void func_ov004_022399ec(void *);
extern int func_ov004_02239858(void *);

void *func_ov004_02239c40(char *self)
{
    // DECLS
    // ENDDECLS
    func_02089b68(self);
    *(void **) (self) = &data_ov004_02255d28;
    *(void **) (self + 0x4c) = 0x0;
    return self;
}

void *func_ov004_02239c28(void *arg)
{
    *((void **) arg) = ((int *) &data_ov004_02255d28);
    func_02089b20(arg);
    return arg;
}

void func_ov004_02239c00(int *out, int a, int ang)
{
    *out = *out + FX_MulFunc(a, FX_SinCosTable_[((u16) ang >> 4) << 1]);
}

int func_ov004_02239bd4(int *out, int a, int ang)
{
    int valueResult;

    valueResult = *out + FX_MulFunc(a, FX_SinCosTable_[(((u16) ang >> 4) << 1) + 1]);
    *out = valueResult;
    return valueResult;
}

int func_ov004_02239bb4(char *self, int a1, int a2)
{
    // DECLS
    // ENDDECLS
    func_ov004_02239c00((int *) self, a1, a2);
    return func_ov004_02239bd4((int *) (self + 0x8), a1, a2);
}

void func_ov004_02239b80(char *self)
{
    if (func_ov004_022392a0((void *) self) != 0) {
        func_ov004_022399ec(self);
    } else {
        *(char *) (self + 0x1fc) = 0;
        *(char *) (self + 0x1fd) = 0;
        func_ov004_02239858(self);
    }
}
