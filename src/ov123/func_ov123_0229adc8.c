/* func_ov123_0229adc8 @ 0x0229adc8, 0x5a bytes, Thumb, module ov123
 * mwccarm 1.2/base -O1,s
 */

extern unsigned int *func_ov123_02299d9c(int);

int func_ov123_0229adc8(int arg0, int x, int y, int val)
{
    unsigned int *base;
    unsigned int *row;
    int col;
    unsigned int *addr;
    int shift;
    unsigned int mask;
    unsigned int data;
    unsigned int nibble;

    if ((unsigned) x >= 32 || (unsigned) y >= 32) {
        return 0;
    }

    base = func_ov123_02299d9c(arg0);
    shift = (x & 7) << 2;
    row = base + y * 4;
    col = x >> 3;
    addr = row + col;
    mask = 0xf << shift;
    data = row[col];
    nibble = (unsigned char) (((data & mask) >> shift) & 0xf);

    if (nibble == val) {
        return 0;
    }

    *addr = data & ~mask;
    *addr |= val << shift;

    return 1;
}
