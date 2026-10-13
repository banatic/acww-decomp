/* func_0204811c @ 0x0204811c, 0x84 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

/* FAKEMATCH: the redundant mask and the empty if keep the z load before the x shift; the plain copies shift x first */

extern void *func_0204e414(void);
extern void func_0204f818(int *px, int *pz, void *p);
extern unsigned short *func_0204f5e0(void *ctx, int cx, int cz, int dx, int dz, int layer);
extern int func_02045d80(int *arr, int k);
extern void func_0204a25c(void *ctx, int x, int z, int k, int m);
void func_0204811c(int a0, void *p1)
{
    void *ctx;
    unsigned short *o;
    int x;
    int z;
    int arr[2];
    int vx;
    int vz;
    int cx;
    int cz;
    int ok;
    ctx = func_0204e414();
    if ((ctx == 0)) {
        return;
    }
    x = 0;
    z = 0;
    func_0204f818(&x, &z, p1);
    vx = x;
    vz = z;
    cx = vx >> 4;
    if ((z && z) && z) {
    }
    cz = vz >> 4;
    o = func_0204f5e0(ctx, cx, cz, vx - (cx << 4), vz - (cz << 4), 0);
    if (o == 0) {
        return;
    }
    ok = 0;
    if (((*o) >= 0xfc) && ((*o) <= 0xfd)) {
        ok = 1;
    }
    if (ok == 0) {
        return;
    }
    arr[0] = x;
    arr[1] = z;
    if (func_02045d80(arr, 0) >= 0) {
        return;
    }
    func_0204a25c(ctx, x, z, 0xfff1, 0);
}
