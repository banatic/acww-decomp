/* func_ov004_02230d70 @ 0x02230d70, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_0223121c();
extern void *data_ov004_022588c8;

int func_ov004_02230d70(char *self)
{
    // DECLS
    // ENDDECLS
    if (*(int *) ((char *) &data_ov004_022588c8) != 0x0) {
        func_ov004_0223121c(*(int *) ((char *) &data_ov004_022588c8), 0xa);
        return 0x1;
    }
    return 0x0;
}
