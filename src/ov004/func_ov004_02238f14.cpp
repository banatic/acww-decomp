/* func_ov004_02238f14 @ 0x02238f14, 0x5c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02238f14 {
    int a;
    ~UnkStruct_02238f14() {}
};

extern "C" {
extern void func_020e89dc(void *, int, int);
extern void func_ov004_02239bb4(void *, int, int);
}
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
