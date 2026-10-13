/* func_ov004_022136f8 @ 0x022136f8, 0xd0 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int m[9];
} Mtx33;

extern int FX_Div(int a, int b);
extern int FX_MulFunc(int a, int b);
extern void *func_ov004_0220fdec(void *self);
extern int func_ov004_0220d4b4(void *p);
extern void MTX_RotY33_(Mtx33 *m, int s, int c);
extern void MTX_Concat33(Mtx33 *dst, Mtx33 *a, Mtx33 *b);
extern short FX_SinCosTable_[];

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
        MTX_RotY33_(&m, FX_SinCosTable_[j], FX_SinCosTable_[j + 1]);
        if ((**(int **) (arg2 + 0xb4) & 2) != 0) {
            *dst = m;
        } else {
            MTX_Concat33(dst, &m, dst);
        }
        **(int **) (arg2 + 0xb4) = **(int **) (arg2 + 0xb4) & ~2;
    }
}
