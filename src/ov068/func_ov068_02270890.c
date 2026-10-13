/* func_ov068_02270890 @ 0x02270890, 0x1d4 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020961a8(int k);
extern int func_0200322c(void *a, void *b);
extern void func_020e8870(short *v, int ang, int k);
extern void func_ov003_0223597c(int *out, int ang);
extern int FX_MulFunc(int a, int b);
extern int FX_Div(int a, int b);
extern void func_ov068_02270a64(void *a, void *b, int d);
extern int func_ov003_022198b0(void);
extern void func_ov003_022353a4(void *self, int a, int b);
extern int func_ov003_02232598(void *self, int k);
extern void func_02044528(void);
extern int func_0209d088(void *p);
extern void NNS_G3dMdlSetMdlAlpha(void *m, int a, int b);

void func_ov068_02270890(char *self)
{
    int st;
    short tmp;
    int v3[3];
    int w[3];
    short *p242;
    int *p210;
    int *p204;
    char *o;
    int oldang;
    int t;
    int *q;

    p242 = (short *) (self + 0x242);
    p210 = (int *) (self + 0x210);
    p204 = (int *) (self + 0x204);
    st = *(unsigned char *) (self + 0x251);
    if (st == 3) {
        o = (char *) func_020961a8(4);
        if (o != 0) {
            oldang = *(short *) (self + 0x23a);
            tmp = oldang;
            func_020e8870(&tmp, func_0200322c(p204, o + 0x5c), 0x1554);
            *(short *) (self + 0x23a) = tmp;
            func_ov003_0223597c(v3, tmp);
            p204[0] = p204[0] + FX_MulFunc(0x23000, v3[0]);
            p204[2] = p204[2] + FX_MulFunc(0x23000, v3[2]);
            func_ov068_02270a64((int *) (self + 0x210), self + 0x50, oldang - tmp);
        }
        t = *p242;
        if (t == 0) {
            if (func_ov003_022198b0() != 0) {
                func_ov003_022353a4(self, 1, 0);
                *p242 = *p242 + 1;
            } else {
                func_ov003_022353a4(self, 0, 1);
            }
            return;
        }
        *p242 = t + 1;
        if (*p242 > 0x42) {
            *(unsigned char *) (self + 0x251) = 7;
            *p242 = 0;
        }
        return;
    }
    func_ov003_0223597c(w, *(short *) (self + 0x23a));
    if (st == 7) {
        p204[0] = p204[0] + FX_MulFunc(w[0], 0x64000);
        p204[2] = p204[2] + FX_MulFunc(w[2], 0x64000);
        p210[0] = p210[0] + 0x266;
        p210[1] = p210[1] + 0x266;
        p210[2] = p210[2] + 0x266;
        func_ov068_02270a64(p210, self + 0x50, 0);
    } else {
        p204[0] = p204[0] + FX_Div(FX_MulFunc(w[0], *(int *) (self + 0x21c) << 12), 0x5000);
        p204[2] = p204[2] + FX_Div(FX_MulFunc(w[2], *(int *) (self + 0x21c) << 12), 0x5000);
        p210[0] = p210[0] + 0x333;
        p210[1] = p210[1] + 0x333;
        p210[2] = p210[2] + 0x333;
    }
    if (func_ov003_02232598(self, 4) != 0) {
        *(unsigned char *) (self + 0x251) = 0x13;
        *(unsigned char *) (self + 0x249) = 0;
        q = (int *) (self + 0x204);
        q[0] = 0;
        q[1] = 0;
        q[2] = 0;
        *(int *) (self + 0x21c) = 0;
        func_02044528();
        NNS_G3dMdlSetMdlAlpha((void *) func_0209d088(self + 0x130), 0, 0);
    }
}
