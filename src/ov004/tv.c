/* tv: 3 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_022157fc @ 0x022157fc, 0x48 bytes, Thumb
 * func_ov004_022157d4 @ 0x022157d4, 0x28 bytes, Thumb
 * func_ov004_02215788 @ 0x02215788, 0x4c bytes, Thumb
 */

extern int func_ov004_0220d208(void *, int, int, int);
extern void func_ov004_0220d280(void *, int, int);
extern void func_ov004_02210054(void *, int, int, int);
extern int func_ov004_02215d80(void *, int);
extern int func_0205265c(unsigned int argument0, int argument1, int argument2, int argument3);
extern int func_ov004_0220d2a8(char *argument0);
extern int func_ov004_02210744(void *);

int func_ov004_022157fc(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0220d280(self + 0x740, 0x1, 0x0);
    func_ov004_0220d208(self + 0x848, 0x1, 0x1, 0x0);
    func_ov004_02215d80(self, 0x1);
    func_ov004_02210054(self, 0x0, 0x1, 0x1000);
    return 0x1;
}

int func_ov004_022157d4(char *self)
{
    // DECLS
    int v1;
    // ENDDECLS
    v1 = func_ov004_0220d2a8(self + 0x740);
    if (v1 != 0x0) {
        return func_0205265c((unsigned int) (self), (int) (0x3), (int) (0xff), (int) (0x1));
    }
    return v1;
}

int func_ov004_02215788(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0220d280(self + 0x740, 0x0, 0x0);
    func_ov004_0220d208(self + 0x848, 0x0, 0x1, 0x0);
    func_ov004_02215d80(self, 0x0);
    func_ov004_02210054(self, 0x0, 0x3, 0x1000);
    func_ov004_02210744(self);
    return 0x1;
}
