/* growth_model: 19 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_022235d8 @ 0x022235d8, 0xa8 bytes, Thumb
 * func_ov003_02223580 @ 0x02223580, 0x58 bytes, Thumb
 * func_ov003_02223274 @ 0x02223274, 0x30c bytes, Thumb
 * func_ov003_02223208 @ 0x02223208, 0x6c bytes, Thumb
 * func_ov003_022231e8 @ 0x022231e8, 0x1e bytes, Thumb
 * func_ov003_022230a0 @ 0x022230a0, 0x148 bytes, Thumb
 * func_ov003_02223078 @ 0x02223078, 0x28 bytes, Thumb
 * func_ov003_02222f8c @ 0x02222f8c, 0xec bytes, Thumb
 * func_ov003_02222f0c @ 0x02222f0c, 0x80 bytes, Thumb
 * func_ov003_02222e24 @ 0x02222e24, 0xe8 bytes, Thumb
 * func_ov003_02222d8c @ 0x02222d8c, 0x96 bytes, Thumb
 * func_ov003_02222d68 @ 0x02222d68, 0x24 bytes, Thumb
 * func_ov003_02222cac @ 0x02222cac, 0xbc bytes, Thumb
 * func_ov003_02222c68 @ 0x02222c68, 0x44 bytes, Thumb
 * func_ov003_02222c34 @ 0x02222c34, 0x34 bytes, Thumb
 * func_ov003_02222bc0 @ 0x02222bc0, 0x74 bytes, Thumb
 * func_ov003_02222b78 @ 0x02222b78, 0x48 bytes, Thumb
 * func_ov003_02222b68 @ 0x02222b68, 0x10 bytes, Thumb
 * func_ov003_02222af0 @ 0x02222af0, 0x76 bytes, Thumb
 */

#include "types.h"

struct Vec {
    int x;
    int z;
};

struct UnkStruct_022235d8 {
    char pad_00[4];
    int unk_04;
    char pad_08[0xb0];
    unsigned char unk_B8;
    char pad_B9[0x13];
    int unk_CC;
    int unk_D0;
};

typedef struct {
    unsigned char pad_00[0x8];
    int unk_08;
    unsigned char pad_0C[0xD4 - 0x8 - 0x4];
    int unk_D4;
    unsigned char pad_D8[0xE0 - 0xD4 - 0x4];
    int unk_E0;
} UnkStruct_02223580;

typedef struct Node {
    u8 pad_00[0xd];
    u8 unk_0D;
} Node;

typedef struct UnkStruct_02223274_4 {
    int unk_00;
    int unk_04;
    int unk_08;
    u8 pad_0C[0x64 - 0x0c];
    void *unk_64;
    u8 pad_68[0xa4 - 0x68];
    int unk_A4;
    u8 pad_A8[4];
    unsigned int ac_lo : 12;
    unsigned int ac_val : 16;
    unsigned int ac_hi : 4;
    u8 pad_B0[8];
    u8 unk_B8;
    u8 pad_B9[7];
    int unk_C0;
    int unk_C4;
    int unk_C8;
    int unk_CC;
    int unk_D0;
    u32 unk_D4;
    int unk_D8;
    int unk_DC;
    int unk_E0;
    u8 pad_E4[0x144 - 0xe4];
    Node *unk_144;
    Node *unk_148;
} UnkStruct_02223274_4;

typedef struct UnkStruct_02223274 {
    int x;
    int y;
} UnkStruct_02223274;

typedef struct UnkStruct_02223274_2 {
    int x;
    int y;
    int z;
} UnkStruct_02223274_2;

typedef struct UnkStruct_02223274_3 {
    u8 pad_00[0x68];
    int unk_68;
} UnkStruct_02223274_3;

typedef struct {
    unsigned int data[12];
} Global48;

typedef struct {
    int unk_00;
    int pad_04;
    void *unk_08;
    char pad_0C[0x58];
    void *unk_64;
    char pad_68[4];
    Global48 unk_6C;
    char pad_9C[0x24];
    void *unk_C0;
} UnkStruct_02223208;

typedef struct {
    int unk_00;
    int unk_04;
    char pad_08[0xcc - 8];
    int x;
    int y;
    int mode;
    char pad_D8[0xe0 - 0xd8];
    char buf[1];
} UnkStruct_022230a0;

struct UnkStruct_02223078 {
    char pad_00[0x5c];
    int unk_5C;
};

typedef struct {
    int x, y, z;
} Vec3;

typedef struct {
    int a, b;
} Pair;

typedef struct {
    char pad_00[8];
    unsigned short unk_08;
} UnkStruct_02222f8c;

typedef struct {
    unsigned short unk_00;
} UnkStruct_02222f8c_2;

typedef struct {
    int x, y, z;
} Vec;

struct UnkStruct_02222f0c {
    int x, y;
};

struct UnkStruct_02222f0c_2 {
    Vec a, b, c, d;
};

typedef struct {
    char pad_00[8];
    unsigned short unk_08;
    unsigned short unk_0A;
} UnkStruct_02222e24;

typedef struct {
    unsigned short unk_00;
} UnkStruct_02222e24_2;

typedef struct {
    int x, y;
} UnkStruct_02222d8c;

typedef struct {
    unsigned char pad_00[4];
    unsigned int unk_04;
    unsigned char pad_08[0xcc - 8];
    unsigned int unk_CC;
    unsigned int unk_D0;
} UnkStruct_02222d68;

typedef struct {
    int a, b;
} UnkStruct_02222cac;

typedef struct {
    int unk_00;
    char pad_04[200];
    int unk_CC;
    int unk_D0;
    int pad_D4;
    int unk_D8;
    char pad_138[92];
    int arr_138[3];
    int unk_144;
    int unk_148;
} UnkStruct_02222c68;

struct UnkStruct_02222c34_2 {
    char pad_00[0x2c];
    void *unk_2C;
};

struct UnkStruct_02222c34 {
    unsigned char *unk_00;
    struct UnkStruct_02222c34_2 *unk_04;
    unsigned char pad_08[0xb0];
    int *unk_B8;
};

typedef struct {
    void *a[8][4];
} UnkStruct_02222b78;

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
} UnkStruct_02222af0;

extern char *data_ov003_0223cf70;
extern void *func_0204e414(void);
extern int func_02073d90(void *);
extern int func_0204b7a0(void *p);
extern struct UnkStruct_022235d8 *func_ov003_02223870(void *a, void *b, int c, int d);
extern int func_02055478(void *, void *);
extern int func_02055140(void *, void *);
extern void func_02055de0(void *, void (*)(void *), int, int, void *, int);
extern void func_0200451c(int *);
extern void *data_ov003_0223cf78;
extern int data_ov003_0223cfa0;
extern void func_02055124(int *);
extern int func_02056f94(int *);
extern int func_020044c0(int *, int, int, int);
extern void func_020044d0(int *, UnkStruct_02223274_2 *);
extern void func_0210744c(void *, int);
extern void func_02107494(void *, int);
extern int func_0204b5ac(u16 *);
extern Node *func_ov003_02223c7c(void *, u32, int, u16 *, UnkStruct_02223274 *, int);
extern Node *func_ov003_02223d14(void *, u32, int, u16 *, UnkStruct_02223274 *, int);
extern int func_0203f8d0(void *, void *);
extern void func_020e96c8(void *, int, int, int);
extern void func_020e9774(void *, int);
extern void func_0205510c(void *, int);
extern int func_02065604(void);
extern void NNS_G3dMdlSetMdlEmi(void *, int, unsigned short);
extern Global48 data_021fbe48;
extern int func_02055454(void *);
extern int func_020044a0(void *);
extern int func_0204f5e0(int, int, int, int, int, int);
extern int func_02045cec(int *, int);
extern void func_02045ea8(int *, int, int);
extern void *func_02044878(int);
extern struct UnkStruct_02223078 *func_020961a8(void *);
extern void func_0204f794(int *out, int a, int b);
extern int func_0204b710(void *self);
extern int func_02045bb8(unsigned char a, unsigned char b);
extern void *func_02045bac(int id);
extern void func_0204f818(int *a, int *b, void *v);
extern void func_ov003_022210d4(int p1, unsigned short h, void *pa, void *w, int a, int b);
extern Vec3 *data_ov003_02239f5c[3];
extern unsigned short data_ov003_02236688[];
extern void *func_020984e8(void);
extern int func_02099020(void *, int);
extern void func_01ffd070(void *, void *, void *);
extern void func_ov003_02221054(void *, int, void *, void *);
extern unsigned char data_020ccf94[];
extern void func_ov003_02221094(int p1, unsigned short h, void *pa, void *w, int a);
extern int func_0204b910(void *);
extern int func_02044540(void);
extern void func_02055060(void *, int, int, int, int, int);
extern void func_02055050(void *);
extern void *func_02064b2c(void *, void *, int, void *);
extern void *NNS_G3dGetJntAnmSet(void *);
extern void *func_02107b44(void *, void *);
extern void func_020e993c(void *, void *);
extern int data_ov003_0223bcc4[][4];
extern int func_02045c84(int, int *, int);

void func_ov003_02222d68(UnkStruct_02222d68 *obj, int arg2);
void func_ov003_02222c68(UnkStruct_02222c68 *self);
void func_ov003_02222c34(struct UnkStruct_02222c34 *p);
int func_ov003_02222b68(int unused, int row, int col);

void func_ov003_022235d8(int a0, struct Vec *v)
{
    void *ctx;
    void *obj;
    struct UnkStruct_022235d8 *p;
    int n;
    int cx;
    int cz;
    int x;
    int z;

    ctx = func_0204e414();
    if (ctx == 0) {
        return;
    }
    x = v->x;
    z = v->z;
    cx = x >> 4;
    cz = z >> 4;
    obj = (void *) func_0204f5e0((int) ctx, cx, cz, x - (cx << 4), z - (cz << 4), 0);
    if (obj == 0) {
        return;
    }
    if (func_02073d90((*(void **) data_020ccf94)) == 0) {
        a0 = 0;
    }
    n = func_0204b7a0(obj);
    if (n <= 0 || n > 4) {
        return;
    }
    p = func_ov003_02223870(data_ov003_0223cf70 + 0x4b20, obj, n - 1, (v->x ^ v->z) & 1);
    if (p == 0) {
        return;
    }
    if (v->x != p->unk_CC) {
        return;
    }
    if (v->z != p->unk_D0) {
        return;
    }
    if (a0 != p->unk_04) {
        return;
    }
    p->unk_B8 = 0;
}

void func_ov003_02223580(UnkStruct_02223580 *self)
{
    func_02055478(&self->unk_08, data_ov003_0223cf78);
    func_02055140(&self->unk_08, data_ov003_0223cf78);
    self->unk_D4 = 8;
    func_02055de0(&self->unk_08, (void (*)(void *)) func_ov003_02222c34, 2, 2, self, 0);
    func_0200451c(&self->unk_E0);
    func_ov003_02222c68((UnkStruct_02222c68 *) self);
}

void func_ov003_02223274(UnkStruct_02223274_4 *self)
{
    UnkStruct_02223274 a;
    UnkStruct_02223274 b;
    UnkStruct_02223274_2 c;
    int flag;
    int base;
    void *h;
    u16 *it;
    int n;
    int q0;
    int q1;
    int s0;
    int s1;

    if (self->unk_00 == 1) {
        func_02055124(&self->unk_08);
        if (func_02056f94(&self->unk_A4) != 0) {
            func_ov003_02222c68((UnkStruct_02222c68 *) self);
        } else {
            flag = 0;
            base = (*(UnkStruct_02223274_3 **) data_020ccf94)->unk_68;
            switch (self->unk_D4) {
                case 4:
                case 5:
                    if (self->ac_val >= 0x11) {
                        self->unk_D8 -= 0x2955;
                        if (self->unk_D8 < 0) {
                            self->unk_D8 = 0;
                        }
                    }
                    switch (self->unk_DC) {
                        case 0:
                            if (self->ac_val >= 4) {
                                flag = 1;
                            }
                            break;
                        case 1:
                            if (self->ac_val >= 0x14) {
                                flag = 1;
                                func_020044c0(&self->unk_E0, 0x7ea, 0x7f, 0);
                            }
                            break;
                    }
                    break;
                case 6:
                case 7:
                    if (self->ac_val >= 0x11) {
                        self->unk_D8 -= 0x2627;
                        if (self->unk_D8 < 0) {
                            self->unk_D8 = 0;
                        }
                    }
                    switch (self->unk_DC) {
                        case 0:
                            if (self->ac_val >= 4) {
                                flag = 1;
                            }
                            break;
                        case 1:
                            if (self->ac_val >= 0xd) {
                                flag = 1;
                                func_020044c0(&self->unk_E0, 0x7ea, 0x7f, 0);
                            }
                            break;
                    }
                    break;
                case 2:
                    if (self->unk_DC == 0 && self->ac_val >= 4) {
                        flag = 1;
                    } else {
                        if (self->unk_144 != 0) {
                            self->unk_144->unk_0D = 0x1a;
                        }
                        if (self->unk_148 != 0) {
                            self->unk_148->unk_0D = 0x1a;
                        }
                    }
                    break;
                case 0:
                    if (self->unk_DC == 0 && self->ac_val >= 4) {
                        flag = 1;
                    }
                    break;
                case 1:
                default:
                    if (self->unk_DC == 0 && self->ac_val >= 4) {
                        flag = 1;
                    }
                    break;
                case 3:
                    break;
            }

            func_0210744c(self->unk_64, self->unk_D8 >> 12);
            base += 0x33;
            func_02107494(self->unk_64, base);

            if (flag != 0) {
                h = func_0204e414();
                if (h != 0) {
                    q0 = self->unk_CC;
                    q1 = self->unk_D0;
                    s0 = q0 >> 4;
                    s1 = q1 >> 4;
                    it = (u16 *) func_0204f5e0((int) h, s0, s1, q0 - (s0 << 4), q1 - (s1 << 4), 0);
                    if (it != 0) {
                        int t3 = 1;
                        int t2 = 1;
                        int t1 = 1;
                        int t0 = 0;
                        unsigned int k;
                        k = *it;
                        if (k >= 0x2b && k <= 0x2e) {
                            t0 = 1;
                        }
                        if (t0 == 0 && !(k >= 0xff && k <= 0x102)) {
                            t1 = 0;
                        }
                        if (t1 == 0 && !(k >= 0x62 && k <= 0x65)) {
                            t2 = 0;
                        }
                        if (t2 == 0 && !(k >= 0xd0 && k <= 0xd3)) {
                            t3 = 0;
                        }
                        if (t3) {
                            n = func_0204b5ac(it);
                        } else {
                            n = func_0204b7a0((void *) it);
                        }
                        if (n > 0) {
                            a.x = self->unk_CC;
                            a.y = self->unk_D0;
                            self->unk_144 =
                                func_ov003_02223c7c(&data_ov003_0223cfa0, self->unk_D4, n - 1, it, &a, self->unk_DC);
                            b.x = self->unk_CC;
                            b.y = self->unk_D0;
                            self->unk_148 =
                                func_ov003_02223d14(&data_ov003_0223cfa0, self->unk_D4, n - 1, it, &b, self->unk_DC);
                            self->unk_DC++;
                        }
                    }
                }
            }
        }
        c.x = self->unk_C0;
        c.y = self->unk_C4;
        c.z = self->unk_C8;
        func_020044d0(&self->unk_E0, &c);
    }
    self->unk_B8 = 1;
}

void func_ov003_02223208(UnkStruct_02223208 *p)
{
    volatile unsigned short pair[2];
    struct {
        int a;
        int b;
        int c;
    } local;
    int ret1;

    if (p->unk_00 != 1) {
        return;
    }

    ret1 = func_0203f8d0(&local, &p->unk_C0);
    func_020e96c8(&data_021fbe48, local.a, local.b, local.c);
    func_020e9774(&data_021fbe48, ret1);
    p->unk_6C = data_021fbe48;
    func_0205510c(&p->unk_08, 0);
    pair[0] = (unsigned short) func_02065604();
    pair[1] = pair[0];
    NNS_G3dMdlSetMdlEmi(p->unk_64, 0, pair[1]);
}

void func_ov003_022231e8(void *p)
{
    func_ov003_02222c68((UnkStruct_02222c68 *) p);
    func_02055454((char *) p + 8);
    func_020044a0((char *) p + 0xe0);
}

void func_ov003_022230a0(UnkStruct_022230a0 *s, int flag)
{
    int h, r;
    int X, Y, ax, ay;
    int t1[2], t2[2], t3[2];

    h = (int) func_0204e414();
    X = s->x;
    Y = s->y;
    ax = X >> 4;
    ay = Y >> 4;
    r = func_0204f5e0(h, ax, ay, X - (ax << 4), Y - (ay << 4), 0);
    switch (s->mode) {
        case 1:
            break;
        case 2:
        case 3:
            t1[0] = s->x;
            t1[1] = s->y;
            if (func_02045cec(t1, 0) >= 0) {
                func_ov003_02222d68((UnkStruct_02222d68 *) s, r);
                t2[0] = s->x;
                t2[1] = s->y;
                func_02045ea8(t2, s->unk_04, 0);
            }
            break;
        default:
            func_ov003_02222d68((UnkStruct_02222d68 *) s, r);
            t3[0] = s->x;
            t3[1] = s->y;
            func_02045ea8(t3, s->unk_04, 0);
            break;
    }
    if (flag == 0) {
        switch (s->mode) {
            case 0:
            case 2:
            case 3:
                func_020044c0((int *) s->buf, 0x7dc, 0x7f, 0);
                break;
            case 1:
                func_020044c0((int *) s->buf, 0x7d9, 0x7f, 0);
                break;
        }
    } else {
        switch (s->mode) {
            case 4:
            case 5:
            case 6:
            case 7:
                func_020044c0((int *) s->buf, 0x855, 0x7f, 0);
                break;
            default:
                func_020044c0((int *) s->buf, 0x7dd, 0x7f, 0);
                break;
        }
    }
    s->unk_00 = 1;
}

int func_ov003_02223078(int a, int *b)
{
    int result = 0;
    struct UnkStruct_02223078 *obj;
    obj = func_020961a8(func_02044878(a));
    if (obj != 0) {
        if (obj->unk_5C < *b) {
            result = 1;
        }
    }
    return result;
}

void func_ov003_02222f8c(UnkStruct_02222f8c_2 *self, int p1, int *p2)
{
    Vec3 *e;
    int i, n;
    int flag;
    volatile unsigned short cc[3];
    Pair pa;
    Pair pa2;
    Vec3 out;
    Vec3 w;
    Vec3 w2;
    UnkStruct_02222f8c *r;
    unsigned short k;
    unsigned short h;
    unsigned short tv;
    int id;

    func_0204f794(&out.x, p2[0], p2[1]);
    h = self->unk_00;
    switch (h) {
        case 0xcc:
            e = data_ov003_02239f5c[2];
            n = 2;
            k = 0x1548;
            break;
        case 0x5b:
            e = data_ov003_02239f5c[0];
            n = 3;
            k = 0x14b8;
            break;
        default:
            e = data_ov003_02239f5c[0];
            n = 3;
            k = data_ov003_02236688[func_0204b710(self)];
            break;
    }
    pa.a = 0;
    pa.b = 0;
    for (i = 0; i < n; i++) {
        id = func_02045bb8((unsigned char) p1, (unsigned char) i);
        w.x = out.x + e->x;
        w.y = out.y + e->y;
        w.z = out.z + e->z;
        if (id >= 0) {
            r = (UnkStruct_02222f8c *) func_02045bac(id);
            cc[2] = r->unk_08;
            tv = cc[2];
            cc[1] = tv;
            cc[0] = tv;
            pa.a = cc[0] >> 8;
            pa.b = cc[1] & 0xff;
            flag = 0;
        } else {
            func_0204f818(&pa.a, &pa.b, &w);
            flag = 1;
        }
        w2.x = w.x;
        w2.y = w.y;
        w2.z = w.z;
        pa2.a = pa.a;
        pa2.b = pa.b;
        func_ov003_022210d4(p1, k, &pa2, &w2, flag, i);
        e++;
    }
}

void func_ov003_02222f0c(void *p0, struct UnkStruct_02222f0c *p1)
{
    int args[2];
    struct UnkStruct_02222f0c_2 t;
    Vec *tbl;
    Vec *e;
    if (func_02073d90(*(void **) data_020ccf94) != 0) {
        return;
    }
    if (func_02099020(func_020984e8(), 1) != 0) {
        return;
    }
    func_0204f794((int *) (&t.a), p1->x, p1->y);
    tbl = *(Vec **) ((unsigned char *) data_ov003_02239f5c);
    e = &tbl[func_ov003_02223078((int) p0, (int *) (&t.a))];
    func_01ffd070(&t.c, &t.a, e);
    t.b.x = t.c.x;
    t.b.y = t.c.y;
    t.b.z = t.c.z;
    t.d.x = t.c.x;
    t.d.y = t.c.y;
    t.d.z = t.c.z;
    args[0] = p1->x;
    args[1] = p1->y;
    func_ov003_02221054(p0, 0x1569, args, &t.d);
}

void func_ov003_02222e24(UnkStruct_02222e24_2 *self, int p1, int *p2)
{
    int id;
    int flag;
    volatile unsigned short cc[3];
    Pair pa;
    Pair pb;
    struct {
        Vec3 a;
        Vec3 b;
    } o;
    Vec3 wa;
    Vec3 wb;
    Vec3 *e;
    UnkStruct_02222e24 *r;
    unsigned int ok;
    unsigned short h;
    int h1, h2;
    unsigned short tv;

    id = func_02045bb8((unsigned char) p1, 0);
    if (id < 0) {
        return;
    }
    ok = 0;
    flag = 0;
    h = self->unk_00;
    if (h >= 0x66 && h <= 0x68) {
        ok = 1;
    }
    if (ok > 0) {
        e = data_ov003_02239f5c[0];
        if (h == 0x66) {
            flag = 1;
        }
    } else if (h >= 0x6a && h <= 0x6c) {
        e = data_ov003_02239f5c[1];
        if (h == 0x6a) {
            flag = 1;
        }
    }
    func_0204f794(&o.a.x, p2[0], p2[1]);
    e = e + func_ov003_02223078(p1, (int *) (&o.a));
    r = (UnkStruct_02222e24 *) func_02045bac(id);
    o.b.x = o.a.x + e->x;
    o.b.y = o.a.y + e->y;
    o.b.z = o.a.z + e->z;
    cc[2] = r->unk_08;
    tv = cc[2];
    cc[1] = tv;
    cc[0] = tv;
    h1 = cc[0] >> 8;
    h2 = cc[1] & 0xff;
    if (flag == 0) {
        wa.x = o.b.x;
        wa.y = o.b.y;
        wa.z = o.b.z;
        pa.a = h1;
        pa.b = h2;
        func_ov003_022210d4(p1, r->unk_0A, &pa, &wa, 0, 0);
    } else {
        wb.x = o.b.x;
        wb.y = o.b.y;
        wb.z = o.b.z;
        pb.a = h1;
        pb.b = h2;
        func_ov003_02221094(p1, r->unk_0A, &pb, &wb, 0);
    }
}

void func_ov003_02222d8c(unsigned short *a, void *b, UnkStruct_02222d8c *c)
{
    UnkStruct_02222d8c p1, p2, p3;
    int in;
    unsigned short id;

    in = 0;
    id = *a;
    if (id >= 0x2f && id <= 0x56) {
        in = 1;
    }
    if (in != 0 || (id >= 0xc8 && id <= 0xcf) || (id >= 0x57 && id <= 0x5b)) {
        if (func_0204b910(a) == 0) {
            return;
        }
        p1.x = c->x;
        p1.y = c->y;
        func_ov003_02222f8c((UnkStruct_02222f8c_2 *) a, (int) b, (int *) (&p1));
        return;
    }
    if (id == 0x67 || id == 0x6b) {
        if (func_02044540() == 0) {
            return;
        }
        p2.x = c->x;
        p2.y = c->y;
        func_ov003_02222f0c(b, (struct UnkStruct_02222f0c *) (&p2));
        return;
    }
    if ((id >= 0x66 && id <= 0x68) || (id >= 0x6a && id <= 0x6c)) {
        p3.x = c->x;
        p3.y = c->y;
        func_ov003_02222e24((UnkStruct_02222e24_2 *) a, (int) b, (int *) (&p3));
    }
}

void func_ov003_02222d68(UnkStruct_02222d68 *obj, int arg2)
{
    unsigned int arr[2];
    arr[0] = obj->unk_CC;
    arr[1] = obj->unk_D0;
    func_ov003_02222d8c((unsigned short *) arg2, (void *) obj->unk_04, (UnkStruct_02222d8c *) arr);
}

void func_ov003_02222cac(char *self, int b, UnkStruct_02222cac *c, int d, int e, int g)
{
    Vec v;
    char *t;
    int flag;
    func_0204e414();
    flag = 1;
    t = data_ov003_0223cf70 + 0x696c;
    if (d == 2) {
        flag = 0;
    }
    func_02055060(self + 8, *(int *) (0x80 + (t + (d << 4)) + (e << 2)), flag, 0x1000, 0, 0);
    if (*(int *) (self + 0xd4) == 8) {
        func_02055050(self + 8);
    }
    *(int *) (self + 0xd4) = d;
    *(int *) (self + 4) = b;
    *(int *) (self + 0xcc) = c->a;
    *(int *) (self + 0xd0) = c->b;
    func_0204f794((int *) (&v), c->a, c->b);
    *(int *) (self + 0xc0) = v.x;
    *(int *) (self + 0xc4) = v.y;
    *(int *) (self + 0xc8) = v.z;
    *(int *) (self + 0xd8) = 0x1f000;
    *(int *) (self + 0xdc) = 0;
    func_ov003_022230a0((UnkStruct_022230a0 *) self, g);
}

void func_ov003_02222c68(UnkStruct_02222c68 *self)
{
    int i;
    self->unk_00 = 0;
    self->unk_D8 = 0;
    self->unk_CC = -1;
    self->unk_D0 = -1;
    for (i = 0; i < 3; i++) {
        self->arr_138[i] = -1;
    }
    self->unk_144 = 0;
    self->unk_148 = 0;
}

void func_ov003_02222c34(struct UnkStruct_02222c34 *p)
{
    void *base;
    unsigned int v;
    base = p->unk_04->unk_2C;
    if (p->unk_00[1] == 2) {
        v = *(unsigned int *) ((unsigned char *) base + 0xd4);
        switch (v) {
            case 0:
            case 1:
            case 2:
            case 3:
                *p->unk_B8 = 0;
                break;
        }
    }
}

void func_ov003_02222bc0(void *self)
{
    int i = 0;
    int j = 0;
    void *z1 = 0;
    void *z2 = 0;
    void *z3 = 0;
    void **q;
    void **slot;
    void *res;
    char *row;
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 4; j++) {
            row = (char *) self + i * 0x10;
            res = (void *) func_ov003_02222b68((int) self, i, j);
            if (res != 0) {
                q = (void **) (row + j * 4);
                *(void **) (row + j * 4) = func_02064b2c(res, data_ov003_0223cf78, 4, z1);
                q += 0x20;
                *q = func_02107b44(NNS_G3dGetJntAnmSet(*(void **) (row + j * 4)), z2);
            } else {
                slot = (void **) (row + j * 4);
                *(void **) (row + j * 4) = z3;
                *(void **) ((char *) slot + 0x80) = z3;
            }
        }
    }
}

void func_ov003_02222b78(UnkStruct_02222b78 *s)
{
    void *ctx = data_ov003_0223cf78;
    int i = 0;
    int j = 0;
    void *nul = 0;
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 4; j++) {
            if (s->a[i][j] != 0) {
                func_020e993c(ctx, s->a[i][j]);
                s->a[i][j] = nul;
            }
        }
    }
}

int func_ov003_02222b68(int unused, int row, int col)
{
    return data_ov003_0223bcc4[row][col];
}

int func_ov003_02222af0(UnkStruct_02222af0 *obj)
{
    int local_8[2];
    int local_10[2];
    int local_18[2];
    int ret1, ret2;
    int v8, vC;
    int h8, hC, l8, lC;

    if (obj->unk_10 == 1) {
        goto exit;
    }

    local_8[0] = obj->unk_08;
    local_8[1] = obj->unk_0C;
    if (func_02045c84(obj->unk_04, local_8, 0) < 0) {
        goto exit;
    }

    ret1 = (int) func_0204e414();
    if (ret1 == 0) {
        goto exit;
    }

    v8 = obj->unk_08;
    vC = obj->unk_0C;
    h8 = v8 >> 4;
    hC = vC >> 4;
    lC = vC - (hC << 4);
    l8 = v8 - (h8 << 4);
    ret2 = func_0204f5e0(ret1, h8, hC, l8, lC, 0);
    if (ret2 == 0) {
        goto exit;
    }

    local_10[0] = obj->unk_08;
    local_10[1] = obj->unk_0C;
    func_ov003_02222d8c((unsigned short *) ret2, (void *) obj->unk_04, (UnkStruct_02222d8c *) local_10);

exit:
    local_18[0] = obj->unk_08;
    local_18[1] = obj->unk_0C;
    func_02045ea8(local_18, obj->unk_04, 0);
    obj->unk_00 = 0;
    return 0;
}
