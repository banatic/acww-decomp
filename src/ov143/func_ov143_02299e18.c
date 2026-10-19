/* func_ov143_02299e18 @ 0x02299e18, 0xc0 bytes, Thumb, module ov143
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02299e18 {
    u8 pad_00[0x9a];
    u16 unk_9A;
    u8 pad_9C[0xa0 - 0x9a - 2];
    u8 *unk_A0;
    u8 unk_A4;
    u8 unk_A5;
    u8 pad_A6[2];
    int unk_A8;
} UnkStruct_02299e18;

extern int func_0206fe60(void);
extern u8 data_021f6c54;
extern u8 func_ov143_022997d8(UnkStruct_02299e18 *self, u8 v);
extern unsigned char *func_ov002_02208098(UnkStruct_02299e18 *self, unsigned char value);
extern void func_0206e9ac(u8 v);
extern void func_ov143_02299ad4(UnkStruct_02299e18 *self);
extern void func_0200467c(int a);
extern void func_ov143_02299b2c(UnkStruct_02299e18 *self);
extern void func_ov143_0229a230(UnkStruct_02299e18 *self);
extern void func_ov143_0229a200(UnkStruct_02299e18 *self);
extern void func_ov143_0229a404(UnkStruct_02299e18 *self);
extern void func_ov143_0229a3e0(UnkStruct_02299e18 *self);

int func_ov143_02299e18(UnkStruct_02299e18 *self, unsigned int p)
{
    if (p <= 0xf) {
        self->unk_9A = (u16) p;
        self->unk_A4 = (u8) p;
        if (func_0206fe60() != 0) {
            self->unk_A8 = data_021f6c54;
            self->unk_A5 = func_ov143_022997d8(self, self->unk_A0[p]);
            func_ov002_02208098(self, 1);
        } else {
            func_ov002_02208098(self, 3);
        }
        func_0206e9ac(self->unk_A0[p]);
        return 1;
    }

    switch (p - 0x10) {
        case 0:
            func_ov143_02299ad4(self);
            func_0200467c(0x2a);
            return 1;
        case 1:
            func_ov143_02299b2c(self);
            return 1;
        case 2:
            func_ov143_0229a230(self);
            return 1;
        case 3:
            func_ov143_0229a200(self);
            return 1;
        case 4:
            func_ov143_0229a404(self);
            return 1;
        case 5:
            func_ov143_0229a3e0(self);
            return 1;
    }
    return 0;
}
