/* func_02088df8 @ 0x02088df8, 0x508 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

/* FAKEMATCH: the empty if on gfx_o adds the 4-byte stack slot that puts the base/cnt spills at their offsets; without it every spill sits 4 bytes lower */

#include "types.h"

#pragma opt_loop_invariants off

typedef struct Spr {
    u32 y8 : 8;
    u32 mode : 2;
    u32 gfx : 2;
    u32 mosaic : 1;
    u32 c256 : 1;
    u32 shape : 2;
    u32 x : 9;
    u32 u25 : 3;
    u32 flip : 2;
    u32 size : 2;
    u32 tile : 10;
    u32 prio : 2;
    u32 pal : 4;
    u32 rest : 16;
} Spr;

typedef struct UnkStruct_02088df8 {
    u32 unk_00;
    u16 w2;
    u16 w3;
} UnkStruct_02088df8;
typedef struct Quad {
    int a, b, c, d;
} Quad;

extern int func_02088c14(int a);
extern int func_02088dd8(Spr *p);
extern int func_02088db8(Spr *p);
extern int func_02088c60(UnkStruct_02088df8 *a, int *b, Quad *q);
extern int FX_Div(int a, int b);
extern int FX_MulFunc(int a, int b);

extern int data_021d2914;
extern int data_021d291c;
extern int data_021d2910;
extern int data_021d2918;
extern UnkStruct_02088df8 data_021d2920[];
extern UnkStruct_02088df8 data_021d2d20[];
extern short FX_SinCosTable_[];

void func_02088df8(int a0, Spr *s, int px, int py, int pal, int prio, int sx, int sy, int rot, int p9, int p10, int p11)
{
    int aff;
    UnkStruct_02088df8 *ent;
    int *cnt;
    int t60;
    int *base;
    int mosaic;
    int pal_o;
    int ra;
    int h;
    int hw;
    int hh;
    int t2c;
    int gfx_o;
    int w;
    int idx;
    int c256;
    int tile;
    int rb;
    int f3;
    int f0;
    int f1;
    int x, y;
    u32 mode;
    u32 keep;
    short *psin;
    short *pcos;
    int idx2;
    int prio_o;
    int c0;
    int c1;
    int cosv;
    int sinv;
    int pl;
    Quad q;

    if (func_02088c14(a0)) {
        ent = &data_021d2920[data_021d2914];
        cnt = &data_021d2914;
        base = &data_021d2910;
    } else {
        ent = &data_021d2d20[data_021d291c];
        cnt = &data_021d291c;
        base = &data_021d2918;
    }

    if (sx != 0x1000 || sy != 0x1000 || rot != 0) {
        aff = 1;
    } else {
        aff = 0;
    }

    psin = &FX_SinCosTable_[((int) (u16) (short) rot >> 4) * 2];
    pcos = &FX_SinCosTable_[((int) (u16) (short) rot >> 4) * 2 + 1];
    idx2 = (rot >> 4) * 2;

    for (;;) {
        if (*cnt >= 0x80) {
            break;
        }

        f3 = 0;
        if (aff != 0 && s->mode == 3) {
            f3 = 1;
        }
        f0 = 0;
        if (aff != 0 && s->mode == 0) {
            f0 = 1;
        }
        f1 = 0;
        if (aff != 0 && s->mode == 1) {
            f1 = 1;
        }

        x = s->x;
        if (x >= 0x100) {
            x -= 0x200;
        }
        y = *(char *) s;
        w = func_02088dd8(s);
        h = func_02088db8(s);

        if (aff != 0) {
            if (f3 != 0) {
                w = w << 1;
                h = h << 1;
            }
            hw = w >> 1;
            hh = h >> 1;
            x = (x + hw) << 12;
            y = (y + hh) << 12;
            if (sx != 0x1000) {
                x = FX_Div(x, sx);
            }
            if (sy != 0x1000) {
                y = FX_Div(y, sy);
            }
            if (rot != 0) {
                c0 = *psin;
                c1 = *pcos;
                t60 = FX_MulFunc(c1, x);
                t2c = t60 - FX_MulFunc(c0, y);
                y = FX_MulFunc(c1, y) + FX_MulFunc(c0, x);
                x = ((t2c + (t2c > 0 ? 0x800 : -0x800)) >> 12) - hw;
                y = ((y + (y > 0 ? 0x800 : -0x800)) >> 12) - hh;
            } else {
                x = ((x + 0x800) >> 12) - hw;
                y = ((y + 0x800) >> 12) - hh;
            }
            if (f0 != 0) {
                x -= hw;
                y -= hh;
                w = w << 1;
                h = h << 1;
            }
        }
        x += px;
        y += py;

        if (rot != 0) {
            w = w >= h ? w : h;
            if (x + w < 0 || x > 0x100) {
                if (s->rest == 0xffff) {
                    break;
                }
                s++;
                continue;
            }
            if (y + w < 0 || y > 0xc0) {
                if (s->rest == 0xffff) {
                    break;
                }
                s++;
                continue;
            }
        } else {
            if (x + w < 0 || x > 0x100) {
                if (s->rest == 0xffff) {
                    break;
                }
                s++;
                continue;
            }
            if (y + h < 0 || y > 0xc0) {
                if (s->rest == 0xffff) {
                    break;
                }
                s++;
                continue;
            }
        }

        if (pal == -1) {
            pal_o = s->pal;
        } else {
            pal_o = pal;
        }
        if (prio == -1) {
            prio_o = s->prio;
        } else {
            prio_o = prio;
        }
        if (p9 > 0) {
            gfx_o = p9;
        } else {
            gfx_o = s->gfx;
            if (gfx_o && gfx_o) {
            }
        }

        if (aff != 0) {
            cosv = FX_SinCosTable_[idx2 + 1];
            ra = (cosv * sx + 0x800) >> 12;
            q.a = ra;
            sinv = FX_SinCosTable_[idx2];
            rb = (sinv * sx + 0x800) >> 12;
            q.b = rb;
            q.c = -((sinv * sy + 0x800) >> 12);
            q.d = (cosv * sy + 0x800) >> 12;
            if ((((u32 *) s)[0] & 0x10000000) != 0) {
                q.a = -ra;
                q.b = -rb;
            }
            if ((((u32 *) s)[0] & 0x20000000) != 0) {
                q.c = -q.c;
                q.d = -q.d;
            }
            idx = func_02088c60(ent - *cnt, base, &q);
            if (idx == -1) {
                if (s->rest == 0xffff) {
                    break;
                }
                s++;
                continue;
            }
            if (f1 != 0) {
                mode = 0x100;
            } else {
                mode = 0x300;
            }
        } else {
            idx = 0;
            mode = ((u32 *) s)[0] & 0x30000000;
        }

        if (p10 != 0) {
            mode |= 0x10000000;
        }
        if (p11 != 0) {
            mode |= 0x20000000;
        }

        tile = s->tile;
        c256 = s->c256;
        keep = ((u32 *) s)[0];
        keep = keep & 0xc000c000;
        mosaic = s->mosaic;

        if (mode == 0x100 || mode == 0x300) {
            if (gfx_o == 3) {
                u32 attr = (x & 0x1ff) << 16;
                keep |= (mosaic << 12) | ((gfx_o << 10) | ((idx << 25) | (y & 0xff)));
                attr |= keep;
                ent->unk_00 = mode | attr;
            } else {
                u32 attr = (x & 0x1ff) << 16;
                keep |= (mosaic << 12) | ((gfx_o << 10) | ((y & 0xff) | ((idx << 25) | (c256 << 13))));
                attr |= keep;
                ent->unk_00 = mode | attr;
            }
        } else {
            if (gfx_o == 3) {
                u32 attr = (x & 0x1ff) << 16;
                keep |= (mosaic << 12) | ((y & 0xff) | (gfx_o << 10));
                attr |= keep;
                ent->unk_00 = mode | attr;
            } else {
                u32 attr = (x & 0x1ff) << 16;
                keep |= (mosaic << 12) | ((gfx_o << 10) | ((c256 << 13) | (y & 0xff)));
                attr |= keep;
                ent->unk_00 = mode | attr;
            }
        }

        pl = pal_o << 12;
        pl |= (tile |= prio_o << 10);
        ent->w2 = (u16) pl;
        ent++;
        *cnt = *cnt + 1;
        if (s->rest == 0xffff) {
            break;
        }
        s++;
    }
}
