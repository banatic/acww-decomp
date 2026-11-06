/* camera_control: 30 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0203aeec @ 0x0203aeec, 0x1c bytes, Thumb
 * func_0203aed8 @ 0x0203aed8, 0x14 bytes, Thumb
 * func_0203aec4 @ 0x0203aec4, 0x14 bytes, Thumb
 * func_0203aeac @ 0x0203aeac, 0x18 bytes, Thumb
 * func_0203ae98 @ 0x0203ae98, 0x14 bytes, Thumb
 * func_0203ae84 @ 0x0203ae84, 0x14 bytes, Thumb
 * func_0203ae28 @ 0x0203ae28, 0x5c bytes, Thumb
 * func_0203adc4 @ 0x0203adc4, 0x64 bytes, Thumb
 * func_0203adb0 @ 0x0203adb0, 0x14 bytes, Thumb
 * func_0203ad88 @ 0x0203ad88, 0x28 bytes, Thumb
 * func_0203ad68 @ 0x0203ad68, 0x20 bytes, Thumb
 * func_0203ad58 @ 0x0203ad58, 0x10 bytes, Thumb
 * func_0203ad30 @ 0x0203ad30, 0x28 bytes, Thumb
 * func_0203acd8 @ 0x0203acd8, 0x58 bytes, Thumb
 * func_0203ac78 @ 0x0203ac78, 0x60 bytes, Thumb
 * func_0203ac5c @ 0x0203ac5c, 0x1c bytes, Thumb
 * func_0203ac44 @ 0x0203ac44, 0x18 bytes, Thumb
 * func_0203ac2c @ 0x0203ac2c, 0x18 bytes, Thumb
 * func_0203ac18 @ 0x0203ac18, 0x14 bytes, Thumb
 * func_0203ac04 @ 0x0203ac04, 0x14 bytes, Thumb
 * func_0203ab78 @ 0x0203ab78, 0x8c bytes, Thumb
 * func_0203ab64 @ 0x0203ab64, 0x14 bytes, Thumb
 * func_0203ab50 @ 0x0203ab50, 0x14 bytes, Thumb
 * func_0203ab34 @ 0x0203ab34, 0x1c bytes, Thumb
 * func_0203ab20 @ 0x0203ab20, 0x14 bytes, Thumb
 * func_0203aad0 @ 0x0203aad0, 0x50 bytes, Thumb
 * func_0203aa48 @ 0x0203aa48, 0x88 bytes, Thumb
 * func_0203aa24 @ 0x0203aa24, 0x22 bytes, Thumb
 * func_0203a9f4 @ 0x0203a9f4, 0x30 bytes, Thumb
 * func_0203a9cc @ 0x0203a9cc, 0x28 bytes, Thumb
 */

struct UnkStruct_0203aeec {
    char pad_00[0x21c];
    unsigned int unk_21C;
};

typedef struct UnkStruct_0203aeac {
    char pad_00[0x1fc];
    int unk_1FC;
} UnkStruct_0203aeac;

typedef struct {
    unsigned char pad_00[0xb8];
    int unk_B8;
    int unk_BC;
    unsigned char pad_C0[8];
    int unk_C8;
    unsigned char pad_CC[0x100];
    int unk_1CC;
    int unk_1D0;
    int unk_1D4;
    unsigned char pad_1D8[0x1f6 - 0x1d8];
    unsigned char unk_1F6;
    unsigned char pad_1F7;
    int unk_1F8;
} UnkStruct_0203ae28;

typedef struct UnkStruct_0203adc4 {
    int pad_00;
    int pad1;
    int unk_08;
} UnkStruct_0203adc4;

typedef struct Global {
    unsigned char pad_00[0x118];
    int unk_118;
    unsigned char pad1[0xd8];
    unsigned char unk_1F4;
    unsigned char pad_1F5[3];
    int unk_1F8;
    int unk_1FC;
} Global;

typedef struct {
    char pad_00[0xc8];
    int unk_C8;
} Struct0203ad88;

typedef struct {
    char pad_00[0xc8];
    int unk_C8;
} UnkStruct_0203ad68;

typedef struct UnkStruct_0203ad30 {
    char pad_00[0xc8];
    int unk_C8;
} UnkStruct_0203ad30;

typedef struct {
    short unk_00;
    short unk_02;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    int unk_14;
    int unk_18;
    int unk_1C;
} SubA;

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
} SubB;

typedef struct {
    short a;
    short b;
    int c[7];
} B32;

typedef struct {
    int x, y, z;
} C12;

typedef struct {
    unsigned char pad_00[0xfc];
    B32 sub;
    unsigned char pad_11C[0x4c];
    C12 other;
} UnkStruct_0203ac78;

typedef struct {
    char pad_00[0x1f4];
    unsigned char enabled;
} CARDiWork;

struct UnkStruct_0203ab78 {
    short unk_00;
    short s1;
    int i0;
    int i1;
    int i2;
    int i3;
    int i4;
    int i5;
    int i6;
};

struct UnkStruct_0203ab78_2 {
    char pad_00[0xfc];
    struct UnkStruct_0203ab78 unk_FC;
    char pad_11C[0x2c];
    struct UnkStruct_0203ab78 unk_148;
};

struct UnkStruct_0203ab78_3 {
    char data[16];
};

typedef struct {
    unsigned char pad_00[0x1ec];
    int unk_1EC;
    int unk_1F0;
} UnkStruct_0203aad0;

typedef struct {
    int x, y, z;
} Vec3;

typedef struct {
    int m[12];
} Mtx43;

extern int func_0203c0ac(struct UnkStruct_0203aeec *p, int n);
extern unsigned char data_021c67a4[];
extern int func_0203c4e4(Struct0203ad88 *ptr);
extern SubA data_021c6800;
extern SubB data_021c67f4;
extern void func_0203b994(void *);
extern void func_0203b868(int arg);
extern void func_ov068_0226dc64(int, int);
extern void func_0203c210(struct UnkStruct_0203ab78_2 *p, struct UnkStruct_0203ab78 *f, int arg);
extern void func_01ffcbb0(struct UnkStruct_0203ab78_3 *local, struct UnkStruct_0203ab78_2 *p);
extern int func_0203c57c(struct UnkStruct_0203ab78_2 *p);
extern int func_0203c568(struct UnkStruct_0203ab78_2 *p);
extern int func_0203c548(struct UnkStruct_0203ab78_2 *p);
extern void func_0203bd84(struct UnkStruct_0203ab78_2 *p, struct UnkStruct_0203ab78_3 *local, int a, int b, int c);
extern void func_0200467c(int command);
extern Mtx43 data_021fbe48;
extern void MTX_MultVec43(Vec3 *v, Mtx43 *m, Vec3 *dst);
extern int func_0203c53c(void *p);
extern int FX_Div(int a, int b);
extern void func_020eabc8(Vec3 *v, int s);
extern int func_0203f844(void *buffer, int arg2);
extern void func_020ee62c(void *);
extern void func_020edf54(void *);
extern unsigned char data_020da13c[];
extern unsigned char data_020da87c[];
extern unsigned char data_020e58cc[];

void func_0203aeec(unsigned int value)
{
    (*(struct UnkStruct_0203aeec **) data_021c67a4)->unk_21C = value;
    func_0203c0ac((*(struct UnkStruct_0203aeec **) data_021c67a4), 0x11);
}

void func_0203aed8(void)
{
    unsigned int *r0;
    unsigned int r1;
    unsigned int r3;

    r0 = (unsigned int *) data_021c67a4;
    r0 = (unsigned int *) *r0;
    r1 = 0x13;
    r3 = (unsigned int) (unsigned int (*)(void *, int)) func_0203c0ac;
    ((void (*)(unsigned int, unsigned int)) r3)((unsigned int) r0, r1);
}

void func_0203aec4(void)
{
    unsigned int *ptr;
    unsigned int value;

    ptr = (unsigned int *) data_021c67a4;
    value = *ptr;
    func_0203c0ac((struct UnkStruct_0203aeec *) value, 3);
}

int func_0203aeac(void)
{
    return func_0203c0ac((struct UnkStruct_0203aeec *) ((*(UnkStruct_0203aeac **) data_021c67a4)),
                         (*(UnkStruct_0203aeac **) data_021c67a4)->unk_1FC);
}

void func_0203ae98(void)
{
    unsigned int *ptr;
    unsigned int value;

    ptr = (unsigned int *) data_021c67a4;
    value = *ptr;
    func_0203c0ac((struct UnkStruct_0203aeec *) value, 4);
}

void func_0203ae84(void)
{
    func_0203c0ac((struct UnkStruct_0203aeec *) ((*(unsigned int *) data_021c67a4)), 5);
}

int func_0203ae28(int *v)
{
    int *d;
    if ((*(UnkStruct_0203ae28 **) data_021c67a4)->unk_1F8 == 0x13) {
        (*(UnkStruct_0203ae28 **) data_021c67a4)->unk_C8 = 0;
        (*(UnkStruct_0203ae28 **) data_021c67a4)->unk_B8 = 0;
        (*(UnkStruct_0203ae28 **) data_021c67a4)->unk_BC = 0x15000;
        return 1;
    }
    d = &(*(UnkStruct_0203ae28 **) data_021c67a4)->unk_1CC;
    d[0] = v[0];
    d[1] = v[1];
    d[2] = v[2];
    (*(UnkStruct_0203ae28 **) data_021c67a4)->unk_C8 = 0;
    (*(UnkStruct_0203ae28 **) data_021c67a4)->unk_1F6 = 3;
    return 1;
}

int func_0203adc4(UnkStruct_0203adc4 *a0, int unused, int b)
{
    Global *g;
    int mode;

    g = (*(Global **) data_021c67a4);
    if (g != 0) {
        mode = g->unk_1F8;
        if (mode == 2 || mode == 4) {
            goto check;
        }
        if (mode != 1) {
            goto bottom;
        }
        if (g->unk_1FC == 2) {
            goto check;
        }
    bottom:
        if (g->unk_1F4 != 0) {
            goto check;
        }
        return 0;
    check:
        if (a0->unk_08 - (b >> 1) > g->unk_118 - 0x2000) {
            return 1;
        }
        return 0;
    }

    return 0;
}

unsigned int func_0203adb0(void)
{
    unsigned int *ptr;
    unsigned int offset;
    unsigned int result;

    ptr = (*(unsigned int **) data_021c67a4);
    offset = 0x1e8;
    result = *(unsigned int *) ((unsigned char *) ptr + offset);
    return result;
}

int func_0203ad88(void)
{
    int ret;
    ret = func_0203c4e4((*(Struct0203ad88 **) data_021c67a4));
    if ((*(Struct0203ad88 **) data_021c67a4)->unk_C8 > ret) {
        return 0;
    } else {
        return 1;
    }
}

void func_0203ad68(void)
{
    (*(UnkStruct_0203ad68 **) data_021c67a4)->unk_C8 =
        func_0203c4e4((Struct0203ad88 *) ((*(UnkStruct_0203ad68 **) data_021c67a4)));
}

void func_0203ad58(void)
{
    unsigned int *ptr;
    unsigned int *addr;

    ptr = (*(unsigned int **) data_021c67a4);
    addr = (unsigned int *) ((unsigned char *) ptr + 0xc8);
    *addr = 0;
}

unsigned char func_0203ad30(void)
{
    int a = func_0203c4e4((Struct0203ad88 *) ((*(UnkStruct_0203ad30 **) data_021c67a4)));
    int b = (*(UnkStruct_0203ad30 **) data_021c67a4)->unk_C8;
    return (unsigned char) ((a - b) >> 12);
}

void func_0203acd8(void)
{
    char *base = (*(char **) data_021c67a4);
    SubA *p = (SubA *) (base + 0xfc);
    SubB *q;
    data_021c6800.unk_00 = *(short *) (base + 0xfc);
    data_021c6800.unk_02 = p->unk_02;
    data_021c6800.unk_04 = p->unk_04;
    data_021c6800.unk_08 = p->unk_08;
    data_021c6800.unk_0C = p->unk_0C;
    data_021c6800.unk_10 = p->unk_10;
    data_021c6800.unk_14 = p->unk_14;
    data_021c6800.unk_18 = p->unk_18;
    data_021c6800.unk_1C = p->unk_1C;
    q = (SubB *) (base + 0x168);
    data_021c67f4.unk_00 = q->unk_00;
    data_021c67f4.unk_04 = q->unk_04;
    data_021c67f4.unk_08 = q->unk_08;
}

void func_0203ac78(void)
{
    UnkStruct_0203ac78 *p = (*(UnkStruct_0203ac78 **) data_021c67a4);
    B32 *d = &p->sub;
    d->a = (*(B32 *) &data_021c6800).a;
    d->b = (*(B32 *) &data_021c6800).b;
    d->c[0] = (*(B32 *) &data_021c6800).c[0];
    d->c[1] = (*(B32 *) &data_021c6800).c[1];
    d->c[2] = (*(B32 *) &data_021c6800).c[2];
    d->c[3] = (*(B32 *) &data_021c6800).c[3];
    d->c[4] = (*(B32 *) &data_021c6800).c[4];
    d->c[5] = (*(B32 *) &data_021c6800).c[5];
    d->c[6] = (*(B32 *) &data_021c6800).c[6];
    {
        C12 *o = &(*(UnkStruct_0203ac78 **) data_021c67a4)->other;
        o->x = (*(C12 *) &data_021c67f4).x;
        o->y = (*(C12 *) &data_021c67f4).y;
        o->z = (*(C12 *) &data_021c67f4).z;
    }
}

int func_0203ac5c(void)
{
    return (*(CARDiWork **) data_021c67a4)->enabled != 0;
}

int func_0203ac44(void)
{
    func_0203b994(*(void **) ((int *) data_021c67a4));
    return 1;
}

int func_0203ac2c(void)
{
    func_0203b868((*(int *) data_021c67a4));
    return 1;
}

void func_0203ac18(void)
{
    func_ov068_0226dc64((*(int *) data_021c67a4), 3);
}

void func_0203ac04(void)
{
    (*(unsigned char **) data_021c67a4)[0x1f5] = 1;
}

void func_0203ab78(int arg)
{
    struct UnkStruct_0203ab78 *src;
    struct UnkStruct_0203ab78 *dst;
    struct UnkStruct_0203ab78_3 local;
    int v1, v2, v3;

    func_0203c210((*(struct UnkStruct_0203ab78_2 **) data_021c67a4),
                  &(*(struct UnkStruct_0203ab78_2 **) data_021c67a4)->unk_FC, arg);

    src = &(*(struct UnkStruct_0203ab78_2 **) data_021c67a4)->unk_FC;
    dst = &(*(struct UnkStruct_0203ab78_2 **) data_021c67a4)->unk_148;
    dst->unk_00 = src->unk_00;
    dst->s1 = src->s1;
    dst->i0 = src->i0;
    dst->i1 = src->i1;
    dst->i2 = src->i2;
    dst->i3 = src->i3;
    dst->i4 = src->i4;
    dst->i5 = src->i5;
    dst->i6 = src->i6;

    func_01ffcbb0(&local, (*(struct UnkStruct_0203ab78_2 **) data_021c67a4));

    v1 = func_0203c57c((*(struct UnkStruct_0203ab78_2 **) data_021c67a4));
    v2 = func_0203c568((*(struct UnkStruct_0203ab78_2 **) data_021c67a4));
    v3 = func_0203c548((*(struct UnkStruct_0203ab78_2 **) data_021c67a4));

    func_0203bd84((*(struct UnkStruct_0203ab78_2 **) data_021c67a4), &local, v1, v2, v3);
}

void func_0203ab64(void)
{
    unsigned char *r1;
    unsigned int r0;

    r1 = (*(unsigned char **) data_021c67a4);
    r0 = 0x1f7;
    r1[r0] = 1;
}

void func_0203ab50(void)
{
    unsigned char *ptr;
    unsigned char value;

    value = 0;
    ptr = (*(unsigned char **) data_021c67a4);
    ptr[0x1f7] = value;
}

void func_0203ab34(unsigned char *param0, int param1)
{
    if (param0[0x1f7] == 0) {
        func_0200467c(param1);
    }
}

unsigned int func_0203ab20(void)
{
    if ((*(unsigned int *) data_021c67a4)) {
        return (*(unsigned int *) data_021c67a4) + 0x50;
    }
    return 0;
}

int func_0203aad0(int a, int b)
{
    UnkStruct_0203aad0 *p = (*(UnkStruct_0203aad0 **) data_021c67a4);
    if (p != 0) {
        if (p->unk_1EC != b || p->unk_1F0 != a) {
            func_0203ad58();
            (*(UnkStruct_0203aad0 **) data_021c67a4)->unk_1F0 = a;
            (*(UnkStruct_0203aad0 **) data_021c67a4)->unk_1EC = b;
            return 1;
        }
        return 0;
    }
    return 0;
}

int func_0203aa48(int *outX, int *outY, Vec3 *v)
{
    Vec3 t;
    Mtx43 m;
    int k;
    if ((*(void **) data_021c67a4) != 0) {
        m = *(Mtx43 *) func_0203ab20();
        data_021fbe48 = m;
        MTX_MultVec43(v, &data_021fbe48, &t);
        k = -FX_Div(0x60000, func_0203c53c((*(void **) data_021c67a4)));
        k = FX_Div(k, t.z);
        func_020eabc8(&t, k);
        *outX = t.x >> 12;
        *outY = -(t.y >> 12);
        return 1;
    }
    return 0;
}

void func_0203aa24(int arg0, int arg1, int arg2)
{
    char buffer[12];

    func_0203f844(buffer, arg2);
    func_0203aa48((int *) arg0, (int *) arg1, (Vec3 *) buffer);
}

void *func_0203a9f4(volatile unsigned int *self)
{
    *self = (unsigned int) data_020da87c;
    *self = (unsigned int) data_020e58cc;
    *self = (unsigned int) data_020da13c;
    func_020ee62c((void *) self);
    func_020edf54((void *) self);
    return (void *) self;
}

void *func_0203a9cc(void *obj)
{
    volatile unsigned int *p;
    p = (volatile unsigned int *) obj;
    *p = (unsigned int) data_020da87c;
    *p = (unsigned int) data_020e58cc;
    *p = (unsigned int) data_020da13c;
    func_020ee62c(obj);
    return obj;
}
