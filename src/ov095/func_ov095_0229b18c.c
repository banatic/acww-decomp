/* func_ov095_0229b18c @ 0x0229b18c, 0x3c bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov095_0229b16c(int);
extern void func_02088df8(int, int, int, int, int, int, int, int, int, int, int, int);

void func_ov095_0229b18c(int a0, int a1, int a2)
{
    int ret = func_ov095_0229b16c(a0);
    func_02088df8(1, ret, a1, a2, -1, 3, 0x1000, 0x1000, 0, -1, 0, 0);
}
