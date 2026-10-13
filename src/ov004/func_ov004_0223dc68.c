/* func_ov004_0223dc68 @ 0x0223dc68, 0x64 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov004_0223e3e0(void *self);
extern void func_ov004_0223e3d4(void *self, int v);
extern void func_02004290(void *self, int arg);
extern void func_020042a0(void *self, int arg);

void func_ov004_0223dc68(char *self, int mode)
{
    switch (mode) {
        case 0:
            *(u8 *) (self + 0x263) = 1;
            if (func_ov004_0223e3e0(self) == 2) {
                func_02004290(self + 0x114, 0x225);
            } else {
                func_ov004_0223e3d4(self, 1);
            }
            break;
        case 1:
            func_020042a0(self + 0x114, 0x226);
            break;
        default:
            func_020042a0(self + 0x114, 0x227);
            break;
    }
}
