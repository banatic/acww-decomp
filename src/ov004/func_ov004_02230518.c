/* func_ov004_02230518 @ 0x02230518, 0x20 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *data_ov004_02258870;
extern int func_ov004_0223080c(void *p, int n);

int func_ov004_02230518(void)
{
    if (data_ov004_02258870 != 0) {
        return func_ov004_0223080c(data_ov004_02258870, 1);
    }
    return 0;
}
