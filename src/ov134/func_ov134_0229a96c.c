/* func_ov134_0229a96c @ 0x0229a96c, 0xd0 bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u8 pad_00[0xa0];
    u8 unk_A0;
    u8 pad_A1[0x10];
    u8 unk_B1;
    u8 pad_B2[0x9];
    u8 unk_BB;
    u8 unk_BC;
    u8 unk_BD;
    u8 pad_BE[0x870 - 0xbe];
} UnkStruct_0229a96c;

extern int func_0209de88(u8 a, u8 b, u8 c);
extern int func_ov134_022995a0(UnkStruct_0229a96c *self, int n);
extern int func_ov134_022995b0(UnkStruct_0229a96c *self, int n);
extern int func_ov134_0229aaa8(UnkStruct_0229a96c *self, int n);
extern int func_ov134_0229aa78(UnkStruct_0229a96c *self, int n);
extern int func_ov134_0229aa4c(UnkStruct_0229a96c *self, int n);
extern int func_ov134_0229aa3c(UnkStruct_0229a96c *self, int n);
extern void func_0206fdd4(void *dst, int a, int b, int c, int d, int e);

void func_ov134_0229a96c(UnkStruct_0229a96c *self, int a, int b)
{
    u8 com = self->unk_A0;

    if (com == 1) {
        if (a == 0) {
            return;
        }

        if (a == 1 || a == 2 || a == 5) {
            if (b == 3) {
                b = 4;
            }
            if (b == 5) {
                b = 7;
            }
        }
    } else if (com == 2) {
        if (a != 1 && a != 2) {
            return;
        }
    }

    if (a == 5 && b == 3) {
        if (func_0209de88(self->unk_BD, self->unk_BC, self->unk_BB) == 0) {
            b = 8;
            func_ov134_022995b0(self, b);
        } else {
            func_ov134_022995a0(self, 8);
        }
    }

    if (self->unk_B1 == a && b == 3) {
        b = 5;
    }

    func_0206fdd4((u8 *) self + 0x870, func_ov134_0229aaa8(self, a), func_ov134_0229aa78(self, a),
                  func_ov134_0229aa4c(self, a), func_ov134_0229aa3c(self, a), b);

    func_ov134_022995b0(self, 2);
}
