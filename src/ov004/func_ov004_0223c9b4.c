/* func_ov004_0223c9b4 @ 0x0223c9b4, 0x1e bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_0220ebe0(int arg0, int arg1);
extern int func_ov004_0223ca6c(char *argument0, int argument1);

int func_ov004_0223c9b4(char *self, int a1)
{
    // DECLS
    int v1;
    // ENDDECLS
    v1 = func_ov004_0223ca6c((char *) ((char *) (self)), (int) ((int) (0x0)));
    if (v1 != 0x0) {
        return func_ov004_0220ebe0(v1, a1);
    }
    return 0x0;
}
