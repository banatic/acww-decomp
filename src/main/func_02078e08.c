/* func_02078e08 @ 0x02078e08, 0x90 bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

extern void *data_021c80bc;

extern unsigned short *func_0204f5e0(void *ctx, int cx, int cz, int dx, int dz, int layer);

int func_02078e08(int x, int z0, int n, int *pOutX, int *pOutZ)
{
    void *ctx;
    unsigned short *o;
    int i;
    int z;
    int cx;
    int cz;
    int ok;
    int layer;
    int ok0;

    ctx = data_021c80bc;
    if (ctx == 0) {
        goto ret0;
    }
    if (n < 0) {
        goto ret0;
    }
    i = 0;
    ok0 = 0;
    layer = 0;
    for (; i <= n; i++) {
        z = z0 - (i + 1);
        cx = x >> 4;
        cz = z >> 4;
        o = func_0204f5e0(ctx, cx, cz, x - (cx << 4), z - (cz << 4), layer);
        if (o != 0) {
            ok = ok0;
            if (*o >= 0x5000 && *o <= 0x5021) {
                ok = 1;
            }
            if (ok != 0) {
                if (pOutX != 0 && pOutZ != 0) {
                    *pOutX = x;
                    *pOutZ = z0 - (i + 1);
                }
                return 1;
            }
        }
    }
ret0:
    return 0;
}
