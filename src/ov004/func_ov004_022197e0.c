/* func_ov004_022197e0 @ 0x022197e0, 0x44 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_0220d058();
extern void func_ov004_0220d280();
extern void func_ov004_0221078c();

int func_ov004_022197e0(char *self)
{
    // DECLS
    // ENDDECLS
    *(int *) (self + 0x848) = 0x1000;
    func_ov004_0220d280(self + 0x740, 0x1, 0x0);
    func_ov004_0221078c(self);
    func_ov004_0220d058(self + 0x84c, 0x1, 0x1, 0x0);
    return 0x1;
}
