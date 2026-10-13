/* func_ov004_02240490 @ 0x02240490, 0xa8 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_020644cc(int);
extern void func_ov004_02240f2c(void *, int, int, int, int, int, int);
extern void func_ov004_02242df8(void *, int);
extern void func_ov004_02242e84(void *);

void func_ov004_02240490(char *self)
{
    int r = (u8) func_020644cc(5);
    if (func_020644cc(0x64) > 0x32) {
        *(u8 *) (self + 0x170) = 0;
    } else {
        *(u8 *) (self + 0x170) = 1;
    }
    *(int *) (self + 0x4c) = r;
    func_ov004_02240f2c(self, 0x50, 0x50, 0, 0, 0, 1);
    func_ov004_02242df8(self + 0x2c8, r);
    func_ov004_02242e84(self);
    *(u8 *) (self + 0x50) = 0;
    if (func_020644cc(0x64) > 0x32) {
        *(int *) (self + 0x174) = 0x14 * (func_020644cc(9) + 4);
        *(short *) (self + 0x172) = 4;
    } else {
        *(int *) (self + 0x174) = 0x14 * (func_020644cc(3) + 2);
        *(short *) (self + 0x172) = 0x19;
    }
}
