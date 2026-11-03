/* town_tune: 17 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0206eac0 @ 0x0206eac0, 0x18 bytes, Thumb
 * func_0206ea84 @ 0x0206ea84, 0x3a bytes, Thumb
 * func_0206ea5c @ 0x0206ea5c, 0x28 bytes, Thumb
 * func_0206ea54 @ 0x0206ea54, 0x8 bytes, Thumb
 * func_0206ea3c @ 0x0206ea3c, 0x18 bytes, Thumb
 * func_0206ea28 @ 0x0206ea28, 0x14 bytes, Thumb
 * func_0206ea10 @ 0x0206ea10, 0x18 bytes, Thumb
 * func_0206ea00 @ 0x0206ea00, 0x10 bytes, Thumb
 * func_0206e9ec @ 0x0206e9ec, 0x14 bytes, Thumb
 * func_0206e9bc @ 0x0206e9bc, 0x30 bytes, Thumb
 * func_0206e9ac @ 0x0206e9ac, 0x10 bytes, Thumb
 * func_0206e980 @ 0x0206e980, 0x2c bytes, Thumb
 * func_0206e970 @ 0x0206e970, 0x10 bytes, Thumb
 * func_0206e94c @ 0x0206e94c, 0x24 bytes, Thumb
 * func_0206e928 @ 0x0206e928, 0x24 bytes, Thumb
 * func_0206e904 @ 0x0206e904, 0x24 bytes, Thumb
 * func_0206e8d8 @ 0x0206e8d8, 0x2c bytes, Thumb
 */

struct S0206eac0 {
    char pad_00[0x14];
    void *unk_14;
};

struct UnkStruct_0206ea5c {
    unsigned int unk_00;
    unsigned int unk_04;
};

extern void *func_020f70d0(void *p);
extern unsigned long long func_02136778(long long x, int y);
extern unsigned int func_02136b98(unsigned int a, unsigned int b, int c);
extern unsigned char data_021cfbbc[];
extern void func_0200419c(void *dst, const void *src);
extern unsigned char data_021cfbcc[];
extern void func_02004194(unsigned int a, unsigned int b, unsigned int c);
extern void func_02004150(void *ptr, int val);
extern void func_02004158(void *dst, const void *src, unsigned int size);
extern void func_02004148(void *ptr);
extern int data_021cfbac;
extern void func_02004140(void *dest, int value);
extern int func_02004130(int *p);
extern int func_02004128(void *ptr, int arg);
extern void *func_02004120(void *);
extern unsigned char data_021f3b68[];
extern void *func_02004118(void *);
extern void func_020041a4(void *);
extern unsigned int data_020df2a0;
extern int func_02004138(void *);

void func_0206ea28(void);
void func_0206e928(void);

void *func_0206eac0(struct S0206eac0 *self)
{
    func_020f70d0(&self->unk_14);
    func_020f70d0(self);
    return self;
}

void func_0206ea84(unsigned long long *out, const unsigned char *in)
{
    int i = 0;
    *out = 0;
    do {
        *out |= func_02136778(in[i] & 0xf, i * 4);
        i++;
    } while (i < 16);
}

void func_0206ea5c(struct UnkStruct_0206ea5c *s, unsigned char *out)
{
    int i;
    for (i = 0; i < 16; i++) {
        out[i] = (unsigned char) (func_02136b98(s->unk_00, s->unk_04, i * 4) & 0xF);
    }
}

void func_0206ea54(void *object)
{
    func_0206e928();
}

void func_0206ea3c(void *a)
{
    func_0206ea5c((struct UnkStruct_0206ea5c *) a, (unsigned char *) ((void *) data_021cfbbc));
    func_0206ea28();
}

void func_0206ea28(void)
{
    func_0200419c((void *) data_021cfbcc, (const void *) data_021cfbbc);
}

void func_0206ea10(unsigned int arg)
{
    func_02004194((unsigned int) data_021cfbcc, arg, (unsigned int) data_021cfbbc);
}

void func_0206ea00(int arg)
{
    func_02004150(((int *) data_021cfbcc), arg);
}

void func_0206e9ec(void *dst, const void *src)
{
    func_02004158((void *) data_021cfbcc, dst, (unsigned int) src);
}

void func_0206e9bc(int param)
{
    func_02004148(((int *) data_021cfbcc));
    if (param != 0) {
        data_021cfbac = 0x190;
    } else {
        data_021cfbac = 0x14;
    }
}

void func_0206e9ac(int value)
{
    func_02004140((void *) data_021cfbcc, value);
}

int func_0206e980(void)
{
    return (data_021cfbac != 0) || (func_02004130(((int *) data_021cfbcc)) != 0);
}

int func_0206e970(int arg)
{
    return func_02004128(((int *) data_021cfbcc), arg);
}

void func_0206e94c(void)
{
    void *ptr = func_02004120((void *) data_021cfbcc);
    if (ptr != 0) {
        func_0206ea84((unsigned long long *) ((void *) data_021f3b68), (const unsigned char *) ptr);
    }
}

void func_0206e928(void)
{
    void *ptr = func_02004118((void *) data_021cfbcc);
    if (ptr != 0) {
        func_0206ea84((unsigned long long *) ((void *) data_021f3b68), (const unsigned char *) ptr);
    }
}

void func_0206e904(void)
{
    unsigned int *p;
    unsigned int val;

    func_020041a4((void *) data_021cfbcc);
    val = 0;
    val = ~val;
    p = &data_020df2a0;
    *p = val;
    func_0206ea28();
}

void func_0206e8d8(void)
{
    if (data_021cfbac != 0) {
        data_021cfbac--;
    }
    (*(int *) &data_020df2a0) = func_02004138(((int *) data_021cfbcc));
}
