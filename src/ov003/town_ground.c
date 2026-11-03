/* town_ground: 11 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_0221f270 @ 0x0221f270, 0x140 bytes, Thumb
 * func_ov003_0221f244 @ 0x0221f244, 0x2a bytes, Thumb
 * func_ov003_0221f230 @ 0x0221f230, 0x14 bytes, Thumb
 * func_ov003_0221f21c @ 0x0221f21c, 0x12 bytes, Thumb
 * func_ov003_0221f204 @ 0x0221f204, 0x16 bytes, Thumb
 * func_ov003_0221f1f4 @ 0x0221f1f4, 0x10 bytes, Thumb
 * func_ov003_0221f1ec @ 0x0221f1ec, 0x8 bytes, Thumb
 * func_ov003_0221f1ac @ 0x0221f1ac, 0x40 bytes, Thumb
 * func_ov003_0221f144 @ 0x0221f144, 0x68 bytes, Thumb
 * func_ov003_0221f120 @ 0x0221f120, 0x24 bytes, Thumb
 * func_ov003_0221f110 @ 0x0221f110, 0x10 bytes, Thumb
 */

#include "types.h"

typedef struct Data48 {
    int data[12];
} Data48;

typedef struct Node {
    char pad_00[8];
    void *unk_08;
    char pad1[0x14];
    int unk_20;
} Node;

typedef struct Src {
    char pad_00[0x20];
    Node *node;
} Src;

typedef struct UnkStruct_0221f270 {
    void *unk_00;
    char subB[0x64];
    Data48 copyData;
    char pad1[8];
    int unk_A0;
    int unk_A4;
    char subA[0x20];
    char subD[0x20];
    s8 unk_E8;
} UnkStruct_0221f270;

struct UnkStruct_0221f244 {
    char pad_00[0x8];
    unsigned int val;
    char pad_0C[0xC];
    unsigned int *ptr;
    char pad_1C[0x4];
};

struct UnkStruct_0221f244_2 {
    char pad_00[0xA8];
    struct UnkStruct_0221f244 arr[2];
};

struct UnkStruct_0221f1ac {
    char pad_00[0x9c];
    int unk_9C;
};

struct UnkStruct_0221f1ac_2 {
    int unk_00;
    int unk_04;
    int unk_08;
};

typedef struct {
    fx32 x, y, z;
} Vec;

typedef struct {
    fx32 m[12];
} Mtx43;

typedef struct {
    char pad_00[0x64];
    Mtx43 m;
} UnkStruct_0221f144;

extern int data_021c9b24;
extern int data_020ca0ec;
extern Data48 data_021fbe48;
extern int data_ov003_02239aa0[];
extern void *func_02037e84(Src *src);
extern void *func_0203750c(void);
extern int func_02037594(void *a);
extern int func_02037588(void *a);
extern int func_0203757c(void *a);
extern int func_02055f40(void *sub, void *field8, int tmp);
extern int func_0205650c(void *sub, void *field8, int global);
extern void func_02056478(void *sub, int a, int b, int c, int d);
extern int func_02055e00(void *sub);
extern void func_020563dc(void *sub, int a);
extern void func_020e96c8(void *arr, int a, int b, int c);
extern void func_020e9774(void *arr, int v);
extern int func_0203f760(void);
extern int func_02037bd8(void *a);
extern int func_02057a50(void *object, const char *name);
extern void func_02055dc8(void *sub, void *fn, UnkStruct_0221f270 *obj);
extern void func_ov003_0221f668(void *sub, int a);
extern void func_ov003_0221fdb8(void *unused0);
extern void func_02056ffc(void *p);
extern void func_02055e7c(char *a, int b);
extern int func_02055f1c(void *ptr);
extern void *func_0205577c(int x);
extern void *func_02055764(int);
extern void *func_02037608(void *p, int n);
extern void *data_021c67a4; // 0x021c67a4
extern Vec data_021c67d0;   // 0x021c67d0
extern fx32 data_020ca0e4;
extern int func_0203c590(void *);

void func_ov003_0221f1ec(int p0);
int func_ov003_0221f144(UnkStruct_0221f144 *self);

int func_ov003_0221f270(UnkStruct_0221f270 *obj, Src *src, int a2, int a3)
{
    Node *node;
    void *field8;
    int tmp;

    obj->unk_A0 = a2;
    obj->unk_A4 = a3;
    obj->unk_00 = func_02037e84(src);

    tmp = func_02037594(func_0203750c());
    node = src->node;
    if (node->unk_20 != 0) {
        tmp = node->unk_20;
    }
    field8 = node->unk_08;
    func_02055f40(obj->subB, field8, tmp);

    if (func_0205650c(obj->subA, field8, data_021c9b24) != 0) {
        func_02056478(obj->subA, func_02037588(func_0203750c()), 0, 0x1000, 0);
        func_020563dc(obj->subA, func_02055e00(obj->subB));
    }

    if (func_0205650c(obj->subD, field8, data_021c9b24) != 0) {
        func_02056478(obj->subD, func_0203757c(func_0203750c()), 0, 0x1000, 0);
        func_020563dc(obj->subD, func_02055e00(obj->subB));
    }

    func_020e96c8(&data_021fbe48, a2 * data_020ca0ec, 0, 0);
    a3 *= func_0203f760();
    a3 = (s16) a3;
    func_020e9774(&data_021fbe48, a3);

    obj->copyData = data_021fbe48;

    if ((func_02037bd8(obj->unk_00) & 8) != 0) {
        obj->unk_E8 = (s8) func_02057a50((void *) (field8), (const char *) (data_ov003_02239aa0));
        if (obj->unk_E8 != -1) {
            func_02055dc8(obj->subB, func_ov003_0221fdb8, obj);
        }
    }

    func_ov003_0221f668(obj->subB, 1);
    return 1;
}

int func_ov003_0221f244(struct UnkStruct_0221f244_2 *out)
{
    struct UnkStruct_0221f244 *p;
    for (p = out->arr; p < &out->arr[2]; p++) {
        func_02056ffc(p);
        *p->ptr = p->val;
    }
    return 1;
}

int func_ov003_0221f230(char *p)
{
    func_02055e7c(p + 4, 0);
    return 1;
}

int func_ov003_0221f21c(void *arg)
{
    func_02055f1c((char *) arg + 4);
    return 1;
}

int func_ov003_0221f204(int x)
{
    func_0205577c(x);
    func_ov003_0221f1ec(x);
    return x;
}

int func_ov003_0221f1f4(int x)
{
    func_02055764(x);
    return x;
}

void func_ov003_0221f1ec(int p0)
{
    *(int *) ((char *) (((int) (p0) + (156))) + (0)) = 0;
}

int func_ov003_0221f1ac(struct UnkStruct_0221f1ac *self)
{
    struct UnkStruct_0221f1ac_2 *b;
    int res;

    b = (struct UnkStruct_0221f1ac_2 *) func_02037608(func_0203750c(), 0x83);
    res = func_02037594(func_0203750c());
    self->unk_9C = b->unk_08;
    func_02055f40(self, (void *) self->unk_9C, res);
    func_ov003_0221f144((UnkStruct_0221f144 *) self);
    return 1;
}

int func_ov003_0221f144(UnkStruct_0221f144 *self)
{
    void *x = data_021c67a4;
    volatile fx32 coordinates[3];
    if (x != 0) {
        coordinates[0] = data_021c67d0.x;
        coordinates[1] = data_021c67d0.y;
        coordinates[2] = data_021c67d0.z;
        func_020e96c8((void *) (((Mtx43 *) &data_021fbe48)), (fx32) (data_021c67d0.x - data_020ca0e4), 0, 0);
        func_020e9774((void *) (((Mtx43 *) &data_021fbe48)), func_0203c590(x));
        self->m = (*(Mtx43 *) &data_021fbe48);
        return 1;
    }
    return 0;
}

int func_ov003_0221f120(int arg)
{
    if ((*(int *) &data_021c67a4)) {
        func_02055e7c((char *) arg, 0);
        return 1;
    }
    return 0;
}

int func_ov003_0221f110(void *argument0)
{
    func_02055f1c(argument0);
    return 1;
}
