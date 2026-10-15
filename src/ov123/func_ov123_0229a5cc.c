/* func_ov123_0229a5cc @ 0x0229a5cc, 0x70 bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short *data_ov123_0229cf8c[];
extern int func_ov123_0229adc8(int, unsigned char, unsigned char, int);

void func_ov123_0229a5cc(int a, int b, int c, int d, int e)
{
    int row;
    int col;
    unsigned short *ptr;
    int y;
    unsigned int mask;
    int x;
    int base;
    row = c - 8;
    ptr = data_ov123_0229cf8c[e];
    y = 0;
    base = b - 7;
    do {
        mask = 0x8000;
        col = base;
        x = 0;
        do {
            if (mask & (*ptr)) {
                func_ov123_0229adc8(a, (unsigned char) col, (unsigned char) row, d);
            }
            mask = (mask << 15) >> 16;
            col++;
            x++;
        } while (x < 16);
        ptr++;
        row++;
        y++;
    } while (y < 16);
}
