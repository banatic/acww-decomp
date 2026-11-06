/* tile_event_5: 8 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_022226c8 @ 0x022226c8, 0xd0 bytes, Thumb
 * func_ov003_022225c4 @ 0x022225c4, 0x104 bytes, Thumb
 * func_ov003_02222598 @ 0x02222598, 0x2c bytes, Thumb
 * func_ov003_02222560 @ 0x02222560, 0x38 bytes, Thumb
 * func_ov003_0222250c @ 0x0222250c, 0x54 bytes, Thumb
 * func_ov003_022223bc @ 0x022223bc, 0x150 bytes, Thumb
 * func_ov003_02222360 @ 0x02222360, 0x5c bytes, Thumb
 * func_ov003_02222318 @ 0x02222318, 0x48 bytes, Thumb
 */

typedef struct {
    int x, y, z;
} Vec3;

typedef struct {
    char pad_00[8];
    unsigned short unk_08;
    char pad_0A[0x18 - 0xa];
    Vec3 unk_18;
    char pad_24[0x30 - 0x24];
    Vec3 unk_30;
    int unk_3C;
    char pad_40[0x44 - 0x40];
    int unk_44;
    char pad_48[0x4c - 0x48];
    short unk_4C;
    char pad_4E[0x60 - 0x4e];
    int unk_60;
} UnkStruct_022226c8;

typedef struct {
    int x, y;
} UnkStruct_022225c4;

typedef struct {
    unsigned short id;
} UnkStruct_022225c4_2;

typedef struct {
    char pad_00[0x18];
    int unk_18[6];
    int unk_30, unk_34, unk_38, unk_3C, unk_40, unk_44;
    char pad_48[0xa0 - 0x48];
    unsigned char a0;
    unsigned char a1;
} UnkStruct_022225c4_3;

typedef struct {
    char pad_00[0x3c];
    int unk_3C;
    char pad_40[4];
    int unk_44;
} UnkStruct_02222598;

typedef struct UnkStruct_02222560 {
    unsigned int a;
    unsigned int b;
} UnkStruct_02222560;

typedef struct UnkStruct_02222560_2 {
    char pad_00[0x18];
    char pad_18[0x30 - 0x18];
    unsigned int unk_30;
    unsigned int unk_34;
    unsigned int unk_38;
    unsigned int unk_3C;
    unsigned int unk_40;
    unsigned int unk_44;
    char pad_48[0xa0 - 0x48];
    unsigned char unk_A0;
    unsigned char unk_A1;
} UnkStruct_02222560_2;

typedef struct {
    int unk_00;
    int unk_04;
} OtherStruct;

typedef struct {
    char pad_00[8];
    unsigned short status;
    char pad_0A[14];
    int sub;
    char pad_1C[20];
    int v0;
    int v1;
    int v2;
    int v3;
    int v4;
    int v5;
} UnkStruct_0222250c;

typedef struct {
    int unk_00;
    char pad_04[6];
    unsigned short unk_0A;
    char pad_0C[0x10 - 0xc];
    int unk_10, unk_14;
    char pad_18[0x3c - 0x18];
    int unk_3C;
    int unk_40;
    int unk_44;
    char pad_48[0xa0 - 0x48];
    unsigned char a0;
} UnkStruct_022223bc;

typedef struct {
    int x, y;
} UnkStruct_02222360;

typedef struct {
    char pad_00[8];
    unsigned short unk_08;
    char pad_0A[0x32];
    int unk_3C, unk_40, unk_44;
    char pad_48[0x18];
    char sub[4];
} UnkStruct_02222360_2;

struct UnkStruct_02222318 {
    char pad_00[0x3c];
    int unk_3C;
    int unk_40;
    int unk_44;
    char pad_48[0x4e - 0x48];
    unsigned short unk_4E;
};

extern void VEC_Add(void *a, void *b, void *c);
extern int func_020044c0(void *p, int a, int b, int c);
extern void func_ov003_02222860(void *self);
extern void func_0204f794(void *, int, int);
extern UnkStruct_022225c4_2 *func_0204f5e0(void *, int, int, int, int, int);
extern int func_0204f294(void *, int, int);
extern int func_0204b3d0(UnkStruct_022225c4_2 *);
extern void func_02044a30(UnkStruct_022225c4_2 *, UnkStruct_022225c4 *, int, int);
extern void func_020449d4(UnkStruct_022225c4_2 *, UnkStruct_022225c4 *);
extern void func_020449ac(UnkStruct_022225c4 *);
extern void func_ov003_02224140(int, int, int, int);
extern int func_0204eda8(int, int, int);
extern int func_ov003_02221118(int a, unsigned short b, int *pair);
extern int data_ov003_02236c18[];
extern int data_ov003_02236c5c[];

void func_ov003_022226c8(UnkStruct_022226c8 *self)
{
    volatile unsigned short t;
    unsigned int ok;
    unsigned short lo, hi;

    self->unk_3C = self->unk_3C + 0x19a;
    if (self->unk_3C >= 0x1000) {
        self->unk_3C = 0x1000;
    }
    self->unk_44 = self->unk_3C;
    self->unk_30.y = self->unk_30.y - 0x400;
    VEC_Add(&self->unk_18, &self->unk_30, &self->unk_18);
    if (self->unk_18.y < 0) {
        ok = 0;
        self->unk_18.y = 0;
        if (self->unk_4C == 0) {
            self->unk_4C = 1;
            self->unk_30.x = (self->unk_30.x * 0x4cd) >> 12;
            self->unk_30.y = 0x600;
            self->unk_30.z = (self->unk_30.z * 0x4cd) >> 12;
            t = 0xfff1;
            t = self->unk_08;
            lo = t;
            hi = t;
            if (hi >= 0x1492 && lo <= 0x14fd) {
                ok = 1;
            }
            if (ok > 0) {
                func_020044c0(&self->unk_60, 0x70, 0x7f, 0);
            }
        } else {
            self->unk_4C = 2;
            self->unk_30.x = 0;
            self->unk_30.y = 0;
            self->unk_30.z = 0;
            func_ov003_02222860(self);
        }
    }
}

void func_ov003_022225c4(UnkStruct_022225c4_3 *self, UnkStruct_022225c4 *p, void *ctx, int flag)
{
    UnkStruct_022225c4_2 *e;
    int r;
    unsigned int ok;
    unsigned short v;
    int x, y, hx, hy;
    UnkStruct_022225c4 t1, t2, t3;

    func_0204f794(self->unk_18, p->x, p->y);
    self->unk_3C = 0;
    self->unk_40 = 0x1000;
    self->unk_44 = 0;
    self->unk_30 = 0;
    self->unk_34 = 0;
    self->unk_38 = 0;

    x = p->x;
    y = p->y;
    hx = x >> 4;
    hy = y >> 4;
    e = func_0204f5e0(ctx, hx, hy, x - (hx << 4), y - (hy << 4), 0);
    if (e != 0) {
        r = func_0204f294(ctx, p->x, p->y);
        if (func_0204b3d0(e) != 0) {
            t1.x = p->x;
            t1.y = p->y;
            func_02044a30(e, &t1, 0, 0);
        } else {
            ok = 0;
            v = e->id;
            if (v >= 0x21 && v <= 0x24) {
                ok = 1;
            }
            if (ok != 0 || (v >= 0x1f && v <= 0x20)) {
                t2.x = p->x;
                t2.y = p->y;
                func_020449d4(e, &t2);
            } else if (v == 0xe2) {
                t3.x = p->x;
                t3.y = p->y;
                func_020449ac(&t3);
            } else if (r != 0 || (v >= 0xd4 && v <= 0xda) || (v >= 0xdb && v <= 0xe1)) {
                if (flag != 0) {
                    self->a0 = 0;
                    self->a1 = 1;
                }
            }
        }
        if (func_0204f294(ctx, p->x, p->y) != 0) {
            func_ov003_02224140(p->x, p->y, 0xfff1, 0);
        }
    }
}

void func_ov003_02222598(UnkStruct_02222598 *self)
{
    self->unk_3C += 0x571;
    if (self->unk_3C >= 0x1000) {
        self->unk_3C = 0x1000;
        func_ov003_02222860(self);
    }
    self->unk_44 = self->unk_3C;
}

void func_ov003_02222560(UnkStruct_02222560_2 *self, UnkStruct_02222560 *src)
{
    func_0204f794((char *) self + 0x18, src->a, src->b);

    self->unk_3C = 0;
    self->unk_40 = 0x1000;
    self->unk_44 = 0;
    self->unk_30 = 0;
    self->unk_34 = 0;
    self->unk_38 = 0;

    self->unk_A0 = 0;
    self->unk_A1 = 1;
}

void func_ov003_0222250c(UnkStruct_0222250c *obj, OtherStruct *src, int arg2)
{
    func_0204f794(&obj->sub, src->unk_00, src->unk_04);
    if (func_0204eda8(arg2, src->unk_00, src->unk_04) == 0) {
        obj->status = 0xfc;
    } else {
        obj->status = 0xfd;
    }
    obj->v3 = 0x1000;
    obj->v4 = 0x1000;
    obj->v5 = 0x1000;
    obj->v0 = 0;
    obj->v1 = 0;
    obj->v2 = 0;
    func_ov003_02224140((int) ((void *) (src->unk_00)), (int) ((void *) (src->unk_04)),
                        (unsigned short) ((unsigned short) (0xfff1)), 0);
}

void func_ov003_022223bc(UnkStruct_022223bc *self)
{
    unsigned int h, g, f, e, d, c, b, a;
    unsigned short lo, hi;
    int pair[2];

    self->unk_3C = self->unk_3C - 0x154;
    if (self->unk_3C < 0) {
        volatile unsigned short t = 0xfff1;
        a = 0;
        self->unk_3C = 0;
        t = self->unk_0A;
        h = 1;
        g = 1;
        f = 1;
        e = 1;
        d = 1;
        c = 1;
        b = 1;
        lo = t;
        hi = t;
        if (hi <= 5) {
            a = 1;
        }
        if (a == 0) {
            if (!(lo >= 6 && lo <= 0xb)) {
                b = 0;
            }
        }
        if (b == 0) {
            if (!(lo >= 0xc && lo <= 0x11)) {
                c = 0;
            }
        }
        if (c == 0) {
            if (!((lo >= 0x12 && lo <= 0x19) || lo == 0x1c)) {
                d = 0;
            }
        }
        if (d == 0) {
            if (!((lo >= 0x8a && lo <= 0x8f) || (lo >= 0x90 && lo <= 0x95) || (lo >= 0x96 && lo <= 0x9b) ||
                  (lo >= 0x9c && lo <= 0xa3) || lo == 0xa5)) {
                e = 0;
            }
        }
        if (e == 0) {
            if (lo != 0x1a) {
                f = 0;
            }
        }
        if (f == 0) {
            if (lo != 0xa4) {
                g = 0;
            }
        }
        if (g == 0) {
            if (lo != 0x1d) {
                h = 0;
            }
        }
        if (h != 0 || (lo >= 0x26 && lo <= 0x2a) || (lo >= 0x5d && lo <= 0x61) || (lo >= 0x2f && lo <= 0x56) ||
            (lo >= 0x57 && lo <= 0x5b) || (lo >= 0x66 && lo <= 0x68) || lo == 0x69 || (lo >= 0x6a && lo <= 0x6c) ||
            lo == 0x6d || (lo >= 0xc8 && lo <= 0xcf) || (lo >= 0xd4 && lo <= 0xda)) {
            pair[0] = self->unk_10;
            pair[1] = self->unk_14;
            if (func_ov003_02221118(self->unk_00, self->unk_0A, pair) != 0) {
                self->a0 = 0;
                func_ov003_02222860((void *) self);
            }
        } else {
            func_ov003_02222860((void *) self);
        }
    }
    self->unk_44 = self->unk_3C;
}

void func_ov003_02222360(UnkStruct_02222360_2 *self, UnkStruct_02222360 *p)
{
    unsigned int ok;
    int id;
    unsigned short a, b;
    volatile unsigned short v[8];

    func_0204f794((char *) self + 0x18, p->x, p->y);
    ok = 0;
    self->unk_3C = 0;
    self->unk_40 = 0;
    self->unk_44 = 0;
    id = 0x813;
    v[0] = 0xfff1;
    v[0] = self->unk_08;
    a = v[0];
    b = v[0];
    if (b >= 0xa7 && a <= 0xc6) {
        ok = 1;
    }
    if (ok > 0) {
        id = 0x7f0;
    }
    func_020044c0((char *) self + 0x60, id, 0x7f, 0);
}

void func_ov003_02222318(struct UnkStruct_02222318 *p)
{
    if (p->unk_4E >= 16) {
        p->unk_4E = 16;
        func_ov003_02222860(p);
    }
    p->unk_3C = data_ov003_02236c18[p->unk_4E];
    p->unk_44 = p->unk_3C;
    p->unk_40 = data_ov003_02236c5c[p->unk_4E];
}
