/* func_ov095_0229af84 @ 0x0229af84, 0x12 bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

unsigned char func_ov095_0229af84(unsigned char *p)
{
    unsigned int idx = p[0x17];
    if (idx >= 4) {
        return 0xFF;
    }
    return *(p + idx + 0x3c);
}
