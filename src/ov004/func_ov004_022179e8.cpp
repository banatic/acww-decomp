/* func_ov004_022179e8 @ 0x022179e8, 0x40 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_022179e8 {
    char pad_00[0xec];
};
struct UnkStruct_022179e8_2 {
    void *vt;
};

struct UnkStruct_022179e8_3 : UnkStruct_022179e8, UnkStruct_022179e8_2 {
    char pad_F0[0x84c - 0xf0];
    u16 ctr;
};

extern "C" void func_0203ee08(UnkStruct_022179e8_3 *d, UnkStruct_022179e8_2 *b);
extern "C" int func_0203e020(UnkStruct_022179e8_3 *d);
extern "C" void func_020ee470(UnkStruct_022179e8_3 *d);

extern "C" void func_ov004_022179e8(UnkStruct_022179e8_3 *self)
{
    if (self->ctr < 0x16) {
        self->ctr++;
    }
    if (self->ctr == 0x16) {
        func_0203ee08(self, self);
        func_0203e020(self);
        func_020ee470(self);
    }
}
