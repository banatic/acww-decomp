/* field_actor_20: 9 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_022115a4 @ 0x022115a4, 0x60 bytes, Thumb
 * func_ov003_02211530 @ 0x02211530, 0x74 bytes, Thumb
 * func_ov003_0221138c @ 0x0221138c, 0x1a4 bytes, Thumb
 * func_ov003_0221100c @ 0x0221100c, 0x380 bytes, Thumb
 * func_ov003_02210fa0 @ 0x02210fa0, 0x6c bytes, Thumb
 * func_ov003_02210f58 @ 0x02210f58, 0x48 bytes, Thumb
 * func_ov003_02210f50 @ 0x02210f50, 0x8 bytes, Thumb
 * func_ov003_02210f3c @ 0x02210f3c, 0x14 bytes, Thumb
 * func_ov003_02210ef8 @ 0x02210ef8, 0x44 bytes, Thumb
 */

#include "types.h"

typedef struct Status {
    unsigned char flag;
    unsigned short val;
} Status;

typedef struct Vec {
    unsigned int x;
    unsigned int y;
    unsigned int z;
} Vec;

typedef struct UnkStruct_022115a4 {
    unsigned char pad_00[0x7f0];
    unsigned int flag;
    unsigned char pad_7F4[0x100 - 4];
    unsigned char data;
} UnkStruct_022115a4;

typedef struct {
    char pad_00[0x800];
    int unk_800;
} UnkStruct_02211530;

typedef struct {
    int x, y, z;
} Vec3;

typedef struct {
    int w[12];
} Mtx;

typedef struct {
    Vec3 v;
    unsigned char c0;
    unsigned char c1;
} S7d4;

typedef struct {
    char pad_00[0xc4];
    Vec3 v;
    short d0;
    char pad_D2[0x298 - 0xd2];
    Mtx a;
    char pad_2C8[0x2d8 - 0x2c8];
    unsigned int unk_2D8;
    char pad_2DC[0x62c - 0x2dc];
    Vec3 unk_62C;
    char pad_638[0x698 - 0x638];
    Mtx b;
    char pad_6C8[0x704 - 0x6c8];
    int unk_704;
    char pad_708[0x7d4 - 0x708];
    S7d4 s;
    char pad_7E4[0x800 - 0x7e4];
    int unk_800;
    char pad_804[0x824 - 0x804];
    Vec3 unk_824;
} UnkStruct_0221138c;

typedef struct T12c {
    u8 pad[4];
    int unk_04;
    int unk_08;
} T12c;

typedef struct Pair {
    int x;
    int y;
} Pair;

typedef struct UnkStruct_0221100c {
    u8 pad_00[0xec];
    u8 sub_ec[0x10a - 0xec];
    u8 unk_10A;
    u8 pad_10B[0x12c - 0x10b];
    T12c *unk_12C;
    u8 pad_130[0x2d0 - 0x130];
    u8 sub_2d0[0x2d8 - 0x2d0];
    unsigned int unk_2D8;
    u8 pad_2DC[0x704 - 0x2dc];
    int unk_704;
    u8 pad_708[0x7d4 - 0x708];
    int unk_7D4[3];
    u8 unk_7E0;
    u8 pad_7E1[0x7f0 - 0x7e1];
    int unk_7F0;
    u8 pad_7F4[0x7fc - 0x7f4];
    int unk_7FC;
    int unk_800;
    u8 pad_804[0x80c - 0x804];
    int unk_80C;
    u8 pad_810[0x81c - 0x810];
    int unk_81C;
    u16 unk_820;
} UnkStruct_0221100c;

struct Params {
    char pad_00[0x2d8];
    int unk_2D8;
    char pad_2DC[0x7d4 - 0x2dc];
    int arr_0x7d4[3];
    char pad_7E0[0x800 - 0x7e0];
    int unk_800;
};

typedef struct UnkStruct_02210ef8 {
    unsigned char x, y, z;
} UnkStruct_02210ef8;

typedef struct Src {
    char pad_00[0xc];
    UnkStruct_02210ef8 sub;
} Src;

typedef struct UnkStruct_02210ef8_2 {
    char pad_00[0x7d4];
    unsigned char unk_7D4[3];
    char pad_7D7[0x8f0 - 0x7d4 - 3];
    unsigned char unk_8F0[3];
} UnkStruct_02210ef8_2;

extern void func_ov003_022118b8(unsigned char *data, unsigned int *out, unsigned short *val, unsigned char *flag);
extern void func_0204f794(Vec *vec, unsigned int a, unsigned int b);
extern int func_ov003_022118f8(UnkStruct_022115a4 *self, Vec *vec, unsigned short val, unsigned char flag, int c, int d);
extern int func_02073908(void *, int);
extern int func_0200f290(void *, int);
extern int func_ov003_02221294(int, int *, unsigned char);
extern void func_0200f268(void *, int);
extern void *data_020ccf94;
extern void func_02010f5c(void *self);
extern int func_020912d4(int a, void *b, int c, int d);
extern int func_0200f328(void *self, int a);
extern unsigned int *func_0200f27c(void *self, int a);
extern void func_0204f818(int *a, int *b, void *v);
extern int func_02030db8(int a, int b);
extern void func_0200ee40(void *self);
extern void func_0200f650(void *self, int a);
extern int func_0203f7d0(void *a, void *b);
extern int data_ov003_02238134;
extern int func_02056f94(void *p);
extern int func_02056f28(void *p, int a);
extern void func_020109a0(UnkStruct_0221100c *self, int b, int c, unsigned short d);
extern void func_0203ae98(void);
extern int func_0200faf0(UnkStruct_0221100c *self, int a);
extern int func_02008258(UnkStruct_0221100c *self, int a);
extern int func_0203e1c4(void);
extern void func_0203ee14(UnkStruct_0221100c *self, void *b);
extern void func_0203ee08(UnkStruct_0221100c *self, void *b);
extern int func_020984e8(void);
extern void func_020a8164(void *p, void *g);
extern int func_02099020(int h, int a);
extern void func_02098ff8(int h, int a);
extern void *func_02062f90(void *d, void *s);
extern void func_020683b4(void *a, int b, void *c, int d);
extern void *func_02062f4c(void *d);
extern void func_02035624(int a);
extern void func_02035684(int a, int b, int c);
extern void func_020356c4(int a, int b, int c, int d);
extern int func_02099fe8(void);
extern int func_0203e19c(void);
extern int func_0203b144(void);
extern int func_0206fbc0(void);
extern void *func_ov003_02210c24(UnkStruct_0221100c *self, int a, Pair *p, u16 b, int c, short d);
extern int func_0201100c(void *);
extern int func_0200f434(void *, void *);
extern void func_02010d64(void *);
unsigned int func_0200e92c(void *);
void func_0200e90c(void *, int, int, short);
int func_0200e894(int, void *);
int func_0200e91c(void *);

int func_ov003_02210f58(int a, int *b, int c, int d, short e);

void func_ov003_022115a4(UnkStruct_022115a4 *self, int arg2)
{
    Status status;
    unsigned int out[2];
    Vec vec;
    Vec outVec;

    if (self->flag != 0) {
        return;
    }
    out[0] = 0;
    out[1] = 0;
    func_ov003_022118b8(&self->data, out, &status.val, &status.flag);
    func_0204f794(&vec, out[0], out[1]);
    outVec.x = vec.x;
    outVec.y = vec.y;
    outVec.z = vec.z;
    func_ov003_022118f8(self, &outVec, status.val, status.flag, 6, arg2);
}

void func_ov003_02211530(UnkStruct_02211530 *self, int k)
{
    int loc[3];
    int *p;
    if (func_02073908(data_020ccf94, self->unk_800) == 0) {
        if (func_0200f290(self, 0x1c) != 0) {
            p = (int *) ((char *) self + 0x7d4);
            loc[0] = p[0];
            loc[1] = p[1];
            loc[2] = p[2];
            func_ov003_02221294(self->unk_800, loc, ((unsigned char *) p)[0xd]);
            func_0200f268(self, 0x1c);
            func_0200f268(self, 9);
        }
        if (k != 0x60 && k != 0x61) {
            func_0200f268(self, 0xd);
        }
    }
}

void func_ov003_0221138c(UnkStruct_0221138c *self)
{
    int a, b;
    Vec3 loc;
    volatile Vec3 sv;
    Mtx sa, sb;
    Vec3 copy;
    short d;
    S7d4 *q;
    int tx, ty, tz;
    Vec3 *p;

    func_02010f5c(self);
    if (self->unk_704 == 0x49) {
        return;
    }
    q = &self->s;
    loc.x = q->v.x;
    loc.y = q->v.y;
    loc.z = q->v.z;
    switch ((self->unk_2D8 << 4) >> 16) {
        case 5:
            func_020912d4(6, &loc, 0, 0);
            break;
        case 6:
            func_0200f328(self, 0x841);
            func_0200f27c(self, 9);
            break;
        case 0xc:
            func_020912d4(8, &loc, 0, 0);
            func_0204f818(&a, &b, &loc);
            func_02030db8(a, b);
            copy.x = loc.x;
            copy.y = loc.y;
            copy.z = loc.z;
            func_ov003_02221294(self->unk_800, (int *) (&copy), q->c1);
            func_0200f27c(self, 0xd);
            func_0200f268(self, 0x1c);
            break;
    }
    if (((self->unk_2D8 << 4) >> 16) >= 0x18) {
        func_0200f268(self, 9);
        p = &self->v;
        sv.x = self->v.x;
        sv.y = p->y;
        sv.z = p->z;
        d = self->d0;
        sa = self->a;
        sb = self->b;
        func_0200ee40(self);
        func_0200f650(self, 0x1000);
        self->v.x = sv.x;
        self->v.y = sv.y;
        self->v.z = sv.z;
        self->d0 = d;
        self->a = sa;
        self->b = sb;
    } else {
        tz = self->unk_62C.z;
        ty = self->unk_62C.y;
        tx = self->unk_62C.x;
        self->unk_824.x = tx;
        self->unk_824.y = ty;
        self->unk_824.z = tz;
        func_0203f7d0(&self->unk_824, &self->unk_824);
    }
}

void func_ov003_0221100c(UnkStruct_0221100c *self)
{
    void *g;
    struct {
        int pad;
        int o1[2];
        int o2[2];
        int o3[2];
        Pair p1;
        Pair p2;
        Pair p3;
    } A;
    u8 buf[0x28];
    int v1[3];
    int v2[3];
    int v3[3];
    int *pay;
    u8 *statep;
    int n;
    int h;
    int ok;
    u16 kind;
    void *b;

    if (self->unk_704 == 0x49) {
        if (func_02056f94(self->sub_2d0) == 0) {
            return;
        }
        func_020109a0(self, 0x4f, 3, 0);
        return;
    }

    pay = self->unk_7D4;
    statep = (u8 *) pay + 0xc;
    n = (int) (((unsigned int) self->unk_2D8 << 4) >> 16);
    g = data_020ccf94;
    if (func_02073908(g, self->unk_800) != 0) {
        if (func_02056f28(self->sub_2d0, 0x13) != 0) {
            func_0203ae98();
        }
    }
    if (n < 0x19) {
        return;
    }
    if (func_0200faf0(self, 0x400) == 0) {
        return;
    }
    if (func_02056f94(self->sub_2d0) == 0) {
        return;
    }
    if (func_02073908(g, self->unk_800) == 0) {
        func_0200f268((void *) self, 0x12);
        self->unk_7FC = func_02008258(self, self->unk_7F0);
        return;
    }

    switch (*statep) {
        case 0:
            if (func_0203e1c4() == 0) {
                return;
            }
            *statep = 1;
            b = self;
            if (self != 0) {
                b = (char *) self + 0xec;
            }
            func_0203ee14(self, b);
            func_0200f27c((void *) self, 0x11);
            h = func_020984e8();
            func_020a8164((char *) self + 0xec, &data_ov003_02238134);
            ok = 0;
            if (self->unk_820 >= 0x136a && self->unk_820 <= 0x136a) {
                ok = 1;
            }
            if (ok != 0 && func_02099020(h, 0x27) == 0) {
                self->unk_10A = 0x21;
                func_02098ff8(h, 0x27);
            } else {
                ok = 0;
                if (self->unk_820 >= 0x137b && self->unk_820 <= 0x137b) {
                    ok = 1;
                }
                if (ok != 0 && func_02099020(h, 0x28) == 0) {
                    self->unk_10A = 0x23;
                    func_02098ff8(h, 0x28);
                } else {
                    self->unk_10A = 1;
                    func_02062f90(buf, &self->unk_820);
                    func_020683b4(self->unk_12C, 0, buf, 7);
                    func_02062f4c(buf);
                }
            }
            self->unk_12C->unk_08 = 1;
            func_02035624(0x12);
            func_02035684(0xc, 0, 1);
            func_020356c4(0xd, 0x39, 0x7f, 1);
            self->unk_81C = 0xa;
            break;
        case 1:
            if (self->unk_12C == 0) {
                break;
            }
            if (self->unk_12C->unk_04 == 0) {
                break;
            }
            *statep = 2;
            break;
        case 2:
            if (func_02099fe8() == -1) {
                *statep = 3;
                self->unk_81C = 2;
                break;
            }
            if (self->unk_12C == 0) {
                break;
            }
            if (self->unk_12C->unk_04 != 0) {
                break;
            }
            b = self;
            if (self != 0) {
                b = (char *) self + 0xec;
            }
            func_0203ee08(self, b);
            func_0200f268((void *) self, 0x11);
            func_0203e19c();
            A.o1[0] = 0;
            A.o1[1] = 0;
            v1[0] = pay[0];
            v1[1] = pay[1];
            v1[2] = pay[2];
            func_0204f818(&A.o1[0], &A.o1[1], (void *) v1);
            A.p1.x = A.o1[0];
            A.p1.y = A.o1[1];
            func_ov003_02210f58((int) self, (int *) (&A.p1), 0, 6, -1);
            func_0203b144();
            break;
        case 3:
            if (self->unk_81C >= 0xf) {
                *statep = 4;
                break;
            }
            if (self->unk_12C == 0) {
                break;
            }
            if (self->unk_12C->unk_04 != 0) {
                break;
            }
            b = self;
            if (self != 0) {
                b = (char *) self + 0xec;
            }
            func_0203ee08(self, b);
            func_0200f268((void *) self, 0x11);
            A.o2[0] = 0;
            A.o2[1] = 0;
            v2[0] = pay[0];
            v2[1] = pay[1];
            v2[2] = pay[2];
            func_0204f818(&A.o2[0], &A.o2[1], (void *) v2);
            A.p2.x = A.o2[0];
            A.p2.y = A.o2[1];
            func_ov003_02210f58((int) self, (int *) (&A.p2), 1, 6, -1);
            func_0203b144();
            break;
        case 4:
            if (self->unk_12C == 0) {
                break;
            }
            if (self->unk_12C->unk_04 != 0) {
                break;
            }
            if (func_0206fbc0() == 0) {
                break;
            }
            b = self;
            if (self != 0) {
                b = (char *) self + 0xec;
            }
            func_0203ee08(self, b);
            func_0200f268((void *) self, 0x11);
            func_0203e19c();
            *statep = 5;
            break;
        case 5:
            if (self->unk_80C != -1) {
                break;
            }
            A.o3[0] = 0;
            A.o3[1] = 0;
            v3[0] = pay[0];
            v3[1] = pay[1];
            v3[2] = pay[2];
            func_0204f818(&A.o3[0], &A.o3[1], (void *) v3);
            kind = self->unk_820;
            A.p3.x = A.o3[0];
            A.p3.y = A.o3[1];
            func_ov003_02210c24(self, 2, &A.p3, kind, 6, -1);
            func_0203b144();
            break;
    }
}

void func_ov003_02210fa0(struct Params *param)
{
    func_ov003_0221138c((UnkStruct_0221138c *) param);
    if (func_02073908((void *) ((*(int * *) &data_020ccf94)), param->unk_800) != 0) {
        if (((unsigned int) param->unk_2D8 << 4) >> 16 >= 0x19) {
            func_0201100c(param);
        }
    } else {
        int local[3];
        int *p = param->arr_0x7d4;
        local[0] = p[0];
        local[1] = p[1];
        local[2] = p[2];
        func_0200f434(param, local);
    }
    func_02010d64(param);
    func_ov003_0221100c((UnkStruct_0221100c *) param);
}

int func_ov003_02210f58(int a, int *b, int c, int d, short e)
{
    u8 msg[0x20];
    u8 *out;
    int ret;

    func_0200e92c(msg);
    out = &msg[0xc];
    func_0200e90c(msg, 0x60, d, e);
    out[0] = (u8) b[0];
    out[1] = (u8) b[1];
    out[2] = (u8) c;
    ret = func_0200e894(a, msg);
    func_0200e91c(msg);
    return ret;
}

void func_ov003_02210f50(unsigned char *p0, int p1, int p2, int p3)
{
    p0[0] = p1;
    p0[1] = p2;
    p0[2] = p3;
}

void func_ov003_02210f3c(unsigned char *r0, unsigned char *r1, unsigned char *r2, unsigned char *r3)
{
    *r1 = *r0;
    *r2 = *(r0 + 1);
    *r3 = *(r0 + 2);
}

void func_ov003_02210ef8(UnkStruct_02210ef8_2 *self, Src *src, int previous)
{
    UnkStruct_02210ef8 *p = &src->sub;
    unsigned char *fA = self->unk_7D4;
    unsigned char t2 = p->z;
    unsigned char t0 = src->sub.x;
    unsigned char t1 = p->y;
    fA[2] = t2;
    fA[0] = t0;
    fA[1] = t1;
    func_ov003_02210f50(self->unk_8F0, t0, t1, t2);
    func_020109a0((UnkStruct_0221100c *) ((int) self), 0x50, 3, 0);
    func_0200f328((void *) ((int) self), 0x4f);
}
