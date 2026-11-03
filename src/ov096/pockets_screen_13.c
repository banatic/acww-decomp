/* pockets_screen_13: 11 functions, module ov096
 * mwccarm 1.2/base -O4,s
 * func_ov096_0229f874 @ 0x0229f874, 0x58 bytes, Thumb
 * func_ov096_0229f860 @ 0x0229f860, 0x14 bytes, Thumb
 * func_ov096_0229f83c @ 0x0229f83c, 0x24 bytes, Thumb
 * func_ov096_0229f830 @ 0x0229f830, 0xc bytes, Thumb
 * func_ov096_0229f820 @ 0x0229f820, 0x10 bytes, Thumb
 * func_ov096_0229f810 @ 0x0229f810, 0x10 bytes, Thumb
 * func_ov096_0229f800 @ 0x0229f800, 0x10 bytes, Thumb
 * func_ov096_0229f7e0 @ 0x0229f7e0, 0x20 bytes, Thumb
 * func_ov096_0229f7ac @ 0x0229f7ac, 0x34 bytes, Thumb
 * func_ov096_0229f79c @ 0x0229f79c, 0xe bytes, Thumb
 * func_ov096_0229f75c @ 0x0229f75c, 0x40 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0x8d];
    unsigned char unk_8D;
    unsigned char pad_8E[0x2c];
    unsigned char unk_BA;
} Ov096Struct;

extern volatile unsigned char data_021f43ec;
extern int func_ov002_0220b9b8(void *, unsigned char *, unsigned int, int);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_0208e5c4(void *);
extern void func_020b9ccc(char *p);
extern int func_ov002_02209f00(void *p);
extern int func_ov090_02298f84(int argument0);
extern int func_ov094_0229aee8(char *p, int unused1, int unused2);
extern int func_ov094_0229a69c(char *p, int v);

void func_ov096_0229f874(Ov096Struct *self, int a, int b, unsigned int size)
{
    volatile unsigned char data;

    if (b == 0xff) {
        self->unk_BA = self->unk_8D;
    } else {
        self->unk_BA = b;
    }

    data = data_021f43ec;
    data = a;

    func_ov002_0220b9b8((char *) self + 0x2958, (unsigned char *) &data, size, 0);
    func_ov002_02208098((void *) (self), 0x20);
    func_0208e5c4((char *) self + 0x2500);
}

unsigned char *func_ov096_0229f860(void *p)
{
    ((char *) p)[0xc1] = 0xe;
    return func_ov002_02208098((void *) (p), 0x32);
}

void func_ov096_0229f83c(void *self)
{
    int i = 0;
    char *base = (char *) self + 0x2e8;
    do {
        func_020b9ccc(base + i * 0x38);
        i++;
    } while (i < 2);
}

int func_ov096_0229f830(int arg0, unsigned int arg1)
{
    if (arg1 > 14) {
        return 0;
    }
    return 1;
}

int func_ov096_0229f820(int unused, unsigned int b)
{
    if (b >= 15 && b <= 24) {
        return 1;
    }
    return 0;
}

int func_ov096_0229f810(int arg0, unsigned int arg1)
{
    if (arg1 >= 25 && arg1 <= 32) {
        return 1;
    }
    return 0;
}

int func_ov096_0229f800(int a, unsigned int b)
{
    if (b >= 0x22 && b <= 0x25) {
        return 1;
    } else {
        return 0;
    }
}

void func_ov096_0229f7e0(void *p)
{
    char *base = (char *) p + 0x2500;
    int r;

    r = func_ov090_02298f84((int) func_ov002_02209f00(base));
    ((char *) p)[0xb5] = (char) (r + 0x19);
}

unsigned char func_ov096_0229f7ac(unsigned short a, unsigned short b)
{
    if (func_ov096_0229f830((unsigned short) a, (unsigned short) b)) {
        return b;
    }
    if (func_ov096_0229f800((unsigned short) a, (unsigned short) b)) {
        return b - 4;
    }
    return 0;
}

unsigned int func_ov096_0229f79c(unsigned int a, unsigned int b)
{
    if (b <= 14) {
        return (unsigned char) b;
    } else {
        return 38;
    }
}

int func_ov096_0229f75c(char *a, int b, int c, int cond)
{
    int v;

    v = func_ov094_0229aee8(a + 0x358, b, c);
    if (v != 0x23) {
        if (cond) {
            if (func_ov094_0229a69c(a + 0x358, v) != 0) {
                return 0x26;
            }
        }
        return (int) func_ov096_0229f79c((unsigned int) a, v);
    } else {
        return 0x26;
    }
}
