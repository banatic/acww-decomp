/* group_params_4: 17 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0206f9cc @ 0x0206f9cc, 0xc bytes, Thumb
 * func_0206f9c0 @ 0x0206f9c0, 0xc bytes, Thumb
 * func_0206f99c @ 0x0206f99c, 0x24 bytes, Thumb
 * func_0206f990 @ 0x0206f990, 0xc bytes, Thumb
 * func_0206f980 @ 0x0206f980, 0x10 bytes, Thumb
 * func_0206f92c @ 0x0206f92c, 0x54 bytes, Thumb
 * func_0206f910 @ 0x0206f910, 0x1c bytes, Thumb
 * func_0206f8e0 @ 0x0206f8e0, 0x30 bytes, Thumb
 * func_0206f8c8 @ 0x0206f8c8, 0x18 bytes, Thumb
 * func_0206f8b4 @ 0x0206f8b4, 0x14 bytes, Thumb
 * func_0206f898 @ 0x0206f898, 0x1c bytes, Thumb
 * func_0206f87c @ 0x0206f87c, 0x1c bytes, Thumb
 * func_0206f860 @ 0x0206f860, 0x1c bytes, Thumb
 * func_0206f854 @ 0x0206f854, 0xc bytes, Thumb
 * func_0206f848 @ 0x0206f848, 0xc bytes, Thumb
 * func_0206f83c @ 0x0206f83c, 0xc bytes, Thumb
 * func_0206f830 @ 0x0206f830, 0xc bytes, Thumb
 */

extern unsigned short data_021cfc64;
extern unsigned char data_021cfc58;
extern int func_0206fbf8(int);
extern unsigned short data_021cfc68;
extern unsigned char data_021cfd68[];
extern int func_020984e8(void);
extern int func_02098a18(int);
extern unsigned char *func_02097e14(void *p);
extern int func_02066830(int, void *);
extern void func_020664e0(int);
extern int func_02097e08(int);
extern unsigned char data_021cfc98[];
extern int func_0209a1d0(void);
extern unsigned int data_021cfc74;
extern unsigned char data_021cfc78[];

unsigned short func_0206f9cc(void)
{
    return data_021cfc64;
}

unsigned char func_0206f9c0(void)
{
    return data_021cfc58;
}

int func_0206f99c(void)
{
    if (func_0206fbf8(0x25) != 0) {
        data_021cfc68 = 0;
        return 1;
    } else {
        return 0;
    }
}

void func_0206f990(unsigned short val)
{
    data_021cfc68 = val;
}

void func_0206f980(void *src)
{
    func_02066830((int) ((void *) data_021cfd68), (void *) src);
}

void func_0206f92c(void)
{
    int a;
    int b;
    unsigned char *p;

    a = func_020984e8();
    b = (int) func_02097e14((void *) func_02098a18(a));
    func_02066830(b, ((int *) data_021cfd68));
    func_020664e0(b);
    p = (unsigned char *) func_02097e08(func_02098a18(a));
    p[0] = 1;
    p[1] = 1;
    p[2] = 0;
    p[3] = 0;
    p[0] = data_021cfc98[3];
    p[1] = data_021cfc98[4];
    p[2] = data_021cfc98[5];
}

void func_0206f910(void)
{
    int ret;
    ret = func_0209a1d0();
    if (ret) {
        func_02066830(ret, data_021cfd68);
    }
}

int func_0206f8e0(void)
{
    unsigned short v = data_021cfc68;
    if (v & 2) {
        return 2;
    }
    if (v & 1) {
        return 1;
    }
    if (v & 0x800) {
        return 3;
    }
    return 0;
}

int func_0206f8c8(void)
{
    if (data_021cfc68 & 8) {
        return 1;
    }
    return 0;
}

unsigned char func_0206f8b4(void)
{
    return (unsigned char) ((data_021cfc68 >> 6) & 3);
}

int func_0206f898(void)
{
    unsigned short value;
    unsigned short mask;
    int result;

    value = data_021cfc68;
    mask = 0x0400;
    if ((value & mask) != 0) {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}

int func_0206f87c(void)
{
    unsigned short value;
    unsigned int masked;

    value = data_021cfc68;
    masked = value & 0x00000100;
    if (masked != 0) {
        return 0;
    }
    return 1;
}

int func_0206f860(void)
{
    if ((data_021cfc68 & 0x200) == 0) {
        return 0;
    } else {
        return 1;
    }
}

unsigned int func_0206f854(void)
{
    return data_021cfc74;
}

void func_0206f848(int value)
{
    (*(int *) &data_021cfc74) = value;
}

int func_0206f83c(void)
{
    return *((int *) data_021cfc78);
}

void func_0206f830(int value)
{
    (*(int *) data_021cfc78) = value;
}
