/* func_ov004_0222e4fc @ 0x0222e4fc, 0xa4 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_022236c4(void);
extern int func_ov004_022236a8(void);
extern void func_ov004_0222db14(void *, int, void *, void *, int, int, int, int);

void func_ov004_0222e4fc(char *self)
{
    func_ov004_022236c4();
    if (func_ov004_022236a8() == 0xf3) {
        func_ov004_0222db14(self, 0, self + 0x348, self + 0x9ac, 0, 0x1000, 0, 0);
        func_ov004_0222db14(self, 0, self + 0x400, self + 0xa50, 0, 0x1000, 0, 0);
    } else if (func_ov004_022236a8() == 0xf5) {
        func_ov004_0222db14(self, 1, self + 0x348, self + 0x9ac, 0, 0x1000, 0, 0);
        func_ov004_0222db14(self, 1, self + 0x400, self + 0xa50, 0, 0x1000, 0, 0);
    }
}
