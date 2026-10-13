/* func_ov003_02215624 @ 0x02215624, 0x40 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200e92c(void *p);
extern void func_0200e90c(void *p, int n, int x, int y);
extern void func_ov003_02215664(void *p, void *q);
extern void *func_0200e894(void *p, void *q);
extern void func_0200e91c(void *p);

void *func_ov003_02215624(void *a, void *b, int c, int d)
{
    char s1[12];
    char s2[16];
    void *r;

    func_0200e92c(s1);
    func_0200e90c(s1, 0x51, c, d);
    func_ov003_02215664(s2, b);
    r = func_0200e894(a, s1);
    func_0200e91c(s1);
    return r;
}
