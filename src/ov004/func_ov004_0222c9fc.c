/* func_ov004_0222c9fc @ 0x0222c9fc, 0x38 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_0222c3c4(void *p, int n);
extern void func_02055060(void *p, int a, int b, int c, int d, int e);

int func_ov004_0222c9fc(char *self)
{
    func_02055060(self + 0xec, func_ov004_0222c3c4(self + 0x1a4, 1), 1, 0x1000, 0, 0);
    return 1;
}
