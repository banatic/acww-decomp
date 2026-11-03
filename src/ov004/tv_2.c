/* tv_2: 3 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_022158f0 @ 0x022158f0, 0x4c bytes, Thumb
 * func_ov004_022158c8 @ 0x022158c8, 0x28 bytes, Thumb
 * func_ov004_02215874 @ 0x02215874, 0x54 bytes, Thumb
 */

extern int func_ov004_0220d208(void *, int, int, int);
extern void func_ov004_0220d280(void *, int, int);
extern void func_ov004_022101e4(void *, int, int, int, int);
extern int func_ov004_02215d80(void *, int);
extern int func_ov004_0220d2a8(void *p);
extern int func_0205265c(void *p, int a, int b, int c);
extern int func_ov004_0221078c(void *);

int func_ov004_022158f0(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0220d280(self + 0x740, 0x0, 0x0);
    func_ov004_0220d208(self + 0x848, 0x0, 0x1, 0x0);
    func_ov004_02215d80(self, 0x0);
    func_ov004_022101e4(self, 0x0, 0x3, 0x1000, 0x0);
    return 0x1;
}

void func_ov004_022158c8(char *self)
{
    if (func_ov004_0220d2a8(self + 0x740)) {
        func_0205265c(self, 1, 0xff, 1);
    }
}

int func_ov004_02215874(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0220d280(self + 0x740, 0x1, 0x0);
    func_ov004_0220d208(self + 0x848, 0x1, 0x1, 0x0);
    func_ov004_02215d80(self, 0x1);
    func_ov004_022101e4(self, 0x0, 0x1, 0x1000, 0x0);
    func_ov004_0221078c(self);
    return 0x1;
}
