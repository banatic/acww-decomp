/* func_ov128_0229b7ec @ 0x0229b7ec, 0x18 bytes, Thumb, module ov128
 * mwccarm 1.2/base -O4,s
 */

int func_ov128_0229b7ec(unsigned char *base, unsigned short mask)
{
    unsigned short v = *(unsigned short *) (base + 0x2d68);
    v &= mask;
    if (v == 0) {
        return 0;
    } else {
        return 1;
    }
}
