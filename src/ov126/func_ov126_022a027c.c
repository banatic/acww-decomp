/* func_ov126_022a027c @ 0x022a027c, 0xb0 bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u8 pad_00[0xa8];
    u8 a8;
    u8 a9;
    u8 aa;
    u8 pad_AB[0x19c - 0xab];
    u8 sub19c;
    u8 pad_19D[0x4248 - 0x19d];
    u16 unk_4248;
} UnkStruct_022a027c;

extern int func_ov126_022a0740(UnkStruct_022a027c *self);
extern void func_ov126_022a06d8(UnkStruct_022a027c *self);
extern void func_ov126_022a0110(void);
extern void func_ov126_022a0168(UnkStruct_022a027c *self);
extern void func_ov126_022a08c4(UnkStruct_022a027c *self);
extern void func_ov095_0229b3ec(const void *p);
extern int func_ov095_0229b3a0(const void *p, const void *q, int _x);
extern void RtcSendPxiCommand(int cmd);

int func_ov126_022a027c(UnkStruct_022a027c *self, int b)
{
    if (func_ov126_022a0740(self)) {
        func_ov095_0229b3ec(&self->sub19c);
        func_ov126_022a06d8(self);
    } else if (self->a8) {
        if (func_ov095_0229b3a0(&self->sub19c, &self->unk_4248, self->a8) == 0) {
            self->a9 = self->a8;
            self->aa = self->a8 - 1;
            func_ov126_022a06d8(self);
        }
    } else if (self->unk_4248) {
        self->a9 = 0;
        self->aa = 1;
        func_ov126_022a06d8(self);
    } else {
        if (b) {
            // clang-format off
            asm {
                mov r0, self
            }
            // clang-format on
            func_ov126_022a0110();
        }
        return 0;
    }
    RtcSendPxiCommand(0x35);
    func_ov126_022a0168(self);
    func_ov126_022a08c4(self);
    return 1;
}