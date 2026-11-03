/* sound_mark: 8 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_0221f0d0 @ 0x0221f0d0, 0x40 bytes, Thumb
 * func_ov003_0221f0b8 @ 0x0221f0b8, 0x18 bytes, Thumb
 * func_ov003_0221efec @ 0x0221efec, 0xca bytes, Thumb
 * func_ov003_0221efc4 @ 0x0221efc4, 0x28 bytes, Thumb
 * func_ov003_0221efc0 @ 0x0221efc0, 0x2 bytes, Thumb
 * func_ov003_0221efa4 @ 0x0221efa4, 0x1c bytes, Thumb
 * func_ov003_0221ef94 @ 0x0221ef94, 0xe bytes, Thumb
 * func_ov003_0221ef90 @ 0x0221ef90, 0x4 bytes, Thumb
 */

typedef struct {
    char pad_00[0x20];
    int unk_20;
    char pad_24[4];
} Elem; // sizeof == 0x28

typedef struct {
    Elem *data;
    unsigned int w;
    unsigned int h;
} Tbl;

typedef struct {
    int x, y, z;
} Vec3;

typedef struct {
    int kind;
    int unk_04;
    int unk_08;
} UnkStruct_0221efec;

struct Src {
    int a, b, c;
};

struct Dst {
    char flag;
    int a, b, c, count, value;
};

struct UnkStruct_0221efa4 {
    char unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    int unk_14;
};

extern Tbl *data_021c80bc;
extern int func_02037544(void *argument0);
extern int func_020ea990(void *v, void *pos);
extern void func_02037514(UnkStruct_0221efec *out, const unsigned char *c, int k);
extern int data_020ca0ec;

int func_ov003_0221efc4(struct Dst *dst, int idx, struct Src *src, int val);
void func_ov003_0221efa4(struct UnkStruct_0221efa4 *p);

int func_ov003_0221f0d0(int a, unsigned int x, unsigned int y)
{
    Tbl *t = data_021c80bc;
    Elem *e;
    if (t != 0) {
        if (x < t->w && y < t->h && t->data != 0) {
            e = &t->data[y * t->w + x];
        } else {
            e = 0;
        }
        if (e != 0) {
            return e->unk_20;
        }
    }
    return 0;
}

int func_ov003_0221f0b8(int argument0, unsigned int argument1, unsigned int argument2)
{
    int *p;
    p = (int *) func_ov003_0221f0d0(argument0, argument1, argument2);
    if (p != 0) {
        return p[4];
    }
    return 0;
}

void *func_ov003_0221efec(void *p, Vec3 *pos)
{
    int i, j;
    unsigned int k;
    void *c;
    unsigned int n;
    int gx, gz;
    int wz0, zi;
    int xj;
    volatile Vec3 base;
    UnkStruct_0221efec e;
    Vec3 v;
    UnkStruct_0221efec tmp;
    int d;

    func_ov003_0221efa4((struct UnkStruct_0221efa4 *) p);
    gx = pos->x >> 17;
    gz = pos->z >> 17;
    for (i = -1; i <= 1; i++) {
        for (j = -1; j <= 1; j++) {
            wz0 = (gz + i) << 17;
            zi = gz + i;
            xj = gx + j;
            base.x = xj << 17;
            base.z = wz0;
            c = (void *) func_ov003_0221f0b8((int) p, xj, zi);
            if (c != 0) {
                n = func_02037544(c);
                for (k = 0; k < n; k++) {
                    func_02037514(&tmp, c, k);
                    e = tmp;
                    switch (e.kind) {
                        case 5:
                        case 0xf:
                        case 0x11:
                        case 0x12:
                            v.x = base.x + e.unk_04;
                            v.y = 0;
                            v.z = base.z + e.unk_08;
                            d = func_020ea990(&v, pos);
                            func_ov003_0221efc4((struct Dst *) p, d, (struct Src *) (&v), e.kind);
                            break;
                    }
                }
            }
        }
    }
    return p;
}

int func_ov003_0221efc4(struct Dst *dst, int idx, struct Src *src, int val)
{
    if (idx < dst->count) {
        dst->a = src->a;
        dst->b = src->b;
        dst->c = src->c;
        dst->count = idx;
        dst->value = val;
        dst->flag = 1;
        return 1;
    }
    return 0;
}

void func_ov003_0221efc0(void *object) {}

void func_ov003_0221efa4(struct UnkStruct_0221efa4 *p)
{
    p->unk_00 = 0;
    p->unk_04 = 0;
    p->unk_08 = 0;
    p->unk_0C = 0;
    p->unk_14 = 0x11;
    p->unk_10 = data_020ca0ec * 8;
}

void *func_ov003_0221ef94(unsigned char *p)
{
    if (*p) {
        return p + 4;
    }
    return 0;
}

int func_ov003_0221ef90(int *p0)
{
    return p0[5];
}
