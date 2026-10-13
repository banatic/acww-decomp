/* func_ov003_022269b0 @ 0x022269b0, 0x48 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

void func_ov003_022269b0(void *g, int *a, int *b, int *c, int *d, int *e, int *f)
{
    int *pa = a;
    int *pb = b;
    int *pc = c;
    int *pd = d;
    int *pe = e;
    int *pf = f;
    int i, j, k;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 6; j++) {
            pa[0] = 0;
            pb[0] = 0;
            pa++;
            pb++;
        }
    }
    for (k = 0; k < 3; k++) {
        pc[0] = 0;
        pd[0] = 0;
        pe[0] = 0;
        pf[0] = 0;
        pc++;
        pd++;
        pe++;
        pf++;
    }
}
