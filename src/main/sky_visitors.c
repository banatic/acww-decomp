/* sky_visitors: 11 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020c0ad4 @ 0x020c0ad4, 0x48 bytes, Thumb
 * func_020c09b0 @ 0x020c09b0, 0x124 bytes, Thumb
 * func_020c09a8 @ 0x020c09a8, 0x8 bytes, Thumb
 * func_020c08fc @ 0x020c08fc, 0xac bytes, Thumb
 * func_020c08b8 @ 0x020c08b8, 0x44 bytes, Thumb
 * func_020c06d4 @ 0x020c06d4, 0x1e4 bytes, Thumb
 * func_020c06cc @ 0x020c06cc, 0x8 bytes, Thumb
 * func_020c0688 @ 0x020c0688, 0x44 bytes, Thumb
 * func_020c0658 @ 0x020c0658, 0x30 bytes, Thumb
 * func_020c0494 @ 0x020c0494, 0x1c4 bytes, Thumb
 * func_020c048c @ 0x020c048c, 0x8 bytes, Thumb
 */

#include "types.h"

typedef struct {
    char pad_00[0x0c];
    int unk_0C;
    char pad_10[0x48];
    int unk_58;
    char pad_5C[0x04];
    int unk_60;
    int unk_64;
    int unk_68;
} UnkStruct_020c0ad4;

typedef struct {
    char pad_00[0x04];
    int unk_04;
    int unk_08;
    int unk_0C;
    char pad_10[0x24 - 0x10];
    int unk_24;
    char pad_28[0x2e - 0x28];
    unsigned char unk_2E;
    char pad_2F[0x34 - 0x2f];
    int unk_34;
    int unk_38;
    char pad_3C[0x40 - 0x3c];
    int unk_40;
    int unk_44;
    int unk_48;
    int unk_4C;
    char pad_50[0x60 - 0x50];
    int unk_60;
    int unk_64;
    int unk_68;
} UnkStruct_020c09b0;

typedef struct {
    char pad_00[12];
} Elem12;

typedef struct {
    char pad_00[0x34];
    int unk_34;
    int unk_38;
    char pad_3C[0x10];
    int unk_4C;
    char pad_50[0x14];
    int unk_64;
} UnkStruct_020c08fc;

typedef struct {
    char pad_00[0x4c];
    int unk_4C;
    int unk_50;
} Res;

typedef struct {
    char pad_00[0xC];
    int unk_0C;
    char pad_10[0x48];
    int unk_58;
    char pad_5C[0x4];
    int unk_60;
    int unk_64;
    int unk_68;
} UnkStruct_020c08b8;

typedef struct UnkStruct_020c06d4 UnkStruct_020c06d4;

struct UnkStruct_020c06d4 {
    u8 pad_00[0x4];
    int unk_04;
    int unk_08;
    int unk_0C;
    u8 pad_10[0x14];
    int unk_24;
    u8 pad_28[0x6];
    u8 unk_2E;
    u8 pad_2F[0x5];
    int unk_34;
    int unk_38;
    u8 pad_3C[0x4];
    int unk_40;
    int unk_44;
    int unk_48;
    int unk_4C;
    u8 pad_50[0x10];
    int unk_60;
    int unk_64;
    int unk_68;
};

typedef struct Elem12_020c06d4 {
    int a;
    int b;
    int c;
} Elem12_020c06d4;

typedef struct {
    unsigned char pad_00[0x40];
    unsigned int unk_40;
    unsigned int unk_44;
    unsigned int unk_48;
    unsigned int unk_4C;
    unsigned int unk_50;
} UnkStruct_020c0688;

typedef struct {
    char pad_00[8];
    int unk_08;
    int unk_0C;
    char pad_10[0x48];
    int unk_58;
    char pad_5C[4];
    int unk_60;
    int unk_64;
} UnkStruct_020c0658;

typedef struct {
    int x, y, z;
} Vec;

typedef struct UnkStruct_020c0494 UnkStruct_020c0494;

struct UnkStruct_020c0494 {
    char pad_00[4];
    int unk_04;
    int unk_08;
    int unk_0C;
    char sub10[0x24 - 0x10];
    int unk_24;
    char pad_28[0x2e - 0x28];
    unsigned char unk_2E;
    char pad_2F[0x34 - 0x2f];
    Vec unk_34;
    Vec unk_40;
    int unk_4C;
    int unk_50;
    char pad_54[0x60 - 0x54];
    int unk_60;
    int unk_64;
};

extern int func_020644cc(int);
extern void func_020bf568(UnkStruct_020c0ad4 *, int, int);
extern int func_020bf514(void *, int, int, int);
extern int func_020bf308(void *, int, int, int);
extern void func_020bee60(void *, int);
extern void func_020beb78(int, int);
extern void func_020bf26c(void *, int);
extern void func_020bf248(void *, int);
extern void func_020bf5b8(void *);
extern void func_020beb64(int);
extern int FX_MulFunc(int, int);
extern void VEC_Add(void *, void *, void *);
extern Elem12 data_021fa678[];
extern unsigned char data_021fbaf0[];
extern void func_020bf590(void *);
extern int FX_Div(int a, int b);
extern short FX_SinCosTable_[];
extern Res *func_020bdc50(void *a, int b, int c, int *d, int e);
extern void func_0209f128(const void *ptr, int num);
extern unsigned char data_021dc7a8[];
extern int data_021fbee8[3];
extern void func_020beb48(int *);
extern int func_0208a160(void *);
extern void func_02040ba0(int);
extern int func_020952ec(void);
extern int func_02095794(int);
extern int func_020b2b8c(int, int);
extern void func_020beb3c(int *);
extern void func_020beb00(int *, int, int, int, int);
extern void func_020eabc8(void *, int);
extern unsigned char data_021f8b48[];
extern void func_020beb20(int *g);
extern int func_0208a1cc(void *p);
extern void func_0208a158(void *p);
extern void *func_0208a144(void *p);
extern void func_020beb14(int *g);

void func_020c0ad4(UnkStruct_020c0ad4 *s, int flags)
{
    int b;
    int one = 1;

    b = (func_020644cc(2) == 0) ? 1 : 0;
    func_020bf568(s, b, 1000);
    s->unk_0C = one;
    s->unk_58 = 2;
    s->unk_60 = 0;
    s->unk_64 = (flags & one) ? one : 0;
    s->unk_68 = 0;
}

void func_020c09b0(UnkStruct_020c09b0 *self)
{
    int flag;

    if (self->unk_60 == 0) {
        if (func_020bf514(self, 0x1ec, 0x5000, 0x3e8)) {
            self->unk_04 = 3;
        } else {
            if (func_020bf308(self, 0xe000, 0x1a000, (int) 0xffffd000)) {
                int cnt = self->unk_08 + 1;
                func_020bee60(&data_021fa678[self->unk_24], cnt);
                self->unk_08 = cnt;
                func_020beb78((unsigned int) data_021fbaf0, self->unk_64 != 0 ? 1 : 0);
                func_020bf26c(self, 0x7f8);
                self->unk_60 = 1;
            } else {
                func_020bf248(self, 0x7f7);
            }
        }
    } else if (self->unk_60 == 1) {
        self->unk_0C = 0;
        func_020bf5b8(self);
        self->unk_40 = 0;
        self->unk_44 = (int) 0xfffff800;
        self->unk_48 = 0;
        self->unk_60 = 2;
        self->unk_68 = 0;
    } else {
        self->unk_44 += 0x666;
        self->unk_44 = FX_MulFunc(self->unk_44, 0xfd7);
        VEC_Add(&self->unk_34, &self->unk_40, &self->unk_34);
        if (self->unk_38 > 0xd0000) {
            func_020beb64((unsigned int) data_021fbaf0);
            self->unk_04 = 3;
        }
    }

    if (self->unk_60 >= 1) {
        flag = (self->unk_2E == 0) ? 1 : 0;
        func_020beb00((int *) ((unsigned int) data_021fbaf0), self->unk_34, self->unk_38, self->unk_4C, flag);
    }
}

void func_020c09a8(void *argument0)
{
    func_020bf590((void *) argument0);
}

void func_020c08fc(UnkStruct_020c08fc *p)
{
    int t;
    int n;
    int d0;
    int d;
    int t0;
    int idx;
    int vec[3];
    Res *res;

    t = p->unk_64;
    if (t <= 0) {
        return;
    }
    if (t == 1) {
        p->unk_64 = func_020644cc(2) + 1;
        n = func_020644cc(2) + 2;
        d0 = p->unk_4C;
        d = FX_Div(func_020644cc(0x10) << 12, d0);
        idx = ((unsigned short) (short) func_020644cc(0x10000) >> 4) << 1;
        t0 = p->unk_38 + FX_MulFunc(d, FX_SinCosTable_[idx]);
        vec[0] = p->unk_34 + FX_MulFunc(d, FX_SinCosTable_[idx + 1]);
        vec[1] = t0;
        vec[2] = 0;
        res = func_020bdc50(((char *) data_021f8b48), 2, 0x3c, vec, n & 0xf);
        if (res != 0) {
            res->unk_4C = d0;
            res->unk_50 = d0;
        }
    } else {
        p->unk_64 = t - 1;
    }
}

void func_020c08b8(UnkStruct_020c08b8 *obj)
{
    int flag;
    if (func_020644cc(2) == 0) {
        flag = 1;
    } else {
        flag = 0;
    }
    func_020bf568((UnkStruct_020c0ad4 *) obj, flag, 0x1000);
    obj->unk_0C = 0x16;
    obj->unk_58 = 2;
    func_0209f128((void *) data_021dc7a8, 9);
    obj->unk_60 = 0;
    obj->unk_64 = 0;
    obj->unk_68 = 0;
}

void func_020c06d4(UnkStruct_020c06d4 *s)
{
    int state;
    int temp[3];
    int v;
    int ret;

    state = s->unk_60;

    if (state == 0) {
        if (func_020bf514((void *) s, 0x385, 0x1000, 0xfa0) != 0) {
            s->unk_04 = 3;
        } else {
            if (func_020bf308((void *) s, 0x1a000, 0xc000, 0x5000) != 0) {
                func_020bee60(&((Elem12_020c06d4 *) data_021fa678)[s->unk_24], 0x24);
                s->unk_08 = 0x24;
                func_020bf26c((void *) s, 0x7fc);
                func_020beb48(((int *) data_021fbaf0));
                s->unk_60 = 1;
            } else {
                func_020bf248((void *) s, 0x7fb);
            }
        }
    } else if (state == 1) {
        s->unk_0C = 0x17;
        func_020bf5b8((void *) s);
        s->unk_40 = (s->unk_2E != 0) ? 0x2666 : -0x2666;
        s->unk_44 = -0x399A;
        s->unk_48 = 0;
        s->unk_60 = 2;
    } else if (state == 2) {
        if (func_0208a160((char *) s + 0x10) != 0) {
            func_020bee60(&((Elem12_020c06d4 *) data_021fa678)[s->unk_24], 0x25);
            s->unk_08 = 0x25;
            s->unk_60 = 3;
            s->unk_64 = 1;
        }
    } else if (state == 3) {
        s->unk_0C = 0x18;
        func_020bf5b8((void *) s);
        s->unk_60 = 4;
        s->unk_68 = 0;
    } else if (state == 4) {
        if (s->unk_38 > 0xd0000) {
            func_02040ba0(0x44);
            ret = func_02095794((int) func_020952ec());
            func_020b2b8c(ret, (s->unk_2E == 0) ? 1 : 0);
            func_020beb3c(((int *) data_021fbaf0));
            s->unk_04 = 3;
        }
    }

    if (s->unk_60 >= 2) {
        temp[0] = data_021fbee8[0];
        temp[1] = data_021fbee8[1];
        temp[2] = data_021fbee8[2];

        if (s->unk_60 >= 4) {
            temp[0] = (s->unk_2E != 0) ? 0x19a : -0x19a;
            temp[1] = 0x19a;
            v = 0xfd7;
        } else {
            temp[1] = 0x800;
            v = 0x1000;
        }

        VEC_Add(&s->unk_40, temp, &s->unk_40);
        func_020eabc8(&s->unk_40, v);
        VEC_Add(&s->unk_34, &s->unk_40, &s->unk_34);
    }

    if (s->unk_60 >= 1) {
        func_020beb00(((int *) data_021fbaf0), s->unk_34, s->unk_38, s->unk_4C, (s->unk_2E == 0) ? 1 : 0);
    }

    func_020c08fc((UnkStruct_020c08fc *) s);
}

void func_020c06cc(void *argument0)
{
    func_020bf590((void *) argument0);
}

void func_020c0688(int a, int b, int c)
{
    volatile long long unused;
    UnkStruct_020c0688 *obj;

    (void) &unused;
    obj = (UnkStruct_020c0688 *) func_020bdc50((void *) ((unsigned int) data_021f8b48), 2, 0x3c, (int *) a, 0);
    if (obj) {
        obj->unk_4C = b;
        obj->unk_50 = b;
        obj->unk_40 = (unsigned int) FX_MulFunc(c, 0x800);
        obj->unk_44 = 0;
        obj->unk_48 = 0;
    }
}

void func_020c0658(UnkStruct_020c0658 *self)
{
    int flag;

    if (self->unk_08 == 0x28) {
        flag = 1;
    } else {
        flag = 0;
    }

    func_020bf568((UnkStruct_020c0ad4 *) self, flag, 0x8000);

    self->unk_0C = 0x13;
    self->unk_58 = 2;
    self->unk_60 = 0;
    self->unk_64 = 0;
}

void func_020c0494(UnkStruct_020c0494 *p)
{
    int n;
    int old;

    if (p->unk_60 == 0) {
        if (func_020bf514((void *) p, 0x30a, 0x8000, -100) != 0) {
            p->unk_04 = 3;
        } else if (func_020bf308((void *) p, 0x1b000, 0x15000, 0) != 0) {
            n = p->unk_08 + 1;
            func_020bee60((void *) (&((Vec *) data_021fa678)[p->unk_24]), n);
            p->unk_08 = n;
            func_020beb20(((int *) data_021fbaf0));
            func_020bf26c((void *) p, 0x7ff);
            p->unk_60 = 1;
            p->unk_64 = 0;
        } else if (func_0208a1cc(&p->sub10) == 0) {
            old = p->unk_64;
            p->unk_64 = old + 1;
            if (old == 0) {
                func_020bf26c((void *) p, 0x7fe);
            }
        } else {
            p->unk_64 = 0;
        }
    } else if (p->unk_60 == 1) {
        p->unk_0C = 0x14;
        func_020bf5b8((void *) p);
        func_0208a158(&p->sub10);
        p->unk_40.x = p->unk_2E != 0 ? 0x3c00 : -0x3c00;
        p->unk_40.y = -0x4000;
        p->unk_40.z = 0;
        func_020c0688((int) (&p->unk_34), p->unk_4C, p->unk_40.x);
        p->unk_4C = FX_MulFunc(p->unk_4C, 0xe8c);
        p->unk_50 = FX_MulFunc(p->unk_50, 0xe8c);
        p->unk_60 = 2;
        p->unk_64 = 0;
    } else if (p->unk_60 == 2) {
        p->unk_64++;
        if (p->unk_64 >= 1) {
            p->unk_4C = FX_MulFunc(p->unk_4C, 0x119a);
            p->unk_50 = FX_MulFunc(p->unk_50, 0x119a);
            p->unk_60 = 6;
            p->unk_64 = 0;
            func_0208a144(&p->sub10);
        }
    }
    if (p->unk_60 >= 6) {
        p->unk_40.y = p->unk_40.y + 0x59a;
        func_020eabc8((void *) (&p->unk_40), 0x1000);
        VEC_Add((void *) (&p->unk_34), (void *) (&p->unk_40), (void *) (&p->unk_34));
    }
    if (p->unk_60 >= 6) {
        if (p->unk_34.y > 0xd0000) {
            func_020beb14(((int *) data_021fbaf0));
            func_02040ba0(0x45);
            p->unk_04 = 3;
        }
    }
    if (p->unk_60 >= 1) {
        func_020beb00(((int *) data_021fbaf0), p->unk_34.x, p->unk_34.y, p->unk_4C, p->unk_2E != 0 ? 0 : 1);
    }
}

void func_020c048c(void *argument0)
{
    func_020bf590((void *) argument0);
}
