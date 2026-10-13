/* func_ov004_0222e128 @ 0x0222e128, 0x8c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_022236c4(void);
extern int func_ov004_022236a8(void);
extern void func_ov004_0222db14(void *, int, void *, void *, int, int, int, int);
extern int func_0209120c(int, void *, void *, int);

void func_ov004_0222e128(char *self)
{
    int a = func_ov004_022236c4();
    if (func_ov004_022236a8() == 0xf8) {
        func_ov004_0222db14(self, 6, self + 0x348, self + 0x9ac, 1, 0x1000, 0, 0);
        func_ov004_0222db14(self, 4, self + 0x400, self + 0xa50, 1, 0x1000, 0, 0);
        if (a == 0x3b) {
            *(int *) (self + 0xf38) = func_0209120c(0x6b, self + 0xf10, self + 0x8e, 0);
        }
    }
}
