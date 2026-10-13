/* func_ov004_0223b128 @ 0x0223b128, 0xe bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

void *func_ov004_0223b128(char *self, char *a1)
{
    // DECLS
    // ENDDECLS
    *(int *) (self + 0x4) = *(int *) (a1);
    *(int *) (self + 0x8) = *(int *) (a1 + 0x4);
    *(int *) (self + 0xc) = *(int *) (a1 + 0x8);
    return self;
}
