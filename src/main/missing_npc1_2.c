/* missing_npc1_2: 22 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020c26b4 @ 0x020c26b4, 0x64 bytes, Thumb
 * func_020c2640 @ 0x020c2640, 0x74 bytes, Thumb
 * func_020c263c @ 0x020c263c, 0x4 bytes, Thumb
 * func_020c2588 @ 0x020c2588, 0xb4 bytes, Thumb
 * func_020c24d8 @ 0x020c24d8, 0xb0 bytes, Thumb
 * func_020c247c @ 0x020c247c, 0x5c bytes, Thumb
 * func_020c23f8 @ 0x020c23f8, 0x84 bytes, Thumb
 * func_020c2378 @ 0x020c2378, 0x80 bytes, Thumb
 * func_020c234c @ 0x020c234c, 0x2c bytes, Thumb
 * func_020c2348 @ 0x020c2348, 0x4 bytes, Thumb
 * func_020c2344 @ 0x020c2344, 0x4 bytes, Thumb
 * func_020c2324 @ 0x020c2324, 0x20 bytes, Thumb
 * func_020c2300 @ 0x020c2300, 0x24 bytes, Thumb
 * func_020c22c4 @ 0x020c22c4, 0x3c bytes, Thumb
 * func_020c2104 @ 0x020c2104, 0x1c0 bytes, Thumb
 * func_020c2098 @ 0x020c2098, 0x6c bytes, Thumb
 * func_020c1fc8 @ 0x020c1fc8, 0xd0 bytes, Thumb
 * func_020c1fb8 @ 0x020c1fb8, 0x10 bytes, Thumb
 * func_020c1b9c @ 0x020c1b9c, 0x41c bytes, Thumb
 * func_020c1b84 @ 0x020c1b84, 0x18 bytes, Thumb
 * func_020c1b6c @ 0x020c1b6c, 0x18 bytes, Thumb
 * func_020c1b4c @ 0x020c1b4c, 0x20 bytes, Thumb
 */

#include "types.h"

typedef int (*Fn)(void *self);

typedef struct {
    union {
        int ofs;
        Fn fn;
    } u;
    int adj;
    int pad_08[2];
} Pmf;

struct Out1 {
    int a;
    int b;
    int c;
};

struct Out2 {
    int x;
    int y;
    int z;
};

typedef struct {
    u8 pad_00[0x8e];
    u8 unk_8E;
    u8 pad_8F[0x2a0 - 0x8e - 1];
    u8 unk_2A0;
    u8 pad_2A1[0x334 - 0x2a0 - 1];
    u8 unk_334;
    u8 pad_335[0x478 - 0x334 - 1];
    u8 unk_478;
    u8 pad_479[0x564 - 0x478 - 1];
    u8 unk_564;
    u8 pad_565[0x724 - 0x564 - 1];
    u32 unk_724;
} SELF;

struct UnkStruct_020c23f8 {
    char pad_00[0x2a0];
    int unk_2A0;
    char pad_2A4[0x90];
    int unk_334;
    char pad_338[0x1b0];
    int unk_4E8;
    char pad_4EC[0x78];
    int unk_564;
};

typedef struct {
    int x, y, z;
} Vec3;

typedef struct UnkStruct_020c2104 UnkStruct_020c2104;

struct UnkStruct_020c2104 {
    char pad_00[0x5c];
    Vec3 unk_5C;
    char pad_68[0x350 - 0x68];
    int unk_350;
    char pad_354[0x3a8 - 0x354];
    int unk_3A8;
    char pad_3AC[0x510 - 0x3ac];
    unsigned char unk_510;
    char pad_511[0x564 - 0x511];
    int unk_564;
    char pad_568[0x712 - 0x568];
    unsigned short unk_712;
    char pad_714[0x718 - 0x714];
    Vec3 unk_718;
};

typedef struct Vec3_020c1fc8 {
    int x, y, z;
} Vec3_020c1fc8;

typedef struct UnkStruct_020c1fc8 {
    unsigned char pad_00[0x5c];           // 0x00-0x5b
    Vec3_020c1fc8 vec;                    // 0x5c-0x67
    unsigned char pad_68[0x8e - 0x68];    // 0x68-0x8d
    short unk_8E;                         // 0x8e-0x8f
    unsigned char pad_90[0x190 - 0x90];   // 0x90-0x18f
    unsigned int unk_190;                 // 0x190-0x193
    unsigned char pad_194[0x2a0 - 0x194]; // 0x194-0x29f
    unsigned char pad_2A0[0x334 - 0x2a0]; // 0x2a0-0x333
    unsigned char pad_334[0x564 - 0x334]; // 0x334-0x563
} UnkStruct_020c1fc8;

typedef struct {
    int a;
    int b;
    int c;
} Tri;

typedef struct {
    u8 pad_00[0x5c];
    int unk_5C;
    u8 pad_60[0x3b0 - 0x60];
    int unk_3B0;
    u8 pad_3B4[0x564 - 0x3b4];
    int unk_564;
    u8 pad_568[0x618 - 0x568];
    int unk_618;
    u8 pad_61C[0x658 - 0x61c];
    int unk_658;
    u8 pad_65C[0x698 - 0x65c];
    int *unk_698;
    u8 pad_69C[0x728 - 0x69c];
    u8 unk_728;
} UnkStruct_020c1b9c;

extern Pmf data_021fbbfc[];
extern void func_0209129c(int h);
extern int func_02019d0c(void *a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10, int a11);
extern int data_020c814c;
extern unsigned short data_020c80f8;
extern unsigned char data_021fbee8[];
extern unsigned int func_0204e414(void);
extern int func_0204e08c(unsigned int id, void *dst, unsigned int a, unsigned int b);
extern void func_0204f7e0(void *dst, const void *src);
extern int func_02016884(void *, int, void *);
extern int func_02019de8(void *);
extern void func_0201b38c(void *, int);
extern void func_0201b388(void *, int);
extern u32 func_020912d4(int, void *, void *, int);
extern void func_02091278(u32, void *, void *, int);
void func_0201ad18(void *a, int b, int c, int d, void *e, int f, int g, int h);
extern int func_02016104(void *a);
extern int func_0201c314(void *a, int b);
extern int func_020147fc(void *a, int b, int c, int d);
extern int func_02014868(void *);
extern int func_0203e020(void *);
extern int func_020e8840(void *ptr);
extern void *func_020984e8(void);
extern int func_020b65c4(void);
extern void func_0204f794(Vec3 *a, int b, int c);
extern void *func_02095794(int a);
extern int func_0201c378(UnkStruct_020c2104 *p, int a);
extern unsigned int func_02099688(void *a);
extern int func_0208829c(void *);
extern int func_02019e00(void *a);
extern int func_0201ae40(void *a);
extern int func_020ea990(void *a, void *b);
extern void func_0201b044(void *a, void *b);
extern int func_0208602c(void);
extern int func_020860c4(int);
extern void func_02087f20(void *);
extern int func_02019c20(void *ptr, int a, int b, int c, unsigned short e, int f);
extern void func_020c1b28(void *ptr, int a);
extern int func_020044c0(void *ptr, int a, int b, int c);
extern void *data_020ccf94;
extern u8 data_021c75b8;
extern Tri data_020d3150;
extern void *data_020e7ad8;
extern void *func_020a13d0(void);
extern void *func_020984fc(void *);
extern int func_02095ed0(int, void *);
extern int func_02095ab0(Tri *, int, void *);
extern int func_0209615c(void *);
extern int func_020147e0(void *, int, int);
extern void func_02068440(int *);
extern void func_020c37f8(void);
extern void func_0203aed8(void);
extern int func_02082644(int);
extern void func_020160d8(void *, int);
extern void func_0206844c(int *, u8 *, void *);
extern void func_02068434(int *);
extern int func_0200322c(void *, Tri *);
extern int func_02095a8c(int, void *);
extern void func_020c37dc(void);
extern int func_020a1380(void);
extern void func_020b8dc0(void);
extern int func_02073918(void *, int);
extern int func_020882c4(unsigned char *);
extern void func_020882f0(void *);
extern void func_02098ff8(void *, int);
extern void func_02088198(void *);
extern int func_020b5e10(void);
extern int func_020b6098(int, int);
extern void *func_0202eb70(void *self);
extern void *func_0202eb20(void *);
extern void func_020edb3c(void *self);
extern unsigned char data_020e7bd0[];

void func_020c26b4(void *self, int i)
{
    int ok;
    Pmf *e;
    int adj;
    char *t;
    Fn f;

    ok = 1;
    e = &data_021fbbfc[i];
    if (e->u.ofs != 0) {
        adj = e->adj;
        t = (char *) self + (adj >> 1);
        if (adj & 1) {
            f = *(Fn *) (*(char **) t + e->u.ofs);
        } else {
            f = e->u.fn;
        }
        ok = f(t);
    }
    if (ok) {
        if (i != 1 && *(int *) ((char *) self + 0x724) != -1) {
            func_0209129c(*(int *) ((char *) self + 0x724));
            *(int *) ((char *) self + 0x724) = -1;
        }
        *(int *) ((char *) self + 0x654) = i;
    }
}

int func_020c2640(void *obj)
{
    *(int *) ((char *) obj + 0x4e8) |= 2;
    func_0201ad18((char *) obj + 0x3b0, 1, 0, 0, (void *) ((unsigned int) data_021fbee8), 4, data_020c814c, 1);
    func_02019d0c((char *) obj + 0x564, 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    return 1;
}

int func_020c263c(void)
{
    return 1;
}

int func_020c2588(void *self)
{
    int *flags = (int *) ((char *) self + 0x4e8);
    struct Out1 out1;
    struct Out2 out2;
    unsigned int id;

    *flags |= 2;

    func_0201ad18((char *) self + 0x3b0, 0, 0, 0, (void *) ((void *) data_021fbee8), 4, (*(unsigned int *) &data_020c814c), 1);

    func_02019c20((char *) self + 0x564, 1, 0x53, 1, data_020c80f8, 0);

    id = func_0204e414();

    func_0204e08c(id, &out1, 0, 0);
    func_0204f7e0(&out2, (char *) self + 0x5c);

    if (out2.z >= out1.c) {
        goto skip;
    }
    if (out2.x < out1.a - 0x4000) {
        goto skip;
    }
    if (out2.x > out1.a + 0x4000) {
        goto skip;
    }

    *(int *) ((char *) self + 0x64) = out1.c + 0x1000;

skip:
    *((unsigned char *) self + 0x510) = 1;
    return 1;
}

int func_020c24d8(SELF *self)
{
    if (func_02016884(&self->unk_334, 0x53, &self->unk_2A0) && func_02019de8(&self->unk_564)) {
        func_02019d0c(&self->unk_564, 0, 1, 0, 0, 0, 0, 0, 0, (*(u16 *) &data_020c80f8), 0);
        func_0201b38c(&self->unk_2A0, 0x54);
        func_0201b388(&self->unk_2A0, 0x54);
    }

    if (self->unk_724 == (u32) -1) {
        self->unk_724 = func_020912d4(0x54, &self->unk_478, &self->unk_8E, 0);
    }
    if (self->unk_724 != (u32) -1) {
        func_02091278(self->unk_724, &self->unk_478, &self->unk_8E, 0);
    }

    return 1;
}

int func_020c247c(char *self)
{
    func_0201ad18(self + 0x3b0, 0, 0, 0, (void *) data_021fbee8, 4, (*(unsigned int *) &data_020c814c), 1);
    func_02019c20(self + 0x564, 1, 0xab, 1, data_020c80f8, 0);
    return 1;
}

int func_020c23f8(struct UnkStruct_020c23f8 *p)
{
    p->unk_4E8 |= 2;
    if (func_02016884((void *) (&p->unk_334), 0xab, (void *) (&p->unk_2A0)) && func_02019de8((void *) (&p->unk_564))) {
        func_02019d0c((void *) (&p->unk_564), 0, 1, 0, 0, 0, 0, 0, 0, (unsigned short) data_020c80f8, 0);
        func_0201b38c((void *) (&p->unk_2A0), 0xac);
        func_0201b388((void *) (&p->unk_2A0), 0xac);
    }
    return 1;
}

int func_020c2378(void *self)
{
    int ret;
    int size;

    func_0201ad18((char *) self + 0x3b0, 1, 0, 0, (void *) data_021fbee8, 4, data_020c814c, 1);
    size = func_02016104((char *) self + 0x658);
    ret = 0;
    if (size != 0) {
        ret = func_0201c314(self, size);
    }
    func_0201b38c((char *) self + 0x2a0, 0xac);
    func_0201b388((char *) self + 0x2a0, 0xac);
    func_020147fc((char *) self + 0x618, 0, ret, 0);
    return 1;
}

int func_020c234c(void *arg0)
{
    void *r4;
    int result;

    r4 = arg0;
    result = func_02014868((char *) r4 + 0x618);
    if (result == 0) {
        func_0203e020(r4);
        func_020c26b4(r4, 7);
    }
    return 1;
}

int func_020c2348(void)
{
    return 1;
}

int func_020c2344(void)
{
    return 1;
}

// placeholder, not used
// placeholder, not used
int func_020c2324(void *arg0)
{
    unsigned int *ptr;
    unsigned int val;

    ptr = (unsigned int *) ((char *) arg0 + 0x4e8);
    val = *ptr;
    *ptr = val & ~2u;
    *(unsigned short *) ((char *) arg0 + 0x714) = 0x28;
    return 1;
}

int func_020c2300(void *ptr)
{
    if (func_020e8840((char *) ptr + 0x714) == 0) {
        func_020c26b4(ptr, 5);
    }
    return 1;
}

int func_020c22c4(void *self)
{
    unsigned int *p = (unsigned int *) ((char *) self + 0x4e8);
    *p &= ~2;
    *(unsigned short *) ((char *) self + 0x712) = 0x28;
    *(unsigned int *) ((char *) self + 0x718) = *(unsigned int *) ((char *) self + 0x5c);
    *(unsigned int *) ((char *) self + 0x71c) = *(unsigned int *) ((char *) self + 0x60);
    *(unsigned int *) ((char *) self + 0x720) = *(unsigned int *) ((char *) self + 0x64);
    return 1;
}

int func_020c2104(UnkStruct_020c2104 *p)
{
    Vec3 v1, v2, v3, v4;
    void *a;
    void *c;
    int b, d, e;

    a = func_020984e8();
    if (a == 0) {
        return 1;
    }
    if (p->unk_510 == 0 && func_020b65c4() == 0) {
        func_0204e08c((unsigned int) ((void *) func_0204e414()), (void *) (&v1), 0, 0);
        func_0204f7e0((void *) (&v2), (const void *) (&p->unk_5C));
        if (v2.z > v1.z) {
            p->unk_510 = 1;
        }
    }
    if (p->unk_510 == 0 && func_020b65c4() == 0xb) {
        func_0204f7e0((void *) (&v4), (const void *) (&p->unk_5C));
        func_0204f794(&v3, 6, 0xf);
        if (v4.z < v3.z) {
            p->unk_510 = 1;
        }
    }
    c = func_02095794(4);
    if (c == 0) {
        return 1;
    }
    b = func_0201c378(p, 4);
    if (func_020b65c4() != 0) {
        if (func_020b65c4() != 0xc) {
            goto lab;
        }
        if (func_0208829c((void *) func_02099688(a)) != 0) {
            goto lab;
        }
    }
    if (func_02019e00(&p->unk_564) != 2) {
        goto lab;
    }
    if (b > 0x6000) {
        func_020c26b4((void *) p, 6);
        return 1;
    }
    d = func_0201ae40(&p->unk_3A8);
    e = func_020ea990(&p->unk_718, &p->unk_5C);
    p->unk_718.x = p->unk_5C.x;
    p->unk_718.y = p->unk_5C.y;
    p->unk_718.z = p->unk_5C.z;
    if (e <= 0x29 || d != 0) {
        if (func_020e8840(&p->unk_712) != 0) {
            goto lab;
        }
        func_020c26b4((void *) p, 1);
        return 1;
    } else {
        p->unk_712 = 0x28;
    }
lab:
    if (b > 0x2800) {
        if (func_02019e00(&p->unk_564) != 2) {
            func_02019d0c(&p->unk_564, 2, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
        }
        func_0201b044(&p->unk_350, c);
    } else {
        if (func_02019e00(&p->unk_564) != 0) {
            func_02019d0c(&p->unk_564, 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
        }
    }
    return 1;
}

int func_020c2098(void *p)
{
    if (func_020b65c4() == 0) {
        func_02087f20((void *) func_020860c4((int) func_0208602c()));
    }
    func_02019c20((char *) p + 0x564, 1, 0x122, 1, data_020c80f8, 0);
    func_020c1b28((char *) p + 0x658, 4);
    func_020044c0((char *) p + 0x514, 0x7db, 0x7f, 0);
    return 1;
}

int func_020c1fc8(UnkStruct_020c1fc8 *self)
{
    Vec3_020c1fc8 vec;
    Vec3_020c1fc8 *vp;
    short s;

    if (func_02016884((void *) ((char *) self + 0x334), 0x122, (void *) ((char *) self + 0x2a0))) {
        s = self->unk_8E;
        vp = &self->vec;
        vec.x = self->vec.x;
        vec.y = vp->y;
        vec.z = vp->z;
        if (((self->unk_190 << 4) >> 16) == 7) {
            func_020912d4(0x39, &vec, &s, 0);
        }
        if (((self->unk_190 << 4) >> 16) == 9) {
            func_020912d4(0x38, &vec, &s, 0);
        }
        if (func_02019de8((void *) ((char *) self + 0x564))) {
            func_02019c20((void *) ((char *) self + 0x564), 1, 0x123, 1, data_020c80f8, 0);
        }
    }
    if (func_02016884((void *) ((char *) self + 0x334), 0x123, (void *) ((char *) self + 0x2a0))) {
        if (func_02019de8((void *) ((char *) self + 0x564))) {
            func_020c26b4(self, 1);
        }
    }
    return 1;
}

char func_020c1fb8(void *arg0)
{
    char *ptr;
    char value;

    ptr = (char *) arg0;
    value = 0;
    ptr[0x728] = value;
    return 1;
}

int func_020c1b9c(UnkStruct_020c1b9c *self)
{
    void *local1c;
    u8 b20;
    Tri v;
    Tri tmp;
    void *a;
    void *g;
    void *b;
    void *x;
    unsigned int ok;
    int t;

    a = func_020a13d0();
    g = data_020ccf94;
    b = *(void **) ((char *) g + 0x68);
    local1c = func_020984fc(a);
    switch (self->unk_728) {
        case 0:
            if (data_021c75b8 == 2) {
                ok = 1;
            } else {
                ok = 0;
            }
            if (ok == 0) {
                break;
            }
            if (func_02095ed0(1, a) == 0) {
                break;
            }
            self->unk_728 = 1;
            break;
        case 1:
            tmp.a = data_020d3150.a;
            tmp.b = data_020d3150.b;
            tmp.c = data_020d3150.c;
            func_02095ab0(&tmp, 0x35c, a);
            func_02019d0c(&self->unk_564, 1, 1, 0xe000, 0x10800, 0, 0, 0, 0, (*(u16 *) &data_020c80f8), 0);
            self->unk_728 = 2;
            break;
        case 2:
            if (func_0209615c(a) != 0) {
                break;
            }
            if (func_02019de8(&self->unk_564) == 0) {
                break;
            }
            self->unk_728 = 3;
            func_020c1b28(&self->unk_658, 6);
            func_0201ad18(&self->unk_3B0, 0, 0, 0, (void *) ((const void *) data_021fbee8), 4, data_020c814c, 1);
            func_02019d0c(&self->unk_564, 0, 1, 0, 0, 0, 0, 0, 0, (*(u16 *) &data_020c80f8), 0);
            func_020147e0(&self->unk_618, 0, 1);
            break;
        case 3:
            if (self->unk_698[1] != 5) {
                break;
            }
            func_02068440(self->unk_698);
            func_02019d0c(&self->unk_564, 2, 2, 0xea00, 0x12e00, 0, 0, 0, 0, (*(u16 *) &data_020c80f8), 0);
            func_020c37f8();
            func_0203aed8();
            self->unk_728 = 4;
            break;
        case 4:
            if (func_02019de8(&self->unk_564) == 0) {
                break;
            }
            func_02019d0c(&self->unk_564, 0, 1, 0, 0, 0, 0, 0, 0, (*(u16 *) &data_020c80f8), 0);
            func_0201ad18(&self->unk_3B0, 1, 0, 0, (void *) ((const void *) data_021fbee8), 4, data_020c814c, 1);
            t = func_02082644(0x23);
            if (t != 0) {
                func_020160d8(&self->unk_658, t);
            }
            b20 = 0xa;
            func_0206844c(self->unk_698, &b20, data_020e7ad8);
            self->unk_698[2] = 1;
            func_02068434(self->unk_698);
            self->unk_728 = 5;
            break;
        case 5:
            if (func_02014868(&self->unk_618) != 0) {
                break;
            }
            v.a = 0xde00;
            v.b = 0;
            v.c = 0x13a00;
            func_02019d0c(&self->unk_564, 3, 1, 0, 0, 0, func_0200322c(&self->unk_5C, &v), 0, 0, (*(u16 *) &data_020c80f8), 0);
            self->unk_728 = 6;
            break;
        case 6:
            if (func_02019de8(&self->unk_564) == 0) {
                break;
            }
            func_02019d0c(&self->unk_564, 1, 1, 0xde00, 0x13a00, 0, 0, 0, 0, (*(u16 *) &data_020c80f8), 0);
            func_02095a8c(0, a);
            func_020c37dc();
            self->unk_728 = 7;
            break;
        case 7:
            if (func_02019de8(&self->unk_564) == 0) {
                break;
            }
            func_02019d0c(&self->unk_564, 3, 1, 0, 0, 0, 0, 0, 0, (*(u16 *) &data_020c80f8), 0);
            self->unk_728 = 8;
            break;
        case 8:
            if (func_02019de8(&self->unk_564) == 0) {
                break;
            }
            func_02019d0c(&self->unk_564, 1, 1, 0xf000, 0x1d000, 0, 0, 0, 0, (*(u16 *) &data_020c80f8), 0);
            self->unk_728 = 9;
            break;
        case 9:
            if (func_02019de8(&self->unk_564) == 0) {
                break;
            }
            if (a != b && func_020a1380() == 0) {
                func_020b8dc0();
            } else {
                self->unk_728 = 0xa;
            }
            break;
        case 10:
            if (func_02073918(g, 0) != 0) {
                x = (void *) func_02099688(func_020984e8());
                if (func_020882c4(x) == 1) {
                    func_020882f0(x);
                }
                func_02098ff8(func_020984e8(), 0x39);
                func_020882f0((void *) func_02099688(local1c));
                func_02088198((void *) func_020860c4((int) func_0208602c()));
                func_020b6098(func_020b5e10(), 1);
            }
            if (a == b) {
                func_020882f0((void *) func_02099688(func_020984e8()));
                func_02088198((void *) func_020860c4((int) func_0208602c()));
                func_02098ff8(func_020984e8(), 0x31);
                func_020b6098(func_020b5e10(), 0);
            } else {
                func_020b6098(func_020b5e10(), 1);
            }
            self->unk_728 = 0xb;
            break;
    }
    return 1;
}

void *func_020c1b84(void *self)
{
    func_0202eb70(self);
    *(void **) self = ((char *) data_020e7bd0);
    return self;
}

void *func_020c1b6c(void *p)
{
    *(void **) p = (void *) ((char *) data_020e7bd0);
    func_0202eb20(p);
    return p;
}

void *func_020c1b4c(void *self)
{
    *((unsigned int *) self) = (unsigned int) data_020e7bd0;
    func_0202eb20(self);
    func_020edb3c(self);
    return self;
}
