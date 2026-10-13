/* func_ov004_02215c0c @ 0x02215c0c, 0x28 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_0220d2a8(void *p);
extern void func_0205265c(void *p, int a, int b, int c);

void func_ov004_02215c0c(char *self)
{
    if (func_ov004_0220d2a8(self + 0x740)) {
        func_0205265c(self, 1, 0xff, 1);
    }
}
