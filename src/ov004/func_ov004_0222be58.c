/* func_ov004_0222be58 @ 0x0222be58, 0x22 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_02096718(int);
extern int func_ov004_02226d14(int, int, int);

int func_ov004_0222be58(void)
{
    int r;

    r = func_02096718(4);
    if (r != 0) {
        return func_ov004_02226d14(r, 6, -1);
    }
    return 0;
}
