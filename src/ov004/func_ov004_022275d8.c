/* func_ov004_022275d8 @ 0x022275d8, 0x4c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_022275d8 {
    u8 pad_00[0x800];
    int room;
};

extern int data_020ccf94;
extern int func_02073908(int a, int b);
extern void func_ov004_02227708(struct UnkStruct_022275d8 *self);
extern void func_ov004_02227664(struct UnkStruct_022275d8 *self);
extern void func_ov004_02227624(struct UnkStruct_022275d8 *self);
extern int func_02010f6c(struct UnkStruct_022275d8 *self);
extern void func_ov004_02227694(struct UnkStruct_022275d8 *self, int a);

void func_ov004_022275d8(struct UnkStruct_022275d8 *self)
{
    if (func_02073908(data_020ccf94, self->room)) {
        func_ov004_02227708(self);
        func_ov004_02227664(self);
        func_ov004_02227624(self);
    } else {
        func_ov004_02227694(self, func_02010f6c(self));
        func_ov004_02227664(self);
    }
}
