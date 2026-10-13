/* func_0205e954 @ 0x0205e954, 0x10c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

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

extern int data_021ca16c[];

extern u16 *func_0205f100(int *g, int id);
extern UnkStruct_0205e954_2 *func_0205f130(int *g, int id);
extern void func_0205510c(UnkStruct_0205e954_2 *t, VecFx32 *v);
extern UnkStruct_0205e954 func_0205e8f8(UnkStruct_0205e954_3 *p, int n);
extern void func_02060134(int *sub, UnkStruct_0205e954 *s, VecFx32 *v);
extern void func_0203f7d0(VecFx32 *out, VecFx32 *in);
extern void func_02060438(int *sub, VecFx32 *in);

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
    if (*func_0205f100(data_021ca16c, id) != 0xfff1) {
        t = func_0205f130(data_021ca16c, id);
        t->s = *src;
        k = p->unk_04;
        v.x = k;
        v.y = k;
        v.z = k;
        func_0205510c(t, &v);
        if (inr(func_0205f100(data_021ca16c, id), 0x1374, 0x1374) || inr(func_0205f100(data_021ca16c, id), 0x1375, 0x1375)) {
            t1 = func_0205e8f8(p, 2);
            s = t1;
        } else {
            t2 = func_0205e8f8(p, 0);
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
