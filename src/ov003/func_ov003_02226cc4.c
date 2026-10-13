/* func_ov003_02226cc4 @ 0x02226cc4, 0x124 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *data_ov003_0223cf74;
extern int func_ov003_02227170(char *self, int i);
extern int func_ov003_02227154(char *self, int i, int j);
extern int func_ov003_02227138(char *self, int i, int j);
extern int func_020555a4(void *rec, int m, void *g2, int v, void *y, void *p, int q);

int func_ov003_02226cc4(char *self, int *tbl, void **arr, void *y)
{
    int i;
    int j;
    char *g;
    void **q2;
    int *row2;
    void **q;
    int *row;
    char *base;
    for (i = 0; i < 3; i++) {
        int k = func_ov003_02227170(self, i);
        j = 1;
        q = arr + i;
        row = tbl + k * 6;
        base = self + 0x174 + i * 0x3a8;
        while (j <= 4) {
            int m = func_ov003_02227154(self, i, j);
            if (func_020555a4(base + j * 0x9c, m, data_ov003_0223cf74, row[j], *q, y, 2) == 0) {
                return 0;
            }
            j++;
        }
    }
    for (i = 0; i < 3; i++) {
        int k = func_ov003_02227170(self, i);
        j = 0;
        g = self + 0x4b20 + i * 0x530;
        q2 = arr + i;
        row2 = tbl + k * 6;
        while (j < 4) {
            int m = func_ov003_02227138(self, i, j);
            int *e = row2 + j;
            if (func_020555a4(g + j * 0x14c + 8, m, data_ov003_0223cf74, e[1], *q2, y, 2) == 0) {
                return 0;
            }
            j++;
        }
    }
    return 1;
}
