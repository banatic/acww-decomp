/* field_collision_4: 15 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02033ccc @ 0x02033ccc, 0x20 bytes, Thumb
 * func_02033ca8 @ 0x02033ca8, 0x24 bytes, Thumb
 * func_02033c78 @ 0x02033c78, 0x30 bytes, Thumb
 * func_02033c48 @ 0x02033c48, 0x30 bytes, Thumb
 * func_02033c2c @ 0x02033c2c, 0x1c bytes, Thumb
 * func_02033a5c @ 0x02033a5c, 0x1d0 bytes, Thumb
 * func_02033a24 @ 0x02033a24, 0x38 bytes, Thumb
 * func_020339dc @ 0x020339dc, 0x48 bytes, Thumb
 * func_020339b8 @ 0x020339b8, 0x24 bytes, Thumb
 * func_0203394c @ 0x0203394c, 0x6c bytes, Thumb
 * func_0203392c @ 0x0203392c, 0x1e bytes, Thumb
 * func_020338f8 @ 0x020338f8, 0x32 bytes, Thumb
 * func_020338c4 @ 0x020338c4, 0x34 bytes, Thumb
 * func_02033894 @ 0x02033894, 0x30 bytes, Thumb
 * func_02033878 @ 0x02033878, 0x1c bytes, Thumb
 */

#include "types.h"

typedef struct {
    char pad_00[0xA00];
    int unk_A00;
} UnkStruct_02033c48;

typedef struct {
    int x, y, z;
} UnkStruct_02033a5c;

typedef struct {
    int unk_00, unk_04, unk_08, unk_0C;
    unsigned char unk_10, unk_11, unk_12, unk_13;
    unsigned char unk_14;
} UnkStruct_02033a5c_2;

typedef struct {
    char pad_00[0x15];
    unsigned char unk_15;
    char pad_16[0x1e - 0x16];
} UnkStruct_02033a5c_3;

typedef struct {
    char data[64];
} Entry;

typedef struct {
    Entry entries[40];
    volatile u32 count;
} Container;

typedef struct {
    void *ptr;
    char unk_04[8];
    char unk_0C[8];
    char unk_14[12];
    char unk_20[1];
} UnkStruct_020339dc;

typedef struct {
    void *unk_00;
    char pad_04[0x20 - 4];
    char unk_20;
} UnkStruct_020339b8;

struct UnkStruct_0203392c {
    int unk_00;
    int a;
    int b;
    int c;
    int d;
};

struct UnkStruct_020338f8 {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    int unk_14;
    int unk_18;
    int unk_1C;
    int unk_20;
    int unk_24;
    int unk_28;
    int unk_2C;
};

typedef struct {
    char pad_00[0x28];
    int unk_28;
    int unk_2C;
} UnkStruct_020338c4;

typedef struct {
    char pad_00[0x480];
    unsigned int unk_480;
} UnkStruct_02033894;

extern void func_0202ff00(void *);
extern void func_020342a4(void *);
extern void func_02034294(void *arg);
extern void func_0202fed4(void *arg);
extern unsigned char data_020da21c[];
extern void func_0203428c(int, int, int);
extern int func_0202fc18(int, int, int, int, int);
extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern UnkStruct_02033a5c_3 data_020c907c[];
extern int data_021c317c;
extern UnkStruct_02033a5c_2 *func_020342c0(void *a, int x, int y);
extern char data_020da1a4;
extern char data_020da210;
extern void func_0202f8fc(void *dst, int a, int b);
extern void func_0202f6dc(void *);
extern void func_02034280(int *, int *);
extern void func_0202f6ac(struct UnkStruct_020338f8 *, int *, int *, int *);

int func_02033a24(Container *obj, int a, int b, int c, int d, int e, int f);
int func_020338c4(UnkStruct_020338c4 *a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8);

void *func_02033ccc(void *obj)
{
    func_0202ff00(obj);
    func_020342a4((char *) obj + 0x38);
    *(void **) obj = ((char *) data_020da21c);
    return obj;
}

void *func_02033ca8(void *self)
{
    *(void **) self = (void *) data_020da21c;
    func_02034294((char *) self + 0x38);
    func_0202fed4(self);
    return self;
}

int func_02033c78(int a0, int a1, int a2, int a3, int arg5, int arg6, int arg7)
{
    func_0203428c(a0 + 0x38, arg6, arg7);
    func_0202fc18(a0, a1, a2, a3, arg5);
    return 1;
}

UnkStruct_02033c48 *func_02033c48(UnkStruct_02033c48 *ptr)
{
    __cxa_vec_ctor((void *) (ptr), 40, 64, (((void (*)(void *)) func_02033ccc)), (((void (*)(void *)) func_02033ca8)));
    ptr->unk_A00 = 0;
    return ptr;
}

int func_02033c2c(int a)
{
    __cxa_vec_cleanup((void *) (a), 0x28, 0x40, (((void (*)(void *)) func_02033ca8)));
    return a;
}

static inline void setv(UnkStruct_02033a5c *d, int x, int y, int z)
{
    d->x = x;
    d->y = y;
    d->z = z;
}

static inline void setv0(UnkStruct_02033a5c *d, UnkStruct_02033a5c *s, int y)
{
    d->x = s->x;
    d->y = y;
    d->z = s->z;
}

void func_02033a5c(void *a0, void *a1, int x0, int x1, int y0, int y1)
{
    UnkStruct_02033a5c v[17];
    int y;
    int f;
    int t;
    UnkStruct_02033a5c_2 *e;
    int x1a;
    int x0a;
    int x;
    int z1;
    int z0;
    int T;

    for (y = y0; y <= y1; y++) {
        x = x0;
        T = (y << 13) + 0x1000;
        for (; x <= x1; x++) {
            e = func_020342c0(a1, x, y);
            if (e == 0) {
                continue;
            }
            v[0].x = (x << 13) + 0x1000;
            v[0].y = 0;
            v[0].z = T;
            x1a = v[0].x + 0x1000;
            x0a = v[0].x - 0x1000;
            z1 = T + 0x1000;
            z0 = T - 0x1000;
            t = e->unk_14;
            if (t < 0x7c) {
                f = data_020c907c[t].unk_15;
            } else {
                f = 0;
            }
            if (f != 0) {
                setv(&v[1], x0a, e->unk_00, z0);
                setv(&v[2], x0a, e->unk_00, z1);
                setv(&v[3], x1a, e->unk_00, z1);
                setv(&v[4], x1a, e->unk_00, z0);
                func_02033a24((Container *) a0, (int) (&v[1]), (int) (&v[2]), (int) (&v[3]), (int) (&data_021c317c), e->unk_10,
                              0);
                func_02033a24((Container *) a0, (int) (&v[1]), (int) (&v[3]), (int) (&v[4]), (int) (&data_021c317c), e->unk_10,
                              0);
            } else {
                setv(&v[5], v[0].x, e->unk_00, T);
                setv(&v[6], x1a, e->unk_00, z0);
                setv(&v[7], x0a, e->unk_00, z0);
                func_02033a24((Container *) a0, (int) (&v[5]), (int) (&v[6]), (int) (&v[7]), (int) (&data_021c317c), e->unk_10,
                              0);
                setv0(&v[8], &v[0], e->unk_04);
                setv(&v[9], x0a, e->unk_04, z0);
                setv(&v[10], x0a, e->unk_04, z1);
                func_02033a24((Container *) a0, (int) (&v[8]), (int) (&v[9]), (int) (&v[10]), (int) (&data_021c317c),
                              e->unk_11, 0);
                setv0(&v[11], &v[0], e->unk_08);
                setv(&v[12], x0a, e->unk_08, z1);
                setv(&v[13], x1a, e->unk_08, z1);
                func_02033a24((Container *) a0, (int) (&v[11]), (int) (&v[12]), (int) (&v[13]), (int) (&data_021c317c),
                              e->unk_12, 0);
                setv0(&v[14], &v[0], e->unk_0C);
                setv(&v[15], x1a, e->unk_0C, z1);
                setv(&v[16], x1a, e->unk_0C, z0);
                func_02033a24((Container *) a0, (int) (&v[14]), (int) (&v[15]), (int) (&v[16]), (int) (&data_021c317c),
                              e->unk_13, 0);
            }
        }
    }
}

int func_02033a24(Container *obj, int a, int b, int c, int d, int e, int f)
{
    if (obj->count < 40) {
        u32 idx = obj->count;
        obj->count = idx + 1;
        return func_02033c78((int) (&obj->entries[idx]), a, b, c, d, e, f);
    }
    return 0;
}

void *func_020339dc(UnkStruct_020339dc *self)
{
    self->ptr = (void *) &data_020da1a4;
    func_0202f8fc(&self->unk_04, 0, 0);
    func_0202f8fc(&self->unk_0C, 0, 0);
    func_0202f8fc(&self->unk_14, 0, 0);
    func_020342a4(&self->unk_20);
    self->ptr = (void *) &data_020da210;
    return self;
}

UnkStruct_020339b8 *func_020339b8(UnkStruct_020339b8 *obj)
{
    obj->unk_00 = &data_020da210;
    func_02034294(&obj->unk_20);
    func_0202f6dc(obj);
    return obj;
}

int *func_0203394c(int *a, int b, int c, int d, int e, int f, int g, int h)
{
    *a = (int) ((int *) &data_020da1a4);
    func_0202f8fc((char *) a + 4, 0, 0);
    func_0202f8fc((char *) a + 0xc, 0, 0);
    func_0202f8fc((char *) a + 0x14, 0, 0);
    func_020342a4((char *) a + 0x20);
    *a = (int) ((int *) &data_020da210);
    func_020338c4((UnkStruct_020338c4 *) a, b, c, d, e, f, g, h);
    return a;
}

void func_0203392c(int param, struct UnkStruct_0203392c *p)
{
    int avg_x = (p->a + p->c) >> 1;
    int avg_y = (p->b + p->d) >> 1;
    func_0202f8fc((void *) param, avg_x, avg_y);
}

int func_020338f8(struct UnkStruct_020338f8 *a, struct UnkStruct_020338f8 *b)
{
    func_02034280(&a->unk_20, &b->unk_20);
    func_0202f6ac(a, &b->unk_04, &b->unk_0C, &b->unk_14);
    a->unk_28 = b->unk_28;
    a->unk_2C = b->unk_2C;
    return 1;
}

int func_020338c4(UnkStruct_020338c4 *a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8)
{
    func_0203428c((int) ((void *) ((char *) a1 + 0x20)), a7, a8);
    func_0202f6ac((struct UnkStruct_020338f8 *) a1, (int *) a2, (int *) a3, (int *) a4);
    a1->unk_28 = a6;
    a1->unk_2C = a5;
    return 1;
}

void *func_02033894(void *obj)
{
    __cxa_vec_ctor((void *) (obj), 0x18, 0x30, (((void (*)(void *))(void *(*) (void *) ) func_020339dc)),
                   (((void (*)(void *))(void *(*) (void *) ) func_020339b8)));
    ((UnkStruct_02033894 *) obj)->unk_480 = 0;
    return obj;
}

void *func_02033878(void *p)
{
    __cxa_vec_cleanup((void *) (p), 0x18, 0x30, (((void (*)(void *))(void *(*) (void *) ) func_020339b8)));
    return p;
}
