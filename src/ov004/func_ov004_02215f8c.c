/* func_ov004_02215f8c @ 0x02215f8c, 0x64 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_0203e0a8();
extern int func_02095ec4();
extern void func_ov004_0220d058();
extern void func_ov004_0220d280();
extern int func_ov004_0220d2a8();
extern void func_ov004_0220ffbc();
extern void func_ov004_022107d4();
extern void func_ov004_0223cf2c();

int func_ov004_02215f8c(char *self)
{
    // DECLS
    int v5;
    // ENDDECLS
    func_ov004_0220ffbc(self);
    func_ov004_022107d4(self);
    func_ov004_0220d058(self + 0x848, 0x1, 0x1, 0x0);
    func_ov004_0223cf2c(self + 0x798, self + 0x7b8);
    v5 = func_ov004_0220d2a8(self + 0x740);
    if (v5 != 0x0) {
        func_ov004_0220d280(self + 0x740, 0x1, 0x0);
        return func_02095ec4(func_0203e0a8(self, 0x0));
    }
    return v5;
}
