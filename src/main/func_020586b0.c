/* func_020586b0 @ 0x020586b0, 0xd8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern const u8 data_020cbaf0[];
extern int func_020e895c(void *dst, u32 a, u32 b);
extern int func_020044c0(void *p, int a, int b, int c);
extern void func_02059674(void *self, int a);

struct UnkStruct_020586b0 {
    u8 pad_00[0x50];
    u16 unk_50;
    u8 pad_52[0x60 - 0x52];
    u32 unk_60;
    u32 unk_64;
    u32 unk_68;
    u32 unk_6C;
    u32 unk_70;
    u32 unk_74;
    u8 pad_78[0x90 - 0x78];
    u32 unk_90;
    u32 unk_94;
    u32 unk_98;
    u8 pad_9C[0xa8 - 0x9c];
    u32 unk_A8;
    u32 unk_AC;
    u32 unk_B0;
    u8 pad_B4[0xd4 - 0xb4];
    u8 unk_D4;
    u8 _paddr[0xd6 - 0xd5];
    u16 unk_D6;
    u8 _padr2[0xdc - 0xd8];
    u32 unk_DC;
};

void func_020586b0(struct UnkStruct_020586b0 *self)
{
    u32 v;
    u8 limit;
    unsigned int cond;

    limit = data_020cbaf0[2];
    if ((int) self->unk_D6 >= (int) limit) {
        return;
    }

    v = self->unk_A8;
    func_020e895c(&v, 0x1000, 0x200);
    {
        u32 w = v;
        self->unk_A8 = w;
        self->unk_AC = w;
        self->unk_B0 = w;
    }

    func_020e895c(&self->unk_60, self->unk_6C, self->unk_90);
    func_020e895c(&self->unk_64, self->unk_70, self->unk_94);
    func_020e895c(&self->unk_68, self->unk_74, self->unk_98);

    self->unk_D6 = (u16) (self->unk_D6 + 1);
    if ((int) self->unk_D6 < (int) limit) {
        return;
    }

    cond = 0;
    if ((unsigned) self->unk_50 >= 0x1492u && (unsigned) self->unk_50 <= 0x14fdu) {
        cond = 1;
    }
    if (cond > 0) {
        func_020044c0(&self->unk_DC, 0x70, 0x7f, 0);
    }

    self->unk_D4 = 3;
    func_02059674(self, 0);
}
