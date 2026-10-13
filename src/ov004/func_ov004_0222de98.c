/* func_ov004_0222de98 @ 0x0222de98, 0x1c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_0222e860(int);
extern void *data_ov004_02258310;

int func_ov004_0222de98(char *self)
{
    // DECLS
    // ENDDECLS
    if (*(int *) ((char *) &data_ov004_02258310) != 0x0) {
        return func_ov004_0222e860(*(int *) ((char *) &data_ov004_02258310));
    }
    return *(int *) ((char *) &data_ov004_02258310);
}
