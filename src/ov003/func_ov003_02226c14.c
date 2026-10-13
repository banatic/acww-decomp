/* func_ov003_02226c14 @ 0x02226c14, 0xb0 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *data_ov003_0223cf74;
extern int func_ov003_02227118(char *self, int i);
extern int func_ov003_022270f8(char *self, int i);
extern int func_020555a4(void *rec, int m, void *g2, int v, void *y, void *p, int q);

int func_ov003_02226c14(char *self, int *tbl, void **c, void *y)
{
    int i;
    for (i = 1; i <= 4; i++) {
        int m = func_ov003_02227118(self, i);
        if (func_020555a4(self + 0xc6c + i * 0x9c, m, data_ov003_0223cf74, tbl[i], *c, y, 2) == 0) {
            return 0;
        }
    }
    for (i = 0; i < 4; i++) {
        int m = func_ov003_022270f8(self, i);
        char *g = self + 0x5ab0 + i * 0x14c;
        int *e = tbl + i;
        if (func_020555a4(g + 8, m, data_ov003_0223cf74, e[1], *c, y, 2) == 0) {
            return 0;
        }
    }
    return 1;
}
