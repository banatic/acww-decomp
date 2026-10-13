/* func_ov003_02234dac @ 0x02234dac, 0x7c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    short lo, hi;
} UnkStruct_02234dac;
extern UnkStruct_02234dac FX_SinCosTable_[];
extern int FX_Div(int num, int den);

void func_ov003_02234dac(char *self, int a, int lim, int den)
{
    int *v = (int *) (self + 0x204);
    int idx = (unsigned short) a;
    int step = FX_Div(FX_SinCosTable_[idx >> 4].lo, den);
    if (*(int *) (self + 0x220) != *(int *) (self + 0x228)) {
        lim = FX_Div(lim, 0x2000);
    }
    if ((step > 0 && v[1] + step < lim + *(int *) (self + 0x220)) ||
        (step < 0 && v[1] + step > *(int *) (self + 0x220) - lim)) {
        v[1] += step;
    }
}
