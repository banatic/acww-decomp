/* func_ov068_02271c58 @ 0x02271c58, 0x94 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

void func_ov068_02271c58(unsigned char *p, unsigned char *out, int r2, int r3)
{
    short v = *(unsigned char *) (p + 0x254);
    int t = *(int *) (p + 0x224);
    *out = 0;
    if (r3 < 0x2000) {
        v += 25;
    } else {
        if (r3 > t || r2 == 0) {
            *out = 1;
        } else {
            if (r2 <= 1000) {
                v += 1;
            } else if (r2 <= 1100) {
                v += 3;
            } else if (r2 <= 1168) {
                v += 5;
            } else if (r2 == 1169) {
                v += 8;
            } else {
                v += 15;
            }
        }
    }
    if (v > 254) {
        v = 254;
    }
    *(unsigned char *) (p + 0x254) = (unsigned char) v;
}
