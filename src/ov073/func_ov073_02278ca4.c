/* func_ov073_02278ca4 @ 0x02278ca4, 0x64 bytes, Thumb, module ov073
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02278ca4 {
    char pad_00[0x1e];
    u8 unk_1E;
    char pad_1F[0x40 - 0x1f];
    int unk_40;
    char pad_44[0xc8 - 0x44];
    u8 unk_C8;
} UnkStruct_02278ca4;

extern void func_0208b520(void);
extern void func_020157c8(UnkStruct_02278ca4 *self, int a, int b);
extern int func_02015828(UnkStruct_02278ca4 *self, int a);
extern void func_ov073_02278f4c(UnkStruct_02278ca4 *self, int a);
extern void func_0206844c(int h, u8 *p, int k);
extern int data_ov073_02279a10;

void func_ov073_02278ca4(UnkStruct_02278ca4 *self)
{
    u8 arg;
    int code;
    int k;

    k = (int) &data_ov073_02279a10;
    code = 0xff;
    switch (self->unk_1E) {
        case 0x12:
            func_0208b520();
            func_020157c8(self, 0x3a, 0);
            func_02015828(self, 2);
            func_ov073_02278f4c(self, 0);
            break;
        case 0x15:
            if (self->unk_C8 != 0) {
                code = 0x1a;
            } else {
                code = 0x16;
            }
            break;
    }
    if (code != 0xff) {
        arg = (u8) code;
        func_0206844c(self->unk_40, &arg, k);
    }
}
