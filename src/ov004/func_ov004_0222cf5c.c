/* func_ov004_0222cf5c @ 0x0222cf5c, 0x60 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_02055060();
extern int func_02055e00();
extern void func_02056440();
extern int func_ov004_0222c3b4();
extern int func_ov004_0222c3c4();

int func_ov004_0222cf5c(char *self)
{
    // DECLS
    int v3;
    // ENDDECLS
    func_02055060(self + 0xec, func_ov004_0222c3c4(self + 0x1a4, 0x2), 0x0, 0x1000, 0x0, 0x0);
    v3 = func_02055e00(self + 0xec);
    func_02056440(self + 0x290, v3, func_ov004_0222c3b4(self + 0x1a4, 0x2), 0x0, 0x1000, 0x0);
    return 0x1;
}
