/* wipe_2: 19 functions, module ov002
 * mwccarm 1.2/base -O4,s
 * func_ov002_02208874 @ 0x02208874, 0xc bytes, Thumb
 * func_ov002_02208868 @ 0x02208868, 0xc bytes, Thumb
 * func_ov002_02208850 @ 0x02208850, 0x18 bytes, Thumb
 * func_ov002_02208844 @ 0x02208844, 0xc bytes, Thumb
 * func_ov002_0220882c @ 0x0220882c, 0x18 bytes, Thumb
 * func_ov002_0220880c @ 0x0220880c, 0x1e bytes, Thumb
 * func_ov002_022087f4 @ 0x022087f4, 0x16 bytes, Thumb
 * func_ov002_022087ec @ 0x022087ec, 0x8 bytes, Thumb
 * func_ov002_022087d4 @ 0x022087d4, 0x18 bytes, Thumb
 * func_ov002_022087bc @ 0x022087bc, 0x18 bytes, Thumb
 * func_ov002_0220879c @ 0x0220879c, 0x20 bytes, Thumb
 * func_ov002_02208780 @ 0x02208780, 0x1a bytes, Thumb
 * func_ov002_02208764 @ 0x02208764, 0x1a bytes, Thumb
 * func_ov002_02208704 @ 0x02208704, 0x60 bytes, Thumb
 * func_ov002_022086d0 @ 0x022086d0, 0x34 bytes, Thumb
 * func_ov002_0220866c @ 0x0220866c, 0x62 bytes, Thumb
 * func_ov002_02208620 @ 0x02208620, 0x4c bytes, Thumb
 * func_ov002_022085e8 @ 0x022085e8, 0x38 bytes, Thumb
 * func_ov002_02208594 @ 0x02208594, 0x52 bytes, Thumb
 */

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
} UnkStruct_0220882c;

typedef struct {
    char pad_00[0x0c];
    int value;
    char pad_10[0x08];
    unsigned char flag;
} UnkStruct_02208780;

struct S_02208764 {
    char pad_00[0xc];
    int unk_0C;
    char pad_10[0x8];
    unsigned char unk_18;
};

typedef struct {
    unsigned char pad_00[0xc];
    int unk_0C;
    int unk_10;
    int unk_14;
} UnkStruct_02208704;

struct UnkStruct_022086d0 {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
};

typedef struct {
    char pad_00[0x0c];
    int unk_0C;
    char pad_10[0x08];
    unsigned char unk_18;
} UnkStruct_0220866c;

typedef struct UnkStruct_02208620 {
    unsigned char pad_00[0xc];
    int unk_0C;
    int unk_10;
    int unk_14;
} UnkStruct_02208620;

struct UnkStruct_022085e8 {
    char pad_00[0xc];
    int unk_0C;
    int unk_10;
};

extern unsigned char data_ov002_0220bb04[];
extern void func_020edb3c(void *);
extern unsigned int _u32_div_f(unsigned int numerator, unsigned int denominator);
extern struct UnkStruct_0220880c {
    int unk_00;
    int unk_04;
    int unk_08;
} *self;
extern int FX_MulFunc(int a, int b);
extern char data_ov002_0220baf4;
extern void func_ov002_02208348(UnkStruct_02208704 *p, int v);
extern void func_02001b6c(int v);
extern void func_02001d00(int v);
extern void func_02001ba4(int v);
extern void func_02001d1c(int v);
extern void func_02001b7c(int);
extern void func_02001bb4(int);

void func_ov002_02208874(unsigned int *p)
{
    *p = (unsigned int) data_ov002_0220bb04;
}

void func_ov002_02208868(int **p)
{
    *p = ((int *) data_ov002_0220bb04);
}

void *func_ov002_02208850(void *p)
{
    *(void **) p = (void *) ((char *) data_ov002_0220bb04);
    func_020edb3c(p);
    return p;
}

void func_ov002_02208844(void **out)
{
    *out = ((char *) data_ov002_0220bb04);
}

void func_ov002_0220882c(UnkStruct_0220882c *self, unsigned int denominator)
{
    self->unk_08 = 0x1000;
    self->unk_04 = _u32_div_f(0x1000, denominator);
}

int func_ov002_0220880c(struct UnkStruct_0220880c *self)
{
    int f8 = self->unk_08;
    if (f8 == 0) {
        return 1;
    }
    if (f8 > self->unk_04) {
        self->unk_08 = f8 - self->unk_04;
    } else {
        self->unk_08 = 0;
    }
    return 0;
}

int func_ov002_022087f4(int *self, int arg2)
{
    int value = self[2];
    int ret = FX_MulFunc(value, value);
    return (arg2 * ret) >> 12;
}

int func_ov002_022087ec(int *p0, int p1)
{
    return (p1 * p0[2]) >> 12;
}

void *func_ov002_022087d4(void *p)
{
    func_ov002_02208874((unsigned int *) p);
    *(void **) p = (void *) &data_ov002_0220baf4;
    return p;
}

void *func_ov002_022087bc(void *p)
{
    *(int **) p = ((int *) &data_ov002_0220baf4);
    func_ov002_02208844((void **) p);
    return p;
}

void *func_ov002_0220879c(void *p)
{
    *(void **) p = &data_ov002_0220baf4;
    func_ov002_02208844((void **) p);
    func_020edb3c(p);
    return p;
}

int func_ov002_02208780(UnkStruct_02208780 *self)
{
    switch (self->flag) {
        case 0:
            return self->value;
        case 1:
            return -self->value;
        default:
            return 0;
    }
}

int func_ov002_02208764(struct S_02208764 *self)
{
    switch (self->unk_18) {
        case 2:
            return -self->unk_0C;
        case 3:
            return self->unk_0C;
        default:
            return 0;
    }
}

void func_ov002_02208704(UnkStruct_02208704 *p, int dir)
{
    p->unk_0C = func_ov002_022087f4((int *) p, p->unk_10);
    switch (dir) {
        case 0:
            if (p->unk_0C > p->unk_14) {
                func_ov002_02208348(p, 2);
            } else {
                func_02001b6c(1);
                func_02001d00(0x1f);
            }
            break;
        case 1:
            if (p->unk_0C > p->unk_14) {
                func_ov002_02208348(p, 0);
            } else {
                func_02001ba4(1);
                func_02001d1c(0x1f);
            }
            break;
    }
}

void func_ov002_022086d0(struct UnkStruct_022086d0 *self, int mode)
{
    self->unk_0C = func_ov002_022087f4((int *) self, self->unk_10);
    switch (mode) {
        case 0:
            func_ov002_02208348((UnkStruct_02208704 *) self, 2);
            break;
        case 1:
            func_ov002_02208348((UnkStruct_02208704 *) self, 0);
    }
}

int func_ov002_0220866c(UnkStruct_0220866c *self, int kind)
{
    if (func_ov002_0220880c((struct UnkStruct_0220880c *) self)) {
        self->unk_0C = 0;
        switch (kind) {
            case 0:
                func_02001b6c(1);
                func_02001d00(0x1f);
                break;
            case 1:
                func_02001ba4(1);
                func_02001d1c(0x1f);
                break;
            default:
                break;
        }
        return 1;
    } else {
        switch (self->unk_18) {
            case 0:
            case 1:
                func_ov002_02208704((UnkStruct_02208704 *) self, kind);
                break;
            default:
                func_ov002_022086d0((struct UnkStruct_022086d0 *) self, kind);
                break;
        }
        return 0;
    }
}

void func_ov002_02208620(UnkStruct_02208620 *obj, int flag)
{
    obj->unk_0C = obj->unk_10 - func_ov002_022087ec((int *) obj, obj->unk_10);
    if (obj->unk_0C > obj->unk_14) {
        switch (flag) {
            case 0:
                func_02001b7c(1);
                func_ov002_02208348((UnkStruct_02208704 *) obj, 2);
                break;
            case 1:
                func_02001bb4(1);
                func_ov002_02208348((UnkStruct_02208704 *) obj, 0);
                break;
        }
    }
}

void func_ov002_022085e8(struct UnkStruct_022085e8 *a, int b)
{
    a->unk_0C = a->unk_10 - func_ov002_022087ec((int *) a, a->unk_10);
    switch (b) {
        case 0:
            func_ov002_02208348((UnkStruct_02208704 *) a, 2);
            break;
        case 1:
            func_ov002_02208348((UnkStruct_02208704 *) a, 0);
            break;
    }
}

int func_ov002_02208594(void *self, int q)
{
    unsigned char kind;

    if (func_ov002_0220880c((struct UnkStruct_0220880c *) self)) {
        switch (q) {
            case 0:
                func_02001b6c(1);
                break;
            case 1:
                func_02001ba4(1);
                break;
        }
        return 1;
    }

    kind = ((unsigned char *) self)[0x18];
    switch (kind) {
        case 0:
        case 1:
            func_ov002_02208620((UnkStruct_02208620 *) self, q);
            break;
        default:
            func_ov002_022085e8((struct UnkStruct_022085e8 *) self, q);
            break;
    }
    return 0;
}
