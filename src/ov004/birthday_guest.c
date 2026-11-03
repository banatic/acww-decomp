/* birthday_guest: 18 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0221d868 @ 0x0221d868, 0xc4 bytes, Thumb
 * func_ov004_0221d7e0 @ 0x0221d7e0, 0x88 bytes, Thumb
 * func_ov004_0221d784 @ 0x0221d784, 0x5c bytes, Thumb
 * func_ov004_0221d73c @ 0x0221d73c, 0x48 bytes, Thumb
 * func_ov004_0221d6e0 @ 0x0221d6e0, 0x5c bytes, Thumb
 * func_ov004_0221d698 @ 0x0221d698, 0x48 bytes, Thumb
 * func_ov004_0221d664 @ 0x0221d664, 0x34 bytes, Thumb
 * func_ov004_0221d660 @ 0x0221d660, 0x2 bytes, Thumb
 * func_ov004_0221d62c @ 0x0221d62c, 0x34 bytes, Thumb
 * func_ov004_0221d620 @ 0x0221d620, 0xc bytes, Thumb
 * func_ov004_0221d61c @ 0x0221d61c, 0x4 bytes, Thumb
 * func_ov004_0221d5fc @ 0x0221d5fc, 0x20 bytes, Thumb
 * func_ov004_0221d5f0 @ 0x0221d5f0, 0xc bytes, Thumb
 * func_ov004_0221d5dc @ 0x0221d5dc, 0x14 bytes, Thumb
 * func_ov004_0221d5c4 @ 0x0221d5c4, 0x18 bytes, Thumb
 * func_ov004_0221d590 @ 0x0221d590, 0x34 bytes, Thumb
 * func_ov004_0221d560 @ 0x0221d560, 0x30 bytes, Thumb
 * func_ov004_0221d540 @ 0x0221d540, 0x20 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_0221d73c {
    u8 pad_00[0x564];
    u8 sub[0xa4c - 0x564];
    u8 cnt;
};

struct UnkStruct_0221d698 {
    u8 pad_00[0x564];
    u8 sub[0xa4c - 0x564];
    u8 cnt;
};

struct UnkStruct_0221d664 {
    u8 pad_00[0x564];
    u8 sub[0x898 - 0x564];
    int phase;
};

struct InnerOverlay {
    int unk_00;
    int unk_04;
};

struct OuterOverlay {
    char pad_00[0x8DC];
    struct InnerOverlay *ptr;
};

typedef struct {
    void *unk_00;
    char pad_04[0x89c - 4];
    void *unk_89C;
} UnkStruct_0221d560;

struct _Obj {
    void *vtbl;
};

extern u16 func_020e8ed8(int dx, int dy);
extern char *func_ov004_0221d4e8(void);
extern int func_02019d0c(char *p, int a, int b, int c, int d, int e, int f, int g, int h, int i, int j);
extern void func_0201ad18(char *p, int a, int b, char *c, int d, int e, int f, int g);
extern char *data_ov004_02257a18;
extern u16 data_020c80f8;
extern int data_020c814c;
extern unsigned char data_021fbee8[];
extern int func_020e8b4c(int a, int b);
extern int func_020644cc(int);
extern int func_ov004_0221dd24(void *self, int a);
extern int func_ov004_0221c844(void *p, int a);
extern int func_02019c90(void *p, int a, int b, u16 c);
extern void *func_020961a8(int k);
extern int func_0201c314(void *self, void *p);
extern int func_020147fc(void *p, int x, int y, int z);
int func_0203e020(struct OuterOverlay *self);
extern void *func_0202de4c(void *);
extern void *func_0202e5e0(void *argument0);
extern void func_020edf54(unsigned int argument0);
extern void *data_ov004_02253868;
extern char data_ov004_022537d8;
extern void func_020edb3c(void *);

int func_ov004_0221d868(char *self)
{
    // DECLS
    char *o;
    char *m;
    char *g;
    int r;
    // ENDDECLS

    if (*(u16 *) (self + 0xa4e) == 0) {
        m = self + 0x564;
        o = func_ov004_0221d4e8();
        if (o != 0) {
            *(short *) (self + 0xa50) =
                func_020e8ed8(*(int *) (o + 0x5c) - *(int *) (self + 0x5c), *(int *) (o + 0x64) - *(int *) (self + 0x64));
            g = data_ov004_02257a18;
            if (g != 0 && *(unsigned int *) (g + 0x898) <= 1) {
                r = func_ov004_0221c844((void *) g, 1);
            } else {
                r = 0;
            }
            if (r != 0) {
                func_02019d0c(m, 3, 1, 0, 0, 0, *(short *) (self + 0xa50), 0, 0, data_020c80f8, 0);
                func_0201ad18(self + 0x3b0, 2, 0, o, (unsigned int) data_021fbee8, 4, data_020c814c, 1);
                return 1;
            }
        }
    }
    return 0;
}

void func_ov004_0221d7e0(char *self)
{
    short a;
    short b;
    char *o;
    int d1;
    int d2;
    a = *(short *) (self + 0xa50);
    b = (short) (a + 0x8000);
    o = func_ov004_0221d4e8();
    if (o == 0) {
        return;
    }
    d1 = func_020e8b4c(a, *(short *) (self + 0x8e));
    d2 = func_020e8b4c(b, *(short *) (o + 0x8e));
    if (d1 > 0x500) {
        return;
    }
    if (d2 > 0x500) {
        return;
    }
    if (func_020644cc(2) != 0) {
        if (func_ov004_0221dd24(self, 3) != 0) {
            *(u16 *) (self + 0xa4e) = 0x12c;
        }
    } else {
        if (func_ov004_0221dd24(self, 2) != 0) {
            *(u16 *) (self + 0xa4e) = 0x12c;
        }
    }
}

int func_ov004_0221d784(char *self)
{
    char *g = data_ov004_02257a18;
    int r;
    if (g != 0 && *(unsigned int *) (g + 0x898) <= 1) {
        r = func_ov004_0221c844(g, 2);
    } else {
        r = 0;
    }
    if (r != 0) {
        if (func_02019c90(self + 0x564, 1, 3, data_020c80f8) != 0) {
            *(u8 *) (self + 0xa4c) = 0x1e;
            return 1;
        }
    }
    return 0;
}

void func_ov004_0221d73c(struct UnkStruct_0221d73c *self)
{
    if (self->cnt != 0) {
        self->cnt--;
    }
    if (self->cnt != 0) {
        if (self->cnt == 1) {
            func_02019c90(&self->sub, 1, 0, data_020c80f8);
        }
    } else {
        func_ov004_0221dd24((void *) self, 0);
    }
}

int func_ov004_0221d6e0(char *self)
{
    char *g = data_ov004_02257a18;
    int r;
    if (g != 0 && *(unsigned int *) (g + 0x898) <= 1) {
        r = func_ov004_0221c844(g, 3);
    } else {
        r = 0;
    }
    if (r != 0) {
        if (func_02019c90(self + 0x564, 1, 0x1a, data_020c80f8) != 0) {
            *(u8 *) (self + 0xa4c) = 0x32;
            return 1;
        }
    }
    return 0;
}

void func_ov004_0221d698(struct UnkStruct_0221d698 *self)
{
    if (self->cnt != 0) {
        self->cnt--;
    }
    if (self->cnt != 0) {
        if (self->cnt == 1) {
            func_02019c90(&self->sub, 1, 0, data_020c80f8);
        }
    } else {
        func_ov004_0221dd24((void *) self, 0);
    }
}

int func_ov004_0221d664(struct UnkStruct_0221d664 *self)
{
    if (self->phase == 1 || self->phase == 2 || self->phase == 3) {
        func_02019c90(&self->sub, 2, 0, data_020c80f8);
    }
    return 1;
}

void func_ov004_0221d660(void *callbackObject) {}

int func_ov004_0221d62c(void *self)
{
    void *p = func_020961a8(4);
    if (p != 0) {
        func_020147fc((char *) self + 0x618, 0, func_0201c314(self, p), 0);
        return 1;
    }
    return 0;
}

void func_ov004_0221d620(int a)
{
    func_ov004_0221dd24((void *) a, 6);
}

int func_ov004_0221d61c(void *callbackObject)
{
    return 1;
}

void func_ov004_0221d5fc(struct OuterOverlay *self)
{
    if (self->ptr != 0 && self->ptr->unk_04 == 0) {
        func_0203e020(self);
    }
}

void *func_ov004_0221d5f0(char *self)
{
    // DECLS
    // ENDDECLS
    *(u8 *) (self + 0x897) = 0x1;
    return self;
}

int func_ov004_0221d5dc(unsigned char *p)
{
    if (p[0x897] != 0) {
        return 0;
    }
    return 1;
}

void *func_ov004_0221d5c4(void *arg)
{
    *((void **) arg) = ((int *) &data_ov004_022537d8);
    func_0202de4c(arg);
    return arg;
}

void *func_ov004_0221d590(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self) = &data_ov004_02253868;
    *(void **) (self + 0x89c) = ((void * *) &data_ov004_022537d8);
    func_0202de4c(self + 0x89c);
    func_0202e5e0(self);
    func_020edf54((unsigned int) (self));
    return self;
}

void *func_ov004_0221d560(UnkStruct_0221d560 *obj)
{
    obj->unk_00 = ((char *) &data_ov004_02253868);
    obj->unk_89C = &data_ov004_022537d8;
    func_0202de4c((void *) &obj->unk_89C);
    func_0202e5e0(obj);
    return obj;
}

void *func_ov004_0221d540(struct _Obj *obj)
{
    obj->vtbl = &data_ov004_022537d8;
    func_0202de4c(obj);
    func_020edb3c(obj);
    return obj;
}
