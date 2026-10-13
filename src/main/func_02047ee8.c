/* func_02047ee8 @ 0x02047ee8, 0xc4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_02063414(volatile u16 *, int, int, int, int, int, int, int, int, int);
extern int func_02048cb8(int, int, int, int, int, int, int);
extern int func_020ba4d4(void);
extern int func_020644cc(int);
extern int func_02048e54(void);

void func_02047ee8(int a, int b, int nx, int ny, u8 flag)
{
    volatile u16 w[2];
    int z;
    int cx;
    int cy;
    int i;
    int m;

    if (flag == 0) {
        return;
    }
    m = func_020ba4d4();
    if (m != 0 && m != 1 && m != 2) {
        return;
    }
    w[0] = 0xfff1;
    cx = func_020644cc(nx - 1);
    cy = func_020644cc(ny - 1);
    z = 0;
    for (i = 0; i < 3; i++) {
        func_02063414(&w[1], 0x45dc, 0x7f, z, z, z, 1, 0xa, z, 1);
        w[0] = w[1];
        cx = (cx + 1 + func_020644cc(nx - 1)) % nx;
        cy = (cy + 1 + func_020644cc(ny - 1)) % ny;
        func_02048cb8(a, b, cx + 1, cy + 1, w[0], (int) func_02048e54, 1);
    }
}
