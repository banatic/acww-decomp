/* sky_moon_2: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020c0e44 @ 0x020c0e44, 0xc0 bytes, Thumb
 * func_020c0c78 @ 0x020c0c78, 0x1cc bytes, Thumb
 * func_020c0c58 @ 0x020c0c58, 0x20 bytes, Thumb
 */

#include "types.h"

#define FX32_ONE 0x1000
#define GX_RGB(r, g, b) ((u16) ((r) | ((g) << 5) | ((b) << 10)))

typedef struct {
    unsigned char unk_00;
    unsigned char unk_01;
    unsigned char unk_02;
    unsigned char unk_03;
} UnkStruct_020c0e44;

typedef struct {
    u16 r : 5;
    u16 g : 5;
    u16 b : 5;
    u16 unused : 1;
} GXRgb;

typedef struct Elem {
    u8 pad_00[6];
    GXRgb b[5];
    u8 pad_10[6];
    GXRgb a[5];
} Elem;

typedef struct Work {
    u8 unk_00;
    u8 unk_01;
    GXRgb c0;
    GXRgb c1;
    GXRgb c2;
    GXRgb c3;
    u16 col;
} Work;

typedef struct UnkStruct_020c0c78 {
    u8 pad_00[0x6c];
    fx32 t;
} UnkStruct_020c0c78;

extern void func_0209def4(unsigned short *p);
extern unsigned int func_0209dedc(void);
extern int FX_MulFunc(int a, int b);
extern int FX_Sqrt(int a);
extern int FX_Div(int a, int b);
extern Elem data_021fb8bc[];
extern u16 data_021f6cfc[];
extern struct Global2 {
    char pad_00[0x24];
    int unk_24;
} data_021f8ab0;

int func_020c0e44(int *out)
{
    UnkStruct_020c0e44 t;
    int ret = 1;
    unsigned int h, m, base, secs;
    int q, d, s;

    func_0209def4((unsigned short *) &t);
    h = t.unk_01;
    m = t.unk_00;
    base = func_0209dedc();
    secs = 0;
    if (h >= 0x13) {
        secs = base + (0x3c * m + 0xe10 * (h - 0x13));
    } else if (h < 4) {
        secs = base + (0xe10 * h + 0x4650 + 0x3c * m);
    } else {
        ret = 0;
    }
    if (ret != 0) {
        int a;
        q = (int) ((secs << 12) / 0x7e90);
        a = FX_MulFunc(0xffee0000, q) + 0x110000;
        d = q - 0x800;
        s = FX_Sqrt(0x1000 - FX_MulFunc(d, d));
        s = FX_Div(s - 0xddb, 0x225);
        out[0] = a;
        out[1] = s * -16 + 0x3c000;
        out[2] = 0;
    }
    return ret;
}

void func_020c0c78(UnkStruct_020c0c78 *obj)
{
    Elem *p0;
    Elem *p1;
    fx32 invT;
    fx32 ra, ga, ba;
    fx32 rb, gb, bb;
    fx32 rt, gt;
    fx32 t;
    int idx;
    u32 i;
    fx32 f, invF;
    fx32 bt;
    u32 a, b;
    Work w;

    func_0209def4((unsigned short *) (&w));

    b = w.unk_01;
    a = w.unk_00;

    if (b >= 0x13) {
        idx = b - 0x13;
    } else {
        idx = b + 5;
    }

    p0 = &data_021fb8bc[idx];
    p1 = &data_021fb8bc[idx + 1];

    t = obj->t;
    invT = FX32_ONE - t;

    f = (int) (a << 12) / 60;
    invF = FX32_ONE - f;

    for (i = 0; i < 5; i++) {
        w.c0 = p0->a[i];
        w.c1 = p1->a[i];
        w.c2 = p0->b[i];
        w.c3 = p1->b[i];

        ra = (fx32) FX_MulFunc((fx32) (w.c0.r << 12), (fx32) invF) + (fx32) FX_MulFunc((fx32) (w.c1.r << 12), (fx32) f);
        ga = (fx32) FX_MulFunc((fx32) (w.c0.g << 12), (fx32) invF) + (fx32) FX_MulFunc((fx32) (w.c1.g << 12), (fx32) f);
        ba = (fx32) FX_MulFunc((fx32) (w.c0.b << 12), (fx32) invF) + (fx32) FX_MulFunc((fx32) (w.c1.b << 12), (fx32) f);

        rb = (fx32) FX_MulFunc((fx32) (w.c2.r << 12), (fx32) invF) + (fx32) FX_MulFunc((fx32) (w.c3.r << 12), (fx32) f);
        gb = (fx32) FX_MulFunc((fx32) (w.c2.g << 12), (fx32) invF) + (fx32) FX_MulFunc((fx32) (w.c3.g << 12), (fx32) f);
        bb = (fx32) FX_MulFunc((fx32) (w.c2.b << 12), (fx32) invF) + (fx32) FX_MulFunc((fx32) (w.c3.b << 12), (fx32) f);

        rt = (fx32) FX_MulFunc((fx32) ra, (fx32) t) + (fx32) FX_MulFunc((fx32) rb, (fx32) invT);
        gt = (fx32) FX_MulFunc((fx32) ga, (fx32) t) + (fx32) FX_MulFunc((fx32) gb, (fx32) invT);
        bt = (fx32) FX_MulFunc((fx32) ba, (fx32) t) + (fx32) FX_MulFunc((fx32) bb, (fx32) invT);

        w.col = GX_RGB((rt + 0x800) >> 12, (gt + 0x800) >> 12, (bt + 0x800) >> 12);
        data_021f6cfc[i] = w.col;
    }
}

void func_020c0c58(int *param)
{
    int v;
    if (data_021f8ab0.unk_24 != 3 && data_021f8ab0.unk_24 != 4) {
        v = 0x1000;
    } else {
        v = 0;
    }
    param[0x1b] = v;
}
