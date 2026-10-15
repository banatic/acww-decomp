/* func_ov003_0222b428 @ 0x0222b428, 0x1a0 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} UnkStruct_0222b428;
typedef struct {
    char pad_00[8];
    UnkStruct_0222b428 v;
} UnkStruct_0222b428_2;
typedef struct {
    u8 b;
    char pad_01[11];
    u16 w;
    char pad_0E[6];
} UnkStruct_0222b428_3;

typedef struct {
    char pad_00[0x120];
    UnkStruct_0222b428 unk_120;
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
    UnkStruct_0222b428_2 *h;
    char pad_230[0x23d - 0x230];
    u8 unk_23D;
    char pad_23E[2];
    u8 unk_240;
} UnkStruct_0222b428_4;

extern UnkStruct_0222b428_3 data_ov003_0223c014[];
extern s16 func_0200322c(UnkStruct_0222b428 *a, UnkStruct_0222b428 *b);
extern void func_ov003_0222be78(UnkStruct_0222b428 *p, int a, int b);
extern void func_ov003_022277fc(UnkStruct_0222b428_4 *s, int n);
extern int func_ov003_0222799c(UnkStruct_0222b428 *p, UnkStruct_0222b428 *t, int a, int b, int c);
extern int func_ov003_0222793c(int a, int b);
extern int func_ov003_0222791c(int a, int b);
extern void func_02060480(UnkStruct_0222b428_2 *h);
extern int func_ov003_0222a398(UnkStruct_0222b428_4 *s);
extern int func_ov003_0222a784(UnkStruct_0222b428_4 *s);

int func_ov003_0222b428(UnkStruct_0222b428_4 *self)
{
    UnkStruct_0222b428 *tgt;
    UnkStruct_0222b428_2 *h;
    int ang, spd;
    int lim, t;

    h = self->h;
    if (h == 0) {
        return 0;
    }
    tgt = &h->v;
    switch (self->unk_225) {
        case 0:
            spd = ((int) data_ov003_0223c014[self->kind].b << 12) / 100;
            ang = self->unk_23D << 4;
            if (ang >= 0x100) {
                ang = 0x100;
            }
            self->unk_138 = func_0200322c(&self->unk_120, tgt);
            func_ov003_0222be78(&self->unk_120, ang, self->unk_138);
            if (func_ov003_0222799c(&self->unk_120, tgt, spd, spd, spd) != 0) {
                self->unk_23D = 0;
                func_02060480(h);
                self->unk_225 = 1;
            }
            break;
        case 1:
            lim = func_ov003_0222793c(10, 15);
            if (func_ov003_0222793c(0, 100) < 0x32) {
                self->unk_138 = func_0200322c(tgt, &self->unk_120);
            } else {
                self->unk_138 = func_0200322c(&self->unk_120, tgt);
            }
            func_ov003_0222be78(&self->unk_120, 0x100, self->unk_138);
            self->unk_138 = func_0200322c(&self->unk_120, tgt);
            if (self->unk_23D > lim) {
                self->unk_23D = 0;
                t = func_ov003_0222791c(1, 2);
                self->unk_138 = self->unk_138 + (s16) (0x1554 * t);
                self->unk_225 = 2;
            }
            break;
        case 2:
            spd = ((int) data_ov003_0223c014[self->kind].w << 12) / 100;
            func_ov003_0222be78(&self->unk_120, 0x14c, self->unk_138);
            if (func_ov003_0222799c(&self->unk_120, tgt, spd, spd, spd) == 0) {
                if (func_ov003_0222a398(self) == 0) {
                    func_ov003_0222a784(self);
                }
            }
            break;
    }
    func_ov003_022277fc(self, 0x18);
    self->unk_23D = self->unk_23D + 1;
    return 1;
}
