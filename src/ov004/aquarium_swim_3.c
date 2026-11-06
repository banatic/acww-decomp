/* aquarium_swim_3: 6 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02239820 @ 0x02239820, 0x38 bytes, Thumb
 * func_ov004_02239804 @ 0x02239804, 0x1c bytes, Thumb
 * func_ov004_022397ec @ 0x022397ec, 0x18 bytes, Thumb
 * func_ov004_02239790 @ 0x02239790, 0x5c bytes, Thumb
 * func_ov004_02239768 @ 0x02239768, 0x28 bytes, Thumb
 * func_ov004_02239700 @ 0x02239700, 0x68 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_02239790 {
    u8 pad_00[0x1ac];
    int unk_1AC;
    u8 pad_1B0[0x1ca - 0x1b0];
    signed char unk_1CA;
    u8 pad_1CB[0x1cc - 0x1cb];
    int unk_1CC;
    u8 pad_1D0[0x228 - 0x1d0];
    int unk_228;
};

extern void func_02054cac(void *, int, int, int, int, unsigned short, unsigned short);
extern int NNS_G3dGetJntAnmSet(int);
extern int func_02107b44(int, int);
extern int func_020e88dc(int *p, int v, int step);

void func_ov004_02239820(char *self, int a1)
{
    // DECLS
    // ENDDECLS
    func_02054cac(self + 0x64, func_02107b44(NNS_G3dGetJntAnmSet(*(int *) (self + (a1 << 2) + 0x54)), 0x0), 0x2, 0x0, 0x1000,
                  0x0, 0x0);
}

int func_ov004_02239804(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_02239820((char *) self, 0x0);
    *(u8 *) (self + 0x22e) = 0x0;
    return 0x22e;
}

int func_ov004_022397ec(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_02239804((char *) self);
    *(u8 *) (self + 0x1fd) = 0x2;
    return 0x1fd;
}

void func_ov004_02239790(struct UnkStruct_02239790 *self, int step, int hi, int lo)
{
    int *p;

    p = &self->unk_1AC;
    *p = *p + step * self->unk_1CA;
    if (*p > hi) {
        func_020e88dc(p, self->unk_1CC, step);
    } else if (*p < lo) {
        func_020e88dc(p, self->unk_228, step);
    }
}

void func_ov004_02239768(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_02239790((struct UnkStruct_02239790 *) self, *(int *) (self + 0x224), *(int *) (self + 0x1cc),
                        *(int *) (self + 0x228));
}

void func_ov004_02239700(char *self)
{
    // DECLS
    // ENDDECLS
    if ((u32) (*(int *) (self + 0x15c) - 0x2d) <= (u32) 0x1) {
        func_ov004_02239790((struct UnkStruct_02239790 *) self, *(int *) (self + 0x224), *(int *) (self + 0x1cc),
                            *(int *) (self + 0x228));
    } else {
        if (*(u8 *) (self + 0x1e8) == *(int *) (self + 0x15c)) {
            func_ov004_02239790((struct UnkStruct_02239790 *) self, *(int *) (self + 0x224), *(int *) (self + 0x1cc),
                                *(int *) (self + 0x228));
        } else {
            func_ov004_02239790((struct UnkStruct_02239790 *) self, 0x7b, 0x5000, *(int *) (self + 0x228));
        }
    }
}
