/* func_ov096_0229ff54 @ 0x0229ff54, 0x8c bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern u32 func_ov096_0229f290(void *self, int x);
extern u32 func_ov096_0229f200(void *self, int x);
extern void func_ov096_0229c434(void *self);
extern int func_ov096_0229e2fc(void *self, u32 b, u32 w);
extern u16 func_ov096_0229e3b0(void *self, u32 b, u32 w);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov094_02299d7c(void *ptr, int x);
extern unsigned char data_020e54a8;

typedef struct {
    u8 pad_00[0xa4];
    u32 unk_A4;
    u32 unk_A8;
    u16 unk_AC;
    u8 pad_AE[0xc0 - 0xac - 2];
    u8 unk_C0;
} UnkStruct_0229ff54;

void func_ov096_0229ff54(UnkStruct_0229ff54 *self)
{
    u8 b;
    unsigned int flag;

    self->unk_A4 = func_ov096_0229f290(self, 0x24);
    self->unk_A8 = func_ov096_0229f200(self, 0x24);
    b = self->unk_C0;
    if (b == 5) {
        flag = (data_020e54a8 == 0) ? 1 : 0;
        if (flag == 0) {
            goto skip;
        }
    }
    func_ov096_0229c434(self);
skip:
    if (func_ov096_0229e2fc(self, b, self->unk_AC) != 0) {
        func_ov002_02208098((void *) (self), 0x26);
        self->unk_AC = func_ov096_0229e3b0(self, b, self->unk_AC);
        func_ov094_02299d7c((char *) self + 0xde0, 1);
    }
}
