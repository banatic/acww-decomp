/* func_020bfd1c @ 0x020bfd1c, 0x150 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u8 pad_00[4];
    int unk_04;
    u8 pad_08[0xc - 8];
    int unk_0C;
    u8 pad_10[0x31 - 0x10];
    u8 unk_31;
    u8 pad_32[0x34 - 0x32];
    int unk_34;
    u8 pad_38[0x3c - 0x38];
    int unk_3C;
    u8 pad_40[0x50 - 0x40];
    int unk_50;
    u8 pad_54[0x60 - 0x54];
    u32 unk_60;
    int unk_64;
    int unk_68;
    int unk_6C;
    int unk_70;
} UnkStruct_020bfd1c_2;

typedef struct {
    int a;
    int b;
    int c;
} UnkStruct_020bfd1c;

extern int data_021f8b48;

extern int func_020c00f8(int a, int b);
extern int FX_Div(int a, int b);
extern int FX_MulFunc(int a, int b);
extern void func_020c0324(void *p, int a, int b, int c);
extern void func_020bdc50(void *p, int a, int b, UnkStruct_020bfd1c *w, u32 v);

void func_020bfd1c(UnkStruct_020bfd1c_2 *self)
{
    // DECLS
    int lim;
    u32 v;
    int flag;
    int trig;
    int d;
    u32 x;
    u32 a;
    int t;
    int tb;
    int ta;
    // ENDDECLS
    UnkStruct_020bfd1c w;

    v = self->unk_60;
    flag = ((v >> 31) & 1) != 0;
    trig = 0;
    if (self->unk_31 != 0) {
        self->unk_68 = self->unk_68 + 1;
        if (self->unk_68 > 6) {
            trig = 1;
        }
    } else {
        lim = 0xc0000 - self->unk_3C;
        d = func_020c00f8(lim, self->unk_64);
        if (d <= 0x20000) {
            self->unk_50 = FX_Div(0x20000, d);
            self->unk_70 = 0xc0000 - (d / 2);
        } else {
            if (d < lim) {
                self->unk_50 = 0x1000;
            } else {
                self->unk_50 = FX_MulFunc(self->unk_50, 0x14cd);
                if (self->unk_50 >= 0xa000) {
                    self->unk_50 = 0xa000;
                    self->unk_31 = 1;
                }
                d = lim;
            }
            self->unk_70 = 0xc0000 - (d - FX_Div(0x10000, self->unk_50));
        }
        func_020c0324(&self->unk_34, self->unk_6C, self->unk_70, flag);
    }
    if (trig != 0) {
        self->unk_04 = 3;
        x = (v >> 8) & 3;
        if (((self->unk_60 >> 31) & 1) != 0) {
            x = (x & 3) << 8;
            a = x | 0x80000000;
            x = x | 0xc0000001;
        } else {
            t = self->unk_0C;
            x = (x & 3) << 8;
            a = x | (u32) (((int) (t - 2) - 0x1d) & 0xf);
            x = x | (u32) ((((int) (t - 1) - 0x1d) & 0xf) | 0x40000000);
        }
        tb = self->unk_3C - 0x2000;
        ta = self->unk_6C;
        w.a = ta;
        w.b = tb;
        w.c = 0;
        func_020bdc50(&data_021f8b48, 9, 0x3c, &w, a);
        func_020bdc50(&data_021f8b48, 9, 0x3c, &w, x);
    }
}
