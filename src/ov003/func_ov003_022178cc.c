/* func_ov003_022178cc @ 0x022178cc, 0x16c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_02056f28(void *a, int b);
extern void func_020108cc(void *self, int a, int b);
extern int func_02056f94(void *a);
extern void func_0200f27c(void *self, int a);
extern void func_0200f268(void *self, int a);
extern u32 func_02008258(void *self, u32 a);
extern void func_0200c3b0(void *self, int a, int b, int c);
extern void func_0203e110(void);
extern void func_0200d4e8(void *self, int a, int b, int c);
extern void func_ov003_022188d0(void *self, u32 a, u32 b, s16 c, int d, int e);
extern void func_ov003_022186cc(void *self, int a, u32 b, u32 c, s16 d, int e, int f);

typedef struct UnkStruct_022178cc {
    s32 state;  // 0x00
    u32 unk_04; // 0x04
    u32 unk_08; // 0x08
    s32 unk_0C; // 0x0c
    s16 unk_10; // 0x10
    u8 flags;   // 0x12
} UnkStruct_022178cc;

typedef struct UnkStruct_022178cc_2 {
    u8 pad_00[0x2d0];       // 0x000
    u8 unk_2D0[4];          // 0x2d0
    u8 pad_2D4[4];          // 0x2d4
    u32 unk_2D8;            // 0x2d8
    u8 pad_2DC[0x2c8];      // 0x2dc
    u32 unk_5A4;            // 0x5a4
    u8 pad_5A8[0x22c];      // 0x5a8
    UnkStruct_022178cc sub; // 0x7d4
    u8 pad_7E8[8];          // 0x7e8
    u32 unk_7F0;            // 0x7f0
    u8 pad_7F4[8];          // 0x7f4
    u32 unk_7FC;            // 0x7fc
} UnkStruct_022178cc_2;

void func_ov003_022178cc(UnkStruct_022178cc_2 *self)
{
    UnkStruct_022178cc *sub = &self->sub;
    s32 *pCounter = &sub->unk_0C;
    s32 r7;

    if ((sub->flags & 3) == 2) {
        r7 = 0x1000;
        if (((self->unk_2D8 << 4) >> 16) < 8) {
            if (func_02056f28(&self->unk_2D0, 7) != 0) {
                func_020108cc(self, 0, 7);
            }
            if (*pCounter != 0x1000) {
                *pCounter += 0x249;
                if (*pCounter > 0x1000) {
                    *pCounter = 0x1000;
                }
            }
        }
    } else {
        r7 = 0;
        if (*pCounter != 0) {
            *pCounter -= 0x249;
            if (*pCounter < 0) {
                *pCounter = 0;
            }
        }
    }

    self->unk_5A4 = sub->unk_0C;

    if (func_02056f94(&self->unk_2D0) != 0 && r7 == *pCounter) {
        func_0200f27c(self, 1);
        switch (sub->state) {
            case 0x38:
                func_0200f268(self, 0);
                func_ov003_022188d0(self, sub->unk_04, sub->unk_08, sub->unk_10, 6, -1);
                break;
            case 0x39:
                func_0200f268(self, 0);
                func_ov003_022186cc(self, ((u32) (sub->flags & 0xc) << 22) >> 24, sub->unk_04, sub->unk_08, sub->unk_10, 6,
                                    -1);
                break;
            case 0x10:
                func_0200f268(self, 0);
                self->unk_7FC = func_02008258(self, self->unk_7F0);
                func_0200c3b0(self, 3, 5, -1);
                break;
            case 2:
                func_0203e110();
                self->unk_7FC = func_02008258(self, self->unk_7F0);
                func_0200d4e8(self, 3, 1, -1);
                break;
            default:
                break;
        }
    }
}
