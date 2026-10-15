/* func_02008a54 @ 0x02008a54, 0x36 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0200e92c(void *);
extern void func_0200e90c(void *, int, int, int);
extern int func_0200e894(int, void *);
extern int func_0200e91c(void *);

int func_02008a54(int a, int b, int c)
{
    unsigned char buf[32];
    int result;

    func_0200e92c(buf);
    func_0200e90c(buf, 0x83, b, c);
    result = func_0200e894(a, buf);
    func_0200e91c(buf);
    return result;
}
