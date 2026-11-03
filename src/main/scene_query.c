/* scene_query: 21 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020b6774 @ 0x020b6774, 0x12 bytes, Thumb
 * func_020b6760 @ 0x020b6760, 0x12 bytes, Thumb
 * func_020b6744 @ 0x020b6744, 0x1a bytes, Thumb
 * func_020b6730 @ 0x020b6730, 0x12 bytes, Thumb
 * func_020b671c @ 0x020b671c, 0x12 bytes, Thumb
 * func_020b6708 @ 0x020b6708, 0x12 bytes, Thumb
 * func_020b66ec @ 0x020b66ec, 0x1a bytes, Thumb
 * func_020b66d8 @ 0x020b66d8, 0x12 bytes, Thumb
 * func_020b66c4 @ 0x020b66c4, 0x12 bytes, Thumb
 * func_020b66b0 @ 0x020b66b0, 0x12 bytes, Thumb
 * func_020b6694 @ 0x020b6694, 0x1a bytes, Thumb
 * func_020b6680 @ 0x020b6680, 0x12 bytes, Thumb
 * func_020b6674 @ 0x020b6674, 0xc bytes, Thumb
 * func_020b6660 @ 0x020b6660, 0x12 bytes, Thumb
 * func_020b6654 @ 0x020b6654, 0xc bytes, Thumb
 * func_020b6640 @ 0x020b6640, 0x12 bytes, Thumb
 * func_020b660c @ 0x020b660c, 0x32 bytes, Thumb
 * func_020b65d0 @ 0x020b65d0, 0x3c bytes, Thumb
 * func_020b65c4 @ 0x020b65c4, 0xc bytes, Thumb
 * func_020b65b8 @ 0x020b65b8, 0xc bytes, Thumb
 * func_020b65ac @ 0x020b65ac, 0xc bytes, Thumb
 */

extern int func_020b67c0(int p);
extern unsigned char data_020e54a8;
extern unsigned char data_020e54ac;
extern unsigned char data_020e54b0;

unsigned char func_020b65c4(void);

int func_020b6774(unsigned int param)
{
    if (param >= 0x1a && param <= 0x1f) {
        return param - 0x1a;
    } else {
        return -1;
    }
}

int func_020b6760(void)
{
    return func_020b6774((unsigned int) func_020b65c4());
}

int func_020b6744(unsigned int code)
{
    int r0;
    int r2;
    int r1;

    r0 = func_020b6774(code);
    r2 = 0;
    r1 = ~r2;
    if (r0 == r1) {
        r2 = 0;
    } else {
        r2 = 1;
    }
    r0 = r2;
    return r0;
}

int func_020b6730(void)
{
    return func_020b6744(func_020b65c4());
}

int func_020b671c(unsigned int c)
{
    if (c >= 0x20 && c <= 0x29) {
        return c - 0x20;
    } else {
        return -1;
    }
}

int func_020b6708(void)
{
    return func_020b671c((unsigned int) func_020b65c4());
}

int func_020b66ec(unsigned int code)
{
    int r0;
    int r2;

    r0 = func_020b671c(code);
    r2 = 0;
    if (r0 != ~r2) {
        r2 = 1;
    }
    r0 = r2;
    return r0;
}

int func_020b66d8(void)
{
    return func_020b66ec(func_020b65c4());
}

int func_020b66c4(unsigned int value)
{
    if (value >= 17 && value <= 24) {
        return value - 17;
    }
    return -1;
}

int func_020b66b0(void)
{
    return func_020b66c4((unsigned int) func_020b65c4());
}

int func_020b6694(int r2)
{
    int r1;
    int r0;

    r0 = func_020b66c4(r2);
    r2 = 0;
    r1 = ~r2;
    if (r0 == r1) {
        r2 = 0;
    } else {
        r2 = 1;
    }
    r0 = r2;
    return r0;
}

int func_020b6680(void)
{
    return func_020b6694((int) func_020b65c4());
}

int func_020b6674(int arg0)
{
    if (arg0 == 0) {
        return 1;
    }
    return 0;
}

int func_020b6660(void)
{
    return func_020b6674((int) func_020b65c4());
}

int func_020b6654(int r0)
{
    if (r0 == 0x31) {
        return 1;
    }
    return 0;
}

int func_020b6640(void)
{
    return func_020b6654((int) func_020b65c4());
}

int func_020b660c(int p0)
{
    if (func_020b67c0(p0) != 0) {
        goto fail;
    }
    if (p0 == 0x2c) {
        goto fail;
    }
    if (p0 == 0x2d) {
        goto fail;
    }
    if (p0 == 0x2e) {
        goto fail;
    }
    if (p0 == 0x2f) {
        goto fail;
    }
    if ((unsigned char) (p0 + 0xf4) > 2) {
        goto ok;
    }
fail:
    return 0;
ok:
    return 1;
}

int func_020b65d0(void)
{
    unsigned char b = data_020e54a8;
    int flag1;
    unsigned int flag2;

    flag1 = b ? 0 : 1;
    if (flag1 != 0) {
        goto calls;
    }
    flag2 = (b == 1) ? 1u : 0u;
    if (flag2 == 0) {
        goto ret0;
    }
calls:
    return func_020b660c(func_020b65c4());
ret0:
    return 0;
}

unsigned char func_020b65c4(void)
{
    return data_020e54ac;
}

unsigned char func_020b65b8(void)
{
    return data_020e54b0;
}

int func_020b65ac(int r0)
{
    if (r0 < 9) {
        return 0;
    }
    return 1;
}
