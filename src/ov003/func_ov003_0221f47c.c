/* func_ov003_0221f47c @ 0x0221f47c, 0x130 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct RetPtr {
    int pad_00[2];
    void *unk_08;
} RetPtr;

typedef struct Data48 {
    int data[12];
} Data48;

typedef struct UnkStruct_0221f47c {
    char pad_00[0x64];
    Data48 copyData;
    char pad_94[8];
    int unk_9C;
    int unk_A0;
    int unk_A4;
    s16 unk_A8;
    char pad_AA[2];
    int unk_AC;
    int unk_B0;
    char subA[0x20];
    char subD[0x20];
} UnkStruct_0221f47c;

extern int data_ov003_02236664[];
extern int data_021c9b24;
extern Data48 data_021fbe48;

extern int func_ov003_0221f5ac(UnkStruct_0221f47c *obj);
extern void *func_0203750c(void);
extern RetPtr *func_02037608(void *a, int b);
extern int func_02037594(void *a);
extern int func_02037588(void *a);
extern int func_0203757c(void *a);
extern int func_02055f40(UnkStruct_0221f47c *obj, void *field8, int tmp);
extern int func_0205650c(void *sub, void *field8, int global);
extern void func_02056478(void *sub, int a, int b, int c, int d);
extern int func_02055e00(UnkStruct_0221f47c *obj);
extern void func_020563dc(void *sub, int a);
extern int func_0203f8d0(void *buf, int *p9c);
extern void func_020e96c8(void *arr, int field_9c, int a, int b);
extern void func_020e9774(void *arr, int field_a8);

int func_ov003_0221f47c(UnkStruct_0221f47c *obj, int *src, int index)
{
    int localBuf[3];
    RetPtr *ptr;
    void *field8;
    int tmp;

    if (func_ov003_0221f5ac(obj) != 0) {
        return 0;
    }

    obj->unk_9C = src[0];
    obj->unk_A0 = src[1];
    obj->unk_A4 = src[2];

    ptr = func_02037608(func_0203750c(), data_ov003_02236664[index]);
    tmp = func_02037594(func_0203750c());
    field8 = ptr->unk_08;
    func_02055f40(obj, field8, tmp);

    if (func_0205650c(obj->subA, field8, data_021c9b24) != 0) {
        func_02056478(obj->subA, func_02037588(func_0203750c()), 0, 0x1000, 0);
        func_020563dc(obj->subA, func_02055e00(obj));
    }

    if (func_0205650c(obj->subD, field8, data_021c9b24) != 0) {
        func_02056478(obj->subD, func_0203757c(func_0203750c()), 0, 0x1000, 0);
        func_020563dc(obj->subD, func_02055e00(obj));
    }

    obj->unk_A8 = (s16) func_0203f8d0(localBuf, &obj->unk_9C);

    func_020e96c8(&data_021fbe48, obj->unk_9C, 0, 0);
    func_020e9774(&data_021fbe48, obj->unk_A8);

    obj->copyData = data_021fbe48;

    obj->unk_AC = src[0] >> 17;
    obj->unk_B0 = src[2] >> 17;

    return 1;
}
