/* func_ov106_0229d360 @ 0x0229d360, 0x24 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

unsigned char func_ov106_0229d360(unsigned int arg0, unsigned int x)
{
    if (x >= 11 && x <= 20) {
        x -= 11;
        return (unsigned char) x;
    } else if (x >= 21 && x <= 30) {
        x += 14;
        return (unsigned char) x;
    }
    return 0;
}
