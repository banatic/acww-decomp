/* func_ov004_022396a0 @ 0x022396a0, 0x60 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_022396a0 {
    int a;
    ~UnkStruct_022396a0() {}
};
extern "C" void func_020e8a94(void *, int, int, int);

extern "C" void func_ov004_022396a0(char *self)
{
    UnkStruct_022396a0 t;
    u8 v = *(u8 *) (self + 0x1ee);
    if ((u8) (v + 0xff) <= 1) {
        return;
    }
    if (v == 3) {
        func_020e8a94(self + 0x1c4, (s16) (0xffffe557 * *(s8 *) (self + 0x1ca)), 3, 0x222);
    } else if (v == 5) {
        func_020e8a94(self + 0x1c4, 0, 3, 0x222);
    }
}
