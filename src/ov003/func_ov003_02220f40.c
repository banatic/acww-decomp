/* func_ov003_02220f40 @ 0x02220f40, 0x114 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O1,s
 */

extern int data_ov003_0223cfe4;

extern void *func_0204e414(void);
extern void func_0204f818(int *px, int *pz, void *p);
extern unsigned short *func_0204f5e0(void *ctx, int cx, int cz, int dx, int dz, int layer);
extern int func_ov003_0222139c(int *tbl, void *a, int *pos, int *w, int n, int id, int c, int k);

int func_ov003_02220f40(void *a, void *v, int c)
{
    int ret;
    int b4;
    int b3;
    int b2;
    int x;
    void *ctx;
    int cz;
    int b1;
    int z;
    int pos[2];
    unsigned short *o;
    unsigned int id;
    int cx;
    int w[3];

    ctx = func_0204e414();
    if (ctx == 0) {
        return 0;
    }
    x = 0;
    z = 0;
    func_0204f818(&x, &z, v);
    {
        int xx = x, zz = z;
        cx = xx >> 4;
        cz = zz >> 4;
        o = func_0204f5e0(ctx, cx, cz, xx - (cx << 4), zz - (cz << 4), 0);
    }
    ret = 0x2b;
    if (o != 0) {
        b4 = 1;
        b3 = b4;
        b2 = b4;
        b1 = 0;
        id = *o;
        if (id >= 0x2b && id <= 0x2e) {
            b1 = b4;
        }
        if (b1 == 0 && !(id >= 0xff && id <= 0x102)) {
            b2 = 0;
        }
        if (b2 == 0 && !(id >= 0x62 && id <= 0x65)) {
            b3 = 0;
        }
        if (b3 == 0 && !(id >= 0xd0 && id <= 0xd3)) {
            b4 = 0;
        }
        if (b4 != 0 || (id >= 0x26 && id <= 0x2a) || (id >= 0x5d && id <= 0x61) || (id >= 0x2f && id <= 0x56) ||
            (id >= 0x57 && id <= 0x5b) || (id >= 0x66 && id <= 0x68) || id == 0x69 || (id >= 0x6a && id <= 0x6c) ||
            id == 0x6d || (id >= 0xc8 && id <= 0xcf) || id == 0x25 || id == 0x5c || id == 0xc7) {
            ret = id;
        }
    }
    w[0] = 0;
    w[1] = 0;
    w[2] = 0;
    pos[0] = x;
    pos[1] = z;
    return func_ov003_0222139c(&data_ov003_0223cfe4, a, pos, w, 8, ret, c, 0);
}
