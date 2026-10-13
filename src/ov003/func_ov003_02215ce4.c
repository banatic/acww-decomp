/* func_ov003_02215ce4 @ 0x02215ce4, 0x36 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200e92c(void *);
extern void func_0200e90c(void *, int, int, int);
extern int func_0200e894(int, void *);
extern void func_0200e91c(void *);

int func_ov003_02215ce4(int a, int b, int c)
{
    char buf[0x20];
    int ret;

    func_0200e92c(buf);
    func_0200e90c(buf, 0x4E, b, c);
    ret = func_0200e894(a, buf);
    func_0200e91c(buf);
    return ret;
}
