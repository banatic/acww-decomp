/* scene_display: 7 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020b698c @ 0x020b698c, 0x3c bytes, Thumb
 * func_020b68f8 @ 0x020b68f8, 0x94 bytes, Thumb
 * func_020b68e4 @ 0x020b68e4, 0x12 bytes, Thumb
 * func_020b68d4 @ 0x020b68d4, 0x10 bytes, Thumb
 * func_020b68c8 @ 0x020b68c8, 0xc bytes, Thumb
 * func_020b68b0 @ 0x020b68b0, 0x18 bytes, Thumb
 * func_020b68ac @ 0x020b68ac, 0x2 bytes, Thumb
 */

#define g_04000358 (*(unsigned int *) 0x04000358)

extern void G3X_SetFog(int a, int b, int c, int d);
extern void G3X_SetFogTable(unsigned short *p0);
extern unsigned char data_021f6a0c[];
extern unsigned short data_021f69ec[];
extern void func_020540c0(void);
extern void func_020b98dc(void);
extern void func_020b9990(void);
extern void func_02053fdc(void);
extern void func_02001bf0(int);
extern void func_02001bdc(int);
extern void func_020b947c(void);
extern void func_02001b44(int);
extern void func_02001b0c(int);
extern void func_02056318(void);
extern void func_02038a20(void);
extern void GX_SetBankForTex(int);
extern void GX_SetBankForTexPltt(int);
extern void GX_SetBankForBG(int);
extern void GX_SetBankForOBJ(int);
extern void GX_SetBankForSubBG(int);
extern void GX_SetBankForSubOBJ(int);
extern void func_02038a10(void);
extern void func_02056310(void);

void func_020b698c(void *object)
{
    unsigned int val;
    unsigned char b0, b1, b6;
    unsigned short s22, s24;

    b0 = data_021f6a0c[0];
    b1 = data_021f6a0c[1];
    s22 = data_021f69ec[0x11];
    G3X_SetFog(b0, 1, b1, s22);

    s24 = data_021f69ec[0x12];
    b6 = data_021f6a0c[6];
    val = s24 | ((unsigned int) b6 << 16);
    g_04000358 = val;
    G3X_SetFogTable(data_021f69ec);
}

void func_020b68f8(void)
{
    func_020540c0();
    func_020b98dc();
    func_020b9990();
    func_02053fdc();
    GX_SetBankForTex(7);
    GX_SetBankForTexPltt(0x10);
    GX_SetBankForBG(0x20);
    GX_SetBankForOBJ(0x40);
    GX_SetBankForSubBG(0x80);
    GX_SetBankForSubOBJ(0x100);
    *((volatile unsigned int *) 0x04000000) = (*((volatile unsigned int *) 0x04000000)) & 0xffcfffef;
    *((volatile unsigned int *) 0x04001000) = (*((volatile unsigned int *) 0x04001000)) & 0xffcfffef;
    func_02001bf0(0);
    func_02001bdc(1);
    *((volatile unsigned int *) 0x04000000) = (*((volatile unsigned int *) 0x04000000)) & 0xc7ffffff;
    func_020b947c();
    func_02001b44(0x11);
    func_02001b0c(0x10);
    func_02056318();
    func_02038a20();
}

void func_020b68e4(void)
{
    func_02038a10();
    func_02056310();
}

void func_020b68d4(int param)
{
    data_021f6a0c[6] = param & 0x1f;
}

void func_020b68c8(unsigned int value)
{
    data_021f69ec[0x11] = value;
}

void func_020b68b0(int arg0, const unsigned char *src)
{
    unsigned char *dst;
    int i;

    dst = ((unsigned char *) data_021f69ec);
    i = 0;
    do {
        *dst = *src;
        dst++;
        src++;
        i++;
    } while (i < 0x20);
}

void func_020b68ac(void) {}
