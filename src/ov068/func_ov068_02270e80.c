/* func_ov068_02270e80 @ 0x02270e80, 0x1e8 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020961a8(int k);
extern void func_ov003_022353a4(void *self, int a, int b);
extern void func_ov003_02234cc4(void *self);
extern int func_020ea990(void *a, void *b);
extern int func_020644cc(int k);
extern int func_0200322c(void *a, void *b);
extern int FX_Div(int a, int b);
extern int func_020959ac(void);
extern void func_ov003_0223597c(int *out, int ang);
extern int FX_MulFunc(int a, int b);
extern void func_ov003_02234dac(void *self, int a, int b, int c);

void func_ov068_02270e80(char *self, short *p)
{
    int d1;
    unsigned int rnd;
    char *o;
    int v3[3];
    int *p204;
    short cnt;
    short d;
    short lim;
    short na;
    unsigned char *q;

    o = (char *) func_020961a8(4);
    p204 = (int *) (self + 0x204);
    d = 0;
    v3[0] = d;
    v3[1] = d;
    v3[2] = d;
    *p = *p + 0xaaa;
    func_ov003_022353a4(self, d, 1);
    func_ov003_02234cc4(self);
    if (o == 0) {
        goto done;
    }
    o = (char *) ((int) o + 0x5c);
    d1 = func_020ea990(o, p204);
    rnd = (unsigned char) func_020644cc(0x64);
    cnt = *(unsigned char *) (self + 0x254);
    d = *(short *) (self + 0x23a);
    d = func_0200322c(p204, o) - d;
    if (*(unsigned char *) (self + 0x24a) != 0) {
        if (cnt < 0xfe) {
            cnt = cnt + 1;
            *(unsigned char *) (self + 0x254) = cnt;
        }
        if (cnt >= 0x3c) {
            if (d1 < FX_Div(0x1000, 0x10000)) {
                if (func_020959ac() != 0) {
                    *(unsigned char *) (self + 0x24a) = 0;
                    *p = 0;
                    *(unsigned char *) (self + 0x251) = 9;
                }
            }
        }
    }
    if (d1 < 0x2000) {
        if (d1 < FX_Div(0x1000, 0x4000)) {
            if (*(unsigned char *) (self + 0x24a) == 0) {
                *(unsigned char *) (self + 0x24a) = 1;
                *(unsigned char *) (self + 0x254) = 0;
            }
        }
        if (d >= -0x555 && d <= 0x555) {
            goto done;
        }
        if (d > 0 && rnd > 0xf) {
            d = 0x555;
            goto done;
        }
        if (d < 0 && rnd > 0xf) {
            d = -0x555;
            goto done;
        }
        d = 0;
    } else {
        if (d1 > FX_Div(0x1000, 0x2000)) {
            if (*(unsigned char *) (self + 0x24a) != 0 && cnt < 0x3c) {
                *(unsigned char *) (self + 0x24a) = 0;
                *(unsigned char *) (self + 0x254) = 0;
            }
        }
        lim = FX_Div(0x555, 0x4000);
        if (d >= (short) -lim && d <= lim) {
            goto done;
        }
        if (d > 0 && rnd > 0x14) {
            d = lim;
            goto done;
        }
        if (d < 0 && rnd > 0x14) {
            d = (short) -lim;
            goto done;
        }
        d = 0;
    }
done:
    na = d + *(short *) (self + 0x23a);
    *(short *) (self + 0x23a) = na;
    func_ov003_0223597c(v3, na);
    p204[0] = p204[0] + FX_MulFunc(v3[0], 0x8000);
    p204[2] = p204[2] + FX_MulFunc(v3[2], 0x8000);
    func_ov003_02234dac(self, *p, 0x2800, (func_020644cc(8) + 0x12) << 12);
}
