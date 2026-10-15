/* func_ov003_02216124 @ 0x02216124, 0x36 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0200e92c(char *buf);
extern void func_0200e90c(char *buf, int size, const char *fmt, int arg);
extern int func_0200e894(int a, char *buf);
extern int func_0200e91c(char *buf);

int func_ov003_02216124(int a, const char *fmt, int arg)
{
    char buf[32];
    int res;

    func_0200e92c(buf);
    func_0200e90c(buf, 0x4c, fmt, arg);
    res = func_0200e894(a, buf);
    func_0200e91c(buf);
    return res;
}
