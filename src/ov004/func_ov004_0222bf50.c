/* func_ov004_0222bf50 @ 0x0222bf50, 0x22 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_02096718(int);
extern int func_ov004_02227fe4(int, int, int);

int func_ov004_0222bf50(void)
{
    int r;

    r = func_02096718(4);
    if (r != 0) {
        return func_ov004_02227fe4(r, 6, -1);
    }
    return 0;
}
