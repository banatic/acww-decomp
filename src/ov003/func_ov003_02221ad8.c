/* func_ov003_02221ad8 @ 0x02221ad8, 0x1a8 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_02034270(void *dst, void *src, int a, int b);
extern void func_0203423c(void *ptr);
extern void VEC_Add(void *a, void *b, void *c);
extern void func_02090c2c(int a, void *b, int c, void *d);
extern void func_02090aa4(int x, void (*cb)(void));
extern void func_020ba31c(int k);
extern void func_020ba334(int k);
extern void func_ov003_02219930(void *p);
extern void func_ov003_02222860(void *self);
extern int func_ov003_02220bf0(void *p);
extern void func_0204f794(int *out, int x, int y);
extern int _s32_div_f(int a, int b);
extern int func_020984e8(void);
extern void func_02098ff8(int a, int b);
extern void func_ov003_02224140(int a, int b, int c, int d);
extern void func_ov003_02221c9c(void);

extern int data_ov003_0223cf88[];
extern void *data_020e25d4;

typedef struct {
    char pad_00[8];
    u16 unk_08;
    char pad1[6];
    int unk_10, unk_14, unk_18, unk_1C, unk_20;
    char pad_24[0xc];
    int unk_30, unk_34, unk_38;
    char pad_3C[0x10];
    short unk_4C;
    char pad_4E[2];
    short unk_50;
    char pad_52[0x4e];
    unsigned char unk_A0;
} UnkStruct_02221ad8;

typedef struct {
    char pad_00[0x30];
    int unk_30;
    char pad1[8];
    int unk_3C;
} It;

void func_ov003_02221ad8(UnkStruct_02221ad8 *self)
{
    It it;
    int loc[3];
    int *g;
    int f3c;
    int t;

    func_02034270(&it, &self->unk_18, 0, 0);
    if (it.unk_30 != 0) {
        if (self->unk_4C == 0) {
            VEC_Add(&self->unk_18, &self->unk_30, &self->unk_18);
            f3c = it.unk_3C;
            if (self->unk_1C < f3c) {
                self->unk_34 = 0;
                g = data_ov003_0223cf88;
                g[0] = self->unk_18;
                g[1] = self->unk_1C;
                g[2] = self->unk_20;
                g[1] = f3c;
                func_02090c2c(0x45, g, 0, &data_020e25d4);
                func_02090c2c(0x4a, data_ov003_0223cf88, 0, &data_020e25d4);
                func_02090aa4(2, func_ov003_02221c9c);
                self->unk_4C = 1;
                self->unk_50 = 0xc;
                self->unk_1C = self->unk_1C - 0x2000;
                func_020ba31c(1);
            }
        } else {
            self->unk_50 = self->unk_50 - 1;
            if (self->unk_50 < 0) {
                func_020ba334(self->unk_50);
                func_ov003_02219930(&self->unk_18);
                self->unk_A0 = 0;
                func_ov003_02222860(self);
            }
        }
    } else if (self->unk_4C == 0) {
        VEC_Add(&self->unk_18, &self->unk_30, &self->unk_18);
        if (self->unk_1C < 0) {
            self->unk_1C = 0;
            self->unk_50 = func_ov003_02220bf0(&self->unk_10);
            func_0204f794(loc, self->unk_10, self->unk_14);
            t = _s32_div_f(loc[2] - self->unk_20, 8);
            self->unk_30 = _s32_div_f(loc[0] - self->unk_18, 8);
            self->unk_34 = 0x1000;
            self->unk_38 = t;
            self->unk_4C = 1;
            func_020ba31c(0);
        }
    } else {
        self->unk_34 = self->unk_34 - 0x400;
        VEC_Add(&self->unk_18, &self->unk_30, &self->unk_18);
        if (self->unk_1C < 0) {
            self->unk_1C = 0;
            self->unk_30 = 0;
            self->unk_34 = 0;
            self->unk_38 = 0;
            func_020ba334(0);
            if (self->unk_50 == 0) {
                if (self->unk_08 == 0x137b) {
                    func_02098ff8(func_020984e8(), 0x30);
                }
                func_ov003_02224140(self->unk_10, self->unk_14, self->unk_08, 0);
            }
            self->unk_A0 = 0;
            func_ov003_02222860(self);
        }
    }
    func_0203423c(&it);
}
