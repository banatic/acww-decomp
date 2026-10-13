/* func_ov145_022998c4 @ 0x022998c4, 0x2c bytes, Thumb, module ov145
 * mwccarm 1.2/base -O4,s
 */

int func_ov145_022998c4(int unused, int target, int val)
{
    int i;
    int low;

    if (val >= 0x9d && val < 0xbd) {
        for (low = 0x84, i = 0; i < 4; low -= 0x24, i++) {
            if (low > target || low + 0x20 <= target) {
                continue;
            }
            return (unsigned char) i;
        }
    }
    return 6;
}
