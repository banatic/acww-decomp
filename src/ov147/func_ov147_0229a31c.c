/* func_ov147_0229a31c @ 0x0229a31c, 0x58 bytes, Thumb, module ov147
 * mwccarm 1.2/base -O4,s
 */

extern int _s32_div_f(int a, int b);
extern void G2x_SetBlendAlpha_(unsigned int a, unsigned int b, unsigned int c, int d, int e);
extern short FX_SinCosTable_[];

void func_ov147_0229a31c(void *self)
{
    int x;
    short v;
    int w;

    x = _s32_div_f(((unsigned int *) self)[4] << 12, 10);
    x = ((unsigned short) ((x << 18) >> 16)) >> 4;
    v = FX_SinCosTable_[x * 2];
    w = ((v << 4) + 0x800) >> 12;
    if (w < 0) {
        w = 0;
    } else if (w > 16) {
        w = 16;
    }
    G2x_SetBlendAlpha_(0x04000050, 8, 0x21, w, 16 - w);
}
