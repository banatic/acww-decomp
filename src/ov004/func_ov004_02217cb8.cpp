/* func_ov004_02217cb8 @ 0x02217cb8, 0x40 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02217cb8 {
    char pad_00[0xec];
};
struct UnkStruct_02217cb8_2 {
    void *vt;
};

struct Node {
    int unk_00;
    int unk_04;
};

struct UnkStruct_02217cb8_3 : UnkStruct_02217cb8, UnkStruct_02217cb8_2 {
    char pad_F0[0x12c - 0xf0];
    Node *node;
    char pad_130[0x846 - 0x130];
    u8 kind;
};

extern "C" int func_ov004_0222c110(int kind, int flag);
extern "C" void func_0203ee08(UnkStruct_02217cb8_3 *d, UnkStruct_02217cb8_2 *b);
extern "C" void func_0203e020(UnkStruct_02217cb8_3 *d);

extern "C" void func_ov004_02217cb8(UnkStruct_02217cb8_3 *self)
{
    if (self->node != 0 && self->node->unk_04 == 0) {
        func_ov004_0222c110(self->kind, 0);
        func_0203ee08(self, self);
        func_0203e020(self);
    }
}
