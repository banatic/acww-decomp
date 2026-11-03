/* town_ground_2: 9 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_0221f5ec @ 0x0221f5ec, 0x6 bytes, Thumb
 * func_ov003_0221f5e8 @ 0x0221f5e8, 0x4 bytes, Thumb
 * func_ov003_0221f5e0 @ 0x0221f5e0, 0x6 bytes, Thumb
 * func_ov003_0221f5d8 @ 0x0221f5d8, 0x6 bytes, Thumb
 * func_ov003_0221f5ac @ 0x0221f5ac, 0x2a bytes, Thumb
 * func_ov003_0221f47c @ 0x0221f47c, 0x130 bytes, Thumb
 * func_ov003_0221f444 @ 0x0221f444, 0x36 bytes, Thumb
 * func_ov003_0221f424 @ 0x0221f424, 0x20 bytes, Thumb
 * func_ov003_0221f3f0 @ 0x0221f3f0, 0x32 bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned char pad_00[172];
    unsigned long unk_AC;
} UnkStruct_0221f5e0;

typedef struct {
    unsigned char pad_00[176];
    unsigned long unk_B0;
} UnkStruct_0221f5d8;

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

struct UnkStruct_0221f444 {
    char pad_00[8];
    int value;
    char pad_0C[12];
    int *ptr;
    char pad_1C[4];
};

extern int data_ov003_02236664[];
extern int data_021c9b24;
extern Data48 data_021fbe48;
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
extern void func_02056ffc(void *ptr);
extern void func_02055e7c(int, int);
extern int func_02055f1c(int);

short func_ov003_0221f5ec(char *p)
{
    return *(short *) (p + 0xa8);
}

int func_ov003_0221f5e8(int p0)
{
    return ((int) (p0) + (156));
}

unsigned long func_ov003_0221f5e0(UnkStruct_0221f5e0 *p)
{
    return p->unk_AC;
}

unsigned long func_ov003_0221f5d8(UnkStruct_0221f5d8 *p)
{
    return p->unk_B0;
}

int func_ov003_0221f5ac(int arg)
{
    if ((int) func_ov003_0221f5e0((UnkStruct_0221f5e0 *) arg) != -1 && (int) func_ov003_0221f5d8((UnkStruct_0221f5d8 *) arg) != -1) {
        return 1;
    } else {
        return 0;
    }
}

int func_ov003_0221f47c(UnkStruct_0221f47c *obj, int *src, int index)
{
    int localBuf[3];
    RetPtr *ptr;
    void *field8;
    int tmp;

    if (func_ov003_0221f5ac((int) obj) != 0) {
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

int func_ov003_0221f444(void *arg)
{
    if (func_ov003_0221f5ac((int) arg)) {
        struct UnkStruct_0221f444 *p = (struct UnkStruct_0221f444 *) ((unsigned char *) arg + 0xb4);
        struct UnkStruct_0221f444 *end = (struct UnkStruct_0221f444 *) ((unsigned char *) arg + 0xf4);
        while (p < end) {
            func_02056ffc(p);
            *p->ptr = p->value;
            p++;
        }
        return 1;
    }
    return 0;
}

int func_ov003_0221f424(int param)
{
    int result;
    if (func_ov003_0221f5ac(param) != 0) {
        func_02055e7c(param, 0);
        result = 1;
    } else {
        result = 0;
    }
    return result;
}

int func_ov003_0221f3f0(int param)
{
    int r4;
    int r0;
    int r1;

    r4 = param;
    if (func_ov003_0221f5ac(param) != 0) {
        func_02055f1c(r4);
        r0 = 0;
        r1 = ~r0;
        r0 = r4 + 0xb0;
        *(int *) r0 = r1;
        r0 = r4 + 0xb0;
        r0 = *(int *) r0;
        r4 = r4 + 0xac;
        *(int *) r4 = r0;
        return 1;
    } else {
        return 0;
    }
}
