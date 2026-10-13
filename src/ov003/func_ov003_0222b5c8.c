/* func_ov003_0222b5c8 @ 0x0222b5c8, 0x15c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} UnkStruct_0222b5c8;
typedef struct {
    char pad_00[8];
    UnkStruct_0222b5c8 v;
} UnkStruct_0222b5c8_2;
typedef struct {
    u8 b;
    char pad_01[19];
} UnkStruct_0222b5c8_3;

typedef struct {
    char pad_00[0x120];
    UnkStruct_0222b5c8 unk_120;
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
    UnkStruct_0222b5c8_2 *h;
    char pad_230[0x23d - 0x230];
    u8 unk_23D;
    char pad_23E[2];
    u8 unk_240;
} UnkStruct_0222b5c8_4;

extern UnkStruct_0222b5c8_3 data_ov003_0223c014[];
extern s16 func_0200322c(UnkStruct_0222b5c8 *a, UnkStruct_0222b5c8 *b);
extern void func_ov003_0222be78(UnkStruct_0222b5c8 *p, int a, int b);
extern void func_ov003_022277fc(UnkStruct_0222b5c8_4 *s, int n);
extern int func_ov003_0222799c(UnkStruct_0222b5c8 *p, UnkStruct_0222b5c8 *t, int a, int b, int c);
extern int func_ov003_0222793c(int a, int b);
extern void func_0204f818(int *x, int *z, UnkStruct_0222b5c8 *t);
extern int func_02031b5c(int x, int z);

int func_ov003_0222b5c8(UnkStruct_0222b5c8_4 *self)
{
    UnkStruct_0222b5c8 *tgt;
    UnkStruct_0222b5c8_2 *h;
    int spd, ang, r, thr;
    int px, pz;

    h = self->h;
    if (h == 0) {
        return 0;
    }
    tgt = &h->v;
    spd = ((int) data_ov003_0223c014[self->kind].b << 12) / 100;
    ang = self->unk_23D << 4;
    if (ang >= 0x100) {
        ang = 0x100;
    }
    self->unk_138 = func_0200322c(&self->unk_120, tgt);
    func_ov003_0222be78(&self->unk_120, ang, self->unk_138);
    func_ov003_022277fc(self, 0x18);
    if (func_ov003_0222799c(&self->unk_120, tgt, spd, spd, spd) != 0) {
        r = func_ov003_0222793c(0, 100);
        thr = 0x5f;
        func_0204f818(&px, &pz, tgt);
        switch (self->unk_1FE) {
            case 0:
            case 1:
            case 2:
            case 3:
                if (func_02031b5c(px, pz) == 1) {
                    thr = 100;
                }
                break;
            case 4:
                break;
            case 5:
            case 6:
                if (func_02031b5c(px, pz) == 2) {
                    thr = 100;
                }
                break;
        }
        if (r <= thr) {
            self->unk_240 = func_ov003_0222793c(4, 0xb4);
            self->unk_13C = 0;
            self->unk_23D = 0;
            self->unk_225 = 3;
            self->unk_224 = 3;
            self->unk_138 = func_0200322c(&self->unk_120, tgt);
        } else {
            self->unk_23D = 0;
            self->unk_225 = 0;
            self->unk_224 = 2;
            self->unk_138 = func_0200322c(&self->unk_120, tgt);
        }
    }
    self->unk_23D = self->unk_23D + 1;
    return 1;
}
