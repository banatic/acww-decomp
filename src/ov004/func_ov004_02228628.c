/* func_ov004_02228628 @ 0x02228628, 0x50 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200e92c(void *p);
extern void func_0200e90c(void *p, int a, int b, int c);
extern void func_ov004_02228678(void *p, int a, int b, int c, int d);
extern int func_0200e894(int a, void *p);
extern void func_0200e91c(void *p);

int func_ov004_02228628(int a, int b, int c, int d, short e, int f, short g)
{
    char buf0[12];
    char buf1[16];
    int res;

    func_0200e92c(buf0);
    func_0200e90c(buf0, 0x2d, f, g);
    func_ov004_02228678(buf1, b, c, d, e);
    res = func_0200e894(a, buf0);
    func_0200e91c(buf0);
    return res;
}
