/* func_ov068_0227200c @ 0x0227200c, 0x36 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0200e92c(void *);
extern void func_0200e90c(void *, int, void *, void *);
extern void *func_0200e894(void *, void *);
extern int func_0200e91c(void *);

void *func_ov068_0227200c(void *a, void *b, void *c)
{
    char buf[0x20];
    void *ret;

    func_0200e92c(buf);
    func_0200e90c(buf, 0x87, b, c);
    ret = func_0200e894(a, buf);
    func_0200e91c(buf);
    return ret;
}
