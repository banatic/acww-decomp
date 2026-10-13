/* func_02089300 @ 0x02089300, 0x3b8 bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

#include "types.h"

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

typedef struct UnkStruct_02089300 {
    u32 unk_00;
    u16 w2;
    u16 w3;
} UnkStruct_02089300;
typedef struct Quad {
    int a, b, c, d;
} Quad;

extern int func_02088c14(int a);
extern int func_02088dd8(Spr *p);
extern int func_02088db8(Spr *p);
extern int func_02088c60(UnkStruct_02089300 *a, int *b, Quad *q);
extern int FX_MulFunc(int a, int b);

extern int data_021d2914;
extern int data_021d291c;
extern int data_021d2910;
extern int data_021d2918;
extern UnkStruct_02089300 data_021d2920[];
extern UnkStruct_02089300 data_021d2d20[];
extern short FX_SinCosTable_[];

static inline u32 uid(u32 x)
{
    return x;
}
UnkStruct_02089300 *func_02089300(int a0, Spr *s, int px, int py, int pal, int prio, int scale, int rot, int p9)
{
    UnkStruct_02089300 *ent;
    int *cnt;
    int *base;
    int h;
    int idx;
    int c256;
    int tile;
    int c0;
    int ty;
    int c1;
    int hw;
    int hh;
    int hw2;
    int hh2;
    int tx;
    Quad q;
    int x, y, w;
    u32 mode;
    u32 keep;
    int mosaic;
    int gfx;
    int a;
    int nx, ny;
    int pl;

    if (func_02088c14(a0)) {
        cnt = &data_021d2914;
        if (*cnt >= 0x80) {
            return 0;
        }
        ent = &data_021d2920[*cnt];
        base = &data_021d2910;
    } else {
        cnt = &data_021d291c;
        if (*cnt >= 0x80) {
            return 0;
        }
        ent = &data_021d2d20[*cnt];
        base = &data_021d2918;
    }

    x = s->x;
    if (x >= 0x100) {
        x -= 0x200;
    }
    y = *(signed char *) s;
    w = func_02088dd8(s);
    h = func_02088db8(s);

    if (rot != 0) {
        if (p9 != 0) {
            a = ((int) (u16) (short) rot >> 4) * 2;
            hw = w >> 1;
            hh = h >> 1;
            ty = y + hh;
            c0 = FX_SinCosTable_[a];
            x = x + hw;
            c1 = FX_SinCosTable_[a + 1];
            nx = FX_MulFunc(c1, x) - FX_MulFunc(c0, ty);
            ny = FX_MulFunc(c1, ty) + FX_MulFunc(c0, x);
            x = ((nx + (nx > 0 ? 0x800 : -0x800)) >> 12) - hw;
            y = ((ny + (ny > 0 ? 0x800 : -0x800)) >> 12) - hh;
        } else {
            hw2 = w >> 1;
            hh2 = h >> 1;
            a = ((int) (u16) (short) rot >> 4) * 2;
            c0 = FX_SinCosTable_[a];
            c1 = FX_SinCosTable_[a + 1];
            ty = y + hh2;
            tx = x + hw2;
            x = ((tx * c1 - ty * c0) >> 12) - hw2;
            y = ((ty * c1 + tx * c0) >> 12) - hh2;
        }
    }

    if (scale != 0x1000 || rot != 0) {
        if (s->mode != 1) {
            x = x - (w >> 1);
            y = y - (h >> 1);
            w = w << 1;
            h = h << 1;
        }
    }

    x += px;
    y += py;

    if (rot != 0) {
        if (w < h) {
            w = h;
        }
        if (x + w < 0 || x > 0x100) {
            return 0;
        }
        if (y + w < 0 || y > 0xc0) {
            return 0;
        }
    } else {
        if (x + w < 0 || x > 0x100) {
            return 0;
        }
        if (y + h < 0 || y > 0xc0) {
            return 0;
        }
    }

    if (pal == -1) {
        pal = s->pal;
    }
    if (prio == -1) {
        prio = s->prio;
    }

    if (scale != 0x1000 || rot != 0) {
        a = (rot >> 4) * 2;
        q.a = ((int) ((u32) FX_SinCosTable_[a + 1] * uid(scale) + 0x800u)) >> 12;
        c0 = FX_SinCosTable_[a];
        q.b = ((int) ((u32) c0 * (u32) scale + 0x800u)) >> 12;
        q.c = -q.b;
        q.d = q.a;
        if ((((u32 *) s)[0] & 0x10000000) != 0) {
            q.a = -q.a;
            q.b = -q.b;
        }
        if ((((u32 *) s)[0] & 0x20000000) != 0) {
            q.c = -q.c;
            q.d = -q.d;
        }
        idx = func_02088c60(ent - *cnt, base, &q);
        if (idx == -1) {
            return 0;
        }
        if (s->mode == 1) {
            mode = 0x100;
        } else {
            mode = 0x300;
        }
    } else {
        idx = 0;
        mode = ((u32 *) s)[0] & 0x30000000;
    }

    tile = s->tile;
    c256 = s->c256;
    keep = ((u32 *) s)[0] & 0xc000c000;
    mosaic = s->mosaic;
    gfx = s->gfx;

    if (mode == 0x100 || mode == 0x300) {
        if (gfx == 3) {
            ent->unk_00 =
                mode | (((x & 0x1ff) << 16) | (keep | ((mosaic << 12) | ((gfx << 10) | (((u32) idx << 25) | (y & 0xff))))));
        } else {
            ent->unk_00 =
                mode | (((x & 0x1ff) << 16) |
                        (keep | ((mosaic << 12) | ((gfx << 10) | ((y & 0xff) | (((u32) idx << 25) | (c256 << 13)))))));
        }
    } else {
        if (gfx == 3) {
            ent->unk_00 = mode | (((x & 0x1ff) << 16) | (keep | ((mosaic << 12) | ((y & 0xff) | (gfx << 10)))));
        } else {
            ent->unk_00 =
                mode | (((x & 0x1ff) << 16) | (keep | ((mosaic << 12) | ((gfx << 10) | ((c256 << 13) | (y & 0xff))))));
        }
    }

    pl = (u32) pal << 12;
    tile |= (u32) prio << 10;
    ent->w2 = (u16) (pl | tile);
    *cnt = *cnt + 1;
    return ent;
}
