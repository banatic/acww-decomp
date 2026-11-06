/* town_insect_3: 24 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_0222ea84 @ 0x0222ea84, 0x38 bytes, Thumb
 * func_ov003_0222ea04 @ 0x0222ea04, 0x80 bytes, Thumb
 * func_ov003_0222e98c @ 0x0222e98c, 0x76 bytes, Thumb
 * func_ov003_0222e970 @ 0x0222e970, 0x1c bytes, Thumb
 * func_ov003_0222e898 @ 0x0222e898, 0xd8 bytes, Thumb
 * func_ov003_0222e7f8 @ 0x0222e7f8, 0xa0 bytes, Thumb
 * func_ov003_0222e7bc @ 0x0222e7bc, 0x3c bytes, Thumb
 * func_ov003_0222e750 @ 0x0222e750, 0x6c bytes, Thumb
 * func_ov003_0222e6c4 @ 0x0222e6c4, 0x8c bytes, Thumb
 * func_ov003_0222e5fc @ 0x0222e5fc, 0xc8 bytes, Thumb
 * func_ov003_0222e538 @ 0x0222e538, 0xc4 bytes, Thumb
 * func_ov003_0222e4c0 @ 0x0222e4c0, 0x78 bytes, Thumb
 * func_ov003_0222e3a4 @ 0x0222e3a4, 0x11c bytes, Thumb
 * func_ov003_0222e358 @ 0x0222e358, 0x4c bytes, Thumb
 * func_ov003_0222e2d8 @ 0x0222e2d8, 0x80 bytes, Thumb
 * func_ov003_0222e264 @ 0x0222e264, 0x74 bytes, Thumb
 * func_ov003_0222e0ec @ 0x0222e0ec, 0x178 bytes, Thumb
 * func_ov003_0222e0ac @ 0x0222e0ac, 0x40 bytes, Thumb
 * func_ov003_0222e008 @ 0x0222e008, 0xa4 bytes, Thumb
 * func_ov003_0222dec4 @ 0x0222dec4, 0x144 bytes, Thumb
 * func_ov003_0222ddb8 @ 0x0222ddb8, 0x10c bytes, Thumb
 * func_ov003_0222ddac @ 0x0222ddac, 0xc bytes, Thumb
 * func_ov003_0222db40 @ 0x0222db40, 0x26c bytes, Thumb
 * func_ov003_0222da9c @ 0x0222da9c, 0xa4 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_0222ea84 {
    u8 pad_00[0x24d];
    s8 unk_24D;
    u8 pad_24E[2];
    u8 unk_250;
    u8 unk_251;
    u8 pad_252[0xa];
};

typedef struct {
    char pad_00[0x204];
    int unk_204;
    char pad_208[0x54];
} UnkStruct_0222e970;

typedef struct {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_0222e6c4;

typedef struct {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_0222e5fc;

typedef struct {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_0222e538;

typedef struct {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_0222e3a4;

typedef struct {
    int x, y, z;
} Vec3;

typedef struct {
    int r[9];
    Vec3 t;
} Mtx43;

typedef struct {
    char pad_00[0x25c];
} Actor;

typedef struct {
    int x, y, z;
} UnkStruct_0222db40;

typedef struct {
    char pad_00[0x204];
} UnkStruct_0222db40_2;

extern struct UnkStruct_0222ea84 data_ov003_02260e4c[];
extern int func_0203adc4(void *a, int b, int c);
extern short FX_SinCosTable_[];
extern int FX_MulFunc(int a, int b);
extern char *func_020961a8(int idx);
extern unsigned char data_ov003_022617bc[];
extern unsigned char data_ov003_02260994[];
extern void *func_0209d088(void *p);
extern void NNS_G3dMdlSetMdlAlpha(void *p, int a, int b);
extern UnkStruct_0222e6c4 *data_020ccf94;
extern int func_02073dd4(UnkStruct_0222e6c4 *p, int val);
extern int func_02073918(UnkStruct_0222e6c4 *p, int id);
extern void func_02073820(UnkStruct_0222e6c4 *p);
extern void func_020737f0(UnkStruct_0222e6c4 *p, unsigned char *id, int n);
extern void func_02073770(UnkStruct_0222e6c4 *p, int a, int b);
extern void func_0209129c(int h);
extern int func_020a7278(void);
extern unsigned char data_ov003_0226053c;
extern int NNS_G3dMdlGetMdlAlpha(void *p, int a);
extern int FX_Div(int num, int den);
extern char data_ov003_0223c146[];
extern void func_0205510c(void *a, void *b);
extern void func_020acdcc(void *a, int b, int c, unsigned char d);
extern Mtx43 data_021fbe48;
extern int func_0203f8d0(Vec3 *out, Vec3 *p);
extern void func_020e9774(Mtx43 *m, int ang);
extern void func_020e96c8(Mtx43 *m, int x, int y, int z);
extern void func_020e9744(Mtx43 *m, int a);
extern void func_020e9714(Mtx43 *m, int a);
extern void MTX_MultVec43(Vec3 *v, Mtx43 *m, Vec3 *out);
extern int func_0203f7d0(Vec3 *a, Vec3 *b);
extern int func_020912d4(int id, Vec3 *p, int a, short *h);
extern void func_02091278(int id, Vec3 *p, int a, short *h);
extern void func_ov003_0222fe18(void *a, void *b, int c);
extern void func_020e9898(void *a);
extern int func_0209d138(void *a);
extern void func_02044528(void);
extern void *func_020ba4e4(void);
extern int func_ov003_0222d248(int a, void *ctx);
extern int data_021c67a4;
extern int data_021c67d0[];
extern unsigned char data_ov003_0226054c;
extern char data_ov003_02260bf0[];
extern void func_ov003_0222d1bc(UnkStruct_0222db40_2 *d, int k);
extern void func_ov003_0222cf1c(UnkStruct_0222db40_2 *d);
extern void func_ov003_0222c4b8(UnkStruct_0222db40_2 *d, int wx, int wz, int rx, u8 up, u8 dn);
extern int func_02096614(u8 *f, int *y, int *z, int neg, int i);
extern char *func_ov003_02236164(int n);
extern int func_ov003_0221ac18(char *o);
extern int func_ov003_02233c70(int a, int b);
extern int func_020ea990(UnkStruct_0222db40 *a, UnkStruct_0222db40 *b);
extern s16 func_0200322c(UnkStruct_0222db40 *a, UnkStruct_0222db40 *b);
extern int func_ov003_0222ff2c(char *a, char *e);
extern int func_ov003_0222cf60(char *e, UnkStruct_0222db40_2 *d, int id, int p2);
extern int func_ov003_0222d6fc(signed char *c);
extern int func_02061550(unsigned char c);

int func_ov003_0222e98c(int a, int v);
int func_ov003_0222e7bc(int x);
void func_ov003_0222e4c0(int v);
void func_ov003_0222e2d8(void *ctx, char *o);
int func_ov003_0222e264(int a, unsigned char *o);

u8 func_ov003_0222ea84(int i)
{
    struct UnkStruct_0222ea84 *e = &data_ov003_02260e4c[i];

    if (e->unk_24D < 0) {
        e->unk_251 = 0xa;
        e->unk_250 = 0;
    }
    return e->unk_250;
}

int func_ov003_0222ea04(void *ctx, char *o, int n)
{
    int i;
    for (i = 0; i < n; i++) {
        if (*(unsigned char *) (o + 0x250) == 3 && *(unsigned char *) (o + 0x249) != 0) {
            if (n == 8) {
                if (func_ov003_0222e98c((int) ctx, *(unsigned char *) (o + 0x24d)) == 0 ||
                    func_0203adc4(o + 0x204, 0x2000, 0x2000) == 0) {
                    func_ov003_0222e2d8(ctx, (char *) o);
                }
            } else {
                func_ov003_0222e2d8(ctx, (char *) o);
            }
        }
        o += 0x25c;
    }
    return 1;
}

int func_ov003_0222e98c(int a, int v)
{
    switch (v) {
        case 9:
        case 0x10:
        case 0x11:
        case 0x12:
        case 0x13:
        case 0x14:
        case 0x1f:
        case 0x21:
        case 0x22:
        case 0x23:
        case 0x24:
        case 0x26:
        case 0x27:
        case 0x28:
        case 0x29:
        case 0x2a:
        case 0x2b:
        case 0x2c:
        case 0x2d:
        case 0x2e:
        case 0x2f:
        case 0x34:
        case 0x35:
            return 1;
        default:
            return 0;
    }
}

int *func_ov003_0222e970(int i)
{
    return &((UnkStruct_0222e970 *) data_ov003_02260e4c)[i].unk_204;
}

void func_ov003_0222e898(int type, int idx)
{
    unsigned char *p;
    char *src;
    int *d;
    int *q;
    int k;
    int a;

    p = ((unsigned char *) data_ov003_02260e4c) + idx * 0x25c;
    src = func_020961a8(idx);
    if (src != 0) {
        q = (int *) (src + 0x5c);
        d = (int *) (p + 0x204);
        d[0] = q[0];
        d[1] = q[1];
        d[2] = q[2];
        d[1] += 0x1b34;
        a = *(short *) (src + 0x8e);
        *(short *) (p + 0x23a) = (short) a;
        k = ((unsigned short) a >> 4) << 1;
        *(int *) (p + 0x204) += FX_MulFunc(0xfae, FX_SinCosTable_[k]);
        d[2] += FX_MulFunc(0xfae, FX_SinCosTable_[k + 1]);
    }
    p[0x250] = 1;
    p[0x251] = 0x10;
    switch (type) {
        case 0x25:
            p[0x24d] = 0x39;
            break;
        case 0x3a:
            p[0x24d] = 0xb;
            break;
        case 0x3b:
            p[0x24d] = 0x18;
            break;
        default:
            p[0x24d] = (unsigned char) type;
            break;
    }
}

void func_ov003_0222e7f8(int v)
{
    unsigned char *p;
    unsigned char st;
    unsigned char i;
    i = v & 0xf;
    if ((v >> 4) & 1) {
        p = data_ov003_022617bc + i * 0x25c;
    } else if ((v >> 5) & 1) {
        p = data_ov003_02260994 + i * 0x25c;
    }
    *(unsigned short *) (p + 0x242) = 0;
    st = p[0x251];
    if (func_ov003_0222e7bc(*(signed char *) (p + 0x24d)) != 0 && p[0x250] != 4 && st != 0x10 && st != 0xa) {
        if (st != 0x11) {
            if (*(short *) (p + 0x232) > 6) {
                *(short *) (p + 0x232) = 6;
                p[0x251] = 0x11;
            }
        }
    } else {
        p[0x250] = 4;
    }
}

int func_ov003_0222e7bc(int x)
{
    switch (x) {
        case 0xc:
        case 0xd:
        case 0x1b:
        case 0x1c:
        case 0x1d:
        case 0x1e:
        case 0x31:
            return 1;
    }
    return 0;
}

void func_ov003_0222e750(int v)
{
    unsigned char *p;
    unsigned char i;
    i = v & 0xf;
    if ((v >> 4) & 1) {
        p = data_ov003_022617bc + i * 0x25c;
    } else if ((v >> 5) & 1) {
        p = data_ov003_02260994 + i * 0x25c;
    }
    if (p[0x250] == 3) {
        NNS_G3dMdlSetMdlAlpha(func_0209d088(p + 0x130), 0, 0);
    }
    p[0x251] = 0x10;
}

void func_ov003_0222e6c4(unsigned char id, int flag)
{
    unsigned char *p;
    UnkStruct_0222e6c4 *o;

    p = ((unsigned char *) data_ov003_02260e4c) + id * 0x25c;
    o = data_020ccf94;
    if (func_02073dd4(o, o->unk_64) != 0 && flag != 0 && func_02073918(o, id) != 0) {
        o = data_020ccf94;
        func_02073820(o);
        func_020737f0(o, &id, 1);
        func_02073770(o, 0x30, 4);
    }
    if (*(int *) (p + 0x22c) != -1) {
        func_0209129c(*(int *) (p + 0x22c));
        *(int *) (p + 0x22c) = -1;
    }
    p[0x251] = 0xa;
}

int func_ov003_0222e5fc(unsigned char id)
{
    unsigned char *p;
    UnkStruct_0222e5fc *o;
    unsigned char i;
    int r;
    i = id & 0xf;
    if ((id >> 4) & 1) {
        p = data_ov003_022617bc + i * 0x25c;
    } else if ((id >> 5) & 1) {
        p = data_ov003_02260994 + i * 0x25c;
    }
    *(unsigned short *) (p + 0x242) = 0;
    p[0x250] = 4;
    if (func_02073dd4((UnkStruct_0222e6c4 *) ((*(UnkStruct_0222e5fc **) &data_020ccf94)),
                      (*(UnkStruct_0222e5fc **) &data_020ccf94)->unk_64) != 0) {
        o = (*(UnkStruct_0222e5fc **) &data_020ccf94);
        func_02073820((UnkStruct_0222e6c4 *) o);
        func_020737f0((UnkStruct_0222e6c4 *) o, &id, 1);
        func_02073770((UnkStruct_0222e6c4 *) o, 0x30, 4);
    }
    r = *(signed char *) (p + 0x24d);
    switch (r) {
        case 0x3a:
            p[0x251] = 8;
            p[0x250] = 3;
            return 0xb;
        case 0x3b:
            p[0x251] = 8;
            p[0x250] = 3;
            return 0x18;
    }
    return r;
}

unsigned char func_ov003_0222e538(int v, unsigned char unused)
{
    unsigned char id;
    unsigned char *p;
    int ok;
    unsigned char i;
    UnkStruct_0222e538 *o;

    p = 0;
    ok = 0;
    i = v & 0xf;
    if ((v >> 4) & 1) {
        p = data_ov003_022617bc + i * 0x25c;
    } else if ((v >> 5) & 1) {
        p = data_ov003_02260994 + i * 0x25c;
    } else {
        ok = 1;
    }
    if (p == 0) {
        ok = 1;
    }
    if (ok != 1) {
        if (func_02073dd4((UnkStruct_0222e6c4 *) ((*(UnkStruct_0222e538 **) &data_020ccf94)),
                          (*(UnkStruct_0222e538 **) &data_020ccf94)->unk_64) != 0 &&
            func_020a7278() == 0) {
            ok = data_ov003_0226053c;
        }
    }
    if (ok == 1) {
        func_ov003_0222e4c0(v);
        id = v;
        if (func_02073dd4((UnkStruct_0222e6c4 *) ((*(UnkStruct_0222e538 **) &data_020ccf94)),
                          (*(UnkStruct_0222e538 **) &data_020ccf94)->unk_64) != 0 &&
            func_020a7278() == 0) {
            o = (*(UnkStruct_0222e538 **) &data_020ccf94);
            func_02073820((UnkStruct_0222e6c4 *) o);
            func_020737f0((UnkStruct_0222e6c4 *) o, &id, 1);
            func_02073770((UnkStruct_0222e6c4 *) o, 0x2f, 4);
        }
    }
    return ok;
}

void func_ov003_0222e4c0(int v)
{
    char *p;
    unsigned char *q;
    unsigned char i;
    i = v & 0xf;
    p = (char *) v;
    if ((v >> 4) & 1) {
        p = ((char *) data_ov003_022617bc) + i * 0x25c;
    } else if ((v >> 5) & 1) {
        p = ((char *) data_ov003_02260994) + i * 0x25c;
    }
    q = (unsigned char *) (p + 0x251);
    if (*q != 0x10) {
        return;
    }
    if (*(signed char *) (p + 0x24d) < 0) {
        return;
    }
    *q = 0x13;
    NNS_G3dMdlSetMdlAlpha(func_0209d088(p + 0x130), 0, 0x1f);
}

int func_ov003_0222e3a4(unsigned char id)
{
    unsigned char *p;
    unsigned char st;
    unsigned char ty;
    unsigned char i;
    UnkStruct_0222e3a4 *o;

    i = id & 0xf;
    if ((id >> 4) & 1) {
        p = data_ov003_022617bc + i * 0x25c;
    } else if ((id >> 5) & 1) {
        p = data_ov003_02260994 + i * 0x25c;
    } else {
        return 0;
    }

    st = p[0x251];
    ty = p[0x24d];
    if (ty == -1 || p[0x250] != 3 || st == 0xb || st == 9 || st == 0x10) {
        return 0;
    }
    if (ty == 0x31 || ty == 0x1e || ty == 0x35) {
        if (NNS_G3dMdlGetMdlAlpha(func_0209d088(p + 0x130), 0) < 0x1f) {
            return 0;
        }
    }
    if (ty == 0x35 && st == 0x13) {
        return 0;
    }
    if (*(signed char *) (p + 0x24d) != 0x3a && *(signed char *) (p + 0x24d) != 0x3b) {
        NNS_G3dMdlSetMdlAlpha(func_0209d088(p + 0x130), 0, 0);
        p[0x251] = 0x10;
    }
    if (func_02073dd4((UnkStruct_0222e6c4 *) ((*(UnkStruct_0222e3a4 **) &data_020ccf94)),
                      (*(UnkStruct_0222e3a4 **) &data_020ccf94)->unk_64) != 0 &&
        func_020a7278() == 0) {
        data_ov003_0226053c = 2;
        o = (*(UnkStruct_0222e3a4 **) &data_020ccf94);
        func_02073820((UnkStruct_0222e6c4 *) o);
        func_020737f0((UnkStruct_0222e6c4 *) o, &id, 1);
        func_02073770((UnkStruct_0222e6c4 *) o, 0x28, 6);
    }
    return 1;
}

void func_ov003_0222e358(char *self, int pct)
{
    if (pct == 0x64) {
        *(int *) (self + 0x210) = 0x1000;
        *(int *) (self + 0x214) = 0x1000;
        *(int *) (self + 0x218) = 0x1000;
    } else {
        *(int *) (self + 0x210) = FX_Div(pct << 12, 0x64000);
        *(int *) (self + 0x214) = *(int *) (self + 0x210);
        *(int *) (self + 0x218) = *(int *) (self + 0x210);
    }
}

void func_ov003_0222e2d8(void *ctx, char *o)
{
    int *p = (int *) (o + 0x210);
    if (*p > 0) {
        int v;
        int t = (0x1f - NNS_G3dMdlGetMdlAlpha(func_0209d088(o + 0x130), 0)) * 2;
        if (t > 0x1f) {
            v = 0;
        } else {
            v = 0x1f - t;
        }
        func_0205510c(o + 0x50, p);
        if (func_ov003_0222e264((int) ctx, (unsigned char *) o)) {
            func_020acdcc(o + 0x204, *(unsigned short *) (data_ov003_0223c146 + 6 * *(signed char *) (o + 0x24d)), 0x9000,
                          (unsigned char) v);
        }
    }
}

int func_ov003_0222e264(int a, unsigned char *o)
{
    signed char v = (signed char) o[0x24d];

    if (*(unsigned short *) ((char *) ((unsigned short *) data_ov003_0223c146) + v * 6) <= 1) {
        return 0;
    }

    switch (v) {
        case 0x1e:
        case 0x31:
            if (o[0x251] != 0x13) {
                return 1;
            }
            return 0;
        case 0x18:
        case 0x30:
        case 0x32:
        case 0x33:
        case 0x3a:
        case 0x3b:
            return 0;
        default:
            return 1;
    }
}

void func_ov003_0222e0ec(int unused, char *self, int mode)
{
    short h[2];
    Vec3 v;
    Mtx43 m;
    Vec3 t;
    Mtx43 m2;
    Vec3 vin;
    Vec3 vout;
    int ang;
    char *p50;

    p50 = self + 0x50;
    ang = func_0203f8d0(&v, (Vec3 *) (self + 0x204));
    if (mode != 0) {
        data_021fbe48 = *(Mtx43 *) (self + 0x180);
        func_020e9774(&data_021fbe48, *(short *) (self + 0x238));
    } else {
        func_020e96c8(&data_021fbe48, v.x, v.y, v.z);
        func_020e9774(&data_021fbe48, (short) (ang + *(short *) (self + 0x238)));
    }
    if (*(short *) (self + 0x23a) != 0) {
        func_020e9744(&data_021fbe48, *(short *) (self + 0x23a));
    }
    if (*(short *) (self + 0x23c) != 0) {
        func_020e9714(&data_021fbe48, *(short *) (self + 0x23c));
    }
    *(Mtx43 *) (p50 + 0x64) = data_021fbe48;
    if (mode != 0) {
        if (*(signed char *) (self + 0x24d) == 0x39) {
            int *q;
            m = data_021fbe48;
            t.x = m.t.x;
            t.y = m.t.y;
            t.z = m.t.z;
            q = (int *) (self + 0x22c);
            m.t.z = 0;
            m.t.y = 0;
            m.t.x = 0;
            m2 = m;
            vin.y = 0;
            vin.x = 0;
            vin.z = FX_MulFunc(*(int *) (self + 0x210), -0x333);
            MTX_MultVec43(&vin, &m2, &vout);
            t.x = t.x + vout.x;
            t.y = t.y + vout.y;
            t.z = t.z + vout.z;
            func_0203f7d0(&t, &t);
            if (*(int *) (self + 0x21c) == 0) {
                h[0] = (short) *(int *) (self + 0x210);
                *q = func_020912d4(0x3a, &t, 0, h);
                *(int *) (self + 0x21c) = 1;
            } else {
                h[1] = (short) *(int *) (self + 0x210);
                if (*q != -1) {
                    func_02091278(*q, &t, 0, &h[1]);
                }
            }
        }
    }
}

int func_ov003_0222e0ac(void *self)
{
    int r = func_ov003_0222ea04(self, (char *) (((char *) data_ov003_022617bc)), 8);
    r &= func_ov003_0222ea04(self, (char *) (((char *) data_ov003_02260994)), 2);
    r &= func_ov003_0222ea04(self, (char *) (((char *) data_ov003_02260e4c)), 4);
    return r;
}

int func_ov003_0222e008(char *self)
{
    Actor *a = ((Actor *) data_ov003_022617bc);
    Actor *b = ((Actor *) data_ov003_02260994);
    Actor *c = ((Actor *) data_ov003_02260e4c);
    int i;
    int j;
    for (i = 0; i < 8; i++) {
        func_ov003_0222fe18(self, a++, 1);
    }
    for (i = 0; i < 2; i++) {
        void **p;
        func_ov003_0222fe18(self, b++, 2);
        p = (void **) (self + i * 4);
        func_020e9898(p[0x26]);
        p[0x26] = 0;
    }
    for (j = 0; j < 4; j++) {
        func_ov003_0222fe18(self, c++, 3);
    }
    func_0209d138(self + 0x50);
    func_0209d138(self + 0x68);
    func_0209d138(self + 0x80);
    func_02044528();
    return 1;
}

void func_ov003_0222dec4(void *a0, int mode, int slot, int x, int z)
{
    int n;
    int x0, z0, x1, z1;
    void *ctx;
    int rr;
    int *pp;
    int bit;
    int mask;
    int zero;
    char *e;
    u8 i;
    int f;
    int g;
    int v;

    if (mode == 1) {
        e = ((char *) data_ov003_022617bc);
        n = 8;
    } else {
        e = ((char *) data_ov003_02260994);
        n = 2;
    }
    x0 = x - 0x10000;
    z0 = z - 0x1c000;
    x1 = x + 0x10000;
    z1 = z + 0xc000;
    ctx = func_020ba4e4();
    i = 0;
    bit = 1 << slot;
    mask = ~(bit & 0xf);
    zero = 0;
    for (; i < n; i++) {
        if (*(u8 *) (e + 0x248) != 0 && *(s8 *) (e + 0x24d) >= 0) {
            pp = (int *) (e + 0x204);
            f = *(u8 *) (e + 0x258);
            rr = func_ov003_0222d248(*(s8 *) (e + 0x24d), ctx);
            if (func_020a7278() == 0 && rr == 4) {
                rr = 3;
            }
            g = *(u8 *) (e + 0x249);
            if (g == 0 && rr == 4) {
                func_ov003_0222fe18(a0, e, mode);
            } else {
                v = pp[0];
                if (x0 < v && x1 > v && z0 < pp[2] && z1 > pp[2]) {
                    if (g == 0) {
                        *(u8 *) (e + 0x249) = 1;
                        f |= bit;
                        *(u8 *) (e + 0x258) = (u8) f;
                    }
                } else if (((f >> slot) & 1) != 0) {
                    f &= mask;
                    *(u8 *) (e + 0x258) = (u8) f;
                } else if (g != 0 && f == 0 && mode == 1) {
                    *(u8 *) (e + 0x249) = (u8) zero;
                }
            }
        }
        e += 0x25c;
    }
}

void func_ov003_0222ddb8(void *a0, int a1)
{
    int g;
    char *e;
    int n;
    int x0, z0, x1, z1;
    void *ctx;
    int zero1, zero2;
    volatile Vec3 c;
    u8 i;
    int *p;
    int r;
    int v;

    g = data_021c67a4;
    if (a1 == 1) {
        e = ((char *) data_ov003_022617bc);
        n = 8;
    } else {
        e = ((char *) data_ov003_02260994);
        n = 2;
    }
    if (g == 0) {
        return;
    }
    c.x = data_021c67d0[0];
    c.y = data_021c67d0[1];
    c.z = data_021c67d0[2];
    x0 = data_021c67d0[0] - 0x10000;
    z0 = data_021c67d0[2] - 0x1c000;
    x1 = data_021c67d0[0] + 0x10000;
    z1 = data_021c67d0[2] + 0xc000;
    ctx = func_020ba4e4();
    zero1 = 0;
    zero2 = 0;
    for (i = 0; i < n; i++) {
        if (*(u8 *) (e + 0x248) != 0 && *(s8 *) (e + 0x24d) >= 0) {
            p = (int *) (e + 0x204);
            r = func_ov003_0222d248(*(s8 *) (e + 0x24d), ctx);
            if (*(u8 *) (e + 0x249) == 0 && r == 4) {
                func_ov003_0222fe18(a0, e, a1);
            } else {
                if (r == 5) {
                    *(u8 *) (e + 0x246) = (u8) zero1;
                } else {
                    *(u8 *) (e + 0x246) = 1;
                }
                v = p[0];
                if (x0 < v && x1 > v && z0 < p[2] && z1 > p[2]) {
                    *(u8 *) (e + 0x249) = 1;
                } else {
                    *(u8 *) (e + 0x249) = (u8) zero2;
                }
            }
        }
        e += 0x25c;
    }
}

void func_ov003_0222ddac(void)
{
    data_ov003_0226054c = 1;
}

int func_ov003_0222db40(char *a, int id, int p2, int mode)
{
    UnkStruct_0222db40_2 d;
    char *e;
    char *g;
    UnkStruct_0222db40 *p204;
    UnkStruct_0222db40 *q;
    UnkStruct_0222db40 *p;
    char *obj;
    UnkStruct_0222db40 *r6;
    UnkStruct_0222db40 *src;
    UnkStruct_0222db40 *dst;
    unsigned int k;
    char *t;
    unsigned int n;
    int idx;
    int neg;
    int ang;
    int len;
    u8 flag;
    int yy, zz;
    int j;
    int slot;

    e = ((char *) data_ov003_022617bc);
    slot = ~0;
    if (id != 8) {
        func_ov003_0222d1bc(&d, p2);
    } else {
        func_ov003_0222cf1c(&d);
    }
    if (mode == 1) {
        k = 0;
        while (k < 8) {
            if (*(u8 *) (e + 0x248) != 0) {
                if (id != 0x33) {
                    p204 = (UnkStruct_0222db40 *) (e + 0x204);
                    if (id == 0x23) {
                        if (*(signed char *) (e + 0x24d) == 0x23) {
                            return 0;
                        }
                    }
                    if (id != 8) {
                        func_ov003_0222c4b8(&d, p204->x, p204->z, 1, 1, 1);
                    }
                }
            } else if (slot < 0) {
                slot = (signed char) k;
            }
            e = e + 0x25c;
            k = (u8) (k + 1);
        }
    }
    if (slot >= 0 || mode == 2) {
        t = (char *) func_020961a8(4);
        if (t != 0 && mode == 1 && id != 0x33) {
            g = (*(char **) &data_020ccf94);
            if (func_02073dd4((UnkStruct_0222e6c4 *) g, *(int *) (g + 0x64)) != 0) {
                neg = -1;
                for (j = 0; j < 4; j++) {
                    if (func_02096614(&flag, &yy, &zz, neg, j) != 0) {
                        if (flag == 0) {
                            func_ov003_0222c4b8(&d, yy, zz, 5, 8, 5);
                        }
                    }
                }
            } else {
                q = (UnkStruct_0222db40 *) (t + 0x5c);
                func_ov003_0222c4b8(&d, q->x, q->z, 5, 8, 5);
            }
        }
        if (mode == 1) {
            e = ((char *) data_ov003_022617bc) + slot * 0x25c;
        } else {
            e = data_ov003_02260bf0;
        }
        if (id == 0x23) {
            g = (*(char **) &data_020ccf94);
            if (func_02073dd4((UnkStruct_0222e6c4 *) g, *(int *) (g + 0x64)) == 0) {
                n = 0;
                while (n < 2) {
                    obj = func_ov003_02236164(n);
                    if (obj != 0) {
                        p = (UnkStruct_0222db40 *) (obj + 0x5c);
                        r6 = (UnkStruct_0222db40 *) (e + 0x204);
                        ang = func_ov003_0221ac18(obj);
                        len = func_ov003_02233c70(0x20, 1);
                        if (t != 0) {
                            if (func_020ea990((UnkStruct_0222db40 *) (t + 0x5c), p) > 0xc000) {
                                r6->x = p->x;
                                r6->y = p->y;
                                r6->z = p->z;
                                idx = ((u16) len >> 4) * 2;
                                r6->x = r6->x + FX_MulFunc(((s16 *) FX_SinCosTable_)[idx], ang);
                                r6->z = r6->z + FX_MulFunc(((s16 *) FX_SinCosTable_)[idx + 1], ang);
                                *(s16 *) (e + 0x23a) = func_0200322c(p, r6);
                                *(u8 *) (e + 0x248) = 1;
                                *(u8 *) (e + 0x24d) = (u8) id;
                                *(u8 *) (e + 0x249) = 0;
                                *(int *) (e + 0x21c) = n;
                                func_ov003_0222ff2c(a, e);
                                return 1;
                            }
                        }
                    }
                    n = (u8) (n + 1);
                }
                goto zero;
            }
        }
        if (func_ov003_0222cf60(e, &d, id, p2) != 0) {
            *(u8 *) (e + 0x248) = 1;
            *(u8 *) (e + 0x24d) = (u8) id;
            *(u8 *) (e + 0x249) = 0;
            src = (UnkStruct_0222db40 *) (e + 0x204);
            dst = (UnkStruct_0222db40 *) (e + 0x1c8);
            dst->x = src->x;
            dst->y = src->y;
            dst->z = src->z;
            if (mode == 1) {
                func_ov003_0222ff2c(a, e);
            }
            return 1;
        }
    }
zero:
    return 0;
}

int func_ov003_0222da9c(void *a, void *b, signed char c, int d)
{
    unsigned char *p;
    int r;
    unsigned char i;

    r = 0;
    p = data_ov003_022617bc;
    for (i = 0; i < 8; i++) {
        if (p[0x248] == 0) {
            if (c == 0x33) {
                r = func_ov003_0222db40((char *) a, c, (unsigned char) d, (int) b);
            } else if (func_ov003_0222d6fc(&c) != 0) {
                r = func_ov003_0222db40((char *) a, c, func_02061550((unsigned char) c), (int) b);
            }
            if (r == 0 && c != 0x33) {
                p[0x248] = 1;
                *(signed char *) (p + 0x24d) = -10;
            }
            return r;
        }
        p += 0x25c;
    }
    return 0;
}
