/* func_ov109_0229cab0 @ 0x0229cab0, 0x2e bytes, Thumb, module ov109
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov109_0229ccb4(void *a, int b);
extern int func_ov109_0229cc98(void *a, int b);
extern int func_ov094_0229a69c(void *p, int v);

int func_ov109_0229cab0(void *a, int b)
{
    if (func_ov109_0229ccb4(a, b)) {
        int v = func_ov109_0229cc98(a, b);
        return func_ov094_0229a69c((char *) a + 0xcc, v);
    }
    return 1;
}
