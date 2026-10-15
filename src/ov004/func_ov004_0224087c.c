/* func_ov004_0224087c @ 0x0224087c, 0x40 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_02244f90(void);
extern int func_ov004_02240f2c(void *, int, int, int, int, int, int);
extern int func_020644cc(int);

void func_ov004_0224087c(char *self)
{
    func_ov004_02240f2c(self, 0x3c, 0x46, 0, func_ov004_02244f90(), 0, 0x26);
    *(int *) (self + 0x174) = 0x14 * (func_020644cc(0xa) + 3);
    *(short *) (self + 0x98) = 0;
}
