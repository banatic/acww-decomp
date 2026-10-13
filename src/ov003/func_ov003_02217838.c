/* func_ov003_02217838 @ 0x02217838, 0x5c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200e92c(char *p);
extern void func_0200e90c(char *p, int n, int m, short s);
extern void func_ov003_02217894(char *p, int a, int b, int c, int d, short e);
extern void func_0200f268(char *p, int n);
extern int func_0200e894(char *p, char *q);
extern void func_0200e91c(char *p);

int func_ov003_02217838(char *p0, int p1, int p2, int p3, int p4, short p5, int p6, short p7)
{
    char buf1[12];
    char out[20];
    int ret;

    func_0200e92c(buf1);
    func_0200e90c(buf1, 0x3e, p6, p7);
    func_ov003_02217894(out, p1, p2, p3, p4, p5);
    func_0200f268(p0, 1);
    ret = func_0200e894(p0, buf1);
    func_0200e91c(buf1);
    return ret;
}
