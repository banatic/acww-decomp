/* func_ov096_0229c560 @ 0x0229c560, 0xdc bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u8 pad_00[0xb5];
    u8 byte;
} UnkStruct_0229c560;

extern void func_ov096_0229c2dc(UnkStruct_0229c560 *self, int arg);
extern void func_ov096_0229c2ec(UnkStruct_0229c560 *self, int arg);
extern int func_ov096_0229f800(UnkStruct_0229c560 *self, int arg);
extern int func_ov096_0229f810(UnkStruct_0229c560 *self, int arg);
extern int func_ov096_0229f820(UnkStruct_0229c560 *self, int arg);
extern int func_ov096_0229f830(UnkStruct_0229c560 *self, int arg);
extern void func_ov096_0229c63c(UnkStruct_0229c560 *self, int a, int b);
extern void func_ov096_0229c7e0(UnkStruct_0229c560 *self, int a, int b);
extern void func_ov096_0229c888(UnkStruct_0229c560 *self, int a, int b);
extern void func_ov096_0229ca78(UnkStruct_0229c560 *self, int a, int b);
extern int func_ov002_0220889c(int arg);
extern int func_ov002_022088ac(int arg);

int func_ov096_0229c560(UnkStruct_0229c560 *self, int param2, int param3)
{
    u8 old = self->byte;
    func_ov096_0229c2dc(self, 0x30);
    if (param2 == 0) {
        return 0;
    }

    if (func_ov096_0229f830(self, self->byte)) {
        func_ov096_0229ca78(self, param2, param3);
    } else if (func_ov096_0229f820(self, self->byte)) {
        func_ov096_0229c888(self, param2, param3);
    } else if (func_ov096_0229f810(self, self->byte)) {
        func_ov096_0229c7e0(self, param2, param3);
    } else if (func_ov096_0229f800(self, self->byte)) {
        func_ov096_0229c63c(self, param2, param3);
    } else if (self->byte == 0x21) {
        if (func_ov002_0220889c(param2)) {
            self->byte = 0xa;
        } else if (func_ov002_022088ac(param2)) {
            self->byte = 0x18;
            func_ov096_0229c2ec(self, 0x10);
        }
    }

    if (old == self->byte) {
        return 0;
    } else {
        return 1;
    }
}
