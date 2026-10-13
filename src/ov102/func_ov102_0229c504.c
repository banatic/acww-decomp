/* func_ov102_0229c504 @ 0x0229c504, 0x30 bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

unsigned char *func_ov102_0229c504(unsigned char *base)
{
    unsigned char v = base[0x25a8];
    if (v >= 2) {
        return base + 0x2460;
    }
    v++;
    base[0x25a8] = v;
    return base + 0x23f4 + (base[0x25a8] - 1) * 0x6c;
}
