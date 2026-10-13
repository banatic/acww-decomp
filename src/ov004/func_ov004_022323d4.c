/* func_ov004_022323d4 @ 0x022323d4, 0x7c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_02232450(void *);
extern int func_020321bc(void *, int, int, int, int *, int, int);

int func_ov004_022323d4(char *self)
{
    int a[3], b[3];
    int r1, r2;
    if (func_ov004_02232450(self) != 0) {
        a[0] = 0xd000;
        a[1] = 0;
        a[2] = 0x1c000;
        b[0] = 0x13000;
        b[1] = 0;
        b[2] = 0x1c000;
        r1 = func_020321bc(self, 0x2000, 0, 0x4000, a, 0, 0);
        r2 = func_020321bc(self + 0x9c, 0x2000, 0, 0x4000, b, 0, 0);
        if (r1 != 0) {
            if (r2 != 0) {
                return 1;
            }
        }
        return 0;
    }
    return 0;
}
