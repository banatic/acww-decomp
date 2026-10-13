/* func_ov112_0229f6b8 @ 0x0229f6b8, 0x1a bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

unsigned short func_ov112_0229f6b8(unsigned char *p)
{
    unsigned char n;

    n = p[0xBD];
    if (n == 0) {
        return 0;
    }
    return *(unsigned short *) (p + (n - 1) * 2 + 0xC4);
}
