/* func_020f61e4 @ 0x020f61e4, 0x16c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

// Sound/animation step; fx32 math with v == 100 handled separately.

struct UnkStruct_020f61e4 {
    int unk_00;
    unsigned short unk_04;
    signed char unk_06;
    unsigned char unk_07;
    signed char unk_08;
    signed char unk_09;
    unsigned char unk_0A;
    unsigned char unk_0B;
};

struct UnkStruct_020f61e4_2 {
    unsigned char pad_00[0xc];
    int unk_0C;
    unsigned char pad_10[2];
    unsigned char unk_12;
};
struct UnkStruct_020f61e4_3 {
    unsigned char pad_00[0x2c];
    struct UnkStruct_020f61e4_2 *unk_2C;
};

extern struct UnkStruct_020f61e4_3 data_021fd1bc;
extern int func_020eedb8(int, unsigned short, struct UnkStruct_020f61e4 *);
extern void func_020f6194(struct UnkStruct_020f61e4 *);
extern int func_020f6000(struct UnkStruct_020f61e4 *);
extern void func_020f609c(struct UnkStruct_020f61e4 *, int);
extern fx32 FX_Div(fx32, fx32);

void func_020f61e4(struct UnkStruct_020f61e4 *self, int a1)
{
    struct UnkStruct_020f61e4_2 *k;
    unsigned char en;
    int r;
    int v;
    int t;
    int flag;

    if (self->unk_0A == 0) {
        return;
    }
    if (self->unk_08 == -1) {
        flag = (self->unk_00 != 0);
        switch (flag) {
            case 0:
                func_020eedb8(0, self->unk_04, self);
                break;
            default:
                break;
        }
        func_020f6194(self);
        return;
    }
    self->unk_07 = self->unk_07 + 1;
    k = data_021fd1bc.unk_2C;
    en = k->unk_12;
    if (self->unk_07 >= self->unk_0B) {
        r = func_020f6000(self);
        self->unk_07 = 0;
        if (r) {
            return;
        }
    }
    if (en == 0) {
        return;
    }
    self->unk_06 = self->unk_06 + 1;
    self->unk_07 = 0;
    if (self->unk_06 < 0x10) {
        func_020f609c(self, a1);
    } else if (self->unk_06 >= 0x10) {
        func_020f6000(self);
        return;
    }
    v = self->unk_08;
    t = k->unk_0C;
    if (v == 0x64) {
        self->unk_0B = (unsigned char) (t >> 12);
        return;
    }
    self->unk_0B = (unsigned char) ((fx32) (((long long) t * FX_Div(v << 12, 0x64000) + 0x800) >> 12) >> 12);
}
