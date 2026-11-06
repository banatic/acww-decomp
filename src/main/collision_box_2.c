/* collision_box_2: 15 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020325b8 @ 0x020325b8, 0x58 bytes, Thumb
 * func_02032564 @ 0x02032564, 0x54 bytes, Thumb
 * func_02032550 @ 0x02032550, 0x14 bytes, Thumb
 * func_020324fc @ 0x020324fc, 0x54 bytes, Thumb
 * func_020324c4 @ 0x020324c4, 0x38 bytes, Thumb
 * func_0203248c @ 0x0203248c, 0x38 bytes, Thumb
 * func_02032444 @ 0x02032444, 0x48 bytes, Thumb
 * func_02032440 @ 0x02032440, 0x2 bytes, Thumb
 * func_0203243c @ 0x0203243c, 0x2 bytes, Thumb
 * func_02032438 @ 0x02032438, 0x2 bytes, Thumb
 * func_0203242c @ 0x0203242c, 0xc bytes, Thumb
 * func_02032214 @ 0x02032214, 0x218 bytes, Thumb
 * func_020321bc @ 0x020321bc, 0x58 bytes, Thumb
 * func_02032180 @ 0x02032180, 0x3c bytes, Thumb
 * func_020320e0 @ 0x020320e0, 0x9e bytes, Thumb
 */

typedef struct {
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
    short unk_28;
    short unk_2A;
    int unk_2C;
} UnkStruct_020325b8;

typedef struct {
    void *unk_00;
    char pad_04[0x2c];
    char unk_30[0x30];
    char unk_60[0x20];
} Func02032564Ctx;

typedef struct {
    unsigned int unk_00;
    char pad_04[0x30 - 0x4];
    char unk_30[0x30];
    char unk_60;
} UnkStruct_020324c4;

typedef struct {
    void *unk_00;
    unsigned char pad_04[0x2c];
    int unk_30;
    unsigned char pad_34[0x2c];
    int unk_60;
} UnkStruct_0203248c;

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
} SrcStruct;

typedef struct {
    unsigned char pad_00[4];
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    int unk_14;
    int unk_18;
    int unk_1C;
    int unk_20;
    int unk_24;
    short unk_28;
    unsigned char pad_2A[0x98 - 0x2a];
    char unk_98;
} UnkStruct_02032444;

typedef struct {
    int x, y, z;
} Vec3;

typedef struct {
    int a, b;
} Pair;

typedef struct UnkStruct_02032214 UnkStruct_02032214;

struct UnkStruct_02032214 {
    int unk_00;
    Vec3 unk_04;
    Vec3 unk_10;
    Vec3 unk_1C;
    short unk_28;
    short unk_2A;
    UnkStruct_02032214 *unk_2C;
    Vec3 unk_30[4];
    Pair unk_60[4];
    Vec3 unk_80;
    Vec3 unk_8C;
    char unk_98;
};

struct Node;

struct Node {
    unsigned char pad_00[0x2c];
    struct Node *next;
};

typedef struct UnkStruct_02032180 UnkStruct_02032180;

struct UnkStruct_02032180 {
    char pad_00[0x2c];
    UnkStruct_02032180 *next;
};

extern void func_0202f8fc(unsigned char *b, int a, int c);
extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));
extern void func_020012dc(void *);
extern void func_020012e8(void *);
extern void func_0202f2f0(void *);
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern unsigned char data_020da1b4[];
extern int data_021c30e4;
extern int data_021fbe48[];
extern int func_020eaa2c(Vec3 *a, Vec3 *b);
extern void func_020e96c8(void *m, int x, int y, int z);
extern void func_020e9744(void *m, int a);
extern void func_020e9838(void *m, int x, int y, int z);
extern void MTX_MultVec43(Vec3 *src, void *m, Vec3 *dst);
extern void func_02031e28(Vec3 *dst, Vec3 *src);
extern void func_02031e08(Vec3 *dst, Vec3 *src);
extern void func_0202f7cc(Pair *p, int a);
extern void func_020eaca0(int *r0, int *r1, int *r2);
extern void func_01ffd070(Vec3 *dst, void *mtx, Vec3 *src);

void *func_02032550(void *arg);
int func_02032214(UnkStruct_02032214 *self, Vec3 *src1, short d, Vec3 *src2);

void func_020325b8(UnkStruct_020325b8 *p)
{
    int *a;
    unsigned char *b;
    int i;
    i = 0;
    p->unk_2A = 0;
    p->unk_04 = 0;
    p->unk_08 = 0;
    p->unk_0C = 0;
    p->unk_10 = 0;
    p->unk_14 = 0;
    p->unk_18 = 0;
    p->unk_1C = 0x1000;
    p->unk_20 = 0x1000;
    p->unk_24 = 0x1000;
    p->unk_28 = 0;
    p->unk_2C = 0;
    *((unsigned char *) p + 0x98) = 0;
    a = (int *) ((unsigned char *) p + 0x30);
    b = (unsigned char *) p + 0x60;
    for (; i < 4; i++) {
        a[0] = 0;
        a[1] = 0;
        a[2] = 0;
        func_0202f8fc(b, 0, 0);
        a += 3;
        b += 8;
    }
}

Func02032564Ctx *func_02032564(Func02032564Ctx *p)
{
    p->unk_00 = ((char *) data_020da1b4);
    __cxa_vec_ctor((void *) (p->unk_30), 4, 12, (void (*)(void *)) func_020012e8, (void (*)(void *)) func_020012dc);
    __cxa_vec_ctor((void *) (p->unk_60), 4, 8, (((void (*)(void *)) func_02032550)), (void (*)(void *)) func_0202f2f0);
    func_020325b8((UnkStruct_020325b8 *) p);
    return p;
}

void *func_02032550(void *arg)
{
    int zero = 0;
    func_0202f8fc((unsigned char *) arg, zero, zero);
    return arg;
}

void *func_020324fc(void *self)
{
    *(void **) self = ((unsigned char *) data_020da1b4);
    __cxa_vec_ctor((void *) ((char *) self + 0x30), 4, 0xc, (void (*)(void *)) func_020012e8,
                   (void (*)(void *)) func_020012dc);
    __cxa_vec_ctor((void *) ((char *) self + 0x60), 4, 8, (((void (*)(void *)) func_02032550)),
                   (void (*)(void *)) func_0202f2f0);
    func_020325b8((UnkStruct_020325b8 *) self);
    return self;
}

UnkStruct_020324c4 *func_020324c4(UnkStruct_020324c4 *param)
{
    param->unk_00 = (unsigned int) data_020da1b4;
    __cxa_vec_cleanup((void *) (&param->unk_60), 4, 8, (void (*)(void *)) func_0202f2f0);
    __cxa_vec_cleanup((void *) (&param->unk_30), 4, 12, (void (*)(void *)) func_020012dc);
    return param;
}

UnkStruct_0203248c *func_0203248c(UnkStruct_0203248c *param)
{
    param->unk_00 = (void *) data_020da1b4;
    __cxa_vec_cleanup((void *) (&param->unk_60), 4, 8, (void (*)(void *)) func_0202f2f0);
    __cxa_vec_cleanup((void *) (&param->unk_30), 4, 0xc, (void (*)(void *)) func_020012dc);
    return param;
}

int func_02032444(UnkStruct_02032444 *out, int a, int b, int c, SrcStruct *src1, short d, SrcStruct *src2)
{
    out->unk_10 = a;
    out->unk_14 = b;
    out->unk_18 = c;
    func_02032214((UnkStruct_02032214 *) out, (Vec3 *) src1, d, (Vec3 *) src2);
    out->unk_04 = src1->unk_00;
    out->unk_08 = src1->unk_04;
    out->unk_0C = src1->unk_08;
    out->unk_1C = src2->unk_00;
    out->unk_20 = src2->unk_04;
    out->unk_24 = src2->unk_08;
    out->unk_28 = d;
    out->unk_98 = 1;
    return 1;
}

void func_02032440(void) {}

void func_0203243c(void *self) {}

void func_02032438(void *self) {}

void func_0203242c(void *object)
{
    data_021c30e4 = 0;
}

int func_02032214(UnkStruct_02032214 *self, Vec3 *src1, short d, Vec3 *src2)
{
    Vec3 corners[4];
    Vec3 mx, mn;
    Vec3 *p;
    Vec3 *w;
    Vec3 *e;
    Pair *q;
    int hx, hy, zz;
    int i, k;
    int cx, cy, cz, ex, ey, ez;

    if (d == self->unk_28 && func_020eaa2c(&self->unk_04, src1) == 0 && func_020eaa2c(&self->unk_1C, src2) == 0) {
        goto fail;
    }

    self->unk_04.x = src1->x;
    self->unk_04.y = src1->y;
    self->unk_04.z = src1->z;
    self->unk_1C.x = src2->x;
    self->unk_1C.y = src2->y;
    self->unk_1C.z = src2->z;
    self->unk_28 = d;

    hx = self->unk_10.x >> 1;
    hy = self->unk_10.y >> 1;
    zz = self->unk_10.z;

    w = &corners[0];
    w->x = -hx;
    w->y = zz;
    w->z = hy;
    w = &corners[1];
    w->x = hx;
    w->y = zz;
    w->z = hy;
    w = &corners[2];
    w->x = hx;
    w->y = zz;
    w->z = -hy;
    w = &corners[3];
    w->x = -hx;
    w->y = zz;
    w->z = -hy;

    func_020e96c8(data_021fbe48, src1->x, src1->y, src1->z);
    func_020e9744(data_021fbe48, d);
    func_020e9838(data_021fbe48, src2->x, src2->y, src2->z);

    p = &corners[0];
    e = &self->unk_30[0];
    q = &self->unk_60[0];

    if (self->unk_10.x == 0 || self->unk_10.y == 0) {
        k = 1;
        if (self->unk_10.y == 0) {
            k = 0;
        }
        self->unk_2A = 2;
        for (i = 0; i < 4; i++) {
            if ((i & 1) == k) {
                MTX_MultVec43(p, data_021fbe48, e);
                if (i == k) {
                    mx.x = e->x;
                    mx.y = e->y;
                    mx.z = e->z;
                    mn.x = e->x;
                    mn.y = e->y;
                    mn.z = e->z;
                } else {
                    func_02031e28(&mx, e);
                    func_02031e08(&mn, e);
                }
                func_0202f8fc((unsigned char *) q, 0, 0x1000);
                func_0202f7cc(q, (short) (d + (i << 14)));
                e++;
                q++;
            }
            p++;
        }
    } else {
        self->unk_2A = 4;
        for (i = 0; i < self->unk_2A; i++) {
            MTX_MultVec43(p, data_021fbe48, e);
            if (i == 0) {
                mx.x = e->x;
                mx.y = e->y;
                mx.z = e->z;
                mn.x = e->x;
                mn.y = e->y;
                mn.z = e->z;
            } else {
                func_02031e28(&mx, e);
                func_02031e08(&mn, e);
            }
            func_0202f8fc((unsigned char *) q, 0, 0x1000);
            func_0202f7cc(q, (short) (d + (i << 14)));
            e++;
            p++;
            q++;
        }
    }

    cz = (mx.z + mn.z) >> 1;
    cy = (mx.y + mn.y) >> 1;
    cx = (mx.x + mn.x) >> 1;
    self->unk_80.x = cx;
    self->unk_80.y = cy;
    self->unk_80.z = cz;
    ez = mx.z - self->unk_80.z;
    ey = mx.y - self->unk_80.y;
    ex = mx.x - self->unk_80.x;
    self->unk_8C.x = ex;
    self->unk_8C.y = ey;
    self->unk_8C.z = ez;
    return 1;
fail:
    return 0;
}

int func_020321bc(struct Node *obj, int a2, int a3, int a4, int a5, short a6, int *cfg)
{
    int local[3];
    int result;

    local[0] = 0x1000;
    local[1] = 0x1000;
    local[2] = 0x1000;

    if (cfg != 0) {
        local[0] = cfg[0];
        local[1] = cfg[1];
        local[2] = cfg[2];
    }

    result = func_02032444((UnkStruct_02032444 *) obj, a2, a3, a4, (SrcStruct *) a5, (int) a6, (SrcStruct *) local);

    if (result != 0) {
        obj->next = (*(struct Node **) &data_021c30e4);
        (*(struct Node **) &data_021c30e4) = obj;
        return 1;
    }
    return 0;
}

int func_02032180(UnkStruct_02032180 *target)
{
    UnkStruct_02032180 *cur = (*(UnkStruct_02032180 **) &data_021c30e4);
    UnkStruct_02032180 *prev = 0;
    while (cur != 0) {
        if (cur == target) {
            if (prev) {
                prev->next = cur->next;
            } else {
                (*(UnkStruct_02032180 **) &data_021c30e4) = cur->next;
            }
            func_020325b8((UnkStruct_020325b8 *) target);
            return 1;
        }
        prev = cur;
        cur = cur->next;
    }
    return 0;
}

int func_020320e0(Vec3 *p1, Vec3 *p2, Vec3 *p3, Vec3 *p4)
{
    Vec3 *arr[2];
    Vec3 v1;
    Vec3 v2;
    int mask;
    int i;

    arr[0] = p3;
    arr[1] = p4;
    func_020eaca0((int *) &v1, (int *) p1, (int *) p2);
    func_01ffd070(&v2, (void *) p1, p2);
    mask = 0xff;
    for (i = 0; i < 2; i++) {
        Vec3 *p = arr[i];
        int flags = 0;
        if (p->x < v1.x) {
            flags |= 1;
        } else if (p->x > v2.x) {
            flags |= 2;
        }
        if (p->z < v1.z) {
            flags |= 4;
        } else if (p->z > v2.z) {
            flags |= 8;
        }
        if (flags == 0) {
            return 0;
        }
        mask &= flags;
    }
    if (mask == 1) {
        return 1;
    }
    if (mask == 2) {
        return 1;
    }
    if (mask == 4) {
        return 1;
    }
    if (mask == 8) {
        return 1;
    }
    return 0;
}
