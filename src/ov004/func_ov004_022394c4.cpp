/* func_ov004_022394c4 @ 0x022394c4, 0x60 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_022394c4 {
    int a;
    ~UnkStruct_022394c4() {}
};
extern "C" void func_ov004_022394c4(char *self, int a, int b, unsigned mode)
{
    UnkStruct_022394c4 t;
    int *p = (int *) (self + 0x1ac);
    if (mode == 0 || mode == 2) {
        a = *(int *) (self + 0x21c) * a;
        if (a >= b) {
            a = b;
        }
    } else if (mode == 1 || mode == 3) {
        a = *(int *) (self + 0x21c) * a;
        a = b - a;
        if (a <= 0) {
            a = 0;
        }
    }
    if (mode <= 1) {
        *p += a;
    } else if ((u8) (mode + 0xfe) <= 1) {
        *p -= a;
    }
}
