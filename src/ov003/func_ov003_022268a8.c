/* func_ov003_022268a8 @ 0x022268a8, 0x58 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *data_021fbe94;
void func_020e993c(void *p, int q);

void func_ov003_022268a8(void *a, int *b, int *c, int *d)
{
    void *g = data_021fbe94;
    int i;
    for (i = 0; i < 6; i++) {
        if (*b != 0) {
            func_020e993c(g, *b);
            *b = 0;
        }
        b++;
    }
    if (*c != 0) {
        func_020e993c(g, *c);
        *c = 0;
    }
    if (*d != 0) {
        func_020e993c(g, *d);
        *d = 0;
    }
}
