/* func_ov095_0229c104 @ 0x0229c104, 0x2e bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov095_022999b0(void *a, int b);
extern void func_ov095_022999a0(void *a, int b);
extern void func_ov095_0229c22c(void *a, int b, int c, int d);

void func_ov095_0229c104(void *a, int b)
{
    if (func_ov095_022999b0(a, 0x20)) {
        func_ov095_022999a0(a, 0x20);
        func_ov095_0229c22c(a, 2, b, 1);
    }
}
