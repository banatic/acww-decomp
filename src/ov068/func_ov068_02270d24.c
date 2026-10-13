/* func_ov068_02270d24 @ 0x02270d24, 0x30 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

void func_ov068_02270d24(int *r0, int r1)
{
    if (r1 == 0) {
        r0[2] -= 0x52;
    } else {
        r0[2] += 0x52;
    }

    if (r0[2] < 0x1000) {
        r0[2] = 0x1000;
    } else if (r0[2] > 0x2000) {
        r0[2] = 0x2000;
    }
}
