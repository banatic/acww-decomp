/* func_ov051_022608b4 @ 0x022608b4, 0x74 bytes, Thumb, module ov051
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_022608b4 {
    char pad_00[0x40];
    int unk_40;
} UnkStruct_022608b4;

extern int func_020a12ac(void);
extern u8 func_ov051_022605e8(UnkStruct_022608b4 *self, int k);
extern void func_0206844c(int h, u8 *p, int k);
extern int data_ov051_022615c0;

void func_ov051_022608b4(UnkStruct_022608b4 *self, int mode)
{
    u8 a;
    u8 b;
    u8 c;

    switch (mode) {
        case 0:
            if (func_020a12ac() != 0) {
                a = func_ov051_022605e8(self, 0x15);
                func_0206844c(self->unk_40, &a, data_ov051_022615c0);
            } else {
                b = func_ov051_022605e8(self, 0x19);
                func_0206844c(self->unk_40, &b, data_ov051_022615c0);
            }
            break;
        case 1:
            c = func_ov051_022605e8(self, 0x13);
            func_0206844c(self->unk_40, &c, data_ov051_022615c0);
            break;
    }
}
