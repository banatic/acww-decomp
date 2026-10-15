/* func_ov003_0222b1b4 @ 0x0222b1b4, 0x274 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O1,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} UnkStruct_0222b1b4;
typedef struct {
    char pad_00[8];
    UnkStruct_0222b1b4 v;
} UnkStruct_0222b1b4_2;
typedef struct {
    u8 b;
    char pad_01[11];
    u16 w;
    char pad_0E[6];
} UnkStruct_0222b1b4_3;
typedef struct {
    int a, b;
} Pair;

typedef struct {
    char pad_00[0x7e];
    char unk_7E;
    char pad_7F[0x120 - 0x7f];
    UnkStruct_0222b1b4 unk_120;
    char pad_12C[0x138 - 0x12c];
    s16 unk_138;
    char pad_13A[2];
    int unk_13C;
    char pad_140[0x1fe - 0x140];
    u8 unk_1FE;
    u8 kind;
    char pad_200[0x224 - 0x200];
    u8 unk_224;
    u8 unk_225;
    char pad_226[0x22c - 0x226];
    UnkStruct_0222b1b4_2 *h;
    char pad_230[0x23d - 0x230];
    u8 unk_23D;
    char pad_23E[2];
    u8 unk_240;
} UnkStruct_0222b1b4_4;

extern UnkStruct_0222b1b4_3 data_ov003_0223c014[];
extern s16 func_0200322c(UnkStruct_0222b1b4 *a, UnkStruct_0222b1b4 *b);
extern void func_ov003_0222be78(UnkStruct_0222b1b4 *p, int a, int b);
extern void func_ov003_022277fc(UnkStruct_0222b1b4_4 *s, int n);
extern int func_ov003_0222799c(UnkStruct_0222b1b4 *p, UnkStruct_0222b1b4 *t, int a, int b, int c);
extern int func_ov003_0222793c(int a, int b);
extern void func_0206026c(UnkStruct_0222b1b4_2 *h, int a);
extern void func_02060480(UnkStruct_0222b1b4_2 *h);
extern int func_020044c0(UnkStruct_0222b1b4_4 *self, int a, int b, int c);
extern int func_02043368(int a, Pair *p, int c);
extern long long func_020ea940(UnkStruct_0222b1b4 *a, UnkStruct_0222b1b4 *b);
extern int FX_MulFunc(int a, int b);

int func_ov003_0222b1b4(UnkStruct_0222b1b4_4 *self)
{
    UnkStruct_0222b1b4 *tgt;
    UnkStruct_0222b1b4_2 *h;
    int ret;
    int base;
    int spd;
    int t;
    int a4;
    int ang, lim, spd5;
    Pair pr;
    long long d;

    ret = 0;
    h = self->h;
    if (h == 0) {
        return ret;
    }
    tgt = &h->v;
    if (self->unk_13C >= self->unk_240) {
        spd = ((int) data_ov003_0223c014[self->kind].b << 12) / 100;
        if (func_ov003_0222799c(&self->unk_120, tgt, spd, spd, spd) != 0) {
            self->unk_13C = 0;
            func_0206026c(h, 5);
            func_020044c0(self, 0x84f, 0x7f, 0);
            if (self->unk_7E == 0x38 || self->unk_7E == 0x39 || self->unk_7E == 0x3a) {
                pr.a = 0;
                pr.b = 0;
                if (func_02043368(0x10, &pr, 0) != 0) {
                    self->unk_224 = 4;
                    self->unk_225 = 6;
                    ret = 1;
                }
            } else {
                self->unk_224 = 4;
                self->unk_225 = 6;
                ret = 1;
            }
            return ret;
        }
    }
    base = (int) data_ov003_0223c014[self->kind].b << 12;
    switch (self->unk_225) {
        case 3:
            spd = base / 100;
            ang = self->unk_23D << 4;
            if (ang >= 0x100) {
                ang = 0x100;
            }
            func_ov003_0222be78(&self->unk_120, ang, func_0200322c(&self->unk_120, tgt));
            d = func_020ea940(&self->unk_120, tgt);
            if ((long long) FX_MulFunc(spd, spd) >= d) {
                self->unk_23D = 0;
                func_02060480(h);
                self->unk_225 = 4;
            }
            func_ov003_022277fc(self, 0x18);
            break;
        case 4:
            lim = func_ov003_0222793c(10, 20);
            if (func_ov003_0222793c(0, 100) < 0x32) {
                a4 = func_0200322c(tgt, &self->unk_120);
            } else {
                a4 = func_0200322c(&self->unk_120, tgt);
                if (func_ov003_0222793c(0, 100) < 5) {
                    func_02060480(h);
                }
            }
            func_ov003_0222be78(&self->unk_120, 0x100, a4);
            if (self->unk_23D > lim) {
                self->unk_23D = 0;
                self->unk_225 = 5;
            }
            break;
        case 5:
            spd5 = ((int) data_ov003_0223c014[self->kind].w << 12) / 100;
            ang = 0x100 - (self->unk_23D << 4);
            if (ang < 0) {
                ang = 0;
            }
            func_ov003_0222be78(&self->unk_120, ang, func_0200322c(tgt, &self->unk_120));
            if (ang == 0 || func_ov003_0222799c(&self->unk_120, tgt, spd5, spd5, spd5) == 0) {
                self->unk_23D = 0;
                self->unk_225 = 3;
            }
            func_ov003_022277fc(self, 0x10);
            break;
    }
    t = base >> 9;
    d = func_020ea940(&self->unk_120, tgt);
    if (d >= (long long) FX_MulFunc(t, t)) {
        self->unk_138 = func_0200322c(&self->unk_120, tgt);
    }
    self->unk_23D = self->unk_23D + 1;
    return 1;
}
