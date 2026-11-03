/* field_actor_states_5: 15 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02008c8c @ 0x02008c8c, 0x20 bytes, Thumb
 * func_02008c40 @ 0x02008c40, 0x4a bytes, Thumb
 * func_02008bf4 @ 0x02008bf4, 0x4c bytes, Thumb
 * func_02008be8 @ 0x02008be8, 0xc bytes, Thumb
 * func_02008aa8 @ 0x02008aa8, 0x140 bytes, Thumb
 * func_02008a8c @ 0x02008a8c, 0x1a bytes, Thumb
 * func_02008a54 @ 0x02008a54, 0x36 bytes, Thumb
 * func_02008a38 @ 0x02008a38, 0x1a bytes, Thumb
 * func_02008a2c @ 0x02008a2c, 0xc bytes, Thumb
 * func_020089dc @ 0x020089dc, 0x50 bytes, Thumb
 * func_020089b0 @ 0x020089b0, 0x2c bytes, Thumb
 * func_02008970 @ 0x02008970, 0x40 bytes, Thumb
 * func_02008934 @ 0x02008934, 0x3c bytes, Thumb
 * func_02008910 @ 0x02008910, 0x24 bytes, Thumb
 * func_020088fc @ 0x020088fc, 0x14 bytes, Thumb
 */

typedef struct T12c {
    unsigned char pad_00[4];
    int unk_04;
    int unk_08;
} T12c;

struct UnkStruct_02008aa8 {
    unsigned char pad_00[0xec];
    unsigned char pad_EC[0x10a - 0xec];
    unsigned char unk_10A;
    unsigned char pad_10B[0x12c - 0x10a - 1];
    T12c *unk_12C;
    unsigned char pad_130[0x704 - 0x130];
    int unk_704;
    unsigned char pad_708[0x7d4 - 0x708];
    unsigned char unk_7D4;
    unsigned char unk_7D5;
    unsigned char pad_7D6[0x7f0 - 0x7d6];
    int unk_7F0;
    unsigned char pad_7F4[0x7fc - 0x7f4];
    int unk_7FC;
    int unk_800;
};

typedef struct UnkStruct_02008a38 UnkStruct_02008a38;

struct UnkStruct020089dc {
    char pad_00[0x2d0];
    char unk_2D0;
    char pad_2D1[0x800 - 0x2d0 - 1];
    unsigned int unk_800;
};

typedef struct {
    char pad_00[0x800];
    int unk_800;
} UnkStruct_02008970;

extern void func_02008cec(int);
extern void func_02008cac(int);
extern unsigned int func_0200e92c(void *);
extern void func_0200e90c(void *, int, int, int);
extern int func_0200e894(void *, void *);
extern unsigned int *func_0200f27c(void *, int);
extern int func_0200e91c(void *);
extern void func_020109a0(int, int, int, unsigned short);
extern int func_02073908(int, int);
extern void func_02035684(int, int, int);
extern int func_0200f328(int, int);
extern int data_020ccf94;
extern int data_020d83b4;
extern int func_02056f94(void *p);
extern void func_020109fc(void *self, int a, int b, int c);
extern unsigned char func_02008258(void *self, int idx);
extern int func_0200faf0(void *self, int code);
extern int func_0203e1c4(void);
extern void func_0203ee14(void *self, void *b);
extern void func_020a8164(void *p, void *g);
extern void func_0203ae98(void);
extern void func_0203ee08(void *self, void *b);
extern void func_0200f268(void *self, int code);
extern int func_0203e19c(void);
extern int func_0200d4e8(void *self, int a, int b, int c);
extern int func_0203b144(void);
extern void func_02035624(int code);
extern void func_02010f5c(void *);
extern void func_02010d64(void *);
extern int func_02056f28(void *p, int n);
extern void func_020f1fb4(unsigned int a, int b);
extern unsigned char data_021fd1bc[];
extern int func_0200f554(void *arg);

void func_02008c8c(int arg)
{
    func_02010f5c((void *) arg);
    func_02008cec(arg);
    func_02010d64((void *) arg);
    func_02008cac(arg);
}

int func_02008c40(void *p0, int p1, int p2)
{
    char local[0x20];
    func_0200e92c(local);
    func_0200e90c(local, 0x79, p1, p2);
    if (func_0200e894(p0, local)) {
        func_0200f27c(p0, 8);
        func_0200e91c(local);
        return 1;
    }
    func_0200e91c(local);
    return 0;
}

void func_02008bf4(int param, void *message, int previous)
{
    int local;
    int *ptr;

    func_020109a0(param, 0x76, 3, 0);
    local = 0;
    *(char *) (param + 0x7d4) = local;
    ptr = &data_020ccf94;
    if (func_02073908(*ptr, *(int *) (param + 0x800)) != 0) {
        func_02035684(0xc, 0xf, 0);
    }
    func_0200f328(param, 0x83a);
}

void func_02008be8(int a, int b)
{
    func_02008c40((void *) a, 5, b);
}

void func_02008aa8(struct UnkStruct_02008aa8 *self)
{
    unsigned char *statep = &self->unk_7D4;
    void *b;

    if (self->unk_704 == 0x76) {
        if (func_02056f94((char *) self + 0x2d0) != 0) {
            func_020109fc(self, 0x77, 0, 0);
            if (func_02073908((int) ((*(void * *) &data_020ccf94)), self->unk_800) == 0) {
                *statep = 3;
                self->unk_7FC = func_02008258(self, self->unk_7F0);
            }
        }
    } else {
        func_0200faf0(self, 0x400);
        switch (*statep) {
            case 0:
                if (func_0203e1c4() != 0) {
                    *statep = 1;
                    b = (char *) self;
                    if (self != 0) {
                        b = (char *) self + 0xec;
                    }
                    func_0203ee14(self, b);
                    func_0200f27c(self, 0x11);
                    func_020a8164((char *) self + 0xec, &data_020d83b4);
                    self->unk_10A = 0x15;
                    self->unk_12C->unk_08 = 1;
                    func_0203ae98();
                }
                // fall through
            case 1:
                if (self->unk_12C != 0 && self->unk_12C->unk_04 != 0) {
                    *statep = 2;
                }
                break;
            case 2:
                if (self->unk_12C != 0 && self->unk_12C->unk_04 == 0) {
                    b = (char *) self;
                    if (self != 0) {
                        b = (char *) self + 0xec;
                    }
                    func_0203ee08(self, b);
                    func_0200f268(self, 0x11);
                    func_0203e19c();
                    self->unk_7FC = func_02008258(self, self->unk_7F0);
                    func_0200d4e8(self, 3, 1, -1);
                    func_0200f268(self, 8);
                    func_0203b144();
                    func_02035624(0xc);
                }
                break;
        }
    }
}

void func_02008a8c(void *arg)
{
    func_02010f5c(arg);
    func_02010d64(arg);
    func_02008aa8((struct UnkStruct_02008aa8 *) arg);
}

int func_02008a54(int a, int b, int c)
{
    unsigned char buf[32];
    int result;

    func_0200e92c(buf);
    func_0200e90c(buf, 0x83, b, c);
    result = func_0200e894((void *) a, buf);
    func_0200e91c(buf);
    return result;
}

void func_02008a38(UnkStruct_02008a38 *p, int q, int c)
{
    int t = 0;
    if (c) {
        t = 5;
    }
    func_020109fc((void *) p, 0x81, t, t);
}

void func_02008a2c(int a, int b)
{
    func_02008a54(a, 1, b);
}

void func_020089dc(struct UnkStruct020089dc *p)
{
    func_02010f5c(p);
    if (func_02056f28(&p->unk_2D0, 1)) {
        if (func_02073908((*(unsigned int *) &data_020ccf94), p->unk_800)) {
            func_020f1fb4((unsigned int) data_021fd1bc, 0x79);
        } else {
            func_0200f328((int) p, 0x79);
        }
    }
}

void func_020089b0(int param)
{
    if (!((*(volatile unsigned short *) 0x027fffa8 & 0x8000) >> 15)) {
        func_0200d4e8((void *) param, 3, 1, -1);
    }
}

void func_02008970(UnkStruct_02008970 *arg)
{
    func_020089dc((struct UnkStruct020089dc *) arg);
    if (func_02073908(data_020ccf94, arg->unk_800) != 0) {
        func_02010d64(arg);
        func_020089b0((int) arg);
    } else {
        func_0200f554(arg);
        func_02010d64(arg);
    }
}

int func_02008934(void *a, unsigned char b, int c, int d)
{
    struct {
        unsigned char data[0x1c];
    } local;
    int result;
    func_0200e92c(&local);
    func_0200e90c(&local, 0x84, c, d);
    local.data[0xc] = b;
    result = func_0200e894(a, &local);
    func_0200e91c(&local);
    return result;
}

void func_02008910(void *obj, const unsigned char *src, int previous)
{
    unsigned char *p = (unsigned char *) obj + 0x7d4;
    *p = src[0xc];
    p[1] = 0;
    func_020109fc(obj, 0, 3, 3);
}

void func_020088fc(int a, int b)
{
    func_02008934((void *) a, 0, 6, b);
}
