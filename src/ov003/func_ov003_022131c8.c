/* func_ov003_022131c8 @ 0x022131c8, 0x42 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0200e92c(void *);
extern void func_0200e90c(void *, int, int, int);
extern int func_0200e894(int, void *);
extern int func_0200e91c(void *);

int func_ov003_022131c8(int a, char b, char c, int d, short e)
{
    char buf[0x1c];
    int result;
    char *p;

    func_0200e92c(buf);
    func_0200e90c(buf, 0x58, d, e);
    p = &buf[0xc];
    p[0] = b;
    p[1] = c;
    result = func_0200e894(a, buf);
    func_0200e91c(buf);
    return result;
}
