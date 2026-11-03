/* aquarium_fish_classes_6: 2 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02238f14 @ 0x02238f14, 0x5c bytes, Thumb
 * func_ov004_02238eb0 @ 0x02238eb0, 0x64 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_02238f14 {
    int a;
    ~UnkStruct_02238f14() {}
};

extern "C" {
extern int func_020e89dc(void *, int, int);
extern int func_ov004_02239bb4(void *, int, int);
}

struct UnkStruct_02238eb0 {
    int a;
    ~UnkStruct_02238eb0() {}
};

extern "C" void func_ov004_02238f14(char *self)
{
    UnkStruct_02238f14 t;
    int v = *(int *) (self + 0x158) << 1;
    if (v > 0x7b) {
        v = 0x7b;
        *(u8 *) (self + 0x281) = 3;
        *(int *) (self + 0x158) = 0;
    }
    func_020e89dc(self + 0x1c0, *(s16 *) (self + 0x1ec), 0x2d8);
    func_ov004_02239bb4(self + 0x1a8, v, *(s16 *) (self + 0x1c0));
}

extern "C" void func_ov004_02238eb0(char *self)
{
    UnkStruct_02238eb0 t;
    int v = 0x7b - (*(int *) (self + 0x158) << 1);
    if (v < 0) {
        v = 0;
        *(u8 *) (self + 0x281) = 0;
        *(int *) (self + 0x158) = 0;
        *(u8 *) (self + 0x1ee) = 2;
    }
    func_020e89dc(self + 0x1c0, *(s16 *) (self + 0x1ec), 0x2d8);
    func_ov004_02239bb4(self + 0x1a8, v, *(s16 *) (self + 0x1c0));
}
