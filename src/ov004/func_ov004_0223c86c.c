/* func_ov004_0223c86c @ 0x0223c86c, 0x3a bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_0220cefc();
extern int func_ov004_0223ca6c();
extern int func_ov004_0223cadc();
extern int func_ov004_0223cb18();

int func_ov004_0223c86c(char *self)
{
    // DECLS
    int v1;
    int v2;
    // ENDDECLS
    v1 = func_ov004_0223cadc(self, 0x0);
    v2 = func_ov004_0223ca6c(self, 0x0);
    if (v1 != 0x0 && v2 != 0x0) {
        return func_ov004_0220cefc(v2, func_ov004_0223cb18(v1));
    }
    return 0x0;
}
