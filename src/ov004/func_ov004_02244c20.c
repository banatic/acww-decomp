/* func_ov004_02244c20 @ 0x02244c20, 0x20 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

int func_ov004_02244c20(char *self)
{
    // DECLS
    // ENDDECLS
    if ((short) *(int *) (self + 0x174) > 0x0) {
        *(int *) (self + 0x174) = ((short) *(int *) (self + 0x174) - 0x1);
        return 0x0;
    }
    return 0x1;
}
