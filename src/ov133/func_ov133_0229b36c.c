/* func_ov133_0229b36c @ 0x0229b36c, 0x8c bytes, Thumb, module ov133
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

#define CUR(s) (*(vu8 *) ((s) + 0x9f))

extern int func_ov002_022088ac(void *pad);
extern int func_ov002_0220889c(void *pad);
extern int func_ov133_0229b0d4(u8 *self);
extern int func_ov133_0229ba84(u8 *self);
extern int func_ov133_0229ba34(u8 *self);
extern void func_ov002_0220a0b4(u8 *p, int a, int b);

int func_ov133_0229b36c(u8 *self, void *pad)
{
    u8 prev = CUR(self);
    int a;
    int b;

    if (func_ov002_022088ac(pad)) {
        if (CUR(self) != 0) {
            CUR(self) = CUR(self) - 1;
        }
    } else if (func_ov002_0220889c(pad)) {
        if (func_ov133_0229b0d4(self) > CUR(self)) {
            CUR(self) = CUR(self) + 1;
        }
    }
    if (prev != CUR(self)) {
        a = func_ov133_0229ba84(self);
        b = func_ov133_0229ba34(self);
        func_ov002_0220a0b4(self + 0x11c, a, b);
        return 1;
    }
    return 0;
}
