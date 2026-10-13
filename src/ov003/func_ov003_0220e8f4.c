/* func_ov003_0220e8f4 @ 0x0220e8f4, 0x42 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200e92c(void *buf);
extern void func_0200e90c(void *buf, int param, int a, int b);
extern int func_0200e894(void *p1, void *buf);
extern void func_0200e91c(void *buf);

int func_ov003_0220e8f4(void *param1, unsigned int *param2, int a2, int a3)
{
    char buf[0x1c];
    char *p = buf + 0xc;
    int ret;

    func_0200e92c(buf);
    func_0200e90c(buf, 0x73, a2, a3);
    p[0] = (char) param2[0];
    p[1] = (char) param2[1];
    ret = func_0200e894(param1, buf);
    func_0200e91c(buf);
    return ret;
}
