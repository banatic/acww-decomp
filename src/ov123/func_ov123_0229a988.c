/* func_ov123_0229a988 @ 0x0229a988, 0x28 bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

extern int *func_ov123_02299d9c(int *p, int x);

void func_ov123_0229a988(int *dst, int x)
{
    int i;
    int val;
    dst = func_ov123_02299d9c(dst, x);
    val = x * 0x11111111;
    for (i = 0; i < 32; i++) {
        dst[0] = val;
        dst[1] = val;
        dst[2] = val;
        dst[3] = val;
        dst += 4;
    }
}
