/* func_ov003_02217ddc @ 0x02217ddc, 0x36 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0200e92c(void *p);
extern void func_0200e90c(void *p, int x, int y, int z);
extern int func_0200e894(int a, void *p);
extern int func_0200e91c(void *p);

int func_ov003_02217ddc(int a, int b, int c)
{
    char buffer[32];
    int result;
    func_0200e92c(buffer);
    func_0200e90c(buffer, 0x3c, b, c);
    result = func_0200e894(a, buffer);
    func_0200e91c(buffer);
    return result;
}
