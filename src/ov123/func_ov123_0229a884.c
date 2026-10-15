/* func_ov123_0229a884 @ 0x0229a884, 0x56 bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int *func_ov123_02299d9c(int);

int func_ov123_0229a884(int a0, int a1, int a2, int a3, int a4)
{
    unsigned int (*base)[4] = (unsigned int (*)[4]) func_ov123_02299d9c(a0);
    int x = a1;
    int end = a2;
    int zero = 0;
    unsigned int *ptr = base[a3] + (x >> 3);
    int shift = (x & 7) * 4;

    while (x <= end) {
        if (a4 == (unsigned char) ((*ptr >> shift) & 0xf)) {
            return x;
        }
        shift += 4;
        if (shift >= 32) {
            shift = zero;
            ptr++;
        }
        x++;
    }
    return -1;
}
