/* func_ov099_0229d698 @ 0x0229d698, 0x80 bytes, Thumb, module ov099
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov099_0229c95c(u8 *);
extern void func_ov099_0229cb70(u8 *);
extern int func_ov099_0229ceb8(u8 *, int, int, int);
extern int func_ov099_0229ce68(u8 *, int);
extern void func_ov099_0229cf48(u8 *, u8, int);
extern void func_ov099_0229d0f0(u8 *);
extern void func_ov099_0229cb20(u8 *);
extern u8 data_021fbdd8;

void func_ov099_0229d698(u8 *self)
{
    int x;

    func_ov099_0229c95c(self);
    func_ov099_0229cb70(self);
    x = func_ov099_0229ceb8(self, *(unsigned int *) (self + 0x27f8) + 8, *(unsigned int *) (self + 0x27fc) + 8, 0);

    if (x == 0x1d) {
        goto x_eq;
    }

    if (data_021fbdd8 != 0) {
        goto flag_nonzero;
    }

    if (func_ov099_0229ce68(self, x) == 0) {
        func_ov099_0229cf48(self, self[0x2906], 4);
    }
    func_ov099_0229d0f0(self);
    return;

flag_nonzero:
    func_ov099_0229cb20(self);
    return;

x_eq:
    if (data_021fbdd8 != 0) {
        return;
    }
    func_ov099_0229cf48(self, self[0x2906], 4);
}
