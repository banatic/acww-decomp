/* func_ov004_02228840 @ 0x02228840, 0xe bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

void *func_ov004_02228840(char *self, char *a1)
{
    // DECLS
    // ENDDECLS
    *(int *) (self) = *(int *) (a1);
    *(int *) (self + 0x4) = *(int *) (a1 + 0x4);
    *(int *) (self + 0x8) = *(int *) (a1 + 0x8);
    return self;
}
