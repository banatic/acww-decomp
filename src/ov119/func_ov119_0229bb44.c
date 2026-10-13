/* func_ov119_0229bb44 @ 0x0229bb44, 0x38 bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 */

unsigned char *func_ov119_0229bb44(unsigned char *self)
{
    if (self[0x9e] >= 0x13) {
        return self + 0xc68;
    } else {
        self[0x9e] = (*(volatile unsigned char *) &self[0x9e]) + 1;
        return self + 0x4d0 + (self[0x9e] - 1) * 0x6c;
    }
}
