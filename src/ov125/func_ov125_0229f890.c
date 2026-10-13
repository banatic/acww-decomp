/* func_ov125_0229f890 @ 0x0229f890, 0x28 bytes, Thumb, module ov125
 * mwccarm 1.2/base -O4,s
 */

int func_ov125_0229f890(unsigned char *p, unsigned char min, unsigned char max, unsigned char delta)
{
    unsigned char v = p[0x87c];
    if (v >= min && v <= max) {
        p[0x87c] = v + (delta - min);
        return 1;
    }
    return 0;
}
