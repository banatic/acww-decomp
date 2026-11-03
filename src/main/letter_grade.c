/* letter_grade: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0206d7a0 @ 0x0206d7a0, 0xc bytes, Thumb
 * func_0206d780 @ 0x0206d780, 0x20 bytes, Thumb
 * func_0206d714 @ 0x0206d714, 0x6c bytes, Thumb
 * func_0206d6a4 @ 0x0206d6a4, 0x70 bytes, Thumb
 */

extern int func_02051c8c_unk(void *ptr, int value);
extern unsigned short data_020ccf5c[];
extern int data_021ce2f4;
extern unsigned char data_021ce2f8[];
extern unsigned short data_021ce3f4[];

int func_0206d6a4(unsigned short *p, int n, int off);

int func_0206d7a0(void *ptr)
{
    return func_02051c8c_unk((char *) ptr + 0x58, 0x40);
}

int func_0206d780(unsigned short param)
{
    int i;
    for (i = 0; i < 7; i++) {
        if (param == data_020ccf5c[i]) {
            return 1;
        }
    }
    return 0;
}

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
