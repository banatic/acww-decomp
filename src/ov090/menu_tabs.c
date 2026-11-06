/* menu_tabs: 27 functions, module ov090
 * mwccarm 1.2/base -O4,s
 * func_ov090_0229946c @ 0x0229946c, 0x4 bytes, Thumb
 * func_ov090_02299468 @ 0x02299468, 0x4 bytes, Thumb
 * func_ov090_02299458 @ 0x02299458, 0x10 bytes, Thumb
 * func_ov090_022993cc @ 0x022993cc, 0x8c bytes, Thumb
 * func_ov090_0229936c @ 0x0229936c, 0x60 bytes, Thumb
 * func_ov090_0229934c @ 0x0229934c, 0x1e bytes, Thumb
 * func_ov090_02299348 @ 0x02299348, 0x2 bytes, Thumb
 * func_ov090_0229926c @ 0x0229926c, 0xdc bytes, Thumb
 * func_ov090_02299258 @ 0x02299258, 0x14 bytes, Thumb
 * func_ov090_022991e0 @ 0x022991e0, 0x78 bytes, Thumb
 * func_ov090_022991cc @ 0x022991cc, 0x14 bytes, Thumb
 * func_ov090_0229919c @ 0x0229919c, 0x2e bytes, Thumb
 * func_ov090_0229915c @ 0x0229915c, 0x40 bytes, Thumb
 * func_ov090_02299154 @ 0x02299154, 0x8 bytes, Thumb
 * func_ov090_022990e0 @ 0x022990e0, 0x74 bytes, Thumb
 * func_ov090_022990d0 @ 0x022990d0, 0xe bytes, Thumb
 * func_ov090_022990c8 @ 0x022990c8, 0x8 bytes, Thumb
 * func_ov090_022990b8 @ 0x022990b8, 0x10 bytes, Thumb
 * func_ov090_02299098 @ 0x02299098, 0x20 bytes, Thumb
 * func_ov090_02299078 @ 0x02299078, 0x20 bytes, Thumb
 * func_ov090_02299058 @ 0x02299058, 0x20 bytes, Thumb
 * func_ov090_02298fac @ 0x02298fac, 0xac bytes, Thumb
 * func_ov090_02298fa4 @ 0x02298fa4, 0x8 bytes, Thumb
 * func_ov090_02298f84 @ 0x02298f84, 0x1e bytes, Thumb
 * func_ov090_02298f74 @ 0x02298f74, 0x10 bytes, Thumb
 * func_ov090_02298f48 @ 0x02298f48, 0x2c bytes, Thumb
 * func_ov090_02298f20 @ 0x02298f20, 0x28 bytes, Thumb
 */

#include "types.h"

typedef struct UnkStruct_022993cc {
    u8 pad_00[0x93];
    u8 unk_93;
    u8 unk_94;
    u8 unk_95;
    u8 pad_96;
    u8 unk_97;
    u8 unk_98;
} UnkStruct_022993cc;

struct UnkStruct_0229936c {
    unsigned char pad_00[0x8d];
    unsigned char unk_8D;
    unsigned char pad_8E[5];
    unsigned char unk_93;
    unsigned char pad_94[3];
    unsigned char unk_97;
};

// Case 7 goes to the default; gaps in the jump table need no explicit case.

typedef struct UnkStruct_0229926c {
    char pad_00[0x8d];
    u8 unk_8D;
    char pad_8E[5];
    u8 unk_93;
    char pad_94;
    u8 unk_95;
} UnkStruct_0229926c;

struct UnkStruct_022991cc {
    char pad_00[0x94];
    unsigned char flag;
};

typedef struct {
    unsigned char pad_00[0x91];
    unsigned char unk_91;
    unsigned char unk_92;
} Obj_090;

typedef struct {
    u8 b[0x60];
} UnkStruct_02298fac;

typedef struct UnkStruct_02298fac_2 UnkStruct_02298fac_2;

struct UnkStruct_02298fac_2 {
    u8 unk_00[0x93];
    u8 unk_93;
    u8 p1[2];
    u8 unk_96;
    u8 p2[5];
    u8 unk_9C[0xd4 - 0x9c];
    u8 unk_D4[0x10c - 0xd4];
    u8 unk_10C[0x144 - 0x10c];
    u8 unk_144[0x944 - 0x144];
    UnkStruct_02298fac unk_944[8];
    u8 p3[0x1144 - 0xc44];
    u8 unk_1144[0x20];
};

struct Unk_2298f74 {
    unsigned char pad_00[0x98];
    unsigned char flag;
};

extern void func_020ee470(void *parameter0);
extern void func_0206efc0(void);
extern void func_0200467c(int a);
extern void func_02036468(void *p);
extern void func_0206fbb4(void);
extern void func_0206ef8c(void);
extern unsigned char *func_ov002_022080a0(void *obj, unsigned char value);
extern void func_02001c08(int a);
extern u8 data_020e54a8;
extern int func_0207000c(int);
extern void func_0206fc98(u8);
extern int func_ov002_0220b8ac(void *ptr, int arg);
extern int func_02002d14(void *, int, int, int, int, int);
extern int func_02064af4(void *, void *, int);
extern int func_0206fca4(void);
extern int data_ov090_02299914[];
extern int data_ov090_02299928[];
extern int data_ov090_0229993c[];
extern int data_021fbe94;
extern void func_02036470(void *, int);
extern unsigned char data_021c526c[];
extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;
extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;
extern int _s32_div_f(int, int);
extern unsigned char data_ov090_02299960;
extern void func_020b9ccc(void *p);
extern int func_020b9c10(u8 *, u8 *, int, int, int, int);
extern int func_020b9a18(u8 *, UnkStruct_02298fac *, u8 *, int, int, int, int, int);
extern int func_02064328(u8 *, void *, int);
extern int func_020b9b6c(u8 *, u8 *, int, int);
extern u8 data_ov090_02299900[];
extern char data_ov090_02299820;
void *func_ov002_0220ba0c(void *);
void *func_ov002_0220826c(void *);
void func_ov002_02207f6c(void *);

void func_ov090_0229934c(void *obj);
void func_ov090_02299058(void *self);
void func_ov090_02298fac(UnkStruct_02298fac_2 *self, int idx);

int func_ov090_0229946c(void)
{
    return 1;
}

int func_ov090_02299468(void)
{
    return 1;
}

int func_ov090_02299458(void *arg0)
{
    func_020ee470((void *) arg0);
    return 1;
}

void func_ov090_022993cc(UnkStruct_022993cc *self, u32 p)
{
    u8 v;

    self->unk_98 = 0;
    v = self->unk_93;
    func_ov090_02298fac((UnkStruct_02298fac_2 *) self, p);

    if (p == 7) {
        self->unk_94 = 0;
        if (self->unk_97 == 1) {
            self->unk_97 = 2;
        }
        if (self->unk_97 == 0) {
            func_0206efc0();
        }
        func_0200467c(2);
        func_02036468((*(char **) data_021c526c) + 0x1c4);
    } else if (p <= 6 && v <= 6) {
        func_0200467c(3);
    }

    if (p == 0) {
        func_0206fbb4();
    }

    if (v <= 6 && p <= 6) {
        self->unk_95 = 1;
    }
}

unsigned char func_ov090_0229936c(struct UnkStruct_0229936c *p)
{
    switch (p->unk_93) {
        case 7:
            if (p->unk_97 == 0) {
                func_0206ef8c();
                func_ov090_0229934c((void *) p);
            }
            break;
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
            p->unk_8D = 1;
            break;
        default:
            break;
    }
    return p->unk_93;
}

void func_ov090_0229934c(void *obj)
{
    char *p;
    p = (char *) obj;
    p += 0x8c;
    *p = 2;
    func_ov002_022080a0(obj, 1);
    func_02001c08(1);
}

void func_ov090_02299348(void *callbackObject) {}

void func_ov090_0229926c(UnkStruct_0229926c *o)
{
    int t;

    if ((*(u8 *) &data_ov090_02299960) != 0) {
        return;
    }
    o->unk_95 = 0;
    switch (o->unk_93) {
        case 0:
            t = 0;
            if (data_020e54a8 == 0) {
                t = 1;
            }
            if (t) {
                func_0207000c(2);
            } else {
                func_0207000c(1);
            }
            break;
        case 1:
            func_0207000c(3);
            break;
        case 2:
            func_0207000c(4);
            break;
        case 3:
            func_0207000c(5);
            break;
        case 4:
            func_0207000c(6);
            break;
        case 5:
            func_0207000c(7);
            break;
        case 8:
            func_0207000c(8);
            break;
        case 6:
            func_0207000c(0x24);
            break;
        case 9:
        case 10:
        case 11:
        case 12:
            func_0207000c(0xf);
            func_0206fc98((u8) (o->unk_93 + 0xf));
            break;
        case 13:
        case 14:
            func_0207000c(0x2b);
            func_0206fc98(o->unk_93);
            break;
    }
    o->unk_8D = 0;
}

int func_ov090_02299258(void *p)
{
    return func_ov002_0220b8ac((char *) p + 0x1164, 0);
}

void func_ov090_022991e0(unsigned char *param)
{
    func_02002d14(data_ov090_02299914, data_021fbe94, 8, 0xf, 0xf, 0xf);
    func_02064af4(data_ov090_02299928, param + 0x144, 0x800);
    func_02064af4(data_ov090_0229993c, param + 0x944, 0x800);
    {
        int result = func_0206fca4();
        func_ov090_02298fac((UnkStruct_02298fac_2 *) param, result);
    }
    param[0x91] = 1;
    param[0x92] = 0;
    param[0x8c] = 1;
    func_02001c08(0);
}

void func_ov090_022991cc(struct UnkStruct_022991cc *obj)
{
    obj->flag = 1;
    func_ov002_022080a0(obj, 2);
}

void func_ov090_0229919c(Obj_090 *self)
{
    if (self->unk_92 <= 4) {
        self->unk_91 = 0;
        func_ov002_022080a0(self, 0);
    } else {
        self->unk_92 -= 4;
    }
}

void func_ov090_0229915c(void *arg0)
{
    char *p;
    int *g;
    int *addr;

    p = (char *) arg0;
    p[0x91] = 0;
    p[0x92] = 0;
    p[0x94] = 0;
    p[0x95] = 0;

    func_0200467c(1);

    g = (int *) data_021c526c;
    addr = (int *) (*g + 0x1c4);
    func_02036470(addr, 0);
}

void func_ov090_02299154(void *arg0)
{
    func_ov090_02299058((void *) arg0);
}

int func_ov090_022990e0(void)
{
    unsigned int ok;
    int x, y, q;

    ok = (data_021fbdd8 && data_021fbddc);
    if (ok == 0) {
        return -1;
    }

    x = data_021f6c58;
    y = data_021f6c54;
    if (y > 16) {
        return -1;
    }
    if (x < 53) {
        return -1;
    }
    if (x >= 256) {
        return -1;
    }

    x -= 53;
    q = _s32_div_f(x, 25);
    if (q < 7) {
        return q;
    }
    return 7;
}

void func_ov090_022990d0(unsigned char *p)
{
    p[0x94] = 1;
    p[0x91] = 1;
}

void func_ov090_022990c8(int p0)
{
    *(unsigned char *) ((char *) (((int) (p0) + (148))) + (0)) = 0;
}

int func_ov090_022990b8(int r0)
{
    if (r0 == 7) {
        return 0xf3;
    }
    return r0 * 0x19 + 0x3f;
}

unsigned char func_ov090_02299098(unsigned char x)
{
    if (x > 6) {
        return x;
    }
    data_ov090_02299960 = 10;
    if (x == 0) {
        return 6;
    }
    return (unsigned char) (x - 1);
}

unsigned char func_ov090_02299078(unsigned char x)
{
    data_ov090_02299960 = 0xa;
    if (x > 6) {
        return x;
    }
    if (x == 6) {
        return 0;
    }
    return x + 1;
}

void func_ov090_02299058(void *self)
{
    int i;
    char *base;
    i = 0;
    base = (char *) self + 0x9c;
    for (; i < 3; i++) {
        func_020b9ccc(base + i * 56);
    }
}

void func_ov090_02298fac(UnkStruct_02298fac_2 *self, int idx)
{
    u8 buf[0x24];
    UnkStruct_02298fac *e;
    int t;

    self->unk_93 = (u8) idx;
    if ((unsigned int) idx > 7) {
        return;
    }
    if (idx == self->unk_96) {
        return;
    }
    func_020b9c10(self->unk_9C, self->unk_144, 8, 0x80, 0x80, 0xbf);
    e = &self->unk_944[idx];
    t = idx * 3 + 0x80;
    func_020b9a18(self->unk_D4, e, (u8 *) e + 0x400, 8, t, t + 2, t + 0x20, t + 0x22);
    func_02064328(buf, data_ov090_02299900, idx);
    func_02064af4((void *) buf, (void *) self->unk_1144, 0x20);
    func_020b9b6c(self->unk_10C, self->unk_1144, 8, 0xf);
    self->unk_96 = (u8) idx;
}

void func_ov090_02298fa4(int p0)
{
    *(unsigned char *) ((char *) (((int) (p0) + (151))) + (0)) = 1;
}

int func_ov090_02298f84(int param)
{
    int result = _s32_div_f(param - 0x33, 0x19);
    if (result < 0) {
        result = 0;
    }
    if (result > 7) {
        result = 7;
    }
    return result;
}

int func_ov090_02298f74(struct Unk_2298f74 *self)
{
    if (self->flag == 0) {
        return 0;
    }
    return 1;
}

void *func_ov090_02298f48(void *self)
{
    *(void **) self = &data_ov090_02299820;
    func_ov002_0220ba0c((char *) self + 0x1164);
    func_ov002_0220826c(self);
    func_ov002_02207f6c(self);
    return self;
}

void *func_ov090_02298f20(void *obj)
{
    *(char **) obj = &data_ov090_02299820;
    func_ov002_0220ba0c((char *) obj + 0x1164);
    func_ov002_0220826c(obj);
    return obj;
}
