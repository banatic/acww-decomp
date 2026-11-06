/* effect_system_3: 26 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02091154 @ 0x02091154, 0x5c bytes, Thumb
 * func_02091140 @ 0x02091140, 0x14 bytes, Thumb
 * func_02091130 @ 0x02091130, 0x10 bytes, Thumb
 * func_0209110c @ 0x0209110c, 0x24 bytes, Thumb
 * func_020910e4 @ 0x020910e4, 0x26 bytes, Thumb
 * func_02090fd0 @ 0x02090fd0, 0x114 bytes, Thumb
 * func_02090fac @ 0x02090fac, 0x24 bytes, Thumb
 * func_02090f88 @ 0x02090f88, 0x24 bytes, Thumb
 * func_02090f5c @ 0x02090f5c, 0x2c bytes, Thumb
 * func_02090ef4 @ 0x02090ef4, 0x68 bytes, Thumb
 * func_02090ed4 @ 0x02090ed4, 0x20 bytes, Thumb
 * func_02090ebc @ 0x02090ebc, 0x18 bytes, Thumb
 * func_02090db0 @ 0x02090db0, 0x10c bytes, Thumb
 * func_02090d70 @ 0x02090d70, 0x40 bytes, Thumb
 * func_02090d64 @ 0x02090d64, 0xc bytes, Thumb
 * func_02090d50 @ 0x02090d50, 0x12 bytes, Thumb
 * func_02090c2c @ 0x02090c2c, 0x124 bytes, Thumb
 * func_02090ac4 @ 0x02090ac4, 0x168 bytes, Thumb
 * func_02090aa4 @ 0x02090aa4, 0x20 bytes, Thumb
 * func_02090a44 @ 0x02090a44, 0x60 bytes, Thumb
 * func_02090a2c @ 0x02090a2c, 0x18 bytes, Thumb
 * func_020909f8 @ 0x020909f8, 0x34 bytes, Thumb
 * func_0209099c @ 0x0209099c, 0x5a bytes, Thumb
 * func_02090968 @ 0x02090968, 0x32 bytes, Thumb
 * func_02090930 @ 0x02090930, 0x38 bytes, Thumb
 * func_020908a0 @ 0x020908a0, 0x8e bytes, Thumb
 */

#include "types.h"

typedef struct {
    volatile void *unk_00;
    unsigned char pad_04[0x58 - 4];
    unsigned char pad_58[0x35c - 0x58];
} UnkStruct_02091154;

struct UnkStruct_0209110c {
    char pad_00[0x50];
    void *unk_50;
};

typedef struct UnkStruct_02090fd0 {
    u8 pad_00[0x30];
    int unk_30;
} UnkStruct_02090fd0;

typedef struct UnkStruct_02090fd0_2 {
    u8 pad_00[0x50];
    UnkStruct_02090fd0 *unk_50;
    int unk_54;
    u8 unk_58[0x35c - 0x58];
    u8 unk_35C[0x181c - 0x35c];
    u8 unk_181C[4];
} UnkStruct_02090fd0_2;

typedef struct {
    int a;
    int b;
    int c;
} UnkStruct_02090f88;

typedef struct UnkStruct_02090f88_2 UnkStruct_02090f88_2;

struct Vec3 {
    int x;
    int y;
    int z;
};

struct UnkStruct_02090f5c {
    char pad_00[0x50];
    unsigned int unk_50;
};

typedef union {
    u16 v;
    struct {
        u16 r : 5;
        u16 g : 5;
        u16 b : 5;
        u16 a : 1;
    } c;
} UnkStruct_02090db0;

typedef struct {
    u8 pad_00[0x50];
    u8 unk_50;
} UnkStruct_02090db0_2;

typedef struct {
    UnkStruct_02090db0_2 *p;
} UnkStruct_02090db0_3;

typedef struct {
    u8 pad_00[0x18];
    UnkStruct_02090db0_3 *unk_18;
    u8 pad_1C[0x5a - 0x1c];
    u16 unk_5A;
} UnkStruct_02090db0_4;

struct UnkStruct_02090d70_2 {
    int pad_00;
    int unk_04;
    int unk_08;
    int unk_0C;
};

struct Mid {
    struct UnkStruct_02090d70_2 *p;
};

struct UnkStruct_02090d70_3 {
    char pad_00[0x18];
    struct Mid *m;
    int pad_1C;
    int unk_20;
    int unk_24;
    int unk_28;
};

struct UnkStruct_02090d70 {
    int unk_00;
    int unk_04;
    int unk_08;
};

typedef struct {
    unsigned int pad_00[3];
    unsigned int unk_0C;
} UnkStruct_02090d50;

typedef struct {
    u8 pad_00[0x20];
    s16 unk_20;
} UnkStruct_02090c2c;

typedef struct {
    u8 pad_00[8];
    UnkStruct_02090c2c *unk_08;
    u8 pad_0C[0x1c - 0xc];
    int unk_1C;
} UnkStruct_02090c2c_2;

typedef struct {
    u32 f0 : 1;
    u32 f1 : 1;
    u32 pad_flags : 30;
    int *unk_04;
    int count;
} TableEntry;

typedef struct {
    u8 pad_00[0x50];
    void *unk_50;
} Global;

typedef struct UnkStruct_02090ac4 {
    u8 a;
    u8 b;
    u8 c;
    u8 d;
} UnkStruct_02090ac4;

typedef struct Node {
    u8 pad_00[4];
    UnkStruct_02090ac4 unk_04;
    u8 unk_08;
    u8 unk_09;
    u8 pad_0A[0x10 - 0xa];
    void (*fns[1])(struct Node *);
} Node;

typedef struct UnkStruct_02090ac4_3 {
    u32 b0 : 1;
    u32 rest : 31;
    void **unk_04;
    int unk_08;
} UnkStruct_02090ac4_3;

typedef struct UnkStruct_02090ac4_2 {
    u8 pad_00[0x54];
    int unk_54;
} UnkStruct_02090ac4_2;

struct Flags {
    u8 a;
    u8 b;
    u8 c;
    u8 d;
};

struct UnkStruct_02090a44;

typedef void (*OutFunc)(struct UnkStruct_02090a44 *);

struct UnkStruct_02090a44 {
    int unk_00;
    u8 unk_04;
    u8 unk_05;
    u8 unk_06;
    u8 unk_07;
    u8 unk_08;
    u8 pad[3];
    int unk_0C;
    OutFunc unk_10;
    int unk_14;
};

struct In {
    OutFunc func;
    int data;
};

struct Global {
    u8 pad[0x50];
    void *unk_50;
};

struct UnkStruct_02090a2c {
    char pad[0x1C];
    unsigned int flags;
};

struct UnkStruct_02090a2c_2 {
    int first;
    char pad[8];
    struct UnkStruct_02090a2c *inner;
};

typedef struct {
    int a;
    int pad_04[5];
} UnkStruct_020909f8;

typedef struct {
    char flag;
    UnkStruct_020909f8 arr[32];
} UnkStruct_020909f8_2;

typedef struct {
    int unk_00;
    int pad_04;
    unsigned char unk_08;
    char pad_09[7];
    int (*fnarr[2])(void *);
} UnkStruct_0209099c;

typedef struct {
    char unk_00;
    char pad_01[3];
    UnkStruct_0209099c elems[32];
} UnkStruct_0209099c_2;

typedef struct {
    int unk_00;
    char pad_04[4];
    char unk_08;
    char pad_09[15];
} UnkStruct_02090968;

typedef struct {
    char unk_00;
    char pad_01[3];
    UnkStruct_02090968 elems[32];
} UnkStruct_02090968_2;

typedef struct UnkStruct_02090930 {
    int id;
    int unk_04;
    unsigned char flag;
    unsigned char pad_09[0xf];
} UnkStruct_02090930;

struct Entry {
    int unk_00;
    char rest[20];
};

struct UnkStruct_020908a0 {
    unsigned char idx;
    unsigned char pad_01[3];
    struct Entry entries[1];
};

struct Four {
    unsigned char d[4];
};

extern unsigned char data_020da13c[];
extern unsigned char data_020e2724[];
extern void *func_020edf70(unsigned int size);
extern void *func_020ee660(void *);
extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));
extern void *func_0209028c(void *);
extern void *func_020911b0(void *);
extern void *data_021d52cc;
extern void *NNS_FndAllocFromFrmHeapEx(void *heap, unsigned int size, int align);
extern void *func_02064b18(void *arg);
extern unsigned char data_020e276c;
extern int func_020fa3d0(void *arg);
extern int func_020fa3bc(void *arg);
extern void MI_CpuCopy8(void *p, int result, void *field);
extern void *data_021d52d4;
extern void *data_021d52d0;
extern void *func_020e98b4(int n);
extern void *NNS_FndCreateFrmHeapEx(void *h, int n, int z);
extern UnkStruct_02090fd0 *func_020fa9f4(void *fn, int a, int b, int c, int d, int e);
extern void func_020fa820(UnkStruct_02090fd0 *q, void *h);
extern void func_020fa564(UnkStruct_02090fd0 *q, void *r);
extern void func_020e9898(void *h);
extern void NNS_FndDestroyFrmHeap(void *h);
extern void MI_CpuFill8(void *dst, int c, int n);
extern void func_02090858(void *x);
extern void func_0209033c(void *x);
extern void func_02090834(void *p);
extern void func_020fa270(unsigned int value);
extern int func_0203f8d0(UnkStruct_02090f88_2 *p, UnkStruct_02090f88 *t);
extern void func_020fa204(unsigned int, void *, void *);
extern void func_02090810(void *);
extern unsigned int data_0213fee4;
extern void func_020907d8(void *);
extern void func_0209031c(void *);
extern void *data_021d52c4;
extern int func_0204cab4(void);
extern short *data_020e2488[];
extern short data_020e26bc[];
extern u16 func_02065858(void);
extern u16 func_020b7074(void);
extern TableEntry data_020d0f88[];
extern UnkStruct_02090c2c_2 *func_020902f8(void *sub_ptr, int val);
extern UnkStruct_02090c2c_2 *func_020fa0fc(void *f50, int val, int arg3_val);
extern int func_020902d0(void *sub_ptr, int val, UnkStruct_02090c2c_2 *obj);
extern void func_020fa090(void *f50, UnkStruct_02090c2c_2 *obj, int arg1);
extern void MIi_CpuClear32(u32 v, void *dst, u32 size);
extern void func_020907c4(void *, int, void (*callback)(void *));
extern int func_020fa190(void *, int, int);

void func_02090a2c(struct UnkStruct_02090a2c_2 *p);
void func_020909f8(UnkStruct_020909f8_2 *s);
void func_0209099c(UnkStruct_0209099c_2 *out);
void func_02090968(UnkStruct_02090968_2 *out);
UnkStruct_02090930 *func_02090930(void *self, int id);
int func_020908a0(struct UnkStruct_020908a0 *b, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6);

void *func_02091154(void)
{
    UnkStruct_02091154 *p = (UnkStruct_02091154 *) func_020edf70(0x186c);
    if (p != 0) {
        func_020ee660(p);
        p->unk_00 = (void *) data_020da13c;
        p->unk_00 = (void *) data_020e2724;
        func_020909f8((UnkStruct_020909f8_2 *) ((char *) p + 0x58));
        __cxa_vec_ctor((void *) ((char *) p + 0x35c), 4, 0x530, (((void (*)(void *)) func_020911b0)),
                       (((void (*)(void *)) func_0209028c)));
    }
    return p;
}

void *func_02091140(unsigned int param)
{
    return NNS_FndAllocFromFrmHeapEx(data_021d52cc, param, 4);
}

void *func_02091130(void *object)
{
    return func_02064b18(&data_020e276c);
}

int func_0209110c(struct UnkStruct_0209110c *param)
{
    if (func_020fa3d0(param->unk_50) && func_020fa3bc(param->unk_50)) {
        return 1;
    } else {
        return 0;
    }
}

int func_020910e4(void *unused, void *ptr)
{
    void *field;
    int result;

    field = *(void **) ((char *) ptr + 0x18);
    result = (int) func_02091140((unsigned int) field);
    if (result != 0) {
        ptr = (char *) ptr + 0x20;
        MI_CpuCopy8(ptr, result, field);
    }
    return result;
}

int func_02090fd0(UnkStruct_02090fd0_2 *p)
{
    int ok;
    void *h;
    void *r;

    ok = 0;
    (*(UnkStruct_02090fd0_2 **) &data_021d52c4) = p;
    p->unk_50 = 0;
    data_021d52cc = 0;
    p->unk_54 = 0;
    data_021d52d4 = 0;
    data_021d52d0 = func_020e98b4(0xc000);
    if (data_021d52d0 != 0) {
        data_021d52cc = NNS_FndCreateFrmHeapEx(data_021d52d0, 0xc000, 0);
        p->unk_50 = func_020fa9f4((void *) (void *(*) (int) ) func_02091140, 0x20, 0x64, 0x14, 0x15, 0x32);
        p->unk_50->unk_30 = 0x8800;
        if (p->unk_50 != 0) {
            h = func_02091130(p);
            if (h != 0) {
                func_020fa820(p->unk_50, h);
                if (func_0209110c((struct UnkStruct_0209110c *) p)) {
                    r = (void *) func_020910e4((void *) p, h);
                    if (r != 0) {
                        func_020fa564(p->unk_50, r);
                        ok = 1;
                    }
                }
                func_020e9898(h);
            }
        }
    }
    if (ok == 0) {
        if (data_021d52cc != 0) {
            NNS_FndDestroyFrmHeap(data_021d52cc);
            data_021d52cc = 0;
        }
        if (data_021d52d0 != 0) {
            func_02090968((UnkStruct_02090968_2 *) p->unk_58);
            func_020e9898(data_021d52d0);
            data_021d52d0 = 0;
        }
    } else {
        MI_CpuFill8(p->unk_35C, 0, 0x14c0);
        func_02090858(p->unk_35C);
        func_0209033c(p->unk_181C);
    }
    return ok;
}

int func_02090fac(unsigned char *param)
{
    func_0209099c((UnkStruct_0209099c_2 *) (param + 0x58));
    func_02090834(param + 0x35c);
    func_020fa270(*(unsigned int *) (param + 0x50));
    return 1;
}

unsigned short func_02090f88(UnkStruct_02090f88_2 *p, UnkStruct_02090f88 v)
{
    UnkStruct_02090f88 t;
    t.a = v.a;
    t.b = v.b;
    t.c = v.c;
    return (unsigned short) func_0203f8d0(p, &t);
}

int func_02090f5c(struct UnkStruct_02090f5c *param)
{
    func_020fa204(param->unk_50, &data_0213fee4, (void *) (unsigned short (*)(void *, struct Vec3)) func_02090f88);
    func_02090810((char *) param + 0x35c);
    return 1;
}

int func_02090ef4(void *obj)
{
    if (data_021d52cc) {
        NNS_FndDestroyFrmHeap(data_021d52cc);
        data_021d52cc = 0;
    }
    if (data_021d52d0) {
        func_02090968((UnkStruct_02090968_2 *) ((char *) obj + 0x58));
        func_020e9898(data_021d52d0);
        data_021d52d0 = 0;
    }
    func_020907d8((char *) obj + 0x35c);
    func_0209031c((char *) obj + 0x181c);
    data_021d52c4 = 0;
    return 1;
}

short func_02090ed4(void *obj)
{
    int idx;
    unsigned char b;
    idx = func_0204cab4();
    b = ((unsigned char *) obj)[0x80];
    return data_020e2488[b][idx];
}

int func_02090ebc(void)
{
    return data_020e26bc[func_0204cab4()];
}

void func_02090db0(UnkStruct_02090db0_4 *a0)
{
    volatile UnkStruct_02090db0 v0;
    volatile UnkStruct_02090db0 v2;
    volatile UnkStruct_02090db0 v4;
    volatile UnkStruct_02090db0 v6;
    volatile UnkStruct_02090db0 v8;
    volatile UnkStruct_02090db0 va;
    volatile UnkStruct_02090db0 vc;
    volatile UnkStruct_02090db0 ve;
    u8 flags;

    flags = a0->unk_18->p->unk_50;
    if (flags & 0x80) {
        v4.v = func_02065858();
        va = v4;
        v6 = va;
        if (flags & 0x40) {
            v8.v = func_020b7074();
        } else if (flags & 0x20) {
            v2.v = (u16) func_02090ed4((void *) a0);
            vc = v2;
            v8 = vc;
        } else if (flags & 8) {
            v0.v = (u16) func_02090ebc();
            ve = v0;
            v8 = ve;
        } else {
            v8.v = 0x7fff;
        }
        v6.c.r = v8.c.r * v6.c.r / 31;
        v6.c.g = v8.c.g * v6.c.g / 31;
        v6.c.b = v8.c.b * v6.c.b / 31;
        a0->unk_5A = v6.v;
    }
}

void func_02090d70(struct UnkStruct_02090d70_3 *self)
{
    func_02090db0((UnkStruct_02090db0_4 *) self);
    if ((*(struct UnkStruct_02090d70 **) &data_021d52d4)) {
        struct UnkStruct_02090d70 *gp = (*(struct UnkStruct_02090d70 **) &data_021d52d4);
        self->unk_20 = gp->unk_00 + self->m->p->unk_04;
        self->unk_24 = gp->unk_04 + self->m->p->unk_08;
        self->unk_28 = gp->unk_08 + self->m->p->unk_0C;
    }
}

void func_02090d64(void *self)
{
    func_02090d70((struct UnkStruct_02090d70_3 *) (*(void **) ((char *) self + 12)));
}

int func_02090d50(UnkStruct_02090d50 *p)
{
    func_02090db0((UnkStruct_02090db0_4 *) p->unk_0C);
    return 1;
}

int func_02090c2c(int id, int arg1, s16 *arg2, int *arg3)
{
    Global *glob;
    TableEntry *entry;
    int count;
    int *p4;
    int i;
    void *sub_ptr;
    UnkStruct_02090c2c_2 *obj;
    UnkStruct_02090c2c_2 *new_obj;
    int s_idx1;
    int s_idx2;
    UnkStruct_02090c2c *sub;

    if (arg1 == 0) {
        return 0;
    }

    glob = (*(Global **) &data_021d52c4);
    entry = &data_020d0f88[id];
    count = entry->count;
    p4 = entry->unk_04;

    if (arg2 != 0) {
        if (entry->f0 == 1) {
            count >>= 1;
            if (arg2[0] >= 0) {
                p4 += count;
            }
        }
    }

    (*(int *) &data_021d52d4) = arg1;

    if (entry->f1 != 0) {
        sub_ptr = (char *) glob + 0x181c;
        i = 0;
        s_idx1 = 0;
        s_idx2 = 0;
        while (i < count) {
            obj = func_020902f8(sub_ptr, *p4);
            if (obj == 0) {
                new_obj = func_020fa0fc((*(Global **) &data_021d52c4)->unk_50, *p4, *arg3);
                if (new_obj != 0) {
                    if (func_020902d0(sub_ptr, *p4, new_obj) != 0) {
                        new_obj->unk_1C |= 2;
                        func_020fa090((*(Global **) &data_021d52c4)->unk_50, new_obj, arg1);
                        sub = new_obj->unk_08;
                        if (arg2 != 0) {
                            sub->unk_20 = arg2[s_idx2];
                        }
                    }
                }
            } else {
                func_020fa090((*(Global **) &data_021d52c4)->unk_50, obj, arg1);
                sub = obj->unk_08;
                if (arg2 != 0) {
                    sub->unk_20 = arg2[s_idx1];
                }
            }
            p4++;
            arg3++;
            i++;
        }
    } else {
        for (i = 0; i < count; i++) {
            func_020fa0fc((*(Global **) &data_021d52c4)->unk_50, *p4, *arg3);
            p4++;
            arg3++;
        }
    }

    (*(int *) &data_021d52d4) = 0;
    return 1;
}

int func_02090ac4(int idx, void *p1, short *p2, u8 *p3)
{
    void *base;
    int cnt;
    int ok;
    int zero2;
    UnkStruct_02090ac4 bufA;
    UnkStruct_02090ac4 bufB;
    UnkStruct_02090ac4 bufC;
    volatile int zero;
    void *arr[10];
    UnkStruct_02090ac4_3 *e;
    void **w;
    Node *n;
    int i;
    int j;
    void (**pf)(Node *);

    ok = 1;
    zero = 0;
    MIi_CpuClear32(zero, arr, 0x28);
    if (p1 == 0) {
        return 0;
    }
    base = (*(UnkStruct_02090ac4_2 **) &data_021d52c4);
    base = (u8 *) base + 0x58;
    e = &((UnkStruct_02090ac4_3 *) data_020d0f88)[idx];
    cnt = e->unk_08;
    w = e->unk_04;
    if (p2 != 0) {
        if (e->b0 == 1) {
            cnt = cnt >> 1;
            if (p2[0] >= 0) {
                w = w + cnt;
            }
        }
    }
    data_021d52d4 = p1;
    i = 0;
    zero2 = 0;
    goto test;
body:
    n = (Node *) func_02090930(base, (int) (*w));
    if (n != 0) {
        n->unk_08 = 1;
        n->unk_09 = (u8) i;
        bufB = n->unk_04;
        bufA.a = bufB.a;
        bufA.b = bufB.b;
        bufA.c = bufB.c;
        bufA.d = bufB.d;
        bufA.b = (u8) (*(UnkStruct_02090ac4_2 **) &data_021d52c4)->unk_54;
        bufA.c = (u8) i;
        bufC = bufA;
        n->unk_04.a = bufC.a;
        n->unk_04.b = bufC.b;
        n->unk_04.c = bufC.c;
        n->unk_04.d = bufC.d;
        pf = n->fns;
        if (pf != 0) {
            pf[0](n);
        }
    } else {
        n = (Node *) func_020908a0((struct UnkStruct_020908a0 *) base, (int) (*w), (int) p1, (int) p2, (int) p3,
                                   (*(UnkStruct_02090ac4_2 **) &data_021d52c4)->unk_54, i);
        if (n == 0) {
            ok = zero2;
        }
    }
    if (ok == 0) {
        j = 0;
        goto jtest;
    jbody:
        func_02090a2c((struct UnkStruct_02090a2c_2 *) arr[j]);
        j++;
    jtest:
        if (j < i) {
            goto jbody;
        }
        goto done;
    }
    arr[i] = n;
    w = w + 1;
    p3 = p3 + 8;
    i++;
test:
    if (i < cnt) {
        goto body;
    }
done:
    data_021d52d4 = 0;
    (*(UnkStruct_02090ac4_2 **) &data_021d52c4)->unk_54 = (*(UnkStruct_02090ac4_2 **) &data_021d52c4)->unk_54 + 1;
    return ok;
}

void func_02090aa4(int index, void (*callback)(void *))
{
    func_020907c4((char *) data_021d52c4 + 0x35c, index, callback);
}

int func_02090a44(struct UnkStruct_02090a44 *out, int arg1, int arg2, int arg3, struct In *src, struct Flags flags)
{
    u8 b = flags.b;
    u8 c = flags.c;
    u8 d = flags.d;
    int ret = 0;

    out->unk_0C = func_020fa190((*(struct Global **) &data_021d52c4)->unk_50, arg1, arg2);
    if (out->unk_0C != 0) {
        out->unk_00 = arg1;
        out->unk_08 = 1;
        out->unk_10 = src->func;
        out->unk_14 = src->data;
        out->unk_04 = flags.a;
        out->unk_05 = b;
        out->unk_06 = c;
        out->unk_07 = d;
        src->func(out);
        ret = 1;
    }
    return ret;
}

void func_02090a2c(struct UnkStruct_02090a2c_2 *p)
{
    struct UnkStruct_02090a2c *inner;
    inner = p->inner;
    if (inner != 0) {
        inner->flags = (inner->flags & ~1) | 1;
    }
    p->first = -1;
}

void func_020909f8(UnkStruct_020909f8_2 *s)
{
    UnkStruct_020909f8 *p;
    int i;

    p = &s->arr[0];
    do {
        p->a = -1;
        p++;
    } while (p != &s->arr[32]);

    s->flag = 0;

    for (i = 0; i < 32; i++) {
        s->arr[i].a = -1;
    }
}

void func_0209099c(UnkStruct_0209099c_2 *out)
{
    UnkStruct_0209099c *p = out->elems;
    int i = 0;
    int val = i;
    int c = i;
    int sentinel = i;
    unsigned int t;
    int (**fp)(void *);

    for (; i < 32; p++, i++) {
        if (p->unk_00 != ~sentinel) {
            fp = p->fnarr;
            p->unk_08 = (char) val;
            if (fp != 0) {
                if (fp[1](p) != 0) {
                    p->unk_08 = 1;
                }
            }
            if (p->unk_08 == 1) {
                t = 1;
            } else {
                t = c;
            }
            if (t == 0) {
                func_02090a2c((struct UnkStruct_02090a2c_2 *) p);
                out->unk_00 = (char) i;
            }
        }
    }
}

void func_02090968(UnkStruct_02090968_2 *out)
{
    UnkStruct_02090968 *p = out->elems;
    int i = 0;
    int val = i;
    int sentinel = i;
    for (; i < 32; p++, i++) {
        if (p->unk_00 != ~sentinel) {
            p->unk_08 = (char) val;
            func_02090a2c((struct UnkStruct_02090a2c_2 *) p);
            out->unk_00 = (char) i;
        }
    }
}

UnkStruct_02090930 *func_02090930(void *self, int id)
{
    UnkStruct_02090930 *res;
    UnkStruct_02090930 *e;
    int i;
    unsigned int t;

    e = (UnkStruct_02090930 *) ((char *) self + 4);
    res = 0;
    for (i = 0; i < 0x20; i++) {
        if (id == e->id) {
            if (e->flag == 1) {
                t = 1;
            } else {
                t = 0;
            }
            if (t > 0) {
                goto next;
            }
            res = e;
            goto done;
        }
    next:
        e = (UnkStruct_02090930 *) ((char *) e + 0x18);
    }
done:
    return res;
}

int func_020908a0(struct UnkStruct_020908a0 *b, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6)
{
    int result = 0;
    int i;
    unsigned char buf[4];

    buf[1] = (unsigned char) arg5;
    buf[2] = (unsigned char) arg6;
    for (i = 0; i < 32; i++) {
        int idx = b->idx;
        if (b->entries[idx].unk_00 == -1) {
            buf[0] = (unsigned char) idx;
            if (func_02090a44((struct UnkStruct_02090a44 *) (&b->entries[idx]), arg1, arg2, arg3, (struct In *) arg4,
                              *(struct Flags *) &(*(struct Four *) buf)) != 0) {
                result = (int) &b->entries[b->idx];
                b->idx = (unsigned char) ((b->idx + 1) % 32);
                break;
            }
            break;
        } else {
            b->idx = (unsigned char) ((idx + 1) % 32);
        }
    }
    return result;
}
