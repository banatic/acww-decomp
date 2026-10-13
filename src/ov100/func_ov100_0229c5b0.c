/* func_ov100_0229c5b0 @ 0x0229c5b0, 0x30 bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

unsigned char *func_ov100_0229c5b0(unsigned char *p)
{
    if (p[0x2927] >= 2) {
        return p + 0x2854;
    }
    p[0x2927]++;
    return p + 0x27e8 + (p[0x2927] - 1) * 108;
}
