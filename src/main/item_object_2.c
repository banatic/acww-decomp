/* item_object_2: 20 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0209bd80 @ 0x0209bd80, 0x18 bytes, Thumb
 * func_0209bd7c @ 0x0209bd7c, 0x2 bytes, Thumb
 * func_0209bd5c @ 0x0209bd5c, 0x20 bytes, Thumb
 * func_0209bd50 @ 0x0209bd50, 0xc bytes, Thumb
 * func_0209bd44 @ 0x0209bd44, 0xc bytes, Thumb
 * func_0209bd30 @ 0x0209bd30, 0x14 bytes, Thumb
 * func_0209bd24 @ 0x0209bd24, 0xc bytes, Thumb
 * func_0209bd10 @ 0x0209bd10, 0x14 bytes, Thumb
 * func_0209bd04 @ 0x0209bd04, 0xc bytes, Thumb
 * func_0209bcd4 @ 0x0209bcd4, 0x30 bytes, Thumb
 * func_0209bcc4 @ 0x0209bcc4, 0x10 bytes, Thumb
 * func_0209bcb8 @ 0x0209bcb8, 0xc bytes, Thumb
 * func_0209bc94 @ 0x0209bc94, 0x24 bytes, Thumb
 * func_0209bc88 @ 0x0209bc88, 0xc bytes, Thumb
 * func_0209bc54 @ 0x0209bc54, 0x34 bytes, Thumb
 * func_0209bc44 @ 0x0209bc44, 0x10 bytes, Thumb
 * func_0209bc40 @ 0x0209bc40, 0x4 bytes, Thumb
 * func_0209bc24 @ 0x0209bc24, 0x1c bytes, Thumb
 * func_0209bc20 @ 0x0209bc20, 0x2 bytes, Thumb
 * func_0209bbf8 @ 0x0209bbf8, 0x28 bytes, Thumb
 */

typedef struct {
    int unk_00;
    int unk_04;
    volatile unsigned short unk_08;
    volatile unsigned char unk_0A;
} UnkStruct_0209bd80;

typedef struct {
    unsigned char pad_00[8];
    unsigned short unk_08;
    unsigned char unk_0A;
    unsigned char unk_0B;
} UnkStruct_0209bd5c;

typedef struct {
    unsigned char unk_00[8];
    unsigned short unk_08;
    unsigned char unk_0A;
    unsigned char unk_0B;
} UnkStruct_0209bd30;

struct UnkStruct_0209bd04 {
    char pad_00[0xa];
    unsigned char unk_0A;
};

typedef struct {
    unsigned char pad_00[10];
    unsigned char byte;
} UnkStruct_0209bcc4;

struct Struct0209bc88 {
    unsigned char data[0xa];
    unsigned char byte;
};

typedef struct {
    char pad_00[0xa];
    unsigned char byte_at_0xa;
} UnkStruct_0209bc44;

extern int data_020d1a40[];
extern int data_020d1a6c[];
extern void func_0209e474(int p1);
extern void func_0209e234(int p1, int p2);

void func_0209bd80(UnkStruct_0209bd80 *p)
{
    p->unk_00 = 0;
    p->unk_04 = 0;
    p->unk_08 = 0xfff1;
    p->unk_0A = 0x16;
    p->unk_08 = 0xfff1;
}

void func_0209bd7c(void *object) {}

void func_0209bd5c(UnkStruct_0209bd5c *p)
{
    p->unk_0A = 0x16;
    p->unk_08 = 0xfff1;
    p->unk_0B &= ~0x1F;
    p->unk_0B &= ~0xE0;
}

int func_0209bd50(unsigned int x)
{
    if (x >= 22) {
        return 0;
    } else {
        return 1;
    }
}

int func_0209bd44(void *ptr)
{
    return func_0209bd50((unsigned char) (((unsigned char *) ptr)[0xa]));
}

void func_0209bd30(UnkStruct_0209bd30 *s, unsigned char a, unsigned short *h, unsigned char b)
{
    s->unk_0A = a;
    s->unk_08 = *h;
    s->unk_0B = (s->unk_0B & ~0x1f) | (b & 0x1f);
}

int func_0209bd24(unsigned int x)
{
    if (x < 2) {
        return 1;
    }
    return 0;
}

int func_0209bd10(unsigned int r0)
{
    int result = 2;
    if (r0 < 5) {
        result = 0;
    } else if (r0 < 22) {
        result = 1;
    }
    return result;
}

int func_0209bd04(struct UnkStruct_0209bd04 *self)
{
    return func_0209bd10((unsigned char) self->unk_0A);
}

int func_0209bcd4(int *out, int val)
{
    int idx = func_0209bd10(val);
    if (func_0209bd24(idx) != 0) {
        *out = val - data_020d1a40[idx];
        return 1;
    }
    return 0;
}

int func_0209bcc4(UnkStruct_0209bcc4 *a, unsigned int b)
{
    return func_0209bcd4((int *) b, (unsigned char) a->byte);
}

int func_0209bcb8(unsigned int a)
{
    if (a >= 4) {
        return 0;
    } else {
        return 1;
    }
}

int func_0209bc94(unsigned int r0)
{
    int r1 = 4;
    if (r0 < 10) {
        r1 = 0;
    } else if (r0 < 20) {
        r1 = 1;
    } else if (r0 < 21) {
        r1 = 2;
    } else if (r0 < 22) {
        r1 = 3;
    }
    return r1;
}

int func_0209bc88(struct Struct0209bc88 *self)
{
    return func_0209bc94((unsigned char) self->byte);
}

int func_0209bc54(int *out, int val)
{
    int i = func_0209bc94(val);
    int ret = 0;
    if (func_0209bcb8(i) != 0) {
        *out = val - data_020d1a6c[i];
        ret = 1;
    }
    return ret;
}

int func_0209bc44(UnkStruct_0209bc44 *a, int b)
{
    return func_0209bc54((int *) b, (unsigned char) a->byte_at_0xa);
}

int func_0209bc40(unsigned char *p0)
{
    return p0[10];
}

void func_0209bc24(int p1, int p2)
{
    func_0209e474(p1);
    func_0209e234(p1, p2);
}

void *func_0209bc20(void *record)
{
    return record;
}

int func_0209bbf8(unsigned int param)
{
    int ret = 2;
    if (func_0209bc94(param) == 1) {
        if (param < 19) {
            ret = 0;
        } else if (param < 20) {
            ret = 1;
        }
    }
    return ret;
}
