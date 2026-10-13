/* func_ov110_0229d428 @ 0x0229d428, 0x12 bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

unsigned char func_ov110_0229d428(unsigned int unused, unsigned int r1)
{
    if (r1 >= 0xf && r1 <= 0x1d) {
        return (unsigned char) r1;
    }
    return 0x1f;
}
