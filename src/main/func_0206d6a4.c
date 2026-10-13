/* func_0206d6a4 @ 0x0206d6a4, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_021ce3f4[];

int func_0206d6a4(unsigned short *p, int n, int off)
{
    unsigned short a;
    unsigned short b;
    int i;
    unsigned short *base;
    base = &data_021ce3f4[off];

    for (i = 0; i < 3; i++) {
        if (i >= n) {
            a = base[i];
            if (a == 0x3000 || a == 0x20 || a == 0) {
                return 1;
            }
            return 0;
        }
        a = base[i];
        b = p[i];
        if (b != a) {
            if (a == 0x3000 || a == 0x20 || a == 0) {
                return 1;
            }
            return 0;
        }
        if (b == 0x3000 || b == 0x20) {
            return 1;
        }
    }
    return 1;
}
