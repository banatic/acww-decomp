/* func_ov004_0222dc5c @ 0x0222dc5c, 0x20 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *data_ov004_02258310;
extern int func_ov004_0222e73c(void *p, int n);

int func_ov004_0222dc5c(void)
{
    if (data_ov004_02258310 != 0) {
        return func_ov004_0222e73c(data_ov004_02258310, 7);
    }
    return 0;
}
