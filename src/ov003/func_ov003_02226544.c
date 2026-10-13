/* func_ov003_02226544 @ 0x02226544, 0x90 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *data_ov003_0223a068[];
extern int data_ov003_02236afc[];
extern void *data_ov003_0223cf74;
extern int func_020555a4(void *rec, void *g1, void *g2, void *v, void *y, int *p, int q);

int func_ov003_02226544(char *self, void **a, void **b)
{
    int i;
    int j;
    for (i = 0; i < 4; i++) {
        void **p;
        char *base;
        int n;
        j = 0;
        p = &data_ov003_0223a068[i];
        base = self + 0x1590 + i * 0x618;
        n = data_ov003_02236afc[i];
        while (j < n) {
            if (func_020555a4(base + j * 0x9c, *p, data_ov003_0223cf74, *a, *b, &j, 1) == 0) {
                return 0;
            }
            j++;
        }
        a++;
        b++;
    }
    return 1;
}
