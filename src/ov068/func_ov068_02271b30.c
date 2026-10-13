/* func_ov068_02271b30 @ 0x02271b30, 0x128 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O2,s
 */

extern void *data_021c80bc;

extern void func_0204f818(int *px, int *pz, void *p);
extern unsigned short *func_0204f5e0(void *ctx, int cx, int cz, int dx, int dz, int layer);
extern void func_0204f794(void *p, int x, int z);
extern int func_0200322c(void *a, void *b);

int func_ov068_02271b30(char *self)
{
    int kind;
    unsigned char z0, x1, z1;
    char *p204;
    void *ctx;
    int x, z;
    char *p1e0;
    unsigned char i, j;
    int ci, cj;
    unsigned short *o;
    unsigned short v;
    int t1, t2, t3, t4;
    int s, r;

    p1e0 = self + 0x1e0;
    p204 = self + 0x204;
    kind = 0;
    x = 0;
    z = 0;
    ctx = data_021c80bc;
    func_0204f818(&x, &z, p204);
    t1 = x - 1;
    if (t1 < 0x10) {
        t1 = 0x10;
    }
    i = t1;
    t2 = z - 1;
    if (t2 < 0x10) {
        t2 = 0x10;
    }
    z0 = t2;
    t3 = x + 1;
    if (t3 > 0x50) {
        t3 = 0x50;
    }
    x1 = t3;
    t4 = z + 1;
    if (t4 > 0x50) {
        t4 = 0x50;
    }
    z1 = t4;
    for (; i <= x1; i++) {
        for (j = z0; j <= z1; j++) {
            ci = i >> 4;
            cj = j >> 4;
            o = func_0204f5e0(ctx, ci, cj, i - (ci << 4), j - (cj << 4), 0);
            if (o == 0) {
                continue;
            }
            v = *o;
            if (v == 0x500a) {
                kind = 1;
            } else if (v >= 0xe3 && v <= 0xe7) {
                kind = 2;
            }
            if (kind == 0) {
                continue;
            }
            func_0204f794(p1e0, i, j);
            if (kind == 1) {
                *(int *) (p1e0 + 8) = *(int *) (p1e0 + 8) + 0x59a;
            }
            *(int *) (self + 0x21c) = *(int *) (self + 0x21c) + 0x10;
            s = *(short *) (self + 0x23a);
            r = func_0200322c(p204, p1e0);
            *(unsigned short *) (self + 0x240) = r + s;
            *(unsigned char *) (self + 0x251) = 0xe;
            return 1;
        }
    }
    return 0;
}
