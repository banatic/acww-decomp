/* func_0200850c @ 0x0200850c, 0xc0 bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

typedef struct {
    int m[12];
} MtxFx43;

extern void MTX_MultVec43(int *vec, MtxFx43 *m, int *out);
extern void func_0203f7d0(void *obj, int *out);
extern int FX_Div(int numer, int denom);

typedef struct {
    unsigned char pad_00[0x698];
    MtxFx43 mat;
    unsigned char pad_6C8[0x3c];
    int flag;
} UnkStruct_0200850c;

void func_0200850c(void *obj, UnkStruct_0200850c *src, int a)
{
    int saved0, saved1, saved2;
    MtxFx43 mtx1, mtx2;
    int vec[3], output[3], result[3];

    mtx1 = src->mat;

    saved0 = mtx1.m[9];
    saved1 = mtx1.m[10];
    saved2 = mtx1.m[11];

    mtx1.m[11] = 0;
    mtx1.m[10] = 0;
    mtx1.m[9] = 0;

    mtx2 = mtx1;

    vec[0] = 0x320;
    vec[2] = 0;

    if (src->flag == 0x7e) {
        if (a <= 10) {
            vec[1] = 0;
        } else {
            vec[1] = -0xa00;
        }
    } else {
        a *= 0x5000;
        vec[1] = -((0xa000 - FX_Div(a, 0x15000)) >> 4);
    }

    MTX_MultVec43(vec, &mtx2, output);

    {
        int sum0 = saved0 + output[0];
        int sum1 = saved1 + output[1];
        int sum2 = saved2 + output[2];
        result[0] = sum0;
        result[1] = sum1;
        result[2] = sum2;
    }

    func_0203f7d0(obj, result);
}
