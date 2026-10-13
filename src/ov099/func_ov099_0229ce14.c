/* func_ov099_0229ce14 @ 0x0229ce14, 0x14 bytes, Thumb, module ov099
 * mwccarm 1.2/base -O4,s
 */

int func_ov099_0229ce14(int unused, unsigned int value)
{
    if (value >= 15 && value <= 24) {
        return (unsigned char) (value - 15);
    } else {
        return 0;
    }
}
