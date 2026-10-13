/* func_ov003_022186cc @ 0x022186cc, 0x50 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200e92c(void *p);
extern void func_0200e90c(void *p, int a, int b, int c);
extern void func_ov003_0221871c(void *p, int a, int b, int c, int d);
extern int func_0200e894(int a, void *p);
extern void func_0200e91c(void *p);

int func_ov003_022186cc(int a, int b, int c, int d, short e, int f, short g)
{
    char buf0[12];
    char buf1[16];
    int res;

    func_0200e92c(buf0);
    func_0200e90c(buf0, 0x39, f, g);
    func_ov003_0221871c(buf1, b, c, d, e);
    res = func_0200e894(a, buf0);
    func_0200e91c(buf0);
    return res;
}
