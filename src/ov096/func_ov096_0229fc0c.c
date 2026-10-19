/* func_ov096_0229fc0c @ 0x0229fc0c, 0x9c bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_0229fc0c {
    u8 pad_00[0xb6];
    u8 unk_B6;
    u8 pad_B7[0xc4 - 0xb7];
    u32 unk_C4;
} UnkStruct_0229fc0c;

extern int func_020436a8(u32);
extern int func_ov096_0229c2fc(UnkStruct_0229fc0c *, int);
extern int func_ov096_0229f7ac(UnkStruct_0229fc0c *, u8);
extern void func_ov094_0229aa58(void *, int);
extern void func_ov096_0229e6a0(UnkStruct_0229fc0c *);
extern void func_ov096_0229fb9c(UnkStruct_0229fc0c *);
extern void func_ov096_0229e82c(UnkStruct_0229fc0c *, int);
extern void func_ov096_0229f874(UnkStruct_0229fc0c *, int, int, int);
extern void func_0200467c(int);
extern void func_020431b8(u32);

void func_ov096_0229fc0c(UnkStruct_0229fc0c *self)
{
    int s = func_020436a8(self->unk_C4);
    switch (s) {
        case 1:
            if (func_ov096_0229c2fc(self, 0x1000) != 0) {
                int val = func_ov096_0229f7ac(self, self->unk_B6);
                func_ov094_0229aa58((char *) self + 0x358, val);
                func_ov096_0229fb9c(self);
            } else {
                func_ov096_0229e6a0(self);
                func_ov096_0229fb9c(self);
            }
            break;
        case 2:
            if (func_ov096_0229c2fc(self, 0x1000) == 0) {
                func_ov096_0229e82c(self, 1);
            }
            func_ov096_0229fb9c(self);
            func_ov096_0229f874(self, 8, 0xff, 0);
            func_0200467c(0x73);
            break;
        default:
            return;
    }
    func_020431b8(self->unk_C4);
    self->unk_C4 = -1;
}
