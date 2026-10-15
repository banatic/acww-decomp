/* func_0200c3b0 @ 0x0200c3b0, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0200e92c(void *);
extern void func_0200e90c(void *, int, int, int);
extern void func_0200c3f0(void *, int);
extern int func_0200e894(void *, void *);
extern int func_0200e91c(void *);

int func_0200c3b0(void *p1, int p2, int p3, int p4)
{
    char a[0xc];
    char b[0x10];
    int ret;

    func_0200e92c(a);
    func_0200e90c(a, 0x10, p3, p4);
    func_0200c3f0(b, p2);
    ret = func_0200e894(p1, a);
    func_0200e91c(a);
    return ret;
}
