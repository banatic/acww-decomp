/* collision_visitor_2: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02032a54 @ 0x02032a54, 0x54 bytes, Thumb
 * func_020329ec @ 0x020329ec, 0x66 bytes, Thumb
 * func_020328dc @ 0x020328dc, 0x110 bytes, Thumb
 * func_02032844 @ 0x02032844, 0x98 bytes, Thumb
 * func_02032788 @ 0x02032788, 0xbc bytes, Thumb
 */

#include "types.h"

struct Elem {
    unsigned char pad_00[8];
    int unk_08;
    unsigned char pad_0C[0x38 - 0xc];
    unsigned char unk_38;
    unsigned char pad_39[0x40 - 0x39];
};

struct UnkStruct_02032a54_2 {
    unsigned char pad_00[4];
    int cmpVal;
};

struct UnkStruct_02032a54 {
    unsigned char pad_00[4];
    int flags;
    int val;
};

struct UnkStruct_02032a54_3 {
    unsigned char pad_00[4];
    struct UnkStruct_02032a54 *c;
    struct UnkStruct_02032a54_2 *b;
};

struct UnkStruct_020329ec;

struct UnkStruct_020329ec {
    unsigned int unk_00;
    unsigned int unk_04;
    unsigned int unk_08;
};

struct UnkStruct_020329ec_2 {
    unsigned int unk_00;
    struct UnkStruct_020329ec *unk_04;
    unsigned int unk_08;
    unsigned int sub;
    unsigned int unk_10;
    unsigned int unk_14;
    unsigned int unk_18;
    unsigned int unk_1C;
    unsigned int unk_20;
    unsigned int flags;
};

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

typedef struct Output {
    char pad_00[4];
    unsigned int *unk_04;
    char *unk_08;
    char pad1[12];
    unsigned char flag18;
    char pad2[3];
    void *unk_1C;
    char pad_20[4];
    unsigned int unk_24;
    unsigned int unk_28;
    unsigned int unk_2C;
    unsigned int unk_30;
    char pad_34[4];
    unsigned int count38;
} Output;

typedef struct InputElem {
    char pad_00[0x28];
    unsigned int unk_28;
    unsigned int unk_2C;
    unsigned int unk_30;
    char pad1[4];
    unsigned char flag38;
    char pad2[7];
} InputElem;

typedef struct Vec3 {
    int x, y, z;
} Vec3;

typedef struct Elem_02032788 {
    int unk_00;
    int unk_04;
    int unk_08;
    char pad0[8];
    unsigned char unk_14;
    char pad1[0xf];
} Elem_02032788;

typedef struct UnkStruct_02032788 {
    char pad0[4];
    Vec3 *unk_04;
    Vec3 unk_08;
    char pad1[4];
    unsigned char unk_18;
    char pad_19[3];
    void *unk_1C;
    char pad_20[4];
    int unk_24;
    int unk_28;
    int unk_2C;
    int unk_30;
    char pad_34[8];
    int unk_3C;
} UnkStruct_02032788;

extern int func_0202fb8c(void *src, unsigned int size);
extern int func_02031c50(void);
extern int func_02032eb8(void *q, unsigned int a, unsigned int *sub, unsigned int *out, unsigned int b, int c);
extern int func_02032f0c(void *q, unsigned int a, unsigned int b, struct UnkStruct_020329ec *arg3, unsigned int c, int d);
extern void *func_0202feb4(UnkStruct_020328dc *, Vec *, Vec *, Vec *, Vec *);
extern int func_0202fb28(UnkStruct_020328dc *, void *);
extern int func_0202f9d0(UnkStruct_020328dc *, Vec *, void *, void *);
extern void func_02034280(void *, void *);
extern void func_0202fee0(UnkStruct_020328dc *);
extern Vec3 data_021c317c;
extern int func_020304d4(Elem_02032788 *e, Vec3 *b, Vec3 *c);
extern int func_02030324(Elem_02032788 *e, Vec3 *b, Vec3 *c);
extern int func_020ea838(Vec3 *v);

void func_02032a54(struct UnkStruct_02032a54_3 *self, struct Elem *list)
{
    volatile unsigned char scratch[8];
    int count;
    struct Elem *end;
    int mask;
    struct Elem *e;

    (void) &scratch;
    count = *(int *) ((char *) list + 0xa00);
    end = (struct Elem *) ((char *) list + (count << 6));
    mask = 1;

    for (e = list; e < end; e = (struct Elem *) ((char *) e + 0x40)) {
        if (self->b->cmpVal < e->unk_08) {
            if (func_0202fb8c(e, (unsigned int) self->b)) {
                self->b->cmpVal = e->unk_08;
                self->c->flags |= mask;
                self->c->val = e->unk_38;
            }
        }
    }
}

void func_020329ec(struct UnkStruct_020329ec_2 *p, void *q)
{
    unsigned int local;

    if (p->flags & 1) {
        if (func_02032eb8(q, p->unk_08, &p->sub, &local, p->unk_20, func_02031c50())) {
            p->unk_04->unk_04 |= 1;
            p->unk_04->unk_08 = local;
        }
    }

    if (p->flags & 6) {
        func_02032f0c(q, p->unk_08, p->unk_1C, p->unk_04, p->unk_20, func_02031c50());
    }
}

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

void func_02032844(Output *out, InputElem *in)
{
    unsigned int local[3];
    InputElem *ptr;
    int ok;
    unsigned int *dst;
    unsigned int *src;

    out->count38 = *(unsigned int *) ((char *) in + 0xa00);

    for (ptr = in; ptr < (InputElem *) ((char *) in + (out->count38 << 6)); ptr++) {
        if (func_0202fb28((UnkStruct_020328dc *) ptr, &out->unk_08) < 0) {
            continue;
        }

        ok = (func_0202fb28((UnkStruct_020328dc *) ptr, out->unk_04) >= 0) ? 1 : 0;
        if (ok != 0) {
            continue;
        }

        if (func_0202f9d0((UnkStruct_020328dc *) ptr, (Vec *) local, &out->unk_08, out->unk_04) == 0) {
            continue;
        }

        dst = out->unk_04;
        dst[0] = local[0];
        dst[1] = local[1];
        dst[2] = local[2];

        func_02034280(&out->unk_1C, &ptr->flag38);

        src = &ptr->unk_28;
        out->unk_24 = src[0];
        out->unk_28 = src[1];
        out->unk_2C = src[2];

        out->unk_30 = ptr->flag38;
        out->flag18 = 1;
    }
}

static __inline void VEC_Set(volatile Vec3 *p, int x, int y, int z)
{
    p->x = x;
    p->y = y;
    p->z = z;
}

void func_02032788(UnkStruct_02032788 *self, void *arg)
{
    volatile Vec3 tmp;
    Elem_02032788 *base;
    Elem_02032788 *p;

    self->unk_3C = *(int *) arg;
    base = (Elem_02032788 *) ((char *) arg + 4);
    for (p = base; p < base + self->unk_3C; p++) {
        VEC_Set(&tmp, self->unk_04->x, self->unk_04->y, self->unk_04->z);
        if (func_020304d4(p, *(Vec3 *volatile *) &self->unk_04, &self->unk_08) != 0) {
            func_02034280(&self->unk_1C, &p->unk_14);
            self->unk_24 = data_021c317c.x;
            self->unk_28 = data_021c317c.y;
            self->unk_2C = data_021c317c.z;
            self->unk_30 = p->unk_14;
            self->unk_18 = 1;
        }
        VEC_Set(&tmp, self->unk_04->x, self->unk_04->y, self->unk_04->z);
        if (func_02030324(p, *(Vec3 *volatile *) &self->unk_04, &self->unk_08) != 0) {
            func_02034280(&self->unk_1C, &p->unk_14);
            VEC_Set((Vec3 *) &self->unk_24, self->unk_04->x - p->unk_00, 0, self->unk_04->z - p->unk_08);
            func_020ea838((Vec3 *) &self->unk_24);
            self->unk_30 = p->unk_14;
            self->unk_18 = 1;
        }
    }
}
