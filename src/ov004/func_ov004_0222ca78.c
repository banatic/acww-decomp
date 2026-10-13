/* func_ov004_0222ca78 @ 0x0222ca78, 0x48 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_0222c3c4(void *p, int n);
extern void func_02055060(void *p, int a, int b, int c, int d, int e);
extern void func_ov004_0222c2dc(void *p, int n);

int func_ov004_0222ca78(char *self)
{
    func_02055060(self + 0xec, func_ov004_0222c3c4(self + 0x1a4, 0), 1, 0x1000, 0, 0);
    func_ov004_0222c2dc(self + 0x250, 0x4d8);
    return 1;
}
