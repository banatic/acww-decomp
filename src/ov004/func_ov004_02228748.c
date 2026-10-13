/* func_ov004_02228748 @ 0x02228748, 0x2c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_0200f328();
extern void func_02010f5c();
extern int func_02056f28();

int func_ov004_02228748(char *self)
{
    // DECLS
    int v2;
    // ENDDECLS
    func_02010f5c(self);
    v2 = func_02056f28(self + 0x2d0, 0xd);
    if (v2 != 0x0) {
        return func_0200f328(self, 0x4c6);
    }
    return v2;
}
