/* func_ov098_022a2a0c @ 0x022a2a0c, 0xbc bytes, Thumb, module ov098
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_022a2a0c {
    u8 pad_00[0xb6];
    u8 unk_B6;
    u8 pad_B7[0x0d];
    int unk_C4;
    u8 pad_C8[0x2d58];
    int unk_2E20;
    int unk_2E24;
} UnkStruct_022a2a0c;

typedef struct Global {
    u8 pad_00[0x64];
    void *unk_64;
} Global;

extern Global *data_020ccf94;
extern int func_ov096_0229f0dc(UnkStruct_022a2a0c *self, u8 byte);
extern int func_ov098_022a2bfc(UnkStruct_022a2a0c *self);
extern int func_02043db4(void *a, u32 *b, int c, int d, int e);
extern int func_02043634(void *a, int b, int c);
extern void func_ov096_0229fb9c(UnkStruct_022a2a0c *self);
extern void func_ov096_0229f874(UnkStruct_022a2a0c *self, int a, int b, int c);
extern void RtcSendPxiCommand(int cmd);
extern void func_ov002_02208098(UnkStruct_022a2a0c *self, int val);
extern void func_ov096_0229c2ec(UnkStruct_022a2a0c *self, int val);

void func_ov098_022a2a0c(UnkStruct_022a2a0c *self)
{
    u32 arr[2];
    int x;
    int ret;
    int ret2;

    x = func_ov096_0229f0dc(self, self->unk_B6);
    if (func_ov098_022a2bfc(self) != 0) {
        arr[0] = self->unk_2E20;
        arr[1] = self->unk_2E24;
        ret = func_02043db4(data_020ccf94->unk_64, arr, 2, 0, x);
        self->unk_C4 = ret;
        if (self->unk_C4 != -1) {
            func_ov002_02208098(self, 0x2d);
            return;
        }
    }
    ret2 = func_02043634(data_020ccf94->unk_64, 0x18, x);
    self->unk_C4 = ret2;
    if (self->unk_C4 == -1) {
        func_ov096_0229fb9c(self);
        func_ov096_0229f874(self, 8, 0xff, 0);
        RtcSendPxiCommand(0x73);
    } else {
        func_ov002_02208098(self, 0x29);
        func_ov096_0229c2ec(self, 0x1000);
    }
}
