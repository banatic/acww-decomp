/* scene_face: 17 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0201a2e8 @ 0x0201a2e8, 0x1c bytes, Thumb
 * func_0201a2d4 @ 0x0201a2d4, 0x12 bytes, Thumb
 * func_0201a2c8 @ 0x0201a2c8, 0xa bytes, Thumb
 * func_0201a2a8 @ 0x0201a2a8, 0x20 bytes, Thumb
 * func_0201a27c @ 0x0201a27c, 0x2a bytes, Thumb
 * func_0201a234 @ 0x0201a234, 0x46 bytes, Thumb
 * func_0201a1d4 @ 0x0201a1d4, 0x60 bytes, Thumb
 * func_0201a19c @ 0x0201a19c, 0x38 bytes, Thumb
 * func_0201a174 @ 0x0201a174, 0x28 bytes, Thumb
 * func_0201a0dc @ 0x0201a0dc, 0x98 bytes, Thumb
 * func_0201a090 @ 0x0201a090, 0x4c bytes, Thumb
 * func_0201a054 @ 0x0201a054, 0x3a bytes, Thumb
 * func_0201a038 @ 0x0201a038, 0x1c bytes, Thumb
 * func_0201a028 @ 0x0201a028, 0x10 bytes, Thumb
 * func_0201a020 @ 0x0201a020, 0x8 bytes, Thumb
 * func_02019ff0 @ 0x02019ff0, 0x2e bytes, Thumb
 * func_02019f1c @ 0x02019f1c, 0xd4 bytes, Thumb
 */

#include "types.h"

typedef struct {
    char pad_00[0x80];
    int unk_80;
} UnkStruct_0201a2d4;

struct UnkStruct_0201a27c;

struct UnkStruct_0201a27c {
    char pad_00[0x50];
    int unk_50;
    char pad_54[0x24];
    int unk_78;
    int pad_7C;
    int *unk_80;
};

typedef struct {
    char pad_00[0x48];
    char unk_48;
    char pad_49[0x4c - 0x49];
    unsigned int unk_4C;
    unsigned int unk_50;
    char pad_54[0x78 - 0x54];
    unsigned int unk_78;
    char pad_7C[0x80 - 0x7c];
    void *unk_80;
} UnkStruct_0201a234;

struct UnkStruct_0201a1d4 {
    char pad_00[0x14];
    void *unk_14;
    char pad_18[0x30];
    void *unk_48;
    char pad_48_50[4];
    int unk_50;
    char pad_54[0x24];
    void *unk_78;
};

typedef struct {
    unsigned char pad_00[0x78];
    unsigned int unk_78;
    unsigned int unk_7C;
} UnkStruct_0201a19c;

typedef struct UnkStruct_0201a0dc {
    u8 pad_00[0x14];
    u8 unk_14[8];
    u32 unk_1C;
    u8 pad_20[0x24 - 0x20];
    u32 unk_24;
    u8 pad_28[0x74 - 0x28];
    u32 unk_74;
    u32 unk_78;
    u32 unk_7C;
} UnkStruct_0201a0dc;

typedef struct UnkStruct_02019f1c {
    char pad_00[0x1c];
    char sub1c[0x48 - 0x1c];
    char sub48[0x74 - 0x48];
    int unk_74;
    int unk_78;
} UnkStruct_02019f1c;

typedef struct Other {
    char pad_00[0x418];
    int unk_418;
} Other;

extern int func_0201a798(void);
extern int func_02056f94(void *p);
extern int func_0201a3e8(void *);
extern void **func_02082da8(void **);
extern void func_0205d7b8(void **, void *, int, int);
extern void *func_0205d894(void **);
extern void func_0205678c(void **, void *, int, int, int, int);
extern void func_02056730(void **);
extern unsigned int data_020c8170[];
extern int func_0205d8a0(void *p);
extern unsigned char *NNS_G3dGetAnmByIdx(int a, int b);
extern int func_0205cf28(int b);
extern int func_0205cf1c(int b);
extern void func_02056658(int a1, int a2);
extern int func_020566a0(int a1, int a2, int a3);
extern void func_02056610(int a1, int a2);
extern char data_020d8d18;
extern void func_020645bc(unsigned char *);
extern void func_0205682c(void *);
extern void func_02083068(void *);
extern int func_02056f28(void *buf, int n);
extern int func_020645e0(UnkStruct_02019f1c *self);
extern void func_02056778(void *p);
extern int func_0201a7b4(int *p);
extern int func_0201a7bc(int *p);

int func_0201a2e8(void *unused, int value)
{
    return (value == 0x137 || value == 0x138);
}

void func_0201a2d4(UnkStruct_0201a2d4 *ptr)
{
    ptr->unk_80 = func_0201a798();
}

int func_0201a2c8(int a, int b)
{
    int r = 0;
    if (b == 1) {
        r = 5;
    }
    return r;
}

int func_0201a2a8(int unused, int a, int b, int c)
{
    int ret = 0;
    if (a == 0) {
        if (b == 5) {
            ret = 1;
        }
    } else if (b >= c - 0x1000) {
        ret = 1;
    }
    return ret;
}

void func_0201a27c(struct UnkStruct_0201a27c *self)
{
    if (func_0201a2e8((void *) self, self->unk_78)) {
        func_0201a2d4((UnkStruct_0201a2d4 *) self);
        self->unk_50 = func_0201a2c8((int) self, (int) self->unk_80) << 12;
    }
}

int func_0201a234(UnkStruct_0201a234 *param)
{
    int ret = 0;
    if (func_0201a2e8((void *) param, param->unk_78)) {
        ret = func_0201a2a8((int) param, (int) param->unk_80, (param->unk_50 << 4) >> 16, (param->unk_4C << 4) >> 16);
    } else {
        if (func_02056f94(&param->unk_48)) {
            ret = 1;
        }
    }
    return ret;
}

void func_0201a1d4(struct UnkStruct_0201a1d4 *a, void *b, int c)
{
    void **p;
    void *q;

    if (func_0201a3e8(a) == 0) {
        return;
    }
    p = func_02082da8(&a->unk_14);
    func_0205d7b8(p, b, 1, 0);
    q = func_0205d894(p);
    func_0205678c(&a->unk_48, q, 0, 0, c, 0x1000);
    a->unk_50 = 0;
    a->unk_78 = b;
    func_0201a27c((struct UnkStruct_0201a27c *) a);
    func_02056730(&a->unk_48);
}

void func_0201a19c(UnkStruct_0201a19c *obj, int index)
{
    if (index < 0 || index >= 2) {
        return;
    }
    if (func_0201a2e8(obj, obj->unk_78) == 0) {
        obj->unk_7C = obj->unk_78;
    }
    func_0201a1d4((struct UnkStruct_0201a1d4 *) obj, (void *) data_020c8170[index], 0);
}

void func_0201a174(void *param1)
{
    int temp;

    if (*(int *) ((char *) param1 + 0x7c) == 0x16f) {
        *(int *) ((char *) param1 + 0x7c) = 0xba;
    }

    temp = *(int *) ((char *) param1 + 0x7c);
    func_0201a1d4((struct UnkStruct_0201a1d4 *) param1, (void *) temp, 0);
    *(int *) ((char *) param1 + 0x7c) = 0x16f;
}

void func_0201a0dc(UnkStruct_0201a0dc *self, int a, int b, int c, int d)
{
    void *r7;

    if (func_0201a3e8(self) == 0) {
        return;
    }

    r7 = (void *) func_02082da8((void **) self->unk_14);

    if (a != 0 || self->unk_74 != a) {
        func_0205d7b8((void **) r7, (void *) a, 1, 0);
        NNS_G3dGetAnmByIdx(func_0205d8a0(r7), 0);
        func_0205678c((void **) (&self->unk_1C), (void *) (func_0205d8a0(r7)), 0, 0, c, 0x1000);
        self->unk_74 = a;
        self->unk_24 = 0;
        func_02056730((void **) (&self->unk_1C));
    }

    if (d == 2 || func_0201a2e8(self, self->unk_78) == 0) {
        func_0201a1d4((struct UnkStruct_0201a1d4 *) self, (void *) b, 0);
    } else {
        self->unk_7C = b;
    }
}

void func_0201a090(int a, int b, int c, int d)
{
    int x, y;
    if (func_0201a3e8((void *) a)) {
        x = func_0205cf28(b);
        y = func_0205cf1c(b);
        if (x == 0x16f) {
            x = 0;
        }
        if (y == 0x16f) {
            y = 0xba;
        }
        func_0201a0dc((UnkStruct_0201a0dc *) a, x, y, c, d);
    }
}

int func_0201a054(int a0, int a1, int a2, int a3)
{
    if (func_0201a3e8((void *) a0)) {
        func_02056658(a1, a2);
        if (func_020566a0(a1, a2, a3)) {
            return 1;
        }
        func_02056610(a1, a2);
    }
    return 0;
}

void func_0201a038(char *arg0, char *arg1)
{
    func_0201a054((int) arg0, (int) (arg0 + 0x48), (int) (&data_020d8d18), (int) arg1);
}

void func_0201a028(char *r0)
{
    func_02056610((int) (r0 + 0x48), (int) (((int *) &data_020d8d18)));
}

void func_0201a020(unsigned char *argument0)
{
    func_020645bc((unsigned char *) argument0);
}

void func_02019ff0(void *arg0)
{
    func_0205682c((char *) arg0 + 0x1c);
    func_0205682c((char *) arg0 + 0x48);
    func_02083068((char *) arg0 + 0xc);
    func_02083068((char *) arg0 + 0x14);
    func_02083068((char *) arg0 + 4);
}

void func_02019f1c(UnkStruct_02019f1c *self, Other *other)
{
    if (func_0201a3e8((void *) self) == 0) {
        return;
    }

    if (self->unk_74 == 0) {
        if (func_02056f28(&self->sub1c, 0) == 0 || func_020645e0(self) != 0) {
            func_02056778(&self->sub1c);
        }
    } else {
        func_02056778(&self->sub1c);
    }

    if (func_0201a7b4(&other->unk_418) < 2) {
        if (func_0201a7bc(&other->unk_418) != 0) {
            if (func_0201a2e8((void *) self, self->unk_78) == 0) {
                func_0201a19c((UnkStruct_0201a19c *) self, func_0201a7b4(&other->unk_418));
                func_0201a27c((struct UnkStruct_0201a27c *) self);
            } else {
                if (func_0201a234((UnkStruct_0201a234 *) self) != 0) {
                    func_0201a27c((struct UnkStruct_0201a27c *) self);
                }
            }
        } else {
            if (func_0201a2e8((void *) self, self->unk_78) != 0 && func_0201a234((UnkStruct_0201a234 *) self) != 0) {
                func_0201a174((void *) self);
            }
        }
    } else {
        if (func_0201a2e8((void *) self, self->unk_78) != 0) {
            func_0201a174((void *) self);
        }
    }

    self = (UnkStruct_02019f1c *) ((char *) self + 0x48);
    func_02056778(self);
}
