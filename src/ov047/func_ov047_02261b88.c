/* func_ov047_02261b88 @ 0x02261b88, 0x78 bytes, Thumb, module ov047
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02261b88 {
    char pad_00[0x40];
    int unk_40;
    char pad_44[0xc8 - 0x44];
    int unk_C8;
    char pad_CC[0xce - 0xcc];
    u16 unk_CE;
} UnkStruct_02261b88;

extern int func_0206fc6c(void);
extern int func_0206fc8c(void);
extern int func_0209a034(int a);
extern int func_02015330(UnkStruct_02261b88 *self, u16 *p, int a, int b, int c);
extern int func_020155cc(UnkStruct_02261b88 *self);
extern void func_ov047_02261f74(UnkStruct_02261b88 *self, int a);
extern void func_0206844c(int h, u8 *p, int k);
extern int data_ov047_02262fc0;

void func_ov047_02261b88(UnkStruct_02261b88 *self)
{
    int h;
    u8 code;

    h = self->unk_40;
    code = 0x22;
    if (func_0206fc6c() != 0) {
        self->unk_C8 = func_0206fc8c();
        self->unk_CE = (u16) func_0209a034(self->unk_C8);
        func_02015330(self, &self->unk_CE, 0, 0xa, 0);
        code = 0x19;
    } else {
        self->unk_CE = 0xfff1;
        func_020155cc(self);
    }
    func_ov047_02261f74(self, 4);
    func_0206844c(h, &code, (int) &data_ov047_02262fc0);
}
