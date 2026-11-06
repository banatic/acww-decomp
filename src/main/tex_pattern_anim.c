/* tex_pattern_anim: 19 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02056a8c @ 0x02056a8c, 0x12 bytes, Thumb
 * func_02056a64 @ 0x02056a64, 0x28 bytes, Thumb
 * func_02056a4c @ 0x02056a4c, 0x16 bytes, Thumb
 * func_02056a38 @ 0x02056a38, 0x14 bytes, Thumb
 * func_020569b0 @ 0x020569b0, 0x86 bytes, Thumb
 * func_02056968 @ 0x02056968, 0x48 bytes, Thumb
 * func_02056958 @ 0x02056958, 0x10 bytes, Thumb
 * func_02056928 @ 0x02056928, 0x30 bytes, Thumb
 * func_02056910 @ 0x02056910, 0x18 bytes, Thumb
 * func_020568f0 @ 0x020568f0, 0x20 bytes, Thumb
 * func_020568dc @ 0x020568dc, 0x12 bytes, Thumb
 * func_0205685c @ 0x0205685c, 0x80 bytes, Thumb
 * func_0205682c @ 0x0205682c, 0x2e bytes, Thumb
 * func_0205678c @ 0x0205678c, 0xa0 bytes, Thumb
 * func_02056778 @ 0x02056778, 0x14 bytes, Thumb
 * func_02056730 @ 0x02056730, 0x48 bytes, Thumb
 * func_020566a0 @ 0x020566a0, 0x90 bytes, Thumb
 * func_02056658 @ 0x02056658, 0x48 bytes, Thumb
 * func_02056610 @ 0x02056610, 0x48 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_020569b0 {
    int unk_00;
    int unk_04;
    u8 pad_08[0x20 - 8];
    u8 unk_20;
    u8 unk_21;
    u8 unk_22;
    u8 pad_23;
    u16 unk_24;
};

struct UnkStruct_02056968 {
    int unk_00;
    int unk_04;
    u8 pad_08[0x20 - 8];
    u8 unk_20;
    u8 unk_21;
    u8 unk_22;
    u8 pad_23;
    u16 unk_24;
};

struct UnkStruct_02056958 {
    unsigned char pad_00[0x23];
    unsigned char flag;
};

struct UnkStruct_02056928 {
    void *unk_00;
    int pad_04;
    int unk_08;
    int unk_0C;
    int unk_10;
};

struct UnkStruct_020568dc {
    u8 pad_00[0x18];
    u32 unk_18;
    u8 pad_1C[0x04];
    u32 unk_20;
    u16 unk_24;
    u8 unk_26;
    u32 unk_28;
};

struct UnkStruct_0205685c {
    char pad_00[0x18];
    int unk_18;
    void *unk_1C;
    char pad_20[0x26 - 0x20];
    unsigned char unk_26;
    char pad_27[0x28 - 0x27];
    void *unk_28;
};

struct elem {
    unsigned char data[0x28];
};

struct unk {
    unsigned char pad_00[0x26];
    unsigned char count;
    unsigned char pad_27;
    struct elem *array;
};

typedef struct UnkStruct_0205678c_2 {
    void *unk_00;
    u8 pad0[0x1c];
    u8 unk_20;
    u8 unk_21;
    u8 unk_22;
    u8 unk_23;
    u16 unk_24;
    u16 unk_26;
} UnkStruct_0205678c_2;

typedef struct UnkStruct_0205678c {
    u8 pad0[0x18];
    u8 *unk_18;
    u8 pad_1C[4];
    u8 *unk_20;
    u16 unk_24;
    u16 unk_26;
    UnkStruct_0205678c_2 *unk_28;
} UnkStruct_0205678c;

typedef struct {
    char data[40];
} UnkStruct_02056730;

typedef struct {
    char pad_00[8];
    unsigned int unk_08;
    char pad_0C[12];
    unsigned int unk_18;
    unsigned int unk_1C;
    unsigned int unk_20;
    char pad_24[2];
    unsigned char unk_26;
    char pad_27;
    UnkStruct_02056730 *unk_28;
} UnkStruct_02056730_2;

struct UnkStruct_020566a0 {
    u8 pad_00[0x20];
    u8 unk_20;
    u8 unk_21;
    u8 unk_22;
    u8 pad_23;
    u16 unk_24;
    u8 pad_26[2];
};

struct MainObj {
    u8 pad_00[0x18];
    unsigned int unk_18;
    unsigned int unk_1C;
    u8 pad_20[6];
    u8 count;
    u8 pad_27;
    struct UnkStruct_020566a0 *arr;
};

typedef struct {
    char pad_00[0x22];
    unsigned char unk_22;
    unsigned char unk_23;
    char pad1[0x28 - 0x24];
} UnkStruct_02056658_2;

typedef struct {
    char pad_00[0x18];
    int unk_18;
    char pad1[0x26 - 0x1C];
    unsigned char count;
    char pad_27[0x28 - 0x27];
    UnkStruct_02056658_2 *arr;
} UnkStruct_02056658;

typedef struct {
    char pad_00[0x22];
    unsigned char unk_22;
    unsigned char unk_23;
    char pad2[0x4];
} UnkStruct_02056610_2;

typedef struct {
    char pad_00[0x18];
    int unk_18;
    char pad_1C[0x0A];
    unsigned char count;
    char pad2[0x01];
    UnkStruct_02056610_2 *array;
} UnkStruct_02056610;

extern void *func_020ba01c(void *p);
extern void func_020ba004(int a);
extern void func_020b9ec4(void *);
extern int NNS_G3dGetResDictIdxByName(void *a, void *b);
extern int func_020579f0(int, u8);
extern int func_020b9e80(int *, int, u8, int);
extern int data_020dd184;
extern int data_020dd164;
extern void func_02057054(void *ptr);
extern void func_020edb3c(void *obj);
extern void *data_021fbe94;
extern void *func_021077e8(int);
extern void *func_020e9948(void *, int);
extern u8 *NNS_G3dGetAnmByIdx(void *a, int b);
extern void *NNSi_G3dGetTexPatAnmDataByIdx(u8 *hdr, int i);
extern void func_02056fcc(UnkStruct_0205678c *p, int n, u8 d, int e, int b);
extern void func_02056ffc(void *p);
extern int func_02057a50(unsigned int, int);
extern int func_02057a40(unsigned int, int);

void func_02056968(struct UnkStruct_02056968 *s, int a, int b);
void func_020568dc(struct UnkStruct_020568dc *s);
void func_02056730(UnkStruct_02056730_2 *s);

void *func_02056a8c(void *p)
{
    func_020ba01c((char *) p + 4);
    return p;
}

void func_02056a64(unsigned char *r0)
{
    unsigned char *r1;
    unsigned char r2;

    r2 = 0xff;
    r1 = r0 + 0x21;
    *r1 = r2;
    r1 = r0 + 0x22;
    *r1 = r2;
    r1 = r0 + 0x20;
    *r1 = r2;
    r2 = 0;
    r1 = r0 + 0x23;
    *r1 = r2;
    *(unsigned int *) r0 = r2;
    *(unsigned short *) (r0 + 0x24) = 0xffff;
}

int func_02056a4c(int arg)
{
    func_02056a64((unsigned char *) arg);
    func_020ba004(arg + 4);
    return 1;
}

void func_02056a38(void *arg0)
{
    void *r4;
    r4 = arg0;
    func_02056a64((unsigned char *) r4);
    func_020b9ec4((char *) r4 + 4);
}

void func_020569b0(struct UnkStruct_020569b0 *a, unsigned int b, unsigned char *c, int d, int e)
{
    u8 i;
    unsigned char *p;
    int w0m1;
    u16 w0;
    u8 ret;

    if (a->unk_22 == 0xff) {
        return;
    }
    if (b == a->unk_24) {
        return;
    }
    a->unk_24 = (u16) b;

    p = c + *(u16 *) ((int) a->unk_00 + 6);
    i = 0;
    w0 = *(u16 *) (int) a->unk_00;
    w0m1 = w0 - 1;
    while (i < w0m1) {
        if (*(u16 *) (p + 4) > b) {
            break;
        }
        p += 4;
        i = (u8) (i + 1);
    }

    if (a->unk_21 == i) {
        return;
    }
    a->unk_21 = i;

    ret = (u8) NNS_G3dGetResDictIdxByName((void *) (d + 0x3c), c + *(u16 *) (c + 8) + (p[2] << 4));
    if (ret == a->unk_20) {
        return;
    }
    a->unk_20 = ret;

    func_02056968((struct UnkStruct_02056968 *) a, e, d);
}

void func_02056968(struct UnkStruct_02056968 *s, int a, int b)
{
    int v = func_020579f0(b, s->unk_20);
    if (func_020b9e80(&s->unk_04, a, s->unk_22, v) == 0) {
        s->unk_21 = 0xff;
        s->unk_20 = 0xff;
        s->unk_24 = 0xffff;
    }
}

int func_02056958(struct UnkStruct_02056958 *p)
{
    return (p->flag & 1) ? 1 : 0;
}

struct UnkStruct_02056928 *func_02056928(struct UnkStruct_02056928 *obj)
{
    obj->unk_00 = &data_020dd184;
    obj->unk_08 = 0;
    obj->unk_0C = 0;
    obj->unk_10 = 0x1000;
    obj->unk_00 = &data_020dd164;
    func_020568dc((struct UnkStruct_020568dc *) obj);
    return obj;
}

void *func_02056910(void *ptr)
{
    *(void **) ptr = (void *) ((char *) &data_020dd164);
    func_02057054(ptr);
    return ptr;
}

void *func_020568f0(void *obj)
{
    *(void **) obj = (void *) ((unsigned char *) &data_020dd164);
    func_02057054(obj);
    func_020edb3c(obj);
    return obj;
}

void func_020568dc(struct UnkStruct_020568dc *s)
{
    s->unk_18 = 0;
    s->unk_24 = 0;
    s->unk_26 = 0;
    s->unk_28 = 0;
    s->unk_20 = 0;
}

int func_0205685c(struct UnkStruct_0205685c *s, int a, int b, unsigned char c, void *heap)
{
    int i;

    s->unk_18 = a;
    if (!heap) {
        heap = data_021fbe94;
    }
    s->unk_1C = func_021077e8(b);
    s->unk_26 = c;
    s->unk_28 = func_020e9948(heap, 40 * s->unk_26);
    if (!s->unk_28) {
        return 0;
    }
    for (i = 0; i < s->unk_26; i++) {
        if ((char *) s->unk_28 + 40 * i) {
            func_02056a8c((char *) s->unk_28 + 40 * i);
        }
        if (!func_02056a4c((int) ((char *) s->unk_28 + 40 * i))) {
            return 0;
        }
    }
    return 1;
}

void func_0205682c(struct unk *p)
{
    int i;
    for (i = 0; i < p->count; i++) {
        func_02056a38((void *) (&p->array[i]));
    }
    func_020568dc((struct UnkStruct_020568dc *) p);
}

void func_0205678c(UnkStruct_0205678c *p, void *res, int b, int n, u8 d, int e)
{
    u8 *base;
    u8 *q;
    int i;

    p->unk_20 = NNS_G3dGetAnmByIdx(res, 0);
    p->unk_24 = *(u16 *) (p->unk_20 + 4);
    if (n == 0) {
        n = p->unk_24;
    }
    base = p->unk_18 + *(int *) (p->unk_18 + 8);
    for (i = 0; i < p->unk_20[0xd]; i++) {
        q = p->unk_20 + 0xc;
        q = q + *(u16 *) (q + 6);
        p->unk_28[i].unk_22 = (u8) NNS_G3dGetResDictIdxByName((void *) (base + 4), (void *) (q + *(u16 *) (q + 2) + (i << 4)));
        p->unk_28[i].unk_00 = NNSi_G3dGetTexPatAnmDataByIdx(p->unk_20, i);
        p->unk_28[i].unk_21 = 0xff;
        p->unk_28[i].unk_20 = 0xff;
        p->unk_28[i].unk_24 = 0xffff;
    }
    func_02056fcc(p, n, d, e, b);
}

void func_02056778(void *p)
{
    func_02056ffc(p);
    func_02056730((UnkStruct_02056730_2 *) p);
}

void func_02056730(UnkStruct_02056730_2 *s)
{
    unsigned int flag = (s->unk_08 << 4) >> 16;
    int i;
    for (i = 0; i < s->unk_26; i++) {
        if (func_02056958((struct UnkStruct_02056958 *) (s->unk_28 + i)) == 0) {
            func_020569b0((struct UnkStruct_020569b0 *) (s->unk_28 + i), flag, (unsigned char *) s->unk_20, s->unk_1C,
                          s->unk_18);
        }
    }
}

int func_020566a0(struct MainObj *obj, int unused, int param3)
{
    u8 c;
    int i;
    int res1;
    res1 = func_02057a50(obj->unk_18, unused);
    if (res1 == (-1)) {
        return 0;
    }
    c = (u8) func_02057a40(obj->unk_1C, param3);
    if (c == (-1)) {
        return 0;
    }
    for (i = 0; i < obj->count; i++) {
        if (obj->arr[i].unk_22 == res1) {
            if (c != obj->arr[i].unk_20) {
                obj->arr[i].unk_20 = c;
                obj->arr[i].unk_21 = 0xff;
                obj->arr[i].unk_24 = 0xffff;
                func_02056968((struct UnkStruct_02056968 *) (&obj->arr[i]), obj->unk_18, obj->unk_1C);
                return 1;
            } else {
                return 0;
            }
        }
    }

    return 0;
}

void func_02056658(UnkStruct_02056658 *self, const char *name)
{
    unsigned char count;
    int value;
    int i;

    value = func_02057a50(self->unk_18, (int) name);
    if (value == -1) {
        return;
    }
    count = self->count;
    for (i = 0; i < count; i++) {
        if (value == self->arr[i].unk_22) {
            self->arr[i].unk_23 |= 1;
            break;
        }
    }
}

void func_02056610(UnkStruct_02056610 *self, int argument1)
{
    int i;
    int val;

    val = func_02057a50(self->unk_18, (int) argument1);
    if (val == -1) {
        return;
    }

    for (i = 0; i < self->count; i++) {
        if (val == self->array[i].unk_22) {
            self->array[i].unk_23 &= ~1;
            break;
        }
    }
}
