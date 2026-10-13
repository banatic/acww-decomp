/* func_ov102_0229c2a8 @ 0x0229c2a8, 0x18 bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

int func_ov102_0229c2a8(unsigned int *base, unsigned int mask)
{
    if ((base[0x933] & mask) != 0) {
        return 1;
    }
    return 0;
}
