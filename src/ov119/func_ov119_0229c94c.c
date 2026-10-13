/* func_ov119_0229c94c @ 0x0229c94c, 0x1ac bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov119_0229a420(void *self, int);
extern int func_ov002_0220919c(void *p);
extern int func_0206fe54(int v);
extern void func_ov002_02209eb8(void *p);
extern void func_02088df8(int, const void *, int, void *, int, int, int, int, int, int, int, int);
extern void func_020896b8(int, const void *, int, void *, int, int, int);

extern u8 data_ov119_0229ccc0[];
extern void *data_ov119_0229cca8[];
extern u8 data_ov119_0229cdd8[];
extern u16 data_ov119_0229cbe8[];
extern u8 data_ov119_0229ce38[];
extern u8 data_ov119_0229ce08[];

typedef struct UnkStruct_0229c94c {
    u8 pad_00[0x94];
    void *ptr;     // 0x94
    u8 pad_98[2];  // 0x98
    s16 short9a;   // 0x9a
    u8 unk_9C;     // 0x9c
    u8 unk_9D;     // 0x9d
    u8 pad_9E[3];  // 0x9e
    u8 arr_a1[12]; // 0xa1
    u8 pad_AD[3];  // 0xad
    u8 unk_B0;     // 0xb0
} UnkStruct_0229c94c;

int func_ov119_0229c94c(UnkStruct_0229c94c *self)
{
    u8 *base;
    int i, h;
    int neg, zero;

    base = (u8 *) self->ptr + 0x60;

    if (func_ov119_0229a420(self, 1) == 0) {
        return 1;
    }

    if (func_0206fe54(func_ov002_0220919c((char *) self + 0xdc)) != 0) {
        func_ov002_02209eb8((char *) self + 0xda8);
    }

    func_02088df8(1, data_ov119_0229ccc0, 0x80, base, -1, 2, 0x1000, 0x1000, 0, -1, 0, 0);

    for (i = 0; i < 6; i++) {
        int v = (i == self->unk_9D) ? 5 : 4;
        func_02088df8(1, data_ov119_0229cca8[i], 0x80, base, v, 2, 0x1000, 0x1000, 0, -1, 0, 0);
    }

    func_02088df8(1, data_ov119_0229cdd8, 0x80, base, self->unk_B0, 2, 0x1000, 0x1000, 0, -1, 0, 0);

    h = 0x80;

    switch (self->unk_9C) {
        case 4:
            neg = -1;
            zero = 0;
            for (i = 0; i < 12; i++) {
                data_ov119_0229cbe8[2] =
                    (data_ov119_0229cbe8[2] & 0xfffffc00) | ((u16) ((self->arr_a1[i] << 1) + 0x1a0) & 0x3ff);
                func_020896b8(1, data_ov119_0229cbe8, h, base, neg, 2, zero);
                h += 0xe;
            }
            func_02088df8(1, data_ov119_0229ce38, 0x80, base, -1, 2, 0x1000, 0x1000, 0, -1, 0, 0);
            break;
        case 5:
            break;
        default:
            if (self->short9a != -1) {
                func_02088df8(1, data_ov119_0229ce08, 0x80, base + ((int) self->short9a << 4) - 0x10, -1, 2, 0x1000, 0x1000, 0,
                              -1, 0, 0);
            }
            break;
    }

    return 1;
}
