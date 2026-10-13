/* func_ov114_0229cdcc @ 0x0229cdcc, 0x18 bytes, Thumb, module ov114
 * mwccarm 1.2/base -O4,s
 */

unsigned char func_ov114_0229cdcc(unsigned char *p)
{
    unsigned char v = p[0x12b4];
    if (v >= 9) {
        return 8;
    } else {
        p[0x12b4] = v + 1;
        return v;
    }
}
