/* func_ov004_0222b440 @ 0x0222b440, 0x28 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_02056f94(void *p);
extern void func_ov004_0222bdf0(void *self, int a, int b, int d);

void func_ov004_0222b440(void *self)
{
    if (func_02056f94((char *) self + 0x2d0) != 0) {
        func_ov004_0222bdf0(self, 0, 6, ~0);
    }
}
