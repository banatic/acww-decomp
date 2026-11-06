/* field_collision_5: 32 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02034850 @ 0x02034850, 0x8 bytes, Thumb
 * func_02034824 @ 0x02034824, 0x2c bytes, Thumb
 * func_02034820 @ 0x02034820, 0x2 bytes, Thumb
 * func_02034804 @ 0x02034804, 0x1c bytes, Thumb
 * func_02034790 @ 0x02034790, 0x74 bytes, Thumb
 * func_02034780 @ 0x02034780, 0xe bytes, Thumb
 * func_02034714 @ 0x02034714, 0x6c bytes, Thumb
 * func_020346fc @ 0x020346fc, 0x16 bytes, Thumb
 * func_020346c4 @ 0x020346c4, 0x38 bytes, Thumb
 * func_020346a4 @ 0x020346a4, 0x20 bytes, Thumb
 * func_02034664 @ 0x02034664, 0x3e bytes, Thumb
 * func_02034600 @ 0x02034600, 0x64 bytes, Thumb
 * func_020345e0 @ 0x020345e0, 0x20 bytes, Thumb
 * func_02034448 @ 0x02034448, 0x198 bytes, Thumb
 * func_020343f4 @ 0x020343f4, 0x54 bytes, Thumb
 * func_020343f0 @ 0x020343f0, 0x2 bytes, Thumb
 * func_02034310 @ 0x02034310, 0xe0 bytes, Thumb
 * func_020342c0 @ 0x020342c0, 0x50 bytes, Thumb
 * func_020342ac @ 0x020342ac, 0x12 bytes, Thumb
 * func_020342a4 @ 0x020342a4, 0x8 bytes, Thumb
 * func_0203429c @ 0x0203429c, 0x8 bytes, Thumb
 * func_02034298 @ 0x02034298, 0x2 bytes, Thumb
 * func_02034294 @ 0x02034294, 0x2 bytes, Thumb
 * func_0203428c @ 0x0203428c, 0x6 bytes, Thumb
 * func_02034280 @ 0x02034280, 0xa bytes, Thumb
 * func_02034270 @ 0x02034270, 0x10 bytes, Thumb
 * func_02034240 @ 0x02034240, 0x30 bytes, Thumb
 * func_0203423c @ 0x0203423c, 0x2 bytes, Thumb
 * func_020341c8 @ 0x020341c8, 0x74 bytes, Thumb
 * func_0203419c @ 0x0203419c, 0x2c bytes, Thumb
 * func_02034184 @ 0x02034184, 0x18 bytes, Thumb
 * func_02034150 @ 0x02034150, 0x34 bytes, Thumb
 */

#define B(t, i) (((int) (i) < 0x7c) ? (int) t[(i) * 30] : 0)
#define H(i) (((int) (i) < 0x7c) ? (int) (*(short *) &data_020c9098[(i) * 30]) << 8 : 0)

struct UnkStruct_02034714 {
    int arr[6][6][2];
    int unk_120;
    int unk_124;
    int unk_128;
    int unk_12C;
    char unk_130;
    short unk_132;
    short unk_134;
};

typedef struct UnkStruct_02034600 {
    unsigned char mask;
    unsigned char kind[4];
    signed char arr5[4];
    signed char arr9[4];
} UnkStruct_02034600;

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    unsigned char unk_10;
    unsigned char unk_11;
    unsigned char unk_12;
    unsigned char unk_13;
    unsigned char unk_14;
} UnkStruct_02034448;

typedef struct {
    char pad_00[0x498];
    int a;
    int b;
    int c;
    int d;
} UnkStruct_020343f4;

typedef struct {
    unsigned char pad_00[0x498];
    int unk_498;
    int unk_49C;
    int unk_4A0;
    int unk_4A4;
} UnkStruct_02034310;

typedef struct {
    char pad_00[0x498];
    int minX;
    int maxX;
    int minY;
    int maxY;
} UnkStruct_020342c0;

typedef struct {
    int x, y, z;
} Vec3;

typedef struct {
    unsigned char pad_00[0x10];
    Vec3 pos;
    int unk_1C;
    int unk_20;
    unsigned char pad_24[0x14];
    int unk_38;
} UnkStruct_020341c8;

typedef struct {
    char pad_00[0x34];
    int unk_34;
    char pad_38[0x04];
    int unk_3C;
} UnkStruct_0203419c;

typedef struct {
    char pad_00[0x24];
    int unk_24;
    int unk_28;
    int unk_2C;
} UnkStruct_02034150;

extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern void func_02031608(void *);
extern void func_020326bc(void *);
extern void func_02032438(void *);
extern void *func_02032f78(void *);
extern int func_02033c2c(void *);
extern void *func_02033878(void *);
extern int data_020c9050[4];
extern unsigned char data_020c9088[];
extern unsigned char data_020c9089[];
extern unsigned char data_020c908a[];
extern unsigned char data_020c908b[];
extern unsigned char data_020c908c[];
extern unsigned char data_020c908d[];
extern unsigned char data_020c908e[];
extern unsigned char data_020c908f[];
extern unsigned char data_020c9098[];
extern int func_01ffcb2c(int a, int b);
extern void func_02033cec(int param, void *, int, int);
extern int func_02031078(int a0, int a1, int *o1, int *o2, int *o3);
extern long long func_020ea940(Vec3 *a, Vec3 *b);
extern int FX_MulFunc(int a, int b);
extern int FX_Div(int, int);
extern void func_020ea6e0(void *ptr, int value);

void func_02034820(void *object);
void func_02034714(struct UnkStruct_02034714 *d);
int func_020346a4(unsigned char *p);
void func_02034448(UnkStruct_02034448 *self, int a, int b, int flag);
void func_020343f0(void *object);

void func_02034850(int *p0)
{
    p0[0] = 0;
    p0[1] = 0;
}

int func_02034824(int param)
{
    __cxa_vec_ctor((void *) (param), 0x24, 8, (void (*)(void *))(void (*)(void *)) func_02034850,
                   (void (*)(void *)) func_02034820);
    func_02034714((struct UnkStruct_02034714 *) param);
    return param;
}

void func_02034820(void *object) {}

void *func_02034804(void *ptr)
{
    __cxa_vec_cleanup((void *) (ptr), 0x24, 8, (void (*)(void *)) func_02034820);
    return ptr;
}

void *func_02034790(void *arg)
{
    __cxa_vec_cleanup((void *) ((char *) arg + 0x1a94), 0x31, 0x18, (void (*)(void *)) func_02031608);
    func_020326bc((char *) arg + 0x1a91);
    func_02032438((char *) arg + 0x1a90);
    func_02032f78((char *) arg + 0x184c);
    func_02033c2c((char *) arg + 0xe48);
    func_02033878((char *) arg + 0x9c4);
    __cxa_vec_cleanup((void *) ((char *) arg + 4), 8, 0x138, (((void (*)(void *)) func_02034804)));
    return arg;
}

int func_02034780(void *arg0)
{
    if (*(unsigned int *) ((char *) arg0 + 0x28) == 3) {
        return 0;
    }
    return 1;
}

void func_02034714(struct UnkStruct_02034714 *d)
{
    int i;
    int j;
    d->unk_124 = 0;
    d->unk_128 = 0;
    d->unk_120 = 0;
    d->unk_132 = 0;
    d->unk_134 = 0;
    d->unk_12C = -1;
    d->unk_130 = 0;
    for (i = 0; i < 6; i++) {
        for (j = 0; j < 6; j++) {
            d->arr[i][j][0] = 0;
            d->arr[i][j][1] = 0;
        }
    }
}

void func_020346fc(unsigned char *p)
{
    unsigned char *q;
    unsigned char fill = 0xff;
    *p = 0;
    q = p + 1;
    fill = 0xff;
    p = p + 5;
    while (q < p) {
        *q++ = fill;
    }
}

int func_020346c4(unsigned char *base, int a, int b)
{
    int idx;
    unsigned char *p;

    idx = func_020346a4(base);
    if (idx != -1) {
        *base |= (1 << idx);
        p = base + idx;
        p[5] = a;
        p[9] = b;
        p[1] = 0;
        return 1;
    } else {
        return 0;
    }
}

int func_020346a4(unsigned char *p)
{
    unsigned int i;
    for (i = 0; i < 4; i++) {
        if (((*p >> i) & 1) == 0) {
            return i;
        }
    }
    return -1;
}

void func_02034664(unsigned char *arr)
{
    int i = 0;
    unsigned char *p = arr + 1;
    while (p < arr + 5) {
        if (((arr[0] >> i) & 1) && (*p < 3)) {
            (*p)++;
        } else {
            *p = 0xff;
            arr[0] &= ~(1 << i);
        }
        i++;
        p++;
    }
}

int func_02034600(UnkStruct_02034600 *s, int arg1, int arg2)
{
    int i = 0;
    signed char *a = s->arr5;
    signed char *b = s->arr9;
    unsigned char *c = s->kind;

    for (; c < (unsigned char *) s->arr5; a++, b++, i++, c++) {
        if ((s->mask >> i) & 1) {
            unsigned char v = *c;
            if (v < 3) {
                int k = 0, m = 0;
                if (a[k] == arg1 && b[m] == arg2) {
                    return data_020c9050[v];
                }
            }
        }
    }
    return 0;
}

int func_020345e0(int a, int *b, int c)
{
    int d;
    int e;
    d = b[0] >> 13;
    e = b[2] >> 13;
    func_02034448((UnkStruct_02034448 *) a, d, e, c);
    return a;
}

void func_02034448(UnkStruct_02034448 *self, int a, int b, int flag)
{
    int v;

    if (flag == 0) {
        self->unk_14 = (unsigned char) func_01ffcb2c(a, b);
        v = self->unk_14;
        self->unk_10 = (unsigned char) B(data_020c9088, v);
        self->unk_00 = H(self->unk_10);
        self->unk_11 = (unsigned char) B(data_020c9089, v);
        self->unk_04 = H(self->unk_11);
        self->unk_12 = (unsigned char) B(data_020c908a, v);
        self->unk_08 = H(self->unk_12);
        self->unk_13 = (unsigned char) B(data_020c908b, v);
        self->unk_0C = H(self->unk_13);
    } else {
        self->unk_14 = (unsigned char) func_01ffcb2c(a, b);
        v = self->unk_14;
        self->unk_10 = (unsigned char) B(data_020c908c, v);
        self->unk_00 = H(self->unk_10);
        self->unk_11 = (unsigned char) B(data_020c908d, v);
        self->unk_04 = H(self->unk_11);
        self->unk_12 = (unsigned char) B(data_020c908e, v);
        self->unk_08 = H(self->unk_12);
        self->unk_13 = (unsigned char) B(data_020c908f, v);
        self->unk_0C = H(self->unk_13);
    }
}

void *func_020343f4(void *param)
{
    UnkStruct_020343f4 *obj = (UnkStruct_020343f4 *) param;
    __cxa_vec_ctor((void *) (param), 0x31, 0x18, (void (*)(void *)) func_020343f0, (void (*)(void *)) func_02031608);
    obj->d = 0;
    obj->c = obj->d;
    obj->b = obj->c;
    obj->a = obj->b;
    return param;
}

void func_020343f0(void *object) {}

void func_02034310(UnkStruct_02034310 *self, int x0, int x1, int y0, int y1, int value)
{
    int width = x1 - x0 + 1;
    int height = y1 - y0 + 1;
    int row, col;

    if (width <= 7 && height <= 7) {
        self->unk_498 = x0;
        self->unk_49C = x1;
        self->unk_4A0 = y0;
        self->unk_4A4 = y1;
        row = self->unk_4A0;
        while (row <= self->unk_4A4) {
            col = self->unk_498;
            while (col <= self->unk_49C) {
                func_02034448(
                    (UnkStruct_02034448 *) ((char *) self + (row - self->unk_4A0) * 0xa8 + (col - self->unk_498) * 0x18), col,
                    row, value);
                col++;
            }
            row++;
        }
    } else {
        self->unk_498 = x0;
        self->unk_49C = x0 + 6;
        self->unk_4A0 = y0;
        self->unk_4A4 = y0 + 6;
        row = self->unk_4A0;
        while (row <= self->unk_4A4) {
            col = self->unk_498;
            while (col <= self->unk_49C) {
                func_02034448(
                    (UnkStruct_02034448 *) ((char *) self + (row - self->unk_4A0) * 0xa8 + (col - self->unk_498) * 0x18), col,
                    row, value);
                col++;
            }
            row++;
        }
    }
}

void *func_020342c0(UnkStruct_020342c0 *self, int x, int y)
{
    if (x >= self->minX && x <= self->maxX && y >= self->minY && y <= self->maxY) {
        return (void *) ((char *) self + 168 * (y - self->minY) + 24 * (x - self->minX));
    }
    return 0;
}

int func_020342ac(int *ptr, int value)
{
    if (value >= 0 && value < 8) {
        *ptr = value;
        return 1;
    }
    return 0;
}

void func_020342a4(char *p)
{
    p[0] = 0;
    *(int *) (p + 4) = 0;
}

void func_0203429c(char *p)
{
    p[0] = 0;
    *(int *) (p + 4) = 0;
}

void func_02034298(void *object) {}

void func_02034294(void *receiver) {}

void func_0203428c(char *p, int a, int b)
{
    p[0] = (char) a;
    *(int *) (p + 4) = b;
}

void func_02034280(unsigned char *dst, unsigned char *src)
{
    dst[0] = src[0];
    *(int *) (dst + 4) = *(int *) (src + 4);
}

int func_02034270(int param, void *argument1, int argument2, int argument3)
{
    func_02033cec(param, (void *) argument1, (int) argument2, (int) argument3);
    return param;
}

int func_02034240(int a0, int a1, int a2, int a3, int a4)
{
    int local[3];
    local[0] = (a1 << 13) + 0x1000;
    local[1] = 0;
    local[2] = (a2 << 13) + 0x1000;
    func_02033cec(a0, (void *) local, a3, a4);
    return a0;
}

void func_0203423c(void *object) {}

int func_020341c8(UnkStruct_020341c8 *o, int flag)
{
    int a, b, c, t, pz;
    Vec3 v;
    long long d;

    if (flag == 0) {
        return o->unk_38;
    }
    if (func_02031078(o->unk_1C, o->unk_20, &a, &b, &c) != 0 && c != 2) {
        pz = o->unk_20;
        v.x = (o->unk_1C << 13) + 0x1000;
        v.y = 0;
        v.z = (pz << 13) + 0x1000;
        t = a;
        d = func_020ea940(&v, &o->pos);
        if ((long long) FX_MulFunc(t, t) >= d) {
            return o->unk_38 + b;
        }
    }
    return o->unk_38;
}

int func_0203419c(UnkStruct_0203419c *p)
{
    if (p->unk_34 == 0x16) {
        return FX_MulFunc(p->unk_3C, FX_Div(0x1e000, 0x64000));
    } else {
        return p->unk_3C;
    }
}

int func_02034184(int *r0, int r1)
{
    if (r0[12] != 0) {
        if (r1 > r0[15]) {
            return 0;
        }
        return 1;
    } else {
        return 0;
    }
}

void func_02034150(UnkStruct_02034150 *obj, int a, int b, int c)
{
    int val;
    b -= a;
    val = 0;
    obj->unk_24 = val;
    obj->unk_28 = val;
    obj->unk_2C = 0x1000;
    if (b <= 0) {
        val = 0x8000;
    }
    func_020ea6e0(&obj->unk_24, (short) (c + (short) val));
}
