/* func_ov003_022262d8 @ 0x022262d8, 0xdc bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *data_ov003_0223cf70;
extern int func_ov003_022265ec(void *s, void **a, void **b);
extern int func_ov003_022265d4(void *s, void **a, void **b);
extern int func_ov003_02226544(void *s, void **a, void **b);
extern int func_ov003_0222652c(void *s, void **a, void **b);
extern int func_ov003_02226514(void *s, void **a, void **b);
extern int func_ov003_02226490(void *s, void **a, void **b);
extern void func_ov003_022263b4(void *s, void **a, void **b, void **c, void **d);
extern int func_ov003_02226438(void *s);

int func_ov003_022262d8(void)
{
    void *a[2];
    void *b[2];
    void *c[2];
    void *d[2];
    void *e[4];
    void *f[4];
    void *g[4];
    void *h[4];
    int ok1;
    int ok2;
    int i;
    int j;
    int r;
    ok1 = 0;
    ok2 = 0;
    for (i = 0; i < 4; i++) {
        e[i] = 0;
        f[i] = 0;
        g[i] = 0;
        h[i] = 0;
    }
    for (j = 0; j < 2; j++) {
        a[j] = 0;
        b[j] = 0;
        c[j] = 0;
        d[j] = 0;
    }
    if (func_ov003_022265ec(data_ov003_0223cf70, e, f) && func_ov003_022265d4(data_ov003_0223cf70, g, h) &&
        func_ov003_02226544(data_ov003_0223cf70, e, g)) {
        ok1 = 1;
    }
    if (func_ov003_0222652c(data_ov003_0223cf70, a, b) && func_ov003_02226514(data_ov003_0223cf70, c, d) &&
        func_ov003_02226490(data_ov003_0223cf70, a, c)) {
        ok2 = 1;
    }
    func_ov003_022263b4(data_ov003_0223cf70, f, h, b, d);
    r = func_ov003_02226438(data_ov003_0223cf70);
    if (ok1 && ok2 && r) {
        return 1;
    }
    return 0;
}
