/* func_ov004_022158c8 @ 0x022158c8, 0x28 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_0220d2a8(void *p);
extern int func_0205265c(void *p, int a, int b, int c);

void func_ov004_022158c8(char *self)
{
    if (func_ov004_0220d2a8(self + 0x740)) {
        func_0205265c(self, 1, 0xff, 1);
    }
}
