/* func_ov074_02278d44 @ 0x02278d44, 0xa4 bytes, Thumb, module ov074
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02278d44 {
    char pad_00[0x1e];
    u8 unk_1E;
    char pad_1F[0x40 - 0x1f];
    int unk_40;
    char pad_44[0xb0 - 0x44];
    char *unk_B0;
} UnkStruct_02278d44;

extern void func_ov074_02278a90(char *a, char *b);
extern void func_020157c8(UnkStruct_02278d44 *self, int a, int b);
extern void func_02015828(UnkStruct_02278d44 *self, int a);
extern void func_ov074_022790b4(UnkStruct_02278d44 *self, int a);
extern void func_0206844c(int h, u8 *p, int k);
extern int data_ov074_02279d14;

void func_ov074_02278d44(UnkStruct_02278d44 *self)
{
    u8 arg;
    int code;
    int k;

    k = (int) &data_ov074_02279d14;
    code = 0xff;
    switch (self->unk_1E) {
        case 9:
        case 10:
        case 11:
        case 12:
            code = 0xd;
            break;
        case 14:
            func_ov074_02278a90(self->unk_B0 + 0x714, self->unk_B0 + 0xec);
            func_020157c8(self, 3, 0);
            func_02015828(self, 2);
            func_ov074_022790b4(self, 0);
            break;
        case 0x1c:
            func_020157c8(self, 0x14, 0);
            func_02015828(self, 2);
            func_ov074_022790b4(self, 1);
            break;
    }
    if (code != 0xff) {
        arg = (u8) code;
        func_0206844c(self->unk_40, &arg, k);
    }
}
