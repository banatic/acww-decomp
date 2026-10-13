/* func_0206d714 @ 0x0206d714, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206d6a4(unsigned short *p, int n, int off);
extern int data_021ce2f4;
extern unsigned char data_021ce2f8[];

int func_0206d714(unsigned short *p0, int p1)
{
    int i = 0;
    int j = 0;
    int idx;
    int shift;
    int mask;
    int byte;
    int field;

    while (i < data_021ce2f4) {
        if (func_0206d6a4(p0, p1, j)) {
            idx = i >> 2;
            shift = (i & 3) * 2;
            mask = 3 << shift;
            byte = data_021ce2f8[idx];
            field = (byte & mask) >> shift;
            if (field >= 2) {
                return 0;
            }
            data_021ce2f8[idx] &= ~mask;
            data_021ce2f8[idx] |= (field + 1) << shift;
            return 1;
        }
        j += 3;
        i++;
    }
    return 0;
}
