/* func_ov004_0220feac @ 0x0220feac, 0x22 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_020ea990(int a, int c);
int func_ov004_0220feac(int a, int b, int c, int d)
{
    int r;
    if (func_020ea990(a, c) < b + d) {
        r = 1;
    } else {
        r = 0;
    }
    return r;
}
