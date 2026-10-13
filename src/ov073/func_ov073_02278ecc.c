/* func_ov073_02278ecc @ 0x02278ecc, 0x80 bytes, Thumb, module ov073
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02278ecc {
    char pad_00[0x40];
    int unk_40;
    char pad_44[0xc0 - 0x44];
    int unk_C0;
    int unk_C4;
} UnkStruct_02278ecc;

extern int func_0206fc6c(void);
extern int func_0206f83c(void);
extern int func_020874c4(void *p);
extern void func_02015fb0(UnkStruct_02278ecc *self, int a, int b, int c, int d, int e);
extern void func_0206844c(int h, u8 *p, int k);
extern int data_021f3b0c;
extern int data_ov073_02279a10;

void func_ov073_02278ecc(UnkStruct_02278ecc *self)
{
    u8 code;
    int h;
    int n;

    h = self->unk_40;
    code = 0x11;
    if (func_0206fc6c() != 0) {
        n = func_0206f83c() * 10;
        self->unk_C4 = func_0206f83c();
        self->unk_C0 = func_020874c4(&data_021f3b0c) * n;
        func_02015fb0(self, n, 1, 3, 0, 0);
        func_02015fb0(self, self->unk_C0, 2, 0xa, 0, 0);
        code = 0x13;
    }
    func_0206844c(h, &code, (int) &data_ov073_02279a10);
}
