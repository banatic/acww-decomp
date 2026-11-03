/* missing_npc2: 18 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020c3348 @ 0x020c3348, 0x6 bytes, Thumb
 * func_020c3340 @ 0x020c3340, 0x6 bytes, Thumb
 * func_020c327c @ 0x020c327c, 0xc4 bytes, Thumb
 * func_020c3244 @ 0x020c3244, 0x36 bytes, Thumb
 * func_020c3240 @ 0x020c3240, 0x2 bytes, Thumb
 * func_020c323c @ 0x020c323c, 0x2 bytes, Thumb
 * func_020c31bc @ 0x020c31bc, 0x80 bytes, Thumb
 * func_020c3164 @ 0x020c3164, 0x58 bytes, Thumb
 * func_020c312c @ 0x020c312c, 0x38 bytes, Thumb
 * func_020c309c @ 0x020c309c, 0x90 bytes, Thumb
 * func_020c3060 @ 0x020c3060, 0x3a bytes, Thumb
 * func_020c2f60 @ 0x020c2f60, 0x100 bytes, Thumb
 * func_020c2f3c @ 0x020c2f3c, 0x22 bytes, Thumb
 * func_020c2cf4 @ 0x020c2cf4, 0x248 bytes, Thumb
 * func_020c2ca4 @ 0x020c2ca4, 0x50 bytes, Thumb
 * func_020c2c88 @ 0x020c2c88, 0x1c bytes, Thumb
 * func_020c2c5c @ 0x020c2c5c, 0x2c bytes, Thumb
 * func_020c2c34 @ 0x020c2c34, 0x28 bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned char pad_00[180];
    unsigned long unk_B4;
} UnkStruct_020c3348;

typedef struct {
    unsigned char pad_00[180];
    unsigned long unk_B4;
} UnkStruct_020c3340;

typedef struct {
    int val;
    unsigned char c;
} UnkStruct_020c327c;

typedef struct UnkStruct_020c31bc {
    char pad_00[0x3b0];
    char unk_3B0;
    char pad_3B1[0x1a7];
    char unk_558;
    char pad_559[0xb];
    char unk_564;
    char pad_565[0xec];
    char unk_651;
} UnkStruct_020c31bc;

typedef struct {
    int x;
    int pad_04;
    int y;
} UnkStruct_020c3164;

struct UnkStruct_020c309c {
    char pad_00[0x5c];
    int unk_5C;
    char pad_60[4];
    int unk_64;
};

typedef struct UnkStruct_020c2f60 {
    int a;
    int b;
    int c;
} UnkStruct_020c2f60;

typedef struct UnkStruct_020c2cf4 {
    char pad_00[0x5c];
    char unk_5C[0x8e - 0x5c];
    short unk_8E;
    char pad_90[0x98 - 0x90];
    int unk_98;
    char pad_9C[0x350 - 0x9c];
    char unk_350[0x3aa - 0x350];
    char unk_3AA[0x564 - 0x3aa];
    char unk_564[0x651 - 0x564];
    unsigned char unk_651;
} UnkStruct_020c2cf4;

extern int func_020984e8(void);
extern int func_02099020(int a, int b);
extern int func_0202ea80(int a, int b);
extern void func_02098ff8(int a, int b);
extern int func_020644cc(int x);
extern int data_020e7d0c;
extern int func_02099688(int);
extern int func_020882ec(int);
extern void *func_02015e70(void *, int, int);
extern unsigned short data_020c80f8;
extern unsigned int data_020c814c;
extern char data_021fbee8[];
int func_02019d0c(void *a, int b, int c, int d, int e, int f, int g, int h, int i, int j, int k);
void func_02013c0c(void *a);
void func_0201ad18(void *a, int b, int c, int d, int e, int f, int g, int h);
extern int data_021c67a4;
extern struct T12 {
    int a;
    int b;
    int c;
} data_021c67d0;
extern int func_020e92e8(void *);
extern int FX_MulFunc(int, int);
extern void func_0204f7e0(int *, int *);
extern int func_02078e98(int *, int);
extern short FX_SinCosTable_[];
extern int data_021cb5a0;
extern void func_0201af58(void *dst, void *src, int a, short b);
extern int func_0201ae8c(void *buf);
extern int func_0201ae40(u8 *p);
extern int func_0201aff8(u8 *p, u8 *q, int n);
extern void func_0201afd4(u8 *p, UnkStruct_020c2f60 *s);
extern int func_0201afc0(u8 *p);
extern void func_0201af48(u8 *p);
extern int data_021fbcc0;
extern int data_021fbccc;
extern unsigned char func_020e8858(unsigned char *p);
extern int func_02019de8(void *p);
extern int func_0201b354(void *p);
extern int func_0200322c(void *p, int *v);
extern int func_0201c3dc(int a);
extern int func_02019e00(void *p);
extern void func_020c3690(UnkStruct_020c2cf4 *self, int a);
extern int *func_0201afd0(void *p);
extern void func_02013c04(void *p);
extern char data_020e7ea4;
extern void *func_020c338c(void *);
extern void *func_0202ee5c(void *);
extern void func_020edf54(void *);

void func_020c3348(UnkStruct_020c3348 *p, unsigned long v)
{
    p->unk_B4 = v;
}

unsigned long func_020c3340(UnkStruct_020c3340 *p)
{
    return p->unk_B4;
}

void func_020c327c(void *p, UnkStruct_020c327c *out)
{
    int a;
    unsigned int idx;

    a = func_020984e8();
    out->val = data_020e7d0c;

    if (func_02099020(a, 0x33) == 0) {
        if (func_02099020(a, 0x39) == 0) {
            func_020c3348((UnkStruct_020c3348 *) p, 0);
        } else {
            func_020c3348((UnkStruct_020c3348 *) p, 1);
        }
    } else {
        if (func_0202ea80(0x2a, 0) == 0) {
            func_020c3348((UnkStruct_020c3348 *) p, 2);
        } else {
            func_020c3348((UnkStruct_020c3348 *) p, 3);
        }
    }

    idx = (unsigned int) func_020c3340((UnkStruct_020c3340 *) p);
    switch (idx) {
        case 0:
            func_02098ff8(a, 0x33);
            out->c = 0;
            break;
        case 1:
            func_02098ff8(a, 0x33);
            out->c = (unsigned char) (func_020644cc(3) + 1);
            break;
        case 2:
            out->c = (unsigned char) (func_020644cc(3) + 4);
            func_0202ea80(0x2a, 1);
            break;
        case 3:
            out->c = (unsigned char) (func_020644cc(3) + 7);
            break;
    }
}

void func_020c3244(void *param)
{
    int r4;
    r4 = func_02099688(func_020984e8());
    func_02015e70(param, func_020882ec(r4), 0);
    func_02015e70(param, func_020882ec(r4), 1);
}

void func_020c3240(void) {}

void func_020c323c(void) {}

int func_020c31bc(UnkStruct_020c31bc *self)
{
    self->unk_651 = 0;
    func_02019d0c(&self->unk_564, 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    func_02013c0c(&self->unk_558);
    func_02013c0c(&self->unk_558);
    func_0201ad18(&self->unk_3B0, 1, 0, 0, (unsigned int) data_021fbee8, 4, data_020c814c, 1);
    return 1;
}

int func_020c3164(int arg0, UnkStruct_020c3164 *a, UnkStruct_020c3164 *b)
{
    int result = 0;
    int ok2 = 0;
    int ok1 = 0;

    if ((b->x > a->x - 0x10000) && (b->x < a->x + 0x10000)) {
        ok1 = 1;
    }
    if (ok1 && (b->y > a->y - 0x1a000)) {
        ok2 = 1;
    }
    if (ok2 && (b->y < a->y + 0xa000)) {
        result = 1;
    }

    return result;
}

int func_020c312c(char *arg)
{
    char *p = arg + 0x5c;
    int result = 0;
    if (data_021c67a4 != 0) {
        struct T12 tmp;
        tmp.a = data_021c67d0.a;
        tmp.b = data_021c67d0.b;
        tmp.c = data_021c67d0.c;
        result = func_020c3164((int) arg, (UnkStruct_020c3164 *) (&tmp), (UnkStruct_020c3164 *) p);
    }
    return result;
}

int func_020c309c(struct UnkStruct_020c309c *self, int *out1, int *out2)
{
    int r4;
    int r6;
    int r7;
    int local[3];
    int t1, t2;
    r6 = 0;
    local[0] = r6;
    local[1] = r6;
    local[2] = r6;
    r4 = r6;
    while (r4 < 6) {
        r7 = ((unsigned short) (short) func_020e92e8(&data_021cb5a0) >> 4) << 1;
        t1 = FX_MulFunc(0xc000, FX_SinCosTable_[r7]);
        local[0] = t1 + self->unk_5C;
        t2 = FX_MulFunc(0xc000, FX_SinCosTable_[r7 + 1]);
        local[2] = t2 + self->unk_64;
        func_0204f7e0(local, local);
        if (func_02078e98(local, r6) != 0) {
            *out1 = local[0];
            *out2 = local[2];
            r6 = 1;
            break;
        }
        r4++;
    }
    return r6;
}

int func_020c3060(void *src, void *dest, int param)
{
    char buffer[16];
    int result;

    result = 0;
    func_0201af58(buffer, (char *) src + 0x5c, param, *(short *) ((char *) src + 0x94));
    if (func_0201ae8c(buffer) != 1) {
        ((int *) dest)[0] = ((int *) buffer)[0];
        ((int *) dest)[1] = ((int *) buffer)[1];
        ((int *) dest)[2] = ((int *) buffer)[2];
        result = 1;
    }
    return result;
}

int func_020c2f60(u8 *p)
{
    u8 *pa;
    UnkStruct_020c2f60 loc;
    u8 *pb;
    int kind;
    int ret;

    pa = p + 0x564;
    pb = p + 0x350;
    kind = func_0201ae40(p + 0x3a8);
    ret = 0;
    if (!func_0201aff8(pb, p, 1)) {
        switch (kind) {
            case 3:
                func_02019d0c((void *) pa, 0, 1, 0, 0, 0, 0, 0, 0, (*(u16 *) &data_020c80f8), 0);
                ret = 1;
                break;
            case 1:
                if (func_020c3060((void *) p, (void *) (&loc), (int) (&data_021fbccc))) {
                    func_0201afd4(pb, &loc);
                } else {
                    func_02019d0c((void *) pa, 0, 1, 0, 0, 0, 0, 0, 0, (*(u16 *) &data_020c80f8), 0);
                }
                ret = 1;
                break;
            case 2:
                if (func_020c3060((void *) p, (void *) (&loc), (int) (&data_021fbcc0))) {
                    func_0201afd4(pb, &loc);
                } else {
                    func_02019d0c((void *) pa, 0, 1, 0, 0, 0, 0, 0, 0, (*(u16 *) &data_020c80f8), 0);
                }
                ret = 1;
                break;
        }
    } else {
        if (func_0201afc0(pb)) {
            func_0201af48(pb);
        }
    }
    return ret;
}

int func_020c2f3c(void *param)
{
    int result;
    void *ptr;

    ptr = *(void **) ((char *) param + 0x98);
    if (ptr != 0) {
        result = func_020c2f60((u8 *) param);
        if (result != 0) {
            return 1;
        }
    }
    return 0;
}

static __inline int GetState(UnkStruct_020c2cf4 *self)
{
    return func_02019e00(self->unk_564);
}

int func_020c2cf4(UnkStruct_020c2cf4 *self)
{
    void *sub;
    int ok;
    int dir;
    int mode;
    int *p;
    int v[3];
    int v2[3];

    sub = self->unk_564;
    ok = func_020c312c((char *) self);
    func_020e8858(&self->unk_651);
    if (ok != 0) {
        if (func_020c2f3c((void *) self) == 0) {
            if (func_02019de8(sub) != 0) {
                if (func_0201b354(self->unk_3AA) == 2) {
                    func_02019d0c(sub, 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
                } else if ((func_020e92e8((void *) (&data_021cb5a0)) & 7) == 0) {
                    v[0] = ((int *) data_021fbee8)[0];
                    v[1] = ((int *) data_021fbee8)[1];
                    v[2] = ((int *) data_021fbee8)[2];
                    if (func_020c309c((struct UnkStruct_020c309c *) self, v, &v[2]) != 0) {
                        dir = func_0200322c(self->unk_5C, v);
                        if (func_0201c3dc((short) (dir - self->unk_8E)) != 0) {
                            mode = 1;
                            if (func_020644cc(4) == 0) {
                                mode = 2;
                            }
                            if (mode != GetState(self)) {
                                func_02019d0c(sub, mode, 1, v[0], v[2], 0, 0, 0, 0, data_020c80f8, 0);
                                self->unk_651 = 0x64;
                            }
                        } else {
                            if (GetState(self) != 4) {
                                func_02019d0c(sub, 4, 1, v[0], v[2], 0, dir, 0, 0, data_020c80f8, 0);
                                self->unk_651 = 0x50;
                            }
                        }
                    } else {
                        func_02019d0c(sub, 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
                    }
                } else {
                    func_02019d0c(sub, 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
                }
            } else {
                if (self->unk_98 != 0) {
                    if (GetState(self) == 1 || GetState(self) == 2 || GetState(self) == 4) {
                        if (self->unk_651 == 0) {
                            func_02019d0c(sub, 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
                        } else {
                            p = func_0201afd0(self->unk_350);
                            v2[0] = p[0];
                            v2[1] = p[1];
                            v2[2] = p[2];
                            if (func_0201c3dc((short) (func_0200322c(self->unk_5C, v2) - self->unk_8E)) == 0) {
                                func_02019d0c(sub, 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
                            }
                        }
                    }
                }
            }
        }
    } else {
        if (self->unk_98 != 0) {
            func_020c3690(self, 8);
        }
    }
    return 0;
}

int func_020c2ca4(void *self)
{
    func_02019d0c((char *) self + 0x564, 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    *(unsigned char *) ((char *) self + 0x651) = 0;
    func_02013c04((char *) self + 0x558);
    return 1;
}

int func_020c2c88(int param)
{
    if (func_020c312c((char *) param)) {
        func_020c3690((UnkStruct_020c2cf4 *) param, 7);
    }
    return 1;
}

void *func_020c2c5c(void *self)
{
    *(void **) self = &data_020e7ea4;
    func_020c338c((char *) self + 0x658);
    func_0202ee5c(self);
    func_020edf54(self);
    return self;
}

void *func_020c2c34(void *obj)
{
    *(void **) obj = &data_020e7ea4;
    func_020c338c((char *) obj + 0x658);
    func_0202ee5c(obj);
    return obj;
}
