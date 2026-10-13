/* func_ov004_02234024 @ 0x02234024, 0x36 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

void func_ov004_02234024(int a0, int *p, int b, int c, int d, int e)
{
    int d1 = c - b;
    int d2 = e - d;
    int m1 = d1 < 0 ? -d1 : d1;
    int m2 = d2 < 0 ? -d2 : d2;
    if (m1 >= m2) {
        *p += d1;
    } else {
        *p += d2;
    }
}
