/* func_ov004_0223ac14 @ 0x0223ac14, 0x20 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_020e9fc8(int);

void func_ov004_0223ac14(char *self)
{
    // DECLS
    // ENDDECLS
    if (*(int *) (self) != 0x0) {
        func_020e9fc8(*(int *) (self));
        *(void **) (self) = 0x0;
    }
    *(void **) (self + 0xc) = 0x0;
    *(void **) (self + 0x8) = 0x0;
    *(void **) (self + 0x4) = 0x0;
}
