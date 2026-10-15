/* func_02045770 @ 0x02045770, 0x19c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

/* FAKEMATCH: the empty if keeps the x/z copies loaded before the bb.sub pointer is formed; without it the stores are scheduled differently */

#include "types.h"

typedef struct {
    int x;
    int z;
} Pt;
typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    u16 unk_10;
    u16 unk_12;
    int x;
    int z;
    u8 unk_1C;
    u8 unk_1D;
    s8 unk_1E;
    u8 unk_1F;
    int unk_20;
} UnkStruct_02045770;
typedef struct {
    u8 a0 : 2;
    u8 a2 : 2;
    u8 a4 : 2;
    u8 a6 : 2;
    u8 b0 : 5;
    u8 b5 : 2;
    u8 b7 : 1;
    u8 z;
    u8 x;
    u16 tile;
    u16 unk_06;
} UnkStruct_02045770_2;
typedef struct {
    u8 z;
    u8 x;
} UnkStruct_02045770_4;
typedef struct {
    u8 h[2];
    UnkStruct_02045770_4 sub;
    u8 pad[16];
} UnkStruct_02045770_3;
typedef struct {
    u8 pad[0x64];
    int unk_64;
} UnkStruct_02045770_5;
extern void *data_021c80bc;
extern UnkStruct_02045770 data_021c7c48[];
extern UnkStruct_02045770_5 *data_020ccf94;
extern u16 *func_0204f5e0(void *ctx, int cx, int cz, int dx, int dz, int layer);
extern int func_020459f0(int idx, Pt *p);
extern int func_02073d90(UnkStruct_02045770_5 *o);
extern int func_020a7278(void);
extern void func_0204510c(UnkStruct_02045770_2 *w, int a, int b);
extern void func_02073820(UnkStruct_02045770_5 *o);
extern void func_020737f0(UnkStruct_02045770_5 *o, UnkStruct_02045770_2 *w, int n);
extern void func_02073770(UnkStruct_02045770_5 *o, int a, int b);
extern int func_0204590c(UnkStruct_02045770_2 *w, UnkStruct_02045770 *s);
extern int func_02046024(int a, Pt *b, int c, int d, u8 p5, u8 p6, u8 p7, u8 p8, u8 p9, s8 p10);
extern int func_02045380(UnkStruct_02045770_3 *b, UnkStruct_02045770_2 *w, int c);
void func_02045770(u8 idx, int p1)
{
    UnkStruct_02045770_2 w;
    Pt pt;
    Pt pt2;
    UnkStruct_02045770_3 bb;
    void *ctx;
    UnkStruct_02045770 *s;
    u16 *e;
    int x;
    int z;
    int cx;
    int cz;
    UnkStruct_02045770_5 *obj;
    UnkStruct_02045770_4 *q;
    s8 sb;
    ctx = data_021c80bc;
    s = &data_021c7c48[idx];
    if (ctx == 0) {
        s->unk_08 = 3;
        return;
    }
    x = s->x;
    z = s->z;
    cx = x >> 4;
    cz = z >> 4;
    e = func_0204f5e0(ctx, cx, cz, x - (cx << 4), z - (cz << 4), 0);
    if (e == 0) {
        s->unk_08 = 3;
        return;
    }
    pt.x = x;
    pt.z = z;
    if (func_020459f0(idx, &pt) == 0) {
        s->unk_08 = 3;
        return;
    }
    w.a0 = s->unk_00;
    w.a2 = idx;
    w.a4 = s->unk_1D;
    w.b0 = s->unk_0C;
    w.x = x;
    w.z = z;
    w.tile = *e;
    w.unk_06 = s->unk_10;
    w.b5 = p1;
    w.b7 = s->unk_1C;
    obj = data_020ccf94;
    if (func_02073d90(obj) != 0) {
        if (func_020a7278() != 0) {
            func_0204510c(&w, 1, obj->unk_64);
            return;
        }
        obj = data_020ccf94;
        func_02073820(obj);
        func_020737f0(obj, &w, 8);
        func_02073770(obj, 0x31, 6);
        return;
    }
    s->unk_08 = 2;
    if (func_0204590c(&w, s) != 0) {
        return;
    }
    sb = s->unk_1E;
    pt2.x = s->x;
    pt2.z = s->z;
    if (func_02046024(0, &pt2, w.unk_06, w.tile, w.b0, w.a4, w.b5, 4, w.b7, sb) == 0) {
        s->unk_08 = 3;
        return;
    }
    {
        int bx = s->x;
        int bz = s->z;
        if ((!idx) && (!idx)) {
        }
        q = &bb.sub;
        q->x = bx;
        q->z = bz;
    }
    func_02045380(&bb, &w, 0);
}
