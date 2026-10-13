/* func_ov050_02260a68 @ 0x02260a68, 0x2f8 bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct VT2;
struct UnkStruct_02260a68_2 {
    struct VT2 *vt;
};
struct VT2 {
    void (*fn[8])(struct UnkStruct_02260a68_2 *);
};

struct UnkStruct_02260a68_3 {
    u8 pad_00[0x560];
    u8 unk_560;
    u8 pad_561[0x658 - 0x561];
    struct UnkStruct_02260a68_2 unk_658;
    u8 pad_65C[0x740 - 0x65c];
    u8 unk_740;
};

struct UnkStruct_02260a68 {
    u8 pad_00[0x64];
    int unk_64;
};
extern struct UnkStruct_02260a68 *data_020ccf94;

extern void func_0201c054(struct UnkStruct_02260a68_3 *self, int a, int b, int c);
extern int func_0201c0e0(struct UnkStruct_02260a68_3 *self);
extern int func_0201c014(struct UnkStruct_02260a68_3 *self);
extern int func_0201c040(struct UnkStruct_02260a68_3 *self, int *a, int *b);
extern int func_0201c2a4(struct UnkStruct_02260a68_3 *self, int a);
extern void func_ov050_02264834(struct UnkStruct_02260a68_3 *self, int a);
extern void func_02016108(struct UnkStruct_02260a68_2 *s, int a);
extern int func_ov050_02263638(struct UnkStruct_02260a68_2 *s);
extern void func_ov050_02263640(struct UnkStruct_02260a68_2 *s, int a);
extern int func_ov050_02260510(struct UnkStruct_02260a68_3 *self);
extern int func_020a7278(void);
extern int func_02073d90(struct UnkStruct_02260a68 *g);
extern short *func_0209d358(int a, int b);

void func_ov050_02260a68(struct UnkStruct_02260a68_3 *self, int sel, int v)
{
    switch (sel) {
        case 3:
            self->unk_560 = (u8) v;
            if (v != 4) {
                func_0201c054(self, 1, data_020ccf94->unk_64, v);
                func_ov050_02264834(self, 0xf);
            } else if (func_0201c0e0(self) != 0) {
                int k = data_020ccf94->unk_64;
                func_0201c054(self, 1, k, k);
                func_ov050_02264834(self, 0xf);
            }
            break;
        case 1:
            self->unk_560 = (u8) v;
            if (v != 4 && v != data_020ccf94->unk_64) {
                func_0201c054(self, 1, v, v);
                func_ov050_02264834(self, 9);
            } else {
                if (func_0201c0e0(self) != 0) {
                    struct UnkStruct_02260a68 *g = data_020ccf94;
                    int k = g->unk_64;
                    func_0201c054(self, 1, k, k);
                    self->unk_658.vt->fn[2](&self->unk_658);
                    func_02016108(&self->unk_658, func_0201c2a4(self, 4));
                    if (func_ov050_02263638(&self->unk_658) == 0 || func_ov050_02263638(&self->unk_658) == 0x11) {
                        func_ov050_02264834(self, 4);
                    } else if (func_ov050_02263638(&self->unk_658) == 1 || func_ov050_02263638(&self->unk_658) == 0x12 ||
                               func_ov050_02263638(&self->unk_658) == 6 || func_ov050_02263638(&self->unk_658) == 0x1d) {
                        func_ov050_02264834(self, 5);
                    } else if (func_02073d90(g) != 0 || *func_0209d358(0, 0x4a) != 0) {
                        self->unk_658.vt->fn[2](&self->unk_658);
                        func_02016108(&self->unk_658, func_0201c2a4(self, 4));
                        func_ov050_02264834(self, 4);
                    } else {
                        func_ov050_02264834(self, 0x10);
                    }
                }
            }
            break;
        case 0:
            self->unk_560 = (u8) v;
            if (v != 4 && v != data_020ccf94->unk_64) {
                func_0201c054(self, 1, v, v);
                func_ov050_02264834(self, 9);
            } else {
                if (func_0201c0e0(self) != 0) {
                    int k = data_020ccf94->unk_64;
                    func_0201c054(self, 1, k, k);
                    self->unk_658.vt->fn[2](&self->unk_658);
                    func_02016108(&self->unk_658, func_0201c2a4(self, 4));
                    if (func_ov050_02260510(self) != 0) {
                        func_ov050_02263640(&self->unk_658, 5);
                    } else {
                        func_ov050_02263640(&self->unk_658, 0x13);
                    }
                    func_ov050_02264834(self, 4);
                }
            }
            break;
        case 8:
            if (v == 4) {
                if (func_020a7278() != 0) {
                    struct UnkStruct_02260a68 *g = data_020ccf94;
                    func_0201c054(self, 1, g->unk_64, 4);
                    if (func_ov050_02263638(&self->unk_658) != 1 && func_ov050_02263638(&self->unk_658) != 0x12 &&
                        func_ov050_02263638(&self->unk_658) != 6 && func_ov050_02263638(&self->unk_658) != 0x1d) {
                        if (func_02073d90(g) != 0 || *func_0209d358(0, 0x4a) != 0) {
                            func_ov050_02264834(self, 0xd);
                        } else {
                            func_ov050_02264834(self, 1);
                        }
                    }
                    self->unk_740 = 0;
                } else {
                    func_0201c054(self, 1, 4, data_020ccf94->unk_64);
                    func_ov050_02264834(self, 8);
                }
            }
            break;
        case 4: {
            int a;
            int b;
            if (func_0201c014(self) == 0) {
                break;
            }
            if (func_0201c0e0(self) == 0) {
                break;
            }
            a = 4;
            b = 4;
            if (func_0201c040(self, &a, &b) == 0) {
                break;
            }
            if (v != 4) {
                if (v == b) {
                    goto ok;
                }
            }
            if (v != 4) {
                break;
            }
        ok:
            func_0201c054(self, 1, data_020ccf94->unk_64, 4);
            func_ov050_02264834(self, 0xd);
            break;
        }
    }
}
