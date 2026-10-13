/* func_020c0c78 @ 0x020c0c78, 0x1cc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

#define FX32_ONE 0x1000

#define GX_RGB(r, g, b) ((u16) ((r) | ((g) << 5) | ((b) << 10)))

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

extern Elem data_021fb8bc[];
extern u16 data_021f6cfc[];
extern void func_0209def4(Work *w);
extern fx32 FX_MulFunc(fx32 a, fx32 b);

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

    func_0209def4(&w);

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

        ra = FX_MulFunc(w.c0.r << 12, invF) + FX_MulFunc(w.c1.r << 12, f);
        ga = FX_MulFunc(w.c0.g << 12, invF) + FX_MulFunc(w.c1.g << 12, f);
        ba = FX_MulFunc(w.c0.b << 12, invF) + FX_MulFunc(w.c1.b << 12, f);

        rb = FX_MulFunc(w.c2.r << 12, invF) + FX_MulFunc(w.c3.r << 12, f);
        gb = FX_MulFunc(w.c2.g << 12, invF) + FX_MulFunc(w.c3.g << 12, f);
        bb = FX_MulFunc(w.c2.b << 12, invF) + FX_MulFunc(w.c3.b << 12, f);

        rt = FX_MulFunc(ra, t) + FX_MulFunc(rb, invT);
        gt = FX_MulFunc(ga, t) + FX_MulFunc(gb, invT);
        bt = FX_MulFunc(ba, t) + FX_MulFunc(bb, invT);

        w.col = GX_RGB((rt + 0x800) >> 12, (gt + 0x800) >> 12, (bt + 0x800) >> 12);
        data_021f6cfc[i] = w.col;
    }
}
