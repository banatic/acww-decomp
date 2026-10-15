/* func_020f6ff4 @ 0x020f6ff4, 0x60 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_020f6ff4 {
    u32 unk_00;
    u32 unk_04;
    u16 unk_08;
    u8 unk_0A;
} UnkStruct_020f6ff4;

extern void func_020f6f3c(UnkStruct_020f6ff4 *self);
extern int func_020eed18(UnkStruct_020f6ff4 *self, int zero);
extern int func_020eedb8(int arg0, u16 arg1, UnkStruct_020f6ff4 *self);

void func_020f6ff4(UnkStruct_020f6ff4 *self, u32 arg2)
{
    u32 flag;

    func_020f6f3c(self);
    flag = (self->unk_00 != 0);
    if (flag != 0) {
        func_020eed18(self, 0);
    }
    self->unk_04 = arg2;
    self->unk_0A = 1;
    func_020eedb8(0, self->unk_08, self);
}
