/* func_02009e50 @ 0x02009e50, 0x36 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200e92c(char *p);
extern void func_0200e90c(char *p, int arg1, int arg2, int arg3);
extern int func_0200e894(int a, char *p);
extern void func_0200e91c(char *p);

int func_02009e50(int a, int b, int c)
{
    char buf[32];
    int result;
    func_0200e92c(buf);
    func_0200e90c(buf, 0x35, b, c);
    result = func_0200e894(a, buf);
    func_0200e91c(buf);
    return result;
}
