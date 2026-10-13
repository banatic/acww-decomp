/* func_ov004_022271a4 @ 0x022271a4, 0x38 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_02056f94(void *p);
extern void func_ov004_0222714c(void *self, int a, int b, int c, int d);
void func_ov004_022271a4(unsigned char *self)
{
    unsigned char *w;
    if (func_02056f94(self + 0x2d0) != 0) {
        w = self + 0x7d4;
        func_ov004_0222714c(self, w[0], w[1], 6, -1);
    }
}
