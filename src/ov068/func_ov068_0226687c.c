/* func_ov068_0226687c @ 0x0226687c, 0xec bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0226687c {
    u32 unk_00;
    u32 unk_04;
    u8 unk_08;
};

extern int func_ov068_0226cf8c(void *other);
extern int func_0201ac28(void *addr, void *other);
extern int func_ov068_02266b6c(struct UnkStruct_0226687c *self, char *buf, u32 *local2, void *addr, u32 arg5);
extern void func_ov068_02266b04(struct UnkStruct_0226687c *self, void *other, u32 local2, int r3, char *buf);
extern int func_ov068_02266a24(struct UnkStruct_0226687c *self, char *buf, u32 *local2, void *addr, u32 arg5);
extern void func_ov068_022669c4(struct UnkStruct_0226687c *self, void *other, u32 local2, int r3, char *buf);
extern void func_ov068_02266c1c(struct UnkStruct_0226687c *self);
extern void func_ov068_02266aa0(struct UnkStruct_0226687c *self, void *other);
extern void func_ov068_02266968(struct UnkStruct_0226687c *self, void *other);
extern void func_ov068_02266c70(struct UnkStruct_0226687c *self, void *other);

void func_ov068_0226687c(struct UnkStruct_0226687c *self, void *other)
{
    u32 local2;
    char buf[12];
    u8 b;
    int ret;

    if (self->unk_00 != 0) {
        return;
    }

    b = self->unk_08;
    if (b == *(u8 *) ((char *) other + 0x3b0)) {
        switch (b) {
            case 1:
                if ((unsigned) func_ov068_0226cf8c(other) > 1) {
                    return;
                }
                if (func_0201ac28((char *) other + 0x3b0, other) != 0) {
                    return;
                }
                local2 = -1;
                ret = func_ov068_02266b6c(self, buf, &local2, (char *) other + 0x5c, 0x5000);
                if (ret != -1) {
                    func_ov068_02266b04(self, other, local2, ret, buf);
                } else {
                    local2 = -1;
                    ret = func_ov068_02266a24(self, buf, &local2, (char *) other + 0x5c, 0x5000);
                    if (ret != -1) {
                        func_ov068_022669c4(self, other, local2, ret, buf);
                    }
                }
                break;
            case 3:
                if (func_0201ac28((char *) other + 0x3b0, other) != 0) {
                    func_ov068_02266c1c(self);
                }
                switch (self->unk_04) {
                    case 0:
                        func_ov068_02266aa0(self, other);
                        break;
                    case 1:
                        func_ov068_02266968(self, other);
                        break;
                    default:
                        func_ov068_02266c70(self, other);
                        break;
                }
                break;
        }
    } else {
        self->unk_00 = 1;
        self->unk_04 = 3;
    }
}
