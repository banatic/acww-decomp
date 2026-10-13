/* func_ov004_0222c3d4 @ 0x0222c3d4, 0x20 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_020e993c(int, int);
extern void *data_021c9b24;

void func_ov004_0222c3d4(char *self)
{
    // DECLS
    // ENDDECLS
    if (*(int *) (self) != 0x0) {
        func_020e993c(*(int *) ((char *) &data_021c9b24), *(int *) (self));
        *(void **) (self) = 0x0;
    }
}
