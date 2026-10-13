/* func_0204f31c @ 0x0204f31c, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204f340(int, int, int, int, int);

int func_0204f31c(int a, int b, int c)
{
    int q1;
    int q2;
    int r1;
    int r2;
    q1 = b >> 4;
    q2 = c >> 4;
    r2 = c - (q2 << 4);
    r1 = b - (q1 << 4);
    return func_0204f340(a, q1, q2, r1, r2);
}
