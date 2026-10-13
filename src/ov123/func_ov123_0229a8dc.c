/* func_ov123_0229a8dc @ 0x0229a8dc, 0x3a bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

/* FAKEMATCH: the empty if keeps the row pointer formed before the column index; the plain expression adds it after the index */

extern unsigned int (*func_ov123_02299d9c(int, int, int, int))[4];

unsigned char func_ov123_0229a8dc(int p0, unsigned int p1, unsigned int p2, int p3)
{
    unsigned int (*base)[4];
    unsigned int *row;

    if (p1 >= 0x20 || p2 >= 0x20) {
        return 1;
    }

    base = func_ov123_02299d9c(p0, p1, p2, p3);
    row = base[p2];
    if ((row && row) && row) {
    }
    return (unsigned char) ((row[(int) p1 >> 3] >> ((p1 & 7) * 4)) & 0xf);
}
