/* func_ov123_0229ab18 @ 0x0229ab18, 0x68 bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov123_0229adc8(int, int, int, int);

void func_ov123_0229ab18(unsigned char a, unsigned char b, unsigned char c, unsigned int d, unsigned int e, int f)
{
    unsigned char i;
    unsigned char j;
    for (i = b; i <= d; i++) {
        func_ov123_0229adc8(a, i, c, f);
        func_ov123_0229adc8(a, i, e, f);
    }
    for (j = c; j <= e; j++) {
        func_ov123_0229adc8(a, b, j, f);
        func_ov123_0229adc8(a, d, j, f);
    }
}
