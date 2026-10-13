/* func_ov110_0229c53c @ 0x0229c53c, 0x38 bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

unsigned char *func_ov110_0229c53c(unsigned char *p)
{
    if (p[0xfb] >= 2) {
        return p + 0x28c0;
    }
    p[0xfb]++;
    return p + 0x2854 + (p[0xfb] - 1) * 0x6c;
}
