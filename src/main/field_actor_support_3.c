/* field_actor_support_3: 23 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0200ffec @ 0x0200ffec, 0x18 bytes, Thumb
 * func_0200ff28 @ 0x0200ff28, 0xc4 bytes, Thumb
 * func_0200fef0 @ 0x0200fef0, 0x38 bytes, Thumb
 * func_0200fea0 @ 0x0200fea0, 0x50 bytes, Thumb
 * func_0200fdd0 @ 0x0200fdd0, 0xd0 bytes, Thumb
 * func_0200fd04 @ 0x0200fd04, 0xca bytes, Thumb
 * func_0200fc90 @ 0x0200fc90, 0x74 bytes, Thumb
 * func_0200fbe0 @ 0x0200fbe0, 0xb0 bytes, Thumb
 * func_0200fbc4 @ 0x0200fbc4, 0x1c bytes, Thumb
 * func_0200fb7c @ 0x0200fb7c, 0x48 bytes, Thumb
 * func_0200fb58 @ 0x0200fb58, 0x22 bytes, Thumb
 * func_0200fb34 @ 0x0200fb34, 0x24 bytes, Thumb
 * func_0200faf0 @ 0x0200faf0, 0x44 bytes, Thumb
 * func_0200faa8 @ 0x0200faa8, 0x48 bytes, Thumb
 * func_0200fa8c @ 0x0200fa8c, 0x1c bytes, Thumb
 * func_0200fa6c @ 0x0200fa6c, 0x20 bytes, Thumb
 * func_0200fa1c @ 0x0200fa1c, 0x50 bytes, Thumb
 * func_0200f95c @ 0x0200f95c, 0xc0 bytes, Thumb
 * func_0200f888 @ 0x0200f888, 0xd4 bytes, Thumb
 * func_0200f86c @ 0x0200f86c, 0x1c bytes, Thumb
 * func_0200f814 @ 0x0200f814, 0x58 bytes, Thumb
 * func_0200f7ac @ 0x0200f7ac, 0x68 bytes, Thumb
 * func_0200f748 @ 0x0200f748, 0x64 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_0200ffec;

struct UnkStruct_0200ffec_2;

struct UnkStruct_0200ffec {
    char pad_00[0x80c];
    void *elem;
};

struct UnkStruct_0200ffec_2 {
    char pad_00[0xc];
    int value;
};

typedef struct {
    unsigned char pad_00[0x800];
    int unk_800;
    unsigned char pad_804[0x80c - 0x804];
    int unk_80C;
} UnkStruct_0200ff28;

struct Struct0200fef0 {
    unsigned char pad_00[0x810];
    int unk_810;
};

typedef struct UnkStruct_0200fea0 UnkStruct_0200fea0;

struct UnkStruct_0200fea0 {
    u8 pad_00[0x80c];
    int unk_80C; // offset 0x80c
    u8 pad_810[0x4];
    int unk_814; // offset 0x814
};

struct Vec {
    int x;
    int z;
};

// 12-byte object; the callee gets a pointer to its second word. The first word is never written.
struct Loc {
    int unk_00;
    int x;
    int z;
};

struct UnkStruct_0200fdd0 {
    char pad_00[0x800];
    int unk_800;
    char pad_804[8];
    int unk_80C;
    char pad_810[8];
    int unk_818;
    char pad_81C[4];
    unsigned short unk_820;
    unsigned short unk_822;
};

typedef struct Pair {
    int x;
    int y;
} Pair;

typedef struct {
    unsigned short lo;
    unsigned short hi;
} UnkStruct_0200fc90;

typedef struct {
    unsigned char pad_00[0x8e];
    short unk_8E;
} UnkStruct_0200fb34;

typedef struct UnkStruct_0200faf0 {
    char pad_00[0x8E];
    short unk_8E;
} UnkStruct_0200faf0;

struct ThreeInts {
    int a;
    int b;
    int c;
};

typedef struct {
    int x, y, z;
} UnkStruct_0200f95c;

typedef struct {
    unsigned char pad_00[0x60];
    int unk_60;
    unsigned char pad_64[0x8e - 0x64];
    short unk_8E;
    unsigned char pad_90[0x2d0 - 0x90];
    int unk_2D0;
    unsigned char pad_2D4[0x6c8 - 0x2d4];
    int fAx, fAy, fAz;
    int fBx, fBy, fBz;
    unsigned char pad_6E0[0x704 - 0x6e0];
    int unk_704;
} UnkStruct_0200f95c_2;

typedef struct UnkStruct_0200f888 {
    unsigned char pad_00[0xb0];
    unsigned int flags_b0;
    unsigned char pad_B4[0x614];
    int unk_6C8;
    int unk_6CC;
    int unk_6D0;
    int unk_6D4;
    int unk_6D8;
    int unk_6DC;
    unsigned char pad_6E0[0x24];
    int unk_704;
    unsigned char pad_708[0x134];
    unsigned char unk_83C[0x44];
} UnkStruct_0200f888;

struct UnkStruct_0200f814 {
    unsigned char pad_00[3];
    unsigned char unk_03;
    unsigned char unk_04;
    unsigned char unk_05;
};

// Bitfield reads: bits 7-10 and 11-15 of a 16-bit word.
typedef struct UnkStruct_0200f7ac {
    u16 fa : 7;
    u16 fb : 4;
    u16 fc : 5;
} UnkStruct_0200f7ac;

extern struct UnkStruct_0200ffec_2 *func_02042fc4(void *handle);
extern int data_021c80bc;
extern void func_0204f818(int *out1, int *out2, void *arg1);
extern int func_02043a4c(int a, void *buf, int val);
extern int func_02043d84(int a, void *buf, int val, int flag, int extra);
extern int func_02043990(int a, void *buf, int val);
extern int data_020c7640[];
extern int func_020431c8(int);
extern void func_020431b8(int);
extern int func_020436a8(int arg);
extern unsigned short *func_0204f5e0(void *ctx, int cx, int cz, int dx, int dz, int layer);
extern int func_ov004_0222ac24(int, Pair *, int, int, int);
extern int func_0200bdbc(int, Pair *, int, int, int);
extern int func_ov003_02218ec4(int, Pair *, int, int);
extern int func_ov003_022100c4(int, Pair *, int, int, int);
extern void func_020110c4(void *, void *);
extern int func_0200f290(void *, int);
extern int func_0204bcdc(void *);
extern int func_0204bc64(void *);
extern int func_02062148(void *);
extern void func_020114b0(char *ptr, int a, int b, int c, int d);
extern void func_02011490(void *dst, const void *src);
extern int func_020113e0(short *t, int b);
extern void func_020110a0(UnkStruct_0200fb34 *p, short *t);
extern int func_02011404(void *, int, int, int, int);
extern void func_0204f7e0(void *, void *);
extern unsigned char data_020c8094[];
extern int FX_MulFunc(int a, int b);
extern short FX_SinCosTable_[];
extern int func_02056f28(void *flags, int bit);
extern int func_020912d4(int type, void *a, void *b, int c);
extern int func_020b1cb0(const int *p);
extern void func_0200443c(int receiver, unsigned int value, unsigned int flag);
extern int func_02011368(int);
extern int func_020997a8(int);
extern void func_0209e474(void *);
extern void MI_CpuCopy8(void *, void *, int);
extern int func_0209e3ac(void *, void *, int);
extern void func_02099794(int b, UnkStruct_0200f7ac t);
extern u16 *func_0209d358(int z, int n);
extern int func_020112bc(void *a);
extern int func_0200ee0c(void *a);
extern UnkStruct_0200f7ac *func_0209627c(void);
int func_02073908(int a, int b);
int func_0202f188(void);
int func_02008934(int *a, int b, int c, int d);
int func_02008a54(int *a, int b, int c);
extern int data_020ccf94;

void func_0200fb58(void *a, void *b, void *c);
void func_0200fb34(UnkStruct_0200fb34 *p, int b);
void func_0200fa6c(int a, int b);
void func_0200fa1c(struct ThreeInts *out, int unused, struct ThreeInts *in, unsigned short *p, int *q);
void func_0200f888(UnkStruct_0200f888 *self);
int func_0200f814(int a, void *b, struct UnkStruct_0200f814 *dst);

int func_0200ffec(struct UnkStruct_0200ffec *ptr)
{
    return func_02042fc4(ptr->elem)->value;
}

int func_0200ff28(UnkStruct_0200ff28 *self, void *arg1, int mode, int idx)
{
    if (self->unk_80C == -1 && data_021c80bc != 0) {
        int v1, v2;

        v1 = 0;
        v2 = 0;
        func_0204f818(&v1, &v2, arg1);

        switch (mode) {
            case 0: {
                struct {
                    int a, b;
                } buf;
                buf.a = v1;
                buf.b = v2;
                self->unk_80C = func_02043a4c(self->unk_800, &buf, data_020c7640[idx]);
                break;
            }
            case 1: {
                struct {
                    int a, b;
                } buf;
                buf.a = v1;
                buf.b = v2;
                self->unk_80C = func_02043d84(self->unk_800, &buf, data_020c7640[idx], 0, 0xfff1);
                break;
            }
            case 2: {
                struct {
                    int a, b;
                } buf;
                buf.a = v1;
                buf.b = v2;
                self->unk_80C = func_02043990(self->unk_800, &buf, data_020c7640[idx]);
                break;
            }
        }
    }

    return self->unk_80C != -1;
}

void func_0200fef0(struct Struct0200fef0 *p)
{
    int ret;

    if (p->unk_810 == -1) {
        return;
    }

    ret = func_020431c8(p->unk_810);

    if (ret != 1 && ret != 2) {
        return;
    }

    func_020431b8(p->unk_810);
    p->unk_810 = -1;
}

int func_0200fea0(UnkStruct_0200fea0 *self)
{
    int ret = 0;

    self->unk_814 = 0;

    if (self->unk_80C != -1) {
        ret = func_020436a8(self->unk_80C);

        switch (ret) {
            case 1:
            case 2:
                self->unk_814 = func_0200ffec((struct UnkStruct_0200ffec *) self);
                func_020431b8(self->unk_80C);
                self->unk_80C = -1;
                break;
        }
    }

    return ret;
}

int func_0200fdd0(struct UnkStruct_0200fdd0 *s, struct Vec *v, int c, int d)
{
    unsigned short *o;
    int cx;
    int cz;
    int x;
    int z;
    struct Loc loc;

    if (s->unk_80C == -1) {
        x = v->x;
        z = v->z;
        cx = x >> 4;
        cz = z >> 4;
        o = func_0204f5e0((*(void **) &data_021c80bc), cx, cz, x - (cx << 4), z - (cz << 4), 0);
        if (o == 0) {
            s->unk_822 = 0xfff1;
            s->unk_820 = s->unk_822;
            return 2;
        }
        s->unk_822 = *o;
        s->unk_820 = s->unk_822;
        loc.x = v->x;
        loc.z = v->z;
        s->unk_80C = func_02043d84(s->unk_800, (void *) (&loc.x), c, d, 0xfff1);
        if (s->unk_80C == -1) {
            return 0;
        }
        s->unk_818 = func_0200fea0((UnkStruct_0200fea0 *) s);
        switch (s->unk_818) {
            case 0:
                return 1;
            case 2:
                return 0;
        }
        return 3;
    }
    return 1;
}

int func_0200fd04(int a, int b, int c)
{
    int id = func_0200ffec((struct UnkStruct_0200ffec *) ((void *) a));
    int v0 = 0;
    int v1 = 0;

    func_0204f818(&v0, &v1, (void *) b);

    switch (id) {
        case 3:
        case 4:
        case 21:
        case 22:
            if (c) {
                Pair tmp;
                tmp.x = v0;
                tmp.y = v1;
                func_ov004_0222ac24(a, &tmp, -2, 6, -1);
            } else {
                Pair tmp;
                tmp.x = v0;
                tmp.y = v1;
                func_0200bdbc(a, &tmp, -1, 6, -1);
            }
            return 1;
        case 5: {
            Pair tmp;
            tmp.x = v0;
            tmp.y = v1;
            func_ov003_02218ec4(a, &tmp, 6, -1);
        }
            return 1;
        case 20: {
            Pair tmp;
            tmp.x = v0;
            tmp.y = v1;
            func_ov003_022100c4(a, &tmp, 0, 6, -1);
        }
            return 1;
        default:
            return 0;
    }
}

int func_0200fc90(void *arg0)
{
    UnkStruct_0200fc90 s;
    int flag;

    func_020110c4(&s, arg0);

    if (func_0200f290(arg0, 0) != 0) {
        if (func_0204bcdc(&s) != 0) {
            s.hi = 0xfff1;
            flag = (func_0204bc64(&s) == func_0204bc64(&s.hi));
        } else {
            flag = (s.lo == 0xfff1);
        }

        if (flag == 0) {
            return func_02062148(&s) + 1;
        }
    }

    return 0;
}

int func_0200fbe0(void *argument0)
{
    int x;
    unsigned short v;

    x = func_0200fc90((void *) argument0);
    if (x <= 0) {
        return 0;
    }

    v = (unsigned short) (x + 0x1368);

    if (v <= 0x136a) {
        return 1;
    }
    if (v <= 0x1373) {
        return 2;
    }
    if (v <= 0x1375) {
        return 3;
    }
    if (v <= 0x1377) {
        return 4;
    }
    if (v <= 0x1379) {
        return 5;
    }
    if (v <= 0x137b) {
        return 6;
    }
    if (v == 0x137c) {
        return 7;
    }
    if (v == 0x137d) {
        return 8;
    }
    if (v <= 0x137f) {
        return 9;
    }
    if (v <= 0x13a7) {
        return 10;
    }

    return 0;
}

void func_0200fbc4(int a, int b, int c, int d)
{
    int tmp1 = a;
    int tmp2 = d;
    func_0200fb58((void *) a, (void *) b, (void *) c);
    func_0200fb34((UnkStruct_0200fb34 *) tmp1, tmp2);
}

void func_0200fb7c(char *a0, int a1, int a2, int a3)
{
    char *p = a0 + 0x5c;
    func_020114b0(p, a1, 0x0e66, 0x04cd, 0x31);
    p += 8;
    func_020114b0(p, a2, 0x0e66, 0x04cd, 0x31);
    func_0200fb34((UnkStruct_0200fb34 *) a0, a3);
}

void func_0200fb58(void *a, void *b, void *c)
{
    void *p;
    void *q;

    p = (char *) a + 0x5c;
    func_02011490(p, b);
    q = (char *) p + 8;
    func_02011490(q, c);
}

void func_0200fb34(UnkStruct_0200fb34 *p, int b)
{
    short t;
    t = p->unk_8E;
    func_020113e0(&t, b);
    func_020110a0(p, &t);
}

int func_0200faf0(UnkStruct_0200faf0 *p, int arg2)
{
    int localB;
    short localA;
    int result;
    localA = p->unk_8E;
    localB = 0x000C0000;
    if (func_02011404(&localA, 0, arg2, 0x01770000, localB) == 0) {
        result = 1;
    } else {
        result = 0;
    }
    func_020110a0((UnkStruct_0200fb34 *) p, &localA);
    return result;
}

int func_0200faa8(char *param0, int param1)
{
    short s;
    int ret;

    s = *(short *) (param0 + 0x8e);
    if (func_02011404((void *) (&s), -32768, param1, 0x01770000, 0x000c0000) == 0) {
        ret = 1;
    } else {
        ret = 0;
    }
    func_020110a0((UnkStruct_0200fb34 *) param0, &s);
    return ret;
}

void func_0200fa8c(void *param, int argument1)
{
    void *sp[4];
    func_0200fa6c((int) sp, (int) argument1);
    func_0204f7e0(param, sp);
}

void func_0200fa6c(int a, int b)
{
    func_0200fa1c((struct ThreeInts *) a, b, (struct ThreeInts *) (b + 0x5c), (unsigned short *) (b + 0x8e),
                  (int *) ((unsigned int) data_020c8094));
}

void func_0200fa1c(struct ThreeInts *out, int unused, struct ThreeInts *in, unsigned short *p, int *q)
{
    int v;
    int t;
    int r1, r2;

    out->a = in->a;
    out->b = in->b;
    out->c = in->c;
    v = (*p) >> 4;
    t = 2 * v;
    r1 = FX_MulFunc(FX_SinCosTable_[t + 1], *q);
    r2 = FX_MulFunc(FX_SinCosTable_[t], *q);
    out->a += r2;
    out->c += r1;
}

void func_0200f95c(UnkStruct_0200f95c_2 *self)
{
    short arr[2];
    UnkStruct_0200f95c v;

    if (!(func_02056f28(&self->unk_2D0, 1) || func_02056f28(&self->unk_2D0, 9))) {
        return;
    }

    arr[0] = self->unk_8E;
    arr[1] = arr[0] + 0x8000;

    if (func_02056f28(&self->unk_2D0, 9)) {
        v.x = self->fAx;
        v.y = self->fAy;
        v.z = self->fAz;
    } else {
        v.x = self->fBx;
        v.y = self->fBy;
        v.z = self->fBz;
    }
    v.y = self->unk_60;

    if (self->unk_704 == 2) {
        func_020912d4(0, &v, &arr[1], 0);
    }
    func_020912d4(0x27, &v, &arr[0], 0);

    func_0200f888((UnkStruct_0200f888 *) self);
}

void func_0200f888(UnkStruct_0200f888 *self)
{
    unsigned int flag;
    unsigned int flags = self->flags_b0;
    unsigned int cond0, cond1;
    int local[3];

    cond0 = (flags & 4) ? 1 : 0;
    if (cond0 > 0) {
        cond1 = (flags & 2) ? 1 : 0;
        if (cond1 > 0) {
            return;
        }
    }

    if (func_0200f290(self, 0xa) == 0) {
        return;
    }

    flag = (self->unk_704 == 2) ? 1 : 0;

    local[0] = (self->unk_6C8 + self->unk_6D4) >> 1;
    local[1] = (self->unk_6CC + self->unk_6D8) >> 1;
    local[2] = (self->unk_6D0 + self->unk_6DC) >> 1;

    if (func_0200f290(self, 0x19) != 0) {
        int value = func_020b1cb0(local);
        func_0200443c((int) ((char *) self + 0x83c), value, flag);
    } else {
        int value = func_020b1cb0(local);
        func_0200443c((int) ((char *) self + 0x880), value, flag);
    }
}

int func_0200f86c(int arg)
{
    int local[5];
    local[0] = 0;
    local[1] = 0;
    local[2] = 0;
    local[3] = 0;
    return func_0200f814(arg, (void *) (&local[0]), (struct UnkStruct_0200f814 *) (&local[2]));
}

int func_0200f814(int a, void *b, struct UnkStruct_0200f814 *dst)
{
    volatile unsigned short arr[3];

    arr[0] = (unsigned short) func_020997a8(func_02011368(a));
    arr[2] = arr[0];
    arr[1] = arr[2];
    func_0209e474(b);
    MI_CpuCopy8(b, dst, 8);
    dst->unk_05 = (unsigned char) (((unsigned int) arr[1] << 25) >> 25);
    dst->unk_04 = (unsigned char) (((unsigned int) arr[1] << 21) >> 28);
    dst->unk_03 = (unsigned char) (((unsigned int) arr[1] << 16) >> 27);
    return func_0209e3ac(b, dst, 0x3f);
}

void func_0200f7ac(void *a, int b, UnkStruct_0200f7ac *c)
{
    u16 *p;
    UnkStruct_0200f7ac *q;

    // T is passed by value.
    func_02099794(b, *c);
    p = func_0209d358(0, 0x50);
    // Parenthesised so the call term is added first.
    *p = (u16) (func_020112bc(a) + c->fb * 1000 + c->fc * 10);
    if (func_0200ee0c(a) == 0) {
        q = func_0209627c();
        *q = *c;
    }
}

int func_0200f748(int *arg)
{
    if (func_02073908(data_020ccf94, arg[0x200]) != 0) {
        if (func_0202f188() != 0) {
            func_02008934(arg, 0, 6, -1);
            return 1;
        } else if (((*(unsigned short *) 0x027fffa8) & 0x8000) >> 15) {
            func_02008a54(arg, 1, -1);
            return 1;
        }
    }
    return 0;
}
