/* effect_models_2: 18 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02090858 @ 0x02090858, 0x48 bytes, Thumb
 * func_02090834 @ 0x02090834, 0x24 bytes, Thumb
 * func_02090810 @ 0x02090810, 0x24 bytes, Thumb
 * func_020907d8 @ 0x020907d8, 0x38 bytes, Thumb
 * func_020907c4 @ 0x020907c4, 0x14 bytes, Thumb
 * func_02090788 @ 0x02090788, 0x3c bytes, Thumb
 * func_02090764 @ 0x02090764, 0x24 bytes, Thumb
 * func_02090740 @ 0x02090740, 0x24 bytes, Thumb
 * func_02090710 @ 0x02090710, 0x30 bytes, Thumb
 * func_020906dc @ 0x020906dc, 0x34 bytes, Thumb
 * func_02090694 @ 0x02090694, 0x48 bytes, Thumb
 * func_02090664 @ 0x02090664, 0x30 bytes, Thumb
 * func_02090638 @ 0x02090638, 0x2c bytes, Thumb
 * func_0209050c @ 0x0209050c, 0x12c bytes, Thumb
 * func_020904ac @ 0x020904ac, 0x60 bytes, Thumb
 * func_02090424 @ 0x02090424, 0x88 bytes, Thumb
 * func_02090418 @ 0x02090418, 0xc bytes, Thumb
 * func_0209036c @ 0x0209036c, 0xac bytes, Thumb
 */

#include "types.h"

struct UnkStruct_02090858 {
    char data[0x530];
};

typedef struct {
    char data[0x148];
} UnkStruct_02090788_2;

typedef struct UnkStruct_02090788 {
    int unk_00;
    UnkStruct_02090788_2 array[4];
    char sub[1];
} UnkStruct_02090788;

struct Entry {
    int unk_00[3];
};

struct UnkStruct_02090638 {
    char pad_00[0x24];
    int unk_24;
};

typedef struct {
    char pad_00[8];
    unsigned int unk_08;
    char pad_0C[0xc];
    unsigned int *unk_18;
    char pad_1C[4];
} Slot;

typedef struct {
    unsigned int active;
    char pad_04[0x20];
    char sub_24[0x9c];
    char sub_C0[0x1c];
    unsigned int flags[3];
    Slot slots[3];
} UnkStruct_020904ac;

typedef struct {
    int m[12];
} M43;

typedef struct {
    int x, y, z, w;
} Vec4;

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    int unk_14;
    int unk_18;
    short unk_1C;
    short unk_1E;
    short unk_20;
    short unk_22;
    char unk_24[0x80 - 0x24];
    int unk_80;
    int unk_84;
    M43 unk_88;
} UnkStruct_02090424;

struct UnkStruct_0209036c {
    u32 unk_00;
    u8 pad_04[0xc];
    u32 unk_10;
    u32 unk_14;
    u32 unk_18;
    u16 unk_1C;
    u16 unk_1E;
    u16 unk_20;
    u8 pad_22[0x24 - 0x22];
    u8 unk_24[0xe0 - 0x24];
    u32 unk_E0;
    u32 unk_E4;
    u8 pad_E8[0x108 - 0xe8];
    u8 unk_108[0x128 - 0x108];
    u8 unk_128[1];
};

extern int func_020ea1bc(int, int);
extern int data_021d52c8;
extern int data_021fbe94;
extern void func_020e9fd4(void *);
extern int func_02064b2c(int, void *, int, int);
extern struct Entry data_020e26ec[];
extern void func_020e993c(int x, int y);
extern int func_0205556c(int *a, int b, int c);
extern int data_020e2498[];
extern int func_02055478(void *, int);
extern int func_02055140(void *, int);
extern void func_02055060(void *, int, int, int, int, int);
extern void func_02055050(void *);
extern int func_0205650c(void *, int, int);
extern void func_02056478(void *, int, int, int, int);
extern int func_02055e00(void *);
extern void func_020563dc(void *, int);
extern int func_020564d0(void *, int, int);
extern int NNS_G3dGetJntAnmSet(int);
extern int func_02107b44(int, int);
extern int NNS_G3dGetMatCAnmSet(int);
extern int func_02107b80(int, int);
extern int NNS_G3dGetVisAnmSet(int);
extern int func_02107cf0(int, int);
extern void func_02055124(void *);
extern void func_02056ffc(void *);
extern int func_02056f94(void *);
extern M43 data_021fbe48;
extern int func_0203f8d0(Vec4 *out, int *src);
extern void func_020e96c8(M43 *m, int a, int b, int c);
extern void func_020e9774(M43 *m, int a);
extern void func_020e97a4(M43 *m, short a, short b, short c);
extern void func_020e9838(M43 *m, int a, int b, int c);
extern void func_0205510c(void *p, int a);
extern unsigned short func_02065604(void);
extern void NNS_G3dMdlSetMdlEmi(int a, int b, unsigned short c);
extern int func_02055454(char *ptr);

void func_02090788(UnkStruct_02090788 *self, int value);
void func_02090764(char *param);
void func_02090740(char *param);
void func_02090710(void *arg);
void func_020906dc(void *p0, void (*callback)(void *));
void func_02090694(int *out, int *src);
void func_02090664(int *arr);
void func_0209050c(unsigned int *param0, unsigned int *param1);
void func_020904ac(UnkStruct_020904ac *obj);
void func_02090424(UnkStruct_02090424 *o);
void func_02090418(char *ptr);
void func_0209036c(struct UnkStruct_0209036c *self, char *base, void (*callback)(void *));

void func_02090858(struct UnkStruct_02090858 *arr)
{
    int i;
    if (data_021d52c8 == 0) {
        data_021d52c8 = func_020ea1bc(0x2800, data_021fbe94);
    }
    for (i = 0; i < 4; i++) {
        func_02090788((UnkStruct_02090788 *) (arr + i), i);
    }
}

void func_02090834(void *param)
{
    int i;
    for (i = 0; i < 4; i++) {
        func_02090764((char *) ((char *) param + i * 0x530));
    }
}

void func_02090810(void *ptr)
{
    int i;
    void *base;

    base = ptr;
    for (i = 0; i < 4; i++) {
        func_02090740((char *) ((char *) base + i * 0x530));
    }
}

void func_020907d8(void *base)
{
    int i;
    void *p;
    void *q;

    for (i = 0; i < 4; i++) {
        func_02090710((char *) base + i * 0x530);
    }

    p = (*(void **) &data_021d52c8);
    if (p != 0) {
        func_020e9fd4(p);
        (*(void **) &data_021d52c8) = 0;
    }
}

void func_020907c4(void *base, int index, void (*callback)(void *))
{
    func_020906dc((char *) base + index * 0x530, callback);
}

void func_02090788(UnkStruct_02090788 *self, int value)
{
    int i;
    self->unk_00 = value;
    func_02090694((int *) self->sub, (int *) self);
    for (i = 0; i < 4; i++) {
        func_0209050c((unsigned int *) (&self->array[i]), (unsigned int *) self);
    }
}

void func_02090764(char *param)
{
    int i;
    for (i = 0; i < 4; i++) {
        func_020904ac((UnkStruct_020904ac *) (param + 4 + i * 328));
    }
}

void func_02090740(char *param)
{
    int i;
    for (i = 0; i < 4; i++) {
        func_02090424((UnkStruct_02090424 *) (param + 4 + i * 0x148));
    }
}

void func_02090710(void *arg)
{
    void *p;
    int i;
    int j;

    p = (void *) ((char *) arg + 0x524);
    func_02090664((int *) p);

    for (i = 0; i < 4; i++) {
        j = i * 0x148;
        func_02090418((char *) ((void *) ((char *) arg + 4 + j)));
    }
}

void func_020906dc(void *p0, void (*callback)(void *))
{
    char *ptr;
    int i;
    ptr = (char *) p0 + 4;
    i = 0;
    while (i < 4) {
        if (*(void **) ptr == 0) {
            func_0209036c((struct UnkStruct_0209036c *) ptr, (char *) p0, callback);
            return;
        }
        ptr += 0x148;
        i++;
    }
}

void func_02090694(int *out, int *src)
{
    int index = *(volatile int *) src;
    int i = 0;
    int a = 0;
    int b = 0;

    for (; i < 3; i++) {
        struct Entry *e = &data_020e26ec[index];
        if (e->unk_00[i] != 0) {
            out[i] = func_02064b2c(e->unk_00[i], (*(void **) &data_021d52c8), 4, a);
        } else {
            out[i] = b;
        }
    }
}

void func_02090664(int *arr)
{
    int i;
    for (i = 0; i < 3; i++) {
        if (arr[i] != 0) {
            func_020e993c(data_021d52c8, arr[i]);
            arr[i] = 0;
        }
    }
}

int func_02090638(struct UnkStruct_02090638 *obj, int idx)
{
    int flag = 1;
    if (func_0205556c(&obj->unk_24, idx + 0x6d656666, data_020e2498[idx]) == 0) {
        flag = 0;
    }
    return flag;
}

void func_0209050c(unsigned int *param0, unsigned int *param1)
{
    int tmp;
    unsigned int *p;
    unsigned int *r6;
    const unsigned int size = 0x1000;

    tmp = *param1;
    *param0 = 0;
    if (func_02090638((struct UnkStruct_02090638 *) param0, tmp) == 0) {
        return;
    }

    p = (unsigned int *) ((char *) param1 + 0x524);

    if (*p != 0) {
        func_02055478((char *) param0 + 0x24, data_021d52c8);
        func_02055140((char *) param0 + 0x24, data_021d52c8);
        tmp = NNS_G3dGetJntAnmSet(*p);
        tmp = func_02107b44(tmp, 0);
        func_02055060((char *) param0 + 0x24, tmp, 1, size, 0, 0);
        func_02055050((char *) param0 + 0x24);
    }

    if (p[1] != 0) {
        *(unsigned int *) ((char *) param0 + 0xe0) = 1;
        r6 = (unsigned int *) ((char *) param0 + 0x108);
        func_0205650c(r6, *(unsigned int *) ((char *) param0 + 0x80), data_021d52c8);
        tmp = NNS_G3dGetMatCAnmSet(p[1]);
        tmp = func_02107b80(tmp, 0);
        func_02056478(r6, tmp, 1, size, 0);
        func_020563dc(r6, func_02055e00((char *) param0 + 0x24));
    } else {
        *(unsigned int *) ((char *) param0 + 0xe0) = 0;
    }

    if (p[2] != 0) {
        *(unsigned int *) ((char *) param0 + 0xe4) = 1;
        r6 = (unsigned int *) ((char *) param0 + 0x128);
        func_020564d0(r6, *(unsigned int *) ((char *) param0 + 0x80), data_021d52c8);
        tmp = NNS_G3dGetVisAnmSet(p[2]);
        tmp = func_02107cf0(tmp, 0);
        func_02056478(r6, tmp, 1, size, 0);
        func_020563dc(r6, func_02055e00((char *) param0 + 0x24));
    } else {
        *(unsigned int *) ((char *) param0 + 0xe4) = 0;
    }
}

void func_020904ac(UnkStruct_020904ac *obj)
{
    int i;
    if (obj->active != 0) {
        func_02055124(obj->sub_24);
        for (i = 1; i < 3; i++) {
            if (obj->flags[i] != 0) {
                func_02056ffc(&obj->slots[i]);
                *obj->slots[i].unk_18 = obj->slots[i].unk_08;
            }
        }
        if (func_02056f94(obj->sub_C0) != 0) {
            obj->active = 0;
        }
    }
}

void func_02090424(UnkStruct_02090424 *o)
{
    volatile unsigned short a;
    volatile unsigned short b;
    Vec4 v;
    int h;
    if (o->unk_00 != 0) {
        h = func_0203f8d0(&v, &o->unk_04);
        func_020e96c8(&data_021fbe48, v.x, v.y, v.z);
        func_020e9774(&data_021fbe48, h);
        func_020e97a4(&data_021fbe48, o->unk_1C, o->unk_1E, o->unk_20);
        func_020e9838(&data_021fbe48, o->unk_10, o->unk_14, o->unk_18);
        o->unk_88 = data_021fbe48;
        func_0205510c(o->unk_24, 0);
        a = func_02065604();
        b = a;
        NNS_G3dMdlSetMdlEmi(o->unk_80, 0, b);
    }
}

void func_02090418(char *ptr)
{
    func_02055454(ptr + 0x24);
}

void func_0209036c(struct UnkStruct_0209036c *self, char *base, void (*callback)(void *))
{
    char *p;
    int t;

    self->unk_00 = 1;
    self->unk_10 = 0x1000;
    self->unk_14 = 0x1000;
    self->unk_18 = 0x1000;
    self->unk_1C = 0;
    self->unk_1E = 0;
    self->unk_20 = 0;

    p = base + 0x524;
    t = func_02107b44(NNS_G3dGetJntAnmSet(*(u32 *) p), 0);
    func_02055060(self->unk_24, t, 1, 0x1000, 0, 0);

    if (self->unk_E0) {
        t = func_02107b80(NNS_G3dGetMatCAnmSet(*(u32 *) (p + 4)), 0);
        func_02056478(self->unk_108, t, 1, 0x1000, 0);
    }

    if (self->unk_E4) {
        t = func_02107cf0(NNS_G3dGetVisAnmSet(*(u32 *) (p + 8)), 0);
        func_02056478(self->unk_128, t, 1, 0x1000, 0);
    }

    callback(self);
}
