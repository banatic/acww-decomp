/* func_ov004_02240a18 @ 0x02240a18, 0x54 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern long func_ov004_02244f90(void);
extern int func_ov004_02240f2c(void *, int, int, int, long, int, int);
extern int func_020644cc(int);
void func_ov004_02240a18(char *self, int a, int b, int d, unsigned char e)
{
    long v = func_ov004_02244f90();
    func_ov004_02240f2c(self, a, b, 0, v, 0, (int) (0x1000 / d));
    *(short *) (self + 0x98) = (short) (0x14 * (func_020644cc(9) + 2));
    *(unsigned char *) (self + 0xa4) = e;
}
