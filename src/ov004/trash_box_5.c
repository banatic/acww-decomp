/* trash_box_5: 3 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0222f8d0 @ 0x0222f8d0, 0x38 bytes, Thumb
 * func_ov004_0222f8cc @ 0x0222f8cc, 0x2 bytes, Thumb
 * func_ov004_0222f884 @ 0x0222f884, 0x48 bytes, Thumb
 */

extern int func_ov004_0222c3c4(void *p, int n);
extern void func_02055060(void *p, int a, int b, int c, int d, int e);
extern int func_ov004_0222c2dc(void *p, int n);

int func_ov004_0222f8d0(char *self)
{
    func_02055060(self + 0xec, func_ov004_0222c3c4(self + 0x1a4, 0), 1, 0x1000, 0, 0);
    return 1;
}

void func_ov004_0222f8cc(void *callbackObject) {}

int func_ov004_0222f884(char *self)
{
    func_02055060(self + 0xec, func_ov004_0222c3c4(self + 0x1a4, 0), 1, 0x1000, 0, 0);
    func_ov004_0222c2dc(self + 0x250, 0x4d6);
    return 1;
}
