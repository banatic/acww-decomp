/* func_ov004_0222cf18 @ 0x0222cf18, 0x44 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_02055124();
extern void func_02056ffc();
extern int func_020b65c4();
extern int func_ov004_0222d30c();

int func_ov004_0222cf18(char *self)
{
    // DECLS
    int v5;
    // ENDDECLS
    func_02055124(self + 0xec);
    func_02056ffc(self + 0x290);
    *(int *) ((char *) *(int *) (self + 0x2a8)) = *(int *) (self + 0x298);
    v5 = func_020b65c4();
    if (v5 == 0xb) {
        return func_ov004_0222d30c(self, 0xffffe000);
    }
    return v5;
}
