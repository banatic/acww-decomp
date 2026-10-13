/* func_ov103_0229cde8 @ 0x0229cde8, 0x14 bytes, Thumb, module ov103
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char func_ov103_0229cde8(unsigned char param1, unsigned char param2);

unsigned char func_ov103_0229cde8(unsigned char param1, unsigned char param2)
{
    if (param2 >= 0xb && param2 <= 0x14) {
        return param2 - 0xb;
    }
    return 0;
}
