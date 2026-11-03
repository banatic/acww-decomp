/* villager_bonds: 15 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02079cc0 @ 0x02079cc0, 0x2 bytes, Thumb
 * func_02079cbc @ 0x02079cbc, 0x2 bytes, Thumb
 * func_02079cb0 @ 0x02079cb0, 0xc bytes, Thumb
 * func_02079ca4 @ 0x02079ca4, 0xc bytes, Thumb
 * func_02079c74 @ 0x02079c74, 0x2e bytes, Thumb
 * func_02079c30 @ 0x02079c30, 0x44 bytes, Thumb
 * func_02079c00 @ 0x02079c00, 0x30 bytes, Thumb
 * func_02079bc4 @ 0x02079bc4, 0x3c bytes, Thumb
 * func_02079b7c @ 0x02079b7c, 0x48 bytes, Thumb
 * func_02079b3c @ 0x02079b3c, 0x40 bytes, Thumb
 * func_02079b08 @ 0x02079b08, 0x34 bytes, Thumb
 * func_02079a88 @ 0x02079a88, 0x80 bytes, Thumb
 * func_02079a5c @ 0x02079a5c, 0x2a bytes, Thumb
 * func_02079a24 @ 0x02079a24, 0x36 bytes, Thumb
 * func_02079994 @ 0x02079994, 0x8e bytes, Thumb
 */

struct Pair {
    unsigned char a;
    unsigned char b;
};

extern void MI_CpuFill8(void *dest, unsigned char data, unsigned int size);
extern int func_0207cf74(int);
extern int func_02003704(int);
extern int func_020036e8(int);
extern unsigned char data_020cd500[][6];
extern int func_0208090c(int);
extern unsigned char data_020cd484[][4];
extern int func_020808ec(int);
extern struct Pair data_020cd464[];
extern struct Pair data_020cd434[];
extern int func_02080890(int);
extern int func_0208150c(int);

void func_02079cc0(void *object) {}

void func_02079cbc(void *object) {}

void func_02079cb0(void *dest)
{
    MI_CpuFill8(dest, 0, 0x1c);
}

int func_02079ca4(int a, unsigned int b)
{
    if (b >= 28) {
        return 0;
    } else {
        return 1;
    }
}

int func_02079c74(int p0, int p1, int p2)
{
    int sum = 0;
    int low = p1;
    int high = p2;
    int i;
    if (p1 > p2) {
        low = p2;
        high = p1;
    }
    for (i = 0; i < low; i++) {
        sum += 7 - i;
    }
    sum += high - low - 1;
    return sum;
}

void func_02079c30(char *a, int b)
{
    int i;
    int v;
    if (func_0207cf74(b) != 0) {
        for (i = 0; i < 8; i++) {
            if (i == b) {
                continue;
            }
            v = func_02079c74((int) a, b, i);
            if (func_02079ca4((int) a, v) != 0) {
                a[v] = 0;
            }
        }
    }
}

void func_02079c00(signed char *base, int index, int value)
{
    int sum;
    if (func_02079ca4((int) base, index)) {
        sum = base[index] + value;
        if (sum > 127) {
            sum = 127;
        } else if (sum < -128) {
            sum = -128;
        }
        base[index] = (signed char) sum;
    }
}

void func_02079bc4(int a, int b, int c, int d)
{
    if (func_0207cf74(b) != 0 && func_0207cf74(c) != 0) {
        func_02079c00((signed char *) a, func_02079c74(a, b, c), d);
    }
}

int func_02079b7c(signed char *a, int b, int c)
{
    int ret = 0x80000000;
    int idx;
    if (func_0207cf74(b) && func_0207cf74(c)) {
        idx = func_02079c74((int) a, b, c);
        if (func_02079ca4((int) a, idx)) {
            ret = a[idx];
        }
    }
    return ret;
}

int func_02079b3c(int a, int b, int c)
{
    int result = 0;
    if (func_02003704(b) && func_02003704(c)) {
        result = data_020cd500[func_020036e8(b)][func_020036e8(c)];
    }
    return result;
}

unsigned char func_02079b08(int unused, int a, int b)
{
    unsigned char first = (unsigned char) (func_0208090c(a) & 3);
    unsigned char second = (unsigned char) (func_0208090c(b) & 3);
    return data_020cd484[first][second];
}

int func_02079a88(int a, int b, int c)
{
    int x;
    int y;
    struct Pair *p;
    int i;
    x = func_020808ec(b);
    y = func_020808ec(c);
    if (x == y) {
        return 0x40;
    }
    p = data_020cd464;
    for (i = 0; i < 7; p++, i++) {
        if (((p->a == x) && (p->b == y)) || ((p->b == x) && (p->a == y))) {
            return 0x80;
        }
    }

    p = data_020cd434;
    for (i = 0; i < 4; p++, i++) {
        if (((p->a == x) && (p->b == y)) || ((p->b == x) && (p->a == y))) {
            return 0x00;
        }
    }

    return 0x20;
}

int func_02079a5c(int param1, int param2, int param3)
{
    int result;
    int val;
    int val2;

    val = func_02080890(param2);
    val2 = func_02080890(param3);
    result = 0;
    if (val != 0 && val2 != 0) {
        result = 0x3f;
    }
    return result;
}

int func_02079a24(int unused, void *arg1, void *arg2)
{
    void *f1 = (void *) func_02080890((int) arg1);
    void *f2 = (void *) func_02080890((int) arg2);
    int result = 0;
    if (f1 && f2) {
        unsigned char b = ((unsigned char *) f2)[4];
        unsigned char a = ((unsigned char *) f1)[4];
        if (a > b) {
            result = a - b;
        } else {
            result = b - a;
        }
    }
    return result;
}

int func_02079994(int r7, int r5, int r6)
{
    int r4 = 0;
    if (r5 == 0) {
        goto end;
    }
    if (func_02003704(func_0208150c(r5)) == 0) {
        goto end;
    }
    if (r6 == 0) {
        goto end;
    }
    if (func_02003704(func_0208150c(r6)) == 0) {
        goto end;
    }
    r4 = func_02079b3c(r7, func_0208150c(r5), func_0208150c(r6));
    r4 += (int) func_02079b08(r7, r5, r6);
    r4 += func_02079a88(r7, r5, r6);
    r4 += func_02079a5c(r7, r5, r6);
    if (r4 >= 200) {
        goto end;
    }
    r4 -= func_02079a24(r7, (void *) r5, (void *) r6);
    if (r4 < 0) {
        r4 = -r4;
    }
end:
    return r4;
}
