/* func_ov003_0222c6f0 @ 0x0222c6f0, 0x12 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

int func_ov003_0222c6f0(unsigned short *p)
{
    int r = 0;
    if (*p >= 0xcc && *p <= 0xcf) {
        r = 1;
    }
    return r;
}
