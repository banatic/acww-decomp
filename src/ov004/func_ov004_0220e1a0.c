/* func_ov004_0220e1a0 @ 0x0220e1a0, 0x66 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov004_0220e448(void *self);
extern u16 func_0204bc50(void *b, int a);
extern void func_ov004_0220e224(void *self, void *a, void *b);
extern void *func_021077e8(int a);
extern int func_0209d320(void *a);
extern int func_0209d324(void *a);
extern void func_02056064(void *p, int a);
extern int func_020561cc(void *p, int a);
extern void func_ov004_0220e028(void *self);

int func_ov004_0220e1a0(char *self, void *a, void *b, int d)
{
    void *h;

    *(u8 *) (self + 0x72) = (u8) d;
    if (func_ov004_0220e448(self)) {
        return 1;
    }
    *(u16 *) (self + 0x70) = func_0204bc50(b, 0);
    func_ov004_0220e224(self, a, b);
    h = func_021077e8(*(int *) self);
    func_02056064(h, func_0209d320(a));
    *(int *) (self + 0xc) = func_020561cc(h, func_0209d324(a));
    func_ov004_0220e028(self);
    return 1;
}
