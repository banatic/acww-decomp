/* func_ov105_0229d6f8 @ 0x0229d6f8, 0x20 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

unsigned char func_ov105_0229d6f8(unsigned int a, unsigned int b)
{
    if (b <= 9) {
        return b + 0x1a;
    } else if (b >= 10 && b <= 0x22) {
        return b + 0x1a;
    } else {
        return 0x40;
    }
}
