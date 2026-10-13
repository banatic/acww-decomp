/* func_ov098_022a30a4 @ 0x022a30a4, 0x134 bytes, Thumb, module ov098
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov002_02208d4c(void *w, int a, int b);
extern int func_ov098_022a2fc0(void *self, int a);
extern int func_ov098_022a2bfc(void *self);

void func_ov098_022a30a4(char *self, u16 id)
{
    u16 v;
    int f;
    u16 a0, a1;

    v = id;

    f = 0;
    a0 = *(volatile u16 *) &v;
    a1 = *(volatile u16 *) &v;
    if (a1 >= 0x12b0 && a0 <= 0x12e7) {
        f = 1;
    }
    if (f != 0 || (a0 >= 0x12e8 && a0 <= 0x131f)) {
        func_ov002_02208d4c(self + 0x294c, 0x1b, 0x21);
    }

    f = 0;
    a0 = *(volatile u16 *) &v;
    a1 = *(volatile u16 *) &v;
    if (a1 >= 0x12b0 && a0 <= 0x12e7) {
        f = 1;
    }
    if (f != 0) {
        func_ov002_02208d4c(self + 0x294c, 8, 0x15);
        return;
    }
    if (a0 >= 0x12e8 && a0 <= 0x131f) {
        if (func_ov098_022a2fc0(self, 0) != 0) {
            func_ov002_02208d4c(self + 0x294c, 8, 0x18);
        }
        return;
    }
    if ((a0 >= 0x137c && a0 <= 0x137c) || (a0 >= 0x1408 && a0 <= 0x1428) || (a0 >= 0x1471 && a0 <= 0x1491) ||
        (a0 >= 0x14fe && a0 <= 0x1517) || (a0 >= 0x151d && a0 <= 0x151e) || (a0 >= 0x1567 && a0 <= 0x1567)) {
        func_ov002_02208d4c(self + 0x294c, 6, 0x17);
        return;
    }
    if (func_ov098_022a2bfc(self) != 0) {
        func_ov002_02208d4c(self + 0x294c, 7, 0x16);
    }
}
