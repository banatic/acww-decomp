/* func_ov123_0229a82c @ 0x0229a82c, 0x56 bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char *func_ov123_02299d9c(int, int, int, int);

int func_ov123_0229a82c(int a0, int count, int unit, int value)
{
    unsigned char *base;
    unsigned char *ptr;
    unsigned int word;
    int i;
    int shift;
    int nibble;

    if (count <= 0) {
        return 0;
    }

    i = count - 1;
    base = func_ov123_02299d9c(a0, count, unit, value);
    ptr = base + (unit << 4) + ((i >> 3) << 2);
    shift = (i & 7) << 2;

    while (i >= 0) {
        word = *(unsigned int *) ptr;
        nibble = (unsigned char) ((word >> shift) & 0xf);
        if (value != nibble) {
            return i + 1;
        }
        shift -= 4;
        if (shift < 0) {
            shift = 28;
            ptr -= 4;
        }
        i--;
    }
    return 0;
}
