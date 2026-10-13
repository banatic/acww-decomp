/* func_ov003_0222aba4 @ 0x0222aba4, 0x188 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} UnkStruct_0222aba4;
typedef struct {
    char pad_00[8];
    UnkStruct_0222aba4 v;
} UnkStruct_0222aba4_2;
typedef struct {
    volatile u16 id;
    u16 pad_02;
    int pad_04;
} UnkStruct_0222aba4_3;

typedef struct {
    char pad_00[0x7e];
    s8 unk_7E;
    char pad_7F[0x138 - 0x7f];
    s16 unk_138;
    char pad_13A[2];
    int unk_13C;
    char pad_140[0x1ff - 0x140];
    u8 kind;
    char pad_200[0x224 - 0x200];
    u8 unk_224;
    u8 unk_225;
    char pad_226[1];
    s8 unk_227;
    char pad_228[0x22c - 0x228];
    UnkStruct_0222aba4_2 *h;
    UnkStruct_0222aba4 unk_230;
    char pad_23C[2];
    u8 unk_23E;
    u8 unk_23F;
} UnkStruct_0222aba4_4;

extern u8 data_021fbdd8;
extern u8 *data_ov003_0223bf04[];
extern u8 data_020cb786[];
extern u8 data_ov003_0223c016[];
extern u8 data_ov003_0223c017[];

extern void func_ov003_0222a784(UnkStruct_0222aba4_4 *s);
extern void func_02095764(UnkStruct_0222aba4_3 *w, int n);
extern void func_0206026c(UnkStruct_0222aba4_2 *h, int n);
extern int func_ov003_0222793c(int a, int b);
extern int func_ov003_0222a398(UnkStruct_0222aba4_4 *s);

int func_ov003_0222aba4(UnkStruct_0222aba4_4 *self)
{
    UnkStruct_0222aba4_3 w;
    UnkStruct_0222aba4_2 *h;
    int ret;
    unsigned int ok;
    int idx;
    u16 lo, hi;
    int v;
    UnkStruct_0222aba4 *sv;
    UnkStruct_0222aba4 *dv;

    ret = 0;
    if (self == 0) {
        return ret;
    }
    h = self->h;
    if (h == 0) {
        func_ov003_0222a784(self);
        return ret;
    }
    switch (self->unk_224) {
        case 4:
            func_02095764(&w, self->unk_227);
            ok = 0;
            lo = w.id;
            hi = w.id;
            if (hi >= 0x1374 && lo <= 0x1374) {
                ok = 1;
            }
            if (ok) {
                idx = 0;
            } else if (lo >= 0x1375 && lo <= 0x1375) {
                idx = 1;
            } else {
                func_ov003_0222a784(self);
                return 0;
            }
            if (data_021fbdd8 == 0) {
                if (self->unk_13C > data_ov003_0223bf04[idx * 2][data_020cb786[6 * self->unk_7E]] - 1) {
                    func_ov003_0222a784(self);
                    return 0;
                }
            }
            self->unk_224 = 5;
            self->unk_225 = 0xa;
            self->unk_13C = 0;
            func_0206026c(h, 6);
            if (func_ov003_0222793c(0, 2) != 0) {
                v = 1;
            } else {
                v = 0;
            }
            self->unk_23E = v;
            self->unk_23F = func_ov003_0222793c(data_ov003_0223c016[20 * self->kind], data_ov003_0223c017[20 * self->kind]);
            sv = &h->v;
            dv = &self->unk_230;
            dv->x = h->v.x;
            dv->y = sv->y;
            dv->z = sv->z;
            if (self->unk_23E != 0) {
                self->unk_138 = self->unk_138 - 0x4000;
            } else {
                self->unk_138 = self->unk_138 + 0x4000;
            }
            ret = 1;
            break;
        case 6:
            break;
        case 3:
            func_ov003_0222a784(self);
            break;
        default:
            if (func_ov003_0222a398(self) == 0) {
                func_ov003_0222a784(self);
            }
            break;
    }
    return ret;
}
