/* func_ov003_02226874 @ 0x02226874, 0x34 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *data_021fbe94;
void func_020e993c(void *p, int q);

void func_ov003_02226874(void *a, int *b, int *c)
{
    void *g = data_021fbe94;
    if (*b != 0) {
        func_020e993c(g, *b);
        *b = 0;
    }
    if (*c != 0) {
        func_020e993c(g, *c);
        *c = 0;
    }
}
