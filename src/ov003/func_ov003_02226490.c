/* func_ov003_02226490 @ 0x02226490, 0x84 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *data_ov003_02239d28[];
extern void *data_ov003_0223cf74;
extern int func_020555a4(void *rec, void *g1, void *g2, void *v, void *y, int *p, int q);

int func_ov003_02226490(char *self, void **a, void **b)
{
    int i;
    int j;
    for (i = 0; i < 2; i++) {
        void **p;
        char *base;
        j = 0;
        p = &data_ov003_02239d28[i];
        base = self + 0x2df0 + i * 0x138;
        while (j < 2) {
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
