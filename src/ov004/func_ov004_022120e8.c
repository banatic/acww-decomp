/* func_ov004_022120e8 @ 0x022120e8, 0x3c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_0205265c();
extern void func_ov004_0220d058();
extern int func_ov004_0220d2a8();
extern void func_ov004_0220ffbc();

int func_ov004_022120e8(char *self)
{
    // DECLS
    int v3;
    // ENDDECLS
    func_ov004_0220ffbc(self);
    func_ov004_0220d058(self + 0x844, 0x0, 0x1, 0x0);
    v3 = func_ov004_0220d2a8(self + 0x740);
    if (v3 != 0x0) {
        return func_0205265c(self, 0x1, 0xff, 0x1);
    }
    return v3;
}
