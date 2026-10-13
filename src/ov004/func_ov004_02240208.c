/* func_ov004_02240208 @ 0x02240208, 0x34 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_02240f2c(void *, int, int, int, int, int, int);
extern int func_020644cc(int);

void func_ov004_02240208(char *self)
{
    func_ov004_02240f2c(self, 0x28, 0x1e, 0, 0, 0, 0xf);
    *(int *) (self + 0x174) = (short) func_020644cc(0x1e) + 0xa;
}
