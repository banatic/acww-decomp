/* func_ov105_0229d718 @ 0x0229d718, 0x24 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

unsigned char func_ov105_0229d718(unsigned int a, unsigned int n)
{
    if (n >= 26 && n <= 35) {
        return n - 26;
    } else if (n >= 36 && n <= 60) {
        return n - 26;
    } else {
        return 0;
    }
}
