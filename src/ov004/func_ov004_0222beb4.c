/* func_ov004_0222beb4 @ 0x0222beb4, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_02096718();
extern int func_ov004_02228dfc();

int func_ov004_0222beb4(char *self)
{
    // DECLS
    int v1;
    // ENDDECLS
    v1 = func_02096718(0x4);
    if (v1 != 0x0) {
        return func_ov004_02228dfc(v1, 0xa, 0x6, -0x1);
    }
    return 0x0;
}
