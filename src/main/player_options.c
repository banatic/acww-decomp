/* player_options: 32 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0203d4b8 @ 0x0203d4b8, 0x8 bytes, Thumb
 * func_0203d4a8 @ 0x0203d4a8, 0x10 bytes, Thumb
 * func_0203d480 @ 0x0203d480, 0x28 bytes, Thumb
 * func_0203d470 @ 0x0203d470, 0x10 bytes, Thumb
 * func_0203d448 @ 0x0203d448, 0x28 bytes, Thumb
 * func_0203d438 @ 0x0203d438, 0x10 bytes, Thumb
 * func_0203d41c @ 0x0203d41c, 0x1c bytes, Thumb
 * func_0203d394 @ 0x0203d394, 0x86 bytes, Thumb
 * func_0203d390 @ 0x0203d390, 0x2 bytes, Thumb
 * func_0203d38c @ 0x0203d38c, 0x2 bytes, Thumb
 * func_0203d388 @ 0x0203d388, 0x2 bytes, Thumb
 * func_0203d384 @ 0x0203d384, 0x2 bytes, Thumb
 * func_0203d368 @ 0x0203d368, 0x1c bytes, Thumb
 * func_0203d35c @ 0x0203d35c, 0xc bytes, Thumb
 * func_0203d34c @ 0x0203d34c, 0x10 bytes, Thumb
 * func_0203d338 @ 0x0203d338, 0x12 bytes, Thumb
 * func_0203d32c @ 0x0203d32c, 0xc bytes, Thumb
 * func_0203d320 @ 0x0203d320, 0xa bytes, Thumb
 * func_0203d30c @ 0x0203d30c, 0x12 bytes, Thumb
 * func_0203d300 @ 0x0203d300, 0xa bytes, Thumb
 * func_0203d2f4 @ 0x0203d2f4, 0xa bytes, Thumb
 * func_0203d2ec @ 0x0203d2ec, 0x8 bytes, Thumb
 * func_0203d2d4 @ 0x0203d2d4, 0x16 bytes, Thumb
 * func_0203d2c4 @ 0x0203d2c4, 0x10 bytes, Thumb
 * func_0203d2b4 @ 0x0203d2b4, 0x10 bytes, Thumb
 * func_0203d28c @ 0x0203d28c, 0x26 bytes, Thumb
 * func_0203d278 @ 0x0203d278, 0x12 bytes, Thumb
 * func_0203d264 @ 0x0203d264, 0x12 bytes, Thumb
 * func_0203d250 @ 0x0203d250, 0x12 bytes, Thumb
 * func_0203d244 @ 0x0203d244, 0xc bytes, Thumb
 * func_0203d238 @ 0x0203d238, 0xa bytes, Thumb
 * func_0203d22c @ 0x0203d22c, 0xa bytes, Thumb
 */

struct Bits {
    unsigned char flag0 : 1;
};

typedef struct {
    unsigned char b0 : 1;
    unsigned char b1 : 1;
    unsigned char b2 : 1;
    unsigned char b3 : 1;
    unsigned char b4 : 1;
    unsigned char b5 : 1;
    unsigned char b6 : 1;
    unsigned char b7 : 1;
} Flags;

struct UnkStruct_0203d278 {
    unsigned char pad_00;
    unsigned char flag : 1;
};

typedef struct {
    unsigned char unk_00;
    unsigned char unused0 : 2;
    unsigned char flag : 1;
} UnkStruct_0203d250;

typedef struct {
    unsigned char pad_00;
    unsigned char flag;
} UnkStruct_0203d244;

extern unsigned char data_021c6998[];
extern int func_020984e8(void);
extern int func_0209964c(int);
extern void MI_CpuCopy8(void *, void *, int);

void func_0203d35c(void *a, void *b);
void func_0203d34c(int a, int b);
int func_0203d338(const struct Bits *p);
void func_0203d32c(unsigned char *ptr);
void func_0203d320(unsigned char *p);
int func_0203d30c(Flags *p);
void func_0203d300(unsigned char *p);
void func_0203d2f4(unsigned char *p);
int func_0203d2ec(unsigned char *p0);
void func_0203d2d4(unsigned char *p, unsigned int value);
void func_0203d28c(void *arg0);
int func_0203d278(struct UnkStruct_0203d278 *p);
int func_0203d264(unsigned char *ptr);
int func_0203d250(const UnkStruct_0203d250 *s);
void func_0203d244(UnkStruct_0203d244 *p);
void func_0203d238(unsigned char *p);
void func_0203d22c(unsigned char *p);

int func_0203d4b8(void)
{
    return (int) ((int *) data_021c6998);
}

int func_0203d4a8(void)
{
    return func_0203d338((const struct Bits *) ((void *) data_021c6998));
}

void func_0203d480(int param)
{
    if (param == 1) {
        func_0203d32c((unsigned char *) (((char *) data_021c6998)));
    } else {
        func_0203d320((unsigned char *) (((char *) data_021c6998)));
    }
    func_0203d244((UnkStruct_0203d244 *) (((char *) data_021c6998)));
}

int func_0203d470(void)
{
    return func_0203d30c((Flags *) ((int) ((int *) data_021c6998)));
}

void func_0203d448(int param)
{
    if (param == 1) {
        func_0203d300((unsigned char *) (((char *) data_021c6998)));
    } else {
        func_0203d2f4((unsigned char *) (((char *) data_021c6998)));
    }

    func_0203d238((unsigned char *) (((char *) data_021c6998)));
}

int func_0203d438(void)
{
    return func_0203d2ec((unsigned char *) (((int *) data_021c6998)));
}

void func_0203d41c(unsigned int arg0)
{
    unsigned int local_0;

    func_0203d2d4((unsigned char *) (((char *) data_021c6998)), arg0);
    func_0203d22c((unsigned char *) (((char *) data_021c6998)));
}

void func_0203d394(void)
{
    int r5;
    int r4;
    int sp0;

    r5 = func_0209964c((int) func_020984e8());
    r4 = func_0203d4b8();
    if (func_0203d278((struct UnkStruct_0203d278 *) ((void *) r4)) != 0) {
        if (func_0203d4a8() == 1) {
            func_0203d32c((unsigned char *) r5);
        } else {
            func_0203d320((unsigned char *) r5);
        }
    }
    if (func_0203d264((unsigned char *) r4) != 0) {
        if (func_0203d470() == 1) {
            func_0203d300((unsigned char *) r5);
        } else {
            func_0203d2f4((unsigned char *) r5);
        }
    }
    if (func_0203d250((const UnkStruct_0203d250 *) r4) != 0) {
        func_0203d2d4((unsigned char *) r5, func_0203d438());
    }
    func_0203d35c((void *) r5, (void *) (&sp0));
    func_0203d28c((void *) r4);
    func_0203d34c(r4, (int) (&sp0));
}

void func_0203d390(void) {}

void func_0203d38c(void *object) {}

void func_0203d388(void *object) {}

void func_0203d384(void) {}

void func_0203d368(void *arg)
{
    func_0203d320((unsigned char *) arg);
    func_0203d2f4((unsigned char *) arg);
    func_0203d2d4((unsigned char *) arg, 0);
}

void func_0203d35c(void *a, void *b)
{
    MI_CpuCopy8(a, b, 1);
}

void func_0203d34c(int a, int b)
{
    MI_CpuCopy8((void *) b, (void *) a, 1);
}

int func_0203d338(const struct Bits *p)
{
    if (p->flag0) {
        return 1;
    } else {
        return 0;
    }
}

void func_0203d32c(unsigned char *ptr)
{
    *ptr = (*ptr & ~1) | 1;
}

void func_0203d320(unsigned char *p)
{
    p[0] = (unsigned char) (p[0] & ~1);
}

int func_0203d30c(Flags *p)
{
    if (p->b1) {
        return 1;
    } else {
        return 0;
    }
}

void func_0203d300(unsigned char *p)
{
    p[0] |= 2;
}

void func_0203d2f4(unsigned char *p)
{
    p[0] &= ~2;
}

int func_0203d2ec(unsigned char *p0)
{
    return (int) ((unsigned int) ((p0[0] << 28)) >> 30);
}

void func_0203d2d4(unsigned char *p, unsigned int value)
{
    *p = (*p & ~0x0C) | (((unsigned char) value & 3) << 2);
}

int func_0203d2c4(int arg)
{
    func_0203d390();
    return arg;
}

int func_0203d2b4(int arg)
{
    func_0203d384();
    return arg;
}

void func_0203d28c(void *arg0)
{
    unsigned char *p = (unsigned char *) arg0;

    func_0203d368(arg0);
    p[1] &= ~1;
    p[1] &= ~2;
    p[1] &= ~4;
}

int func_0203d278(struct UnkStruct_0203d278 *p)
{
    if (p->flag) {
        return 1;
    } else {
        return 0;
    }
}

int func_0203d264(unsigned char *ptr)
{
    unsigned int bit;
    bit = ((unsigned int) ptr[1] << 30) >> 31;
    if (bit == 0) {
        return 0;
    } else {
        return 1;
    }
}

int func_0203d250(const UnkStruct_0203d250 *s)
{
    if (s->flag) {
        return 1;
    } else {
        return 0;
    }
}

void func_0203d244(UnkStruct_0203d244 *p)
{
    p->flag = (p->flag & ~1) | 1;
}

void func_0203d238(unsigned char *p)
{
    p[1] |= 2;
}

void func_0203d22c(unsigned char *p)
{
    p[1] |= 4;
}
