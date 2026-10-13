/* func_020545b0 @ 0x020545b0, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_020545b0(unsigned char *base, unsigned int bit)
{
    if (bit >= 32) {
        *(unsigned int *) (base + 0x1B0) |= 1u << (bit - 32);
    } else {
        *(unsigned int *) (base + 0x1AC) |= 1u << bit;
    }
}
