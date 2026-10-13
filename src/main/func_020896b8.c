/* func_020896b8 @ 0x020896b8, 0x230 bytes, Thumb, module main
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

typedef struct UnkStruct_020896b8 {
    u32 unk_00;
    u16 w2;
    u16 w3;
} UnkStruct_020896b8;

extern int func_02088c14(int a);
extern int func_02088dd8(Spr *p);
extern int func_02088db8(Spr *p);
extern int func_02088c60(UnkStruct_020896b8 *a, void *b, int c);

extern int data_021d2914;
extern int data_021d291c;
extern int data_021d2910;
extern int data_021d2918;
extern UnkStruct_020896b8 data_021d2920[];
extern UnkStruct_020896b8 data_021d2d20[];

int func_020896b8(int a0, Spr *s, int px, int py, int pal, int prio, int aff)
{
    UnkStruct_020896b8 *ent;
    int *cnt;
    void *base;
    int idx;
    int c256;
    int tile;
    int x, y, w, h, mode, keep, mosaic, gfx, pl;

    if (func_02088c14(a0)) {
        cnt = &data_021d2914;
        if (*cnt >= 0x80) {
            return -1;
        }
        ent = &data_021d2920[*cnt];
        base = &data_021d2910;
    } else {
        cnt = &data_021d291c;
        if (*cnt >= 0x80) {
            return -1;
        }
        ent = &data_021d2d20[*cnt];
        base = &data_021d2918;
    }

    x = s->x;
    if (x >= 0x100) {
        x -= 0x200;
    }
    x += px;
    y = *(char *) s + py;
    w = func_02088dd8(s);
    h = func_02088db8(s);
    if (aff != 0 && s->mode != 1) {
        x -= w >> 1;
        y -= h >> 1;
        w <<= 1;
        h <<= 1;
    }
    if (x + w < 0 || x > 0x100) {
        return -2;
    }
    if (y + h < 0 || y > 0xc0) {
        return -3;
    }

    if (pal == -1) {
        pal = s->pal;
    }
    if (prio == -1) {
        prio = s->prio;
    }

    if (aff != 0) {
        idx = func_02088c60(ent - *cnt, base, aff);
        if (idx == -1) {
            return -4;
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
                mode | (((x & 0x1ff) << 16) | (keep | ((mosaic << 12) | ((gfx << 10) | ((idx << 25) | (y & 0xff))))));
        } else {
            ent->unk_00 = mode | (((x & 0x1ff) << 16) |
                                  (keep | ((mosaic << 12) | ((gfx << 10) | ((y & 0xff) | ((idx << 25) | (c256 << 13)))))));
        }
    } else {
        if (gfx == 3) {
            ent->unk_00 = mode | (((x & 0x1ff) << 16) | (keep | ((mosaic << 12) | ((y & 0xff) | (gfx << 10)))));
        } else {
            ent->unk_00 =
                mode | (((x & 0x1ff) << 16) | (keep | ((mosaic << 12) | ((gfx << 10) | ((c256 << 13) | (y & 0xff))))));
        }
    }

    pl = pal << 12;
    tile |= prio << 10;
    ent->w2 = (u16) (pl | tile);
    (*cnt)++;
    return 1;
}
