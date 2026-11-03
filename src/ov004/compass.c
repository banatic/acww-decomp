/* compass: 10 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02213968 @ 0x02213968, 0x1c bytes, Thumb
 * func_ov004_02213938 @ 0x02213938, 0x30 bytes, Thumb
 * func_ov004_02213914 @ 0x02213914, 0x24 bytes, Thumb
 * func_ov004_022138e8 @ 0x022138e8, 0x2c bytes, Thumb
 * func_ov004_022138c0 @ 0x022138c0, 0x28 bytes, Thumb
 * func_ov004_02213860 @ 0x02213860, 0x60 bytes, Thumb
 * func_ov004_0221385c @ 0x0221385c, 0x4 bytes, Thumb
 * func_ov004_02213850 @ 0x02213850, 0xc bytes, Thumb
 * func_ov004_022137c8 @ 0x022137c8, 0x88 bytes, Thumb
 * func_ov004_022136f8 @ 0x022136f8, 0xd0 bytes, Thumb
 */

#include "types.h"

typedef struct {
    int *unk_00;
    char pad_04[0xe8];
    int *unk_EC;
} UnkStruct_02213914;

typedef struct {
    unsigned int unk_00;
    unsigned char pad_04[0xe8];
    unsigned int unk_EC;
} UnkStruct_022138e8;

typedef struct {
    int m[9];
} Mtx33;

extern int func_ov004_0221152c(unsigned int size);
extern void *func_ov004_022110e4(char *argument0);
extern void *data_ov004_02251c6c;
extern void *data_ov004_02251d18;
extern void *func_ov004_02210cf0(void *);
extern void func_ov004_02211518(void *self);
extern char data_ov004_022531c0[];
extern short func_0205790c(int a, char *b);
extern int func_020e895c(void *p, int a, int b);
extern int FX_MulFunc(int a, int b);
extern s16 FX_SinCosTable_[];
extern int FX_Div(int a, int b);
extern void *func_ov004_0220fdec(void *self);
extern int func_ov004_0220d4b4(void *p);
extern void MTX_RotY33_(Mtx33 *m, int s, int c);
extern void MTX_Concat33(Mtx33 *dst, Mtx33 *a, Mtx33 *b);

void *func_ov004_02213938(char *self);

void func_ov004_02213968(void)
{
    char *conditionInput0;

    if ((conditionInput0 = (char *) (func_ov004_0221152c(0x854)))) {
        func_ov004_02213938((char *) conditionInput0);
    }
}

void *func_ov004_02213938(char *self)
{
    func_ov004_022110e4(self);
    *(void **) (self) = &data_ov004_02251c6c;
    *(void **) (self + 0xec) = &data_ov004_02251d18;
    *(short *) (self + 0x844) = -1;
    return self;
}

void *func_ov004_02213914(UnkStruct_02213914 *obj)
{
    obj->unk_00 = ((int *) &data_ov004_02251c6c);
    obj->unk_EC = ((int *) &data_ov004_02251d18);
    func_ov004_02210cf0(obj);
    return obj;
}

UnkStruct_022138e8 *func_ov004_022138e8(UnkStruct_022138e8 *self)
{
    self->unk_00 = (unsigned int) ((unsigned int *) &data_ov004_02251c6c);
    self->unk_EC = (unsigned int) ((unsigned int *) &data_ov004_02251d18);
    func_ov004_02210cf0(self);
    func_ov004_02211518(self);
    return self;
}

int func_ov004_022138c0(char *self)
{
    *(short *) (self + 0x844) = func_0205790c(*(int *) (self + 0x594), data_ov004_022531c0);
    return 1;
}

int func_ov004_02213860(char *self)
{
    func_020e895c(self + 0x84c, 0, 0x5a00);
    if (*(int *) (self + 0x84c) == 0) {
        *(s16 *) (self + 0x848) = 0;
    } else {
        *(s16 *) (self + 0x848) = (s16) (*(s16 *) (self + 0x848) + 0x960);
    }
    func_020e895c(self + 0x850, FX_MulFunc(*(int *) (self + 0x84c), (s16) (*(s16 *) (self + 0x848))), 0x5a00);
    return 1;
}

int func_ov004_0221385c(void)
{
    return 1;
}

void *func_ov004_02213850(char *self)
{
    // DECLS
    // ENDDECLS
    *(u16 *) (self + 0x846) = 0x0;
    return self;
}

void func_ov004_022137c8(char *self, int flag)
{
    *(s16 *) (self + 0x846) = (s16) (*(s16 *) (self + 0x846) + 1);
    if (*(s16 *) (self + 0x846) == 8) {
        *(u16 *) (self + 0x848) = 0;
        if (flag != 0) {
            *(int *) (self + 0x84c) =
                FX_MulFunc(*(int *) (self + 0x84c), FX_SinCosTable_[(*(u16 *) (self + 0x848) >> 4) * 2]) + 0x2d000;
            if (*(int *) (self + 0x84c) > 0x2d000) {
                *(int *) (self + 0x84c) = 0x2d000;
            }
        } else {
            *(int *) (self + 0x84c) =
                FX_MulFunc(*(int *) (self + 0x84c), FX_SinCosTable_[(*(u16 *) (self + 0x848) >> 4) * 2]) - 0x2d000;
            if (*(int *) (self + 0x84c) < -0x2d000) {
                *(int *) (self + 0x84c) = -0x2d000;
            }
        }
    }
}

void func_ov004_022136f8(char *self, int k, char *arg2)
{
    Mtx33 m;
    Mtx33 *dst;
    void *p;
    int a;
    int t;
    int j;
    short v;

    if (*(short *) (self + 0x844) == k) {
        dst = (Mtx33 *) (*(char **) (arg2 + 0xb4) + 0x28);
        a = FX_MulFunc(FX_Div(*(int *) (self + 0x850), 0x168000), 0x10000000) << 4 >> 16;
        p = func_ov004_0220fdec(self);
        if (p != 0) {
            t = *(short *) ((char *) p + 0x8e);
            v = (short) (a - (t + func_ov004_0220d4b4(self + 0x17c)));
        } else {
            v = (short) (a - *(short *) (self + 0x8e));
        }
        j = ((u16) v >> 4) * 2;
        MTX_RotY33_(&m, ((short *) FX_SinCosTable_)[j], ((short *) FX_SinCosTable_)[j + 1]);
        if ((**(int **) (arg2 + 0xb4) & 2) != 0) {
            *dst = m;
        } else {
            MTX_Concat33(dst, &m, dst);
        }
        **(int **) (arg2 + 0xb4) = **(int **) (arg2 + 0xb4) & ~2;
    }
}
