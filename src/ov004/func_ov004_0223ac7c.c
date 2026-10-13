/* func_ov004_0223ac7c @ 0x0223ac7c, 0x1a bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_020e9b9c(int);

void func_ov004_0223ac7c(char *self)
{
    // DECLS
    // ENDDECLS
    if (*(int *) (self) != 0x0) {
        func_020e9b9c(*(int *) (self));
    }
    *(void **) (self + 0x8) = 0x0;
    *(void **) (self + 0xc) = 0x0;
}
