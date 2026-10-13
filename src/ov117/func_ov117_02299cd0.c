/* func_ov117_02299cd0 @ 0x02299cd0, 0xcc bytes, Thumb, module ov117
 * mwccarm 1.2/base -O1,s
 */

extern void *func_0204e414(void);
extern int func_0204f3e4(void *ctx, int *pa, int *pb, int *pc, int *pd, unsigned short *ida, unsigned short *idb, int n,
                         int k);
extern void func_0204f800(int *px, int *pz, int cx, int cz, int dx, int dz);
extern unsigned short *func_0204f5e0(void *ctx, int cx, int cz, int dx, int dz, int layer);
extern void *func_020b3b50(unsigned short *o);
extern void func_020b3c58(void *h, int *p, int *q, int *r, int *w);
extern void func_ov117_0229a2a4(void *a0, int k, int x, int z, int m);

void func_ov117_02299cd0(void *a0)
{
    void *ctx;
    unsigned short *o;
    void *h;
    unsigned short ida;
    unsigned short idb;
    int x;
    int z;
    int a;
    int b;
    int c;
    int d;
    int p;
    int q;
    int r;
    int w;
    int cx;
    int cz;

    ctx = func_0204e414();
    if (ctx == 0) {
        return;
    }
    ida = 0x500d;
    idb = 0x5010;
    if (func_0204f3e4(ctx, &a, &b, &c, &d, &ida, &idb, 2, 0) == 0) {
        return;
    }
    func_0204f800(&x, &z, a, b, c, d);
    {
        int xx = x, zz = z;
        cx = xx >> 4;
        cz = zz >> 4;
        o = func_0204f5e0(ctx, cx, cz, xx - (cx << 4), zz - (cz << 4), 0);
    }
    x *= 2;
    z *= 2;
    x += 1;
    z += 1;
    h = func_020b3b50(o);
    if (h != 0) {
        func_020b3c58(h, &p, &q, &r, &w);
        x += p >> 11;
        z += q >> 11;
    }
    func_ov117_0229a2a4(a0, 0xe, x, z, 0);
}
