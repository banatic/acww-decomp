/* func_ov003_0220dbb4 @ 0x0220dbb4, 0x36 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200e92c(void *);
extern void func_0200e90c(void *, int, void *, void *);
extern int func_0200e894(void *, void *);
extern void func_0200e91c(void *);

int func_ov003_0220dbb4(void *a, void *b, void *c)
{
    char buf[0x20];
    int ret;

    func_0200e92c(buf);
    func_0200e90c(buf, 0x81, b, c);
    ret = func_0200e894(a, buf);
    func_0200e91c(buf);
    return ret;
}
