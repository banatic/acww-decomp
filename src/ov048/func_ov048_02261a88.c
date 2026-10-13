/* func_ov048_02261a88 @ 0x02261a88, 0x70 bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02261a88 {
    char pad_00[0x40];
    int unk_40;
    char pad_44[0xae - 0x44];
    u8 unk_AE;
} UnkStruct_02261a88;

extern u8 func_ov048_022609fc(UnkStruct_02261a88 *self);
extern void func_0206844c(int h, u8 *p, int k);
extern int data_ov048_02263d20;

void func_ov048_02261a88(UnkStruct_02261a88 *self, int mode, int v)
{
    u8 a;
    u8 b;
    u8 c;

    if (mode == 0) {
        self->unk_AE = (u8) v;
        if (*((u8 *) self + 0x811) != 0) {
            a = self->unk_AE;
            func_0206844c(self->unk_40, &a, data_ov048_02263d20);
        } else {
            b = 0x6a;
            func_0206844c(self->unk_40, &b, data_ov048_02263d20);
        }
    }
    if (mode == 1) {
        c = func_ov048_022609fc(self);
        func_0206844c(self->unk_40, &c, data_ov048_02263d20);
    }
}
