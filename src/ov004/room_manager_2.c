/* room_manager_2: 5 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0223c108 @ 0x0223c108, 0x2 bytes, Thumb
 * func_ov004_0223c080 @ 0x0223c080, 0x88 bytes, Thumb
 * func_ov004_0223bfe0 @ 0x0223bfe0, 0xa0 bytes, Thumb
 * func_ov004_0223bf40 @ 0x0223bf40, 0xa0 bytes, Thumb
 * func_ov004_0223bdac @ 0x0223bdac, 0x194 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_0223c080;

struct UnkStruct_0223c080_2 {
    struct UnkStruct_0223c080 *unk_00;
    unsigned int unk_04;
    unsigned int unk_08;
};

typedef struct {
    int x, y, z;
} Vec;

typedef struct {
    char pad_00[0x5c];
    Vec pos;
} Player;

typedef struct {
    char pad_00[0x7b8];
    Vec pos;
} UnkStruct_0223bfe0;

typedef struct {
    char pad_00[0x7b8];
    Vec pos;
} UnkStruct_0223bf40;

struct Vec3 {
    int x;
    int y;
    int z;
};

extern struct UnkStruct_0223c080_2 *data_021c80bc;
extern int func_02037e0c(struct UnkStruct_0223c080 *, int, int, u8);
extern int func_0204bcdc(int);
extern int func_0204bc64(int);
extern int func_0204bc7c(int);
extern void func_ov004_0223c62c(int, int, int, int, u8, int);
extern Player *func_020961a8(int);
extern void *func_ov004_0223ce84(void);
extern UnkStruct_0223bfe0 *func_ov004_0223cd58(void *, unsigned int);
extern int func_ov004_0221124c(UnkStruct_0223bfe0 *);
extern long long func_01ffd028(const Vec *, const Vec *);
extern unsigned int func_ov004_0223c130(void);
extern void *func_ov004_022168d8(UnkStruct_0223bfe0 *);
extern int data_ov004_022595d8;
extern int func_ov004_022111f0(UnkStruct_0223bf40 *);
extern void *func_ov004_022168e4(UnkStruct_0223bf40 *);
extern int func_ov004_022112c4(void *e);
extern void *func_ov004_02215d74(void *e);
extern void *func_ov004_0223b2cc(void);
extern int func_ov004_0223b28c(void);
extern int func_ov004_0223b2ac(void);
extern int func_ov004_0223b258(void);
extern int func_ov004_0223b2ec(void);
extern int func_02003e00(void *a);
extern void func_02003e10(void *a, int b);
extern void func_02003e20(void *a, int b, struct Vec3 *c);
extern u8 data_ov004_022595b8;
extern struct Vec3 data_021fbee8;

void func_ov004_0223c108(void *receiver) {}

static __inline int atleast(unsigned int x, unsigned int n)
{
    return x > n;
}

static __inline struct UnkStruct_0223c080 *get(void)
{
    struct UnkStruct_0223c080_2 *g = data_021c80bc;
    if (!atleast(g->unk_04, 0) || !atleast(g->unk_08, 0) || g->unk_00 == 0) {
        return 0;
    }
    return g->unk_00;
}

void func_ov004_0223c080(void *receiver)
{
    struct UnkStruct_0223c080 *q = get();
    u32 k;
    int i, j;
    for (k = 0; k < 2; k++) {
        for (i = 0; i < 0x10; i++) {
            for (j = 0; j < 0x10; j++) {
                int item = func_02037e0c(q, j, i, k);
                if (item != 0 && func_0204bcdc(item) != 0) {
                    int c = func_0204bc64(item);
                    int d = func_0204bc7c(item);
                    func_ov004_0223c62c(j, i, c, d, k, 0);
                }
            }
        }
    }
}

void func_ov004_0223bfe0(void *receiver)
{
    Player *pl = func_020961a8(4);
    if (pl != 0) {
        Vec me;
        int besti;
        unsigned int i;
        int best;
        int d;
        Vec *q;
        q = &pl->pos;
        me.x = q->x;
        me.y = q->y;
        me.z = q->z;
        i = 0;
        besti = -1;
        best = data_ov004_022595d8;
        for (; i < func_ov004_0223c130(); i++) {
            UnkStruct_0223bfe0 *o = func_ov004_0223cd58(func_ov004_0223ce84(), i);
            if (o != 0 && func_ov004_0221124c(o) != 0) {
                Vec p;
                Vec tmp = o->pos;
                p.x = tmp.x;
                p.y = tmp.y;
                p.z = tmp.z;
                d = (int) func_01ffd028(&p, &me);
                if (d < best) {
                    besti = i;
                    best = d;
                }
            }
        }
        if (besti != -1) {
            UnkStruct_0223bfe0 *o = func_ov004_0223cd58(func_ov004_0223ce84(), besti);
            if (o != 0) {
                func_ov004_022168d8(o);
            }
        }
    }
}

void func_ov004_0223bf40(void *receiver)
{
    Player *pl = func_020961a8(4);
    if (pl != 0) {
        Vec me;
        int besti;
        unsigned int i;
        int best;
        int d;
        Vec *q;
        q = &pl->pos;
        me.x = q->x;
        me.y = q->y;
        me.z = q->z;
        i = 0;
        besti = -1;
        best = data_ov004_022595d8;
        for (; i < func_ov004_0223c130(); i++) {
            UnkStruct_0223bf40 *o = (UnkStruct_0223bf40 *) func_ov004_0223cd58(func_ov004_0223ce84(), i);
            if (o != 0 && func_ov004_022111f0(o) != 0) {
                Vec p;
                Vec tmp = o->pos;
                p.x = tmp.x;
                p.y = tmp.y;
                p.z = tmp.z;
                d = (int) func_01ffd028(&p, &me);
                if (d < best) {
                    besti = i;
                    best = d;
                }
            }
        }
        if (besti != -1) {
            UnkStruct_0223bf40 *o = (UnkStruct_0223bf40 *) func_ov004_0223cd58(func_ov004_0223ce84(), besti);
            if (o != 0) {
                func_ov004_022168e4(o);
            }
        }
    }
}

void func_ov004_0223bdac(void *self)
{
    // DECLS
    int best;
    void *e;
    void *p;
    void *w;
    struct Vec3 *q;
    unsigned int i;
    unsigned int bi;
    int d;
    int n;
    // ENDDECLS
    struct Vec3 out;
    struct Vec3 base;
    struct Vec3 tmp;
    struct Vec3 c1;
    struct Vec3 c2;
    int flag;

    if (data_ov004_022595b8 == 0) {
        return;
    }
    flag = 1;
    out.x = data_021fbee8.x;
    out.y = data_021fbee8.y;
    out.z = data_021fbee8.z;
    p = (void *) func_020961a8(4);
    if (p != 0) {
        q = (struct Vec3 *) ((char *) p + 0x5c);
        base.x = q->x;
        base.y = q->y;
        base.z = q->z;
        bi = ~0;
        best = data_ov004_022595d8;
        for (i = 0; i < func_ov004_0223c130(); i++) {
            e = (void *) func_ov004_0223cd58(func_ov004_0223ce84(), i);
            if (e == 0) {
                continue;
            }
            if (func_ov004_022112c4(e) == 0) {
                continue;
            }
            c1 = *(struct Vec3 *) ((char *) e + 0x7b8);
            tmp.x = c1.x;
            tmp.y = c1.y;
            tmp.z = c1.z;
            d = (int) func_01ffd028((const Vec *) (&tmp), (const Vec *) (&base));
            if (d < best) {
                bi = i;
                best = d;
            }
        }
        if (bi != ~0) {
            e = (void *) func_ov004_0223cd58(func_ov004_0223ce84(), bi);
            if (e != 0) {
                func_ov004_02215d74(e);
                c2 = *(struct Vec3 *) ((char *) e + 0x7b8);
                out.x = c2.x;
                out.y = c2.y;
                out.z = c2.z;
                flag = 0;
            }
        }
    }
    w = func_ov004_0223b2cc();
    if (w != 0) {
        if (flag != 0) {
            if (*(u8 *) ((char *) self + 0x2a9) == 0 || *(u8 *) ((char *) self + 0x2a8) == 0) {
                func_02003e00(w);
                *(u8 *) ((char *) self + 0x2a8) = 1;
            }
            func_02003e20(w, func_ov004_0223b28c(), 0);
        } else {
            if (*(u8 *) ((char *) self + 0x2a9) != 0 || *(u8 *) ((char *) self + 0x2a8) == 0 ||
                *(int *) ((char *) self + 0x2ac) != func_ov004_0223b2ec()) {
                n = func_ov004_0223b28c() - 1;
                if (n < 0) {
                    n = 0;
                }
                if (func_ov004_0223b2ac() == 0 && n == 0 && func_ov004_0223b258() != 0) {
                    d = 1;
                } else {
                    d = 0;
                }
                func_02003e10(w, d);
                *(u8 *) ((char *) self + 0x2a8) = 1;
            }
            func_02003e20(w, func_ov004_0223b28c(), &out);
        }
    }
    *(u8 *) ((char *) self + 0x2a9) = (u8) flag;
    *(int *) ((char *) self + 0x2ac) = func_ov004_0223b2ec();
}
