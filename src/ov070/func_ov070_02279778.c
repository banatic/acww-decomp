/* func_ov070_02279778 @ 0x02279778, 0xa8 bytes, Thumb, module ov070
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02279778 {
    char pad_00[0x40];
    int unk_40;
    char pad_44[0xb4 - 0x44];
    int unk_B4;
    char pad_B8[0xc0 - 0xb8];
    int unk_C0;
} UnkStruct_02279778;

extern int func_0206fc6c(void);
extern int func_0206f83c(void);
extern void func_0201b420(int a, int b);
extern void func_0208b514(void);
extern int func_0208602c(void);
extern void func_020860f0(int a, int b);
extern void func_0206844c(int h, u8 *p, int k);
extern int data_ov070_02279d58;

void func_ov070_02279778(UnkStruct_02279778 *self)
{
    u8 code;
    int h;
    int v;

    h = self->unk_40;
    code = 0x4b;
    self->unk_C0 = 0;
    if (func_0206fc6c() != 0) {
        self->unk_C0 = func_0206f83c();
        code = 0x2d;
        v = self->unk_C0;
        if (v > 1000 && v <= 2000) {
            code = 0x2e;
        } else if (v > 2000 && v <= 4000) {
            code = 0x2f;
        } else if (v > 4000) {
            code = 0x30;
        }
        func_0201b420(self->unk_B4, self->unk_C0);
    } else {
        func_0208b514();
        func_020860f0(func_0208602c(), 0xa);
    }
    func_0206844c(h, &code, (int) &data_ov070_02279d58);
}
