/* func_ov003_022183f4 @ 0x022183f4, 0x36 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0200e92c(void *);
extern void func_0200e90c(void *, int, int, int);
extern int func_0200e894(void *, void *);
extern int func_0200e91c(void *);

int func_ov003_022183f4(void *a, int b, int c)
{
    char buf[0x20];
    int ret;
    func_0200e92c(buf);
    func_0200e90c(buf, 0x3a, b, c);
    ret = func_0200e894(a, buf);
    func_0200e91c(buf);
    return ret;
}
