/* mes_slider_window_3: 20 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020abdc0 @ 0x020abdc0, 0x8 bytes, Thumb
 * func_020abd98 @ 0x020abd98, 0x28 bytes, Thumb
 * func_020abd68 @ 0x020abd68, 0x30 bytes, Thumb
 * func_020abd5c @ 0x020abd5c, 0xc bytes, Thumb
 * func_020abd44 @ 0x020abd44, 0x18 bytes, Thumb
 * func_020abd2c @ 0x020abd2c, 0x18 bytes, Thumb
 * func_020abd14 @ 0x020abd14, 0x18 bytes, Thumb
 * func_020abcfc @ 0x020abcfc, 0x18 bytes, Thumb
 * func_020abce4 @ 0x020abce4, 0x18 bytes, Thumb
 * func_020abccc @ 0x020abccc, 0x18 bytes, Thumb
 * func_020abcc0 @ 0x020abcc0, 0xc bytes, Thumb
 * func_020abcb4 @ 0x020abcb4, 0xc bytes, Thumb
 * func_020abca8 @ 0x020abca8, 0xc bytes, Thumb
 * func_020abc9c @ 0x020abc9c, 0xc bytes, Thumb
 * func_020abc90 @ 0x020abc90, 0xc bytes, Thumb
 * func_020abc84 @ 0x020abc84, 0xc bytes, Thumb
 * func_020abc78 @ 0x020abc78, 0xc bytes, Thumb
 * func_020abc6c @ 0x020abc6c, 0xc bytes, Thumb
 * func_020abc40 @ 0x020abc40, 0x2c bytes, Thumb
 * func_020abc3c @ 0x020abc3c, 0x2 bytes, Thumb
 */

struct UnkStruct_020abd98 {
    char pad_00[0xe4];
    unsigned char something;
    char pad_E5[0x141 - 0xe4 - 1];
    unsigned char flag;
};

struct UnkStruct_020abca8 {
    char pad_00[0x141];
    unsigned char byte;
};

extern int func_020aca54(unsigned char *ptr);
extern void func_0200467c(int command);
extern void func_020aca94(int, int);
extern int func_020aca7c(void *p);
extern int func_020aca74(void *ptr);
extern void *func_020aca6c(void *);
extern int func_020aca70(void *);
extern void func_0208e508(char *ptr, int);
extern void func_020aca3c(void *p);
extern void func_0208f0c4(void *p, int x);

void func_020abc78(unsigned char *r0);

void func_020abdc0(unsigned char *argument0)
{
    func_020abc78((unsigned char *) argument0);
}

int func_020abd98(struct UnkStruct_020abd98 *p)
{
    if (p->flag != 0) {
        if (func_020aca54(&p->something) != 0) {
            return 1;
        }
    }
    return 0;
}

void func_020abd68(unsigned char *ptr, unsigned char value, int flag)
{
    if (flag != 0 && *(ptr + 0x145) == 0 && value != 0) {
        func_0200467c(0x3b);
    }
    *(ptr + 0x145) = value;
}

void func_020abd5c(int a, int b)
{
    func_020aca94(a + 0xE4, b);
}

int func_020abd44(void *p)
{
    return func_020aca7c((char *) p + 0xE4) + 0x80 - *(short *) ((char *) p + 0x18);
}

int func_020abd2c(void *s)
{
    return func_020aca74((char *) s + 0xE4) + 0x60 - *(signed short *) ((char *) s + 0x1A);
}

int func_020abd14(void *p)
{
    return (int) ((char *) func_020aca6c((char *) p + 0xE4) + 0x60) - *(signed short *) ((char *) p + 0x1A);
}

int func_020abcfc(void *arg0)
{
    int result;
    int offset;
    void *ptr;

    ptr = arg0;
    result = func_020aca70((char *) ptr + 0xe4);
    offset = *(short *) ((char *) ptr + 0x1a);
    return result + 0x60 - offset;
}

int func_020abce4(void *arg0)
{
    int val;

    val = *(int *) ((char *) arg0 + 0x13c);
    val = val - 1;
    if ((unsigned int) val <= 4) {
        return 1;
    }
    return 0;
}

int func_020abccc(unsigned char *arg)
{
    unsigned int value;
    value = *(unsigned int *) (arg + 0x13C);
    if ((value - 6) > 5) {
        return 0;
    }
    return 1;
}

int func_020abcc0(void *ptr)
{
    return *(int *) ((char *) ptr + 0x13c);
}

void func_020abcb4(unsigned char *p)
{
    p[0x140] = 1;
}

void func_020abca8(struct UnkStruct_020abca8 *arg0)
{
    arg0->byte = 1;
}

void func_020abc9c(unsigned char *r0)
{
    unsigned char r2 = 0;
    unsigned short r1 = 0x141;
    r0[r1] = r2;
}

void func_020abc90(unsigned char *r0)
{
    r0[0x142] = 1;
}

void func_020abc84(unsigned char *r0)
{
    unsigned char *base = r0;
    base[0x143] = 1;
}

void func_020abc78(unsigned char *r0)
{
    unsigned char r2 = 1;
    unsigned int r1 = 0x144;
    r0[r1] = r2;
}

void func_020abc6c(char *ptr, int argument1)
{
    func_0208e508(ptr + 0x20, (int) argument1);
}

void func_020abc40(char *self)
{
    *(unsigned int *) (self + 0x13c) = 0;
    func_020abc6c((char *) self, 0);
    func_020aca3c(self + 0xe4);
    self += 0x6c;
    func_0208f0c4(self, 0);
}

void func_020abc3c(void) {}
