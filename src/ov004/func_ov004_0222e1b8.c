/* func_ov004_0222e1b8 @ 0x0222e1b8, 0x68 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_022236a8();
extern int func_ov004_022236c4();
extern int func_ov004_0222db14();

int func_ov004_0222e1b8(char *self)
{
    // DECLS
    int v2;
    // ENDDECLS
    v2 = func_ov004_022236a8(func_ov004_022236c4(self));
    if (v2 == 0xf7) {
        func_ov004_0222db14(self, 0x5, self + 0x348, self + 0x9ac, 0x0, 0x1000, 0x0, 0x0);
        return func_ov004_0222db14(self, 0x3, self + 0x400, self + 0xa50, 0x0, 0x1000, 0x0, 0x0);
    }
    return v2;
}
