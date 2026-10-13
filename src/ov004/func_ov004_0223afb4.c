/* func_ov004_0223afb4 @ 0x0223afb4, 0x1e bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_020e9fc8();

int func_ov004_0223afb4(char *self)
{
    // DECLS
    // ENDDECLS
    if (*(int *) (self + 0x10) != 0x0) {
        func_020e9fc8(*(int *) (self + 0x10));
        *(void **) (self + 0x10) = 0x0;
        return 0x1;
    }
    return 0x0;
}
