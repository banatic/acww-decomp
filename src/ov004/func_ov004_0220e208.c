/* func_ov004_0220e208 @ 0x0220e208, 0x18 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_020e9898(int);

int func_ov004_0220e208(char *self)
{
    // DECLS
    // ENDDECLS
    if (*(int *) (self) != 0x0) {
        func_020e9898(*(int *) (self));
        *(void **) (self) = 0x0;
        return 0x0;
    }
    return *(int *) (self);
}
