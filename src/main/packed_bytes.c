/* packed_bytes: 16 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02077a54 @ 0x02077a54, 0x10 bytes, Thumb
 * func_02077a34 @ 0x02077a34, 0x1e bytes, Thumb
 * func_02077a14 @ 0x02077a14, 0x1e bytes, Thumb
 * func_020779d8 @ 0x020779d8, 0x3c bytes, Thumb
 * func_020779b8 @ 0x020779b8, 0x20 bytes, Thumb
 * func_02077978 @ 0x02077978, 0x40 bytes, Thumb
 * func_02077950 @ 0x02077950, 0x28 bytes, Thumb
 * func_02077928 @ 0x02077928, 0x28 bytes, Thumb
 * func_02077910 @ 0x02077910, 0x18 bytes, Thumb
 * func_020778f8 @ 0x020778f8, 0x18 bytes, Thumb
 * func_020778e0 @ 0x020778e0, 0x18 bytes, Thumb
 * func_020778c8 @ 0x020778c8, 0x18 bytes, Thumb
 * func_020778b0 @ 0x020778b0, 0x18 bytes, Thumb
 * func_02077898 @ 0x02077898, 0x16 bytes, Thumb
 * func_02077880 @ 0x02077880, 0x18 bytes, Thumb
 * func_02077868 @ 0x02077868, 0x16 bytes, Thumb
 */

typedef struct {
    int a;
    int b;
    int c;
} UnkStruct_020778e0;

typedef struct {
    int a;
    int b;
    int c;
} UnkStruct_02077880;

extern void MI_CpuCopy8(int *dst, int src, int n);

void func_02077a54(unsigned char *out, unsigned char a, unsigned char b)
{
    *out = ((b << 6) & 0xC0) | (a & 0x3F);
}

void func_02077a34(unsigned char *a, unsigned char *b, unsigned char *c)
{
    if (c) {
        *c = ((unsigned int) *a >> 6) & 3;
    }
    *b = *a & 0x3f;
}

void func_02077a14(unsigned char *out, int val, int ctrl)
{
    out[0] = ((ctrl << 4) & 0xF0) | ((val >> 16) & 0x0F);
    out[1] = (unsigned char) (val >> 8);
    out[2] = (unsigned char) val;
}

void func_020779d8(const unsigned char *p, unsigned int *out, unsigned char *q)
{
    if (q) {
        *q = ((unsigned int) p[0] >> 4) & 0xF;
    }
    *out = (p[2] & 0xFF) | (((p[0] << 16) & 0x000F0000) | ((p[1] << 8) & 0x0000FF00));
}

void func_020779b8(unsigned char *ptr, int val, int other)
{
    *ptr = (unsigned char) (val >> 8);
    *(ptr + 1) = (unsigned char) val;
    ptr += 2;
    func_02077a14(ptr, other, (unsigned char) ((unsigned char) ((val >> 16) & 0xf)));
}

void func_02077978(const unsigned char *p, unsigned int *out, unsigned int *arg)
{
    unsigned char tmp;
    func_020779d8(p + 2, arg, &tmp);
    *out = (p[1] & 0xFF) | (((tmp << 16) & 0x000F0000) | ((p[0] << 8) & 0x0000FF00));
}

void func_02077950(int a, int b, int c, int d, unsigned char e)
{
    func_020779b8((unsigned char *) a, b, c + 0x80000);
    func_02077a14((unsigned char *) (a + 5), d, e);
}

void func_02077928(int a, int b, int *c, int d, int e)
{
    func_02077978((const unsigned char *) a, (unsigned int *) b, (unsigned int *) c);
    *c -= 0x80000;
    func_020779d8((const unsigned char *) (a + 5), (unsigned int *) d, (unsigned char *) e);
}

void func_02077910(int a, int b)
{
    MI_CpuCopy8(&b, a, 2);
}

short func_020778f8(int arg)
{
    short buf;
    MI_CpuCopy8((int *) arg, (int) (&buf), 2);
    return buf;
}

void func_020778e0(void *p, UnkStruct_020778e0 v)
{
    MI_CpuCopy8((int *) (&v), (int) p, 2);
}

int func_020778c8(int p1)
{
    short local;
    MI_CpuCopy8((int *) p1, (int) (&local), 2);
    return local;
}

void func_020778b0(int a, int b, ...)
{
    MI_CpuCopy8(&b, a, 2);
}

unsigned short func_02077898(const void *param)
{
    unsigned short value;
    MI_CpuCopy8((int *) param, (int) (&value), 2);
    return value;
}

void func_02077880(void *p, UnkStruct_02077880 v)
{
    MI_CpuCopy8((int *) (&v), (int) p, 2);
}

unsigned short func_02077868(int arg0)
{
    unsigned short result;
    MI_CpuCopy8((int *) arg0, (int) (&result), 2);
    return result;
}
