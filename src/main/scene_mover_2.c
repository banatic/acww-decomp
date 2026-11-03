/* scene_mover_2: 19 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0201b324 @ 0x0201b324, 0x2c bytes, Thumb
 * func_0201b320 @ 0x0201b320, 0x2 bytes, Thumb
 * func_0201b2e0 @ 0x0201b2e0, 0x40 bytes, Thumb
 * func_0201b2d8 @ 0x0201b2d8, 0x8 bytes, Thumb
 * func_0201b268 @ 0x0201b268, 0x70 bytes, Thumb
 * func_0201b1a4 @ 0x0201b1a4, 0xc4 bytes, Thumb
 * func_0201b1a0 @ 0x0201b1a0, 0x4 bytes, Thumb
 * func_0201b188 @ 0x0201b188, 0x18 bytes, Thumb
 * func_0201b0bc @ 0x0201b0bc, 0xca bytes, Thumb
 * func_0201b078 @ 0x0201b078, 0x44 bytes, Thumb
 * func_0201b044 @ 0x0201b044, 0x32 bytes, Thumb
 * func_0201b040 @ 0x0201b040, 0x4 bytes, Thumb
 * func_0201aff8 @ 0x0201aff8, 0x46 bytes, Thumb
 * func_0201aff4 @ 0x0201aff4, 0x4 bytes, Thumb
 * func_0201afec @ 0x0201afec, 0x6 bytes, Thumb
 * func_0201afe4 @ 0x0201afe4, 0x6 bytes, Thumb
 * func_0201afd4 @ 0x0201afd4, 0xe bytes, Thumb
 * func_0201afd0 @ 0x0201afd0, 0x4 bytes, Thumb
 * func_0201afc0 @ 0x0201afc0, 0x10 bytes, Thumb
 */

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    char pad0[0x44 - 0x0c];
    char unk_44;
} UnkStruct_0201b268;

typedef struct {
    char pad0[0x5c];
    char unk_5C;
    char pad_5D[0x94 - 0x5d];
    short unk_94;
    char pad_96[0x98 - 0x96];
    int unk_98;
    char pad_9C[0x4cc - 0x9c];
    char unk_4CC;
} UnkStruct_0201b268_2;

typedef struct {
    int x, y, z;
} VecFx32;

typedef struct {
    int unk_00;
    short unk_04;
    unsigned char pad1[2];
    int unk_08;
    int unk_0C;
    unsigned char unk_10;
    unsigned char pad2[3];
} Rec;

typedef struct {
    int x, y, z;
    unsigned char pad1[0x30 - 0xc];
    int idx30;
    unsigned char pad2[0x36 - 0x34];
    short unk_36;
    unsigned char pad_38[0x50 - 0x38];
    int unk_50;
    unsigned char unk_54;
} SelfT;

typedef struct {
    char pad_00[0x34];
    unsigned short unk_34;
    char pad_36[0x0E];
    unsigned short unk_44;
} UnkStruct_0201b188;

typedef struct {
    char pad_00[0x5c];
    unsigned short unk_5C;
} UnkStruct_0201b188_2;

struct UnkStruct_0201b078 {
    char pad_00[0x34];
    short unk_34;
    short unk_36;
    char pad1[0x1D];
    unsigned char unk_55;
};

struct UnkStruct_0201b078_2 {
    char pad_00[0x8E];
    short unk_8E;
    char pad1[0x4];
    short unk_94;
};

struct Vec3 {
    int x, y, z;
};

struct Src {
    unsigned char pad_00[0x5c];
    struct Vec3 vec;
};

struct UnkStruct_0201aff8 {
    unsigned char pad_00[0x38];
    struct Vec3 unk_38;
    struct Vec3 unk_44;
    int threshold;
};

typedef struct {
    unsigned int a;
    unsigned int b;
    unsigned int c;
} Vec3;

typedef struct {
    unsigned char pad_00[0x44];
    Vec3 v;
} UnkStruct_0201afd4;

extern int data_020c81d8;
extern void MI_CpuCopy8(int, int, int);
extern int func_020e88dc(int *a, int b, int c);
extern int func_0200322c(void *a, void *b);
extern int func_020ea990(void *a, void *b);
extern void func_02003244(void *a, void *b);
extern Rec data_020c822c[];
extern int func_02016884(void *a, int b, void *c);
extern void func_020164ec(void *a, void *arg1, int b, unsigned short c, int d);
extern void func_02016764(void *a, void *arg1, int b, unsigned short c, int d, int e, int f, int g);
extern int func_020e8b4c(int a, int b);
extern int func_020eaa6c(void *param1, void *param2);
extern int func_020ea9e4(struct Vec3 *dst, struct Vec3 *src);
extern int func_020eaa2c(void *a, void *b);

void func_0201b268(UnkStruct_0201b268 *p, UnkStruct_0201b268_2 *q);
void func_0201afd4(UnkStruct_0201afd4 *dst, const Vec3 *src);

int func_0201b324(int *p0)
{
    p0[0] = 4096;
    p0[1] = 0;
    p0[2] = 0;
    p0[12] = 5;
    p0[14] = 0;
    p0[15] = 0;
    p0[16] = 0;
    p0[17] = 0;
    p0[18] = 0;
    p0[19] = 0;
    *(unsigned char *) ((char *) (((int) ((int) p0) + (84))) + (0)) = 0;
    *(unsigned char *) ((char *) (((int) ((int) p0) + (85))) + (0)) = 0;
    return (int) p0;
}

void func_0201b320(void *object) {}

void func_0201b2e0(int p0)
{
    *(int *) ((char *) (p0) + (0)) = 4096;
    *(int *) ((char *) (p0) + (4)) = 0;
    *(int *) ((char *) (p0) + (8)) = 0;
    *(int *) ((char *) (p0) + (48)) = 5;
    *(int *) ((char *) (p0) + (56)) = 0;
    *(int *) ((char *) (p0) + (60)) = 0;
    *(int *) ((char *) (p0) + (64)) = 0;
    *(int *) ((char *) (p0) + (68)) = 0;
    *(int *) ((char *) (p0) + (72)) = 0;
    *(int *) ((char *) (p0) + (76)) = 0;
    *(unsigned char *) ((char *) (((int) (p0) + (84))) + (0)) = 0;
    *(unsigned char *) ((char *) (((int) (p0) + (85))) + (0)) = 0;
    MI_CpuCopy8((int) &data_020c81d8, ((int) (p0) + (12)), 36);
}

void func_0201b2d8(void *argument0, void *argument1)
{
    func_0201b268((UnkStruct_0201b268 *) ((void *) argument0), (UnkStruct_0201b268_2 *) ((void *) argument1));
}

void func_0201b268(UnkStruct_0201b268 *p, UnkStruct_0201b268_2 *q)
{
    if (p->unk_00 == 0) {
        q->unk_98 = 0;
    } else {
        int r2 = (p->unk_04 < p->unk_00) ? (p->unk_04) : (p->unk_08);
        func_020e88dc(&q->unk_98, p->unk_00, r2);
        r2 = func_0200322c(&q->unk_5C, &p->unk_44);
        if (r2 == q->unk_94) {
            int tmp = func_020ea990(&p->unk_44, &q->unk_5C);
            if (tmp < q->unk_98) {
                q->unk_98 = tmp;
            }
        }
    }
    func_02003244(q, &q->unk_4CC);
}

void func_0201b1a4(SelfT *self, void *arg1, int idx, int flag4, unsigned short p5)
{
    Rec *rec;
    VecFx32 *arr;
    VecFx32 *q;

    if (idx < 0 || idx >= 5) {
        idx = 0;
    }

    rec = &data_020c822c[idx];

    arr = (VecFx32 *) ((char *) self + 0xc);
    q = &arr[rec->unk_08];
    self->x = arr[rec->unk_08].x;
    self->y = q->y;
    self->z = q->z;

    if (flag4 == 0) {
        self->unk_36 = rec->unk_04;
    } else {
        self->unk_36 = (short) flag4;
    }

    self->unk_50 = rec->unk_0C;

    if (idx != 4) {
        if ((self->unk_54 == 1 && rec->unk_10 == 1) ||
            func_02016884((char *) arg1 + 0x334, rec->unk_00, (char *) arg1 + 0x2a0)) {
            func_020164ec((char *) arg1 + 0x334, arg1, rec->unk_00, p5, 0);
        } else {
            func_02016764((char *) arg1 + 0x334, arg1, rec->unk_00, p5, 0, 0x1000, 0, 0);
        }
    }

    self->idx30 = idx;
    self->unk_54 = rec->unk_10;
}

int func_0201b1a0(int *p0)
{
    return p0[12];
}

void func_0201b188(UnkStruct_0201b188 *a, UnkStruct_0201b188_2 *b)
{
    a->unk_34 = (unsigned short) func_0200322c((void *) (&b->unk_5C), (void *) (&a->unk_44));
}

int func_0201b0bc(int unused, short *p, short target, short step, unsigned char mode)
{
    short d = step;
    int a;
    int ret;

    if (step < 0) {
        a = (short) -step;
    } else {
        a = step;
    }
    ret = 0;
    if (step != 0) {
        switch (mode) {
            case 1:
            case 2:
                if (func_020e8b4c(target, p[0]) <= a) {
                    short t = p[0] - target;
                    if (t > 0) {
                        d = -step;
                    }
                } else if (mode == 1) {
                    d = a;
                } else {
                    d = -a;
                }
                break;
            default: {
                short t = p[0] - target;
                if (t > 0) {
                    d = -step;
                }
                break;
            }
        }
        p[0] = p[0] + d;
        {
            int raw = p[0] - target;
            short ad = raw;
            short adz;
            if (ad < 0) {
                ad = -ad;
            }
            if (d < 0) {
                adz = -d;
            } else {
                adz = d;
            }
            if (ad <= adz) {
                if ((short) raw * d >= 0) {
                    p[0] = target;
                    ret = 1;
                }
            }
        }
    } else {
        if (p[0] == target) {
            ret = 1;
        }
    }
    return ret;
}

void func_0201b078(struct UnkStruct_0201b078 *a, struct UnkStruct_0201b078_2 *b)
{
    if (func_0201b1a0((int *) a) == 4) {
        b->unk_94 = a->unk_34;
    } else {
        func_0201b0bc((int) a, (short *) (&b->unk_94), a->unk_34, a->unk_36, a->unk_55);
        b->unk_8E = b->unk_94;
    }
}

void func_0201b044(void *param1, void *param2)
{
    int result;
    void *ptr1;
    void *ptr2;

    ptr1 = param1;
    ptr2 = param2;

    result = func_020eaa6c((char *) ptr1 + 0x38, (char *) ptr1 + 0x44);
    if (result != 0) {
        func_0201afd4((UnkStruct_0201afd4 *) ptr1, (const Vec3 *) ptr2);
    }

    *(int *) ((char *) ptr1 + 0x38) = *(int *) ptr2;
    *(int *) ((char *) ptr1 + 0x3c) = *(int *) ((char *) ptr2 + 4);
    *(int *) ((char *) ptr1 + 0x40) = *(int *) ((char *) ptr2 + 8);
}

int func_0201b040(int p0)
{
    return ((int) (p0) + (68));
}

int func_0201aff8(struct UnkStruct_0201aff8 *self, struct Src *src, int cond)
{
    int v[3];
    int result;
    int ret;
    struct Vec3 *srcv;

    srcv = &src->vec;
    v[0] = src->vec.x;
    v[1] = srcv->y;
    v[2] = srcv->z;
    v[1] = 0;
    result = 0;

    if (cond) {
        ret = func_020ea9e4((struct Vec3 *) v, &self->unk_38);
    } else {
        ret = func_020ea9e4((struct Vec3 *) v, &self->unk_44);
    }

    if (ret < self->threshold) {
        result = 1;
    }

    return result;
}

void func_0201aff4(unsigned short *p0, int p1)
{
    p0[26] = p1;
}

short func_0201afec(void *p)
{
    return *(short *) ((unsigned char *) p + 0x34);
}

short func_0201afe4(void *p)
{
    return *(short *) ((unsigned char *) p + 0x36);
}

void func_0201afd4(UnkStruct_0201afd4 *dst, const Vec3 *src)
{
    dst->v.a = src->a;
    dst->v.b = src->b;
    dst->v.c = src->c;
}

int func_0201afd0(int p0)
{
    return ((int) (p0) + (68));
}

int func_0201afc0(void *arg0)
{
    return func_020eaa2c((char *) arg0 + 0x38, (char *) arg0 + 0x44);
}
