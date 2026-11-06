/* camera_modes: 19 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0203b5bc @ 0x0203b5bc, 0x5c bytes, Thumb
 * func_0203b584 @ 0x0203b584, 0x38 bytes, Thumb
 * func_0203b4fc @ 0x0203b4fc, 0x88 bytes, Thumb
 * func_0203b4b4 @ 0x0203b4b4, 0x48 bytes, Thumb
 * func_0203b42c @ 0x0203b42c, 0x88 bytes, Thumb
 * func_0203b40c @ 0x0203b40c, 0x20 bytes, Thumb
 * func_0203b334 @ 0x0203b334, 0xd8 bytes, Thumb
 * func_0203b320 @ 0x0203b320, 0x14 bytes, Thumb
 * func_0203b2dc @ 0x0203b2dc, 0x44 bytes, Thumb
 * func_0203b2b8 @ 0x0203b2b8, 0x24 bytes, Thumb
 * func_0203b1d4 @ 0x0203b1d4, 0xe4 bytes, Thumb
 * func_0203b1b4 @ 0x0203b1b4, 0x20 bytes, Thumb
 * func_0203b174 @ 0x0203b174, 0x3e bytes, Thumb
 * func_0203b144 @ 0x0203b144, 0x30 bytes, Thumb
 * func_0203b130 @ 0x0203b130, 0x14 bytes, Thumb
 * func_0203b0b8 @ 0x0203b0b8, 0x78 bytes, Thumb
 * func_0203affc @ 0x0203affc, 0xbc bytes, Thumb
 * func_0203af80 @ 0x0203af80, 0x7c bytes, Thumb
 * func_0203af08 @ 0x0203af08, 0x78 bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned char pad_00[4];
    unsigned char unk_04;
} UnkStruct_0203b584;

typedef struct {
    int x, y, z;
} Vec3;

typedef struct {
    char pad_00[0x110];
    int unk_110, unk_114, unk_118;
} UnkStruct_0203b4fc;

typedef struct {
    int unk_00;
    unsigned char unk_04;
} GStruct;

typedef struct {
    char pad_00[0x110];
    int unk_110, unk_114, unk_118;
} UnkStruct_0203b42c;

struct UnkStruct_0203b1d4 {
    void *ptr;
    s16 unk_04;
    s16 unk_06;
};

typedef struct {
    s16 x;
    s16 y;
} TabEntry;

typedef struct {
    char pad_00[0x1f8];
    int unk_1F8;
} UnkStruct_0203b144;

struct UnkStruct_0203af80 {
    int a;
    int b;
    int c;
};

struct GStruct {
    char pad_00[0x1ca];
    unsigned char unk_1CA;
    char pad_1CB[1];
    int unk_1CC[3];
    char pad_1D8[0x1f8 - 0x1cc - 12];
    int unk_1F8;
};

typedef struct {
    char pad_00[0x1ca];
    unsigned char unk_1CA;
    char pad_1CB[1];
    int unk_1CC[3];
    int unk_1D8[3];
} UnkStruct_0203af08;

extern unsigned char *data_021f6948;
extern void func_ov004_02247438(unsigned int, int);
extern void func_ov003_02236564(unsigned int);
extern void func_0203caa4(void *a, int b, int c);
extern void func_0203c99c(void *a, int b);
extern void func_0203ad58(void);
extern Vec3 data_021fbee8;
extern Vec3 *func_02095794(int a);
extern void func_0203be6c(void *self);
extern void func_01ffcbb0(void *dst, void *src);
extern int func_0203c57c(void *self);
extern int func_0203c568(void *self);
extern int func_0203c548(void *self);
extern void func_0203bd84(void *self, void *c, int a, int b, int d);
extern short FX_SinCosTable_[];
extern void *func_ov003_022196e0(int);
extern void func_020eaca0(void *out, void *a, void *b);
extern int func_020ea9c8(void *in);
extern int func_0200322c(void *a, void *b);
extern int FX_MulFunc(int a, int b);
extern void func_0203bc50(void *self, Vec3 *p);
extern void func_0203ac78(void);
extern void func_0203ad68(void);
extern int func_020e89dc(void *, u32, u32);
extern int func_020e8bb0(void *, u32, u32, u32, u32);
extern void MTX_MultVec33(void *, void *, void *);
extern void func_020eabc8(void *, int);
extern void VEC_Add(void *, void *, void *);
extern UnkStruct_0203b144 *data_021c67a4;
extern int func_0203c0ac(UnkStruct_0203b144 *p, int flag);
extern void func_01ffd070(void *out, void *a, void *b);
extern void func_020eaad0(void *out, void *in, int scale);
extern int VEC_Mag(void *v);
extern int data_020da718;
extern int func_020b65c4(void);

void func_0203b5bc(unsigned int arg)
{
    char buffer[12];
    unsigned int v1, v2, v3;
    if (data_021f6948[4] == 0) {
        func_ov004_02247438(arg, 0);
    } else {
        func_ov003_02236564(arg);
    }
    func_0203be6c((void *) arg);
    func_01ffcbb0(buffer, (void *) arg);
    v1 = (unsigned int) func_0203c57c((void *) arg);
    v2 = (unsigned int) func_0203c568((void *) arg);
    v3 = (unsigned int) func_0203c548((void *) arg);
    func_0203bd84((void *) arg, (void *) buffer, v1, v2, v3);
}

int func_0203b584(void *a)
{
    if ((*(UnkStruct_0203b584 **) &data_021f6948)->unk_04 == 0) {
        func_0203caa4(a, 0x1c, 0);
    } else {
        func_0203caa4(a, 0x1b, 0);
    }
    func_0203c99c(a, 3);
    func_0203ad58();
    return 1;
}

void func_0203b4fc(UnkStruct_0203b4fc *self)
{
    volatile int A[3];
    char buf[16];
    Vec3 *p;
    int a, b, d;
    A[0] = data_021fbee8.x;
    A[1] = data_021fbee8.y;
    A[2] = data_021fbee8.z;
    p = func_02095794(4);
    if (p != 0) {
        A[0] = p->x;
        A[1] = p->y;
        A[2] = p->z;
    }
    self->unk_110 = A[0];
    self->unk_114 = A[1];
    self->unk_118 = A[2];
    func_0203be6c(self);
    func_01ffcbb0(buf, self);
    a = func_0203c57c(self);
    b = func_0203c568(self);
    d = func_0203c548(self);
    func_0203bd84(self, buf, a, b, d);
}

int func_0203b4b4(int *p)
{
    if ((*(GStruct **) &data_021f6948)->unk_04 == 0) {
        func_0203caa4((void *) p, 13, 0);
    } else {
        func_0203caa4((void *) p, 12, 0);
    }
    func_0203c99c((void *) p, 0);
    func_0203ad58();
    *((int *) ((char *) p + 0x1e4)) = 0x1000;
    return 1;
}

void func_0203b42c(UnkStruct_0203b42c *self)
{
    volatile int A[3];
    char buf[16];
    Vec3 *p;
    int a, b, d;
    A[0] = data_021fbee8.x;
    A[1] = data_021fbee8.y;
    A[2] = data_021fbee8.z;
    p = func_02095794(4);
    if (p != 0) {
        A[0] = p->x;
        A[1] = p->y;
        A[2] = p->z;
    }
    self->unk_110 = A[0];
    self->unk_114 = A[1];
    self->unk_118 = A[2];
    func_0203be6c(self);
    func_01ffcbb0(buf, self);
    a = func_0203c57c(self);
    b = func_0203c568(self);
    d = func_0203c548(self);
    func_0203bd84(self, buf, a, b, d);
}

int func_0203b40c(int a)
{
    func_0203caa4((void *) a, 0, 0);
    (func_0203c99c((void *) a, 0), func_0203ad58());
    return 1;
}

void func_0203b334(void *self)
{
    Vec3 A;
    char buf1[12];
    char buf2[16];
    Vec3 *p1, *p2;
    int v, raw, k;

    A.x = data_021fbee8.x;
    A.y = data_021fbee8.y;
    A.z = data_021fbee8.z;

    p1 = (void *) func_02095794(4);
    p2 = func_ov003_022196e0(4);

    if (p1 != 0 && p2 != 0) {
        func_020eaca0(buf1, p1, p2);
        v = func_020ea9c8(buf1);
        raw = func_0200322c(p1, p2);
        v = FX_MulFunc(v, 0xb33);

        A.x = p1->x;
        A.y = p1->y;
        A.z = p1->z;

        k = (int) ((unsigned short) raw) >> 4;
        A.x += FX_MulFunc(v, FX_SinCosTable_[2 * k]);
        A.z += FX_MulFunc(v, FX_SinCosTable_[2 * k + 1]);
    }

    func_0203bc50(self, &A);
    func_0203be6c(self);
    func_01ffcbb0(buf2, self);

    {
        int r1 = func_0203c57c(self);
        int r2 = func_0203c568(self);
        int r3 = func_0203c548(self);
        func_0203bd84(self, buf2, r1, r2, r3);
    }
}

int func_0203b320(void)
{
    func_0203ac78();
    func_0203ad68();
    return 1;
}

void func_0203b2dc(int p)
{
    Vec3 buffer;
    func_0203ac78();
    func_0203be6c((void *) p);
    func_01ffcbb0(&buffer, (void *) p);
    func_0203bd84((void *) p, &buffer, func_0203c57c((void *) p), func_0203c568((void *) p), func_0203c548((void *) p));
}

int func_0203b2b8(void *p)
{
    unsigned short *base;
    base = (unsigned short *) ((char *) p + 0x21c);
    base[2] = 0;
    base[3] = 0x2000;
    func_0203ad68();
    return 1;
}

void func_0203b1d4(unsigned char *p)
{
    struct UnkStruct_0203b1d4 *w;
    int v;
    void *a;
    void *b;
    void *c;
    u32 local_b[3];
    u32 local_a[3];

    w = (struct UnkStruct_0203b1d4 *) (p + 0x21c);
    w->unk_04 = w->unk_04 + w->unk_06;
    func_020e89dc(&w->unk_06, 0x6000, 0x180);
    v = FX_MulFunc(((TabEntry *) FX_SinCosTable_)[(u16) w->unk_04 >> 4].x, (int) (*(void **) (p + 0x21c)));

    func_0203bc50(p, (Vec3 *) (p + 0x130));
    func_020e8bb0(w, 0, 0x400, 0x80, 0x10);
    func_0203be6c(p);
    func_01ffcbb0(local_a, p);
    a = (void *) func_0203c57c(p);
    b = (void *) func_0203c568(p);
    c = (void *) func_0203c548(p);
    func_0203bd84(p, local_a, (int) a, (int) b, (int) c);

    local_b[0] = 0;
    local_b[1] = 0x1000;
    local_b[2] = 0;
    MTX_MultVec33(local_b, p + 0xcc, local_b);
    func_020eabc8(local_b, v);
    VEC_Add(p + 0x194, local_b, p + 0x194);
    VEC_Add(p + 0x188, local_b, p + 0x188);
}

int func_0203b1b4(void *param1)
{
    func_0203caa4(param1, 0x1f, 0);
    func_0203c99c(param1, 5);
    func_0203ad58();
    return 1;
}

void func_0203b174(void *p)
{
    int stackArg;
    char buf[12];
    int v1, v2;
    func_0203be6c(p);
    func_01ffcbb0((void *) buf, p);
    v1 = func_0203c57c(p);
    v2 = func_0203c568(p);
    stackArg = func_0203c548(p);
    func_0203bd84(p, (void *) buf, v1, v2, stackArg);
}

int func_0203b144(void)
{
    UnkStruct_0203b144 *p;
    int field;
    p = data_021c67a4;
    field = p->unk_1F8;
    if (field == 9) {
        return 0;
    } else if (field == 0) {
        return 1;
    } else {
        return func_0203c0ac(p, 0);
    }
}

int func_0203b130(void)
{
    return func_0203c0ac((UnkStruct_0203b144 *) ((*(int *) &data_021c67a4)), 1);
}

int func_0203b0b8(int *a, int *b, int *out, int *extra)
{
    int ret;
    volatile int d[3];
    int e[3];
    func_020eaca0((void *) d, a, b);
    e[0] = d[0];
    e[1] = d[1];
    e[2] = d[2];
    e[2] = FX_MulFunc(d[2], data_020da718);
    ret = VEC_Mag(e);
    if (out != 0) {
        int t[3];
        int r[3];
        func_01ffd070(t, a, b);
        func_020eaad0(r, t, 1);
        out[0] = r[0];
        out[1] = r[1];
        out[2] = r[2];
        if (extra != 0) {
            int v = d[2] >> 1;
            if (v < 0) {
                v = -v;
            }
            *extra = v;
        }
    }
    return ret;
}

int func_0203affc(int *a, int *b, int *c, int *out, int *extra)
{
    int min[3];
    int max[3];
    int out1[3];
    int tmp[3];
    int result[3];
    int max2;
    int m;

    min[0] = a[0];
    min[1] = a[1];
    min[2] = a[2];
    max[0] = a[0];
    max[1] = a[1];
    max[2] = a[2];

    if (min[0] > b[0]) {
        min[0] = b[0];
    } else {
        max[0] = b[0];
    }
    if (min[2] > b[2]) {
        min[2] = b[2];
    } else {
        max[2] = b[2];
    }

    if (min[0] > c[0]) {
        min[0] = c[0];
    }
    if (min[2] > c[2]) {
        min[2] = c[2];
    }
    if (max[0] < c[0]) {
        max[0] = c[0];
    }
    if (max[2] < c[2]) {
        max[2] = c[2];
    }

    func_020eaca0((void *) out1, (void *) max, (void *) min);

    max2 = out1[2];
    m = out1[0];
    if (m <= max2) {
        m = max2;
    }

    if (out != 0) {
        func_01ffd070((void *) tmp, (void *) min, (void *) max);
        func_020eaad0((void *) result, (void *) tmp, 1);
        out[0] = result[0];
        out[1] = result[1];
        out[2] = result[2];
        out[1] = (a[1] + b[1]) >> 1;
        if (extra != 0) {
            *extra = out1[2] >> 1;
        }
    }

    return m;
}

int func_0203af80(struct UnkStruct_0203af80 *param)
{
    if ((*(struct GStruct **) &data_021c67a4)->unk_1F8 == 9) {
        return 0;
    }
    if (func_020b65c4() == 0xc) {
        return 0;
    }
    if (func_0203b0b8((int *) ((int) func_02095794(4)), (int *) param, 0, 0) >= 0xb000) {
        return func_0203b144();
    } else {
        int *p;
        (*(struct GStruct **) &data_021c67a4)->unk_1CA = 0;
        p = (*(struct GStruct **) &data_021c67a4)->unk_1CC;
        p[0] = param->a;
        p[1] = param->b;
        p[2] = param->c;
        return func_0203c0ac((UnkStruct_0203b144 *) ((*(struct GStruct **) &data_021c67a4)), 2);
    }
}

void func_0203af08(int *a, int *b)
{
    int r;

    r = func_0203affc((int *) func_02095794(4), a, b, 0, 0);
    if (r >= 0xb000) {
        func_0203b144();
    } else {
        int *d;
        (*(UnkStruct_0203af08 **) &data_021c67a4)->unk_1CA = 1;
        d = (*(UnkStruct_0203af08 **) &data_021c67a4)->unk_1CC;
        d[0] = a[0];
        d[1] = a[1];
        d[2] = a[2];
        d = (*(UnkStruct_0203af08 **) &data_021c67a4)->unk_1D8;
        d[0] = b[0];
        d[1] = b[1];
        d[2] = b[2];
        func_0203c0ac((UnkStruct_0203b144 *) ((*(UnkStruct_0203af08 **) &data_021c67a4)), 2);
    }
}
