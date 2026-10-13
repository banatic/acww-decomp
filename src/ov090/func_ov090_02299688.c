/* func_ov090_02299688 @ 0x02299688, 0x74 bytes, Thumb, module ov090
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_ov090_02299880[];
extern int func_020896b8(int a, void *p, int b, int c, int d, int e, int f);

int func_ov090_02299688(unsigned char *self)
{
    int i, j;
    int m1;
    int zeroA;
    int zeroB;

    if (self[0x91] == 0) {
        return 0;
    }

    j = 0;
    i = j;
    m1 = ~j;
    zeroA = j;
    zeroB = j;
    do {
        func_020896b8(1, &data_ov090_02299880[j * 8], 0x80, self[0x92] + 0x50, m1, 2, zeroA);
        func_020896b8(1, &data_ov090_02299880[(j + 1) * 8], 0x80, self[0x92] + 0x50, m1, 2, zeroB);
        i++;
        j += 2;
    } while (i <= 7);
    return 1;
}
