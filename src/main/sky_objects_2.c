/* sky_objects_2: 7 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020bde5c @ 0x020bde5c, 0x3c bytes, Thumb
 * func_020bde24 @ 0x020bde24, 0x38 bytes, Thumb
 * func_020bdd9c @ 0x020bdd9c, 0x88 bytes, Thumb
 * func_020bdd10 @ 0x020bdd10, 0x8c bytes, Thumb
 * func_020bdc50 @ 0x020bdc50, 0xc0 bytes, Thumb
 * func_020bdc14 @ 0x020bdc14, 0x3c bytes, Thumb
 * func_020bdbe0 @ 0x020bdbe0, 0x34 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0x2f18];
    unsigned short unk_2F18;
    unsigned short unk_2F1A;
    unsigned int unk_2F1C;
    unsigned int unk_2F20;
} UnkStruct_020bde24;

extern void func_0209def4(void *ptr);
extern unsigned int func_0209dedc(void);
extern void func_0209df64(void *p);
extern int func_0209dcdc(void *p, void *q);
extern int FX_Div(int a, int b);
extern int data_020d266c[];
extern int func_020644cc(int param);
extern int func_020be1c4(char *work, int a);
extern int func_020be0f8(char *work, int a, int b);
extern void func_020bee74(char *a, int b, char *c);
extern void func_020be160(char *a, int b);
extern void func_020bf948(char *a);
extern void func_020bf810(char *a, int b);
extern signed char data_020d2bb9[];
extern void func_020bf5f0(void *);

void func_020bde5c(void *base)
{
    unsigned int mode;
    unsigned short val;
    unsigned int *dst;

    func_0209def4((char *) base + 0x2f18);
    mode = func_0209dedc();
    dst = (unsigned int *) ((char *) base + 0x2f1c);
    *dst = mode;
    val = *(unsigned short *) ((char *) base + 0x2f18);
    *(unsigned short *) ((char *) base + 0x2f1a) = val;
    *(unsigned int *) ((char *) base + 0x2f20) = *dst;
}

void func_020bde24(UnkStruct_020bde24 *self)
{
    self->unk_2F1A = self->unk_2F18;
    self->unk_2F20 = self->unk_2F1C;
    func_0209def4((void *) (&self->unk_2F18));
    self->unk_2F1C = func_0209dedc();
}

int func_020bdd9c(void)
{
    unsigned char buf[8];
    int value;
    int shifted;
    int quotient;
    int c;

    buf[2] = 1;
    buf[3] = 1;
    buf[4] = 0;
    buf[5] = 0;
    func_0209df64(&buf[6]);
    func_0209def4(&buf[0]);
    value = func_0209dcdc(&buf[6], &buf[2]);
    if (buf[1] < 12) {
        value--;
    }
    if (value < 0) {
        value = 0;
    }
    value = value * 100 + 0x974;
    shifted = (value % 0xb89) << 12;
    quotient = shifted / 100;
    c = FX_Div(quotient, 0x1d87b);
    c = c * 28 - 0x800;
    c = c >> 12;
    if (c < 0) {
        c = 0x1b;
    }
    if (c > 0x1b) {
        c = 0x1b;
    }
    return c + 3;
}

int func_020bdd10(int arg0, int index, int flags)
{
    int ret = data_020d266c[index];
    if (index == 4) {
        ret = func_020bdd9c();
    } else if (index == 7) {
        if (func_020644cc(2) != 0) {
            ret = 40;
        }
    } else if (index == 5) {
        if (flags & 1) {
            ret = 33;
        }
    } else if (index == 9) {
        unsigned t = (flags & 0xF) + 0x1D;
        if ((t - 0x1D) <= 1) {
            ret = 45;
        } else if (t == 0x21 || t == 0x24 || t == 0x27 || t == 0x2A) {
            ret = 43;
        } else {
            ret = 44;
        }
    } else if (index == 2) {
        unsigned mask = flags & 0xF;
        if (mask == 0) {
            ret = 47;
        } else if (mask == 1) {
            ret = 49;
        } else {
            ret = 48;
        }
    }
    return ret;
}

void *func_020bdc50(char *work, int param1, int param2, int *param3, int param4)
{
    int result1, result2, index;
    char *p;

    result1 = func_020bdd10((int) work, param1, param4);
    p = 0;
    result2 = func_020be1c4(work, result1);
    if (result2 == 5) {
        goto done;
    }
    index = func_020be0f8(work, param1, param2);
    if (index == 0x3c) {
        goto done;
    }
    if (result2 != 6) {
        func_020bee74(work + 0x1b30 + result2 * 12, result1, work + 0x2eb8);
        func_020be160(work, result2);
    }
    index *= 0x74;
    p = work + index;
    func_020bf948(p);
    *(int *) p = param1;
    *(int *) (p + 4) = 1;
    *(int *) (p + 0x24) = result2;
    *(int *) (p + 8) = result1;
    *(char *) (p + 0x5d) = (signed char) data_020d2bb9[result1 << 4];
    if (param3) {
        *(int *) (p + 0x34) = param3[0];
        *(int *) (p + 0x38) = param3[1];
        *(int *) (p + 0x3c) = param3[2];
    }
    func_020bf810(p, param4);
    (*(int *) (work + 0x2f14))++;
done:
    return p;
}

void func_020bdc14(void *arg0, int arg1)
{
    void *r5;
    void *r6;
    void *r4;
    int *r4_ptr;
    int r0;

    r5 = arg0;
    r6 = (char *) r5 + 0x1b30;
    r4 = (char *) r5 + 0x2f14;
    while (r5 < r6) {
        if (arg1 == *(int *) r5) {
            func_020bf5f0(r5);
            r4_ptr = (int *) r4;
            r0 = *r4_ptr;
            *r4_ptr = r0 - 1;
        }
        r5 = (char *) r5 + 0x74;
    }
}

void func_020bdbe0(void *arg0)
{
    void *r5;
    void *r6;
    int *r4;
    int *r0;

    r5 = arg0;
    r6 = (char *) r5 + 0x1b30;
    r4 = (int *) ((char *) r5 + 0x2f14);

    while (r5 < r6) {
        if (*(int *) r5 != 0xd) {
            func_020bf5f0(r5);
            (*r4)--;
        }
        r5 = (char *) r5 + 0x74;
    }
}
