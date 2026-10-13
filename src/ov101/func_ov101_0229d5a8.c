/* func_ov101_0229d5a8 @ 0x0229d5a8, 0x7c bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov101_0229ca2c(u8 *);
extern void func_ov101_0229cb44(u8 *);
extern int func_ov101_0229cdd0(u8 *, int, int, int);
extern int func_ov101_0229cd80(u8 *, int);
extern void func_ov101_0229ce50(u8 *, u8, int);
extern void func_ov101_0229cf80(u8 *);
extern void func_ov101_0229cb18(u8 *);
extern u8 data_021fbdd8;

void func_ov101_0229d5a8(u8 *self)
{
    int x;

    func_ov101_0229ca2c(self);
    func_ov101_0229cb44(self);
    x = func_ov101_0229cdd0(self, *(unsigned int *) (self + 0xa4) + 8, *(unsigned int *) (self + 0xa8) + 8, 0);

    if (x == 0x10) {
        goto x_eq;
    }

    if (data_021fbdd8 != 0) {
        goto flag_nonzero;
    }

    if (func_ov101_0229cd80(self, x) == 0) {
        func_ov101_0229ce50(self, self[0xb2], 4);
    }
    func_ov101_0229cf80(self);
    return;

flag_nonzero:
    func_ov101_0229cb18(self);
    return;

x_eq:
    if (data_021fbdd8 != 0) {
        return;
    }
    func_ov101_0229ce50(self, self[0xb2], 4);
}
