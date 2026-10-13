/* func_ov003_022348dc @ 0x022348dc, 0xa8 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;
extern void func_ov003_0223597c(void *a, int b);
extern int func_ov003_02232598(void *a, int b);
extern void func_ov003_02230f60(void *a);
extern int FX_MulFunc(int a, int b);
extern int FX_Div(int num, int den);
extern int func_ov003_02235b54(void *a, int b, int c);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *c);

void func_ov003_022348dc(char *self, int t)
{
    Vec3 *v = (Vec3 *) (self + 0x204);
    short *p = (short *) (self + 0x242);
    Vec3 d;
    int n;
    int x;
    func_ov003_0223597c(&d, *(short *) (self + 0x23a));
    if (func_ov003_02232598(self, 1)) {
        func_ov003_02230f60(self);
    }
    n = *p;
    x = FX_MulFunc(t, (0x44 * n) << 12);
    x >>= FX_Div((n * n) << 12, 0x1000) + 0xc;
    d.y = x;
    if (func_ov003_02235b54(self, 0x50, 0xe38) == 0) {
        d.x = FX_MulFunc(d.x, 0x10000);
        d.z = FX_MulFunc(d.z, 0x10000);
    }
    *p = (short) (*p + 1);
    VEC_Add(v, &d, v);
}
