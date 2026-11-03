/* music_264_2: 25 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02037454 @ 0x02037454, 0x2 bytes, Thumb
 * func_02037450 @ 0x02037450, 0x2 bytes, Thumb
 * func_0203743c @ 0x0203743c, 0x14 bytes, Thumb
 * func_02037438 @ 0x02037438, 0x2 bytes, Thumb
 * func_02037430 @ 0x02037430, 0x8 bytes, Thumb
 * func_0203741c @ 0x0203741c, 0x14 bytes, Thumb
 * func_02037404 @ 0x02037404, 0x18 bytes, Thumb
 * func_020373c8 @ 0x020373c8, 0x3c bytes, Thumb
 * func_0203736c @ 0x0203736c, 0x5c bytes, Thumb
 * func_0203735c @ 0x0203735c, 0x10 bytes, Thumb
 * func_0203734c @ 0x0203734c, 0x10 bytes, Thumb
 * func_02037318 @ 0x02037318, 0x32 bytes, Thumb
 * func_020372f8 @ 0x020372f8, 0x20 bytes, Thumb
 * func_020372ec @ 0x020372ec, 0xc bytes, Thumb
 * func_020372d4 @ 0x020372d4, 0x18 bytes, Thumb
 * func_020372bc @ 0x020372bc, 0x18 bytes, Thumb
 * func_020372b4 @ 0x020372b4, 0x8 bytes, Thumb
 * func_02037298 @ 0x02037298, 0x1a bytes, Thumb
 * func_02037278 @ 0x02037278, 0x1e bytes, Thumb
 * func_02037260 @ 0x02037260, 0x18 bytes, Thumb
 * func_0203723c @ 0x0203723c, 0x22 bytes, Thumb
 * func_02037238 @ 0x02037238, 0x4 bytes, Thumb
 * func_02037210 @ 0x02037210, 0x28 bytes, Thumb
 * func_020371f0 @ 0x020371f0, 0x20 bytes, Thumb
 * func_020371c8 @ 0x020371c8, 0x28 bytes, Thumb
 */

struct UnkStruct_020373c8 {
    unsigned char pad_00[6];
    unsigned char unk_06;
    unsigned char pad_07;
    unsigned int unk_08;
};

typedef struct {
    unsigned char pad_00[6];
    unsigned char unk_06;
    unsigned char unk_07;
    unsigned int unk_08;
} UnkStruct_0203736c;

typedef struct {
    unsigned int unk_00;
    unsigned short unk_04;
    unsigned short unk_06;
    unsigned int unk_08;
    unsigned int unk_0C;
    unsigned short unk_10;
    unsigned short unk_12;
    unsigned int unk_14;
} UnkStruct_02037318;

struct F0x020372f8 {
    unsigned int a;
    unsigned int b;
    unsigned int c;
    unsigned short d;
    unsigned char e;
    unsigned char unk_0F;
    unsigned char g;
};

struct UnkStruct_02037298 {
    char unk_00[0x10];
    unsigned char flag;
};

struct UnkStruct_02037260 {
    char unk_00[0x10];
    unsigned char unk_10;
};

typedef struct {
    unsigned char pad_00[0x8];
    unsigned int unk_08;
    unsigned char pad_0C[0x3];
    unsigned char unk_0F;
    unsigned char unk_10;
} UnkStruct_0203723c;

typedef struct {
    char pad_00[8];
    int index;
    unsigned short unk_0C;
} UnkStruct_02037210;

typedef struct {
    unsigned char pad_00[0xc];
    unsigned short val;
} UnkStruct_020371f0;

struct UnkStruct_020371c8 {
    unsigned char pad_00[8];
    unsigned int unk_08;
};

extern unsigned int func_0209dee8(void);
extern void func_0209df94(unsigned short *);
extern void func_0209def4(void *object);
extern int func_0209dedc(void);
extern void func_020edb3c(void *self);
extern unsigned char data_020da2c4[];
extern void func_0203710c(struct UnkStruct_02037298 *obj);
extern void func_02037190(void *);
extern unsigned short data_020c9f28[];
void func_020356c4(int, int, int, int);
extern void func_02035638(unsigned short value);
extern unsigned char *func_02036648(void);

void func_02037318(UnkStruct_02037318 *p);
void func_02037278(void *param);
void func_020371f0(UnkStruct_020371f0 *s);
void func_020371c8(struct UnkStruct_020371c8 *p);

void func_02037454(void *receiver) {}

void func_02037450(void *receiver) {}

void func_0203743c(void *arg0)
{
    void *r4;
    r4 = arg0;
    func_02037318((UnkStruct_02037318 *) r4);
    func_02037318((UnkStruct_02037318 *) r4);
}

void func_02037438(void *receiver) {}

void func_02037430(void *argument0)
{
    func_02037318((UnkStruct_02037318 *) ((void *) argument0));
}

void func_0203741c(void *arg0)
{
    void *r4;
    r4 = arg0;
    func_02037318((UnkStruct_02037318 *) r4);
    func_02037318((UnkStruct_02037318 *) r4);
}

int func_02037404(unsigned short *a, unsigned short *b, unsigned short *c)
{
    if (a[2] == b[0] && a[3] == c[0]) {
        return 1;
    }
    return 0;
}

int func_020373c8(struct UnkStruct_020373c8 *a, unsigned int b, unsigned int c, unsigned int d, unsigned int e)
{
    unsigned int x = a->unk_08 + (unsigned char) a->unk_06 * 60;
    unsigned int start = c + b * 60;
    unsigned int end = e + d * 60;
    int result = 0;
    if (start <= end) {
        if (x >= start && x < end) {
            result = 1;
        }
    } else {
        if (x >= start || x < end) {
            result = 1;
        }
    }
    return result;
}

unsigned int func_0203736c(UnkStruct_0203736c *p, unsigned int h2, unsigned int m2, unsigned int s2, unsigned int h3,
                           unsigned int m3, unsigned int s3)
{
    unsigned int t1 = p->unk_08 + (p->unk_07 * 3600 + p->unk_06 * 60);
    unsigned int t2 = s2 + (h2 * 3600 + m2 * 60);
    unsigned int t3 = s3 + (h3 * 3600 + m3 * 60);
    unsigned int r = 0;
    if (t2 <= t3) {
        if (t1 >= t2 && t1 < t3) {
            r = 1;
        }
    } else {
        if (t1 >= t2 || t1 < t3) {
            r = 1;
        }
    }
    return r;
}

int func_0203735c(void *arg0)
{
    unsigned char r1;
    unsigned char r0;

    r1 = *(unsigned char *) ((char *) arg0 + 0x13);
    r0 = *(unsigned char *) ((char *) arg0 + 7);
    if (r1 != r0) {
        return 1;
    }
    return 0;
}

int func_0203734c(void *self)
{
    if (*(int *) ((char *) self + 0xc) != *(int *) self) {
        return 1;
    }
    return 0;
}

void func_02037318(UnkStruct_02037318 *p)
{
    unsigned int tmp;
    p->unk_0C = p->unk_00;
    p->unk_10 = p->unk_04;
    p->unk_12 = p->unk_06;
    tmp = p->unk_08;
    p->unk_14 = tmp;
    p->unk_00 = func_0209dee8();
    func_0209df94(&p->unk_04);
    func_0209def4(&p->unk_06);
    p->unk_08 = func_0209dedc();
}

void func_020372f8(struct F0x020372f8 *s, unsigned int v)
{
    s->a = (unsigned int) ((char *) data_020da2c4);
    s->b = v;
    s->c = 0x18;
    s->d = 0xffff;
    s->e = 0;
    s->unk_0F = 0;
    s->g = 0;
}

void func_020372ec(int **p)
{
    *p = ((int *) data_020da2c4);
}

void *func_020372d4(void *self)
{
    *(unsigned int *) self = (unsigned int) data_020da2c4;
    func_020edb3c(self);
    return self;
}

void func_020372bc(unsigned short *arg0)
{
    unsigned int val;
    unsigned char val2;

    val = 0xffff;
    *(unsigned short *) (arg0 + 6) = (unsigned short) val;
    *(unsigned int *) (arg0 + 4) = 0x18;
    val2 = 0;
    *(unsigned char *) ((unsigned char *) arg0 + 14) = val2;
    *(unsigned char *) ((unsigned char *) arg0 + 15) = val2;
    *(unsigned char *) ((unsigned char *) arg0 + 16) = val2;
    return;
}

void func_020372b4(void *argument0)
{
    func_02037278((void *) argument0);
}

void func_02037298(struct UnkStruct_02037298 *obj)
{
    if (obj->flag != 0) {
        func_020371c8((struct UnkStruct_020371c8 *) obj);
        func_0203710c(obj);
    }
}

void func_02037278(void *param)
{
    void *r4 = param;
    func_020371f0((UnkStruct_020371f0 *) r4);
    *(unsigned int *) ((char *) r4 + 8) = 0x18;
    func_02037190(r4);
    *(unsigned char *) ((char *) r4 + 0xf) = 0;
    *(unsigned char *) ((char *) r4 + 0x10) = 0;
}

void func_02037260(struct UnkStruct_02037260 *arg)
{
    arg->unk_10 = 1;
    func_020371c8((struct UnkStruct_020371c8 *) arg);
    func_0203710c((struct UnkStruct_02037298 *) arg);
}

int func_0203723c(UnkStruct_0203723c *self)
{
    if (self->unk_0F == 0) {
        func_020371f0((UnkStruct_020371f0 *) self);
        self->unk_08 = 24;
        func_02037190((void *) self);
    }
    self->unk_10 = 0;
    return 0;
}

void func_02037238(unsigned char *p0, int p1)
{
    p0[15] = p1;
}

void func_02037210(UnkStruct_02037210 *s)
{
    unsigned short val = data_020c9f28[s->index];
    func_020356c4(0x24, val, 0x7f, 0);
    s->unk_0C = val;
}

void func_020371f0(UnkStruct_020371f0 *s)
{
    if (s->val == 0xffff) {
        return;
    }
    func_02035638(s->val);
    s->val = 0xffff;
}

void func_020371c8(struct UnkStruct_020371c8 *p)
{
    unsigned char b;
    b = func_02036648()[7];
    if (b != p->unk_08) {
        func_020371f0((UnkStruct_020371f0 *) p);
        p->unk_08 = b;
        func_02037210((UnkStruct_02037210 *) p);
    }
}
