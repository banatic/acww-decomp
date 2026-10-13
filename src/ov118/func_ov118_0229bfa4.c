/* func_ov118_0229bfa4 @ 0x0229bfa4, 0xcc bytes, Thumb, module ov118
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov118_0229add4(void *self);
extern void func_ov118_0229ad24(void *self);
extern void func_ov118_0229a450(void *self, int flag);
extern void func_ov118_0229aad8(void *self);
extern int func_ov118_0229a460(void *self, int flag);
extern void func_ov118_0229b778(void *self);
extern void func_ov118_0229a440(void *self, int flag);
extern void func_0200284c(int a, int b, int c);
extern int func_020b9bbc(void *a, void *b, int c, int d, int e);

typedef struct {
    u8 pad_00[0x98];
    u16 unk_98;
    u8 pad_9A[0xa3 - 0x9a];
    u8 unk_A3;
    u8 pad_A4[0xb4 - 0xa4];
    u8 unk_B4[1];
    u8 pad_B5[0xd8 - 0xb5];
    u8 unk_D8[1];
    u8 pad_D9[0x724 - 0xd9];
    u8 unk_724[1];
    u8 pad_725[0xf24 - 0x725];
    u8 unk_F24[1];
} UnkStruct_0229bfa4;

void func_ov118_0229bfa4(UnkStruct_0229bfa4 *self)
{
    if (func_ov118_0229add4(self)) {
        func_ov118_0229ad24(self);
        func_0200284c(6, 0, self->unk_98 - 0x50);
        if (self->unk_A3 != (self->unk_98 >> 4)) {
            func_ov118_0229a450(self, 0x80);
        }
    }

    func_ov118_0229aad8(self);

    if (func_ov118_0229a460(self, 0x80) != 0) {
        func_ov118_0229b778(self);
        func_ov118_0229a440(self, 0x80);
    }

    if (func_ov118_0229a460(self, 0x20) != 0) {
        if (func_020b9bbc(&self->unk_D8, &self->unk_724, 4, 0x800, 0) != 0) {
            func_ov118_0229a440(self, 0x20);
        }
    }

    if (func_ov118_0229a460(self, 2) != 0) {
        if (func_020b9bbc(&self->unk_B4, &self->unk_F24, 6, 0x800, 0) != 0) {
            func_ov118_0229a440(self, 2);
        }
    }
}
