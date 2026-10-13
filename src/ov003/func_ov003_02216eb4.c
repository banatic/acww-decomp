/* func_ov003_02216eb4 @ 0x02216eb4, 0x36 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200e92c(void *);
extern void func_0200e90c(void *, int, void *, void *);
extern int func_0200e894(void *, void *);
extern void func_0200e91c(void *);

int func_ov003_02216eb4(void *a0, void *a1, void *a2)
{
    char buf[0x20];
    int ret;
    func_0200e92c(buf);
    func_0200e90c(buf, 0x47, a1, a2);
    ret = func_0200e894(a0, buf);
    func_0200e91c(buf);
    return ret;
}
