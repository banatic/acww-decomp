/* fish_shadow_3: 19 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_0222a784 @ 0x0222a784, 0x36 bytes, Thumb
 * func_ov003_0222a634 @ 0x0222a634, 0x150 bytes, Thumb
 * func_ov003_0222a578 @ 0x0222a578, 0xbc bytes, Thumb
 * func_ov003_0222a56c @ 0x0222a56c, 0xc bytes, Thumb
 * func_ov003_0222a558 @ 0x0222a558, 0x14 bytes, Thumb
 * func_ov003_0222a544 @ 0x0222a544, 0x14 bytes, Thumb
 * func_ov003_0222a3ec @ 0x0222a3ec, 0x158 bytes, Thumb
 * func_ov003_0222a398 @ 0x0222a398, 0x54 bytes, Thumb
 * func_ov003_0222a378 @ 0x0222a378, 0x20 bytes, Thumb
 * func_ov003_0222a330 @ 0x0222a330, 0x48 bytes, Thumb
 * func_ov003_0222a16c @ 0x0222a16c, 0x1c4 bytes, Thumb
 * func_ov003_0222a088 @ 0x0222a088, 0xe4 bytes, Thumb
 * func_ov003_02229f2c @ 0x02229f2c, 0x15c bytes, Thumb
 * func_ov003_02229f00 @ 0x02229f00, 0x2a bytes, Thumb
 * func_ov003_02229eac @ 0x02229eac, 0x54 bytes, Thumb
 * func_ov003_02229e2c @ 0x02229e2c, 0x80 bytes, Thumb
 * func_ov003_02229dc0 @ 0x02229dc0, 0x6c bytes, Thumb
 * func_ov003_02229db4 @ 0x02229db4, 0xc bytes, Thumb
 * func_ov003_02229da4 @ 0x02229da4, 0x10 bytes, Thumb
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;

typedef struct {
    volatile u16 id;
    u16 pad_02;
    int pad_04;
} UnkStruct_0222a578;

typedef struct {
    u8 a;
    u8 pad_01;
    s16 b;
} UnkStruct_0222a578_2;

typedef struct {
    UnkStruct_0222a578_2 *p;
    int pad_04;
} UnkStruct_0222a578_3;

typedef struct {
    int x, y, z;
} UnkStruct_0222a16c;

typedef struct {
    char pad_00[0x120];
    UnkStruct_0222a16c unk_120;
    char pad_12C[0x1fe - 0x12c];
    u8 unk_1FE;
    char pad_1FF[0x218 - 0x1ff];
    UnkStruct_0222a16c unk_218;
} UnkStruct_0222a16c_2;

typedef struct {
    int x, y, z;
} UnkStruct_02229f2c;

typedef struct {
    char pad_00[0x34];
    int r;
    char pad_38[8];
} UnkStruct_02229f2c_2;

typedef struct {
    u16 v;
    char pad_02[18];
} UnkStruct_02229f2c_3;

typedef struct {
    char pad_00[0x120];
    int unk_120;
    char pad_124[4];
    int unk_128;
    char pad_12C[0x138 - 0x12c];
    s16 unk_138;
    char pad_13A[0x1ff - 0x13a];
    u8 kind;
} UnkStruct_02229f2c_4;

void *func_02095794(int k);
int func_ov003_02228150(void *p, void *q);
extern char data_ov003_0225f76c[];
extern u8 data_ov003_0223c014[];
extern int data_020ccf94;
extern char *func_02060924(int);
extern int func_02073d90(int g);
extern int func_ov003_0222799c(char *p, Vec3 *v, int a, int b, int c);
extern int func_ov003_0222791c(int a, int b);
extern void func_020604fc(char *p, char *self);
extern void func_02095764(UnkStruct_0222a578 *w, int x);
extern int func_0200322c(void *self, void *obj);
extern int func_020e8b4c(int a, int b);
extern u8 data_020cb785[];
extern UnkStruct_0222a578_3 data_ov003_0223bf00[];
extern u16 data_ov003_0225f0b8;
extern char data_ov003_0225f4dc[];
extern int func_020912d4(int id, Vec3 *v, int a, int b);
extern void func_020779b8(u8 *p, int a, int b);
extern void MI_CpuCopy8(const void *src, void *dst, unsigned n);
extern void func_02073820(int g);
extern void func_020737f0(int g, u8 *p, int n);
extern void func_02073770(int g, int a, int b);
void func_0204f818(int *a, int *b, Vec3 *t);
int func_02031b5c(int a, int b);
extern s16 FX_SinCosTable_[];
extern UnkStruct_02229f2c_3 data_ov003_0223c024[];
extern int func_02034270(UnkStruct_02229f2c_2 *out, UnkStruct_02229f2c *p, int a, int b);
extern void func_0203423c(UnkStruct_02229f2c_2 *p);
int func_020ea990(int h, void *p);
extern int func_ov003_02228018(void *p);
extern u8 func_ov003_0222793c(int a, int b);
extern void func_02004290(void *p, int k);

int func_ov003_0222a578(void *self, int p1, int p2, int p3);
int func_ov003_0222a558(void);
void func_ov003_0222a544(void);
int func_ov003_0222a088(char *self);
void func_ov003_02229f2c(UnkStruct_02229f2c_4 *self, int *o1, int *o2, int *o3);
void func_ov003_02229eac(u8 *st, char *obj);
void func_ov003_02229e2c(u8 *s, char *b);
void func_ov003_02229dc0(u8 *s, char *p);

int func_ov003_0222a784(void *p)
{
    int r = 0;
    void *h;
    if (p == 0) {
        return r;
    }
    h = func_02095794(4);
    if (h == 0) {
        return r;
    }
    if (func_ov003_02228150(p, h) != 0) {
        r = 1;
    }
    return r;
}

int func_ov003_0222a634(char *self)
{
    int ret;
    Vec3 b;
    Vec3 a;
    char *p;
    int g;
    int owner;
    // P
    char *rec;
    int ok;
    int i;
    // /P
    ret = 0;
    p = func_02060924(0);
    if (p == 0) {
        return 0;
    }
    g = data_020ccf94;
    if (func_02073d90(g)) {
        int v = *(int *) (p + 0x3c);
        if (v < 0) {
            return 0;
        }
        owner = *(int *) (g + 0x64);
        if (v != owner) {
            return 0;
        }
    } else {
        owner = 0;
    }
    rec = data_ov003_0225f76c;
    ok = 1;
    for (i = 0; i < 6; i++) {
        if (self != rec && owner == *(s8 *) (rec + 0x227)) {
            ok = 0;
            break;
        }
        rec += 0x24c;
    }
    if (ok) {
        Vec3 *q = (Vec3 *) (self + 0x120);
        a.x = q->x;
        a.y = q->y;
        a.z = q->z;
        if (func_ov003_0222a578((void *) (&a), *(short *) (self + 0x138), owner, *(s8 *) (self + 0x7e))) {
            int t = (data_ov003_0223c014[*(u8 *) (self + 0x1ff) * 0x14] << 12) / 100;
            Vec3 *r = (Vec3 *) (p + 8);
            b.x = r->x;
            b.y = r->y;
            b.z = r->z;
            if (func_ov003_0222a558() && func_ov003_0222799c(self + 0x120, &b, t, t, t)) {
                if (*(u8 *) (self + 0x200) != 2) {
                    *(u8 *) (self + 0x200) = 2;
                }
                *(short *) (self + 0x138) = *(short *) (self + 0x138) + (short) func_ov003_0222791c(0x5000, 0x7fff);
                *(short *) (self + 0x140) = 0x14;
            } else {
                *(s8 *) (self + 0x227) = owner;
                *(int *) (self + 0x22c) = (int) p;
                func_020604fc(p, self);
                ret = 1;
                *(u8 *) (self + 0x23c) = 1;
            }
        }
        func_ov003_0222a544();
    }
    return ret;
}

int func_ov003_0222a578(void *self, int p1, int p2, int p3)
{
    UnkStruct_0222a578 w;
    char *h;
    void *obj;
    UnkStruct_0222a578_3 *e;
    int ret, idx, k, q, lim;
    unsigned int ok;
    u16 lo, hi;

    ret = 0;
    h = func_02060924(0);
    if (h == 0) {
        return 0;
    }
    func_02095764(&w, p2);
    ok = 0;
    lo = w.id;
    hi = w.id;
    if (hi >= 0x1374 && lo <= 0x1374) {
        ok = 1;
    }
    if (ok) {
        idx = 0;
    } else if (lo >= 0x1375 && lo <= 0x1375) {
        idx = 1;
    } else {
        return 0;
    }
    obj = h + 8;
    k = data_020cb785[6 * p3];
    q = ((int) data_ov003_0223bf00[idx].p[k].a << 12) / 10;
    if (func_ov003_0222799c((char *) self, (Vec3 *) obj, q, q, q) != 0) {
        lim = data_ov003_0223bf00[idx].p[k].b;
        if (func_020e8b4c(func_0200322c(self, obj), p1) <= lim) {
            ret = 1;
        }
    }
    return ret;
}

void func_ov003_0222a56c(void)
{
    data_ov003_0225f0b8 = 10;
}

int func_ov003_0222a558(void)
{
    if (data_ov003_0225f0b8 != 0) {
        return 1;
    }
    return 0;
}

void func_ov003_0222a544(void)
{
    if (data_ov003_0225f0b8 != 0) {
        data_ov003_0225f0b8 = data_ov003_0225f0b8 - 1;
    }
}

int func_ov003_0222a3ec(char *self, int flag)
{
    u8 buf[12];
    Vec3 v;
    char *rec;
    Vec3 *q;
    Vec3 *r;
    int k;
    int d;
    int g;
    int kind;
    *(u8 *) (self + 0x1fd) = 1;
    k = *(s8 *) (self + 0x227);
    if (k == -1) {
        return 0;
    }
    rec = &data_ov003_0225f4dc[k * 0xa4];
    *(int *) (rec + 0x40) = 1;
    *(int *) (rec + 0x48) = 1;
    q = (Vec3 *) (self + 0x120);
    r = (Vec3 *) (rec + 0x60);
    r->x = q->x;
    r->y = q->y;
    r->z = q->z;
    *(u8 *) (rec + 0x78) = flag;
    d = *(s8 *) (self + 0x7e);
    *(int *) (rec + 0x90) = d;
    kind = *(u8 *) (self + 0x1ff);
    v.x = q->x;
    v.y = q->y;
    v.z = q->z;
    switch (kind) {
        case 0:
            func_020912d4(0x12, &v, 0, 0);
            break;
        case 1:
            func_020912d4(0x13, &v, 0, 0);
            break;
        case 2:
            func_020912d4(0x14, &v, 0, 0);
            break;
        case 3:
            func_020912d4(0x15, &v, 0, 0);
            break;
        case 4:
            func_020912d4(0x16, &v, 0, 0);
            break;
        case 5:
            func_020912d4(0x17, &v, 0, 0);
            break;
        case 6:
            func_020912d4(0x19, &v, 0, 0);
            break;
        case 7:
            func_020912d4(0x18, &v, 0, 0);
            break;
    }
    buf[0] = 0;
    buf[1] = d;
    func_020779b8(&buf[7], *(int *) (self + 0x120), *(int *) (self + 0x128));
    MI_CpuCopy8(&buf[7], &buf[2], 5);
    g = data_020ccf94;
    func_02073820(g);
    func_020737f0(g, buf, 7);
    func_02073770(g, 0x2a, 4);
    return 1;
}

int func_ov003_0222a398(char *e)
{
    int h = *(int *) (e + 0x22c);
    if (h == 0) {
        return 0;
    }
    *(u8 *) (e + 0x23d) = 0;
    *(s8 *) (e + 0x227) = -1;
    func_020604fc((char *) h, 0);
    *(int *) (e + 0x22c) = 0;
    *(u8 *) (e + 0x23c) = 0;
    *(u8 *) (e + 0x224) = 7;
    *(int *) (e + 0x13c) = 0;
    return 1;
}

int func_ov003_0222a378(char *self)
{
    int r = 2;
    int v;
    v = *(int *) (self + 0x120) >> 17;
    if (v == 0) {
        r = 0;
    } else if (v == 5) {
        r = 1;
    }
    return r;
}

int func_ov003_0222a330(char *self)
{
    int a, b;
    Vec3 t;
    int r = 0;
    Vec3 *p = (Vec3 *) (self + 0x120);
    t.x = p->x;
    t.y = p->y;
    t.z = p->z;
    t.z = t.z - 0x2000;
    func_0204f818(&a, &b, &t);
    if (func_02031b5c(a, b) == 1) {
        r = 1;
    }
    return r;
}

int func_ov003_0222a16c(UnkStruct_0222a16c_2 *self)
{
    int ret;
    int px, pz;
    int t;

    ret = 0;
    func_0204f818(&px, &pz, (Vec3 *) (&self->unk_120));
    switch (self->unk_1FE) {
        case 0:
        case 1:
        case 2:
        case 3:
            if (func_ov003_0222a088((char *) self) != 0) {
                self->unk_120.x = self->unk_218.x;
                self->unk_120.y = self->unk_218.y;
                self->unk_120.z = self->unk_218.z;
                ret = 1;
            } else if (func_02031b5c(px, pz) == 1) {
                self->unk_120.x = self->unk_218.x;
                self->unk_120.y = self->unk_218.y;
                self->unk_120.z = self->unk_218.z;
                ret = 3;
            }
            break;
        case 5:
        case 6:
            t = func_ov003_0222a378((char *) self);
            if (t == 0) {
                ret = 6;
            } else if (t == 1) {
                ret = 7;
            } else if (func_ov003_0222a088((char *) self) != 0) {
                self->unk_120.x = self->unk_218.x;
                self->unk_120.y = self->unk_218.y;
                self->unk_120.z = self->unk_218.z;
                ret = 2;
            } else if (func_02031b5c(px, pz) != 1) {
                self->unk_120.x = self->unk_218.x;
                self->unk_120.y = self->unk_218.y;
                self->unk_120.z = self->unk_218.z;
                ret = 4;
            } else if (func_ov003_0222a330((char *) self) != 0) {
                ret = 5;
            }
            break;
        default:
            if (func_02031b5c(px, pz) == 2) {
                if (func_ov003_0222a088((char *) self) != 0) {
                    self->unk_120.x = self->unk_218.x;
                    self->unk_120.y = self->unk_218.y;
                    self->unk_120.z = self->unk_218.z;
                    ret = 1;
                }
            } else if (func_02031b5c(px, pz) == 1) {
                t = func_ov003_0222a378((char *) self);
                if (t == 0) {
                    ret = 6;
                } else if (t == 1) {
                    ret = 7;
                } else if (func_ov003_0222a088((char *) self) != 0) {
                    self->unk_120.x = self->unk_218.x;
                    self->unk_120.y = self->unk_218.y;
                    self->unk_120.z = self->unk_218.z;
                    ret = 2;
                } else if (func_ov003_0222a330((char *) self) != 0) {
                    ret = 5;
                }
            } else {
                self->unk_120.x = self->unk_218.x;
                self->unk_120.y = self->unk_218.y;
                self->unk_120.z = self->unk_218.z;
                ret = 1;
            }
            break;
    }
    return ret;
}

int func_ov003_0222a088(char *self)
{
    int x;
    int y;
    int z;
    int ok = 1;
    func_ov003_02229f2c((UnkStruct_02229f2c_4 *) self, &x, &y, &z);
    switch (*(u8 *) (self + 0x1fe)) {
        case 0:
        case 1:
        case 2:
        case 3:
            if (((x >= 0xb && x <= 0x12) || x == 7 || x == 0x14) && ((y >= 0xb && y <= 0x12) || y == 7 || y == 0x14) &&
                ((z >= 0xb && z <= 0x12) || z == 7 || z == 0x14)) {
                ok = 0;
            }
            break;
        case 5:
        case 6:
            if ((x == 8 || x == 0x17) && (y == 8 || y == 0x17) && (z == 8 || z == 0x17)) {
                ok = 0;
            }
            break;
        default:
            if (((x >= 0xb && x <= 0x12) || x == 8 || x == 7 || x == 0x14) &&
                ((y >= 0xb && y <= 0x12) || y == 8 || y == 7 || y == 0x14) &&
                ((z >= 0xb && z <= 0x12) || z == 8 || z == 7 || z == 0x14)) {
                ok = 0;
            }
            break;
    }
    return ok;
}

void func_ov003_02229f2c(UnkStruct_02229f2c_4 *self, int *o1, int *o2, int *o3)
{
    UnkStruct_02229f2c pa, pb, pc;
    UnkStruct_02229f2c_2 b1, b2, b3;
    int t;
    int zz;
    int zz2;
    int t2;
    int zz3;
    int t3;
    int rad;
    int a;

    a = self->unk_138;
    t = ((u16) (s16) (a + 0x2000) >> 4) << 1;
    rad = data_ov003_0223c024[self->kind].v;
    zz = self->unk_128 + FX_SinCosTable_[t + 1] * rad / 100;
    pa.x = self->unk_120 + FX_SinCosTable_[t] * rad / 100;
    pa.y = -0x1333;
    pa.z = zz;
    t2 = ((u16) (s16) (a - 0x2000) >> 4) << 1;
    zz2 = self->unk_128 + FX_SinCosTable_[t2 + 1] * rad / 100;
    pb.x = self->unk_120 + FX_SinCosTable_[t2] * rad / 100;
    pb.y = -0x1333;
    pb.z = zz2;
    t3 = ((u16) self->unk_138 >> 4) << 1;
    zz3 = self->unk_128 + FX_SinCosTable_[t3 + 1] * rad / 100;
    pc.x = self->unk_120 + FX_SinCosTable_[t3] * rad / 100;
    pc.y = -0x1333;
    pc.z = zz3;
    func_02034270(&b1, &pa, 0, 0);
    func_02034270(&b2, &pb, 0, 0);
    func_02034270(&b3, &pc, 0, 0);
    *o1 = b1.r;
    *o2 = b2.r;
    *o3 = b3.r;
    func_0203423c(&b3);
    func_0203423c(&b2);
    func_0203423c(&b1);
}

void func_ov003_02229f00(char *p, void *a)
{
    switch (*(u8 *) (p + 3)) {
        case 0:
            func_ov003_02229eac((u8 *) p, (char *) a);
            break;
        case 1:
            func_ov003_02229e2c((u8 *) p, (char *) a);
            break;
        case 2:
            func_ov003_02229dc0((u8 *) p, (char *) a);
            break;
    }
}

void func_ov003_02229eac(u8 *st, char *obj)
{
    int h;
    if (st[0] != 0) {
        st[0] = (u8) (st[0] - 3);
        if (st[0] < 10) {
            st[0] = 0;
        }
    }
    if (st[2] != 0) {
        st[2] = (u8) (st[2] - 1);
    }
    h = (int) func_02095794(0);
    if (h != 0) {
        if (func_020ea990(h, obj + 0x120) < 0x8000) {
            st[3] = 1;
        }
    }
}

void func_ov003_02229e2c(u8 *s, char *b)
{
    void *p;
    if (s[2] != 0) {
        s[2] -= 1;
    }
    p = func_02095794(0);
    if (p != 0 && func_020ea990((int) p, b + 0x120) >= 0x8000) {
        s[3] = 0;
    } else if (func_ov003_02228018(0)) {
        s[0] += 1;
        if (s[0] >= 0xc8) {
            s[0] = 0xc8;
        }
    } else {
        if (s[0] != 0) {
            s[0] -= 1;
        }
        if (s[0] <= 0x96 && s[2] == 0) {
            s[1] = func_ov003_0222793c(0x3c, 0x8c);
            s[3] = 2;
        }
    }
}

void func_ov003_02229dc0(u8 *s, char *p)
{
    if (s[1] != 0) {
        s[1] -= 1;
        func_02004290(p + 0x40, 0x82f);
    } else {
        s[2] = func_ov003_0222793c(0x14, 0x50);
        s[3] = 1;
    }
    if (func_ov003_02228018(0)) {
        s[2] = func_ov003_0222793c(0x14, 0x28);
        s[3] = 1;
        s[1] = 0;
        s[0] += 1;
        if (s[0] >= 0xc8) {
            s[0] = 0xc8;
        }
    } else if (s[0] != 0) {
        s[0] -= 1;
    }
}

void func_ov003_02229db4(u8 *p)
{
    p[0] = 0;
    p[1] = 0;
    p[2] = 0;
    p[3] = 0;
}

void func_ov003_02229da4(char *self)
{
    func_ov003_02229db4((u8 *) (self + 0x248));
}
