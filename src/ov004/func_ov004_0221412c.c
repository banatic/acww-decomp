/* func_ov004_0221412c @ 0x0221412c, 0x34 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_02052738();
extern void func_02054cdc();
extern int func_02056f94();

int func_ov004_0221412c(char *self)
{
    // DECLS
    int v2;
    // ENDDECLS
    func_02054cdc(self + 0x538);
    v2 = func_02056f94(self + 0x5d4);
    if (v2 != 0x0) {
        return func_02052738(self, 0x0, 0xff, 0x1);
    }
    return v2;
}
