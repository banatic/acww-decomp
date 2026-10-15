/* func_ov004_0222e5a4 @ 0x0222e5a4, 0xa0 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short func_ov004_022236c4(void);
extern int func_ov004_022236a8(void);
extern void func_ov004_0222db14(void *, int, void *, void *, int, int, int, int);

void func_ov004_0222e5a4(char *self)
{
    func_ov004_022236c4();
    if (func_ov004_022236a8() == 0xf2) {
        func_ov004_0222db14(self, 0, self + 0xec, self + 0x1a4, 0, 0x1000, 0, 0);
        func_ov004_0222db14(self, 0, self + 0x290, self + 0x908, 0, 0x1000, 0, 0);
    } else if (func_ov004_022236a8() == 0xf4) {
        func_ov004_0222db14(self, 1, self + 0xec, self + 0x1a4, 0, 0x1000, 0, 0);
        func_ov004_0222db14(self, 1, self + 0x290, self + 0x908, 0, 0x1000, 0, 0);
    }
}
