/* func_ov004_0220d9bc @ 0x0220d9bc, 0x18 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_021077e8();

int func_ov004_0220d9bc(char *self)
{
    // DECLS
    // ENDDECLS
    if (*(int *) (self + 0x28) != 0x0) {
        return func_021077e8(*(int *) (self + 0x28));
    }
    return 0x0;
}
