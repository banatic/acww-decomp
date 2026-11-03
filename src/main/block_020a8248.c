/* block_020a8248: 14 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020a82e8 @ 0x020a82e8, 0x10 bytes, Thumb
 * func_020a82e4 @ 0x020a82e4, 0x2 bytes, Thumb
 * func_020a82bc @ 0x020a82bc, 0x26 bytes, Thumb
 * func_020a82b0 @ 0x020a82b0, 0xc bytes, Thumb
 * func_020a82ac @ 0x020a82ac, 0x2 bytes, Thumb
 * func_020a82a8 @ 0x020a82a8, 0x4 bytes, Thumb
 * func_020a82a4 @ 0x020a82a4, 0x4 bytes, Thumb
 * func_020a82a0 @ 0x020a82a0, 0x4 bytes, Thumb
 * func_020a829c @ 0x020a829c, 0x4 bytes, Thumb
 * func_020a8298 @ 0x020a8298, 0x4 bytes, Thumb
 * func_020a8290 @ 0x020a8290, 0x6 bytes, Thumb
 * func_020a8278 @ 0x020a8278, 0x18 bytes, Thumb
 * func_020a8260 @ 0x020a8260, 0x18 bytes, Thumb
 * func_020a8248 @ 0x020a8248, 0x18 bytes, Thumb
 */

extern void MI_CpuFill8(int a, int b, int c);
extern int data_020d1c44[];
extern void *data_020d1ca8[];
extern int data_020d1d0c[];

void func_020a82b0(int a);

int func_020a82e8(int a)
{
    func_020a82b0(a);
    return a;
}

void func_020a82e4(void *receiver) {}

void func_020a82bc(void *r0, const void *r1)
{
    unsigned char *dst = (unsigned char *) r0;
    const unsigned char *src = (const unsigned char *) r1;

    *(unsigned int *) dst = *(const unsigned int *) src;
    dst[4] = src[4];
    dst[5] = src[5];
    dst[6] = src[6];
    dst[7] = src[7];
    dst[8] = src[8];
    dst[9] = src[9];
    dst[10] = src[10];
    dst[11] = src[11];
}

void func_020a82b0(int a)
{
    MI_CpuFill8(a, 0, 12);
}

void *func_020a82ac(void *object)
{
    return object;
}

int func_020a82a8(unsigned char *p0)
{
    return p0[4];
}

int func_020a82a4(unsigned char *p0)
{
    return p0[5];
}

int func_020a82a0(unsigned char *p0)
{
    return p0[6];
}

int func_020a829c(unsigned char *p0)
{
    return p0[7];
}

int func_020a8298(unsigned char *p0)
{
    return p0[9];
}

void func_020a8290(unsigned char *d, unsigned char *s)
{
    *d = s[8];
}

int func_020a8278(unsigned char *argument0)
{
    return data_020d1c44[func_020a82a8((unsigned char *) argument0)];
}

void *func_020a8260(unsigned char *argument0)
{
    return data_020d1ca8[func_020a82a8((unsigned char *) argument0)];
}

int func_020a8248(unsigned char *argument0)
{
    return data_020d1d0c[func_020a82a8((unsigned char *) argument0)];
}
