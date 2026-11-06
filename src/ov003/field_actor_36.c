/* field_actor_36: 31 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_02215ef8 @ 0x02215ef8, 0x8 bytes, Thumb
 * func_ov003_02215ef0 @ 0x02215ef0, 0x8 bytes, Thumb
 * func_ov003_02215e78 @ 0x02215e78, 0x78 bytes, Thumb
 * func_ov003_02215e38 @ 0x02215e38, 0x40 bytes, Thumb
 * func_ov003_02215e0c @ 0x02215e0c, 0x2c bytes, Thumb
 * func_ov003_02215dfc @ 0x02215dfc, 0x10 bytes, Thumb
 * func_ov003_02215db8 @ 0x02215db8, 0x44 bytes, Thumb
 * func_ov003_02215d1c @ 0x02215d1c, 0x9c bytes, Thumb
 * func_ov003_02215ce4 @ 0x02215ce4, 0x36 bytes, Thumb
 * func_ov003_02215cbc @ 0x02215cbc, 0x28 bytes, Thumb
 * func_ov003_02215cb0 @ 0x02215cb0, 0xc bytes, Thumb
 * func_ov003_02215c84 @ 0x02215c84, 0x2c bytes, Thumb
 * func_ov003_02215c44 @ 0x02215c44, 0x40 bytes, Thumb
 * func_ov003_02215bf8 @ 0x02215bf8, 0x4c bytes, Thumb
 * func_ov003_02215bc0 @ 0x02215bc0, 0x36 bytes, Thumb
 * func_ov003_02215ba8 @ 0x02215ba8, 0x18 bytes, Thumb
 * func_ov003_02215b90 @ 0x02215b90, 0x16 bytes, Thumb
 * func_ov003_02215af0 @ 0x02215af0, 0xa0 bytes, Thumb
 * func_ov003_02215ac4 @ 0x02215ac4, 0x2c bytes, Thumb
 * func_ov003_02215a70 @ 0x02215a70, 0x54 bytes, Thumb
 * func_ov003_02215958 @ 0x02215958, 0x118 bytes, Thumb
 * func_ov003_02215918 @ 0x02215918, 0x40 bytes, Thumb
 * func_ov003_02215894 @ 0x02215894, 0x84 bytes, Thumb
 * func_ov003_022157f4 @ 0x022157f4, 0xa0 bytes, Thumb
 * func_ov003_02215798 @ 0x02215798, 0x5c bytes, Thumb
 * func_ov003_02215760 @ 0x02215760, 0x36 bytes, Thumb
 * func_ov003_02215718 @ 0x02215718, 0x48 bytes, Thumb
 * func_ov003_0221570c @ 0x0221570c, 0xc bytes, Thumb
 * func_ov003_02215688 @ 0x02215688, 0x84 bytes, Thumb
 * func_ov003_02215668 @ 0x02215668, 0x20 bytes, Thumb
 * func_ov003_02215664 @ 0x02215664, 0x4 bytes, Thumb
 */

#include "types.h"

typedef struct {
    fx32 x, y, z;
} Vec;

typedef struct {
    char pad_00[0x5c];
    Vec pos;
    char pad_68[0x76c];
    short unk_7D4;
} UnkStruct_02215e78;

typedef struct {
    fx32 x;
    fx32 z;
} UnkStruct_02215e78_2;

struct UnkStruct_02215dfc {
    unsigned char pad_00[0x7d4];
    signed short unk_7D4;
};

struct Param0 {
    char pad_00[0x2d0];
    char unk_2D0[0x800 - 0x2d0];
    int unk_800;
};

struct UnkStruct_02215d1c {
    char pad_00[0x98];
    void *unk_98;
    char pad_9C[0x800 - 0x98 - 4];
    int unk_800;
};

typedef struct {
    char pad_00[0x98];
    int unk_98;
} UnkStruct_02215bf8;

typedef struct {
    int x, y, z;
} Vec3;

typedef struct {
    char pad_00[0x5c8];
    char unk_5C8;
    char pad_5C9[3];
    int unk_5CC;
    Vec3 unk_5D0;
    char pad_5DC[0x800 - 0x5dc];
    int unk_800;
    char pad_804[0x8c4 - 0x804];
    int unk_8C4;
    int unk_8C8;
    int unk_8CC;
    char pad_8D0[0x8f0 - 0x8d0];
    char unk_8F0;
} UnkStruct_02215958;

typedef struct {
    char pad_00[0x5c];
    int unk_5C;
    char pad_60[0x64 - 0x60];
    int unk_64;
    char pad_68[0x8e - 0x68];
    short unk_8E;
    char pad_90[0x5d0 - 0x90];
    int arr[3];
} UnkStruct_02215918;

struct UnkStruct_02215894 {
    char pad_00[0x5a0];
    char unk_5A0[0x30];
    unsigned int src[3];
    char pad_5DC[0x600 - 0x5dc];
    unsigned char unk_600;
    char pad_601[0x800 - 0x601];
    unsigned int unk_800;
    char pad_804[0x8c4 - 0x804];
    unsigned int dest0;
    unsigned int dest1;
    unsigned int dest2;
};

typedef struct {
    unsigned char pad_00[0x7f0];
    int unk_7F0;
    unsigned char pad_7F4[0x8];
    int unk_7FC;
    int unk_800;
} UnkStruct_02215798;

extern void func_020779b8(void *ptr, int val, int other);
extern void func_02077978(void *argument0, void *argument1, int argument2);
extern void func_020109a0(void *, int b, int c, unsigned short d);
extern void func_0205eae0(void *, int, int, int);
extern void func_02060438(void *, Vec *);
extern int func_020e8ed8(fx32, fx32);
extern int func_ov003_02215f00(void *self, const int *data, int count, int param);
extern void func_02010f5c(void *);
extern int func_02056f28(void *, int);
extern int func_0200f328(void *, int);
extern void func_0200fb34(void *obj, int val);
extern int func_02056f94(void *p);
extern void func_0203ae84(void);
extern int func_02073908(int, int);
extern int func_0201100c(void *);
extern void func_02010d64(void *);
extern int func_020113a4(void *, int, int);
extern void func_0201107c(void *, int *);
extern int func_0200f554(void *);
extern int data_020ccf94;
extern unsigned int func_0200e92c(void *);
extern void func_0200e90c(void *, int, int, int);
extern int func_0200e894(int, void *);
extern int func_0200e91c(void *);
extern int func_02008258(void *p, int val);
extern int func_0200d4e8(void *p, int a, int b, int c);
extern void func_02077950(int a, int b, int c, int d, int e);
extern void func_02077928(int, char *, char *, char *, int);
extern void func_020109fc(void *p, int a, int b, int c);
extern void func_02060428(void *a, void *b);
extern void func_02036458(int);
extern void func_0206026c(void *, int);
extern int data_021c526c;
extern int func_020113e0(short *p, int v);
extern void func_020110a0(void *object, short *values);
extern int func_0205e8d8(void *);
extern void func_02036460(void *);
extern int func_0200f290(char *p, int a);
extern int func_020604f8(char *p);
extern void func_ov003_0222ad2c(void *object);
extern int func_ov003_02228400(char *p, int a);
extern void *func_ov003_02215624(char *p, int a, int b, int c);
extern int func_020b6590(void);
extern int func_020b758c(int a, int b);
extern int func_020604c8(char *p);
extern void func_02035684(int, int, int);
extern int func_020604b0(void *p);
extern void func_0200f2a0(unsigned char *a, int b, unsigned char *c);
extern void *func_ov003_02215494(unsigned char *a, int b, int c);
extern void func_02035624(int a);
extern void *func_ov003_0221535c(unsigned char *a, int b, int c);

int func_ov003_02215bc0(int a, int b, int c);
void *func_ov003_02215760(void *r0, void *r1, void *r2);

void func_ov003_02215ef8(void *argument0, int argument1, int argument2)
{
    func_020779b8(argument0, argument1, argument2);
}

void func_ov003_02215ef0(void *argument0, void *argument1, int argument2)
{
    func_02077978(argument0, argument1, argument2);
}

void func_ov003_02215e78(UnkStruct_02215e78 *self, void *data, int previous)
{
    Vec v[2];
    UnkStruct_02215e78_2 *p;
    fx32 x, z;
    func_020109a0(self, 0x52, 3, 0);
    func_0205eae0((char *) self + 0x5a0, 0x15, 3, 0);
    p = (UnkStruct_02215e78_2 *) ((char *) data + 0xc);
    z = p->z;
    x = p->x;
    v[0].x = x;
    v[0].y = 0;
    v[0].z = z;
    v[1].x = x;
    v[1].y = 0;
    v[1].z = z;
    func_02060438((char *) self + 0x5c8, &v[1]);
    func_ov003_02215ef8((char *) self + 0x8f0, (fx32) v[0].x, (fx32) v[0].z);
    self->unk_7D4 = (short) func_020e8ed8(v[0].x - self->pos.x, v[0].z - self->pos.z);
}

void func_ov003_02215e38(void *self, int param)
{
    int t0, t1, v;
    struct {
        int a[3];
        int b[3];
    } loc;

    func_ov003_02215ef0((char *) self + 0x8f0, (void *) (&t0), (int) (&t1));
    v = *(int *) ((char *) self + 0x60);

    loc.a[0] = t0;
    loc.a[1] = v;
    loc.a[2] = t1;
    loc.b[0] = t0;
    loc.b[1] = v;
    loc.b[2] = t1;

    func_ov003_02215f00(self, loc.b, 6, param);
}

void func_ov003_02215e0c(void *p)
{
    func_02010f5c(p);
    if (func_02056f28((char *) p + 0x2d0, 0x11) != 0) {
        func_0200f328(p, 0x849);
    }
}

void func_ov003_02215dfc(struct UnkStruct_02215dfc *obj)
{
    func_0200fb34(obj, obj->unk_7D4);
}

void func_ov003_02215db8(struct Param0 *param0)
{
    if (func_02056f94(&param0->unk_2D0)) {
        func_ov003_02215bc0((int) param0, 6, -1);
        if (func_02073908((int) ((*(void **) &data_020ccf94)), param0->unk_800)) {
            func_0203ae84();
        }
    }
}

void func_ov003_02215d1c(struct UnkStruct_02215d1c *self)
{
    int v1, v2;
    if (func_02073908(data_020ccf94, self->unk_800) != 0) {
        func_ov003_02215dfc((struct UnkStruct_02215dfc *) self);
        func_ov003_02215e0c(self);
        func_0201100c(self);
        func_02010d64(self);
        v1 = func_020113a4(self->unk_98, 0, 0x171);
        func_0201107c(self, &v1);
        func_ov003_02215db8((struct Param0 *) self);
    } else {
        func_ov003_02215e0c(self);
        if (func_0200f554(self) != 0) {
            func_0201100c(self);
        }
        func_02010d64(self);
        v2 = func_020113a4(self->unk_98, 0, 0x171);
        func_0201107c(self, &v2);
        func_ov003_02215db8((struct Param0 *) self);
    }
}

int func_ov003_02215ce4(int a, int b, int c)
{
    char buf[0x20];
    int ret;

    func_0200e92c(buf);
    func_0200e90c(buf, 0x4E, b, c);
    ret = func_0200e894(a, buf);
    func_0200e91c(buf);
    return ret;
}

void func_ov003_02215cbc(int r0, void *message, int previous)
{
    int r4 = r0;
    func_020109a0((void *) r4, 0x53, 3, 0);
    func_0205eae0((void *) (r4 + 0x5a0), 0x16, 3, 0);
}

void func_ov003_02215cb0(int a, int b)
{
    func_ov003_02215ce4(a, 6, b);
}

void func_ov003_02215c84(void *self)
{
    void *r4 = self;
    func_02010f5c((void *) ((int) self));
    if (func_02056f28((char *) r4 + 0x2d0, 0xc) != 0) {
        func_0200f328(r4, 0x84a);
    }
}

void func_ov003_02215c44(unsigned char *self)
{
    if (func_02056f94(self + 0x2d0) == 0) {
        return;
    }
    *(int *) (self + 0x7fc) = func_02008258(self, *(int *) (self + 0x7f0));
    func_0200d4e8(self, 3, 1, -1);
}

void func_ov003_02215bf8(UnkStruct_02215bf8 *ptr)
{
    int local;
    func_ov003_02215c84(ptr);
    if (func_0200f554(ptr) != 0) {
        func_0201100c(ptr);
    }
    func_02010d64(ptr);
    local = func_020113a4((void *) ptr->unk_98, 0, 0x171);
    func_0201107c(ptr, &local);
    func_ov003_02215c44((unsigned char *) ptr);
}

int func_ov003_02215bc0(int a, int b, int c)
{
    char buf[32];
    int ret;
    func_0200e92c(buf);
    func_0200e90c(buf, 0x4f, b, c);
    ret = func_0200e894(a, buf);
    func_0200e91c(buf);
    return ret;
}

void func_ov003_02215ba8(int a, int *b, int c)
{
    func_02077950(a, b[0], b[1], b[2], c);
}

void func_ov003_02215b90(int a, char *b, int c)
{
    func_02077928(a, b, b + 4, b + 8, c);
}

void func_ov003_02215af0(unsigned char *self, void *message, int previous)
{
    struct Output {
        unsigned char flag;
        unsigned char pad[3];
        unsigned int w[3];
    } out;
    unsigned char *r4;
    unsigned int g;
    unsigned int tmp[3];

    r4 = self + 0x8f0;
    func_020109fc(self, 0x54, 3, 0);

    g = (*(unsigned int *) &data_020ccf94);
    if (func_02073908(g, *(unsigned int *) (self + 0x800)) == 0) {
        func_ov003_02215b90((int) r4, (char *) out.w, (int) (&out.flag));
        if (out.flag == 3) {
            tmp[0] = out.w[0];
            tmp[1] = out.w[1];
            tmp[2] = out.w[2];
            func_02060428(self + 0x5c8, tmp);
        }
    }

    func_0205eae0(self + 0x5a0, 0x17, 3, 0);

    if (func_02073908(g, *(unsigned int *) (self + 0x800)) != 0) {
        func_ov003_02215ba8((int) r4, (int *) (self + 0x5d0),
                            (unsigned char) ((unsigned char) (*(unsigned int *) (self + 0x5cc))));
    }
}

void func_ov003_02215ac4(void *obj, unsigned short val)
{
    int state;

    state = *(int *) ((char *) obj + 0x7f0);
    if (state == 0x4d) {
        return;
    }
    if (state == 0x4f) {
        *(unsigned short *) ((char *) obj + 0x0c84) = val;
    } else {
        func_ov003_02215bc0((int) obj, 6, (unsigned short) val);
    }
}

void func_ov003_02215a70(void *param0, int param1)
{
    if (func_02073908(data_020ccf94, *(int *) ((char *) param0 + 0x800)) != 0) {
        func_02036458(data_021c526c + 0x1c4);
        return;
    }
    if (param1 == 0x50) {
        return;
    }
    if (param1 == 0x51) {
        return;
    }
    func_0206026c((char *) param0 + 0x5c8, 1);
}

void func_ov003_02215958(UnkStruct_02215958 *self)
{
    u8 mode;
    volatile Vec3 p;
    struct {
        Vec3 q, r, s;
    } W;
    void *e;
    int m;
    int k;
    int dx, dz;
    Vec3 *pv;

    e = &self->unk_8F0;
    if (func_02073908(data_020ccf94, self->unk_800) != 0) {
        func_ov003_02215ba8((int) e, (int *) (&self->unk_5D0), (u8) self->unk_5CC);
        return;
    }
    func_ov003_02215b90((int) e, (char *) ((Vec3 *) &p), (int) (&mode));
    m = mode;
    k = self->unk_5CC;
    if (k != 4) {
        if (k != 3) {
            if (m == 4) {
                func_0206026c(&self->unk_5C8, m);
                W.r.x = p.x;
                W.r.y = p.y;
                W.r.z = p.z;
                func_02060428(&self->unk_5C8, (void *) (&W.r));
            } else if (k >= 6) {
                func_0206026c(&self->unk_5C8, 0);
            }
        }
    } else {
        pv = &self->unk_5D0;
        W.q.x = pv->x;
        W.q.y = pv->y;
        W.q.z = pv->z;
        dx = W.q.x - p.x;
        dz = W.q.z - p.z;
        if (dx * dx + dz * dz >= 0x400000) {
            W.s.x = p.x;
            W.s.y = p.y;
            W.s.z = p.z;
            func_02060428(&self->unk_5C8, (void *) (&W.s));
        }
        if (m == 5) {
            func_0206026c(&self->unk_5C8, m);
            func_0200f328((void *) self, 0x84f);
            self->unk_8C4 = p.x;
            self->unk_8C8 = p.y;
            self->unk_8CC = p.z;
        }
    }
}

void func_ov003_02215918(UnkStruct_02215918 *this)
{
    short s;
    short val;
    int *base;
    int d1, d2, res;

    base = this->arr;
    d1 = base[0] - this->unk_5C;
    d2 = base[2] - this->unk_64;
    res = func_020e8ed8(d1, d2);
    val = this->unk_8E;
    s = val;
    func_020113e0(&s, res);
    func_020110a0((void *) (this), (short *) (&s));
}

void func_ov003_02215894(struct UnkStruct_02215894 *self)
{
    if (func_0205e8d8(self->unk_5A0) == 0) {
        return;
    }
    if (self->unk_600 == 0) {
        return;
    }
    func_0200f328(self, 0x84b);
    {
        unsigned int *p = self->src;
        self->dest0 = p[0];
        self->dest1 = p[1];
        self->dest2 = p[2];
    }
    if (func_02073908((int) ((*(void **) &data_020ccf94)), self->unk_800) == 0) {
        return;
    }
    func_02036460((void *) ((char *) (*(void **) &data_021c526c) + 0x1c4));
}

void func_ov003_022157f4(char *p)
{
    void *condition_value_1;
    func_ov003_02215894((struct UnkStruct_02215894 *) p);
    if (func_0205e8d8((void *) (p + 0x5a0)) == 0) {
        return;
    }
    if (func_0200f290(p, 0xb) != 0) {
        condition_value_1 = (void *) (func_020604f8(p + 0x5c8));
        if (condition_value_1 != 0) {
            func_ov003_0222ad2c(condition_value_1);
        } else {
            func_ov003_02228400(p + 0x5d0, 0x1000);
        }
        func_ov003_02215624(p, 0, 6, -1);
    } else {
        if (*(unsigned char *) (p + 0x140) == 0 && func_020b758c(func_020b6590(), 0) == 0) {
            return;
        }
        if (func_020604c8(p + 0x5c8) != 0) {
            func_ov003_02215760((void *) p, (void *) 6, (void *) (-1));
        } else {
            func_ov003_02215624(p, 0, 6, -1);
        }
    }
}

void func_ov003_02215798(UnkStruct_02215798 *self)
{
    func_02010f5c(self);
    func_ov003_02215958((UnkStruct_02215958 *) self);
    func_0200f554(self);
    func_ov003_02215918((UnkStruct_02215918 *) self);
    func_02010d64(self);

    if (func_02073908(data_020ccf94, self->unk_800) != 0) {
        func_ov003_022157f4((char *) self);
    } else {
        self->unk_7FC = func_02008258(self, self->unk_7F0);
    }
}

void *func_ov003_02215760(void *r0, void *r1, void *r2)
{
    void *sp[8];
    void *r4;
    void *r5;
    void *r6;

    r5 = r0;
    r4 = r1;
    r6 = r2;

    func_0200e92c(sp);
    func_0200e90c(sp, 0x50, (int) r4, (int) r6);
    r4 = (void *) func_0200e894((int) r5, sp);
    func_0200e91c(sp);
    return r4;
}

void func_ov003_02215718(int a0, void *message, int previous)
{
    func_020109fc((void *) a0, 0x55, 3, 0);
    func_0205eae0((void *) (a0 + 0x5a0), 0x18, 3, 0);
    if (func_02073908(data_020ccf94, *(int *) (a0 + 0x800)) != 0) {
        func_02035684(0x12, 0, 0);
    }
}

void func_ov003_0221570c(int a, int b)
{
    func_ov003_02215760((void *) a, (void *) 6, (void *) b);
}

void func_ov003_02215688(unsigned char *self)
{
    unsigned char *p = self + 0x5d0;

    if (func_02073908(data_020ccf94, *(int *) (self + 0x800)) != 0) {
        switch (func_020604b0(self + 0x5c8)) {
            case 0:
                func_0200f2a0(self, 0x7f6, p);
                break;
            case 1:
                func_ov003_02215494(self, 6, -1);
                func_02035624(0x12);
                break;
            case 2:
                func_ov003_0221535c(self, 6, -1);
                break;
            default:
                break;
        }
    } else {
        func_0200f2a0(self, 0x7f6, p);
    }
}

void func_ov003_02215668(int arg)
{
    func_02010f5c((void *) arg);
    func_0200f554((void *) arg);
    func_02010d64((void *) arg);
    func_ov003_02215688((unsigned char *) arg);
}

void func_ov003_02215664(unsigned char *p0, int p1)
{
    p0[0] = p1;
}
