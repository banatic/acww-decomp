/* func_ov003_0220fe4c @ 0x0220fe4c, 0xc8 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_02073908(void *g, u32 val);
extern u32 func_02008258(void *self, u32 val);
extern int func_ov003_0220fda0(void *self, u32 *arr, int a, int b);
extern int func_0200d4e8(void *self, int a, int b, int c);
extern void *data_020ccf94;

typedef struct UnkStruct_0220fe4c {
    u32 unk_00;   // 0x00
    u32 unk_04;   // 0x04
    u32 unk_08;   // 0x08
    u8 pad_0C[2]; // 0x0c
    u8 unk_0E;    // 0x0e
    u8 unk_0F;    // 0x0f
} UnkStruct_0220fe4c;

typedef struct UnkStruct_0220fe4c_2 {
    u8 pad_00[0x7d4];
    UnkStruct_0220fe4c sub; // 0x7d4
    u8 pad_7E4[0x7f0 - 0x7e4];
    u32 unk_7F0; // 0x7f0
    u32 unk_7F4; // 0x7f4
    u32 unk_7F8; // 0x7f8
    u32 unk_7FC; // 0x7fc
    u32 unk_800; // 0x800
    u8 pad_804[0x818 - 0x804];
    u32 unk_818; // 0x818
} UnkStruct_0220fe4c_2;

void func_ov003_0220fe4c(UnkStruct_0220fe4c_2 *self)
{
    UnkStruct_0220fe4c *p = &self->sub;
    void *g = data_020ccf94;

    if (func_02073908(g, self->unk_800) != 0) {
        if (p->unk_0F == 0) {
            if (self->unk_818 == 1) {
                p->unk_0F = 1;
            } else if (self->unk_818 == 2) {
                p->unk_0F = 2;
            }
        }
    }

    if (p->unk_0E < 2) {
        p->unk_0E++;
        return;
    }

    if (func_02073908(g, self->unk_800) == 0) {
        self->unk_7FC = func_02008258(self, self->unk_7F0);
    }

    switch (p->unk_0F) {
        case 0:
            break;
        case 1: {
            u32 tmp[3];
            tmp[0] = p->unk_00;
            tmp[1] = p->unk_04;
            tmp[2] = p->unk_08;
            func_ov003_0220fda0(self, tmp, 6, -1);
            break;
        }
        case 2: {
            self->unk_7FC = func_02008258(self, self->unk_7F0);
            func_0200d4e8(self, 3, 1, -1);
            break;
        }
    }
}
