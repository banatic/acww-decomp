/* func_ov004_0222deb4 @ 0x0222deb4, 0x88 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_02054ecc(void *);
extern int func_ov004_0222c3c4(void *, int);
extern int func_02056f94(void *);
extern void func_ov004_0222db14(void *, int, void *, void *, int, int, int, int);

void func_ov004_0222deb4(char *self)
{
    if (func_02054ecc(self + 0x348) == func_ov004_0222c3c4(self + 0x9ac, 0xb)) {
        if (func_02056f94(self + 0x3e4) != 0) {
            func_ov004_0222db14(self, 0xc, self + 0x348, self + 0x9ac, 1, 0x1000, 0, 0);
            func_ov004_0222db14(self, 0xa, self + 0x400, self + 0xa50, 1, 0x1000, 0, 0);
        }
    }
}
