/* func_ov123_0229a7d4 @ 0x0229a7d4, 0x56 bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char *func_ov123_02299d9c(int a, int b, int c, int d);

int func_ov123_0229a7d4(int a, int b, int c, int d)
{
    int idx;
    unsigned char *p;
    int shift;
    unsigned char val;

    if (b >= 31) {
        return 31;
    }
    idx = b + 1;
    p = func_ov123_02299d9c(a, b, c, d) + (c << 4) + ((idx >> 3) * 4);
    shift = (idx & 7) * 4;
    while (idx <= 31) {
        val = (unsigned char) ((*(unsigned int *) p >> shift) & 0xf);
        if (d != val) {
            return idx - 1;
        }
        shift += 4;
        if (shift > 28) {
            shift = 0;
            p += 4;
        }
        idx++;
    }
    return 31;
}
