/* func_ov003_022263b4 @ 0x022263b4, 0x84 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *data_021fbe94;
extern void func_020e993c(void *h, void *p);

void func_ov003_022263b4(void *self, void **a, void **b, void **c, void **d)
{
    void *h;
    int i;
    h = data_021fbe94;
    for (i = 0; i < 4; i++) {
        if (*a) {
            func_020e993c(h, *a);
            *a = 0;
        }
        if (*b) {
            func_020e993c(h, *b);
            *b = 0;
        }
        a++;
        b++;
    }
    for (i = 0; i < 2; i++) {
        if (*c) {
            func_020e993c(h, *c);
            *c = 0;
        }
        if (*d) {
            func_020e993c(h, *d);
            *d = 0;
        }
        c++;
        d++;
    }
}
