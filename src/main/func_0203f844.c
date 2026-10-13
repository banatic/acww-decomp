/* func_0203f844 @ 0x0203f844, 0x8c bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

extern unsigned char *data_021f6948;
extern int data_021c748c;
extern short FX_SinCosTable_[];
extern int FX_Div(int, int);
extern int FX_MulFunc(int, int);

struct Src {
    int a;
    int b;
    int c;
};

struct Dst {
    int a;
    int b;
    int c;
};

int func_0203f844(struct Dst *out, struct Src *in)
{
    int flag = (data_021f6948[4] == 1) ? 1 : 0;
    int base, r6, idx2;

    if (flag != 0) {
        base = in->b + 0x1f576;
        r6 = (int) (((unsigned) FX_Div(in->c, data_021c748c) * 0x2999) << 4) >> 16;
        out->a = in->a;
        idx2 = ((unsigned short) r6 >> 4) * 2;
        out->b = FX_MulFunc(base, FX_SinCosTable_[idx2 + 1]);
        out->c = FX_MulFunc(base, FX_SinCosTable_[idx2]);
        return r6;
    } else {
        out->a = in->a;
        out->b = in->b;
        out->c = in->c;
        return 0;
    }
}
