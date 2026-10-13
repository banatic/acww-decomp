/* func_ov003_022191c0 @ 0x022191c0, 0x278 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int m[9];
    int tx, ty, tz;
} Mtx43;
typedef struct {
    int x, y, z;
} Vec3;

typedef struct {
    volatile unsigned short a;
    short b, c, d;
} Id;

extern void func_0200faf0(void *self, int k);
extern int _s32_div_f(int a, int b);
extern void func_ov003_02219668(Mtx43 *m, Vec3 *v);
extern void func_0203f7d0(Vec3 *a, Vec3 *b);
extern void func_02091278(int h, Vec3 *v, int a, int b);
extern int func_0209120c(int k, Vec3 *v, int a, int b);
extern void func_ov003_0222d83c(int a, unsigned short *p, Mtx43 *m, int c);
extern void func_ov003_0222aaa0(Vec3 *v, int k);
extern int FX_MulFunc(int a, int b);
extern void func_0204fdec(int h, int k, Vec3 *w, Vec3 *v, int a, int b, int c, int d, int e, int f);

void func_ov003_022191c0(char *self)
{
    Id id;
    Mtx43 m;
    Vec3 v;
    Vec3 w;
    Vec3 vv;
    char *p7d4;
    int *p7d8;
    int t;
    int q;
    int ok;
    unsigned short lo, hi;
    int k;
    short s;
    int d8;
    float f;
    int fx;

    p7d4 = self + 0x7d4;
    id.a = *(unsigned short *) p7d4;
    p7d8 = (int *) (p7d4 + 4);
    func_0200faf0(self, 0x400);
    m = *(Mtx43 *) (self + 0x698);
    v.x = 0x4cd;
    v.y = 0;
    v.z = 0;
    t = (int) ((unsigned int) (*(int *) (self + 0x2d8) << 4) >> 16);
    if (*(int *) (self + 0x704) != 0xa0 && t >= 0x10) {
        q = _s32_div_f(0x19a * (t - 0xf), 0xc);
        v.x = v.x + q * 2;
        v.y = v.y + q;
        v.z = v.z - q;
    }
    func_ov003_02219668(&m, &v);
    d8 = *p7d8;
    ok = 0;
    if (d8 > -1) {
        w.x = m.tx;
        w.y = m.ty;
        w.z = m.tz;
        func_0203f7d0(&w, &w);
        func_02091278(*p7d8, &w, 0, 0);
    } else if (d8 == -1) {
        *p7d8 = -2;
        if (*(unsigned char *) (p7d4 + 0xc) == 0) {
            lo = id.a;
            hi = id.a;
            if (hi >= 0x12b0 && lo <= 0x12e7) {
                ok = 1;
            }
            if (ok != 0) {
                k = lo - 0x12b0;
            } else {
                k = -1;
            }
            if (k == 0x18 || k == 0x30 || k == 0x32 || k == 0x33) {
                w.x = m.tx;
                w.y = m.ty;
                w.z = m.tz;
                func_0203f7d0(&w, &w);
                *p7d8 = func_0209120c(0x5a, &w, 0, 0);
            }
        }
    }
    if (*(int *) (self + 0x704) != 0xa0) {
        if (t <= 0xa) {
            s = 0;
        } else if (t < 0x10) {
            s = 0x11 * (t - 0xa);
        } else {
            s = 0x64;
        }
    } else {
        if (t < 6) {
            s = 0x64 - 0x11 * t;
        } else {
            s = 0;
        }
    }
    if (*(unsigned char *) (p7d4 + 0xc) == 0) {
        id.b = s;
        id.c = s;
        id.d = s;
        func_ov003_0222d83c((unsigned char) *(int *) (self + 0x800), (unsigned short *) &id.b, &m, 0);
        return;
    }
    f = s / 100.0f;
    fx = (int) (f > 0.0f ? 0.5f + 4096.0f * f : 4096.0f * f - 0.5f);
    ok = 0;
    lo = id.a;
    hi = id.a;
    if (hi >= 0x12e8 && lo <= 0x131f) {
        ok = 1;
    }
    if (ok != 0) {
        k = lo - 0x12e8;
    } else {
        k = -1;
    }
    func_ov003_0222aaa0(&vv, k);
    vv.x = FX_MulFunc(vv.x, fx);
    vv.y = FX_MulFunc(vv.y, fx);
    vv.z = FX_MulFunc(vv.z, fx);
    w.x = m.tx;
    w.y = m.ty;
    w.z = m.tz;
    func_0203f7d0(&w, &w);
    ok = 0;
    lo = id.a;
    hi = id.a;
    if (hi >= 0x12e8 && lo <= 0x131f) {
        ok = 1;
    }
    if (ok != 0) {
        k = lo - 0x12e8;
    } else {
        k = -1;
    }
    func_0204fdec(*(int *) (p7d4 + 8), k, &w, &vv, 0, 0, 0, 1, 1, 0x1f);
}
