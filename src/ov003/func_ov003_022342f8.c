/* func_ov003_022342f8 @ 0x022342f8, 0xb0 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int FX_MulFunc(int a, int b);
extern int FX_Div(int a, int b);
extern int func_ov003_02235b54(void *a, int b, int c);
extern void func_ov003_0223597c(int *v, int a);
extern int func_ov003_02232598(void *a, int b);
extern void func_ov003_02230f60(void *a);

void func_ov003_022342f8(char *self, short *out)
{
    int t;
    int v[3];
    int *p;
    int m;

    p = (int *) (self + 0x204);
    if (*(unsigned char *) (self + 0x251) == 0xb) {
        if (func_ov003_02235b54(self, 0x50, 0xe38) == 0) {
            func_ov003_0223597c(v, *(short *) (self + 0x23a));
            p[0] += FX_MulFunc(v[0], 0x10000);
            p[2] += FX_MulFunc(v[2], 0x10000);
        }
    }
    t = *out << 12;
    m = FX_MulFunc(0x44000, t);
    p[1] += (m >> 12) + (FX_Div(FX_MulFunc(t, t), 0x2000) >> 12);
    *out = *out + 1;
    if (func_ov003_02232598(self, 1) != 0) {
        func_ov003_02230f60(self);
    }
}
