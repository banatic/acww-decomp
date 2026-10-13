/* func_ov003_02226a88 @ 0x02226a88, 0x7c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *data_ov003_0223cf74;
extern int func_ov003_02227170(char *self, int i);
extern int func_ov003_02227154(char *self, int i, int k);
extern int func_020555a4(void *rec, int m, void *g2, int v, void *y, void *p, int q);

int func_ov003_02226a88(char *self, int *tbl, void **arr, void *y)
{
    int i;
    for (i = 0; i < 3; i++) {
        int k = func_ov003_02227170(self, i);
        int m = func_ov003_02227154(self, i, 5);
        int *e = tbl + k * 6;
        if (func_020555a4(self + 0x480 + i * 0x3a8, m, data_ov003_0223cf74, e[5], arr[i], y, 1) == 0) {
            return 0;
        }
    }
    return 1;
}
