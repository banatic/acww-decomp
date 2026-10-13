/* func_ov003_02213f74 @ 0x02213f74, 0x134 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *data_021c80bc;
extern short FX_SinCosTable_[];
extern unsigned short *func_0204f5a8(void *ctx, void *p, int k);
extern int func_020e8ed8(int dx, int dz);
extern int func_020e8b4c(int a, int b);
extern int FX_MulFunc(int a, short b);

int func_ov003_02213f74(char *self, int *a, int *b, unsigned char *flag)
{
    int *p;
    volatile int pos[3];
    unsigned short *o;
    unsigned short v;
    int a1, a2;
    int bz, pz;
    int dx, dz;
    int d;
    short c;
    int t;

    p = (int *) (self + 0x5c);
    pos[0] = p[0];
    pos[1] = p[1];
    pos[2] = p[2];
    o = func_0204f5a8(data_021c80bc, a, 0);
    if (o != 0) {
        v = *o;
        if (v == 0x1b || v == 0x89) {
            return 1;
        }
    }
    if (*flag == 0) {
        a1 = func_020e8ed8(b[0] - pos[0], b[2] - pos[2]);
        a2 = func_020e8ed8(a[0] - pos[0], a[2] - pos[2]);
        a1 = (short) func_020e8b4c(a1, 0);
        a2 = (short) func_020e8b4c(a2, 0);
        if (a1 == a2) {
            bz = b[2];
            pz = pos[2];
            if ((pz >= bz && bz > a[2]) || (pz <= bz && bz < a[2])) {
                return 1;
            }
            return 0;
        }
        if ((a1 >= 0x4000 && a2 > a1) || (a2 < 0x4000 && a2 <= a1)) {
            return 1;
        }
        dx = a[0] - pos[0];
        dz = a[2] - pos[2];
        d = dx * dx + dz * dz;
        c = FX_SinCosTable_[((unsigned short) (short) (a1 - a2) >> 4) * 2 + 1];
        t = FX_MulFunc(d, c);
        t = FX_MulFunc(t, c);
        if (d - t < 0x900000) {
            return 0;
        }
        return 1;
    }
    bz = b[2];
    pz = pos[2];
    if ((pz >= bz && bz > a[2]) || (pz <= bz && bz < a[2])) {
        return 1;
    }
    return 0;
}
