/* func_ov004_0222dc00 @ 0x0222dc00, 0x1c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *data_ov004_02258310;

int func_ov004_0222dc00(void)
{
    // DECLS
    // ENDDECLS
    if (*(int *) ((char *) &data_ov004_02258310) != 0x0) {
        return *(int *) ((char *) *(int *) ((char *) &data_ov004_02258310) + 0xefc);
    }
    return 0x0;
}
