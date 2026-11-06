/* held_item: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0205ea60 @ 0x0205ea60, 0x64 bytes, Thumb
 * func_0205e954 @ 0x0205e954, 0x10c bytes, Thumb
 * func_0205e8f8 @ 0x0205e8f8, 0x5c bytes, Thumb
 * func_0205e8e4 @ 0x0205e8e4, 0x14 bytes, Thumb
 * func_0205e8d8 @ 0x0205e8d8, 0xc bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned char unk_00;
    unsigned char pad_01[7];
    unsigned char buf[8];
    unsigned int unk_10;
    unsigned char pad_14[12];
    unsigned int *unk_20;
    unsigned char pad_24[4];
} UnkStruct_0205ea60;

typedef struct {
    unsigned int pad_00;
} GType;

typedef struct VecFx32 {
    fx32 x;
    fx32 y;
    fx32 z;
} VecFx32;

typedef struct UnkStruct_0205e954 {
    int a[9];
    VecFx32 v;
} UnkStruct_0205e954;

typedef struct UnkStruct_0205e954_2 {
    u8 pad0[0x64];
    UnkStruct_0205e954 s;
} UnkStruct_0205e954_2;

typedef struct UnkStruct_0205e954_3 {
    u8 id;
    u8 pad0[3];
    int unk_04;
    u8 pad_08[0x28 - 8];
    int unk_28;
    int unk_2C;
} UnkStruct_0205e954_3;

typedef struct {
    u32 data[12];
} Buf;

extern unsigned short *func_0205f100(GType *g, int byte);
extern int func_0205f024(GType *g, int byte);
extern int func_0205f64c(unsigned short *);
extern int func_0205f130(GType *g, int byte);
extern void func_02054cdc(void *);
extern void func_02056ffc(void *ptr);
extern void func_02060214(UnkStruct_0205ea60 *p);
extern int data_021ca16c[];
extern void func_0205510c(UnkStruct_0205e954_2 *t, VecFx32 *v);
extern void func_02060134(int *sub, UnkStruct_0205e954 *s, VecFx32 *v);
extern int func_0203f7d0(VecFx32 *out, VecFx32 *in);
extern void func_02060438(int *sub, VecFx32 *in);
extern int func_02055d0c(void *src, void *dst, u32 n);
extern int func_020604e8(int arg);

void func_0205e8f8(Buf *out, const u8 *key, u32 arg2);

void func_0205ea60(UnkStruct_0205ea60 *p)
{
    unsigned char byte;
    int r6;

    byte = p->unk_00;
    if (*func_0205f100(((GType *) data_021ca16c), byte) == 0xfff1) {
        goto common;
    }
    func_0205f024(((GType *) data_021ca16c), byte);
    r6 = func_0205f64c((unsigned short *) func_0205f100(((GType *) data_021ca16c), byte));
    if (r6 == 0x2b) {
        goto common;
    }
    func_02054cdc((void *) func_0205f130(((GType *) data_021ca16c), byte));
    if (r6 != 0x27) {
        goto common;
    }
    func_02056ffc((unsigned char *) p + 8);
    *p->unk_20 = p->unk_10;
common:
    p = (UnkStruct_0205ea60 *) ((unsigned char *) p + 0x28);
    func_02060214(p);
}

static __inline int inr(u16 *q, u16 lo, u16 hi)
{
    int r;
    r = 0;
    if (*q >= lo && *q <= hi) {
        r = 1;
    }
    return r;
}

void func_0205e954(UnkStruct_0205e954_3 *p, UnkStruct_0205e954 *src)
{
    VecFx32 v;
    UnkStruct_0205e954 s;
    VecFx32 out;
    UnkStruct_0205e954 t1;
    UnkStruct_0205e954 t2;
    VecFx32 tmp1;
    VecFx32 tmp2;
    UnkStruct_0205e954_2 *t;
    int id;
    fx32 k;

    id = p->id;
    if (*(u16 *) func_0205f100((GType *) data_021ca16c, id) != 0xfff1) {
        t = (UnkStruct_0205e954_2 *) func_0205f130((GType *) data_021ca16c, id);
        t->s = *src;
        k = p->unk_04;
        v.x = k;
        v.y = k;
        v.z = k;
        func_0205510c(t, &v);
        if (inr((u16 *) func_0205f100((GType *) data_021ca16c, id), 0x1374, 0x1374) ||
            inr((u16 *) func_0205f100((GType *) data_021ca16c, id), 0x1375, 0x1375)) {
            func_0205e8f8((Buf *) (&t1), (const u8 *) p, 2);
            s = t1;
        } else {
            func_0205e8f8((Buf *) (&t2), (const u8 *) p, 0);
            s = t2;
        }
        func_02060134(&p->unk_28, &s, &v);
        tmp1.x = s.v.x;
        tmp1.y = s.v.y;
        tmp1.z = s.v.z;
        func_0203f7d0(&out, &tmp1);
        switch (p->unk_2C) {
            case 7:
            case 8:
                tmp2.x = out.x;
                tmp2.y = out.y;
                tmp2.z = out.z;
                func_02060438(&p->unk_28, &tmp2);
                break;
        }
    }
}

void func_0205e8f8(Buf *out, const u8 *key, u32 arg2)
{
    Buf buf;
    u8 k;
    int i;
    k = *key;
    if (*(u16 *) (u16 *) func_0205f100((GType *) (((u32 *) data_021ca16c)), (u8) k) != 0xfff1) {
        func_02055d0c((void *) func_0205f130((GType *) (((u32 *) data_021ca16c)), (u8) k), &buf, arg2);
    } else {
        for (i = 0; i < 12; i++) {
            buf.data[i] = 0;
        }
    }
    *out = buf;
}

int func_0205e8e4(const unsigned char *arg)
{
    return func_0205f130((GType *) (((int *) data_021ca16c)), (unsigned char) (*arg));
}

int func_0205e8d8(int arg)
{
    return func_020604e8(arg + 0x28);
}
