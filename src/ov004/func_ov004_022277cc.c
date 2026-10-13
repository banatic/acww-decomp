/* func_ov004_022277cc @ 0x022277cc, 0x4c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_022277cc {
    u8 pad_00[0x800];
    int room;
};

extern int data_020ccf94;
extern int func_02073908(int a, int b);
extern void func_ov004_022278fc(struct UnkStruct_022277cc *self);
extern void func_ov004_02227858(struct UnkStruct_022277cc *self);
extern void func_ov004_02227818(struct UnkStruct_022277cc *self);
extern int func_02010f6c(struct UnkStruct_022277cc *self);
extern void func_ov004_02227888(struct UnkStruct_022277cc *self, int a);

void func_ov004_022277cc(struct UnkStruct_022277cc *self)
{
    if (func_02073908(data_020ccf94, self->room)) {
        func_ov004_022278fc(self);
        func_ov004_02227858(self);
        func_ov004_02227818(self);
    } else {
        func_ov004_02227888(self, func_02010f6c(self));
        func_ov004_02227858(self);
    }
}
