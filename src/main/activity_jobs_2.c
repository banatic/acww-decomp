/* activity_jobs_2: 19 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020a4840 @ 0x020a4840, 0x8c bytes, Thumb
 * func_020a475c @ 0x020a475c, 0xe4 bytes, Thumb
 * func_020a4740 @ 0x020a4740, 0x1c bytes, Thumb
 * func_020a467c @ 0x020a467c, 0xc4 bytes, Thumb
 * func_020a4678 @ 0x020a4678, 0x2 bytes, Thumb
 * func_020a464c @ 0x020a464c, 0x2c bytes, Thumb
 * func_020a4648 @ 0x020a4648, 0x2 bytes, Thumb
 * func_020a45f0 @ 0x020a45f0, 0x58 bytes, Thumb
 * func_020a45ec @ 0x020a45ec, 0x2 bytes, Thumb
 * func_020a4594 @ 0x020a4594, 0x58 bytes, Thumb
 * func_020a4590 @ 0x020a4590, 0x2 bytes, Thumb
 * func_020a4560 @ 0x020a4560, 0x30 bytes, Thumb
 * func_020a455c @ 0x020a455c, 0x2 bytes, Thumb
 * func_020a44f0 @ 0x020a44f0, 0x6c bytes, Thumb
 * func_020a44ec @ 0x020a44ec, 0x2 bytes, Thumb
 * func_020a44bc @ 0x020a44bc, 0x2e bytes, Thumb
 * func_020a44b8 @ 0x020a44b8, 0x2 bytes, Thumb
 * func_020a4454 @ 0x020a4454, 0x64 bytes, Thumb
 * func_020a4450 @ 0x020a4450, 0x2 bytes, Thumb
 */

struct UnkStruct_020a4840 {
    char pad_00[0xa1];
    unsigned char state;
};

struct Buf {
    char pad_00[0x24];
};

typedef struct UnkStruct_020a475c UnkStruct_020a475c;

struct UnkStruct_020a475c {
    unsigned char pad_00[0xA1];
    unsigned char state;
    unsigned char pad_A2[0x6C];
    struct {
        unsigned char low : 4;
        unsigned char high : 4;
    } flags;
};

struct UnkStruct_020a467c {
    unsigned char pad_00[0xa1];
    unsigned char state;
    unsigned char pad_A2[0x6c];
    unsigned char low : 4;
    unsigned char high : 4;
};

struct UnkStruct_020a464c {
    int unk_00;
    int unk_04;
};

typedef struct {
    int a[3];
} UnkStruct_020a45f0;

struct UnkStruct_020a4594 {
    int unk_00;
    int unk_04;
};

typedef struct {
    unsigned int pad_00;
    unsigned int unk_04;
} ResultStruct;

extern unsigned char data_021dc7a8[];
extern int data_021dc7bc;
extern int data_021f3c34;
extern int data_020e3c54;
extern void *func_02098844(int *p, int v);
extern void *func_02094fd4(struct Buf *b);
extern void *func_02099870(void *p);
extern void *func_02095074(void *p, struct Buf *b);
extern void func_02068404(int a, int b, struct Buf *c);
extern void func_02099a38(void *p);
extern void func_0209ef10(unsigned char *p, int v);
extern int func_020a1954(struct UnkStruct_020a4840 *o, int *p, int n);
extern int func_02098880(int *p);
extern void *func_02094fbc(struct Buf *b);
extern int func_020a259c(UnkStruct_020a475c *self, int arg2);
extern int func_020a238c(UnkStruct_020a475c *self);
extern int func_020a2120(UnkStruct_020a475c *self, int value);
extern void func_020a261c(void *object);
extern void func_020a25cc(void *receiver);
extern unsigned char data_020e3c68[];
extern void func_020a4e94(void *s, int a);
extern struct UnkStruct_020a464c *func_020682e0(int a);
extern int func_020b5e10(void);
extern int func_020b6098(int a, int b);
extern int func_020b63f4(int, int, void *, int, int, int, int);
extern UnkStruct_020a45f0 data_020d1bfc;
extern int data_020d1c14[3];
extern int func_020b6434(int, int, int, int);
extern void func_02068320(void *);
extern int func_020a1c9c(void);
extern void func_0209ef7c(int *);
extern void func_02098540(void);
extern void func_020792c8(void);
extern void func_0209e6ec(int *, int);
extern void func_0209e604(int *);
extern void func_020792b4(void);
extern void func_020a53ec(int, int, int, int);
extern unsigned char data_021c75b8;
extern int func_0209f150(void *ptr, unsigned int value);
extern void func_020a1308(void);
extern void func_020a12fc(void);
extern void func_020a13e8(void);

void func_020a4840(struct UnkStruct_020a4840 *self)
{
    struct Buf buf;
    unsigned char *base;
    int h;
    void *f;

    h = (int) func_020682e0(0);
    base = data_021dc7a8;
    f = func_02098844(&data_021dc7bc, data_021f3c34);
    func_02094fd4(&buf);
    func_02095074(func_02099870(f), &buf);
    func_02068404(h, 0, &buf);
    func_02099a38(f);
    func_0209ef10(base, data_021f3c34);
    func_020a1954(self, &data_020e3c54, 7);
    if (func_02098880(&data_021dc7bc) == 0) {
        base[0x17276] = 0;
    }
    self->state = 0;
    func_02094fbc(&buf);
}

void func_020a475c(UnkStruct_020a475c *self)
{
    switch (self->state) {
        case 0:
            if (func_020a259c(self, 0) != 0) {
                self->state = 1;
            }
            break;
        case 1: {
            int r = func_020a238c(self);
            if (r == 1) {
                self->state = 5;
            } else if (r == 3) {
                break;
            } else {
                self->state = 2;
            }
            break;
        }
        case 2: {
            int r = func_020a2120(self, self->flags.high);
            if (r == 1) {
                self->state = 5;
            } else if (r == 0) {
                self->state = 3;
            }
            break;
        }
        case 3: {
            int r = func_020a2120(self, self->flags.low);
            if (r == 1) {
                self->state = 5;
            } else if (r == 0) {
                self->state = 4;
            }
            break;
        }
        case 4: {
            int r = func_020a2120(self, 2);
            if (r == 1) {
                self->state = 5;
            } else if (r == 0) {
                self->state = 7;
            }
            break;
        }
        case 5:
            func_020a261c(self);
            self->state = 6;
            break;
        case 6:
            break;
        default:
            func_020a25cc(self);
            func_020a4e94((void *) self, 0xC);
            break;
    }
}

void func_020a4740(void *param0)
{
    unsigned char *ptr;
    ptr = (unsigned char *) param0;
    func_020a1954((struct UnkStruct_020a4840 *) ptr, (int *) ((void *) data_020e3c68), 0x27);
    ptr[0xa1] = 0;
}

void func_020a467c(struct UnkStruct_020a467c *self)
{
    switch (self->state) {
        case 0:
            if (func_020a259c((UnkStruct_020a475c *) self, 0) != 0) {
                self->state = 1;
            }
            break;
        case 1: {
            int r = func_020a238c((UnkStruct_020a475c *) self);
            if (r == 1) {
                self->state = 4;
            } else if (r != 3) {
                self->state = 2;
            }
            break;
        }
        case 2: {
            int r = func_020a2120((UnkStruct_020a475c *) self, self->high);
            if (r == 1) {
                self->state = 4;
            } else if (r == 0) {
                self->state = 3;
            }
            break;
        }
        case 3: {
            int r = func_020a2120((UnkStruct_020a475c *) self, self->low);
            if (r == 1) {
                self->state = 4;
            } else if (r == 0) {
                self->state = 6;
            }
            break;
        }
        case 4:
            func_020a261c(self);
            self->state = 5;
            break;
        case 5:
            break;
        default:
            func_020a25cc(self);
            func_020a4e94(self, 0xf);
            break;
    }
}

void func_020a4678(void) {}

void func_020a464c(void *arg)
{
    struct UnkStruct_020a464c *p = func_020682e0(0);
    int val = p->unk_04;
    if (val == 0) {
        func_02068320((void *) p);
        func_020b6098(func_020b5e10(), 1);
        func_020a4e94(arg, 0);
    }
}

void func_020a4648(void) {}

void func_020a45f0(int param)
{
    int *p;
    UnkStruct_020a45f0 local;

    p = (int *) func_020682e0(0);
    if (p[1] == 0) {
        func_02068320((void *) p);
        local.a[0] = data_020d1bfc.a[0];
        local.a[1] = data_020d1bfc.a[1];
        func_020b63f4((local.a[2] = data_020d1bfc.a[2], func_020b5e10()), 13, &local, 0x00800000, 0, 3, 2);
        func_020a4e94((void *) param, 0);
    }
}

void func_020a45ec(void) {}

void func_020a4594(int param)
{
    struct UnkStruct_020a4594 *p;
    int local[3];

    p = (struct UnkStruct_020a4594 *) func_020682e0(0);
    if (p->unk_04 != 0) {
        return;
    }
    func_02068320((void *) p);
    local[0] = data_020d1c14[0];
    local[1] = data_020d1c14[1];
    local[2] = data_020d1c14[2];
    func_020b63f4(func_020b5e10(), 0xe, (void *) local, 0x00800000, 0, 3, 2);
    func_020a4e94((void *) param, 0);
}

void func_020a4590(void) {}

void func_020a4560(int arg)
{
    int *p;
    p = (int *) func_020682e0(0);
    if (p[1] != 0) {
        return;
    }
    func_02068320((void *) ((int) p));
    func_020b6434(func_020b5e10(), 0x2f, 3, 2);
    func_020a4e94((void *) arg, 0);
}

void func_020a455c(void) {}

void func_020a44f0(int *param)
{
    void *p;
    int x;
    p = (void *) func_020682e0(0);
    if (((int *) p)[1] != 0) {
        return;
    }
    func_02068320(p);
    x = func_020a1c9c();
    if ((x == 4) || (x == 1)) {
        func_0209ef7c(((int *) data_021dc7a8));
        func_02098540();
        func_020792c8();
        func_0209e6ec(((int *) data_021dc7a8), 3);
    } else {
        func_0209e6ec(((int *) data_021dc7a8), 4);
    }
    func_0209e604(((int *) data_021dc7a8));
    func_020792b4();
    func_020b6434((int) ((void *) func_020b5e10()), 0x2c, 3, 2);
    func_020a4e94((void *) param, 0);
}

void func_020a44ec(void) {}

void func_020a44bc(void *param)
{
    struct UnkStruct_020a44bc {
        int pad_00;
        int field;
    } *p;
    int zero;

    p = (void *) func_020682e0(0);
    if (p->field != 0) {
        return;
    }
    zero = 0;
    func_02068320(p);
    func_020a53ec(2, 3, zero, zero);
    func_020a4e94(param, 0);
}

void func_020a44b8(void) {}

void func_020a4454(void *arg0)
{
    ResultStruct *result;
    unsigned int flag;
    result = (ResultStruct *) func_020682e0(0);
    flag = data_021c75b8 == 2;
    if (flag == 0) {
        return;
    }
    if (result->unk_04 != 0) {
        return;
    }
    func_02068320(result);
    if (func_0209f150(((unsigned int *) data_021dc7a8), 0x12) != 0) {
        func_020a1308();
    } else {
        func_020a12fc();
    }
    func_020a13e8();
    func_020b6434(func_020b5e10(), 0x2d, 3, 0);
    func_020a4e94(arg0, 0);
}

void func_020a4450(void) {}
