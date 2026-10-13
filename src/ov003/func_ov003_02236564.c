/* func_ov003_02236564 @ 0x02236564, 0xa4 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int *func_02095794(int a);
extern int func_0203affc(int *a, int *b, int *c, int *d, int *out);
extern int func_0203b0b8(int *a, int *b, int *c, int *out);
extern int FX_Div(int a, int b);
extern void func_0203c9b0(void *self, int a, int b, int t);

void func_ov003_02236564(char *self)
{
    int r;
    int v;
    int *k;
    int t;

    k = func_02095794(4);
    if (*(unsigned char *) (self + 0x1ca) != 0) {
        r = func_0203affc(k, (int *) (self + 0x1cc), (int *) (self + 0x1d8), (int *) (self + 0x110), &v);
    } else {
        r = func_0203b0b8(k, (int *) (self + 0x1cc), (int *) (self + 0x110), &v);
    }
    *(int *) (self + 0x118) += v;
    if (r < 0x4800) {
        r = 0x4800;
    } else if (r > 0xb000) {
        r = 0xb000;
    }
    t = FX_Div(r - 0x4800, 0x6800);
    *(int *) (self + 0x1e4) = 0x1000 - t;
    func_0203c9b0(self, 0xa, 0, t);
}
