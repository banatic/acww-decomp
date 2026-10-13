/* func_ov050_02261040 @ 0x02261040, 0x1c bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov050_022618d0(int *p, int a, int b);

void func_ov050_02261040(int *p, int x)
{
    if (x == 4) {
        return;
    }
    func_ov050_022618d0(p, 3, x);
    p[0x34] = 0x48;
}
