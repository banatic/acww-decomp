/* func_ov004_0223ca6c @ 0x0223ca6c, 0x2e bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_0223cadc();
extern int func_ov004_0223cb5c();
extern int func_ov004_0223cd58();
extern int func_ov004_0223ce84();

int func_ov004_0223ca6c(char *self)
{
    // DECLS
    int v1;
    int v2;
    // ENDDECLS
    v1 = func_ov004_0223cadc(self);
    if (v1 != 0x0) {
        v2 = func_ov004_0223ce84(v1);
        return func_ov004_0223cd58(v2, func_ov004_0223cb5c(v1));
    }
    return 0x0;
}
