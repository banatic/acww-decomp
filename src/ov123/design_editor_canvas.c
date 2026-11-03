/* design_editor_canvas: 6 functions, module ov123
 * mwccarm 1.2/base -O4,s
 * func_ov123_0229a988 @ 0x0229a988, 0x28 bytes, Thumb
 * func_ov123_0229a918 @ 0x0229a918, 0x70 bytes, Thumb
 * func_ov123_0229a8dc @ 0x0229a8dc, 0x3a bytes, Thumb
 * func_ov123_0229a884 @ 0x0229a884, 0x56 bytes, Thumb
 * func_ov123_0229a82c @ 0x0229a82c, 0x56 bytes, Thumb
 * func_ov123_0229a7d4 @ 0x0229a7d4, 0x56 bytes, Thumb
 */

extern int func_ov123_0229a63c(void *, int, int, void *);
extern int data_ov123_0229cb2c[];
extern unsigned char *func_ov123_02299d9c(int);

void func_ov123_0229a988(int *dst, int x)
{
    int i;
    int val;
    dst = (int *) func_ov123_02299d9c((int) dst);
    val = x * 0x11111111;
    for (i = 0; i < 32; i++) {
        dst[0] = val;
        dst[1] = val;
        dst[2] = val;
        dst[3] = val;
        dst += 4;
    }
}

void func_ov123_0229a918(void *a, void *b)
{
    int *p;
    int *q;
    int i;
    int init;
    int o;

    p = (int *) func_ov123_02299d9c((int) a);
    init = 0;
    o = 0;
    while (o < 2) {
        q = data_ov123_0229cb2c;
        i = init;
        while (i < 16) {
            p[0] = func_ov123_0229a63c(a, p[0], q[0], b);
            p[1] = func_ov123_0229a63c(a, p[1], q[1], b);
            p[2] = func_ov123_0229a63c(a, p[2], q[0], b);
            p[3] = func_ov123_0229a63c(a, p[3], q[1], b);
            p += 4;
            q += 2;
            i++;
        }
        o++;
    }
}

unsigned char func_ov123_0229a8dc(int p0, unsigned int p1, unsigned int p2)
{
    unsigned int *row;

    if (p1 >= 0x20 || p2 >= 0x20) {
        return 1;
    }

    row = ((unsigned int (*)[4]) (char *) func_ov123_02299d9c((int) ((char *) p0)))[p2];
    return (unsigned char) ((row[(int) p1 >> 3] >> ((p1 & 7) * 4)) & 0xf);
}

int func_ov123_0229a884(int a0, int a1, int a2, int a3, int a4)
{
    unsigned int (*base)[4] = (unsigned int (*)[4]) func_ov123_02299d9c(a0);
    int x = a1;
    int end = a2;
    int zero = 0;
    unsigned int *ptr = base[a3] + (x >> 3);
    int shift = (x & 7) * 4;

    while (x <= end) {
        if (a4 == (unsigned char) ((*ptr >> shift) & 0xf)) {
            return x;
        }
        shift += 4;
        if (shift >= 32) {
            shift = zero;
            ptr++;
        }
        x++;
    }
    return -1;
}

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
    base = func_ov123_02299d9c(a0);
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

int func_ov123_0229a7d4(int a, int b, int c, int d)
{
    int idx;
    unsigned char *p;
    int shift;
    unsigned char val;

    if (b >= 31) {
        return 31;
    }
    idx = b + 1;
    p = func_ov123_02299d9c(a) + (c << 4) + ((idx >> 3) * 4);
    shift = (idx & 7) * 4;
    while (idx <= 31) {
        val = (unsigned char) ((*(unsigned int *) p >> shift) & 0xf);
        if (d != val) {
            return idx - 1;
        }
        shift += 4;
        if (shift > 28) {
            shift = 0;
            p += 4;
        }
        idx++;
    }
    return 31;
}
