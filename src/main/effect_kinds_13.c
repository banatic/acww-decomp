/* effect_kinds_13: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02094a4c @ 0x02094a4c, 0x10c bytes, Thumb
 * func_0209493c @ 0x0209493c, 0x110 bytes, Thumb
 * func_020948b8 @ 0x020948b8, 0x84 bytes, Thumb
 * func_02094884 @ 0x02094884, 0x34 bytes, Thumb
 */

#include "types.h"

typedef struct {
    int x;
    int y;
    int z;
} Vec;

typedef struct Node {
    struct Node *next;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    u8 unk_14[0x24 - 0x14];
    u16 unk_24;
    u16 unk_26;
    u8 unk_28[0x38 - 0x28];
    int unk_38;
    int unk_3C;
    int unk_40;
} Node;

typedef struct {
    u8 unk_00[0x30];
    int unk_30;
    u8 unk_34[0x3c - 0x34];
    int unk_3C;
} UnkStruct_02094a4c;

typedef struct {
    Node *pad_00;
    int d1;
    Node *unk_08;
} Head;

struct Vec {
    int x, y, z;
};

struct Node_0209493c {
    struct Node_0209493c *next;
    u8 pad_04[4];
    int x, y, z;
    u8 pad_14[0x10];
    u16 unk_24;
    u16 unk_26;
    u8 pad_28[0x10];
    int dx, dy, dz;
};

struct Head {
    u8 pad_00[8];
    struct Node_0209493c *list;
};

struct Iter {
    u8 pad_00[0x30];
    int flag;
    u8 pad_34[0x10];
};

typedef struct Key {
    unsigned char b[4];
} Key;

typedef struct Entry {
    unsigned char pad_00[14];
    short s;
    int pad_10;
    int unk_14;
    int unk_18;
} Entry;

typedef struct UnkStruct_020948b8 {
    int pad_00;
    int pad_04;
    int pad_08;
    int unk_0C;
} UnkStruct_020948b8;

typedef struct UnkStruct_020948b8_2 {
    int pad_00;
    Key key;
    int pad_08;
    UnkStruct_020948b8 *inner;
} UnkStruct_020948b8_2;

typedef struct {
    u32 a;
    u32 b;
    u32 c;
} UnkStruct_02094884_2;

typedef struct {
    u32 x;
    u32 y;
    u32 z;
} Mid;

typedef struct {
    u16 p;
    u16 q;
    u16 r;
} Tail;

typedef struct {
    u32 head;
    UnkStruct_02094884_2 inner;
    Mid mid;
    Tail tail;
} UnkStruct_02094884;

extern Vec data_021fbee8;
extern int func_02034270(UnkStruct_02094a4c *, Vec *, int, int);
extern void func_0203423c(UnkStruct_02094a4c *);
extern int func_02094cf8(int, int, Vec *, int, int, int);
extern int func_0203419c(struct Iter *);
extern Entry data_021d52d8[];
extern void func_020914dc(void *e);
extern u32 data_021d5658[3];

int func_02094a4c(Head *h, int p1, int p2, int p3, int p4, int p5, int p6, int p7, int p8)
{
    int ret;
    Vec v;
    UnkStruct_02094a4c ctx;
    Node *n;

    n = h->unk_08;
    v.x = data_021fbee8.x;
    v.y = data_021fbee8.y;
    v.z = data_021fbee8.z;
    ret = 0;
    while (n) {
        ret = 1;
        v.x = n->unk_08 + n->unk_38;
        v.y = n->unk_0C + n->unk_3C;
        v.z = n->unk_10 + n->unk_40;
        func_02034270(&ctx, &v, 0, 0);
        if (ctx.unk_30) {
            if (v.y <= ctx.unk_3C) {
                v.y = ctx.unk_3C;
                if (p1 != -1) {
                    func_02094cf8(p1, 0x64, &v, 0, 0, p2);
                }
                if (p3 != -1) {
                    func_02094cf8(p3, 0x64, &v, 0, 0, p4);
                }
                n->unk_26 = n->unk_24;
            }
        } else {
            if (v.y <= 0) {
                if (p5 != -1) {
                    v.y = 0;
                    func_02094cf8(p5, 0x64, &v, 0, 0, p6);
                }
                if (p7 != -1) {
                    v.y = 0;
                    func_02094cf8(p7, 0x64, &v, 0, 0, p8);
                }
                n->unk_26 = n->unk_24;
            }
        }
        n = n->next;
        func_0203423c(&ctx);
    }
    return ret;
}

int func_0209493c(struct Head *h, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8)
{
    struct Node_0209493c *n;
    int ret;
    struct Vec v;
    struct Iter it;
    int t;

    n = h->list;
    v.x = (*(struct Vec *) &data_021fbee8).x;
    v.y = (*(struct Vec *) &data_021fbee8).y;
    v.z = (*(struct Vec *) &data_021fbee8).z;
    ret = 0;
    if (n) {
        ret = 1;
        while (n) {
            v.x = n->x + n->dx;
            v.y = n->y + n->dy;
            v.z = n->z + n->dz;
            func_02034270((UnkStruct_02094a4c *) (&it), (Vec *) (&v), 0, 0);
            if (it.flag) {
                t = func_0203419c(&it);
                if (v.y <= t) {
                    v.y = t;
                    if (a1 != -1) {
                        func_02094cf8(a1, 0x64, (Vec *) (&v), 0, 0, a2);
                    }
                    if (a3 != -1) {
                        func_02094cf8(a3, 0x64, (Vec *) (&v), 0, 0, a4);
                    }
                    n->unk_26 = n->unk_24;
                }
            } else {
                if (v.y <= 0) {
                    if (a5 != -1) {
                        v.y = 0;
                        func_02094cf8(a5, 0x64, (Vec *) (&v), 0, 0, a6);
                    }
                    if (a7 != -1) {
                        v.y = 0;
                        func_02094cf8(a7, 0x64, (Vec *) (&v), 0, 0, a8);
                    }
                    n->unk_26 = n->unk_24;
                }
            }
            n = n->next;
            func_0203423c((UnkStruct_02094a4c *) (&it));
        }
    }
    return ret;
}

int func_020948b8(UnkStruct_020948b8_2 *obj, int a, int b, int c, int d, int e, int f, int g, int h)
{
    Key tmp;
    int result;
    int saved_c = c;
    Entry *cur;

    tmp = obj->key;
    cur = &data_021d52d8[tmp.b[0]];
    result = 0;
    if (cur->unk_14 == (-1)) {
        goto end;
    }
    if (cur->s == (-1)) {
        if (obj->inner->unk_0C > 0) {
            cur->s = 0;
        }
        result = 1;
    }
    if (cur->s != 0) {
        goto end;
    }
    result = func_02094a4c((Head *) obj->inner, a, b, saved_c, d, e, f, g, h);
end:
    if (result == 0) {
        func_020914dc(cur);
    }

    return result;
}

/* FAKEMATCH: storing each triple's first member through self and the rest through a member pointer gives the base-register stores; plain field stores and a struct copy change the size */
void func_02094884(UnkStruct_02094884 *self)
{
    u32 *ptr;
    ptr = data_021d5658;
    {
        UnkStruct_02094884_2 *ip = &self->inner;
        if (ptr) {
            self->inner.a = ptr[0];
            ip->b = ptr[1];
            ip->c = ptr[2];
        } else {
            self->inner.a = data_021d5658[0];
            ip->b = data_021d5658[1];
            ip->c = data_021d5658[2];
        }
    }
    {
        Mid *mp = &self->mid;
        self->mid.x = 0x1000;
        mp->y = 0x1000;
        mp->z = 0x1000;
    }
    {
        Tail *tp = &self->tail;
        self->tail.p = 0;
        tp->q = 0;
        tp->r = 0;
    }
}
