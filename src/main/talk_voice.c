/* talk_voice: 19 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02068bc4 @ 0x02068bc4, 0x4 bytes, Thumb
 * func_02068bbc @ 0x02068bbc, 0x6 bytes, Thumb
 * func_02068bb8 @ 0x02068bb8, 0x4 bytes, Thumb
 * func_02068bb0 @ 0x02068bb0, 0x6 bytes, Thumb
 * func_02068b88 @ 0x02068b88, 0x28 bytes, Thumb
 * func_02068b64 @ 0x02068b64, 0x24 bytes, Thumb
 * func_02068b30 @ 0x02068b30, 0x34 bytes, Thumb
 * func_02068b24 @ 0x02068b24, 0xc bytes, Thumb
 * func_02068b0c @ 0x02068b0c, 0x18 bytes, Thumb
 * func_02068ae4 @ 0x02068ae4, 0x28 bytes, Thumb
 * func_02068ad0 @ 0x02068ad0, 0x12 bytes, Thumb
 * func_02068a04 @ 0x02068a04, 0xcc bytes, Thumb
 * func_02068a00 @ 0x02068a00, 0x4 bytes, Thumb
 * func_020689b4 @ 0x020689b4, 0x4c bytes, Thumb
 * func_0206899c @ 0x0206899c, 0x18 bytes, Thumb
 * func_02068958 @ 0x02068958, 0x44 bytes, Thumb
 * func_02068924 @ 0x02068924, 0x34 bytes, Thumb
 * func_020688e0 @ 0x020688e0, 0x44 bytes, Thumb
 * func_020688dc @ 0x020688dc, 0x2 bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned char pad_00[32];
    unsigned long unk_20;
} UnkStruct_02068bbc;

typedef struct {
    unsigned char pad_00[20];
    unsigned long unk_14;
} UnkStruct_02068bb0;

struct UnkStruct_02068b88 {
    char pad_00[0x20];
    int unk_20;
    int unk_24;
};

typedef void *(*FuncType)(void *);

struct UnkStruct_02068b30 {
    void *unk_00;
    int unk_04;
    char pad_08[12];
    int unk_14;
    int unk_18;
    char unk_1C;
    char unk_1D;
    char unk_1E;
    char pad_1F;
    int unk_20;
    int unk_24;
    int unk_28;
};

typedef struct {
    char pad_00[8];
    unsigned short arr[2];
    unsigned short cond;
    int zero;
} UnkStruct_02068ae4;

typedef struct {
    u32 unk_00;
    u32 unk_04;
    u16 data[4];
    int count;
    u8 pad_14[8];
    u8 flag1c;
    u8 flag1d;
    u8 flag1e;
    u8 pad_1F[5];
    u32 unk_24;
    u32 unk_28;
} UnkStruct_02068a04;

typedef struct UnkStruct_020689b4 UnkStruct_020689b4;

typedef int (*Func)(UnkStruct_020689b4 *);

typedef struct Vtbl {
    char pad_00[0x6c];
    Func fn;
} Vtbl;

struct UnkStruct_020689b4 {
    Vtbl *vtbl;
};

typedef struct UnkStruct_020689b4_2 {
    char pad_00[0x14a8];
    UnkStruct_020689b4 *obj;
} UnkStruct_020689b4_2;

typedef struct Main {
    char pad_00[4];
    UnkStruct_020689b4_2 *inner;
    char pad_08[0x18 - 0x08];
    int unk_18;
    char pad_1C[0x20 - 0x1c];
    int unk_20;
    int unk_24;
} Main;

typedef struct {
    char pad_00[0x24];
    int unk_24;
} UnkStruct_0206899c;

struct UnkStruct_02068958 {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    int unk_14;
    int unk_18;
    int unk_1C;
    int unk_20;
    int unk_24;
    int unk_28;
};

typedef struct UnkStructC UnkStructC;

typedef struct UnkTable {
    char pad_00[0x68];
    int (*func)(UnkStructC *);
} UnkTable;

struct UnkStructC {
    UnkTable *table;
};

typedef struct UnkStructB {
    char pad_00[0x14a8];
    UnkStructC *obj;
} UnkStructB;

typedef struct UnkStructA {
    char pad_00[4];
    UnkStructB *b;
} UnkStructA;

struct UnkStruct_020688e0_2;

struct VT {
    unsigned char pad_00[0x6c];
    int (*unk_6C)(struct UnkStruct_020688e0_2 *o);
};

struct UnkStruct_020688e0_2 {
    struct VT *vt;
};

typedef struct {
    unsigned char pad_00[4];
    unsigned char *unk_04;
    unsigned char pad_08[0x1c];
    int unk_24;
    int unk_28;
} UnkStruct_020688e0;

extern void func_020045cc(int param);
extern char data_020def3c;
extern void func_020edb3c(unsigned int *p);
extern unsigned short data_020cb8f4;
extern void func_0200467c(int cmd);
extern void func_020045f4(int a, int b, int c, int d);
extern void func_020680ec(u32 p, int flag);
extern void func_020680d0(u32 p);
extern int func_02004618(int v);
extern void func_020045dc(void);
extern int func_0203d438(void);
extern unsigned char data_020cce7c[];
extern unsigned char data_020cce88[];
extern int func_0207f270(int arg);
extern int func_020794c4(int arg);

void func_02068ae4(UnkStruct_02068ae4 *p, int flag);
unsigned char func_02068958(struct UnkStruct_02068958 *self);
unsigned char func_02068924(UnkStructA *arg0);
void func_020688e0(UnkStruct_020688e0 *p);
void func_020688dc(void *receiver);

void func_02068bc4(int *p0, int p1)
{
    p0[8] = p1;
}

void func_02068bbc(UnkStruct_02068bbc *p)
{
    p->unk_20 = 5;
}

void func_02068bb8(int *p0, int p1)
{
    p0[5] = p1;
}

void func_02068bb0(UnkStruct_02068bb0 *p)
{
    p->unk_14 = 7;
}

void func_02068b88(struct UnkStruct_02068b88 *param0, int param1)
{
    if (param0->unk_20 == 5 && param0->unk_24 != 5 && param0->unk_24 != param1) {
        func_020045cc(param1);
        param0->unk_24 = param1;
    }
}

void func_02068b64(void *p)
{
    void *base;
    void *obj;
    void *vtable;
    FuncType fn;
    void *ret;

    base = *(void **) ((char *) p + 4);
    obj = *(void **) ((char *) base + 0x14a8);
    vtable = *(void **) obj;
    fn = *(FuncType *) ((char *) vtable + 0x6c);
    ret = fn(obj);
    func_02068b88((struct UnkStruct_02068b88 *) p, (int) ret);
}

struct UnkStruct_02068b30 *func_02068b30(struct UnkStruct_02068b30 *p, int arg)
{
    p->unk_00 = &data_020def3c;
    p->unk_04 = arg;
    p->unk_14 = 7;
    p->unk_18 = 0;
    p->unk_1C = 0;
    p->unk_1D = 0;
    p->unk_1E = 0;
    p->unk_20 = 5;
    p->unk_24 = 5;
    p->unk_28 = 0;
    func_02068ae4((UnkStruct_02068ae4 *) p, 1);
    return p;
}

void func_02068b24(int *p)
{
    *p = (int) ((int *) &data_020def3c);
}

unsigned int *func_02068b0c(unsigned int *p)
{
    *p = (unsigned int) ((unsigned int *) &data_020def3c);
    func_020edb3c(p);
    return p;
}

void func_02068ae4(UnkStruct_02068ae4 *p, int flag)
{
    int i = 0;
    unsigned short val = data_020cb8f4;

    do {
        p->arr[i] = val;
        i++;
    } while (i < 2);

    if (flag) {
        p->cond = val;
    }

    p->zero = 0;
}

void func_02068ad0(void *r0, short r1)
{
    int r3;
    int r2;

    r3 = *(int *) ((char *) r0 + 0x10);
    if (r3 < 2) {
        r2 = r3 + 1;
        *(int *) ((char *) r0 + 0x10) = r2;
        r2 = r3 << 1;
        r0 = (char *) r0 + r2;
        *(short *) ((char *) r0 + 8) = r1;
    }
}

void func_02068a04(UnkStruct_02068a04 *self)
{
    int res1, res2;
    int flag, i;
    u16 base, v;

    func_020688e0((UnkStruct_020688e0 *) self);
    func_020688dc((void *) self);
    if (self->flag1c != 0 || self->flag1d != 0) {
    } else {
        res1 = (int) func_02068958((struct UnkStruct_02068958 *) self);
        res2 = (int) func_02068924((UnkStructA *) self);
        if (self->count >= 1) {
            if (self->unk_24 == 5) {
                if (res1 != 2) {
                    func_0200467c(0x2c);
                }
            } else {
                func_020045f4(res1, res2, self->data[0], self->data[1]);
            }
        }
        flag = 0;
        if (self->unk_28 != 4) {
            i = 0;
            base = (*(u16 *) &data_020cb8f4);
            while (i < self->count) {
                v = self->data[i];
                if (v != base && v != 0x3000 && v != 0x0a && v != 0x30fb && v != 0xff01 && v != 0xff1f && v != 0xfe &&
                    v != 0xff0c) {
                    flag = 1;
                }
                i++;
            }
        }
        func_020680ec(self->unk_04, flag);
    }
    if (self->flag1e != 0) {
        func_020680d0(self->unk_04);
    }
}

void func_02068a00(int *p0, int p1)
{
    p0[6] = p1;
}

void func_020689b4(Main *p)
{
    int r4 = 5;
    if (p->unk_20 != 5) {
        r4 = p->unk_20;
    } else {
        if ((int) func_02068958((struct UnkStruct_02068958 *) p) == 0) {
            if (p->unk_18 == 3) {
                r4 = 1;
            } else {
                r4 = p->inner->obj->vtbl->fn(p->inner->obj);
            }
        }
    }
    p->unk_24 = r4;
    if (r4 != 5) {
        func_02004618(r4);
    }
}

void func_0206899c(UnkStruct_0206899c *p)
{
    if (p->unk_24 != 5) {
        func_020045dc();
    }
    p->unk_24 = 5;
}

unsigned char func_02068958(struct UnkStruct_02068958 *self)
{
    int ret;
    int c;
    int flag;
    int index;
    ret = func_0203d438();
    c = self->unk_18;
    flag = (ret == 0);
    if (self->unk_14 != 7) {
        c = self->unk_14;
    }
    index = ret;
    if (c != 0 && c != 3 && flag) {
        index = 1;
    }
    if (self->unk_28 == 4 && flag) {
        index = 1;
    }
    return data_020cce7c[index];
}

unsigned char func_02068924(UnkStructA *arg0)
{
    int idx = 0;
    UnkStructB *b;
    UnkStructC *obj;
    int result1;
    int result2;

    b = arg0->b;
    obj = b->obj;
    result1 = obj->table->func(obj);
    if (result1 != 0) {
        result2 = func_0207f270(result1);
        if (result2 != 0) {
            idx = func_020794c4(result2);
        }
    }
    return data_020cce88[idx];
}

void func_020688e0(UnkStruct_020688e0 *p)
{
    int m = 5;
    if (p->unk_24 == 0) {
        if (p->unk_28 == 9) {
            m = 4;
        }
    } else if (p->unk_24 == 4) {
        if (p->unk_28 != 9) {
            struct UnkStruct_020688e0_2 *o = *(struct UnkStruct_020688e0_2 **) (p->unk_04 + 0x14a8);
            m = o->vt->unk_6C(o);
        }
    }
    if (m != 5) {
        func_02068b88((struct UnkStruct_02068b88 *) p, m);
    }
}

void func_020688dc(void *receiver) {}
