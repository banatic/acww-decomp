/* func_0204f380 @ 0x0204f380, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204f3a4(int, int, int, int, int);

void func_0204f380(int a, int b, int c)
{
    int b_hi = b >> 4;
    int c_hi = c >> 4;
    int c_lo = c - (c_hi << 4);
    func_0204f3a4(a, b_hi, c_hi, b - (b_hi << 4), c_lo);
}
