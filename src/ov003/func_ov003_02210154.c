/* func_ov003_02210154 @ 0x02210154, 0x36 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_0200e92c(char *buf);
extern void func_0200e90c(char *buf, int size, int a, int b);
extern int func_0200e894(int a, char *buf);
extern int func_0200e91c(char *buf);

int func_ov003_02210154(int a, int b, int c)
{
    char buf[0x20];
    int ret;
    func_0200e92c(buf);
    func_0200e90c(buf, 0x65, b, c);
    ret = func_0200e894(a, buf);
    func_0200e91c(buf);
    return ret;
}
