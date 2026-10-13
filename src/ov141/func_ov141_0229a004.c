/* func_ov141_0229a004 @ 0x0229a004, 0x24 bytes, Thumb, module ov141
 * mwccarm 1.2/base -O4,s
 */

int func_ov141_0229a004(const unsigned char *p)
{
    int i;
    for (i = 0; i < 6; i++) {
        const unsigned char *q = p + i;
        if (q[0x1a7f] == 0) {
            return i;
        }
    }
    return -1;
}
