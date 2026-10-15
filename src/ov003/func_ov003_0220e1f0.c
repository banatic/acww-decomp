/* func_ov003_0220e1f0 @ 0x0220e1f0, 0x36 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0200e92c(void *);
extern void func_0200e90c(void *, int, void *, void *);
extern void *func_0200e894(void *, void *);
extern int func_0200e91c(void *);

void *func_ov003_0220e1f0(void *p0, void *p1, void *p2)
{
    char buf[0x20];
    void *ret;

    func_0200e92c(buf);
    func_0200e90c(buf, 0x75, p1, p2);
    ret = func_0200e894(p0, buf);
    func_0200e91c(buf);
    return ret;
}
