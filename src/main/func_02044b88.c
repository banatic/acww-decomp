/* func_02044b88 @ 0x02044b88, 0x13c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef union Col {
    struct {
        u16 r : 5;
        u16 g : 5;
        u16 b : 5;
        u16 a : 1;
    } unk_00;
    u16 v;
} Col;

typedef struct Vec {
    int x;
    int y;
    int z;
} Vec;

typedef struct Env {
    u32 unk_00;
    u8 unk_04;
    u8 unk_05;
    u8 unk_06;
    u8 unk_07;
    Vec vec;
    s16 unk_14;
} Env;

typedef struct UnkStruct_02044b88 {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
} UnkStruct_02044b88;

typedef struct UnkStruct_02044b88_2 {
    u8 pad_00[0x18];
    UnkStruct_02044b88 **unk_18;
    u8 pad_1C[4];
    int unk_20;
    int unk_24;
    int unk_28;
    u8 pad_2C[0x3c - 0x2c];
    u16 unk_3C;
    u16 unk_3E;
    u16 unk_40;
    u8 pad_42[0x5a - 0x42];
    u16 unk_5A;
} UnkStruct_02044b88_2;

extern Env data_021c77a0;
extern u16 *data_020db770[];
extern u16 *data_020db7a8[];

extern u16 func_020bbf00(int n);
extern void func_020ea6e0(Vec *v, int a);
extern int func_020ea838(Vec *v);

void func_02044b88(UnkStruct_02044b88_2 *p)
{
    Col c[4];
    Vec v;
    Env *g;
    Vec *q;
    int ty, tz;

    g = (Env *) &data_021c77a0;
    q = (Vec *) ((char *) g + 8);
    p->unk_20 = g->vec.x + (*p->unk_18)->unk_04;
    p->unk_24 = q->y + (*p->unk_18)->unk_08;
    p->unk_28 = q->z + (*p->unk_18)->unk_0C;

    c[0].v = func_020bbf00(3);
    c[3].v = c[0].v;
    c[1].v = c[3].v;

    if (g->unk_06 != 0) {
        c[2].v = *data_020db770[g->unk_04];
    } else {
        c[2].v = *data_020db7a8[g->unk_04];
    }

    c[1].unk_00.r = (u16) ((c[2].unk_00.r * c[1].unk_00.r) / 31);
    c[1].unk_00.g = (u16) ((c[2].unk_00.g * c[1].unk_00.g) / 31);
    c[1].unk_00.b = (u16) ((c[2].unk_00.b * c[1].unk_00.b) / 31);
    p->unk_5A = c[1].v;

    if (g->unk_00 == 2) {
        v.x = 0x400;
        v.y = 0x1000;
        v.z = 0;
        func_020ea6e0(&v, g->unk_14);
        if (func_020ea838(&v) != 0) {
            ty = v.y;
            tz = v.z;
            p->unk_3C = (u16) v.x;
            p->unk_3E = (u16) ty;
            p->unk_40 = (u16) tz;
        }
    }
}
