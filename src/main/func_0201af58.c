/* func_0201af58 @ 0x0201af58, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int FX_MulFunc(int, int);
extern const short FX_SinCosTable_[];

void func_0201af58(int *out, int *in1, int *in2, int angle)
{
    int t = (unsigned short) angle >> 4;
    int sin = FX_SinCosTable_[t * 2];
    int cos = FX_SinCosTable_[t * 2 + 1];

    out[0] = in1[0] + FX_MulFunc(in2[0], cos) + FX_MulFunc(in2[2], sin);
    out[1] = 0;
    out[2] = in1[2] - FX_MulFunc(in2[0], sin) + FX_MulFunc(in2[2], cos);
}
