/* func_ov004_02242180 @ 0x02242180, 0xa8 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *func_ov004_02241ba8(void *self);
extern int func_ov004_02244e38(void *self, void *v);
extern int func_ov004_02244c20(void *self);
extern short func_ov004_022447c0(int a, void *t);
extern short func_ov004_0224105c(int a);
extern int func_020644cc(int);

void func_ov004_02242180(char *self)
{
    void *t = func_ov004_02241ba8(self);
    if (func_ov004_02244e38(self, self + 0x2c8) != 0) {
        *(short *) (self + 0x172) = 3;
    } else if (func_ov004_02244c20(self) != 0) {
        if (t != 0) {
            *(short *) (self + 0xac) = func_ov004_022447c0(*(short *) (self + 0x192), t);
        } else {
            *(short *) (self + 0xac) = func_ov004_0224105c(0x10);
        }
        *(u8 *) (self + 0x9a) = 0;
        *(short *) (self + 0x172) = 0x19;
        if (*(u8 *) (self + 0x22) != 0) {
            *(int *) (self + 0x174) = (short) (0x14 * (func_020644cc(6) + 1));
        } else {
            *(int *) (self + 0x174) = (short) (0x14 * (func_020644cc(0x1e) + 5));
        }
    }
}
