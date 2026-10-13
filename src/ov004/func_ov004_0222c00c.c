/* func_ov004_0222c00c @ 0x0222c00c, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_02096718();
extern int func_ov004_022282c0();

int func_ov004_0222c00c(char *self)
{
    // DECLS
    int v1;
    // ENDDECLS
    v1 = func_02096718(0x4);
    if (v1 != 0x0) {
        return func_ov004_022282c0(v1, *(int *) (self), 0x6, -0x1);
    }
    return 0x0;
}
