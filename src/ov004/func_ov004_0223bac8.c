/* func_ov004_0223bac8 @ 0x0223bac8, 0x14 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *data_ov004_0225967c;

void func_ov004_0223bac8(char *self)
{
    // DECLS
    // ENDDECLS
    *(int *) ((char *) &data_ov004_0225967c) = *(int *) (self);
    *(int *) ((char *) &data_ov004_0225967c + 0x4) = *(int *) (self + 0x4);
    *(int *) ((char *) &data_ov004_0225967c + 0x8) = *(int *) (self + 0x8);
}
