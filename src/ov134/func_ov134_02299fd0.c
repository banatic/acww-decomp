/* func_ov134_02299fd0 @ 0x02299fd0, 0x1e4 bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int unk_00;
    char pad_04[4];
    u8 unk_08[0x10];
    char pad_18[0xa4 - 0x18];
    u8 unk_A4;
    u8 unk_A5;
    char pad_A6[0xab - 0xa6];
    u8 unk_AB;
    u8 unk_AC;
    char pad_AD[0x1870 - 0xad];
    u16 unk_1870[0x400];
    u16 unk_2070[0x400];
} UnkStruct_02299fd0;
extern void MIi_CpuCopy16(void *, void *, int); // func_021173fc
extern int func_ov134_0229aa6c(UnkStruct_02299fd0 *, u8);
extern int func_ov134_02299bcc(UnkStruct_02299fd0 *, int);
extern void func_0206fdd4(void *, int, int, int, int, int);
extern void func_ov134_0229b5ac(UnkStruct_02299fd0 *, u8, int, int, int, int, int);
extern void func_ov134_022995b0(UnkStruct_02299fd0 *, int);
void func_ov134_02299fd0(UnkStruct_02299fd0 *self)
{
    int jt;
    int t;

    int i;
    int start;
    u16 *p;

    int n;
    int e;
    int j;
    u8 v;
    int c;
    int d;
    int col;
    int u;
    MIi_CpuCopy16(self->unk_1870, self->unk_2070, 0x800);
    d = self->unk_AB - self->unk_00;
    func_ov134_0229aa6c(self, self->unk_A5);
    start = 8 - func_ov134_0229aa6c(self, self->unk_A5);
    if (d > 0) {
        d += 0xf;
        col = (0x10 - (d >> 4)) * 2;
        p = (u16 *) (((char *) self->unk_2070) + (col << 6));
        for (; col < 0x20; col++) {
            for (j = start; j < 8; j++) {
                p[j] = 0x3074;
            }

            p += 0x20;
        }
    }
    n = (self->unk_00 - self->unk_AB) >> 4;
    for (i = 0; i < 0x10; i++) {
        t = i + n;
        c = t & 0xf;
        if ((t >= 0) && (t < self->unk_AC)) {
            if (func_ov134_02299bcc(self, t) != 0) {
                func_0206fdd4(self->unk_2070, start, c * 2, 7, (c * 2) + 1, 6);
            }
            if (t != self->unk_08[c]) {
                self->unk_08[c] = (u8) t;
                v = self->unk_A5;
                if (v == 0) {
                    t += 0x7d0;
                }
                v = (u8) (v + 0xff);
                if (v <= 1) {
                    t++;
                }
                func_ov134_0229b5ac(self, self->unk_A4, (c << 4) + 0x80, 8, t, 0xf, 0xe);
            }
        }
    }

    u = self->unk_AC;
    e = self->unk_AB - self->unk_00;
    e = e + (u << 4);
    if (e < 0xc0) {
        d = ((0xcf - e) >> 4) * 2;
        jt = (u * 2) & 0x1f;
        for (i = 0; i < d; i++) {
            p = (u16 *) (((char *) self->unk_2070) + (jt << 6));
            for (j = start; j < 8; j++) {
                p[j] = 0x3074;
            }

            jt = (jt + 1) & 0x1f;
        }
    }
    col = (((self->unk_00 - self->unk_AB) + 0x20) & 0xff) >> 3;
    for (c = 0; c < 5; c++) {
        p = (u16 *) (((char *) self->unk_2070) + (col << 6));
        for (jt = 0; jt < 10; jt++) {
            p[jt] = 0x10;
        }

        p[0x1f] = 0x10;
        col = (col - 1) & 0x1f;
    }

    col = (((self->unk_00 - self->unk_AB) + 0xb0) & 0xff) >> 3;
    for (c = 0; c < 3; c++) {
        p = (u16 *) (((char *) self->unk_2070) + (col << 6));
        for (jt = 0; jt < 10; jt++) {
            p[jt] = 0x10;
        }

        p[0x1f] = 0x10;
        col = (col + 1) & 0x1f;
    }

    func_ov134_022995b0(self, 1);
}
