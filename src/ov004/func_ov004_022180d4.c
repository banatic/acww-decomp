/* func_ov004_022180d4 @ 0x022180d4, 0x2c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_0223c5b8(int a, int b);
extern int func_020308a4(int a, int b);
int func_ov004_022180d4(int *self)
{
    int r;
    if (func_ov004_0223c5b8(self[0], self[1]) == 0 && func_020308a4(self[0], self[1]) == -1) {
        r = 1;
    } else {
        r = 0;
    }
    return r;
}
