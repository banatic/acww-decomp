/* villager_talk_subjects_3: 10 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02023124 @ 0x02023124, 0xd8 bytes, Thumb
 * func_02023040 @ 0x02023040, 0xe4 bytes, Thumb
 * func_02023010 @ 0x02023010, 0x2e bytes, Thumb
 * func_02022f3c @ 0x02022f3c, 0xd4 bytes, Thumb
 * func_02022ee4 @ 0x02022ee4, 0x58 bytes, Thumb
 * func_02022e8c @ 0x02022e8c, 0x58 bytes, Thumb
 * func_02022e34 @ 0x02022e34, 0x58 bytes, Thumb
 * func_02022ddc @ 0x02022ddc, 0x58 bytes, Thumb
 * func_02022d84 @ 0x02022d84, 0x58 bytes, Thumb
 * func_02022d2c @ 0x02022d2c, 0x58 bytes, Thumb
 */

#include "types.h"

typedef struct UnkStruct_02023124 {
    char pad_00[0x830];
    int unk_830;
} UnkStruct_02023124;

typedef struct {
    int unk_00;
    unsigned char unk_04;
} Cfg;

typedef struct UnkStruct_02023124_2 {
    char pad_00[0x100];
    UnkStruct_02023124 *unk_100;
    char unk_104[0x1e];
    unsigned char unk_122;
} UnkStruct_02023124_2;

typedef struct {
    u8 unk_00;
    u8 unk_01;
    unsigned short unk_02;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    int unk_14;
} Agg;

struct UnkStruct_02023040 {
    u8 id;
    u8 unk_01;
    u8 unk_02;
};

struct Node {
    struct UnkStruct_02023040 *items;
    u8 cnt;
    u8 pad_05[3];
};

typedef struct UnkStruct_02022f3c {
    char pad_00[0x830];
    int unk_830;
} UnkStruct_02022f3c;

typedef struct UnkStruct_02022f3c_2 {
    char pad_00[0x100];
    UnkStruct_02022f3c *unk_100;
    char unk_104[0x1e];
    unsigned char unk_122;
} UnkStruct_02022f3c_2;

typedef struct {
    unsigned short unk_00;
    unsigned short pad_02;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    int unk_14;
} Agg_02022f3c;

struct UnkStruct_02022ee4 {
    unsigned int a;
    unsigned char b;
};

struct Data_020c8db0 {
    int unk_00;
    unsigned char unk_04;
};

struct UnkStruct_02022e34 {
    int a;
    unsigned char b;
};

struct UnkStruct_02022e34_2 {
    char pad_00[0x100];
    void *ptr;
};

typedef struct {
    char pad_00[0x830];
    unsigned int value;
} inner_t;

typedef struct {
    char pad_00[0x100];
    inner_t *ptr;
    char arr[30];
} outer_t;

typedef struct {
    char pad_00[0x100];
    void *ptr;
    char arr1[0x1e];
    char arr2;
} UnkStruct_02022d84;

typedef struct {
    int unk_00;
    unsigned char unk_04;
} UnkStruct_02022d84_2;

typedef struct UnkStruct_02022d2c {
    char pad_830[0x830];
    int value;
} UnkStruct_02022d2c;

typedef struct UnkStruct_02022d2c_2 {
    char pad_100[0x100];
    UnkStruct_02022d2c *inner;
} UnkStruct_02022d2c_2;

extern Cfg data_020c8b88;
extern int data_020d9f84;
extern void func_0209e474(void *p);
extern int func_0202d060(unsigned short *a, int *b, int *c, int *d, void *e);
extern int func_0202c9c0(int x);
extern void func_02015de4(UnkStruct_02023124_2 *self, unsigned short *a, int b, int c);
extern int func_02015dd4(UnkStruct_02023124_2 *self, int n, Agg *a, void *tbl, u8 *e);
extern int func_0208150c(int x);
extern int func_020036e8(int x);
extern u8 data_020d9f74[];
extern int func_0209a478(int);
extern Cfg data_020c8a20;
extern int func_0204fafc(int x);
extern int *func_0204fc3c(int a, int b);
extern int func_0202cb70(Agg_02022f3c *a, int *b, int *c, int *d, int *e);
extern int func_0202da38(void *, void *, void *, int, int, int, int scale, int, int);
extern struct UnkStruct_02022ee4 data_020c8dc0;
extern struct Data_020c8db0 data_020c8db0;
extern struct UnkStruct_02022e34 data_020c8b70;
extern struct {
    unsigned int val;
    unsigned char byte;
} data_020c8a10;
extern UnkStruct_02022d84_2 data_020c8a08;
extern struct {
    int a;
    unsigned char b;
} data_020c8d70;

int func_02023124(UnkStruct_02023124_2 *self)
{
    // DECLS
    int ret;
    Agg agg;
    // ENDDECLS

    ret = 0;
    agg.unk_04 = 0;
    agg.unk_08 = 0;
    agg.unk_0C = 5;
    agg.unk_02 = 0xfff1;
    agg.unk_10 = 0;
    agg.unk_14 = 0;
    func_0209e474(&agg.unk_04);
    if (func_0202d060(&agg.unk_02, &agg.unk_0C, &agg.unk_10, &agg.unk_14, &agg.unk_04) == 1) {
        if (agg.unk_0C >= 3) {
            ret = 1;
        }
        ret = ret * 3 + func_0202c9c0(agg.unk_10);
        func_02015de4(self, &agg.unk_02, 0, 7);
        if (agg.unk_14 >= 3) {
            agg.unk_14 = agg.unk_14 - 1;
        }
        agg.unk_00 = agg.unk_14;
        agg.unk_01 = 0;
        func_02015dd4(self, 3, &agg, &data_020d9f84, &agg.unk_01);
        func_0202da38((void *) self, (void *) self->unk_104, (void *) (&self->unk_122), 0x1e, func_020036e8(func_0208150c(self->unk_100->unk_830)), data_020c8b88.unk_00, data_020c8b88.unk_04, ret, 0);
        ret = 1;
    }
    return ret;
}

void func_02023040(void *p0, int kind, u16 *pid, int p3, struct Node **list, void *p5)
{
    int key;
    int res;
    struct Node **pp;
    struct Node *p;
    struct UnkStruct_02023040 *q;
    int j;
    unsigned int ok;
    int i;
    unsigned int id;
    int k;
    u8 buf[2];

    pp = list;
    res = (u8) kind;
    if (pp == 0) {
        goto done;
    }
    ok = 0;
    id = *pid;
    if (id >= 0x12e8 && id <= 0x131f) {
        ok = 1;
    }
    if (ok == 0) {
        goto done;
    }
    if (p3 > 1) {
        goto done;
    }
    if (id >= 0x12e8 && id <= 0x131f) {
        key = id - 0x12e8;
    } else {
        key = -1;
    }
    for (i = 0; i < 3; pp++, i++) {
        p = *pp;
        if (p == 0) {
            continue;
        }
        for (j = 0; j < 2; p++, j++) {
            q = p->items;
            if (q == 0) {
                continue;
            }
            for (k = 0; k < p->cnt; q++, k++) {
                if (q->id == key && func_0209a478(q->unk_02) <= 1) {
                    break;
                }
            }
            if (p->cnt < k) {
                break;
            }
        }
        if (j == 2) {
            break;
        }
    }
    if (i == 3) {
        res = 3;
    }
done:
    buf[0] = (u8) res;
    buf[1] = 0;
    func_02015dd4((UnkStruct_02023124_2 *) p0, (int) p5, (Agg *) (&buf[0]), data_020d9f74, &buf[1]);
}

int func_02023010(unsigned int v)
{
    int r = 0;
    switch (v) {
        case 0:
        case 2:
        case 4:
            r = 0;
            break;
        case 5:
        case 6:
            r = 1;
            break;
        case 1:
        case 3:
            r = 2;
            break;
    }
    return r;
}

int func_02022f3c(UnkStruct_02022f3c_2 *self)
{
    int ret;
    int *h;
    Agg_02022f3c agg;
    int t;
    ret = 0;
    agg.unk_04 = 0;
    agg.unk_08 = 0;
    agg.unk_0C = 5;
    agg.unk_00 = 0xfff1;
    agg.unk_10 = 0;
    agg.unk_14 = 0;
    func_0209e474(&agg.unk_04);
    t = ((u8 *) (&agg))[8];
    h = func_0204fc3c(t, func_0204fafc(((u8 *) (&agg))[7]));
    if (h != 0) {
        if (func_0202cb70(&agg, &agg.unk_0C, &agg.unk_10, &agg.unk_14, h) == 1) {
            ret = 0;
            if (agg.unk_0C >= 3) {
                ret = 1;
            }
            ret = (ret * 3) + func_02023010(agg.unk_10);
            func_02015de4((UnkStruct_02023124_2 *) self, (unsigned short *) (&agg), 0, 7);
            func_02023040((void *) self, agg.unk_14, (u16 *) (&agg), agg.unk_0C, (struct Node **) (*h), (void *) 1);
            func_0202da38((void *) self, (void *) self->unk_104, (void *) (&self->unk_122), 0x1e, func_020036e8(func_0208150c(self->unk_100->unk_830)), data_020c8a20.unk_00, data_020c8a20.unk_04, ret, 0);
            ret = 1;
        }
    }
    return ret;
}

int func_02022ee4(void *p)
{
    int A, B, D, E;
    unsigned char C;
    A = func_020036e8(func_0208150c(*(int *) (*(int *) ((char *) p + 0x100) + 0x830)));
    B = data_020c8dc0.a;
    C = data_020c8dc0.b;
    D = 0;
    E = 0;
    func_0202da38(p, (char *) p + 0x104, (char *) p + 0x122, 30, A, B, C, D, E);
    return 1;
}

int func_02022e8c(void *arg)
{
    int v1, v2, v3, v4, v5;

    v1 = func_020036e8((int) ((unsigned char *) (unsigned int) func_0208150c(*(int *) ((char *) *(int *) ((char *) arg + 0x100) + 0x830))));
    v2 = data_020c8db0.unk_00;
    v3 = data_020c8db0.unk_04;
    v4 = 0;
    v5 = 0;
    func_0202da38(arg, (char *) arg + 0x104, (char *) arg + 0x122, 0x1e, v1, v2, v3, v4, v5);
    return 1;
}

int func_02022e34(struct UnkStruct_02022e34_2 *o)
{
    int res;
    int d0;
    unsigned char d1;

    res = func_020036e8(func_0208150c(*(int *) ((char *) o->ptr + 0x830)));
    d0 = data_020c8b70.a;
    d1 = data_020c8b70.b;

    func_0202da38(o, (void *) ((char *) o + 0x104), (void *) ((char *) o + 0x122), 0x1e, res, d0, d1, 0, 0);

    return 1;
}

int func_02022ddc(outer_t *obj)
{
    func_0202da38(obj, obj->arr, obj->arr + 30, 30, func_020036e8(func_0208150c(obj->ptr->value)), data_020c8a10.val,
                  data_020c8a10.byte, 0, 0);
    return 1;
}

int func_02022d84(UnkStruct_02022d84 *a)
{
    func_0202da38(a, (void *) a->arr1, (void *) (&a->arr2), 0x1e, func_020036e8((int) ((unsigned char *) (unsigned int) func_0208150c(*(int *) ((char *) a->ptr + 0x830)))), data_020c8a08.unk_00, data_020c8a08.unk_04, 0, 0);
    return 1;
}

int func_02022d2c(UnkStruct_02022d2c_2 *param)
{
    func_0202da38((void *) param, (void *) ((char *) param + 0x104), (void *) ((char *) param + 0x122), 0x1e, func_020036e8(func_0208150c(param->inner->value)), data_020c8d70.a, data_020c8d70.b, 0, 0);
    return 1;
}
