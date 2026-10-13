/* func_ov003_0222af74 @ 0x0222af74, 0x240 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} UnkStruct_0222af74;
typedef struct {
    char pad_00[8];
    UnkStruct_0222af74 v;
} UnkStruct_0222af74_2;
typedef struct {
    u8 b;
    u8 unk_01;
    char pad[10];
    u16 w;
    char pad_0E[6];
} UnkStruct_0222af74_3;
typedef struct {
    u8 *p;
    int pad;
} UnkStruct_0222af74_4;

typedef struct {
    char pad_00[0x7e];
    signed char unk_7E;
    char pad_7F[0x120 - 0x7f];
    UnkStruct_0222af74 unk_120;
    char pad_12C[0x138 - 0x12c];
    s16 unk_138;
    char pad_13A[2];
    int unk_13C;
    char pad_140[0x1ff - 0x140];
    u8 kind;
    char pad_200[0x225 - 0x200];
    u8 unk_225;
    char pad_226[1];
    signed char unk_227;
    char pad_228[0x22c - 0x228];
    UnkStruct_0222af74_2 *h;
} UnkStruct_0222af74_5;

extern UnkStruct_0222af74_3 data_ov003_0223c014[];
extern UnkStruct_0222af74_4 data_ov003_0223bf04[];
extern u8 data_020cb786[];
extern s16 func_0200322c(UnkStruct_0222af74 *a, UnkStruct_0222af74 *b);
extern void func_ov003_0222be78(UnkStruct_0222af74 *p, int a, int b);
extern void func_ov003_022277fc(UnkStruct_0222af74_5 *s, int n);
extern int func_ov003_0222799c(UnkStruct_0222af74 *p, UnkStruct_0222af74 *t, int a, int b, int c);
extern int func_ov003_0222793c(int a, int b);
extern void func_02095764(volatile u16 *t, int a);
extern void func_0206026c(UnkStruct_0222af74_2 *h, int a);

int func_ov003_0222af74(UnkStruct_0222af74_5 *self)
{
    UnkStruct_0222af74_2 *h;
    UnkStruct_0222af74 *tgt;
    int ok;
    u16 lo, hi;
    volatile u16 t;
    int sel;
    int *p13c;
    int spd;
    int ang;
    int r;

    h = self->h;
    if (h == 0) {
        return 0;
    }
    if (self->unk_227 == -1) {
        return 0;
    }
    tgt = &h->v;
    func_ov003_022277fc(self, 0x18);
    func_02095764(&t, self->unk_227);
    ok = 0;
    lo = t;
    hi = t;
    if (hi >= 0x1374 && lo <= 0x1374) {
        ok = 1;
    }
    if (ok != 0) {
        sel = 0;
    } else if (lo >= 0x1375 && lo <= 0x1375) {
        sel = 1;
    } else {
        return 0;
    }
    p13c = &self->unk_13C;
    if (*p13c >= data_ov003_0223bf04[sel].p[data_020cb786[self->unk_7E * 6]]) {
        *p13c = 0;
        func_0206026c(h, 4);
        return 0;
    }
    switch (self->unk_225) {
        case 6:
            spd = ((int) data_ov003_0223c014[self->kind].b << 12) / 100;
            ang = func_0200322c(&self->unk_120, tgt);
            func_ov003_0222be78(&self->unk_120, 0x180, ang);
            func_ov003_0222be78(&self->unk_120, 0xc0, (s16) (ang + 0x4000));
            if (func_ov003_0222799c(&self->unk_120, tgt, spd, spd, spd) != 0) {
                self->unk_225 = 8;
            } else {
                self->unk_225 = 7;
            }
            break;
        case 7:
            spd = ((int) data_ov003_0223c014[self->kind].b << 12) / 100;
            ang = func_0200322c(&self->unk_120, tgt);
            func_ov003_0222be78(&self->unk_120, 0x180, ang);
            func_ov003_0222be78(&self->unk_120, 0xc0, (s16) (ang - 0x4000));
            if (func_ov003_0222799c(&self->unk_120, tgt, spd, spd, spd) != 0) {
                self->unk_225 = 8;
            } else {
                self->unk_225 = 6;
            }
            break;
        case 8:
            spd = ((int) data_ov003_0223c014[self->kind].unk_01 << 12) / 100;
            func_ov003_0222be78(&self->unk_120, 0x180, func_0200322c(tgt, &self->unk_120));
            r = func_ov003_0222793c(0, 100);
            if (func_ov003_0222799c(&self->unk_120, tgt, spd, spd, spd) == 0) {
                if (r >= 0x46) {
                    self->unk_225 = 6;
                } else {
                    self->unk_225 = 9;
                }
            }
            break;
        case 9:
            if (func_ov003_0222793c(0, 100) <= 0x32) {
                self->unk_225 = 7;
            }
            break;
    }
    self->unk_138 = func_0200322c(&self->unk_120, tgt);
    return 1;
}
