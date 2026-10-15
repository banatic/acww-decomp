/* func_ov114_0229cf58 @ 0x0229cf58, 0xd8 bytes, Thumb, module ov114
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    char pad_00[0x81a];
    char unk_81A;
    char pad_81B[0x129c - 0x81b];
    int unk_129C;
    int unk_12A0;
    char pad_12A4[0x12b0 - 0x12a4];
    u8 unk_12B0;
    u8 unk_12B1;
    char pad_12B2[3];
    u8 unk_12B5;
} UnkStruct_0229cf58;

extern void *func_ov114_0229cd70(UnkStruct_0229cf58 *self);
extern int func_020a7bf4(void *p, int idx);
extern int func_020a8a34(void *h, int a);
extern void func_020a8c1c(void *h);
extern void func_02070adc(void *h, int a, int b, int c, int d, int e, int f);
extern void func_02070a04(void *h, int a, int b);

void func_ov114_0229cf58(UnkStruct_0229cf58 *self)
{
    void *h[3];
    void *cur;
    int i;
    int idx;
    int y;
    int r;

    idx = self->unk_12B5 * 3;
    h[0] = func_ov114_0229cd70(self);
    h[1] = func_ov114_0229cd70(self);
    h[2] = func_ov114_0229cd70(self);
    y = 0xbb;
    for (i = 0; i < 3; i++) {
        r = func_020a7bf4(&self->unk_81A, idx);
        if (r != 0) {
            cur = h[i];
            func_020a8a34(cur, r);
        } else {
            cur = h[i];
            func_020a8c1c(cur);
        }
        func_02070adc(cur, self->unk_12B1, y, 0xd, 2, 3, 0);
        func_02070a04(cur, 0, 0);
        idx++;
        y += 0x1a;
    }
    if (self->unk_12B5 == 0) {
        self->unk_12A0 = 4;
    } else {
        self->unk_12A0 = 5;
    }
    if (self->unk_12B5 + 1 >= self->unk_12B0) {
        self->unk_129C = 4;
    } else {
        self->unk_129C = 5;
    }
}
