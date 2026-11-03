/* trash_box_4: 3 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0222f81c @ 0x0222f81c, 0x38 bytes, Thumb
 * func_ov004_0222f818 @ 0x0222f818, 0x2 bytes, Thumb
 * func_ov004_0222f7d0 @ 0x0222f7d0, 0x48 bytes, Thumb
 */

extern int func_ov004_0222c3c4(void *p, int n);
extern void func_02055060(void *p, int a, int b, int c, int d, int e);
extern int func_ov004_0222c2dc(void *, int);

int func_ov004_0222f81c(char *self)
{
    func_02055060(self + 0xec, func_ov004_0222c3c4(self + 0x1a4, 1), 1, 0x1000, 0, 0);
    return 1;
}

void func_ov004_0222f818(void *callbackObject) {}

int func_ov004_0222f7d0(char *self)
{
    // DECLS
    // ENDDECLS
    func_02055060(self + 0xec, func_ov004_0222c3c4(self + 0x1a4, 0x1), 0x1, 0x1000, 0x0, 0x0);
    func_ov004_0222c2dc(self + 0x250, 0x4d7);
    return 0x1;
}
