/* func_0207edcc @ 0x0207edcc, 0xa4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#pragma opt_loop_invariants off

extern unsigned char data_020e54a8;
extern void *data_021c80bc;

extern void *func_02095794(int k);
extern void func_0204f818(int *px, int *pz, void *obj);
extern unsigned short *func_0204f5e0(void *ctx, int cx, int cz, int dx, int dz, int layer);

int func_0207edcc(void)
{
    void *obj;
    void *ctx;
    unsigned short *o;
    unsigned int ok;
    int ok2;
    int count;
    int x;
    int z;
    int i;
    int j;
    int cx;
    int cz;

    obj = func_02095794(4);
    ok = (data_020e54a8 != 0) ? 0 : 1;
    if (ok == 0) {
        goto ret0;
    }
    if (obj == 0) {
        goto ret0;
    }
    ctx = data_021c80bc;
    if (ctx == 0) {
        goto ret0;
    }
    count = 0;
    x = 0;
    z = 0;
    func_0204f818(&x, &z, obj);
    for (j = z - 1; j <= z + 1; j++) {
        for (i = x - 1; i <= x + 1; i++) {
            cx = i >> 4;
            cz = j >> 4;
            o = func_0204f5e0(ctx, cx, cz, i - (cx << 4), j - (cz << 4), 0);
            if (o == 0) {
                continue;
            }
            ok2 = 0;
            if (*o >= 0x21 && *o <= 0x24) {
                ok2 = 1;
            }
            if (ok2 == 0) {
                continue;
            }
            count++;
            if (count >= 3) {
                return 1;
            }
        }
    }
ret0:
    return 0;
}
