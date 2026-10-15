/* func_ov112_022a0798 @ 0x022a0798, 0x6c bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov002_0220a700(u8 *p);
extern int func_0208e4bc(u8 *p);
extern int func_ov002_0220a6e0(u8 *p);
extern int func_ov002_0220a768(u8 *p, int);
extern int func_ov002_0220a72c(u8 *p, int);
extern void func_ov002_0220a0b4(u8 *p, int, int);
extern void func_ov112_0229f3e0(u8 *p);
extern unsigned char *func_ov002_022080a0(u8 *p, unsigned char value);

void func_ov112_022a0798(u8 *self)
{
    if (func_ov002_0220a700(self + 0x427c) != 0) {
        if (func_0208e4bc(self + 0x4448) != 0) {
            int v1 = func_ov002_0220a6e0(self + 0x427c);
            int v2 = func_ov002_0220a768(self + 0x427c, -1);
            int v3 = func_ov002_0220a72c(self + 0x427c, -1);
            func_ov002_0220a0b4(self + 0x4448, v1 + v2, v1 + v3);
        }
    } else {
        func_ov112_0229f3e0(self);
        func_ov002_022080a0(self, 1);
    }
}
