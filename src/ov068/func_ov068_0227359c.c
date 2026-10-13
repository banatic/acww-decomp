/* func_ov068_0227359c @ 0x0227359c, 0x13c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0227359c;

extern void func_ov068_022731b4(struct UnkStruct_0227359c *self);
extern void func_02056ffc(void *p);
extern void func_02055124(void *p);
extern int func_ov051_02260474(void);
extern void func_ov051_02260490(void);
extern void func_ov068_02272fe8(struct UnkStruct_0227359c *self, u8 kind, void *a, void *b, int c, int d, int e, int f);
extern void NNS_G3dMdlSetMdlAlpha(void *p, int a, u8 b);

struct UnkStruct_0227359c {
    u8 pad_00[0xec];
    u8 unk_EC[0x5c];
    void *unk_148;
    u8 pad_14C[0x144];
    u8 unk_290[8];
    u32 unk_298;
    u8 pad_29C[0xc];
    u32 *unk_2A8;
    u8 pad_2AC[4];
    u8 unk_2B0[8];
    u32 unk_2B8;
    u8 pad_2BC[0xc];
    u32 *unk_2C8;
    u8 pad_2CC[4];
    u8 unk_2D0[0x160];
    u8 unk_430;
    u8 pad_431[3];
    u8 unk_434[0xb8];
    u8 unk_4EC[0xae];
    s16 unk_59A;
    s16 unk_59C;
    s16 unk_59E;
    s16 unk_5A0;
};

int func_ov068_0227359c(struct UnkStruct_0227359c *self)
{
    int val;
    int kind;

    func_ov068_022731b4(self);
    func_02056ffc(self->unk_2B0);

    *self->unk_2C8 = self->unk_2B8;

    func_02055124(self->unk_EC);
    func_02056ffc(self->unk_290);

    *self->unk_2A8 = self->unk_298;

    if (self->unk_430 != 0) {
        func_02055124(self->unk_2D0);
    }

    val = func_ov051_02260474();
    func_ov051_02260490();

    kind = 0;
    switch (val) {
        case 0xfb:
            kind = 0;
            break;
        case 0x8d:
            kind = 1;
            break;
        case 0x8e:
            kind = 2;
            break;
        case 0x8f:
            kind = 3;
            break;
        case 0x90:
            kind = 4;
            break;
        case 0x91:
            kind = 5;
            break;
    }

    func_ov068_02272fe8(self, (u8) kind, self->unk_434, self->unk_4EC, 0, 0x1000, 0, 0);

    func_02055124(self->unk_434);

    NNS_G3dMdlSetMdlAlpha(self->unk_148, self->unk_59C, (u8) self->unk_59A);
    NNS_G3dMdlSetMdlAlpha(self->unk_148, self->unk_59E, (u8) self->unk_59A);
    NNS_G3dMdlSetMdlAlpha(self->unk_148, self->unk_5A0, (u8) self->unk_59A);

    return 1;
}
