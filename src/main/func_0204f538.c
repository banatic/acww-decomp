/* func_0204f538 @ 0x0204f538, 0x2a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0204f564(int a, int b, int c, int d, int e, int f, unsigned char g);

void func_0204f538(int a, int b, int c, int d, unsigned char e)
{
    int c_high = c >> 4;
    int d_high = d >> 4;
    int c_low = c - (c_high << 4);
    int d_low = d - (d_high << 4);
    func_0204f564(a, b, c_high, d_high, c_low, d_low, e);
}
