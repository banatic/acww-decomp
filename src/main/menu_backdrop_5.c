/* menu_backdrop_5: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0206f408 @ 0x0206f408, 0x94 bytes, Thumb
 * func_0206f38c @ 0x0206f38c, 0x7c bytes, Thumb
 * func_0206f35c @ 0x0206f35c, 0x30 bytes, Thumb
 * func_0206f2f0 @ 0x0206f2f0, 0x6c bytes, Thumb
 */

#define REG_BLDY (*(volatile unsigned short *) 0x04000042)

extern short data_021cfc1c[];
extern unsigned char data_021cfc14;
extern unsigned char data_027e0438[24];
extern int func_0205bfdc(char *);
extern void func_02001ca0(int, int, int, int);
extern char data_021cfc2c[];
extern unsigned char data_027e0434; // 0x027e0434
extern int func_0205c024(void *a, void *b, void (*c)(void), int d);
extern void func_01ffccf4(void);

void func_0206f408(void)
{
    int i;
    int level;

    if (data_021cfc1c[0] > 20) {
        data_021cfc1c[0] -= 20;
    } else {
        func_0205bfdc(((char *) data_021cfc2c));
        data_021cfc14 &= ~1;
        func_02001ca0(0, 0, 0xff, 0xc0);
        REG_BLDY = 0xff;
        data_021cfc1c[0] = 0;
    }
    for (i = 0; i < 24; i++) {
        level = data_021cfc1c[0] - i;
        if (level < 0) {
            data_027e0438[i] = 0;
        } else if (level > 0xfe) {
            data_027e0438[i] = 0xfe;
        } else {
            data_027e0438[i] = level;
        }
    }
    REG_BLDY = ((data_027e0438[0] << 8) & 0xff00) | 0xff;
}

void func_0206f38c(void)
{
    int i;
    int v;
    int d;

    if ((*(short *) data_021cfc1c) < 0x103) {
        (*(short *) data_021cfc1c) = (short) ((*(short *) data_021cfc1c) + 0x14);
    } else {
        func_0205bfdc((char *) (((int *) data_021cfc2c)));
        data_021cfc14 &= ~1;
        (*(short *) data_021cfc1c) = 0xfe;
        *(unsigned short *) 0x04000042 = 0xfeff;
    }
    i = 0;
    v = (*(short *) data_021cfc1c);
    for (; i < 0x18; i++) {
        d = v - i;
        if (d < 0) {
            data_027e0438[i] = 0;
        } else if (d > 0xfe) {
            data_027e0438[i] = 0xfe;
        } else {
            data_027e0438[i] = (unsigned char) d;
        }
    }
}

void func_0206f35c(void)
{
    if (data_021cfc14 & 1) {
        func_0205bfdc(data_021cfc2c);
        data_021cfc14 &= ~1;
    }
}

void func_0206f2f0(void)
{
    int i;

    (*(short *) data_021cfc1c) = 0x117;
    if (func_0205c024((void *) ((unsigned char *) data_021cfc2c), (void *) func_01ffccf4, func_0206f408, 0) != 0) {
        data_021cfc14 |= 1;
    }

    for (i = 0; i < 24; i++) {
        data_027e0438[i] = 0xFE;
    }

    func_02001ca0((*(short *) data_021cfc1c), 0, 0xFF, 0xC0);
    data_027e0434 = 0;
}
