/* vector_3: 5 functions, module autoload_2
 * mwccarm 1.2/base -O4,s
 * func_020eacf8 @ 0x020eacf8, 0x50 bytes, ARM
 * func_020eace4 @ 0x020eace4, 0x14 bytes, ARM
 * func_020eaca0 @ 0x020eaca0, 0x44 bytes, ARM
 * func_020eac34 @ 0x020eac34, 0x6c bytes, ARM
 * func_020eabc8 @ 0x020eabc8, 0x6c bytes, ARM
 */

#define g_040002b0 (*(unsigned short *) 0x040002b0)

int func_020eacf8(long long v)
{
    volatile unsigned short *ctrl = (volatile unsigned short *) 0x040002b0;
    volatile unsigned long long *numer = (volatile unsigned long long *) 0x040002b8;
    volatile int *res = (volatile int *) 0x040002b4;

    *ctrl = 1;
    *numer = (unsigned long long) v << 2;
    while (*ctrl & 0x8000)
        ;
    return (*res + 1) >> 1;
}

void func_020eace4(void)
{
    g_040002b0 = 1;
}

void func_020eaca0(int *r0, int *r1, int *r2)
{
    int a, b, c, d, e, f;

    a = r1[0];
    b = r2[0];
    c = r1[2];
    d = r2[2];
    e = r1[1];
    f = r2[1];

    r0[0] = a - b;
    r0[1] = e - f;
    r0[2] = c - d;
}

void func_020eac34(long *out, long *in, long scale)
{
    long long x, y, z;
    z = ((long long) in[2] * scale + 0x800) >> 12;
    y = ((long long) in[1] * scale + 0x800) >> 12;
    x = ((long long) in[0] * scale + 0x800) >> 12;
    out[0] = (long) x;
    out[1] = (long) y;
    out[2] = (long) z;
}

void func_020eabc8(int *v, int scale)
{
    v[0] = (int) (((long long) v[0] * scale + 0x800) >> 12);
    v[1] = (int) (((long long) v[1] * scale + 0x800) >> 12);
    v[2] = (int) (((long long) v[2] * scale + 0x800) >> 12);
}
