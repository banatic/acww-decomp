/* func_02048e34 @ 0x02048e34, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204edd0(void);

int func_02048e34(void)
{
    int r4 = 0;
    if (func_0204edd0() != 0) {
        r4 = 1;
    }
    return r4;
}
