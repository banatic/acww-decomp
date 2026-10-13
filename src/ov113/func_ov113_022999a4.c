/* func_ov113_022999a4 @ 0x022999a4, 0x20 bytes, Thumb, module ov113
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char func_ov113_022999a4(unsigned char *p);

unsigned char func_ov113_022999a4(unsigned char *p)
{
    unsigned char v;
    v = p[0x9b];
    if (v <= 3) {
        return 0xaa;
    }
    if (v <= 5) {
        return 0x56;
    }
    if (v <= 0x14) {
        return 0x98;
    }
    return 0x60;
}
