/* func_0207ff58 @ 0x0207ff58, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_0207ff58(int a, volatile unsigned short *p)
{
    int r = -1;
    unsigned int ok = 0;
    unsigned short v = *p;
    if (v >= 0xf000 && v <= 0xf02f) {
        ok = 1;
    }
    if (ok != 0) {
        if (v >= 0xf000 && v <= 0xf02f) {
            r = (*p - 0xf000) >> 2;
        } else {
            r = -1;
        }
        if (r >= 3) {
            r = r - 2;
        }
    }
    return r;
}
