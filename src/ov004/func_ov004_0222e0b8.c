/* func_ov004_0222e0b8 @ 0x0222e0b8, 0x6c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_022236a8();
extern int func_ov004_022236c4();
extern int func_ov004_0222db14();

int func_ov004_0222e0b8(char *self)
{
    // DECLS
    int v1;
    int v2;
    // ENDDECLS
    v1 = func_ov004_022236c4(self);
    v2 = func_ov004_022236a8(v1);
    if (v2 == 0xf8) {
        func_ov004_0222db14(self, 0x7, self + 0x348, self + 0x9ac, 0x3, 0x1000, v1, 0x0);
        return func_ov004_0222db14(self, 0x5, self + 0x400, self + 0xa50, 0x3, 0x1000, v1, 0x0);
    }
    return v2;
}
