/* func_ov003_02215fd8 @ 0x02215fd8, 0xa8 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02215fd8_2 {
    u8 pad_00[4];
    u32 unk_04;
};

struct UnkStruct_02215fd8 {
    u8 pad_00[0x12c];
    struct UnkStruct_02215fd8_2 *unk_12C;
    u8 pad_130[0x7d4 - 0x130];
    u8 state;
    u8 pad_7D5[0x7f0 - 0x7d5];
    u32 unk_7F0;
    u8 pad_7F4[0x7fc - 0x7f4];
    u32 unk_7FC;
    u32 unk_800;
    u8 pad_804[0x81c - 0x804];
    u32 unk_81C;
};

extern void func_0203ee08(void *a, void *b);
extern void func_0200f268(void *a, int b);
extern int func_0203e19c(void);
extern u32 func_02008258(void *a, u32 b);
extern int func_02095694(int a, u32 b);
extern unsigned int *func_0200f27c(void *a, int b);
extern int func_0200d4e8(void *a, int b, int c, int d);
extern int func_0203b144(void);

void func_ov003_02215fd8(struct UnkStruct_02215fd8 *self)
{
    u8 state = self->state;
    switch (state) {
        case 0:
            if (self->unk_12C != 0 && self->unk_12C->unk_04 != 0) {
                self->state = 1;
                self->unk_81C = 0xc;
            }
            break;
        case 1:
            if (self->unk_12C != 0 && self->unk_12C->unk_04 == 0) {
                char *ptr = (char *) self;
                if (self != 0) {
                    ptr += 0xec;
                }
                func_0203ee08(self, ptr);
                func_0200f268(self, 0x11);
                func_0203e19c();
                self->unk_7FC = func_02008258(self, self->unk_7F0);
                func_02095694(0, self->unk_800);
                func_0200f27c(self, 0);
                func_0200d4e8(self, 3, 1, -1);
                func_0203b144();
            }
            break;
        default:
            break;
    }
}
