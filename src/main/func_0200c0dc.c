/* func_0200c0dc @ 0x0200c0dc, 0x42 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0200e92c(void *p);
extern void func_0200e90c(void *p, int a, int b, int c);
extern int func_0200e894(int a, void *p);
extern int func_0200e91c(void *p);

int func_0200c0dc(int a, char b, char c, int d, short e)
{
    char buf[28];
    char *p;
    int result;

    func_0200e92c(buf);
    func_0200e90c(buf, 20, d, e);
    p = &buf[12];
    p[1] = b;
    p[0] = c;
    result = func_0200e894(a, buf);
    func_0200e91c(buf);
    return result;
}
