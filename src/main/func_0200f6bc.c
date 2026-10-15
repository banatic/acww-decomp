/* func_0200f6bc @ 0x0200f6bc, 0x8c bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

typedef struct {
    int m[9];
    int tx;
    int ty;
    int tz;
} Mtx43;

typedef struct {
    unsigned char pad_00[0x698];
    Mtx43 mat;
} BaseStruct;

extern int FX_MulFunc(int a, int b);
extern void MTX_MultVec43(int *in, Mtx43 *mat, int *out);
extern int func_0203f7d0(int a, int *v);

void func_0200f6bc(int arg0, BaseStruct *base, int *scale)
{
    Mtx43 mat, mat2;
    int tx, ty, tz;
    int in[3], out[3], res[3];
    int s0, s1, s2;

    mat = base->mat;
    tx = mat.tx;
    ty = mat.ty;
    tz = mat.tz;
    mat.tz = 0;
    mat.ty = 0;
    mat.tx = 0;
    mat2 = mat;
    in[0] = FX_MulFunc(0x800, *scale);
    in[1] = FX_MulFunc(0xfffffc00, *scale);
    in[2] = 0;
    MTX_MultVec43(in, &mat2, out);
    s0 = tx + out[0];
    s1 = ty + out[1];
    s2 = tz + out[2];
    res[0] = s0;
    res[1] = s1;
    res[2] = s2;
    func_0203f7d0(arg0, res);
}
