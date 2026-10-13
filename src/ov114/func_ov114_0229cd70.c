/* func_ov114_0229cd70 @ 0x0229cd70, 0x30 bytes, Thumb, module ov114
 * mwccarm 1.2/base -O4,s
 */

unsigned char *func_ov114_0229cd70(unsigned char *p)
{
    if (p[0x12b6] >= 4) {
        return p + 0x11b0;
    }
    p[0x12b6]++;
    return p + 0x106c + (p[0x12b6] - 1) * 0x6c;
}
