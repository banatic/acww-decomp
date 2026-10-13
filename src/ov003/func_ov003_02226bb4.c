/* func_ov003_02226bb4 @ 0x02226bb4, 0x60 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *data_ov003_02239c8c;
extern void *data_ov003_0223cf74;
extern int func_020555a4(void *rec, void *g1, void *g2, void *x, void *y, int *ip, int k);

int func_ov003_02226bb4(char *self, void **a, void **b)
{
    int i;
    for (i = 0; i < 3; i++) {
        if (func_020555a4(self + 0x1014 + i * 0x9c, data_ov003_02239c8c, data_ov003_0223cf74, *a, *b, &i, 1) == 0) {
            return 0;
        }
    }
    return 1;
}
