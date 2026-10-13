/* func_ov004_02228888 @ 0x02228888, 0x40 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02228888 {
    u8 pad_00[0x5c];
    u8 sub[4];
};

extern u8 data_020e54a8;
extern void func_ov004_0223a6d8(void *p);
extern void func_02010f5c(struct UnkStruct_02228888 *self);
extern void func_02010d64(struct UnkStruct_02228888 *self);
extern void func_ov004_022288c8(struct UnkStruct_02228888 *self);
extern void func_ov004_02228978(struct UnkStruct_02228888 *self);

void func_ov004_02228888(struct UnkStruct_02228888 *self)
{
    int on;

    on = !(data_020e54a8 != 1);
    if (on != 0) {
        func_ov004_0223a6d8(&self->sub);
    }
    func_02010f5c(self);
    func_02010d64(self);
    func_ov004_022288c8(self);
    func_ov004_02228978(self);
}
