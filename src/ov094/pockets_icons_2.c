/* pockets_icons_2: 5 functions, module ov094
 * mwccarm 1.2/base -O4,s
 * func_ov094_0229b104 @ 0x0229b104, 0xc bytes, Thumb
 * func_ov094_0229b0f8 @ 0x0229b0f8, 0xc bytes, Thumb
 * func_ov094_0229b0e0 @ 0x0229b0e0, 0x18 bytes, Thumb
 * func_ov094_0229b0d4 @ 0x0229b0d4, 0xc bytes, Thumb
 * func_ov094_0229b088 @ 0x0229b088, 0x4c bytes, Thumb
 */

extern char data_ov094_0229bf80[];
extern void func_020edb3c(void *);
extern int func_02064328(char *dst, const char *src);
extern int func_02064af4(char *dst, const char *src, unsigned int size);
extern unsigned int func_0206fe28(unsigned int i);
extern unsigned char data_ov094_0229c0d4[];

void func_ov094_0229b104(char **p)
{
    *p = ((char *) data_ov094_0229bf80);
}

void func_ov094_0229b0f8(char **out)
{
    *out = data_ov094_0229bf80;
}

void *func_ov094_0229b0e0(void *arg)
{
    *(char **) arg = data_ov094_0229bf80;
    func_020edb3c(arg);
    return arg;
}

void func_ov094_0229b0d4(unsigned char *p)
{
    p[0x804] = 0xff;
}

void *func_ov094_0229b088(char *self, int param)
{
    char buf[0x2c];
    char *p;
    int bank;

    bank = param >> 4;
    if (bank != ((unsigned char *) self)[0x804]) {
        ((unsigned char *) self)[0x804] = (unsigned char) bank;
        func_02064328(buf, (const char *) data_ov094_0229c0d4);
        func_02064af4(buf, self + 4, 0x800);
    }

    p = self + 4;
    p += func_0206fe28(param & 0xf) << 5;

    return p;
}
