/* func_ov003_02226900 @ 0x02226900, 0x78 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *data_021fbe94;
extern void func_020e993c(void *h, void *p);

void func_ov003_02226900(void *self, void **a, void **b, void **c)
{
    void *h;
    int i;
    int j;
    h = data_021fbe94;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 6; j++) {
            if (*a) {
                func_020e993c(h, *a);
                *a = 0;
            }
            a++;
        }
    }
    for (i = 0; i < 3; i++) {
        if (*b) {
            func_020e993c(h, *b);
            *b = 0;
        }
        if (*c) {
            func_020e993c(h, *c);
            *c = 0;
        }
        b++;
        c++;
    }
}
