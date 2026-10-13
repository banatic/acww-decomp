/* func_ov004_0222471c @ 0x0222471c, 0x20 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_020960f8(int a, int b);
extern void func_ov004_022249b4(char *self, int a);
int func_ov004_0222471c(char *self)
{
    if (func_020960f8(0x28, 4) != 0) {
        func_ov004_022249b4(self, 1);
    }
    return 1;
}
