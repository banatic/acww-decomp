/* func_ov003_0221f270 @ 0x0221f270, 0x140 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
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
