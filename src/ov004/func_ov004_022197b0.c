/* func_ov004_022197b0 @ 0x022197b0, 0x30 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_0205265c();
extern int func_ov004_0220d2a8();
extern void func_ov004_022107d4();
extern void func_ov004_0221081c();

int func_ov004_022197b0(char *self)
{
    // DECLS
    int v3;
    // ENDDECLS
    func_ov004_0221081c(self);
    func_ov004_022107d4(self);
    v3 = func_ov004_0220d2a8(self + 0x740);
    if (v3 != 0x0) {
        return func_0205265c(self, 0x2, 0xff, 0x1);
    }
    return v3;
}
