/* design_editor_input: 3 functions, module ov123
 * mwccarm 1.2/base -O4,s
 * func_ov123_022998c0 @ 0x022998c0, 0x70 bytes, Thumb
 * func_ov123_02299878 @ 0x02299878, 0x48 bytes, Thumb
 * func_ov123_022996dc @ 0x022996dc, 0x19c bytes, Thumb
 */

#include "types.h"

typedef struct UnkStruct_02299878 {
    char pad_00[0xB1];
    unsigned char b1;
    unsigned char b2;
    char pad_B3;
    unsigned char b4;
    unsigned char b5;
} UnkStruct_02299878;

struct UnkStruct_022996dc {
    u8 pad_00[0xa2];
    u8 unk_A2;
    u8 pad_A3;
    u8 unk_A4;
    u8 unk_A5;
    u8 pad_a6_a7[2];
    u8 unk_A8;
    u8 unk_A9;
    u8 pad_aa_b0[7];
    u8 unk_B1;
    u8 unk_B2;
    u8 pad_B3;
    u8 unk_B4;
    u8 unk_B5;
};

extern void func_ov123_0229b160(void *param, unsigned char val);
extern unsigned char data_021fbe40[];
extern unsigned char *func_ov002_02208098(UnkStruct_02299878 *p, unsigned char value);
extern void func_ov123_02299630(UnkStruct_02299878 *p, int a);
extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;
extern void func_ov123_0229ae24(struct UnkStruct_022996dc *self);
extern int func_ov123_02299650(struct UnkStruct_022996dc *self, u32 param);
extern void func_ov123_02299640(struct UnkStruct_022996dc *self, u32 param);
extern void func_0200459c(int a);
extern int func_ov123_0229ab80(struct UnkStruct_022996dc *self, u8 cur_a8, u8 cur_a9, u8 orig_a8, u8 orig_a9, u8 a2, u8 a4);
extern void func_0200467c(u16 cmd);
extern u8 func_ov123_0229afa8(struct UnkStruct_022996dc *self);
extern void func_02004644(int cmd, int arg);
extern void func_ov123_0229ae84(struct UnkStruct_022996dc *self);
extern void func_ov123_02299ec4(struct UnkStruct_022996dc *self);

int func_ov123_022998c0(unsigned char *param)
{
    unsigned short keys = ((unsigned short *) data_021fbe40)[1];
    unsigned char b;

    if (keys & 0x200) {
        b = param[0xa2];
        if (b > 1) {
            func_ov123_0229b160(param, b - 1);
        } else {
            func_ov123_0229b160(param, 15);
        }
        return 1;
    }
    if (keys & 0x100) {
        b = param[0xa2];
        if (b < 15) {
            func_ov123_0229b160(param, b + 1);
        } else {
            func_ov123_0229b160(param, 1);
        }
        return 1;
    }
    return 0;
}

void func_ov123_02299878(UnkStruct_02299878 *p)
{
    p->b1 = 0;
    p->b2 = 0x22;
    func_ov002_02208098(p, 2);
    func_ov123_02299630(p, 0x2000);
    p->b4 = data_021f6c58;
    p->b5 = data_021f6c54;
}

void func_ov123_022996dc(struct UnkStruct_022996dc *self)
{
    u8 a8 = self->unk_A8;
    u8 a9 = self->unk_A9;

    func_ov123_0229ae24(self);

    if (func_ov123_02299650(self, 0x1000) != 0 && self->unk_A4 <= 2) {
        int g0 = (*(u8 *) &data_021f6c58);
        int g1 = (*(u8 *) &data_021f6c54);
        int b4 = self->unk_B4;

        if (g0 != b4 || g1 != self->unk_B5) {
            int d1 = b4 - g0;
            int d2;
            int sum;
            if (d1 < 0) {
                d1 = -d1;
            }
            if ((int) self->unk_B5 > g1) {
                d2 = self->unk_B5 - g1;
                sum = d1 + d2;
            } else {
                d2 = self->unk_B5 - g1;
                sum = d1 - d2;
            }
            func_0200459c(sum);
            func_ov123_02299640(self, 0x100000);
        }

        if (self->unk_A8 != a8 || self->unk_A9 != a9) {
            if (func_ov123_0229ab80(self, self->unk_A8, self->unk_A9, a8, a9, self->unk_A2, self->unk_A4) != 0) {
                func_0200467c(0x861);
            }
            func_ov123_02299640(self, 0x40);
        }
    }

    {
        u8 r4 = func_ov123_0229afa8(self);
        if (((u8) (r4 + 0xdf)) <= 1) {
            self->unk_B2 = 0x22;
        } else {
            if (func_ov123_02299650(self, 0x2000) != 0) {
                if (r4 != self->unk_B2) {
                    func_ov123_02299630((UnkStruct_02299878 *) self, 0x2000);
                    self->unk_B1 = 0;
                }
            } else {
                if (r4 == self->unk_B2) {
                    self->unk_B1++;
                    if (self->unk_B1 >= 0x14) {
                        if (func_ov123_02299650(self, 0x80000) != 0) {
                            func_ov123_02299630((UnkStruct_02299878 *) self, 0x80000);
                            func_ov123_02299630((UnkStruct_02299878 *) self, 0x100000);
                            func_02004644(0x862, 1);
                        }
                        self->unk_A5 = self->unk_B2;
                        func_ov123_0229ae84(self);
                        func_ov123_02299ec4(self);
                        func_ov123_02299630((UnkStruct_02299878 *) self, 0x1000);
                        func_ov123_02299640(self, 0x2000);
                    }
                } else {
                    self->unk_B2 = r4;
                    self->unk_B1 = 0;
                }
            }
        }
    }
}
