/* func_ov142_0229a3c0 @ 0x0229a3c0, 0x9c bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov142_02299668(char *self, unsigned int a1);
extern void func_0206fdd4(char *a, int b, int c, int d, int e, int f);
extern int func_020b9bbc(char *a, char *b, int c, int d, int e);
extern void func_ov142_02299648(char *self, int a1);

void func_ov142_0229a3c0(char *self)
{
    int v;
    s16 a, b;
    int d, t;

    if (func_ov142_02299668(self, 0x200) != 0) {
        v = 5;
    } else {
        v = 3;
    }

    func_0206fdd4(self + 0x2060, 0, 0, 0x1f, 0x1f, v);

    if (*(u8 *) (self + 0xbc) == *(u8 *) (self + 0xbe)) {
        a = *(s16 *) (self + 0xb8);
        b = *(s16 *) (self + 0xb4);
        d = a - b;
        if (d >= 0 && d < 9) {
            t = (a & 0xf) << 1;
            func_0206fdd4(self + 0x2060, 0, t, 0x1f, t + 1, 4);
        }
    }

    if (func_020b9bbc(self + 0x948, self + 0x2060, 4, 0x800, 0) != 0) {
        func_ov142_02299648(self, 2);
    }
}
