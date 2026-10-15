/* func_ov123_0229a8dc @ 0x0229a8dc, 0x3a bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

extern char *func_ov123_02299d9c(char *p);

unsigned char func_ov123_0229a8dc(int p0, unsigned int p1, unsigned int p2)
{
    unsigned int *row;

    if (p1 >= 0x20 || p2 >= 0x20) {
        return 1;
    }

    row = ((unsigned int (*)[4]) func_ov123_02299d9c((char *) p0))[p2];
    return (unsigned char) ((row[(int) p1 >> 3] >> ((p1 & 7) * 4)) & 0xf);
}
