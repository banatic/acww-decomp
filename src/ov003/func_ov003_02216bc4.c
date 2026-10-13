/* func_ov003_02216bc4 @ 0x02216bc4, 0x36 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200e92c(void *);
extern void func_0200e90c(void *, int, int, int);
extern int func_0200e894(void *, void *);
extern void func_0200e91c(void *);

int func_ov003_02216bc4(void *a0, int a1, int a2)
{
    char buf[0x20];
    int ret;
    func_0200e92c(buf);
    func_0200e90c(buf, 0x48, a1, a2);
    ret = func_0200e894(a0, buf);
    func_0200e91c(buf);
    return ret;
}
