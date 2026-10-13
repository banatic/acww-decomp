/* func_ov003_0222703c @ 0x0222703c, 0x70 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov003_02227170(void *self, int k);
extern void *func_ov003_022270ac(void *self, int i);
extern int func_ov003_02227324(void *self, void **dst, void **mid, void **src, int n);

int func_ov003_0222703c(void *self, void **a, void **b)
{
    int done[3];
    int i, k;
    int idx;
    i = 0;
    do {
        done[i] = 0;
        i++;
    } while (i < 3);
    for (k = 0; k < 3; k++) {
        idx = func_ov003_02227170(self, k);
        if (done[idx] == 0) {
            if (!func_ov003_02227324(self, a + idx * 6, b + idx * 6, func_ov003_022270ac(self, idx), 6)) {
                return 0;
            }
            done[idx] = 1;
        }
    }
    return 1;
}
