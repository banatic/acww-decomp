/* aquarium_fish_kinds_2: 3 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02237454 @ 0x02237454, 0x1dc bytes, Thumb
 * func_ov004_022373b4 @ 0x022373b4, 0xa0 bytes, Thumb
 * func_ov004_02237374 @ 0x02237374, 0x40 bytes, Thumb
 */

#include "types.h"

#define W(p, o) (*(int *) ((p) + (o)))
#define S(p, o) (*(short *) ((p) + (o)))
#define B(p, o) (*(signed char *) ((p) + (o)))

struct UnkStruct_022373b4 {
    u8 pad_00[0x50];
    int unk_50;
    u8 pad_54[0x15c - 0x54];
    int unk_15C;
    u8 pad_160[0x1e8 - 0x160];
    u8 unk_1E8;
    u8 unk_1E9;
    u8 pad_1EA[0x258 - 0x1ea];
    int unk_258;
    int unk_25C;
    int unk_260;
    int unk_264;
    int unk_268;
    int unk_26C;
};

extern int FX_MulFunc(int, int);
extern void func_ov004_022354e0(struct UnkStruct_022373b4 *self);
extern void func_ov004_022358c0(void *, int);
extern void func_ov004_02237134(void *);
extern void func_ov004_02237218(void *);

void func_ov004_02237454(u8 *self)
{
    switch (self[0x1ee]) {
        case 3:
            ++W(self, 0x23c);
            break;
        case 5:
            --W(self, 0x23c);
            break;
        case 4:
            if (!self[0x258]) {
                W(self, 0x158) = 0;
            }
            break;
        case 1:
            W(self, 0x1ac) -= W(self, 0x224) * 2;
            if (W(self, 0x1ac) < W(self, 0x228)) {
                W(self, 0x1ac) = W(self, 0x228);
            }
            return;
    }
    {
        int pitch = -W(self, 0x23c) * B(self, 0x256);
        pitch *= ((W(self, 0x20c) * 1000) >> 12);
        S(self, 0x1c4) = pitch;
    }
    if (S(self, 0x1c4) <= -0x1554) {
        S(self, 0x1c4) = -0x1554;
    } else if (S(self, 0x1c4) >= 0x1554) {
        S(self, 0x1c4) = 0x1554;
    }
    W(self, 0x1ac) += W(self, 0x224) * B(self, 0x256);
    switch (self[0x258]) {
        case 0:
            if (W(self, 0x1ac) > 0x299a && self[0x1ee] == 4) {
                ++self[0x257];
                if (self[0x257] >= 20) {
                    self[0x1ee] = 5;
                    self[0x258] = 1;
                    self[0x257] = 0;
                }
            }
            break;
        case 1:
            W(self, 0x1ac) -= FX_MulFunc(0x1800, W(self, 0x224) * B(self, 0x256));
            if (self[0x1ee] == 6) {
                if (W(self, 0x1ac) < W(self, 0x1cc)) {
                    B(self, 0x256) = 1;
                    self[0x255] = 0;
                    self[0x258] = 0;
                    self[0x259] = 1;
                } else {
                    self[0x1ee] = 2;
                    B(self, 0x256) = -1;
                    self[0x258] = 2;
                }
            }
            break;
        case 2:
            if (W(self, 0x1ac) < W(self, 0x1cc) && self[0x1ee] == 2) {
                B(self, 0x256) = 1;
                self[0x255] = 0;
                self[0x258] = 0;
                self[0x259] = 1;
            }
            break;
    }
    if (W(self, 0x1ac) > 0x299a) {
        W(self, 0x1ac) = 0x299a;
    } else if (W(self, 0x1ac) < W(self, 0x228)) {
        W(self, 0x1ac) = W(self, 0x228);
    }
}

void func_ov004_022373b4(struct UnkStruct_022373b4 *self)
{
    self->unk_50 = (int) self;
    self->unk_1E8 = self->unk_15C;
    self->unk_1E9 = self->unk_15C;
    if (self->unk_15C == 0x26) {
        self->unk_258 = 0x9e00;
        self->unk_25C = 0x1000;
        self->unk_260 = 0x14700;
        self->unk_264 = 0xa100;
        self->unk_268 = 0xb00;
        self->unk_26C = 0x14a00;
    } else if (self->unk_15C == 0xc) {
        self->unk_258 = 0x15900;
        self->unk_25C = 0x1000;
        self->unk_260 = 0x13900;
    }
    func_ov004_022354e0(self);
}

void *func_ov004_02237374(char *self)
{
    // DECLS
    // ENDDECLS
    if (*(int *) (self + 0x15c) == 0x26) {
        func_ov004_02237218(self);
    } else {
        if (*(int *) (self + 0x15c) == 0xc) {
            func_ov004_02237134(self);
        }
    }
    func_ov004_022358c0(self, 0x666);
    *(void **) (self + 0x158) = (char *) *(int *) (self + 0x158) + 0x1;
    return self + 0x158;
}
