/* func_ov104_0229da18 @ 0x0229da18, 0x20 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

unsigned char func_ov104_0229da18(int unused, unsigned int b)
{
    if (b <= 9) {
        return b + 11;
    }
    if (b >= 45 && b <= 54) {
        return b - 24;
    }
    return 33;
}
