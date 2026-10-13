/* func_ov132_0229ad88 @ 0x0229ad88, 0x30 bytes, Thumb, module ov132
 * mwccarm 1.2/base -O4,s
 */

unsigned char *func_ov132_0229ad88(unsigned char *self)
{
    if (self[0x1504] >= 2) {
        return self + 0x330;
    } else {
        self[0x1504] = self[0x1504] + 1;
        return self + 0x2c4 + 0x6c * (self[0x1504] - 1);
    }
}
