/* func_ov004_02214fc8 @ 0x02214fc8, 0x58 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_02051f4c();
extern void func_02054cdc();
extern int func_020b65c4();
extern int func_ov004_0220d280();
extern int func_ov004_0220d2a8();
extern int func_ov004_0220fd8c();
extern void func_ov004_02215298();

int func_ov004_02214fc8(char *self)
{
    // DECLS
    int v3;
    int v5;
    // ENDDECLS
    func_ov004_02215298(self, self + 0x5c);
    func_02054cdc(self + 0x538);
    v3 = func_ov004_0220d2a8(self + 0x740);
    if (v3 != 0x0) {
        v5 = func_020b65c4(func_ov004_0220d280(self + 0x740, 0x0, 0x0));
        return func_02051f4c(v5, self + 0x5c, func_ov004_0220fd8c(self));
    }
    return v3;
}
