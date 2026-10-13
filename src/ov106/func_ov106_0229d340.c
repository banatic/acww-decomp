/* func_ov106_0229d340 @ 0x0229d340, 0x20 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char func_ov106_0229d340(unsigned char r0, unsigned char r1);

unsigned char func_ov106_0229d340(unsigned char r0, unsigned char r1)
{
    if (r1 <= 9) {
        return (unsigned char) (r1 + 11);
    }
    if (r1 >= 0x23 && r1 <= 0x2c) {
        return (unsigned char) (r1 - 14);
    }
    return 0x20;
}
