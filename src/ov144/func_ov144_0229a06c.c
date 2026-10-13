/* func_ov144_0229a06c @ 0x0229a06c, 0x38 bytes, Thumb, module ov144
 * mwccarm 1.2/base -O4,s
 */

unsigned char *func_ov144_0229a06c(volatile unsigned char *p)
{
    if (p[0xbf] >= 9) {
        return (unsigned char *) p + 0x69c;
    }
    p[0xbf] = p[0xbf] + 1;
    return (unsigned char *) p + 0x33c + 0x6c * (p[0xbf] - 1);
}
