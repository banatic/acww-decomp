/* func_0200fb7c @ 0x0200fb7c, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020114b0(char *ptr, int a, int b, int c, int d);
extern void func_0200fb34(char *ptr, int a);

void func_0200fb7c(char *a0, int a1, int a2, int a3)
{
    char *p = a0 + 0x5c;
    func_020114b0(p, a1, 0x0e66, 0x04cd, 0x31);
    p += 8;
    func_020114b0(p, a2, 0x0e66, 0x04cd, 0x31);
    func_0200fb34(a0, a3);
}
