/* func_ov004_02240630 @ 0x02240630, 0x34 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_02244f90(void);
extern int func_ov004_02240f2c(void *self, int a, int b, int c, int d, int e, int f);
extern void func_ov004_02240fc0(void *self);

void func_ov004_02240630(char *self)
{
    int x = func_ov004_02244f90();
    func_ov004_02240f2c(self, 0xc8, 0x3c, 0, x, 0, 0x1);
    func_ov004_02240fc0(self);
    *(int *) (self + 0x4c) = 0x38e;
}
