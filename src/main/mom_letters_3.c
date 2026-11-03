/* mom_letters_3: 12 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02097dd0 @ 0x02097dd0, 0x2 bytes, Thumb
 * func_02097dcc @ 0x02097dcc, 0x2 bytes, Thumb
 * func_02097dac @ 0x02097dac, 0x1e bytes, Thumb
 * func_02097d68 @ 0x02097d68, 0x44 bytes, Thumb
 * func_02097d50 @ 0x02097d50, 0x18 bytes, Thumb
 * func_02097d48 @ 0x02097d48, 0x8 bytes, Thumb
 * func_02097d38 @ 0x02097d38, 0x10 bytes, Thumb
 * func_02097d18 @ 0x02097d18, 0x1e bytes, Thumb
 * func_02097cf8 @ 0x02097cf8, 0x1e bytes, Thumb
 * func_02097cd4 @ 0x02097cd4, 0x24 bytes, Thumb
 * func_02097cc8 @ 0x02097cc8, 0xc bytes, Thumb
 * func_02097cbc @ 0x02097cbc, 0xc bytes, Thumb
 */

void func_02097d50(unsigned char *dest, const unsigned int *src);
void func_02097d48(unsigned char *p0, int p1);
int func_02097d38(unsigned char *p, unsigned int mask);

void func_02097dd0(void *object) {}

void func_02097dcc(void *object) {}

void func_02097dac(unsigned char *r0)
{
    unsigned char *p;
    int i;

    r0[0] = 1;
    r0[1] = 1;
    r0[2] = 0;
    r0[3] = 0;

    for (i = 0; i < 0xf; i++) {
        p = r0 + i;
        p[4] = 0;
    }

    r0[3] = 0x64;
}

int func_02097d68(const unsigned char *a, const int *b)
{
    if (func_02097d38((unsigned char *) a, 0x80)) {
        if (a[2] == b[0] && a[1] == b[1] && a[0] == b[2]) {
            return 1;
        } else {
            return 0;
        }
    } else {
        func_02097d50((unsigned char *) a, (const unsigned int *) b);
        return 1;
    }
}

void func_02097d50(unsigned char *dest, const unsigned int *src)
{
    dest[2] = (unsigned char) src[0];
    dest[1] = (unsigned char) src[1];
    dest[0] = (unsigned char) src[2];
    func_02097d48((unsigned char *) dest, 0x80);
}

void func_02097d48(unsigned char *p0, int p1)
{
    p0[3] = (p0[3] | p1);
}

int func_02097d38(unsigned char *p, unsigned int mask)
{
    if ((p[3] & mask) == 0) {
        return 0;
    } else {
        return 1;
    }
}

void func_02097d18(unsigned char *param0, int param1)
{
    unsigned char *r5;
    int r4;
    unsigned char r3;
    int r2;
    int r0;

    r5 = param0 + 4;
    r4 = param1 >> 3;
    r3 = r5[r4];
    r2 = 1;
    r0 = 7;
    r2 = r2 << (param1 & r0);
    r3 = r3 | r2;
    r5[r4] = r3;
}

void func_02097cf8(unsigned char *base, int bit)
{
    base += 4;
    base[bit >> 3] &= ~(1 << (bit & 7));
}

int func_02097cd4(unsigned char *data, int index)
{
    int mask;
    mask = 1 << (index & 7);
    return (mask & *(data + (index >> 3) + 4)) != 0;
}

unsigned char func_02097cc8(unsigned char *param)
{
    unsigned char value;
    value = param[3] & 0x7f;
    return value;
}

void func_02097cbc(unsigned char *p, unsigned char value)
{
    value |= (p[3] & 0x80);
    p[3] = value;
}
