/* func_02044fe8 @ 0x02044fe8, 0x124 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

#pragma opt_loop_invariants off

typedef struct {
    int x;
    int z;
} Pt;

typedef struct {
    u8 f0 : 1;
    u8 f1 : 2;
    u8 kind : 5;
    u8 n0 : 3;
    u8 n3 : 2;
    u8 n5 : 2;
    u8 n7 : 1;
    u16 unk_02;
    u16 unk_04;
    u16 unk_06[3];
    u16 unk_0C;
} UnkStruct_02044fe8;

extern void *data_021c80bc;
extern u16 *func_0204f5e0(void *ctx, int cx, int cz, int dx, int dz, int layer);
extern void func_ov003_02221118(int a, int b, Pt *p);
extern int func_02045f24(int a, Pt *b, int c, int d, u8 p5, u8 p6, u8 p7, u8 p8, u8 p9, s8 p10);

void func_02044fe8(UnkStruct_02044fe8 *p)
{
    volatile u16 tmp;
    Pt pt0;
    Pt pt1;
    Pt pt2;
    int x, z;
    int cx, cz;
    void *ctx;
    u16 tile;
    int i;
    u16 wc;

    x = p->unk_02 >> 8;
    z = p->unk_02 & 0xff;
    switch (p->kind) {
        case 0xc:
        case 0xd:
        case 0xf:
        case 0x17:
            return;
        case 0x18:
        case 0x1a:
            pt0.x = x;
            pt0.z = z;
            func_ov003_02221118(p->f1, p->unk_04, &pt0);
            break;
    }
    tile = 0xfff1;
    ctx = data_021c80bc;
    if (ctx != 0) {
        cx = x >> 4;
        cz = z >> 4;
        tile = *func_0204f5e0(ctx, cx, cz, x - (cx << 4), z - (cz << 4), 0);
    }
    {
        u8 a9 = p->n7;
        u8 a7 = p->n5;
        u8 a6 = p->n3;
        u8 a5 = p->kind;
        pt1.x = x;
        pt1.z = z;
        func_02045f24(p->f1, &pt1, p->unk_04, tile, a5, a6, a7, 4, a9, -1);
    }
    if (p->f0 == 0) {
        return;
    }
    wc = p->unk_0C;
    for (i = 0; i < 3; i++) {
        u16 *w = (u16 *) ((int) p + 6);
        int xx = w[i] >> 8;
        int zz = w[i] & 0xff;
        tmp = p->unk_06[i];
        if (tmp != 0xffff) {
            u8 b9 = p->n7;
            pt2.x = xx;
            pt2.z = zz;
            func_02045f24(p->f1, &pt2, wc, 0xfff1, 0, 0, 0, (u8) i, b9, -1);
        }
    }
}
