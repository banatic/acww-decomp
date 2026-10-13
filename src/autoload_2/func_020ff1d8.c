/* func_020ff1d8 @ 0x020ff1d8, 0x1cc bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

typedef struct {
    u16 unk_00;
    u16 c1;
    u8 t0, t1, t2, pad_07;
    u16 f0 : 2;
    u16 interp : 1;
} Anim;

typedef struct {
    u8 pad_00[0x22];
    u16 base;
} Res;

typedef struct {
    Res *res;
    int pad_04;
    Anim *anim;
} Emtr;

typedef struct {
    u8 pad_00[0x36];
    u16 color;
} Ptcl;

#define RGB(r, g, b) ((u16) ((r) | ((g) << 5) | ((b) << 10)))

void func_020ff1d8(Ptcl *ptcl, Emtr *emtr, int t)
{
    Anim *a = emtr->anim;
    int t0 = a->t0;
    Res *res = emtr->res;
    int t1 = a->t1;
    int t2 = a->t2;
    u16 src, dst;
    int dr, sr, dg, sg, db, sb;

    if (t < t0) {
        ptcl->color = a->unk_00;
        return;
    }
    if (t < t1) {
        dst = res->base;
        src = a->unk_00;
        dr = dst & 0x1f;
        dg = (dst >> 5) & 0x1f;
        db = (dst >> 10) & 0x1f;
        sr = src & 0x1f;
        sg = (src >> 5) & 0x1f;
        sb = (src >> 10) & 0x1f;
        if (!a->interp) {
            ptcl->color = RGB(dr, dg, db);
            return;
        }
        ptcl->color = RGB(sr + (t - t0) * (dr - sr) / (t1 - t0), sg + (t - t0) * (dg - sg) / (t1 - t0),
                          sb + (t - t0) * (db - sb) / (t1 - t0));
        return;
    }
    if (t < t2) {
        u16 src2, dst2;
        int sr2, dr2, sg2, dg2, db2, sb2;

        dst2 = a->c1;
        src2 = res->base;
        dr2 = dst2 & 0x1f;
        dg2 = (dst2 >> 5) & 0x1f;
        sr2 = src2 & 0x1f;
        sg2 = (src2 >> 5) & 0x1f;
        sb2 = (src2 >> 10) & 0x1f;
        db2 = (dst2 >> 10) & 0x1f;
        if (!a->interp) {
            ptcl->color = RGB(dr2, dg2, db2);
            return;
        }
        ptcl->color = RGB(sr2 + (t - t1) * (dr2 - sr2) / (t2 - t1), sg2 + (t - t1) * (dg2 - sg2) / (t2 - t1),
                          sb2 + (t - t1) * (db2 - sb2) / (t2 - t1));
        return;
    }
    ptcl->color = a->c1;
}
