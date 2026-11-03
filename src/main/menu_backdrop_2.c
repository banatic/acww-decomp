/* menu_backdrop_2: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0206ebac @ 0x0206ebac, 0x40 bytes, Thumb
 * func_0206eb7c @ 0x0206eb7c, 0x30 bytes, Thumb
 * func_0206eb1c @ 0x0206eb1c, 0x60 bytes, Thumb
 * func_0206eb0c @ 0x0206eb0c, 0x10 bytes, Thumb
 */

extern void func_02001bb4(int);
extern void func_02001ba4(int);
extern void func_02001d88(int);
extern void func_02001d1c(int);
extern void func_02001b34(int);
extern void func_0206f28c(void);
extern int func_0203aeac(void);
extern unsigned short data_021cfc20;
extern int func_0206f278(void);
extern void func_020027f0(int a);
extern void func_0206fcc8(void);
extern unsigned char data_021cfc0c;

int func_0206ebac(void)
{
    func_02001bb4(2);
    func_02001ba4(1);
    func_02001d88(0x1f);
    func_02001d1c(0x1b);
    func_02001b34(0xa);
    func_0206f28c();
    if (func_0203aeac() != 0) {
        data_021cfc20 = 0xb;
    }
    return 1;
}

int func_0206eb7c(void)
{
    if (func_0206f278() == 0) {
        data_021cfc20 = 0xC;
        func_02001ba4(2);
        func_020027f0(1);
        func_0206fcc8();
    }
    return 1;
}

void func_0206eb1c(unsigned short *a, unsigned short *b)
{
    int i;
    a[0] = 0;
    for (i = 1; i < 16; i++) {
        unsigned short c = a[i];
        unsigned short r = c & 0x1f;
        unsigned short g = (c & 0x3e0) >> 5;
        unsigned short bl = (c & 0x7c00) >> 10;
        r = (r + 0x1f) >> 1;
        g = (g + 0x1f) >> 1;
        bl = (bl + 0x1f) >> 1;
        b[i] = (unsigned short) (r | (g << 5) | (bl << 10));
    }
}

void func_0206eb0c(unsigned char param)
{
    data_021cfc0c |= param;
}
