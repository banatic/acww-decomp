/* func_0200fa1c @ 0x0200fa1c, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int FX_MulFunc(int a, int b);
extern short FX_SinCosTable_[];

struct ThreeInts {
    int a;
    int b;
    int c;
};

void func_0200fa1c(struct ThreeInts *out, int unused, struct ThreeInts *in, unsigned short *p, int *q)
{
    int v;
    int t;
    int r1, r2;

    out->a = in->a;
    out->b = in->b;
    out->c = in->c;
    v = (*p) >> 4;
    t = 2 * v;
    r1 = FX_MulFunc(FX_SinCosTable_[t + 1], *q);
    r2 = FX_MulFunc(FX_SinCosTable_[t], *q);
    out->a += r2;
    out->c += r1;
}
