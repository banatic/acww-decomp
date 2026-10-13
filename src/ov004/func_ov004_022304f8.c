/* func_ov004_022304f8 @ 0x022304f8, 0x20 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *data_ov004_02258870;
extern int func_ov004_0223080c(void *p, int n);

int func_ov004_022304f8(void)
{
    if (data_ov004_02258870 != 0) {
        return func_ov004_0223080c(data_ov004_02258870, 2);
    }
    return 0;
}
