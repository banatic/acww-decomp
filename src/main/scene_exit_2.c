/* scene_exit_2: 11 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020b64a0 @ 0x020b64a0, 0x20 bytes, Thumb
 * func_020b649c @ 0x020b649c, 0x2 bytes, Thumb
 * func_020b6468 @ 0x020b6468, 0x34 bytes, Thumb
 * func_020b6454 @ 0x020b6454, 0x14 bytes, Thumb
 * func_020b6434 @ 0x020b6434, 0x1e bytes, Thumb
 * func_020b63f4 @ 0x020b63f4, 0x40 bytes, Thumb
 * func_020b6214 @ 0x020b6214, 0x1e0 bytes, Thumb
 * func_020b6140 @ 0x020b6140, 0xd4 bytes, Thumb
 * func_020b6098 @ 0x020b6098, 0xa8 bytes, Thumb
 * func_020b6044 @ 0x020b6044, 0x54 bytes, Thumb
 * func_020b5fc8 @ 0x020b5fc8, 0x7c bytes, Thumb
 */

#include "types.h"

typedef struct {
    char a;     // 0x00
    char b;     // 0x01
    short c;    // 0x02
    int d;      // 0x04
    int e;      // 0x08
    int unk_0C; // 0x0c
    int g;      // 0x10
    char h;     // 0x14
    char i;     // 0x15
    short j;    // 0x16
    char k;     // 0x18
} Struct020b64a0;

struct UnkStruct_020b6468 {
    unsigned char b;
    char pad_01;
    short s1;
    int i1;
    int i2;
    int i3;
    int v;
    unsigned char c1;
    unsigned char c2;
    short s2;
    unsigned char c3;
};

typedef struct {
    unsigned int unk_00;
    unsigned int unk_04;
    unsigned int unk_08;
} Src;

typedef struct {
    unsigned char tag;
    unsigned char flag;
    short half;
    unsigned int a;
    unsigned int b;
    unsigned int c;
    unsigned int d;
    unsigned char x;
    unsigned char y;
} Dst;

typedef struct UnkStruct_020b6214 {
    u8 kind;
    u8 pad_01[0x13];
    u8 flagA;
    u8 flagB;
    u8 pad_16[0x6];
} UnkStruct_020b6214;

typedef struct Desc {
    UnkStruct_020b6214 *data;
    u8 count;
    u8 pad_05[3];
} Desc;

typedef struct GObj {
    u8 pad_00[0xc];
    Desc *desc;
} GObj;

typedef struct UnkStruct_020b6214_2 {
    u32 pad_00;
} UnkStruct_020b6214_2;

typedef struct {
    unsigned char k;
    unsigned char pad_01;
    short unk_02;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    unsigned char unk_14;
    unsigned char unk_15;
    unsigned char pad_16[6];
} UnkStruct_020b6140_4;

typedef struct {
    UnkStruct_020b6140_4 *unk_00;
    unsigned char unk_04;
} UnkStruct_020b6140;

typedef struct {
    unsigned char pad_00[0xc];
    UnkStruct_020b6140 *unk_0C;
} UnkStruct_020b6140_2;

typedef struct {
    unsigned char pad_00[0x64];
    int unk_64;
} UnkStruct_020b6140_3;

typedef struct {
    unsigned char unk_00;
    unsigned char unk_01;
    unsigned char unk_02;
    short unk_04;
    unsigned int unk_08;
    unsigned int unk_0C;
    unsigned int unk_10;
    unsigned char rest[12];
} UnkStruct_020b6098;

typedef struct Rec {
    char pad_00[0x16];
    short unk_16;
    unsigned char unk_18;
    char pad_19[3];
} Rec;

typedef struct Tbl {
    Rec *recs;
    unsigned char count;
} Tbl;

typedef struct Root {
    char pad_00[0xc];
    Tbl *t;
} Root;

extern GObj *data_021f6948;
extern int func_0204e414(void);
extern int func_0204e108(int ret, u32 *v, u32 *w1, u32 *w2);
extern int func_0204e08c(int ret, u32 *v, u32 *w1, u32 *w2);
extern u8 func_020b64dc(UnkStruct_020b6214_2 *obj);
extern u32 *func_020b64ec(UnkStruct_020b6214_2 *obj);
extern u32 func_020b64e8(UnkStruct_020b6214_2 *obj);
extern u16 func_020b64e0(UnkStruct_020b6214_2 *obj);
extern u32 func_020b64d4(UnkStruct_020b6214_2 *obj);
extern u32 func_020b64cc(UnkStruct_020b6214_2 *obj);
extern UnkStruct_020b6140_3 *data_020ccf94;
extern int func_02073dd4(UnkStruct_020b6140_3 *g, int v);
extern void func_020b64f0(void *table, unsigned char b0, void *rest, unsigned int w8, int s4, unsigned int w12,
                          unsigned int w16);
extern unsigned char data_021f69a0[];
extern unsigned char data_021f69b8[];
extern void func_0204f7e0(int *dst, int *src);

void func_020b64a0(Struct020b64a0 *p)
{
    p->a = 0x3f;
    p->d = 0;
    p->e = 0;
    p->unk_0C = 0;
    p->g = 0;
    p->c = 0;
    p->b = 1;
    p->h = 2;
    p->i = 2;
    p->j = 0;
    p->k = 0;
}

void func_020b649c(void *object) {}

void func_020b6468(struct UnkStruct_020b6468 *out, unsigned char b, int *data, int v, short s1, unsigned char c1,
                   unsigned char c2, short s2, unsigned char c3)
{
    out->b = b;
    out->i1 = data[0];
    out->i2 = data[1];
    out->i3 = data[2];
    out->v = v;
    out->s1 = s1;
    out->c1 = c1;
    out->c2 = c2;
    out->s2 = s2;
    out->c3 = c3;
}

unsigned char func_020b6454(unsigned char *r0, unsigned char r1)
{
    if (r0[0] == 0x3f) {
        r0[0] = r1;
        r0[1] = 1;
        return 1;
    }
    return 0;
}

int func_020b6434(unsigned char *p, unsigned char a, unsigned char b, unsigned char c)
{
    if (p[0] == 0x3f) {
        p[0] = a;
        p[0x14] = b;
        p[0x15] = c;
        p[1] = 1;
        return 1;
    }
    return 0;
}

int func_020b63f4(Dst *dst, unsigned char val, const Src *src, unsigned int extra, short p1, unsigned char p2,
                  unsigned char p3)
{
    if (dst->tag == 0x3f) {
        dst->tag = val;
        dst->a = src->unk_00;
        dst->b = src->unk_04;
        dst->c = src->unk_08;
        dst->d = extra;
        dst->half = p1;
        dst->flag = 0;
        dst->x = p2;
        dst->y = p3;
        return 1;
    } else {
        return 0;
    }
}

inline u32 inline_fn(u32 *arg0)
{
    return arg0[1];
}

int func_020b6214(int unused, int idx, u8 *status, u32 *outVec, u32 *outWord, u16 *outShort, u32 *outWord2, u32 *outWord3,
                  u8 *outByte1, u8 *outByte2)
{
    UnkStruct_020b6214 *base;
    Desc *desc;
    UnkStruct_020b6214 *el;
    u32 w1;
    u32 w2;
    u32 v[3];
    int ret;
    int kind;
    int count;
    if (idx == (-1)) {
        goto fail;
    }
    if (data_021f6948 == 0) {
        goto fail;
    }
    desc = data_021f6948->desc;
    if (desc == 0) {
        goto fail;
    }
    base = desc->data;
    if (base == 0) {
        goto fail;
    }
    count = desc->count;
    if ((idx < 0) || (idx >= count)) {
        goto fail;
    }
    el = &base[idx];
    ret = func_0204e414();
    kind = el->kind - 0x3c;
    switch (kind) {
        case 2:
            if (func_0204e108(ret, v, &w1, &w2)) {
                v[2] += 0x1000;
                *status = 0;
                outVec[0] = v[0];
                outVec[1] = inline_fn(v);
                outVec[2] = v[2];
                *outWord = 0x0f000000;
                *outShort = 0;
                *outWord2 = w1;
                *outWord3 = w2;
                *outByte1 = el->flagA;
                *outByte2 = el->flagB;
            }
            return 3;

        case 1:
            if (func_0204e08c(ret, v, &w1, &w2)) {
                v[2] += 0x1000;
                *status = 0;
                outVec[0] = v[0];
                outVec[1] = inline_fn(v);
                outVec[2] = v[2];
                *outWord = 0x0f000000;
                *outShort = 0;
                *outWord2 = w1;
                *outWord3 = w2;
                *outByte1 = el->flagA;
                *outByte2 = el->flagB;
            }
            return 3;

        case 3:
            *status = func_020b64dc(((UnkStruct_020b6214_2 *) data_021f69a0));
            {
                u32 *p = func_020b64ec(((UnkStruct_020b6214_2 *) data_021f69a0));
                outVec[0] = p[0];
                outVec[1] = inline_fn(p);
                outVec[2] = p[2];
            }
            *outWord = func_020b64e8(((UnkStruct_020b6214_2 *) data_021f69a0));
            *outShort = func_020b64e0(((UnkStruct_020b6214_2 *) data_021f69a0));
            *outWord2 = func_020b64d4(((UnkStruct_020b6214_2 *) data_021f69a0));
            *outWord3 = func_020b64cc(((UnkStruct_020b6214_2 *) data_021f69a0));
            *outByte1 = el->flagA;
            *outByte2 = el->flagB;
            return 2;

        case 0:
            *status = func_020b64dc(((UnkStruct_020b6214_2 *) data_021f69b8));
            {
                u32 *p = func_020b64ec(((UnkStruct_020b6214_2 *) data_021f69b8));
                outVec[0] = p[0];
                outVec[1] = inline_fn(p);
                outVec[2] = p[2];
            }
            *outWord = func_020b64e8(((UnkStruct_020b6214_2 *) data_021f69b8));
            *outShort = func_020b64e0(((UnkStruct_020b6214_2 *) data_021f69b8));
            *outWord2 = func_020b64d4(((UnkStruct_020b6214_2 *) data_021f69b8));
            *outWord3 = func_020b64cc(((UnkStruct_020b6214_2 *) data_021f69b8));
            *outByte1 = (*el).flagA;
            *outByte2 = el->flagB;
            return 3;

        default:
            goto fail_default;
    }

fail_default:
    return 1;

fail:
    return 1;
}

int func_020b6140(void *p0, int idx, unsigned char *p2, int *p3, int *p4, short *p5, unsigned char *p6, unsigned char *p7,
                  int *p8, int *p9)
{
    int a, b;
    int r;

    r = func_020b6214((int) p0, idx, (u8 *) p2, (u32 *) p3, (u32 *) p4, (u16 *) p5, (u32 *) (&a), (u32 *) (&b), (u8 *) p6,
                      (u8 *) p7);
    if (p8 != 0) {
        *p8 = a;
    }
    if (p9 != 0) {
        *p9 = b;
    }
    if (r == 1) {
        if (idx != -1 && (*(UnkStruct_020b6140_2 **) &data_021f6948) != 0 &&
            (*(UnkStruct_020b6140_2 **) &data_021f6948)->unk_0C != 0 &&
            (*(UnkStruct_020b6140_2 **) &data_021f6948)->unk_0C->unk_00 != 0) {
            UnkStruct_020b6140_4 *arr = (*(UnkStruct_020b6140_2 **) &data_021f6948)->unk_0C->unk_00;
            int n = (*(UnkStruct_020b6140_2 **) &data_021f6948)->unk_0C->unk_04;
            if (idx >= 0 && idx < n) {
                UnkStruct_020b6140_4 *e = &arr[idx];
                unsigned char kind = e->k;
                if (e->unk_08 == 0) {
                    e->unk_08 = 0x200;
                }
                if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64) != 0 && kind == 7) {
                    kind = 8;
                }
                *p2 = kind;
                p3[0] = e->unk_04;
                p3[1] = e->unk_08;
                p3[2] = e->unk_0C;
                *p4 = e->unk_10;
                *p5 = e->unk_02;
                *p6 = e->unk_14;
                *p7 = e->unk_15;
                return r;
            }
        }
        return 0;
    }
    return r;
}

int func_020b6098(void *self, int arg1)
{
    UnkStruct_020b6098 data;
    int r;

    r = func_020b6140(self, arg1, (unsigned char *) (&data.unk_00), (int *) (&data.rest), (int *) (&data.unk_08),
                      (short *) (&data.unk_04), (unsigned char *) (&data.unk_01), (unsigned char *) (&data.unk_02),
                      (int *) (&data.unk_0C), (int *) (&data.unk_10));
    if (r == 0) {
        goto fail;
    }
    switch (r) {
        case 2:
            func_020b64f0(data_021f69a0, data.unk_00, &data.rest, data.unk_08, (int) data.unk_04, data.unk_0C, data.unk_10);
            break;
        case 3:
            func_020b64f0(data_021f69b8, data.unk_00, &data.rest, data.unk_08, (int) data.unk_04, data.unk_0C, data.unk_10);
            break;
    }
    r = func_020b63f4((Dst *) self, data.unk_00, (const Src *) (&data.rest), data.unk_08, (int) data.unk_04, data.unk_01,
                      data.unk_02);
    if (r == 0) {
        goto fail;
    }
    return 1;
fail:
    return 0;
}

int func_020b6044(void *unused, int idx, int *outA, short *outB)
{
    Tbl *t;
    Rec *r;
    int n;

    *outA = 0;
    *outB = 0;
    if (idx == -1) {
        goto ret0;
    }
    if ((*(Root **) &data_021f6948) == 0) {
        goto ret0;
    }
    t = (*(Root **) &data_021f6948)->t;
    if (t == 0) {
        goto ret0;
    }
    r = t->recs;
    if (r == 0) {
        goto ret0;
    }
    n = t->count;
    if (idx < 0) {
        goto ret0;
    }
    if (idx >= n) {
        goto ret0;
    }
    r = (Rec *) ((char *) r + idx * 0x1c);
    if (outA != 0) {
        *outA = r->unk_18;
    }
    if (outB != 0) {
        *outB = r->unk_16;
    }
    return 1;
ret0:
    return 0;
}

int func_020b5fc8(int a, int b, int *dest, int *src)
{
    short s0;
    int w4;
    int tmp[3];
    if (func_020b6044((void *) a, b, &w4, &s0) != 0) {
        func_0204f7e0(tmp, src);
        {
            int t2 = tmp[2];
            int t1 = src[1];
            int t0 = tmp[0];
            dest[0] = t0;
            dest[1] = t1;
            dest[2] = t2;
        }
        if (s0 == 0 || s0 == 0xffff8000) {
            dest[0] = src[0];
            return 1;
        }
        if (s0 == 0x4000 || s0 == 0xffffc000) {
            dest[2] = src[2];
            return 1;
        }
        return 1;
    }
    dest[0] = src[0];
    dest[1] = src[1];
    dest[2] = src[2];
    return 0;
}
