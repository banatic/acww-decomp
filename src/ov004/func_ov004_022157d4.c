/* func_ov004_022157d4 @ 0x022157d4, 0x28 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_0205265c();
extern int func_ov004_0220d2a8();

int func_ov004_022157d4(char *self)
{
    // DECLS
    int v1;
    // ENDDECLS
    v1 = func_ov004_0220d2a8(self + 0x740);
    if (v1 != 0x0) {
        return func_0205265c(self, 0x3, 0xff, 0x1);
    }
    return v1;
}
