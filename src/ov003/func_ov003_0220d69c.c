/* func_ov003_0220d69c @ 0x0220d69c, 0x36 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200e92c(void *);
extern void func_0200e90c(void *, int, void *, void *);
extern void *func_0200e894(void *, void *);
extern void func_0200e91c(void *);

void *func_ov003_0220d69c(void *p0, void *p1, void *p2)
{
    char buf[0x20];
    void *ret;

    func_0200e92c(buf);
    func_0200e90c(buf, 0x89, p1, p2);
    ret = func_0200e894(p0, buf);
    func_0200e91c(buf);
    return ret;
}
