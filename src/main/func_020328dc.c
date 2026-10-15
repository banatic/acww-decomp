/* func_020328dc @ 0x020328dc, 0x110 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec;

typedef struct {
    u8 pad_00[0x28];
    Vec unk_28;
    u8 pad1[4];
} UnkStruct_020328dc;

typedef struct {
    u8 pad_00[4];
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    int unk_14;
    int unk_18;
    u8 pad1[4];
    u8 unk_20;
    u8 pad_21[0x2c - 0x21];
    int unk_2C;
} UnkStruct_020328dc_2;

typedef struct {
    UnkStruct_020328dc_2 items[24];
    int count;
} UnkStruct_020328dc_3;

typedef struct {
    u8 pad_00[4];
    Vec *unk_04;
    u8 unk_08[0x10];
    u8 unk_18;
    u8 pad1[3];
    u8 unk_1C[8];
    Vec unk_24;
    int unk_30;
    int unk_34;
} UnkStruct_020328dc_4;

extern void *func_0202feb4(UnkStruct_020328dc *, Vec *, Vec *, Vec *, Vec *);
extern int func_0202fb28(UnkStruct_020328dc *, void *);
extern int func_0202f9d0(UnkStruct_020328dc *, Vec *, void *, void *);
extern void func_02034280(void *, void *);
extern void func_0202fee0(UnkStruct_020328dc *);

static __inline void VecSet(Vec *v, int x, int y, int z)
{
    v->x = x;
    v->y = y;
    v->z = z;
}

void func_020328dc(UnkStruct_020328dc_4 *p, UnkStruct_020328dc_3 *q)
{
    Vec vv[7];
    UnkStruct_020328dc tri[2];
    UnkStruct_020328dc_2 *e;
    UnkStruct_020328dc *t;
    Vec *s;
    int n;

    p->unk_34 = q->count;
    for (e = q->items; e < q->items + p->unk_34; e++) {
        VecSet(&vv[1], e->unk_14, 0, e->unk_18);
        VecSet(&vv[2], e->unk_04, e->unk_2C, e->unk_08);
        VecSet(&vv[3], e->unk_04, -0x8000, e->unk_08);
        VecSet(&vv[4], e->unk_0C, -0x8000, e->unk_10);
        VecSet(&vv[5], e->unk_0C, e->unk_2C, e->unk_10);
        func_0202feb4(&tri[0], &vv[2], &vv[3], &vv[4], &vv[1]);
        func_0202feb4(&tri[1], &vv[2], &vv[4], &vv[5], &vv[1]);
        for (t = tri; t < tri + 2; t++) {
            if (func_0202fb28(t, p->unk_08) < 0) {
                continue;
            }
            n = (func_0202fb28(t, p->unk_04) >= 0);
            if (n) {
                continue;
            }
            if (!func_0202f9d0(t, &vv[0], p->unk_08, p->unk_04)) {
                continue;
            }
            VecSet(p->unk_04, vv[0].x, p->unk_04->y, vv[0].z);
            func_02034280(p->unk_1C, &e->unk_20);
            s = &t->unk_28;
            p->unk_24.x = s->x;
            p->unk_24.y = s->y;
            p->unk_24.z = s->z;
            p->unk_30 = e->unk_20;
            p->unk_18 = 1;
        }
        func_0202fee0(&tri[1]);
        func_0202fee0(&tri[0]);
    }
}
