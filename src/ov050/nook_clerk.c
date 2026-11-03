/* nook_clerk: 18 functions, module ov050
 * mwccarm 1.2/base -O4,s
 * func_ov050_02260d8c @ 0x02260d8c, 0x48 bytes, Thumb
 * func_ov050_02260d60 @ 0x02260d60, 0x2c bytes, Thumb
 * func_ov050_02260a68 @ 0x02260a68, 0x2f8 bytes, Thumb
 * func_ov050_022609f0 @ 0x022609f0, 0x76 bytes, Thumb
 * func_ov050_022609d8 @ 0x022609d8, 0x18 bytes, Thumb
 * func_ov050_02260738 @ 0x02260738, 0x2a0 bytes, Thumb
 * func_ov050_02260718 @ 0x02260718, 0x20 bytes, Thumb
 * func_ov050_022606b4 @ 0x022606b4, 0x64 bytes, Thumb
 * func_ov050_022605c0 @ 0x022605c0, 0xf4 bytes, Thumb
 * func_ov050_02260528 @ 0x02260528, 0x98 bytes, Thumb
 * func_ov050_02260510 @ 0x02260510, 0x18 bytes, Thumb
 * func_ov050_022604f8 @ 0x022604f8, 0x18 bytes, Thumb
 * func_ov050_022604e0 @ 0x022604e0, 0x18 bytes, Thumb
 * func_ov050_022604bc @ 0x022604bc, 0x22 bytes, Thumb
 * func_ov050_02260498 @ 0x02260498, 0x24 bytes, Thumb
 * func_ov050_02260474 @ 0x02260474, 0x24 bytes, Thumb
 * func_ov050_02260448 @ 0x02260448, 0x2c bytes, Thumb
 * func_ov050_02260420 @ 0x02260420, 0x28 bytes, Thumb
 */

#include "types.h"

struct VT2;

struct UnkStruct_02260a68_2 {
    struct VT2 *vt;
};

struct VT2 {
    void (*fn[8])(struct UnkStruct_02260a68_2 *);
};

struct UnkStruct_02260a68_3 {
    u8 pad_00[0x560];
    u8 unk_560;
    u8 pad_561[0x658 - 0x561];
    struct UnkStruct_02260a68_2 unk_658;
    u8 pad_65C[0x740 - 0x65c];
    u8 unk_740;
};

struct UnkStruct_02260a68 {
    u8 pad_00[0x64];
    int unk_64;
};

typedef struct {
    int x, y, z;
} Vec3;

typedef struct {
    int x;
    int y;
    int z;
} Vec3_02260738;

typedef struct UnkStruct_02260738_3 {
    char pad_00[0x618];
    int unk_618;
    char pad1[0x658 - 0x61c];
    int unk_658;
    char pad_65C[0x732 - 0x65c];
    u16 unk_732;
    int unk_734;
    int unk_738;
    u8 unk_73C;
} UnkStruct_02260738_3;

typedef struct UnkStruct_02260738 {
    char pad_00[0x5c];
    Vec3_02260738 unk_5C;
    char pad1[0x8e - 0x68];
    u16 unk_8E;
} UnkStruct_02260738;

typedef struct {
    u16 a;
    u16 b;
} UnkStruct_02260738_2;

typedef struct {
    int a, b, c;
} InterData;

typedef struct {
    int unk_00;
    int pad_04;
    int unk_08;
} DataT;

struct UnkStruct_022605c0 {
    int a;
    int b;
    int c;
};

struct UnkStruct_02260510 {
    char pad_00[0xc];
    unsigned short unk_0C;
};

struct UnkStruct_022604f8 {
    char pad_00[0xc];
    unsigned short unk_0C;
};

struct UnkStruct_022604e0 {
    char pad_00[0xc];
    unsigned short unk_0C;
};

typedef struct {
    void *vt;
    char pad_04[0x654];
    int unk_658;
} UnkStruct_02260448;

extern int func_02014868(void *);
extern int func_0201c014(void *);
extern int data_ov050_022650a8[];
extern void func_0201c054(struct UnkStruct_02260a68_3 *self, int a, int b, int c);
extern int func_0201c0e0(struct UnkStruct_02260a68_3 *self);
extern int func_0201c040(struct UnkStruct_02260a68_3 *self, int *a, int *b);
extern int func_0201c2a4(struct UnkStruct_02260a68_3 *self, int a);
extern void func_ov050_02264834(struct UnkStruct_02260a68_3 *self, int a);
extern void func_02016108(struct UnkStruct_02260a68_2 *s, int a);
extern int func_ov050_02263638(struct UnkStruct_02260a68_2 *s);
extern int func_020a7278(void);
extern short *func_0209d358(int a, int b);
extern Vec3 *func_02095794(int a);
extern void *func_0200338c(void *a, int b);
extern void func_020eaca0(Vec3 *dst, Vec3 *a, Vec3 *b);
extern int VEC_Mag(Vec3 *v);
extern UnkStruct_02260738 *func_020961a8(int);
extern int func_0203ec98(void);
extern int FX_MulFunc(int, int);
extern void func_0204f818(int *, int *, Vec3_02260738 *);
extern int func_ov004_0223cd50(void);
extern int func_ov004_0223cc10(int, int, int, int);
extern int func_020b6590(void);
extern int func_020b7524(int, int, int);
extern int func_020b758c(int, Vec3_02260738 *);
extern u16 *func_ov004_02246378(int, int);
extern int func_020984e8(void);
extern int func_0202e9fc(void);
extern int func_02062fe8(u16 *);
extern void func_ov050_02263640(void *, int);
extern int data_ov050_022650e4[][2];
extern int func_0204bcdc(u16 *);
extern int func_0204bc64(u16 *);
extern u8 data_021f6c38;
extern u8 data_021f6c34;
extern UnkStruct_02260738_2 data_021fbe40;
extern short FX_SinCosTable_[];
extern int func_02099640(int);
extern DataT data_ov050_02265090;
extern int func_0203e0a8(void *, int);
extern void *data_020ccf94;
extern int func_02030818(struct UnkStruct_022605c0 *v);
extern int func_0201c2c8(void *obj, int n);
extern void func_0201aff4(void *p, int n);
extern int func_02073d90(void *);
extern int func_02099020(void *p, int n);
extern int func_0208602c(void);
extern int func_020860d0(int argument0);
extern int func_02087ec0(void *argument0);
extern void *func_ov050_022636b0(void *p);
extern void *func_0202ee5c(void *p);
extern void func_020edf54(void *p);
extern char data_ov050_02265a60[];

int func_ov050_022609d8(void *argument0);
int func_ov050_02260718(int param);
int func_ov050_02260510(struct UnkStruct_02260510 *self);
int func_ov050_022604e0(struct UnkStruct_022604e0 *self);
int func_ov050_022604bc(int arg);

int func_ov050_02260d8c(void *p)
{
    if (*(int *) ((char *) p + 0x64) < *(int *) (data_ov050_022650a8 + 2)) {
        return 0;
    }
    if (func_02014868((char *) p + 0x618) != 0) {
        goto ret0;
    }
    if (func_0201c014(p) != 0) {
        goto ret0;
    }
    if (func_ov050_02260718((int) p) == 0) {
        goto ret1;
    }
ret0:
    return 0;
ret1:
    return 1;
}

int func_ov050_02260d60(void *p)
{
    if (func_02014868((char *) p + 0x618) != 0) {
        goto ret0;
    }
    if (func_0201c014(p) == 0) {
        goto ret1;
    }
ret0:
    return 0;
ret1:
    return 1;
}

void func_ov050_02260a68(struct UnkStruct_02260a68_3 *self, int sel, int v)
{
    switch (sel) {
        case 3:
            self->unk_560 = (u8) v;
            if (v != 4) {
                func_0201c054(self, 1, (*(struct UnkStruct_02260a68 * *) &data_020ccf94)->unk_64, v);
                func_ov050_02264834(self, 0xf);
            } else if (func_0201c0e0(self) != 0) {
                int k = (*(struct UnkStruct_02260a68 * *) &data_020ccf94)->unk_64;
                func_0201c054(self, 1, k, k);
                func_ov050_02264834(self, 0xf);
            }
            break;
        case 1:
            self->unk_560 = (u8) v;
            if (v != 4 && v != (*(struct UnkStruct_02260a68 * *) &data_020ccf94)->unk_64) {
                func_0201c054(self, 1, v, v);
                func_ov050_02264834(self, 9);
            } else {
                if (func_0201c0e0(self) != 0) {
                    struct UnkStruct_02260a68 *g = (*(struct UnkStruct_02260a68 * *) &data_020ccf94);
                    int k = g->unk_64;
                    func_0201c054(self, 1, k, k);
                    self->unk_658.vt->fn[2](&self->unk_658);
                    func_02016108(&self->unk_658, func_0201c2a4(self, 4));
                    if (func_ov050_02263638(&self->unk_658) == 0 || func_ov050_02263638(&self->unk_658) == 0x11) {
                        func_ov050_02264834(self, 4);
                    } else if (func_ov050_02263638(&self->unk_658) == 1 || func_ov050_02263638(&self->unk_658) == 0x12 ||
                               func_ov050_02263638(&self->unk_658) == 6 || func_ov050_02263638(&self->unk_658) == 0x1d) {
                        func_ov050_02264834(self, 5);
                    } else if (func_02073d90((void *) g) != 0 || *func_0209d358(0, 0x4a) != 0) {
                        self->unk_658.vt->fn[2](&self->unk_658);
                        func_02016108(&self->unk_658, func_0201c2a4(self, 4));
                        func_ov050_02264834(self, 4);
                    } else {
                        func_ov050_02264834(self, 0x10);
                    }
                }
            }
            break;
        case 0:
            self->unk_560 = (u8) v;
            if (v != 4 && v != (*(struct UnkStruct_02260a68 * *) &data_020ccf94)->unk_64) {
                func_0201c054(self, 1, v, v);
                func_ov050_02264834(self, 9);
            } else {
                if (func_0201c0e0(self) != 0) {
                    int k = (*(struct UnkStruct_02260a68 * *) &data_020ccf94)->unk_64;
                    func_0201c054(self, 1, k, k);
                    self->unk_658.vt->fn[2](&self->unk_658);
                    func_02016108(&self->unk_658, func_0201c2a4(self, 4));
                    if (func_ov050_02260510((struct UnkStruct_02260510 *) self) != 0) {
                        func_ov050_02263640((void *) (&self->unk_658), 5);
                    } else {
                        func_ov050_02263640((void *) (&self->unk_658), 0x13);
                    }
                    func_ov050_02264834(self, 4);
                }
            }
            break;
        case 8:
            if (v == 4) {
                if (func_020a7278() != 0) {
                    struct UnkStruct_02260a68 *g = (*(struct UnkStruct_02260a68 * *) &data_020ccf94);
                    func_0201c054(self, 1, g->unk_64, 4);
                    if (func_ov050_02263638(&self->unk_658) != 1 && func_ov050_02263638(&self->unk_658) != 0x12 &&
                        func_ov050_02263638(&self->unk_658) != 6 && func_ov050_02263638(&self->unk_658) != 0x1d) {
                        if (func_02073d90((void *) g) != 0 || *func_0209d358(0, 0x4a) != 0) {
                            func_ov050_02264834(self, 0xd);
                        } else {
                            func_ov050_02264834(self, 1);
                        }
                    }
                    self->unk_740 = 0;
                } else {
                    func_0201c054(self, 1, 4, (*(struct UnkStruct_02260a68 * *) &data_020ccf94)->unk_64);
                    func_ov050_02264834(self, 8);
                }
            }
            break;
        case 4: {
            int a;
            int b;
            if (func_0201c014((void *) self) == 0) {
                break;
            }
            if (func_0201c0e0(self) == 0) {
                break;
            }
            a = 4;
            b = 4;
            if (func_0201c040(self, &a, &b) == 0) {
                break;
            }
            if (v != 4) {
                if (v == b) {
                    goto ok;
                }
            }
            if (v != 4) {
                break;
            }
        ok:
            func_0201c054(self, 1, (*(struct UnkStruct_02260a68 * *) &data_020ccf94)->unk_64, 4);
            func_ov050_02264834(self, 0xd);
            break;
        }
    }
}

int func_ov050_022609f0(unsigned char *self)
{
    Vec3 vecA;
    Vec3 vecB;
    Vec3 diff1, diff2;
    void *obj;
    int dist1, dist2;

    Vec3 *pA;
    Vec3 *pB;

    if (!func_ov050_022604bc((int) self)) {
        goto fail;
    }

    pA = func_02095794(4);
    vecA.x = pA->x;
    vecA.y = pA->y;
    vecA.z = pA->z;

    obj = (void *) func_ov050_022609d8(self);
    obj = func_0200338c(obj, 0);
    if (!obj) {
        goto fail;
    }

    pB = (Vec3 *) ((unsigned char *) obj + 0x5c);
    vecB.x = pB->x;
    vecB.y = pB->y;
    vecB.z = pB->z;

    func_020eaca0(&diff1, &vecA, &vecB);
    dist1 = VEC_Mag(&diff1);

    func_020eaca0(&diff2, &vecA, (Vec3 *) (self + 0x5c));
    dist2 = VEC_Mag(&diff2);

    if (dist2 < dist1) {
        return 1;
    }
fail:
    return 0;
}

int func_ov050_022609d8(void *argument0)
{
    if (func_ov050_022604e0((struct UnkStruct_022604e0 *) argument0) != 0) {
        return 0x75;
    } else {
        return 0x74;
    }
}

int func_ov050_02260738(UnkStruct_02260738_3 *self)
{
    u16 sent[2];
    UnkStruct_02260738 *o;
    Vec3_02260738 *sp5c;
    int x;
    int z;
    int x2;
    int z2;
    Vec3_02260738 v;
    Vec3_02260738 v2;
    unsigned int a;
    unsigned int b;
    int r;
    int val;
    int t;
    int ok;
    u16 h;
    u16 c1;
    u16 c2;
    int q;
    int k;
    int i;
    o = func_020961a8(4);
    if ((data_021f6c38 != 0) && (data_021f6c34 != 0)) {
        a = 1;
    } else {
        a = 0;
    }
    if (a != 0) {
        b = 1;
    } else {
        b = 0;
    }
    if ((((o == 0) || (func_0203ec98() != 0)) || (func_02014868(&self->unk_618) != 0)) ||
        (((data_021fbe40.b & 1) == 0) && (b == 0))) {
        return 0;
    }
    if ((func_02073d90((void *) ((*(int *) &data_020ccf94))) != 0) || ((*func_0209d358(0, 0x4a)) != 0)) {
        if (func_ov050_022604e0((struct UnkStruct_022604e0 *) self) != 0) {
            return 0;
        }
    } else if ((func_ov050_022604bc((int) self) != 0) && (func_ov050_022609f0((unsigned char *) self) == 0)) {
        return 0;
    }
    self->unk_732 = 0xfff1;
    sp5c = &o->unk_5C;
    v.x = sp5c->x;
    v.y = sp5c->y;
    v.z = sp5c->z;
    h = o->unk_8E;
    x = 0;
    z = 0;
    i = (h >> 4) * 2;
    v.x = v.x + FX_MulFunc(0x2000, FX_SinCosTable_[i]);
    v.z += FX_MulFunc(0x2000, FX_SinCosTable_[i + 1]);
    func_0204f818(&x, &z, &v);
    if (b != (0)) {
        val = func_ov004_0223cc10(func_ov004_0223cd50(), x, z, 0);
        r = val;
        if (r != 0) {
            if (r != func_020b7524(func_020b6590(), 0, 0)) {
                return 0;
            }
        } else {
            x2 = 0;
            z2 = 0;
            func_020b758c(func_020b6590(), &v2);
            func_0204f818(&x2, &z2, &v2);
            if ((x2 != x) || (z2 != z)) {
                return 0;
            }
        }
    }
    sent[0] = *func_ov004_02246378(x, z);
    if (func_0204bcdc(&sent[0]) != 0) {
        sent[1] = 0xfff1;
        t = func_0204bc64(&sent[0]);
        if (t == func_0204bc64(&sent[1])) {
            ok = 1;
        } else {
            ok = 0;
        }
    } else {
        ok = (sent[0] == 0xfff1) ? (1) : (0);
    }
    if (ok != 0) {
        return 0;
    }
    r = 0;
    q = 0;
    k = 5;
    if (func_ov050_022604bc((int) self) != 0) {
        q = 1;
    }
    r = 0;
    c1 = sent[0];
    c2 = *((volatile u16 *) (&sent[0]));
    if ((c2 >= 0x1100) && (c1 <= 0x1143)) {
        r = 1;
    }
    if ((r != 0) || ((c1 >= 0x1144) && (c1 <= 0x1187))) {
        k = 0;
    } else if ((c1 >= 0x1000) && (c1 <= 0x10ff)) {
        k = 1;
    } else if ((c1 >= 0x1521) && (c1 <= 0x1530)) {
        if (((void) (func_020984e8()), func_0202e9fc()) != 0) {
            k = 2;
        } else {
            k = 3;
        }
    } else if (func_02062fe8(&sent[0]) != 0) {
        k = 4;
    }
    func_ov050_02263640(&self->unk_658, data_ov050_022650e4[k][q]);
    self->unk_732 = sent[0];
    self->unk_734 = x;
    self->unk_738 = z;
    self->unk_73C = 0;
    return 1;
}

int func_ov050_02260718(int param)
{
    int result;
    if (func_ov050_02260738((UnkStruct_02260738_3 *) ((void *) param)) != 0) {
        func_0203e0a8((void *) param, 0);
        result = 1;
    } else {
        result = 0;
    }
    return result;
}

int func_ov050_022606b4(void *self)
{
    int id;
    InterData *ip;
    int ta, tb, tc;
    volatile struct {
        int a, b, c;
    } local;

    id = func_020984e8();
    func_02099640(id);

    if (func_02099020((void *) id, 1) == 0) {
        goto fail;
    }

    ip = (InterData *) func_02095794(4);
    ta = ip->a;
    local.a = ta;
    tb = ip->b;
    local.b = tb;
    tc = ip->c;
    local.c = tc;

    if (tc >= data_ov050_02265090.unk_08) {
        goto fail;
    }
    if (ta <= data_ov050_02265090.unk_00) {
        goto fail;
    }

    func_ov050_02263640((char *) self + 0x658, 0x1e);
    func_0203e0a8(self, 0);
    return 1;
fail:
    return 0;
}

int func_ov050_022605c0(void *obj)
{
    struct UnkStruct_022605c0 v;
    struct UnkStruct_022605c0 *s;
    void *h;

    s = (struct UnkStruct_022605c0 *) func_02095794(4);
    v.a = s->a;
    v.b = s->b;
    v.c = s->c;
    if (func_ov050_02263638((struct UnkStruct_02260a68_2 *) ((char *) obj + 0x658)) != 1 && func_ov050_02263638((struct UnkStruct_02260a68_2 *) ((char *) obj + 0x658)) != 0x12) {
        if (func_ov050_022604bc((int) obj) != 0 && func_ov050_022609f0((unsigned char *) obj) == 0) {
            if (func_02030818(&v) != 0) {
                func_0201aff4((char *) obj + 0x350, func_0201c2c8(obj, 4));
            }
            return 0;
        }
        if (func_02073d90(data_020ccf94) != 0 || *func_0209d358(0, 0x4a) != 0) {
            return 0;
        }
        h = (void *) func_020984e8();
        func_02099640((int) h);
        if (func_02099020(h, 1) != 0) {
            return 0;
        }
    }
    if (func_02030818(&v) != 0) {
        if (func_ov050_022604bc((int) obj) != 0) {
            func_ov050_02263640((char *) obj + 0x658, 0x12);
        } else {
            func_ov050_02263640((char *) obj + 0x658, 1);
        }
        func_0203e0a8(obj, 0);
        func_ov050_02264834((struct UnkStruct_02260a68_3 *) obj, 0x12);
        return 1;
    }
    return 0;
}

int func_ov050_02260528(void *obj)
{
    if (func_0203ec98() != 0) {
        return 0;
    }
    if (func_02073d90(data_020ccf94) != 0 || *func_0209d358(0, 0x4a) != 0) {
        return 0;
    }
    if (func_02099020((void *) func_020984e8(), 1) != 0) {
        return 0;
    }

    if (func_02087ec0((void *) func_020860d0(func_0208602c())) != 0) {
        if (func_ov050_02260510((struct UnkStruct_02260510 *) obj) != 0) {
            func_ov050_02263640((char *) obj + 0x658, 6);
        } else if (func_ov050_022604e0((struct UnkStruct_022604e0 *) obj) != 0) {
            func_ov050_02263640((char *) obj + 0x658, 0x1d);
        }
        func_0203e0a8(obj, 0);
        return 1;
    }
    return 0;
}

int func_ov050_02260510(struct UnkStruct_02260510 *self)
{
    unsigned int flag = (self->unk_0C == 0x76) ? 1 : 0;
    if (flag > 0) {
        return 1;
    }
    return 0;
}

int func_ov050_022604f8(struct UnkStruct_022604f8 *self)
{
    unsigned int flag = (self->unk_0C == 0x75) ? 1 : 0;
    if (flag > 0) {
        return 1;
    }
    return 0;
}

int func_ov050_022604e0(struct UnkStruct_022604e0 *self)
{
    unsigned int flag = (self->unk_0C == 0x74) ? 1 : 0;
    if (flag > 0) {
        return 1;
    }
    return 0;
}

int func_ov050_022604bc(int arg)
{
    if (func_ov050_022604e0((struct UnkStruct_022604e0 *) arg) || func_ov050_022604f8((struct UnkStruct_022604f8 *) arg)) {
        return 1;
    }
    return 0;
}

int func_ov050_02260498(int param)
{
    int result;
    int r4;
    r4 = param;
    if (func_ov050_022604bc(param) != 0) {
        func_ov050_022609f0((unsigned char *) r4);
        result = 0x3000;
    } else {
        result = 0x3000;
    }
    return result;
}

int func_ov050_02260474(int param)
{
    int result;
    if (func_ov050_022604bc(param) != 0) {
        func_ov050_022609f0((unsigned char *) param);
        result = 0x4000;
    } else {
        result = 0x4000;
    }
    return result;
}

void *func_ov050_02260448(UnkStruct_02260448 *self)
{
    self->vt = (void *) ((char *) data_ov050_02265a60);
    func_ov050_022636b0(&self->unk_658);
    func_0202ee5c(self);
    func_020edf54(self);
    return self;
}

void *func_ov050_02260420(void *self)
{
    *(void **) self = data_ov050_02265a60;
    func_ov050_022636b0((char *) self + 0x658);
    func_0202ee5c(self);
    return self;
}
