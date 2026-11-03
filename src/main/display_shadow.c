/* display_shadow: 10 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02001afc @ 0x02001afc, 0x10 bytes, Thumb
 * func_02001aac @ 0x02001aac, 0x50 bytes, Thumb
 * func_02001a7c @ 0x02001a7c, 0x30 bytes, Thumb
 * func_02001a5c @ 0x02001a5c, 0x20 bytes, Thumb
 * func_02001a48 @ 0x02001a48, 0x14 bytes, Thumb
 * func_02001a30 @ 0x02001a30, 0x18 bytes, Thumb
 * func_02001a1c @ 0x02001a1c, 0x14 bytes, Thumb
 * func_02001a04 @ 0x02001a04, 0x18 bytes, Thumb
 * func_020019f4 @ 0x020019f4, 0x10 bytes, Thumb
 * func_020019dc @ 0x020019dc, 0x18 bytes, Thumb
 */

extern struct {
    unsigned char pad[0x15];
    unsigned char flag;
} data_0213fe74;
extern void G2x_SetBlendBrightness_(unsigned int addr, unsigned int size, unsigned int data);
extern void G2x_SetBlendBrightnessExt_(unsigned int addr, unsigned int arg1, unsigned int arg2, unsigned int arg3,
                                       unsigned int arg4, unsigned int arg5);
extern void func_02001d00(int);
extern void func_02001ce8(int);
extern void func_02001b7c(int);
extern unsigned char data_0213fe94[];
extern void func_02001b6c(int);

void func_02001a48(void);

void func_02001afc(unsigned char mask)
{
    data_0213fe74.flag &= ~mask;
}

void func_02001aac(unsigned int param)
{
    if (param != 0) {
        G2x_SetBlendBrightness_(0x04000050, 0x3f, param);
        G2x_SetBlendBrightness_(0x04001050, 0x3f, param);
    } else {
        G2x_SetBlendBrightnessExt_(0x04000050, 0x1f, 0x20, 0x10, 0x10, param);
        G2x_SetBlendBrightnessExt_(0x04001050, 0x1f, 0x20, 0x10, 0x10, param);
    }
}

void func_02001a7c(void)
{
    unsigned char *p;
    unsigned char val;

    func_02001a48();
    func_02001d00(0x1f);
    func_02001ce8(0x10);
    func_02001b7c(4);
    p = data_0213fe94;
    val = p[0x12];
    val |= 1;
    p[0x12] = val;
}

void func_02001a5c(void)
{
    unsigned char *p;
    unsigned char val;

    func_02001b6c(4);
    p = data_0213fe94;
    val = p[0x12];
    val |= 2;
    p[0x12] = val;
}

void func_02001a48(void)
{
    (*(struct { unsigned char pad[0x12]; unsigned char flag12; unsigned char flag13; } *) data_0213fe94).flag13 = 0x1f;
    (*(struct { unsigned char pad[0x12]; unsigned char flag12; unsigned char flag13; } *) data_0213fe94).flag12 |= 4;
}

unsigned char func_02001a30(unsigned char mask)
{
    data_0213fe94[0x13] &= ~mask;
    data_0213fe94[0x12] |= 4;
    return 4;
}

void func_02001a1c(unsigned char value)
{
    data_0213fe94[0x14] = value;
    data_0213fe94[0x12] |= 4;
}

void func_02001a04(unsigned char a, unsigned char b, unsigned char c)
{
    data_0213fe94[0x13] = a;
    data_0213fe94[0x14] = b;
    data_0213fe94[0x15] = c;
    data_0213fe94[0x12] |= 8;
}

void func_020019f4(void)
{
    unsigned char *ptr;
    unsigned char val;

    ptr = data_0213fe94;
    val = ptr[0x12];
    val |= 2;
    ptr[0x12] = val;
}

// placeholder, not used
void func_020019dc(unsigned char r0, unsigned char r1, unsigned char r2)
{
    unsigned char *base = (unsigned char *) data_0213fe94;
    unsigned char tmp;

    base[0x13] = r0;
    base[0x14] = r1;
    base[0x15] = r2;

    tmp = base[0x12];
    tmp |= 0x10;
    base[0x12] = tmp;
}
