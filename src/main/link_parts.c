/* link_parts: 29 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020a7830 @ 0x020a7830, 0x20 bytes, Thumb
 * func_020a7820 @ 0x020a7820, 0x10 bytes, Thumb
 * func_020a7810 @ 0x020a7810, 0x10 bytes, Thumb
 * func_020a77f4 @ 0x020a77f4, 0x1a bytes, Thumb
 * func_020a77dc @ 0x020a77dc, 0x18 bytes, Thumb
 * func_020a77cc @ 0x020a77cc, 0x10 bytes, Thumb
 * func_020a77c8 @ 0x020a77c8, 0x2 bytes, Thumb
 * func_020a7794 @ 0x020a7794, 0x34 bytes, Thumb
 * func_020a7778 @ 0x020a7778, 0x1a bytes, Thumb
 * func_020a7768 @ 0x020a7768, 0xe bytes, Thumb
 * func_020a7758 @ 0x020a7758, 0x10 bytes, Thumb
 * func_020a7754 @ 0x020a7754, 0x2 bytes, Thumb
 * func_020a774c @ 0x020a774c, 0x8 bytes, Thumb
 * func_020a7738 @ 0x020a7738, 0x14 bytes, Thumb
 * func_020a772c @ 0x020a772c, 0xc bytes, Thumb
 * func_020a771c @ 0x020a771c, 0x10 bytes, Thumb
 * func_020a7718 @ 0x020a7718, 0x2 bytes, Thumb
 * func_020a7710 @ 0x020a7710, 0x6 bytes, Thumb
 * func_020a7704 @ 0x020a7704, 0xa bytes, Thumb
 * func_020a76f8 @ 0x020a76f8, 0xa bytes, Thumb
 * func_020a76e8 @ 0x020a76e8, 0x10 bytes, Thumb
 * func_020a76e4 @ 0x020a76e4, 0x2 bytes, Thumb
 * func_020a76e0 @ 0x020a76e0, 0x4 bytes, Thumb
 * func_020a76d8 @ 0x020a76d8, 0x6 bytes, Thumb
 * func_020a76d0 @ 0x020a76d0, 0x6 bytes, Thumb
 * func_020a76cc @ 0x020a76cc, 0x2 bytes, Thumb
 * func_020a76c8 @ 0x020a76c8, 0x2 bytes, Thumb
 * func_020a76ac @ 0x020a76ac, 0x1a bytes, Thumb
 * func_020a7684 @ 0x020a7684, 0x26 bytes, Thumb
 */

typedef struct {
    unsigned long unk_00;
} UnkStruct_020a76d0;

extern void func_020a7890(int a, int *buf, int b, int c, int d, int e);
extern void func_020a7934(void);
extern void func_020a7930(void);
extern void func_020a78ec(int a, int b, int c, int d, unsigned char e, int f);

void func_020a7768(unsigned char *r0);
void func_020a772c(unsigned char *r0);
void func_020a76f8(char *p);
void func_020a76d0(UnkStruct_020a76d0 *p);

void func_020a7830(int a, int b, int c, int d, int e)
{
    int buf;
    func_020a7890(a, &buf, b, c, d, e);
}

void *func_020a7820(void *p)
{
    func_020a7934();
    return p;
}

int func_020a7810(int arg)
{
    func_020a7930();
    return arg;
}

void func_020a77f4(int a, int b, int c, int d, unsigned char e, int f)
{
    func_020a78ec(a, b, c, d, e, f);
}

void func_020a77dc(int a, int b, int c, int d, int e, int f)
{
    int local[2];
    local[0] = e;
    local[1] = f;
    func_020a7890(a, (int *) b, c, d, local[0], local[1]);
}

int func_020a77cc(int arg)
{
    func_020a7768((unsigned char *) arg);
    return arg;
}

void func_020a77c8(void *object) {}

void func_020a7794(unsigned char *r0, unsigned char r1, unsigned char r2, unsigned char r3, unsigned int r4)
{
    unsigned int r5;
    unsigned int r6;

    r6 = r4 & 1;
    if (r6 != 0) {
        *r0 = r1;
    }

    r5 = r4 & 2;
    if (r5 != 0) {
        *(r0 + 1) = r2;
    }

    r5 = r4 & 4;
    if (r5 != 0) {
        *(r0 + 2) = r3;
    }

    *(unsigned int *) (r0 + 4) |= r4;
}

void func_020a7778(unsigned char *src, unsigned char *d1, unsigned char *d2, unsigned char *d3, unsigned int *d4)
{
    *d1 = src[0];
    *d2 = src[1];
    *d3 = src[2];
    *d4 = *(unsigned int *) (src + 4);
}

void func_020a7768(unsigned char *r0)
{
    r0[0] = 0x3f;
    r0[1] = 0;
    r0[2] = 0;
    *(unsigned int *) (r0 + 4) = 0;
}

void *func_020a7758(void *param)
{
    func_020a772c((unsigned char *) param);
    return param;
}

void func_020a7754(void *object) {}

void func_020a774c(unsigned char *p0, int p1, int p2, int p3)
{
    p0[0] = p1;
    p0[1] = p2;
    p0[2] = p3;
}

void func_020a7738(unsigned char *src, unsigned char *dst1, unsigned char *dst2, unsigned char *dst3)
{
    dst1[0] = src[0];
    dst2[0] = src[1];
    dst3[0] = src[2];
}

void func_020a772c(unsigned char *r0)
{
    r0[0] = 0x3f;
    r0[1] = 0;
    r0[2] = 0;
}

int func_020a771c(int arg)
{
    func_020a76f8((char *) arg);
    return arg;
}

void func_020a7718(void *object) {}

void func_020a7710(char *p, int a, int b)
{
    *(int *) p = a;
    p[4] = (char) b;
}

void func_020a7704(int *src, int *dst1, unsigned char *dst2)
{
    *dst1 = *src;
    *dst2 = *(unsigned char *) ((char *) src + 4);
}

void func_020a76f8(char *p)
{
    *(int *) p = 4;
    p[4] = 0x3f;
}

void *func_020a76e8(void *arg)
{
    func_020a76d0((UnkStruct_020a76d0 *) arg);
    return arg;
}

void func_020a76e4(void *object) {}

void func_020a76e0(int *p0, int p1)
{
    p0[0] = p1;
}

void func_020a76d8(int *s, int *d)
{
    *d = *s;
}

void func_020a76d0(UnkStruct_020a76d0 *p)
{
    p->unk_00 = 0;
}

void func_020a76cc(void *object) {}

void func_020a76c8(void *object) {}

void func_020a76ac(unsigned char *out, int a, int b, int c)
{
    *out = (a & 0x07) | (((b << 5) & 0xE0) | (c << 3));
}

void func_020a7684(unsigned char *arg0, unsigned int *arg1, unsigned int *arg2, unsigned int *arg3)
{
    unsigned char local_0;
    unsigned int local_1;
    unsigned int local_2;
    unsigned int local_3;

    local_0 = *arg0;
    local_1 = local_0 & 7;
    *arg1 = local_1;
    local_2 = (*arg0 >> 5) & 7;
    *arg2 = local_2;
    local_3 = (*arg0 >> 3) & 3;
    *arg3 = local_3;
}
