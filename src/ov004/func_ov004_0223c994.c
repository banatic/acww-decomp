/* func_ov004_0223c994 @ 0x0223c994, 0x1e bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_0220cf90();
extern int func_ov004_0223ca6c();

int func_ov004_0223c994(char *self, int a1)
{
    // DECLS
    int v1;
    // ENDDECLS
    v1 = func_ov004_0223ca6c(self, 0x0);
    if (v1 != 0x0) {
        return func_ov004_0220cf90(v1, a1);
    }
    return 0x0;
}
