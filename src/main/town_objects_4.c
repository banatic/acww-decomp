/* town_objects_4: 13 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020b2a68 @ 0x020b2a68, 0x28 bytes, Thumb
 * func_020b2a64 @ 0x020b2a64, 0x2 bytes, Thumb
 * func_020b2a60 @ 0x020b2a60, 0x4 bytes, Thumb
 * func_020b2a5c @ 0x020b2a5c, 0x4 bytes, Thumb
 * func_020b2a58 @ 0x020b2a58, 0x4 bytes, Thumb
 * func_020b2a50 @ 0x020b2a50, 0x6 bytes, Thumb
 * func_020b2a4c @ 0x020b2a4c, 0x4 bytes, Thumb
 * func_020b2a48 @ 0x020b2a48, 0x4 bytes, Thumb
 * func_020b2a44 @ 0x020b2a44, 0x4 bytes, Thumb
 * func_020b2a40 @ 0x020b2a40, 0x4 bytes, Thumb
 * func_020b2a3c @ 0x020b2a3c, 0x4 bytes, Thumb
 * func_020b2a20 @ 0x020b2a20, 0x1c bytes, Thumb
 * func_020b2a10 @ 0x020b2a10, 0x10 bytes, Thumb
 */

unsigned int func_020b2a10(unsigned int a, unsigned int b, unsigned int c);

void func_020b2a68(void *dst, const void *src)
{
    unsigned short s;
    unsigned char c;
    signed char sc;

    s = *(const unsigned short *) src;
    *(unsigned short *) dst = s;
    c = *(const unsigned char *) ((const char *) src + 2);
    *((unsigned char *) dst + 2) = c;
    c = *(const unsigned char *) ((const char *) src + 3);
    *((unsigned char *) dst + 3) = c;
    sc = *(const signed char *) ((const char *) src + 4);
    *((unsigned char *) dst + 4) = (unsigned char) sc;
    c = *(const unsigned char *) ((const char *) src + 5);
    *((unsigned char *) dst + 5) = c;
    c = *(const unsigned char *) ((const char *) src + 6);
    *((unsigned char *) dst + 6) = c;
    c = *(const unsigned char *) ((const char *) src + 7);
    *((unsigned char *) dst + 7) = c;
    c = *(const unsigned char *) ((const char *) src + 8);
    *((unsigned char *) dst + 8) = c;
    c = *(const unsigned char *) ((const char *) src + 9);
    *((unsigned char *) dst + 9) = c;
}

void func_020b2a64(void *self) {}

int func_020b2a60(unsigned short *p0)
{
    return p0[0];
}

int func_020b2a5c(unsigned char *p0)
{
    return p0[2];
}

int func_020b2a58(unsigned char *p0)
{
    return p0[3];
}

int func_020b2a50(signed char *p)
{
    return p[4];
}

int func_020b2a4c(unsigned char *p0)
{
    return p0[5];
}

int func_020b2a48(unsigned char *p0)
{
    return p0[6];
}

int func_020b2a44(unsigned char *p0)
{
    return p0[7];
}

int func_020b2a40(unsigned char *p0)
{
    return p0[8];
}

int func_020b2a3c(unsigned char *p0)
{
    return p0[9];
}

unsigned int func_020b2a20(int a, int b, int c)
{
    int ret = func_020b2a60((unsigned short *) a);
    return func_020b2a10(ret, b, c);
}

unsigned int func_020b2a10(unsigned int a, unsigned int b, unsigned int c)
{
    return (a << 16) | (((c & 0xFF) << 8) | (b & 0xFF));
}
